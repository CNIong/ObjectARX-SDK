' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

' Hello World VB.NET sample
' by Cyrille Fauvel - Autodesk Developer Technical Services

Option Explicit On 

Imports System
Imports System.Type
Imports System.CLSCompliantAttribute
Imports System.Reflection
Imports System.Runtime.InteropServices

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Interop
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.EditorInput

<Assembly: ExtensionApplication(GetType(HelloWorld.HelloWorldApp))> 
<Assembly: CommandClass(GetType(HelloWorld.HelloWorldCommands))> 

Namespace HelloWorld

    Public Class HelloWorldApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
            ' Create an AutoCAD toolbar with 4 buttons linked to the 4 commands defined below

            Dim helloModule As System.Reflection.Module = System.Reflection.Assembly.GetExecutingAssembly().GetModules()(0)
            Dim helloModulePath As String = helloModule.FullyQualifiedName
            Try
                helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
                helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
            Catch
                MsgBox("Error with Module Path")
                Exit Sub
            End Try

            Dim acadApp As Autodesk.AutoCAD.Interop.AcadApplication = Autodesk.AutoCAD.ApplicationServices.Application.AcadApplication
            Dim hwTb As Autodesk.AutoCAD.Interop.AcadToolbar = acadApp.MenuGroups.Item(0).Toolbars.Add("Hello World!")
            Dim tbBut0 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(0, "Hello", "Hello World - Hello command", "_HELLO ")
            tbBut0.SetBitmaps(helloModulePath + "\tbBut0.bmp", helloModulePath + "\tbBut0.bmp")
            Dim tbBut1 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(1, "HelloForm", "Hello World - HelloForm command", "_HelloForm ")
            tbBut1.SetBitmaps(helloModulePath + "\tbBut1.bmp", helloModulePath + "\tbBut1.bmp")
            Dim tbBut2 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(2, "HelloText", "Hello World - Hello command", "_HELLOTEXT ")
            tbBut2.SetBitmaps(helloModulePath + "\tbBut0.bmp", helloModulePath + "\tbBut0.bmp")
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub

    End Class

    Public Class HelloWorldCommands

        ' Defines a command which prompt a message on the AutoCAD command line
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLO")> _
        Public Sub HelloCommand()
            Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage(vbNewLine + "Hello World!" + vbNewLine)
        End Sub

        ' Defines a command which displays a Windows form
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLOFORM")> _
        Public Sub HelloFormCommand()
            Dim dlg As New HellowWorldForm()
            Application.ShowModalDialog(dlg)
        End Sub

        ' Defines a command which adds a 'Hello World' MText object to Model Space
        <Autodesk.AutoCAD.Runtime.CommandMethod("ASDK", "HELLOTEXT", Autodesk.AutoCAD.Runtime.CommandFlags.Modal)> _
        Public Sub HelloTextCommand()
            '   ObjectARX generally reports errors through return values.
            '   .NET uses exceptions (Note - VB.NET has far superior error handling to VB6)

            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim trans As Transaction
            trans = db.TransactionManager.StartTransaction()
            Try
                '   Create new mtext and set text
                Dim text As MText = New MText()
                text.Contents = "Hello World!!"

                '   Append entity to model space
                Dim bt As BlockTable = trans.GetObject(db.BlockTableId, OpenMode.ForRead)
                Dim btr As BlockTableRecord = trans.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite)
                btr.AppendEntity(text)

                'Add the text to the transaction, and commit the changes.
                trans.AddNewlyCreatedDBObject(text, True)
                trans.Commit()
            Catch
                MsgBox("Error in Hello World")
            Finally 'Finally code is invoked whether there's an error or not
                'ensure that the mtext is diposed even if we throw
                'if we don't throw this does nothing
                trans.Dispose()
            End Try
        End Sub

    End Class

End Namespace