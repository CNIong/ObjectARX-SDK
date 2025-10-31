//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// This is the main source file to look at. It contains implementation of 
// the AssocFilletActionBody class.
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "eoktest.h"
#include "dbobjptr2.h"
#include "dbproxy.h"
#include "dbidmap.h"
#include "AcDbAssocObjectPointer.h"
#include "AcDbAssocDependency.h"
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbAssocObjectActionParam.h"
#include "AssocFilletActionBody.h"
#include "acdbabb.h"   // AcDb::  abbreviations
#include "adeskabb.h"  // Adesk:: abbreviations

// Always use AcDbSmartObjectPointer
//
#define AcDbObjectPointer AcDbSmartObjectPointer

ACRX_DXF_DEFINE_MEMBERS(AssocFilletActionBody, 
                        AcDbAssocActionBody, 
                        AcDb::kDHL_1027, 
                        AcDb::kMRelease83, 
                        AcDbProxyObject::kAllAllowedBits, 
                        ASSOCFILLETACTIONBODY, 
                        AssocFilletSample)

// Names of action parameters
//
const wchar_t* const kInputEdgeParamName     = L"InputEdge";
const wchar_t* const kTrimInputEdgeParamName = L"TrimInput";
const wchar_t* const kRadiusParamName        = L"Radius";


double AssocFilletActionBody::getRadius(AcString& expressionOut) const
{
    expressionOut = L"";
    AcDbEvalVariant value;
    if (!eOkVerify(getValueParam(kRadiusParamName, value, expressionOut, AcString())))
        return 0.0;
    double radius = 0.0;
    return eOkVerify(value.getValue(radius)) ? fabs(radius) : 0.0;
}


ErrorStatus AssocFilletActionBody::setRadius(double radius, const AcString& expression)
{
    ASSERT(radius >= 0.0);
    return setValueParam(kRadiusParamName, fabs(radius), expression, L"", AcString(), true);
}


// We are using AcDbAssocEdgeActionParam. We could also directly use
// AcDbAssocDependency (on the whole entity) or AcDbAssocGeomDependency
// (on an edge subentity of an entity), as the advantage of an edge action 
// parameter that can also hold constant geometry is not used in our scenario.
//
// AcDbAssocEdgeActionParam internally uses AcDbAssocObjectPointer to open the
// referenced entity. If the referenced entity is being dragged, the returned 
// entity is a temporary non-database-resident clone of the original entity,
// created by the dragger. The client code does not need to worry as it 
// happens transparently
//
AcDbEdgeRef AssocFilletActionBody::getInputEdge(int index) const
{
    ASSERT(index == 0 || index == 1);
    AcDbObjectPointer<AcDbAssocEdgeActionParam> pEdgeParam(paramAtName(kInputEdgeParamName, index), kForRead);
    if (!eOkVerify(pEdgeParam.openStatus()))
        return AcDbEdgeRef();
    AcArray<AcDbEdgeRef> edgeRefs;
    ErrorStatus err = pEdgeParam->getEdgeRef(edgeRefs);
    return VERIFY(err == eOk && edgeRefs.length() == 1) ? edgeRefs[0] : AcDbEdgeRef();
}


AcGeCurve3d* AssocFilletActionBody::getInputCurve(int index) const
{
    const AcDbEdgeRef inputEdge = getInputEdge(index);
    return inputEdge.curve() != nullptr ? static_cast<AcGeCurve3d*>(inputEdge.curve()->copy()) : nullptr;
}


ErrorStatus AssocFilletActionBody::setInputEdge(int index, const AcDbEdgeRef& inputEdge)
{
    ASSERT(index == 0 || index == 1);
    AcDbObjectPointer<AcDbAssocEdgeActionParam> pEdgeParam(paramAtName(kInputEdgeParamName, index), kForWrite);
    if (!eOkVerify(pEdgeParam.openStatus()))
        return pEdgeParam.openStatus();
    return pEdgeParam->setEdgeRef(inputEdge, true, false);
}


AcDbObjectId AssocFilletActionBody::getFilletArcId() const
{
    if (mFilletArcDepId.isNull())
        return AcDbObjectId::kNull;
    AcDbObjectPointer<AcDbAssocDependency> pArcEntityDep(mFilletArcDepId, kForRead);
    if (!eOkVerify(pArcEntityDep.openStatus()))
        return AcDbObjectId::kNull;
    return pArcEntityDep->dependentOnObject();
}


AcGeCircArc3d AssocFilletActionBody::getFilletArcGeom() const
{
    const AcDbObjectId filletArcId = getFilletArcId();
    if (filletArcId.isNull()) // Legal case when the radius is 0.0
        return AcGeCircArc3d(); 

    // We are using AcDbAssocObjectPointer, not AcDbSmartObjectPointer,
    // because this method is also called during dragging
    //
    AcDbAssocObjectPointer<AcDbArc> pArc(filletArcId, kForRead);
    if (!eOkVerify(pArc.openStatus()))
        return AcGeCircArc3d();

    AcGeCurve3d* pGeCurve = nullptr;
    if (!eOkVerify(pArc->getAcGeCurve(pGeCurve)))
        return AcGeCircArc3d();

    if (!VERIFY(pGeCurve->type() == AcGe::kCircArc3d))
        return AcGeCircArc3d();
    const AcGeCircArc3d geArc = *static_cast<AcGeCircArc3d*>(pGeCurve);
    delete pGeCurve;
    return geArc;
}


bool AssocFilletActionBody::isTrimInputEdge(int index, AcString& expressionOut) const
{
    ASSERT(index == 0 || index == 1);
    AcDbEvalVariant value;
    if (!eOkVerify(getValueParam(kTrimInputEdgeParamName, value, expressionOut, AcString(), index)))
        return false;
    Adesk::Int32 trimIt = 0;
    if (!eOkVerify(value.getValue(trimIt)))
        return false;
    ASSERT(trimIt == 0 || trimIt == 1);
    return trimIt != 0;
}


ErrorStatus AssocFilletActionBody::setTrimInputEdge(int index, bool yesNo, const AcString& expression)
{
    ASSERT(index == 0 || index == 1);
    ErrorStatus err = setValueParam(kTrimInputEdgeParamName, AcDbEvalVariant((Adesk::Int32)yesNo), expression, L"", AcString(), true, index);
    if (!eOkVerify(err))
        return err;

    // Synchronize the Dependency to be read-only or read-write
    //
    AcDbObjectPointer<AcDbAssocEdgeActionParam> pEdgeParam(paramAtName(kInputEdgeParamName, index), kForRead);
    if (!eOkVerify(pEdgeParam.openStatus()))
        return pEdgeParam.openStatus();
    AcDbObjectIdArray depIds;
    if (!eOkVerify(err = pEdgeParam->getDependencies(true, true, depIds)))
        return err;
    if (!VERIFY(depIds.length() == 1))
        return eInvalidInput;
    AcDbObjectPointer<AcDbAssocDependency> pDep(depIds[0], kForWrite);
    if (!eOkVerify(pDep.openStatus()))
        return pDep.openStatus();

    // Trim input edge        --> read-write-dependency
    // Do not trim input edge --> read-only  dependency
    //
    pDep->setIsWriteDependency(yesNo); 
    return eOk;
}
    
    
bool AssocFilletActionBody::isFilletArc(const AcDbObjectId& filletArcId, AcDbObjectId& filletActionIdOut)
{
    filletActionIdOut.setNull();
    AcDbAssocObjectPointer<AcDbArc> pArc(filletArcId, kForRead);
    if (pArc.openStatus() != eOk)
        return false; // Not an AcDbArc entity
    
    AcDbObjectIdArray actionIds;
    ErrorStatus err = AcDbAssocAction::getActionsDependentOnObject(pArc, false, true, actionIds);
    if (!eOkVerify(err))
        return false;

    for (int i = 0; i < actionIds.length(); i++)
    {
        AcDbObjectPointer<AssocFilletActionBody> pFilletActionBody(AcDbAssocAction::actionBody(actionIds[i]), kForRead);
        if (pFilletActionBody.openStatus() != eOk)
            continue;

        if (pFilletActionBody->getFilletArcId() == filletArcId)
        {
            filletActionIdOut = actionIds[i]; 
            return true;
        }
    }
    return false; // No AssocFilletActionBody found on the arc
}


ErrorStatus AssocFilletActionBody::createFilletArcEntity()
{
    assertWriteEnabled();

    const AcDbObjectId inputEntityId = getInputEdge(0).entity().topId();
    
    AcDbObjectPointer<AcDbEntity> pInputEntity(inputEntityId, kForRead);
    if (!eOkVerify(pInputEntity.openStatus()))
        return pInputEntity.openStatus();

    const AcDbObjectId btrId = pInputEntity->blockId();
    AcDbObjectPointer<AcDbBlockTableRecord> pBtr(btrId, kForWrite);
    if (!eOkVerify(pBtr.openStatus()))
        return pBtr.openStatus();

    AcDbArc* const pArc = new AcDbArc();
    pArc->setDatabaseDefaults(database());
    pArc->setLayer(pInputEntity->layerId());

    ErrorStatus err = eOk;
    AcDbObjectId arcEntityId;
    if (!eOkVerify(err = pBtr->appendAcDbEntity(arcEntityId, pArc)))
    {
        delete pArc;
        return err;
    }
    pArc->close();

    if (VERIFY(mFilletArcDepId.isNull()))
    {
        // Create an AcDbAssocDependency on the fillet AcDbArc entity. 
        // The dependency on is write-only: The action does not use the geometry 
        // of the fillet arc entity, just sets it
        //
        addDependency(nullptr, nullptr, false/*isReadDep*/, true/*isWriteDep*/,
                      0/*order*/, mFilletArcDepId);
    }

    AcDbObjectPointer<AcDbAssocDependency> pFilletArcDep(mFilletArcDepId, kForWrite);
    if (!eOkVerify(pFilletArcDep.openStatus()))
        return pFilletArcDep.openStatus();

    if (!VERIFY(pFilletArcDep->dependentOnObject().isNull()))
        pFilletArcDep->detachFromObject();

    return pFilletArcDep->attachToObject(arcEntityId); 
}


ErrorStatus AssocFilletActionBody::eraseFilletArcEntity()
{
    assertWriteEnabled();

    const AcDbObjectId filletArcId = getFilletArcId();

    AcDbObjectPointer<AcDbAssocDependency> pFilletArcDep(mFilletArcDepId, kForWrite);
    if (pFilletArcDep.openStatus() == eOk)
        pFilletArcDep->erase();
    mFilletArcDepId = AcDbObjectId::kNull;

    AcDbObjectPointer<AcDbArc> pFilletArc(filletArcId, kForWrite, false, true);
    if (pFilletArc.openStatus() == eOk)
        pFilletArc->erase();
    return eOk;
}


ErrorStatus AssocFilletActionBody::computeNewGeometry(bool updateConfigState, AcGeCurve3d* pInputCurveOut[2], AcGeCircArc3d& filletArcOut) 
{
    assertReadEnabled();
    pInputCurveOut[0] = pInputCurveOut[1] = nullptr;
    filletArcOut = AcGeCircArc3d();

    AcGeCurve3d* pCurve[2] = { getInputCurve(0), getInputCurve(1), };
    std::unique_ptr<AcGeCurve3d> delete0(pCurve[0]);
    std::unique_ptr<AcGeCurve3d> delete1(pCurve[1]);
    if (!VERIFY(pCurve[0] != nullptr && pCurve[1] != nullptr))
        return eNullPtr;
    const bool isTrimInput[2] = { isTrimInputEdge(0), isTrimInputEdge(1), };

    // If contents of mFilletConfig is going to change, we need to do undo recording
    //
    if (updateConfigState)
        assertWriteEnabled();

    AcGeCircArc3d filletArc;
    ErrorStatus err = mFilletConfig.evaluate(updateConfigState, pCurve, getRadius(), isTrimInput, true/*adjustTweakedCurves*/, filletArc);
    if (err == eOk)
    {
        pInputCurveOut[0] = pCurve[0];
        pInputCurveOut[1] = pCurve[1];
        delete0.release();
        delete1.release();

        // If radius is 0.0, filletArc has center at the intersection, but 
        // we want to return a null arc that the caller expects in this case
        //
        if (getRadius() != 0.0) 
            filletArcOut = filletArc;
    }
    return err;
}


ErrorStatus AssocFilletActionBody::transformActionByOverride(const AcGeMatrix3d& trans)
{
    mFilletConfig.transformBy(trans);
    return eOk;
}


void AssocFilletActionBody::evaluateOverride()
{
    assertReadEnabled();

    AcDbAssocEvaluationCallback* const pEvalCallback = currentEvaluationCallback();

    if (pEvalCallback->evaluationMode() == kModifyActionAssocEvaluationMode)
    {
        // If the action is not satisfied, i.e. its evaluation would produce different
        // geometry than the current one, request the action to be erased
        //
        if (doesActionMatchCurrentGeometry())
        {
            setStatus(kIsUpToDateAssocStatus);

            // mFilletConfig needs to be updated. For example, after copy the referenced
            // geometries have been transformed, but contents of mFilletConfig has not 
            //
            AcGeCurve3d* pNewInputCurveUnused[2] = { nullptr, nullptr, }; 
            AcGeCircArc3d newFilletArcUnused;                            
            computeNewGeometry(true/*updateConfigState*/, pNewInputCurveUnused, newFilletArcUnused);
            delete pNewInputCurveUnused[0];
            delete pNewInputCurveUnused[1];
        }
        else
        {
            setStatus(kErasedAssocStatus);
        }
        return;
    }

    if (hasAnyErasedOrBrokenDependencies())
    {
        setStatus(kErasedAssocStatus); // Request the action to be erased
        eraseFilletArcEntity();        // Explicitly erase the AcDbArc entity controlled by this fillet action
        return;
    }

    // Regular evaluation calculates the new geometry of the fillet arc, 
    // if requested calculates the trimmed/extended input curves, and modifies
    // the referenced entities by setting new geoemtry to them

    evaluateDependencies();

    AcGeCurve3d* pNewInputCurve[2] = { nullptr, nullptr, };
    AcGeCircArc3d newFilletArc;
    ErrorStatus err = computeNewGeometry(true/*updateConfigState*/, pNewInputCurve, newFilletArc);

    std::unique_ptr<AcGeCurve3d> delete0(pNewInputCurve[0]);
    std::unique_ptr<AcGeCurve3d> delete1(pNewInputCurve[1]);
    if (err != eOk)
        goto Done;

    // Change the fillet AcDbArc, or erase it if the fillet radius is 0.0
    //
    if (getRadius() > 0.0)
    {
        if (getFilletArcId().isNull())
        {
            createFilletArcEntity();
        }

        // Notice that we are using AcDbAssocObjectPointer, not AcDb(Smart)ObjectPointer.
        // During dragging, it returns a temporary non-database-resident clone of 
        // the original entity, instead of the original database-resident entity.
        // The clone is then modified by our code and drawn by the dragger. 
        // The database-resident entity is only modified at the end of the 
        // dragging, on the last drag sample
        //
        AcDbAssocObjectPointer<AcDbArc> pFilletArc(getFilletArcId(), kForWrite);
        if (!eOkVerify(err = pFilletArc.openStatus())) // E.g. the arc entity is on a locked layer
            goto Done;
        if (!eOkVerify(err = pFilletArc->setFromAcGeCurve(newFilletArc)))
            goto Done;
    }
    else // radius == 0.0, no fillet arc
    {
        eraseFilletArcEntity();
    }

    // Adjust (trim/extend) the two input edges, if requested
    //
    for (int i = 0; i < 2; i++)
    {
        if (isTrimInputEdge(i))
        {
            AcDbObjectPointer<AcDbAssocEdgeActionParam> pInputEdgeParam(paramAtName(kInputEdgeParamName, i), kForWrite);
            if (eOkVerify(pInputEdgeParam.openStatus()))
            {
                // Notice that setEdgeSubentityGeometry() uses AcDbAssocObjectPointer 
                // to open the entity it is going to modify. While in the middle of 
                // dragging, it is going to be a non-database-resident clone of the
                // original entity
                //
                if (!eOkVerify(err = pInputEdgeParam->setEdgeSubentityGeometry(pNewInputCurve[i])))
                    goto Done;
            }
        }
    }

Done:
    if (err == eOk)
    {
        setStatus(kIsUpToDateAssocStatus);
    }
    else
    {
        AcDbObjectPointer<AcDbAssocAction> pAction(parentAction(), kForRead);
        currentEvaluationCallback()->setActionEvaluationErrorStatus(pAction, err);
        setStatus(kFailedToEvaluateAssocStatus);
    }
}


// If both input edges have been cloned, also request to clone the fillet action
// and the fillet AcDbArc entity
//
ErrorStatus AssocFilletActionBody::addMoreObjectsToDeepCloneOverride(
    AcDbIdMapping&     idMap, 
    AcDbObjectIdArray& additionalObjectsToClone) const
{
    for (int i = 0; i < 2; i++)
    {
        const AcDbEdgeRef inputEdge = getInputEdge(0);
        if (!idMap.compute(AcDbIdPair(inputEdge.entity().leafId(), AcDbObjectId::kNull, false)))
            return eOk; // Input entity not cloned, do not request the action to be cloned
    }

    additionalObjectsToClone.append(parentAction());
    additionalObjectsToClone.append(getFilletArcId());
    return eOk;
}


static AcDbObjectId mapId(const AcDbIdMapping& idMap, const AcDbObjectId& id)
{
    AcDbIdPair pair(id, AcDbObjectId::kNull, false);
    idMap.compute(pair);
    return pair.value();
}


static AcDbObjectId getBtrOfEntity(const AcDbObjectId entityId)
{
    AcDbObjectPointer<AcDbEntity> pEntity(entityId, kForRead);
    if (!eOkVerify(pEntity.openStatus()))
        return AcDbObjectId::kNull;
    return pEntity->ownerId();
}


// Move the cloned fillet AcDbArc entity to the BTR that also owns the first 
// cloned input edge entity
//
ErrorStatus AssocFilletActionBody::postProcessAfterDeepCloneOverride(AcDbIdMapping& idMap)
{
    if (getFilletArcId().isNull())
        return eOk; // 0.0 radius fillet. no fillet AcDbArc

    const AcDbObjectId clonedArcId          = mapId(idMap, getFilletArcId());
    const AcDbObjectId clonedInputEdgeId    = mapId(idMap, getInputEdge(0).entity().topId());
    const AcDbObjectId clonedInputEdgeBTRId = getBtrOfEntity(clonedInputEdgeId);

    if (getBtrOfEntity(clonedArcId) != clonedInputEdgeBTRId)
    {
        AcDbObjectPointer<AcDbBlockTableRecord> pDestinationBTR(clonedInputEdgeBTRId, kForWrite);
        if (!eOkVerify(pDestinationBTR.openStatus()))
            return eOk;
        AcDbObjectIdArray ids;
        ids.append(clonedArcId);
        eOkVerify(pDestinationBTR->assumeOwnershipOf(ids));
    }
    return eOk;
}


bool AssocFilletActionBody::doesActionMatchCurrentGeometry() const
{
    if (hasAnyErasedOrBrokenDependencies())
        return false;

    AcGeCurve3d* pNewInputCurve[2] = { nullptr, nullptr, };
    AcGeCircArc3d newFilletArc;
    if (const_cast<AssocFilletActionBody*>(this)->computeNewGeometry(false/*updateConfigState*/, pNewInputCurve, newFilletArc) != eOk)
        return false;
    std::unique_ptr<AcGeCurve3d> delete0(pNewInputCurve[0]);
    std::unique_ptr<AcGeCurve3d> delete1(pNewInputCurve[1]);
    if (pNewInputCurve[0] == nullptr || pNewInputCurve[1] == nullptr)
        return false;

    const AcGeCurve3d* pCurrentInputCurve[2] = { getInputCurve(0), getInputCurve(1), };
    const AcGeCircArc3d currentFilletArc = getFilletArcGeom();
    std::unique_ptr<const AcGeCurve3d> delete2(pCurrentInputCurve[0]);
    std::unique_ptr<const AcGeCurve3d> delete3(pCurrentInputCurve[1]);
    if (pCurrentInputCurve[0] == nullptr || pCurrentInputCurve[1] == nullptr)
        return false;

    AcGeTolSetter relaxedTol;

    return currentFilletArc.isEqualTo(newFilletArc)             &&
           pCurrentInputCurve[0]->isEqualTo(*pNewInputCurve[0]) && 
           pCurrentInputCurve[1]->isEqualTo(*pNewInputCurve[1]);
}


ErrorStatus AssocFilletActionBody::audit(AcDbAuditInfo* pAuditInfo)
{
    ErrorStatus err = __super::audit(pAuditInfo);
    if (err != eFixedAllErrors && err != eOk || pAuditInfo->auditPass() == AcDbAuditInfo::PASS1)
        return err;

    if (hasAnyErasedOrBrokenDependencies())
    {
        pAuditInfo->errorsFound(1);
        if (pAuditInfo->fixErrors())
        {
            // Erase the action but leave the fillet arc entity
            //
            AcDbObjectPointer<AcDbAssocAction> pFilletAction(parentAction(), kForWrite);
            if (eOkVerify(pFilletAction.openStatus()))
            {
                pFilletAction->erase();
                if (pAuditInfo != nullptr)
                    pAuditInfo->errorsFixed(1);
            }
            err = eFixedAllErrors;
        }
        else
        {
            err = eLeftErrorsUnfixed;
        }
    }
    return err;
}


ErrorStatus AssocFilletActionBody::createAndPostToDatabase(
    const AcDbEdgeRef  inputEdge[2],
    const bool         trimInputEdge[2],
    const AcString     trimInputEdgeExpression[2],
    const AcGePoint3d  pickPoint[2],
    double             radius,
    const AcString&    radiusExpression,
    AcDbObjectId&      createdActionIdOut)
{
    createdActionIdOut = AcDbObjectId::kNull;

    AcDbObjectId createdActionId, createdActionBodyId;

    ErrorStatus err = createActionAndActionBodyAndPostToDatabase(AssocFilletActionBody::desc(), 
                                                                 inputEdge[0].entity().topId(), 
                                                                 createdActionId, 
                                                                 createdActionBodyId);
    if (!eOkVerify(err))
        return err;

    AcDbObjectPointer<AssocFilletActionBody> pFilletActionBody(createdActionBodyId, kForWrite);
    if (!eOkVerify(pFilletActionBody.openStatus()))
        return pFilletActionBody.openStatus();

    AcDbObjectId paramId;
    int paramIndex = 0;
    for (int i = 0; i < 2; i++)
    {
        if (!eOkVerify(err = pFilletActionBody->addParam(kInputEdgeParamName, AcDbAssocEdgeActionParam::desc(), paramId, paramIndex)))
            goto Done;
        if (!eOkVerify(err = pFilletActionBody->setInputEdge(i, inputEdge[i])))
            goto Done;
        if (!eOkVerify(err = pFilletActionBody->setTrimInputEdge(i, trimInputEdge[i], trimInputEdgeExpression[i])))
            goto Done;
    }
    if (!eOkVerify(err = pFilletActionBody->createFilletArcEntity()))
        goto Done;
    if (!eOkVerify(err = pFilletActionBody->setRadius(radius, radiusExpression)))
        goto Done;

    pFilletActionBody->mFilletConfig.setPickPoints(pickPoint);

Done:
    if (err != eOk)
    {
        pFilletActionBody->eraseFilletArcEntity();

        // If setting parameters of the fillet action body failed, for example
        // because the provided expression was invalid, erase the action.
        // It will also erase all the owned objects, i.e. the action body, 
        // action parameters, and dependencies. Only the fillet AcDbArc entity
        // needs to be erased explicitly
        //
        AcDbObjectPointer<AcDbAssocAction> pAction(createdActionId, kForWrite);
        if (eOkVerify(pAction.openStatus()))
            pAction->erase();
    }
    else
    {
        // Set the output argument at the very end, after the operation succeeded
        //
        createdActionIdOut = createdActionId;
    }
    return err;
}


enum ObjectVersion
{
    kObjectVersion0       = 0,
    kCurrentObjectVersion = kObjectVersion0,
};


ErrorStatus AssocFilletActionBody::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    const ErrorStatus err = AcDbAssocActionBody::dwgOutFields(pFiler);
    if (!eOkVerify(err))
        return err;

    pFiler->writeUInt16((UInt16)kCurrentObjectVersion);
    pFiler->writeSoftPointerId(mFilletArcDepId); // The dependency is already hard owned by the action
    return mFilletConfig.dwgOutFields(pFiler);
}


ErrorStatus AssocFilletActionBody::dwgInFields(AcDbDwgFiler* pFiler)
{
    const ErrorStatus err = AcDbAssocActionBody::dwgInFields(pFiler);
    if (!eOkVerify(err))
        return err;

    UInt16 objVer = kCurrentObjectVersion;
    pFiler->readUInt16(&objVer);

    const ObjectVersion objectVersion = (ObjectVersion)objVer;

    if (objectVersion != kCurrentObjectVersion)
    {
        if (objectVersion > kCurrentObjectVersion)
        {
            ASSERT(!"Object version higher than the current version");
            return Acad::eMakeMeProxy;
        }
        else
        {
            // Read the data in the format of the previous version of the class
            // . . .
            //
            return Acad::eMakeMeProxy;
        }
    }
    pFiler->readSoftPointerId((AcDbSoftPointerId*)&mFilletArcDepId);
    return mFilletConfig.dwgInFields(pFiler);
}


#define ASSOCFILLET_CLASS _T("AssocFilletActionBody")

ErrorStatus AssocFilletActionBody::dxfOutFields(AcDbDxfFiler* pFiler) const
{
    ErrorStatus err = AcDbAssocActionBody::dxfOutFields(pFiler);
    if (!eOkVerify(err))
        return err;

    if (!eOkVerify(err = pFiler->writeItem(kDxfSubclass, ASSOCFILLET_CLASS)))
        return err;

    pFiler->writeUInt32(kDxfInt32, (UInt32)kCurrentObjectVersion);
    pFiler->writeObjectId(kDxfSoftPointerId, mFilletArcDepId);
    return mFilletConfig.dxfOutFields(pFiler);
}


ErrorStatus AssocFilletActionBody::dxfInFields(AcDbDxfFiler* pFiler)
{
    ErrorStatus err = AcDbAssocActionBody::dxfInFields(pFiler);
    if (!eOkVerify(err))
        return err;

    if (!pFiler->atSubclassData(ASSOCFILLET_CLASS))
        return pFiler->filerStatus();

    resbuf rb;
    if (!eOkVerify(err = pFiler->readResBuf(&rb)))
        return err;

    if (rb.restype != kDxfInt32)
    {
        pFiler->pushBackItem();
        return eInvalidDxfCode;
    }
    const ObjectVersion objectVersion = (ObjectVersion)rb.resval.rlong;

    if (objectVersion != kCurrentObjectVersion)
    {
        if (objectVersion > kCurrentObjectVersion)
        {
            ASSERT(!"Object version higher than the current version");
            return Acad::eMakeMeProxy;
        }
        else
        {
            // Read the data in the format of the previous version of the class
            // . . .
            //
            return Acad::eMakeMeProxy;
        }
    }

    if (!eOkVerify(err = pFiler->readResBuf(&rb)))
        return err;
    if (!VERIFY(rb.restype = kDxfSoftPointerId))
        return eInvalidResBuf;
    mFilletArcDepId.setFromOldId(rb.resval.mnLongPtr);

    return mFilletConfig.dxfInFields(pFiler);
}
