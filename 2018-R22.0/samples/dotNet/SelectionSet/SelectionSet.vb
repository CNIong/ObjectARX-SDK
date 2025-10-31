' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   


Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.EditorInput

<Assembly: ExtensionApplication(Nothing)> 
<Assembly: CommandClass(GetType(Selection.AcEdSSGetCommand))> 

Namespace Selection
    _

    Public Class AcEdSSGetCommand

        Shared SelentityCount As Integer = 0
        Shared UseThisSelectionResult As PromptSelectionResult
        Shared UseThisSelectionOption As PromptSelectionOptions = Nothing

        'This command does a simple selection and ignores all 
        'entities other than red circles
        <CommandMethod("SSet")> _
        Public Sub ssGetFilter()
            'Setup
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor

            'Declare our filter entries this way.
            'We build them the same way in ObjectARX.
            'DxfCode.Start (equal to 0) - This is for 'Entity Name'
            'DxfCode.Color is for ACI color - 1 = Red
            Dim values() As TypedValue = { _
                New TypedValue(DxfCode.Start, "CIRCLE"), _
                New TypedValue(DxfCode.Color, 1) _
                }
            Dim sfilter As New SelectionFilter(values) ' Create the filter using our values...

            'Set the selection options
            Dim SelOpts As New PromptSelectionOptions()
            SelOpts.MessageForAdding = "Select Red Circles:"
            SelOpts.AllowDuplicates = True
            'Make the selection:
            Dim res As PromptSelectionResult = ed.GetSelection(SelOpts, sfilter)

            If Not res.Status = PromptStatus.OK Then Return

            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
            Dim idarray As ObjectId() = SS.GetObjectIds()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim id As ObjectId
                For Each id In idarray
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForRead, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                Next id
            Finally
                myT.Dispose()
            End Try
        End Sub

        'This command allows only a single entity to be picked
        <CommandMethod("single")> _
        Public Sub singlePick()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim Opts As New PromptSelectionOptions()
            Opts.SingleOnly = True
            Opts.MessageForAdding = "Select a single entity"
            Dim res As PromptSelectionResult = ed.GetSelection(Opts)
            If res.Status = PromptStatus.Error Then
                Return
            End If
            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
            Dim idarray As ObjectId() = SS.GetObjectIds()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager

            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim id As ObjectId
                For Each id In idarray
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                Next id
            Finally
                myT.Dispose()
            End Try
        End Sub 'singlePick


        'This command demonstrates Implied pick
        <CommandMethod("Implied", CommandFlags.UsePickSet)> _
        Public Sub ImpliedPick()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim res As PromptSelectionResult = ed.SelectImplied()
            If res.Status = PromptStatus.Error Then Return
            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
            Dim idarray As ObjectId() = SS.GetObjectIds()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager

            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim id As ObjectId
                For Each id In idarray
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                Next id
            Finally
                myT.Dispose()
            End Try
        End Sub 'ImpliedPick


        'This command demonstrates the Cwindow Selection
        <CommandMethod("CWindow")> _
       Public Sub CrossWindow()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim res As PromptSelectionResult = ed.SelectCrossingWindow(New Point3d(1.0, 1.0, 0), New Point3d(10.0, 10.0, 0))
            If res.Status = PromptStatus.Error Then
                Return
            End If
            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
            Dim idarray As ObjectId() = SS.GetObjectIds()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim id As ObjectId
                For Each id In idarray
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                Next id
            Finally
                myT.Dispose()
            End Try
        End Sub 'CrossWindow


        'This command demonstrates CPolygon selection
        <CommandMethod("CPolygon")> _
        Public Sub CrossPlygon()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim values(4) As Point3d
            values(0) = New Point3d(1.0, 1.0, 0.0)
            values(1) = New Point3d(1.0, 50.0, 0.0)
            values(2) = New Point3d(50.0, 50.0, 0.0)
            values(3) = New Point3d(50.0, 1.0, 0.0)

            Dim polygon As New Point3dCollection(values)
            Dim res As PromptSelectionResult = ed.SelectCrossingPolygon(polygon)
            If res.Status = PromptStatus.Error Then
                Return
            End If
            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
            Dim idarray As ObjectId() = SS.GetObjectIds()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim id As ObjectId
                For Each id In idarray
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                Next id
            Finally
                myT.Dispose()
            End Try
        End Sub 'CrossPlygon

        'This command has a number of keywords attached to the selection.
        'Based on the keyword that user enters, it does either fence,window,windowpolygon,
        'lastentitySelection,PreviousSelection
        <CommandMethod("OptionSel")> _
        Public Sub OptionSel()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim Opts As New PromptSelectionOptions()
            Opts.Keywords.Add("myFence")
            Opts.Keywords.Add("myWindow")
            Opts.Keywords.Add("myWpoly")
            ' Opts.Keywords.Add("Implied")
            Opts.Keywords.Add("myLastSel")
            Opts.Keywords.Add("myPrevSel")

            AddHandler Opts.KeywordInput, AddressOf handle_KeywordInput
            Dim res As PromptSelectionResult = ed.GetSelection(Opts)
            If res.Status = PromptStatus.OK Then
                Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                Dim idarray As ObjectId() = SS.GetObjectIds()
                Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
                Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager

                Dim myT As Transaction = tm.StartTransaction()
                Try
                    Dim id As ObjectId
                    For Each id In idarray
                        Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                        ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                    Next id
                Finally
                    myT.Dispose()
                End Try
            End If
        End Sub 'OptionSel

        Private Shared Sub handle_KeywordInput(ByVal sender As Object, ByVal e As SelectionTextInputEventArgs)
            If e.Input.CompareTo("myFence") = 0 Then
                Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                Dim values(4) As Point3d
                values(0) = New Point3d(5.0, 5.0, 0.0)
                values(1) = New Point3d(13.0, 15.0, 0.0)
                values(2) = New Point3d(12.0, 9.0, 0.0)
                values(3) = New Point3d(5.0, 5.0, 0.0)

                Dim Fence As New Point3dCollection(values)
                Dim res As PromptSelectionResult = ed.SelectFence(Fence)
                If res.Status = PromptStatus.Error Then
                    Return
                End If
                Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                Dim idarray As ObjectId() = SS.GetObjectIds()
                e.AddObjects(idarray)
            Else
                If e.Input.CompareTo("myWindow") = 0 Then
                    Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                    Dim res As PromptSelectionResult = ed.SelectWindow(New Point3d(1.0, 1.0, 0.0), New Point3d(30.0, 20.0, 0.0))
                    If res.Status = PromptStatus.Error Then
                        Return
                    End If
                    Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                    Dim idarray As ObjectId() = SS.GetObjectIds()
                    e.AddObjects(idarray)
                Else
                    If e.Input.CompareTo("myWpoly") = 0 Then
                        Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                        Dim values(4) As Point3d
                        values(0) = New Point3d(5.0, 5.0, 0.0)
                        values(1) = New Point3d(13.0, 15.0, 0.0)
                        values(2) = New Point3d(12.0, 9.0, 0.0)
                        values(3) = New Point3d(5.0, 5.0, 0.0)

                        Dim Polygon As New Point3dCollection(values)
                        Dim res As PromptSelectionResult = ed.SelectWindowPolygon(Polygon)
                        If res.Status = PromptStatus.Error Then
                            Return
                        End If
                        Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                        Dim idarray As ObjectId() = SS.GetObjectIds()
                        e.AddObjects(idarray)

                    Else
                        If e.Input.CompareTo("myLastSel") = 0 Then
                            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                            Dim res As PromptSelectionResult = ed.SelectLast()
                            If res.Status = PromptStatus.Error Then
                                Return
                            End If
                            Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                            Dim idarray As ObjectId() = SS.GetObjectIds()
                            e.AddObjects(idarray)
                        Else
                            If e.Input.CompareTo("myPrevSel") = 0 Then
                                Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                                Dim res As PromptSelectionResult = ed.SelectPrevious()
                                If res.Status = PromptStatus.Error Then
                                    Return
                                End If
                                Dim SS As Autodesk.AutoCAD.EditorInput.SelectionSet = res.Value
                                Dim idarray As ObjectId() = SS.GetObjectIds()
                                e.AddObjects(idarray)
                            End If
                        End If
                    End If
                End If
            End If
        End Sub


        'This command demonstrates some selection Related input context reactors.
        'It exercises promptingForSelection, PromptedForSelection and SelectionAdded
        'events of the editor.

        <CommandMethod("SSetReactors")> _
          Public Sub SSetAddFilterTest()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager

            Dim SelOpts As New PromptSelectionOptions()
            SelOpts.AllowDuplicates = True
            AddHandler ed.PromptingForSelection, AddressOf handle_promptSelectionOptions
            AddHandler ed.PromptedForSelection, AddressOf handle_promptSelectionResult
            AddHandler ed.SelectionAdded, AddressOf handle_SelectionAdded
            Dim SelRes As PromptSelectionResult = ed.GetSelection(SelOpts)
            RemoveHandler ed.SelectionAdded, AddressOf handle_SelectionAdded
            RemoveHandler ed.PromptingForSelection, AddressOf handle_promptSelectionOptions
            RemoveHandler ed.PromptedForSelection, AddressOf handle_promptSelectionResult


            If SelRes.Status = PromptStatus.OK Then
                Dim SS1 As Autodesk.AutoCAD.EditorInput.SelectionSet = SelRes.Value
                Dim idarray1 As ObjectId() = SS1.GetObjectIds()

                Dim myT As Transaction = tm.StartTransaction()
                Try
                    Dim id As ObjectId
                    For Each id In idarray1
                        Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                        ed.WriteMessage((ControlChars.Lf + "You selected: " + entity.GetType().FullName))
                    Next id
                Finally
                    myT.Dispose()
                End Try
            End If
        End Sub 'SSetAddFilterTest




        Private Shared Sub handle_SelectionAdded(ByVal sender As Object, ByVal e As SelectionAddedEventArgs)
            Dim ss As Autodesk.AutoCAD.EditorInput.SelectionSet = e.Selection
            SelentityCount += 1
            If SelentityCount = 2 Then
                e.Remove(0)
            End If
        End Sub 'handle_SelectionAdded

        Private Shared Sub handle_promptSelectionResult(ByVal sender As Object, ByVal e As PromptSelectionResultEventArgs)
            UseThisSelectionResult = e.Result
        End Sub 'handle_promptSelectionResult


        Private Shared Sub handle_promptSelectionOptions(ByVal sender As Object, ByVal e As PromptSelectionOptionsEventArgs)
            UseThisSelectionOption = e.Options
        End Sub 'handle_promptSelectionOptions

        'This command helps to use the previous selection options and selection Results
        'that we had during the execution of SSetReactors command. It demonstrates how to
        'use PromptingForSelection and PromptedForSelection events.
        <CommandMethod("useSelection")> _
         Public Sub UsingSelectionOptionsAndResults()

            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try

                Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
                If UseThisSelectionOption Is Nothing Then
                    Exit Sub
                End If
                Dim res2 As PromptSelectionResult = ed.GetSelection(UseThisSelectionOption)
                Dim res1 As PromptSelectionResult = UseThisSelectionResult

                Dim SS2 As Autodesk.AutoCAD.EditorInput.SelectionSet = res2.Value

                Dim idarray2 As ObjectId() = SS2.GetObjectIds()
                Dim SS1 As Autodesk.AutoCAD.EditorInput.SelectionSet = res1.Value
                Dim idarray1 As ObjectId() = SS1.GetObjectIds()
                Dim id As ObjectId
                For Each id In idarray1
                    Dim entity As Entity = tm.GetObject(id, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected:" + entity.GetType().FullName))
                Next id

                Dim id1 As ObjectId
                For Each id1 In idarray2
                    Dim entity2 As Entity = tm.GetObject(id1, OpenMode.ForWrite, True)
                    ed.WriteMessage((ControlChars.Lf + "You selected:" + entity2.GetType().FullName))
                Next id1
            Finally
                    myT.Dispose()
            End Try
        End Sub 'UsingSelectionOptionsAndResults 

    End Class 'AcEdSSGetCommand
End Namespace 'Selection







