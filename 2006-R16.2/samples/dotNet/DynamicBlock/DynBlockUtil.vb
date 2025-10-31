' Copyright 2004 by Autodesk, Inc.

'Permission to use, copy, modify, and distribute this software in
'object code form for any purpose and without fee is hereby granted, 
'provided that the above copyright notice appears in all copies and 
'that both that copyright notice and the limited warranty and
'restricted rights notice below appear in all supporting 
'documentation.

'AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
'AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
'MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
'DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
'UNINTERRUPTED OR ERROR FREE.

'Use, duplication, or disclosure by the U.S. Government is subject to 
'restrictions set forth in FAR 52.227-19 (Commercial Computer
'Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
'(Rights in Technical Data and Computer Software), as applicable.

Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.DatabaseServices

Namespace DynamicBlock

    'some useful constants
    Public Enum PropTypeCode
        RTREAL = 40 'kDouble or AcDb::kDxfReal ''5001
        RTSHORT = 70 ' kShort or AcDb::kDxfInt16 ''5003
        RTSTR = 1 'kString or AcDb::kDxfText ''5005
        'The following are not used in Rio
        RTNONE = -9999 'kNone or AcDb::kDxfInvalid ''5000
        RTPOINT = 10 'kPoint2d or AcDb::kDxfXCoord ''5002
        RTENAME = 91 'kOldId or AcDb::kDxfInt32+1 ''5006
        RT3DPOINT = 11 'kPoint3d or AcDb::kDxfXCoord+1 ''5009
        RTLONG = 90 'kLong or AcDb::kDxfInt32 ''5010
    End Enum

    ' This is a wrapper  for DynamicBlockReferenceProperty class
    ' It returns a string for the Value and PropertyType properties
    Public Class DynBlkRefProp

        Dim m_prop As DynamicBlockReferenceProperty

        Public Sub SetProp(ByRef prop As DynamicBlockReferenceProperty)
            m_prop = prop
        End Sub

        Public ReadOnly Property PropertyName() As String
            Get
                Return m_prop.PropertyName
            End Get
        End Property

        Public ReadOnly Property PropertyType() As String
            Get
                Return DynBlockUtil.PropTypeToString(m_prop.PropertyTypeCode)
            End Get
        End Property

        Public Property Value() As String
            Get
                If m_prop.Value Is Nothing Then
                    Return ""
                Else
                    Return m_prop.Value.ToString
                End If
            End Get
            Set(ByVal Value As String)
                If m_prop.ReadOnly = True Then
                    MessageBox.Show("Property is read-only")
                Else
                    Try
                        Select Case m_prop.PropertyTypeCode
                            Case Is = PropTypeCode.RTNONE
                            Case Is = PropTypeCode.RTSHORT
                                m_prop.Value = System.Convert.ToInt16(Value)
                            Case Is = PropTypeCode.RTLONG
                                m_prop.Value = System.Convert.ToInt64(Value)
                            Case Is = PropTypeCode.RTREAL
                                m_prop.Value = System.Convert.ToDouble(Value)
                            Case Is = PropTypeCode.RTENAME
                            Case Is = PropTypeCode.RTPOINT
                            Case Is = PropTypeCode.RT3DPOINT
                            Case Is = PropTypeCode.RTSTR
                                m_prop.Value = Value
                        End Select
                    Catch e As Exception
                        MessageBox.Show(e.Message)
                    End Try
                End If
            End Set
        End Property

        Public ReadOnly Property Description() As String
            Get
                Return m_prop.Description
            End Get
        End Property

    End Class

    ' Helper class for DynamicBlocks
    Public Class DynBlockUtil

        'Constructors
        Public Sub New()
            m_blockId = New ObjectId()
            m_propNameArray = New ArrayList()
            m_propTypeArray = New ArrayList()
            m_propValArray = New ArrayList()
            m_propDescArray = New ArrayList()
            m_props = New ArrayList()
            m_blockId = m_blockId.Null
            m_numProps = 0
        End Sub

        Public Sub New(ByVal blkId As ObjectId)
            Me.New()
            SetBlockId(blkId)
        End Sub


        ' ObjectId of block reference
        Dim m_blockId As New ObjectId()

        ' Dynamic Array of properties for each 'column' in the list view
        Dim m_propNameArray As ArrayList
        Dim m_propTypeArray As ArrayList
        Dim m_propValArray As ArrayList
        Dim m_propDescArray As ArrayList
        Dim m_numProps As Integer

        'Dynamic array of properties
        Dim m_props As ArrayList

        Public Function numItems() As Integer
            numItems = m_numProps
        End Function

        'Methods
        Public Sub SetBlockId(ByVal blkId As ObjectId)
            m_blockId = blkId
            ' Immediately build the list
            BuildPropertyList()
        End Sub

        ' builds dynamic block's properties
        Private Sub BuildPropertyList()
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor
            ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

            If m_blockId.IsNull Then
                ed.WriteMessage(vbCrLf & "!Dynblockutil Error: m_blockId is null" & vbCrLf)
                Exit Sub
            End If

            'Start with zero props
            m_numProps = 0

            'Iterate through the dynamic block and get all properties
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            Dim trans As Autodesk.AutoCAD.DatabaseServices.Transaction = tm.StartTransaction

            Dim obj As DBObject
            Dim blkRef As BlockReference
            Dim dynBlkRefProps As DynamicBlockReferencePropertyCollection
            Dim dynBlkRefProp As DynamicBlockReferenceProperty

            Try
                obj = tm.GetObject(m_blockId, OpenMode.ForWrite)
                If TypeOf obj Is BlockReference Then
                    blkRef = obj
                    'check if this is a dynamic block
                    If blkRef.IsDynamicBlock = True Then
                        ed.WriteMessage(vbCrLf & "Dynamic Block ObjectId = " & m_blockId.OldId & vbCrLf)
                    Else
                        ed.WriteMessage(vbCrLf & "Error! Object not a dynamic block ")
                        Exit Try
                    End If
                Else
                    Exit Try
                End If

                dynBlkRefProps = blkRef.DynamicBlockReferencePropertyCollection

                For Each dynBlkRefProp In dynBlkRefProps

                    Dim dynProp As New DynBlkRefProp()
                    dynProp.SetProp(dynBlkRefProp)
                    ' Add to m_props array
                    m_props.Add(dynProp)

                    If dynBlkRefProp.PropertyName Is Nothing Then
                        m_propNameArray.Add("")
                    Else
                        m_propNameArray.Add(dynBlkRefProp.PropertyName)
                    End If

                    If dynBlkRefProp.PropertyTypeCode = 0 Then
                        m_propTypeArray.Add("")
                    Else
                        m_propTypeArray.Add(PropTypeToString(dynBlkRefProp.PropertyTypeCode))
                    End If

                    If dynBlkRefProp.Value Is Nothing Then
                        m_propValArray.Add("")
                    Else
                        m_propValArray.Add(dynBlkRefProp.Value.ToString())
                    End If

                    If dynBlkRefProp.Description Is Nothing Then
                        m_propDescArray.Add("")
                    Else
                        m_propDescArray.Add(dynBlkRefProp.Description)
                    End If

                    'Increment number of properties
                    m_numProps = m_numProps + 1
                Next

                trans.Commit()
            Catch e As Exception
                ed.WriteMessage(e.Message)
                trans.Abort()
            Finally
                If (Not trans Is Nothing) Then
                    trans.Dispose()
                End If
            End Try

        End Sub


        Public Function GetProps(ByRef props As ArrayList)
            props = m_props
        End Function

        'function to list properties of a dynamic block at the command line
        Public Sub ListDynBlock()
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor
            ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
            Try
                Dim i As Integer
                For i = 0 To m_numProps - 1
                    ed.WriteMessage("Property : " & i + 1 & vbCrLf)
                    ed.WriteMessage("   Name : " & m_propNameArray(i) & vbCrLf)
                    ed.WriteMessage("   Description  : " & m_propDescArray(i) & vbCrLf)
                    ed.WriteMessage("   Value Type = " & m_propTypeArray(i) & vbCrLf)
                    ed.WriteMessage("   Value  = " & m_propValArray(i) & vbCrLf & vbCrLf)
                Next
            Catch
                ed.WriteMessage("Oops!" & vbCrLf)
            End Try

        End Sub

        Public Shared Function PropTypeToString(ByVal propType As PropTypeCode) As String
            Select Case propType
                Case Is = PropTypeCode.RTNONE
                    Return "None"
                Case Is = PropTypeCode.RTSHORT
                    Return "Short"
                Case Is = PropTypeCode.RTLONG
                    Return "Long"
                Case Is = PropTypeCode.RTREAL
                    Return "Double"
                Case Is = PropTypeCode.RTENAME
                    Return "OldId"
                Case Is = PropTypeCode.RTPOINT
                    Return "Point2d"
                Case Is = PropTypeCode.RT3DPOINT
                    Return "Point3d"
                Case Is = PropTypeCode.RTSTR
                    Return "String"
            End Select
        End Function

        Public Shared Function SelectDynamicBlock(ByVal promptMsg As String) As ObjectId
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor
            ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            Dim trans As Autodesk.AutoCAD.DatabaseServices.Transaction = tm.StartTransaction

            Try
                Dim prOptions As Autodesk.AutoCAD.EditorInput.PromptEntityOptions _
                = New Autodesk.AutoCAD.EditorInput.PromptEntityOptions(vbCrLf & promptMsg & " : ")
                prOptions.SetRejectMessage(vbCrLf & "Selected entity must be a block reference")

                Dim prEntRes As Autodesk.AutoCAD.EditorInput.PromptEntityResult
                prOptions.AddAllowedClass(GetType(BlockReference), True)

                'ask user to select a block reference
                prEntRes = ed.GetEntity(prOptions)

                If Not (prEntRes.Status = Autodesk.AutoCAD.EditorInput.PromptStatus.OK) Then
                    Exit Try
                End If

                Dim blkRef As BlockReference
                blkRef = tm.GetObject(prEntRes.ObjectId, OpenMode.ForRead)

                If Not blkRef.IsDynamicBlock Then
                    MessageBox.Show("Block Reference not a dynamic block" & vbCrLf)
                    Exit Try
                End If
                trans.Commit()
                SelectDynamicBlock = blkRef.ObjectId
            Catch e As Exception
                ed.WriteMessage(e.Message)
                trans.Abort()
            Finally
                trans.Dispose()
            End Try
        End Function

    End Class


End Namespace

