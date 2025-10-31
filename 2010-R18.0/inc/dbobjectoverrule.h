
// (C) Copyright 2008-2009 by Autodesk, Inc.
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

#pragma once

#include "rxoverrule.h"

#pragma pack (push, 8)

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbObjectOverrule overrules a subset of operations that AcDbObject class 
/// specifies. It is intended as a base class for clients who want to alter 
/// some or all behavior of a given AcDbObject-derived class. At the base level, 
/// each default implementation simply calls the corresponding method in the 
/// target class.
/// </description>  
class AcDbObjectOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>                    
    ACDB_PORT AcDbObjectOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subOpen.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <param name="mode">Passed in mode that the object is being opened in.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::open calls the 
    /// protected virtual AcDbObject::subOpen method. 
    /// </remarks>                             
    ACDB_PORT virtual Acad::ErrorStatus open(AcDbObject* pSubject, AcDb::OpenMode mode);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subClose.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::close calls the 
    /// protected virtual AcDbObject::subClose method. 
    /// </remarks>       
    ACDB_PORT virtual Acad::ErrorStatus close(AcDbObject* pSubject);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subCancel.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::cancel calls the 
    /// protected virtual AcDbObject::subCancel method. 
    /// </remarks>
    ACDB_PORT virtual Acad::ErrorStatus cancel(AcDbObject* pSubject);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subErase.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <param name="erasing">Passed in copy of the erasing argument that was 
    /// passed into the erase() function call that triggered this subErase() 
    /// call.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::erase calls the 
    /// protected virtual AcDbObject::subErase method. 
    /// </remarks>
    ACDB_PORT virtual Acad::ErrorStatus erase(AcDbObject* pSubject, Adesk::Boolean erasing);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subDeepClone.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <param name="pOwnerObject">Input object to which the clones should be 
    /// appended.</param>
    /// <param name="pClonedObject">Returns a pointer to the cloned object, 
    /// or NULL if not cloned.</param>
    /// <param name="idMap">Input current object ID map.</param>
    /// <param name="isPrimary">Input Boolean indicating whether this object is 
    /// primary or owned.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::deepClone calls the 
    /// protected virtual AcDbObject::subDeepClone method. 
    /// </remarks>
    ACDB_PORT virtual Acad::ErrorStatus deepClone(const AcDbObject* pSubject,
                                                  AcDbObject* pOwnerObject,
                                                  AcDbObject*& pClonedObject,
                                                  AcDbIdMapping& idMap,
                                                  Adesk::Boolean isPrimary = true);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subWblockClone.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <param name="pOwnerObject">Input object to which the clones should be 
    /// appended. If the owner has not been cloned, then the AcDbDatabase must 
    /// be passed in.</param>
    /// <param name="pClonedObject">Returns a pointer to the cloned object, 
    /// or NULL if not cloned.</param>
    /// <param name="idMap">Input current object ID map.</param>
    /// <param name="isPrimary">Input Boolean indicating whether this object is 
    /// primary or owned.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbObjectOverrule::wblockClone calls the 
    /// protected virtual AcDbObject::subWblockClone method. 
    /// </remarks>
    ACDB_PORT virtual Acad::ErrorStatus wblockClone(const AcDbObject* pSubject,
                                                    AcRxObject* pOwnerObject,
                                                    AcDbObject*& pClonedObject,
                                                    AcDbIdMapping& idMap,
                                                    Adesk::Boolean isPrimary = true);

};


#pragma pack (pop)
