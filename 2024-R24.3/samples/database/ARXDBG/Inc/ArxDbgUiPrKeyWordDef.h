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

#ifndef ARXDBGUIPRKEYWORDEF_H
#define ARXDBGUIPRKEYWORDEF_H

#include "ArxDbgUiPrKeyWord.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrKeyWordDef:
**      a keyword prompt with a default response
**
**  **jma
**
*************************************/

class ArxDbgUiPrKeyWordDef : public ArxDbgUiPrKeyWord {

public:
                    ArxDbgUiPrKeyWordDef(LPCTSTR msg, LPCTSTR keyWordList, LPCTSTR def);
    virtual         ~ArxDbgUiPrKeyWordDef();

    virtual Status  go();             // issue the prompt

private:
    CString    m_default;

    bool	   keyWordMatch();

        // outlawed functions
							ArxDbgUiPrKeyWordDef(const ArxDbgUiPrKeyWordDef&);
    ArxDbgUiPrKeyWordDef&	operator=(const ArxDbgUiPrKeyWordDef&);
};

#endif  // ARXDBGUIPRKEYWORDEF_H
