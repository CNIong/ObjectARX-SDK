//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2010-2011 by Autodesk, Inc.  
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
// CREATED BY: Sharad Jaiswal                            May 2010
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "AcDbAssocArrayActionBody.h"

class AcDbVertexRef;

/// <summary><para>
/// AcDbAssocArrayModifyActionBody class is an associative action which modify
/// or override items of an associative array. This class and its derived class
/// in general manage item specific modification on an associative array. This
/// class inparticular is responsible for replacing some items with a set of 
/// source objects.
/// </para><para>
/// This class may be derived to support any modification action specific to
/// array items.
/// </para></summary>
/// <remarks> Deriving from this class is not supported. </remarks>
///
class ACDB_PORT AcDbAssocArrayModifyActionBody : public AcDbAssocArrayActionBody
{
public:
    ACDB_DECLARE_MEMBERS(AcDbAssocArrayModifyActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocArrayModifyActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Destructor. </summary>
    ///
    ~AcDbAssocArrayModifyActionBody(void);

    /// <summary> Obtains list of items which are being overriden by this
    /// action. </summary>
    /// <param name="indices"> The output list of spatial indices. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getOverridenItems(AcArray<AcDbItemLocator>& indices) const;

    /// <summary> Sets the list of items which are to be overriden by this
    /// action. </summary>
    /// <param name="indices"> The input list of spatial indices. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setOverridenItems(const AcArray<AcDbItemLocator>& indices);

    /// <summary> Checks whether an item at given index is controlled by this
    /// action. This method returns true if this item is being overridden by
    /// this action.</summary>
    /// <param name="item"> The input reference of array item. </param>
    /// <returns> true, if the item is controlled by this action. </returns>
    ///
    virtual bool controlsItem(const AcDbAssocArrayItem& item) const ADESK_OVERRIDE;

    /// <summary><para> Creates associative array modification action body to
    /// override given set of items from the array. This method is also 
    /// responsible for creating action and attaching appropriate dependencies. 
    /// </para><para> The item indices can be obtained from subent ids using 
    /// static method AcDbAssocArrayActionBody::getArrayItemLocators(). </para>
    /// </summary>
    /// <param name="arrayId">       The input array object id. </param>
    /// <param name="indices">       The input list of item locators. </param>
    /// <param name="substEntities"> The input list of entities to be used as source for replacement. </param>
    /// <param name="basePoint">     The input vertex ref to define base point. 
    /// </param>
    /// <param name="actionBodyId">  The returned array action body id. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    static Acad::ErrorStatus createInstance(AcDbObjectId arrayId,
                                       const AcArray<AcDbItemLocator>& indices,
                                       const AcDbObjectIdArray& substEntities, 
                                       AcDbVertexRef& basePoint,
                                       AcDbObjectId& actionBodyId);
};

