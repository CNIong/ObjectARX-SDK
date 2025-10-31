' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

Option Explicit On
Imports Autodesk.AutoCAD.Runtime
Imports ACSMCOMPONENTS22Lib

<Assembly: CommandClass(GetType(SSExample))> 

Public Class SSExample

    Sub Example_SSC()

        Dim sheetset As New Sheetset
        On Error Resume Next

        Dim sheet1 As IAcSmComponent
        Dim sheet2 As IAcSmComponent
        Dim sheet3 As IAcSmComponent
        Dim sheet4 As IAcSmComponent
        Dim categoryX As IAcSmComponent
        Dim categoryXX As IAcSmComponent

        Dim sheetSetName As String = ""
        Dim dwtPath As String
        Dim defSheetLoc As String
        Dim path As String


        Dim sFullPath As String = System.Windows.Forms.Application.ExecutablePath()
        Dim sExePath As String = System.IO.Directory.GetParent(sFullPath).FullName

        'This is the path where sheet1, sheet2 and sheet3 drawings are stored
        Dim sampleRootPath As String = sExePath & "\Sample\ActiveX\SheetSetVBA"

        Dim resourcePath As String
        resourcePath = sampleRootPath

        'Set the default sheet location same as resource path
        defSheetLoc = sampleRootPath

        'set the location to dwt for the sheet set
        dwtPath = sampleRootPath

        'Get the name for the sheet set from the user
        Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor
        Do While (sheetSetName = "")
            Dim stringOptions As Autodesk.AutoCAD.EditorInput.PromptStringOptions = New Autodesk.AutoCAD.EditorInput.PromptStringOptions("Enter the name of the sheet set(extension not needed): ")
            stringOptions.AllowSpaces = True

            Dim resString As Autodesk.AutoCAD.EditorInput.PromptResult = ed.GetString(stringOptions)
            If resString.Status = Autodesk.AutoCAD.EditorInput.PromptStatus.OK Then
                sheetSetName = resString.StringResult
            End If
        Loop

        'Get the path where sheet set will be created
        Dim oFolder1 As New System.Windows.Forms.FolderBrowserDialog()
        oFolder1.Description = "Select a path:"
        oFolder1.ShowNewFolderButton = True
        If oFolder1.ShowDialog() = Windows.Forms.DialogResult.OK Then
            path = oFolder1.SelectedPath
            If path = "" Then
                MsgBox("Path not selected... Exiting!!")
                Exit Sub
            End If
        Else
            MsgBox("Path not selected... Exiting!!")
            Exit Sub
        End If

        'Create a new sheet set
        sheetset.CreateSheetSet(sheetSetName, _
                                path, _
                                "This is my VBA sheet set", _
                                "IRD.dwt", _
                                dwtPath, _
                                defSheetLoc)

        'Exit if sheet set not created
        If sheetset.GetSheetSet Is Nothing Then
            MsgBox("Cannot create sheetset...Exiting!!")
            Exit Sub
        End If


        'start notifications
        sheetset.NotifyStart()

        'Add custom properties at sheet set level
        sheetset.AddCustomProperty("Custom Property 1", "XXXX", Nothing, PropertyFlags.CUSTOM_SHEETSET_PROP)
        sheetset.AddCustomProperty("Custom Property 2", "YYYY", Nothing, PropertyFlags.CUSTOM_SHEETSET_PROP)

        'Add resource file location
        sheetset.AddResourceFileLocation(resourcePath)

        'Add label block
        sheetset.AddLabelBlock("Label", resourcePath + "\" + "Label Block.dwg")

        'Add callout blocks
        sheetset.AddCalloutBlock("Right", resourcePath + "\" + "Pointer Blocks.dwg")
        sheetset.AddCalloutBlock("Left", resourcePath + "\" + "Pointer Blocks.dwg")
        sheetset.AddCalloutBlock("Up", resourcePath + "\" + "Pointer Blocks.dwg")
        sheetset.AddCalloutBlock("Down", resourcePath + "\" + "Pointer Blocks.dwg")


        'Add a category "category X" to sheet set root
        categoryX = sheetset.AddSheetCategory("Category X", _
                                                  "This is category X", _
                                                  Nothing) 'parent is sheet set root

        'Add a nested category under "category X"
        categoryXX = sheetset.AddSheetCategory("Nested Category XX", _
                                                 "This is nested category XX", _
                                                 categoryX) 'parent is categoryX


        'Add  sheet 1 to sheet set root
        sheet1 = sheetset.AddSheet(Nothing, _
                                       "Sheet 1", _
                                       "This is sheet1", _
                                       "Sheet 1", _
                                       resourcePath + "\" + "sheet1.dwg")

        'Add custom property for sheet 1

        sheetset.AddCustomProperty("ABCD", "####", sheet1, 2)

        'Add sheet2 based on a layout to category "category X"
        sheet2 = sheetset.AddSheet(categoryX, _
                                        "Sheet 2", _
                                        "This is sheet2", _
                                        "Sheet 2", _
                                        resourcePath + "\" + "sheet2.dwg")


        'Add sheet3 based on a layout to nested category "category XX"
        sheet3 = sheetset.AddSheet(categoryXX, _
                                        "Sheet 3", _
                                        "This is sheet3", _
                                        "Sheet 3", _
                                        resourcePath + "\" + "sheet3.dwg")

        ' Add a fresh sheet4 not based on any layout

        sheet4 = sheetset.AddSheet(Nothing, _
                                       "Fresh Sheet", _
                                       "This is a fresh sheet")
        'Add selection set
        Dim selset As IAcSmSheetSelSet
        selset = sheetset.AddSheetSelectionSet("My Selection Set", "This is my selection set")

        sheetset.LockDatabase()
        selset.Add(sheet1)
        selset.Add(sheet2)
        selset.Add(sheet3)
        sheetset.UnlockDatabase()

        'end notifications
        sheetset.NotifyEnd()
        Autodesk.AutoCAD.ApplicationServices.Application.UpdateScreen()
    End Sub

    ' Define command 'RunSampleSSC'
    <CommandMethod("RunSampleSSC")> _
    Public Sub RunSampleSSC()
        ' Type your code here
        Example_SSC()
    End Sub

End Class
