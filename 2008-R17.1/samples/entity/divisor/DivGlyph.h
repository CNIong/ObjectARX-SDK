//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#include <adslib.h>
#include <acgi.h>
#include <acgiutil.h>
#include <geassign.h>

// Note: All template class functions have been inlined in the .h, due to the bug
// described in the MS Knowledge Base Article Q128789:
// BUG: LNK2001 on Member Function When Use Nested Class Template
 
template <int i> class AsdkDivGlyph : public AcGiGlyph
{
public:
    AsdkDivGlyph( const TCHAR *szDesc ) {
        m_szDesc = _tcsdup( szDesc );
    }
    virtual ~AsdkDivGlyph(){
        delete m_szDesc; m_szDesc = NULL;
    }
    virtual Acad::ErrorStatus setLocation( const AcGePoint3d& dcsPoint ) {
        m_ptPosDc = dcsPoint;
        return Acad::eOk;
    }
    virtual void viewportDraw( AcGiViewportDraw* vportDrawContext ) {
        // Calculate the size of the glyph in WCS (use for text height factor)
        int glyphPixels = acdbCustomOsnapManager()->osnapGlyphSize();
        AcGePoint2d glyphSize;
        vportDrawContext->viewport().getNumPixelsInUnitSquare( m_ptPosDc, glyphSize );
        double glyphHeight = glyphPixels / glyphSize[ Y ];

        // Get the extents of the glyph text, so we can centre it
        AcGiTextStyle style;
        AcGePoint2d ptExt = style.extents( m_szDesc, Adesk::kFalse, -1, Adesk::kFalse );

        struct resbuf rbFrom, rbTo;
        rbFrom.restype = RTSHORT;
        rbFrom.resval.rint = 2; // From DCS
        rbTo.restype = RTSHORT;
        rbTo.resval.rint = 0; // To WCS

        // Translate the X-axis of the DCS to WCS co-ordinates (as a displacement vector)
        AcGeVector3d ptDir;
        acedTrans( asDblArray( AcGeVector3d::kXAxis ), &rbFrom, &rbTo, 1, asDblArray( ptDir ));

        // Translate the centre of the glyph from DCS to WCS co-ordinates
        AcGePoint3d ptPos, ptCen;
        AcGeVector3d vecExt( ptExt[ X ] / 2, ptExt[ Y ] / 2, 0 );
        ptPos = m_ptPosDc - vecExt / 2; 
        if ( RTNORM != acedTrans( asDblArray( ptPos ), &rbFrom, &rbTo, 0, asDblArray( ptCen )))
           ptCen = m_ptPosDc;

        // Draw the centred text representing the glyph
        vportDrawContext->geometry().text( ptCen, vportDrawContext->viewport().viewDir(), ptDir, glyphHeight, 1.0, 0.0, m_szDesc );
    }

private:
    AcGePoint3d m_ptPosDc;
    TCHAR *m_szDesc;
};
