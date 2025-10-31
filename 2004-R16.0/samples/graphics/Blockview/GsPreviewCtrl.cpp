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

// GsPreviewCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "stdarx.h"
#include "resource.h"
#include "GsPreviewCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGsPreviewCtrl

BEGIN_MESSAGE_MAP(CGsPreviewCtrl, CStatic)
//{{AFX_MSG_MAP(CGsPreviewCtrl)
ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_MOUSEWHEEL()
ON_WM_LBUTTONDOWN()
ON_WM_MBUTTONDOWN()
ON_WM_MBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_NCHITTEST()
ON_WM_SETFOCUS()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGsPreviewCtrl message handlers

void CGsPreviewCtrl::OnPaint() 
{
	CPaintDC dc(this); 
	//update the gs view
	mpView->invalidate(); 
	mpView->update();
}

// Erase view and delete model
void CGsPreviewCtrl::erasePreview()
{
	if (mpView)
		mpView->eraseAll();
	if (mpManager && mpModel) {  
		mpManager->destroyAutoCADModel (mpModel);
		mpModel = NULL;
	}
}

void CGsPreviewCtrl::setModel(AcGsModel* pModel)
{
	erasePreview();
	mpModel = pModel;
	mbModelCreated =false;
}

void CGsPreviewCtrl::clearAll()
{
	if (mpView)  
	{
		mpView->eraseAll();
	}
	if (mpDevice)    
	{
		bool b = mpDevice->erase(mpView);
		RXASSERT(b);
	}
	
	if (mpFactory)    
	{
		if (mpView)  
		{
			mpFactory->deleteView(mpView);
			mpView = NULL;
		}
		if (mpGhostModel) 
		{
			mpFactory->deleteModel(mpGhostModel);
			mpGhostModel = NULL;
		}
		mpFactory = NULL;
	}
	
	if (mpManager)    
	{
		if (mpModel) 
		{
			if (mbModelCreated)
				mpManager->destroyAutoCADModel(mpModel);
			mpModel = NULL;
		}
    
		if (mpDevice)    
		{
			mpManager->destroyAutoCADDevice(mpDevice);
			mpDevice = NULL;
		}
		mpManager = NULL;
	}    
}


void CGsPreviewCtrl::init(HMODULE hRes, bool bCreateModel)
{
	//Load our special cursors
	mhPanCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_PAN));
	mhCrossCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_CROSS));
	mhOrbitCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_ORBIT));
	::SetClassLong(m_hWnd,GCL_HCURSOR,NULL);
	//Instantiate view, a device and a model object
	CRect rect;
	if (!mpManager) 
	{
		// get the AcGsManager object for a specified AutoCAD MDI Client CView
		mpManager = acgsGetGsManager();
		RXASSERT(mpManager);
		// get the GS class factory
		mpFactory = mpManager->getGSClassFactory();
		RXASSERT(mpFactory);
		// create an AcGsDevice object. The window handle passed in to this 
		// function is the display surface onto which the graphics system draws
		//a device with standard autocad color palette
		mpDevice = mpManager->createAutoCADDevice(m_hWnd);
		RXASSERT(mpDevice);
		
		// get the size of the window that we are going to draw in
		GetClientRect( &rect);
		// make sure the gs device knows how big the window is
		mpDevice->onSize(rect.Width(), rect.Height());   
		// construct a simple view
		mpView = mpFactory->createView();
		RXASSERT(mpView);
		if (bCreateModel)
		{
			RXASSERT(mpModel==NULL);
			// create an AcGsModel object with the AcGsModel::kMain RenderType 
			// (which is a hint to the graphics system that the geometry in this 
			// model should be rasterized into its main frame buffer). This 
			// AcGsModel is created with get and release functions that will open and close AcDb objects.
			mpModel = mpManager->createAutoCADModel();
			RXASSERT(mpModel);
			mbModelCreated = true;
		}
		//another model without open/close for the orbit gadget
		mpGhostModel = mpFactory->createModel(AcGsModel::kDirect,0,0,0);
		mpView->add(&mOrbitGadget,mpGhostModel);
		mOrbitGadget.setGsView(mpView);
		mpDevice->add(mpView);
		
		// get the view port information - see parameter list
		ads_real height = 0.0, width = 0.0, viewTwist = 0.0;
		AcGePoint3d targetView;
		AcGeVector3d viewDir;
		GetActiveViewPortInfo (height, width, targetView, viewDir, viewTwist, true);
		
		//pDb->ucsxdir().crossProduct(pDb->ucsydir())
		  //pView->setView(position, target,
		mpView->setView(targetView + viewDir, targetView,
			AcGeVector3d(0.0, 1.0, 0.0),  // upvector
			1.0, 1.0);
			/*mpView->setView(AcGePoint3d(0.0, 0.0, 1.0),
			AcGePoint3d(0.0, 0.0,  0.0),
			AcGeVector3d(0.0, 1.0,  0.0),
		1.0, 1.0); */
	}
}


void CGsPreviewCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	if (mpDevice) {
		GetClientRect( &rect);
		mpDevice->onSize(rect.Width(), rect.Height());
	}
}

BOOL CGsPreviewCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (mpView)
	{
		if (zDelta<0)
			mpView->zoom(0.5);
		else
			mpView->zoom(1.5);
		Invalidate();
	}
	return TRUE;
}

void CGsPreviewCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	//start orbit
	mbOrbiting = true;
	SetCapture();
	//set up the proper cursor
	::SetClassLong(m_hWnd,GCL_HCURSOR,NULL);
	::SetCursor(mhOrbitCursor);
	//store the start point
	mStartPt = point;
}

void CGsPreviewCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//end orbit
	mbOrbiting = false;
	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);
	ReleaseCapture();
}

void CGsPreviewCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
	//start pan
	mbPanning = true;
	SetCapture();
	//set up the proper cursor
	::SetClassLong(m_hWnd,GCL_HCURSOR,NULL);
	::SetCursor(mhPanCursor);
	//store the start point
	mStartPt = point;
	
	
}

void CGsPreviewCtrl::OnMButtonUp(UINT nFlags, CPoint point) 
{
	//end pan
	ReleaseCapture();
	mbPanning = false;
	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);
}

void CGsPreviewCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (mpView)
	{
		if (mbPanning)
		{
			//transform the point from device coordinates to
			//world coordinates
			AcGeVector3d pan_vec(-(point.x-mStartPt.x),point.y-mStartPt.y,0);
			pan_vec.transformBy(mpView->viewingMatrix() * mpView->worldToDeviceMatrix().inverse());
			mpView->dolly(pan_vec);
			Invalidate();
			mStartPt = point;
		}
		if (mbOrbiting)
		{
			const double Half_Pi =  1.570796326795;
			
			AcGsDCRect view_rect;
			mpView->getViewport (view_rect);
			
			int nViewportX = (view_rect.m_max.x - view_rect.m_min.x) + 1;
			int nViewportY = (view_rect.m_max.y - view_rect.m_min.y) + 1;
			
			int centerX = (int)(nViewportX / 2.0f + view_rect.m_min.x);
			int centerY = (int)(nViewportY / 2.0f + view_rect.m_min.y); 
      
			const double radius  = min (nViewportX, nViewportY) * 0.4f;
			
			// compute two vectors from last and new cursor positions:
			
			AcGeVector3d last_vector ((mStartPt.x - centerX) / radius,
				-(mStartPt.y - centerY) / radius,
				0.0);
			
			if (last_vector.lengthSqrd () > 1.0)     // outside the radius
				last_vector.normalize  ();
			else
				last_vector.z = sqrt (1.0 - last_vector.x * last_vector.x - last_vector.y * last_vector.y);
			
			AcGeVector3d new_vector((point.x - centerX) / radius,
				-(point.y - centerY) / radius,
				0.0);
			
			if (new_vector.lengthSqrd () > 1.0)     // outside the radius
				new_vector.normalize  ();
			else
				new_vector.z = sqrt (1.0 - new_vector.x * new_vector.x - new_vector.y * new_vector.y);
			
			// determine angles for proper sequence of camera manipulations:
			
			AcGeVector3d    rotation_vector (last_vector);
			rotation_vector = rotation_vector.crossProduct (new_vector);  // rotation_vector = last_vector x new_vector
			
			AcGeVector3d    work_vector (rotation_vector);
			work_vector.z = 0.0f;                      // projection of rotation_vector onto xy plane
			
			double          roll_angle      = atan2 (work_vector.x, 
				work_vector.y);        // assuming that the camera's up vector is "up",
			// this computes the angle between the up vector 
			// and the work vector, which is the roll required
			// to make the up vector coincident with the rotation_vector
			
			double length = rotation_vector.length ();
			double orbit_y_angle = (length != 0.0) ? acos (rotation_vector.z / length) + Half_Pi : Half_Pi;                   // represents inverse cosine of the dot product of the
			if (length > 1.0f)                                              // rotation_vector and the up_vector divided by the
				length = 1.0f;                                              // magnitude of both vectors.  We add pi/2 because we 
			// are making the up-vector parallel to the the rotation
			double          rotation_angle  = asin (length);                // vector ... up-vector is perpin. to the eye-vector.
			
			// perform view manipulations
			
			mpView->roll( roll_angle);               // 1: roll camera to make up vector coincident with rotation vector
			mpView->orbit( 0.0f,  orbit_y_angle);     // 2: orbit along y to make up vector parallel with rotation vector
			mpView->orbit( rotation_angle, 0.0f);     // 3: orbit along x by rotation angle
			mpView->orbit( 0.0f, -orbit_y_angle);     // 4: orbit along y by the negation of 2
			mpView->roll(-roll_angle);               // 5: roll camera by the negation of 1
			Invalidate();
			mStartPt = point;
		}
	}
	
}

UINT CGsPreviewCtrl::OnNcHitTest(CPoint point) 
{
	return HTCLIENT;
}


void CGsPreviewCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);
	
}

