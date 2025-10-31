#ifndef _AD_DBAUDITRECREATE_H
#define _AD_DBAUDITRECREATE_H 1
// 
//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
//

#include "acdb.h"

/// <summary>
/// AcDbAuditRecreatePE
///
/// Defines Runtime Extension Protocol for audit-time object recreation
///
/// The contract is rather simple, although the implementation may
/// be less so.   All 3 member functions are invoked from the AcDb
/// library, in the context of RECOVER and/or AUDIT.  The contract is:
///
/// When an object of a given class is requested via
/// AcDbAuditInfo::fetchObject, and is not valid, then
/// first, the PE object's replace(...) member is invoked.
/// if it returns eOk and a new instance of a class, then that
/// instance is place in the original object id, and the repair is
/// finished.
///
/// If that fails, then the PE object's redirect(...) member
/// is invoked. If it returns
/// true, and then the new object id is entered into the
/// indirect object lookup table.
///
/// if redirect(...) returns false, then the object reference
/// is no longer valid, and "NULL" is returned for a new object is.
///
/// Instances of this class will be invoked from the Audit complex when
/// an instance of a given class is to "recreated" because an original
/// one is missing.
/// </summary>

class AcDbAuditRecreatePE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAuditRecreatePE);
    /// <summary>
    /// replace is invoked as the first step to create a
    /// replacement object for a missing or corrupted object.
    /// </summary>
    ///
    /// <param name="pNewObj">
    /// Reference to an AcDbObject pointer which, when true is
    /// returned, should represent a valid instance of the
    /// requested class, which will end up being bound to originalObjId.
    /// </param>
    ///
    /// <param name="originalObjId">
    /// The object id of the corrupted or missing object.
    /// </param>
    ///
    /// <param name="pObjClass">
    /// The anticipated class of the missing/corrupted object.
    /// </param>
    ///
    /// <param name="pDb">
    /// The database being recovered or audited.
    /// </param>
    ///
    /// <param name="pAuditInfo">
    /// The current audit state, including the entire indirect object
    /// table.
    /// </param>
    ///
    /// <returns>
    /// If it returns true, then pNewObj
    /// should be pointing to a valid object which will be bound to
    /// the input object id.
    /// If false is returned, then pNewObj should be ignored.
    /// </returns>
    ///
    /// <remarks>
    /// If false is returned, then the redirect member is invoked
    /// next.
    /// </remarks>
    ///
    virtual bool replace(AcDbObject*&   pNewObj,
                         AcDbObjectId   originalObjId,
                         AcRxClass*     pObjClass,
                         AcDbDatabase*  pDb,
                         AcDbAuditInfo* pAuditInfo)
    { return false; };

    /// <summary>
    /// redirect is invoked as the second attempt to establish a
    /// replacement object for a missing or corrupted object.
    /// It returns the object id of an existing object
    /// </summary>
    ///
    /// <param name="newObjId">
    /// The object Id that references to "original ObjId" should be
    /// mapped to.  newObjId can either be an existing object in
    /// the database (such as Layer "0") or a newly created object.
    /// </param>
    ///
    /// <param name="originalObjId">
    /// The object id of the corrupted or missing object.
    /// </param>
    ///
    /// <param name="pObjClass">
    /// The anticipated class of the missing/corrupted object.
    /// </param>
    ///
    /// <param name="pDb">
    /// The database being recovered or audited.
    /// </param>
    ///
    /// <param name="pAuditInfo">
    /// The current audit state, including the indirect object
    /// lookup table.
    /// </param>
    ///
    /// <returns>
    /// If it returns true, then newObjId should represent a valid
    /// object in pDb which can replace references to originalObjId.
    /// If false is returned, then newObjId should be ignored.
    /// </returns>
    ///
    /// <remarks>
    /// This member is invoked if and only if the replace member returns
    /// false.
    /// if false is returned, then object recreation fails.
    /// </remarks>
    ///
    virtual bool redirect(AcDbObjectId&  newObjId,
                          AcDbObjectId   originalObjId,
                          AcRxClass*     pObjClass,
                          AcDbDatabase*  pDb,
                          AcDbAuditInfo* pAuditInfo)
    { return false; };

};

#endif /* _AD_DBAUDITRECREATE_H */
