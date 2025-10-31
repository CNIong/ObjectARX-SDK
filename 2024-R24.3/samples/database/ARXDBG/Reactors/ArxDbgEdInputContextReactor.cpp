//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgEdInputContextReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmObjects.h"
#include "ArxDbgRbList.h"



/****************************************************************************
**
**  ArxDbgEdInputContextReactor::ArxDbgEdInputContextReactor
**
**  **jma
**
*************************************/

ArxDbgEdInputContextReactor::ArxDbgEdInputContextReactor()
:	m_showDetails(false),
	m_suppressDetailsDuringDrag(true),
	m_dragJustStarted(false)
{
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::~ArxDbgEdInputContextReactor
**
**  **jma
**
*************************************/

ArxDbgEdInputContextReactor::~ArxDbgEdInputContextReactor()
{
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgEdInputContextReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::suppressDetailsDuringDrag
**
**  **jma
**
*************************************/

bool
ArxDbgEdInputContextReactor::suppressDetailsDuringDrag() const
{
	return m_suppressDetailsDuringDrag;
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::setSuppressDetailsDuringDrag
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::setSuppressDetailsDuringDrag(bool suppressThem)
{
	m_suppressDetailsDuringDrag = suppressThem;
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printDetails
**
**  **jma
**
*************************************/

bool
ArxDbgEdInputContextReactor::printDetails()
{
	if (m_suppressDetailsDuringDrag) {
		if (acedIsDragging()) {
				// print the first drag message, but suppress the rest until the
				// end of the drag sequence
			if (m_dragJustStarted) {
				m_dragJustStarted = false;
				return true;
			}
			return false;
		}
		else
			return m_showDetails;
	}
	else {
		return m_showDetails;
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetPoint
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetPoint(const AcGePoint3d* pointIn,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Point"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetPoint
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetPoint(Acad::PromptStatus returnStatus,
					const AcGePoint3d& pointOut,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Point"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("POINT"), ArxDbgUtils::ptToStr(pointOut, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetAngle
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetAngle(const AcGePoint3d* pointIn,
                   const TCHAR* promptString,
                   int initGetFlags,
                   const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Angle"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetAngle
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetAngle(Acad::PromptStatus returnStatus,
					double& angle,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Angle"));

	if (m_showDetails) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ANGLE"), ArxDbgUtils::angleToStr(angle, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetDistance
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetDistance(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Distance"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetDistance
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetDistance(Acad::PromptStatus returnStatus,
                    double& distance,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Distance"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("DISTANCE"), ArxDbgUtils::doubleToStr(distance, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetOrientation
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetOrientation(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int   initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Orientation"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetOrientation
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetOrientation(Acad::PromptStatus returnStatus,
                    double& angle,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End GetOrientation"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ANGLE"), ArxDbgUtils::angleToStr(angle, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetCorner
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetCorner(const AcGePoint3d* firstCorner,
                    const TCHAR* promptString,
                    int   initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Corner"));

	if (printDetails()) {
		printFirstCorner(firstCorner);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetCorner
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetCorner(Acad::PromptStatus returnStatus,
					AcGePoint3d& secondCorner,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Corner"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("SECOND CORNER"), ArxDbgUtils::ptToStr(secondCorner, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetScaleFactor
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetScaleFactor(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Scale Factor"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetScaleFactor
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetScaleFactor(Acad::PromptStatus returnStatus,
                    double& distance,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Scale Factor"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("SCALE FACTOR"), ArxDbgUtils::doubleToStr(distance, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetString
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetString(const TCHAR* promptString, int initGetFlags)
{
	printReactorMessage(_T("Begin Get String"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetString
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetString(Acad::PromptStatus returnStatus, TCHAR* pString)
{
	printReactorMessage(_T("End Get String"));

	if (printDetails()) {
		printReturnStatus(returnStatus);
		printValue(_T("STRING"), pString);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetKeyword
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetKeyword(const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Keyword"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetKeyword
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetKeyword(Acad::PromptStatus returnStatus, const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Keyword"));

	if (printDetails()) {
		printReturnStatus(returnStatus);
		printValue(_T("KEYWORD"), pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetInteger
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetInteger(const int* dfault,
					const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Integer"));

	if (printDetails()) {
		printDefaultInt(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetInteger
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetInteger(Acad::PromptStatus returnStatus,
					int& retValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Integer"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("INTEGER"), ArxDbgUtils::intToStr(retValue, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetColor
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetColor(const int* dfault,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Color"));

	if (printDetails()) {
		printDefaultInt(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetColor
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetColor(Acad::PromptStatus returnStatus,
					int& retValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Color"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("COLOR"), ArxDbgUtils::colorToStr(retValue, str, true));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginGetReal
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginGetReal(const double* dfault,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Real"));

	if (printDetails()) {
		printDefaultReal(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endGetReal
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endGetReal(Acad::PromptStatus returnStatus,
					double& returnValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Real"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("REAL"), ArxDbgUtils::doubleToStr(returnValue, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginEntsel
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginEntsel(const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Entsel"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endEntsel
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endEntsel(Acad::PromptStatus returnStatus,
					AcDbObjectId& entPicked,
					AcGePoint3d& pickPoint,
					const TCHAR* pKeyword)
{
	printReactorMessage(_T("End Entsel"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ENTITY PICKED"), ArxDbgUtils::objToClassAndHandleStr(entPicked, str));
		printValue(_T("PICK POINT"), ArxDbgUtils::ptToStr(pickPoint, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginNentsel
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginNentsel(const TCHAR* promptString,
					Adesk::Boolean pickFlag,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Nentsel"));

	if (printDetails()) {
		CString str;
		printPrompt(promptString);
		printValue(_T("PICK FLAG"), ArxDbgUtils::booleanToStr(pickFlag, str));
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endNentsel
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endNentsel(Acad::PromptStatus returnStatus,
					AcDbObjectId entPicked,
					const AcGePoint3d&  pickPoint,
					const AcGeMatrix3d& xform,
					const resbuf* referenceStack,
					const TCHAR* pKeyword)
{
	printReactorMessage(_T("End Nentsel"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ENTITY PICKED"), ArxDbgUtils::objToClassAndHandleStr(entPicked, str));
		printValue(_T("PICK POINT"), ArxDbgUtils::ptToStr(pickPoint, str));
// TBD: need matrix and ref stack
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginSSGet
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginSSGet(const TCHAR*  pPrompt,
					int  initGetFlags,
					const TCHAR* pKeywords,
					const TCHAR* pSSControls, // str in ADS
					const AcArray<AcGePoint3d>& points,
					const resbuf* entMask)
{
	printReactorMessage(_T("Begin SSGet"));

	if (printDetails()) {
		CString str;
		printPrompt(pPrompt);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
		printValue(_T("SS CONTROLS"), pSSControls);
		printPoints(points);
		printResbufs(_T("ENT MASK"), entMask);
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endSSGet
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endSSGet(Acad::PromptStatus returnStatus,
					const AcArray<AcDbObjectId>& ss)
{
	printReactorMessage(_T("End SSGet"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);

		ArxDbgUiTdmObjects dbox(ss, acedGetAcadDwgView(), _T("SSGet Set"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginDragSequence
**
**  **jma
**
*************************************/
    
void
ArxDbgEdInputContextReactor::beginDragSequence(const TCHAR* promptString)
{
	m_dragJustStarted = true;

	printReactorMessage(_T("Begin Drag Sequence"));

	if (m_showDetails)
		printPrompt(promptString);
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endDragSequence
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endDragSequence(Acad::PromptStatus returnStatus,
                    AcGePoint3d& pickPoint, AcGeVector3d& vec)
{
	printReactorMessage(_T("End Drag Sequence"));

	if (m_showDetails) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("PICK POINT"), ArxDbgUtils::ptToStr(pickPoint, str));
		printValue(_T("VECTOR"), ArxDbgUtils::vectorToStr(vec, str));
	}
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::beginQuiescentState
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::beginQuiescentState()
{
	printReactorMessage(_T("Begin Quiescent State"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::endQuiescentState
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::endQuiescentState()
{
	printReactorMessage(_T("End Quiescent State"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printReactorMessage(LPCTSTR event) const
{
	if (m_suppressDetailsDuringDrag && acedIsDragging())
		;
	else
		acutPrintf(_T("\n\n%-15s : [%s] "), _T("[ED INPUT REACTOR]"), event);
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printPrompt
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printPrompt(const TCHAR* promptStr) const
{
	if (promptStr)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("PROMPT"), promptStr);
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printKeywords
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printKeywords(const TCHAR* keywords) const
{
	if (keywords)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("KEYWORDS"), keywords);
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printKeywordPicked
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printKeywordPicked(const TCHAR*& keywordPicked) const
{
	if (keywordPicked)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("KEYWORD PICKED"), keywordPicked);
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printInitGetFlags
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printInitGetFlags(int flags) const
{
	CString str;
	acutPrintf(_T("\n   %-20s: %s"), _T("INIT FLAGS"), ArxDbgUtils::initFlagsToStr(flags, str));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printReturnStatus
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printReturnStatus(Acad::PromptStatus returnStatus) const
{
	CString str;
	acutPrintf(_T("\n   %-20s: %s"), _T("RETURN STAT"), ArxDbgUtils::promptStatusToStr(returnStatus, str));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printValue
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printValue(LPCTSTR label, LPCTSTR value) const
{
	if (value)
		acutPrintf(_T("\n   %-20s: %s"), label, value);
	else
		acutPrintf(_T("\n   %-20s: %s"), label, _T("Null"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printPointIn
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printPointIn(const AcGePoint3d* pointIn) const
{
	CString str;
	if (pointIn != NULL)
		printValue(_T("POINT IN"), ArxDbgUtils::ptToStr(*pointIn, str));
	else
		printValue(_T("POINT IN"), _T("Null"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printFirstCorner
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printFirstCorner(const AcGePoint3d* pointIn) const
{
	CString str;
	if (pointIn != NULL)
		printValue(_T("FIRST CORNER"), ArxDbgUtils::ptToStr(*pointIn, str));
	else
		printValue(_T("FIRST CORNER"), _T("Null"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printDefaultInt
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printDefaultInt(const int* def) const
{
	CString str;
	if (def != NULL)
		printValue(_T("DEFAULT"), ArxDbgUtils::intToStr(*def, str));
	else
		printValue(_T("DEFAULT"), _T("Null"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printDefaultReal
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printDefaultReal(const double* def) const
{
	CString str;
	if (def != NULL)
		printValue(_T("DEFAULT"), ArxDbgUtils::doubleToStr(*def, str));
	else
		printValue(_T("DEFAULT"), _T("Null"));
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printResbufs
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printResbufs(LPCTSTR label, const resbuf* rb) const
{
	printValue(label, _T(""));

    CString dxfCodeStr, valueStr, tmpStr;
    const resbuf* tmp = rb;
    while (tmp) {
        dxfToStr(tmp, dxfCodeStr, valueStr);
        tmpStr.Format(_T("(%s . %s)"), dxfCodeStr, valueStr);
		printValue(_T(""), tmpStr);
        tmp = tmp->rbnext;
    }
}

/****************************************************************************
**
**  ArxDbgEdInputContextReactor::printPoints
**
**  **jma
**
*************************************/

void
ArxDbgEdInputContextReactor::printPoints(const AcGePoint3dArray& pts) const
{
	int len = pts.length();
	if (len == 0)
		return;

	printValue(_T("POINTS"), _T(""));
	
	CString str;
	for (int i=0; i<len; i++) {
		printValue(_T(""), ArxDbgUtils::ptToStr(pts[i], str));
    }
}










