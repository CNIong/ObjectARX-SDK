//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

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

