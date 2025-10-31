//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// squarent.cpp
// 
// Example square custom entity
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <Windows.h>
#include <acgi.h> 
#include <aced.h>
#include <acdb.h>
#include <dbsymtb.h>
#include <dbproxy.h>

#include <adslib.h>

#include "squarent.h"
#include "tchar.h"

#include <objbase.h>
#include <initguid.h>
#include "..\AsdkSquareWrap\AsdkSquareLib_i.c"



const TCHAR* kClassName = _T("AsdkSquare");


ACRX_DXF_DEFINE_MEMBERS(AsdkSquare, AcDbCurve, 
						AcDb::kDHL_1012, AcDb::kMRelease0, 
						AcDbProxyEntity::kEraseAllowed,
                        ASDKSQUARE, _T("SquareApp|By: ADF Pubs"))

AsdkSquare::AsdkSquare() : mNormal (0.0,0.0,1.0), mOrient(1.0,0.0,0.0),mId(0)
{
}

AsdkSquare::~AsdkSquare()
{
}

Adesk::Boolean
AsdkSquare::subWorldDraw(AcGiWorldDraw* wd)
{
	AcGeVector3d orient, trans;

	orient = trans = mOrient;
	trans.rotateBy(HALFPI, mNormal);

	int i;
	AcGePoint3d* aSquare_side = NULL;
	Adesk::Int32* pFaceList = NULL;

	switch (wd->regenType()) {

	case kAcGiStandardDisplay:
    case kAcGiSaveWorldDrawForR12:
    case kAcGiSaveWorldDrawForProxy:
	
		aSquare_side = new AcGePoint3d[2];
		for (i = 0; i < 4; i++) {
			switch(i) {
			case 0:
		        aSquare_side[0] = mCenter + orient;
			    aSquare_side[1] = mCenter + trans;
				break;
			case 1:
				aSquare_side[0] = mCenter + trans;
			    aSquare_side[1] = mCenter - orient;
				break;
			case 2:
		        aSquare_side[0] = mCenter - orient;
			    aSquare_side[1] = mCenter - trans;
				break;
			case 3:
		        aSquare_side[0] = mCenter - trans;
			    aSquare_side[1] = mCenter + orient;
				break;
			}

			wd->subEntityTraits().setSelectionMarker(i);
			wd->geometry().polyline(2, aSquare_side);
		}
		double height;
		squareSideLength(height);
		height = height / 8.0;
		TCHAR strId[5]; 
		_itot(mId, strId, 10);

		wd->geometry().text(mCenter,
                            mNormal,
                            mOrient,
							height,
                                 1.0,
                                 0.0,
                                 strId);
		
		break;        
	case kAcGiHideOrShadeCommand:
	case kAcGiShadedDisplay:
		pFaceList = new Adesk::Int32[8];

		pFaceList[0] = 3;
		pFaceList[1] = 0;
		pFaceList[2] = 1;
		pFaceList[3] = 2;
		pFaceList[4] = 3;
		pFaceList[5] = 2;
		pFaceList[6] = 3;
		pFaceList[7] = 0;

		aSquare_side = new AcGePoint3d[4];
		aSquare_side[0] = mCenter + orient;
		aSquare_side[1] = mCenter + trans;
		aSquare_side[2] = mCenter - orient;
		aSquare_side[3] = mCenter - trans;
		wd->geometry().shell(4, aSquare_side, 8, pFaceList);
				
		delete pFaceList;
		break;
	default:
		assert(Adesk::kFalse);

	}
	
	if (aSquare_side != NULL)
		delete [] aSquare_side;

	return Adesk::kTrue;
	
}

Acad::ErrorStatus
AsdkSquare::dwgInFields( AcDbDwgFiler* filer )
{

  assertWriteEnabled();

  Acad::ErrorStatus es;
  
  es = AcDbEntity::dwgInFields( filer );
  if (es != Acad::eOk) return es;

  es = filer->readItem( &mCenter );
  if (es != Acad::eOk) return es;

  es = filer->readItem( &mOrient );
  if (es != Acad::eOk) return es;
  
  es = filer->readItem( &mNormal );
  if (es != Acad::eOk) return es;

  return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSquare::dwgOutFields( AcDbDwgFiler* filer ) const
{
  assertReadEnabled();

  Acad::ErrorStatus es;
  es = AcDbEntity::dwgOutFields( filer );
  if (es != Acad::eOk) return es;

  es = filer->writeItem( mCenter );
  if (es != Acad::eOk) return es;
  
  es = filer->writeItem( mOrient );
  if (es != Acad::eOk) return es;
  
  es = filer->writeItem( mNormal );
  if (es != Acad::eOk) return es;

  return filer->filerStatus();
}


Acad::ErrorStatus
AsdkSquare::dxfInFields( AcDbDxfFiler* filer )
{
  assertWriteEnabled();

  struct resbuf rb;

  Acad::ErrorStatus es = AcDbEntity::dxfInFields( filer );

  if ( es != Acad::eOk ) {
    return es;
  }

  if( !filer->atSubclassData( kClassName ) ) {
    return Acad::eBadDxfSequence;
  }

  while ( es == Acad::eOk ) {
    if ( (es = filer->readItem( &rb )) == Acad::eOk ) {
      switch(rb.restype) {

      case AcDb::kDxfXCoord:
        mCenter.set( rb.resval.rpoint[X], 
          rb.resval.rpoint[Y], rb.resval.rpoint[Z] );
        break;
      case AcDb::kDxfNormalX:
        mNormal.set( rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z] );
		break;
      case AcDb::kDxfNormalX + 1:
        mOrient.set( rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z] );
		break;

      }
    }
  }
  return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSquare::dxfOutFields( AcDbDxfFiler* filer ) const
{
  assertReadEnabled();

  AcDbEntity::dxfOutFields(filer);

  filer->writeItem( AcDb::kDxfSubclass, kClassName );

  filer->writeItem( AcDb::kDxfXCoord, mCenter );

  filer->writeItem( AcDb::kDxfNormalX + 1, mOrient );

  filer->writeItem( AcDb::kDxfNormalX, mNormal );

  return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSquare::subGetOsnapPoints(
    AcDb::OsnapMode       osnapMode,
    Adesk::GsMarker       gsSelectionMark,
    const AcGePoint3d&    pickPoint,
    const AcGePoint3d&    lastPoint,
    const AcGeMatrix3d&   viewXform,
    AcGePoint3dArray&     snapPoints,
    AcDbIntArray&         /*geomIds*/) const
{
    assertReadEnabled();
    Acad::ErrorStatus es = Acad::eOk;

   if (   osnapMode != AcDb::kOsModeEnd
        && osnapMode != AcDb::kOsModeMid
        && osnapMode != AcDb::kOsModeNear
        && osnapMode != AcDb::kOsModePerp
        && osnapMode != AcDb::kOsModeCen)
    {
        return Acad::eOk;
    }

	AcGeVector3d orient, trans;
	orient = trans = mOrient;
	trans.rotateBy(HALFPI, mNormal);

    AcGeLineSeg3d lnsg;
    AcGeLine3d line;
    AcGeVector3d vec;
	AcGePoint3d pt;
	AcGeVector3d viewDir(viewXform(Z, 0), viewXform(Z, 1), viewXform(Z, 2));

	switch(gsSelectionMark) {
	case 0:
        lnsg.set((mCenter + orient),(mCenter + trans));
		break;
	case 1:
        lnsg.set((mCenter + trans),(mCenter - orient));
		break;
	case 2:
		lnsg.set((mCenter - orient),(mCenter - trans));
		break;
	case 3:
	    lnsg.set((mCenter - trans),(mCenter + orient));
		break;
	}

    switch (osnapMode) {

    case AcDb::kOsModeEnd:

		snapPoints.append(lnsg.startPoint());
		snapPoints.append(lnsg.endPoint());		
		break;

    case AcDb::kOsModeNear:
        pt = lnsg.projClosestPointTo(pickPoint, viewDir);
        snapPoints.append(pt);
        break;

    case AcDb::kOsModeCen:
        snapPoints.append(mCenter);
        break;

    case AcDb::kOsModeMid:
		snapPoints.append(lnsg.midPoint());
		break;
    
	case AcDb::kOsModePerp:
        vec = lnsg.startPoint() - lnsg.endPoint();
        vec.normalize();
        line.set(lnsg.startPoint(), vec);
        pt = line.closestPointTo(lastPoint);
        snapPoints.append(pt);
        break;
    
	default:
        return Acad::eOk;
    }
    return es;
}

Acad::ErrorStatus
AsdkSquare::subGetGripPoints(
    AcGePoint3dArray& gripPoints,
    AcDbIntArray& osnapModes,
    AcDbIntArray& geomIds) const
{
    assertReadEnabled();

	AcGePoint3dArray aSquare;
	aSquare.setLogicalLength(5);

	AcGeVector3d orient, trans;
	orient = trans = mOrient;
	trans.rotateBy(HALFPI, mNormal);

    aSquare[0] = mCenter + orient;
    aSquare[1] = mCenter + trans;
    aSquare[2] = mCenter - orient;
    aSquare[3] = mCenter - trans;
	aSquare[4] = mCenter;

 	gripPoints.append(aSquare);

	return Acad::eOk;
}

Acad::ErrorStatus
AsdkSquare::subMoveGripPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();
	AcGeVector3d trans = mOrient;
	trans.rotateBy(HALFPI, mNormal);

	for (int i = 0; i < indices.length(); i++) {
		switch (indices[i]) {
		case 0:
			this->setSquareOrient(mOrient + offset);
			break;
		case 1:
			this->setSquareOrient(trans + offset);
			break;
		case 2:
			this->setSquareOrient(mOrient.mirror(mNormal) - offset);
			break;
		case 3:
			this->setSquareOrient(trans.mirror(mNormal) - offset);
			break;
		case 4:
			this->setSquareCenter(mCenter + offset);
			break;
		}

	}

    return Acad::eOk;
}

void
AsdkSquare::subList() const
{
	assertReadEnabled();

    // Must call subList() rather than list() because if this method
    // was called from an execution of list(), then we'll end up in an
    // infinite recursion which will cause a crash when the stack
    // overflows.
    //
	AcDbEntity::subList();

	double size;
	squareSideLength(size);

	int id;
	squareId(id);

    ads_printf(_T("\n\tId of Square: \t\t%d"), id);
    ads_printf(_T("\n\tCenter Point: \t\t%f, %f, %f"), mCenter[X], mCenter[Y], mCenter[Z]);

    ads_printf(_T("\n\tOrientation Vector: \t\t%f, %f, %f"), mOrient[X], mOrient[Y], mOrient[Z]);
    ads_printf(_T("\n\tNormal Vector: \t\t%f, %f, %f"), mNormal[X], mNormal[Y], mNormal[Z]);

    ads_printf(_T("\n\tSize of Square: \t\t%f"), size);
    ads_printf(_T("\n\tArea of Square: \t\t%f"), size * size);
  
}

Acad::ErrorStatus
AsdkSquare::subTransformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

	AcGePoint3d xquad = mCenter + mOrient;
	xquad.transformBy(xform);
  
	mCenter.transformBy(xform);
	mOrient.transformBy(xform);

    mNormal.transformBy(xform);
    mNormal.normalize();
    return Acad::eOk;

}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus
AsdkSquare::subGetClassID(CLSID* pClsid) const
{
    *pClsid = CLSID_AsdkSquareWrapper;
    return Acad::eOk;
}

// END CODE APPEARING IN SDK DOCUMENT.

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		AsdkSquare::rxInit();
		acrxBuildClassHierarchy();

        break;
    case AcRx::kUnloadAppMsg:
        deleteAcRxClass(AsdkSquare::desc());
        break;
    case AcRx::kLoadDwgMsg:

        break;
    case AcRx::kUnloadDwgMsg:

        break;
	case AcRx::kInvkSubrMsg:

		break;
    default:
		;
    }
    return AcRx::kRetOK;
}

