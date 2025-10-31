#ifndef     _ACGRADTHUMB_H
#define     _ACGRADTHUMB_H
//
//  (C) Copyright 1992-2002 by Autodesk, Inc.
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
//  DESCRIPTION:  Definition of CAcGradientThumbEngine
//                
//

#include "dbcolor.h"

// CAcGradientThumbnailEngine defines the interface to the gradient thumbnail generation engine.
//
// Use the function createGradientThumbnailEngine() to get a pointer to an instace of the engine.
//
// When finished with the engine the pointer returned by createGradientThumbnailEngine() should be deleted
//
class CAcGradientThumbnailEngine
{
    public:
        virtual ~CAcGradientThumbnailEngine() {};

        virtual Acad::ErrorStatus gradientThumbnailsSetRotation( double angle ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetShift( bool bShifted ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetStartColor( AcCmEntityColor startColor ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetStopColor( AcCmEntityColor stopColor ) = 0;

        virtual Acad::ErrorStatus gradientThumbnailsRender(void) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsDrawBitmap( int gradientNumber, HDC hDC, int xPos, int yPos ) = 0;

};

CAcGradientThumbnailEngine *createGradientThumbnailEngine();


#endif // _ACGRADTHUMB_H