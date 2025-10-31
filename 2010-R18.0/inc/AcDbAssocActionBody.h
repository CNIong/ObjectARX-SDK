
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
// CREATED BY: Jiri Kripac                                 August 2007
//
// DESCRIPTION:
//
// AcDbAssocActionBody abstract base class for deriving custom action body
// classes.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocAction.h"
#pragma pack (push, 8)


/// <summary> <para>
/// Abstract base class for deriving custom action body classes that implement
/// functionality of custom actions.
/// </para> <para>
/// An object of a class derived from the AcDbAssocActionBody class is always 
/// owned by a parent AcDbAssocAction object. The AcDbAssocAction object has 
/// an AcDbHardOwnershipId on it and the AcDbAssocActionBody::ownerId() of the 
/// object returns the AcDbObjectId of its parent AcDbAssocAction object. 
/// </para> <para>
/// Therefore a custom action object (in the logical sense of the word "object") 
/// is always represented by a pair of physical AcDbObjects: 
///
///  - The parent action object of the AcDbAssocAction class (or possibly, but
///    less commonly, of a derived class).
///  - The action body object of a custom class derived from the 
///    AcDbAssocActionBody abstract base class.
///
/// </para> <para>
/// This factoring out of the functionality of the custom actions into separate 
/// classes derived from the AcDbAssocActionBody class, instead of deriving the 
/// custom action classes directly from the AcDbAssocAction class, allows
/// better handling of the situations when the application code that implements 
/// the custom action behavior is not available. Only the custom object of the
/// AcDbAssocActionBody-derived class will become a proxy, but its parent 
/// AcDbAssocAction object will always be available and the associative mechanism
/// can still function to some extent.
/// </para> <para>
/// The abstract AcDbAssocActionBody base class defines a set of virtual methods 
/// named xxxxxxOverride() that correspond to methods named xxxxxx() in the parent
/// AcDbAssocAction class. When a method xxxxxx() is called on the parent action 
/// object and the action object owns an action body object, the corresponding 
/// xxxxxxOverride() method on the action body object is called and it either 
/// supersedes or amends the default xxxxxx() implementation, depending on the 
/// particular method. 
/// </para> <para>
/// If the action object does not own an action body object or if the action 
/// body object does not override the xxxxxxOverride() method, the default
/// implementation in the parent action object is performed. Also, when the 
/// custom action body object becomes a proxy because its application code
/// is not available, the parent action method just performs its default 
/// implementation.
/// </para> <para>
/// Custom action body classes derived from the AcDbAssocActionBody class 
/// implement their behavior by overriding the appropriate xxxxxxOverride() 
/// methods. Only the evaluateOverride() method must always be overridden in 
/// the custom classes. If not overridden, the other xxxxxxOverride() methods 
/// will do nothing and the default implementation in the parent AcDbAssocAction 
/// object will be performed. This may be the appropriate behavior in most cases.
/// </para> <para>
/// The custom action body classes also need to serialize their data. When 
/// serializing AcDbObjectIds of the AcDbAssocDependencies, these should be 
/// serialized as AcDbHardPointerIds, not as AcDbHardOwnershipIds, because the 
/// AcDbAssocDependencies are owned (in the AutoCAD database sense) by the 
/// parent AcDbAssocAction object, not by the custom action body object. 
/// </para> <para>
/// Because each AcDbAssocActionBody object is owned by its parent 
/// AcDbAssocAction object, erasing the parent AcDbAssocAction object also 
/// erases the owned AcDbAssocActionBody object. There is no need to erase
/// AcDbAssocActionBody objects explicitly.
/// </para> </summary> 
///
class ACDB_PORT AcDbAssocActionBody : public AcDbObject
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocActionBody);

    explicit AcDbAssocActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);
    virtual ~AcDbAssocActionBody();

    /// <summary>
    /// Returns AcDbObjectId of the parent AcDbAssocAction that owns this 
    /// action body object.
    /// </summary>
    ///
    AcDbObjectId parentAction() const { return ownerId(); }

    // The following non-virtual methods are just shortcuts that just forward 
    // to the parent AcDbAssocAction class, to save some typing for the
    // implementers of the derived custom action body classes

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbAssocStatus status() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool            notifyOwningNetwork = true,
                                bool            setInOwnedActions   = false);

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbObjectId owningNetwork() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus getDependencies(bool readDependenciesWanted, 
                                      bool writeDependenciesWanted,
                                      AcDbObjectIdArray& dependencyIds) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus addDependency(const AcDbObjectId& dependencyId, 
                                    bool                setThisActionAsOwningAction = true); 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeDependency(const AcDbObjectId& dependencyId, 
                                       bool                alsoEraseIt);

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeAllDependencies(bool alsoEraseThem);

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus evaluateDependencies();

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    bool isActionEvaluationInProgress() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbAssocEvaluationCallback* currentEvaluationCallback() const;

public: 
    
    // Virtual methods that can be overridden by the derived classes

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. This method has to be overridden and
    /// this is how the behavior of custom actions is implemented.
    /// </summary>
    ///
    virtual void evaluateOverride() = NULL;

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    Acad::ErrorStatus getDependenciesOverride(bool readDependenciesWanted, 
                                              bool writeDependenciesWanted,
                                              AcDbObjectIdArray& dependencyIds) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    Acad::ErrorStatus getDependentObjectsOverride(bool readDependenciesWanted,
                                                  bool writeDependenciesWanted,
                                                  AcDbObjectIdArray& objectIds) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus removeAllDependenciesOverride(bool alsoEraseThem)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isOwnedDependencyOverride(const AcDbAssocDependency* pDependency, 
                                                        bool& isOwnedDependency) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isExternalDependencyOverride(const AcDbAssocDependency* pDependency, 
                                                           bool& isExternalDependency) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus hasDependencyCachedValueOverride(const AcDbAssocDependency* pDependency,
                                                               bool& hasDepCachedValue) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isRelevantDependencyChangeOverride(const AcDbAssocDependency* pDependency,
                                                                 bool& isRelevantDepChange) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus areDependenciesOnTheSameThingOverride(const AcDbAssocDependency* pDependency1,
                                                                    const AcDbAssocDependency* pDependency2,
                                                                    bool& areDependentOnSameThing) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus areDependenciesEqualOverride(const AcDbAssocDependency* pDependency1,
                                                           const AcDbAssocDependency* pDependency2,
                                                           bool& areEqual) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateDependencyOverride(AcDbAssocDependency* pDependency)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus dependentObjectClonedOverride(const AcDbAssocDependency* pDependency, 
                                                            const AcDbObject*          pDbObj, 
                                                            const AcDbObject*          pNewObj)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus addMoreObjectsToDeepCloneOverride(AcDbIdMapping& idMap, 
                                                                AcDbObjectIdArray& additionalObjectsToClone) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus postProcessAfterDeepCloneOverride(AcDbIdMapping& idMap) 
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus postProcessAfterDeepCloneCancelOverride(AcDbIdMapping& idMap)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus ownedDependencyStatusChangedOverride(AcDbAssocDependency* pOwnedDependency, 
                                                                   AcDbAssocStatus      previousStatus)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isEqualToOverride(const AcDbAssocAction* pOtherAction, bool& isEqual) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluationPriorityOverride(AcDbAssocEvaluationPriority& priority) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus getDependentActionsToEvaluateOverride(AcDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus transformActionByOverride(const AcGeMatrix3d&)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus dragStatusOverride(const AcDb::DragStat status)
    { return Acad::eNotImplemented; }

}; // class AcDbAssocActionBody


#pragma pack (pop)

