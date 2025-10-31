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
// BoltTool.cpp : Implementation of CBoltTool
#include "stdafx.h"
#include "BoltTools.h"
#include "BoltTool.h"
#include "AcTc_i.c"
#include "actc.h"
#include "AcPi.h"
#include "AcPExCtl.h"
#include "AcPExCtl_i.c"
#include "dbents.h"
#include "dbobjptr.h"
#include "..\boltObject\asdkBolt.h"
#include "dbsol3d.h"
#include "..\boltUi\boltjig.h"


void WritePropertiesToCatalog(CBoltProperties props,MSXML::IXMLDOMNode* pParentNode);
CString createUniqueImageName(void);

/////////////////////////////////////////////////////////////////////////////
// CBoltTool

CLIPFORMAT CBoltTool::mcfAutoCAD = NULL;

BOOL GetUnknownArrays(int nCount, 
                      IUnknown** pObjUnkArray, 
                      VARIANT* pStatUnkArray, 
                      VARIANT* pDynPMUnkArrays);

BOOL                    GetChildNodeValue   (MSXML::IXMLDOMNode* pNode,
                                             LPCTSTR pszNodeName, 
                                             CString& sValue); 
BOOL                    GetChildNode        (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszNodeName, 
                                             MSXML::IXMLDOMNode** ppChild);
BOOL                    AddChildNode        (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszChildNodeName, 
                                             short nNodeType,
                                             MSXML::IXMLDOMNode** ppChild);
BOOL                    RemoveChildren      (MSXML::IXMLDOMNode* pNode);   

BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             char *sValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             double& fValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             long& lValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             GUID& guid);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              long lValue);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const GUID& guid);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const CString& sValue);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              double fValue);
STDMETHODIMP CBoltTool::CreateTool(/*[out, retval]*/ IUnknown** ppTool)
{
    return QueryInterface(IID_IUnknown, (void**) ppTool);
}

STDMETHODIMP CBoltTool::get_EditMode(/*[out, retval]*/ long* pVal)
{
    *pVal = kEditDefault;
    return S_OK;
}


STDMETHODIMP CBoltTool::GetStockTool(/*[out, retval]*/ IUnknown** ppToolClass)
{ 
    return E_NOTIMPL; 
}


STDMETHODIMP CBoltTool::SetToolProperties(/*[in]*/ IUnknown* pProp)
{
    HRESULT hr = pProp->QueryInterface(IID_IAcadToolProperties, (void**) &mpToolProp);
    return S_OK;
}


// Load the tool from the XML file...
STDMETHODIMP CBoltTool::Load(/*[in]*/ IUnknown* pNodeUnk)
{
   MSXML::IXMLDOMNodePtr pEntityNode = pNodeUnk;
    if (pEntityNode == NULL)
        return E_INVALIDARG;

    MSXML::IXMLDOMNodePtr pAttributeNode;
	
    if (GetChildNode(pEntityNode, "Entity", &pAttributeNode)) {
        MSXML::IXMLDOMNodePtr pChild;
		if (GetChildNode(pAttributeNode, "Part_Number", &pChild)) {
            GetAttributeValue(pChild, "Value",  partNumber );
        }
		if (GetChildNode(pAttributeNode, "Color", &pChild)) {
            GetAttributeValue(pChild, "Value", (long&) mnColor);
			GetAttributeValue(pChild, "Unspecified", (long&)mColorUnspecified);
        }
		if (GetChildNode(pAttributeNode, "Layer", &pChild)) {
            GetAttributeValue(pChild, "Value", mLayer);
			GetAttributeValue(pChild, "Unspecified", (long&)mLayerUnspecified);
        }
		if(GetChildNode(pEntityNode,"Bolt",&pAttributeNode)){
			if (GetChildNode(pAttributeNode, "Material", &pChild))
				GetAttributeValue(pChild, "Value", materialName);
			if (GetChildNode(pAttributeNode, "Head_Diameter", &pChild))
				GetAttributeValue(pChild, "Value", (double&) headDiameter);
			if (GetChildNode(pAttributeNode, "Head_Sides", &pChild))
				GetAttributeValue(pChild, "Value", (long&) headSides);
			if (GetChildNode(pAttributeNode, "Head_Height", &pChild))
				GetAttributeValue(pChild, "Value", (double&) headHeight);
			if (GetChildNode(pAttributeNode, "Shaft_Length", &pChild))
				GetAttributeValue(pChild, "Value", (double&) shaftLength);
			if (GetChildNode(pAttributeNode, "Shaft_Diameter", &pChild))
				GetAttributeValue(pChild, "Value", (double&) shaftDiameter);
			if (GetChildNode(pAttributeNode, "Thread_Length", &pChild))
				GetAttributeValue(pChild, "Value", (double&) threadLength);
			if (GetChildNode(pAttributeNode, "Thread_Width", &pChild))
				GetAttributeValue(pChild, "Value", (double&) threadWidth);
		}
	}
	return S_OK;
}

// Write the tool to the XML file...
STDMETHODIMP CBoltTool::Save(/*[in]*/ IUnknown* pXmlElement) 
{
    USES_CONVERSION;

    MSXML::IXMLDOMNodePtr pEntityNode = pXmlElement;
    if (pEntityNode == NULL)
        return E_INVALIDARG;

	if(bDroppedTool)
	{
		// We just created this tool, so the data portion has not been written yet...
		WritePropertiesToCatalog(props,pEntityNode); // ...so write it now!
		bDroppedTool=false;
		return S_OK;
	}

	MSXML::IXMLDOMNodePtr pAttributeNode;
   
	if (GetChildNode(pEntityNode, "Entity", &pAttributeNode)) {
        MSXML::IXMLDOMNodePtr pChild;
		if (GetChildNode(pAttributeNode, "Part_Number", &pChild)) {
            SetAttributeValue(pChild, "Value", (LPCTSTR) partNumber );
        }
		if (GetChildNode(pAttributeNode, "Color", &pChild)) {
            SetAttributeValue(pChild, "Value", (long) mnColor);
			SetAttributeValue(pChild, "Unspecified", (long)mColorUnspecified);
        }
        if (GetChildNode(pAttributeNode, "Layer", &pChild)) {
            SetAttributeValue(pChild, "Value", mLayer);
			SetAttributeValue(pChild, "Unspecified", (long)mLayerUnspecified);
        }
		if(GetChildNode(pEntityNode,"Bolt",&pAttributeNode)){
			if (GetChildNode(pAttributeNode, "Material", &pChild))
				SetAttributeValue(pChild, "Value", materialName);
			if (GetChildNode(pAttributeNode, "Head_Diameter", &pChild))
				SetAttributeValue(pChild, "Value", (double) headDiameter);
			if (GetChildNode(pAttributeNode, "Head_Sides", &pChild))
				SetAttributeValue(pChild, "Value", (long) headSides);
			if (GetChildNode(pAttributeNode, "Head_Height", &pChild))
				SetAttributeValue(pChild, "Value", (double) headHeight);
			if (GetChildNode(pAttributeNode, "Shaft_Length", &pChild))
				SetAttributeValue(pChild, "Value", (double) shaftLength);
			if (GetChildNode(pAttributeNode, "Shaft_Diameter", &pChild))
				SetAttributeValue(pChild, "Value", (double) shaftDiameter);
			if (GetChildNode(pAttributeNode, "Thread_Length", &pChild))
				SetAttributeValue(pChild, "Value", (double) threadLength);
			if (GetChildNode(pAttributeNode, "Thread_Width", &pChild))
				SetAttributeValue(pChild, "Value", (double) threadWidth);
		}
	}
    return S_OK; 
}

// Called when the tool is executed...
STDMETHODIMP CBoltTool::Execute(/*[in]*/ long lFlag, /*[in]*/ DWORD /*HWND*/ hWnd, /*[in]*/ DWORD point, /*[in]*/ DWORD dwKeyState)
{
    // Prevent multiple entries into this tool.
	static bool executeMutex=false;
	if(executeMutex)
		return  S_OK;
	executeMutex=true;
	
	// Set the focus to AutoCAD
	acedGetAcadDwgView()->SetFocus();
	
	// Lock the document
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    AcAxDocLock docLock( pDb, AcAxDocLock::kNormal );
    if(docLock.lockStatus() != Acad::eOk){
        return E_FAIL;
    }
    
	USES_CONVERSION;
	// Create the Bolt Jig manually (in the BoltUI module), and fill in the appropriate items.
	AsdkBoltJig jig;
		
	ACAD_COLOR acadColor=(ACAD_COLOR)mnColor;
	jig.mBolt->put_Color(acadColor);
	jig.mBolt->put_Layer(A2OLE(mLayer));
	jig.setHeadSides(headSides);
	jig.setHeadDiameter(headDiameter);
	jig.setHeadHeight(headHeight);
	jig.setShaftDiameter(shaftDiameter);
	jig.setShaftLength(shaftLength);
	jig.setThreadLength(threadLength);
	jig.setThreadWidth(threadWidth);
	jig.setPartNumber(partNumber);
	jig.setMaterialName(materialName);
	jig.inputInitialValues();
	
	 executeMutex=false;
	return S_OK;
}


STDMETHODIMP CBoltTool::GetData(/*[in]*/ VARIANT *pObjUnkArray, /*[in]*/ VARIANT *pDynUnkArray) 
{ 
    mhPreviewWnd = (HWND) pObjUnkArray->lVal;
	
	CComPtr<IUnknown> pUnk;
	QueryInterface(IID_IUnknown, (void**) &pUnk);
	GetUnknownArrays(1, &pUnk, pObjUnkArray, pDynUnkArray);
    return S_OK;
}


STDMETHODIMP CBoltTool::BeginEdit() 
{ 
	return S_OK;
}

// CPH V059GLV4
STDMETHODIMP CBoltTool::Dropped(/*[in]*/ BSTR bstrUrl)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBoltTool::Refreshed(/*[in]*/ BSTR bstrUrl)
{
	return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::SetEditorWindow(/*[in]*/ LONG /*HWND*/ hWndEditor, /*[in]*/ IUnknown*	pPropInspector)
{
	return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::ValidateEditChanges()
{
	return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::GetToolProperties(/*[out, retval]*/ IUnknown** pToolProp)
{
	return E_NOTIMPL;
}

//	STDMETHOD (Edit) (/*[in]*/ IUnknown* pProp,/*[in]*/ LONG /*HWND*/ hWndParent, /*[out]*/ VARIANT_BOOL* pRet 
//	STDMETHOD (EndEdit)(/*[in]*/ VARIANT_BOOL bEditCancelled);


STDMETHODIMP CBoltTool::Edit(/*[in]*/ IUnknown* pProp, /*[in]*/ LONG /*HWND*/ hWndParent,/*[out]*/ VARIANT_BOOL* pRet) 
{ 
    return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::EndEdit(/*[in]*/ VARIANT_BOOL bEditCancelled) 
{ 
    return S_OK;
}

//STDMETHODIMP CBoltTool::CancelExecution(
//            /*[in]*/  long lReason, 
//            /*[out]*/ long* pRetFlag)
//{
//    return E_NOTIMPL;
//}

// end CPH V059GLV4


STDMETHODIMP CBoltTool::New() 
{
	mnColor =256;  // bylayer
	nIdCmdFirst=0;
	nIdCmdLast=0;
	strcpy(mLayer,"0");
	mpToolProp=NULL; 
    
    return S_OK;
}


STDMETHODIMP CBoltTool::GetContextMenu(
            /*[in]*/ int nContextFlag, 
            /*[in]*/ DWORD /*HMENU*/ hMenu,
            /*[in]*/ UINT idCmdFirst,
            /*[in]*/  UINT idCmdLast, 
            /*[out, retval]*/ DWORD* pFlag)
{
    HMENU HMenu  = (HMENU)hMenu;
    BOOL bRet = IsMenu(HMenu);
    if (bRet == FALSE)
        return E_INVALIDARG;

    if (idCmdLast < idCmdFirst)
        return E_INVALIDARG;

    nIdCmdFirst = idCmdFirst;
    nIdCmdLast = idCmdLast;
    
    AppendMenu(HMenu, MF_SEPARATOR, 0,0);
	// Part Number...
	AppendMenu(HMenu,MF_ENABLED|MF_STRING,idCmdFirst,partNumber);
	// Use this tool to modify an existing selection set. calls executeAsModifier()..see InvokeCommand()
	AppendMenu(HMenu, MF_ENABLED|MF_STRING | MF_UNCHECKED, idCmdFirst, "Apply Properties to Entities");
	
    *pFlag = kContextMenuShow;
    return S_OK;
}

STDMETHODIMP CBoltTool::GetCommandString(
            /*[in]*/ UINT idCmd,
            /*[out, retval]*/BSTR* pbstrHelpText)
{
    return S_OK;
}


STDMETHODIMP CBoltTool::InvokeCommand(
            /*[in]*/ UINT idCmd, 
            /*[in]*/ DWORD /*HWND*/ hWnd)
{
    VERIFY( idCmd >= nIdCmdFirst && idCmd <= nIdCmdLast);
    if ((idCmd < nIdCmdFirst) || (idCmd > nIdCmdLast))
        return E_FAIL;
	if(idCmd==nIdCmdFirst)
		executeAsModifier();
	
	nIdCmdFirst = 0;
    nIdCmdLast = 0;

    return S_OK;
}

STDMETHODIMP CBoltTool::GetDragDropContextInfo(
            /*[in]*/ IUnknown*  pIUnknown,
            /*[out]*/BSTR* pbstrText, 
            /*[out]*/ DWORD* pFlag)
{
    _bstr_t bstrName(_T("Create Bolt Tool"));
    *pbstrText = bstrName.copy();
    return S_OK;
}


//IPropertyUnspecified members

STDMETHODIMP CBoltTool::IsValueUnspecified(/* [in] */ VARIANT varId, /* [out] */ VARIANT_BOOL *pVal)
{
	if (varId.ulVal == 2 || varId.ulVal == 3)
	{
		if (varId.ulVal == 2 && mColorUnspecified)	
				*pVal=VARIANT_TRUE;	
		else if (varId.ulVal == 3 && mLayerUnspecified)	
				*pVal=VARIANT_TRUE;	
		else
			*pVal = VARIANT_FALSE;

		return S_OK;
	}
	
	return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::SetUnspecified(/* [in] */ VARIANT varId, /* [in] */ VARIANT_BOOL bIsUnspecified)
{
	if (varId.ulVal == 2)
		mColorUnspecified = (bIsUnspecified == VARIANT_TRUE ? true : false);
	else if (varId.ulVal == 3)
		mLayerUnspecified = (bIsUnspecified == VARIANT_TRUE ? true : false);
	return S_OK;
}

STDMETHODIMP CBoltTool::IsUnspecifiedAllowed(/* [in] */ VARIANT varId, /* [out] */ VARIANT_BOOL *pVal)
{
	if (varId.ulVal == 2 || varId.ulVal == 3)
		*pVal=VARIANT_TRUE;	
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CBoltTool::GetUnspecifiedString(VARIANT var,BSTR * str)
{
    // Called to get the string which specifies an undefined value in these controls..
	_bstr_t unspecifiedString(_T("*Undefined*"));
    *str = unspecifiedString.copy();
	return S_OK;
}

// IDropTarget members

STDMETHODIMP CBoltTool::GetDropTarget(/*[out, retval]*/ IUnknown** ppDropTarget) 
{
    CComPtr<IDropTarget> pDropTarget;
    HRESULT hr = QueryInterface(IID_IDropTarget, (void**) &pDropTarget);
    if (FAILED(hr) || pDropTarget == NULL)
        return E_NOTIMPL;

    return QueryInterface(IID_IUnknown, (void**) ppDropTarget);
}

STDMETHODIMP CBoltTool::DragEnter(/* [unique][in] */ IDataObject __RPC_FAR *pDataObj,
                                    /* [in] */ DWORD grfKeyState,
                                    /* [in] */ POINTL pt,
                                    /* [out][in] */ DWORD __RPC_FAR *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    return S_OK;
}

STDMETHODIMP CBoltTool::DragOver(/* [in] */ DWORD grfKeyState,
                                   /* [in] */ POINTL pt,
                                   /* [out][in] */ DWORD __RPC_FAR *pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    return S_OK;
}
    
STDMETHODIMP CBoltTool::DragLeave(void)
{
    return S_OK;
}

extern CString imagePath;
extern char modulePath[MAX_PATH];

// Called when a tool is dropped on the same palette as this tool, and this tool is the first tool to implement IDropTarget.
STDMETHODIMP CBoltTool::Drop(/* [unique][in] */ IDataObject __RPC_FAR *pDataObj,
                               /* [in] */ DWORD grfKeyState,
                               /* [in] */ POINTL pt,
                               /* [out][in] */ DWORD __RPC_FAR *pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;

    USES_CONVERSION;

	COleDataObject data;
    data.Attach(pDataObj, FALSE);

    // This feature is based on the AutoCAD Drag and Drop functionality, which uses the Windows System Clipboard.

    // First, get the clipboard info.
	ClipboardInfo clipInfo;
    if (!GetClipInfo(&data, &clipInfo))
        return S_OK;

    // Extract the properties of the bolt that was dropped
	if (!ExtractProperties(clipInfo.szTempFile)) {
        *pdwEffect = DROPEFFECT_NONE;
        return E_FAIL;
    }

	// Now apply those properties.
	if (mpToolProp != NULL) {
		HRESULT hr;
		// First the tool's name.
		if(strlen(props.partNumber)!=0)
			hr=mpToolProp->put_Name(A2OLE(props.partNumber));
		else
		{
			hr=mpToolProp->put_Name(A2OLE("Custom Bolt"));
			strcpy(props.partNumber,"Custom Bolt");
			strcpy(props.materialName,"Custom");
		}
		
		hr=mpToolProp->SetImage(64,64,NULL,_bstr_t("IDB_BOLTIMAGE"),_bstr_t("asdkBoltTools.arx"));
	}
		
	data.Detach();

    return S_OK;
}

BOOL CBoltTool::GetClipInfo(COleDataObject* pDataObject, 
                              ClipboardInfo* pClipboardInfo)
{
    CLIPFORMAT cFormat = mcfAutoCAD;

    if (!pDataObject->IsDataAvailable(cFormat)) {
        return FALSE;
    }

    STGMEDIUM stgMedium = { TYMED_HGLOBAL,  NULL };
    FORMATETC fmt = { cFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    BOOL bValid = pDataObject->GetData(cFormat, &stgMedium, &fmt);
    
	if (bValid && stgMedium.hGlobal != NULL) {
        ClipboardInfo* pClipInfo =
            (ClipboardInfo*)::GlobalLock(stgMedium.hGlobal);
        assert(strcmp(pClipInfo->szSignature, szClipSignature) == 0);

        // Copy all the data
        *pClipboardInfo = *pClipInfo;
        
		::GlobalUnlock(stgMedium.hGlobal);
        ::ReleaseStgMedium(&stgMedium);
        return TRUE;
    }
    return FALSE;
}

// Extract the properties from the dropped entity...
BOOL CBoltTool::ExtractProperties(LPCTSTR pszTempFile)
{
    AcDbDatabase tempDb(false, true);
    Acad::ErrorStatus es = tempDb.readDwgFile(pszTempFile);
    ASSERT(es == Acad::eOk);
    if (es != Acad::eOk)
        return FALSE;

	AcDbBlockTableRecordIterator *pItr = NULL;
	{
		AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE,&tempDb,AcDb::kForRead);
		if(pBTR->newIterator(pItr)!=Acad::eOk)
			return FALSE;
	}

    asdkBolt *pDropBolt=NULL;
	while(!pItr->done())
	{
		// This means that the first entity in (the temporary) MS must be a bolt...
		AcDbEntity *pEnt;
		if(pItr->getEntity(pEnt, AcDb::kForRead)!=Acad::eOk)
		{
			delete pItr;
			return FALSE;
		}
		if(pEnt->isA()==asdkBolt::desc())
		{
			pDropBolt=asdkBolt::cast(pEnt->desc());
			pDropBolt=(asdkBolt*)pEnt;
			break;// we only need the first one...
		}
		pItr->step();
	}
    delete pItr;

	if(pDropBolt==NULL)
		return FALSE;

    AcCmColor col=pDropBolt->color();
	props.color=col.colorIndex();
	strcpy(props.layer,pDropBolt->layer());

	props.headDiameter=pDropBolt->headDiameter;
	props.headHeight=pDropBolt->headHeight;
	props.headSides=pDropBolt->headSides;
	strcpy(props.materialName,pDropBolt->materialName);
	strcpy(props.partNumber,pDropBolt->partNumber);
	props.shaftDiameter=pDropBolt->shaftDiameter;
	props.shaftLength=pDropBolt->shaftLength;
	props.threadLength=pDropBolt->threadLength;
	props.threadWidth=pDropBolt->threadWidth;
    	
	pDropBolt->close();
	bDroppedTool=true;
    
    return TRUE;
}


// IPerPropertyDisplay methods

STDMETHODIMP CBoltTool::GetCustomPropertyCtrl(
            /* [in] */ VARIANT varId,
            /* [in] */ LCID lcid,
            /* [out] */BSTR *pProgId)
{
    LPOLESTR pOleStr = NULL;
    HRESULT hr = E_NOTIMPL;
    if (varId.lVal == 2) 
        hr = ProgIDFromCLSID(CLSID_PropertyEditorColor, &pOleStr);
	if (varId.iVal == 3)
		hr = ProgIDFromCLSID(CLSID_PropertyEditorLayer, &pOleStr);

    if (SUCCEEDED(hr)) {
        if (pOleStr) {
            CComBSTR bstrStr(pOleStr);
            *pProgId = bstrStr.Copy();
            CoTaskMemFree(pOleStr);
        } else {
            hr = E_POINTER;
        }
    }
    return hr;
}
    
STDMETHODIMP CBoltTool::GetPropertyIcon(
    /* [in] */ VARIANT varId,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pIcon)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBoltTool::GetPropertyWeight(
    /* [in] */ VARIANT varId,
    /* [out] */ long *pPropertyWeight)
{
    return E_NOTIMPL;
}
    

STDMETHODIMP CBoltTool::GetEllipsisBitMap(
    /* [in] */ VARIANT varId,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBitMap)
{
    return E_NOTIMPL;
}
    

STDMETHODIMP CBoltTool::GetPropTextColor(
    /* [in] */ VARIANT varId,
    /* [out] */ OLE_COLOR __RPC_FAR *pTextColor)
{
    return E_NOTIMPL;
}
    

STDMETHODIMP CBoltTool::GetPropHelpProc(
    /* [in] */ VARIANT varId,
    /* [out] */ LONG __RPC_FAR *pHelpProc)
{
    return E_NOTIMPL;
}
    

STDMETHODIMP CBoltTool::IsFullView(
    /* [in] */ VARIANT varId,
    /* [out] */ VARIANT_BOOL __RPC_FAR *pbVisible,
    /* [out] */ DWORD __RPC_FAR *pIntegralHeight)
{
    return E_NOTIMPL;
}

BOOL CBoltTool::UpdatePreview(void)
{
    return TRUE;
}

STDMETHODIMP CBoltTool::get_Color(long *pVal)
{
	*pVal=mnColor;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_Color(long newVal)
{
	mnColor=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_HeadDiameter(double *pVal)
{
	*pVal=headDiameter;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadDiameter(double newVal)
{
	headDiameter=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_HeadSides(long *pVal)
{
	*pVal=headSides;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadSides(long newVal)
{
	headSides=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_HeadHeight(double *pVal)
{
	*pVal=headHeight;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_HeadHeight(double newVal)
{
	headHeight=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ShaftLength(double *pVal)
{
	*pVal=shaftLength;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ShaftLength(double newVal)
{
	shaftLength=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ShaftDiameter(double *pVal)
{
	*pVal=shaftDiameter;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ShaftDiameter(double newVal)
{
	shaftDiameter=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ThreadLength(double *pVal)
{
	*pVal=threadLength;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ThreadLength(double newVal)
{
	threadLength=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_ThreadWidth(double *pVal)
{
	*pVal=threadWidth;
	return S_OK;
}

STDMETHODIMP CBoltTool::put_ThreadWidth(double newVal)
{
	threadWidth=newVal;
	return S_OK;
}

STDMETHODIMP CBoltTool::get_Layer(BSTR *pVal)
{
    if (mLayer) {
        CComBSTR bstrLayer(mLayer);
		*pVal = bstrLayer.Copy();
    } else {
        CComBSTR bstrLayer("0");
        *pVal = bstrLayer.Copy();
    }
	return S_OK;
}

STDMETHODIMP CBoltTool::put_Layer(BSTR newVal)
{
	USES_CONVERSION;
	strcpy(mLayer,OLE2A(newVal));
	return S_OK;
}

STDMETHODIMP CBoltTool::get_partNumber(BSTR* pVal)
{
	CComBSTR bstrPartNumber(partNumber);
	*pVal = bstrPartNumber.Copy();
	return S_OK;
}

STDMETHODIMP CBoltTool::put_partNumber(BSTR newVal)
{
	USES_CONVERSION;
	strcpy(partNumber,OLE2A(newVal));
	return S_OK;
}

STDMETHODIMP CBoltTool::get_materialName(BSTR* pVal)
{
	CComBSTR bstrMaterialName(materialName);
	*pVal = bstrMaterialName.Copy();
	return S_OK;
}

STDMETHODIMP CBoltTool::put_materialName(BSTR newVal)
{
	USES_CONVERSION;
	strcpy(materialName,OLE2A(newVal));
	return S_OK;
}

// This will obtain a selection from the user, and each bolt in the selection will obtain this tool's properties.
void CBoltTool::executeAsModifier(void)
{
    acedGetAcadDwgView()->SetFocus();
	
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    AcAxDocLock docLock( pDb, AcAxDocLock::kNormal );
    if(docLock.lockStatus() != Acad::eOk){
        return;
    }
	
	ads_name ss;
	if(acedSSGet(NULL,NULL,NULL,NULL,ss)!=RTNORM)
		return; 
	long len;
	acedSSLength(ss,&len);
	if (len == 0)
		return;
	for(int c=0;c<len;c++)
	{
		ads_name ename;
		AcDbObjectId Id;
		acedSSName(ss,c,ename);
		acdbGetObjectId(Id,ename);
		asdkBolt* pBolt;
		Acad::ErrorStatus es;
		if((es=acdbOpenObject(pBolt,Id,AcDb::kForWrite,false))!=Acad::eOk)
			continue;
		pBolt->setColorIndex(mnColor);
		pBolt->headDiameter=headDiameter;
		pBolt->headHeight=headHeight;
		pBolt->headSides=headSides;
		pBolt->shaftDiameter=shaftDiameter;
		pBolt->shaftLength=shaftLength;
		pBolt->threadLength=threadLength;
		pBolt->threadWidth=threadWidth;
		pBolt->calculatePnts(); 
		pBolt->close();
	}
}
