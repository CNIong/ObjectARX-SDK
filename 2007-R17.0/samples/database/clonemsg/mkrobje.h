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
//  mkrobje.h

#include "dbmain.h"
#include "geassign.h"
#include "gegbl.h"
#include "gegblabb.h"
#include "dbmain.h"           // object

// definition of your own object AsdkMkrObject

class AsdkMkrObject : public AcDbObject
{
public:
  ACRX_DECLARE_MEMBERS(AsdkMkrObject);

  /////////////////////////////////////////////////////////
  // Methods specific to AsdkMkrObject
  /////////////////////////////////////////////////////////
  // TODO: add your specific methods for this new class


  /////////////////////////////////////////////////////////
  // Overridden methods from AcDbObject
  /////////////////////////////////////////////////////////

  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

private:
  // TODO: add your specific membervariables


};
