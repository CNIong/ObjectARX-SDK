///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
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

