' Copyright 2023 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

' Import namespace names from referenced projects and assemblies
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Geometry

' import the custom entity wrapper
Imports Autodesk.ObjectDbxSample.Poly

Imports DBTransMan = Autodesk.AutoCAD.DatabaseServices.TransactionManager

Public Class mgPolyTestApp

  ' declare the commandmethod attribute 
    <Autodesk.AutoCAD.Runtime.CommandMethod("TestCreate")> _
    Public Sub TestFunction()

        ' get the working databasre
        Dim db As Database = HostApplicationServices.WorkingDatabase
        ' get the transaction manager for the working database
        Dim tm As DBTransMan = db.TransactionManager
        ' create a new transaction
        Dim myT As Transaction = tm.StartTransaction()
        ' start our try/catch block
        Try
            ' create a poly samp object via the .net wrapper
            Dim poly As New Autodesk.ObjectDbxSample.Poly()
            ' set the properties for the poly
            poly.Center = New Point2d(100, 100)
            poly.StartPoint2d = New Point2d(300, 100)
            poly.NumberOfSides = 5
            poly.Name = "Managed Poly"

            ' get the blocktable as before, but lets open it for read within the transaction manager
            Dim bt As BlockTable = CType(tm.GetObject(db.BlockTableId, OpenMode.ForRead, False), BlockTable)
            ' do the same again but for the model space itself, we will need to open model space for write as
            ' we will be adding to it
            Dim btr As BlockTableRecord = CType(tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False), BlockTableRecord)
            ' add the new line to the model space as before
            btr.AppendEntity(poly)
            ' and then make sure that the transaction knows about this new object
            tm.AddNewlyCreatedDBObject(poly, True)
            ' finally commit the changes
            myT.Commit()

        Catch

            ' an error occurred
            ' ...


        Finally

            ' for the transactions we need to call the dispose to finish off
            myT.Dispose()

        End Try
    End Sub

End Class
