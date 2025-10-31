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

#ifndef ARXDBGUIPRANGLEDEF_H
#define ARXDBGUIPRANGLEDEF_H

#include "ArxDbgUiPrAngle.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrAngleDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrAngleDef : public ArxDbgUiPrAngle {

public:
                    ArxDbgUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, double def);
                    ArxDbgUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type,
                            const AcGePoint3d& basePt, double def);
    virtual        ~ArxDbgUiPrAngleDef();

    virtual Status  go();       // issue the prompt

private:
        // data members
    double          m_default;

        // outlawed functions
                        ArxDbgUiPrAngleDef(const ArxDbgUiPrAngleDef&);
    ArxDbgUiPrAngleDef&	operator=(const ArxDbgUiPrAngleDef&);
};

#endif  // ARXDBGUIPRANGLEDEF_H
