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

#ifndef ARXDBGUIPRPOINT_H
#define ARXDBGUIPRPOINT_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrBase:
**
**  **jma
**
*************************************/

class ArxDbgUiPrPoint : public ArxDbgUiPrBase {

public:
                        ArxDbgUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList);
                        ArxDbgUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt);
    virtual             ~ArxDbgUiPrPoint();

    virtual Status      go();             // issue the prompt
    const AcGePoint3d&  value()    const;

    const AcGePoint3d&  basePt() const;
    void                setBasePt(const AcGePoint3d& basePt);
    void                setUseBasePt(bool useIt);
    void                setUseDashedLine(bool useIt);
    void                setNoLimitsCheck(bool noCheck);
    void                setAllowNone(bool allowIt);

protected:
    AcGePoint3d         m_value;
    AcGePoint3d         m_basePt;
    bool		        m_useBasePt;
    bool		        m_useDashedLine;
    bool			    m_noLimCheck;
    bool			    m_allowNone;

private:
        // helper functions
    void                init();

        // outlawed functions
                        ArxDbgUiPrPoint(const ArxDbgUiPrPoint&);
    ArxDbgUiPrPoint&	operator=(const ArxDbgUiPrPoint&);
};

#endif  // ARXDBGUIPRPOINT_H
