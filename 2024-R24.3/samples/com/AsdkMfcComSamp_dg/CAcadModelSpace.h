//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CAcadModelSpace wrapper class

class CAcadModelSpace : public COleDispatchDriver
{
public:
	CAcadModelSpace(){} // Calls COleDispatchDriver default constructor
	CAcadModelSpace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAcadModelSpace(const CAcadModelSpace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAcadModelSpace methods
public:
	CString get_Handle()
	{
		CString result;
		InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ObjectName()
	{
		CString result;
		InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void GetXData(LPCTSTR AppName, VARIANT * XDataType, VARIANT * XDataValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AppName, XDataType, XDataValue);
	}
	void SetXData(VARIANT XDataType, VARIANT XDataValue)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &XDataType, &XDataValue);
	}
	void Delete()
	{
		InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_ObjectID()
	{
		long result;
		InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Database()
	{
		LPDISPATCH result;
		InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_HasExtensionDictionary()
	{
		BOOL result;
		InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetExtensionDictionary()
	{
		LPDISPATCH result;
		InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_OwnerID()
	{
		long result;
		InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH result;
		InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Erase()
	{
		InvokeHelper(0x475, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH Item(VARIANT Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x600, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Origin()
	{
		VARIANT result;
		InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Origin(VARIANT newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	LPDISPATCH AddCustomObject(LPCTSTR ClassName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x603, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ClassName);
		return result;
	}
	LPDISPATCH Add3DFace(VARIANT Point1, VARIANT Point2, VARIANT point3, VARIANT Point4)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x604, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Point1, &Point2, &point3, &Point4);
		return result;
	}
	LPDISPATCH Add3DMesh(long M, long N, VARIANT PointsMatrix)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x605, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, M, N, &PointsMatrix);
		return result;
	}
	LPDISPATCH Add3DPoly(VARIANT PointsArray)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x606, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &PointsArray);
		return result;
	}
	LPDISPATCH AddArc(VARIANT Center, double Radius, double StartAngle, double EndAngle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x607, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, Radius, StartAngle, EndAngle);
		return result;
	}
	LPDISPATCH AddAttribute(double Height, long Mode, LPCTSTR Prompt, VARIANT InsertionPoint, LPCTSTR Tag, LPCTSTR Value)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x608, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Height, Mode, Prompt, &InsertionPoint, Tag, Value);
		return result;
	}
	LPDISPATCH AddBox(VARIANT Origin, double Length, double Width, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x609, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Origin, Length, Width, Height);
		return result;
	}
	LPDISPATCH AddCircle(VARIANT Center, double Radius)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x60a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, Radius);
		return result;
	}
	LPDISPATCH AddCone(VARIANT Center, double BaseRadius, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x60b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, BaseRadius, Height);
		return result;
	}
	LPDISPATCH AddCylinder(VARIANT Center, double Radius, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x60c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, Radius, Height);
		return result;
	}
	LPDISPATCH AddDimAligned(VARIANT ExtLine1Point, VARIANT ExtLine2Point, VARIANT TextPosition)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x60d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &ExtLine1Point, &ExtLine2Point, &TextPosition);
		return result;
	}
	LPDISPATCH AddDimAngular(VARIANT AngleVertex, VARIANT FirstEndPoint, VARIANT SecondEndPoint, VARIANT TextPoint)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x60e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
		return result;
	}
	LPDISPATCH AddDimDiametric(VARIANT ChordPoint, VARIANT FarChordPoint, double LeaderLength)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x60f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &ChordPoint, &FarChordPoint, LeaderLength);
		return result;
	}
	LPDISPATCH AddDimRotated(VARIANT ExtLine1Point, VARIANT ExtLine2Point, VARIANT DimLineLocation, double RotationAngle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x610, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &ExtLine1Point, &ExtLine2Point, &DimLineLocation, RotationAngle);
		return result;
	}
	LPDISPATCH AddDimOrdinate(VARIANT DefinitionPoint, VARIANT LeaderEndPoint, long UseXAxis)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_I4 ;
		InvokeHelper(0x611, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &DefinitionPoint, &LeaderEndPoint, UseXAxis);
		return result;
	}
	LPDISPATCH AddDimRadial(VARIANT Center, VARIANT ChordPoint, double LeaderLength)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, &ChordPoint, LeaderLength);
		return result;
	}
	LPDISPATCH AddEllipse(VARIANT Center, VARIANT MajorAxis, double RadiusRatio)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x613, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, &MajorAxis, RadiusRatio);
		return result;
	}
	LPDISPATCH AddEllipticalCone(VARIANT Center, double MajorRadius, double MinorRadius, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x614, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, MajorRadius, MinorRadius, Height);
		return result;
	}
	LPDISPATCH AddEllipticalCylinder(VARIANT Center, double MajorRadius, double MinorRadius, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x615, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, MajorRadius, MinorRadius, Height);
		return result;
	}
	LPDISPATCH AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_R8 VTS_R8 ;
		InvokeHelper(0x616, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Profile, Height, TaperAngle);
		return result;
	}
	LPDISPATCH AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x617, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Profile, Path);
		return result;
	}
	LPDISPATCH AddLeader(VARIANT PointsArray, LPDISPATCH Annotation, long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x618, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &PointsArray, Annotation, Type);
		return result;
	}
	LPDISPATCH AddMText(VARIANT InsertionPoint, double Width, LPCTSTR Text)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_BSTR ;
		InvokeHelper(0x619, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &InsertionPoint, Width, Text);
		return result;
	}
	LPDISPATCH AddPoint(VARIANT Point)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x61a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Point);
		return result;
	}
	LPDISPATCH AddLightWeightPolyline(VARIANT VerticesList)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x61b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &VerticesList);
		return result;
	}
	LPDISPATCH AddPolyline(VARIANT VerticesList)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x61c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &VerticesList);
		return result;
	}
	LPDISPATCH AddRay(VARIANT Point1, VARIANT Point2)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x61d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Point1, &Point2);
		return result;
	}
	VARIANT AddRegion(VARIANT ObjectList)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x61e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &ObjectList);
		return result;
	}
	LPDISPATCH AddRevolvedSolid(LPDISPATCH Profile, VARIANT AxisPoint, VARIANT AxisDir, double Angle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x61f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Profile, &AxisPoint, &AxisDir, Angle);
		return result;
	}
	LPDISPATCH AddShape(LPCTSTR Name, VARIANT InsertionPoint, double ScaleFactor, double RotationAngle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Name, &InsertionPoint, ScaleFactor, RotationAngle);
		return result;
	}
	LPDISPATCH AddSolid(VARIANT Point1, VARIANT Point2, VARIANT point3, VARIANT Point4)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Point1, &Point2, &point3, &Point4);
		return result;
	}
	LPDISPATCH AddSphere(VARIANT Center, double Radius)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x622, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, Radius);
		return result;
	}
	LPDISPATCH AddSpline(VARIANT PointsArray, VARIANT StartTangent, VARIANT EndTangent)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x623, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &PointsArray, &StartTangent, &EndTangent);
		return result;
	}
	LPDISPATCH AddText(LPCTSTR TextString, VARIANT InsertionPoint, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x624, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TextString, &InsertionPoint, Height);
		return result;
	}
	LPDISPATCH AddTolerance(LPCTSTR Text, VARIANT InsertionPoint, VARIANT Direction)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x625, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Text, &InsertionPoint, &Direction);
		return result;
	}
	LPDISPATCH AddTorus(VARIANT Center, double TorusRadius, double TubeRadius)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x626, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, TorusRadius, TubeRadius);
		return result;
	}
	LPDISPATCH AddTrace(VARIANT PointsArray)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x627, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &PointsArray);
		return result;
	}
	LPDISPATCH AddWedge(VARIANT Center, double Length, double Width, double Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x628, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Center, Length, Width, Height);
		return result;
	}
	LPDISPATCH AddXline(VARIANT Point1, VARIANT Point2)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x629, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Point1, &Point2);
		return result;
	}
	LPDISPATCH InsertBlock(VARIANT InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, VARIANT Password)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x62a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, &Password);
		return result;
	}
	LPDISPATCH AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity, VARIANT HatchObjectType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0x62b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PatternType, PatternName, Associativity, &HatchObjectType);
		return result;
	}
	LPDISPATCH AddRaster(LPCTSTR imageFileName, VARIANT InsertionPoint, double ScaleFactor, double RotationAngle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x62c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, imageFileName, &InsertionPoint, ScaleFactor, RotationAngle);
		return result;
	}
	LPDISPATCH AddLine(VARIANT StartPoint, VARIANT EndPoint)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x62d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &StartPoint, &EndPoint);
		return result;
	}
	BOOL get_IsLayout()
	{
		BOOL result;
		InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Layout()
	{
		LPDISPATCH result;
		InvokeHelper(0x62f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsXRef()
	{
		BOOL result;
		InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH AddMInsertBlock(VARIANT InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing, VARIANT Password)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x631, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, NumRows, NumColumns, RowSpacing, ColumnSpacing, &Password);
		return result;
	}
	LPDISPATCH AddPolyfaceMesh(VARIANT VertexList, VARIANT FaceList)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x632, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &VertexList, &FaceList);
		return result;
	}
	LPDISPATCH AddMLine(VARIANT VertexList)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x633, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &VertexList);
		return result;
	}
	LPDISPATCH AddDim3PointAngular(VARIANT AngleVertex, VARIANT FirstEndPoint, VARIANT SecondEndPoint, VARIANT TextPoint)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x634, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
		return result;
	}
	LPDISPATCH get_XRefDatabase()
	{
		LPDISPATCH result;
		InvokeHelper(0x635, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, VARIANT InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay, VARIANT Password)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0x636, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PathName, Name, &InsertionPoint, Xscale, Yscale, Zscale, Rotation, bOverlay, &Password);
		return result;
	}
	void Unload()
	{
		InvokeHelper(0x637, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Reload()
	{
		InvokeHelper(0x638, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Bind(BOOL bPrefixName)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x639, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bPrefixName);
	}
	void Detach()
	{
		InvokeHelper(0x63a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IAcadModelSpace properties
public:

};
