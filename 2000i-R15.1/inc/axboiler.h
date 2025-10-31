//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// AXBOILER.H
//
// Interface declarations for the AutoCAD Automation API +
// common object/entity manipulation functions.
//

#ifndef __AXBOILER_H_
#define __AXBOILER_H_

#ifndef AXAUTOEXP
#ifdef AXAUTO15_DLL
	#define AXAUTOEXP __declspec(dllexport)
#else
	#define AXAUTOEXP __declspec(dllimport)
#endif
#endif


DEFINE_GUID(IID_IAcadBaseObject, 
0x5f3c54c0, 0x49e1, 0x11cf, 0x93, 0xd5, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IAcadBaseObject */
#undef INTERFACE
#define INTERFACE IAcadBaseObject

interface DECLSPEC_UUID("5F3C54C0-49E1-11cf-93D5-0800099EB3B7") 
IAcadBaseObject : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject methods */
    STDMETHOD(SetObjectId)(THIS_ AcDbObjectId& objId, 
                           AcDbObjectId ownerId = AcDbObjectId::kNull, 
                           TCHAR* keyName = NULL) PURE;
    STDMETHOD(GetObjectId)(THIS_ AcDbObjectId* objId) PURE;
    STDMETHOD(Clone)(THIS_ AcDbObjectId ownerId, LPUNKNOWN* pUnkClone) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
    STDMETHOD(NullObjectId)(THIS) PURE;
    STDMETHOD(OnModified)(THIS) PURE;
};

typedef IAcadBaseObject* LPACADBASEOBJECT;

DEFINE_GUID(IID_IRetrieveApplication, 
0x765b4640, 0x664a, 0x11cf, 0x93, 0xf3, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IRetrieveApplication */
interface DECLSPEC_UUID("765B4640-664A-11cf-93F3-0800099EB3B7") 
IRetrieveApplication : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IRetrieveApplication methods */
    STDMETHOD(SetApplicationObject)(THIS_ LPDISPATCH pAppDisp) PURE;
    STDMETHOD(GetApplicationObject)(THIS_ LPDISPATCH* pAppDisp) PURE;
};

typedef IRetrieveApplication* LPRETRIEVEAPPLICATION;

DEFINE_GUID(IID_IAcadBaseDatabase, 
0xcb1488c4, 0x2bec, 0x11d2, 0xb6, 0x7b, 0x0, 0x60, 0xb0, 0x87, 0xe2, 0x35);

/* Definition of interface: IAcadBaseDatabase */
interface DECLSPEC_UUID("CB1488C4-2BEC-11d2-B67B-0060B087E235") 
IAcadBaseDatabase : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject methods */
    STDMETHOD(SetDatabase)(THIS_ AcDbDatabase*& pDb) PURE;
    STDMETHOD(GetDatabase)(THIS_ AcDbDatabase** pDb) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
};

typedef IAcadBaseDatabase* LPACADBASEDATABASE;

//
// Common object/entity helper functions
//
HRESULT AXAUTOEXP 
AcAxErase(AcDbObjectId& objId);

HRESULT AXAUTOEXP 
AcAxSetXData(AcDbObjectId& objId, VARIANT type, VARIANT data);

HRESULT AXAUTOEXP 
AcAxGetXData(AcDbObjectId& objId, BSTR bstrName, VARIANT* type, VARIANT* data);

HRESULT AXAUTOEXP 
AcAxGetObjectName(AcDbObjectId& objId, BSTR* pName);

HRESULT AXAUTOEXP 
AcAxGetHandle(AcDbObjectId& objId, BSTR* pHandle);

HRESULT AXAUTOEXP 
AcAxGetColor(AcDbObjectId& objId, AcColor* pColor);

HRESULT AXAUTOEXP 
AcAxPutColor(AcDbObjectId& objId, AcColor color);

HRESULT AXAUTOEXP 
AcAxGetLayer(AcDbObjectId& objId, BSTR* pLayer);

HRESULT AXAUTOEXP 
AcAxPutLayer(AcDbObjectId& objId, BSTR layer);

HRESULT AXAUTOEXP 
AcAxGetLinetype(AcDbObjectId& objId, BSTR* pLinetype);

HRESULT AXAUTOEXP 
AcAxPutLinetype(AcDbObjectId& objId, BSTR linetype);

HRESULT AXAUTOEXP 
AcAxGetLinetypeScale(AcDbObjectId& objId, double* pLinetypeScale);

HRESULT AXAUTOEXP 
AcAxPutLinetypeScale(AcDbObjectId& objId, double linetypeScale);

HRESULT AXAUTOEXP 
AcAxGetVisible(AcDbObjectId& objId, VARIANT_BOOL* pVisible);

HRESULT AXAUTOEXP 
AcAxPutVisible(AcDbObjectId& objId, VARIANT_BOOL visible);

HRESULT AXAUTOEXP 
AcAxArrayPolar(AcDbObjectId& objId, LPDISPATCH pAppDisp, int numObjs, 
               double fillAngle, VARIANT basePoint, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxArrayRectangular(AcDbObjectId& objId, LPDISPATCH pAppDisp, int numRows, 
                     int numCols, int numLvls, double disRows, double disCols,
                     double disLvls, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxHighlight(AcDbObjectId& objId, VARIANT_BOOL bHighlight);

HRESULT AXAUTOEXP 
AcAxCopy(AcDbObjectId& objId, LPDISPATCH pAppDisp, LPDISPATCH* pCopyObj, 
         AcDbObjectId ownerId = AcDbObjectId::kNull);

HRESULT AXAUTOEXP 
AcAxMove(AcDbObjectId& objId, VARIANT fromPoint, VARIANT toPoint);

HRESULT AXAUTOEXP 
AcAxRotate(AcDbObjectId& objId, VARIANT basePoint, double rotationAngle);

HRESULT AXAUTOEXP 
AcAxRotate3D(AcDbObjectId& objId, VARIANT point1, VARIANT point2, 
             double rotationAngle);

HRESULT AXAUTOEXP 
AcAxMirror(AcDbObjectId& objId, LPDISPATCH pAppDisp, VARIANT point1, 
           VARIANT point2, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxMirror3D(AcDbObjectId& objId, LPDISPATCH pAppDisp, VARIANT point1, 
             VARIANT point2, VARIANT point3, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxScaleEntity(AcDbObjectId& objId, VARIANT basePoint, double scaleFactor);

HRESULT AXAUTOEXP 
AcAxTransformBy(AcDbObjectId& objId, VARIANT transMatrix);

HRESULT AXAUTOEXP 
AcAxUpdate(AcDbObjectId& objId);

HRESULT AXAUTOEXP 
AcAxGetBoundingBox(AcDbObjectId& objId, VARIANT* minPoint, VARIANT* maxPoint);

HRESULT AXAUTOEXP 
AcAxIntersectWith(AcDbObjectId& objId, LPDISPATCH pEntity, 
                  AcExtendOption option, VARIANT* intPoints);

HRESULT AXAUTOEXP 
AcAxGetPlotStyleName(AcDbObjectId& objId, BSTR* plotStyleName);

HRESULT AXAUTOEXP 
AcAxPutPlotStyleName(AcDbObjectId& objId, BSTR plotStyleName);

HRESULT AXAUTOEXP 
AcAxGetLineWeight(AcDbObjectId& objId, ACAD_LWEIGHT* lineWeight);

HRESULT AXAUTOEXP 
AcAxPutLineWeight(AcDbObjectId& objId, ACAD_LWEIGHT lineWeight);

HRESULT AXAUTOEXP 
AcAxGetHyperlinks(AcDbObjectId& objId, LPDISPATCH pAppDisp, 
                  IAcadHyperlinks** pHyperlinks);

HRESULT AXAUTOEXP 
AcAxHasExtensionDictionary(AcDbObjectId& objId, VARIANT_BOOL* bHasDictionary);

HRESULT AXAUTOEXP 
AcAxGetExtensionDictionary(AcDbObjectId& objId, LPDISPATCH pAppDisp, 
                           IAcadDictionary** pExtDictionary);

HRESULT AXAUTOEXP 
AcAxGetDatabase(AcDbDatabase* pDb, LPDISPATCH pAppDisp, LPDISPATCH* pDisp);

HRESULT AXAUTOEXP
AcAxGetOwnerId(AcDbObjectId& objId, long* pOwnerId); 

//
// Utility functions
//
HRESULT AXAUTOEXP
RaiseAcAXException(REFGUID iid, HRESULT hRes, DWORD dwException, ...);

HRESULT  AXAUTOEXP
RaiseArxException(REFGUID iid, HRESULT hRes, Acad::ErrorStatus es);

HRESULT AXAUTOEXP
AcAxGetIUnknownOfObject(LPUNKNOWN* ppUnk, AcDbObjectId& objId, LPDISPATCH pApp);

HRESULT AXAUTOEXP
AcAxGetIUnknownOfObject(LPUNKNOWN* ppUnk, AcDbObject* pObj, LPDISPATCH pApp);


#endif