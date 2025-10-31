
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
// CREATED BY: Pei Zhan                                 July 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbGeomRef.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps reference to a vertex subentity of an AcDbEntity,
/// or directly keeps AcGePoint3d geometry.
/// </summary>
///
class ACDB_PORT AcDbAssocVertexActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocVertexActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocVertexActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para>
    /// The input AcDbVertexRef is a non-persistent reference to a vertex geometry,
    /// the AcDbAssocVertexActionParam will make a persistent reference to that vertex. 
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced vertex subentity. In case the whole AcDbPoint 
    /// entity is referenced, not a subentity of an AcDbEntity, an AcDbAssocDependency 
    /// is used. If it is constant geometry in the form of an AcGePoint3d, no 
    /// dependency is created.
    /// </para></summary>
    /// <param name="vertexRef"> 
    /// Reference to an "vertex" subentity of an entity, to a AcDbPoint entity, 
    /// or to an AcGePoint3d constant geometry. See AcDbVertexRef for details.
    /// </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setVertexRef(const AcDbVertexRef &vertexRef, bool isReadDep, bool isWriteDep);

    /// <summary> <para>
    /// Returns references to the transient subentities of an AcDbEntity, that 
    /// correspond to the persistent subentity that this vertex action parameter 
    /// references. It can also be reference to the whole AcDbPoint entity  or to 
    /// constant AcGePoint3d geometry. See AcDbVertexRef for details.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced vertex subentity. In case the whole AcDbPoint 
    /// entity is referenced, not a subentity of an AcDbEntity, an AcDbAssocDependency 
    /// is used. If it is constant geometry in the form of an AcGePoint3d, no 
    /// dependency is created.
    /// </para></summary>
    /// <param name="vertexRef"> 
    /// References to the transient subentities of an AcDbEntity, that correspond 
    /// to the persistent subentity that this vertex action parameter references. 
    /// It can also be reference to the whole AcDbPoint or to constant AcGePoint3d 
    /// geometry. See AcDbVertexRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getVertexRef ( AcDbVertexRef &vertexRef ) const;

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocDependency
    /// or AcDbAssocGeomDependency, it returns AcDbCompoundObjectId of the entity 
    /// this dependency depends on.
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
