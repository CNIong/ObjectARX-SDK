//
//
// (C) Copyright 2003-2004 by Autodesk, Inc. 
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
#pragma once

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
#define DISPID_COLOR	        0x0000000C

#include "stdafx.h"
#include "resource.h"
#include "AsdkPromptBase.h"

extern TCHAR *szDefaultValues [8] ;

class AsdkBoltJig : public  AsdkPromptBase<IBolt, &CLSID_Bolt>
{

public:
	bool m_bSetFromTool;

	long m_HeadSides;
	double m_HeadHeight;
	double m_ShaftLength;
	double m_ThreadLength;
	double m_ThreadWidth;
	double m_HeadDiameter;
	double m_ShaftDiameter;

public:
   BEGIN_PROMPT_MAP(AsdkBoltJig)
		PROMPT_ENTRY("HeadSides", DISPID_HEADSIDES, RTLONG, 0, IDS_HEADSIDES_PROMPT, false)
		PROMPT_ENTRY("HeadHeight", DISPID_HEADHEIGHT, RTREAL, 0, IDS_HEADHEIGHT_PROMPT, false)
		PROMPT_ENTRY("ShaftLength", DISPID_SHAFTLENGTH, RTREAL, 0, IDS_SHAFTLENGTH_PROMPT, false)
		PROMPT_ENTRY("ThreadLength", DISPID_THREADLENGTH, RTREAL, 0, IDS_THREADLENGTH_PROMPT, false)
		PROMPT_ENTRY("ThreadWidth", DISPID_THREADWIDTH, RTREAL, 0, IDS_THREADWIDTH_PROMPT, false)
		PROMPT_ENTRY("Position", DISPID_POSITION, RT3DPOINT, 0, IDS_POSITION_PROMPT, true)
		PROMPT_ENTRY("HeadDiameter", DISPID_HEADDIAMETER, RTREAL, 0, IDS_HEADDIAMETER_PROMPT, true)
		PROMPT_ENTRY("ShaftDiameter", DISPID_SHAFTDIAMETER, RTREAL, 0, IDS_SHAFTDIAMETER_PROMPT, true)
	END_PROMPT_MAP
	 
	DEFINE_SAMPLER(AcEdJig::kCrosshair,(UserInputControls)(kNullResponseAccepted| kAccept3dCoordinates));

	// Added to support prompting from a tool.
	virtual void constructorCallback ()
	{
		m_bSetFromTool =false ;
	}
	
	virtual void setPropertyDefaults (int index =-1)
	{
		AsdkPromptBase<IBolt, &CLSID_Bolt>::setPropertyDefaults (index) ;
		if(!m_bSetFromTool)
			return;

		PROMPT_MAP_ENTRY *pPromptMap=GetPromptMap();
		m_pWrapperObject->put_headSides(m_HeadSides);
		pPromptMap [0].m_bGotThisProperty=true;
		m_pWrapperObject->put_headHeight(m_HeadHeight);
		pPromptMap [1].m_bGotThisProperty=true;
		m_pWrapperObject->put_shaftLength(m_ShaftLength);
		pPromptMap [2].m_bGotThisProperty=true;
		m_pWrapperObject->put_threadLength(m_ThreadLength);
		pPromptMap [3].m_bGotThisProperty=true;
		m_pWrapperObject->put_threadWidth(m_ThreadWidth);
		pPromptMap [4].m_bGotThisProperty=true;
		m_pWrapperObject->put_headDiameter(m_HeadDiameter);
		pPromptMap [6].m_bGotThisProperty=true;
		m_pWrapperObject->put_shaftDiameter(m_ShaftDiameter);
		pPromptMap [7].m_bGotThisProperty=true;
	}

	virtual bool defaultValueCallback (int index, LPTSTR szDefaultVal) {
		assert ( index >= 0 && index <= 7 ) ;
		_tcscpy (szDefaultVal, szDefaultValues [index]) ;
		return (true) ;
	}

	virtual HINSTANCE GetResourceInstance ()
	{
		return (_hdllInstance) ;
	}

	AcDbObject *GetObjectPointer ()
	{
		return (m_pDbrObject) ;
	}

};
