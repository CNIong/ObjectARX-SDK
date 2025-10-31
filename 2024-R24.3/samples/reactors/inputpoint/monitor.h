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

class AsdkInputPointMonitor : public AcEdInputPointMonitor
{
public:
    virtual Acad::ErrorStatus monitorInputPoint(const AcEdInputPoint& input, AcEdInputPointMonitorResult& output);
    virtual bool excludeFromOsnapCalculation (const AcArray<AcDbObjectId>& nestedEntity, INT_PTR gsSelectionMark);
};

