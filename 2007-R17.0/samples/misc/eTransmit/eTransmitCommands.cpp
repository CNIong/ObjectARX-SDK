//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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
// ObjectARX defined commands, created by Fenton Webb [08/08/2003], DevTech, Autodesk
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"



//////////////////////////////////////////////////////////////////////////////
// gets a file folder
static int GetFolder (CString title, CString &folder);
//////////////////////////////////////////////////////////////////////////////
CComPtr<ITransmittalAddFileNotificationHandler> pHandler;
CComPtr<ITransmittalOperation> pITransmitOperation;
//////////////////////////////////////////////////////////////////////////////
Adesk::Boolean bActive = Adesk::kFalse;
//////////////////////////////////////////////////////////////////////////////
// This is command 'ADDNOTIFIER, by Fenton Webb [07/08/2003], DevTech, Autodesk
void asdkAddNotifier()
{
	if (bActive == Adesk::kTrue)
	{
		acutPrintf(_T("\n*** Notifier already in place. ***"));
		return;
	}	

	//	Initialise  AddFileNotification interface.
	if (!SUCCEEDED(pHandler.CoCreateInstance(CLSID_AddFileHandler)))
	{
		acedPrompt(_T("\n*** Couldn't instantiate handler interface ***"));
		return;
	}

	// Initialise the ITransmittalOperation interface.
	if (!SUCCEEDED(pITransmitOperation.CoCreateInstance(CLSID_TransmittalOperation)))
	{
		//	If failed, release the handler interface and end command
		acedPrompt(_T("\n*** Couldn't instantiate Transmittal interface ***"));
		pHandler.Release();
		return;
	}

	//	Subscribe to eTransmit notifications.
	if (!SUCCEEDED(pITransmitOperation->subscribeToAddFileNotification(pHandler)))
	{
		acedPrompt(_T("\n*** Couldn't subscribe to Add File notification ***"));
		pHandler.Release();
		pITransmitOperation.Release();
		return;
	}
	bActive = Adesk::kTrue;
	acedPrompt(_T("\n*** eTransmit Notifier attached ***"));
	return;
}

//////////////////////////////////////////////////////////////////////////////
// This is command 'REMOVENOTIFIER, by Fenton Webb [07/08/2003], DevTech, Autodesk
void asdkRemoveNotifier()
{
	if (bActive == Adesk::kFalse)
	{
		acedPrompt(_T("\n*** There is no eTransmit Notifier in place ***"));
		return;
	}

	//	Stop subscribing to eTransmit notifications
	if (SUCCEEDED(pITransmitOperation->cancelSubscriptionToAddFileNotification(pHandler)))
	{
		pITransmitOperation.Release();
		pHandler.Release();
		bActive = Adesk::kFalse;
		acedPrompt(_T("\n*** eTransmit Notifier removed ***"));
	}
	else
	{
		acedPrompt(_T("\n*** Can't unsubscribe from Add File notification ***"));
	}
}

//////////////////////////////////////////////////////////////////////////////
// This is command 'MYTRANSMIT, by Fenton Webb [07/08/2003], DevTech, Autodesk
void asdkMyTransmit()
{
	// get the files that need to be sent
	CFileDialog fileDlgDwgs (TRUE, _T("*.dwg"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("Drawing files (*.dwg) |*.dwg||"), acedGetAcadFrame());	
	// now ping up the dialog
	int res = fileDlgDwgs.DoModal();
	// if the user selected ok
	if (res == IDOK)
	{
		CComPtr<ITransmittalOperation2> pITransmitOperation2;
		// Initialise new TransmittalOperation2 interface, if ok
		if (SUCCEEDED(pITransmitOperation2.CoCreateInstance(CLSID_TransmittalOperation2)))
		{
			CComPtr<ITransmittalInfo2> pITransmitInfo2;
			// get the ITransmittalInfo2 interface related to current transmittal operation.
			CHECK(pITransmitOperation2->getTransmittalInfoInterface (&pITransmitInfo2));		

			CString transmitalFolder;
			// Specify the root directory where transmittal package will be created.
			res = GetFolder(CString(_T("Root directory for transmittal package")), transmitalFolder);
			// if the user selected successfully
			if (res == IDOK)
			{
				// set where we want the files to be packaged into
				CHECK(pITransmitInfo2->put_destinationRoot (_bstr_t(transmitalFolder)));
				// Specify which drawing file format to save drawing files to when 
				// they are added to a transmittal package, we want no conversion, which is default anyway
				CHECK(pITransmitInfo2->put_saveVersion (eNoConversion));
				// Specify that we want the preservation of the directory structure in transmittal package. 
				// If this false, all files are put in the specified root directory or if the option 
				// ‘organized folder structure’ is selected, they will be put in appropriate directory.
				CHECK(pITransmitInfo2->put_preserveSubdirs(TRUE));

				// TODO: how to deal with duplicate files when packaging to a directory
				CHECK(pITransmitInfo2->put_defaultOverwriteValue (eOverwriteNo));

				// these are all defaulted to true anyway
				// pITransmitInfo2->put_includeXrefDwg (TRUE);
				// pITransmitInfo2->put_includeImageFile (TRUE);
				// pITransmitInfo2->put_includeFontFile (TRUE);
				// pITransmitInfo2->put_includePlotFile(TRUE);

				AddFileReturnVal retVal;
				CComPtr<ITransmittalFile> pITransmitFile;
				// now that we have everything setup, we need to loop through
				// all the dwg files that the user has selected and add them to the transmittal
				POSITION pos = fileDlgDwgs.GetStartPosition();
				// loop while we have files
				while (pos != NULL)
				{
					// get the drawing name out of the position list
					CString dwgFile = fileDlgDwgs.GetNextPathName(pos);
					// add the drawing to the transmittal
					if (SUCCEEDED(pITransmitOperation2->addDrawingFile (_bstr_t(dwgFile), &pITransmitFile, &retVal)))
						acutPrintf (_T("\nAdded '%s' to the transmittal, return code = %d"), dwgFile, retVal);
				}

				// File Graph...
				CComQIPtr<ITransmittalOperation> pITransmittalOperation = pITransmitOperation2;
				// get the ITransmittalFilesGraph interface
				CComQIPtr<ITransmittalFilesGraph> pIGraph;
				CHECK(pITransmittalOperation->graphInterfacePtr (&pIGraph));

				// query interface for the ITransmittalFilesGraph2 interface
				CComQIPtr<ITransmittalFilesGraph2> pIGraph2 = pIGraph;
				// get the root of the files graph
				CComPtr<ITransmittalFile> pRoot;
				pIGraph2->getRoot(&pRoot);					
				
				// now display the dialog, this will call dlg.TraverseTransmittalDependents() to fill
				// the tree view control
				CTransmittalGraphDialog dlg (pRoot, acedGetAcadFrame());
				if (dlg.DoModal() == IDOK)
				{
					// finally create the transmittal, you will now need to zip up the files 
					// contained in transmitalFolder and send them yourself
					CHECK(pITransmitOperation2->createTransmittalPackage ());
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// gets a folder
static int GetFolder (CString title, CString &folder)
{
	LPMALLOC shAlloc;
	int returnValue = IDCANCEL;

	//  we need the shell's default allocator
	if ( ::SHGetMalloc(&shAlloc) == NOERROR )
	{
		BROWSEINFO bi;
		TCHAR buf[MAX_PATH];
		LPITEMIDLIST idList;
		LPARAM params[2];

		//  init data
		bi.hwndOwner = acedGetAcadFrame()->m_hWnd;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = buf;
		bi.lpszTitle = title;
		params[0] = (LPARAM)(LPCTSTR)folder;
		params[1] = title.IsEmpty() ? NULL : (LPARAM)(LPCTSTR)title;
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = (LPARAM)params;

		//  call dialog
		if ( (idList = ::SHBrowseForFolder(&bi)) != NULL )
		{
			//  convert ID list to file system path
			if ( ::SHGetPathFromIDList(idList, buf) )
			{
				folder = buf;
				returnValue = IDOK;
			}
			//  release ID list
			shAlloc->Free(idList);
		}
		//  release shell allocator
		shAlloc->Release();
	}	

	return (returnValue);
}

