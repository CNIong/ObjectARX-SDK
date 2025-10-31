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

#ifndef ARXDBGUIPRSTRINGDEF_H
#define ARXDBGUIPRSTRINGDEF_H

#include "ArxDbgUiPrString.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrStringDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrStringDef : public ArxDbgUiPrString {

public:
                    ArxDbgUiPrStringDef(LPCTSTR msg, LPCTSTR def, bool allowSpaces = true);
    virtual         ~ArxDbgUiPrStringDef();

    virtual Status  go();    // issue the prompt

private:
        // data members
    CString		m_default;

        // outlawed functions
							ArxDbgUiPrStringDef(const ArxDbgUiPrStringDef&);
    ArxDbgUiPrStringDef&	operator=(const ArxDbgUiPrStringDef&);
};



#endif  // ARXDBGUIPRSTRINGDEF_H
