Option Explicit On 

Imports System
Imports System.Type
Imports System.CLSCompliantAttribute
Imports System.Reflection
Imports System.Runtime.InteropServices
Imports System.Windows.Forms

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.ApplicationServices

<Assembly: ExtensionApplication(GetType(DrawingBrowser.DrawingBrowserApp))> 
<Assembly: CommandClass(GetType(DrawingBrowserCommand))> 

Namespace DrawingBrowser

    Public Class DrawingBrowserApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub
    End Class

    Public Class DrawingBrowserCommand

        <Autodesk.AutoCAD.Runtime.CommandMethod("BrowseDWG")> _
        Public Function BrowseDrawing()

            Dim dlg As New BrowseDialog()
            dlg.Show()

            dlg.TreeView1.BeginUpdate()
            dlg.Cursor.Current = Cursors.AppStarting
            dlg.TreeView1.Nodes.Clear()

            Dim rootNode As TreeNode = dlg.TreeView1.Nodes.Add("Database")
            ParseDWG.fillIcons(dlg.TreeView1)

            Dim myT As Transaction = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction()
            rootNode.Text = HostApplicationServices.WorkingDatabase.Filename
            ParseDWG.ExtractObjectInfo(rootNode, HostApplicationServices.WorkingDatabase)
            myT.Commit()

            ParseDWG.Cleanup()

            dlg.Cursor.Current = Cursors.Default
            'dlg.TreeView1.ExpandAll()
            dlg.TreeView1.EndUpdate()

        End Function
    End Class

End Namespace