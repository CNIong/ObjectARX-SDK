
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2007-2009 by Autodesk, Inc. 
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
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocPersSubentIdPE AcRx protocol extension abstract base class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocSimplePersSubentId.h"
#pragma pack (push, 8)


/// <summary>
/// Information about the geometric transformation applied to geometric entities 
/// and/or their subentities. 
/// </summary>
///
struct AcDbAssocTransInfo
{
  /// <summary> The geometric transformation type. </summary>
  enum TransType
  {
    /// <summary> Translation and/or rotation. </summary>
    kGeneral = 0,

    /// <summary> Scaling and/or translation. </summary>
    kScaling,

    /// <summary> Circle radius change only. </summary>
    kRadius,

    /// <summary> Ellipse major radius change only. </summary>
    kMajorRadius,

    /// <summary> Ellipse minor radius change only. </summary>
    kMinorRadius,

    /// <summary> Radius fixed. </summary>
    kFixedRadius,

    /// <summary> Geometry fixed. </summary>
    kFixed,

    /// <summary> Geometry fixed only when possible. </summary>
    kFixWhenPossible,

    /// <summary> Not a valid transformation type. </summary>
    kNone,
  };

  /// <summary> Default constructor. </summary>
  /// 
  AcDbAssocTransInfo() : mRadius(-1.0), mTransType(kGeneral)
  {}

  /// <summary> The type of the transformation applied to the entity or sub-entity. </summary>
  ///
  TransType mTransType;

  /// <summary>
  /// The transformation matrix applied to the entity or sub-entity.
  /// It is only valid when the mTransType is NOT kRadius, kMajorRadius or kMinorRadius.
  /// It is relative to the world coordinate system.
  /// </summary>
  ///
  AcGeMatrix3d mTrans;

  /// <summary>
  /// The radius value to be applied to the entity or sub-entity.
  /// It is only valid when the mTransType is kRadius, kMajorRadius or kMinorRadius.
  /// </summary>
  ///
  double mRadius;
};


/// <summary>
/// Information about the transformation applied to a subentity of a geometric entity. 
/// </summary>
/// <remarks>
/// This enum is deprecated and should not be used.
/// </remarks>
///
struct AcDbAssocSubentTransInfo : AcDbAssocTransInfo
{
  /// <summary> The AcDbSubentId of the sub-entity that is being transformed. </summary>
  AcDbSubentId mSubentId;
};


/// <summary> Rigid set type. </summary>
enum RigidSetType
{
  /// <summary> Not a rigid set. </summary>
  kNotRigidSet = 0,

  /// <summary> A rigid set that can be uniformly scaled. </summary>
  kScalableRigidSet,

  /// <summary> A rigid set that cannot be scaled. </summary>
  kNonScalableRigidSet
};


/// <summary> <para>
/// AcRx protocol extension base class that defines protocol to obtain a persistent 
//  AcDbAssocPersSubentId from a transient AcDbSubentId. It also adds subentity 
/// query and manipulation protocol that is not available in the AcDbEntity class 
/// proper so that the client code can manipulate subentities of entities.
/// </para> <para>
/// The derived concrete classes implement this protocol for the individual
/// derived AcDbEntity classes. Only the methods that are pertinent to the 
/// particular AcDbEntity type need to be overridden.
/// </para> <para>
/// Notice that ObjectARX provides implementation of the AcDbAssocPersSubentIdPE
/// protocol extension for the common entity types such as AcDbLine, AcDbCircle,
/// AcDbArc, AcDbPolyline, AcDb2dPolyline, etc.
/// </para> </summary>
///
class ACDB_PORT AcDbAssocPersSubentIdPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocPersSubentIdPE);

    /// <summary> <para>
    /// Mapping: AcDbSubentId --> AcDbAssocPersSubentId
    /// <para> </para>
    /// Creates a new AcDbAssocPersSubentId object from a given AcDbSubentId. 
    /// The default implementation creates an AcDbSimplePersSubentId that just
    /// holds the given AcDbSubentId.
    /// </para> </summary>
    /// <param name="pEntity"> 
    /// The entity must be open for write, but usually no changes to the 
    /// entity will be made (usually no assertWriteEnabled() will be called).
    /// </param>
    /// <param name="compId"> 
    /// Contains full context path to pEntity. Can be empty for simple reference.
    /// </param>
    /// <param name="subentId"> Transient AcDbSubentId. </param>
    /// <returns> The newly created AcDbAssocPersSubentId or NULL if it cannot be created. </returns>
    ///
    virtual AcDbAssocPersSubentId* createNewPersSubent(AcDbEntity* pEntity,
                                                       const class AcDbCompoundObjectId& compId,
                                                       const AcDbSubentId& subentId)
    {
        return new AcDbAssocSimplePersSubentId(subentId);
    }

    /// <summary> <para>
    /// Mapping: AcDbAssocPersSubentId --> AcDbSubentId(s)
    /// </para> <para>
    /// Obtains all AcDbSubentIds of the provided AcDbEntity that correspond to
    /// the provided AcDbAssocPersSubentId.
    /// </para> </summary>
    /// <remarks>
    /// Notice that one AcDbAssocPersSubentId may correspond to none, one or more
    /// that one AcDbSubentId, because the entity may have changed and there may 
    /// not be just a single subentity corresponding to the original subentity 
    /// identified by the AcDbAssocPersSubentId.
    /// </remarks>
    /// <param  name="pEntity"> The entity needs to be open for read. </param>
    /// <param  name="pPerSubentId"> The persistent subentity id on the entity. </param>
    /// <param  name="subents"> The returned AcDbSubentIds. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getTransientSubentIds(const AcDbEntity*            pEntity, 
                                                    const AcDbAssocPersSubentId* pPerSubentId,
                                                    AcArray<AcDbSubentId>&       subents) const;

    /// <summary>
    /// Gets all subentities of the given type. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="subentType"> The required type of the subentities. </param>
    /// <param name="allSubentIds">  Returned AcDbSubentIds of the required type. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getAllSubentities(const AcDbEntity*      pEntity,
                                                AcDb::SubentType       subentType,
                                                AcArray<AcDbSubentId>& allSubentIds)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the vertex AcDbSubentIds corresponding to the given edge AcDbSubentId.
    /// This protocol is needed to query the relations between the edge and vertex
    /// subentities. The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> 
    /// Edge AcDbSubentId whose vertex AcDbSubentIds are to be obtained. 
    /// </param>
    /// <param name="startVertexSubentId"> 
    /// Returned AcDbSubentId of the start vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="endVertexSubentId"> 
    /// Returned AcDbSubentId of the end vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="otherVertexSubentIds"> 
    /// Returned other AcDbSubentIds associated with the edge, such as the 
    /// circle or arc center, spline control and fit points, etc.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeVertexSubentities(const AcDbEntity*      pEntity,
                                                       const AcDbSubentId&    edgeSubentId,
                                                       AcDbSubentId&          startVertexSubentId,
                                                       AcDbSubentId&          endVertexSubentId,
                                                       AcArray<AcDbSubentId>& otherVertexSubentIds)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the vertex AcDbSubentIds corresponding to the given edge AcDbSubentId
    /// whose geometry is defined by a spline. 
    /// This protocol is needed to query the relations between the edge and vertex
    /// subentities. The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> 
    /// Edge AcDbSubentId whose vertex AcDbSubentIds are to be obtained. 
    /// </param>
    /// <param name="startVertexSubentId"> 
    /// Returned AcDbSubentId of the start vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="endVertexSubentId"> 
    /// Returned AcDbSubentId of the end vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="controlPointSubentIds"> 
    /// Returned AcDbSubentIds identifying the spline control points. The order
    /// is the same as the order of the spline control points.
    /// </param>
    /// <param name="fitPointSubentIds"> 
    /// Returned AcDbSubentIds identifying the spline fit points (if any). 
    /// The order is the same as the order of the spline fit points.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSplineEdgeVertexSubentities(const AcDbEntity*      pEntity,
                                                             const AcDbSubentId&    edgeSubentId,
                                                             AcDbSubentId&          startVertexSubentId,
                                                             AcDbSubentId&          endVertexSubentId,
                                                             AcArray<AcDbSubentId>& controlPointSubentIds,
                                                             AcArray<AcDbSubentId>& fitPointSubentIds)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the coordinates of a vertex subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="vertexSubentId"> Vertex AcDbSubentId whose position is to be obtained. </param>
    /// <param name="vertexPosition"> Returned coordinates of the vertex subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getVertexSubentityGeometry(const AcDbEntity*   pEntity,
                                                         const AcDbSubentId& vertexSubentId,
                                                         AcGePoint3d&        vertexPosition)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the curve of an edge subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> Edge AcDbSubentId whose curve is to be obtained. </param>
    /// <param name="pEdgeCurve"> Returned curve of the edge subentity (the caller becomes its owner). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeSubentityGeometry(const AcDbEntity*   pEntity,
                                                       const AcDbSubentId& edgeSubentId,
                                                       AcGeCurve3d*&       pEdgeCurve)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the surface of a face subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose surface is to be changed. </param>
    /// <param name="pFaceSurface"> Returned surface of the face subentity (the caller becomes its owner). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getFaceSubentityGeometry(const AcDbEntity*   pEntity,
                                                       const AcDbSubentId& faceSubentId,
                                                       AcGeSurface*&       pFaceSurface)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the geometry of a vertex subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="vertexSubentId"> Vertex AcDbSubentId whose position is to be changed. </param>
    /// <param name="newVertexPosition"> New coordinates of the vertex subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setVertexSubentityGeometry(AcDbEntity*         pEntity,
                                                         const AcDbSubentId& vertexSubentId,
                                                         const AcGePoint3d&  newVertexPosition)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the curve of an edge subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed.  The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="edgeSubentId"> Edge AcDbSubentId whose curve is to be changed. </param>
    /// <param name="pNewEdgeCurve"> New curve of the edge subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setEdgeSubentityGeometry(AcDbEntity*         pEntity,
                                                       const AcDbSubentId& edgeSubentId,
                                                       const AcGeCurve3d*  pNewEdgeCurve)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the surface of a face subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose surface is to be changed. </param>
    /// <param name="pNewFaceSurface"> New surface of the face subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setFaceSubentityGeometry(AcDbEntity*         pEntity,
                                                       const AcDbSubentId& faceSubentId,
                                                       const AcGeSurface*  pNewFaceSurface)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the geometry of a subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed. Because not many entities will need
    /// to implement this method, there is default implementation that just 
    /// returns eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="subentId"> AcDbSubentId whose geometry is to be changed. </param>
    /// <param name="pNewSubentityGeometry"> New geometry of the subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setSubentityGeometry(AcDbEntity*         pEntity,
                                                   const AcDbSubentId& subentId,
                                                   const AcDbEntity*   pNewSubentityGeometry)
    {
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Get transformation information on subentities according to stretch points 
    /// movement. This method should be called after AcDbEntity::moveStretchPointsAt().
    /// The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <remarks>
    /// This method is deprecated and should not be used.
    /// </remarks>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="indices">
    /// Input array containing index values (which correspond to stretch points 
    /// reported by the AcDbEntity::getStretchPoints() method) that indicate which 
    /// stretch points are being translated.
    /// </param>
    /// <param name="offset">
    /// Input vector (in WCS coordinates) indicating the direction and magnitude 
    /// that the stretch points have been translated. 
    /// </param>
    /// <param name="aSubentTransInfos">
    /// Returned array of AcDbAssocSubentTransInfo indicating the transformation 
    /// of subentities caused by the stretch points movement. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentTransFromStretchPoints(const AcDbEntity*   pEntity,
                                                              const AcDbIntArray& indices, 
                                                              const AcGeVector3d& offset,
                                                              AcArray<AcDbAssocSubentTransInfo>& aSubentTransInfos) const
    {
      return Acad::eNotImplemented;
    }

    /// <summary>
    /// Get transformation information on subentities according to grip points 
    /// movement. This method should be called after AcDbEntity::moveGripPointsAt().
    /// The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <remarks>
    /// This method is deprecated and should not be used.
    /// </remarks>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="indices">
    /// Input array containing index values (which correspond to grip points 
    /// reported by the AcDbEntity::getGripPoints() method) that indicate which 
    /// stretch points are being translated.
    /// </param>
    /// <param name="offset">
    /// Input vector (in WCS coordinates) indicating the direction and magnitude 
    /// that the grip points have been translated. 
    /// </param>
    /// <param name="aSubentTransInfos">
    /// Returned array of AcDbAssocSubentTransInfo indicating the transformation 
    /// of subentities caused by the grip points movement. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentTransFromGripPoints(const AcDbEntity*   pEntity,
                                                           const AcDbIntArray& indices, 
                                                           const AcGeVector3d& offset,
                                                           AcArray<AcDbAssocSubentTransInfo>& aSubentTransInfos) const
    {
      return Acad::eNotImplemented;
    }

    /// <summary>
    /// Get transformation information on subentities according to grip points 
    /// movement. This method should be called after AcDbEntity::moveGripPointsAt().
    /// The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <remarks>
    /// This method is deprecated and should not be used.
    /// </remarks>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="indices">
    /// Input array containing index values (which correspond to grip points 
    /// reported by the AcDbEntity::getGripPoints() method) that indicate which 
    /// stretch points are being translated.
    /// </param>
    /// <param name="offset">
    /// Input vector (in WCS coordinates) indicating the direction and magnitude 
    /// that the grip points have been translated. 
    /// </param>
    /// <param name="aSubentTransInfos">
    /// Returned array of AcDbAssocSubentTransInfo indicating the transformation 
    /// of subentities caused by the grip points movement. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentTransFromGripPoints(const AcDbEntity*       pEntity,
                                                           const AcDbVoidPtrArray& gripAppData, 
                                                           const AcGeVector3d&     offset,
                                                           AcArray<AcDbAssocSubentTransInfo>& aSubentTransInfos) const
    {
      return Acad::eNotImplemented;
    }

    /// <summary>
    /// Call this method to obtain block transformation matrix for a given 
    /// sub-entity within the block reference.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="fullSubentPath">
    /// Full path of the sub-entity whose collective transformation matrix is 
    /// to be determined.
    /// </param>
    /// <param name="trans"> Output block transformation matrix. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentGeometryXform(const AcDbEntity*        pEntity,
                                                     const AcDbObjectIdArray& fullSubentPath,
                                                     AcGeMatrix3d&            trans) const
    {
        trans.setToIdentity();
        return Acad::eOk;
    }

    /// <summary> <para>
    /// Mirrors the given AcDbAssocPersSubentId, i.e. it changes it so that it
    /// identitifies the same subentity in the mirrored entity as it identified
    /// before the entity has been mirrored. It is called from the default
    /// implementation of the AcDbAssocPersSubentId::mirror() method.
    /// </para> <para>
    /// The default implementation is a no-op, but some derived AcDbAssocPersSubentIdPE 
    /// protocol extension classes (such as AcDbAssocArcPersSubentIdPE) may need 
    /// to override this method.
    /// </para> </summary>
    /// <param  name="pMirroredEntity"> 
    /// The entity that has been mirrored. It needs to be open for read. 
    /// </param>
    /// <param name="persSubentIdToMirror"> 
    /// The AcDbAssocPersSubentId to be changed to reflect the fact that the 
    /// entity has been mirrored.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus mirrorPersSubent(const AcDbEntity*      pMirroredEntity,
                                               AcDbAssocPersSubentId& persSubentIdToMirror)
    {
        return Acad::eOk;
    }

    /// <summary>
    /// Returns kScalableRigidSet or kNonScalableRigidSet if the entity is a rigid 
    /// set, i.e. it can be rotated and translated as a whole, but its subentities 
    /// cannot be individually changed.
    /// The default implementation returns kNotRigidSet.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <returns> kScalableRigidSet or kNonScalableRigidSet if the entity is a rigid set. </returns>
    ///
    virtual int getRigidSetState(const AcDbEntity* pEntity) { return kNotRigidSet; }

    /// <summary>
    /// Get the transformation of the rigid set entity.
    /// The default implementation returns Acad::eNotApplicable.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="trans"> The returned transformation matrix. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getRigidSetTransform(const AcDbEntity* pEntity,
                                                   AcGeMatrix3d&     trans)
    {
        return Acad::eNotApplicable;
    }

    /// <summary>
    /// Set the transformation of the rigid set entity.
    /// The default implementation returns Acad::eNotApplicable.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="trans"> New transformation matrix of the rigid set entity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setRigidSetTransform(AcDbEntity*         pEntity, 
                                                   const AcGeMatrix3d& trans)
    {
        return Acad::eNotApplicable;
    }

}; // class AcDbAssocPersSubentIdPE

#pragma pack (pop)


