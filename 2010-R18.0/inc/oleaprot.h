//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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

#ifndef OLEAUTO_H
#define OLEAUTO_H

#include "dbmain.h"
#include <wtypes.h>
#pragma pack (push, 8)

//
// AcAxOleLinkManager is used to maintain the link between an ARX
// objects and their respective COM wrapper.
//
class AcAxOleLinkManager
{
public:
    
    // Given a pointer to a database resident object, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbObject* pObject) = 0;

    // Set the link between a database resident object and a 
    // COM wrapper. If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject, IUnknown* pUnknown) = 0;

    // Given a pointer to a database object, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbDatabase* pDatabase) = 0;

    // Set the link between a database object and a COM wrapper. 
    // If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbDatabase* pDatabase, IUnknown* pUnknown) = 0;

    // Given a pointer to a database object, return the
    // IDispatch of then document object. NULL is returned if
    // the database does not belong to a particular document.
    virtual IDispatch* GetDocIDispatch(AcDbDatabase* pDatabase) = 0;

    // Set the link between a database object and the IDispatch
    // of the document it belongs to. If the IDispatch is NULL, then 
    // the link is removed.
    virtual Adesk::Boolean SetDocIDispatch(AcDbDatabase* pDatabase, IDispatch* pDispatch) = 0;

    // Given a pointer to a database resident object and a subentID, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbObject* pObject,
        const AcDbSubentId &id) = 0;

    // Set the link between a database resident object, a subentID and a 
    // COM wrapper. If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject,
        const AcDbSubentId &id, IUnknown* pUnknown) = 0;
};

AcAxOleLinkManager* AcAxGetOleLinkManager();

#pragma pack (pop)
#endif // OLEAUTO_H
