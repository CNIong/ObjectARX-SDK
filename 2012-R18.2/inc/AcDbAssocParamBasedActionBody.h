//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2007-2011 by Autodesk, Inc. 
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
#include "dbEval.h"
#include "AcValue.h"
#include "AcDbAssocActionBody.h"
#pragma pack (push, 8)


/// <summary><para>
/// AcDbAssocParamBasedActionBody allows custom action body classes keep and 
/// access their data in a uniform an high-level manner. Instead of each concrete 
/// custom action body devising its own way how to keep its data, they the data 
/// is uniformly stored in the form of AcDbAssocActionParam(eters), and for simple 
/// numerical values, in the form of value action parameters. The action parameters 
/// take care of keeping the data in various ways and provide the current values 
/// to the action body anytime the action body requests them. The custom action 
/// body does not even need to implement code to serialize and clone its data, 
/// because the data is managed by the AcDbAssocParamBasedActionBody base class. 
/// See the AcDbAssocActionParam class and derived classes for more details.
/// </para><para>
/// Another advantage of keeping the action body data in action parameters is that 
/// it is possible to write code that traverses and inspects the action body data 
/// in a generic way, without knowing anything about the action body itself.
/// </para><para>
/// AcDbAssocParamBasedActionBody owns an array of AcDbAssocActionParams and an
/// array of value action parameters. The AcDbAssocActionParams and the value 
/// action parameters are completely independent of each other. 
/// </para><para>
/// The value action parameter represents a named array of numerical values, such 
/// as a doubles, ints, strings or vectors. Usually the array will contain only 
/// a single element, but generally it con contain any number of elements. 
/// The value parameter name is a case-sensitive string. 
/// </para><para>
/// Each individual value may either be a constant, or defined by an expression. 
/// When it is defined by an expression, the value parameter keeps AcDbObjectId 
/// of a read-only AcDbAssocValueDependency (the dependency is owned by the 
/// parent AcDbAssocAction) on an anonymous AcDbAssocVariable that keeps the 
/// expression and provides the input value for the value parameter. This anonymous 
/// variable is exclusively managed by the value parameter who is responsible for 
/// its creation, deletion, copy, etc.
/// </para><para>
/// If the user enters the expression in the form of "name=expression", the
/// automatically created AcDbAssocVariable is assigned the given "name" instead
/// of being anonymous, i.e. with empty name. If the variable has explicit name,
/// it apperars in the parameters manager and can be referenced by other expressions
/// as any other variable. However, it is still completely managed by the value 
/// parameter who takes care of the variable deletion, copy, etc. 
/// </para></summary>
///
class ACDB_PORT AcDbAssocParamBasedActionBody : public AcDbAssocActionBody
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocParamBasedActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocParamBasedActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Removes all owned AcDbAssocActionParams, optionally also erasing them. 
    /// </summary>
    /// <param name="alsoEraseThem">  
    /// If true, the owned AcDbAssocActionParams are also erased. Otherwise they
    /// are just detached so that this action body is not their database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus removeAllParams(bool alsoEraseThem);

    /// <summary> Returns then number of the owned AcDbAssocActionParams. </summary>
    /// <returns> Number of the owned AcDbAssocActionParameters. </returns>
    ///
    int paramCount() const;

    /// <summary> 
    /// Returns an array of the owned AcDbAssocActionParams. 
    /// </summary>
    /// <returns> 
    /// Array of the owned AcDbAssocActionParams. Notice that it returns a 
    /// const reference to an internal array. The client code must not hold on 
    /// to this array and should make a copy of the array if it is doing anything 
    /// more than just momentarily accessing its elements.
    /// </returns>
    ///
    const AcDbObjectIdArray& ownedParams() const;

    /// <summary> 
    /// Adds a new AcDbAssocActionParam. The AcDbAssocParamBasedActionBody
    /// becomes the database owner of this action parameter.
    /// </summary>
    /// <param name="paramId"> 
    /// AcDbObjectId of the action parameter being added. If the action parameter 
    /// is already owned by this AcDbAssocParamBasedActionBody, it it just returns 
    /// its existing index in the array and does not add it again. 
    ///</param>
    /// <param name="paramIndex"> 
    /// Returned index of the newly added action parameter. If the parameter is 
    /// already owned by this AcDbAssocParamBasedActionBody, its existing index
    /// is returned.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addParam(const AcDbObjectId& paramId, int& paramIndex);

    /// <summary> 
    /// Utility methods that creates a new AcDbAssocActionParam of the given 
    /// pParamClass and with the given paramName and adds it to the database and 
    /// to this AcDbAssocParamBasedActionBody. 
    /// </summary>
    /// <param name="paramName"> Name of the action parameter to create. </param>
    /// <param name="pParamClass"> Type of the action parameter to create. </param>
    /// <param name="paramId"> AcDbObjectId of the newly created action parameter. </param>
    /// <param name="paramIndex"> Index of the newly created action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addParam(const AcString& paramName, AcRxClass* pParamClass, AcDbObjectId& paramId, int& paramIndex); 

    /// <summary> 
    /// Removes the AcDbAssocActionParam, optionally also erasing it. 
    /// </summary>
    /// <param name="paramId"> AcDbObjectId of the action parameter to remove. </param>
    /// <param name="alsoEraseIt">  
    /// If true, the owned action parameter is also erased. Otherwise it is just
    /// detached so that this AcDbAssocParamBasedActionBody is not its database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeParam(const AcDbObjectId& paramId, bool alsoEraseIt); 

    /// <summary> 
    /// Returns all owned AcDbAssocActionParams with the given name. Notice that
    /// more than one action parameter may have the same name. The parameters are 
    /// always returned in the same order which is the order the parameters were 
    /// added to the action body. Thus, an array of action parameters can easily 
    /// be represented by multiple action parameters with the same name.
    /// </summary>
    /// <param name="paramName">  The name of the action parameter. </param>
    /// <returns> All owned action parameters with the given name. </returns>
    ///
    const AcDbObjectIdArray& paramsAtName(const AcString& paramName) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam specified by its name and optional 
    /// index among all parameters with the same name. The default index 0 means
    /// the first parameter with the given name is returned.
    /// </summary>
    /// <param name="paramName"> The name of the action parameter. </param>
    /// <param name="index"> Index among all parameters with the same name. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtName(const AcString& paramName, int index = 0) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam in the array of all action parameters 
    /// owned by this AcDbAssocParamBasedActionBody.
    /// </summary>
    /// <param name="paramIndex"> Index in the array of all action parameters. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtIndex(int paramIndex) const;

    /// <summary> 
    /// Returns names of all owned value action parameters. The names of the value
    /// action parameters are arbitrary case-sensitive strings but must be unique.
    /// </summary>
    /// <param name="paramNames"> Names of all owned value action parameters. </param>
    ///
    void ownedValueParamNames(AcArray<AcString>& paramNames) const;

    /// <summary> 
    /// Obtains arrays of values, expressions and evaluatorIds for a given value 
    /// action parameter. The arrays can be of any length, but in most cases they 
    /// will be of length 1, meaning that the value action parameter keeps a single 
    /// value, not an array of values. All three returned arrays are of the same 
    /// length. If there is no expression for a particular array element, the 
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="paramName">    The name of the value action parameter. </param>
    /// <param name="values">       The returned array of values. </param>
    /// <param name="expressions">  The returned array ox expressions. </param>
    /// <param name="evaluatorIds"> The returned array of evaluatorIds. </param>
    /// <returns> 
    /// If a value action parameter with the given name is not found, returns Acad::eNullPtr.
    /// </returns>
    ///
    Acad::ErrorStatus getValueParamArray(const AcString&           paramName,
                                         AcArray<AcDbEvalVariant>& values,
                                         AcArray<AcString>&        expressions, 
                                         AcArray<AcString>&        evaluatorIds) const;

    /// <summary> 
    /// The same as getValueParamArray() but returns just the valueIndex's element 
    /// of the returned array.
    /// </summary>
    /// <param name="paramName">    The name of the value action parameter. </param>
    /// <param name="values">       The returned values. </param>
    /// <param name="expressions">  The returned expression. </param>
    /// <param name="evaluatorIds"> The returned evaluatorId. </param>
    /// <param name="valueIndex">   Index of the array element. </param>
    /// <returns> 
    /// If a value action parameter with the given name is not found, returns 
    /// Acad::eNullPtr. If the valueIndex is out of range, returns Acad::eInvalidIndex.
    /// </returns>
    ///
    Acad::ErrorStatus getValueParam(const AcString&  paramName,
                                    AcDbEvalVariant& value,
                                    AcString&        expression, 
                                    AcString&        evaluatorId, 
                                    int              valueIndex = 0) const;

    /// <summary><para> 
    /// Sets arrays of values, expressions and evaluatorIds for a given value 
    /// action parameter. The arrays can be of any length, but in most cases they 
    /// will be of length 1, meaning that the value action parameter keeps a single 
    /// value, not an array of values. All three arrays must be of the same length. 
    /// If there is no expression for a particular array element, the expression 
    /// string and the evaluatorId must be empty strings. 
    /// </para><para>
    /// If the user enters the expression in the form of "name=expression", the
    /// automatically created AcDbAssocVariable is assigned the given "name",
    /// apperars in the parameters manager and can be referenced by other 
    /// expressions as any other variable. If the expression is in the form
    /// "expression", an anonymous variable is created that cannot be referenced
    /// and is not visible in the parameters manager.
    /// </para><para>
    /// If a value parameter of the given name does not exist, it is created.
    /// Otherwise the existing value parameter is used.
    /// </para></summary>
    /// <param name="paramName">     The name of the value action parameter. </param>
    /// <param name="values">        The array of values to set. </param>
    /// <param name="expressions">   The array of expressions to set. </param>
    /// <param name="evaluatorIds">  The array of evaluatorIds to set. </param>
    /// <param name="errorMessages"> The returned array of error messages for the individual expressions. </param>
    /// <param name="silentMode">    Do not print error message if the expression string is invalid. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamArray(const AcString&                 paramName,
                                         const AcArray<AcDbEvalVariant>& values,
                                         const AcArray<AcString>&        expressions,
                                         const AcArray<AcString>&        evaluatorIds,
                                         AcArray<AcString>&              errorMessages,
                                         bool                            silentMode);

    /// <summary><para>
    /// The same as setValueParamArray() but sets just the valueIndex's element. 
    /// If the existing array is shorter that ther given valueIndex, the array
    /// is extended to cover the valueIndex's element. 
    /// </para><para>
    /// If a value parameter of the given name does not exist, it is created.
    /// Otherwise the existing value parameter is used.
    /// </para><para>
    /// </para></summary>
    /// <param name="paramName">     The name of the value action parameter. </param>
    /// <param name="values">        The value to set. </param>
    /// <param name="expressions">   The expression to set. </param>
    /// <param name="evaluatorIds">  The evaluatorId to set. </param>
    /// <param name="errorMessages"> The returned message for the expressions. </param>
    /// <param name="silentMode">    Do not print error message if the expression string is invalid. </param>
    /// <param name="valueIndex">    Index of the array element to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParam(const AcString&        paramName,
                                    const AcDbEvalVariant& value,
                                    const AcString&        expression,
                                    const AcString&        evaluatorId,
                                    AcString&              errorMessage,
                                    bool                   silentMode,
                                    int                    valueIndex = 0);

    /// <summary> Returns AcValue::UnitType of the value parameter. </summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> The AcValue::UnitType of the value parameter. </returns>
    ///
    AcValue::UnitType valueParamUnitType(const AcString& paramName) const;

    /// <summary> Sets the AcValue::UnitType of the value parameter. </summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="unitType"> AcValue::UnitType. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamUnitType(const AcString& paramName, AcValue::UnitType unitType);

    /// <summary> 
    /// Removes the value parameter and also erases the corresponding AcDbAssocVariables, 
    /// if there are any. 
    /// </summary>
    /// <param name="paramName"> The name of the value action parameter to remove. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeValueParam(const AcString& paramName); 

    /// <summary><para>
    /// Each individual value of a value action parameter may either be a constant, 
    /// or defined by an expression. When it is defined by an expression, the value 
    /// action parameter keeps AcDbObjectId of a read-only AcDbAssocValueDependency 
    /// (the dependency is owned by the parent AcDbAssocAction) on an AcDbAssocVariable 
    /// that keeps the expression and provides the input value for the value 
    /// action parameter. This variable is exclusively managed by the value parameter 
    /// who is responsible for its creation, deletion, copy, etc.
    /// </para><para>
    /// If the user enters the expression in the form of "name=expression", this
    /// automatically created AcDbAssocVariable is assigned the given "name",
    /// apperars in the parameters manager and can be referenced by other 
    /// expressions as any other variable. If the expression is in the form
    /// "expression", an anonymous variable is created that cannot be referenced
    /// and is not visible in the parameters manager.    
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="variableIds"> 
    /// Returned array of AcDbAssocVariables for all the values of the value action 
    /// parameter with the given name. If a value is a constant and does not have 
    /// a corresponding AcDbAssocVariable, AcDbObjectId::kNull is returned for 
    /// that array element.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus valueParamInputVariables(const AcString& paramName, AcDbObjectIdArray& variableIds) const;

    /// <summary><para>
    /// The value parameter can keep AcDbObjectId of an "output" dependency (of 
    /// any kind) on a controlled object. The value parameter (expected to have 
    /// just a single value) then becomes "linked" with the named "property" of 
    /// the controlled object. 
    /// </para><para>
    /// The property name is the name of the value parameter. The "property" 
    /// of the controlled object is accessed via the AcDbAssocValueProviderPE 
    /// protocol extension that the controlled object must expose. The setValue() 
    /// method of the protocol extension is then called to set the "property" of 
    /// the controlled object to be the same as the current value of the value 
    /// parameter. The getValue() method of the protocol extension is then called
    /// to obtain the current value of the "property" of the controlled object and 
    /// set it to the value parameter.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="controlledObjectDepId"> 
    /// An existing AcDbAssocDependency (or a derived class) on the AcDbObject 
    /// controlled by this value parameter. The dependency is owned by the action
    /// that owns this AcDbAssocParamBasedActionBody.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamControlledObjectDep(const AcString& paramName, const AcDbObjectId& controlledObjectDepId);

    /// <summary><para>
    /// Updates the "propery" of the controlled object from the current value of 
    /// a value action parameter.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateValueParamControlledObject(const AcString& paramName) const;

    /// <summary><para>
    /// Updates the value of the value action parameter from the current value of
    /// a named "property" of the controlled object.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateValueParamFromControlledObject(const AcString& paramName);

    /// <summary><para>
    /// Updates named properties of all objects that are linked with value action 
    /// paramerters.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateAllObjectsControlledByValueParams() const;

    /// <summary>
    /// Transforms all constant geometries in all owned AcDbAssocParam(eters). 
    /// Example of a constant geometry is an AcGeCurve3d* in AcDbAssocEdgeActionParam
    /// or AcGePoint3d in AcDbAssocVertexActionParam.
    /// </summary>
    /// <param name="transform">
    /// Transformation to be applied to all constant geometries in the owned 
    /// AcDbAssocActionParams.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus transformAllConstantGeometryParams(const AcGeMatrix3d& transform);

    /// <summary>
    /// Scales values of all value action parameters whose units indicate they 
    /// represent distances. If the value is defined by an expression, the expression 
    /// is replaced with a constant value. 
    /// </para></summary>
    /// <param name="scaleFactor">
    /// Scaling factor to be applied to all distance value action parameters.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus scaleAllDistanceValueParams(double scaleFactor);

    /// <summary><para>
    /// This method may be overridden in derived action body clases.
    /// </para><para>    
    /// The AcDbAssocAction::removeActionsControllingObject() method notifies all
    /// action bodies that have a write-dependency on the controlled object by 
    /// calling this method. The individual action bodies then can do some work 
    /// before they are detached from the controlled object, or can even not let 
    /// themselves be detached. 
    /// </para><para>    
    /// It this method returns Acad::eOk, AcDbAssocAction::removeActionsControllingObject() 
    /// will not detach the action from the controlled object, expecting the 
    /// action body to do it by itself. If not overridden, this method returns 
    /// Acad::eNotImplemented, indicating that AcDbAssocAction::removeActionsControllingObject() 
    /// should detach the action from the controlled object.
    /// </para></summary>
    /// <param name="pControlledObject">
    /// An AcDbObject for which AcDbAssocAction::removeActionsControllingObject()
    /// is being called. This action body has a write-dependency on this object.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus removeActionsControllingObjectOverride(AcDbObject* pControlledObject)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// This base class method must be called from every derived evaluateOverride()
    /// method. It synchronizes the values of the value action parameters from the 
    /// AcDbAssocVariables.
    /// </summary>
    ///
    virtual void evaluateOverride();

    /// <summary>
    /// Using this method the action body reveals its AcDbStepIds and AcDbPersSubentIds
    /// to the AcDbAssocPersSubentManager.
    /// </summary>
    /// <remarks> This method is currently for internal use only. </remarks>
    /// <param name="stepIds">       The array of returned AcDbPersStepIds.    </param>
    /// <param name="persSubentIds"> The array of returned  AcDbPersSubentIds. </param>
    ///
    virtual Acad::ErrorStatus collectPersSubentNamingDataOverride(AcDbPersStepIdArray&   stepIds, 
                                                                  AcDbPersSubentIdArray& persSubentIds) const;

    /// <summary>
    /// Using this method the action body asks the AcDbAssocPersSubentManager 
    /// to remap its AcDbPersStepIds and PersSubentIds after the action body 
    /// has been cloned.
    /// </summary>
    /// <remarks> This method is currently for internal use only. </remarks>
    /// <param name="pCloner"> 
    /// AcDbAssocPersSubentManagerCloner that the action body uses to remap 
    /// its AcDbPersStepIds and PersSubentIds.
    /// </param>
    //
    virtual Acad::ErrorStatus clonePersSubentNamingDataOverride(class AcDbAssocPersSubentManagerCloner* pCloner);

    /// <summary>
    /// General notification that the action body can receive. The information 
    /// about the notification is passed in an AcDbAssocNotificationData object. 
    /// </summary>
    /// <remarks> This method is currently for internal use only. </remarks>
    /// <param name="pNotificationData"> 
    /// Pointer to an AcDbAssocNotificationData object. The action body should check 
    /// the type of the AcDbAssocNotificationData object, cast it to that type, 
    /// and obtain the notification information from it.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus notificationOverride(class AcDbAssocNotificationData* pNotificationData);

}; // class AcDbAssocParamBasedActionBody


/// <summary>
/// Just to be able to specify output AcString parameters by default value.
/// </summary>
///
ACDB_PORT AcString& dummyString();

#pragma pack (pop)

