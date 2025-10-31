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
// From PolySamp. 

// Once connected to the wrapper (CBolt) at its connection point, 
// this object functions as the listener/handler object for the wrapper's 
// property modified events. 
// In other words, it functions as a "sink" for the wrapper. 
// Any property modification through IBolt will call the sink's OnChanged method

#ifndef _ASDK_COMBOLTCMD_H
#define _ASDK_COMBOLTCMD_H

#include "stdafx.h"
#include "acdocman.h"
#include "rxobject.h"

// DISPIDs for resources
#define DISPID_ALIGNMENT        0x00000001
#define DISPID_HEADDIAMETER     0x00000002
#define DISPID_HEADHEIGHT       0x00000003
#define DISPID_HEADSIDES        0x00000004
#define DISPID_MATERIALNAME     0x00000005
#define DISPID_POSITION         0x00000006
#define DISPID_SHAFTDIAMETER    0x00000007
#define DISPID_SHAFTLENGTH      0x00000008
#define DISPID_PARTNUMBER       0x00000009
#define DISPID_THREADLENGTH     0x0000000A
#define DISPID_THREADWIDTH      0x0000000B


#define DEFINE_CMDFLAG(flagName)                \
private:                                        \
    bool b##flagName;                           \
public:                                         \
    bool flagName() { return b##flagName;};

class ATL_NO_VTABLE CComBoltCmd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPropertyNotifySink
{
public:
	CComBoltCmd()
        : m_pDoc(NULL),
		  bGotAlignment(false),
          bGotHeadDiameter(false),
          bGotHeadHeight(false),
          bGotHeadSides(false),
          bGotMaterialName(false),
          bGotPosition(false),
          bGotShaftDiameter(false),
          bGotShaftLength(false),
		  bGotPartNumber(false),
		  bGotThreadLength(false),
		  bGotThreadWidth(false),
		  bModelessInterrupt(false) // CPH RTMODELESS workaround
	{
	}

DECLARE_NOT_AGGREGATABLE(CComBoltCmd)

BEGIN_COM_MAP(CComBoltCmd)
	COM_INTERFACE_ENTRY(IPropertyNotifySink)
END_COM_MAP()


// IPropertyNotifySink
	STDMETHOD(OnChanged)(DISPID dispid);
	STDMETHOD(OnRequestEdit)(DISPID dispid);

// C++ Methods
public:
    void SetDocument(AcApDocument *pDoc) {m_pDoc = pDoc;};
	bool bModelessInterrupt;// CPH RTMODELESS workaround

protected:
    void InterruptPrompt();

private:
    AcApDocument *m_pDoc;
    
    DEFINE_CMDFLAG(GotAlignment);
    DEFINE_CMDFLAG(GotHeadDiameter);
    DEFINE_CMDFLAG(GotHeadHeight);
    DEFINE_CMDFLAG(GotHeadSides);
    DEFINE_CMDFLAG(GotMaterialName);
    DEFINE_CMDFLAG(GotPosition);
    DEFINE_CMDFLAG(GotShaftDiameter);
	DEFINE_CMDFLAG(GotShaftLength);
	DEFINE_CMDFLAG(GotPartNumber);
	DEFINE_CMDFLAG(GotThreadLength);
	DEFINE_CMDFLAG(GotThreadWidth);

};

#endif;