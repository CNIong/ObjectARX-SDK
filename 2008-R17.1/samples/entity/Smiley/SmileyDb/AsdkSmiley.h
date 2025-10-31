//
// (C) Copyright 2000-2007 by Autodesk, Inc. 
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

// AsdkSmiley custom object.

#if !defined(ARX__ASDKSMILEY_H__19990215_125311)
#define ARX__ASDKSMILEY_H__19990215_125311

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4275 4251)

#ifdef _SMILEYDB_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ASDKSMILEYDB_DBXSERVICE
#define ASDKSMILEYDB_DBXSERVICE _T("ASDKSMILEYDB_DBXSERVICE")
#endif


#include <dbents.h>
#include <acgi.h>
#include <math.h>

#include <objbase.h>

class DLLIMPEXP AsdkSmiley : public AcDbEntity
{
public:

	ACRX_DECLARE_MEMBERS(AsdkSmiley);

	// Constructor / Destructor
	AsdkSmiley();
	virtual ~AsdkSmiley();

	//{{AFX_ARX_METHODS(AsdkSmiley)
	virtual Acad::ErrorStatus setBackColor( const AcCmEntityColor& color);
	virtual Acad::ErrorStatus setColor(const AcCmEntityColor& color,
	                                   Adesk::Boolean doSubents = true);
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
	virtual void list() const;
	virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
	                                         int gsSelectionMark,
	                                         const AcGePoint3d& pickPoint,
	                                         const AcGePoint3d& lastPoint,
	                                         const AcGeMatrix3d& viewXform,
	                                         AcGePoint3dArray& snapPoints,
	                                         AcDbIntArray& geomIds) const;
	virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray& gripPoints,
	                                        AcDbIntArray& osnapModes,
	                                        AcDbIntArray& geomIds) const;
	virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
	                                           const AcGeVector3d& offset);
	virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& stretchPoints) const;
	virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices,
	                                              const AcGeVector3d& offset);
	virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
	virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);
    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
	//}}AFX_ARX_METHODS

	//{{AFX_ARX_DATA_ACCESS(AsdkSmiley)
	//}}AFX_ARX_DATA_ACCESS


    // Smiley specific protocol
    //
    // smiley center
    virtual AcGePoint3d center() const;
    virtual void setCenter(const AcGePoint3d c);

    // smiley radius
    virtual double radius() const;
    virtual void setRadius(const double r);
    virtual void scaleRadius(const double r);

    // smiley normal
    virtual AcGeVector3d normal() const;
    virtual void setNormal(const AcGeVector3d v);

    // smiley eyes apart
    virtual double eyesApart() const;
    virtual void setEyesApart(const double d);

    // smiley eyes height
    virtual double eyesHeight() const;
    virtual void setEyesHeight(const double h);

    // smiley eyes size
    virtual double eyeSize() const;
    virtual void setEyeSize(const double s);

    // eye locations
    virtual void eyes(AcGePoint3dArray &array) const;

    virtual AcGePoint3d mouthCenter() const;
    virtual double mouthRadius() const;

    // left point of mouth arc (smile)
    virtual AcGePoint3d mouthLeft() const;
    virtual void setMouthLeft(const AcGePoint3d &p);

    // bottom point of mouth arc (smile)
    virtual AcGePoint3d mouthBottom() const;
    virtual void setMouthBottom(const AcGePoint3d &p);

    // right point of mouth arc (smile)
    virtual AcGePoint3d mouthRight() const;
    virtual void setMouthRight(const AcGePoint3d &p);

    // whole mouth
    virtual void setMouth( const AcGePoint3d& left, const AcGePoint3d& bottom, const AcGePoint3d& right);

    // ensure radius is sufficiently large to accomodate features
    virtual void ensureRadius();

	virtual AcCmEntityColor AsdkSmiley::backColor();
	
	static void initCLSID();

private:

    Acad::ErrorStatus osnapNear(
                                const AcGePoint3d&  pickPoint,
                                AcGePoint3dArray&   snapPoints) const;
    Acad::ErrorStatus osnapCen(
                                const AcGePoint3d&  pickPoint,
                                AcGePoint3dArray&   snapPoints) const;
    Acad::ErrorStatus osnapQuad(
                                const AcGePoint3d&  pickPoint,
                                AcGePoint3dArray&   snapPoints) const;

private:
	//{{AFX_ARX_DATA(AsdkSmiley)
	//}}AFX_ARX_DATA

    // data members
    //
    AcGeVector3d  mnormal;            // smiley normal vector
    double        meyesapart;         // smiley eyes apart
    double        meyesheight;        // smiley eyes height
    double        meyesize;           // smiley eye size
    AcGeCircArc3d mfacecircle;        // smiley mouth arc (not written out)
    AcGeCircArc3d mmoutharc;          // smiley mouth arc (not written out)
	AcDbObjectId  mFriend;
	
	AcCmEntityColor mbackcolor;


	static bool   s_bHasClsid;
	static CLSID  s_clsid;		      // COM wrapper's CLSID, for OPM exposure

private:

	void *operator new[](size_t nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](size_t nSize, const TCHAR *file, int line) { return 0; }

};

#endif // !defined(ARX__ASDKSMILEY_H__19990215_125311)