#ifndef _ACEDSEL_H
#define _ACEDSEL_H
//
// (C) Copyright 1998-2009 by Autodesk, Inc.
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
// DESCRIPTION: Definition of Selection-related AcEd constructs, which
//              currently consists solely of the AcEdSolidSubentitySelector.
//

#include "AcArray.h"
#include "dbid.h"
#include "dbsubeid.h"
#include "acgitransient.h"
#pragma pack (push, 8)

class AcEdSelectedTransientImp;
class AcGsDCRect;

class AcEdSolidSubentitySelector
{
public:
    AcEdSolidSubentitySelector();
    ~AcEdSolidSubentitySelector();

    Acad::ErrorStatus selectFaces(AcDbObjectId& selectedSolidId, 
        AcArray<AcDbSubentId *>& faceSet);
};

class AcEdSelectedTransient
{
public:
    AcEdSelectedTransient();
    AcEdSelectedTransient(const AcEdSelectedTransient& source);
    AcEdSelectedTransient& operator=(const AcEdSelectedTransient& source);
    ~AcEdSelectedTransient();

    AcGiDrawable* parent();
    AcGiDrawable* drawable();
    Adesk::GsMarker marker();
    AcGiTransientDrawingMode mode();
    int subDrawingMode();

protected:
    AcEdSelectedTransientImp* mImp;
    friend class AcEdTransientSelectionInternals;
};

//This function returns all transients that draw any geometry inside the pickbox. 
Acad::ErrorStatus acedSelectTransients(const AcGsDCRect& rect,
                                       int viewportNumber,
                                       AcArray<AcEdSelectedTransient>& result);


#pragma pack (pop)
#endif // _ACEDSEL_H
