//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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


#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning - atlcom.h
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#pragma warning(pop) // C4265


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



    
       

    
