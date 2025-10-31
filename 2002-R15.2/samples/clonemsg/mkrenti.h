// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// mkrenti.h


#include "dbmain.h"
#include "geassign.h"
#include "gegbl.h"
#include "gegblabb.h"
#include "dbmain.h"         // entity

#define MESSAGE(x) acadErrorStatusText(x)

#define INTERNAL_STATUS_ERROR(x) \
  acrx_abort("!%s@%d: %s", __FILE__, __LINE__, MESSAGE(x))

#define AOK(what) { Acad::ErrorStatus stat = what; \
  if (stat != Acad::eOk) INTERNAL_STATUS_ERROR(stat); }

#define ASSERT( x )  if (!(x)) acrx_abort( /*NOXLATE*/"INTERNAL ERROR" ); else

// definition of your own entity AsdkMkrEntity

class AsdkMkrEntity : public AcDbEntity
{
public:
  ACRX_DECLARE_MEMBERS(AsdkMkrEntity);

  /////////////////////////////////////////////////////////
  // Constructors and destructor
  /////////////////////////////////////////////////////////

  AsdkMkrEntity();
  virtual ~AsdkMkrEntity();


  /////////////////////////////////////////////////////////
  // Methods specific to AsdkMkrEntity
  /////////////////////////////////////////////////////////

  void setPos(const AcGePoint3d&);
  void setId(const AcDbObjectId&);
  AcDbObjectId id() const;


  /////////////////////////////////////////////////////////
  // Overridden methods from AcDbEntity
  /////////////////////////////////////////////////////////

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
  virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& x0) const;
  virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices,
                                                const AcGeVector3d& offset);
  virtual Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                          AcDb::Intersect intType,
                                          AcGePoint3dArray& points,
                                          int thisGsMarker = 0,
                                          int otherGsMarker = 0) const;
  virtual Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                          AcDb::Intersect intType,
                                          const AcGePlane& projPlane,
                                          AcGePoint3dArray& points,
                                          int thisGsMarker = 0,
                                          int otherGsMarker = 0) const;
  virtual void list() const;
  virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
  virtual Acad::ErrorStatus getTransformedCopy(const AcGeMatrix3d& xform,
                                               AcDbEntity*& ent) const;
  virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
  virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;


  /////////////////////////////////////////////////////////
  // Overridden methods from AcDbObject
  /////////////////////////////////////////////////////////

private:

  AcGePoint3d       m_center;
#ifdef DIRECT
  AcDbHardOwnershipId m_refId;
#elif defined( HARDPOINTER )
  AcDbHardPointerId m_refId;
#else
  AcDbSoftPointerId m_refId;
#endif

};  // END

