// (C) Copyright 1996-2002 by Autodesk, Inc. 
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
// POLYCMD.H  
//
// DESCRIPTION:
//
// This file contains an object for creating a polysamp object using
// the Property Palette.

#define DEFINE_CMDFLAG(flagName)                \
private:                                        \
    bool b##flagName;                           \
public:                                         \
    bool flagName() { return b##flagName;};

class ATL_NO_VTABLE CComPolyCmd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPropertyNotifySink
{
public:
	CComPolyCmd()
        : m_pDoc(NULL),
          bGotNumSides(false),
          bGotTextString(false),
          bGotCenter(false),
          bGotNormal(false),
          bGotStartPoint(false),
          bGotTextStyleName(false),
          bGotElevation(false)
	{
	}

DECLARE_NOT_AGGREGATABLE(CComPolyCmd)

BEGIN_COM_MAP(CComPolyCmd)
	COM_INTERFACE_ENTRY(IPropertyNotifySink)
END_COM_MAP()


// IPropertyNotifySink
	STDMETHOD(OnChanged)(DISPID dispid);
	STDMETHOD(OnRequestEdit)(DISPID dispid);

// C++ Methods
public:
    void SetDocument(AcApDocument *pDoc) {m_pDoc = pDoc;};

protected:
    void InterruptPrompt();

private:
    AcApDocument *m_pDoc;
    
    DEFINE_CMDFLAG(GotNumSides);
    DEFINE_CMDFLAG(GotTextString);
    DEFINE_CMDFLAG(GotCenter);
    DEFINE_CMDFLAG(GotNormal);
    DEFINE_CMDFLAG(GotStartPoint);
    DEFINE_CMDFLAG(GotTextStyleName);
    DEFINE_CMDFLAG(GotElevation);
};
