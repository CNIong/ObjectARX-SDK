// (C) Copyright 2002-2008 by Autodesk, Inc. 
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

//////////////////////////////////////////////////////////////////////////
//----- acrxEntryPoint.h
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////
static AcDbObjectId MyCreateLayer(CString layerName, Adesk::UInt16 colorIndex);

//////////////////////////////////////////////////////////////////////////
#define szRDS _RXST("adsk")

//////////////////////////////////////////////////////////////////////////
//----- ObjectARX EntryPoint
class CQuickPropertiesApp : public AcRxArxApp 
{
public:
	CQuickPropertiesApp () : AcRxArxApp () 
  {
    acutPrintf(_T("\nLoaded QuickProperties Sample\n"));
  }

public:

  // body defined below
  virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt);
  virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt); 

  virtual void RegisterServerComponents () 
  {
    //----- Self-register COM server upon loading.
    if (FAILED(::DllRegisterServer ()))
      acutPrintf (_RXST("Failed to register asdkMyEntity COM server.\n")) ;
  }
public:

  // - adskQuickProperties.addEnt command (do not rename)
  static void adskQuickPropertiesaddEnt();
} ;

//////////////////////////////////////////////////////////////////////////
AcRx::AppRetCode CQuickPropertiesApp::On_kInitAppMsg (void *pkt)
{
  acutPrintf(_T("\nCommands are:\n"));
  acutPrintf(_T("\n addEnt - Creates an asdkMyEntity, Zooms to it, then PICKFIRST select it for editing with the Properties Palette"));
  acutPrintf(_T("\n"));

  // try to autoload the dbx, hopefully it's in the same folder
  TCHAR dllFilePath[_MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT];
  // get the path to where this dll is being loaded from
  GetModuleFileName(_hdllInstance, dllFilePath, _MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT);
  // now split the filepath into its individual components
  TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];	
  _tsplitpath_s (dllFilePath, drive, dir, fname, ext);
  // now try to load the dbx
  if (!acrxLoadModule(CString(drive)+CString(dir)+_T("adskQuickPropertiesDbx.dbx"), false))
    acutPrintf(_T("\nWarning - failed to load DBX for this sample, you must load it by hand..."));

  // You *must* call On_kInitAppMsg here
  AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg (pkt);

  // make the application unloadable
  acrxDynamicLinker->unlockApplication(pkt);

  return (retCode) ;
}

//////////////////////////////////////////////////////////////////////////
AcRx::AppRetCode CQuickPropertiesApp::On_kUnloadAppMsg (void *pkt) 
{
  // You *must* call On_kUnloadAppMsg here
  AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg (pkt);

  // TODO: Unload dependencies here
  acrxUnloadModule(_T("adskQuickPropertiesDbx.dbx"));

  return (retCode);
}

//////////////////////////////////////////////////////////////////////////
// Commands
void CQuickPropertiesApp::adskQuickPropertiesaddEnt()
{
  AcDbObjectId id;
  // get the zoom extents of the entity later
  AcDbExtents entityExtents;
  {
    // create a smart pointer object so I don't have to worry about closing
    AcDbObjectPointer<asdkMyEntity> myEntity;
    // create the asdkMyEntity
    myEntity.create();
    // now set up the data
    myEntity->setDatabaseDefaults();
    myEntity->setLayer(MyCreateLayer(CString(_T("MyLayer1")), AcCmEntityColor::kRed));
    myEntity->setStartPoint(AcGePoint3d(100, 200, 0));
    myEntity->setEndPoint(AcGePoint3d(200, 300, 0));

    // now add it to the current space
    AcDbBlockTableRecordPointer curSpace(curDoc()->database()->currentSpaceId(), AcDb::kForWrite);
    // if ok
    if (curSpace.openStatus() == Acad::eOk)
      curSpace->appendAcDbEntity(myEntity);  

    // save the object Id
    id = myEntity->objectId();
    // get the extents of the entity before it is closed
    myEntity->getGeomExtents(entityExtents);
    
  } // everything will be closed up by here

  // now zoom the entity extents
  acedCommand(RTSTR, _T("_.Zoom"), RT3DPOINT, asDblArray(entityExtents.minPoint()), 
                                   RT3DPOINT, asDblArray(entityExtents.maxPoint()), RTNONE);

  // finally select the object so we can see it's properties
  ads_name ss, ename;
  // convert to old ads name
  acdbGetAdsName(ename, id);
  // create a selection set for it
  acedSSAdd(ename, NULL, ss);
  // now select it with the pick first selection
  acedSSSetFirst(ss, NULL);
  // finally free the selection set
  acedSSFree(ss);

  struct resbuf rb;
  memset(&rb, 0, sizeof(rb));
  rb.restype = RTSHORT;
  rb.resval.rint = 1;
  // set the lineweight display on
  acedSetVar(_T("LWDISPLAY"), &rb);
}

//////////////////////////////////////////////////////////////////////////
static AcDbObjectId MyCreateLayer(CString layerName, Adesk::UInt16 colorIndex)
{
  AcDbLayerTableRecordPointer layer(layerName, curDoc()->database(), AcDb::kForRead);
  // if not ok
  if (layer.openStatus() != Acad::eOk)
  {
    // create it
    layer.create();
    // set properties for it
    AcCmColor color;
    color.setColorIndex(colorIndex);
    layer->setColor(color);
    // now add it
    AcDbLayerTablePointer layerTable (curDoc()->database()->layerTableId(), AcDb::kForWrite);
    // if ok
    if (layerTable.openStatus() == Acad::eOk)
      layerTable->add(layer);
  }

  return layer->objectId();
}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ARX_ENTRYPOINT(CQuickPropertiesApp)
//////////////////////////////////////////////////////////////////////////
// ACRX_CMD_MODAL|ACRX_CMD_REDRAW are used to be able to *set* the pickfirst in my command and so it will stay selected on completion of the command
ACED_ARXCOMMAND_ENTRY_AUTO(CQuickPropertiesApp, adskQuickProperties, addEnt, addEnt, ACRX_CMD_MODAL|ACRX_CMD_REDRAW, NULL)
