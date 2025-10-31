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

#ifndef ARXDBGUIPRKEYWORD_H
#define ARXDBGUIPRKEYWORD_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrKeyWord:
**      A prompt with keywords only. Doesn't do much over what Prompt
**  does except provide a "go" function to issue the prompt.
**
**  **jma
**
*************************************/

class ArxDbgUiPrKeyWord : public ArxDbgUiPrBase {

public:
                    ArxDbgUiPrKeyWord(LPCTSTR msg, LPCTSTR keyWordList);
    virtual         ~ArxDbgUiPrKeyWord();

    virtual Status  go();                           // issue the prompt
    LPCTSTR         value();                        // for consistency

    void            setAllowNone(bool allowIt);

protected:
    bool			m_allowNone;

private:
        // outlawed functions
                        ArxDbgUiPrKeyWord(const ArxDbgUiPrKeyWord&);
    ArxDbgUiPrKeyWord&	operator=(const ArxDbgUiPrKeyWord&);
};


#endif  // ARXDBGUIPRKEYWORD_H
