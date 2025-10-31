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
#ifndef POLYSAMP_MATCH_H
#define POLYSAMP_MATCH_H

#include "dbmatch.h"

//
//  Polysamp Run Time extension class for Match Properties.
//
class AsdkPolyMatchProp: public AcDbMatchProperties
{
  public:
    virtual void copyProperties(AcDbEntity* pSrcEntity, AcDbEntity* pTrgEntity,
                                unsigned int flag) const ;
};


//
// Dynamic linker reactor to watch for loading of MatchProp app server application
//
class AppEventCatcher : public AcRxDLinkerReactor 
{
  public:
    virtual void rxAppLoaded(const TCHAR* moduleName);

    static short thisAppLoaded;
};


#endif // POLYSAMP_MATCH_H
