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

Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.EditorInput
Imports DBTransMan = Autodesk.AutoCAD.DatabaseServices.TransactionManager

'This application implements a command called GROUPTEST.         
'This command first prompts the user to select some entities that are placed into
'a group called "ASDK_GROUPTEST". Then it calls the function
'removeAllButLines() to iterate over the group and remove all the 
'entities that are not lines. Finally, it changes the remaining entities
'in the group to red. 
'
'To use Groups.dll:
'
'1. Start AutoCAD and open a new drawing.
'2. Type netload and select Groups.dll.
'3. Execute the GROUPTEST command.
'
'Autodesk references added to this project are the acdbmgd.dll and acmgd.dll .NET components,
'and the AutoCAD Type Library COM component.

<Assembly: CommandClass(GetType(GroupCommands))> 

Namespace DotNetAcDbGroup
    Public Class GroupCommands

        <CommandMethod("grouptest")> _
        Public Sub test1()
            Dim gpid As ObjectId
            Dim gp As New Group("grouptest", True)
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim dict As DBDictionary = tm.GetObject(db.GroupDictionaryId, OpenMode.ForWrite, True)
                gpid = dict.SetAt("ASDK_GROUPTEST", gp)
                tm.AddNewlyCreatedDBObject(gp, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
            Dim groupmade As Integer = makeGroup(gpid)
            If groupmade = 1 Then
                removeAllButLines(gpid)
            End If
        End Sub

        Private Sub removeAllButLines(ByVal groupId As ObjectId)
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim myGroup As Group = tm.GetObject(groupId, OpenMode.ForWrite, True)
                Dim idarray As ObjectId() = myGroup.GetAllEntityIds()
                Dim id As ObjectId
                For Each id In idarray
                    Dim thisObj As DBObject = tm.GetObject(id, OpenMode.ForWrite, True)
                    If Not TypeOf (thisObj) Is Autodesk.AutoCAD.DatabaseServices.Line Then
                        myGroup.Remove(id)
                        ed.WriteMessage(vbCrLf + "Removing " + thisObj.GetType().FullName + " from the group.")
                    End If
                Next
                myGroup.SetColorIndex(1)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
        End Sub

        Private Function makeGroup(ByVal groupId As ObjectId) As Integer
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Dim myGroup As Group = tm.GetObject(groupId, OpenMode.ForWrite, True)
            Try
                Dim res As PromptSelectionResult = ed.GetSelection()
                Dim SS As SelectionSet = res.Value
                Dim idarray() As ObjectId = SS.GetObjectIds()
                Dim id As ObjectId
                For Each id In idarray
                    Dim ent As Entity = tm.GetObject(id, OpenMode.ForRead, True)
                    myGroup.Append(id)
                    ed.WriteMessage(vbCrLf + "Adding " + ent.GetType().FullName + " to the group.")
                Next id
                ta.Commit()
            Catch
                ed.WriteMessage(vbCrLf + "No selections made.")
                Return -1
            Finally
                ta.Dispose()
            End Try
            Return 1
        End Function
    End Class
End Namespace
