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

#ifndef ARXDBGUIPRDOUBLE_H
#define ARXDBGUIPRDOUBLE_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrDouble:
**
**  **jma
**
*************************************/

class ArxDbgUiPrDouble : public ArxDbgUiPrBase {

public:

    enum DoubleType {
        kAny    = 0,
        kNoNeg,
        kNoZero,
        kNoNegNoZero,
        kRange
    };

                    ArxDbgUiPrDouble(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type);
    virtual         ~ArxDbgUiPrDouble();

    virtual Status  go();             // issue the prompt
    double          value();

    void            setDoubleType(DoubleType newType);
    void            setRange(double minVal, double maxVal);

    void            setUnit(int unit);
    void            setPrecision(int precision);

protected:
        // data members
    double          m_value;
    double          m_minVal;
    double          m_maxVal;
    DoubleType      m_doubleType;
    int             m_unit;
    int             m_precision;

        // helper functions
    bool		    inRange();

private:
        // outlawed functions
						ArxDbgUiPrDouble(const ArxDbgUiPrDouble&);
    ArxDbgUiPrDouble&	operator=(const ArxDbgUiPrDouble&);
};


#endif  // ARXDBGUIPRDOUBLE_H
