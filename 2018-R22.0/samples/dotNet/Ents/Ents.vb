' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.ApplicationServices
Imports DBTransMan = Autodesk.AutoCAD.DatabaseServices.TransactionManager

<assembly: Autodesk.AutoCAD.Runtime.ExtensionApplication(Nothing)>
<assembly: Autodesk.AutoCAD.Runtime.CommandClass(GetType(CreateEntities.MakeEntities))>

'This application implements a command called MKENTS. It will create a line and 
'a circle, append them to an object ID array, change the circle's color to red,
'and then make a group of the line and circle using "ASDK_TEST_GROUP" as the 
'group's name. The MKENTS command also creates a new layer named "ASDK_MYLAYER".
'
'To use Ents.dll:
'
'1. Start AutoCAD and open a new drawing.
'2. Type netload and select Ents.dll.
'3. Execute the MKENTS command.
'
'Autodesk references added to this project are the acdbmgd.dll and acmgd.dll .NET components,
'and the AutoCAD Type Library COM component.

Namespace CreateEntities

    Public Class MakeEntities
        <CommandMethod("MKENTS")> _
        Public Sub runit()
            Try
            	Call createNewLayer()
            	Dim coll As New ObjectIdCollection()

            	coll.Add(CreateCircle())
            	coll.Add(CreateLine())
            	Dim last As Integer
            	last = coll.Count
            	changeColor(coll.Item(last - 1), 1)
            	createGroup(coll, "ASDK_TEST_GROUP")
            Catch ex As System.Exception
                MsgBox(ex.Message)
            Finally
            End Try
        End Sub

        Public Sub createNewLayer()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim LT As LayerTable = tm.GetObject(db.LayerTableId, OpenMode.ForRead, False)
                If LT.Has("ASDK_MYLAYER") = False Then
                	Dim LTRec As New LayerTableRecord()
               		LTRec.Name = "ASDK_MYLAYER"
                    LT.UpgradeOpen()
                	LT.Add(LTRec)
                	tm.AddNewlyCreatedDBObject(LTRec, True)
					ta.Commit()
                End If
            Finally
                ta.Dispose()
            End Try
        End Sub

        Public Function CreateLine() As ObjectId
            Dim startpt As New Point3d(4.0, 2.0, 0.0)
            Dim endpt As New Point3d(10.0, 7.0, 0.0)
            Dim pLine As New Line(startpt, endpt)

            Dim lineid As ObjectId
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim bt As BlockTable = tm.GetObject(db.BlockTableId, OpenMode.ForRead, False)
                Dim btr As BlockTableRecord = tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False)
                lineid = btr.AppendEntity(pLine)
                tm.AddNewlyCreatedDBObject(pLine, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
            Return lineid
        End Function

        Public Function CreateCircle() As ObjectId
            Dim center As New Point3d(9.0, 3.0, 0.0)
            Dim normal As New Vector3d(0.0, 0.0, 1.0)
            Dim pcirc As New Circle(center, normal, 2.0)
            Dim Circid As ObjectId

            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction
            Try
                Dim bt As BlockTable = tm.GetObject(db.BlockTableId, OpenMode.ForRead, False)
                Dim btr As BlockTableRecord = tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False)
                Circid = btr.AppendEntity(pcirc)
                tm.AddNewlyCreatedDBObject(pcirc, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
            Return Circid
        End Function

        Private Sub changeColor(ByVal entId As ObjectId, ByVal newColor As Long)
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim ent As Entity = tm.GetObject(entId, OpenMode.ForWrite, True)
                ent.ColorIndex = newColor
                ta.Commit()
            Catch
                Console.WriteLine("Error in setting the color for the entity")
            Finally
                ta.Dispose()
            End Try
        End Sub

        Private Sub createGroup(ByVal objIds As ObjectIdCollection, ByVal pGroupName As System.String)
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim gp As New Group(pGroupName, True)
                Dim dict As DBDictionary = tm.GetObject(db.GroupDictionaryId, OpenMode.ForWrite, True)
                dict.SetAt("ASDK_NEWNAME", gp)
                Dim thisId As ObjectId
                For Each thisId In objIds
                    gp.Append(thisId)
                Next
                tm.AddNewlyCreatedDBObject(gp, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
        End Sub
    End Class

End Namespace
