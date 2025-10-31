//
//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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
//


//-----------------------------------------------------------------------------
#if !defined(ARX__PALETTESET)
#define ARX__PALETTESET

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "aduiPaletteSet.h"
#include "resource.h"

class CMyPaletteSet : public CAdUiPaletteSet 
{
    
	DECLARE_DYNCREATE(CMyPaletteSet)

protected:
	virtual void GetMinimumSize(CSize& size);
	virtual void GetMaximumSize(CSize& size);
	
public:
	DECLARE_MESSAGE_MAP()
};


#endif //----- !defined(ARX__ARX__PALETTESET)
