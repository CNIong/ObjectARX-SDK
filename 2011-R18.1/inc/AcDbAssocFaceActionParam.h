
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
#include "AcDbAssocActionParam.h"
#include "AcDbGeomRef.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps reference to a face. It uses AcDbAssocGeomDependency 
/// to define a persistent reference to a face subentity of an AcDbEntity. Alternatively,
/// it may directly keep the face geometry in the action parameter in the form 
/// of an ASM body, instead of referencing some other AcDbEntity.
/// </summary>
///
class ACDB_PORT AcDbAssocFaceActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocFaceActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocFaceActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para>
    /// The input AcDbFaceRef is a non-persistent reference to a face geometry, 
    /// the AcDbAssocEdgeActionParam will make a persistent reference to that face. 
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced face subentity.  If it is constant geometry 
    /// in the form of a face of an ASM body, no dependency is created.
    /// </para></summary>
    /// <param name="faceRef"> 
    /// Reference to a "face" subentity of an entity, or constant geometry in the 
    /// form of a face of an ASM body. See AcDbFaceRef for details.
    /// </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setFaceRef(const AcDbFaceRef& faceRef, bool isReadDependency = true, bool isWriteDependency = false);

    /// <summary> <para>
    /// Returns references to the transient subentities of an AcDbEntity, that 
    /// correspond to the persistent subentity that this face action parameter 
    /// references. It can also be a constant geometry in the form of a face of
    /// an ASM body. See AcDbFaceRef for details.
    /// </para><para>
    /// When a single face (such as face of a solid or surface) is referenced by 
    /// this AcDbAssocFaceActionParam and some parameters of the solid/surface 
    /// are changed and the solid/surface is re-evaluated from its actions, this 
    /// single face may then correspond to any number of faces, because the original 
    /// face might have gotten split, merged, or even may have disappeared. That 
    /// is why the output is an array of FaceRefs, but in typical case the array 
    /// will contain just a single element.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced face subentity.
    /// </para></summary>
    /// <param name="faceRefs"> 
    /// References to the transient subentities of an AcDbEntity, that correspond 
    /// to the persistent subentity that this face action parameter references. 
    /// See AcDbFaceRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getFaceRef(AcArray<AcDbFaceRef>& faceRefs) const;

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocGeomDependency, 
    /// it returns AcDbCompoundObjectId of the entity this dependency depends on.
    /// </summary>
    /// <param name="compoundId"> 
    /// The AcDbCompoundObjectId of the entity this action parameter depends on,
    /// or an empty compound object id if the action parameter does not depend
    /// on any entity.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentOnCompoundObject(AcDbCompoundObjectId& compoundId) const;
};

#pragma pack (pop)

