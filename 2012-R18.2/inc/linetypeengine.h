//
#pragma once
//
// (C) Copyright 2004-2006 by Autodesk, Inc.
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

#include "acgi.h"
#pragma pack (push, 8)

class AcGiImpLinetypeEngine;

class AcGiLinetypeEngine : public AcRxObject 
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLinetypeEngine);

    AcGiLinetypeEngine();
    virtual ~AcGiLinetypeEngine();

    // Tessellate the polyline with linetype applied, through world draw
    virtual Acad::ErrorStatus tessellate (bool                 bIsArc,
                                          bool                 bIsCircle,
                                          const Adesk::UInt32  nPoints,
                                          const AcGePoint3d  * pVertexList,
                                          AcGiWorldDraw *      pWorldDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          const AcGeVector3d * pNormal);

    // Tessellate the polyline with linetype applied, through viewport draw
    virtual Acad::ErrorStatus tessellate (bool                 bIsArc,
                                          bool                 bIsCircle,
                                          const Adesk::UInt32  nPoints,
                                          const AcGePoint3d  * pVertexList,
                                          AcGiViewportDraw *   pViewportDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          const AcGeVector3d * pNormal);

    virtual Acad::ErrorStatus tessellate (const AcGeCircArc3d& arcSeg,
                                          const AcGeMatrix3d&  ecsMat,
                                          double               startWidth,
                                          double               endWidth,
                                          AcGiCommonDraw *     pDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          double               thick);

    virtual Acad::ErrorStatus tessellate (const AcGeLineSeg3d& lineSeg,
                                          const AcGeMatrix3d&  ecsMat,
                                          double               startWidth,
                                          double               endWidth,
                                          AcGiCommonDraw *     pDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale);

private:
    AcGiImpLinetypeEngine * mpAcGiImpLinetypeEngine;
};

#pragma pack (pop)
