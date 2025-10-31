// (C) Copyright 1997-1998 by Autodesk, Inc.
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
// docman.cpp:  MDI Document Manager API Examples

#include "stdafx.h"
#include <string.h>
#include "adesk.h"
#include "aced.h"
#include "acdocman.h"
#include "adslib.h"
#include "actrans.h"
#include "rxmfcapi.h"
#include "AcExtensionModule.h"

#include "MDITestDialog.h"
#include "common.h"

class AsdkDocReactor;
class AsdkEditorReactor;
class AsdkDocToModReactor;


// Global pointers to our two reactor classes
AsdkDocReactor*      gpDocReactor;       // MDI Safe
AsdkEditorReactor*   gpEditReactor;      // MDI Safe
AsdkDocToModReactor* gpDocToModReactor;  // MDI Safe

// the following global will point to our modeless dialog
CMDITestDialog*      modelessDlg = NULL; // MDI Safe


extern "C" HWND adsw_acadMainWnd();

AcApDocument* AcadSetActiveDocument(AcApDocument* pAcDocument);


/////////////////////////////////////////////////////////////////////////////
// Define the sole extension module object.

AC_IMPLEMENT_EXTENSION_MODULE(docmanDLL);


/////////////////////////////////////////////////////////////////////////
// The Document Reactor ...
// Subscribe to all of the document reactors the example simply monitors
// and reports when any of the following document reactors are fired.
/////////////////////////////////////////////////////////////////////////
class AsdkDocReactor : public AcApDocManagerReactor
{
public:
    virtual void  documentCreated(AcApDocument* );
    virtual void  documentToBeDestroyed(AcApDocument* );
    virtual void  documentLockModeChanged(AcApDocument*,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          const char* pCommandName);
    virtual void  documentBecameCurrent(AcApDocument* );

    virtual void  documentToBeActivated(AcApDocument* pActivatingDoc );
    virtual void  documentToBeDeactivated(AcApDocument* pDeactivatingDoc );
	virtual void  documentActivationModified(bool bActivation);
};

// Simple AcEd reactor declaration. Notify when a save is complete.
// This is the typical method to look when a documents name might have changed
class AsdkEditorReactor : public AcEditorReactor
{
public:
    virtual void saveComplete (AcDbDatabase*, const char* pActualName);
};


// Notification when a SAVE is complete Typical method to detect when
// a document has been renamed
void 
AsdkEditorReactor::saveComplete (AcDbDatabase*, const char* pActualName)
{
    AcApDocument* pDoc = acDocManager->curDocument();
    if (pDoc)
        acutPrintf("DOCUMENT: Save complete %s\n", pDoc->fileName());
}

// Notification of when a document is created
void 
AsdkDocReactor::documentCreated(AcApDocument* pDoc)
{
    if (pDoc)
        acutPrintf("DOCUMENT: Created %s\n", pDoc->fileName());
}

// Notification of when a document is destroyed
// Always uses the documentCount() API to detect when the last document
// is destroyed. Apps. may use this API to detect when AutoCAD is 
// going to the zero document state or if an action needs to be performed
// before the last database is destroyed.
void 
AsdkDocReactor::documentToBeDestroyed(AcApDocument* pDoc)
{
    if (!acDocManager) 
		return;

    if (acDocManager->documentCount() == 1) 
    {
        // Last document destroyed going to zero document state or quitting
        acutPrintf("LAST DOCUMENT: To be destroyed %s\n", pDoc->fileName());
    } else {
        acutPrintf("DOCUMENT: To be destroyed %s\n", pDoc->fileName());
    }
}

// Notification of when a document is to be activated
// Advance applications can use this API along with sendStringToExecute()
// to "Pass Commands" across documents. One example of this is
// the MATCHPROP command whihc allows properties to be "painted"
// across documents as well as within the same document.
void 
AsdkDocReactor::documentToBeActivated(AcApDocument* pActivatingDoc)
{
    if (pActivatingDoc) 
        acutPrintf("DOCUMENT: To be Activated %s\n", pActivatingDoc->fileName());
}

// Notification of when a document is deactivated. Useful if an
// application needs notification when a document they may be performing
// an action in is about to be suspended
void 
AsdkDocReactor::documentToBeDeactivated(AcApDocument* pDeactivatingDoc)
{
    if (pDeactivatingDoc) 
        acutPrintf("DOCUMENT: To be DEActivated %s\n", pDeactivatingDoc->fileName());
}


// Notification of when cross document activation is turned on or off. 
// Useful if an
// application needs notification when another application has disabled
// document activation
void 
AsdkDocReactor::documentActivationModified(bool bActivation)
{
	if (bActivation)
		acutPrintf("DOCUMENT Activation is ON. \n");
	else
		acutPrintf("DOCUMENT Activation is OFF. \n");
}

void 
AsdkDocReactor::documentLockModeChanged(AcApDocument* pDoc,
                                        AcAp::DocLockMode myPrevMode,
                                        AcAp::DocLockMode myCurMode,
                                        AcAp::DocLockMode curMode,
                                        const char* pCommandName)
{
	if(!pDoc)
		return;

    acutPrintf("%s %sLOCK %s CHANGED TO %s FOR %s\n", pDoc->fileName(), 
        acDocManager->isApplicationContext() ? "APP " : "",
                                               modeStr(myPrevMode),
                                               modeStr(myCurMode),
                                               pCommandName);
}

void 
AsdkDocReactor::documentBecameCurrent(AcApDocument* pDoc)
{
	if(pDoc)
        acutPrintf("DOCUMENT: Became current %s\n", pDoc->fileName());
}


/////////////////////////////////////////////////////////////////////////
// The Document To Modeless Dialog Reactor ...
// Subscribe to all of the document reactors. The example simply monitors
// and reports when any of the following document reactors are fired.
// However this reactor is tailored to interact with the modeless dialog,
// sending messages and updating it when reactors are fired.
// Unlike the other reactors, this one will be attached/detached on
// creation/destruction of the dialog itself.
/////////////////////////////////////////////////////////////////////////
class AsdkDocToModReactor : public AcApDocManagerReactor
{
public:
    virtual void  documentCreated(AcApDocument* );
    virtual void  documentToBeDestroyed(AcApDocument* );
    virtual void  documentLockModeChanged(AcApDocument*,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          const char* pCommandName);
	virtual void  documentLockModeWillChange(AcApDocument*,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          AcAp::DocLockMode,
                                          const char* pGlobalCmdName);
    virtual void  documentBecameCurrent(AcApDocument* );

    virtual void  documentToBeActivated(AcApDocument* pActivatingDoc );
    virtual void  documentToBeDeactivated(AcApDocument* pDeactivatingDoc );
	virtual void  documentActivationModified(bool bActivation);
};


void AsdkDocToModReactor::documentCreated(AcApDocument* pDoc)
{
	if(!pDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentCreated   called (%s)\n", pDoc ? pDoc->fileName() : "NULL");
	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_CREATEDOC, 0, 0L);
}

void AsdkDocToModReactor::documentToBeDestroyed(AcApDocument* pDoc)
{
	if(!pDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentToBeDestroyed   called (%s)\n", pDoc ? pDoc->fileName() : "NULL");
	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_DESTROYDOC, 0, 0L);
}

void AsdkDocToModReactor::documentToBeActivated(AcApDocument* pActivatingDoc)
{
	if(!pActivatingDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentToBeActivated   called (%s)\n", pActivatingDoc ? pActivatingDoc->fileName() : "NULL");
	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_ACTIVATEDOC, 0, 0L);
}

void AsdkDocToModReactor::documentToBeDeactivated(AcApDocument* pDeactivatingDoc)
{
	if(!pDeactivatingDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentToBeDeactivated   called (%s)\n", pDeactivatingDoc ? pDeactivatingDoc->fileName() : "NULL");
	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_DEACTIVATEDOC, 0, 0L);
}


void AsdkDocToModReactor::documentLockModeChanged(AcApDocument* pDoc,
                                        AcAp::DocLockMode myPrevMode,
                                        AcAp::DocLockMode myCurMode,
                                        AcAp::DocLockMode curMode,
                                        const char* pCommandName)
{
	if(!pDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentLockModeChanged   called (%s - from %s to %s)\n",
		  pDoc ? pDoc->fileName() : "NULL", modeStr(myPrevMode), modeStr(myCurMode) );
	char *p = new char[20]; // this will be deleted on the dialog's side

	strcpy( p, modeStr(myCurMode) );

	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_LOCKMODCHANGED, 0, (LONG)p );
}


void AsdkDocToModReactor::documentLockModeWillChange(AcApDocument* pDoc,
                                        AcAp::DocLockMode myCurMode,
                                        AcAp::DocLockMode myNewMode,
                                        AcAp::DocLockMode currentMode,
                                        const char* pGlobalCmdName)
{
	if(!pDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentLockModeWillChange called (%s - from %s to %s)\n",
		  pDoc ? pDoc->fileName() : "NULL", modeStr(myCurMode), modeStr(myNewMode) );
	char *p = new char[20]; // this will be deleted on the dialog's side

	strcpy( p, modeStr(myNewMode) ); 

	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_LOCKMODWILLCHANGE, 0, (LONG)p );
}


void AsdkDocToModReactor::documentBecameCurrent(AcApDocument* pDoc)
{
	if(!pDoc)
		return;
	TRACE("#### Docman   AsdkDocToModReactor::documentBecameCurrent   called (%s)\n", pDoc ? pDoc->fileName() : "NULL" );
	if( modelessDlg )
		modelessDlg->SendMessage(WM_ACAD_CURRENTDOC, 0, 0L);
}

void AsdkDocToModReactor::documentActivationModified(bool bActivation)
{
	if( !modelessDlg )
        return;

	if (bActivation)
		modelessDlg->SendMessage(WM_ACAD_ACTMODIFIED, 0, 1L); // send a "TRUE"
	else
		modelessDlg->SendMessage(WM_ACAD_ACTMODIFIED, 0, 0L); // send a "FALSE"
}


// Commands ...

//
//  NAME: getYorN        
//
//  REMARKS: Simple Yes or No utility prompt
//           
//          
// 
//  RETURNS:
//      TRUE for Yes False for No 
static Adesk::Boolean 
getYorN(const char* pStr)
{
    char yorn_str[132];

    // specific prompt.
    acutPrintf("\n%s", pStr);

    acedInitGet(0, "No Yes _No Yes");

    yorn_str[0] = 'Y';
    yorn_str[1] = '\0';

    switch (acedGetString(Adesk::kFalse, " -- No/<Yes>:  ",
                          yorn_str)) {
    case RTKWORD:
        acedGetInput(yorn_str);
        /* Deliberate fallthrough */
    default:
        break;
    }

    return (!((yorn_str[0] == 'N') || (yorn_str[0] == 'n')));
}


//
//	startDlg()
//
//	Start up the modeless dialog.
//
//
Adesk::Boolean startDlg()
{
	CAcModuleResourceOverride resOverride;
	HWND hwndAcad = adsw_acadMainWnd();

	if ( !hwndAcad ) {
		AfxMessageBox( "Unable to locate AutoCAD parent window." );
		return Adesk::kFalse;
	}

	CWnd *pWnd = CWnd::FromHandle ( hwndAcad );
	if( modelessDlg == NULL ) {
		if ( (modelessDlg = new CMDITestDialog ( pWnd )) == NULL ) {
			AfxMessageBox ( "Unable to allocate a CMDITestDialog." );
			return Adesk::kFalse;
		}

		BOOL succeeded = modelessDlg->Create ( pWnd );
		if ( !succeeded ) {
			AfxMessageBox ( "Unable to create the dialog." );
			return Adesk::kFalse;
		}
	}
	modelessDlg->ShowWindow(SW_SHOWNORMAL);

	// add the reactor once the dialog was created
	acDocManager->addReactor( gpDocToModReactor );
		
	return Adesk::kTrue;
}


//
//	endDlg()
//
//
Adesk::Boolean endDlg()
{
	if ( !modelessDlg )
		return Adesk::kTrue;

	Adesk::Boolean ok = modelessDlg->DestroyWindow();
	if ( ok )
		modelessDlg = NULL;
	return ok;
}


//
//  NAME: listDocuments        
//
//  REMARKS: Iterate over all the open documents. Very common piece of code
//           for MDI aware applications.
//          
// 
//  RETURNS:
//      void 
void
listDocuments()
{
    AcApDocument* pDoc;
    AcApDocumentIterator* pDocIter;

    pDocIter = acDocManager->newAcApDocumentIterator();

    for ( ; !pDocIter->done(); pDocIter->step()) {
        pDoc = pDocIter->document();
        acutPrintf("  %s\n", pDoc->fileName());
    }
    delete pDocIter;
}

//
//  NAME: watchDocuments        
//
//  REMARKS:  Turn on all reactor notifications
//          
//          
// 
//  RETURNS:
//      void 
void
watchDocuments()
{
    if (getYorN("Start watching Documents")) {
        acDocManager->addReactor(gpDocReactor);
        acedEditor->addReactor(gpEditReactor);
        acutPrintf("  Added reactor to the Document Manager.\n");
    } else {
        acedEditor->removeReactor(gpEditReactor);
        acDocManager->removeReactor(gpDocReactor);
        acutPrintf("  Removed reactor from the Document Manager.\n");
    }
}

//
//  NAME: selectDocument        
//
//  REMARKS:  Simple utility to have the user choose an open document to
//            perform some action on.
//          
//          
// 
//  RETURNS:
//      void 
static AcApDocument* selectDocument()
{
    AcApDocument* documentArray[10];

    AcApDocument* pDoc;
    AcApDocumentIterator* pDocIter;
    int nDocs = 0;;

    pDocIter = acDocManager->newAcApDocumentIterator();

    for ( ; !pDocIter->done(); pDocIter->step(), nDocs++) {
        pDoc = pDocIter->document();
        documentArray[nDocs] = pDoc;
        acutPrintf("%d.  %s\n", nDocs + 1, pDoc->fileName());
    }
    delete pDocIter;

    acedInitGet(RSG_NOZERO | RSG_NONEG, NULL);
    int iSelection;
    int inputStatus = acedGetInt("Which document should this command execute in: ", &iSelection);
    if (inputStatus == RTNORM && iSelection <= nDocs) {
        return documentArray[iSelection - 1];
    } else {
        return NULL;
    }
}

//
//  NAME: activate        
//
//  REMARKS:  Simple utility to have the user choose an open document to
//            be activated programmatically. 
//            NOTE: This and other APIs that change context (switch from one
//            active document to another) have the effect of suspending the current
//            document context. What this implies is if the ARX application
//            had code immediately following the activateDocument() API call
//            and this command was executed from a current document (ie. NOT
//            from the application context) The code following the API
//            call would never execute until that document became activated
//            again.
//          
//          
// 
//  RETURNS:
//      void 
void
activate()
{
    AcApDocument* pDoc = selectDocument();

    if (pDoc == NULL) {
        acutPrintf("No document selected.\n");
        return;
    } 
   
    acDocManager->activateDocument(pDoc);
    // A line of code here will not execute until the document
    // that started this command is activated again.
}

//
//  NAME: send        
//
//  REMARKS:  Simple routine to exercise switching between documents and sending commands.
//            
//         NOTEs: The actual signature for sendStringToExecute is:
//                virtual Acad::ErrorStatus sendStringToExecute(
//                                       AcApDocument* pAcTargetDocument,
//                                       const char * pszExecute,
//                                       bool bActivate = true,
//                                       bool bWrapUpInactiveDoc = false) = 0;
//
//         By default this API activates the document you are sending the string to
//         to be executed to. The last parameter, bWrapUpInactiveDoc is only applicable
//         if bActivate == False. This special ability allows you to "clean up" 
//         a document you might have left with some dangling command when constructing
//         a command that spans documents. One scenario is you are in the middle of
//         a custom command whose implementation is designed to "follow" the user
//         as they move from one document to another. If you have registered a reactor
//         on documentToBeActivated(). When this reactor fires you wish to complete
//         your current command in the document that is being deactivated and start
//         a command in the document about to be activated. 
//         Given these conditions, you would possibly send a "return" to the old 
//         document and "execute my new command" string to the one about to activated.
//         The "return" you would want to process in the background so you would pass
//         bActivate = False and bWrapUpInactiveDoc = True. 
// 
//  RETURNS:
//      void 
// 
void
send()
{
    AcApDocument* pDoc = selectDocument();

    if (pDoc == NULL) {
        acutPrintf("No document selected.\n");
        return;
    } 

    acDocManager->sendStringToExecute(pDoc, /*NOXLATE*/"_Line\n");
    // The API inputPending() allows you to check to see if someone else has already
    // made a request via sendStringToExecute() to a target document.
    // You may not care if your command is autonomous and does not depend on the target
    // document being in a quiescent state. If not call both  isQuiescent() and inputPending()
    acutPrintf("\nSent String to Doc: %s Pending Input %d\n", pDoc->fileName(), acDocManager->inputPending(pDoc));

}

//
//  NAME: cmd()        
//
//  REMARKS:  Simple routine to exercise acedCommand. While this still works in MDI
//            it will ALWAYS apply to the active document. You might find
//            sendStringToExecute to be more modern and robust.
//            Also, sendStringToExecute allows you to send strings to sub prompts
//            something not possible from acedCommand where the entire command
//            sequence must be explicit.
//            
//          
//          
// 
//  RETURNS:
//      void 
void
cmd()
{
    acedCommand (RTSTR, /*NOXLATE*/"_new", RTSTR, "", RTNONE);    
    acedCommand (RTSTR, /*NOXLATE*/"_line", RTSTR, "0,0", RTSTR, "1,1", RTSTR, "", RTNONE);
    acedCommand (RTSTR, /*NOXLATE*/"_line", RTSTR, "2,0", RTSTR, "3,0", RTSTR, "", RTNONE);
    acedCommand (RTSTR, /*NOXLATE*/"_line", RTSTR, "2,2", RTSTR, "3,3", RTSTR, "", RTNONE);
    
}

//  NAME: toggleActivate()        
//
//  REMARKS:  Simple routine to exercise toggling activation on and off
//            
//            
//            NOTEs: This is a very powerful API you are completly 
//            circumventing the users ability to switch between documents
//            BE VERY SURE YOU ALWAYS RE-ENABLE ACTIVATION.
//            Given that warning it can also be very useful for porting old
//            non-reentrant commands. If you have some command that performs
//            perhaps a modal action like file i/o and you know the user should
//            never switch documents during its operation you can bracket
//            the call with these APIs.
//          
// 
//  RETURNS:
//      void 

void
toggleActivate()
{

    if (getYorN("Enable Multiple Document Activation")) {
		if( !(acDocManager->isDocumentActivationEnabled()) ) {
			Acad::ErrorStatus st = acDocManager->enableDocumentActivation();
			if ( st == Acad::eOk )
				acutPrintf(/*NOXLATE*/"==== Acad::eOk ====\n");
			else if ( st == Acad::eInvalidContext )
				acutPrintf(/*NOXLATE*/" ==== Acad::eInvalidContext ====\n");
			else
				acutPrintf(" ==== I have no clue what's going on.... ====\n");
		} else {
			acutPrintf("*******  Activation is already on.*******\n");
			return;
		}

        acutPrintf("*******  Activation ON.*******\n");
    } else {
        acDocManager->disableDocumentActivation();
        acutPrintf("*******  Activation OFF.*******\n");
    }

}



//  NAME: newdoc()        
//
//  REMARKS:  Simple routine to exercise creating new document in MDI using standard user interface
//            This API is functionally equivalent to an acedCommand of the NEW command,
//            but uses the standard Windows messaging mechanism.
//            (  PostMessage(hMainWnd, WM_COMMAND, ID_FILE_NEW, 0); )
//            It is cleaner  and will handle more situations like command already in progress
//            and you do not have to worry about nesting of acedCommand if you use this API.
//            
//            NOTEs: See the same caveats as activateDocument() example
//          
//          
// 
//  RETURNS:
//      void 
// 
void
newdoc()
{
    acDocManager->newDocument();
    acutPrintf("New document created.\n");
}


//  NAME: opendoc()        
//
//  REMARKS:  Simple routine to exercise opening a document in MDI using standard user interface
//            This API is functionally equivalent to an acedCommand of the OPEN command,
//            but uses the standard Windows messaging mechanism.
//            (  PostMessage(hMainWnd, WM_COMMAND, ID_FILE_OPEN, 0); )
//            It is cleaner  and will handle more situations like command already in progress
//            and you do not have to worry about nesting of acedCommand if you use this API.
//            
//            NOTEs: See the same caveats as activateDocument() example
//          
// 
//  RETURNS:
//      void 
// 
void
opendoc()
{
    acDocManager->openDocument();
    
}

//  NAME: closedoc()        
//
//  REMARKS:  Simple routine to exercise closing a document in MDI using standard user interface
//            This API is functionally equivalent to an acedCommand of the OPEN command,
//            but uses the standard Windows messaging mechanism.
//            (  PostMessage(hMainWnd, WM_CLOSE, 0, 0); )
//            It is cleaner  and will handle more situations like command already in progress
//            and you do not have to worry about nesting of acedCommand if you use this API.
//            
//            NOTEs: See the same caveats as activateDocument() example but realize in this case
//            if the CLOSE completes obviously the calling routine will never be returned to.
// 
//  RETURNS:
//      void 
// 
void
closedoc()
{
    AcApDocument* pDoc = selectDocument();

    if (pDoc == NULL) {
        acutPrintf("No document selected.\n");
        return;
    } 

    acDocManager->closeDocument(pDoc);
    // A line of code here will NEVER execute if the close succeeds
}


//  NAME: inAppContext()        
//
//  REMARKS:  Simple callback function to be executed in the application context.
//            
//              NOTES: The application context is unique from each document. It is the supervisor
//              that delegates between each document that is currently opened. Mode-less dialogs
//              and other floating dialogs execute in this domain. As such it is the only
//              context where a document can be created that will not be suspended when the new document
//              becomes active. In the previous OPEN and NEW APIs it was explained that once
//              suspended a line of code following those APIs would not be executed until that 
//              document is activated again. For advanced operations a developer may require the
//              ability to execute a routine from within the applciation context to overcome
//              this limitation. As such, executeInApplicationContext() and its companion funcitons
//              appContextOpenDocument() and appContextNewDocument() were provided.
//          
// 
//  RETURNS:
//      void 
// 
void 
inAppContext( void *pData)
{
    AcApDocument* pDoc = acDocManager->curDocument();
    if (acDocManager->isApplicationContext()) {
        acutPrintf("\nSucessfully Switched to App. Context\n");
        if (pData != NULL)
            acutPrintf("\nData: %s\n", (char *)pData);        
    } else
        acutPrintf("\nERROR: in Document context : %s\n",pDoc->fileName());

}

//  NAME: appcontext()        
//
//  REMARKS:  Simple function which requests a routine to be executed via the application context.
//
//
//              NOTEs: See explanation for inAppContext()
//  RETURNS:
//      void 
// 
void
appContext()
{
    static char pData[] = "Test Param";

    AcApDocument* pDoc = acDocManager->curDocument();
    if (pDoc) {
        acutPrintf("\nCurrently in Document context : %s, Switching to App.\n",pDoc->fileName());
        acDocManager->executeInApplicationContext(inAppContext, (void *)pData);
    }    

}


//  NAME: openSyncDocHelper()        
//
//  REMARKS:  Simple callback function to be executed in the application context.
//              Demonstrates opening a document synchronously to retain control
//              in caller function
//
//              NOTEs: See explanation for inAppContext()
//  RETURNS:
//      void 
// 
void 
openSyncDocHelper( void *pData)
{
    AcApDocument* pDoc = acDocManager->curDocument();
    if (acDocManager->isApplicationContext()) {
        acutPrintf("\nSucessfully Switched to App. Context\n");
        acDocManager->appContextOpenDocument((const char *)pData);
        acutPrintf("\nOpened a document synchronously:%s.\n", (const char *)pData);
    } else
        acutPrintf("\nERROR: in Document context : %s\n",pDoc->fileName());

}

//  NAME: openSyncDoc()        
//
//  REMARKS:  Simple function which requests a OPEN to be executed via the application context.
//
//
//              NOTEs: See explanation for inAppContext()
//  RETURNS:
//      void 
// 
void
openSyncDoc()
{
    static char pData[] = /*NOXLATE*/"test1.dwg";

    AcApDocument* pDoc = acDocManager->curDocument();
    if (pDoc) {
        acutPrintf("\nCurrently in Document context : %s, Switching to App.\n",pDoc->fileName());
        acDocManager->executeInApplicationContext(openSyncDocHelper, (void *)pData);
    }    

}

//  NAME: newSyncDocHelper()        
//
//  REMARKS:  Simple callback function to be executed in the application context.
//              Demonstrates creating a new document synchronously to retain control
//              in caller function
//
//              NOTEs: See explanation for inAppContext()
//  RETURNS:
//      void 
// 
void 
newSyncDocHelper( void *pData)
{
    AcApDocument* pDoc = acDocManager->curDocument();
    if (acDocManager->isApplicationContext()) {
        acutPrintf("\nSucessfully Switched to App. Context\n");
        acDocManager->appContextNewDocument((const char *)pData);
        acutPrintf("\nOpened a new document synchronously.\n");
    } else
        acutPrintf("\nERROR: in Document context : %s\n",pDoc->fileName());

}

//  NAME: newSyncDoc()        
//
//  REMARKS:  Simple function which requests a NEW to be executed via the application context.
//
//
//              NOTEs: See explanation for inAppContext()
//  RETURNS:
//      void 
// 
void
newSyncDoc()
{
    static char pData[] = /*NOXLATE*/"acad.dwt";

    AcApDocument* pDoc = acDocManager->curDocument();
    if (pDoc) {
        acutPrintf("\nCurrently in Document context : %s, Switching to App.\n",pDoc->fileName());
        acDocManager->executeInApplicationContext(newSyncDocHelper, (void *)pData);
    }    

}


//  NAME: testdlg()        
//
//  REMARKS:  creates a modeless dialog which calls several API functions
//            (from the application context & document context)
//
//
//              NOTEs: 
//  RETURNS:
//      void 
// 
void testdlg()
{
	if( modelessDlg ) {
		// dialog was already created, just display it
		// (the dialog only gets deallocated when docman.arx is unloaded)
		modelessDlg->ShowWindow( SW_SHOWNORMAL );
		return;
	}

	if( !modelessDlg && !startDlg() ) {
		ads_printf( "Failed to create modeless dialog box.\n" );
	}

}



void
initApp()
{
    gpDocReactor = new AsdkDocReactor();

    gpEditReactor = new AsdkEditorReactor();

	gpDocToModReactor = new AsdkDocToModReactor();

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_LISTDOCS",
                            "LISTDOCS",
                            ACRX_CMD_MODAL,
                            listDocuments);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_WATCHDOCS",
                            "WATCHDOCS",
                            ACRX_CMD_MODAL,
                            watchDocuments);


    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_SEND",
                            "send",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK ,
                            send);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_ACTIVATE",
                            "activate",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK ,
                            activate);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_NEWDOC",
                            "newdoc",
                            ACRX_CMD_MODAL ,
                            newdoc);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_OPENDOC",
                            "opendoc",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK ,
                            opendoc);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_CLOSEDOC",
                            "closedoc",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK ,
                            closedoc);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_CMD",
                            "cmd",
                            ACRX_CMD_MODAL ,
                            cmd);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_TOGGLE",
                            "toggle",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK,
                            toggleActivate);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_APPPROC",
                            "appcontext",
                            ACRX_CMD_MODAL | ACRX_CMD_NONEWSTACK,
                            appContext);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_NEWSYNCDOC",
                            "newsyncdoc",
                            ACRX_CMD_MODAL ,
                            newSyncDoc);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
                            /*NOXLATE*/"ASDK_OPENSYNCDOC",
                            "opensyncdoc",
                            ACRX_CMD_MODAL ,
                            openSyncDoc);

    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_DOCUMENTMANAGER",
							/*NOXLATE*/"ASDK_TESTDLG",
							"testdlg",
							ACRX_CMD_MODAL ,
							testdlg,
							NULL,
							-1,
							docmanDLL.ModuleResourceInstance());

}

void
unloadApp()
{
    acedRegCmds->removeGroup(/*NOXLATE*/"ASDK_DOCUMENTMANAGER");

    acDocManager->removeReactor(gpDocToModReactor);
    delete gpDocToModReactor;
    gpDocToModReactor = NULL;

	// destroy modeless dialog if displayed
	if( modelessDlg ) {
		modelessDlg->DestroyWindow();
		delete modelessDlg;
        modelessDlg = NULL;
	}

    acDocManager->removeReactor(gpDocReactor);
    delete gpDocReactor;
    gpDocReactor = NULL;

    acedEditor->removeReactor(gpEditReactor);
    delete gpEditReactor;
    gpEditReactor = NULL;
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        // This application can be unloaded
        acrxDynamicLinker->unlockApplication(pkt);
        // This is an MDI aware application
        acrxDynamicLinker->registerAppMDIAware(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
		break;
    }
    return AcRx::kRetOK;
}


//////////////////////////////////////////////////////////////
/// DllMain
//////////////////////////////////////////////////////////////
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		docmanDLL.AttachInstance(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		docmanDLL.DetachInstance();
	}
	return 1;   // ok
}



