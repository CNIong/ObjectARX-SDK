//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "acedinpt.h"

class AsdkInputPointFilter : public AcEdInputPointFilter
{
public:
    AsdkInputPointFilter(){ m_changePoint = false; };
    virtual Acad::ErrorStatus processInputPoint(const AcEdInputPoint& input, AcEdInputPointFilterResult& output);

    // Non-standard protocol
    //
    void enableChanges(){ m_changePoint = true; };
    void disableChanges(){ m_changePoint = false; };

private:
    bool m_changePoint;

};
