//////////////////////////////////////////////////////////////////////////
// (C) Copyright 2006-2007 by Autodesk, Inc. 
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
#include "dbannotationscale.h"
#include "dbAnnotativeObjectPE.h"
#include "dbObjectContextInterface.h"
#include "dbObjectContextCollection.h"
#include "dbObjectContextManager.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#define szRDS _RXST(_T("adsk"))

//////////////////////////////////////////////////////////////////////////
// util functions
static bool DisplayAttachedProtocols(AcDbEntity *ent, bool printIt=true);
// util function for editing Annotation properties
static bool EditAttachedProtocols(AcDbEntity *ent);
// function to print out the AcDbObjectContext data
static bool PrintObjectContext (AcDbObjectContext *objectContext);

//////////////////////////////////////////////////////////////////////////
//----- ObjectARX EntryPoint
class CAnnotationApp : public AcRxArxApp 
{
public:
	
  CAnnotationApp () : AcRxArxApp () 
  {
    acutPrintf(_T("\nLoaded Annotation Sample\n"));
  }

  // body defined below
	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt);
	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt); 

	virtual void RegisterServerComponents () 
  {
	}
public:

  // adskAnnotationScaling.listAnno command (do not rename)
  static void adskAnnotationScalinglistAnno();
  // adskAnnotationScaling.checkAnno command (do not rename)
  static void adskAnnotationScalingcheckAnno();
  // adskAnnotationScaling.addAnnoEnt command (do not rename)
  static void adskAnnotationScalingaddAnnoEnt();
};

//////////////////////////////////////////////////////////////////////////
AcRx::AppRetCode CAnnotationApp::On_kInitAppMsg (void *pkt)
{
  acutPrintf(_T("\nCommands are:\n"));
  acutPrintf(_T("\n  listAnno - lists the Annotation Scales context setups from current dwg"));
  acutPrintf(_T("\n  checkAnno - select an entity on screen to check its Annotation Scale settings"));
  acutPrintf(_T("\n  addAnnoEnt - create a Custom entity and set supported Scales to include 1:22\n\n"));

  // try to autoload the dbx, hopefully it's in the same folder
  TCHAR dllFilePath[_MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT];
  // get the path to where this dll is being loaded from
  GetModuleFileName(acrxGetApp()->GetModuleInstance(), dllFilePath, _MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT);
  // now split the filepath into its individual components
  TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];	
  _tsplitpath (dllFilePath, drive, dir, fname, ext);
  // now try to load the dbx
  if (!acrxLoadModule(CString(drive)+CString(dir)+_T("asdkAnnotationDBX.dbx"), false))
    acutPrintf(_T("\nWarning - failed to load DBX for this sample, you must load it by hand..."));

  // You *must* call On_kInitAppMsg here
  AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg (pkt) ;

  // make the application unloadable
  acrxDynamicLinker->unlockApplication(pkt);

  // TODO: Add your initialization code here
  
  return (retCode) ;
}

//////////////////////////////////////////////////////////////////////////
AcRx::AppRetCode CAnnotationApp::On_kUnloadAppMsg (void *pkt) 
{
  // TODO: Add your code here

  // You *must* call On_kUnloadAppMsg here
  AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg (pkt) ;

  // TODO: Unload dependencies here
  acrxUnloadModule(_T("asdkAnnotationDBX.dbx"));

  return (retCode) ;
}

//////////////////////////////////////////////////////////////////////////
// Commands
//////////////////////////////////////////////////////////////////////////
// adskAnnotationScaling.listAnno command (do not rename)
// Lists the Annotation Contexts inside a drawing
void CAnnotationApp::adskAnnotationScalinglistAnno()
{
  // get the current drawing
  AcDbDatabase *dwg = curDoc()->database();
  // next get the objectContextManager
  AcDbObjectContextManager *contextManager = dwg->objectContextManager();
  // if ok
  if (contextManager)
  {
    // now get the annotation scales collection context
    AcDbObjectContextCollection* const contextCollection = contextManager->contextCollection(ACDB_ANNOTATIONSCALES_COLLECTION);
    // if ok
    if (contextCollection) 
    {
      // get the current annotation scale
      AcDbAnnotationScale *annoScale = dwg->cannoscale();
      // now print it
      acutPrintf(_T("\n>>> Current Annotation Scale: Visible=%d, Annotitive Dwg=%d\n "), dwg->annoAllVisible(), dwg->annotativeDwg());
      PrintObjectContext(annoScale);
      acutPrintf(_T("\n\n<<<<<<"));

      // lets iterate through them, create a new iterator
      AcDbObjectContextCollectionIterator* pIter = contextCollection->newIterator();
      // now loop the items        
      for (pIter->start(); !pIter->done(); pIter->next()) 
      {
        AcDbObjectContext *objectContext = NULL;
        // get the context object for this iteration
        Acad::ErrorStatus es = pIter->getContext(objectContext);
        // if we have what we want
        PrintObjectContext(objectContext);
        // remember to delete because getContext allocates the memory
        delete objectContext;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// adskAnnotationScaling.checkAnno command (do not rename)
void CAnnotationApp::adskAnnotationScalingcheckAnno()
{
  ads_name  ename;
  ads_point pt;
  // pick an entity to check
  int res = acedEntSel (_T("\nPick an entity to check its Annotation settings : "), ename, pt);
  // if the user didn't cancel
  if (res == RTNORM)
  {
    AcDbObjectId objId;
    acdbGetObjectId(objId, ename);
    // open the entity for read
    AcDbObjectPointer<AcDbEntity>ent (objId, AcDb::kForRead);
    // if ok
    if (ent.openStatus() == Acad::eOk)
    {
      // print and find out what annotation protocols are attached
      bool noProtocols = DisplayAttachedProtocols(ent);
      // if no annotative PE's
      if (noProtocols)
        acutPrintf(_T("\nThe selected object is not annotative in any way"));
      else
      {
        // now print out the supported scales for this object
        
        // get the Object Context Protocol Extension Object, we know it's there because we wouldn't be in this else otherwise
        AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(ent, AcDbObjectContextInterface);

        // as usual, get the current drawing
        AcDbDatabase *dwg = curDoc()->database();
        // next get the objectContextManager
        AcDbObjectContextManager *contextManager = dwg->objectContextManager();
        // if ok
        if (contextManager)
        {
          // now get the annotation scales collection context
          AcDbObjectContextCollection* const contextCollection = contextManager->contextCollection(ACDB_ANNOTATIONSCALES_COLLECTION);
          // if ok
          if (contextCollection) 
          {
            // lets iterate through them, create a new iterator
            AcDbObjectContextCollectionIterator* pIter = contextCollection->newIterator();
            // now loop the items        
            for (pIter->start(); !pIter->done(); pIter->next()) 
            {
              AcDbObjectContext *objectContext = NULL;
              // get the context object for this iteration
              Acad::ErrorStatus es = pIter->getContext(objectContext);
              // check to see if our entity supports this context
              if (objectContextInterface->hasContext(ent, *objectContext))
              {
                // if we have what we want
                PrintObjectContext(objectContext);
              }
              // remember to delete because getContext allocates the memory
              delete objectContext;
            }
          }
        }
        // see if the user wants to modify the settings
        EditAttachedProtocols(ent);
      }
    }
  }
}

#include "..\AnnotationDBX\asdkMyAnnotativeObject.h"
//////////////////////////////////////////////////////////////////////////
// adds a custom entity (with annotation support) and sets up the supported Annotation scales for it
void CAnnotationApp::adskAnnotationScalingaddAnnoEnt()
{
  AcGePoint3d insPnt;
  // pick a point on screen for the object
  int res = acedGetPoint(NULL, _T("\nPick point for object : "), asDblArray(insPnt));
  // if ok
  if (res == RTNORM)
  {
    // create a new instance of my object, this is derived from AcDbText so that means the 
    // Annotation Context framework is already implemented for us
    AcDbObjectPointer<asdkMyAnnotativeObject> ent;
    ent.create();
    // set the properties for it
    ent->setDatabaseDefaults();
    ent->setPosition(insPnt);
    // set the AcDbText height, because we are derived from AcDbText
    // the Annotation framework is already in place
    ent->setHeight(1);
    ent->setTextString(_T("AcDbText Derived Annotative Text - Scales automatically"));
    // now set my own Text height, this will show how to utilise the Annotation
    // framework - see the worldDraw/viewportDraw of the custom entity
    ent->setMyTextHeight(1);
    ent->setMyTextString(_T("My Custom Object Text - code implemented to handle scaling Framework"));
    // now add to the current space, open it for write
    AcDbBlockTableRecordPointer curSpace(curDoc()->database()->currentSpaceId(), AcDb::kForWrite);
    // if ok
    if (curSpace.openStatus() == Acad::eOk)
      curSpace->appendAcDbEntity(ent);

    // now add the scales for this object
    // first, get the current drawing
    AcDbDatabase *dwg = curDoc()->database();
    // next get the objectContextManager
    AcDbObjectContextManager *contextManager = dwg->objectContextManager();
    // if ok
    if (contextManager)
    {
      // now get the Annotation Scaling context collection (named ACDB_ANNOTATIONSCALES_COLLECTION)
      AcDbObjectContextCollection* const contextCollection = contextManager->contextCollection(ACDB_ANNOTATIONSCALES_COLLECTION);
      // if ok
      if (contextCollection) 
      {
        // create a brand new scale context
        AcDbAnnotationScale annotationScale;
        annotationScale.setName(_T("MyScale 1:22"));
        annotationScale.setPaperUnits(1);
        annotationScale.setDrawingUnits(22);
        // now add to the drawing's context collection
        Acad::ErrorStatus es = contextCollection->addContext(&annotationScale);
      
        // now add to the entity - remember that we derived from AcDbText, which already has the 
        // annotative framework already setup        
        // so, extract the PEX for the entity
        AcDbAnnotativeObjectPE *annotationPE = ACRX_PE_PTR(ent, AcDbAnnotativeObjectPE);
        // if ok
        if (annotationPE)
          // set that it is annotative
          annotationPE->setAnnotative(ent, true);

        // now get the Object Context PEX
        AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(ent, AcDbObjectContextInterface);
        // if ok
        if (objectContextInterface) 
        {
          // add My scale context to the list of contexts
          es = objectContextInterface->addContext(ent, annotationScale);
          // now set the current Annotation scale to the one we want so it displays at 1:22
          dwg->setCannoscale(&annotationScale);
          // all done!
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// util function for displaying what Annotation Protocols are attached to an entity
static bool DisplayAttachedProtocols(AcDbEntity *ent, bool printIt)
{
  bool noProtocols = true;
  // try to extract the Annotation Protocol Extension Object
  AcDbAnnotativeObjectPE *annotationPE = ACRX_PE_PTR(ent, AcDbAnnotativeObjectPE);
  // if ok
  if (annotationPE)
  {
    if (printIt)
      acutPrintf(_T("\nObject has Annotation Scaling: Annotative=%s"), annotationPE->annotative(ent) ? _T("true"):_T("false"));
    noProtocols = false;
  }

  // try to extract the Paper Orienation Protocol Extension Object - should reside on Text and MText by default
  AcDbPaperOrientationPE *paperOrientationPE = ACRX_PE_PTR(ent, AcDbPaperOrientationPE);
  // if ok
  if (paperOrientationPE)
  {
    if (printIt)
      acutPrintf(_T("\nObject has Paper Orientation: PaperOrientation=%s"), paperOrientationPE->paperOrientation(ent) ? _T("true"):_T("false"));
    noProtocols = false;
  }

  // try to extract the Object Context Protocol Extension Object
  AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(ent, AcDbObjectContextInterface);
  // if ok
  if (objectContextInterface) 
  {
    if (printIt)
    {
      acutPrintf(_T("\nObject has an Object Context Interface..."));
      // if annotative is set
      if (annotationPE && annotationPE->annotative(ent))
      {
        // get the current annotation scale
        AcDbAnnotationScale *currentAnnoScale = curDoc()->database()->cannoscale();
        // check to see if our object supports this scale
        if (objectContextInterface->hasContext(ent, *currentAnnoScale))
        {
          // print out its data
          PrintObjectContext(currentAnnoScale);
        }
      }
      else
        acutPrintf(_T("\n...but Annotative not set..."));
    }
    noProtocols = false;
  }
  return noProtocols;
}

//////////////////////////////////////////////////////////////////////////
// util function for editing Annotation properties
bool EditAttachedProtocols(AcDbEntity *ent)
{
  Acad::ErrorStatus es = Acad::eOk;

  TCHAR reply[22];
  _tcscpy(reply, _T("Yes"));
  acedInitGet(NULL, _T("Yes No"));
  int res = acedGetKword(_T("\nModify Settings? <Yes> : "), reply);
  // if so
  if (res == RTNONE || reply[0] == _T('Y'))
  {
    ent->upgradeOpen();
    // try to extract the Annotation Protocol Extension Object
    AcDbAnnotativeObjectPE *annotationPE = ACRX_PE_PTR(ent, AcDbAnnotativeObjectPE);
    // if ok
    if (annotationPE)
    {
      // ask about annotative setting
      acedInitGet(NULL, _T("Yes No"));
      _tcscpy(reply, _T("Yes"));
      res = acedGetKword(_T("\nMake Annotative <Yes> : "), reply);
      // ok now set
      es = annotationPE->setAnnotative(ent, reply[0] == _T('Y') || res == RTNONE);

      // ask about force setting
      acedInitGet(NULL, _T("Yes No"));
      _tcscpy(reply, _T("Yes"));
      res = acedGetKword(_T("\nMake ForceAnnoAllVisible <Yes> : "), reply);
      // Overrides the ANNOALLVISIBLE system variable for this object and forces
      // it to display regardless of the current scale.
      es = annotationPE->setForceAnnoAllVisible(ent, (reply[0] == _T('Y') || res == RTNONE));

      // ask about force setting
      acedInitGet(NULL, _T("Yes No"));
      _tcscpy(reply, _T("Yes"));
      res = acedGetKword(_T("\nMake FromStyle <Yes> : "), reply);
      // if yes
      //es = annotationPE->setFromStyle(ent, reply[0] == _T('Y') || res == RTNONE);
    }
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////
// util function to print out the AcDbObjectContext data
static bool PrintObjectContext (AcDbObjectContext *objectContext)
{
  // if we have what we want
  if (objectContext && objectContext->isKindOf(AcDbAnnotationScale::desc()) ) 
  {
    // find out the name of the annotation scale context
    AcString strName;
    AcDbAnnotationScale *annoScale = (AcDbAnnotationScale*)objectContext;
    Acad::ErrorStatus es = annoScale->getName(strName);
    double paperUnits = 0;
    es = annoScale->getPaperUnits(paperUnits);
    double drawingUnits = 0;
    es = annoScale->getDrawingUnits(drawingUnits);
    double scale = 0;
    es = annoScale->getScale(scale);
    acutPrintf(_T("\n '%s' - PaperUnits(%.1f) DrawingUnits(%.1f) - Scale = %.1f "), (const TCHAR *)strName, paperUnits, drawingUnits, scale);
  }
  else if (objectContext)
  {
    acutPrintf(_T("\nNot %s, but a %s"), AcDbAnnotationScale::desc()->name(), objectContext->isA()->name());
    return false;
  }

  return true;
}


//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CAnnotationApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CAnnotationApp, adskAnnotationScaling, listAnno, listAnno, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CAnnotationApp, adskAnnotationScaling, checkAnno, checkAnno, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CAnnotationApp, adskAnnotationScaling, addAnnoEnt, addAnnoEnt, ACRX_CMD_TRANSPARENT, NULL)
