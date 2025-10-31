//
// (C) Copyright 1998-2010 by Autodesk, Inc. 
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
//
//  dbosnap2.h - header file for custom osnap api
//

#ifndef _DBOSNAP2_H
#define _DBOSNAP2_H

#include "dbosnap.h"

class AcDbCustomOsnapMode2 : public AcDbCustomOsnapMode{
public:
    /// <summary>
    /// This method is called to get an icon that will be displayed on osnap 
    /// right-clicking menu.
    /// AutoCAD will not close this handle, you can cache it and destroy
    /// the icon resource in destructor.
    /// </summary>
    ///
    /// <returns>
    /// Returns a handle to an icon. The icon you supply should be in size of 16*16.
    /// </returns>
    virtual HICON menuIcon()
    {
        return NULL;
    }

    /// <summary>
    /// This method is called to get a string used for displaying on osnap 
    /// right-clicking menu.
    /// </summary>
    /// <returns>
    /// Returns Custom OSNAP mode display string.
    /// </returns>
    virtual const ACHAR * displayString()
    {
        return localModeString();
    }
};

#endif // _DBOSNAP2_H
