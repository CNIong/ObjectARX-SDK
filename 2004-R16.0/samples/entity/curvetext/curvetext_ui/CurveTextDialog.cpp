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
#include "CurveTextDialog.h"
#include "utils.h"
#include "curvetextJig.h"
#include "..\CurveText_DB\curvetextIterator.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCurveTextDia dialog


CCurveTextDia::CCurveTextDia(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(CCurveTextDia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurveTextDia)
	m_size = 0.2;
	m_string = _T("");
	m_showCurve = TRUE;
	m_showText = TRUE;
	m_space = 1.0;
	m_fit = FALSE;
	m_style = _T("");
	m_position = -1;
	m_dynamic = FALSE;
	m_repeat = FALSE;
	m_reverse = FALSE;
	//}}AFX_DATA_INIT
//	fromInitDialog = false;
}


void CCurveTextDia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveTextDia)
	DDX_Control(pDX, IDC_END_RESET, m_resetPoint_button);
	DDX_Control(pDX, IDC_END_POINT, m_endPoint_Button);
	DDX_Control(pDX, IDC_START_POINT, m_startPoint_button);
	DDX_Control(pDX, IDC_ABOVE, m_position_button);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_edit_size);
	DDX_Control(pDX, IDC_CHECK_FIT, m_Fit_Button);
	DDX_Control(pDX, IDC_EDIT_STRING, m_editString);
	DDX_Control(pDX, IDC_CHECK_REVERSE, m_reverse_button);
	DDX_Control(pDX, IDC_CHECK_REPEATTEXT, m_repeat_button);
	DDX_Control(pDX, IDC_CHECK_SHOWTEXT, m_showText_button);
	DDX_Control(pDX, IDC_CHECK_SHOW, m_show_button);
	DDX_Control(pDX, IDC_EDIT_SPACE, m_editSpace);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_combo);
	DDX_Check(pDX, IDC_CHECK_SHOW, m_showCurve);
	DDX_Check(pDX, IDC_CHECK_SHOWTEXT, m_showText);
	DDX_Check(pDX, IDC_CHECK_FIT, m_fit);
	DDX_CBString(pDX, IDC_COMBO_STYLE, m_style);
	DDX_Radio(pDX, IDC_ABOVE, m_position);
	DDX_Check(pDX, IDC_CHECK_DYNAMIC, m_dynamic);
	DDX_Check(pDX, IDC_CHECK_REPEATTEXT, m_repeat);
	DDX_Check(pDX, IDC_CHECK_REVERSE, m_reverse);
	//}}AFX_DATA_MAP
	CString value;
	m_edit_size.GetWindowText(value);
	if(value != "*Varies*")
		DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	m_editString.GetWindowText(value);
	if(value != "*Varies*")
		DDX_Text(pDX, IDC_EDIT_STRING, m_string);
	DDV_MaxChars(pDX, m_string, 256);
	m_editSpace.GetWindowText(value);
	if(value != "*Varies*")
		DDX_Text(pDX, IDC_EDIT_SPACE, m_space);

}


BEGIN_MESSAGE_MAP(CCurveTextDia, CDialog)
	//{{AFX_MSG_MAP(CCurveTextDia)
	ON_BN_CLICKED(IDC_START_POINT, OnStartPoint)
	ON_BN_CLICKED(IDC_END_POINT, OnEndPoint)
	ON_BN_CLICKED(IDC_END_RESET, OnResetPoint)
	ON_BN_CLICKED(IDC_CHECK_FIT, OnCheckFit)
	ON_BN_CLICKED(IDC_ABOVE, OnAbove)
	ON_BN_CLICKED(IDC_BELOW, OnBelow)
	ON_BN_CLICKED(IDC_CHECK_SHOW, OnCheckShow)
	ON_BN_CLICKED(IDC_CHECK_SHOWTEXT, OnCheckShowtext)
	ON_BN_CLICKED(IDC_MIDDLE, OnMiddle)
	ON_EN_CHANGE(IDC_EDIT_SIZE, OnChangeEditSize)
	ON_EN_CHANGE(IDC_EDIT_STRING, OnChangeEditString)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnSelchangeComboStyle)
	ON_BN_CLICKED(IDC_CHECK_DYNAMIC, OnCheckDynamic)
	ON_EN_CHANGE(IDC_EDIT_SPACE, OnChangeEditSpace)
	ON_BN_CLICKED(IDC_CHECK_REPEATTEXT, OnCheckRepeattext)
	ON_BN_CLICKED(IDC_CHECK_REVERSE, OnCheckReverse)
	ON_EN_KILLFOCUS(IDC_EDIT_SIZE, OnKillfocusEditSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCurveTextDia message handlers

void CCurveTextDia::OnStartPoint() 
{
	setPoint(TRUE);
}

void CCurveTextDia::OnEndPoint() 
{
	setPoint(FALSE);
}

void CCurveTextDia::setPoint(bool isStartPoint)
{
	// Since we are setting the text position along the curve,
	// "clean" the current display by hiding the text.
	//
	BOOL isTextDisplayed = m_showText;
	if(isTextDisplayed)
	{
		OnCheckShowtext();
		refreshDisplay();
	}

	// Indicates an AutoCAD interactive command is starting
	//
	BeginEditorCommand();
	ShowWindow(SW_HIDE);

	AsdkCurveText *pCurveText = getCurveText(AcDb::kForWrite);
	assert(pCurveText);

	// execute the Jig which updates the object directly
	//
	CCurveTextJig *pJig = new CCurveTextJig(isStartPoint, pCurveText);
	pJig->doIt();
	delete pJig;

	CompleteEditorCommand();
	ShowWindow(SW_SHOW);
	// Restore the text if needed
	//
	if(isTextDisplayed)
	{
		OnCheckShowtext();
	}
	refreshDisplay();
}


BOOL CCurveTextDia::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();

	// Here we initialize our combo box with a list
	// of all the text styles currently available
	//
	AcDbTextStyleTable* pStyleTable;
	// get the text style table
	AOK(acdbHostApplicationServices()->workingDatabase()->getTextStyleTable(pStyleTable, AcDb::kForRead));

	AcDbTextStyleTableIterator* pIterator;
	AOK(pStyleTable->newIterator(pIterator));

	AcDbTextStyleTableRecord *pStyle;
	const char * name;
	// iterate through the text style table
	//
	for( ; !pIterator->done(); pIterator->step())
	{
		AOK(pIterator->getRecord(pStyle, AcDb::kForRead));

		// get the name of the style
		//
		AOK(pStyle->getName(name));

		///////////////////////////////////////////
		// Needed because of the iterator bug
		// if the linetype is not continuous
		//
		if(name == NULL)
			continue;
		// add it to the combo box
		//
		m_combo.AddString(name);
		AOK(pStyle->close());
	}
	delete pIterator;
	AOK(pStyleTable->close());
	
	// if no style has been defined
	// for the curve text entity, than it is "STANDARD"
	getTextStyleName(m_style, m_styleId);
	if(m_style.IsEmpty())
		m_style = "STANDARD";
	
	m_combo.SelectString( -1, m_style);

	m_editSpace.SetStyleMask( AC_ES_NUMERIC | AC_ES_NOBLANK	| AC_ES_NOZERO);
	m_edit_size.SetStyleMask( AC_ES_NUMERIC | AC_ES_NOBLANK	| AC_ES_NOZERO);


	if(m_fit)
		m_editSpace.EnableWindow(FALSE);
	else
		m_editSpace.EnableWindow();


	if(curveTextIdArray.length() > 1)
	{
		m_startPoint_button.EnableWindow(FALSE);
		m_endPoint_Button.EnableWindow(FALSE);
	
		if(global.isStringVarying)
		{
			m_editString.SetWindowText("*Varies*");
		}
		if(global.isStyleIdVarying)
		{
			m_combo.SetCurSel(-1);
		}
		if(global.isShowCurveVarying)
		{
			m_show_button.SetCheck(2);
		}
		if(global.isShowTextVarying)
		{
			m_showText_button.SetCheck(2);
		}
		if(global.isFitVarying)
		{
			m_Fit_Button.SetCheck(2);
		}
		if(global.isReverseVarying)
		{
			m_reverse_button.SetCheck(2);
		}
		if(global.isRepeatVarying)
		{
			m_repeat_button.SetCheck(2);
		}
		if(global.isSizeVarying)
		{
			m_edit_size.SetWindowText("*Varies*");
		}
		if(global.isSpaceVarying)
		{
			m_editSpace.SetWindowText("*Varies*");
		}
		if(global.isPositionVarying)
		{
			m_position_button.SetCheck(2);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCurveTextDia::OnResetPoint() 
{
	// reset values for the start and end points
	// to the begining and end of the curve
	m_startDist = m_length = 0.0;

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setStartDist(0.0);
		pCurveText->setLength(0.0);
	}

	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnCheckFit() 
{
	if(m_fit)
	{
		m_fit = FALSE;
		m_Fit_Button.SetCheck(0);
	}
	else
	{
		m_fit = TRUE;
		m_Fit_Button.SetCheck(1);
	}

	m_editSpace.EnableWindow(!m_fit);

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setFit((m_fit)? true : false);
	}

	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::updatePosition()
{
	UpdateData();
	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setPosition(m_position);
	}

	if(global.isDynamic)
		refreshDisplay();
}

AsdkCurveText *
CCurveTextDia::getCurveText(AcDb::OpenMode mode)
{
	return getCurveText(curveTextIdArray[0], mode);
}
	
AsdkCurveText *
CCurveTextDia::getCurveText(AcDbObjectId oId, AcDb::OpenMode mode)
{
	AsdkCurveText* pCt;
	pTrans->getObject((AcDbObject*&)pCt, oId, mode);
	return pCt;
}

void CCurveTextDia::OnAbove() 
{
	updatePosition();
}

void CCurveTextDia::OnBelow() 
{
	updatePosition();
}

void CCurveTextDia::OnMiddle() 
{
	updatePosition();
}

void CCurveTextDia::OnCheckShow() 
{
	if(m_showCurve)
	{
		// To prevent the curve and the text
		// to be hidden both. See OnCheckShowtext().
		//
		if(!m_showText)
			return;
		m_showCurve = false;
	}
	else
		m_showCurve = true;

	m_show_button.SetCheck(m_showCurve);

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->showCurve((m_showCurve) ? true : false);
	}

	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnCheckShowtext() 
{
	if(m_showText)
	{
		m_showText = false;
		// To prevent the curve and the text
		// to be hidden both. See OnCheckShow().
		//
		if(!m_showCurve)
		{
			m_showCurve = true;
			m_show_button.SetCheck(true);
		}
	}
	else
		m_showText = true;

	m_showText_button.SetCheck(m_showText);

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->showText((m_showText) ? true : false);
		pCurveText->showCurve((m_showCurve) ? true : false);
	}
	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnChangeEditSize() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	CString value;
	m_edit_size.GetWindowText(value);
	if(value == "*Varies*")
		return;
	if(value.IsEmpty())
		return;
	if(!m_edit_size.Validate())
		return;

	UpdateData();

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setSize(m_size);
	}
	if(global.isDynamic)
		refreshDisplay();
}


void CCurveTextDia::OnKillfocusEditSize() 
{
	// TODO: Add your control notification handler code here
	CString value;
	m_edit_size.GetWindowText(value);
	if(value == "*Varies*")
	{
		m_edit_size.SetModify(FALSE);
	}
}


void CCurveTextDia::OnChangeEditString() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.

	CString value;
	m_editString.GetWindowText(value);
	if(value == "*Varies*")
		return;

	UpdateData();
	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setString(m_string);
	}
	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnSelchangeComboStyle() 
{
	UpdateData();
	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setStyle(m_style);
	}
	m_styleId = pCurveText->getStyle();
	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnCheckDynamic() 
{
	if(m_dynamic)
	{
		m_dynamic = global.isDynamic = FALSE;
	}
	else
	{
		m_dynamic = global.isDynamic = TRUE;
		refreshDisplay();
	}
}

void CCurveTextDia::OnChangeEditSpace() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.

	CString value;
	m_editSpace.GetWindowText(value);
	if(value == "*Varies*")
		return;
	if(value.IsEmpty())
		return;
	if(!m_editSpace.Validate())
		return;

	UpdateData();

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setSpace(m_space);
	}
	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::copyGlobalState()
{
	
	m_string	=	global.string;

	if(global.size == 0.0)
		m_size	= getDefaultCharacterSize();
	else
		m_size	=	global.size;

	m_showCurve	=	global.showCurve;
	m_showText	=	global.showText;
	m_styleId	=	global.styleId;
	m_space		=	global.space;
	m_fit		=	global.fit;
	m_position	=	global.position;
	m_dynamic	=	global.isDynamic;
	m_repeat	=	global.repeat;
	m_length	=	global.length;
	m_startDist	=	global.startDist;
	m_reverse	=	global.reverse;
}

void CCurveTextDia::updateGlobalState()
{
	global.string		=	m_string;
	global.showCurve	=	m_showCurve? true : false;
	global.showText		=	m_showText? true : false;
	global.styleId		=	m_styleId;
	global.space		=	m_space;
	global.fit			=	m_fit? true : false;
	global.position		=	m_position;
	global.isDynamic	=	m_dynamic ? true : false;
	global.size			=	m_size;
	global.repeat		=	m_repeat? true : false;
	global.reverse		=	m_reverse? true : false;
	global.length		=	m_length;
	global.startDist	=	m_startDist;
}

void CCurveTextDia::OnCheckRepeattext() 
{
	if(m_repeat)
		m_repeat = false;
	else
		m_repeat = true;

	m_repeat_button.SetCheck(m_repeat);

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setRepeatText(m_repeat);
	}
	if(global.isDynamic)
		refreshDisplay();
}

void CCurveTextDia::OnCheckReverse() 
{
	if(m_reverse)
		m_reverse = false;
	else
		m_reverse = true;

	m_reverse_button.SetCheck(m_reverse);

	AsdkCurveText *pCurveText;
	for(long i=0; i<curveTextIdArray.length(); i++)
	{
		pCurveText = getCurveText(curveTextIdArray[i], AcDb::kForWrite);
		assert(pCurveText);
		pCurveText->setReverse(m_reverse);
	}
	if(global.isDynamic)
		refreshDisplay();
}

