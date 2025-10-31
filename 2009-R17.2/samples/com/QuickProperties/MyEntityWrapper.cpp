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
//----- MyEntityWrapper.cpp : Implementation of CMyEntityWrapper
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "MyEntityWrapper.h"

//----- CMyEntityWrapper
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::InterfaceSupportsErrorInfo (REFIID riid) {
	static const IID * arr [] ={
		&IID_IMyEntityWrapper
	} ;

	for ( int i =0 ; i < sizeof (arr) / sizeof (arr [0]) ; i++ ) {
		if ( InlineIsEqualGUID (*arr [i], riid) )
			return (S_OK) ;
	}
	return (S_FALSE) ;
}

//////////////////////////////////////////////////////////////////////////
//IAcadBaseObjectImpl
HRESULT CMyEntityWrapper::CreateNewObject (AcDbObjectId &objId, AcDbObjectId &ownerId, TCHAR *keyName) {
	try {
		HRESULT hr ;
		if ( FAILED(hr =CreateObject (ownerId, keyName)) )
			throw hr ;
		if ( FAILED(hr =AddToDb (objId, ownerId, keyName)) )
			throw hr ;
	} catch( HRESULT hr ) {
		return (hr) ;
	}
	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
//IAcadBaseObject2Impl
STDMETHODIMP CMyEntityWrapper::ForceDbResident (VARIANT_BOOL *forceDbResident) 
{
	if ( forceDbResident == NULL )
		return (E_POINTER) ;
	//----- Return ACAX_VARIANT_TRUE if the object must be database resident to be functional
	*forceDbResident =ACAX_VARIANT_FALSE ;
	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::CreateObject (AcDbObjectId ownerId /*=AcDbObjectId::kNull*/, TCHAR *keyName /*=NULL*/) 
{
	try 
  {
		Acad::ErrorStatus es ;
		AcDbObjectPointer<asdkMyEntity> obj;
		if ( (es =obj.create ()) != Acad::eOk )
			throw es ;

		obj->setDatabaseDefaults (ownerId.database ()) ;

		asdkMyEntity *pTmp =NULL ;
		obj.release (pTmp) ;

		SetObject ((AcDbObject *&)pTmp) ;
	} catch ( const Acad::ErrorStatus ) {
		return (Error (L"Failed to create asdkMyEntity", IID_IMyEntityWrapper, E_FAIL)) ;
	}
	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::AddToDb (AcDbObjectId &objId, AcDbObjectId ownerId /*=AcDbObjectId::kNull*/, TCHAR *keyName /*=NULL*/) 
{
	try 
  {
		AcAxDocLock docLock (ownerId) ;

		Acad::ErrorStatus es ;
		AcAxObjectRefPtr<asdkMyEntity> obj (&m_objRef, AcDb::kForRead) ;

		//----- Entities can be owned by block table records only
		AcDbBlockTableRecordPointer pBlockTableRecord (ownerId, AcDb::kForWrite, true) ;
		if ( (es =pBlockTableRecord.openStatus ()) != Acad::eOk )
			throw es ;

		if ( (es =pBlockTableRecord->appendAcDbEntity (objId, obj.object ())) != Acad::eOk )
			throw es ;
	} catch( const Acad::ErrorStatus ) {
		return (Error(L"Failed to add asdkMyEntity to database", IID_IMyEntityWrapper, E_FAIL)) ;
	}
	return (SetObjectId (objId)) ;
}

//////////////////////////////////////////////////////////////////////////
// IOPMPropertyExtension
STDMETHODIMP CMyEntityWrapper::ShowProperty (/*[in]*/ DISPID dispid,/*[out]*/ BOOL* pShow)
{
  // try and open the obejct
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if we opened it ok
  if (myEnt.openStatus() == Acad::eOk)
  {
    // see which field it is
    switch (dispid)
    {
      // if it's the  type
      case (0x01) : *pShow = true; return (S_OK);
      // point value
      case (0x02) : *pShow = true; return (S_OK);
      // text string - if normal type don't show
      case (0x03) : *pShow = myEnt->mGetMyType() == 0 ? false:true; return (S_OK);
      // rotation
      case (0x04) : *pShow = true; return (S_OK);
      // length
      case (0x05) : *pShow = true; return (S_OK);
      // dropdown
      case (0x06) : *pShow = true; return (S_OK);
      // surfacearea
      case (0x07) : *pShow = true; return (S_OK);
      // radius
      case (0x08) : *pShow = true; return (S_OK);
      // width
      case (0x09) : *pShow = true; return (S_OK);
      // height
      case (0x0a) : *pShow = true; return (S_OK);
    }
  }

  // otherwise return the std opm property defaults
  return AcOpmShowProperty(reinterpret_cast<IUnknown*>(this), CMyEntityWrapper::GetOPMPropertyMap(), dispid, pShow);
}
//////////////////////////////////////////////////////////////////////////
//IOPMPropertyExpander
STDMETHODIMP CMyEntityWrapper::GetElementValue (DISPID dispID, DWORD dwCookie, VARIANT *pVarOut) 
{
	if ( pVarOut == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::SetElementValue (DISPID dispID, DWORD dwCookie, VARIANT VarIn) 
{
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::GetElementStrings (DISPID dispID, OPMLPOLESTR __RPC_FAR *pCaStringsOut, OPMDWORD __RPC_FAR *pCaCookiesOut) 
{
	if ( pCaStringsOut == NULL || pCaCookiesOut == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::GetElementGrouping (DISPID dispID, short *groupingNumber) 
{
	if ( groupingNumber == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::GetGroupCount (DISPID dispID, long *nGroupCnt) 
{
	if ( nGroupCnt == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}


//////////////////////////////////////////////////////////////////////////
// my properties
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyType(LONG* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyType();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyType(LONG newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      // now send it to the entity
      myEnt->mSetMyType(newVal);
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyPointValue(ACAD_POINT* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if ok
  if (myEnt.openStatus() == Acad::eOk)
    AcAxPoint3d(myEnt->mGetMyPointValue()).setVariant(pVal);

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyPointValue(ACAD_POINT newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyPointValue(AcAxPoint3d(newVal));
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyTextString(BSTR* pVal)
{
  // check to see if we have something set already
  if (*pVal)
    SysFreeString(*pVal);

  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if ok
  if (myEnt.openStatus() == Acad::eOk)
  {
    // get the text string
    TCHAR *myTextString = myEnt->mGetMyTextString();
    // send it back to opm
    USES_CONVERSION;
    *pVal = SysAllocString(T2W((LPTSTR)myTextString));
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyTextString(BSTR newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
    {
      // convert to TCHAR
      USES_CONVERSION;
      TCHAR *myTextString = W2T(newVal);
      // now send it to the entity
      myEnt->mSetMyTextString(myTextString);
    }
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyRotation(ACAD_ANGLE* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyRotation();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyRotation(ACAD_ANGLE newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyRotation(newVal);
  }
  return S_OK;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyLength(ACAD_ANGLE* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyLength();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyLength(ACAD_ANGLE newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyLength(newVal);
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyDropDown(LONG* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyDropDown();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyDropDown(LONG newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      // now send it to the entity
      myEnt->mSetMyDropDown(newVal);
  }

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MySurfaceArea(ACAD_NOUNITS* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMySurfaceArea();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MySurfaceArea(ACAD_NOUNITS newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMySurfaceArea(newVal);
  }
  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyRadius(ACAD_DISTANCE* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyRadius();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyRadius(ACAD_DISTANCE newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyRadius(newVal);
  }
  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyWidth(ACAD_DISTANCE* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyWidth();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyWidth(ACAD_DISTANCE newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyWidth(newVal);
  }
  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::get_MyHeight(ACAD_DISTANCE* pVal)
{
  // open for read, no need to lock the document
  AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForRead);
  // if opened ok
  if (myEnt.openStatus() == Acad::eOk)
    *pVal = myEnt->mGetMyHeight();

  return S_OK;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityWrapper::put_MyHeight(ACAD_DISTANCE newVal)
{
  // lock the document
  AcAxDocLock lock(m_objId);
  // if locked ok
  if (lock.lockStatus() == Acad::eOk)
  {
    // open the entity for write
    AcDbObjectPointer<asdkMyEntity> myEnt(m_objId, AcDb::kForWrite);
    // if opened ok
    if (myEnt.openStatus() == Acad::eOk)
      myEnt->mSetMyHeight(newVal);
  }
  return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// IFilterableProperty
// The "ShowFilterableProperty" method is used to dictate whether a
// property should be visible in the property filter customization user
// interface.  It is passed a DISPID of the property whose visibility is
// being determined (which would normally be "DISPID_DYNAMIC" for dynamic
// properties) and an AcFilterablePropertyContext that specifies whether
// the framework is querying about appearance in the "Quick Properties"
// customization user interface or for the "Rollover tooltips"
// customization user interface.  A boolean value indicating whether or
// not the property should be shown is returned via the "pbShow"
// output parameter.
STDMETHODIMP CMyEntityWrapper::ShowFilterableProperty(/*[in]*/DISPID dispID,
                                                  /*[in]*/AcFilterablePropertyContext context,
                                                  /*[out, retval]*/BOOL* pbShow)
{
  // check that all is valid
  if (!pbShow)
    return E_POINTER;

  // make sure it's NOT a dynamic property
  ASSERT(dispID != DISPID_DYNAMIC);

  // see which property we are on, lets just show them all for now
  switch (dispID) 
  {
    // ok just show it
    default: return ShowProperty(dispID, pbShow);
  }

  return S_OK;
}

