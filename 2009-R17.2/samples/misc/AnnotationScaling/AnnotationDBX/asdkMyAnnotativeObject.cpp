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
//----- asdkMyAnnotativeObject.cpp : Implementation of asdkMyAnnotativeObject
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "asdkMyAnnotativeObject.h"
//////////////////////////////////////////////////////////////////////////
#include "dbannotationscale.h"
#include "dbAnnotativeObjectPE.h"
#include "dbObjectContextInterface.h"
#include "dbObjectContextCollection.h"
#include "dbObjectContextManager.h"

//////////////////////////////////////////////////////////////////////////
// check to see if the pass entity supports the following scale
bool IsThisScaleSupported(AcDbEntity *ent, AcDbAnnotationScale *scale);

//////////////////////////////////////////////////////////////////////////
Adesk::UInt32 asdkMyAnnotativeObject::kCurrentVersionNumber =1 ;

//////////////////////////////////////////////////////////////////////////
ACRX_DXF_DEFINE_MEMBERS (
	asdkMyAnnotativeObject, AcDbText,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, ASDKMYANNOTATIVEOBJECT,
	"ASDKANNOTATIONDBXAPP"
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

//////////////////////////////////////////////////////////////////////////
asdkMyAnnotativeObject::asdkMyAnnotativeObject () : AcDbText () 
{
  mIsSelected = false;
  mMyTextHeight = 1;
  mMyTextString = NULL;
  setMyTextString(_T(""));
  mOriginalScale = 0.0; 
}

asdkMyAnnotativeObject::~asdkMyAnnotativeObject () 
{
  if (mMyTextString != NULL)
    delete[] mMyTextString;

  mMyTextString = NULL;
}

//////////////////////////////////////////////////////////////////////////
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus asdkMyAnnotativeObject::dwgOutFields (AcDbDwgFiler *pFiler) const 
{
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbText::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (asdkMyAnnotativeObject::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....
  pFiler->writeItem(mMyTextHeight);
  pFiler->writeItem(mMyTextString);
  pFiler->writeItem(mOriginalScale);

	return (pFiler->filerStatus ()) ;
}

//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::dwgInFields (AcDbDwgFiler *pFiler) 
{
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbText::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > asdkMyAnnotativeObject::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < asdkMyAnnotativeObject::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....
  switch(kCurrentVersionNumber)
  {
    default:
    case 1:
    {
      pFiler->readItem(&mMyTextHeight);
      pFiler->readItem(&mMyTextString);
      pFiler->readItem(&mOriginalScale);
    }break;
  }
  mIsSelected = false;
	return (pFiler->filerStatus ()) ;
}

//////////////////////////////////////////////////////////////////////////
// global worldDraw function
Adesk::Boolean asdkMyAnnotativeObject::worldDraw(AcGiWorldDraw* mode)
{
  AcDbText::worldDraw(mode);
  
  // see if we are annotative
  AcDbAnnotativeObjectPE *annotationPE = ACRX_PE_PTR(this, AcDbAnnotativeObjectPE);
  // if we are, then return flag to invoke viewport draw
  if (annotationPE && annotationPE->annotative(this))
      return false;
  // otherwise, draw normally
  else
  {
    myCommonDraw(mode, true);
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////
void asdkMyAnnotativeObject::viewportDraw(AcGiViewportDraw* mode)
{
  AcDbText::viewportDraw(mode);

  myCommonDraw(mode, false);
}

//////////////////////////////////////////////////////////////////////////
extern AcCmEntityColor accmResolveEffectiveColorToRGB(const AcCmEntityColor& effectiveColor, AcDbObjectId entLayerId);
extern AcCmEntityColor accmAttenuateRGB(const AcCmEntityColor& in);
//////////////////////////////////////////////////////////////////////////
// common draw routine
void asdkMyAnnotativeObject::myCommonDraw(AcGiCommonDraw* commonDraw, bool isWorldDraw)
{
  bool isSupportedScale = false;
  // try to extract the Object Context Protocol Extension Object
  AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(this, AcDbObjectContextInterface);

  // if not worlddrawing and is selected
  if (!isWorldDraw && mIsSelected)
  {
    // if we have an Annotation Scaling context interface
    if (objectContextInterface) 
    {
      // loop all the annotations and display them
      // get the drawing we are working on...
      AcDbDatabase *dwg = commonDraw->context()->database();
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
          // save the original draw color
          AcCmEntityColor originalColor = commonDraw->context()->effectiveColor();

          // lets iterate through them, create a new iterator
          AcDbObjectContextCollectionIterator* pIter = contextCollection->newIterator();
          // now loop the items        
          for (pIter->start(); !pIter->done(); pIter->next()) 
          {
            AcDbObjectContext *objectContext = NULL;
            // get the context object for this iteration
            Acad::ErrorStatus es = pIter->getContext(objectContext);

            // get the current annotation scale
            AcDbAnnotationScale *annotationScale = AcDbAnnotationScale::cast(objectContext);
            // check to see if our object supports this scale
            if (annotationScale && objectContextInterface->hasContext(this, *annotationScale))
            {
              double scale = 1.0;
              // if so, get the scale
              annotationScale->getScale(scale);
              scale = (1/scale) * mOriginalScale;

              // get the viewport annotation scale and compare it to the annotation scale, if the same, highlight it
              if (fabs(getViewportScale(commonDraw, isWorldDraw, isSupportedScale) - scale) < 0.0001) 
              {
                commonDraw->subEntityTraits().setSelectionMarker(kBright);
                commonDraw->subEntityTraits().setTrueColor(originalColor);
              } 
              else 
              {
                commonDraw->subEntityTraits().setSelectionMarker(kDim);

                AcCmEntityColor bright = accmResolveEffectiveColorToRGB(originalColor, layerId());
                AcCmEntityColor dim = accmAttenuateRGB(bright);
                commonDraw->subEntityTraits().setTrueColor( dim );
              }

              // now physically draw the text for selection
              myDrawRoutine(commonDraw, isWorldDraw, scale);              
            }
          }
        }
      }
    }
  }
  else 
  {
    if (mIsSelected)
      commonDraw->subEntityTraits().setSelectionMarker(kBright);

    // get the viewport scale, and if it is a supported scale for this object
    double viewportScale = getViewportScale(commonDraw, isWorldDraw, isSupportedScale);
    // if supported then draw it regardless 
    if (isSupportedScale)
      myDrawRoutine(commonDraw, isWorldDraw, viewportScale);              
    // if it's not supported, but in Model space then draw it
    else if (commonDraw->context()->database()->tilemode())
      myDrawRoutine(commonDraw, isWorldDraw, viewportScale);              
  }
}

//////////////////////////////////////////////////////////////////////////
// draw routine
void asdkMyAnnotativeObject::myDrawRoutine(AcGiCommonDraw* commonDraw, bool isWorldDraw, double scale)
{
  // work out my text's insertion point
  AcGePoint3d textPnt = AcGePoint3d(position().x, position().y - 1.5*height(), 0);
  // work out my text's rotation
  AcGeVector3d textDirection = AcGeVector3d::kXAxis;
  textDirection.rotateBy(rotation(), normal());

  if ( isWorldDraw ) 
  {
    AcGiWorldDraw *worldDraw = (AcGiWorldDraw*)commonDraw;
    // now draw it
    worldDraw->geometry().text(textPnt, normal(), textDirection, myTextHeight()*scale, widthFactor(), oblique(), myTextString());  
  } 
  else 
  {
    AcGiViewportDraw *viewportDraw = (AcGiViewportDraw*)commonDraw;
    // now draw it
    viewportDraw->geometry().text(textPnt, normal(), textDirection, myTextHeight()*scale, widthFactor(), oblique(), myTextString());  
  }
}

//////////////////////////////////////////////////////////////////////////
// utility function for extracting the viewport annotation scale
double asdkMyAnnotativeObject::getViewportScale(AcGiCommonDraw *commonDraw, bool isWorldDraw, bool &isSupportedScale)
{
  // see which object owns us
  AcDbBlockTableRecordPointer owner (ownerId(), AcDb::kForRead);

  isSupportedScale = true;

  double scale = 1.0;
  // if worlddraw, then simply get the current annotation scale
  if (isWorldDraw)
  {
  }
  else
  {
    // cast the common draw to viewport draw
    AcGiViewportDraw *viewportDraw = (AcGiViewportDraw *)commonDraw;
    AcDbObjectPointer<AcDbViewport> viewport(viewportDraw->viewportObjectId(), AcDb::kForRead);
    // if ok
    if (viewport.openStatus() == Acad::eOk)
    {
      // get the current viewport's annotation scale setting
      AcDbAnnotationScale *viewPortScaleContext = viewport->annotationScale();
      // check to see if I support this viewport's scale
      isSupportedScale = IsThisScaleSupported(this, viewPortScaleContext);
      if (isSupportedScale)
      {
        viewPortScaleContext->getScale(scale);
        scale = (1/scale) * mOriginalScale;
      }
    }
    // if in modelspace
    else
    {
      // get the current annotation scale
      AcDbAnnotationScale *cannoScale = commonDraw->context()->database()->cannoscale();
      // check to see if I support the current annotation scale
      isSupportedScale = IsThisScaleSupported(this, cannoScale);
      if (isSupportedScale)
      {
        // get the scale value
        cannoScale->getScale(scale);
        scale = (1/scale) * mOriginalScale;
      }
    }
  }
  // return it
  return scale;
}

//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::highlight(const AcDbFullSubentPath& subentPath, const Adesk::Boolean highlightAll) const
{
  AcDbObjectId id = objectId();
  // Filter out the ghosted stuff from selection highlighting so that it 
  // will be less pronounced.
  AcDbFullSubentPath shiningPath(id, AcDb::kEdgeSubentType, kBright); 

  // try to extract the Object Context Protocol Extension Object
  AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(this, AcDbObjectContextInterface);
  // if we have an Annotation Scaling context interface
  if (objectContextInterface) 
  {
    if (!mIsSelected)
    {
      // get ride of the const function definition issues :-S
      (const_cast<asdkMyAnnotativeObject*>(this))->mIsSelected = true;
      acdbQueueForRegen(&id, 1);
    }
  }

  if (mIsSelected) 
    // Highlight only bright stuff
    return AcDbText::highlight(shiningPath, highlightAll);
  else 
    // Default highlighting.
    return AcDbText::highlight(subentPath, highlightAll);
}

//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::unhighlight(const AcDbFullSubentPath& subentPath, const Adesk::Boolean highlightAll) const
{
  if (mIsSelected) 
  {
    AcDbObjectId id = this->objectId();
    // get ride of the const function definition issues :-S
    (const_cast<asdkMyAnnotativeObject*>(this))->mIsSelected = false;
    acdbQueueForRegen(&id,1);
  }
  
  return AcDbText::unhighlight(subentPath, highlightAll);
}

//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::getGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath, AcArray<INT_PTR>& gsMarkers) const
{
  if (mIsSelected) 
  {
    const INT_PTR nSubEntId = subPath.subentId().index();
    assert(nSubEntId == kBright);
    gsMarkers.append(nSubEntId);
    return Acad::eOk;
  } 
  else
    return AcDbText::getGsMarkersAtSubentPath(subPath, gsMarkers);
}

//////////////////////////////////////////////////////////////////////////
double asdkMyAnnotativeObject::myTextHeight()
{
  assertReadEnabled();
  
  return(mMyTextHeight);
}
//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::setMyTextHeight(double modelTextHeight)
{
  // initialise the undo mechanism and fire object events
  assertWriteEnabled();

  // if not set
  if (fabs(mOriginalScale) < 0.00000000000000000001)
  {
    // get the current annotation scale
    AcDbAnnotationScale *annoScale = acdbHostApplicationServices()->workingDatabase()->cannoscale();
    // if ok
    if (annoScale)
      annoScale->getScale(mOriginalScale);
    else
    {
      acutPrintf(_T("\nERROR - Should never happen"));
    }
  }

  // Hp = Hm * s
  // mMyTextHeight is paper height.  
  mMyTextHeight = modelTextHeight;// * scale;

  return Acad::eOk;
}
//////////////////////////////////////////////////////////////////////////
ACHAR* asdkMyAnnotativeObject::myTextString()
{
  assertReadEnabled();
  
  return(mMyTextString);
}
//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::setMyTextString(ACHAR *textString)
{
  // initialise the undo mechanism and fire object events
  assertWriteEnabled();

  if (mMyTextString != NULL)
    delete[] mMyTextString;

  mMyTextString = _tcsdup(textString);

  return Acad::eOk;
}

//////////////////////////////////////////////////////////////////////////
bool asdkMyAnnotativeObject::isSelected()
{
  assertReadEnabled();

  return mIsSelected;
}
//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyAnnotativeObject::setIsSelected(bool isSelected)
{
  // initialise the undo mechanism and fire object events
  assertWriteEnabled();

  mIsSelected = isSelected;

  return Acad::eOk;
}

//////////////////////////////////////////////////////////////////////////
// check to see if the pass entity supports the following scale
bool IsThisScaleSupported(AcDbEntity *ent, AcDbAnnotationScale *scale)
{
  // check to see if this scale is supported
  AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(ent, AcDbObjectContextInterface);
  // if scale contexts
  if (objectContextInterface)
  {
    // check to see if our entity supports this context
    if (objectContextInterface->hasContext(ent, *scale))
      return true;
  }

  return false;
}