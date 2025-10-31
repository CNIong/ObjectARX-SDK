//
// Copyright (C) 1994-1998 by Autodesk, Inc.
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

// Display Interface for IE

/*
* Begin multiple inclusion protection...
*/
#ifndef	_iewin_h
#define	_iewin_h

#if !defined(_INC_WINDOWS) && !defined(_WINDOWS_)
#include <windows.h>
#endif /* _windows_h */

extern "C" {
void ieWinPaint(Ief *p, HDC hDC, int xDest, int yDest,
                                   int destWidth = 0, int destHeight = 0, 
                                   UInt rasOp = SRCCOPY);

void ieWinSetDIBPalette(UInt8 *pPal, int sizePal,
                                                    unsigned int colorUse);
}

#endif /* _iewin_h */
