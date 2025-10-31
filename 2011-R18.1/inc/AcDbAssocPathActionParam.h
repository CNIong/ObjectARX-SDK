
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2009-2010 by Autodesk, Inc. 
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
#include "AcDbAssocCompoundActionParam.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps a sequence of edges. It is an 
/// AcDbAssocCompoundActionParam that owns AcDbAssocEdgeActionParams that represent 
/// the individual segments of the path.
/// </summary>
///
class ACDB_PORT AcDbAssocPathActionParam : public AcDbAssocCompoundActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocPathActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocPathActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary>
    /// Sets the AcDbAssocPathActionParam from a sequence of AcDbEdgeRefs.
    /// </summary>
    /// <param name="edgeRefs">  
    /// Array of references to "edge" subentities. See AcDbEdgeRef and 
    /// AcDbAssocEdgeActionParam for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setEdgeRefArray(const AcArray<AcDbEdgeRef>& edgeRefs);

    /// <summary>
    /// Changes a single segment in the AcDbAssocPathActionParam.
    /// </summary>
    /// <param name="edgeRefIndex"> Index of the segment to change. </param> 
    /// <param name="edgeRef">  
    /// Reference to an "edge" subentity. See AcDbEdgeRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus updateEdgeRef(int edgeRefIndex, const AcDbEdgeRef& edgeRef);

    /// <summary><para>
    /// Returns an array of references to transient subentities of AcDbEntities 
    /// that correspond to persistent subentities that this AcDbAssocPathActionParam 
    /// references. It can also be references to the whole AcDbEntities or to 
    /// constant AcGeCurve3d geometries. See AcDbEdgeRef for details.
    /// </para><para>
    /// When an edge (such as of an AcDbSurface or AcDb3dSolid) is referenced 
    /// by this AcDbAssocPathActionParam and some parameters of the solid/surface 
    /// are changed and the solid/surface is re-evaluated from its actions, this 
    /// edge may then correspond to any number of edges, because the original 
    /// edge might have gotten split, merged, or even may have disappeared. That 
    /// is why the output is an array of arrays of EdgeRefs, but in typical case 
    /// the array will contain arrays with just a single element.
    /// </para></summary>
    /// <param name="edgeRefs"> 
    /// Array of arrays of references to transient subentities of AcDbEntities 
    /// that correspond to the persistent subentities that this path action 
    /// parameter references. It can also be references to the whole AcDbEntities 
    /// or to constant AcGeCurve3d geometries. See AcDbEdgeRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeRefArray(AcArray<AcArray<AcDbEdgeRef> >& edgeRefs) const;
};

#pragma pack (pop)
