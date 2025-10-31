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

    virtual ~CComPolyCmd()
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
