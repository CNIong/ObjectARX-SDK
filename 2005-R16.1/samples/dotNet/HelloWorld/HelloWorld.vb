' Hello World VB.NET sample
' by Cyrille Fauvel - Autodesk Developer Technical Services
' Copyright Autodesk (c) 2003

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

<Assembly: ExtensionApplication(GetType(HelloWorld.HelloWorldApp))> 
<Assembly: CommandClass(GetType(HelloWorldCommands))> 

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
            Dim tbBut3 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(3, "GetHello", "Hello World - Hello command", "_GETHELLO ")
            tbBut3.SetBitmaps(helloModulePath + "\tbBut1.bmp", helloModulePath + "\tbBut1.bmp")

        End Sub

    Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
    End Sub

    End Class

    Public Class HelloWorldCommands

        ' Defines a command which prompt a message on the AutoCAD command line
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLO")> _
        Public Function HelloCommand()
            Autodesk.AutoCAD.ApplicationServices.CommandLinePrompts.Message(vbNewLine + "Hello World!" + vbNewLine)
        End Function

        ' Defines a command which displays a Windows form
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLOFORM")> _
        Public Function HelloFormCommand()
            Dim dlg As New HellowWorldForm()
            dlg.ShowDialog()
        End Function

        ' Deinfes a command which adds a 'Hello World' MText object to Model Space, using transactions.
        <Autodesk.AutoCAD.Runtime.CommandMethod("ASDK", "HELLOTEXT", Autodesk.AutoCAD.Runtime.CommandFlags.Modal)> _
        Public Function HelloTextCommand()
            '   ObjectARX generally reports errors through return values.
            '   .NET uses exceptions (Note - VB.NET has far superior error handling to VB6)
            Dim text As MText
            Dim bt As BlockTable
            Dim btr As BlockTableRecord
            Try
                Dim db As Database = HostApplicationServices.WorkingDatabase
                Dim objId As ObjectId = db.BlockTableId
                '   open blocktable. Note ObjectId.Open() replaces acdbOpenObject etc
                bt = objId.Open(OpenMode.ForRead)
                objId = bt.Item(btr.ModelSpace)
                btr = objId.Open(OpenMode.ForWrite)
                '   Create new mtext and set text
                text = New MText()
                text.SetContents("Hello World!!")
                '   Append entity to model space
                btr.AppendEntity(text)
            Catch
                '   no error checking
            Finally '   Finally code is invoked whether there's an error or not
                '   No transactions this time, so close entities manually
                text.Close()
                btr.Close()
                bt.Close()
            End Try
        End Function

        '   This function demonstrates non-transaction DB modification and iterating model space
        '   Note - no significant error checking, so code could fall over
        <Autodesk.AutoCAD.Runtime.CommandMethod("ASDK", "GETHELLO", Autodesk.AutoCAD.Runtime.CommandFlags.Modal)> _
        Public Function GetHelloCommand()
            '   Declare variables
            Dim btr As BlockTableRecord
            Dim bt As BlockTable

            Try
                Dim db As Database = HostApplicationServices.WorkingDatabase
                Dim id As ObjectId = db.BlockTableId
                bt = id.Open(OpenMode.ForRead) '   open blocktable. Note ObjectId.Open() replaces acdbOpenObject etc
                id = bt.Item(btr.ModelSpace)
                btr = id.Open(OpenMode.ForRead)
                Dim obj As Object
                ' Loop through model space
                For Each id In btr
                    Try
                        obj = id.Open(OpenMode.ForRead)
                        '   Is it MText
                        If obj.GetType.ToString = "Autodesk.AutoCAD.DatabaseServices.MText" Then
                            Dim text As MText = obj
                            '   Output the text value to command line
                            CommandLinePrompts.Message(text.Contents & vbCrLf)
                        End If
                    Catch
                        '   No error handling
                        CommandLinePrompts.Message("Oops!!" & vbCrLf)
                    Finally
                        obj.Close()
                    End Try
                Next
            Catch
                CommandLinePrompts.Message("Oops!!" & vbCrLf)
            Finally
                bt.Close()
                btr.Close()
            End Try
        End Function

    End Class

End Namespace