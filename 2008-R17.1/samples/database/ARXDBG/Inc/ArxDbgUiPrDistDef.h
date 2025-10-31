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

#ifndef ARXDBGUIPRDISTDEF_H
#define ARXDBGUIPRDISTDEF_H

#include "ArxDbgUiPrDist.h"


/****************************************************************************
**
**  CLASS ArxDbgUiPrDistDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrDistDef : public ArxDbgUiPrDist {

public:
                ArxDbgUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type, double def);
                ArxDbgUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type,
                        const AcGePoint3d& basePt, double def);
    virtual     ~ArxDbgUiPrDistDef();

    virtual Status go();       // issue the prompt

private:
        // data members
    double      m_default;

        // outlawed functions
                        ArxDbgUiPrDistDef(const ArxDbgUiPrDistDef&);
    ArxDbgUiPrDistDef&	operator=(const ArxDbgUiPrDistDef&);
};

#endif  // ARXDBGUIPRDISTDEF_H
