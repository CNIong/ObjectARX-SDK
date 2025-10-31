[!if=(AddCppTemplate, "TRUE")]
[!if=(FileExists, "FALSE")]
// [!CPPName] : Implementation of [!ClassName]

#include "stdafx.h"
#include "[!ProjectName].h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]
[!crlf]

#define AXEntityDocLock(objId)                              \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if(docLock.lockStatus() != Acad::eOk)                   \
        throw docLock.lockStatus();

/////////////////////////////////////////////////////////////////////////////
// [!ClassName]
[!crlf]
[!if=(ErrorInfoEnabled, "TRUE")]
STDMETHODIMP [!ClassName]::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_[!InterfaceName]
        [!if=(DerivedFrom,"AcDbObject")]
        ,&IID_IAcadObject
        [!else]
        ,&IID_IAcadEntity
        [!endif]
        [!if=(OpmPropExpander,"TRUE")]
        ,&IID_IOPMPropertyExpander
        [!endif]
        [!if=(OpmPropExtImpl,"TRUE")]
        ,&IID_ICategorizeProperties
        ,&IID_IPerPropertyBrowsing
        ,&IID_IOPMPropertyExtension
        [!endif]
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
[!endif]
HRESULT [!ClassName]::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<[!AcDbClassName]> pO;
        if((es = pO.create()) != Acad::eOk)
            throw es;

        AcDbDatabase* pDb = ownerId.database();
        pO->setDatabaseDefaults(pDb);
[!if=(DerivedFrom,"AcDbEntity")]
        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pO.object())) != Acad::eOk)
            throw es;
[!else]
        //TO DO: if your object does not reside in a dictionary
        //modify the following code accordingly
        AcDbDictionaryPointer pDictionary(ownerId, AcDb::kForWrite);
        if((es = pDictionary.openStatus()) != Acad::eOk)
            throw es;

        if((es = pDictionary->setAt(keyName,pO.object(),objId)) != Acad::eOk)
            throw es;
[!endif]
    }
    catch(const Acad::ErrorStatus)
    {
        //we can becaome more sophisticated 
        return Error(L"Failed to create [!AcDbClassName]",IID_[!InterfaceName],E_FAIL);
    }

    return S_OK;
}

[!if=(OpmPropExpander,"TRUE")]
//IOPMPropertyExpander
STDMETHODIMP [!ClassName]::GetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [out] */ VARIANT * pVarOut)
{
    //TO DO: Implement this function.
    return S_OK;
}

//IOPMPropertyExpander
STDMETHODIMP [!ClassName]::SetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [in] */ VARIANT VarIn)
{
    //TO DO: Implement this function.
    return S_OK;
}
//IOPMPropertyExpander
STDMETHODIMP [!ClassName]::GetElementStrings( 
	/* [in] */ DISPID dispID,
	/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
	/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{
    //TO DO: Implement this function.
    return S_OK;
}
//IOPMPropertyExpander
STDMETHODIMP [!ClassName]::GetElementGrouping(
    /* [in] */ DISPID dispID,
	/* [out] */ short *groupingNumber)
{
    //TO DO: Implement this function.
    return S_OK;
}
//IOPMPropertyExpander
STDMETHODIMP [!ClassName]::GetGroupCount(
    /* [in] */ DISPID dispID,
	/* [out] */ long *nGroupCnt)
{
    //TO DO: Implement this function.
    return S_OK;
}
[!endif]
[!endif]

[!if(InsertDbServerName)]
    [!AddSymbolToString(AcDbServerNameVariable, "str", AcDbServerName)]
    static const char* [!AcDbServerNameVariable] = "[!AcDbServerName].dbx";
[!endif]

[!if(InsertLoadDbServer)]
[!if=(DllMainExists,"0")]
    // check if the arx app is loaded or not.
    // if not, load it as UI so that we won't have
    // proxy if this dll is unloaded by OS
    [!AcDbServerNameVariable] = "[!AcDbServerName].dbx";
    if (!isModuleLoaded([!AcDbServerNameVariable]))
    {
        if (!acrxLoadModule([!AcDbServerNameVariable], false, true))
 	       return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
    }
    //bump the reference count 
    acrxLoadModule([!AcDbServerNameVariable], false, false);
[!else]
        // check if the arx app is loaded or not.
        // if not, load it as UI so that we won't have
        // proxy if this dll is unloaded by OS
        if (!isModuleLoaded([!AcDbServerNameVariable]))
        {
            if (!acrxLoadModule([!AcDbServerNameVariable], false, true))
 	           return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
        }
        //bump the reference count 
        acrxLoadModule([!AcDbServerNameVariable], false, false);
[!endif]
[!endif]

[!if(InsertUnloadDbServer)]
[!if=(DllMainExists,"0")]
    //try to decrease the refcount on the dbx
    //if we couldn't load it then this a no op.
    acrxUnloadModule([!AcDbServerNameVariable]);
[!else]
        //try to decrease the refcount on the dbx
        //if we couldn't load it then this a no op.
        acrxUnloadModule([!AcDbServerNameVariable]);
[!endif]
[!endif]
