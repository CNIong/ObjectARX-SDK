//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2010-2011 by Autodesk, Inc.  
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
// CREATED BY: Mei Jiayin                            March 2010
//
// DESCRIPTION: 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcDbAssocArrayParameters.h"
#include "acdbassocparambasedactionbody.h"

/// <summary>
/// AcDbAssocArrayCommonParameters class provides interface to manipulate array 
/// parameters that are common to Rectangular, Path and Polar Array. 
/// Its derived classes implement logic for providing array item
/// transforms as well as grip manipulation. 
/// </summary>
///
class ACDB_PORT AcDbAssocArrayCommonParameters : public AcDbAssocArrayParameters
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayCommonParameters);

    /// <summary> Default destructor.</summary>
    ///
    virtual ~AcDbAssocArrayCommonParameters(void);

    /// <summary> 
    /// Gets the level count of the array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns level count. </returns>
    ///
    int levelCount(AcString& expression = AcString(), AcString& evaluatorId = AcString()) const;

    /// <summary> 
    /// Gets the level spacing of the array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns level spacing. </returns>
    ///
    double levelSpacing(AcString& expression = AcString(), AcString& evaluatorId = AcString()) const;

    /// <summary> 
    /// Gets the row count of the array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns row count. </returns>
    ///
    int rowCount(AcString& expression = AcString(), AcString& evaluatorId = AcString()) const;
    
    /// <summary> 
    /// Gets the row elevation of the array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns row elevation. </returns>
    ///
    double rowElevation(AcString& expression = AcString(), AcString& evaluatorId = AcString()) const;
    
    /// <summary> 
    /// Gets the row spacing of the array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns row spacing. </returns>
    ///
    double rowSpacing(AcString& expression = AcString(), AcString& evaluatorId = AcString()) const;

    /// <summary> 
    /// Sets the level count of the array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="nLevels">      The level count to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setLevelCount(int nLevels, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());
    
    /// <summary> 
    /// Sets the level spacing of the array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="offset">       The level spacing to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setLevelSpacing(double offset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the row count of the array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="nRows">        The row count to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRowCount(int nRows, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the row elevation of the array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="elevation">    The row elevation to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRowElevation(double elevation, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the row spacing of the array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="offset">       The row spacing to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRowSpacing(double offset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary>
    /// Obtains array base plane geometry definition if there was any base
    /// plane information was set to the parameters. Base plane can be defined
    /// using normal vector or an AcDbFaceRef and base point vertex ref.
    /// </summary>
    /// <param name="basePoint">  The returned base point, default is origin. 
    /// </param>
    /// <param name="normal">  The returned normal to the base plane at the 
    /// base point. The default value is Z-Axis. </param>
    /// <param name="pFace">  The returned base plane geometry, if NULL is 
    /// passed it won't return the face ref. If base plane was not set it
    /// will return empty face ref. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus getBasePlane(AcDbVertexRef& basePoint, 
        AcGeVector3d& normal, AcDbFaceRef* pFace = NULL) const;

    /// <summary>
    /// Sets array base plane geometry definition. Base plane is surface or
    /// plane information on which array is laid out.
    /// </summary>
    /// <param name="basePoint">  The input base point geometry. </param>
    /// <param name="normal">  The input normal to define the base plane.
    /// This parameter is ignored if pFace is provided. </param>
    /// <param name="pFace">  The input base plane geometry. If NULL is 
    /// passed the base plane is defined based on input normal. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus setBasePlane(const AcDbVertexRef& basePoint, 
        const AcGeVector3d& normal, const AcDbFaceRef* pFace = NULL);

    /// <summary>
    /// Obtains canonical form of given item locator. The given locator may be
    /// counted wrt start or end, but the returned canonical form is always
    /// counted from start of the array pattern.
    /// </summary>
    /// <param name="locator">  The input item locator or spatial index. </param>
    /// <returns> Canonical form of input locator. </returns>
    ///
    virtual AcDbItemLocator getCanonicalForm(const AcDbItemLocator& locator) const;

protected:
    friend class AcDbImpAssocArrayCommonParameters;
    explicit AcDbAssocArrayCommonParameters(AcDbImpAssocArrayCommonParameters* pSelf);
};
