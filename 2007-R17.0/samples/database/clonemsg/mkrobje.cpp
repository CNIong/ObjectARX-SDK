// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
//  mkrobje.cpp
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "assert.h"
#include "dbmain.h"
#include "acdb.h"
#include "acdbabb.h"
#include "mkrobje.h"
#include <dbproxy.h>
#include "tchar.h"




// Code for the Class Body.
//
ACRX_DXF_DEFINE_MEMBERS(AsdkMkrObject, AcDbObject, 
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        0, ASDKMKROBJECT, ASDKMKR)


// Overridden methods from AcDbObject

Acad::ErrorStatus AsdkMkrObject::dwgInFields(AcDbDwgFiler* filer)
{
  assertWriteEnabled();

  Acad::ErrorStatus es;

  // call dwgInFields from AcDbObject
  if ((es = AcDbObject::dwgInFields(filer)) != Acad::eOk) {
    return es;
  }
  // TODO: add the functions for your own membervariables in the following way:
  // es = filer->readItem(&m...);
  // assert(es == Acad::eOk);

  return es;
}


Acad::ErrorStatus AsdkMkrObject::dwgOutFields(AcDbDwgFiler* filer) const
{
  assertReadEnabled();

  Acad::ErrorStatus es;

  // call dwgOutFields from AcDbObject
  if ((es = AcDbObject::dwgOutFields(filer)) != Acad::eOk) {
    return es;
  }
  // TODO: add the functions for your own membervariables in the following way:
  // es = filer->writeItem(m...);
  // assert(es == Acad::eOk);

  return es;
}


Acad::ErrorStatus AsdkMkrObject::dxfInFields(AcDbDxfFiler* filer)
{
  assertWriteEnabled();

  Acad::ErrorStatus es = eOk;
  resbuf rb;

  if ((AcDbObject::dxfInFields(filer) != Acad::eOk) ||
      !filer->atSubclassData(_T(/*NOXLATE*/"AsdkMkrObject"))) {
    return filer->filerStatus();
  }

  while ((es == eOk) && ((es = filer->readResBuf(&rb)) == eOk)) {

    switch (rb.restype) {
    // TODO: add the cases for your entity
      case kDxfXCoord:
      default:
        filer->pushBackItem();
        es = Acad::eEndOfFile;
        break;
    } /*switch*/
  } /*while*/

  if (es != Acad::eEndOfFile)
    return eInvalidResBuf;

  // end of dxfInFields
  return es;
}


Acad::ErrorStatus AsdkMkrObject::dxfOutFields(AcDbDxfFiler* filer) const
{
  assertReadEnabled();

  Acad::ErrorStatus es;

  es = AcDbObject::dxfOutFields(filer);
  assert(es == Acad::eOk);

  // TODO: add the functions for your own entity in the following way:
  // es = filer->writeItem(AcDb::kDxfXCoord, mCenter);
  // assert(es == Acad::eOk);

  es = filer->writeItem(AcDb::kDxfSubclass, _T(/*NOXLATE*/"AsdkMkrObject"));
  assert(es == Acad::eOk);

  // end of dxfOutFields
  return es;
}
