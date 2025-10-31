'(C) Copyright 2006-2008 by Autodesk, Inc. 
'
' Permission to use, copy, modify, and distribute this software in
' object code form for any purpose and without fee is hereby granted, 
' provided that the above copyright notice appears in all copies and 
' that both that copyright notice and the limited warranty and
' restricted rights notice below appear in all supporting 
' documentation.
'
' AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
' AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
' MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
' DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
' UNINTERRUPTED OR ERROR FREE.
'
' Use, duplication, or disclosure by the U.S. Government is subject to 
' restrictions set forth in FAR 52.227-19 (Commercial Computer
' Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
' (Rights in Technical Data and Computer Software), as applicable.
'

Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.GraphicsInterface
Imports Autodesk.AutoCAD.Colors
Imports Autodesk.AutoCAD.EditorInput
Imports Autodesk.AutoCAD.Windows


Imports Autodesk.SimpleSquare

Public Class SquareCommands

    'Command defined to run a managed jig to place our Simple Square object.
    <CommandMethod("JIGSQ")> _
    Public Sub JigSquare()

        Dim jig As New SquareJig
        If jig.Run <> PromptStatus.OK Then
            Exit Sub
        End If

        Dim acadDb As Database = HostApplicationServices.WorkingDatabase
        Dim trans As Transaction = acadDb.TransactionManager.StartTransaction
        Try
            Dim bt As BlockTable = trans.GetObject(acadDb.BlockTableId, OpenMode.ForRead)
            Dim btr As BlockTableRecord = trans.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite)

            'Demonstrate the events that we expose with our wrapper...this will get called whenever anyone modifies
            'the Square object on the AutoCAD screen or otherwise.
            AddHandler jig.Square.SquareModified, AddressOf OnSquareModified

            'Add the square to Model Space...
            btr.AppendEntity(jig.Square)
            trans.AddNewlyCreatedDBObject(jig.Square, True)
            trans.Commit()

        Catch ex As Exception
            MsgBox("Error during ADDSQ Command: " + ex.Message)
        Finally
            trans.Dispose()
        End Try
    End Sub

    'Here is the handler method we've subscribed to be called when the square object is modified.
    Public Sub OnSquareModified(ByVal id As ObjectId)

        'Define a buble window notification for this event...
        Dim bubbleWindow As New TrayItemBubbleWindow
        bubbleWindow.Text = id.ToString 'Just to identify the Square object uniquely...
        bubbleWindow.IconType = IconType.Information
        bubbleWindow.Title = "Square Object Modified!"

        'Show the bubble notification
        If (Autodesk.AutoCAD.ApplicationServices.Application.StatusBar.TrayItems.Count > 0) Then
            Autodesk.AutoCAD.ApplicationServices.Application.StatusBar.TrayItems(0).ShowBubbleWindow(bubbleWindow)
        End If
    End Sub

End Class


'Defines a class that is used to place our Simple Square object interactively on the AutoCAD screen.
Public Class SquareJig
    Inherits EntityJig
    Implements IDisposable

    Private Const SIN45 = 0.707106769F 'Used for some math below
    Private Const PI = 3.14159274F ' Used for some math below

    Private disposedValue As Boolean = False ' To detect redundant calls

    Private m_cursorPoint As Point3d
    Private m_jigSquare As MgSimpleSquare
    Private m_jigMode As Boolean = False
    Private m_insertionPoint As Point3d
    Private m_rotationPoint As Point3d

#Region "Public Properties"

    Public Property InsertionPoint() As Point3d
        Get
            Return m_insertionPoint
        End Get
        Set(ByVal value As Point3d)
            m_insertionPoint = value
        End Set
    End Property

    Public ReadOnly Property Square() As MgSimpleSquare
        Get
            Return m_jigSquare
        End Get
    End Property

#End Region

#Region "Public Methods"

    Public Sub New()
        'Construct the base class - passing in a square
        MyBase.New(New MgSimpleSquare)
        Try
            m_jigSquare = CType(Entity, MgSimpleSquare)
            If m_jigSquare Is Nothing Then
                Throw New ApplicationException("Could not create Square")
            End If

            m_jigSquare.SetDatabaseDefaults()
        Catch
            Throw
        End Try
    End Sub

    'This actually runs the jig - if it is successful it will return a status that we can
    'interpret within the SQJIG command to actually add the Square to the database.
    Public Function Run() As Autodesk.AutoCAD.EditorInput.PromptStatus
        Dim promptResult As PromptResult

        Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
        Dim pointOptions As New PromptPointOptions("Select Square center position")
        pointOptions.AllowNone = False
        pointOptions.AllowArbitraryInput = False

        Dim pointResult As PromptPointResult = ed.GetPoint(pointOptions)
        If pointResult.Status <> PromptStatus.OK Then
            Dispose(True)
            Return PromptStatus.Cancel
        End If

        m_jigSquare.Center = pointResult.Value

        promptResult = Application.DocumentManager.MdiActiveDocument.Editor.Drag(Me)

        If promptResult.Status <> PromptStatus.OK Then
            Dispose(True)
            Return promptResult.Status
        End If
        Return PromptStatus.OK
    End Function

#End Region

#Region "Protected Methods"

    Protected Overrides Sub Finalize()

        Me.Dispose(False)
        MyBase.Finalize()

    End Sub

    'Update - called to update the underlying jigged entity (our square).  
    'We interpret the cursor location the way we want - in our case it represents
    'a corner location - we use that to calculate each of the other points throug the Rotation and SideLength properties.
    Protected Overrides Function Update() As Boolean
        Try
            Dim square As MgSimpleSquare = CType(Entity, MgSimpleSquare)

            Dim vector As Vector2d = m_cursorPoint.GetVectorTo(square.Center).Convert2d(New Plane(square.Center, square.Normal()))
            ' Avoid using a zero length vector
            If vector.Length > 0.0 Then
                square.Rotation = vector.Angle() - (PI / 4)
                square.SideLength = vector.Length * SIN45 * 2
                Return True
            Else
                Return False
            End If
        Catch
            Throw
        End Try
    End Function

    'Sampler - called during each mouse-move during the jig placement.
    'We need only update the cursor location...
    Protected Overrides Function Sampler(ByVal prompts As JigPrompts) As SamplerStatus
        Try
            Dim jigOpts As New JigPromptPointOptions("Specify corner point: " + vbCrLf)
            jigOpts.UserInputControls = UserInputControls.NullResponseAccepted

            Dim dres As PromptPointResult = prompts.AcquirePoint(jigOpts)

            If Not m_cursorPoint.Equals(dres.Value) Then
                m_cursorPoint = dres.Value
                Return SamplerStatus.OK
            Else
                Return SamplerStatus.NoChange
            End If
        Catch
            Throw
        End Try
    End Function


#End Region


#Region " IDisposable"
    ' IDisposable
    Protected Overridable Sub Dispose(ByVal disposing As Boolean)
        If Not disposedValue Then
            If disposing Then
                If Not m_jigSquare Is Nothing Then
                    m_jigSquare.Dispose()
                    GC.SuppressFinalize(Me)
                End If
            End If
        End If
        disposedValue = True
    End Sub

    ' This code added by Visual Basic to correctly implement the disposable pattern.
    Public Sub Dispose() Implements IDisposable.Dispose
        ' Do not change this code.  Put cleanup code in Dispose(ByVal disposing As Boolean) above.
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
#End Region

End Class



