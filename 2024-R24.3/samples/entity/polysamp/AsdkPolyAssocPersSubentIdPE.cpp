//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCROPTION:
//
// Implementation of the AsdkPolyAssocPersSubentIdPE protocol extension class.

#include "acdb.h"
#include "eoktest.h"
#include "poly.h"
#include "gearc3d.h"    // AcGeCircArc3d
#include "gelnsg3d.h"   // AcGeLineSeg3d
#include "AsdkPolyAssocPersSubentIdPE.h"
#include "AcDbAssocIndexPersSubentId.h"

ACRX_CONS_DEFINE_MEMBERS(AsdkPolyAssocPersSubentIdPE, AcDbAssocPersSubentIdPE, 0)


// 0 < numSides    && numSides    <= AsdkPoly::kMaxNumSides
// 0 < subentIndex && subentIndex <= numSides
//
static unsigned int makeCodeFromNumSidesAndSubentIndex(int numSides, int subentIndex)
{
    return (AsdkPoly::kMaxNumSides+1) * numSides + subentIndex;
}

static int getNumSidesFromCode(unsigned int code)
{
    return code / (AsdkPoly::kMaxNumSides+1);
}

static int getSubentIndexFromCode(unsigned int code)
{
    return code % (AsdkPoly::kMaxNumSides+1);
}


AcDbAssocPersSubentId* AsdkPolyAssocPersSubentIdPE::createNewPersSubent(
    AcDbEntity*                 pEntity,
    AcDbDatabase*,
    const AcDbCompoundObjectId& compId,
    const AcDbSubentId&         subentId)
{
    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return nullptr;
    if (!(subentId.type() == AcDb::kVertexSubentType || subentId.type() == AcDb::kEdgeSubentType))
        return nullptr; // AsdkPoly entity only has vertex and edge subentities

    if ((int)subentId.index() == kCenterSubentIndex) // The center has fixed index kCenterSubentIndex (-1)
        return new AcDbAssocIndexPersSubentId(subentId.type(), kCenterSubentIndex);

    const unsigned int code = makeCodeFromNumSidesAndSubentIndex(pPoly->numSides(), (int)subentId.index());

    return new AcDbAssocIndexPersSubentId(subentId.type(), code);
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getTransientSubentIds(
    const AcDbEntity*            pEntity,
    AcDbDatabase*                pDatabase,
    const AcDbAssocPersSubentId* pPersSubentId,
    AcArray<AcDbSubentId>&       transSubentIds) const 
{
    transSubentIds.removeAll();

    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;

    const AcDbAssocIndexPersSubentId* const pIndexPersSubentId = AcDbAssocIndexPersSubentId::cast(pPersSubentId);
    if (pIndexPersSubentId == nullptr)
        return Acad::eNotThatKindOfClass;

    const AcDb::SubentType subentType = pIndexPersSubentId->subentType(pEntity, pDatabase);
    if (!(subentType == AcDb::kVertexSubentType || subentType == AcDb::kEdgeSubentType))
        return Acad::eWrongSubentityType;

    const unsigned int code = pIndexPersSubentId->index();

    const int oldNumSides = getNumSidesFromCode(code);
    const int newNumSides = pPoly->numSides();
    const int oldIndex    = getSubentIndexFromCode(code);
    int       newIndex    = 0;

    if (oldIndex == kCenterSubentIndex) // The center has fixed index kCenterSubentIndex (-1)
    {
        transSubentIds.append(AcDbSubentId(subentType, kCenterSubentIndex));
        return Acad::eOk;
    }

    // Find mapping: oldSubentIndex --> newSubentIndex
    //
    if (newNumSides == oldNumSides)
    {
        // The poly entity in its current state has the same number of sides as the 
        // entity had in the state when the persistent subentity id was created.
        //
        // There is no question about which edge/vertex subentity in the current state 
        // of the entity to choose as the "topology" of the entity hasn't changed
        //
        newIndex = oldIndex;
    }
    else 
    {
        switch (pPoly->getPersSubentIdSolver())
        {
        case AsdkPoly::kFixedIndicesPersSubentIdSolver:
            {
                newIndex = oldIndex;
                if (newIndex > newNumSides)
                    newIndex = newNumSides;
            }
            break;
        case AsdkPoly::kDistributeIndicesProportionallyPersSubentIdSolver:
            {
                const double numSidesRatio = newNumSides / (double)oldNumSides;

                // The poly entity in its current state has a different number of sides than the
                // entity had in the state when the persistent subentity id was created.
                //
                // There is no 1-on-1 mapping between edges/vertices in the previous and 
                // in the current state of the poly entity.
                //
                // We can define a mapping that maps each edge/vertex in the previous state of the
                // entity to a single edge/vertex in the current state of the entity
                //
                newIndex = int(numSidesRatio * (oldIndex - 1) + 0.5) + 1;
            }
            break;
        default:
            {
                assert(!"Unsupported PersSubentIdSolver");
                newIndex = oldIndex;
            }
            break;
        }
    }

    transSubentIds.append(AcDbSubentId(subentType, newIndex));
    return Acad::eOk;
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getRigidSetTransform(const AcDbEntity* pEntity,
                                                                    AcGeMatrix3d&     trans)
{ 
    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;

    // Create a rigid transformation matrix from the AsdkPoly definition data 
    //
    AcGePoint3d        center;
    AcGePoint3d        startPoint;
    const AcGeVector3d normal = pPoly->normal();
    pPoly->getCenter(center);
    pPoly->getStartPoint(startPoint);

    const AcGeVector3d xAxis = (startPoint - center).normal();
    const AcGeVector3d yAxis = (normal.crossProduct(xAxis)).normal();
    const AcGeVector3d zAxis = normal.normal();

    trans.setCoordSystem(center, xAxis, yAxis, zAxis);
    return Acad::eOk;
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getAllSubentities(const AcDbEntity*      pEntity,
                                                                 AcDb::SubentType       subentType,
                                                                 AcArray<AcDbSubentId>& allSubentIds)
{
    allSubentIds.removeAll();

    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;
    if (!(subentType == AcDb::kVertexSubentType || subentType == AcDb::kEdgeSubentType))
        return Acad::eOk; // AsdkPoly only has vertex and edge subentities

    for (int i = 0; i < pPoly->numSides(); i++)
    {
        allSubentIds.append(AcDbSubentId(subentType, i+1));
    }

    // The center is returned as a vertex subentity, but also as a pseudo edge 
    // subentity (needed because constraints deal with edges, not isolated vertices)
    //
    allSubentIds.append(AcDbSubentId(subentType, kCenterSubentIndex));
    return Acad::eOk;
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getEdgeVertexSubentities(const AcDbEntity*      pEntity,
                                                                        const AcDbSubentId&    edgeSubentId,
                                                                        AcDbSubentId&          startVertexSubentId,
                                                                        AcDbSubentId&          endVertexSubentId,
                                                                        AcArray<AcDbSubentId>& otherVertexSubentIds)
{
    startVertexSubentId = endVertexSubentId = AcDbSubentId();
    otherVertexSubentIds.removeAll();

    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;
    if (edgeSubentId.type() != AcDb::kEdgeSubentType)
        return Acad::eWrongSubentityType;
    const int index = (int)edgeSubentId.index();

    if (index == kCenterSubentIndex)
    {
        // The pseudo edge subentity at the center (needed because constraints 
        // deal with edges, not isolated vertices)
        //
        otherVertexSubentIds.append(AcDbSubentId(AcDb::kVertexSubentType, kCenterSubentIndex));
        return Acad::eOk;
    }

    if (!(1 <= index && index <= pPoly->numSides()))
        return Acad::eInvalidIndex;

    startVertexSubentId = AcDbSubentId(AcDb::kVertexSubentType, index);
    endVertexSubentId   = AcDbSubentId(AcDb::kVertexSubentType, index == pPoly->numSides() ? 1 : index+1);
    return Acad::eOk;
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getVertexSubentityGeometry(const AcDbEntity*   pEntity,
                                                                          const AcDbSubentId& vertexSubentId,
                                                                          AcGePoint3d&        vertexPosition)
{
    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;
    if (vertexSubentId.type() != AcDb::kVertexSubentType)
        return Acad::eWrongSubentityType;
    const int index = (int)vertexSubentId.index();

    if (index == kCenterSubentIndex)
    {
        pPoly->getCenter(vertexPosition);
        return Acad::eOk;
    }
    if (!(1 <= index && index <= pPoly->numSides()))
        return Acad::eInvalidIndex;
    AcGePoint3dArray vertexCoords;
    pPoly->getVertices3d(vertexCoords);
    vertexPosition = vertexCoords[index-1];
    return Acad::eOk;
}


Acad::ErrorStatus AsdkPolyAssocPersSubentIdPE::getEdgeSubentityGeometry(const AcDbEntity*   pEntity,
                                                                        const AcDbSubentId& edgeSubentId,
                                                                        AcGeCurve3d*&       pEdgeCurve)
{
    const AsdkPoly* const pPoly = AsdkPoly::cast(pEntity);
    if (pPoly == nullptr)
        return Acad::eNotThatKindOfClass;
    if (edgeSubentId.type() != AcDb::kEdgeSubentType)
        return Acad::eWrongSubentityType;
    const int index1 = (int)edgeSubentId.index();

    if (index1 == kCenterSubentIndex)
    {
        AcGePoint3d center;
        pPoly->getCenter(center);

        // The pseudo edge subentity at the center (needed because constraints 
        // deal with edges, not isolated vertices)
        //
        const double radius = pPoly->center().distanceTo(pPoly->startPoint());
        pEdgeCurve = new AcGeCircArc3d(center, pPoly->normal(), radius);
        return Acad::eOk;
    }

    if (!(1 <= index1 && index1 <= pPoly->numSides()))
        return Acad::eInvalidIndex;
    const int index2 = index1 == pPoly->numSides() ? 1 : index1+1;

    AcGePoint3dArray vertexCoords;
    pPoly->getVertices3d(vertexCoords);
    pEdgeCurve = new AcGeLineSeg3d(vertexCoords[index1-1], vertexCoords[index2-1]);
    return Acad::eOk;
}
