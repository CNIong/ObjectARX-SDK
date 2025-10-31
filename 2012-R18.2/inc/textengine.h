//
#ifndef _TEXTENGINE_H
#define _TEXTENGINE_H 1
//
// (C) Copyright 1994-2007 by Autodesk, Inc. 
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
// This is the Graphics Interface for view independent and dependent
// elaboration of AcDb Entities.
//
// The AutoCAD Graphics Interface (AcGi) is a set of objects comprising 
// an API for elaborating the graphics representation of new AutoCAD
// entitites.  These objects support many geometric primitives, 
// transformation matrix querying, and graphical attributes. 

#include "acgi.h"
#include "AdAChar.h"
#include "Adesk.h"

#pragma pack (push, 8)

typedef void (*PolylineCallback) (int, int const *, AcGePoint3d const *, void *);
typedef void (*UnicodeCallback) (Adesk::LongPtr, wchar_t const *, int, void *);

class AcGiTextEngine {

public:
    static   AcGiTextEngine * create();
    virtual ~AcGiTextEngine() { ; }


    // Returns the extents of the text string in unit coordinates.
    virtual void getExtents (AcGiTextStyle &    ts, 
                             ACHAR const *      pStr,
                             int                nLength,
                             bool               bPenUp,
                             bool               bRaw,
                             AcGePoint2d &      extents) = 0;


    // Tessellates the shape text and sends the tessellated vectors as a
    // single poly polyline call for the entire text string. Again, this
    // is in unit coordinates. The code to tessellate truetype text needs
    // to be added to this routine sometime in the future.
    virtual void tessellate (AcGiTextStyle &    ts,
                             ACHAR const *      pStr,
                             int                nLength,
                             bool               bRaw,
                             double             deviation,
                             void *             pVoid,
                             PolylineCallback   pPolylineCallback) = 0;

    // Processes any control codes that are embedded in the passed in
    // string (give examples?). The converted unicode is passed back
    // through a unicode callback function. In addition, any
    // overscores/underscores that might result from the processing of
    // control codes will be drawn through the polyline callback. The
    // vectors representing the overlines and underlines will be in unit
    // coordinates as well. Currently, this is implemented for truetype
    // text only. Needs to be updated for shape text as well.
    virtual void tessellate (AcGiTextStyle &    ts,
                             ACHAR const *      pString,
                             int                nLength,
                             bool               bRaw,
                             void *             pVoid,
                             UnicodeCallback    pUnicodeCallback,
                             PolylineCallback   pPolylineCallback) = 0;


};

#pragma pack (pop)
#endif // not _TEXTENGINE_H
