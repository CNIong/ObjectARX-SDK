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
// Abstract base callback classes. Applications derive their own concrete 
// callback classes from these abstract classes. Callbacks are used by:
//
// - Body::hideDisplay() method     ... class OutputPolylineCallback 
//
// - Body::triangulate()
//   Face::triangulate() methods    ... class OutputTriangleCallback
//
// - Body::save()
//   Body::restore()     methods    ... class SaveRestoreCallback
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_CALLBACK_H
#define AMODELER_INC_CALLBACK_H


#include "global.h"
#include "color.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp OutputPolylineCallback
//
// Abstract base callback class used by Body::hideDisplay(). See source file
// "dxfout.cpp" for the implementation of a sample callback class which will 
// be saved to a DXF file.
//
{
public:

    virtual ~OutputPolylineCallback() {}
    
    // edgeArray [] ... Edges which correspond to the segments of the output 
    //                  polyline. In can be used to maintain the associativity
    //                  between the drawing and the original edges, or just
    //                  to obtain the color of the segments of the polyline.
    //
    // pointArray[] ... Points of the output polyline. The points are in the 
    //                  coordinate space of the body vertices projected by the 
    //                  projection transformation which is given as an input
    //                  argument to the Body::hideDisplay() method.
    //
    // bulgeArray[] ... Bulge array. It may contain values different from 0
    //                  only for the Body::kArcReconstructDrawingImprove
    //                  option.
    //
    // numPoints    ... Number of elelemts in edgeArray[], pointArray[] and 
    //                  bulgeArray[].
    //
    // isClosed     ... The polyline is closed.
    //
    // isVisible    ... True==visible line, false==hidden line segment.
    //
    virtual void outputPolyline(Edge*          edgeArray [],
                                const Point3d  pointArray[],
                                const double   bulgeArray[],
                                int            numPoints,
                                bool           isClosed,
                                bool           isVisible) = NULL;

    // This callback method may be called only if Body::HiddenLineDrawingImprove 
    // is Body::kArcReconstructDrawingImprove. startAngle == endAngle == 0 
    // indicates a full circle. The edge argument is one edge on the arc/circle.
    // 
    virtual void outputArc     (Edge*          edge,
                                const Point3d& center,
                                double         radius,
                                double         startAngle,
                                double         endAngle,
                                bool           isVisible) = NULL;

}; // class OutputPolylineCallback



class DllImpExp OutputTriangleCallback
//
// Abstract base callback class used by Body::triangulate() and 
// Face::triangluate() methods. See source file "dxfout.cpp" for the 
// implementation of a sample callback class which will be saved to 
// a DXF file.
//
{
public:

    virtual ~OutputTriangleCallback() {}

    // The coordinates of the triangle/quadrilateral vertices are obtained by 
    // accessing the vertices referenced by the edges. For example:
    //
    //   const Point3d p0 = edgeArray[0]->point();  
    //   const Point3d p1 = edgeArray[1]->point();  
    //   const Point3d p2 = edgeArray[2]->point();  
    //   const Point3d p3 = edgeArray[3]->point();
    //
    // To find out whether the triangle/quadrilateral side between vertices 
    // edgeArray[i]->vertex() and edgeArray[(i+1)%numSides]->vertex() 
    // corresponds to a real edge in the body, to a bridge edge in the body
    // or is just a triangulation edge, use the following code:
    //
    //   if (edgeArray[i]->next()->vertex() == edgeArray[(i+1)%numSides]->vertex()
    //   {
    //       if (!edgeArray[i]->isBridge())
    //       {
    //            // The triangle side is a real edge in the body. We usually
    //            // want to make them visible.
    //       }
    //       else 
    //       {
    //           // The triangle side is a bridge edge in the body. We usually 
    //           // want to make them not visible.
    //       }
    //   }
    //   else
    //   {
    //       // The triangle side does not correspond to any real edge in the
    //       // body. We usually want to make them not visible.
    //   }
    //
    virtual void outputTriangle(Edge* edgeArray[], int arrayLength) = NULL;

    enum { kMaxTriStripLength = 200 };

    // The outputTriStrip() callback is called only if the TriangulationType
    // is kGenerateTriStrips or kGenerateTriStripsPerSurface. 
    // The arrayLength <= kMaxTriStripLength, the tristrip contains arrayLength
    // vertices and arrayLength-2 triangles. 
    //
    // The firstTriangleIsCcw indicates whether the first triangle in the 
    // tristrip is CCW or CW oriented, i.e. whether the three points: 
    //    edgeArray[0]->point()
    //    edgeArray[1]->point()
    //    edgeArray[2]->point()
    // define a CCW or CW oriented triangle. 
    //
    // The CCW/CW orientation of the following triangles in the tristrip 
    // then alternates. E.g., if firstTriangleIsCcw, and we want to output the
    // second triangle as CCW, the order of the three points will be:
    //    edgeArray[2]->point()
    //    edgeArray[1]->point() 
    //    edgeArray[3]->point() 
    //
    virtual void outputTriStrip(Edge* edgeArray[], 
                                int   arrayLength,
                                bool  firstTriangleIsCcw) = NULL;

}; // class OutputTriangleCallback



class DllImpExp SaveRestoreCallback
//
// Abstract base callback class used by Body::save() and Body::restore() 
// methods. 
//
{
public:

    virtual ~SaveRestoreCallback() {}

    virtual void saveBytes   (const void* buffer, int requiredLength) = NULL;
    virtual void restoreBytes(void*       buffer, int requiredLength) = NULL;

}; // class SaveRestoreCallback



class DllImpExp TopologyChangeCallback
//
// Abstract base callback class which the client code can use to obtain
// information about which topological entities were created, deleted, split 
// and merged during a particular modeling operation
//
{
public:

    virtual ~TopologyChangeCallback() {}

    virtual void entityCreated(Entity*)                              = NULL;
    virtual void entityDeleted(Entity*)                              = NULL;
    virtual void entitySplit  (Entity* pOrig,      Entity* pNew)     = NULL;
    virtual void entityMerged (Entity* pSurviving, Entity* pDeleted) = NULL;


}; // class TopologyChangeCallback



class DllImpExp SaveToSatCallback
//
// Basic callback for saving the AModeler body in the ACIS SAT file format.
// It does not mimic the fileio\satfile.hxx SatFile protocol because is is
// currently not needed. We may define the full ACIS protocol if needed
//
{
public:

    virtual ~SaveToSatCallback() {}

    virtual void saveIndex  (int)         = NULL; // Entity index
    virtual void saveIdent  (const char*) = NULL;
    virtual void saveDouble (double)      = NULL;
    virtual void saveInt    (int)         = NULL;

}; // class SaveToSatCallback


AMODELER_NAMESPACE_END
#endif

