//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
