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

#ifndef ARXDBGUIPRDOUBLEDEF_H
#define ARXDBGUIPRDOUBLEDEF_H

#include "ArxDbgUiPrDouble.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrDoubleDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrDoubleDef : public ArxDbgUiPrDouble {

public:
                    ArxDbgUiPrDoubleDef(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type, double def);
    virtual         ~ArxDbgUiPrDoubleDef();

    virtual Status  go();             // issue the prompt

private:
        // data members
    double          m_default;

        // outlawed functions
							ArxDbgUiPrDoubleDef(const ArxDbgUiPrDoubleDef&);
    ArxDbgUiPrDoubleDef&	operator=(const ArxDbgUiPrDoubleDef&);
};

#endif  // ARXDBGUIPRDOUBLEDEF_H
