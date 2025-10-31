
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2009-2010 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rihts notice below appear in all supporting 
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
// CREATED BY: Pei Zhan                                 June 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

/// <summary>
/// Action that sets the contents of AcDbPlaneSurface entity based on the 
/// input data of the action. With this action, when the input edges that was used to create
/// a plane surface are changed, the plane surface will regenerated
/// </summary>
///

class ACDB_PORT AcDbAssocPlaneSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocPlaneSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocPlaneSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Create an instance of AcDbAssocPlaneSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Resulting plane surface id. </param>
    /// <param name="inputPath">  Input closed edges that used to create the plane surface. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& inputPath,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocPlaneSurfaceActionBody

#pragma pack (pop)
