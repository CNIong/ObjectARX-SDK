//
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
//
#ifndef _ASDK_BOLTJIG_H
#define _ASDK_BOLTJIG_H

#include "stdafx.h"

#include "dbjig.h"
#include "dbmain.h"

#include <afxdisp.h>        // MFC OLE automation classes
#include "rxmfcapi.h"

#include "adslib.h"
#include "acestext.h"
#include "dbents.h"
#include "dbregion.h"
#include "dbsol3d.h"

#include "gepnt3d.h"
#include "dbxutil.h"
#include "dbapserv.h"

#include <comdef.h>
#include "acdocman.h"

#include "..\boltWrapper\boltWrapper.h"
#include "..\boltWrapper\boltWrapper_i.c"

#include "axpnt3d.h"
#include "initguid.h"
#include "axboiler.h"

extern CComModule _Module;
#include "CComBoltCmd.h"
#include "..\boltObject\asdkBolt.h"

#ifdef _BOLTUI_
#define JIGDLLIMPEXP __declspec(dllexport)
#else
#define JIGDLLIMPEXP 
#endif

class JIGDLLIMPEXP AsdkBoltJig : public  AcEdJig
{
 public:
    AsdkBoltJig();

    virtual ~AsdkBoltJig();

    DWORD m_dConnectionID;

    CComPtr<IUnknown> m_pUnkCmd;
    CComPtr<IBolt> mBolt;
    CComQIPtr<IAcadBaseObject2> m_pBaseObj;
    CComObject<CComBoltCmd>* m_pBoltCmd;
    CComPtr<IConnectionPoint> m_pConPt;
    AcDbDatabase* m_pDb;
	AcGePoint3d cursorPos,lastCursorPos;
	
	bool GotHeadDiameter, GotPosition, GotShaftDiameter;

	asdkBolt *m_pBolt;

	
	double headDia, shaftDia;

    // overridden methods from AcEdJig class
    //
    AcDbEntity*        entity() const;
    DragStatus	       sampler();
    Adesk::Boolean     update();
	void release();
	void getPointer();
	void inputInitialValues();

    void getPosition(AcGePoint3d &c) {
        AcAxPoint3d pt3dCtr(0.0,0.0,0.0);
        VARIANT *pVar = pt3dCtr.asVariantPtr();
        mBolt->get_position(pVar);
        pt3dCtr = pVar;
        c.x = pt3dCtr.x;
        c.y = pt3dCtr.y;
		c.z = pt3dCtr.z;
    }
	
    void setPosition(AcGePoint3d &c) {
        AcAxPoint3d pt3d(c.x,c.y,c.z);
        mBolt->put_position(*pt3d.asVariantPtr());
    }
	
	void setHeadSides(long c) {
        mBolt->put_headSides(c);
    }
	void setHeadDiameter(double c) {
        mBolt->put_headDiameter(c);
    }
    void setHeadHeight(double c) {
        mBolt->put_headHeight(c);
    }
    void setShaftLength(double c) {
        mBolt->put_shaftLength(c);
    }
    void setShaftDiameter(double c) {
        mBolt->put_shaftDiameter(c);
    }
    void setThreadLength(double c) {
        mBolt->put_threadLength(c);
    }
    void setThreadWidth(double c) {
        mBolt->put_threadWidth(c);
    }
	void setMaterialName(char* c){
		CComBSTR bstr(c);
		mBolt->put_materialName(bstr.m_str);
	}
	void setPartNumber(char *c){
		CComBSTR bstr(c);
		mBolt->put_partNumber(bstr.m_str);
	}

    void getHeadSides(int &c) {
        mBolt->get_headSides(&c);
    }
	void getHeadDiameter(double &c) {
        mBolt->get_headDiameter(&c);
    }
    void getHeadHeight(double &c) {
        mBolt->get_headHeight(&c);
    }
    void getShaftLength(double &c) {
        mBolt->get_shaftLength(&c);
    }
    void getShaftDiameter(double &c) {
        mBolt->get_shaftDiameter(&c);
    }
    void getThreadLength(double &c) {
        mBolt->get_threadLength(&c);
    }
    void getThreadWidth(double &c) {
        mBolt->get_threadWidth(&c);
    }
	void getMaterialName(char *c) {
		USES_CONVERSION;
		CComBSTR bstr;
		mBolt->get_materialName(&bstr.m_str);
		strcpy(c,OLE2A(bstr.m_str));
	}
	void getPartNumber(char *c) {
		USES_CONVERSION;
		CComBSTR bstr;
		mBolt->get_partNumber(&bstr.m_str);
		strcpy(c,OLE2A(bstr.m_str));
	}

private:
public:
	int samplerType;
};

#endif
