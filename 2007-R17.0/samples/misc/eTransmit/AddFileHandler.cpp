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

// AddFileHandler.cpp : Implementation of CAddFileHandler
#include "StdAfx.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ETransmit.h"
#include "AddFileHandler.h"
#include "string.h"




/////////////////////////////////////////////////////////////////////////////
// CAddFileHandler

STDMETHODIMP CAddFileHandler::addFileNotificationHandler(ITransmittalFile * pFile, ITransmittalOperation * pTransmit)
{
	//	Get the pathname and filename
	CComBSTR SrcName;
	// sourcePath( [out, retval] BSTR* pVal );
	pFile->get_sourcePath(&SrcName);
	
	//	Convert BSTR to char * for text manipulation
	USES_CONVERSION;
    TCHAR * strFile = OLE2T(SrcName);
	
	//	Output progress to command line
    acutPrintf(_T("\n***  Handling file : %s ***"), strFile);
	
	// We only want to respond once per transmittal. 
	//	The response should be to the main dwg file.
	//	(The main drawing file has FileType = eDwgFile).
	FileType type;
	// fileType( [out, retval] FileType* pVal );
	pFile->get_FileType(&type);
    if (type != eDwgFile)
	{
        return S_OK;
	}	
	
	//	locate last backslash in filename
	TCHAR * temp = _tcsrchr(strFile, _T('\\'));
	
	//	Truncate string at that point to remove filename from pathname
	*temp = _T('\0');
	
	//	Store path (without filename) in a BSTR for use by COM interface
	CComBSTR pathName;
	pathName.Append(strFile);
	
	//	Specify pathname + filename of the files we want to add.
	CComBSTR filesToAdd[4];
	filesToAdd[0] = pathName;
	filesToAdd[0].Append(_T("\\Test.xml"));
	filesToAdd[1] = pathName;
	filesToAdd[1].Append(_T("\\TestSchema.xml"));
	filesToAdd[2] = pathName;
	filesToAdd[2].Append(_T("\\testXmlProj.dvb"));
	filesToAdd[3] = pathName;
	filesToAdd[3].Append(_T("\\XMLReadMe.doc"));
	
	//	Add the library files to the transmittal
	AddFileReturnVal returnVal;
	ITransmittalFile * pIAddedFile = NULL;
	
	//	Try to add all four files.
	Adesk::Boolean errFlag = Adesk::kFalse;
	for (int i = 0; i < 4; i++)
	{
		// addFile(
		//			[in] const BSTR bstrFullPath,
		//			[in] const BSTR bstrVersion,
		//			[in] const ITransmittalFile* pIParentFile,
		//			[in] BOOL bAddedBy3rdParty,
		//			[out] ITransmittalFile** ppIAddedFile,
		//			[out, retval] AddFileReturnVal* pRetVal );
		pTransmit->addFile(filesToAdd[i], NULL, pFile, TRUE, &pIAddedFile, &returnVal);
		if ((returnVal != eFileAdded) || (pIAddedFile == NULL))
		{
			errFlag = Adesk::kTrue;
		}
		else
		{
			//	Even if addFile returns eFileAdded, we have to check that the new file
			//	does exist. If the pathname was wrong, then addFile can return eFileAdded, 
			//	even if the file cannot be found.
			long fileExists;
			// fileExists( [out, retval] BOOL* pVal );
			pIAddedFile->get_fileExists(&fileExists);
			if ( !fileExists )
			{
				errFlag = Adesk::kTrue;
			}
		}
	}
	
	//	Add text to transmittal report.	
	
	long reportStorageIndex = -1;
	CComBSTR ReportText;
	
	ReportText = _T("\r\n*** Notifier Sample Report ***\r\n\r\n");
	ReportText.Append(_T("Demonstrated at iDevelop - 2nd November, 2000 \r\n"));
    ReportText.Append(_T("http://www.autodesk.com/idevelop2000 \r\n\r\n"));
	// addToReport(
	//				[in] const BSTR bstrTextToAdd,
	//				[in] const long nIndex,
	//				[out, retval] long* pnIndex);
	pTransmit->addToReport(ReportText, -1, &reportStorageIndex);
	
	if (errFlag)	//	report failure.
	{
		ReportText = _T("One or more files could not be included with the drawing '");
		ReportText.Append(SrcName);
		ReportText.Append(_T("'.\r\n"));
		ReportText += _T("Please contact the sender.\r\n\r\n");
		pTransmit->addToReport(ReportText, reportStorageIndex, NULL);
	}
	else		//	report success
	{
		ReportText = _T("The drawing '");
		ReportText.Append(SrcName);
		ReportText.Append(_T("' was created from an XML document using a VBA macro.\r\n"));
		ReportText.Append(_T("Please see the included Read Me file for more details.\r\n\r\n")) ;
		pTransmit->addToReport(ReportText, reportStorageIndex, NULL);
	}
	return S_OK;
}


STDMETHODIMP CAddFileHandler::beginFilesGraphCreation(ITransmittalOperation * pTransmit)
{
	acedPrompt(_T("\n\n*** Start of Files Graph Creation ***\n"));
	return S_OK;
}


STDMETHODIMP CAddFileHandler::endFilesGraphCreation(ITransmittalOperation * pTransmit)
{
	acedPrompt(_T("\n\n*** End of Files Graph Creation ***\n"));
	return S_OK;
}
