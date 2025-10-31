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
