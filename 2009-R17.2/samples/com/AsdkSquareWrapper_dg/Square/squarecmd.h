//
// (C) Copyright 1999-2002 by Autodesk, Inc. 
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

// squarecmd.h : Declaration of the CAsdkSquareCmd class

#ifndef __SQUARECMD_H_
#define __SQUARECMD_H_

#define DISPID_NUMBER       0x01
#define DISPID_SQUARESIZE   0x02
#define DISPID_CENTERPOINT  0x03

#define DEFINE_CMDFLAG(flagName, dispid)        \
public:                                         \
    bool flagName() { return ((m_bits & (0x01 << dispid)) == 1); };




class ATL_NO_VTABLE CAsdkSquareCmd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPropertyNotifySink
{
public:
	CAsdkSquareCmd()
        : m_pDoc(NULL)
	{
        m_pDoc = NULL;
        m_bits = 0;
	}

DECLARE_NOT_AGGREGATABLE(CAsdkSquareCmd)

BEGIN_COM_MAP(CAsdkSquareCmd)
	COM_INTERFACE_ENTRY(IPropertyNotifySink)
END_COM_MAP()


// IPropertyNotifySink
	STDMETHOD(OnChanged)(DISPID dispid) 
    {
        m_bits |= 0x01 << dispid;
        return S_OK;
    };
	
    STDMETHOD(OnRequestEdit)(DISPID dispid) { return S_OK; };

// C++ Methods
public:
    void SetDocument(AcApDocument *pDoc) { m_pDoc = pDoc; };

protected:
    void InterruptPrompt() 
    { 
        if (NULL != m_pDoc)
            acDocManager->sendModelessInterrupt(m_pDoc);
    };

private:
    AcApDocument *m_pDoc;
    long m_bits;
    
    DEFINE_CMDFLAG(GotNumber, DISPID_NUMBER);
    DEFINE_CMDFLAG(GotSquareSize, DISPID_SQUARESIZE);
    DEFINE_CMDFLAG(GotCenterPoint, DISPID_CENTERPOINT);
};

#endif //__SQUARECMD_H_

