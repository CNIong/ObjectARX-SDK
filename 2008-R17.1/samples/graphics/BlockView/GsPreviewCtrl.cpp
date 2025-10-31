//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//
// GsPreviewCtrl.cpp : implementation file
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
//#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "stdarx.h"
#include "resource.h"
#include "GsPreviewCtrl.h"
#include "Ac64bitHelpers.h"


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
      // free all of our temporary entities
      freeTempEntities();

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


//////////////////////////////////////////////////////////////////////////
void CGsPreviewCtrl::init(HMODULE hRes, bool bCreateModel)
{
  //Load our special cursors
  mhPanCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_PAN));
  mhCrossCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_CROSS));
  mhOrbitCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_ORBIT));
  SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)NULL);
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
  // if zooming
  if (mZooming)
  {
    mMouseDown = true;
    mMouseMoving = false;    
  }
  else
  {
    SetFocus();
    //start orbit
    mbOrbiting = true;
    SetCapture();
    //set up the proper cursor
    SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)NULL);
    ::SetCursor(mhOrbitCursor);
  }

  //store the start point
  mStartPt = point;
}

void CGsPreviewCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if (mZooming && mMouseDown)
  {
    // end zoom
    mZooming = false;
    mMouseDown = false;
    mMouseMoving = false;

    // AcGsView Y coordinates origin is at the screen bottom
    RECT rect;
    GetClientRect(&rect);
    mpView->zoomWindow(AcGePoint2d(mStartPt.x,rect.bottom - mStartPt.y),AcGePoint2d(mEndPt.x,rect.bottom - mEndPt.y));

    mpView->invalidate();
    mpView->update();
  }
  else
  {
    //end orbit
    mbOrbiting = false;
    SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)mhCrossCursor);
    ReleaseCapture();
  }
}

void CGsPreviewCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
  //start pan
  mbPanning = true;
  SetCapture();
  //set up the proper cursor
  SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)NULL);
  ::SetCursor(mhPanCursor);
  //store the start point
  mStartPt = point;
}

void CGsPreviewCtrl::OnMButtonUp(UINT nFlags, CPoint point) 
{
  //end pan
  ReleaseCapture();
  mbPanning = false;
  SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)mhCrossCursor);
}

void CGsPreviewCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
  // is the GsView valid
  if (mpView)
  {
    if (mZooming)
    {
      // if left button is down
      if (mMouseDown)
      {
        if (mMouseMoving)
        {
          // erase the old rectangle
          RubberRectangle(mStartPt, mEndPt);
        }

        // draw the new rectangle
        RubberRectangle(mStartPt, point);
        mMouseMoving = true;
        // save the new point for next time
        mEndPt = point;
      }
    }
    else
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

}

#if _MSC_VER < 1400
UINT
#else
LRESULT
#endif
CGsPreviewCtrl::OnNcHitTest(CPoint point) 
{
  return HTCLIENT;
}


void CGsPreviewCtrl::OnSetFocus(CWnd* pOldWnd) 
{
  SetClassLongPtr(m_hWnd,GCLP_HCURSOR,(LONG_PTR)mhCrossCursor);

}

//////////////////////////////////////////////////////////////////////////
// draws XOR ink Rectangle
void CGsPreviewCtrl::RubberRectangle(CPoint startPt, CPoint endPt) 
{
  // get the device context for the client area
  CDC *cdc = this->GetDC();
  // if ok
  if (cdc != NULL)
  {
    HDC hdc = cdc->GetSafeHdc();
    // Create a black pen with a dotted style to draw the border of the rectangle.
    HPEN gdiPen = CreatePen(PS_DOT, 1, RGB(0,0,0));
    // Set the ROP cdrawint mode to XOR.
    SetROP2(hdc, R2_XORPEN);

    // Select the pen into the device context.
    HGDIOBJ oldPen = SelectObject(hdc, gdiPen);

    // Create a stock NULL_BRUSH brush and select it into the device
    // context so that the rectangle isn't filled.
    HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH) );

    // Now XOR the hollow rectangle on the Graphics object with
    // a dotted outline.
    Rectangle(hdc, startPt.x, startPt.y, endPt.x, endPt.y);

    // Put the old stuff back where it was.
    SelectObject(hdc, oldBrush); // no need to delete a stock object
    SelectObject(hdc, oldPen);
    DeleteObject(gdiPen);		// but we do need to delete the pen

    // Return the device context to Windows.
    this->ReleaseDC(cdc);
  }
}


//////////////////////////////////////////////////////////////////////////
// records a temp entity and returns the total number recorded internally
int CGsPreviewCtrl::addTempEntity(AcDbEntity *ent)
{
  // remember this entity
  mTempEnts.append(ent);
  return mTempEnts.length();
}
//////////////////////////////////////////////////////////////////////////
// frees the temporary memory, returns the total number freed
int CGsPreviewCtrl::freeTempEntities()
{
  int count = 0;
  int length = mTempEnts.length();
  // loop through and free the memory
  for (int i=0; i<length; ++i)
  {
    // if ok
    if (mTempEnts[i] != NULL)
    {
      // delete
      delete mTempEnts[i];
      ++count;
    }
  }

  mTempEnts.removeAll();

  return count;
}
