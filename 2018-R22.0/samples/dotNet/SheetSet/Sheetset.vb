' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

'
Option Explicit On
Imports ACSMCOMPONENTS22Lib

Public Class Sheetset

    Dim sheetCount As Integer
    Dim sheetSetMgr As IAcSmSheetSetMgr
    Dim sheetset As IAcSmSheetSet
    Dim sheetdb As IAcSmDatabase
    Dim eventHndlr As EventHandler
    Dim eventSSMCookie As Long
    Dim eventDbCookie As Long
    Dim eventSSetCookie As Long
    Dim dwtLayoutref As New AcSmAcDbLayoutReference 'default DWT
    Dim fileRef As New AcSmFileReference 'default sheet location

    Function isInitialized() As Boolean
        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

        If sheetSetMgr Is Nothing Then
            ed.WriteMessage("\nSheetset manager not initialized!!")
            isInitialized = False
        End If

        If sheetset Is Nothing Then
            ed.WriteMessage("\nSheetset not initialized!!")
            isInitialized = False
        End If

        If sheetdb Is Nothing Then
            ed.WriteMessage("\nSheetset database not initialized!!")
            isInitialized = False
        End If

        isInitialized = True
    End Function

    Public Sub CreateSheetSet(ByVal name As String, _
    ByVal path As String, _
    ByVal desc As String, _
    Optional ByVal dwtName As String = "", _
    Optional ByVal dwtPath As String = "", _
    Optional ByVal defaultSheetLoc As String = "")

        On Error Resume Next
        'Release previous db and sheet set
        sheetdb = Nothing
        sheetset = Nothing

        Dim fullPath As String
        Dim pos As Integer

        pos = Len(path)

        'check to see if user entered '\' for path at the end of the string
        'if not, append it
        If InStr(pos - 1, path, "\") = pos Then
            fullPath = path & name & ".dst"
        Else
            fullPath = path & "\" & name & ".dst"
        End If


        'Create a new database overwriting existing sheetset file
        sheetdb = sheetSetMgr.CreateDatabase(fullPath, "", True)

        'Lock the database before doing any operation on it
        Call LockDatabase()

        'Get the sheet set from the database
        sheetset = sheetdb.GetSheetSet

        'Set name and description
        sheetset.SetName(name)
        sheetset.SetDesc("This is my sheet set " & name & ".dst")

        If Len(dwtPath) > 0 Then
            dwtLayoutref = New AcSmAcDbLayoutReference
            dwtLayoutref.InitNew(sheetset)
            dwtLayoutref.SetName(dwtName)
            dwtLayoutref.SetFileName(dwtPath + "\" + dwtName)
            dwtLayoutref.SetName("Sheet")

            'Set default dwg template
            sheetset.SetDefDwtLayout(dwtLayoutref)
        End If

        If Len(defaultSheetLoc) > 0 Then
            fileRef = New AcSmFileReference
            fileRef.InitNew(sheetset)
            fileRef.SetFileName(defaultSheetLoc)

            'set default sheet location
            sheetset.SetNewSheetLocation(fileRef)
        End If

        'Unlock database
        Call UnlockDatabase()

        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
        ed.WriteMessage("\nNew sheet set " & fullPath & " created")
        Autodesk.AutoCAD.ApplicationServices.Application.UpdateScreen()

    End Sub


    Function AddSheet(ByVal parentCategory As IAcSmSubset, _
    ByVal sheetName As String, _
    ByVal sheetDesc As String, _
    Optional ByVal layoutName As String = "", _
    Optional ByVal layoutDWGPath As String = "") As IAcSmSheet

        On Error Resume Next

        Dim newSheet As AcSmSheet

        If isInitialized() = False Then
            AddSheet = Nothing
            Exit Function
        End If

        'Lock the database first
        LockDatabase()

        If parentCategory Is Nothing Then
            'category to insert is the sheet set root
            parentCategory = sheetset
        End If

        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
        If layoutName = "" Then
            If sheetset.GetDefDwtLayout Is Nothing Or sheetset.GetNewSheetLocation Is Nothing Then
                ed.WriteMessage("\nCannot add sheet :" & sheetName & vbCrLf)
                Autodesk.AutoCAD.ApplicationServices.Application.UpdateScreen()
                AddSheet = Nothing
                Exit Function
            Else
                'Create a fresh sheet
                newSheet = parentCategory.AddNewSheet(sheetName, sheetDesc)
                newSheet.SetTitle(sheetName)
                ' Now insert the sheet
                parentCategory.InsertComponent(newSheet, Nothing)
            End If
        Else
            'Create a sheet based on a layout
            Dim layoutRef As New AcSmAcDbLayoutReference

            layoutRef.InitNew(sheetset)

            'Set layout name and file name
            layoutRef.SetName(layoutName)
            layoutRef.SetFileName(layoutDWGPath)

            'Import a sheet based on a layout into the category
            newSheet = parentCategory.ImportSheet(layoutRef)

            'Now insert the sheet
            parentCategory.InsertComponent(newSheet, Nothing)

        End If

        'Increment sheet number
        sheetCount = sheetCount + 1

        'Give the new sheet a number based on sheet count
        newSheet.SetNumber(sheetCount)

        'Unlock database
        UnlockDatabase()

        'retrun new sheet
        AddSheet = newSheet

    End Function

    Public Sub LockDatabase()
        On Error Resume Next
        If isInitialized() = False Then
            Exit Sub
        End If
        Dim lockStatus As AcSmLockStatus
        lockStatus = sheetdb.GetLockStatus

        If lockStatus = 0 Then
            sheetdb.LockDb(sheetdb)
        End If

    End Sub

    Public Sub UnlockDatabase()
        On Error Resume Next
        If isInitialized() = False Then
            Exit Sub
        End If
        Dim lockStatus As AcSmLockStatus
        If lockStatus = AcSmLockStatus.AcSmLockStatus_Locked_Local Or AcSmLockStatus.AcSmLockStatus_Locked_Remote Then
            sheetdb.UnlockDb(sheetdb)
        End If
    End Sub

    Function AddSheetCategory(ByVal name As String, _
    ByVal desc As String, _
    ByVal parentCat As IAcSmSubset) As IAcSmSubset

        On Error Resume Next

        If isInitialized() = False Then
            AddSheetCategory = Nothing
            Exit Function
        End If

        Dim newCat As AcSmSubset

        If parentCat Is Nothing Then
            'parent category is the sheet set root
            parentCat = sheetset
        End If

        'Lock database before we add a category
        LockDatabase()
        newCat = parentCat.CreateSubset(name, desc)
        'Unlock database
        UnlockDatabase()

        'return the newly created category
        AddSheetCategory = newCat

    End Function
    ' List all sheets and categories at the command line
    Public Sub List(ByVal db As IAcSmDatabase)

        On Error Resume Next

        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
        Dim iter As IAcSmEnumPersist
        Dim Item As IAcSmPersist
        Dim sheet As IAcSmSheet
        Dim subset As IAcSmSubset
        Dim cpbag As AcSmCustomPropertyBag
        Dim name As String
        name = Nothing
        Dim desc As String
        Dim value As String

        iter = db.GetEnumerator
        Item = iter.Next

        Do While Not Item Is Nothing
            sheet = Item
            subset = Item
            cpbag = Item

            'If Not subset Is Nothing Then
            If Item.GetTypeName = "AcSmSubset" Then
                'list the category (subset)
                name = subset.GetName
                desc = subset.GetDesc
                ed.WriteMessage("\n-------------------------------" & vbCrLf)
                ed.WriteMessage("\nSubSet Name :" & name & vbCrLf)
                ed.WriteMessage("\nSubSet Desc :" & desc & vbCrLf)
                ed.WriteMessage("\n-------------------------------" & vbCrLf)

                'ElseIf Not sheet Is Nothing Then
            ElseIf Item.GetTypeName = "AcSmSheet" Then
                'list the sheet
                name = sheet.GetName
                desc = sheet.GetDesc
                ed.WriteMessage("\nsheet Name :" & name & vbCrLf)
                ed.WriteMessage("\nsheet Desc :" & desc & vbCrLf)

            ElseIf Item.GetTypeName = "AcSmCustomPropertyBag" Then

                'Iterate through custom properties
                Dim propIter As IAcSmEnumProperty
                propIter = cpbag.GetPropertyEnumerator

                Dim propName As String
                Dim propval As AcSmCustomPropertyValue
                Do While True
                    propval = Nothing
                    propName = ""
                    propIter.Next(name, propval)
                    If propName = "" Then Exit Do 'jump out of loop

                    If Not IsDBNull(propval) And Not IsReference(propval) Then
                        ed.WriteMessage("\nProperty  " & propName & " : " & propval.GetValue & " " & vbCrLf)
                    End If
                Loop
            End If

            Item = iter.Next
        Loop

        Autodesk.AutoCAD.ApplicationServices.Application.UpdateScreen()

    End Sub
    Public Sub AddCalloutBlock(ByVal blockname As String, _
    ByVal dwg As String)

        On Error Resume Next
        If isInitialized() = False Then
            Exit Sub
        End If

        LockDatabase()
        Dim calloutBlocks As IAcSmCalloutBlocks
        Dim calloutRef As New AcSmAcDbBlockRecordReference

        calloutBlocks = sheetset.GetCalloutBlocks

        calloutRef.InitNew(sheetdb)
        calloutRef.SetFileName(dwg)
        calloutRef.SetName(blockname)

        calloutBlocks.Add(calloutRef)
        UnlockDatabase()

    End Sub

    Public Sub AddLabelBlock(ByVal blockname As String, _
    ByVal dwg As String)

        On Error Resume Next

        If isInitialized() = False Then
            Exit Sub
        End If

        LockDatabase()

        Dim labelRef As New AcSmAcDbLayoutReference
        labelRef.InitNew(sheetdb)
        labelRef.SetFileName(dwg)
        labelRef.SetName(blockname)

        sheetset.SetDefLabelBlk(labelRef)
        UnlockDatabase()
    End Sub

    Public Sub AddResourceFileLocation(ByVal resource As String)
        On Error Resume Next

        If isInitialized() = False Then
            Exit Sub
        End If

        LockDatabase()
        Dim resources As IAcSmResources
        Dim fileRef As New AcSmFileReference

        resources = sheetset.GetResources
        fileRef.InitNew(sheetdb)
        fileRef.SetFileName(resource)

        resources.Add(fileRef)
        UnlockDatabase()
    End Sub
    Function AddSheetSelectionSet(ByVal name As String, _
    ByVal desc As String) As IAcSmSheetSelSet

        On Error Resume Next

        If isInitialized() = False Then
            AddSheetSelectionSet = Nothing
            Exit Function
        End If

        'lock database
        LockDatabase()

        Dim sheetSelSets As IAcSmSheetSelSets
        sheetSelSets = sheetset.GetSheetSelSets
        Dim sheetSelSet As IAcSmSheetSelSet
        sheetSelSet = Nothing

        sheetSelSets.Add(name, desc, sheetSelSet)

        'unlock database
        UnlockDatabase()

        'return the selection set
        AddSheetSelectionSet = sheetSelSet

    End Function

    Public Sub AddCustomProperty(ByVal key As String, _
    ByVal value As String, _
    ByVal comp As IAcSmComponent, _
    ByVal propFlags As PropertyFlags)
        On Error Resume Next

        If isInitialized() = False Then
            Exit Sub
        End If

        LockDatabase()

        Dim bag As IAcSmCustomPropertyBag
        If comp Is Nothing Then
            comp = sheetset
        End If

        bag = comp.GetCustomPropertyBag

        Dim propval As New AcSmCustomPropertyValue
        propval.InitNew(bag)

        propval.SetFlags(propFlags)
        propval.SetValue(value)

        bag.SetProperty(key, propval)

        UnlockDatabase()
    End Sub
    Public Sub NotifyStart()

        On Error Resume Next

        If isInitialized() = False Then
            Exit Sub
        End If

        If Not eventHndlr Is Nothing Then
            Exit Sub
        End If

        eventHndlr = New EventHandler
        'register for sheet set manager events
        eventSSMCookie = sheetSetMgr.Register(eventHndlr)

        'register database events
        eventDbCookie = sheetdb.Register(eventHndlr)

        'register for sheet set events
        eventSSetCookie = sheetset.Register(eventHndlr)

    End Sub
    Public Sub NotifyEnd()
        On Error Resume Next
        If isInitialized() = False Then
            Exit Sub
        End If

        sheetSetMgr.Unregister(eventSSMCookie)
        sheetdb.Unregister(eventDbCookie)
        sheetset.Unregister(eventSSetCookie)

        eventHndlr = Nothing
    End Sub
    Function GetSheetSet() As IAcSmSheetSet
        GetSheetSet = sheetset
    End Function

    Public Sub CleanUp(ByVal err As String)
        On Error Resume Next
        If sheetdb Is Nothing Then
            Exit Sub
        End If

        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
        ed.WriteMessage("\n" & err & vbCrLf)

        Dim lockStat As AcSmLockStatus
        lockStat = sheetdb.GetLockStatus
        If lockStat = AcSmLockStatus.AcSmLockStatus_Locked_Local Or AcSmLockStatus.AcSmLockStatus_Locked_Remote Then
            sheetdb.UnlockDb(sheetdb)
            sheetdb = Nothing
            sheetset = Nothing
            sheetSetMgr = Nothing
            eventHndlr = Nothing
            dwtLayoutref = Nothing
            fileRef = Nothing
        End If

    End Sub

    Public Sub New()
        On Error Resume Next
        sheetCount = 0
        'Get the sheet set manager
        sheetSetMgr = New AcSmSheetSetMgr
    End Sub

    Protected Overrides Sub Finalize()
        On Error Resume Next
        sheetdb = Nothing
        sheetset = Nothing
        sheetSetMgr = Nothing
        eventHndlr = Nothing
        dwtLayoutref = Nothing
        fileRef = Nothing
    End Sub

End Class
