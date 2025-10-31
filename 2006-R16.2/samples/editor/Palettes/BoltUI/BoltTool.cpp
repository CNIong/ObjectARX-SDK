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
// BoltTool.cpp : Implementation of CBoltTool

#include "BoltTool.h"
#include "boltjig.h"

// CBoltTool

TCHAR szBoltToolName[MAX_PATH]={"BoltTool"};
TCHAR szBoltImage[MAX_PATH]={"IDB_BOLTIMAGE"};
static UINT m_nMenuIds[MAX_MENU_ENTRIES] = {0,0,0,0};

STDMETHODIMP CBoltTool::get_HeadSides(LONG* pVal)
{
	*pVal=m_HeadSides;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadSides(LONG newVal)
{
	m_HeadSides=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_HeadHeight(DOUBLE* pVal)
{
	*pVal=m_HeadHeight;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadHeight(DOUBLE newVal)
{
	m_HeadHeight=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ShaftLength(DOUBLE* pVal)
{
	*pVal=m_ShaftLength;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ShaftLength(DOUBLE newVal)
{
	m_ShaftLength=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ThreadLength(DOUBLE* pVal)
{
	*pVal=m_ThreadLength;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ThreadLength(DOUBLE newVal)
{
	m_ThreadLength=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ThreadWidth(DOUBLE* pVal)
{
	*pVal=m_ThreadWidth;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ThreadWidth(DOUBLE newVal)
{
	m_ThreadWidth=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_HeadDiameter(DOUBLE* pVal)
{
	*pVal=m_HeadDiameter;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadDiameter(DOUBLE newVal)
{
	m_HeadDiameter=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ShaftDiameter(DOUBLE* pVal)
{
	*pVal=m_ShaftDiameter;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ShaftDiameter(DOUBLE newVal)
{
	m_ShaftDiameter=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_MaterialName(BSTR *pVal)
{
	CComBSTR bStr(m_MaterialName);
	bStr.CopyTo(pVal);
	return S_OK;
}

STDMETHODIMP CBoltTool::put_MaterialName(BSTR newVal)
{
	CComBSTR bStr(newVal);
	COLE2T szMaterialName(bStr);
	_tcscpy(m_MaterialName,szMaterialName);
	return S_OK;
}

STDMETHODIMP CBoltTool::get_PartNumber(BSTR *pVal)
{
	CComBSTR bStr(m_PartNumber);
	bStr.CopyTo(pVal);
	return S_OK;}

STDMETHODIMP CBoltTool::put_PartNumber(BSTR newVal)
{
	CComBSTR bStr(newVal);
	COLE2T szPartNumber(bStr);
	_tcscpy(m_PartNumber,szPartNumber);
	return S_OK;
}

STDMETHODIMP CBoltTool::executeCallback()
{
	// First determine that AutoCAD is properly prepared for execution of this tool (i.e. no commands)
	struct resbuf res;
	acedGetVar("CMDNAMES",&res);
	if(strlen(res.resval.rstring))
	{
		free(res.resval.rstring);
		res.resval.rstring=NULL;
		return E_FAIL;
	}
	if(res.resval.rstring)
		free(res.resval.rstring);
	res.resval.rstring=NULL;
	
	CComObject <AsdkBoltJig> PromptObject; // Instantiate a Prompt for the Employee
	
	// Set the color, layer, Material and Part Number.
	asdkBolt *pBolt=(asdkBolt*)asdkBolt::cast(PromptObject.GetObjectPointer ());
	if(pBolt)
	{
		// Color, Color Name and Book Name
		AcCmColor color;
		color.setColor(m_Color.color());
		color.setNames(m_Color.colorName(),m_Color.bookName());
		
		pBolt->setColor(color);
		pBolt->setLayer(CT2A(m_szLayer));
		pBolt->setMaterialName(CT2A(m_MaterialName));
		pBolt->setPartNumber(CT2A(m_PartNumber));
	}
	else
		return E_FAIL;
	
	// Specify that we're setting the Tool's properties to the Prompt so they are not jigged.
	PromptObject.m_bSetFromTool=true;
	PromptObject.m_HeadSides=m_HeadSides;
	PromptObject.m_HeadHeight=m_HeadHeight;
	PromptObject.m_ShaftLength=m_ShaftLength;
	PromptObject.m_ShaftDiameter=m_ShaftDiameter;
	PromptObject.m_ThreadLength=m_ThreadLength;
	PromptObject.m_ThreadWidth=m_ThreadWidth;
	PromptObject.m_HeadDiameter=m_HeadDiameter;
				
	// Enter the prompt loop
	AcDbObjectId PromptId=PromptObject.promptLoop();

	acedPostCommandPrompt();
	
	return S_OK;
}

STDMETHODIMP CBoltTool::dropCallback(AcDbEntity *pDropEntity)
{
	// Cast the pointer first, and make sure it is successful.	
	asdkBolt *pBolt=(asdkBolt*)asdkBolt::cast(pDropEntity);
	if(pBolt)
	{
		m_Color.setColor(pBolt->color().color());
		m_Color.setNames(pBolt->color().colorName(),pBolt->color().bookName());
		_tcscpy(m_szLayer,CA2T(pBolt->layer()));
		m_bColorUnspecified=FALSE; // Set these two to not be Unspecified.
		m_bLayerUnspecified=FALSE;
		// For specifying the state of controls other than these two, you will need to use
		// the parent class' ISpecifiedAllowed() and SetUnspecified()

		_tcscpy(m_MaterialName,CA2T(pBolt->materialName));
		_tcscpy(m_PartNumber,CA2T(pBolt->partNumber));
		
		m_HeadSides=pBolt->getHeadSides();
		m_HeadHeight=pBolt->getHeadHeight();
		m_ShaftLength=pBolt->getShaftLength();
		m_ShaftDiameter=pBolt->getShaftDiameter();
		m_ThreadLength=pBolt->getThreadLength();
		m_ThreadWidth=pBolt->getThreadWidth();
		m_HeadDiameter=pBolt->getHeadDiameter();
		
		return S_OK;
	}
	return E_FAIL;
	// You don't need to worry about closing the object passed in...
}


STDMETHODIMP CBoltTool::New()
{
	// Initialize the members
	m_HeadSides=6;
	m_HeadHeight=2.0f;
	m_ShaftLength=10.0f;
	m_ShaftDiameter=2.0f;
	m_ThreadLength=3.0f;
	m_ThreadWidth=0.2f;
	m_HeadDiameter=5.0f;
	
	m_Color.setColor(0);
	m_Color.setNames(NULL,NULL);// Initialize the color names as well... 
	
	_tcscpy(m_szLayer,_T("0"));
	_tcscpy(m_MaterialName,_T("Stainless"));
	_tcscpy(m_PartNumber,_T("Unassigned"));
    	
	return S_OK;
}
STDMETHODIMP CBoltTool::get_EditMode(/*[out, retval]*/ long* pVal)
{
	*pVal=kEditDefault | kEditMultiple;
	 return S_OK;
}
STDMETHODIMP CBoltTool::BeginMultipleEdit(VARIANT tools,  VARIANT stockToolIds)
{
	return S_OK;
}
//Check if the menu already contains the menu item specified by MenuString
BOOL FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (_tcscmp(str, MenuString) == 0))
         return true;
   }

   return false;
}
//Add our own menu items to the standard context menu
STDMETHODIMP CBoltTool::Customize(/* [in] */ int nContextFlag,
							/* [in] */ DWORD hMenu,
							/* [in] */ UINT idCmdFirst,
						/* [in] */ UINT idCmdLast,
						/* [in] */ GUID *pPaletteId,
						/* [retval][out] */ DWORD *pFlag)
{
	
	AcTcPalette* pPalette = (AcTcPalette*)(AcTcGetManager()->FindItem(*pPaletteId));
	ASSERT(pPalette != NULL);
	TCHAR pszString[128];
	pPalette->GetName(pszString, 128);
	if (_tcscmp(pszString, "BoltPalette")!= 0)	
		return E_NOTIMPL;
	CMenu* menu = new CMenu;
	switch (nContextFlag)
	{
		//Add an entry to palette set tab context menu
		case kContextMenuPaletteSetTab:	
			if (menu->Attach(HMENU(hMenu))) 
			{	
				if( !FindMenuItem(menu,"PaletteSet Menu"))
				{
					m_nMenuIds[0] = idCmdFirst + 0;
					menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[0], "PaletteSet Menu");
				}
				menu->Detach();
			}
			break;
		//Add an entry to palette background context menu
		case kContextMenuPaletteBackground:
			
			
			if (menu->Attach(HMENU(hMenu))) 
			{	
				if( !FindMenuItem(menu,"Background Menu")&& (idCmdLast-idCmdFirst)>=1)
				{
					m_nMenuIds[1] = idCmdFirst +1;
					menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[1], "Background Menu");
				}
				menu->Detach();
			}
			break;
		//Add an entry to palette set caption context menu
		case kContextMenuPaletteSetCaption:
	
			
			if (menu->Attach(HMENU(hMenu))) 
			{	
				if( !FindMenuItem(menu,"Caption Menu")&& (idCmdLast-idCmdFirst)>=2)
				{
					m_nMenuIds[2] = idCmdFirst + 2;
					menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[2], "Caption Menu");
				}
				menu->Detach();
			}
			break;
		//Add an entry to palette set option Button context menu
		case kContextMenuPaletteSetOptionButton:

			
			if (menu->Attach(HMENU(hMenu))) 
			{	
				if( !FindMenuItem(menu,"Option Button Menu")&& (idCmdLast-idCmdFirst)>=3)
				{
					m_nMenuIds[3] = idCmdFirst + 3;
					menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[3], "Option Button Menu");
				}
				menu->Detach();
			}
		break;
	}
	delete menu;
	return S_OK;
}
// execute when custom menu items are clicked
STDMETHODIMP CBoltTool::InvokeMenuCommand(/* [in] */ UINT idCmd,
									/* [in] */ GUID *pPaletteId,
									/* [in] */ DWORD hWnd,
								    /* [retval][out] */ DWORD *pFlag)
{
	if (idCmd == m_nMenuIds[0])
			::AfxMessageBox("Palette Set Menu chosen");
	
	else if (idCmd == m_nMenuIds[1])
	{
		::AfxMessageBox("Backgroud Menu chosen");
		//Add an aluminum bolt to the palette
		AcTcPalette* pPalette = (AcTcPalette*)(AcTcGetManager()->FindItem(*pPaletteId));
		ASSERT(pPalette != NULL);
		New();
		_tcscpy(m_MaterialName,_T("Aluminum"));
		_tcscpy(m_PartNumber,_T("Unassigned"));
		if(!CreateToolATC(pPalette,_T("Aluminum Bolt"),_T("IDB_BOLTALUMINUM")))
			acutPrintf("\nFailed to create an alumninum bolt\n");
		// Refresh the Tool Palette with the above changes.
		AcTcGetManager()->LoadCatalogs();
	}
	else if(idCmd == m_nMenuIds[2])
			::AfxMessageBox("Caption Menu chosen");
	else if(idCmd == m_nMenuIds[3])
			::AfxMessageBox("Option Button Menu chosen");
	return S_OK;
}

