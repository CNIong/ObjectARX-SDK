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