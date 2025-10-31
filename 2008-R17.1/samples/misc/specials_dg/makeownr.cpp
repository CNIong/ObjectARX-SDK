#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif



// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// Description:
//

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Uses the OwnerDemo class defined in the next example
// (see "ARX Example," below)

// Sets pOwner to be the owner of pOwned
//
void
makeOwner(OwnerDemo* pOwner, AcDbObject* pOwned)
{
    // First let pOwner know its the owner.  This
    // establishes ownership for filing persistence.
    //
    pOwner->setIdData(pOwned->ojectId());

    // Now set up the backpointer so that the owned
    // object knows who it's owner is.
    //
    pOwned->setOwnerId(pOwner->objectId());

// END CODE APPEARING IN SDK DOCUMENT.
