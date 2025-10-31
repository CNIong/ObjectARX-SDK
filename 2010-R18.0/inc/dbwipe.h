//
//
//////////////////////////////////////////////////////////////////////////////
//   Copyright (C) 1997-2009 by Autodesk, Inc. 
//
//   Permission to use, copy, modify, and distribute this software in
//   object code form for any purpose and without fee is hereby granted, 
//   provided that the above copyright notice appears in all copies and 
//   that both that copyright notice and the limited warranty and
//   restricted rights notice below appear in all supporting 
//   documentation.
//
//   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
//   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
//   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
//   UNINTERRUPTED OR ERROR FREE.
//
//   Use, duplication, or disclosure by the U.S. Government is subject to 
//   restrictions set forth in FAR 52.227-19 (Commercial Computer
//   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
//   (Rights in Technical Data and Computer Software), as applicable. 
//

#ifndef __DBWIPE_H__
#define __DBWIPE_H__

#ifdef _DBWIPEOBJ_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP
#endif

#include "windows.h"
#include "imgdef.h"
#include "imgent.h"

namespace Atil
{
    class Image;
};

#define WIPEOUTOBJSERVICE	/*NOXLATE*/ACRX_T("WipeOut")

/////////////////////////////////////////////////////////////////////////////
// AcDbWipeout class
//
#pragma warning(push)
#pragma warning( disable : 4275 ) 
class DLLIMPEXP AcDbWipeout : public AcDbRasterImage
{
public:
    ACRX_DECLARE_MEMBERS(AcDbWipeout);

                                AcDbWipeout();

    // AcDbEntity overrides
    //
    virtual AcRxObject*         clone() const;

// AcDbRasterImage overwritten methods.

    virtual AcGeVector2d        imageSize(Adesk::Boolean bGetCachedValue = Adesk::kFalse) const;
    AcGiSentScanLines*          getScanLines(const AcGiRequestScanLines& req) const;
	Adesk::Boolean				isClipped() const;
	virtual void				setDisplayOpt(
                                    ImageDisplayOpt option, 
                                    Adesk::Boolean bValue
                                );
	virtual Adesk::Boolean		isSetDisplayOpt(ImageDisplayOpt option) const;

	virtual Acad::ErrorStatus	setBrightness( Adesk::Int8 value );
	virtual Adesk::Int8			brightness() const;
	
	virtual Acad::ErrorStatus	setContrast( Adesk::Int8 value );
	virtual Adesk::Int8			contrast() const;

	virtual Acad::ErrorStatus	setFade( Adesk::Int8 value );
	virtual Adesk::Int8			fade() const;

    virtual AcGeVector2d        scale() const;

// Wipeout specific functions

    Acad::ErrorStatus           append(AcDbObjectId& id);
    static Acad::ErrorStatus    createImageDefinition();
    static Acad::ErrorStatus    fitPointsToImage(
                                    AcGePoint2dArray& pointArray,
                                    AcGePoint2d& minPoint,
                                    double& scale,
                                    Adesk::Boolean bFlipY = Adesk::kFalse);
    Adesk::Boolean              frame() const;
    Adesk::Boolean              setFrame(Adesk::Boolean bFrame);

protected:
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* mode);
    virtual void                subViewportDraw(AcGiViewportDraw* mode);

    virtual void                subList() const;

    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                   const AcDbVoidPtrArray& gripAppData,
                                   const AcGeVector3d& offset, 
                                   const int bitflags);
    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                   const AcDbIntArray& indices,
                                   const AcGeVector3d&     offset);
    virtual Acad::ErrorStatus   subTransformBy(
                                    const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus   subGetTransformedCopy(
                                    const AcGeMatrix3d& xform,
                                    AcDbEntity*& ent
                                ) const;
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;

private:
    Adesk::Boolean              isHighlighted() const;

    void                        getPlane(AcGeBoundedPlane& boundedPlane) const;
    AcGeMatrix2d                fastMatrixInvert(const AcGeMatrix2d& m) const;
    void                        drawFrame(
                                    AcGiViewportDraw* mode,
                                    const AcGePoint3dArray& verts) const;
    Acad::ErrorStatus           setDcToScreen(
                                    const AcGePoint2d& lowerLeft,
                                    const AcGePoint2d& upperRight,
                                    int width,
                                    int height,
                                    AcGeMatrix2d& dcToScreen) const;
    void                        setFrameExtents(
                                    AcGiWorldDraw* mode,
                                    const AcGePoint3dArray& verts) const;

public:
    static long                 mImageData;
private:
    Adesk::Boolean              mHighlight;

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them
    // private in order to prevent usage of them.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](size_t nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif
};
#pragma warning(pop)
#endif //__DBWIPE_H__
