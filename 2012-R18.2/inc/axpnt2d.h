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
#ifndef __AXPNT2D_H_
#define __AXPNT2D_H_

#include "gept2dar.h"
#include "gepnt2d.h"
#include "gevec2d.h"
#pragma pack (push, 8)

#ifndef AXAUTOEXP
#ifdef AXAUTO_DLL
	#define AXAUTOEXP __declspec(dllexport)
#else
	#define AXAUTOEXP __declspec(dllimport)
#endif
#endif

#pragma warning(disable : 4290) 

class AXAUTOEXP AcAxPoint2d : public AcGePoint2d
{
public:
    // constructors
    AcAxPoint2d();
    AcAxPoint2d(double x, double y);
    AcAxPoint2d(const AcGePoint2d& pt);
    AcAxPoint2d(const AcGeVector2d& pt);
   	AcAxPoint2d(const VARIANT* var) throw(HRESULT);
   	AcAxPoint2d(const VARIANT& var) throw(HRESULT);
   	AcAxPoint2d(const SAFEARRAY* safeArrayPt) throw(HRESULT);

    // equal operators
   	AcAxPoint2d& operator=(const AcGePoint2d& pt);
   	AcAxPoint2d& operator=(const AcGeVector2d& pt);
   	AcAxPoint2d& operator=(const VARIANT* var) throw(HRESULT);
   	AcAxPoint2d& operator=(const VARIANT& var) throw(HRESULT);
   	AcAxPoint2d& operator=(const SAFEARRAY* safeArrayPt) throw(HRESULT);

    // type requests
    VARIANT* asVariantPtr() const throw(HRESULT);
    SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);

    VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
    VARIANT* setVariant(VARIANT* var) const throw(HRESULT);

    // utilities
private:
    AcAxPoint2d& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

#pragma warning(disable : 4275) 

class AXAUTOEXP AcAxPoint2dArray : public AcGePoint2dArray
{
public:
    // equal operators
   	AcAxPoint2dArray& append(const AcGePoint2d& pt);
   	AcAxPoint2dArray& append(const VARIANT* var) throw(HRESULT);
   	AcAxPoint2dArray& append(const VARIANT& var) throw(HRESULT);
   	AcAxPoint2dArray& append(const SAFEARRAY* safeArrayPt) throw(HRESULT);
    
    
    // type requests
    SAFEARRAY* asSafeArrayPtr() const throw(HRESULT);

    VARIANT& setVariant(VARIANT& var) const throw(HRESULT);
    VARIANT* setVariant(VARIANT* var) const throw(HRESULT);

    // utilities
private:
    AcAxPoint2dArray& fromSafeArray(const SAFEARRAY* safeArrayPt) throw(HRESULT);
};

#pragma pack (pop)
#endif
