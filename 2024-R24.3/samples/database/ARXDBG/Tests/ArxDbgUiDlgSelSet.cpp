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

#include "ArxDbgUiDlgSelSet.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgUiTdmObjects.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::ArxDbgUiDlgSelSet
**
**  **jma
**
*************************************/

ArxDbgUiDlgSelSet::ArxDbgUiDlgSelSet(CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgSelSet::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgSelSet)
    m_puMainSelectTypeIndex = 0;		// default to User Select
	m_filterLockedLayers = FALSE;
	m_rejectNonCurrent = FALSE;
	m_rejectPaperSpaceViewport = FALSE;
	m_useKwordCallback = FALSE;
	m_useOtherCallback = FALSE;
	m_allowDuplicates = FALSE;
	m_allowSingleOnly = FALSE;
	m_useSelectPrompt = FALSE;
	m_useRemovePrompt = FALSE;
	m_useFilter = FALSE;
	m_doIsKindOfTest = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgSelSet)
	DDX_Control(pDX, ARXDBG_BN_SELECT_OBJS, m_selectButton);
	DDX_Control(pDX, ARXDBG_PU_CLASSTYPE, m_puClassType);
	DDX_Control(pDX, ARXDBG_PU_MAIN_SELECT_METHOD, m_puMainSelectType);
    DDX_CBIndex(pDX, ARXDBG_PU_MAIN_SELECT_METHOD, m_puMainSelectTypeIndex);
    DDX_CBIndex(pDX, ARXDBG_PU_CLASSTYPE, m_puClassTypeIndex);
    DDX_Check(pDX, ARXDBG_CB_FILTER_LOCKED, m_filterLockedLayers);
    DDX_Check(pDX, ARXDBG_CB_REJECT_NON_CURRENT, m_rejectNonCurrent);
    DDX_Check(pDX, ARXDBG_BN_REJECT_PSPACE_VPORT, m_rejectPaperSpaceViewport);
    DDX_Check(pDX, ARXDBG_CB_ALLOW_DUPS, m_allowDuplicates);
    DDX_Check(pDX, ARXDBG_CB_SINGLE_ONLY, m_allowSingleOnly);
    DDX_Check(pDX, ARXDBG_CB_KEYWORD_CALLBACK, m_useKwordCallback);
    DDX_Check(pDX, ARXDBG_CB_OTHER_CALLBACK, m_useOtherCallback);
    DDX_Check(pDX, ARXDBG_CB_USE_SELECT_PROMPT, m_useSelectPrompt);
    DDX_Check(pDX, ARXDBG_CB_USE_REMOVE_PROMPT, m_useRemovePrompt);
	DDX_Text(pDX, ARXDBG_EB_SELECT_PROMPT, m_selectPrompt);
	DDX_Text(pDX, ARXDBG_EB_REMOVE_PROMPT, m_removePrompt);
    DDX_Check(pDX, ARXDBG_CB_USE_FILTER, m_useFilter);
    DDX_Check(pDX, ARXDBG_CB_DO_ISKINDOF_TEST, m_doIsKindOfTest);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgSelSet message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgSelSet, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgSelSet)
    ON_BN_CLICKED(ARXDBG_BN_SELECT_OBJS, OnSelectObjects)
    ON_BN_CLICKED(ARXDBG_CB_USE_SELECT_PROMPT, OnPromptToggle)
    ON_BN_CLICKED(ARXDBG_CB_USE_REMOVE_PROMPT, OnPromptToggle)
    ON_BN_CLICKED(ARXDBG_CB_USE_FILTER, OnFilterToggle)
    ON_CBN_SELENDOK(ARXDBG_PU_MAIN_SELECT_METHOD, OnSelendokSelectType)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgSelSet message handlers

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgSelSet::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();

    m_selectButton.AutoLoad();

		// do initial disabling
	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_SELECT_PROMPT, m_useSelectPrompt);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_REMOVE_PROMPT, m_useRemovePrompt);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_PU_CLASSTYPE, m_useFilter);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_DO_ISKINDOF_TEST, m_useFilter);

	m_puClassType.ResetContent();

	AcDbVoidPtrArray allEntClasses;
	getClassesDerivedFrom(AcDbEntity::desc(), allEntClasses);

	int index;
	AcRxClass* rxClass;
	int len = allEntClasses.length();
	for (int i=0; i<len; i++) {
		rxClass = static_cast<AcRxClass*>(allEntClasses[i]);
	    index = m_puClassType.AddString(rxClass->name());
		m_puClassType.SetItemDataPtr(index, rxClass);
	}

		// make AcDbEntity be the default selected class type
	m_puClassType.SelectString(-1, AcDbEntity::desc()->name());

	m_puMainSelectType.SetCurSel(0);	// set to "User"
	OnSelendokSelectType();				// fake out an event to update enabled modes

	return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::OnPromptToggle
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::OnPromptToggle() 
{
	UpdateData(TRUE);

	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_SELECT_PROMPT, m_useSelectPrompt);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_REMOVE_PROMPT, m_useRemovePrompt);
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::OnFilterToggle
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::OnFilterToggle() 
{
	UpdateData(TRUE);

	ArxDbgUtils::enableDlgItem(this, ARXDBG_PU_CLASSTYPE, m_useFilter);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_DO_ISKINDOF_TEST, m_useFilter);
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::setFlagModes
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::setFlagModes(bool allowed) 
{
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_FILTER_LOCKED, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_REJECT_NON_CURRENT, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_REJECT_PSPACE_VPORT, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_ALLOW_DUPS, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_SINGLE_ONLY, allowed);
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::setKeywordModes
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::setKeywordModes(bool allowed) 
{
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_KEYWORD_CALLBACK, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_OTHER_CALLBACK, allowed);
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::setPromptModes
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::setPromptModes(bool allowed) 
{
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_USE_SELECT_PROMPT, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_USE_REMOVE_PROMPT, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_SELECT_PROMPT, (allowed && m_useSelectPrompt));
	ArxDbgUtils::enableDlgItem(this, ARXDBG_EB_REMOVE_PROMPT, (allowed && m_useRemovePrompt));
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::setFilterModes
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::setFilterModes(bool allowed) 
{
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_USE_FILTER, allowed);
	ArxDbgUtils::enableDlgItem(this, ARXDBG_PU_CLASSTYPE, (allowed && m_useFilter));
	ArxDbgUtils::enableDlgItem(this, ARXDBG_CB_DO_ISKINDOF_TEST, (allowed && m_useFilter));
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::OnSelendokSelectType
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::OnSelendokSelectType()
{
	int index = m_puMainSelectType.GetCurSel();
	if (index != CB_ERR) {
		if (index == 0) {			// User
			setFlagModes(true);
			setKeywordModes(true);
			setPromptModes(true);
			setFilterModes(true);
		}
		else if (index == 5) {		// Last
			setFlagModes(false);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(false);
		}
		else if (index == 6) {		// Point
			setFlagModes(true);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(true);
		}
		else {
			setFlagModes(false);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(true);
		}
	}
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::OnSelectObjects
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::OnSelectObjects() 
{
	UpdateData(TRUE);	// make DDX calls happen so we have current data

	BeginEditorCommand();

	AcGePoint3d pt1, pt2;
	AcGePoint3dArray pts;
	Acad::ErrorStatus es;

    ArxDbgSelSet::SelSetStatus stat = ArxDbgSelSet::kNone;
	ArxDbgSelSet ss;

	ss.setFilterLockedLayers(intToBool(m_filterLockedLayers));
	ss.setRejectNonCurrentSpace(intToBool(m_rejectNonCurrent));
	ss.setRejectPaperSpaceViewport(intToBool(m_rejectPaperSpaceViewport));
	ss.setAllowDuplicates(intToBool(m_allowDuplicates));
	ss.setAllowSingleOnly(intToBool(m_allowSingleOnly), true);

	if (m_useKwordCallback)
		ss.setKeywordCallback(_T("MYkeyword _ MYkeyword"), ArxDbgUiDlgSelSet::keywordCallback);

	if (m_useOtherCallback)
		ss.setOtherCallback(ArxDbgUiDlgSelSet::otherCallback);

	ArxDbgRbList filterRbList;		// this will be NULL by default unless filter is present
	if (m_useFilter)
		getFilter(filterRbList);

	if (m_puMainSelectTypeIndex == 0) {			// User
		if (!m_useSelectPrompt && !m_useRemovePrompt)
			stat = ss.userSelect(filterRbList.data());
		else {
				// obviously, this would be much easier in real usage scenarios
				// since we would already know the value of the prompts.
			CString tmpStr1, tmpStr2;
			if (m_useSelectPrompt && (m_selectPrompt.IsEmpty() == FALSE))
				tmpStr1.Format(_T("\n%s"), m_selectPrompt);

			if (m_useRemovePrompt && (m_removePrompt.IsEmpty() == FALSE))
				tmpStr2.Format(_T("\n%s"), m_removePrompt);

			stat = ss.userSelect(tmpStr1, tmpStr2, filterRbList.data());
		}
	}
	else if (m_puMainSelectTypeIndex == 1) {		// Implied
		stat = ss.impliedSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 2) {		// Crossing
		if (!getBoxPoints(pt1, pt2, true))
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.crossingSelect(pt1, pt2, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 3) {		// Crossing Poly
		es = ArxDbgUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.crossingPolygonSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 4) {		// Fence
		es = ArxDbgUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.fenceSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 5) {		// Last
		stat = ss.lastSelect();
	}
	else if (m_puMainSelectTypeIndex == 6) {		// Point
		ArxDbgUiPrPoint prPt(_T("Specify point"), NULL);
		if (prPt.go() != ArxDbgUiPrBase::kOk)
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.pointSelect(prPt.value(), filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 7) {		// Previous
		stat = ss.previousSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 8) {		// Window
		if (!getBoxPoints(pt1, pt2, false))
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.windowSelect(pt1, pt2, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 9) {		// Window Poly
		es = ArxDbgUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.windowPolygonSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 10) {		// Filter Only
		stat = ss.filterOnlySelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 11) {		// All
		stat = ss.allSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 12) {		// Box
		if (!getBoxPoints(pt1, pt2, false))
			stat = ArxDbgSelSet::kCanceled;
		else
			stat = ss.boxSelect(pt1, pt2, filterRbList.data());
	}
	else {
		ASSERT(0);
	}

	if (stat == ArxDbgSelSet::kSelected) {
		AcDbObjectIdArray objIds;
		ss.asArray(objIds);
		ArxDbgUiTdmObjects dbox(objIds, acedGetAcadDwgView(), _T("Selected Objects"));
		dbox.DoModal();
	}
	else if (stat == ArxDbgSelSet::kNone) {
		ArxDbgUtils::alertBox(_T("Nothing selected!"));
	}
	else if (stat == ArxDbgSelSet::kRejected) {
		acutPrintf(_T("\nRejected."));
	}
	else {
		acutPrintf(_T("\nCanceled."));
	}

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::getFilter
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::getFilter(ArxDbgRbList& rbList)
{
	if (m_useFilter == false)
		return;

	void* tmpPtr = m_puClassType.GetItemDataPtr(m_puClassTypeIndex);
	if (tmpPtr == NULL) {
		ASSERT(0);
		return;
	}

	AcRxClass* classType = static_cast<AcRxClass*>(tmpPtr);
	
	AcDbVoidPtrArray filterClasses;
	filterClasses.append(classType);	// add our class for sure

		// if doing isKindOf test
	if (m_doIsKindOfTest == TRUE)
		getClassesDerivedFrom(classType, filterClasses);

	resbuf* tmpRb;

	tmpRb = acutNewRb(-4);
	acutNewString(_T("<or"), tmpRb->resval.rstring);
	rbList.addTail(tmpRb);

	const TCHAR* dxfStr;
	int len = filterClasses.length();
	for (int i=0; i<len; i++) {
		dxfStr = static_cast<AcRxClass*>(filterClasses[i])->dxfName();
		if (dxfStr) {
			tmpRb = acutNewRb(0);
			acutNewString(dxfStr, tmpRb->resval.rstring);
			rbList.addTail(tmpRb);
		}
		//else {
			//ASSERT(0);    // can't assert because AcDbCurve has no DXF name
		//}
	}

	tmpRb = acutNewRb(-4);
	acutNewString(_T("or>"), tmpRb->resval.rstring);
	rbList.addTail(tmpRb);
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::getBoxPoints
**
**  **jma
**
*************************************/

bool
ArxDbgUiDlgSelSet::getBoxPoints(AcGePoint3d& pt1, AcGePoint3d& pt2, bool useDash)
{
	ArxDbgUiPrPoint prPt(_T("Specify first corner"), NULL);
	if (prPt.go() != ArxDbgUiPrBase::kOk)
		return false;

	ArxDbgUiPrCorner prCorner(_T("Specify other corner"), NULL, prPt.value());
	prCorner.setUseDashedLine(useDash);

	if (prCorner.go() != ArxDbgUiPrBase::kOk)
		return false;

	pt1 = prPt.value();
	pt2 = prCorner.value();

	return true;
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::keywordCallback
**
**  **jma
**
*************************************/

struct resbuf*
ArxDbgUiDlgSelSet::keywordCallback(const TCHAR* str)
{
	ASSERT(str != NULL);

    acutPrintf(_T("\nKEYWORD: %s"), str);

    return NULL;
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::otherCallback
**
**  **jma
**
*************************************/

struct resbuf*
ArxDbgUiDlgSelSet::otherCallback(const TCHAR* str)
{
	ASSERT(str != NULL);

    acutPrintf(_T("\nOTHER INPUT: %s"), str);

    return NULL;
}

/****************************************************************************
**
**  ArxDbgUiDlgSelSet::getClassesDerivedFrom
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgSelSet::getClassesDerivedFrom(AcRxClass* searchClassType, AcDbVoidPtrArray& derivedClasses)
{
    AcRxDictionaryIterator* iter;
    AcRxDictionary* classDict = acrxClassDictionary;
    if (classDict == NULL) {
        ASSERT(0);
        return;
    }

    iter = classDict->newIterator();
    if (iter != NULL) {
            // iterate over each item and get its info
        AcRxObject* classDictItem;
        AcRxClass* classObj;

        for (; !iter->done(); iter->next()) {
            classDictItem = iter->object();
            if ((classObj = AcRxClass::cast(classDictItem)) != NULL) {
                if (classObj->isDerivedFrom(static_cast<AcRxClass*>(searchClassType))) {
                    if (derivedClasses.contains(classObj) == false) {
                        derivedClasses.append(classObj);
                    }
                }
            }
            else {
                ASSERT(0);
            }
        }
        delete iter;
    }
    else {
        ASSERT(0);
    }
}
