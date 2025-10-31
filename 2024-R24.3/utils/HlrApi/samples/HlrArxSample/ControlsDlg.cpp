//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "StdAfx.h"


#include "resource.h"
#include "ControlsDlg.h"

#include "../../Inc/Hlr.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog


CControlsDlg::CControlsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlsDlg)
	mBlock = FALSE;
	mCleanUp = FALSE;
	mEntity = FALSE;
	mHandlePoints = FALSE;
	mHideTangents = FALSE;
	mIsoLines = FALSE;
	mProcessAll = FALSE;
	mProgress = FALSE;
	mProject = FALSE;
	mReuse = FALSE;
	mShowAll = FALSE;
	mSubentity = FALSE;
	mUnite = FALSE;
	mHonorInternals = FALSE;
	mMeshSilhouettes = FALSE;
	//}}AFX_DATA_INIT
}


void CControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlsDlg)
	DDX_Control(pDX, IDC_EDIT, mEdit);
	DDX_Check(pDX, IDC_BLOCK, mBlock);
	DDX_Check(pDX, IDC_CLEANUP, mCleanUp);
	DDX_Check(pDX, IDC_ENTITY, mEntity);
	DDX_Check(pDX, IDC_HANDLEPOINTS, mHandlePoints);
	DDX_Check(pDX, IDC_HIDETANGENTS, mHideTangents);
	DDX_Check(pDX, IDC_ISOLINES, mIsoLines);
	DDX_Check(pDX, IDC_PROCESSALL, mProcessAll);
	DDX_Check(pDX, IDC_PROGRESS, mProgress);
	DDX_Check(pDX, IDC_PROJECT, mProject);
	DDX_Check(pDX, IDC_REUSE, mReuse);
	DDX_Check(pDX, IDC_SHOWALL, mShowAll);
	DDX_Check(pDX, IDC_SUBENTITY, mSubentity);
	DDX_Check(pDX, IDC_UNITE, mUnite);
	DDX_Check(pDX, IDC_HONORINTERNALS, mHonorInternals);
	DDX_Check(pDX, IDC_MESHSILHOUETTES, mMeshSilhouettes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlsDlg, CDialog)
	//{{AFX_MSG_MAP(CControlsDlg)
	ON_BN_CLICKED(IDC_BLOCK, OnBlock)
	ON_BN_CLICKED(IDC_ENTITY, OnEntity)
	ON_BN_CLICKED(IDC_PROCESSALL, OnProcessall)
	ON_BN_CLICKED(IDC_PROGRESS, OnProgress)
	ON_BN_CLICKED(IDC_PROJECT, OnProject)
	ON_BN_CLICKED(IDC_SHOWALL, OnShowall)
	ON_BN_CLICKED(IDC_UNITE, OnUnite)
	ON_BN_CLICKED(IDC_CLEANUP, OnCleanup)
	ON_BN_CLICKED(IDC_HANDLEPOINTS, OnHandlepoints)
	ON_BN_CLICKED(IDC_HIDETANGENTS, OnHidetangents)
	ON_BN_CLICKED(IDC_ISOLINES, OnIsolines)
	ON_BN_CLICKED(IDC_REUSE, OnReuse)
	ON_BN_CLICKED(IDC_SUBENTITY, OnSubentity)
	ON_BN_CLICKED(IDC_HONORINTERNALS, OnHonorinternals)
	ON_BN_CLICKED(IDC_MESHSILHOUETTES, OnMeshsilhouettes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg message handlers

BOOL CControlsDlg::OnInitDialog () {
	CDialog::OnInitDialog () ;
	
	// TODO: Add extra initialization here
	mBlock =(mnControls & kBlock) == kBlock ;
	mCleanUp =(mnControls & kCleanup) == kCleanup ;
	mEntity =(mnControls & kEntity) == kEntity ;
	mHandlePoints =(mnControls & kHandlePoints) == kHandlePoints ;
	mHideTangents =(mnControls & kHideTangents) == kHideTangents ;
	mIsoLines =(mnControls & kIsolines) == kIsolines ;
	mProcessAll =(mnControls & kProcessAll) == kProcessAll ;
	mProgress =(mnControls & kProgress) == kProgress ;
	mProject =(mnControls & kProject) == kProject  ;
	mReuse =(mnControls & kReuse) == kReuse ;
	mShowAll =(mnControls & kShowAll) == kShowAll ;
	mSubentity =(mnControls & kSubentity) == kSubentity ;
	mUnite =(mnControls & kUnite) == kUnite ;
	mHonorInternals =(mnControls & kHonorInternals) == kHonorInternals ;
	mMeshSilhouettes =(mnControls & kMeshSilhouettes ) == kMeshSilhouettes ;
	UpdateData (FALSE) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CControlsDlg::OnBlock () {
    	mEdit.SetWindowText (ACRX_T("Are the objectIds for the generating\r\nentities required, including those\r\nof the nested blocks")) ;
}

void CControlsDlg::OnEntity () {
	mEdit.SetWindowText (ACRX_T("Is it required to return the entity which\r\ncaused a particular curve to\r\nbe created?")) ;
}

void CControlsDlg::OnProcessall () {
	mEdit.SetWindowText (ACRX_T("Process all entities without looking\r\nat their layer state on which they lie on")) ;
}

void CControlsDlg::OnProgress () {
	mEdit.SetWindowText (ACRX_T("Should the progress bar be displayed\r\n (not yet supported)")) ;
}

void CControlsDlg::OnProject () {
	mEdit.SetWindowText (ACRX_T("Should the curves be projected to a plane?")) ;
}

void CControlsDlg::OnShowall () {
	mEdit.SetWindowText (ACRX_T("Should all curves be returned, or just\r\nvisible ones?")) ;
}

void CControlsDlg::OnUnite () {
	mEdit.SetWindowText (ACRX_T("Should the entities be united before hidden\r\nlines? Will be much slower, but more\r\naccurate for intersecting entities")) ;
}

void CControlsDlg::OnCleanup () {
	mEdit.SetWindowText (ACRX_T("Should stored data be cleaned after use?")) ;
}

void CControlsDlg::OnHandlepoints () {
	mEdit.SetWindowText (ACRX_T("Should we show single points\r\n(requires bit more processing)")) ;
}

void CControlsDlg::OnHidetangents () {
	mEdit.SetWindowText (ACRX_T("Should tangent edges be suppressed\r\n(not yet supported)")) ;
}

void CControlsDlg::OnIsolines () {
	mEdit.SetWindowText (ACRX_T("Should isolines be shown\r\n(same as would be seen in AutoCAD)")) ;
}

void CControlsDlg::OnReuse () {
	mEdit.SetWindowText (ACRX_T("Should the algorithm use the data which\r\nwere created previously?")) ;
}

void CControlsDlg::OnSubentity () {
	mEdit.SetWindowText (ACRX_T("Should the subenty information be returned\r\nfor solids?")) ;
}

void CControlsDlg::OnHonorinternals () {
	mEdit.SetWindowText (ACRX_T("Should we process internal edges' visibility?\r\n(i.e. AcDbPolyFaceMesh / ACIS internal common edge)")) ;
}

void CControlsDlg::OnMeshsilhouettes () {
	mEdit.SetWindowText (ACRX_T("Should we calculate silhouette curves on polyface meshes\r\n")) ;
}

void CControlsDlg::OnOK () {
	CDialog::OnOK () ;
	mnControls =
		    (mBlock ? kBlock : 0)
		  | (mCleanUp ? kCleanup : 0)
		  | (mEntity ? kEntity : 0)
		  | (mHandlePoints ? kHandlePoints : 0)
		  | (mHideTangents ? kHideTangents : 0)
		  | (mIsoLines ? kIsolines : 0)
		  | (mProcessAll ? kProcessAll : 0)
		  | (mProgress ? kProgress : 0)
		  | (mProject ? kProject : 0)
		  | (mReuse ? kReuse : 0)
		  | (mShowAll ? kShowAll : 0)
		  | (mSubentity ? kSubentity : 0)
		  | (mUnite ? kUnite : 0)
		  | (mHonorInternals ? kHonorInternals : 0)
		  | (mMeshSilhouettes ? kMeshSilhouettes : 0) ;
}
