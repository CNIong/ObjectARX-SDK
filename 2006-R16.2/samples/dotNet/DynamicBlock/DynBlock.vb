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
Imports System.Type
Imports System.Reflection
Imports System.Windows.Forms
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.DatabaseServices


<Assembly: ExtensionApplication(GetType(DynamicBlock.DynamicBlockApp))> 
<Assembly: CommandClass(GetType(DynamicBlockCommands))> 

Namespace DynamicBlock

    Public Class DynamicBlockApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub

    End Class

    Public Class DynamicBlockCommands

        '''''''''''''''''''''' Command Dynlist ''''''''''''''''''''''''''''''''''''''''''''''''
        ' Lists all the properties of dynamic blocks in the drawing
        <Autodesk.AutoCAD.Runtime.CommandMethod("DYNLIST")> _
        Public Sub DynList()
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            Dim trans As Autodesk.AutoCAD.DatabaseServices.Transaction = tm.StartTransaction
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor
            ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

            Try
                'Iterate through Model Space and 
                'list the properties of all dynamic blocks
                Dim bt As BlockTable
                Dim msbtr As BlockTableRecord
                bt = tm.GetObject(db.BlockTableId, OpenMode.ForRead)
                msbtr = tm.GetObject(bt.Item(msbtr.ModelSpace), OpenMode.ForRead)

                Dim objId As ObjectId
                Dim obj As DBObject
                Dim blkRef As BlockReference

                For Each objId In msbtr
                    Dim dynblkUtil As New DynamicBlock.DynBlockUtil(objId)
                    dynblkUtil.ListDynBlock()
                Next
                
                trans.Commit()
            Catch e As Exception
                'aborts (or causes a "rollback" of) the transaction
                trans.Abort()
            Finally
                If (Not trans Is Nothing) Then
                    trans.Dispose()
                End If
            End Try

        End Sub
        '''''''''''''''''''''' End Command Dynlist ''''''''''''''''''''''''''''''''''''''''''''''''

        '''''''''''''''''''''' Command DynEdit ''''''''''''''''''''''''''''''''''''''''''''''''
        ' Allow user to edit properties of a dynamic block reference
        <Autodesk.AutoCAD.Runtime.CommandMethod("DYNEDIT")> _
        Public Sub DynEdit()
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            Dim trans As Autodesk.AutoCAD.DatabaseServices.Transaction = tm.StartTransaction

            Try
                Dim blkRefId As ObjectId
                Dim blkref As BlockReference
                blkRefId = DynBlockUtil.SelectDynamicBlock("Select a dynamic block to edit")
                If blkRefId.IsNull Then
                    ' Nothing selected
                    Exit Try
                End If
                'Open the block ref to keep it alive during edit
                blkref = tm.GetObject(blkRefId, OpenMode.ForRead)
                Dim Form As Forms.EditPropForm = New Forms.EditPropForm()
                Form.SetBlockId(blkRefId)
                Form.ShowDialog()
                trans.Commit()
            Catch e As Exception
                MessageBox.Show(e.Message)
                trans.Abort()
            Finally
                If (Not trans Is Nothing) Then
                    trans.Dispose()
                End If
            End Try
        End Sub
        '''''''''''''''''''''' End Command DynEdit ''''''''''''''''''''''''''''''''''''''''''''''''

        '''''''''''''''''''''' End Command DynFreeze ''''''''''''''''''''''''''''''''''''''''''''''''
        ' Converts the block to a static block
        <Autodesk.AutoCAD.Runtime.CommandMethod("DYNFREEZE")> _
        Public Sub FreezeBlock()
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim tm As Autodesk.AutoCAD.DatabaseServices.TransactionManager = db.TransactionManager
            Dim trans As Autodesk.AutoCAD.DatabaseServices.Transaction = tm.StartTransaction
            Try
                Dim blkRefId As ObjectId
                Dim blkRef As BlockReference
                blkRefId = DynBlockUtil.SelectDynamicBlock("Select a dynamic block to freeze")
                blkRef = tm.GetObject(blkRefId, OpenMode.ForWrite)
                If Not (blkRef Is Nothing) Then
                    blkRef.ConvertToStaticBlock()
                End If
                trans.Commit()
            Catch e As Exception
                MessageBox.Show(e.Message)
                trans.Abort()
            Finally
                If (Not trans Is Nothing) Then
                    trans.Dispose()
                End If
            End Try
        End Sub
        '''''''''''''''''''''' End Command DynFreeze ''''''''''''''''''''''''''''''''''''''''''''''''

    End Class

End Namespace