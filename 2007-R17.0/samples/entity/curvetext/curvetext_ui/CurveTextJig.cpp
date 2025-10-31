// (C) Copyright 1993-2006 by Autodesk, Inc.
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


#include "curvetextjig.h"
#include "utils.h"
#include "..\CurveText_DB\curvetextIterator.h"



CCurveTextJig::CCurveTextJig(bool isStartPoint, AsdkCurveText *pCurveText)
{
	assert(pCurveText);
	pCurveText->assertWriteEnabled();
	// Tells if the jig is to get the start point (isStartPoint = true)
	// or the end point (the length) of the text.
	//
	this->isStartPoint = isStartPoint;
	m_pCurvetext = pCurveText;
	m_InputPoint.setCurveText(m_pCurvetext);
	CcurvetextIterator *pCtIt = new CcurvetextIterator(m_pCurvetext);
	m_curveLength = pCtIt->getCurveLength();
	delete pCtIt;
}

CCurveTextJig::~CCurveTextJig()
{
}


void
CCurveTextJig::doIt()
{

	AcDbObjectId eId;
	if(!m_pCurvetext) return;

	double startDist = m_pCurvetext->getStartDist();
	double length = m_pCurvetext->getLength();
	m_pCurvetext->setInJig(true);
	// sets the input point monitor
	//
	curDoc()->inputPointManager()->addPointMonitor(&m_InputPoint);
	// starts the drag sequence
	//
	AcEdJig::DragStatus stat = drag();
	// remove the input point monitor
	//
	curDoc()->inputPointManager()->removePointMonitor(&m_InputPoint);
	m_pCurvetext->setInJig(false);
	// if cancel, resets the orignal state
	//
    if(stat == AcEdJig::kCancel)
	{
		m_pCurvetext->setStartDist(startDist);
		m_pCurvetext->setLength(length);
		m_pCurvetext->recordGraphicsModified();
		return;
	}
}

AcEdJig::DragStatus
CCurveTextJig::sampler()
{
    DragStatus stat;
	stat = acquirePoint(m_point);

	if(stat == AcEdJig::kCancel)
		return stat;

	if(m_dist == m_InputPoint.getDistanceOnCurve())
		return AcEdJig::kNoChange;
	else
		m_dist = m_InputPoint.getDistanceOnCurve();
    return stat;
}

Adesk::Boolean
CCurveTextJig::update()
{
	if(isStartPoint)
	{
		if(m_pCurvetext->isReversed() == false)
			m_pCurvetext->setStartDist(m_InputPoint.getDistanceOnCurve());
		else
			m_pCurvetext->setStartDist(m_curveLength - m_InputPoint.getDistanceOnCurve());
	}
	else
	{
		if(m_pCurvetext->isReversed() == false)
		{
			if(m_pCurvetext->isClosed() == false)
			{
				m_pCurvetext->setLength(m_InputPoint.getDistanceOnCurve() - m_pCurvetext->getStartDist());
			}
			else
			{
				double length = m_InputPoint.getDistanceOnCurve() - m_pCurvetext->getStartDist();
				if(length < 0)
					length += m_curveLength;
				m_pCurvetext->setLength(length);
			}
		}
		else
		{
			if(m_pCurvetext->isClosed() == false)
				m_pCurvetext->setLength(fabs(m_curveLength - m_pCurvetext->getStartDist() - m_InputPoint.getDistanceOnCurve()));
			else
			{
				double length = m_curveLength - m_pCurvetext->getStartDist() - m_InputPoint.getDistanceOnCurve();
				if(length < 0)
					length += m_curveLength;
				m_pCurvetext->setLength(length);
			}
		}
	}
    return Adesk::kTrue;
}


AcDbEntity*
CCurveTextJig::entity() const
{
	return m_pCurvetext;
}

