//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
//----- CFilterDocumentReactor.h : Declaration of the CFilterDocumentReactor
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acdocman.h"
#include "SubSelFilter.h"
#include "SubEntSelFilter.h"
//-----------------------------------------------------------------------------


// Class to maintain the list of filter per document
// The corresponding Filter for an AcDocument is tracked,
// mainly in order to delete it if the document is going away.

class CFilterDocumentReactor : public AcApDocManagerReactor {

public:
	ACRX_DECLARE_MEMBERS(CFilterDocumentReactor) ;

protected:
	//----- Auto initialization and release flag.
	bool mbAutoInitAndRelease ;

public:
	CFilterDocumentReactor (const bool autoInitAndRelease =true) ;
	virtual ~CFilterDocumentReactor () ;

	virtual void Attach () ;
	virtual void Detach () ;
	virtual AcApDocManager *Subject () const { return (acDocManager) ; }
	virtual bool IsAttached () const { return (mbAutoInitAndRelease) ; }

	// -----------------------------------------------------------------------------
	//virtual void documentActivated(AcApDocument * pActivatedDoc);
	// -----------------------------------------------------------------------------
	virtual void documentToBeDestroyed(AcApDocument * pDocToDestroy);
	// -----------------------------------------------------------------------------
	//virtual void documentCreated(AcApDocument * pDocCreating);

	//-------------------------------------------------------------------------------
	  void addSubSelFilter(AcApDocument* pDoc);
	  void addSubEntSelFilter(AcApDocument* pDoc);
	  void deleteSubSelFilter(AcApDocument* pDoc);
      void deleteSubEntSelFilter(AcApDocument* pDoc);
	  void removeAllFilters();

private:


		typedef std::map<long, CSubSelFilter*> SubSelFilterMap;
        typedef SubSelFilterMap::iterator SSFMapIterator;
        typedef std::pair<long, CSubSelFilter*> SSFMapPair;

		typedef std::map<long, CSubEntSelFilter*> SubEntSelFilterMap;
        typedef SubEntSelFilterMap::iterator SESFMapIterator;
        typedef std::pair<long, CSubEntSelFilter*> SESFMapPair;


		SubSelFilterMap mSSFMap;
        SubEntSelFilterMap mSESFMap;

} ;

ACDB_REGISTER_OBJECT_ENTRY_AUTO(CFilterDocumentReactor)
