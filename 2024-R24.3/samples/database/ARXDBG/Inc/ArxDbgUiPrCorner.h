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

#ifndef ARXDBGUIPRCORNER_H
#define ARXDBGUIPRCORNER_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrCorner:
**
**  **jma
**
*************************************/

class ArxDbgUiPrCorner : public ArxDbgUiPrBase {

public:
                        ArxDbgUiPrCorner(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt);
    virtual             ~ArxDbgUiPrCorner();

    virtual Status      go();             // issue the prompt
    const AcGePoint3d&  value();

    void                setBasePt(const AcGePoint3d& basePt);
    void                setUseDashedLine(bool useIt);
    void                setNoLimitsCheck(bool noCheck);

protected:
        // data members
    AcGePoint3d         m_value;
    AcGePoint3d         m_basePt;
    bool			    m_useDashedLine;
    bool			    m_noLimCheck;

private:
        // outlawed functions
                        ArxDbgUiPrCorner(const ArxDbgUiPrCorner&);
    ArxDbgUiPrCorner&	operator=(const ArxDbgUiPrCorner&);
};


#endif  // ARXDBGUIPRCORNER_H
