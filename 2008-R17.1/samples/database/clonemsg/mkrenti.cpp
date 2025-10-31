// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
// mkrenti.cpp
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "assert.h"
#include "dbmain.h"
#include "acdb.h"
#include "acdbabb.h"
#include "MkrEnti.h"
#include "acgi.h"
#include "tchar.h"




// Code for the Class Body.
//
ACRX_DXF_DEFINE_MEMBERS(AsdkMkrEntity, AcDbEntity, 
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
                        0, ASDKMKRENTITY, ASDKMKR)


AsdkMkrEntity::AsdkMkrEntity()
: m_center( 0.0, 0.0, 0.0 ), m_refId( 0 )
{
}

AsdkMkrEntity::~AsdkMkrEntity()
{
}

void
AsdkMkrEntity::setPos( const AcGePoint3d& pt )
{
    assertWriteEnabled();
    m_center = pt;
}

void
AsdkMkrEntity::setId(const AcDbObjectId& id )
{
    assertWriteEnabled();
    m_refId = id;
}

AcDbObjectId
AsdkMkrEntity::refId() const
{
	assertReadEnabled();
    return m_refId;
}

//
// Overridden methods from AcDbEntity
//

Acad::ErrorStatus
AsdkMkrEntity::getOsnapPoints(AcDb::OsnapMode osnapMode,
                              int gsSelectionMark,
                              const AcGePoint3d& pickPoint,
                              const AcGePoint3d& lastPoint,
                              const AcGeMatrix3d& viewXform,
                              AcGePoint3dArray& snapPoints,
                              AcDbIntArray& geomIds) const
{
    assertReadEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::getGripPoints(AcGePoint3dArray& gripPoints,
                             AcDbIntArray& osnapModes,
                             AcDbIntArray& geomIds) const
{
    assertReadEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::moveGripPointsAt(const AcDbIntArray& indices,
                                const AcGeVector3d& offset)
{
    assertWriteEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::getStretchPoints(AcGePoint3dArray& x0) const
{
    assertReadEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::moveStretchPointsAt(const AcDbIntArray& indices,
                                   const AcGeVector3d& offset)
{
    assertWriteEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::intersectWith(const AcDbEntity* ent,
                             AcDb::Intersect intType,
                             AcGePoint3dArray& points,
                             int thisGsMarker,
                             int otherGsMarker) const
{
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::intersectWith(const AcDbEntity* ent,
                             AcDb::Intersect intType,
                             const AcGePlane& projPlane,
                             AcGePoint3dArray& points,
                             int thisGsMarker,
                             int otherGsMarker) const
{
    return Acad::eOk;
}


void
AsdkMkrEntity::list() const
{
    assertReadEnabled();
    AcDbEntity::list();
    acutPrintf( _T("%18sCenter at: %-9.16q0,%-9.16q0,%-9.16q0\n"),
        _T(""), m_center[0], m_center[1], m_center[2] );
    acutPrintf( _T("%18sAssociated object id: %x\n"), _T(""), m_refId.asOldId() );
}


Acad::ErrorStatus
AsdkMkrEntity::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    m_center.transformBy( xform );
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::getTransformedCopy(const AcGeMatrix3d& xform,
                                  AcDbEntity*& ent) const
{
    assertReadEnabled();
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkMkrEntity::explode(AcDbVoidPtrArray& entitySet) const
{
    assertReadEnabled();
    return Acad::eOk;
}


Adesk::Boolean
AsdkMkrEntity::worldDraw(AcGiWorldDraw* mode)
{
    assertReadEnabled();
    mode->geometry().circle( m_center, 2.0, AcGeVector3d::kZAxis );
    return Adesk::kTrue;
}


Acad::ErrorStatus
AsdkMkrEntity::dwgInFields(AcDbDwgFiler* filer)
{
  assertWriteEnabled();

  Acad::ErrorStatus es;

  // call dwgInFields from AcDbEntity
  //
  if ((es = AcDbEntity::dwgInFields(filer)) != Acad::eOk) {
    return es;
  }
  filer->readItem( &m_center );
  filer->readItem( &m_refId );

  return es;
}


Acad::ErrorStatus
AsdkMkrEntity::dwgOutFields(AcDbDwgFiler* filer) const
{
  assertReadEnabled();

  Acad::ErrorStatus es;

  // call dwgOutFields from AcDbEntity
  //
  if ((es = AcDbEntity::dwgOutFields(filer)) != Acad::eOk) {
    return es;
  }
  filer->writeItem( m_center );
  filer->writeItem( m_refId );

  return es;
}


Acad::ErrorStatus
AsdkMkrEntity::dxfInFields(AcDbDxfFiler* filer)
{
  assertWriteEnabled();

  Acad::ErrorStatus es = eOk;
  resbuf rb;

  if ((AcDbEntity::dxfInFields(filer) != Acad::eOk) ||
      !filer->atSubclassData(_T(/*NOXLATE*/"AsdkMkrEntity"))) {
    return filer->filerStatus();
  }

  while ((es == eOk) && ((es = filer->readResBuf(&rb)) == eOk)) {

    switch (rb.restype) {
      case kDxfXCoord:
          m_center = asPnt3d( rb.resval.rpoint );
          break;
#ifdef DIRECT
      case kDxfHardOwnershipId:
#elif defined( HARDPOINTER )
      case kDxfHardPointerId:
#else
      case kDxfSoftPointerId:
#endif
          m_refId.setFromOldId( rb.resval.mnLongPtr );
          break;
      default:
        filer->pushBackItem();
        es = Acad::eEndOfFile;
        break;
    } /*switch*/
  } /*while*/

  if (es != Acad::eEndOfFile)
    return eInvalidResBuf;

  return es;
}


Acad::ErrorStatus
AsdkMkrEntity::dxfOutFields(AcDbDxfFiler* filer) const
{
  assertReadEnabled();

  Acad::ErrorStatus es;

  es = AcDbEntity::dxfOutFields(filer);
  assert(es == Acad::eOk);

  es = filer->writeItem(AcDb::kDxfSubclass, _T(/*NOXLATE*/"AsdkMkrEntity"));
  assert(es == Acad::eOk);
  filer->writeItem( AcDb::kDxfXCoord, m_center );
#ifdef DIRECT
  filer->writeItem( kDxfHardOwnershipId, m_refId );
#elif defined( HARDPOINTER )
  filer->writeItem( kDxfHardPointerId, m_refId );
#else
  filer->writeItem( kDxfSoftPointerId, m_refId );
#endif

  return es;
}
