//
//
// (C) Copyright 1990-2008 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
#include "StdAfx.h"
//-----------------------------------------------------------------------------
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "assert.h"
#include "tchar.h"



//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

extern Acad::ErrorStatus postToDatabase(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus	  es;
    AcDbBlockTable*		pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead);
    assert(es == Acad::eOk);

    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite);
    assert(es == Acad::eOk);

    es = pBlockTable->close();
    assert(es == Acad::eOk);

    es = pSpaceRecord->appendAcDbEntity(objId, ent);
    assert(es == Acad::eOk);

    es = ent->close();
    assert(es == Acad::eOk);

    es = pSpaceRecord->close();
    assert(es == Acad::eOk);

    return es;
}
/*
void TestNumberField()
{
    Acad::ErrorStatus es;
    AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
    AsdkTextFileEvaluator * pnEvaluator = new AsdkTextFileEvaluator();

    const char * tempId;
    tempId = pnEvaluator->getEvaluatorId();
    //create the field
    AcDbField *numField = new AcDbField();
    AcDbObjectId fieldId;
    es=pDb->addAcDbObject(fieldId,numField);
    es= numField->setEvaluatorId(tempId);
    es= numField->setFieldCode("%<\\TextFile c:\\temp\\test.txt>%");
    
    AcFdFieldEngine * pEngine = acfdGetFieldEngine();

    AcFdFieldResult * pResult=NULL;
    es=pnEvaluator->compile(numField,pDb,pResult);
    es= numField->close();

    AcDbField * pField;
    es= acdbOpenObject(pField,fieldId,AcDb::kForWrite);

    es=pField->evaluate(AcDbField::kRegen,pDb);
    es=pField->close();
}
*/

void addEvalIdToRegistry()
{
    //get the 'NumberField' Key location
    HKEY hSoftKey = NULL;
    HKEY hNumFldKey = NULL;
    const TCHAR * acadkey = acrxProductKey();
    const size_t nappKey = 1024;
    TCHAR appkey[nappKey]=_T("");
    _stprintf_s(appkey, nappKey, _T("%s\\Applications"),acadkey);

    if (RegOpenKeyEx(HKEY_CURRENT_USER, appkey, 0, KEY_WRITE|KEY_READ,
        &hSoftKey) == ERROR_SUCCESS)
    {
        DWORD dw;
        if (RegCreateKeyEx(hSoftKey, _T("TextFileField"), 0, REG_NONE,
            REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
            &hNumFldKey, &dw) == ERROR_SUCCESS)
        {
            //Add 'FIELDEVALUATORS' entry to 'TextFileField'
            TCHAR evalId[14]=_T("TextFileField");
            RegSetValueEx(hNumFldKey,_T("FIELDEVALUATORS"),0,REG_SZ,(LPBYTE)evalId,sizeof(evalId));
        }
    }
}

void updateRegistry()
{
    TCHAR moduleName[256];
    ::GetModuleFileName(_hdllInstance, moduleName, 256);
    // Fill the AppInfo structure with our demand loading details.
    AcadAppInfo appInfo;
    appInfo.setAppName(_T("TextFileField")); // Application name
    appInfo.setModuleName(moduleName);// Module path
    appInfo.setAppDesc(_T("AsdkTextFileField")); // Description
    appInfo.setLoadReason(// Specify when we want these to load
        AcadApp::LoadReasons(
        AcadApp::kOnCommandInvocation |
        AcadApp::kOnLoadRequest));
    
    appInfo.writeToRegistry(false,true);// Write the appInfo to the registry.
    
    appInfo.writeGroupNameToRegistry(_T("TEXTFILEFIELD_GROUP"));// Write the group name
    
    // Write out all our commands (Global,Local).
    appInfo.writeCommandNameToRegistry(_T("TextFileField"),_T("tnf"));

    addEvalIdToRegistry();
}

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CTextFileFieldApp : public AcRxDbxApp {

public:
    CTextFileFieldApp () : AcRxDbxApp () {}

    virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
        AcRx::AppRetCode retCode =AcRxDbxApp::On_kInitAppMsg (pkt) ;
        m_textFileFieldLoader.registerLoader();
        updateRegistry();
        return (retCode) ;
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
        AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadAppMsg (pkt) ;
        m_textFileFieldLoader.unregisterLoader();
        return (retCode) ;
    }

    virtual void RegisterServerComponents () {
    }

private:
    AsdkTextFileEvaluatorLoader m_textFileFieldLoader;
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CTextFileFieldApp)

