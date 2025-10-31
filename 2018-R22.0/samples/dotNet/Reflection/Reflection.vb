' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

Option Explicit On 

Imports System
Imports System.Type
Imports System.CLSCompliantAttribute
Imports System.Reflection
Imports System.Runtime.InteropServices
Imports System.Xml

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.EditorInput


<Assembly: ExtensionApplication(GetType(Reflection.ReflectionApp))> 
<Assembly: CommandClass(GetType(Reflection.ReflectionCommand))> 
'<Assembly: AssemblyKeyFile("..\..\mykey.snk")> 

Namespace Reflection
    '<summary>
    'Summary description for "Reflection" sample.
    'To run this sample project create the references to acdbmgd, acmgd, System, System.Data, System.Drawing and System.XML
    'The steps to run this application :
    '1. Draw an entity (circle, ploygon etc.) 
    '2. Call "NetLoad" from the command prompt
    '3. Load Filer "Reflection.dll"
    '4. Call "reflection" from the command prompt
    '5. Select the entity
    '6. Enter a filename
    'Result : the application will dump the information at the filename entered in .XML.
    ' The .XML will be save under /bin folder
    '</summary>
    Public Class ReflectionApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub
    End Class

    Public Class ReflectionCommand
        Dim ed As Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

        <Autodesk.AutoCAD.Runtime.CommandMethod("Reflection")> _
        Public Sub exportObjectInfo()

            Dim objID As ObjectId = SelectMyEntity()
            Dim exportFilename As String

            If (objID.IsNull) Then
                ed.WriteMessage("*cancelled*" + Chr(10))
                Exit Sub
            End If

            exportFilename = SelectMyExportFilename()
            If exportFilename = Nothing Then
                ed.WriteMessage("*cancelled*" + Chr(10))
                Exit Sub
            End If

            Dim myTrans As Transaction = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction()
            'Dim ent As Entity = CType(myTrans.GetObject(entRes.ObjectId, OpenMode.ForRead), Entity)
            Dim obj As Object = CType(myTrans.GetObject(objID, OpenMode.ForRead), Object)

            Dim outXml As AcReflection = New AcReflection(exportFilename)
            outXml.ProcessEntity(obj)
            myTrans.Commit()
        End Sub

        Function SelectMyEntity() As ObjectId
            Dim opt As New PromptEntityOptions("Please select an Entity to export")
            Dim entRes As PromptEntityResult

            Do
                entRes = ed.GetEntity(opt)
                opt.Message = Chr(10) & "an Entity please"
            Loop Until ((entRes.Status = PromptStatus.Error) Or _
                        (entRes.Status = PromptStatus.None) Or _
                        (entRes.Status = PromptStatus.Cancel) Or _
                         (entRes.Status = PromptStatus.OK))
            If (entRes.Status <> PromptStatus.OK) Then
                ' Cancelled
                Return Nothing
            End If
            Return entRes.ObjectId
        End Function

        Function SelectMyExportFilename() As String
            Dim filename As String
            Dim stringOpt As New PromptStringOptions(Chr(10) + "Please specify the filename you wish to export to")
            Dim promptRes As PromptResult
            Do
                promptRes = ed.GetString(stringOpt)
                stringOpt.Message = Chr(10) + "filename please"
            Loop Until ((promptRes.Status = PromptStatus.Error) Or _
                        (promptRes.Status = PromptStatus.None) Or _
                        (promptRes.Status = PromptStatus.Cancel) Or _
                         (promptRes.Status = PromptStatus.OK))


            If (promptRes.Status <> PromptStatus.OK) Or (promptRes.StringResult.Length() = 0) Then
                ' Cancelled
                Return Nothing
            End If

            filename = promptRes.StringResult.Trim()
            If Right(filename, 4).ToUpper() <> ".XML" Then
                filename = filename + ".xml"
            End If
            Return filename

        End Function
    End Class

End Namespace
