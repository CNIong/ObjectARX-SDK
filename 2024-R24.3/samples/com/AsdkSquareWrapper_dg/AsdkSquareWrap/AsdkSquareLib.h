//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Mar 25 13:39:08 2005
 */
/* Compiler settings for AsdkSquareLib.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __AsdkSquareLib_h__
#define __AsdkSquareLib_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAsdkSquareWrapper_FWD_DEFINED__
#define __IAsdkSquareWrapper_FWD_DEFINED__
typedef interface IAsdkSquareWrapper IAsdkSquareWrapper;
#endif 	/* __IAsdkSquareWrapper_FWD_DEFINED__ */


#ifndef __AsdkSquareWrapper_FWD_DEFINED__
#define __AsdkSquareWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class AsdkSquareWrapper AsdkSquareWrapper;
#else
typedef struct AsdkSquareWrapper AsdkSquareWrapper;
#endif /* __cplusplus */

#endif 	/* __AsdkSquareWrapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __ASDKSQUARELIBLib_LIBRARY_DEFINED__
#define __ASDKSQUARELIBLib_LIBRARY_DEFINED__

/* library ASDKSQUARELIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ASDKSQUARELIBLib;

#ifndef __IAsdkSquareWrapper_INTERFACE_DEFINED__
#define __IAsdkSquareWrapper_INTERFACE_DEFINED__

/* interface IAsdkSquareWrapper */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAsdkSquareWrapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("800F70AD-6DE9-11D2-A7A6-0060B0872457")
    IAsdkSquareWrapper : public IAcadEntity
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Number( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Number( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SquareSize( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SquareSize( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CenterPoint( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CenterPoint( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAsdkSquareWrapperVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAsdkSquareWrapper * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectName )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetXData )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BSTR AppName,
            /* [out][idldescattr] */ VARIANT *XDataType,
            /* [out][idldescattr] */ VARIANT *XDataValue,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *SetXData )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT XDataType,
            /* [in][idldescattr] */ VARIANT XDataValue,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectID )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IAcadDatabase **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_HasExtensionDictionary )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetExtensionDictionary )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IAcadDictionary **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_OwnerID )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Erase )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_TrueColor )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IAcadAcCmColor **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_TrueColor )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ IAcadAcCmColor *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Layer )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Layer )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Linetype )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Linetype )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_LinetypeScale )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ ACAD_NOUNITS *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_LinetypeScale )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ ACAD_NOUNITS noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BOOLEAN noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ArrayPolar )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ signed INT NumberOfObjects,
            /* [in][idldescattr] */ double AngleToFill,
            /* [in][idldescattr] */ VARIANT CenterPoint,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ArrayRectangular )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ signed INT NumberOfRows,
            /* [in][idldescattr] */ signed INT NumberOfColumns,
            /* [in][idldescattr] */ signed INT NumberOfLevels,
            /* [in][idldescattr] */ double DistBetweenRows,
            /* [in][idldescattr] */ double DistBetweenCols,
            /* [in][idldescattr] */ double DistBetweenLevels,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Highlight )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BOOLEAN HighlightFlag,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT FromPoint,
            /* [in][idldescattr] */ VARIANT ToPoint,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Rotate3D )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Mirror )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Mirror3D )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ VARIANT point3,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ScaleEntity )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double ScaleFactor,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *TransformBy )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ VARIANT TransformationMatrix,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingBox )( 
            IAsdkSquareWrapper * This,
            /* [out][idldescattr] */ VARIANT *MinPoint,
            /* [out][idldescattr] */ VARIANT *MaxPoint,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IntersectWith )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ IDispatch *IntersectObject,
            /* [in][idldescattr] */ enum AcExtendOption option,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_PlotStyleName )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_PlotStyleName )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Lineweight )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ ACAD_LWEIGHT *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Lineweight )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ ACAD_LWEIGHT noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Hyperlinks )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ IAcadHyperlinks **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_EntityName )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_EntityType )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_color )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ ACAD_COLOR *retval);
        
        /* [id][propput][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_color )( 
            IAsdkSquareWrapper * This,
            /* [in][idldescattr] */ ACAD_COLOR noname,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Number )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Number )( 
            IAsdkSquareWrapper * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SquareSize )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SquareSize )( 
            IAsdkSquareWrapper * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterPoint )( 
            IAsdkSquareWrapper * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CenterPoint )( 
            IAsdkSquareWrapper * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IAsdkSquareWrapperVtbl;

    interface IAsdkSquareWrapper
    {
        CONST_VTBL struct IAsdkSquareWrapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsdkSquareWrapper_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IAsdkSquareWrapper_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IAsdkSquareWrapper_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IAsdkSquareWrapper_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IAsdkSquareWrapper_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IAsdkSquareWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IAsdkSquareWrapper_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IAsdkSquareWrapper_get_Handle(This,retval)	\
    (This)->lpVtbl -> get_Handle(This,retval)

#define IAsdkSquareWrapper_get_ObjectName(This,retval)	\
    (This)->lpVtbl -> get_ObjectName(This,retval)

#define IAsdkSquareWrapper_GetXData(This,AppName,XDataType,XDataValue,retval)	\
    (This)->lpVtbl -> GetXData(This,AppName,XDataType,XDataValue,retval)

#define IAsdkSquareWrapper_SetXData(This,XDataType,XDataValue,retval)	\
    (This)->lpVtbl -> SetXData(This,XDataType,XDataValue,retval)

#define IAsdkSquareWrapper_Delete(This,retval)	\
    (This)->lpVtbl -> Delete(This,retval)

#define IAsdkSquareWrapper_get_ObjectID(This,retval)	\
    (This)->lpVtbl -> get_ObjectID(This,retval)

#define IAsdkSquareWrapper_get_Application(This,retval)	\
    (This)->lpVtbl -> get_Application(This,retval)

#define IAsdkSquareWrapper_get_Database(This,retval)	\
    (This)->lpVtbl -> get_Database(This,retval)

#define IAsdkSquareWrapper_get_HasExtensionDictionary(This,retval)	\
    (This)->lpVtbl -> get_HasExtensionDictionary(This,retval)

#define IAsdkSquareWrapper_GetExtensionDictionary(This,retval)	\
    (This)->lpVtbl -> GetExtensionDictionary(This,retval)

#define IAsdkSquareWrapper_get_OwnerID(This,retval)	\
    (This)->lpVtbl -> get_OwnerID(This,retval)

#define IAsdkSquareWrapper_get_Document(This,retval)	\
    (This)->lpVtbl -> get_Document(This,retval)

#define IAsdkSquareWrapper_Erase(This,retval)	\
    (This)->lpVtbl -> Erase(This,retval)

#define IAsdkSquareWrapper_get_TrueColor(This,retval)	\
    (This)->lpVtbl -> get_TrueColor(This,retval)

#define IAsdkSquareWrapper_put_TrueColor(This,noname,retval)	\
    (This)->lpVtbl -> put_TrueColor(This,noname,retval)

#define IAsdkSquareWrapper_get_Layer(This,retval)	\
    (This)->lpVtbl -> get_Layer(This,retval)

#define IAsdkSquareWrapper_put_Layer(This,noname,retval)	\
    (This)->lpVtbl -> put_Layer(This,noname,retval)

#define IAsdkSquareWrapper_get_Linetype(This,retval)	\
    (This)->lpVtbl -> get_Linetype(This,retval)

#define IAsdkSquareWrapper_put_Linetype(This,noname,retval)	\
    (This)->lpVtbl -> put_Linetype(This,noname,retval)

#define IAsdkSquareWrapper_get_LinetypeScale(This,retval)	\
    (This)->lpVtbl -> get_LinetypeScale(This,retval)

#define IAsdkSquareWrapper_put_LinetypeScale(This,noname,retval)	\
    (This)->lpVtbl -> put_LinetypeScale(This,noname,retval)

#define IAsdkSquareWrapper_get_Visible(This,retval)	\
    (This)->lpVtbl -> get_Visible(This,retval)

#define IAsdkSquareWrapper_put_Visible(This,noname,retval)	\
    (This)->lpVtbl -> put_Visible(This,noname,retval)

#define IAsdkSquareWrapper_ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)	\
    (This)->lpVtbl -> ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)

#define IAsdkSquareWrapper_ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)	\
    (This)->lpVtbl -> ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)

#define IAsdkSquareWrapper_Highlight(This,HighlightFlag,retval)	\
    (This)->lpVtbl -> Highlight(This,HighlightFlag,retval)

#define IAsdkSquareWrapper_Copy(This,retval)	\
    (This)->lpVtbl -> Copy(This,retval)

#define IAsdkSquareWrapper_Move(This,FromPoint,ToPoint,retval)	\
    (This)->lpVtbl -> Move(This,FromPoint,ToPoint,retval)

#define IAsdkSquareWrapper_Rotate(This,BasePoint,RotationAngle,retval)	\
    (This)->lpVtbl -> Rotate(This,BasePoint,RotationAngle,retval)

#define IAsdkSquareWrapper_Rotate3D(This,Point1,Point2,RotationAngle,retval)	\
    (This)->lpVtbl -> Rotate3D(This,Point1,Point2,RotationAngle,retval)

#define IAsdkSquareWrapper_Mirror(This,Point1,Point2,retval)	\
    (This)->lpVtbl -> Mirror(This,Point1,Point2,retval)

#define IAsdkSquareWrapper_Mirror3D(This,Point1,Point2,point3,retval)	\
    (This)->lpVtbl -> Mirror3D(This,Point1,Point2,point3,retval)

#define IAsdkSquareWrapper_ScaleEntity(This,BasePoint,ScaleFactor,retval)	\
    (This)->lpVtbl -> ScaleEntity(This,BasePoint,ScaleFactor,retval)

#define IAsdkSquareWrapper_TransformBy(This,TransformationMatrix,retval)	\
    (This)->lpVtbl -> TransformBy(This,TransformationMatrix,retval)

#define IAsdkSquareWrapper_Update(This,retval)	\
    (This)->lpVtbl -> Update(This,retval)

#define IAsdkSquareWrapper_GetBoundingBox(This,MinPoint,MaxPoint,retval)	\
    (This)->lpVtbl -> GetBoundingBox(This,MinPoint,MaxPoint,retval)

#define IAsdkSquareWrapper_IntersectWith(This,IntersectObject,option,retval)	\
    (This)->lpVtbl -> IntersectWith(This,IntersectObject,option,retval)

#define IAsdkSquareWrapper_get_PlotStyleName(This,retval)	\
    (This)->lpVtbl -> get_PlotStyleName(This,retval)

#define IAsdkSquareWrapper_put_PlotStyleName(This,noname,retval)	\
    (This)->lpVtbl -> put_PlotStyleName(This,noname,retval)

#define IAsdkSquareWrapper_get_Lineweight(This,retval)	\
    (This)->lpVtbl -> get_Lineweight(This,retval)

#define IAsdkSquareWrapper_put_Lineweight(This,noname,retval)	\
    (This)->lpVtbl -> put_Lineweight(This,noname,retval)

#define IAsdkSquareWrapper_get_Hyperlinks(This,retval)	\
    (This)->lpVtbl -> get_Hyperlinks(This,retval)

#define IAsdkSquareWrapper_get_EntityName(This,retval)	\
    (This)->lpVtbl -> get_EntityName(This,retval)

#define IAsdkSquareWrapper_get_EntityType(This,retval)	\
    (This)->lpVtbl -> get_EntityType(This,retval)

#define IAsdkSquareWrapper_get_color(This,retval)	\
    (This)->lpVtbl -> get_color(This,retval)

#define IAsdkSquareWrapper_put_color(This,noname,retval)	\
    (This)->lpVtbl -> put_color(This,noname,retval)


#define IAsdkSquareWrapper_get_Number(This,pVal)	\
    (This)->lpVtbl -> get_Number(This,pVal)

#define IAsdkSquareWrapper_put_Number(This,newVal)	\
    (This)->lpVtbl -> put_Number(This,newVal)

#define IAsdkSquareWrapper_get_SquareSize(This,pVal)	\
    (This)->lpVtbl -> get_SquareSize(This,pVal)

#define IAsdkSquareWrapper_put_SquareSize(This,newVal)	\
    (This)->lpVtbl -> put_SquareSize(This,newVal)

#define IAsdkSquareWrapper_get_CenterPoint(This,pVal)	\
    (This)->lpVtbl -> get_CenterPoint(This,pVal)

#define IAsdkSquareWrapper_put_CenterPoint(This,newVal)	\
    (This)->lpVtbl -> put_CenterPoint(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_Number_Proxy( 
    IAsdkSquareWrapper * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_Number_Proxy( 
    IAsdkSquareWrapper * This,
    /* [in] */ short newVal);


void __RPC_STUB IAsdkSquareWrapper_put_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_SquareSize_Proxy( 
    IAsdkSquareWrapper * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_SquareSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_SquareSize_Proxy( 
    IAsdkSquareWrapper * This,
    /* [in] */ double newVal);


void __RPC_STUB IAsdkSquareWrapper_put_SquareSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_CenterPoint_Proxy( 
    IAsdkSquareWrapper * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_CenterPoint_Proxy( 
    IAsdkSquareWrapper * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IAsdkSquareWrapper_put_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAsdkSquareWrapper_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AsdkSquareWrapper;

#ifdef __cplusplus

class DECLSPEC_UUID("800F70AE-6DE9-11D2-A7A6-0060B0872457")
AsdkSquareWrapper;
#endif
#endif /* __ASDKSQUARELIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


