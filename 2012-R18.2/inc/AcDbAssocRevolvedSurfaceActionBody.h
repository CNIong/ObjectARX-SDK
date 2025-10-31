
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
// CREATED BY: Pei Zhan                                 May 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)


/// <summary>
/// Action that sets the contents of AcDbRevolvedSurface entity based on the 
/// input data of the action. With this action, if the original input data is 
/// changed, the revolved surface will regenerate. 
/// </summary>
///
class ACDB_PORT AcDbAssocRevolvedSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocRevolvedSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocRevolvedSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Set revolve angle of the resulting revolved surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocParamBasedActionBody by calling method 
    /// setValueParam with name "kRevolveAngleParamName". 
    /// </para></summary>
    /// <param name="angle">  New value of the revolve angle. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRevolveAngle(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get revolve angle of the resulting revolved surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocParamBasedActionBody by calling method 
    /// getValueParam with name "kRevolveAngleParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Revolve angle. </returns>
    ///
    double revolveAngle(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Create an instance of AcDbAssocRevolvedSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Object id of resulting revolved surface. </param>
    /// <param name="revolvePath">  Input profile that is to be revolved to create the resulting surface. </param>
    /// <param name="axisPath">  Input profile that is to be revolved around to create the resulting surface, if the axis is not an entity but a vector, pass AcDbPathRef(NULL). </param>
    /// <param name="dAngle">  Revolve angle that used to create the resulting revolved surface. </param>
    /// <param name="dStartAngle">  Start angle that used to create the resulting revolved surface. </param>
    /// <param name="revolveOptions">  Revolve option that used to create the resulting revolved surface. </param>
    /// <param name="bFlipAxisDirection"> When a linear entity is used as axis, the vector is calculated as (endpoint - startpoint), set this option if the vector should be reversed. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& revolvePath,
                                             const AcDbPathRef& axisPath,
                                             double dAngle,
                                             double dStartAngle,
                                             const AcDbRevolveOptions& revolveOptions,
                                             bool bFlipAxisDirection,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocRevolvedSurfaceActionBody

#pragma pack (pop)
