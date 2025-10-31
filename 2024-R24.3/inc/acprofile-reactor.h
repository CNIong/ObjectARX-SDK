//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#pragma once
#include "AdAChar.h"
#include "AcCoreDefs.h" // for ACCORE_PORT

class AcApProfileManagerReactor 
{
public:
    ACCORE_PORT virtual ~AcApProfileManagerReactor();
    virtual void currentProfileWillChange(const ACHAR * /*newProfile*/) {}
    virtual void currentProfileChanged(const ACHAR * /*newProfile*/) {}
    virtual void currentProfileWillBeReset(const ACHAR * /*currentProfile*/) {}
    virtual void currentProfileReset(const ACHAR * /*currentProfile*/) {}
    virtual void currentProfileWillBeSaved(const ACHAR * /*currentProfile*/) {}
    virtual void currentProfileSaved(const ACHAR * /*currentProfile*/) {}
    virtual void profileWillReset(const ACHAR * /*profileName*/) {}
    virtual void profileReset(const ACHAR * /*profileName*/) {}
    virtual void profileWillBeSaved(const ACHAR * /*profileName*/) {}
    virtual void profileSaved(const ACHAR * /*profileName*/) {}
};
