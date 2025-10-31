// (C) Copyright 1993-2002 by Autodesk, Inc.
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

#include "stdafx.h"

#include "curvetextIterator.h"
#include "utils.h"


CcurvetextIterator::CcurvetextIterator(const AsdkCurveText *pCurveText, AcGiWorldDraw *ctxt)
{
	assert(pCurveText);
	m_pCurveText = (AsdkCurveText *)pCurveText;
	m_done = false;
	m_widthArray = global.widthArray;
	// calculate the length of the curve by getting the end parameter
	// and then calculating the distance at this parameter
	//
	double endParam;
	AOK(m_pCurveText->getEndParam(endParam));
	AOK(m_pCurveText->getDistAtParam(endParam, m_curveLength));

	m_fit = m_pCurveText->isFit();
	m_reverse = pCurveText->isReversed();
	m_closed = pCurveText->isClosed()? TRUE : FALSE;
	m_repeatText = pCurveText->isRepeatText();
	// calculate the current position
	// 
	if(m_reverse == false)
		m_currentDistance = pCurveText->getStartDist();
	else
		m_currentDistance = m_curveLength - pCurveText->getStartDist();

	// Calculate the array of character sizes
	// based on the text style used
	//
	// initialize our AcGiTextStyle from our text style name
	//
	AOK(fromAcDbTextStyle(m_style, m_pCurveText->getStyle()));
	// loadStyleRec has to be called to initiaze TrueType fonts
	//
	m_style.loadStyleRec();
	// set the text size
	//
	m_style.setTextSize(m_pCurveText->getSize());
	// now calculate the length of each character
	// and store it in the array
	//
	CString string = m_pCurveText->getString();
	m_nbChar = string.GetLength();
	if(m_nbChar == 0)
	{
		m_done = true;
		return;
	}
	AcGePoint2d charSize;
	char c;
	m_stringLength = 0.0;
	for(int i=0; i<m_nbChar; i++)
	{
		c = string[i];
		// we get the "extents" of each character
		// after having applies the text style.
		//
		charSize = m_style.extents( &c,
								  Adesk::kTrue,
								  1,
								  Adesk::kFalse,
								  ctxt);
		// We store the values in a global array
		// so we don't have to allocate the memory
		// for the array each time.
		// The drawback is that there IS a limit (256)
		// in the number of characters we can handle.
		//
		m_widthArray[i] = charSize.x;
		m_stringLength += charSize.x * m_pCurveText->getSpace();
	}

	// if there is no length limit for the text,
	// (m_length = 0) which is the default,
	// then the limit is the end of the curve
	// (curveLentgh), or 0 if the curve is reversed
	//
	if(m_reverse == false)
	{
		if(m_pCurveText->getLength() <= 0.0)
		{
			if(m_closed == false)
				m_endDistance = m_curveLength;
			else
				m_endDistance = m_currentDistance + m_curveLength;
		}
		else
		{
			m_endDistance = m_currentDistance + m_pCurveText->getLength();
		}

		// if the text string is not repeated,
		// we will not go pass the stringLength
		if(m_repeatText == false && m_fit == false)
		{
			if(m_endDistance > (m_currentDistance + m_stringLength))
				m_endDistance = m_currentDistance + m_stringLength;
		}

		if(m_closed == false)
		{
			// we cannot go pass the end of the curve
			//
			if(m_endDistance > m_curveLength)
				m_endDistance = m_curveLength;
		}
	}
	else
	{
		if(m_pCurveText->getLength() <= 0.0)
		{
			if(m_closed == false)
				m_endDistance = 0.0;
			else
				m_endDistance = m_currentDistance - m_curveLength;
		}
		else
		{
			m_endDistance = m_currentDistance - m_pCurveText->getLength();
		}
		// if the text string is not repeated,
		// we will not go pass the begining of the string
		if(m_repeatText == false && m_fit == false)
		{
			if(m_endDistance < (m_currentDistance - m_stringLength))
				m_endDistance = m_currentDistance - m_stringLength;
		}
		if(m_closed == false)
		{
			// we cannot go pass the begining of the curve
			//
			if(m_endDistance < 0.0)
				m_endDistance = 0.0;
		}
	}

	if(m_reverse == false)
	{
		m_currentDirectionDistance = m_currentDistance + 
									 (m_widthArray[0] / 2.0);
	}
	else
	{
		m_currentDirectionDistance = m_currentDistance - 
									 (m_widthArray[0] / 2.0);
	}

	m_currentIteration = 0;


	if(m_fit == true && m_nbChar > 1)
		// Here we calculate the disctance between two character insertion points
		// when the text is fit.
		// 
		m_fitCharSpace = (fabs(m_endDistance - m_currentDistance) 
						 - m_widthArray[m_nbChar -1] / 2.0)
						 / (m_nbChar - 1.0);
	else
		m_fitCharSpace = 0.0;
}
	
CcurvetextIterator::~CcurvetextIterator()
{
}

bool
CcurvetextIterator::done()
{
	return m_done;
}

void
CcurvetextIterator::step()
{

	m_currentIteration++;
	int index = m_currentIteration - 1;
	if(m_currentIteration == m_nbChar)
	{
		if(m_pCurveText->isRepeatText() == false)
		{
			m_done = true;
			return;
		}
		else
		{
			m_currentIteration = 0;
			index = m_nbChar -1;
		}
	}

	if(m_reverse == false)
	{
		if(m_fit == true)
		{
			m_currentDistance += m_fitCharSpace;
		}
		else
		{
			m_currentDistance += m_widthArray[index] 
								 * m_pCurveText->getSpace();
		}
		if(m_currentDistance >= m_endDistance)
		{
				m_done = true;
				return;
		}

		m_currentDirectionDistance = m_currentDistance + 
									 (m_widthArray[m_currentIteration] / 2.5);
	}
	else
	{
		if(m_fit == true)
		{
			m_currentDistance -= m_fitCharSpace;
		}
		else
		{
			m_currentDistance -= m_widthArray[index]
								 * m_pCurveText->getSpace();
		}
		if(m_currentDistance <= m_endDistance)
		{
				m_done = true;
				return;
		}
		m_currentDirectionDistance = m_currentDistance - 
									 (m_widthArray[m_currentIteration] / 2.5);
	}
}

Acad::ErrorStatus
CcurvetextIterator::getCurrentPosition(AcGePoint3d & currentPosition)
{
	Acad::ErrorStatus es;
	if(m_closed == false)
	{
		es = m_pCurveText->getPointAtDist(fabs(m_currentDistance), currentPosition);
		if(es != Acad::eOk)
			return es;
	}
	else
	{
		double dist = m_currentDistance;
		while(dist < 0.0)
			dist += m_curveLength;
		while(dist > m_curveLength)
			dist -= m_curveLength;
		es = m_pCurveText->getPointAtDist(dist, currentPosition);
		if(es != Acad::eOk)
			return es;
	}
	return Acad::eOk;
}

Acad::ErrorStatus 
CcurvetextIterator::getEndPosition(AcGePoint3d &endPosition)
{
	Acad::ErrorStatus es;
	if(m_closed == false)
	{
		es = m_pCurveText->getPointAtDist(fabs(m_endDistance), endPosition);
		if(es != Acad::eOk)
			return es;
	}
	else
	{
		double dist = m_endDistance;
		while(dist < 0.0)
			dist += m_curveLength;
		while(dist > m_curveLength)
			dist -= m_curveLength;
		es = m_pCurveText->getPointAtDist(dist, endPosition);
		if(es != Acad::eOk)
			return es;
	}
	return Acad::eOk;
}

AcGiTextStyle &
CcurvetextIterator::getTextStyle()
{
	return m_style;
}


Acad::ErrorStatus 
CcurvetextIterator::getCurrentDirection(AcGeVector3d & currentDirection)
{
	// some security: we cannot go pass the end of the
	// curve if it is not closed.
	//
	Acad::ErrorStatus es;
	if(m_currentDirectionDistance > m_curveLength && ! m_closed)
		m_currentDirectionDistance = m_curveLength;
	double param;
	if(m_closed == false)
	{
		es = m_pCurveText->getParamAtDist(fabs(m_currentDirectionDistance), param);
		if(es != Acad::eOk)
			return es;
	}
	else
	{
		double dist = m_currentDirectionDistance;
		while(dist < 0)
			dist += m_curveLength;
		while(dist > m_curveLength)
			dist -= m_curveLength;
		es = m_pCurveText->getParamAtDist(dist, param);
		if(es != Acad::eOk)
			return es;
	}

	es = m_pCurveText->getFirstDeriv(param, currentDirection);
	if(es != Acad::eOk)
		return es;
	if(m_reverse == true)
		currentDirection = -currentDirection;
	return Acad::eOk;
}

char
CcurvetextIterator::getCurrentCharacter()
{
	return m_pCurveText->getString()[m_currentIteration];
}

double
CcurvetextIterator::getCurveLength()
{
	return m_curveLength;
}