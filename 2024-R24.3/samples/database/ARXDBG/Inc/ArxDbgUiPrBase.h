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

#ifndef ARXDBGUIPRBASE_H
#define ARXDBGUIPRBASE_H

/****************************************************************************
**
**  CLASS ArxDbgUiPrBase:
**      base class for prompts. Holds keyword mechanism and basic
**  status return value.
**
**  **jma
**
*************************************/

class ArxDbgUiPrBase {

public:

    enum Status {
        kCancel    = 0,
        kNone,        // not returned unless explicitly enabled
        kKeyWord,
        kOk
    };

    virtual LPCTSTR				keyWords() const;
    virtual Acad::ErrorStatus   setKeyWords(LPCTSTR keyWordList);

    virtual LPCTSTR		        message() const;
    virtual Acad::ErrorStatus   setMessage(LPCTSTR message);

    virtual LPCTSTR             keyWordPicked() const;
    virtual bool		        isKeyWordPicked(LPCTSTR matchKeyWord);

    virtual Status              go() = 0;   // issue the prompt

protected:
                    ArxDbgUiPrBase(LPCTSTR msg, LPCTSTR keyWordList);
    virtual         ~ArxDbgUiPrBase();    // must be public to call delete on base class pointer

        // data members
    CString		m_keyWords;
    CString		m_message;
    CString		m_keyWordPicked;

private:
        // outlawed functions
                    ArxDbgUiPrBase(const ArxDbgUiPrBase&);
    ArxDbgUiPrBase&	operator=(const ArxDbgUiPrBase&);
};

#endif //   ARXDBGUIPRBASE_H
