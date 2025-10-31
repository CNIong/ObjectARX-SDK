//
//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
//----- adskDocReactor.h : Declaration of the adskDocReactor
//-----------------------------------------------------------------------------
#pragma once

#ifdef DRAWORDERSAMP_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "acdocman.h"

//-----------------------------------------------------------------------------
//----- Note: Uncomment the DLLIMPEXP symbol below if you wish exporting
//----- your class to other ARX/DBX modules
class /*DLLIMPEXP*/ adskDocReactor : public AcApDocManagerReactor {

public:
	ACRX_DECLARE_MEMBERS(adskDocReactor) ;

protected:
	//----- Auto initialization and release flag.
	bool mbAutoInitAndRelease ;

public:
	adskDocReactor (const bool autoInitAndRelease =true) ;
	virtual ~adskDocReactor () ;
	virtual void Attach () ;
	virtual void Detach () ;
	virtual AcApDocManager *Subject () const ;
	virtual bool IsAttached () const ;
	virtual void documentLockModeChanged(AcApDocument* pDoc,
							 AcAp::DocLockMode myPreviousMode,
							 AcAp::DocLockMode myCurrentMode,
							 AcAp::DocLockMode currentMode,
                             const TCHAR* pGlobalCmdName);


} ;

#ifdef DRAWORDERSAMP_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(adskDocReactor)
#endif
