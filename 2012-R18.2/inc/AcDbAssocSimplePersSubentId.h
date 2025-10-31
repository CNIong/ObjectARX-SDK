
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
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocSimplePersSubentId concrete derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acarray.h"
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary>
/// The concrete derived AcDbAssocPersSubentId class that simply keeps the
/// AcDbSubentId when it is persistent and does not change.
/// </summary>
///
class ACDB_PORT AcDbAssocSimplePersSubentId : public AcDbAssocPersSubentId
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocSimplePersSubentId);

    /// <summary>
    /// Constructor. Just keeps the given AcDbSubentId.
    /// </summary>
    explicit AcDbAssocSimplePersSubentId(AcDbSubentId subentId = kNullSubentId) : mSubentId(subentId) {}

    /// <summary>
    /// Returns number 1 if not null or 0 if null.
    /// </summary>
    /// <param  name="pEntity"> Not used. </param>
    /// <returns> Returns count 1 or 0. </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity) const { return !isNull() ? 1 : 0; }

    /// <summary> Returns the type of the stored AcDbSubentId. </summary>
    /// <returns> AcDb::SubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity) const { return mSubentId.type(); }

    /// <summary> Returns the stored AcDbSubentId. </summary>
    /// <returns> The stored AcDbSubentId. </returns>
    ///
    virtual AcDbSubentId subentId(const AcDbEntity* pEntity) const { return mSubentId; }

    /// <summary> 
    /// Returns true iff the AcDbSubentId stored in this AcDbAssocSimplePersSubentId is null.
    /// </summary>
    /// <returns> True iff the stored AcDbSubentId is null. </returns>
    ///
    virtual bool isNull() const
    {
        return mSubentId.type() == AcDb::kNullSubentType;
    }

    /// <summary>
    /// Returns true iff this and the other AcDbAssocSimplePersSubentId reference
    /// exactly the same subentity of the same entity. It simply compares the 
    /// stored AcDbSubentIds.
    /// </summary>
    /// <param  name="pEntity"> 
    /// The entity owning the subentities of this and the other AcDbAssocPersSubentId. 
    /// </param>
    /// <param  name="pOther"> The other AcDbAssocSimplePersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocSimplePersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity* pEntity, const AcDbAssocPersSubentId* pOther) const
    {
        if (!AcDbAssocPersSubentId::isEqualTo(pEntity, pOther))
            return false;

        const AcDbAssocSimplePersSubentId* const pOtherSimple = dynamic_cast<const AcDbAssocSimplePersSubentId*>(pOther);

        return mSubentId == pOtherSimple->mSubentId;
    }

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);

    /// <summary> The standard protocol. </summary>
    /// <param  name="pAuditInfo"> See the AcDbAuditInfo documentation. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

private:

    AcDbSubentId mSubentId;

}; // class AcDbAssocSimplePersSubentId

#pragma pack (pop)


