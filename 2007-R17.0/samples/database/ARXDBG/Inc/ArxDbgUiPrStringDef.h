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

#ifndef ARXDBGUIPRSTRINGDEF_H
#define ARXDBGUIPRSTRINGDEF_H

#include "ArxDbgUiPrString.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrStringDef:
**
**  **jma
**
*************************************/

class ArxDbgUiPrStringDef : public ArxDbgUiPrString {

public:
                    ArxDbgUiPrStringDef(LPCTSTR msg, LPCTSTR def, bool allowSpaces = true);
    virtual         ~ArxDbgUiPrStringDef();

    virtual Status  go();    // issue the prompt

private:
        // data members
    CString		m_default;

        // outlawed functions
							ArxDbgUiPrStringDef(const ArxDbgUiPrStringDef&);
    ArxDbgUiPrStringDef&	operator=(const ArxDbgUiPrStringDef&);
};



#endif  // ARXDBGUIPRSTRINGDEF_H
