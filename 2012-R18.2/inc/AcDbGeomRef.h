
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2009-2011 by Autodesk, Inc. 
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
// CREATED BY: Jiri Kripac                                 October 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h" 
#include "gemat3d.h"
#include "AcDbCompoundObjectId.h"
#pragma pack (push, 8)



/// <summary><para>
/// Base class for the concrete derived classes like AcDbEdgeRef, AcDbPathRef
/// and AcDbVertexRef. These are simple classes that keep a reference to a subentity 
/// of an entity and can represent this subentity information in various ways. 
/// They are used mainly to pass around information about geometry of a subentity 
/// or of an entity, not to keep this information.
/// </para><para>
/// The subentity references are non-presistent. Anytime the referenced entity 
/// is changed or re-evaluated, the subentity reference becomes invalid.
/// Persistent references can be established using AcDbAssocEdgeActionParam, 
/// AcDbAssocPathActionParam, AcDbAssocVertexActionParam, or directly using 
/// AcDbAssocGeomDependencies.
/// </para></summary>
///
class ACDB_PORT AcDbGeomRef : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGeomRef);

    virtual ~AcDbGeomRef() {}

    /// <summary> Resets the contents of the AcDbGeomRef to empty. </summary>
    ///
    virtual void reset() = 0;

    /// <summary> Checks is the contents of this AcDbGeomRef is valid. </summary>
    ///
    virtual bool isValid() const = 0;

    /// <summary> 
    /// Checks if the AcDbGeomRef is empty, i.e. not referencing any entity,
    /// subentity, and not holding any constant geometry. 
    /// </summary>
    ///
    virtual bool isEmpty() const = 0;
};


/// <summary><para>
/// Base class for AcDbFaceRef, AcDbEdgeRef and AcDbVertexRef. It keeps an 
/// AcDbCompoundObjectId of an AcDbEntity and AcDbSubentId of a subentity of 
/// this entity.
/// </para></summary>
///
class ACDB_PORT AcDbSubentRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSubentRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbSubentRef() {}

    /// <summary> The constructor sets data members of the AcDbSubentRef. </summary>
    ///
    AcDbSubentRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId); 

    AcDbSubentRef& operator =(const AcDbSubentRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isEmpty() const { return mEntityId.isEmpty(); }

    /// <summary> 
    /// Returns the AcDbCompoundObjectId of the entity that the AcDbSubentRef references.
    /// May be empty if a derived class holds constant geometry and does not 
    /// reference any existing AcDbEntity.
    /// </summary>
    ///
    const AcDbCompoundObjectId& entity() const { return mEntityId; }

    /// <summary> 
    /// Returns the AcDbSubentId in an AcDbEntity that the AcDbSubentRef references. 
    /// May be null if whole AcDbEntity is referenced.
    /// </summary>
    ///
    AcDbSubentId subentId() const { return mSubentId; }

    /// <summary> Returns true if entity() is not null. </summary>
    ///
    bool hasEntity() const { return !mEntityId.isEmpty(); }

    /// <summary> Returns true if subentId() is not null. </summary>
    ///
    bool hasSubent() const { return mSubentId != kNullSubentId; }

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from the data the AcDbSubentRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    AcDbEntity* createEntity() const;

protected:

    /// <summary> Sets mEntity data member. </summary>
    ///
    void setEntity(const AcDbCompoundObjectId& entityId) { mEntityId = entityId; }

    /// <summary> Sets mSubentId data member. </summary>
    ///
    void setSubent(const AcDbSubentId& subentId) { mSubentId = subentId; }

    /// <summary> Sets mEntity and mSubentId data members. </summary>
    ///
    void setFromSubentPath(const AcDbFullSubentPath&);

private:
    AcDbCompoundObjectId mEntityId;
    AcDbSubentId         mSubentId;
};


/// <summary>
/// Reference to a face. It can either be represented by a face AcDbSubentId of 
/// an ASM-based AcDbEntity (AcDbSurface, AcDb3dSolid, AcDbRegion) or by
/// a constant ASM BODY and the AcDbSubentId then specifies the index of the 
/// face in the constant ASM BODY.
/// </summary>
///
class ACDB_PORT AcDbFaceRef : public AcDbSubentRef
{
#ifdef _ADESK_MAC_
private:
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbFaceRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbFaceRef();
    AcDbFaceRef(const AcDbFaceRef&);
    virtual ~AcDbFaceRef();

    /// <summary> 
    /// The constructor sets the data members of the AcDbFaceRef. The provided
    /// ASM BODY is not copied, the caller is responsible for providing a copy,
    /// if needed.
    /// </summary>
    ///
    AcDbFaceRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId, class BODY* = NULL); 

    AcDbFaceRef& operator =(const AcDbFaceRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;
    virtual bool isEmpty() const { return __super::isEmpty() && mpAsmBody == NULL; }

    /// <summary> 
    /// Returns the ASM BODY that the AcDbFaceRef may hold. It does not return a 
    /// copy of the ASM BODY, therefore the client code needs to make a copy if 
    /// it needs to do any modifications to this ASM BODY.
    /// </summary>
    ///
    class BODY* asmBody() const { return mpAsmBody; }    

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from the data the AcDbFaceRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    AcDbEntity* createEntity() const;

private:
    class BODY* mpAsmBody;
};


/// <summary><para>
/// Reference to an edge, i.e. a subentity whose geometry is a simple curve. 
/// </para><para>
/// It may either be the whole entity that itself is a single curve, kEdgeSubentType 
/// subentity of an entity, or a constant AcGeCurve3d. Notice that this reference
/// is generally non-persistent, because it uses transient AcDbSubentId. 
/// </para><para>
/// The option to reference the whole entity is questionable and has been provided
/// just for the compatibility with old code that takes the whole entity. We should 
/// probably always represent edges by kEdgeSubentType subentities of entities, even
/// if the whole entity is just a single edge, such as line, arc, or circle.
/// </para></summary>
///
class ACDB_PORT AcDbEdgeRef : public AcDbSubentRef
{
#ifdef _ADESK_MAC_
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbEdgeRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbEdgeRef();
    AcDbEdgeRef(const AcDbEdgeRef&);
    virtual ~AcDbEdgeRef();

    /// <summary> The constructor sets the data members of the AcDbEdgeRef. </summary>
    ///
    AcDbEdgeRef(const AcDbCompoundObjectId&, 
                const AcDbSubentId& edgeSubentId = kNullSubentId, 
                const AcDbSubentId& faceSubentId = kNullSubentId, 
                const AcGeCurve3d* pCurve        = NULL);

    /// <summary> 
    /// Creates AcDbEdgeRef from an entity in a block table record
    /// and referenced via a path of block inserts.
    /// </summary>
    ///
    AcDbEdgeRef(const AcDbFullSubentPath&);  

    /// <summary> 
    /// The constructor makes the AcDbEdgeRef keep the AcDbObjectId of the given 
    /// AcDbEntity. Moreover, if the entity is derived from AcDbCurve, it obtains 
    /// a copy of the AcGeCurve3d and keeps in it the AcDbEdgeRef.
    /// </summary>
    ///
    AcDbEdgeRef(const AcDbEntity* pEntity);  

    /// <summary> 
    /// The constructor makes the AcDbEdgeRef keep the AcGeCurve3d.
    /// </summary>
    ///
    AcDbEdgeRef(const AcGeCurve3d* pGeCurve);

    AcDbEdgeRef& operator =(const AcDbEdgeRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;
    virtual bool isEmpty() const { return __super::isEmpty() && mpCurve == NULL; }

    /// <summary> 
    /// The AcDbEdgeRef can also hoid the AcDbSubentId of a face subentity. The face
    /// needs to bounded by the referenced edge subentity. The additional face 
    /// information is needed in cases like when an edge shared by two adjacent 
    /// faces is refrenced and used for a smooth blend operation. It needs to
    /// be known which face to use to create the smooth blend to.
    ///</summary>
    ///
    void setFaceSubentity(const AcDbSubentId& faceSubentId);

    /// <summary> 
    /// Returns the optional face AcDbSubentId of one of the faces adjacent to the
    /// referenced edge.
    /// </summary>
    ///
    AcDbSubentId faceSubentId() const { return mFaceSubentId; }

    /// <summary> 
    /// Returns the constant AcGeCurve3d* that the AcDbEdgeRef may hold.
    /// </summary>
    ///
    const AcGeCurve3d* curve() const { return mpCurve; }    

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from then data the AcDbEdgeRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    AcDbEntity* createEntity() const;

private:
    AcDbSubentId mFaceSubentId;
    AcGeCurve3d* mpCurve;
};


/// <summary>
/// Reference to a vertex, i.e. a subentity whose geometry is a point. It may 
/// either be whole AcDbPoint entity, kVertexSubentType subentity of an entity, or 
/// a constant AcGePoint3d. Notice that this reference is generally non-persistent, 
/// because it uses transient AcDbSubentId. 
/// </summary>
///
class ACDB_PORT AcDbVertexRef : public AcDbSubentRef
{
#ifdef _ADESK_MAC_
private:
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbVertexRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbVertexRef();
    AcDbVertexRef(const AcDbVertexRef&);
    virtual ~AcDbVertexRef();

    /// <summary> The constructor sets the data members of the AcDbEdgeRef. </summary>
    ///
    AcDbVertexRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId, const AcGePoint3d& = AcGePoint3d::kOrigin);

    /// <summary> 
    /// Creates AcDbVertexRef from an entity in a block table record
    //  and referenced via a path of block inserts.
    /// </summary>
    ///
    AcDbVertexRef(const AcDbFullSubentPath&);

    /// <summary> 
    /// The constructor makes the AcDbVertexRef keep the AcDbObjectId of the given 
    /// AcDbEntity. Moreover, if the entity is derived from AcDbPoint, it keeps 
    /// its AcGePoint3d as AcGePoint3d.
    /// </summary>
    ///
    AcDbVertexRef(const AcDbEntity*);

    /// <summary> 
    /// The constructor makes the AcDbVertexRef keep the AcGePoint3d.
    /// </summary>
    ///
    AcDbVertexRef(const AcGePoint3d&);

    AcDbVertexRef& operator =(const AcDbVertexRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;

    /// <summary> 
    /// Returns the AcGePoint3d directly held in the AcDbVertexRef. 
    /// </summary>
    ///
    AcGePoint3d point() const;

    /// <summary> 
    /// Creates a new non-database resident AcDbPoint from then data the AcDbVertexRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the AcDbPoint after it is no more needed. 
    /// </summary>
    ///
    class AcDbPoint* createEntity()const;

private:
    AcGePoint3d mPoint; 
};


/// <summary>
/// Reference to a path, which is just a sequence of edges. If the path has an 
/// array of edges which happen to be connected at their end points, it will try 
/// to concatenate the curves into one composite curve.
/// </summary>
///
class ACDB_PORT AcDbPathRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPathRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbPathRef();
    AcDbPathRef(const AcDbPathRef&);

    /// <summary> 
    /// Creates an AcDbPathRef from a sequence of AcDbEdgeRefs.
    /// </summary>
    ///
    AcDbPathRef(const AcArray<AcDbEdgeRef> &edges);

    /// <summary> 
    /// Constructor an AcDbPathRef that is a sequence of connected edges.
    /// </summary>
    /// <param name="edgeSubentPathArr"> 
    /// Subent paths of the edges that make up the path. 
    /// </param>
    /// <param name="faceSubentPathArr"> 
    /// Optional subent paths of the faces for each edge.  The number of elements in
    /// this array must be 0 or be the same as the number of elements in
    /// edgeSubentPathArr. 
    /// </param>
   AcDbPathRef(const AcDbFullSubentPathArray& edgeSubentPathArr,
               const AcDbFullSubentPathArray& faceSubentPathArr);

    virtual ~AcDbPathRef();

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;
    virtual bool isEmpty() const;

    /// <summary> Sets the AcDbPathRef from a sequence of AcDbEdgeRefs. </summary>
    ///
    void setEdgeRefs(const AcArray<AcDbEdgeRef>& edges);

    /// <summary> 
    /// Returns an array of AcDbEntities created from the individual AcDbEdgeRefs
    /// in the path. If concatenate is true, it tries to concatenate them.
    /// </summary>
    ///
    void getEntityArray(AcArray<AcDbEntity*>& entities, bool concatenate);

    /// <summary> Returns the array of AcDbEdgeRefs kept in the AcDbPathRef. </summary>
    ///
    const AcArray<AcDbEdgeRef>& edgeRefs() const { return mEdgeRefs; }

    /// <summary> Returns true if the geometry of the path is equal to the geometry of the given curve. </summary>
    ///
    bool isEqualTo(const AcGeCurve3d*);

    /// <summary> 
    /// Returns true if all elements of the path are references to entities, i.e.
    /// they are not constant geometries.
    /// </summary>
    ///
    bool isReferencePath();

private:
    AcArray<AcDbEdgeRef> mEdgeRefs;
};


/// <summary>
/// Arbitrary 3D vector, of any length.
/// </summary>
///
class ACDB_PORT AcDbVectorRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbVectorRef);

    explicit AcDbVectorRef();

    explicit AcDbVectorRef(const AcDbVectorRef&);

    explicit AcDbVectorRef(const AcGeVector3d&);

    virtual ~AcDbVectorRef();

    AcDbVectorRef& operator = (const AcDbVectorRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;
    virtual bool isEmpty() const;

    const AcGeVector3d vector() const { return mVector; }

    void set(const AcGeVector3d&);

private:

    AcGeVector3d mVector;
};


/// <summary>
/// Coordinate system, actually an arbitrary matrix. The axes do not need to be
/// unit lengths, perpendicular, or form right-hand coord system (may be mirrored).
/// </summary>
///
class ACDB_PORT AcDbCoordSystemRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbCoordSystemRef);

    explicit AcDbCoordSystemRef();

    explicit AcDbCoordSystemRef(const AcDbCoordSystemRef&);

    explicit AcDbCoordSystemRef(const AcGeMatrix3d&);

    explicit AcDbCoordSystemRef(const AcDbCompoundObjectId&, const AcGeMatrix3d&); 

    explicit AcDbCoordSystemRef(const AcArray<const AcDbSubentRef*>&);

    virtual ~AcDbCoordSystemRef();

    AcDbCoordSystemRef& operator = (const AcDbCoordSystemRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual void reset();
    virtual bool isValid() const;
    virtual bool isEmpty() const;

    const AcGeMatrix3d&                  coordSystem() const { return mCoordSystem; }
    const AcDbCompoundObjectId&          entityId   () const { return mEntityId;    }
    const AcArray<const AcDbSubentRef*>& subentRefs () const { return mSubentRefs;  }

    void set(const AcGeMatrix3d&);
    void set(const AcDbCompoundObjectId&);
    void set(const AcArray<const AcDbSubentRef*>&);

private:

    AcGeMatrix3d                  mCoordSystem;
    AcDbCompoundObjectId          mEntityId;
    AcArray<const AcDbSubentRef*> mSubentRefs;
};


#pragma pack (pop)

