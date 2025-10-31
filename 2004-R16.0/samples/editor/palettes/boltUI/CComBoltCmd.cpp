//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
#include "CComBoltCmd.h"

HRESULT CComBoltCmd::OnChanged(DISPID dispId)
{
    switch(dispId) {
        case DISPID_ALIGNMENT:
           bGotAlignment = true;
           break;
        case DISPID_HEADDIAMETER:
           bGotHeadDiameter = true;
           break;
        case DISPID_HEADHEIGHT:
           bGotHeadHeight = true;
           break;
        case DISPID_HEADSIDES:
           bGotHeadSides = true;
           break;
        case DISPID_MATERIALNAME:
           bGotMaterialName = true;
           break;
        case DISPID_POSITION:
           bGotPosition = true;
           break;
        case DISPID_SHAFTDIAMETER:
           bGotShaftDiameter = true;
           break;
		case DISPID_SHAFTLENGTH:
           bGotShaftLength = true;
           break;
		case DISPID_PARTNUMBER:
           bGotPartNumber = true;
           break;
		case DISPID_THREADLENGTH:
           bGotThreadLength = true;
           break;
		case DISPID_THREADWIDTH:
           bGotThreadWidth = true;
           break;
        default:
           break;
    }
    InterruptPrompt();
    return S_OK;
}

HRESULT CComBoltCmd::OnRequestEdit(DISPID dispId)
{
    return S_OK;
}

void CComBoltCmd::InterruptPrompt()
{
    if (NULL != m_pDoc)
    {
        acDocManager->sendModelessInterrupt(m_pDoc);
		// CPH RTMODELESS workaround
		bModelessInterrupt = true;
    }
}

