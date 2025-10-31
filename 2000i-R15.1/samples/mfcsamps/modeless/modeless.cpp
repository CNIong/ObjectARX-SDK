//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//
#include "stdafx.h"

extern CSampDialog* gpDlg;
extern bool gbDisplayDialog;

#include "AdskDMgr.h"
class CDocInfo
{
public:
	CDocInfo();
	bool undoBtnAvailable;
	bool undoCmd;
};

CDocInfo::CDocInfo(){this->undoBtnAvailable=false; this->undoCmd=false;}

AsdkDataManager<CDocInfo> DocDataMgr; //MDI safe
#define docState DocDataMgr.docData()

//
//	Attach the database reactor if one isn't attached already.  
//	Then, start up the dialog.
//
//
void attachDbReactor(AcDbDatabase* pDb)
{
	if(gbDisplayDialog)
	{
		AcDbDatabase* pWkDb = acdbHostApplicationServices()->workingDatabase();
		assert(pWkDb == pDb);
		AcDbDatabase* pCurDb = curDoc()->database();
		assert(pCurDb == pDb);
		acDocManager->lockDocument(curDoc(), AcAp::kWrite);
    
		gpDbReactor = new CDbModReactor();
		pWkDb->addReactor(gpDbReactor);
		acutPrintf("\nAttached CDbModReactor to the current database.\n");     
		
		acDocManager->unlockDocument(curDoc());
		acedPostCommandPrompt();
	}
	else
		endDlg();
}
//
//
//	Detach the database reactor if the db is deactivated.  
//  Close the dialog if requested by the user.
//
//
void detachDbReactor(AcDbDatabase* pDb)
{
	acDocManager->lockDocument(curDoc(), AcAp::kWrite);
    if(gpDbReactor) 
    {
        pDb->removeReactor(gpDbReactor);
		delete gpDbReactor;
		gpDbReactor = NULL;
		acutPrintf("\nDetached DbReactor from the current database.\n");
    }
	acDocManager->unlockDocument(curDoc());

	acedPostCommandPrompt();
}
//
//	CDbModReactor overrides
//
//
//
void CDbModReactor::objectModified(const AcDbDatabase* pDb,
                                  const AcDbObject* pDbObj)
{
	AcAxDocLock docLock(pDbObj->ownerId(), AcAxDocLock::kNormal);	
	if(docLock.lockStatus() != Acad::eOk)
		return;
    else 
		objDisplay("modified", pDbObj);

}
//
//
//
void CDbModReactor::objectErased(const AcDbDatabase* pDb,
                                const AcDbObject* pDbObj,
                                Adesk::Boolean bErased)
{
	AcAxDocLock docLock(pDbObj->ownerId(), AcAxDocLock::kNormal);	
	if(docLock.lockStatus() != Acad::eOk)
		return;
    else
	{
		char buf[40];
		sprintf(buf, "%serased", (bErased ? "" : "not "));
		objDisplay(buf, pDbObj);
	}
}
//
// Update the content displayed in the modeless dialog.
//
void objDisplay(const char* pWhat, const AcDbObject* pDbObj)
{
	if(!gpDlg)
		return;
    char hstr[20];
    char idstr[20];
	const char *pClsName = NULL;
	if(pDbObj)
	{
		AcDbObjectId id = pDbObj->objectId();
		AcDbHandle h;
		pClsName = pDbObj->isA()->name();
    
		pDbObj->getAcDbHandle(h);
		h.getIntoAsciiBuffer(hstr);
    
		acutPrintf("\nDbModReactor: obj %s: "
			"class %s, id %lx, handle %s.\n",
			pWhat, pClsName , id, hstr);
    
		sprintf(idstr, "0x%08lx", id);
	}
	else
	{
		pClsName = "";
		strcpy(hstr, "");
		strcpy(idstr, "");
	}

	gpDlg->SetDlgItemText(IDC_WHAT, pWhat);
	gpDlg->SetDlgItemText(IDC_EDIT_CLASS, pClsName);
	gpDlg->SetDlgItemText(IDC_EDIT_OBJID, idstr);
	gpDlg->SetDlgItemText(IDC_EDIT_HANDLE, hstr);

	//enable UNDO dialog button only if UNDO not already underway and
	//either an entity is being generated or modified.
	if (pDbObj->isKindOf(AcDbEntity::desc()) && !docState.undoCmd) 
		docState.undoBtnAvailable = TRUE;
	
}


void CEdReactor::commandWillStart(const char *cmd)
{
		if (!strcmp(cmd,"UNDO"))
			docState.undoCmd = TRUE;
}

void CEdReactor::commandEnded(const char *cmd)
{
	if (docState.undoBtnAvailable)
	{
		
		gpDlg->m_undoBtn.EnableWindow(TRUE);
		//disable this button next command if no entity changes
		docState.undoBtnAvailable = FALSE; 
		
	}	
	else
		gpDlg->m_undoBtn.EnableWindow(FALSE);
	
	if (docState.undoCmd)
		docState.undoCmd = FALSE; //undo is finished
}
/////////////////////////////////////////////////////////////////////////////////////
//
// document manager reactor
//
/////////////////////////////////////////////////////////////////////////////////////
//
//
//
void CDocReactor::documentActivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
	acutPrintf("\ndocumentActiveated: %s.\n", pDoc->fileName());
	acedPostCommandPrompt();
#endif
	attachDbReactor(pDoc->database());
}
//
// We need to attach the database reactor to the newly created
// database. We need to delete the previous database reactor as well.
//

void CDocReactor::documentCreated(AcApDocument* pDoc)
{
#ifndef NDEBUG
	acutPrintf("\ndocumentCreated: %s.\n", pDoc->fileName());
	acedPostCommandPrompt();
#endif
	if(gpDlg)
		objDisplay("", NULL);
}

//
// This deactivation includes a non-Acad window is activated 
// so the Acad window is losing focus.
//
void CDocReactor::documentToBeDeactivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
	acutPrintf("\ndocumentToBeDeactiveated: %s.", pDoc->fileName());
	acedPostCommandPrompt();
#endif
	detachDbReactor(pDoc->database());
	if(gpDlg)
		objDisplay("", NULL);
}
//
// Obviously, we need to delete the database reactor associated
// with the destroyed doc.
//
void CDocReactor::documentToBeDestroyed(AcApDocument* pDoc)
{
#ifndef NDEBUG
	acutPrintf("\ndocumentToBeDestroyed: %s.\n", pDoc->fileName());
	acedPostCommandPrompt();
#endif
	detachDbReactor(pDoc->database());
	if(gpDlg)
		objDisplay("", NULL);
}
//
// This one can not be used because it gives the historically 
// to be activated document prior to the current action.
//
void CDocReactor::documentToBeActivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
	acutPrintf("\ndocumentToBeActivated: %s.", pDoc->fileName());
	acedPostCommandPrompt();
#endif
}


