//
// (C) Copyright 2002 by Autodesk, Inc. 
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

/////////////////////////////////////////////
// AcApDocManagerReactor reactors.

#if !defined(ARX__RDOCMANAGERREACTOR_H__20020813_101601)
#define ARX__RDOCMANAGERREACTOR_H__20020813_101601

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "acdocman.h"


class asdkDocManagerReactor : public AcApDocManagerReactor
{
public:

	// Constructor / Destructor
	asdkDocManagerReactor(const bool autoInitAndRelease = true);
	virtual ~asdkDocManagerReactor();

	//{{AFX_ARX_METHODS(asdkDocManagerReactor)
	virtual void documentCreated(AcApDocument* pDocCreating);
	virtual void documentToBeDestroyed(AcApDocument* pDocToDestroy);
	//}}AFX_ARX_METHODS

private:
	// Auto initialization and release flag.
	bool m_autoInitAndRelease;
};



#endif // !defined(ARX__RDOCMANAGERREACTOR_H__20020813_101601)