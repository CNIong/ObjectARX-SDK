//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


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
