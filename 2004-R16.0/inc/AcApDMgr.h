// (C) Copyright 1990-2002 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acdocman.h"

//-----------------------------------------------------------------------------
//----- Defines
//-----     #pragma warning(disable: 4786)
//----- in your precompiled header to get rid of this warning

//-----------------------------------------------------------------------------
//----- 'DEBUG workaround' prevents the #include <map> statement in AdskDMgr.h
//----- from pulling in "use_ansi.h" that would force the debug CRT through #pragma-s.
#if defined(_DEBUG) && !defined(_FULLDEBUG_)
//----- The result of the above line is that arx/dbx application statically linked 
//----- to MFC will use the debug version of the c++ runtime, all other 
//----- configurations will use the release version.
#undef _DEBUG
#pragma message ("     Compiling STL header files in release mode.")
#include <map>
#define _DEBUG
#else
#include <map>
#endif

//-----------------------------------------------------------------------------
template <class T> class AcApDataManager : public AcApDocManagerReactor {

public:
	AcApDataManager () {
		acDocManager->addReactor (this) ;
	}
	~AcApDataManager () {
		acDocManager->removeReactor (this) ;
	}
	virtual void documentToBeDestroyed (AcApDocument *pDoc) {
		m_dataMap.erase (pDoc) ;
	}

	T &docData (AcApDocument *pDoc) {
		std::map<AcApDocument *, T>::iterator i =m_dataMap.find (pDoc) ;
		if ( i == m_dataMap.end () )
			return (m_dataMap [pDoc]) ;
		return ((*i).second) ;
	}
	T &docData () {
		return (docData (acDocManager->curDocument ())) ;
	}

private:
	std::map<AcApDocument *, T> m_dataMap ;
} ;
