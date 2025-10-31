// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "acad1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace properties

/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace operations

CString IAcadModelSpace::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadModelSpace::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadModelSpace::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadModelSpace::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadModelSpace::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadModelSpace::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadModelSpace::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadModelSpace::GetCount()
{
	long result;
	InvokeHelper(0x600, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadModelSpace::GetName()
{
	CString result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadModelSpace::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadModelSpace::AddCustomObject(LPCTSTR ClassName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x603, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ClassName);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x604, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DMesh(long M, long N, const VARIANT& PointsMatrix)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x605, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		M, N, &PointsMatrix);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DPoly(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x606, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadModelSpace::AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x607, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, StartAngle, EndAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x608, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Height, Mode, Prompt, &InsertionPoint, Tag, Value);
	return result;
}

LPDISPATCH IAcadModelSpace::AddBox(const VARIANT& Origin, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x609, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Origin, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCircle(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x60a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCone(const VARIANT& Center, double BaseRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, BaseRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCylinder(const VARIANT& Center, double Radius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &TextPosition);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x60f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ChordPoint, &FarChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x610, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &DimLineLocation, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x611, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&DefinitionPoint, &LeaderEndPoint, UseXAxis);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &ChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x613, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &MajorAxis, RadiusRatio);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x614, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x615, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_R8;
	InvokeHelper(0x616, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Height, TaperAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x617, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Path);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_DISPATCH VTS_I4;
	InvokeHelper(0x618, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, Annotation, Type);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_BSTR;
	InvokeHelper(0x619, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Width, Text);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPoint(const VARIANT& Point)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLightWeightPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRay(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x61d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

VARIANT IAcadModelSpace::AddRegion(const VARIANT& ObjectList)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ObjectList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x61f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, &AxisPoint, &AxisDir, Angle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSphere(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x622, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x623, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, &StartTangent, &EndTangent);
	return result;
}

LPDISPATCH IAcadModelSpace::AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x624, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TextString, &InsertionPoint, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x625, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Text, &InsertionPoint, &Direction);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x626, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, TorusRadius, TubeRadius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTrace(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x627, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadModelSpace::AddWedge(const VARIANT& Center, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x628, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddXline(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x629, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadModelSpace::InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x62a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation);
	return result;
}

LPDISPATCH IAcadModelSpace::AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BOOL;
	InvokeHelper(0x62b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PatternType, PatternName, Associativity);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x62c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		imageFileName, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x62d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&StartPoint, &EndPoint);
	return result;
}

BOOL IAcadModelSpace::GetIsLayout()
{
	BOOL result;
	InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x62f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadModelSpace::GetIsXRef()
{
	BOOL result;
	InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x631, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, NumRows, NumColumns, RowSpacing, ColumnSpacing);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x632, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList, &FaceList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMLine(const VARIANT& VertexList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x633, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x634, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadModelSpace::GetXRefDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x635, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL;
	InvokeHelper(0x636, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PathName, Name, &InsertionPoint, Xscale, Yscale, Zscale, Rotation, bOverlay);
	return result;
}

void IAcadModelSpace::Unload()
{
	InvokeHelper(0x637, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadModelSpace::Reload()
{
	InvokeHelper(0x638, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadModelSpace::Bind(BOOL bPrefixName)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x639, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPrefixName);
}

void IAcadModelSpace::Detach()
{
	InvokeHelper(0x63a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDocument properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDocument operations

LPDISPATCH IAcadDocument::GetModelSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPaperSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetBlocks()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDocument::CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Objects, &Owner, IdPairs);
	return result;
}

LPDISPATCH IAcadDocument::GetGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDimStyles()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetLayers()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetLinetypes()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDictionaries()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetRegisteredApplications()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetTextStyles()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetUserCoordinateSystems()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetViews()
{
	LPDISPATCH result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetViewports()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

double IAcadDocument::GetElevationModelSpace()
{
	double result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetElevationModelSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDocument::GetElevationPaperSpace()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetElevationPaperSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDocument::GetLimits()
{
	VARIANT result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetLimits(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadDocument::HandleToObject(LPCTSTR Handle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Handle);
	return result;
}

LPDISPATCH IAcadDocument::ObjectIdToObject(long ObjectID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ObjectID);
	return result;
}

LPDISPATCH IAcadDocument::GetLayouts()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPlotConfigurations()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPreferences()
{
	LPDISPATCH result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPlot()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetActiveLayer()
{
	LPDISPATCH result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLayer(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveLinetype()
{
	LPDISPATCH result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLinetype(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveDimStyle()
{
	LPDISPATCH result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveDimStyle(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveTextStyle()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveTextStyle(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveUCS()
{
	LPDISPATCH result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveUCS(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveViewport()
{
	LPDISPATCH result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveViewport(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActivePViewport()
{
	LPDISPATCH result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActivePViewport(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDocument::GetActiveSpace()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveSpace(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDocument::GetSelectionSets()
{
	LPDISPATCH result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetActiveSelectionSet()
{
	LPDISPATCH result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetFullName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetName()
{
	CString result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetPath()
{
	CString result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetObjectSnapMode()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetObjectSnapMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDocument::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetSaved()
{
	BOOL result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetMSpace()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetMSpace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH IAcadDocument::GetUtility()
{
	LPDISPATCH result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::Open(LPCTSTR FullName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FullName);
	return result;
}

void IAcadDocument::AuditInfo(BOOL FixErr)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FixErr);
}

LPDISPATCH IAcadDocument::Import(LPCTSTR FileName, const VARIANT& InsertionPoint, double ScaleFactor)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, &InsertionPoint, ScaleFactor);
	return result;
}

void IAcadDocument::Export(LPCTSTR FileName, LPCTSTR Extension, LPDISPATCH SelectionSet)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, Extension, SelectionSet);
}

LPDISPATCH IAcadDocument::New(LPCTSTR TemplateFileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TemplateFileName);
	return result;
}

void IAcadDocument::Save()
{
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::SaveAs(LPCTSTR FullFileName, const VARIANT& SaveAsType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullFileName, &SaveAsType);
}

void IAcadDocument::Wblock(LPCTSTR FileName, LPDISPATCH SelectionSet)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, SelectionSet);
}

void IAcadDocument::PurgeAll()
{
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT IAcadDocument::GetVariable(LPCTSTR Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Name);
	return result;
}

void IAcadDocument::SetVariable(LPCTSTR Name, const VARIANT& Value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, &Value);
}

void IAcadDocument::LoadShapeFile(LPCTSTR FullName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullName);
}

void IAcadDocument::Regen(long WhichViewports)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 WhichViewports);
}

LPDISPATCH IAcadDocument::GetPickfirstSelectionSet()
{
	LPDISPATCH result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetActive()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::Activate()
{
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::Close(const VARIANT& SaveChanges, const VARIANT& FileName)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SaveChanges, &FileName);
}

void IAcadDocument::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetWindowState()
{
	long result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetWidth()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetHeight()
{
	long result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLayout(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SendCommand(LPCTSTR Command)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Command);
}

long IAcadDocument::GetHwnd()
{
	long result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetWindowTitle()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::StartUndoMark()
{
	InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::EndUndoMark()
{
	InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadApplication properties

/////////////////////////////////////////////////////////////////////////////
// IAcadApplication operations

BOOL IAcadApplication::GetVisible()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadApplication::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadApplication::GetCaption()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetActiveDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetActiveDocument(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadApplication::GetFullName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetHeight()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadApplication::GetWindowLeft()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadApplication::GetPath()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetLocaleId()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetWindowTop()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadApplication::GetVersion()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetWidth()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadApplication::GetPreferences()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadApplication::GetStatusId(LPDISPATCH VportObj)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		VportObj);
	return result;
}

VARIANT IAcadApplication::ListArx()
{
	VARIANT result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadApplication::LoadArx(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

LPDISPATCH IAcadApplication::GetInterfaceObject(LPCTSTR ProgID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ProgID);
	return result;
}

void IAcadApplication::UnloadArx(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void IAcadApplication::Update()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::Quit()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadApplication::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetMenuGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetMenuBar()
{
	LPDISPATCH result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::LoadDVB(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void IAcadApplication::UnloadDVB(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

LPDISPATCH IAcadApplication::GetDocuments()
{
	LPDISPATCH result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::Eval(LPCTSTR Expression)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Expression);
}

long IAcadApplication::GetWindowState()
{
	long result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadApplication::RunMacro(LPCTSTR MacroPath)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroPath);
}

void IAcadApplication::ZoomExtents()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::ZoomAll()
{
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::ZoomCenter(const VARIANT& Center, double Magnify)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Center, Magnify);
}

void IAcadApplication::ZoomScaled(double scale, long ScaleType)
{
	static BYTE parms[] =
		VTS_R8 VTS_I4;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 scale, ScaleType);
}

void IAcadApplication::ZoomWindow(const VARIANT& LowerLeft, const VARIANT& UpperRight)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &LowerLeft, &UpperRight);
}

void IAcadApplication::ZoomPickWindow()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadApplication::GetAcadState()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::ZoomPrevious()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups operations

LPDISPATCH IAcadMenuGroups::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadMenuGroups::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::Load(LPCTSTR MenuFileName, const VARIANT& BaseMenu)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		MenuFileName, &BaseMenu);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup operations

LPDISPATCH IAcadMenuGroup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadMenuGroup::GetName()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadMenuGroup::GetType()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadMenuGroup::GetMenuFileName()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetMenus()
{
	LPDISPATCH result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetToolbars()
{
	LPDISPATCH result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadMenuGroup::Unload()
{
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadMenuGroup::Save(long MenuFileType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuFileType);
}

void IAcadMenuGroup::SaveAs(LPCTSTR MenuFileName, long MenuFileType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuFileName, MenuFileType);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus operations

LPDISPATCH IAcadPopupMenus::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPopupMenus::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::Add(LPCTSTR MenuName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		MenuName);
	return result;
}

void IAcadPopupMenus::InsertMenuInMenuBar(LPCTSTR MenuName, const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuName, &Index);
}

void IAcadPopupMenus::RemoveMenuFromMenuBar(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu operations

LPDISPATCH IAcadPopupMenu::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPopupMenu::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenu::GetName()
{
	CString result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenu::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPopupMenu::GetNameNoMnemonic()
{
	CString result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IAcadPopupMenu::GetShortcutMenu()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadPopupMenu::GetOnMenuBar()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddMenuItem(const VARIANT& Index, LPCTSTR Label, LPCTSTR Macro)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index, Label, Macro);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddSubMenu(const VARIANT& Index, LPCTSTR Label)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index, Label);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddSeparator(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void IAcadPopupMenu::InsertInMenuBar(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void IAcadPopupMenu::RemoveFromMenuBar()
{
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IAcadPopupMenu::GetTagString()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem operations

LPDISPATCH IAcadPopupMenuItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenuItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetLabel()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPopupMenuItem::GetTagString()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetTagString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadPopupMenuItem::GetEnable()
{
	BOOL result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetEnable(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPopupMenuItem::GetCheck()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetCheck(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPopupMenuItem::GetType()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenuItem::GetSubMenu()
{
	LPDISPATCH result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetMacro()
{
	CString result;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetMacro(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPopupMenuItem::GetIndex()
{
	long result;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetCaption()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetHelpString()
{
	CString result;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetHelpString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadPopupMenuItem::Delete()
{
	InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPopupMenuItem::GetEndSubMenuLevel()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetEndSubMenuLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar operations

LPDISPATCH IAcadMenuBar::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadMenuBar::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuBar::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuBar::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
