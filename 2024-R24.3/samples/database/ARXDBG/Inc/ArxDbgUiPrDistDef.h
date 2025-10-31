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

#ifndef ARXDBGUIPRDISTDEF_H
#define ARXDBGUIPRDISTDEF_H

#include "ArxDbgUiPrDist.h"


/****************************************************************************
**
**  CLASS ArxDbgUiPrDistDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrDistDef : public ArxDbgUiPrDist {

public:
                ArxDbgUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type, double def);
                ArxDbgUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type,
                        const AcGePoint3d& basePt, double def);
    virtual     ~ArxDbgUiPrDistDef();

    virtual Status go();       // issue the prompt

private:
        // data members
    double      m_default;

        // outlawed functions
                        ArxDbgUiPrDistDef(const ArxDbgUiPrDistDef&);
    ArxDbgUiPrDistDef&	operator=(const ArxDbgUiPrDistDef&);
};

#endif  // ARXDBGUIPRDISTDEF_H
