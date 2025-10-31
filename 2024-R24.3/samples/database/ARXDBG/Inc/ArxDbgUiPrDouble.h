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
