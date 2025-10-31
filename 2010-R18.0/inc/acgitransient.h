//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2002-2009 by Autodesk, Inc. 
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
// This API extends AcGi to support transient.
//

#pragma once

typedef enum{
    kAcGiMain = 0,
    kAcGiSprite,
    kAcGiDirectShortTerm,
    kAcGiHighlight,
    kAcGiDirectTopmost,
    kAcGiContrast,
    kAcGiDrawingModeCount
} AcGiTransientDrawingMode;

class AcGiTransientManager
{
public:
    virtual             ~AcGiTransientManager   (void) { }

    virtual bool        addTransient            (AcGiDrawable* pDrawable,
                                                 AcGiTransientDrawingMode mode,
                                                 int subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        eraseTransient          (AcGiDrawable* pDrawable,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        eraseTransients         (AcGiTransientDrawingMode mode,
                                                 int subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual void        updateTransient         (AcGiDrawable* pDrawable,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        addChildTransient       (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0;

    virtual bool        eraseChildTransient     (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0;

    virtual void        updateChildTransient    (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0; 

    virtual int         getFreeSubDrawingMode   (AcGiTransientDrawingMode mode,
                                                 int& subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;
};

AcGiTransientManager* acgiGetTransientManager();
void acgiSetTransientManager(AcGiTransientManager* transientManager);
