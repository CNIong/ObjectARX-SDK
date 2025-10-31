// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
// POLYCMD.CPP
//
// DESCRIPTION:
//
// This file contains an object for creating a polysamp object using
// the Property Palette.
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>


#include "rxobject.h"
#include "acadi.h"

#include ".\compoly\compoly_i.h"
#include ".\compoly\compolygon.h"

#include "acdocman.h"
#include "polycmd.h"




HRESULT CComPolyCmd::OnChanged(DISPID dispId)
{
    switch(dispId) {
        case DISPID_TEXTSTRING:
           bGotTextString = true;
           break;
        case DISPID_NUMSIDES:
           bGotNumSides = true;
           break;
        case DISPID_NORMAL:
           bGotNormal = true;
           break;
        case DISPID_CENTER:
           bGotCenter = true;
           break;
        case DISPID_STARTPOINT:
           bGotStartPoint = true;
           break;
        case DISPID_TEXTSTYLENAME:
           bGotTextStyleName = true;
           break;
        case DISPID_ELEVATION:
           bGotElevation = true;
           break;
        default:
           break;
    }
    InterruptPrompt();
    return S_OK;
}

HRESULT CComPolyCmd::OnRequestEdit(DISPID dispId)
{
    return S_OK;
}

void CComPolyCmd::InterruptPrompt()
{
    if (NULL != m_pDoc)
    {
        acDocManager->sendModelessInterrupt(m_pDoc);
    }
}



    
       

    
