
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
// CREATED BY: Jiri Kripac                                 April 2007
//
// DESCRIPTION:
//
// AcDbAssocManager class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcString.h"
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)


/// <summary> <para>
/// This class currently just contains static methods to evaluate the top-level
/// network of a given database and to add/remove global evaluation callbacks.
/// </para> <para>
/// There is currently no need to create an object of AcDbAssocManager class and 
/// add it to the database, but this object is still derived from AcDbObject,
/// in case in the future there is a need to have a database-resident instance
/// of AcDbAssocManager class that might keep additional data.
/// </para> </summary>
///
class ACDB_PORT AcDbAssocManager : public AcDbObject
{
public:     
    ACRX_DECLARE_MEMBERS(AcDbAssocManager);

    /// <summary> Default constructor. </summary>
    ///
    AcDbAssocManager();

    /// <summary> <para>
    /// Evaluates the top-level AcDbAssocNetwork of the given database, using the
    /// global evaluation callback. The top-level network owns subnetworks, such 
    /// as subnetworks owned by the individual AcDbBlockTableRecords. Notice that 
    /// the top-level network owns its subentworks in logical sense, but not 
    /// necessarily in AutoCAD database ownership sense. See addAction() and
    /// getInstanceFromObject() methods of AcDbAssocNetwork class for more details.
    /// </para> <para>
    /// Evaluating the top-level network evaluates all the subnetworks that need 
    /// to be evaluated.
    /// </para> <para>
    /// When a sub-network owned by an AcDbBlockTableRecord becomes empty, i.e. 
    /// containing no actions, is is erased at the end of the evaluation of the 
    /// top-level network. Also, when the top-level network becomes empty, it is
    /// erased. When an AcDbAssoc2dConstraintGroup becomes empty, i.e. not having 
    /// any dependencies on AcDbEntities, it is erased at the end of its evaluation.
    /// </para> <para>
    /// In most cases the client code does not need to evaluate the top-level
    /// network explicitly. It is happening automatically on document lock mode 
    /// change and also during dragging, on every drag sample.
    /// </para> </summary>
    /// <param name="pDatabase"> Database whose top-level network is to be evaluated. </param>
    /// <param name="pCallback"> Optional AcDbAssocEvaluationCallback that is 
    /// added to the global callback before the evaluation and removed after the
    /// evaluation is completed. </param>
    /// <param name="callbackOrder"> Order of the optional AcDbAssocEvaluationCallback. </param>
    /// <returns> Returns true if any evaluation happened, false otherwise. </returns>
    ///
    static bool evaluateTopLevelNetwork(AcDbDatabase*                pDatabase,
                                        AcDbAssocEvaluationCallback* pCallback     = NULL, 
                                        int                          callbackOrder = 0);

    /// <summary> <para>
    /// Returns the global AcDbAssocEvaluationCallback that is used while dragging,
    /// when evaluating the top-level associative network on document lock mode 
    /// change, or anytime AcDbAssocManager::evaluateTopLevelNetwork() is explicitly 
    /// called by the client code. 
    /// </para> <para>
    /// It is actually an object of AcDbAssocEvaluationMultiCallback class 
    /// (this class is currently not exposed, but may be expossed if needed) 
    /// that keeps a vector of AcDbAssocEvaluationCallbacks and sequentially calls 
    /// all the individual callbacks. The returned AcDbAssocEvaluationMultiCallback
    /// object must not be modified or deleted by the caller.
    /// </para> <para>
    /// During dragging, the dragging evaluation callback is temporarily inserted 
    /// into this global multi-callback with order 0 and is removed after the 
    /// dragging is finished.
    /// </para> </summary>
    /// <returns> The global AcDbAssocEvaluationMultiCallback object. </returns>
    ///
    static AcDbAssocEvaluationCallback* globalEvaluationMultiCallback();

    /// <summary>
    /// Adds the given user-provided AcDbAssocEvaluationCallback to the global 
    /// AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="pCallback"> 
    /// The user-provided evaluation callback. The callback does not become owned 
    /// by the global AcDbAssocEvaluationMultiCallback, it is just referenced by it.
    /// </param>
    /// <param name="order"> 
    /// Specifies the ordering of the user-provided callbacks in the global
    /// AcDbAssocEvaluationMultiCallback. The lower-order callbacks are called
    /// before the higher-order callbacks. The drag callback is inserted with
    /// order 0, i.e. callbacks with negative order will be called before 
    /// it and callbacks with positive order will be called after it.
    /// </param>
    /// <returns> 
    /// Acad::eInvalidInput if pCallback pointer is NULL, otherwise Acad::eOk.
    /// </returns>
    ///
    static Acad::ErrorStatus addGlobalEvaluationCallback(AcDbAssocEvaluationCallback* pCallback, int order);

    /// <summary>
    /// Removes the given user-provided evaluation callback from the global 
    /// AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="pCallback"> 
    /// The user-provided evaluation callback to be removed.
    /// </param>
    /// <returns> 
    /// Acad::eInvalidInput if pCallback pointer not found in the global 
    /// AcDbAssocEvaluationMultiCallback, otherwise Acad::eOk.
    /// </returns>
    ///
    static Acad::ErrorStatus removeGlobalEvaluationCallback(AcDbAssocEvaluationCallback* pCallback);

    /// <summary>
    /// Returns all evaluation callbacks kept in the global AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="callbacks"> The returned evaluation callbacks. </param>
    /// <param name="orders"> The returned evaluation callback orders. </param>
    ///
    static void getGlobalEvaluationCallbacks(AcArray<AcDbAssocEvaluationCallback*>& callbacks,
                                             AcArray<int>&                          orders);

    /// <summary>
    /// Returns true iff the given database has some associative data, in particular
    /// if there is a global AcDbAssocNetwork for the whole database. See the
    /// related AcDbAssocNetwork::getInstanceFromDatabase() method.
    /// </summary>
    ///
    static bool hasAssocNetwork(const AcDbDatabase* pDatabase);

    /// <summary>
    /// Audits the associative data in the database and tries to fix the errors
    /// that might have happened during round-trip, due to lazy-erase, etc.
    /// </summary>
    /// <param name="pDatabase"> AcDbDatabase whose associative data is to be audited. </param>
    /// <param name="traverseWholeDatabase"> If true, all objects in the database
    /// are visited and checked, and therefore loaded into memory. </param>
    ///
    static Acad::ErrorStatus auditAssociativeData(AcDbDatabase* pDatabase, bool traverseWholeDatabase);

    /// <summary>
    /// This is an internal method that initializes the Associative Framework 
    /// subsystem. Must be called before the subsystem is first used and may 
    /// safely be called more than once. There is no need for the client code
    /// to call this method.
    /// </summary>
    /// <returns> Should always return Acad::eOk. </returns>
    ///
    static Acad::ErrorStatus initialize();

}; // class AcDbAssocManager

#pragma pack (pop)

