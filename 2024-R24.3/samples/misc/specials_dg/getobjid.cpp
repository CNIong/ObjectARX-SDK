//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// Description: Special code snippet. A more elaborate version of this is
//              used in many of the other samples
//

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

AcDbEntity*
selectEntity(AcDbObjectId& eId, AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;
    ads_entsel(_T("\nSelect an entity: "), en, pt);

    // Exchange the ads_name for an object ID.
    //
    acdbGetObjectId(eId, en);

    AcDbEntity * pEnt;
    acdbOpenObject(pEnt, eId, openMode);

    return pEnt;
}

// END CODE APPEARING IN SDK DOCUMENT.
