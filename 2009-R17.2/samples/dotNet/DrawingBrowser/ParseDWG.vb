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

Imports System.Reflection
Imports System.Collections
Imports System.Drawing
Imports System.Windows.Forms

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices

Module ParseDWG

    Dim objArray As System.Collections.ArrayList = New System.Collections.ArrayList()

    Private Enum ImageIndex
        PropertyImage = 0
        DrawingImage
        OpenImage
        ClosedImage
        EnumImage
        ObjectImage
        MethodImage
        BlocksImage
        DimstylesImage
        LayersImage
        LayoutsImage
        LinetypesImage
        TextstylesImage
        XrefsImage
    End Enum

    Public Sub fillIcons(ByRef tree As TreeView)
        Dim helloModule As System.Reflection.Module = System.Reflection.Assembly.GetExecutingAssembly().GetModules()(0)
        Dim helloModulePath As String = helloModule.FullyQualifiedName

        Try
            helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
            helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
        Catch
            MsgBox("Error with Module Path")
            Exit Sub
        End Try

        Dim images As New ImageList()
        images.Images.Add(New Bitmap(helloModulePath + "\images\property.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\drawing.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\open.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\closed.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\enum.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\object.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\method.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\blocks.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\dimstyles.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\layers.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\layouts.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\linetypes.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\textstyles.bmp"))
        images.Images.Add(New Bitmap(helloModulePath + "\images\xrefs.bmp"))
        tree.ImageList = images
    End Sub

    Private Sub AssignIconFromName(ByRef node As TreeNode, ByVal name As String, ByVal defaultIndex As ImageIndex)
        If name = "BlockTableId" Then
            AssignIconFromIndex(node, ImageIndex.BlocksImage)
        ElseIf name = "LayerTableId" Then
            AssignIconFromIndex(node, ImageIndex.LayersImage)
        ElseIf name = "DimstylesTableId" Then
            AssignIconFromIndex(node, ImageIndex.DimstylesImage)
        ElseIf name = "LinetypesTableId" Then
            AssignIconFromIndex(node, ImageIndex.LinetypesImage)
        ElseIf name = "TextstylesTableId" Then
            AssignIconFromIndex(node, ImageIndex.TextstylesImage)
        ElseIf name = "XrefTableId" Then
            AssignIconFromIndex(node, ImageIndex.XrefsImage)
        ElseIf Right(name, 2) = "Id" Then
            AssignIconFromIndex(node, ImageIndex.ObjectImage)
        Else
            AssignIconFromIndex(node, defaultIndex)
        End If
    End Sub

    Private Sub AssignIconFromIndex(ByRef node As TreeNode, ByVal index As ImageIndex)
        node.ImageIndex = index
        node.SelectedImageIndex = index
    End Sub

    Sub ExtractObjectInfo(ByVal rootNode As System.Windows.Forms.TreeNode, ByVal obj As Object)
        Dim objPtr As Object
        Try
            'Is the object a top-level database?
            objPtr = CType(obj, Autodesk.AutoCAD.DatabaseServices.Database)
            AssignIconFromIndex(rootNode, ImageIndex.DrawingImage)
        Catch
            'Is it an objectId? If so, open it
            Dim idObj As Autodesk.AutoCAD.DatabaseServices.ObjectId = CType(obj, Autodesk.AutoCAD.DatabaseServices.ObjectId)
            objPtr = obj.Database.TransactionManager.GetObject(idObj, OpenMode.ForRead, False)
            AssignIconFromName(rootNode, rootNode.Text.Substring(0, rootNode.Text.IndexOf(" ")), ImageIndex.ObjectImage)
        End Try

        Try
            'Add the current object to a list, if it isn't already in it (and if it is, drop out to end the recursion)
            Dim wrapper As DisposableWrapper = CType(objPtr, DisposableWrapper)
            Dim iList As IList = objArray
            If iList.Contains(wrapper.UnmanagedObject) Then Exit Sub
            iList.Add(wrapper.UnmanagedObject)

            rootNode.Text += " (" + objPtr.GetType.ToString.Substring(objPtr.GetType.Namespace.ToString.Length + 1) + ")"

            'Get each of the API properties and methods, and get their information using reflection (adding the info to the tree)
            Dim methInfo As MethodInfo
            For Each methInfo In objPtr.GetType.GetMethods(BindingFlags.Instance Or BindingFlags.Public)
                Try
                    Dim prefix As String = Left(methInfo.Name, 4)
                    If prefix <> "get_" And prefix <> "set_" Then
                        Dim paramInfo As ParameterInfo
                        Dim paramString As String = ""
                        Dim bFirst As Boolean = True
                        For Each paramInfo In methInfo.GetParameters
                            If Not bFirst Then paramString += ", "
                            paramString += paramInfo.ParameterType.ToString.Substring(paramInfo.ParameterType.Namespace.ToString.Length + 1)
                            paramString += " " + paramInfo.Name
                            bFirst = False
                        Next
                        paramString = " (" + paramString + ")"
                        If methInfo.ReturnType.FullName <> "System.Void" Then
                            paramString += " returns "
                            paramString += methInfo.ReturnType.ToString.Substring(methInfo.ReturnType.Namespace.ToString.Length + 1)
                        End If
                        Dim node As TreeNode = rootNode.Nodes.Add(methInfo.Name + paramString)
                        AssignIconFromIndex(node, ImageIndex.MethodImage)
                    End If
                Catch
                End Try
            Next

            Dim propInfo As PropertyInfo
            For Each propInfo In objPtr.GetType.GetProperties(BindingFlags.Instance Or BindingFlags.Public)
                Try
                    Dim paramInfo() As ParameterInfo = propInfo.GetIndexParameters
                    If Not paramInfo Is Nothing And paramInfo.Length = 0 Then

                        Dim getter As MethodInfo = propInfo.GetGetMethod
                        Dim val As Object = getter.Invoke(objPtr, Nothing)
                        Dim node As TreeNode = rootNode.Nodes.Add(propInfo.Name + " = " + val.ToString + " (" + val.GetType.Name + ")")
                        AssignIconFromName(node, propInfo.Name, ImageIndex.PropertyImage)

                        If (TypeOf val Is ObjectId) Or (TypeOf val Is RXClass) Then
                            'Don't recurse objects referred to as "owners", as we will get to them in due course
                            If propInfo.Name = "OwnerId" Then
                                AssignIconFromIndex(node, ImageIndex.ObjectImage)
                            Else
                                ExtractObjectInfo(node, val)
                            End If
                        End If
                    End If
                Catch
                End Try
            Next
        Catch
        End Try
    End Sub

    Sub Cleanup()
        objArray.Clear()
    End Sub

End Module
