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

#ifndef ARXDBGUIPRINTDEF_H
#define ARXDBGUIPRINTDEF_H

#include "ArxDbgUiPrInt.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrIntDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrIntDef : public ArxDbgUiPrInt {

public:
                    ArxDbgUiPrIntDef(LPCTSTR msg, LPCTSTR keyWordList, IntType type, int def);
    virtual         ~ArxDbgUiPrIntDef();

    virtual Status  go();             // issue the prompt

private:
        // data members
    int             m_default;

        // outlawed functions
						ArxDbgUiPrIntDef(const ArxDbgUiPrIntDef&);
    ArxDbgUiPrIntDef&	operator=(const ArxDbgUiPrIntDef&);
};


#endif  // ARXDBGUIPRINTDEF_H
