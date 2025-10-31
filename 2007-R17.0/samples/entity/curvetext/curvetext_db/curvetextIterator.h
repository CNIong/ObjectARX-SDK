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

#ifndef CURVETEXTITERATOR_H
#define CURVETEXTITERATOR_H

#include "CurveText.h"
#include <acgiutil.h>

class
#ifdef CURVETEXTDBX
_declspec(dllexport)
#endif
CcurvetextIterator
{
public:
	CcurvetextIterator(const AsdkCurveText *pCurveText, AcGiWorldDraw *ctxt = NULL);
	~CcurvetextIterator();

	bool				done();
	void				step();
	Acad::ErrorStatus	getCurrentPosition(AcGePoint3d &currentPosition);
	Acad::ErrorStatus	getEndPosition(AcGePoint3d &endPosition);
	Acad::ErrorStatus	getCurrentDirection(AcGeVector3d &currentDirection);
	TCHAR				getCurrentCharacter();
	AcGiTextStyle&		getTextStyle();
	double				getCurveLength();


private:
	AsdkCurveText*	m_pCurveText;
	double			m_currentDistance;
	double			m_stringLength;
	double			m_currentDirectionDistance;
	double			m_endDistance;
	double			m_fitCharSpace;
	TCHAR			m_currentCharacter;
	double*			m_widthArray;
	double			m_curveLength;
	int				m_nbChar;
	int				m_currentIteration;
	bool			m_reverse;
	bool			m_fit;
	bool			m_done;
	bool			m_closed;
	bool			m_repeatText;
	AcGiTextStyle	m_style;

};



#endif
