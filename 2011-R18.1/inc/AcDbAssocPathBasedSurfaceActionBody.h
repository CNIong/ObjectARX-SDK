
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2007-2010 by Autodesk, Inc. 
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
// CREATED BY: Jiri Kripac                                 March 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbAssocSurfaceActionBody.h"
#include "AcDbAssocVertexActionParam.h"
#pragma pack (push, 8)


/// <summary>
/// Base action body class for surface creation actions that take as input one 
/// or more paths. It just provides utility methods to get/set the 
/// AcDbAssocPathActionParams.
/// </summary>
///
class ACDB_PORT AcDbAssocPathBasedSurfaceActionBody : public AcDbAssocSurfaceActionBody
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocPathBasedSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocPathBasedSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Removes all AcDbAssocPathActionParams. </summary>
    ///
    Acad::ErrorStatus removeAllPathParams();

    /// <summary> Gets all AcDbAssocPathActionParams. </summary>
    ///
    Acad::ErrorStatus getInputPathParams(AcDbObjectIdArray& pathParamIds) const;

    /// <summary> 
    /// Gets the current geometry of all input paths. The outermost array is for
    /// every path, the second array is for the segments of each path, and the 
    /// inner-most array is for each segment of each path. Because the referenced
    /// entity might have changed, a single original edge in the original entity
    /// may generally correspond to any number of edges in the current entity, or 
    /// to no edge at all (though, it most cases it will be just a single edge).
    /// </summary>
    ///
    Acad::ErrorStatus getInputPaths(AcArray<AcArray<AcArray<AcDbEdgeRef> > >&) const;

    /// <summary> 
    /// Sets all input paths. Each path is specified by an array of AcDbEdgeRefs.
    /// </summary>
    ///
    Acad::ErrorStatus setInputPaths(const AcArray<AcArray<AcDbEdgeRef> >&);

    /// <summary> Sets all input paths. </summary>
    ///
    Acad::ErrorStatus setInputPaths(const AcArray<AcDbPathRef>&);

    /// <summary> 
    /// Changes the single input path specified by its pathIndex. The path with
    /// the given index must already exist.
    /// </summary>
    ///
    Acad::ErrorStatus updateInputPath(int pathIndex, const AcDbPathRef&);

    /// <summary> Removes all AcDbAssocVertexActionParams. </summary>
    ///
    Acad::ErrorStatus removeAllVertexParams();

    /// <summary> Gets all AcDbAssocVertexActionParams. </summary>
    ///
    Acad::ErrorStatus getInputVertexParams(AcDbObjectIdArray& vertexParamIds) const;

    /// <summary> 
    /// Sets all input points. Points can sometimes be used instead of profile
    /// paths.
    /// </summary>
    ///
    Acad::ErrorStatus setInputPoints(const AcArray<AcDbVertexRef>&);

    /// <summary> Gets all input points. </summary>
    ///
    Acad::ErrorStatus getInputPoints(AcArray<AcDbVertexRef>&) const;

    /// <summary>
    /// This method is to simplify the user selection of the underlying path 
    /// geometry that is the input for the action. The resulting surface usually 
    /// overlaps the input path geometry and it would be difficult for the user 
    /// to select the geometry that is the input to the action. Calling this method 
    /// makes the resutling surface be drawn under the input paths so that 
    /// the input paths are easier to select by the user.
    /// </summary>
    ///
    Acad::ErrorStatus makeInputPathsDrawOnTopOfResultingSurface() const;

}; // class AcDbAssocPathBasedSurfaceActionBody

#pragma pack (pop)

