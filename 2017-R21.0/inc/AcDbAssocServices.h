//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            thisfile
//
// Description:     This and the accomanying cpp will be in core2d and exported. acdb will contain the corresponding imp class
//                  and set the host pointer.
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adesk.h"
#include "AdAChar.h"
#include "rxvaluetype.h"

#include "AcDbAssocGlobal.h"
#include <set>
#include "AcDbCore2dDefs.h"

class AcDbAssocFileReadPersIdsCollector;
class AcRxValue;
class AcViewport;
class AcDbBlockParameter;

class AcDbAssocStateHandle
{
protected:
    AcDbAssocStateHandle() {}
public:
    virtual ~AcDbAssocStateHandle() {};

    //nope
    AcDbAssocStateHandle(const AcDbAssocStateHandle&);
    void operator =(const AcDbAssocStateHandle&);
};

class IAcDbAssocHost
{
public:
    virtual Acad::ErrorStatus markSyncUpWithXrefsNeeded(AcDbDatabase* pDatabase) = 0;
    virtual void notifyAboutSourceAndDestinationBTR(const AcDbObjectId& sourceBTRId, const AcDbObjectId& destinationBTRId, bool cloneAllActions) = 0;

    virtual void processAfterFileRead(AcDbDatabase*, bool traverseWholeDatabase) = 0;
    virtual bool getObjectContainsConstraintGroups(AcDbObjectId btrId) = 0;
    virtual int getNumberOfConstraint(AcDbObjectId constraint2dGrpId) = 0;

    virtual AcRxClass* descAcDbBlockActionEntity() = 0;
    virtual AcRxClass* descAcDbAssocPersSubentIdPE() = 0;
    virtual AcRxClass* descAcDbBlockPropertiesTable() = 0;
    virtual AcRxClass* descAcDbBlockConstraintParameter() = 0;
    virtual AcRxClass* descAcDbBlockUserParameter() = 0;
    virtual AcRxClass* descAcDbAssocDependency() = 0;
    virtual AcRxClass* descAcDbAssocDependencyBody() = 0;
    virtual AcRxClass* descAcDbAssocAction() = 0;
    virtual AcRxClass* descAcDbAssocActionBody() = 0;
    virtual AcRxClass* descAcDbAssocExternalPersSubentIdHolder() = 0;
    virtual AcRxClass* descAcDbAssoc2dConstraintGroup() = 0;
    virtual AcRxClass* descAcDbAssocVariable() = 0;
    virtual AcRxClass* descAcDbAssocArrayParameters() = 0;

    virtual void getAllDimConstrObjectsInDatabase(AcDbDatabase *pDatabase, AcDbObjectIdArray &dimConstrObjectIds) = 0;

    virtual Acad::ErrorStatus persSubentIdPeGetAllSubentities(const AcDbEntity*      pEntity,
                                                            AcDb::SubentType       subentType,
                                                            AcArray<AcDbSubentId>& allSubentIds) = 0;

    virtual Acad::ErrorStatus persSubentIdPeGetEdgeSubentityGeometry(const AcDbEntity*   pEntity,
                                                                   const AcDbSubentId& edgeSubentId,
                                                                   AcGeCurve3d*&       pEdgeCurve) = 0;

    virtual bool isArrayEditDisallowed(AcDbObjectId objId) = 0;

    virtual AcDbAssocStateHandle* newActionEvaluationInProgressSetter(AcDbDatabase*, const AcDbObjectId& actionId, AcDbAssocEvaluationCallback*) = 0;
    virtual AcDbAssocStateHandle* newIsPerformingDeepCloning() = 0;
    virtual AcDbAssocStateHandle* newDeepCloningInsertStarContextNotifier() = 0;
    
    virtual AcDbAssocStateHandle* newDependencyNotificationDisabler(bool disable = true) = 0;
    virtual AcDbAssocStateHandle* newDeepCloningDisable() = 0;
    virtual AcDbAssocStateHandle* newPersSubentManagerReactorDeepCloningDisabler() = 0;
    virtual AcDbAssocStateHandle* newEvaluationCallbackSetter(AcDbDatabase* pDb) = 0;
    virtual AcDbAssocStateHandle* newTransformByNotifier(AcDbEntity* pEnt, const AcGeMatrix3d& mat) = 0;
    virtual AcDbAssocStateHandle* newNetworkEvaluationDisabler(AcDbDatabase* pDb) = 0;
    virtual AcDbAssocStateHandle* newRollbackOnErrorUtil(Acad::ErrorStatus& es) = 0;

    virtual AcDbObjectId networkGetInstanceFromObject(const AcDbObjectId& owningObjectId,
                                              bool                createIfDoesNotExist,
                                              bool                addToTopLevelNetwork = true,
                                              const AcString&     dictionaryKey        = ACRX_T("")) = 0;

    virtual bool hasConstraints(AcDbObjectId id) = 0;

    //AcDbBlockAuthEntityUtil
    virtual double getGripScale(double nPixels) = 0;
    virtual AcViewport* getAcViewportPtr() = 0;

    virtual bool handleEntityAttachmentPointMoved( AcDbObjectId dimDepBodyId,
                                                const AcArray<AcGeCurve3d*>& newCurves,
                                                const double measurement ) = 0;
    virtual bool handleEntityAttachmentPointMoved( AcDbObjectId dimDepBodyId,
                                                  const AcArray<AcGePoint3d>& points,
                                                  const double measurement ) = 0;

    virtual bool hasAssocNetwork(AcDbDatabase* pDb) = 0;
    virtual bool hasNamedObjects(AcDbDatabase* pDb) = 0;
    virtual bool hasManager(AcDbDatabase* pDb) = 0;

    virtual void deepCloningNotifyAboutTransform( const AcGeMatrix3d& mat, 
                                                  const std::set<AcDbObjectId>* pOrigActionsForTransform,
                                                  const std::set<AcDbObjectId>* pClonedActionsForTransform ) = 0;
    virtual void deepCloningNotifyAboutEntitiesInBTRTransformedAfterClone(const AcDbObjectId& BTRCloneId, const AcGeMatrix3d& transf) = 0;
    virtual void deepCloningNotifyAboutSourceAndDestinationBTR( const AcDbObjectId& sourceBTRId, 
                                                                const AcDbObjectId& destBTRId,
                                                                bool                cloneAllActions ) = 0;
    virtual Acad::ErrorStatus networkRemoveInstanceFromObject( const AcDbObjectId& owningObjectId,
                                                               bool                alsoEraseIt,
                                                               const AcString&     dictionaryKey = ACRX_T("") ) = 0;

    virtual void deepCloningCollectActionsReferencingObject( const AcDbObjectId&     origObjId, 
                                                             const AcDbObjectId&     clonedObjId,
                                                             const AcDbIdMapping&    idMap,
                                                             std::set<AcDbObjectId>& allClonedActionsSet ) = 0;
    virtual void cleanup() = 0;
    virtual double getAdjustedLength(double dLength) = 0;
    virtual Acad::ErrorStatus getAssocAnnotationActionBodyFromDim(const AcDbObjectId& idDim, AcDbObjectId& idActionBody) = 0;
    virtual int dimGetAnnotationPointRefCount(const AcDbObject* pDimActionBody) = 0;
    //virtual void dynBlockAssocCallbackCacheBlockRefContext(AcDbBlockReference* const pBlockRef) = 0;
    virtual bool dynBlockAssocCallbackCacheAndDisableBlockRefHandling(AcDbDatabase* pDb, AcDbBlockReference* const pBlockRef) = 0;
    virtual void dynBlockAssocCallbackEnableBlockReferenceHandling(AcDbDatabase* pDb, AcDbBlockReference* const pBlockRef) = 0;

    virtual void detachPersistentReactorsBeforeChangeOfBTR(AcDbBlockReference* pBlockRef) = 0;
    virtual void reattachPersistentReactorsAfterChangeOfBTR(AcDbBlockReference* pBlockRef) = 0;
    virtual bool evaluateTopLevelNetwork(AcDbDatabase*                pDatabase,
                                    AcDbAssocEvaluationCallback* pCallback     = NULL, 
                                    int                          callbackOrder = 0) = 0;

    virtual Acad::ErrorStatus transformActionBy(AcDbObjectId id, const AcGeMatrix3d& transfMatrix) = 0;
    virtual bool isEquivalentWith(const AcDbObject* pThis, const AcDbObject* pOther, AcRxObject* pContext) = 0;
    virtual void notifyAboutExplicitlyMappedObject(const AcDbObjectId& sourceObjId, const AcDbObjectId& destinationObjId) = 0;
    virtual bool dimDependencyBodyGetSectorType(AcDbObjectId dimDepBodyId, int& sectorType) = 0;
    virtual bool isTrackingExternalObjectChanges(const AcDbObject* pObject) = 0;
    virtual GUID getExternalObjectRevisionGuid(const AcDbObject* pObject) = 0;
    virtual Acad::ErrorStatus enableExternalObjectChangeTracking(AcDbObject* pObject, bool yesNo) = 0;
    virtual void getAssocMLeaderLineIndices(AcDbEntity* pEnt, AcArray<int>& assocMLeaderLines) = 0;
    virtual Acad::ErrorStatus notifyDependenciesOnObject(const AcDbObject* pObject, AcDbAssocStatus newStatus) = 0;
    virtual void notifyAboutExplicitlyClonedEntities(const AcDbObjectIdArray& sourceEntityIds, const AcDbObjectId& destinationBTRId) = 0;
    virtual void notifyAboutDeepClonedObject(AcDbObject* pOrigObject, AcDbIdMapping&, bool isDeepCloning) = 0;
    virtual Acad::ErrorStatus recomposeAfterFileRead(AcDbDatabase*) = 0;
    virtual Acad::ErrorStatus fileReadCompleted(AcDbDatabase*, bool purgeUnusedIds) = 0;
    virtual Acad::ErrorStatus getAssociatedDimensionForEntity(const AcDbObjectId &objectId, AcDbObjectIdArray &dimensions) = 0;
    virtual void registerDeepCloneRxEventReactor(AcDbIdMapping&) = 0;
    virtual AcDbAssocFileReadPersIdsCollector* newAcDbAssocFileReadPersIdsCollector() = 0;
    virtual void deleteAcDbAssocFileReadPersIdsCollector(AcDbAssocFileReadPersIdsCollector*& p) = 0;
    virtual Acad::ErrorStatus dimDependencyBodyGetFromEntity(AcDbObjectId dimId, AcDbObjectId& dimDepBodyId) = 0;
    virtual bool dimDependencyBodyIsConstraintActive(AcDbObjectId dimId) = 0;
    virtual bool isDimconstraintReferencedInExpressions(AcDbObjectId dimDepBodyId) = 0;
    virtual Acad::ErrorStatus dimDependencyBodySetIsReferenceOnly(AcDbObjectId dimDepBodyId, bool yesNo) = 0;
    virtual Acad::ErrorStatus dimDependencyBodyGetVariableNameAndExpression(AcDbObjectId dimDepBodyId, AcString& name, AcString& expression, AcString& value) = 0;
    virtual Acad::ErrorStatus dimDependencyBodySetAssocVariableNameAndExpression(AcDbObjectId dimDepBodyId, AcString& strToValidate) = 0;
    virtual Acad::ErrorStatus dimDependencyBodyGetVariableDescription(AcDbObjectId dimDepBodyId, AcString& strDesc) = 0;
    virtual Acad::ErrorStatus dimDependencyBodySetVariableDescription(AcDbObjectId dimDepBodyId, const AcString& strDesc) = 0;
    virtual AcDbObjectId traverseToObjectAtPathName(const AcDbObjectId& contextId, const AcString& pathName, AcString& propertyName, AcString* pCanonicalPathName = NULL) = 0;
    virtual Acad::ErrorStatus getObjectName(const AcDbObjectId& objectId, AcString& objectName) = 0;
    virtual bool isValidPointRefActionParam(const AcDbObjectId& ptRefId) = 0;
    virtual Acad::ErrorStatus dimDependencyBodySetVariableExpression(AcDbObjectId dimDepBodyId, const AcString& newExpression) = 0;
    virtual Acad::ErrorStatus getFacets(AcDbBlockReference* pReference, AcArray<const AcRxClass*>& facets) = 0;
    virtual void queueDynamicConstraintsForRegen(AcDbDatabase* pDatabase) = 0;
    virtual bool getBlockFlippedStateLabel(AcDbBlockParameter* pBlockParam, int flipParameter, AcString& sValue) = 0;
    virtual Acad::ErrorStatus getDependencyIdsFromConstraintVariable(const AcDbDimension* pDim, AcDbObjectIdArray& ids) = 0;
    virtual bool isPerformingDeepCloning() = 0;
    virtual Acad::ErrorStatus dimUpdateDependentOnObjectOverride(AcDbObjectId dimDepBodyId) = 0;
    virtual void dimDependencyDragStatus(AcDbObjectId dimId, const AcDb::DragStat status) = 0;
    virtual bool drawReferenceEntities(AcGiWorldDraw *pDraw, AcDbObjectIdArray& entityReferenceEntityIds) = 0;
    virtual void dimListConstraintData(const AcDbDimension* pDim) = 0;
    virtual bool isConstraintDynamic(const AcDbObject* pObj) = 0;
    virtual bool isConstraintDynamic(AcDbObjectId id) = 0;
    virtual bool isConstraintReady(AcDbObjectId id) = 0;
    virtual int dimConstraintNameFormat(AcDbObjectId id) = 0;
    virtual bool dimIsConstraintObject(AcDbObjectId id) = 0;
    virtual bool dimGetConstraintValue(AcDbObjectId id, double& value) = 0;
    virtual bool dimIsConstraintObject(AcDbObjectId id, bool &hasExpression, bool &isReferenceConstraint) = 0;
    virtual Acad::ErrorStatus getDynamicConstraintLayer(AcDbObjectId &layerId, bool bCreateIfNotFound, AcDbDatabase* pDatabase) = 0;
    virtual Acad::ErrorStatus arrayCommonParametersBaseProperty_subGetValue(const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayCommonParametersBaseProperty_subSetValue(AcRxObject* pO, const AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayCommonParametersTypePropertyBase_subGetValue(const AcRxObject* pOwner, const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayPathParametersLengthPropertyBase_subGetValue(const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayPolarParametersCenterPropertyBase_subGetValue(const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayPolarParametersCenterPropertyBase_subSetValue(AcRxObject* pO, const AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayParameterTotalSpanPropertyBase_subGetValue(const AcString& name, const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayParameterTotalSpanPropertyBase_subSetValue(const AcString& name, AcRxObject* pO, const AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayParameterValueParamPropertyBase_subGetValue(const AcString& name, const AcRxValueType& type, const AcRxObject* pO, AcRxValue& value) = 0;
    virtual Acad::ErrorStatus arrayParameterValueParamPropertyBase_subSetValue(const AcString& name, const AcRxValueType& type, const AcRxObject* pO, const AcRxValue& value) = 0;
    virtual bool conditionAcDbBlockReferenceIsArray(const AcRxObject* pO, int& arrayType) = 0;
    virtual AcString arrayExpressionPropertyBase_expression(const AcRxObject* pO, const AcString& valueParamName) = 0;
    virtual bool curve_isTransformingBackupEntity(AcDbEntity* pEnt) = 0;
    virtual Acad::ErrorStatus getNetworkParamIds(AcDbObjectId btrId, AcDbObjectIdArray& networkParamIds) = 0;

    virtual bool isGeomDependencyReadOnly(const AcDbObjectId& dimObjId) = 0;
};


class AcDbAssocServices
{
    static IAcDbAssocHost* mpHost;

    static IAcDbAssocHost* host();

public:
    ACDBCORE2D_PORT static void setHost(IAcDbAssocHost* pHost);

public:

    //AcDbAssocManager
    static Acad::ErrorStatus markSyncUpWithXrefsNeeded(AcDbDatabase* pDatabase);
    static void notifyAboutSourceAndDestinationBTR(const AcDbObjectId& sourceBTRId, const AcDbObjectId& destinationBTRId, bool cloneAllActions);


    static void processAfterFileRead(AcDbDatabase*, bool traverseWholeDatabase);

    static bool getObjectContainsConstraintGroups(AcDbObjectId btrId);
    static int getNumberOfConstraint(AcDbObjectId constraint2dGrpId);

    static AcRxClass* descAcDbBlockActionEntity();
    static AcRxClass* descAcDbAssocPersSubentIdPE();
    static AcRxClass* descAcDbBlockPropertiesTable();
    static AcRxClass* descAcDbBlockConstraintParameter();
    static AcRxClass* descAcDbBlockUserParameter();
    static AcRxClass* descAcDbAssocDependency();
    static AcRxClass* descAcDbAssocDependencyBody();
    static AcRxClass* descAcDbAssocAction();
    static AcRxClass* descAcDbAssocActionBody();
    static AcRxClass* descAcDbAssocExternalPersSubentIdHolder();
    static AcRxClass* descAcDbAssoc2dConstraintGroup();
    static AcRxClass* descAcDbAssocVariable();
    static AcRxClass* descAcDbAssocArrayParameters();

    static void getAllDimConstrObjectsInDatabase(AcDbDatabase *pDatabase, AcDbObjectIdArray &dimConstrObjectIds);

    static Acad::ErrorStatus persSubentIdPeGetAllSubentities(const AcDbEntity*      pEntity,
                                                            AcDb::SubentType       subentType,
                                                            AcArray<AcDbSubentId>& allSubentIds);

    static Acad::ErrorStatus persSubentIdPeGetEdgeSubentityGeometry(const AcDbEntity*   pEntity,
                                                                   const AcDbSubentId& edgeSubentId,
                                                                   AcGeCurve3d*&       pEdgeCurve);

    static bool isArrayEditDisallowed(AcDbObjectId objId);


    static AcDbAssocStateHandle* newActionEvaluationInProgressSetter(AcDbDatabase*, const AcDbObjectId& actionId, AcDbAssocEvaluationCallback*);
    static AcDbAssocStateHandle* newIsPerformingDeepCloning();
    static AcDbAssocStateHandle* newDeepCloningInsertStarContextNotifier();
    ACDBCORE2D_PORT static AcDbAssocStateHandle* newDependencyNotificationDisabler(bool disable = true);
    static AcDbAssocStateHandle* newDeepCloningDisable();
    static AcDbAssocStateHandle* newPersSubentManagerReactorDeepCloningDisabler();
    static AcDbAssocStateHandle* newEvaluationCallbackSetter(AcDbDatabase* pDb);
    static AcDbAssocStateHandle* newTransformByNotifier(AcDbEntity* pEnt, const AcGeMatrix3d& mat);
    static AcDbAssocStateHandle* newNetworkEvaluationDisabler(AcDbDatabase* pDb);

    static AcDbObjectId networkGetInstanceFromObject(const AcDbObjectId& owningObjectId,
                                              bool                createIfDoesNotExist,
                                              bool                addToTopLevelNetwork = true,
                                              const AcString&     dictionaryKey        = ACRX_T(""));

    static bool hasConstraints(AcDbObjectId id);
    static double getGripScale(double nPixels);
    static AcViewport* getAcViewportPtr();

    static bool handleEntityAttachmentPointMoved( AcDbObjectId dimDepBodyId,
                                                  const AcArray<AcGeCurve3d*>& newCurves,
                                                  const double measurement );

    static bool handleEntityAttachmentPointMoved( AcDbObjectId dimDepBodyId,
                                                  const AcArray<AcGePoint3d>& points,
                                                  const double measurement );
    
    static bool hasAssocNetwork(AcDbDatabase* pDb); //AcDbAssocManager::
    static bool hasNamedObjects(AcDbDatabase* pDb); //AcDbAssocNamespace::
    static bool hasManager(AcDbDatabase* pDb);      //AcDbAssocPersSubentManager::
    static void deepCloningNotifyAboutTransform( const AcGeMatrix3d& mat, 
                                                 const std::set<AcDbObjectId>* pOrigActionsForTransform,
                                                 const std::set<AcDbObjectId>* pClonedActionsForTransform );
    static void deepCloningNotifyAboutEntitiesInBTRTransformedAfterClone(const AcDbObjectId& BTRCloneId, const AcGeMatrix3d& transf);
    static void deepCloningNotifyAboutSourceAndDestinationBTR( const AcDbObjectId& sourceBTRId, 
                                                               const AcDbObjectId& destBTRId,
                                                               bool                cloneAllActions );
    static Acad::ErrorStatus networkRemoveInstanceFromObject( const AcDbObjectId& owningObjectId,
                                                              bool                alsoEraseIt,
                                                              const AcString&     dictionaryKey = ACRX_T(""));

    static void deepCloningCollectActionsReferencingObject( const AcDbObjectId&     origObjId, 
                                                            const AcDbObjectId&     clonedObjId,
                                                            const AcDbIdMapping&    idMap,
                                                            std::set<AcDbObjectId>& allClonedActionsSet );
    static void cleanup();
    static double getAdjustedLength(double dLength);
    static Acad::ErrorStatus getAssocAnnotationActionBodyFromDim(const AcDbObjectId& idDim, AcDbObjectId& idActionBody);
    static int dimGetAnnotationPointRefCount(const AcDbObject* pDimActionBody);

    //static void dynBlockAssocCallbackCacheBlockRefContext(AcDbBlockReference* const pBlockRef);
    static bool dynBlockAssocCallbackCacheAndDisableBlockRefHandling(AcDbDatabase* pDb, AcDbBlockReference* const pBlockRef);
    static void dynBlockAssocCallbackEnableBlockReferenceHandling(AcDbDatabase* pDb, AcDbBlockReference* const pBlockRef);

    static void detachPersistentReactorsBeforeChangeOfBTR(AcDbBlockReference* pBlockRef); 
    static void reattachPersistentReactorsAfterChangeOfBTR(AcDbBlockReference* pBlockRef); 

    static bool evaluateTopLevelNetwork(AcDbDatabase*                pDatabase,
                                    AcDbAssocEvaluationCallback* pCallback     = NULL, 
                                    int                          callbackOrder = 0);

    static Acad::ErrorStatus transformActionBy(AcDbObjectId id, const AcGeMatrix3d& transfMatrix);

    static bool isEquivalentWith(const AcDbObject* pThis, const AcDbObject* pOther, AcRxObject* pContext);
    static void notifyAboutExplicitlyMappedObject(const AcDbObjectId& sourceObjId, const AcDbObjectId& destinationObjId);
    static bool dimDependencyBodyGetSectorType(AcDbObjectId dimDepBodyId, int& sectorType);
    static bool isTrackingExternalObjectChanges(const AcDbObject* pObject);
    static GUID getExternalObjectRevisionGuid(const AcDbObject* pObject);
    static Acad::ErrorStatus enableExternalObjectChangeTracking(AcDbObject* pObject, bool yesNo);
    static void getAssocMLeaderLineIndices(AcDbEntity* pEnt, AcArray<int>& assocMLeaderLines);
    static Acad::ErrorStatus notifyDependenciesOnObject(const AcDbObject* pObject, AcDbAssocStatus   newStatus);
    static void notifyAboutExplicitlyClonedEntities(const AcDbObjectIdArray& sourceEntityIds, const AcDbObjectId& destinationBTRId);
    static void notifyAboutDeepClonedObject(AcDbObject* pOrigObject, AcDbIdMapping&, bool isDeepCloning);
    static Acad::ErrorStatus recomposeAfterFileRead(AcDbDatabase*);
    static Acad::ErrorStatus fileReadCompleted(AcDbDatabase*, bool purgeUnusedIds);
    static Acad::ErrorStatus getAssociatedDimensionForEntity(const AcDbObjectId &objectId, AcDbObjectIdArray &dimensions);
    static void registerDeepCloneRxEventReactor(AcDbIdMapping&);
    static AcDbAssocFileReadPersIdsCollector* newAcDbAssocFileReadPersIdsCollector();
    static void deleteAcDbAssocFileReadPersIdsCollector(AcDbAssocFileReadPersIdsCollector*& p);
    static Acad::ErrorStatus dimDependencyBodyGetFromEntity(AcDbObjectId dimId, AcDbObjectId& dimDepBodyId);
    static bool dimDependencyBodyIsConstraintActive(AcDbObjectId dimDepBodyId);
    static bool isDimconstraintReferencedInExpressions(AcDbObjectId dimDepBodyId);
    static Acad::ErrorStatus dimDependencyBodySetIsReferenceOnly(AcDbObjectId dimDepBodyId, bool yesNo);
    static Acad::ErrorStatus dimDependencyBodyGetVariableNameAndExpression(AcDbObjectId dimDepBodyId, AcString& name, AcString& expression, AcString& value);
    static Acad::ErrorStatus dimDependencyBodySetAssocVariableNameAndExpression(AcDbObjectId dimDepBodyId, AcString& strToValidate);
    static Acad::ErrorStatus dimDependencyBodyGetVariableDescription(AcDbObjectId dimDepBodyId, AcString& strDesc);
    static Acad::ErrorStatus dimDependencyBodySetVariableDescription(AcDbObjectId dimDepBodyId, const AcString& strDesc);
    static AcDbObjectId traverseToObjectAtPathName(const AcDbObjectId& contextId, const AcString& pathName, AcString& propertyName, AcString* pCanonicalPathName = NULL);
    static Acad::ErrorStatus getObjectName(const AcDbObjectId& objectId, AcString& objectName);
    static bool isValidPointRefActionParam(const AcDbObjectId& ptRefId);
    static Acad::ErrorStatus dimDependencyBodySetVariableExpression(AcDbObjectId dimDepBodyId, const AcString& newExpression);
    static Acad::ErrorStatus getFacets(AcDbBlockReference* pReference, AcArray<const AcRxClass*>& facets);
    static void queueDynamicConstraintsForRegen(AcDbDatabase* pDatabase);
    static bool getBlockFlippedStateLabel(AcDbBlockParameter* pBlockParam, int flipParameter, AcString& sValue);
    static Acad::ErrorStatus getDependencyIdsFromConstraintVariable(const AcDbDimension* pDim, AcDbObjectIdArray& ids);
    static bool isPerformingDeepCloning();
    static Acad::ErrorStatus dimUpdateDependentOnObjectOverride(AcDbObjectId dimDepBodyId);
    static void dimDependencyDragStatus(AcDbObjectId dimId, const AcDb::DragStat status);
    static bool drawReferenceEntities(AcGiWorldDraw *pDraw, AcDbObjectIdArray& entityReferenceEntityIds);
    static void dimListConstraintData(const AcDbDimension* pDim);
    static bool isConstraintDynamic(const AcDbObject* pObj);
    static bool isConstraintDynamic(AcDbObjectId id);
    static bool isConstraintReady(AcDbObjectId id);
    static int dimConstraintNameFormat(AcDbObjectId id);
    static bool dimIsConstraintObject(AcDbObjectId id);
    static bool dimGetConstraintValue(AcDbObjectId id, double& value);
    static bool dimIsConstraintObject(AcDbObjectId id, bool &hasExpression, bool &isReferenceConstraint);
    static Acad::ErrorStatus arrayCommonParametersBaseProperty_subGetValue(const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayCommonParametersBaseProperty_subSetValue(AcRxObject* pO, const AcRxValue& value);
    static Acad::ErrorStatus arrayCommonParametersTypePropertyBase_subGetValue(const AcRxObject* pOwner, const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayPathParametersLengthPropertyBase_subGetValue(const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayPolarParametersCenterPropertyBase_subGetValue(const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayPolarParametersCenterPropertyBase_subSetValue(AcRxObject* pO, const AcRxValue& value);
    static Acad::ErrorStatus arrayParameterTotalSpanPropertyBase_subGetValue(const AcString& name, const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayParameterTotalSpanPropertyBase_subSetValue(const AcString& name, AcRxObject* pO, const AcRxValue& value);
    static Acad::ErrorStatus arrayParameterValueParamPropertyBase_subGetValue(const AcString& name, const AcRxValueType& type, const AcRxObject* pO, AcRxValue& value);
    static Acad::ErrorStatus arrayParameterValueParamPropertyBase_subSetValue(const AcString& name, const AcRxValueType& type, const AcRxObject* pO, const AcRxValue& value);
    static bool conditionAcDbBlockReferenceIsArray(const AcRxObject* pO, int& arrayType);
    static AcString arrayExpressionPropertyBase_expression(const AcRxObject* pO, const AcString& valueParamName);
    static bool curve_isTransformingBackupEntity(AcDbEntity* pEnt);
    static Acad::ErrorStatus getNetworkParamIds(AcDbObjectId btrId, AcDbObjectIdArray& networkParamIds);
    static AcDbAssocStateHandle* newRollbackOnErrorUtil(Acad::ErrorStatus& es);
    static Acad::ErrorStatus getDynamicConstraintLayer(AcDbObjectId &layerId, bool bCreateIfNotFound, AcDbDatabase* pDatabase);

    static bool isGeomDependencyReadOnly(const AcDbObjectId& dimObjId);
};


/// <summary> This enum describes dimensional constraint type. </summary>
///
enum AcDbAssocConstraintType
{
    /// <summary> None Associate Constraint </summary>
    kNoneAssocConstraintType = 0,
    /// <summary> Distance Associate Constraint </summary>
    kDistanceAssocConstraintType,
    /// <summary> Horizontal Distance Associate Constraint </summary>
    kHorizontalDistanceAssocConstraintType,
    /// <summary> Vertical Distance Associate Constraint </summary>
    kVerticalDistanceAssocConstraintType,
    /// <summary> AcAngleConstraint::kParallelAntiClockwise Associate Constraint </summary>
    kAngle0AssocConstraintType, 
    /// <summary> AcAngleConstraint::kAntiParallelClockwise Associate Constraint </summary>
    kAngle1AssocConstraintType,
    /// <summary> AcAngleConstraint::kParallelClockwise Associate Constraint </summary>
    kAngle2AssocConstraintType,
    /// <summary> AcAngleConstraint::kAntiParallelAntiClockwise Associate Constraint </summary>
    kAngle3AssocConstraintType,
    /// <summary> Radius Associate Constraint </summary>
    kRadiusAssocConstraintType,
    /// <summary> Diameter Associate Constraint </summary>
    kDiameterAssocConstraintType,
};
