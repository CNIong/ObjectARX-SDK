//
// (C) Copyright 1998-1999,2002 by Autodesk, Inc. 
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

#ifndef _AXLOCK_H
#define _AXLOCK_H

#include "acadstrc.h"

#pragma pack (push, 8)

class AcDbDatabase;
class AcDbObjectId;

class AcAxDocLock
{
public:

    // When appending entities to a database from the session context, 
    // AutoCAD requires the following be true to properly append and
    // display the entities:
    //
    // 1. The document is locked
    // 2. The document context is current
    //
    // The document for a database needs to be locked before any write 
    // operation is performed. Since, AutoCAD has graphics information
    // in a per document basis. The document context for the database
    // must be current during the creation of any new entities. This 
    // will guarantee the graphics are updated correctly.
    //
    // Document activation is disabled to deal with the possibility that 
    // a user could attempt to activate another document while a local 
    // COM client is in the process of appending a new entity.

    enum DocLockType
    {
        kNormal         = 0,    // Locking to allow write operations
        kCurDocSwitch   = 1     // Locking + switch the doc context;
                                //  document activation is disabled in
                                //  this mode.
    };
    
    // Constructors are responsible for performing all necessary
    // operations and keeping track of what must be undone in
    // the destructor.
    AcAxDocLock();    // locks the current document w/ normal lock type
    AcAxDocLock(const AcDbObjectId& objectId, DocLockType = kNormal);
    AcAxDocLock(AcDbDatabase * pDatabase, DocLockType = kNormal);

    // Destructor is responsible for reseting everything to its prior
    // state. This is done using information cached during construction.
    ~AcAxDocLock();

    // Return lock status to caller. Use this function after construction
    // to determine whether the locking succeeded or not.
    Acad::ErrorStatus lockStatus() const;

private:

    void lockDocument(AcDbDatabase* pDatabase, DocLockType lockType = kNormal);
    void initialize();

    Acad::ErrorStatus   m_lockStatus;
    void*               m_pDocToUnlock;
    void*               m_pCurDocToRestore;
    bool                m_restoreActivation;
};

#pragma pack (pop)

#endif      // _AXLOCK_H
