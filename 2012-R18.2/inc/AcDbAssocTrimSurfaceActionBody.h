
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
#include "AcDbSurfaceTrimInfo.h"
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)


/// <summary>
/// Action that used to record a surface trimming operation, so it can be used to retrim
/// the surface when blank/tool are changed.
/// The trim action can be associative or semi-associative(permanent): when it is associative, 
/// the trimmed area will update when the tools/blank are changed by using the modified tools/blank 
/// to re-calculate the trimmed area. 
/// If it is semi-associative(permanent), the trimmed area will stay unchanged even if the tools/blank 
/// are modified because it will remember the geometry of the tools when they were first used and
/// always use it to trim the blank
/// </summary>
///
class ACDB_PORT AcDbAssocTrimSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocTrimSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocTrimSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Set trim info about how tools are used to trim the blank
    /// </summary>
    /// <param name="trimInfoArray">  A of trim info, each element in the array represent information of one tool. </param>
    /// <param name="bAutoExtend">  If the tools should be extended to trim the blank, if they are simple, analytic geometry </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setTrimInfo(const AcArray<AcDbSurfaceTrimInfo> trimInfoArray, bool bAutoExtend);

    /// <summary> 
    /// Make the trim action semi-associative(permanent), so the trimmed area will stay unchanged if tools are modified
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///   
    Acad::ErrorStatus makeTrimPermanent();

    /// <summary> 
    /// Undo the trimmed area generated in this action to go back to untrimmed condition
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///   
    Acad::ErrorStatus untrim();

    /// <summary> 
    /// Get trimmed area generated in this action
    /// </summary>
    /// <returns> Trimmed area. </returns>
    ///
    double getTrimmedArea() const;

    /// <summary> 
    /// Create an instance of AcDbAssocTrimSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Object id resulting blank surface that is to be trimmed. </param>
    /// <param name="trimInfo">  Array of trim info that specify the tool information. </param>
    /// <param name="bAutoExtend"> Option about if the tools should be extended to trim the blank, if they are simple, analytic geometry . </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <param name="bEnabled">  If the action will be fully associative. when it is associative, the trimmed area will update when
    /// the tools/blank are changed by using the modified tools/blank to re-calculate the trimmed area. 
    /// if it is semi-associative(permanent), the trimmed area will stay unchanged even if the tools/blank 
    /// are modified because it will remember the geometry of the tools when they were were first used and
    /// always use it to trim the blank </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId,
                                             const AcArray<AcDbSurfaceTrimInfo>& trimInfo,
                                             bool bAutoExtend, 
                                             bool bEnabled,
                                             AcDbObjectIdArray& createdActionIds);

}; // class AcDbAssocTrimSurfaceActionBody

#pragma pack (pop)
