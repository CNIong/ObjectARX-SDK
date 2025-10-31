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

#ifndef ARXDBGUIPRSTRING_H
#define ARXDBGUIPRSTRING_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrString:
**
**  **jma
**
*************************************/

class ArxDbgUiPrString : public ArxDbgUiPrBase {

public:
                    ArxDbgUiPrString(LPCTSTR msg, bool allowSpaces = true);
    virtual         ~ArxDbgUiPrString();

    virtual Status  go();       // issue the prompt
    LPCTSTR         value();

        // overridden because this class does not support keywords
    virtual LPCTSTR				keyWords() const;
    virtual Acad::ErrorStatus   setKeyWords(LPCTSTR keyWordList);

    virtual LPCTSTR             keyWordPicked();
    virtual bool		        isKeyWordPicked(LPCTSTR matchKeyWord);

protected:
    CString		m_value;
    bool		m_allowSpaces;

private:
        // outlawed functions
						ArxDbgUiPrString(const ArxDbgUiPrString&);
    ArxDbgUiPrString&	operator=(const ArxDbgUiPrString&);
};

#endif  // ARXDBGUIPRSTRING_H
