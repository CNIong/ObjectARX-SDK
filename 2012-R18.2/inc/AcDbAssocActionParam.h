// 
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2009-2011 by Autodesk, Inc. 
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
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)


/// <summary><para>
/// Abstract base class for all derived AcDbAssocXxxActionParam classes. Action 
/// parameters are owned by AcDbAssocParamBasedActionBody, either directly or via
/// an AcDbAssocCompoundActionParam hierarchy.
/// </para><para>
/// Action parameters provide a uniform and high-level way for custom action bodies 
/// derived from AcDbAsscoParamBasedActionBody to keep and access their data. 
/// Instead of each custom action body implementing its own code to keep its data 
/// and devise its own representation of the data, the action body can keep all 
/// of its data in the form of action parameters. The action body then does not 
/// need to take care of the data serialization and cloning, because it is performed 
/// automatically by the base AcDbAsscoParamBasedActionBody class. External 
/// code can inspect the action body data without knowing anything about the action 
/// body itself, because the data in the form of action parameters can be traversed
/// and inspected in a general way.
/// </para><para>
/// The concrete derived action parameter classes provide a general and high-level 
/// mechanism for keeping and accessing the application data, transparent to the 
/// client code. For example, when an action body needs to keep a reference to an 
/// edge subentity of an entity (such as to a line entity, segment of a polyline, 
/// edge of a solid or surface, or generally to anything that provides AcGeCurve3d 
/// geometry), it just creates an object of AcDbAssocEdgeActionParam class that 
/// takes care of keeping the data. Anytime the client code needs the current 
/// geometry of the edge subentity, it asks the AcDbAssocEdgeActionParam and it 
/// provides the geometry to the client code. The AcDbAssocEdgeActionParam takes 
/// care of keeping the data in various ways, such as by referencing an AcDbEntity 
/// in the database, by referencing an edge subentity of an AcDbEntity, or by directly 
/// keeping a constant AcGeCurve. The client code does not need to worry about 
/// how the data is kept. It just asks the AcDbAssocEdgeActionParam and obtains
/// the current AcGeCurve3d* from it.
/// </para></summary>
///
class ACDB_PORT AcDbAssocActionParam : public AcDbObject
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    AcDbAssocActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Returns the action parameter name. It may be any string, possibly empty.
    /// The parameter name is case sensitive. Multiple action parameters owned
    /// by the same action body may have the same name.
    /// </summary>
    /// <returns> The name of the action parameter. </returns>
    ///
    const AcString& name() const;

    /// <summary>
    /// Sets the parameter name. It may be any string, possibly empty. 
    /// The parameter name is case sensitive. Multiple action parameters owned
    /// by the same action body may have the same name.
    /// </summary>
    /// <param name="newName">  New name of this action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setName(const AcString& newName);

    /// <summary>
    /// Resets the contents of the parameter to "empty" state, optionally
    /// erasing all objects that the parameter physically or logically owns, 
    /// such as sub-parameters or dependencies (dependencies are "physically" owned 
    /// by the action but may be "logically" owned by the action parameter). If 
    /// alsoEraseOwnedObjects is true, the default implementation just calls 
    /// detachDependenices(), otherwise it does nothing.
    /// <</summary>
    /// <param name="alsoEraseOwnedObjects">  
    /// If true is passed, the objects owned by this action parameter are erased.
    /// Otherwise they are just detached.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus makeParamEmpty(bool alsoEraseOwnedObjects);

    /// <summary>
    /// If the parameter has some dependencies, it detaches and erases them,
    /// making the parameter not depend on any other object.
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus detachDependencies();

    /// <summary>
    /// Similar to detachDependencies() but before detaching the dependencies,
    /// it may also make a backup copy of the current contents of the dependent-on
    /// entities and keep this backup copy as constant data. The default 
    /// implementation just calls detachDependencies().
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus makeParamConstant();

    /// <summary>
    /// Transforms any constant geometry kept in the action parameter, such as 
    /// AcGeCurve3d* or AcGePoint3d.
    /// </summary>
    /// <param name="transform"> The transform to be applied to the constant geometry. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus transformConstantGeometry(const AcGeMatrix3d& transform);

    /// <summary>
    /// Climbs up the action parameter ownership hierarchy (action parameters may 
    /// be owned by other parameters, such as by AcDbAssocCompoundActionParam), 
    /// up to the AcDbAssocParamBasedActionBody, and from it to the action owning 
    /// the action body.
    /// </summary>
    /// <returns> 
    /// The AcDbAssocAction that owns (directly or indirectly) this action parameter. 
    ///</returns>
    ///
    AcDbObjectId parentAction() const;

    /// <summary>
    /// Returns all dependencies that the action parameter references. These 
    /// dependencies are "physically" owned by the action, but may be "logically" 
    /// owned by action parameters that use them. For example, AcDbAssocEdgeActionParam
    /// may logically own an AcDbAssocGeomDependency or AcDbAssocDependency on
    /// the entity that provides the edge geometry.
    /// </summary>
    /// <param name="readDependenciesWanted">  Read-type dependencies wanted. </param>
    /// <param name="writeDependenciesWanted"> Write-type dependencies wanted. </param>
    /// <param name="dependencyIds"> Returned AcDbObjectIds of AcDbAssocDependencies. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getDependencies(bool readDependenciesWanted, 
                                              bool writeDependenciesWanted,
                                              AcDbObjectIdArray& dependencyIds) const;

    /// <summary>
    /// Returns the internal AcDbAssocStatus member data of the action parameter. 
    /// If alsoCheckDependencies, it also considers the status of all the dependencies 
    /// referred to by this action parameter and returns the most 'severe' status of 
    /// all the statuses. Generally evaluation requests statuses are the most severe and
    /// kIsUpToDateAssoc it the least severe.
    /// </summary>
    ///
    AcDbAssocStatus status(bool alsoCheckDependencies) const;

    /// <summary><para>
    /// Sets the internal AcDbAssocStatus member data of the action parameter, including
    /// setting the same newStatus in action parameters owning this action parameter.
    /// At the end of an action evaluation, the AcDbAssocStatus of all action parameters
    /// owned by that action (body) is reset to kIsUpToDateAssocStatus.
    /// </para><para>
    /// For the logic of setting various AcDbAssocStatus values, see the documentation
    /// of AcDbAssocDependency::setStatus() because this method exercises analogous logic.
    /// </para></summary>
    /// <param name="newStatus"> The new AcDbAssocStatus of the action parameter. </param>
    /// <param name="notifyParentAction">
    /// If true, isEvaluationRequest(newStatus), the status of the AcDbAssocAction owning 
    /// this action parameter is set to the same status (unless the action evaluation status 
    /// is already more severe than the new one). The action then notifies its owning network.
    /// <param name="setInOwnedParams"> 
    /// Allows to set the same newStatus in all action parameters owned by this action parameter.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool            notifyParentAction = true, 
                                bool            setInOwnedParams   = false);

    /// <summary>
    /// Using this method the action parameter reveals its AcDbStepIds and AcDbPersSubentIds
    /// to the AcDbAssocPersSubentManager.
    /// </summary>
    /// <param name="stepIds"> The array of returned AcDbPersStepIds. </param>
    /// <param name="persSubentIds"> The array of returned  AcDbPersSubentIds. </param>
    /// <remarks> This method is currently for internal use only. </remarks>
    ///
    virtual void collectPersSubentNamingDataOverride(AcDbPersStepIdArray&   stepIds, 
                                                     AcDbPersSubentIdArray& persSubentIds) const;

    /// <summary>
    /// Using this method the action parameter asks the AcDbAssocPersSubentManager 
    /// to remap its AcDbPersStepIds and PersSubentIds after the action parameter 
    /// has been cloned.
    /// </summary>
    /// <param name="pCloner"> 
    /// AcDbAssocPersSubentManagerCloner that the action parameter uses to remap 
    /// its AcDbPersStepIds and PersSubentIds.
    /// </param>
    /// <remarks> This method is currently for internal use only. </remarks>
    ///
    virtual void clonePersSubentNamingDataOverride(AcDbAssocPersSubentManagerCloner* pCloner);
};

#pragma pack (pop)

