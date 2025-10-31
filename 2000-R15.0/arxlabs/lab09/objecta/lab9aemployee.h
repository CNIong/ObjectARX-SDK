//
// (C) Copyright 1999 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//
#ifndef _Employee_h_
#define _Employee_h_

//-----------------------------------------------------------------------------
#define OARX_FIRM_DICT "OARX_DICT" //----- Firm Dictionary
#define OARX_APP_DICT "OARX_LAB9_DICT" //----- Application Dictionary
#define MODULE_NAME "OarxLab9a"
#define MODULE_FILENAME "OarxLab9a.dbx"

//-----------------------------------------------------------------------------
//----- This is the Custom Entity Declaration
class OarxEmployee : public AcDbEntity {

	static unsigned long mVersion ;

protected:
    long mID ;
    long mCubeNumber ;
    char *mFirstName ;
    char *mLastName ;
	AcGePoint3d mCenter ;

	void CleanUp () ;

public:
	ACRX_DECLARE_MEMBERS (OarxEmployee);

public:
	OarxEmployee () ;
	virtual ~OarxEmployee () ;

	//----- Note: All methods must be implemented as 'virtual', because
	//----- we want to export our class to another ARX module without using
	//----- the Microsoft 'lib' link mechanism...

	//----- Set/Get protocol
	virtual long ID () const ;
	virtual Acad::ErrorStatus setID (const long ID) ;

	virtual long cubeNumber () const ;
	virtual Acad::ErrorStatus setCubeNumber (const long cubeNumber) ;

	virtual const char *firstName () const ;
	virtual Acad::ErrorStatus setFirstName (const char *strFirstName) ;

	virtual const char *lastName () const ;
	virtual Acad::ErrorStatus setLastName (const char *strLastName) ;

	virtual const AcGePoint3d center () const ;
	virtual Acad::ErrorStatus setCenter (const AcGePoint3d center) ;

	//----- DXF implementation
	//----- Supports Lisp Entget, DxfIn, DxfOut. etc...
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

	//----- Dwg implementation
	//----- Supports Open from/Save to DWG file, COPY, MOVE, etc...
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	//----- Implements graphical representation to all views
	virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;

	//----- EXPLODE command
	virtual Acad::ErrorStatus explode (AcDbVoidPtrArray &entitySet) const ;

	//----- Implement Grips
	virtual Acad::ErrorStatus getGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapMasks, AcDbIntArray &geomIds) const ;
	virtual Acad::ErrorStatus moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ;

	//----- Support MOVE, COPY, etc...
	virtual Acad::ErrorStatus transformBy (const AcGeMatrix3d &xform) ;

	virtual Acad::ErrorStatus getOsnapPoints (
			AcDb::OsnapMode osnapMode, int gsSelectionMark, const AcGePoint3d &pickPoint,
			const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform, AcGePoint3dArray &snapPoints,
			AcDbIntArray &geomIds) const ;

	//----- Implement Stretches, and Support the STRETCH command
	virtual Acad::ErrorStatus getStretchPoints (AcGePoint3dArray &stretchPoints) const ;
	virtual Acad::ErrorStatus moveStretchPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ;

} ;

//-----------------------------------------------------------------------------
//----- This is the AcRxService class Declaration
class OarxEmployeeService : public AcRxService {

public:
	virtual Adesk::Boolean isEmployeeExist (int id) ;
	virtual AcDbObjectId getAppDictionary () ;

	virtual OarxEmployee *createEmployee (int id, AcGePoint3d location, int cubeNumber, char *strFirstName, char *strLastName) ;

} ;

#define EmployeeServiceName "OarxEmployeeService"
#define EmployeeService ((OarxEmployeeService *)acrxServiceDictionary->at (EmployeeServiceName))

#endif //----- _Employee_h_
