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

#ifndef ARXDBGUIPRDIST_H
#define ARXDBGUIPRDIST_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrDist:
**
**  **jma
**
*************************************/

class ArxDbgUiPrDist : public ArxDbgUiPrBase {

public:
    enum DistType {
        kAny    = 0,
        kNoNeg,
        kNoZero,
        kNoNegNoZero,
        kRange
    };

                ArxDbgUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type);
                ArxDbgUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type, const AcGePoint3d& basePt);
    virtual     ~ArxDbgUiPrDist();

    virtual Status  go();       // issue the prompt
    double          value();

    void            setDistType(DistType newType);
    void            setRange(double minVal, double maxVal);
    void            setBasePt(const AcGePoint3d& basePt);
    void            setUseBasePt(bool useIt);
    void            setUseDashedLine(bool useIt);
    void            set2dOnly(bool only2d);
    void            setUnit(int unit);
    void            setPrecision(int precision);

    void            setAllowNone(bool allowIt);

protected:
        // data memebers
    bool		    m_allowNone;
    double          m_value;
    double          m_minVal;
    double          m_maxVal;
    DistType        m_distType;
    AcGePoint3d     m_basePt;
    bool		    m_useBasePt;
    bool		    m_useDashedLine;
    bool			m_2dOnly;
    int             m_unit;
    int             m_precision;

        // helper functions
    bool		    inRange();

private:
        // helper functions
    void        init();

        // outlawed functions
                    ArxDbgUiPrDist(const ArxDbgUiPrDist&);
    ArxDbgUiPrDist&	operator=(const ArxDbgUiPrDist&);
};


#endif  // ARXDBGUIPRDIST_H
