
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
/// Action that sets the contents of AcDbSweptSurface entity based on the 
/// input data of the action. With this action the swept surface will regenerate
/// if any of the original input data is changed. 
/// </summary>
///
class ACDB_PORT AcDbAssocSweptSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocSweptSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocSweptSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Set scale factor of the resulting swept surface (correspondent to scale factor in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocParamBasedActionBody by calling method 
    /// setValueParam with name "kScaleFactorParamName". 
    /// </para></summary>
    /// <param name="scale">  New value of scale factor. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setScaleFactor(double scale, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get scale factor of the resulting swept surface (correspondent to scale factor in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocParamBasedActionBody by calling method 
    /// getValueParam with name "kScaleFactorParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Scale factor. </returns>
    ///
    double scaleFactor(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set align angle of the resulting swept surface (correspondent to align angle in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocParamBasedActionBody by calling method 
    /// setValueParam with name "kRotationAngleParamName". 
    /// </para></summary>
    /// <param name="angle">  New value of align angle. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setAlignAngle(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get align angle of the resulting swept surface (correspondent to align angle in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocParamBasedActionBody by calling method 
    /// setValueParam with name "kRotationAngleParamName". 
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Align angle. </returns>
    ///
    double alignAngle(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set twist angle of the resulting swept surface (correspondent to twist angle in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocParamBasedActionBody by calling method 
    /// setValueParam with name "kTwistAngleParamName". 
    /// </para></summary>
    /// <param name="angle">  New value of twist angle. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setTwistAngle(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get twist angle of the resulting swept surface (correspondent to twist angle in AcDbSweepOptions)
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocParamBasedActionBody by calling method 
    /// getValueParam with name "kTwistAngleParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Twist angle. </returns>
    ///
    double twistAngle(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Create an instance of AcDbAssocSweptSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Object id of the resulting swept surface. </param>
    /// <param name="sweepProfile">  Input profile that is to be swept to create the resulting surface. </param>
    /// <param name="sweepPathProfile">  Input sweep path profile that is to be swept along to create the resulting surface. </param>
    /// <param name="sweptOptions">  Input sweep option to create resulting surface. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& sweepProfile,
                                             const AcDbPathRef& sweepPathProfile,
                                             const AcDbSweepOptions& sweptOptions,
                                             bool  bEnabled,
                                             AcDbObjectId& createdActionId);
}; // class AcDbAssocSweptSurfaceActionBody

#pragma pack (pop)
