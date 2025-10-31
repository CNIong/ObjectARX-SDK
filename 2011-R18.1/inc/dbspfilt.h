#ifndef AD_DBSPFILT_H
#define AD_DBSPFILT_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// DESCRIPTION: Source file for the AcDbSpatialFilter class.
//
#include "dbfilter.h"
#include "gepnt2d.h"
#include "gevec2d.h"
#include "gept2dar.h"

#pragma pack (push, 8)

// Applies to both front and back clip
//
#define ACDB_INFINITE_XCLIP_DEPTH (1.0e+300)

class AcDbExtents;

class AcDbSpatialFilter: public  AcDbFilter
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSpatialFilter);

	     AcDbSpatialFilter();
    virtual ~AcDbSpatialFilter();

    virtual AcRxClass* indexClass() const;   


    // To Be Obsoleted...
    virtual void queryBounds(AcDbExtents& ext, 
                             const AcDbBlockReference * pRefBlkRef) const;

 

    AcDbSpatialFilter(const AcGePoint2dArray& pts, 
                      const AcGeVector3d&     normal,
                      double                  elevation,
                      double                  frontClip,
                      double                  backClip,
                      Adesk::Boolean          enabled);

    void queryBounds(AcDbExtents& ext) const;

    Acad::ErrorStatus  getVolume(AcGePoint3d&  fromPt, 
                                 AcGePoint3d&  toPt, 
                                 AcGeVector3d& upDir,
                                 AcGeVector2d& viewField) const;


    Acad::ErrorStatus setDefinition(const AcGePoint2dArray& pts, 
                                    const AcGeVector3d&     normal,
                                    double                  elevation,
                                    double                  frontClip,
                                    double                  backClip,
                                    Adesk::Boolean          enabled);                                    

    Acad::ErrorStatus getDefinition(AcGePoint2dArray& pts, 
                                    AcGeVector3d&     normal,
                                    double&           elevation,
                                    double&           frontClip,
                                    double&           backClip,
                                    Adesk::Boolean&   enabled) const;   

    AcGeMatrix3d& getClipSpaceToWCSMatrix(AcGeMatrix3d& mat) const;
    AcGeMatrix3d& getOriginalInverseBlockXform(AcGeMatrix3d& mat) const;

    // New functions to support large dwg project.
    //
    Acad::ErrorStatus setPerspectiveCamera(const AcGePoint3d& fromPt);
 
    Adesk::Boolean    clipVolumeIntersectsExtents(const AcDbExtents& ext) const;

    Adesk::Boolean    hasPerspectiveCamera() const;
};

#pragma pack (pop)

#endif // AD_DBSPFILT_H
