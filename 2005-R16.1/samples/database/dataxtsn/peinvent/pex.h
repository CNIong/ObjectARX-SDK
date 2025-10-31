//
// (C) Copyright 1996,1998 by Autodesk, Inc. 
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

#ifndef PEINVENT_H
#define PEINVENT_H 1

// String used for command group name, and REGAPP name, and
// other places where a text key is required.
//
#define PE_INVENTORY_SERVICE  "ASDK_PE_INVENTORY_ID"
#define PE_INVENTORY_GROUP  "ASDK_PE_INVENTORY_GROUP"

/* ================ AdskObjectInventory ================ */
 
class AsdkObjectInventory : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AsdkObjectInventory);

    virtual Acad::ErrorStatus inventoryId(const AcDbObject* pObj, char*& inventoryId) const;
    virtual Acad::ErrorStatus setInventoryId(AcDbObject* pObj, char* inventoryId);
};

#endif /* PEINVENT_H */
