
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
// AcDbAssocSingleEdgePersSubentId concrete derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acarray.h"
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary>
/// The concrete derived AcDbAssocPersSubentId class that identifies an edge
/// subentity if the entity has only a single edge subentity (such as in the 
/// case of curve entities).
/// </summary>
///
class ACDB_PORT AcDbAssocSingleEdgePersSubentId : public AcDbAssocPersSubentId
{
public:

	ACRX_DECLARE_MEMBERS(AcDbAssocSingleEdgePersSubentId);

    /// <summary>
    /// Always returns number 1.
    /// </summary>
    /// <param  name="pEntity"> Not used. </param>
    /// <returns> Always returns count 1. </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity) const { return 1; }

    /// <summary> Always returns AcDb::kEdgeSubentType. </summary>
    /// <param  name="pEntity"> Not used. </param>
    /// <returns> AcDb::kEdgeSubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity) const { return AcDb::kEdgeSubentType; }

    /// <summary> 
    /// Always returns false because AcDbAssocSingleEdgePersSubentId always 
    /// identities the single edge of an entity.
    /// </summary>
    /// <returns> Always returns false. </returns>
    ///
    virtual bool isNull() const { return false; }

    /// <summary>
    /// Returns true iff this and the other AcDbAssocSingleEdgePersSubentId 
    /// reference exactly the same subentity of the same entity. It just calls
    /// the base class AcDbAssocPersSubentId::isEqualTo() because there is no
    /// additional data stored in this derived AcDbAssocSingleEdgePersSubentId
    /// class.
    /// </summary>
    /// <param  name="pEntity"> 
    /// The entity owning the subentities of this and the other AcDbAssocSingleEdgePersSubentId. 
    /// </param>
    /// <param  name="pOther"> The other AcDbAssocSingleEdgePersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocSingleEdgePersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity* pEntity, const AcDbAssocPersSubentId* pOther) const
    {
        return AcDbAssocPersSubentId::isEqualTo(pEntity, pOther);
    }
}; // class AcDbAssocSingleEdgePersSubentId

#pragma pack (pop)


