//   Copyright (C) 1998-2007 by Autodesk, Inc.
//
//     Permission to use, copy, modify, and distribute this software
//     for any purpose is restricted by the VIP Subscription program
//     license agreement.  This application was developed exclusively
//     for distribution by the VIP subscription program and may not
//     be posted pubicly, modified, copied, or distributed by any other
//     methods. 
//
//     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
//     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
//     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
//     UNINTERRUPTED OR ERROR FREE.
//
//     Use, duplication, or disclosure by the U.S. Government is subject to 
//     restrictions set forth in FAR 52.227-19 (Commercial Computer 
//     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
//     (Rights in Technical Data and Computer Software), as applicable. 
//

// AsdkInputPointFilter methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "acgi.h"
#include "dbents.h"
#include "tchar.h"

#include "filter.h"

Acad::ErrorStatus
AsdkInputPointFilter::processInputPoint(const AcEdInputPoint& input, AcEdInputPointFilterResult& output)
{
    if ( !input.pointComputed() )
        // Points cannot be computed in the Filter
        // Forced picking may be enabled
        return Acad::eOk;

    if ( m_changePoint )
    {
        // Change the computed point to an offset of (0.2, 0.2, 0.2)
        // and draw a circular glyph at that ne point
        output.setNewPoint(input.computedPoint() + AcGeVector3d(0.2,0.2,0.0));
        input.drawContext()->geometry().circle( output.newPoint(), 0.1, AcGeVector3d::kZAxis );
        output.setDisplayOsnapGlyph(true);

        if ( 0 != input.pickedEntities().length() )
        {
            // Add a tooltip to line entities under the cursor
            //
            AcDbLine *pLine;
            if ( Acad::eOk == acdbOpenObject( pLine, input.pickedEntities()[X], kForRead ))
            {
                pLine->close();
                output.setNewTooltipString(_T("This is a line!!!"));
            }
        }
    }
    return Acad::eOk;
}
