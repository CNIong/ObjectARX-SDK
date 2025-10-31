///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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
// DESCRIPTION:
//
// Function:
//
//   void dxfPolylineToAugmentedPolygon()
//
// Reads the first 2D polyline from a given DXF file and creates an
// augmented polygon from the polyline data read (see the "vertdata.h"  
// file for the description of an augmented polygon). The polygon can 
// then be swept to produce a solid body.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_DXFINPLN_H
#define AMODELER_INC_DXFINPLN_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


DllImpExp void dxfPolylineToAugmentedPolygon(FILE*                pInputDxfFile,
                                             int                  approx,
                                             Point3d*&            plg,
                                             PolygonVertexData**& vertexData,
                                             int&                 numVertices,
                                             Vector3d&            plgNormal);

AMODELER_NAMESPACE_END
#endif

