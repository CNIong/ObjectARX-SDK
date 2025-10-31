' Copyright (C) 2004 by Autodesk, Inc.

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
