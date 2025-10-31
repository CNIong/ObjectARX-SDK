//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcFdUtil.h
//
// Description:     Header for global methods exported from AcFdEval 
//                  module
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

interface IAcSmDatabase;
interface IAcSmSheetSet;
interface IAcSmComponent;


#ifdef  ACFD_API
#  define   ACFD_PORT  __declspec(dllexport)
#else
#  define   ACFD_PORT  
#endif


// Options for AcFdMakeFieldCode()
#define ACFD_MFC_HYPERLINK                  (0x1 << 0)
#define ACFD_MFC_PLACEHOLDER                (0x1 << 1)


ACFD_PORT BOOL      AcFdMakeFieldCode       (const AcDbObjectId& objId, 
                                             LPCTSTR pszPropName, 
                                             char*& pszFieldCode, 
                                             LPCTSTR pszFormat      = NULL, 
                                             LPCTSTR pszHLUrl       = NULL, 
                                             LPCTSTR pszHLDesc      = NULL, 
                                             LPCTSTR pszHLSubLoc    = NULL);
ACFD_PORT BOOL      AcFdMakeFieldCode       (IAcSmDatabase* pSmDb, 
                                             IAcSmSheetSet* pSmSheetSet, 
                                             IAcSmComponent* pSmComp, 
                                             LPCTSTR pszCompName, 
                                             LPCTSTR pszPropName, 
                                             char*& pszFieldCode, 
                                             LPCTSTR pszFormat      = NULL, 
                                             int nOptions           = 0);

ACFD_PORT BOOL      AcFdExtractData         (AcDbField* pField, 
                                             char*& pszSheetSetFile, 
                                             char*& pszSheetSetId, 
                                             char*& pszCompName, 
                                             char*& pszCompId, 
                                             char*& pszPropName);
ACFD_PORT BOOL      AcFdExtractData         (AcDbField* pField, 
                                             AcDbObjectId& objId, 
                                             char*& pszPropName);
