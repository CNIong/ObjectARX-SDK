#ifndef _ACGIUTIL_H
#define _ACGIUTIL_H 1
//
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
//

#include "dbid.h"
#include "AdAChar.h"
#include "acgi.h"

#pragma pack (push, 8)

Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&,
                              const AcDbObjectId& AcDbStyleId);
Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName);

// This version of toAcDbTextStyle will use the styleName of the
// AcGiTextStyle as the name of the AcDbTextStyle to write to.  If
// the AcGiTextStyle's styleName == NULL, then a random name will
// be generated and used for the AcDbTextStyle and the AcGiTextStyle's
// styleName will be set to the random name as well.
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&);

// This version of toAcDbTextStyle will use the styleName of the
// AcGiTextStyle as the name of the AcDbTextStyle to write to.  If
// the AcGiTextStyle's styleName == NULL, then a random name will
// be generated and used for the AcDbTextStyle and the AcGiTextStyle's
// styleName will be set to the random name as well.
//
// AcDbStyleId is set to the objectId of the AcDbTextStyleTableRecord
// object that maps to the AcGiTextStyle's name.
//
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&,
                                  AcDbObjectId& AcDbStyleId);

// Agruments reversed to avoid ambiguious function overloading. In
// this version,  the AcDbObjectId is the Id of the AcDbTextStyleTableRecord
// to write.
//
Acad::ErrorStatus toAcDbTextStyle(const AcDbObjectId AcDbStyleId,
                                  AcGiTextStyle&);

Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName);

// AcDbStyleId is set to the objectId of the AcDbTextStyleTableRecord
// object that maps to the AcGiTextStyle's name.
//
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName,
                                  AcDbObjectId& AcDbStyleId);


#pragma pack (pop)

#endif // ACGIUTIL_H
