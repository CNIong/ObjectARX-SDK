// (C) Copyright 1999 by Autodesk, Inc. 
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

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 14 20:45:14 1998
 */
/* Compiler settings for V:\Temp\sq\AsdkSquareLib\AsdkSquareLib.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAsdkSquareWrapper_FWD_DEFINED__
#define __IAsdkSquareWrapper_FWD_DEFINED__
typedef interface IAsdkSquareWrapper IAsdkSquareWrapper;
#endif  /* __IAsdkSquareWrapper_FWD_DEFINED__ */


#ifndef __AsdkSquareWrapper_FWD_DEFINED__
#define __AsdkSquareWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class AsdkSquareWrapper AsdkSquareWrapper;
#else
typedef struct AsdkSquareWrapper AsdkSquareWrapper;
#endif /* __cplusplus */

#endif  /* __AsdkSquareWrapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


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
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Number( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SquareSize( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SquareSize( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CenterPoint( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CenterPoint( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IAsdkSquareWrapperVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ struct GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ struct GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ObjectName )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXData )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR AppName,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *XDataType,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *XDataValue,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXData )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT XDataType,
            /* [in][idldescattr] */ VARIANT XDataValue,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ObjectID )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Database )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasExtensionDictionary )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BOOLEAN __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtensionDictionary )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ IAcadDictionary __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OwnerID )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [id][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erase )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ ACAD_COLOR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_COLOR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Layer )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Layer )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Linetype )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Linetype )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LinetypeScale )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ ACAD_NOUNITS __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LinetypeScale )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_NOUNITS noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BOOLEAN __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BOOLEAN noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArrayPolar )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ signed INT NumberOfObjects,
            /* [in][idldescattr] */ double AngleToFill,
            /* [in][idldescattr] */ VARIANT CenterPoint,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArrayRectangular )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ signed INT NumberOfRows,
            /* [in][idldescattr] */ signed INT NumberOfColumns,
            /* [in][idldescattr] */ signed INT NumberOfLevels,
            /* [in][idldescattr] */ double DistBetweenRows,
            /* [in][idldescattr] */ double DistBetweenCols,
            /* [in][idldescattr] */ double DistBetweenLevels,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Highlight )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BOOLEAN HighlightFlag,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT FromPoint,
            /* [in][idldescattr] */ VARIANT ToPoint,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate3D )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror3D )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ VARIANT point3,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleEntity )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double ScaleFactor,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformBy )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT TransformationMatrix,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBoundingBox )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *MinPoint,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *MaxPoint,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntersectWith )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ IDispatch __RPC_FAR *IntersectObject,
            /* [in][idldescattr] */ enum AcExtendOption option,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PlotStyleName )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PlotStyleName )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lineweight )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ ACAD_LWEIGHT __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Lineweight )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_LWEIGHT noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ IAcadHyperlinks __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntityName )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntityType )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Number )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Number )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SquareSize )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SquareSize )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CenterPoint )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CenterPoint )( 
            IAsdkSquareWrapper __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IAsdkSquareWrapperVtbl;

    interface IAsdkSquareWrapper
    {
        CONST_VTBL struct IAsdkSquareWrapperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsdkSquareWrapper_QueryInterface(This,riid,ppvObj,retval)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IAsdkSquareWrapper_AddRef(This,retval)  \
    (This)->lpVtbl -> AddRef(This,retval)

#define IAsdkSquareWrapper_Release(This,retval) \
    (This)->lpVtbl -> Release(This,retval)

#define IAsdkSquareWrapper_GetTypeInfoCount(This,pctinfo,retval)    \
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IAsdkSquareWrapper_GetTypeInfo(This,itinfo,lcid,pptinfo,retval) \
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IAsdkSquareWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)   \
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IAsdkSquareWrapper_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) \
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IAsdkSquareWrapper_get_Handle(This,retval)  \
    (This)->lpVtbl -> get_Handle(This,retval)

#define IAsdkSquareWrapper_get_ObjectName(This,retval)  \
    (This)->lpVtbl -> get_ObjectName(This,retval)

#define IAsdkSquareWrapper_GetXData(This,AppName,XDataType,XDataValue,retval)   \
    (This)->lpVtbl -> GetXData(This,AppName,XDataType,XDataValue,retval)

#define IAsdkSquareWrapper_SetXData(This,XDataType,XDataValue,retval)   \
    (This)->lpVtbl -> SetXData(This,XDataType,XDataValue,retval)

#define IAsdkSquareWrapper_Delete(This,retval)  \
    (This)->lpVtbl -> Delete(This,retval)

#define IAsdkSquareWrapper_get_ObjectID(This,retval)    \
    (This)->lpVtbl -> get_ObjectID(This,retval)

#define IAsdkSquareWrapper_get_Application(This,retval) \
    (This)->lpVtbl -> get_Application(This,retval)

#define IAsdkSquareWrapper_get_Database(This,retval)    \
    (This)->lpVtbl -> get_Database(This,retval)

#define IAsdkSquareWrapper_get_HasExtensionDictionary(This,retval)  \
    (This)->lpVtbl -> get_HasExtensionDictionary(This,retval)

#define IAsdkSquareWrapper_GetExtensionDictionary(This,retval)  \
    (This)->lpVtbl -> GetExtensionDictionary(This,retval)

#define IAsdkSquareWrapper_get_OwnerID(This,retval) \
    (This)->lpVtbl -> get_OwnerID(This,retval)

#define IAsdkSquareWrapper_Erase(This,retval)   \
    (This)->lpVtbl -> Erase(This,retval)

#define IAsdkSquareWrapper_get_Color(This,retval)   \
    (This)->lpVtbl -> get_Color(This,retval)

#define IAsdkSquareWrapper_put_Color(This,noname,retval)    \
    (This)->lpVtbl -> put_Color(This,noname,retval)

#define IAsdkSquareWrapper_get_Layer(This,retval)   \
    (This)->lpVtbl -> get_Layer(This,retval)

#define IAsdkSquareWrapper_put_Layer(This,noname,retval)    \
    (This)->lpVtbl -> put_Layer(This,noname,retval)

#define IAsdkSquareWrapper_get_Linetype(This,retval)    \
    (This)->lpVtbl -> get_Linetype(This,retval)

#define IAsdkSquareWrapper_put_Linetype(This,noname,retval) \
    (This)->lpVtbl -> put_Linetype(This,noname,retval)

#define IAsdkSquareWrapper_get_LinetypeScale(This,retval)   \
    (This)->lpVtbl -> get_LinetypeScale(This,retval)

#define IAsdkSquareWrapper_put_LinetypeScale(This,noname,retval)    \
    (This)->lpVtbl -> put_LinetypeScale(This,noname,retval)

#define IAsdkSquareWrapper_get_Visible(This,retval) \
    (This)->lpVtbl -> get_Visible(This,retval)

#define IAsdkSquareWrapper_put_Visible(This,noname,retval)  \
    (This)->lpVtbl -> put_Visible(This,noname,retval)

#define IAsdkSquareWrapper_ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)  \
    (This)->lpVtbl -> ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)

#define IAsdkSquareWrapper_ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)  \
    (This)->lpVtbl -> ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)

#define IAsdkSquareWrapper_Highlight(This,HighlightFlag,retval) \
    (This)->lpVtbl -> Highlight(This,HighlightFlag,retval)

#define IAsdkSquareWrapper_Copy(This,retval)    \
    (This)->lpVtbl -> Copy(This,retval)

#define IAsdkSquareWrapper_Move(This,FromPoint,ToPoint,retval)  \
    (This)->lpVtbl -> Move(This,FromPoint,ToPoint,retval)

#define IAsdkSquareWrapper_Rotate(This,BasePoint,RotationAngle,retval)  \
    (This)->lpVtbl -> Rotate(This,BasePoint,RotationAngle,retval)

#define IAsdkSquareWrapper_Rotate3D(This,Point1,Point2,RotationAngle,retval)    \
    (This)->lpVtbl -> Rotate3D(This,Point1,Point2,RotationAngle,retval)

#define IAsdkSquareWrapper_Mirror(This,Point1,Point2,retval)    \
    (This)->lpVtbl -> Mirror(This,Point1,Point2,retval)

#define IAsdkSquareWrapper_Mirror3D(This,Point1,Point2,point3,retval)   \
    (This)->lpVtbl -> Mirror3D(This,Point1,Point2,point3,retval)

#define IAsdkSquareWrapper_ScaleEntity(This,BasePoint,ScaleFactor,retval)   \
    (This)->lpVtbl -> ScaleEntity(This,BasePoint,ScaleFactor,retval)

#define IAsdkSquareWrapper_TransformBy(This,TransformationMatrix,retval)    \
    (This)->lpVtbl -> TransformBy(This,TransformationMatrix,retval)

#define IAsdkSquareWrapper_Update(This,retval)  \
    (This)->lpVtbl -> Update(This,retval)

#define IAsdkSquareWrapper_GetBoundingBox(This,MinPoint,MaxPoint,retval)    \
    (This)->lpVtbl -> GetBoundingBox(This,MinPoint,MaxPoint,retval)

#define IAsdkSquareWrapper_IntersectWith(This,IntersectObject,option,retval)    \
    (This)->lpVtbl -> IntersectWith(This,IntersectObject,option,retval)

#define IAsdkSquareWrapper_get_PlotStyleName(This,retval)   \
    (This)->lpVtbl -> get_PlotStyleName(This,retval)

#define IAsdkSquareWrapper_put_PlotStyleName(This,noname,retval)    \
    (This)->lpVtbl -> put_PlotStyleName(This,noname,retval)

#define IAsdkSquareWrapper_get_Lineweight(This,retval)  \
    (This)->lpVtbl -> get_Lineweight(This,retval)

#define IAsdkSquareWrapper_put_Lineweight(This,noname,retval)   \
    (This)->lpVtbl -> put_Lineweight(This,noname,retval)

#define IAsdkSquareWrapper_get_Hyperlinks(This,retval)  \
    (This)->lpVtbl -> get_Hyperlinks(This,retval)

#define IAsdkSquareWrapper_get_EntityName(This,retval)  \
    (This)->lpVtbl -> get_EntityName(This,retval)

#define IAsdkSquareWrapper_get_EntityType(This,retval)  \
    (This)->lpVtbl -> get_EntityType(This,retval)


#define IAsdkSquareWrapper_get_Number(This,pVal)    \
    (This)->lpVtbl -> get_Number(This,pVal)

#define IAsdkSquareWrapper_put_Number(This,newVal)  \
    (This)->lpVtbl -> put_Number(This,newVal)

#define IAsdkSquareWrapper_get_SquareSize(This,pVal)    \
    (This)->lpVtbl -> get_SquareSize(This,pVal)

#define IAsdkSquareWrapper_put_SquareSize(This,newVal)  \
    (This)->lpVtbl -> put_SquareSize(This,newVal)

#define IAsdkSquareWrapper_get_CenterPoint(This,pVal)   \
    (This)->lpVtbl -> get_CenterPoint(This,pVal)

#define IAsdkSquareWrapper_put_CenterPoint(This,newVal) \
    (This)->lpVtbl -> put_CenterPoint(This,newVal)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_Number_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_Number_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IAsdkSquareWrapper_put_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_SquareSize_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_SquareSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_SquareSize_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IAsdkSquareWrapper_put_SquareSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_get_CenterPoint_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IAsdkSquareWrapper_get_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAsdkSquareWrapper_put_CenterPoint_Proxy( 
    IAsdkSquareWrapper __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IAsdkSquareWrapper_put_CenterPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAsdkSquareWrapper_INTERFACE_DEFINED__ */


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
