//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
///////////////////////////////////////////////
// ObjectARX defined commands
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
//#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"
#include "BlockViewDlg.h"

//////////////////////////////////////////////////////////////////////////
// This is command 'BLOCKVIEW' or 'BVIEW'
void AsdkBlockView()
{
    //switch our resources to the foreground
    CAcModuleResourceOverride overr;
    //construct and display the preview dialog
    CBlockViewDlg dlg;
    dlg.DoModal();
}

// This is command 'CONFIGGS'
void AsdkConfigGS()
{
    const TCHAR* regEntry = NULL; 
    TCHAR regPath[2024];	
    
    // Get the current AutoCAD registry path 
    // e.g. Software\Autodesk\AutoCAD\R17.0\ACAD-301:409 
    regEntry = acrxProductKey();
    // this is the path we want	
    _stprintf_s (regPath, _T("%s\\3DGS Configuration\\GSHEIDI10"), regEntry); 
        
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
                pConfig->configure (regPath, true); 
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// This is command 'RenderOffScreen' or 'ROS'
// Create an off screen AcGsDevice which we can render too
void AsdkRenderOffScreen()
{
  // Obtain the current viewport's screen size.  This will be the rendered image size.
  AcDbObjectId curVportId = acedActiveViewportId();
  AcDbObjectPointer<AcDbViewportTableRecord> curVport (curVportId,AcDb::kForRead);
  int l,r,b,t;
  acgsGetViewportInfo(curVport->number(),l,b,r,t);
  int height = t - b - 1;
  int width = r - l - 1;

  // get the acgsManager
  AcGsManager *gsManager = acgsGetGsManager();
  // if ok
  if (gsManager)
  {
    // get the class factory for the gsview
    AcGsClassFactory *factory = gsManager->getGSClassFactory();
    // if ok
    if (factory)
    {
      // create a new off screen device
      AcGsDevice *offDevice = factory->createOffScreenDevice();
      // if ok
      if (offDevice)
      {
        // size it to what the user requires
        offDevice->onSize(width, height);

        // construct a simple view
        AcGsView *pView = factory->createView();

        // if ok
        if (pView)
        {
          // Note: AcGsView::setMode is deprecated, use AcGsView::setVisualStyle instead
          #pragma warning (push)
          #pragma warning (disable:4996)
          // set the gsview mode to kGouraudShaded
          pView->setMode(AcGsView::kGouraudShaded);
          #pragma warning (pop)

          // set the device rendered to software
          offDevice->setDeviceRenderer(AcGsDevice::kFullRender);
          // add the gs view to the device
          offDevice->add(pView);
          // force update calls to all gsviews
          offDevice->update();

          // as the function suggests, create AutoCAD Model
          AcGsModel *pModel = gsManager->createAutoCADModel();
          // if ok
          if (pModel)
          {
            AcDbBlockTableRecordPointer spaceRec(curDoc()->database()->currentSpaceId(), AcDb::kForRead);
            // if ok
            if (spaceRec.openStatus() == Acad::eOk)
            {
              // add the current space AcDbBlockTableRecord to the gsview
              pView->add(spaceRec, pModel);
              // make sure it is closed
              spaceRec.close();

              // TODO: here you can set the visual style required
              // record what the visual style was
              AcDbObjectId defVisualStyle = pModel->visualStyle();
              // now set it to something
              pModel->setVisualStyle(defVisualStyle);

              // set the AcGsView to have the same view target and postion as the *Active* AutoCAD view
              AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
              AcGeMatrix3d viewMat;
              SetViewTo(pView, pDb, viewMat);

              // A Zoom extents to fill the frame to the offscreen device
              AcDbExtents viewExtents(pDb->extmin(), pDb->extmax());
              viewExtents.transformBy (viewMat);
              
              pView->zoomExtents(viewExtents.minPoint(),viewExtents.maxPoint());
              pView->zoom(0.95f);
              
              refreshView(pView);
              
              // send -1.0 to avoid dynamic tessellation while interactivity is enabled, 
              // regardless of whether degradation is enabled or not
              pView->beginInteractivity(-1.0);

              // get the filename to output
              struct resbuf *result = NULL;
              int status = acedGetFileNavDialog(_T("SnapShot"), NULL, _T("jpg;png;tif;bmp"), _T("BlockViewSnapshotBrowseDialog"), 1, &result);  
              if (status == RTNORM)
              {
                // make the filename var more friendly
                ACHAR *pFileName = result->resval.rstring;
                // create the image and write to disk
                if (!CreateAtilImage(pView, width, height, 32, 0, pFileName, true))
                  AfxMessageBox(_T("Failed to create image..."));
              }
            }
          }

          // now do the various GS clean up ops
          pView->eraseAll();
          offDevice->erase(pView);
          factory->deleteView(pView);
          factory->deleteModel(pModel);
        }
      }

      // finally
      factory->deleteDevice(offDevice);
    }
  }
}