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
