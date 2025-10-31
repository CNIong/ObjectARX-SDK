#ifndef GEOMENT_DBBODY_H
#define GEOMENT_DBBODY_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc. 
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
// DESCRIPTION:
// The AcDbBody class is the interface class for representing
// general ACIS bodies inside AutoCAD.  All the functionality
// supported through this class is implemented in the class
// AcDbImpBody and its base classes.

#include "dbmain.h"
#include "dbsubeid.h"

#pragma pack (push, 8)

class AcDbBody: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBody);
             AcDbBody();
    virtual ~AcDbBody();

    virtual Adesk::Boolean    isNull       () const;

    virtual void*             body         () const;                   // INTERNAL USE ONLY
    virtual Acad::ErrorStatus setBody      (const void* modelerBody);  // INTERNAL USE ONLY

    virtual AcDbSubentId    internalSubentId (void*) const;                   // INTERNAL USE ONLY
    virtual void*           internalSubentPtr(const AcDbSubentId& id) const;  // INTERNAL USE ONLY

    static  Acad::ErrorStatus acisOut      (const ACHAR* fileName,
                                            const AcDbVoidPtrArray&);
    static  Acad::ErrorStatus acisIn       (const ACHAR* fileName,
                                            AcDbVoidPtrArray&);
 
    virtual Adesk::UInt32 numChanges() const;

    void invalidateCachedBodySubentIds(); // INTERNAL USE ONLY
};

#pragma pack (pop)

#endif
