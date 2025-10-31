//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// AsdkInputPointFilter methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _MSC_VER
#include <Windows.h>
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
