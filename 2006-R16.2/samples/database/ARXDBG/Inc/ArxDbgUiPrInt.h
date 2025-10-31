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

#ifndef ARXDBGUIPRINT_H
#define ARXDBGUIPRINT_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrInt:
**
**  **jma
**
*************************************/

class ArxDbgUiPrInt : public ArxDbgUiPrBase {

public:
        // type restricts input to an appropriate range
    enum IntType {
        kAny    = 0,
        kNoNeg,
        kNoZero,
        kNoNegNoZero,
        kRange
    };

                    ArxDbgUiPrInt(LPCTSTR msg, LPCTSTR keyWordList, IntType type);
    virtual         ~ArxDbgUiPrInt();

    virtual Status  go();             // issue the prompt
    int             value();

    virtual void    setRange(int minVal, int maxVal);
    virtual void    setType(IntType type);

protected:
        // data members
    IntType        m_intType;
    int            m_value;
    int            m_minVal;
    int            m_maxVal;

        // helper functions
    bool		   inRange();

private:
        // outlawed functions
					ArxDbgUiPrInt(const ArxDbgUiPrInt&);
    ArxDbgUiPrInt&	operator=(const ArxDbgUiPrInt&);
};


#endif  // ARXDBGUIPRINT_H
