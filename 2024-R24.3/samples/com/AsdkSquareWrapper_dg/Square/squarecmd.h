//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

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

