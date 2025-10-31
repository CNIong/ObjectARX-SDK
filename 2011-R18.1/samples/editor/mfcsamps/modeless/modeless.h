// (C) Copyright 1996-2006 by Autodesk, Inc. 
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

#include <dbapserv.h>
#define CUR_DB acdbHostApplicationServices()->workingDatabase()

//helper functions:
void objDisplay(const TCHAR* pWhat, const AcDbObject* pDbObj);

void attachDbReactor(AcDbDatabase* pDb);
void detachDbReactor(AcDbDatabase* pDb, bool bDlgStay);
BOOL endDlg();
BOOL startDlg();
void hello();
void MyArxCmd();


Adesk::Boolean getYorN( const TCHAR* pStr );

void errmsg( LPTSTR msg );
void errmsgf( LPTSTR fmt, ... );
void initApp();
void unloadApp();

extern "C" AcRx::AppRetCode acrxEntryPoint ( AcRx::AppMsgCode msg, void* );

