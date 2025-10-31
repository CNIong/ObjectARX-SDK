#ifndef POLYSAMP_MATCH_H
#define POLYSAMP_MATCH_H
//
// (C) Copyright 1994-2006 by Autodesk, Inc. 
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
