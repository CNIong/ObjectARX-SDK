' Copyright 2004-2007 by Autodesk, Inc.

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
Imports System.Reflection
Imports Autodesk.AutoCAD
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.EditorInput
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.GraphicsInterface

<Assembly: ExtensionApplication(GetType(GiMeta.GiMetaApp))> 
<Assembly: CommandClass(GetType(GiMeta.GiMetaCommand))> 


Namespace GiMeta

    Public Class MyUtil
        Shared Sub displayMsg(ByVal msg As String)
            Dim ed As Autodesk.AutoCAD.EditorInput.Editor = Application.DocumentManager.MdiActiveDocument.Editor

            ed.WriteMessage(Chr(10) + msg)
        End Sub
    End Class

    Public Class GiMetaApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub
    End Class

    Public Class GiMetaCommand

        <Autodesk.AutoCAD.Runtime.CommandMethod("myGiMeta")> _
        Public Sub test()
            Dim ed As Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

            Dim opt As New PromptEntityOptions("Please select an entity")
            Dim entRes As PromptEntityResult
            Dim mySelectedEntity As Entity

            Do
                entRes = ed.GetEntity(opt)
                opt.Message = Chr(10) & "An Entity please"
            Loop Until ((entRes.Status = PromptStatus.Error) Or _
                       (entRes.Status = PromptStatus.None) Or _
                       (entRes.Status = PromptStatus.OK))

            If (entRes.Status = PromptStatus.None Or entRes.Status = PromptStatus.Error) Then
                Exit Sub
            End If

            Dim myDB As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim myTrans As Transaction = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction()

            mySelectedEntity = CType(myTrans.GetObject(entRes.ObjectId, OpenMode.ForRead), Entity)

            Try
                Dim gimeta As MyWorldDraw = New MyWorldDraw()
                mySelectedEntity.WorldDraw(gimeta)
                myTrans.Commit()
            Finally
                myTrans.Dispose()
            End Try
        End Sub

        Public Sub New()

        End Sub
    End Class

    Public Class MyWorldGeometry
        Inherits WorldGeometry

        Public Sub New()
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

        Public Overrides Sub SetExtents(ByVal extents As Autodesk.AutoCAD.DatabaseServices.Extents3d)
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

        Public Overrides Sub StartAttributesSegment()
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

#Region "Properties"
        Public Overrides ReadOnly Property WorldToModelTransform() As Autodesk.AutoCAD.Geometry.Matrix3d
            Get
                MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
                Return New Autodesk.AutoCAD.Geometry.Matrix3d()
            End Get
        End Property

        Public Overrides ReadOnly Property ModelToWorldTransform() As Autodesk.AutoCAD.Geometry.Matrix3d
            Get
                MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
                Return New Autodesk.AutoCAD.Geometry.Matrix3d()
            End Get
        End Property
#End Region

#Region "Circle"
        Public Overloads Overrides Function Circle(ByVal firstPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal secondPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal thirdPoint As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overloads Overrides Function Circle(ByVal center As Autodesk.AutoCAD.Geometry.Point3d, ByVal radius As Double, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d) As Boolean
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

#End Region
#Region "CircularArc"
        Public Overloads Overrides Function CircularArc(ByVal start As Autodesk.AutoCAD.Geometry.Point3d, ByVal point As Autodesk.AutoCAD.Geometry.Point3d, ByVal endingPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal arcType As Autodesk.AutoCAD.GraphicsInterface.ArcType) As Boolean
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overloads Overrides Function CircularArc(ByVal center As Autodesk.AutoCAD.Geometry.Point3d, ByVal radius As Double, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal startVector As Autodesk.AutoCAD.Geometry.Vector3d, ByVal sweepAngle As Double, ByVal arcType As Autodesk.AutoCAD.GraphicsInterface.ArcType) As Boolean
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
#End Region

#Region "Polyline"
        Public Overloads Overrides Function Polyline( _
                        ByVal value As Autodesk.AutoCAD.DatabaseServices.Polyline, _
                        ByVal fromIndex As Integer, _
                        ByVal segments As Integer) As Boolean
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overloads Overrides Function Polyline( _
                        ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, _
                        ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, _
                        ByVal subEntityMarker As IntPtr) As Boolean 'Fix 1
            MyUtil.displayMsg("Selected Entity Name = " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
#End Region

#Region "PushModelTranform"
        Public Overloads Overrides Function PushModelTransform(ByVal matrix As Autodesk.AutoCAD.Geometry.Matrix3d) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overloads Overrides Function PushModelTransform(ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
#End Region

#Region "Text"
        Public Overloads Overrides Function Text(ByVal position As Autodesk.AutoCAD.Geometry.Point3d, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal direction As Autodesk.AutoCAD.Geometry.Vector3d, ByVal height As Double, ByVal width As Double, ByVal oblique As Double, ByVal message As String) As Boolean
            MyUtil.displayMsg("Text function 1 called")
            Return True
        End Function

        Public Overloads Overrides Function Text(ByVal position As Autodesk.AutoCAD.Geometry.Point3d, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal direction As Autodesk.AutoCAD.Geometry.Vector3d, ByVal message As String, ByVal raw As Boolean, ByVal textStyle As Autodesk.AutoCAD.GraphicsInterface.TextStyle) As Boolean
            MyUtil.displayMsg("Text function 2 called")
            Return True
        End Function
#End Region

#Region "Misc"
        Protected Sub New(ByVal unmanagedPointer As IntPtr, ByVal autoDelete As Boolean)
            MyBase.New(unmanagedPointer, autoDelete)
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

        Public Overrides Function Ray(ByVal point1 As Autodesk.AutoCAD.Geometry.Point3d, ByVal point2 As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Shell(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal faces As Autodesk.AutoCAD.Geometry.IntegerCollection, ByVal edgeData As Autodesk.AutoCAD.GraphicsInterface.EdgeData, ByVal faceData As Autodesk.AutoCAD.GraphicsInterface.FaceData, ByVal vertexData As Autodesk.AutoCAD.GraphicsInterface.VertexData, ByVal bAutoGenerateNormal As Boolean) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Draw(ByVal value As Autodesk.AutoCAD.GraphicsInterface.Drawable) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Mesh(ByVal rows As Integer, ByVal columns As Integer, ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal edgeData As Autodesk.AutoCAD.GraphicsInterface.EdgeData, ByVal faceData As Autodesk.AutoCAD.GraphicsInterface.FaceData, ByVal vertexData As Autodesk.AutoCAD.GraphicsInterface.VertexData,ByVal bAutoGenerateNormal As Boolean) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Polygon(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Sub PopClipBoundary()
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

        Public Overrides Function PopModelTransform() As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Function

        Public Overrides Function PushClipBoundary(ByVal boundary As Autodesk.AutoCAD.GraphicsInterface.ClipBoundary) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function WorldLine(ByVal startPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal endPoint As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Xline(ByVal point1 As Autodesk.AutoCAD.Geometry.Point3d, ByVal point2 As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Polypoint(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal normals As Autodesk.AutoCAD.Geometry.Vector3dCollection, ByVal subentityMarkers As Autodesk.AutoCAD.Geometry.IntPtrCollection) As Boolean 'Fix 2
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
#End Region

    End Class

#Region "MyContext"
    Public Class MyContext
        Inherits Context
        Public Overrides ReadOnly Property Database() As Autodesk.AutoCAD.DatabaseServices.Database
            Get
                MyUtil.displayMsg("Get Method for Database is called")
                Return New Autodesk.AutoCAD.DatabaseServices.Database()
            End Get
        End Property
        Public Overrides ReadOnly Property IsPostScriptOut() As Boolean
            Get
                MyUtil.displayMsg("Get Method for IsPostScriptOut is called")
                Return True
            End Get
        End Property
        Public Overrides ReadOnly Property IsPlotGeneration() As Boolean
            Get
                MyUtil.displayMsg("Get Method for IsPlotGeneration is called")
                Return True
            End Get
        End Property
        Public Overrides ReadOnly Property IsBoundaryClipping() As Boolean
            Get
                MyUtil.displayMsg("Get Method for IsBoundaryClipping is called")
                Return True
            End Get
        End Property
    End Class
#End Region

#Region "MySubEntityTraits"
    Public Class MySubEntityTraits
        Inherits SubEntityTraits

        Private entityColor As Autodesk.AutoCAD.Colors.EntityColor
        Private myFillType As Autodesk.AutoCAD.GraphicsInterface.FillType = FillType.FillAlways
        Private myLineWeight As Autodesk.AutoCAD.DatabaseServices.LineWeight = LineWeight.ByLayer
        Private myObjectId As Autodesk.AutoCAD.DatabaseServices.ObjectId
        Private myLineType As Autodesk.AutoCAD.DatabaseServices.ObjectId
        Private myLineTypeScale As Double
        Private myThickness As Double

        Public Overrides Property Layer() As Autodesk.AutoCAD.DatabaseServices.ObjectId
            Get
                MyUtil.displayMsg("Custom WorldDraw Get Layer called")
                Return myObjectId
            End Get
            Set(ByVal Value As Autodesk.AutoCAD.DatabaseServices.ObjectId)
                MyUtil.displayMsg("Custom WorldDraw Set Layer called")
                myObjectId = Value
            End Set
        End Property
        Public Overrides Property LineWeight() As Autodesk.AutoCAD.DatabaseServices.LineWeight
            Get
                MyUtil.displayMsg("Custom WorldDraw Get LineWeight called")
                Return myLineWeight
            End Get
            Set(ByVal Value As Autodesk.AutoCAD.DatabaseServices.LineWeight)
                MyUtil.displayMsg("Custom WorldDraw Set LineWeight called")
                myLineWeight = Value
            End Set
        End Property
        Public Overrides Property TrueColor() As Autodesk.AutoCAD.Colors.EntityColor
            Get
                MyUtil.displayMsg("Custom WorldDraw GetTrueColor called")
                Return entityColor
            End Get
            Set(ByVal Value As Autodesk.AutoCAD.Colors.EntityColor)
                MyUtil.displayMsg("Custom WorldDraw SetTrueColor called")
                entityColor = Value
            End Set
        End Property
        Public Overrides Property LineType() As Autodesk.AutoCAD.DatabaseServices.ObjectId
            Get
                MyUtil.displayMsg("Custom WorldDraw GetLineType called")
                Return New Autodesk.AutoCAD.DatabaseServices.ObjectId()
            End Get
            Set(ByVal Value As Autodesk.AutoCAD.DatabaseServices.ObjectId)
                MyUtil.displayMsg("Custom WorldDraw SetLineType called")
                myLineType = Value
            End Set
        End Property
        Public Overrides Property Color() As Short
            Get
                MyUtil.displayMsg("Custom WorldDraw GetColor called")
                Return entityColor.ColorIndex
            End Get
            Set(ByVal Value As Short)
                MyUtil.displayMsg("Custom WorldDraw SetColor called")
            End Set
        End Property
        Public Overrides Property LineTypeScale() As Double
            Get
                MyUtil.displayMsg("Custom WorldDraw Get LineTypeScale called ")
                Return myLineTypeScale
            End Get
            Set(ByVal Value As Double)
                Value = myLineTypeScale
                MyUtil.displayMsg("Custom WorldDraw Set LineTypeScale called ")
            End Set
        End Property
        Public Overrides Property FillType() As Autodesk.AutoCAD.GraphicsInterface.FillType
            Get
                MyUtil.displayMsg("Custom WorldDraw Get FillType called ")
                Return myFillType
            End Get
            Set(ByVal Value As Autodesk.AutoCAD.GraphicsInterface.FillType)
                myFillType = Value
                MyUtil.displayMsg("Custom WorldDraw Set FillType called ")
            End Set
        End Property

        Public Overrides Property Thickness() As Double
            Get
                MyUtil.displayMsg("Custom WorldDraw Get Thickness called ")
                Return myThickness
            End Get
            Set(ByVal Value As Double)
                myThickness = Value
                MyUtil.displayMsg("Custom WorldDraw Set Thickness called ")
            End Set
        End Property

        Public Sub New()
            MyBase.New()
        End Sub

        Public Overrides Sub SetSelectionMarker(ByVal markerId As IntPtr) 'Fix 3
            MyUtil.displayMsg("Custom WorldDraw SetSelectionMarker")
        End Sub

        Public Overrides Property Sectionable() As Boolean
            Get

            End Get
            Set(ByVal Value As Boolean)

            End Set
        End Property

        Public Overrides Property VisualStyle() As ObjectId
            Get

            End Get
            Set(ByVal Value As ObjectId)

            End Set
        End Property

        Public Overrides Property Material() As ObjectId
            Get

            End Get
            Set(ByVal Value As ObjectId)

            End Set
        End Property

        Public Overrides Property Mapper() As Autodesk.AutoCAD.GraphicsInterface.Mapper
            Get
                Return New Mapper()
            End Get
            Set(ByVal Value As Mapper)

            End Set
        End Property

        Public Overrides Property PlotStyleDescriptor() As Autodesk.AutoCAD.DatabaseServices.PlotStyleDescriptor
            Get

            End Get
            Set(ByVal Value As PlotStyleDescriptor)

            End Set
        End Property

        Public Overrides Property DrawFlags() As Integer
            Get

            End Get
            Set(ByVal Value As Integer)

            End Set
        End Property

        Public Overrides Property EdgeStyleOverride() As Autodesk.AutoCAD.GraphicsInterface.EdgeStyleOverride
            Get
                Return New EdgeStyleOverride()
            End Get
            Set(ByVal Value As EdgeStyleOverride)

            End Set
        End Property

        Public Overrides Property ShadowFlags() As Autodesk.AutoCAD.GraphicsInterface.ShadowFlags
            Get

            End Get
            Set(ByVal Value As ShadowFlags)

            End Set
        End Property

        Public Overrides Property SelectionOnlyGeometry() As Boolean
            Get

            End Get
            Set(ByVal value As Boolean)

            End Set
        End Property
    End Class

#End Region

#Region "MyGeometry"
    Public Class MyGeometry
        Inherits Autodesk.AutoCAD.GraphicsInterface.Geometry
        Public Sub New()
            MyBase.New(Nothing, True)
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
        End Sub

        Public Overrides ReadOnly Property WorldToModelTransform() As Autodesk.AutoCAD.Geometry.Matrix3d
            Get
                Return New Autodesk.AutoCAD.Geometry.Matrix3d()
            End Get
        End Property

        Public Overrides Function Draw(ByVal value As Autodesk.AutoCAD.GraphicsInterface.Drawable) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name + " called.")
            Return True
        End Function
        Public Overrides Function Polygon(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overrides Function Shell(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal faces As Autodesk.AutoCAD.Geometry.IntegerCollection, ByVal edgeData As Autodesk.AutoCAD.GraphicsInterface.EdgeData, ByVal faceData As Autodesk.AutoCAD.GraphicsInterface.FaceData, ByVal vertexData As Autodesk.AutoCAD.GraphicsInterface.VertexData, ByVal bAutoGenerateNormal As Boolean) As Boolean
            MyUtil.displayMsg(MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overloads Overrides Function Polyline( _
                          ByVal value As Autodesk.AutoCAD.DatabaseServices.Polyline, _
                          ByVal fromIndex As Integer, _
                          ByVal segments As Integer) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + " [1]")
            Return True
        End Function

        Public Overloads Overrides Function Polyline( _
                        ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, _
                        ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, _
                        ByVal subEntityMarker As IntPtr) As Boolean 'Fix 4
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + " [2]")
            Return True
        End Function

        Public Overloads Overrides Function CircularArc(ByVal start As Autodesk.AutoCAD.Geometry.Point3d, ByVal point As Autodesk.AutoCAD.Geometry.Point3d, ByVal endingPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal arcType As Autodesk.AutoCAD.GraphicsInterface.ArcType) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + " [1]")
            Return True
        End Function

        Public Overloads Overrides Function CircularArc(ByVal center As Autodesk.AutoCAD.Geometry.Point3d, ByVal radius As Double, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal startVector As Autodesk.AutoCAD.Geometry.Vector3d, ByVal sweepAngle As Double, ByVal arcType As Autodesk.AutoCAD.GraphicsInterface.ArcType) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + " [2]")
            Return True
        End Function

        Public Overrides Function Xline(ByVal point1 As Autodesk.AutoCAD.Geometry.Point3d, ByVal point2 As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overloads Overrides Function Text(ByVal position As Autodesk.AutoCAD.Geometry.Point3d, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal direction As Autodesk.AutoCAD.Geometry.Vector3d, ByVal height As Double, ByVal width As Double, ByVal oblique As Double, ByVal message As String) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + "[1]")
            Return True
        End Function

        Public Overloads Overrides Function Text(ByVal position As Autodesk.AutoCAD.Geometry.Point3d, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d, ByVal direction As Autodesk.AutoCAD.Geometry.Vector3d, ByVal message As String, ByVal raw As Boolean, ByVal textStyle As Autodesk.AutoCAD.GraphicsInterface.TextStyle) As Boolean
            MyUtil.displayMsg("Entity is a " + MethodInfo.GetCurrentMethod().Name + "[2]")
            Return True
        End Function
        Public Overrides ReadOnly Property ModelToWorldTransform() As Autodesk.AutoCAD.Geometry.Matrix3d
            Get
                MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
                Return New Autodesk.AutoCAD.Geometry.Matrix3d()
            End Get
        End Property
        Public Overrides Function Ray(ByVal point1 As Autodesk.AutoCAD.Geometry.Point3d, ByVal point2 As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overloads Overrides Function Circle(ByVal firstPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal secondPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal thirdPoint As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name + "[1]")
            Return True
        End Function

        Public Overloads Overrides Function Circle(ByVal center As Autodesk.AutoCAD.Geometry.Point3d, ByVal radius As Double, ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name + "[2]")
            Return True
        End Function

        Public Overrides Function WorldLine(ByVal startPoint As Autodesk.AutoCAD.Geometry.Point3d, ByVal endPoint As Autodesk.AutoCAD.Geometry.Point3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overrides Sub PopClipBoundary()
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
        End Sub
        Public Overrides Function PopModelTransform() As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function

        Public Overrides Function Mesh(ByVal rows As Integer, ByVal columns As Integer, ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal edgeData As Autodesk.AutoCAD.GraphicsInterface.EdgeData, ByVal faceData As Autodesk.AutoCAD.GraphicsInterface.FaceData, ByVal vertexData As Autodesk.AutoCAD.GraphicsInterface.VertexData, ByVal bAutoGenerateNormal As Boolean) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overrides Function PushClipBoundary(ByVal boundary As Autodesk.AutoCAD.GraphicsInterface.ClipBoundary) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
        Public Overloads Overrides Function PushModelTransform(ByVal matrix As Autodesk.AutoCAD.Geometry.Matrix3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name + "[1]")
            Return True
        End Function
        Public Overloads Overrides Function PushModelTransform(ByVal normal As Autodesk.AutoCAD.Geometry.Vector3d) As Boolean
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name + "[2]")
            Return True
        End Function
        Public Overrides Function Polypoint(ByVal points As Autodesk.AutoCAD.Geometry.Point3dCollection, ByVal normals As Autodesk.AutoCAD.Geometry.Vector3dCollection, ByVal subentityMarkers As Autodesk.AutoCAD.Geometry.IntPtrCollection) As Boolean 'Fix 5
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return True
        End Function
    End Class
#End Region

#Region "MyWorldDraw"
    Public Class MyWorldDraw
        Inherits WorldDraw

        Public Overrides ReadOnly Property Geometry() As Autodesk.AutoCAD.GraphicsInterface.WorldGeometry
            Get
                MyUtil.displayMsg("Custom WorldDraw called Get Geometry")
                Return New MyWorldGeometry()
            End Get
        End Property

        Public Overrides ReadOnly Property Context() As Autodesk.AutoCAD.GraphicsInterface.Context
            Get
                MyUtil.displayMsg("Custom WorldDraw called Get Context")
                Return New MyContext()
            End Get
        End Property

        Sub New()
            MyBase.New()
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name + "[2]")
        End Sub

        Public Overrides Function Deviation(ByVal deviationType As Autodesk.AutoCAD.GraphicsInterface.DeviationType, ByVal pointOnCurve As Autodesk.AutoCAD.Geometry.Point3d) As Double
            MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
            Return New Double()
        End Function

        Public Overrides ReadOnly Property SubEntityTraits() As Autodesk.AutoCAD.GraphicsInterface.SubEntityTraits
            Get
                MyUtil.displayMsg("Custom WorldDraw SubEntityTraits called")
                Return New MySubEntityTraits()
            End Get
        End Property

        Public Overrides ReadOnly Property RawGeometry() As Autodesk.AutoCAD.GraphicsInterface.Geometry
            Get
                MyUtil.displayMsg("Get RawGeometry called")
                Return New MyGeometry()
            End Get
        End Property

        Public Overrides ReadOnly Property RegenType() As Autodesk.AutoCAD.GraphicsInterface.RegenType
            Get
                MyUtil.displayMsg("Get RegenType called")
                Return RegenType.HideOrShadeCommand
            End Get
        End Property

        Public Overrides ReadOnly Property RegenAbort() As Boolean
            Get
                MyUtil.displayMsg("Custom WorldDraw called " + MethodInfo.GetCurrentMethod().Name)
                Return True
            End Get
        End Property
        Public Overrides ReadOnly Property NumberOfIsolines() As Integer
            Get
                MyUtil.displayMsg("Get RawGeometry called")
                Return 5
            End Get
        End Property
        Public Overrides ReadOnly Property IsDragging() As Boolean
            Get
                MyUtil.displayMsg("Custom WorldDraw ReadOnly Property called = ")
                Return True

            End Get
        End Property

    End Class
#End Region

End Namespace
