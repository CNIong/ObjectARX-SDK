//
// (C) Copyright 2002-2003 by Autodesk, Inc. 
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

//////////////////////////////////////////////////////////////////////////////
// include the custom colour palettes
#include "ColorPalette.h"
#include "BlockViewDlg.h"

Acad::ErrorStatus postToDwg (AcDbEntity *pEnt, AcDbDatabase *pDb = NULL, char *requiredSpace = ACDB_MODEL_SPACE);;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockViewDlg dialog

extern CAcExtensionModule BlockViewDLL;

CBlockViewDlg::CBlockViewDlg(CWnd* pParent /*=NULL*/)
: CAcUiDialog(CBlockViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlockViewDlg)
	//}}AFX_DATA_INIT
}


void CBlockViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlockViewDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_VIEWMODE, m_viewMode);
}


BEGIN_MESSAGE_MAP(CBlockViewDlg, CAcUiDialog)
//{{AFX_MSG_MAP(CBlockViewDlg)
	ON_BN_CLICKED(IDC_ADDENTITY, OnAddentity)
	ON_BN_CLICKED(IDC_ADDTEMPENTITY, OnAddtempentity)
	ON_BN_CLICKED(IDC_REMAPCOLORS, OnBnClickedRemapcolors)
	ON_BN_CLICKED(IDC_STANDARDCOLORS, OnBnClickedStandardcolors)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_VIEWMODE, OnCbnSelchangeViewmode)
	ON_COMMAND(ID_TOOLS_PRINT, OnToolsPrint)
	ON_COMMAND(ID_FILE_ACGSCONFIG, OnFileAcGsConfig)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockViewDlg message handlers

static int currentViewSetting = 0;
BOOL CBlockViewDlg::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	if (!mPreviewCtrl.SubclassDlgItem(IDC_VIEW,this))
		return FALSE;

	// then use the current editor drawing
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase(); 
	// now initialise the drawing control
	InitDrawingControl(pDb);

	// set to the default setting
	m_viewMode.SetCurSel(currentViewSetting);
	OnCbnSelchangeViewmode();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//***************************************************************************************
// get the view port information - see parameter list
bool GetActiveViewPortInfo (ads_real &height, ads_real &width, AcGePoint3d &target, AcGeVector3d &viewDir, ads_real &viewTwist, bool getViewCenter)
{
	// make sure the active view port is uptodate
	acedVports2VportTableRecords();
	
	// get the working db
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase(); 
	// if not ok
	if (pDb == NULL)
		return false;
	
	// open the view port records
	AcDbViewportTable *pVTable = NULL;
	Acad::ErrorStatus es = pDb->getViewportTable (pVTable, AcDb::kForRead);
	// if we opened them ok
	if (es == Acad::eOk)
	{
		AcDbViewportTableRecord *pViewPortRec = NULL;
		es = pVTable->getAt ("*Active", pViewPortRec, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			// get the height of the view
			height = pViewPortRec->height ();
			// get the width
			width = pViewPortRec->width ();
			// if the user wants the center of the viewport used
			if (getViewCenter == true)
			{
				struct resbuf rb;
				memset (&rb, 0, sizeof (struct resbuf));
				// get the system var VIEWCTR
				acedGetVar ("VIEWCTR", &rb);
				// set that as the target
				target = AcGePoint3d (rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			}
			// we want the viewports camera target setting
			else
			{
				// get the target of the view
				target = pViewPortRec->target ();
			}		

			// get the view direction
			viewDir = pViewPortRec->viewDirection ();
			// get the view twist of the viewport
			viewTwist = pViewPortRec->viewTwist ();
		}
		// close after use
		pVTable->close ();
		pViewPortRec->close();			
	}	
	
	return (true);
}

void CBlockViewDlg::OnAddentity() 
{
	// lock the document
	AcAxDocLock lock;
	// if ok
	if (lock.lockStatus () == Acad::eOk)
	{
		// create a new line with random coords
		AcDbLine *line = new AcDbLine (AcGePoint3d (rand()/100,rand()/100,rand()/100), AcGePoint3d (rand()/100,rand()/100,rand()/100));
		// if we created it ok
		if (line != NULL)
		{
			// add to the dwg database
			postToDwg (line);

			// get the AcGsView from the CStatic control
			AcGsView *pView = mPreviewCtrl.view();	
			// add the newly created line to the AcGsView
			pView->add (line, mPreviewCtrl.model());
			// close the line now we are finished with it
			line->close ();
			// mark the AcGsView as invalid so that it knows it has to update
			pView->invalidate ();
			// update the view
			pView->update ();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// adds an entity to the required space... default is current dwg and ACDB_MODEL_SPACE.
Acad::ErrorStatus postToDwg (AcDbEntity *pEnt, AcDbDatabase *pDb, char *requiredSpace)
{
	// if the default database is to be used
	if (pDb == NULL)
		pDb = acdbHostApplicationServices()->workingDatabase();

	AcDbBlockTable *blockTable = NULL;
	// get a pointer to the block table 
	Acad::ErrorStatus es = pDb->getBlockTable (blockTable, AcDb::kForRead);
	// if it failed then abort
	if (es != Acad::eOk)
		return (es);
	
	AcDbBlockTableRecord *blockTableRecord = NULL;
	// now get a pointer to the model space entity records
	es = blockTable->getAt (requiredSpace, blockTableRecord, AcDb::kForWrite);
	// can close the block table itself as we don't need it anymore
	blockTable->close ();
	// if it failed then abort
	if (es != Acad::eOk)
		return (es);
	// otherwise put the entity into the model space
	es = blockTableRecord->appendAcDbEntity (pEnt);
	// now close it up
	blockTableRecord->close();

	return (es);
}

void CBlockViewDlg::OnAddtempentity() 
{
	// create a new line with random coords
	AcDbLine *line = new AcDbLine (AcGePoint3d (rand()/100,rand()/100,rand()/100), AcGePoint3d (rand()/100,rand()/100,rand()/100));
	// if we created it ok
	if (line != NULL)
	{
		// get the AcGsView from the CStatic control
		AcGsView *pView = mPreviewCtrl.view();	
		// add the newly created line to the AcGsView
		pView->add (line, mPreviewCtrl.model());
		// mark the AcGsView as invalid so that it knows it has to update
		pView->invalidate ();
		// update the view
		pView->update ();
	}
}

void CBlockViewDlg::OnBnClickedRemapcolors()
{
	// setup the backgroud colour to the same as Pspace
	//
	AcColorSettings colourSettings; 
	// get the AutoCAD current colour settings
	acedGetCurrentColors(&colourSettings); 	
	DWORD colorDW; 
	// get the background colour
	colorDW = colourSettings.dwGfxLayoutBkColor;
	// get the current device background colour	
	AcGsColor color = mPreviewCtrl.mpDevice->getBackgroundColor();
	// now update them to the new color
	color.m_red   = GetRValue(colorDW);
	color.m_green = GetGValue(colorDW);
	color.m_blue  = GetBValue(colorDW);
    color.m_filler = 255; // opaque background
	// finally lets set the new colour   
    mPreviewCtrl.mpDevice->setBackgroundColor(color);

	// now remap the colours, so that on a white background, white lines appear red
	mPreviewCtrl.mpDevice->setLogicalPalette (MyAcadColorPs, 256);
	// get the AcGsView from the CStatic control
	AcGsView *pView = mPreviewCtrl.view();	
	// mark the AcGsView as invalid so that it knows it has to update
	pView->invalidate ();
	// update the view
	pView->update ();
}

void CBlockViewDlg::OnBnClickedStandardcolors()
{
	// setup the backgroud colour to the same as Pspace
	//
	AcColorSettings colourSettings; 
	// get the AutoCAD current colour settings
	acedGetCurrentColors(&colourSettings); 	
	DWORD colorDW; 
	// get the background colour
	colorDW = colourSettings.dwGfxModelBkColor; 
	// get the current device background colour	
	AcGsColor color = mPreviewCtrl.mpDevice->getBackgroundColor();
	// now update them to the new color
	color.m_red   = GetRValue(colorDW);
	color.m_green = GetGValue(colorDW);
	color.m_blue  = GetBValue(colorDW);
    color.m_filler = 255; // opaque background
	// finally lets set the new colour   
	mPreviewCtrl.mpDevice->setBackgroundColor(color);
	
	// now remap the colours back to the default
	mPreviewCtrl.mpDevice->setLogicalPalette (MyAcadColorMs, 256);
	// get the AcGsView from the CStatic control
	AcGsView *pView = mPreviewCtrl.view();	
	// mark the AcGsView as invalid so that it knows it has to update
	pView->invalidate ();
	// update the view
	pView->update ();
}
						 
void CBlockViewDlg::OnSize(UINT nType, int cx, int cy) 
{
	//CAcUiDialog::OnSize(nType, cx, cy);

	CRect rect, clientRect;
	CWnd *wnd = NULL;
	// now update all the controls
	wnd = GetDlgItem (IDC_VIEW);
	// if ok
	if (wnd != NULL)
	{
		wnd->MoveWindow(7, 40, cx - 14, cy - 130);

		wnd = GetDlgItem (IDC_VIEWMODE);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(7, 40 + cy - 130 + 7, rect.Width(),rect.Height());

		wnd = GetDlgItem (IDC_REMAPCOLORS);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(150, 40 + cy - 130 + 7, rect.Width(),rect.Height());

		wnd = GetDlgItem (IDC_STANDARDCOLORS);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(250, 40 + cy - 130 + 7, rect.Width(),rect.Height());

		// now update the buttons
		wnd = GetDlgItem (IDC_ADDENTITY);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(7, cy - 30, rect.Width(),rect.Height());

		wnd = GetDlgItem (IDC_ADDTEMPENTITY);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(80, cy - 30, rect.Width(),rect.Height());

		wnd = GetDlgItem (IDOK);
		// get the original coords
		wnd->GetWindowRect (rect);
		// update the position and size
		wnd->MoveWindow(330, cy - 30, rect.Width(),rect.Height());
	}
}

//////////////////////////////////////////////////////////////////////////////
// takes a drawing and updates the GsView with it
Acad::ErrorStatus CBlockViewDlg::InitDrawingControl (AcDbDatabase *pDb, const char *space)
{
	// have we got a valid drawing
	if (pDb == NULL)
		return Acad::eNullBlockName;
	
	// get the blocktable
	AcDbBlockTable *pTab = NULL;
	Acad::ErrorStatus es = pDb->getBlockTable (pTab, AcDb::kForRead);
	// if ok
	if (es == Acad::eOk)
	{
		// get the space required
		AcDbBlockTableRecord *pRec = NULL;
		es = pTab->getAt (space, pRec, AcDb::kForRead);
		// if ok
		if (es == Acad::eOk)
		{
			pTab->close();
			
			// initialize the preview control
			mPreviewCtrl.init(BlockViewDLL.ModuleResourceInstance(),true);
			
			// we are going to set the view to the current view of the drawing
			// The overall approach is to calculate the extents of the database in the coordinate system of the view
			// Calculate the extents in WCS
			AcGePoint3d extMax = pDb->extmax();
			AcGePoint3d extMin = pDb->extmin();

			// get the view port information - see parameter list
			ads_real height = 0.0, width = 0.0, viewTwist = 0.0;
			AcGePoint3d targetView;
			AcGeVector3d viewDir;
			GetActiveViewPortInfo (height, width, targetView, viewDir, viewTwist, true);

			// we are only interested in the directions of the view, not the sizes, so we normalise. 
			viewDir = viewDir.normal();

			//**********************************************
			// Our view coordinate space consists of z direction 
			// get a perp vector off the z direction
			// Make sure its normalised
			AcGeVector3d viewXDir = viewDir.perpVector ().normal();
			// correct the x angle by applying the twist
			viewXDir = viewXDir.rotateBy (viewTwist, -viewDir);
			// now we can work out y, this is of course perp to the x and z directions. No need to normalise this, 
			// as we know that x and z are of unit length, and perpendicular, so their cross product must be on unit length
			AcGeVector3d viewYDir = viewDir.crossProduct (viewXDir);

			// find a nice point around which to transform the view. We'll use the same point as the center of the view.
			AcGePoint3d boxCenter = extMin + 0.5 * ( extMax - extMin );

			//**********************************************
			// create a transform from WCS to View space
			// this represents the transformation from WCS to the view space. (Actually not quite since 
			// we are keeping the fixed point as the center of the box for convenience )
			AcGeMatrix3d viewMat;
			viewMat = AcGeMatrix3d::alignCoordSys (boxCenter, AcGeVector3d::kXAxis, AcGeVector3d::kYAxis, AcGeVector3d::kZAxis,  
				boxCenter, viewXDir, viewYDir, viewDir).inverse();

			AcDbExtents wcsExtents(extMin, extMax);
			// now we have the view Extents
			AcDbExtents viewExtents = wcsExtents;
			// transforms the extents in WCS->view space
			viewExtents.transformBy (viewMat);

			//**********************************************
			// get the extents of the AutoCAD view
			double xMax = fabs(viewExtents.maxPoint ().x - viewExtents.minPoint ().x);
			double yMax = fabs(viewExtents.maxPoint ().y - viewExtents.minPoint ().y);

			//**********************************************
			// setup the view
			AcGsView *pView = mPreviewCtrl.view();	
			AcGePoint3d eye = boxCenter + viewDir;

			// upvector				
			pView->setView(eye, boxCenter, viewYDir, xMax, yMax);

			pView->add(pRec, mPreviewCtrl.model()); 

			pRec->close();
		}
	}

	return es;
}

//////////////////////////////////////////////////////////////////////////////
void CBlockViewDlg::OnCbnSelchangeViewmode()
{
	// get the current value of the combo box
	int viewMode = m_viewMode.GetCurSel();

	// setup the view
	AcGsView *pView = mPreviewCtrl.view();	
	// find out what we are now set to
	currentViewSetting = m_viewMode.GetCurSel();
	// and set the view mode
	pView->setMode((AcGsView::RenderMode)currentViewSetting);
	// mark the AcGsView as invalid so that it knows it has to update
	pView->invalidate ();
	// update the view
	pView->update ();
}

//////////////////////////////////////////////////////////////////////////////
// Open a drawing
void CBlockViewDlg::OnFileOpen()
{
	struct resbuf *result = NULL;
	int status = acedGetFileNavDialog( "Select Drawing File", "*.dwg", "DWG", "BlockViewFileOpenDialog", 0, &result);
	if (status == RTNORM)
	{
		// create a new database to read our drawing into
		AcDbDatabase *pDb = new AcDbDatabase (Adesk::kFalse);
		// read in the drawing
		Acad::ErrorStatus es = pDb->readDwgFile (result->resval.rstring);
		// if we didn't read it ok
		if (es != Acad::eOk)
		{
			AfxMessageBox(CString("Sorry, failed to open \"") + result->resval.rstring + "\"");
			// then use the current editor drawing
			pDb = acdbHostApplicationServices()->workingDatabase(); 
		}

		// clear the GsView completely, lets have a fresh start
		AcGsView *pView = mPreviewCtrl.view();	
		pView->eraseAll();

		// now initialise the drawing control
		InitDrawingControl(pDb);

		acutRelRb( result );
	}
}

//#include "ie.h"

//////////////////////////////////////////////////////////////////////////////
// output the AcGsView
void CBlockViewDlg::OnToolsPrint()
{
	AfxMessageBox ( "To enable this feature, please follow the instructions in the source code, inside CBlockViewDlg::OnToolsPrint()." );
	/*

	// This feature requires the use of the Image Engine SDK.
	// To enable, download and extract the SDK and then uncomment the below code, performing the following additional steps:
	// 1) Uncomment the #include for ie.h, and the code in this function, below.
	// 2) Add ie80.lib as an Additional Dependency in the Linker -> Input settings for the project.
	// 3) Add the Image Engine SDK include folder to the include path list for the project or for your development environment.
	// 4) Add the Image Engine SDK library folder to the library path list for the project or for your development environment.
	// 5) Comment the above AfxMessageBox() warning.

	struct resbuf *result = NULL;
	int status = acedGetFileNavDialog( "Create Snapshot File", "Snapshot.jpg", "JPG", "BlockViewSnapshotBrowseDialog", 1, &result);
	if (status == RTNORM)
	{
		CRect rect, clientRect;
		// get the View control
		CWnd *wnd = GetDlgItem (IDC_VIEW);
		// if ok
		if (wnd != NULL)
		{
			// get the original coords
			wnd->GetWindowRect (rect);
			// Get the snapshot of the image
			AcGsDCRect screenRect;
			// setup the view
			AcGsView *pView = mPreviewCtrl.view();	
			// get the extents of the viewport in device coordinates (pixels)
			pView->getViewport (screenRect);
			// create a new IeImg, ready for getSnapShot to use
			IeImg imgSource (IeSize(rect.Width(), rect.Height()), IePixTyp::u8_4, csRgb);
			// get a snapshot of the current graphics state of the view
			pView->getSnapShot (&imgSource, screenRect.m_min);
			// Add the filter
			if (imgSource.isValid())
			{
				// read and initialise the Ief from the IeImg that we have already setup
				Ief *pPipe = imgSource.read (IeSize::full, IeOffset::origin, IeImg::flipVert);
				// Store it as a JPG file.
				IeFileDesc fdWrite (result->resval.rstring, "JFIF", IeFileDesc::openWrite);
				// is it ok
				if (fdWrite.isValid())
				{
					// if definitly ok, then lets write it out
					if (fdWrite.write(pPipe))
					{
						AfxMessageBox (CString ("Written snapshot to: \"") + result->resval.rstring + "\"" );
					}
				}
			}
		}	
		acutRelRb( result );
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////
// display the gs config dialog
void CBlockViewDlg::OnFileAcGsConfig()
{
	const char* regEntry = NULL; 
	char regPath[2024];	

	// Get the current AutoCAD registry path 
	// e.g. Software\Autodesk\AutoCAD\R16.1\ACAD-301:409 
	regEntry = acrxProductKey();
	// this is the path we want	
	sprintf (regPath, "%s\\3DGS Configuration\\GSHEIDI10", regEntry); 
	// get the GsManager from current MDI Client Window 
	AcGsManager *pGsMgr = acgsGetGsManager (NULL); 	
	// if we go the gs manager ok
	if (pGsMgr != NULL)		
	{ 
		// get the GsClass factory
		AcGsClassFactory *pClassFactory = pGsMgr->getGSClassFactory(); 	
		// if we got it ok
		if (pClassFactory != NULL) 
		{
			// now get the gs config class
			AcGsConfig *pConfig = pClassFactory->getConfig(); 
			// if we got this ok too
			if (pConfig != NULL)
			{
				// display the config dialog
				if (pConfig->configure (regPath, true))
				{
					// setup the view
					AcGsView *pView = mPreviewCtrl.view();	
					// mark the AcGsView as invalid so that it knows it has to update
					pView->invalidate ();
					// update the view
					pView->update ();
				}
			}
		}
	}
}

