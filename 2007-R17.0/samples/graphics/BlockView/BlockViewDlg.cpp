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
//

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
//#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

////////////////////////////////////////////////////////////////////////
// include the custom colour palettes
#include "ColorPalette.h"
#include "RgbModel.h"
#include "BlockViewDlg.h"
#include "resource.h"
#include ".\blockviewdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockViewDlg dialog

extern CAcExtensionModule BlockViewDLL;

CBlockViewDlg::CBlockViewDlg(CWnd *pParent /*=NULL*/)
: CAcUiDialog(CBlockViewDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CBlockViewDlg)
  //}}AFX_DATA_INIT
}


void CBlockViewDlg::DoDataExchange(CDataExchange *pDX)
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
  ON_COMMAND(ID_TOOLS_PRINT, OnFileOutput)
  ON_COMMAND(ID_FILE_ACGSCONFIG, OnFileAcGsConfig)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_COMMAND(ID_SHOWLINETYPES, OnShowlinetypes)
  ON_COMMAND(ID_SHOWSECTIONING, OnShowSectioning)
  ON_COMMAND(ID_RENDERERTYPE_KDEFAULT, OnRenderertypeKdefault)
  ON_COMMAND(ID_RENDERERTYPE_KSOFTWARE, OnRenderertypeKsoftware)
  ON_COMMAND(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY, OnRenderertypeKsoftwareNewViewsOnly)
  ON_COMMAND(ID_RENDERERTYPE_KFULLRENDER, OnRenderertypeKfullRender)
  ON_COMMAND(ID_RENDERERTYPE_KSELECTIONRENDER, OnRenderertypeKselectionRender)
  ON_COMMAND(ID_ZOOM_WINDOW, OnZoomWindow)
  ON_COMMAND(ID_ZOOM_EXTENTS, OnZoomExtents)
  ON_COMMAND(ID_SETTINGS_VISUALSTYLE, &CBlockViewDlg::OnSettingsVisualstyle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockViewDlg message handlers

static int currentViewSetting = 0;
BOOL CBlockViewDlg::OnInitDialog() 
{
  CAcUiDialog::OnInitDialog();
    
  if (!mPreviewCtrl.SubclassDlgItem(IDC_VIEW,this))
    return FALSE;

  // now initialise the drawing control with the current working database
  InitDrawingControl(acdbHostApplicationServices()->workingDatabase());

  // set to the default setting
  m_viewMode.SetCurSel(currentViewSetting);
  OnCbnSelchangeViewmode();

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

//***************************************************************************************
// get the view port information - see parameter list
bool GetActiveViewPortInfo (AcDbDatabase *pDb, ads_real &height, ads_real &width, AcGePoint3d &target, AcGeVector3d &viewDir, ads_real &viewTwist, bool getViewCenter)
{
  // if not ok
  if (pDb == NULL)
    return false;

  // get the current working database as a backup
  AcDbDatabase *workingDataBase = acdbHostApplicationServices()->workingDatabase();
  // now set the working database
  acdbHostApplicationServices()->setWorkingDatabase(pDb);

  // make sure the active view port is uptodate
  acedVports2VportTableRecords();

  // open the view port records
  AcDbViewportTable *pVTable = NULL;
  Acad::ErrorStatus es = pDb->getViewportTable (pVTable, AcDb::kForRead);
  // if we opened them ok
  if (es == Acad::eOk)
  {
    AcDbViewportTableRecord *pViewPortRec = NULL;
    es = pVTable->getAt (_T("*Active"), pViewPortRec, AcDb::kForRead);
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
        acedGetVar (_T("VIEWCTR"), &rb);
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

  // now restore the original working database
  acdbHostApplicationServices()->setWorkingDatabase(workingDataBase);

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
      // add to the dwg database, to the current space
      AcDbBlockTableRecordPointer curSpace(curDoc()->database()->currentSpaceId(), AcDb::kForWrite);
      // if ok, add it
      if (curSpace.openStatus() == Acad::eOk)
        curSpace->appendAcDbEntity(line);

      // add the newly created line to the AcGsView
      mPreviewCtrl.mpView->add (line, mPreviewCtrl.model());
      // close the line now we are finished with it
      line->close ();
      // update the gsView
      refreshView(mPreviewCtrl.mpView);
    }
  }
}

void CBlockViewDlg::OnAddtempentity() 
{
  // create a new line with random coords
  AcDbLine *line = new AcDbLine (AcGePoint3d (rand()/100,rand()/100,rand()/100), AcGePoint3d (rand()/100,rand()/100,rand()/100));
  // if we created it ok
  if (line != NULL)
  {
    // add the newly created line to the AcGsView
    mPreviewCtrl.mpView->add (line, mPreviewCtrl.model());
    // update the gsView
    refreshView(mPreviewCtrl.mpView);
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
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
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
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
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
Acad::ErrorStatus CBlockViewDlg::InitDrawingControl (AcDbDatabase *pDb, const TCHAR *space)
{
  // have we got a valid drawing
  if (pDb == NULL)
    return Acad::eNullBlockName;

  // save the passed drawing so that we can use it later in various controls such as zoom extents
  mCurrentDwg = pDb;

  AcDbBlockTableRecordPointer spaceRec(space, pDb, AcDb::kForRead);
  // if ok
  if (spaceRec.openStatus() == Acad::eOk)
  {
    // initialize the preview control
    mPreviewCtrl.init(BlockViewDLL.ModuleResourceInstance(),true);
    // set the view to the *Active* AutoCAD view
    SetViewTo(mPreviewCtrl.mpView, pDb, m_viewMatrix);
    // tell the view to display this space
    mPreviewCtrl.view()->add(spaceRec, mPreviewCtrl.model()); 
  }

  return spaceRec.openStatus();
}

//////////////////////////////////////////////////////////////////////////////
void CBlockViewDlg::OnCbnSelchangeViewmode()
{
  // get the current value of the combo box
  int viewMode = m_viewMode.GetCurSel();

  // find out what we are now set to
  currentViewSetting = m_viewMode.GetCurSel();
  // and set the view mode
  mPreviewCtrl.mpView->setMode((AcGsView::RenderMode)currentViewSetting);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

//////////////////////////////////////////////////////////////////////////////
// Open a drawing
void CBlockViewDlg::OnFileOpen()
{
  struct resbuf *result = NULL;
  int status = acedGetFileNavDialog( _T("Select Drawing File"), _T("*.dwg"), _T("DWG"), _T("BlockViewFileOpenDialog"), 0, &result);
  if (status == RTNORM)
  {
    // create a new database to read our drawing into
    AcDbDatabase *pDb = new AcDbDatabase (Adesk::kFalse);
    // read in the drawing
    Acad::ErrorStatus es = pDb->readDwgFile (result->resval.rstring);
    // if we didn't read it ok
    if (es != Acad::eOk)
    {
      AfxMessageBox(CString(_T("Sorry, failed to open \"")) + result->resval.rstring + _T("\""));
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

#include <dbrender.h>
//#include <atil.h>

#include "FileWriteDescriptor.h"
#include "RowProviderInterface.h"
#include "FileSpecifier.h"
#include "DataModelAttributes.h"
#include "DataModel.h"
#include "Image.h"

#include <JfifFormatCodec.h>
#include <PngFormatCodec.h>
#include <TiffFormatCodec.h>
#include <BmpFormatCodec.h>
#include <TiffCustomProperties.h>
#include <PngCustomProperties.h>
#include <FileReadDescriptor.h>

// include the libs
// for Atil
#pragma comment (lib, "AdImaging.lib")
#pragma comment (lib, "AdIntImgServices.lib")
// for AcDbMentalRayRenderSettings
#pragma comment (lib, "AcSceneOE.lib") //cph
//////////////////////////////////////////////////////////////////////////////
// output the AcGsView
void CBlockViewDlg::OnFileOutput()
{
  // get the filename to output
  struct resbuf *result = NULL;
  int status = acedGetFileNavDialog(_T("SnapShot"), NULL, _T("jpg;png;tif;bmp"), _T("BlockViewSnapshotBrowseDialog"), 1, &result);  
  if (status == RTNORM)
  {
    // extract the size of the Gs View control
    CWnd *gsViewWnd = CWnd::GetDlgItem(IDC_VIEW);
    CRect sizeRect;
    if (gsViewWnd != NULL)
      gsViewWnd->GetClientRect(&sizeRect);
    else
      AfxMessageBox(_T("Failed to get the GsView Control size, the image will be invalid"));

    // make the filename var more friendly
    ACHAR *pFileName = result->resval.rstring;
    // create the image and write to disk
    if (!CreateAtilImage(mPreviewCtrl.mpView, sizeRect.Width(), sizeRect.Height(), 32, 0, pFileName))
      AfxMessageBox(_T("Failed to create image..."));
  }
}

//////////////////////////////////////////////////////////////////////////
// creates an Atil image using AcGsView::getSnapShot()
bool CreateAtilImage(AcGsView *pView, 
                     int width, int height, 
                     int colorDepth, int paletteSize, 
                     ACHAR *pFileName,
                     bool renderToImage)
{
  bool done = false;

  AcGsDCRect screenRect(0,width,0, height);
  if (!renderToImage)
    // get the screen rect from the gsview
    pView->getViewport(screenRect);

  try
  {
    // we want colorDepth to be either 24 or 32
    if (colorDepth < 24)
      colorDepth = 24;
    if (colorDepth > 24)
      colorDepth = 32;

    // create rbgmodel 32 bit true color
    Atil::RgbModel rgbModel(colorDepth);
    Atil::ImagePixel initialColor(rgbModel.pixelType());
    // create the Atil image on the stack
    Atil::Image imgSource(Atil::Size(width, height), &rgbModel, initialColor);

    // check what output function we require
    if (renderToImage)
    {
      // setup the render settings object
      AcDbMentalRayRenderSettings mentalRayRenderer;
      // now render to image the gsview
      bool ok = pView->RenderToImage(&imgSource, &mentalRayRenderer, NULL, screenRect);
      // if not ok
      if (!ok)
        AfxMessageBox(_T("Failed to RenderToImage"));
    }
    else
    {
      // get a snapshot of the GsView
      pView->getSnapShot(&imgSource, screenRect.m_min);
    }

    // if ok
    if (imgSource.isValid())
    {
      Atil::RowProviderInterface *pPipe = imgSource.read(imgSource.size(), Atil::Offset(0,0),Atil::kLeftRightBottomUp);
      if(pPipe != NULL)
      {
        TCHAR drive[_MAX_DRIVE];
        TCHAR dir[_MAX_DIR];
        TCHAR fname[_MAX_FNAME];
        TCHAR ext[_MAX_EXT];	
        // find out what extension we have
        _tsplitpath_s(pFileName, drive, dir, fname, ext);

        Atil::ImageFormatCodec *pCodec = NULL;
        // create the codec depending on what the user chose

        if (CString(ext) == _T(".jpg"))
          pCodec = new JfifFormatCodec();
        else if (CString(ext) == _T(".png"))
          pCodec = new PngFormatCodec();
        else if (CString(ext) == _T(".tif"))
          pCodec = new TiffFormatCodec();
        else if (CString(ext) == _T(".bmp"))
          pCodec = new BmpFormatCodec();

        // if we have a new codec
        if (pCodec != NULL)
        {
          // and it is compatible
          if (Atil::FileWriteDescriptor::isCompatibleFormatCodec(pCodec, &(pPipe->dataModel()), pPipe->size())) 
          {
            // create a new file output object
            Atil::FileWriteDescriptor fileWriter(pCodec);
            Atil::FileSpecifier fs(Atil::StringBuffer((lstrlen(pFileName) + 1) * sizeof(TCHAR), 
                (const Atil::Byte *)pFileName, Atil::StringBuffer::kUTF_16), Atil::FileSpecifier::kFilePath);

            // if the file already exists
            // we better delete it because setFileSpecifier will fail otherwise
            _tremove(pFileName);

            if (fileWriter.setFileSpecifier(fs))
            {
              fileWriter.createImageFrame(pPipe->dataModel(), pPipe->size());

              // At any rate you want to fetch the property from the write file descriptor then alter it and set it in…
              Atil::FormatCodecPropertyInterface *pProp = fileWriter.getProperty(Atil::FormatCodecPropertyInterface::kCompression);
              if (pProp != NULL) 
              {
                if (CString(ext) == _T(".jpg")) 
                {
                  Atil::FormatCodecIntProperty *pComp = dynamic_cast<Atil::FormatCodecIntProperty*>(pProp);
                  if (pComp != NULL) 
                  { 
                    int min=0, max=0;
                    pComp->getPropertyLimits(min, max);
                    // set the quality to 90%
                    pComp->setValue((int)((double)max * .9));

                    // apply any changes we have made
                    fileWriter.setProperty(pComp);
                  }
                }                  
                else if (CString(ext) == _T(".png")) 
                {
                  PngCompression *pComp = dynamic_cast<PngCompression*>(pProp);
                  if (pComp != NULL) 
                  {
                    // Why not compress all we can? 
                    pComp->selectCompression(PngCompressionType::kHigh);

                    // apply any changes we have made
                    fileWriter.setProperty(pComp);
                  }
                }
                else if (CString(ext) == _T(".tif")) 
                {
                  // All image types can be compressed using kNone, kLZW, and kDeflate.
                  // If it is 8 bit (palette'd or gray scale) the kPackbits is available. 
                  // If it is 1 bit (bi-tonal) then the CCITT family of kCCITT_* compression of which the kCCITT_FAX4 is the best are available.
                  // If it is 24 bit (3 channel RGB) then kJPEG is available which will use JPEG DCT compression in the TIFF file. 
                  TiffCompression *pComp = dynamic_cast<TiffCompression*>(pProp);
                  if (pComp != NULL) 
                  {
                    // G4 is only valid for 1 bit images. 
                    if (pComp->selectCompression(TiffCompressionType::kCCITT_FAX4) == false) 
                    {
                      // So if that fails, resort to LZW now that it is patent free
                      if (pComp->selectCompression(TiffCompressionType::kLZW) == false) 
                      {
                        // If that fails (and is shouldn’t, be) then set none.
                        pComp->selectCompression(TiffCompressionType::kNone);
                      }
                    }
                    // apply any changes we have made
                    fileWriter.setProperty(pComp);
                  }
                }

                // clean up
                delete pProp; 
                pProp = NULL;
              }
            }

            // be sure that the format has all the information it needs to write the file. 
            // In ATIL every property is required to have a valid default value. 
            // So if a certain property is REQUIRED by the codec to save the file, then it is safe 
            // and proper to simply loop over all the possible properties, enquire if it is required 
            // and simply set it with it’s default value
            Atil::FormatCodecPropertySetIterator* pPropsIter = fileWriter.newPropertySetIterator();
            // if ok
            if (pPropsIter)
            {
              for (pPropsIter->start(); !pPropsIter->endOfList(); pPropsIter->step())
              {
                Atil::FormatCodecPropertyInterface* pProp = pPropsIter->openProperty();
                if (pProp->isRequired()) 
                {
                  fileWriter.setProperty(pProp);
                }
                pPropsIter->closeProperty();
              }
              delete pPropsIter;
            }

            // ok - ready to write it
            fileWriter.writeImageFrame(pPipe);
            done = true;
          }
        }
        delete pCodec;
      }
    }
  }
  catch ( Atil::ATILException e )
  {
    const Atil::StringBuffer *pStringMsg =e.getMessage();
  }

  return done;
}

//////////////////////////////////////////////////////////////////////////////
// display the gs config dialog
void CBlockViewDlg::OnFileAcGsConfig()
{
  const TCHAR *regEntry = NULL; 
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
        if (pConfig->configure (regPath, true))
        {
          // update the gsView
          refreshView(mPreviewCtrl.mpView);
        }
      }
    }
  }
}

void CBlockViewDlg::OnShowlinetypes()
{
  // toggle the setting
  mPreviewCtrl.mpModel->enableLinetypes(toggleCheckMenuItem(ID_SHOWLINETYPES));
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnShowSectioning()
{
  // toggle the setting
  mPreviewCtrl.mpModel->setEnableSectioning(toggleCheckMenuItem(ID_SHOWSECTIONING));
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

// util function to toggle the tick for a specific menu item
bool CBlockViewDlg::toggleCheckMenuItem(UINT resId)
{
  // redirect the MFC resource pointer to us
  CAcModuleResourceOverride res;
  // find out what the menu it now set to
  CMenu *menu = GetMenu();
  UINT menuState = menu->GetMenuState(resId, MF_BYCOMMAND);
  // now set the menu to the correct checking status
  menu->CheckMenuItem(resId, ((menuState & MF_CHECKED) ? MF_UNCHECKED:MF_CHECKED));
  // the new setting
  return(((menuState & MF_CHECKED) ? false:true));
}

void CBlockViewDlg::OnRenderertypeKdefault()
{
  setMenuCheck(ID_RENDERERTYPE_KDEFAULT);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARE);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY);
  setMenuUnCheck(ID_RENDERERTYPE_KFULLRENDER);
  setMenuUnCheck(ID_RENDERERTYPE_KSELECTIONRENDER);
  mPreviewCtrl.mpDevice->setDeviceRenderer(AcGsDevice::kDefault);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnRenderertypeKsoftware()
{
  setMenuUnCheck(ID_RENDERERTYPE_KDEFAULT);
  setMenuCheck(ID_RENDERERTYPE_KSOFTWARE);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY);
  setMenuUnCheck(ID_RENDERERTYPE_KFULLRENDER);
  setMenuUnCheck(ID_RENDERERTYPE_KSELECTIONRENDER);
  mPreviewCtrl.mpDevice->setDeviceRenderer(AcGsDevice::kSoftware);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnRenderertypeKsoftwareNewViewsOnly()
{
  setMenuUnCheck(ID_RENDERERTYPE_KDEFAULT);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARE);
  setMenuCheck(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY);
  setMenuUnCheck(ID_RENDERERTYPE_KFULLRENDER);
  setMenuUnCheck(ID_RENDERERTYPE_KSELECTIONRENDER);
  mPreviewCtrl.mpDevice->setDeviceRenderer(AcGsDevice::kSoftwareNewViewsOnly);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnRenderertypeKfullRender()
{
  setMenuUnCheck(ID_RENDERERTYPE_KDEFAULT);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARE);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY);
  setMenuCheck(ID_RENDERERTYPE_KFULLRENDER);
  setMenuUnCheck(ID_RENDERERTYPE_KSELECTIONRENDER);
  mPreviewCtrl.mpDevice->setDeviceRenderer(AcGsDevice::kFullRender);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnRenderertypeKselectionRender()
{
  setMenuUnCheck(ID_RENDERERTYPE_KDEFAULT);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARE);
  setMenuUnCheck(ID_RENDERERTYPE_KSOFTWARENEWVIEWSONLY);
  setMenuUnCheck(ID_RENDERERTYPE_KFULLRENDER);
  setMenuCheck(ID_RENDERERTYPE_KSELECTIONRENDER);
  mPreviewCtrl.mpDevice->setDeviceRenderer(AcGsDevice::kSelectionRender);
  // update the gsView
  refreshView(mPreviewCtrl.mpView);
}

// util functions for setting the tick for a specific menu item
void CBlockViewDlg::setMenuCheck(UINT resId, UINT nCheck)
{
  // redirect the MFC resource pointer to us
  CAcModuleResourceOverride res;
  // find out what the menu it now set to
  CMenu *menu = GetMenu();
  // now set the menu to the correct checking status
  menu->CheckMenuItem(resId, nCheck);
}
void CBlockViewDlg::setMenuUnCheck(UINT resId)
{
  setMenuCheck(resId, MF_UNCHECKED);
}
//////////////////////////////////////////////////////////////////////////
void CBlockViewDlg::OnZoomWindow()
{
  // seto to Zoom window
  mPreviewCtrl.mZooming = true;
}

void CBlockViewDlg::OnZoomExtents()
{
    AcDbExtents viewExtents(mCurrentDwg->extmin(), mCurrentDwg->extmax());
    viewExtents.transformBy (m_viewMatrix);

    mPreviewCtrl.mpView->zoomExtents(viewExtents.minPoint(),viewExtents.maxPoint());
    refreshView(mPreviewCtrl.mpView);
}

void CBlockViewDlg::OnSettingsVisualstyle()
{
  // hide the dialog while we list out what we have
  BeginEditorCommand();

  // switch to the text screen
  acedTextScr();

  Acad::ErrorStatus es = Acad::eNotHandled;
  // first print out what the visual style is set to
  AcDbObjectId visualStyleId = mPreviewCtrl.mpView->visualStyle();
  // if set
  if (visualStyleId != AcDbObjectId::kNull)
  {
    // get the owner dictionary entry, to find out the name of the visual style
    AcDbDictionaryPointer visualStyleDict(curDoc()->database()->visualStyleDictionaryId(), AcDb::kForRead);
    // if ok
    if (visualStyleDict.openStatus() == Acad::eOk)
    {
      ACHAR *name = NULL;
      visualStyleDict->nameAt(visualStyleId, name);
      acutPrintf(_T("\n\nCurrently set to: %s"), name);
    }
  }
  else
    acutPrintf(_T("\n\nCurrently not set.\n"));

  // display the visual styles available for selection
  acutPrintf(ACRX_T("\n\nVisual Styles available: \n\n"));
  int index;
  AcArray<const ACHAR *> visualStyleList;
  if (curDoc()->database()->getVisualStyleList(visualStyleList) == Acad::eOk) 
  {
    acutPrintf(ACRX_T("0: Sets no Visual Style\n"));
    for (index=0; index<visualStyleList.length(); ++index)
      acutPrintf(ACRX_T("%d: %s\n"), index+1, visualStyleList[index]);
  }

  bool quit = false;
  do 
  {
    acedInitGet(RSG_NONEG, NULL);
    int replyIndex = 1;
    // now ask which one he wants
    int res = acedGetInt(_T("Select option <1> : "), &replyIndex);
    // if ok
    if (res != RTCAN)
    {
      // check the index to make sure it is valid
      if (replyIndex > visualStyleList.length())
      {
        acutPrintf(_T("Please enter a value between 1 and %d..."), visualStyleList.length());
        continue;
      }

      // if reply == 0 then he wants to remove the visual style from the AcGsView
      if (replyIndex == 0)
      {
        // assign it to the acgsview
        mPreviewCtrl.mpView->setVisualStyle(AcDbObjectId::kNull);
        quit = true;
        continue;
      }

      // get the owner dictionary entry, to find out the name of the visual style
      AcDbDictionaryPointer visualStyleDict(curDoc()->database()->visualStyleDictionaryId(), AcDb::kForRead);
      // if ok
      if (visualStyleDict.openStatus() == Acad::eOk)
      {
        AcDbObjectId selectedVisualStyleId;
        // get the selected visual style id
        // The getVisualStyleList() returns the localized visual style names that should be displayed in the UI.  
        // However, the entries in the visual style dictionary are stored using the globalized names
        // we need to convert back to globalized before we can call getAt
        es = visualStyleDict->getAt(acdbXlateReservedString(visualStyleList[replyIndex-1], false), selectedVisualStyleId);
        // if ok
        if (es == Acad::eOk)
        {
          // assign it to the acgsview
          mPreviewCtrl.mpView->setVisualStyle(selectedVisualStyleId);
          quit = true;
        }
      }
    }
    else
      quit = true;

  }while (!quit);

  // ok, display the dialog again
  CompleteEditorCommand();

  // finally refresh the acgsview
  refreshView(mPreviewCtrl.mpView);
}

//////////////////////////////////////////////////////////////////////////
// set the passed AcGsView to the *Active* AutoCAD AcDbDatabase view
void SetViewTo(AcGsView *pView, AcDbDatabase *pDb, AcGeMatrix3d& viewMat)
{
  // we are going to set the view to the current view of the drawing
  // The overall approach is to calculate the extents of the database in the coordinate system of the view
  // Calculate the extents in WCS
  AcGePoint3d extMax = pDb->extmax();
  AcGePoint3d extMin = pDb->extmin();

  // get the view port information - see parameter list
  ads_real height = 0.0, width = 0.0, viewTwist = 0.0;
  AcGePoint3d targetView;
  AcGeVector3d viewDir;
  GetActiveViewPortInfo (pDb, height, width, targetView, viewDir, viewTwist, true);

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
  AcGePoint3d eye = boxCenter + viewDir;

  // upvector				
  pView->setView(eye, boxCenter, viewYDir, xMax, yMax);
  // update the gsView
  refreshView(pView);
}

//////////////////////////////////////////////////////////////////////////
// updates the gsView
void refreshView(AcGsView *pView)
{
  if (pView != NULL)
  {
    pView->invalidate();
    pView->update();
  }
}

