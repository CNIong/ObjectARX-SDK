//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdb.h"
#include "acgs.h"
#include "gs.h"
#include "acedads.h"
#include "acgsmanager.h"
#include "dbmain.h"
#include "acestext.h"
#include "acdocman.h"
#include "adscodes.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "gemat3d.h"
#include "acgi.h"
#include "geassign.h"
#include <math.h>
#include "dbjig.h"
#include "cmdexception.h"
#include "intermediary.h"
#include "dbapserv.h"
#include "aced.h"
#include "dbxutil.h"



#if _MSC_VER > 1200
#pragma warning(push)
#endif
#pragma warning(disable:4290)
#pragma warning(disable:4310)


static AcDbObjectId GetModelSpaceBlockID (void)
{
    AcDbObjectId            ObjectId;
    AcDbBlockTable *        pBlockTable;
    Acad::ErrorStatus       status;

    status = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
    if (status != Acad::eOk) 
        return false;

    status = pBlockTable->getAt(ACDB_MODEL_SPACE, ObjectId);
    pBlockTable->close();
    return ObjectId;
}


class Jig3d : public AcEdJig
{
protected:
    AcDbPolyline m_dummy;
    AcGsModel* m_pModel;
    AcGePoint3d m_refPoint;
    double m_elev;
    Intermediary m_int;
	AcGeMatrix3d m_xform;
	AcGeMatrix3d m_xformTemp;
    AcGePoint3d  m_LastPoint;
    AcDbObjectId m_MSBObjectID;

	enum Mode {kMove=0, kRotateX, kRotateY, kRotateZ} m_mode;

	void apply() throw(CmdException);

public:
    Jig3d()
        :m_pModel(0),m_LastPoint(0.0,0.0,0.0)
    { }
    ~Jig3d();
	//This sample uses AcEdJig in a slightly unconventional way.
	//The following two overrides are usually concerned with
	//updating the display. They are dummies in this sample
	//since we are updating the display ourselves.
    virtual Adesk::Boolean  update()
	{
	    return Adesk::kFalse;
	}
    virtual AcDbEntity* entity() const
	{
	    return const_cast<AcDbPolyline*>(&m_dummy);
	}

	virtual DragStatus	sampler(); 
    void engage(void)throw(CmdException);
	void init(const AcDbObjectId& idEntity,const AcGePoint3d& refPoint,int viewportNumber) throw(CmdException);
};
Jig3d::~Jig3d()
{
    if (m_pModel)
    {
        m_pModel->onErased (&m_int, m_MSBObjectID.asOldId());
    }
}

AcEdJig::DragStatus Jig3d::sampler()
{
    setSpecialCursorType(AcEdJig::kRubberBand);
    AcGePoint3d pt,temp;
	AcEdJig::DragStatus status;
	double angle;
	if (m_mode == kMove){
		setKeywordList(_T("Base X Y Z Exit"));
		status = acquirePoint(pt,m_refPoint);
        acdbWcs2Ucs(asDblArray(pt),asDblArray(pt),Adesk::kFalse);
        pt.z = m_elev;
        acdbUcs2Wcs(asDblArray(pt),asDblArray(pt),Adesk::kFalse);
	} else {
		setKeywordList(_T("Exit"));
    	status = acquirePoint(pt,m_refPoint);
        acdbWcs2Ucs(asDblArray(pt),asDblArray(pt),Adesk::kFalse);
        pt.z = m_elev;
        acdbUcs2Wcs(asDblArray(pt),asDblArray(pt),Adesk::kFalse);
		angle = acutAngle(asDblArray(pt),asDblArray(m_refPoint));
	}

    if (pt == m_LastPoint)      // if there is no work to be done,
        return status;          // exit early!
    m_LastPoint = pt;

	if (status == AcEdJig::kNormal){
		switch (m_mode)
		{
		case kMove:
			m_xformTemp = AcGeMatrix3d::translation(pt-m_refPoint);
			m_int.setTransform(m_xformTemp*m_xform);
			break;
		case kRotateX:
			m_xformTemp = AcGeMatrix3d::rotation(angle,AcGeVector3d::kXAxis,m_refPoint);
			m_int.setTransform(m_xformTemp*m_xform);
			break;
		case kRotateY:
			m_xformTemp = AcGeMatrix3d::rotation(angle,AcGeVector3d::kYAxis,m_refPoint);
			m_int.setTransform(m_xformTemp*m_xform);
			break;
		case kRotateZ:
			m_xformTemp = AcGeMatrix3d::rotation(angle,AcGeVector3d::kZAxis,m_refPoint);
			m_int.setTransform(m_xformTemp*m_xform);
			break;
		}
		m_pModel->onModified(&m_int, m_MSBObjectID.asOldId());

	}
    return status;
}
void Jig3d::apply() throw(CmdException)
{
	m_xform = m_xformTemp*m_xform;
	AcDbEntity* pE;
	if (acdbOpenObject(pE,m_int.m_idEntity,AcDb::kForWrite)==Acad::eOk)
	{
		Acad::ErrorStatus es;
		if ((es=pE->transformBy(m_xform))!=Acad::eOk)
			throw CmdException(es,_T("Transformation cannot be applied to object"));
		pE->close();
	}
}

void Jig3d::init(const AcDbObjectId& idEntity,const AcGePoint3d& refPoint,int viewportNumber) throw(CmdException)
{
	m_int.m_idEntity    = idEntity;
    m_refPoint          = refPoint;
    AcGsManager * pMan  = acgsGetGsManager();
    if (pMan==NULL)
        throw CmdException(_T("Cannot get Gs manager"));

    AcGsView * pView    = acgsGetGsView (viewportNumber, false);
    if (pView==0)
        throw CmdException(_T("Perform this command in a 3d View.  Use the shademode command to activate one."));

    m_MSBObjectID       = GetModelSpaceBlockID();
    if (m_MSBObjectID.asOldId() == 0)
        throw CmdException(_T("Unable to retrieve modelspace block ID"));

    m_pModel            = pMan->getDBModel();
    if (m_pModel==NULL)
        throw CmdException(_T("Unable to retrieve AcDb AcGsModel"));
    AcGePoint3d pt(refPoint);
    acdbWcs2Ucs(asDblArray(pt),asDblArray(pt),Adesk::kFalse);
    m_elev = pt.z;
    m_pModel->onAdded  (&m_int, m_MSBObjectID.asOldId());
	m_mode = kMove;
}

void Jig3d::engage(void) throw(CmdException)
{
    TCHAR* prompt = _T("\nSpecify displacement or [Base point/X/Y/Z/Exit]:");
	AcEdJig::DragStatus status;
	do
	{
		setDispPrompt(prompt);
		status = drag();
		switch (status)
		{
		case AcEdJig::kKW1:
			if (m_mode == kMove)
            {
                acedGetPoint(asDblArray(m_refPoint),_T("Specify base point:"),asDblArray(m_refPoint));
                acdbUcs2Wcs(asDblArray(m_refPoint),asDblArray(m_refPoint),Adesk::kFalse);
            }
			else {
				apply();
				status = AcEdJig::kCancel;
			}
			break;
		case AcEdJig::kKW2:
			assert(m_mode == kMove);
			m_mode = kRotateX;
            prompt = _T("Specify rotation around X axis or [Exit]:");
			break;
		case AcEdJig::kKW3:
			assert(m_mode == kMove);
			m_mode = kRotateY;
            prompt = _T("Specify rotation around Y axis [Exit]:");
			break;
		case AcEdJig::kKW4:
			assert(m_mode == kMove);
			m_mode = kRotateZ;
            prompt = _T("Specify rotation around Z axis [Exit]:");
			break;
		case AcEdJig::kKW5:
			apply();
			status = AcEdJig::kCancel;
			break;
		default:
			m_xform = m_xformTemp*m_xform;
			if (m_mode == kMove)
				m_refPoint+=m_xformTemp.translation();
			m_mode = kMove;
            prompt = _T("\nSpecify displacement or [Base point/X/Y/Z/Exit]:");
			break;
		}
	}
	while (status != AcEdJig::kCancel);
}

void jig3d()
{
    
    try
    {
        struct resbuf rb;
        acedGetVar(_T("cvport"), &rb);
        if (rb.resval.rint==1)
            throw CmdException(_T("3djig cannot be used in layout mode"));
        ads_name ename;
        ads_point pt;
		int rt;
        if ((rt = acedEntSel(_T("Select object:"),ename,pt))==RTCAN)
			return;
		if (rt!=RTNORM)
			throw CmdException(Acad::eInvalidInput,_T("Invalid selection. Try again!"));
        AcDbObjectId id;
        acdbGetObjectId(id,ename);

        Jig3d jig;
        acdbUcs2Wcs(pt,pt,Adesk::kFalse);
        jig.init(id, asPnt3d(pt), rb.resval.rint);
        jig.engage();
    }
    catch(CmdException e)
    {
        const TCHAR* strDesc = e.description();
        if (strDesc == NULL)
            strDesc = _T("No description.");
        acutPrintf(_T("ERROR:%s (es=%s)"),strDesc,acadErrorStatusText(e.errorStatus()));
    }
}
#if _MSC_VER > 1200
#pragma warning(pop)
#endif
