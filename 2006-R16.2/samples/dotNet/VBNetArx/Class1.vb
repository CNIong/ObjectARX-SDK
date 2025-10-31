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
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.ApplicationServices
Imports System.Reflection
Imports System.IO
Imports System.Collections
Imports System.Runtime.InteropServices
Imports Autodesk.AutoCAD.Interop
Imports System.Diagnostics
Imports Autodesk.AutoCAD.PlottingServices
Imports DBTransMan = Autodesk.AutoCAD.DatabaseServices.TransactionManager

'to test:
'1. use the NETLOAD command to load mgdarx.dll
'2. issue one of the supported commands (XREC, HYPER, COMINTEROP)
Namespace MgdArx
    _

    Public Class MyCommands

        'this method will be automatically hooked into the AutoCAD command interpreter
        'type "cominterop" on the command line after loading this application with
        'the NETLOAD command 
        <CommandMethod("COMINTEROP", CommandFlags.Session)> _
        Public Shared Sub ComInteropCommand()
            'use AcadApplication property to the to the COM object model
            Dim acadApp As AcadApplication = CType(Application.AcadApplication, AcadApplication)
            'use the COM object model to iterate through the docs
            Dim acadDoc As AcadDocument
            For Each acadDoc In acadApp.Documents
                'use the static FromAcadDocument method to convert a COM
                'document to a mnaged document
                Dim doc As Document = Document.FromAcadDocument(acadDoc)

                ' lock the document...note:  disposal of the lock (below) unlocks the document!
                Dim docLock As DocumentLock = doc.LockDocument()

                Try
                    'use ObjectId to convert between COM wrappers for database
                    'objects and their managed wrappers.
                    Dim id As New ObjectId(acadDoc.ActiveLayer.ObjectID)
                    Dim trans As Transaction = doc.Database.TransactionManager.StartTransaction()
                    Try
                        Dim ltr As LayerTableRecord = trans.GetObject(id, OpenMode.ForWrite)
                        ltr.Description = "Changed by the cominterop command"
                        trans.Commit()
                    Finally
                        trans.Dispose()
                    End Try
                Finally
                    docLock.Dispose() ' unlock the document
                End Try
            Next acadDoc
        End Sub 'ComInteropCommand

        'this method will be automatically hooked into the AutoCAD command interpreter
        <CommandMethod("HYPER")> _
        Public Shared Sub HyperCommand()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try
                'create a line
                Dim line As New Line(New Point3d(0, 0, 0), New Point3d(1, 1, 0))
                Dim bt As BlockTable = CType(tm.GetObject(db.BlockTableId, OpenMode.ForRead, False), BlockTable)
                Dim btr As BlockTableRecord = CType(tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False), BlockTableRecord)
                'add it to the model space block table record
                btr.AppendEntity(line)
                'make sure that the transaction knows about this new object
                tm.AddNewlyCreatedDBObject(line, True)
                'add some hyperlinks 
                Dim hyper As New HyperLink()
                hyper.Name = "www.autodesk.com"
                line.Hyperlinks.Add(hyper)
                If line.Hyperlinks.Contains(hyper) Then
                    hyper.Name = "www.gotdotnet.com"
                End If
                line.Hyperlinks.Add(hyper)
                Dim i As Integer
                For i = 0 To line.Hyperlinks.Count - 1
                    Debug.WriteLine(line.Hyperlinks(i).ToString())
                Next i 'commit transaction
                myT.Commit()
            Finally
                myT.Dispose()
            End Try
        End Sub 'HyperCommand

        <CommandMethod("XRECORD")> _
        Public Shared Sub XRecCommand()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor = _
                Application.DocumentManager.MdiActiveDocument.Editor
            'start a transaction
            Dim myT As Transaction = tm.StartTransaction()
            Try
                Dim rec As New Xrecord()
                rec.Data = New ResultBuffer( _
                        New TypedValue(CInt(DxfCode.Text), "This is a test"), _
                        New TypedValue(CInt(DxfCode.Int8), 0), _
                        New TypedValue(CInt(DxfCode.Int16), 1), _
                        New TypedValue(CInt(DxfCode.Int32), 2), _
                        New TypedValue(CInt(DxfCode.HardPointerId), db.BlockTableId), _
                        New TypedValue(CInt(DxfCode.BinaryChunk), New Byte() {0, 1, 2, 3, 4}), _
                        New TypedValue(CInt(DxfCode.ArbitraryHandle), db.BlockTableId.Handle), _
                        New TypedValue(CInt(DxfCode.UcsOrg), New Point3d(0, 0, 0)))

                Dim dict As DBDictionary = CType(myT.GetObject(db.NamedObjectsDictionaryId, OpenMode.ForWrite, False), DBDictionary)
                dict.SetAt("test", rec)
                tm.AddNewlyCreatedDBObject(rec, True)
                'list the entries we just added
                ed.WriteMessage("Xrecord items:" + ControlChars.Lf)
                Dim rb As TypedValue
                For Each rb In rec.Data
                    ed.WriteMessage(String.Format("TypeCode={0}, Value={1}" + ControlChars.Lf, rb.TypeCode, rb.Value))
                Next rb
                'add some xdata on the xrecord (silly but this is just a test)
                'first have to register an app
                Dim tbl As RegAppTable = CType(myT.GetObject(db.RegAppTableId, OpenMode.ForWrite, False), RegAppTable)
                Dim app As New RegAppTableRecord()
                app.Name = "MyApp"
                tbl.Add(app)
                tm.AddNewlyCreatedDBObject(app, True)

                rec.XData = New ResultBuffer(New TypedValue(CInt(DxfCode.ExtendedDataRegAppName), "MyApp"), New TypedValue(CInt(DxfCode.ExtendedDataAsciiString), "This is some xdata string"))
                'list them
                ed.WriteMessage("Xdata items:" + ControlChars.Lf)
                For Each rb In rec.XData
                    ed.WriteMessage(String.Format("TypeCode={0}, Value={1}" + ControlChars.Lf, rb.TypeCode, rb.Value))
                Next rb
                'commit transaction
                myT.Commit()
            Finally
                myT.Dispose()
            End Try
        End Sub 'XRecCommand
    End Class 'MyCommands
End Namespace 'MgdArx
