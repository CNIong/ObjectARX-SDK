//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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
#ifndef __AXMAT3D_H_
#define __AXMAT3D_H_

#include "gemat3d.h"
#pragma pack (push, 8)

#ifndef AXAUTOEXP
#ifdef AXAUTO_DLL
	#define AXAUTOEXP __declspec(dllexport)
#else
	#define AXAUTOEXP __declspec(dllimport)
#endif
#endif

//#pragma warning(disable : 4290) 

class AXAUTOEXP AcAxMatrix3d : public AcGeMatrix3d
{
public:
    // constructors
    AcAxMatrix3d();
    AcAxMatrix3d(const VARIANT* var) throw(HRESULT);
    AcAxMatrix3d(const VARIANT& var) throw(HRESULT);
    AcAxMatrix3d(const SAFEARRAY* safeArrayPt) throw(HRESULT);

    // equal operators
    AcAxMatrix3d& operator=(const VARIANT* var) throw(HRESULT);
    AcAxMatrix3d& operator=(const VARIANT& var) throw(HRESULT);
    AcAxMatrix3d& operator=(const SAFEARRAY* safeArrayPt) throw(HRESULT);

    // utilities
private:
    AcAxMatrix3d& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

#pragma pack (pop)
#endif

