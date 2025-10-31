//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Mar 25 13:33:55 2005
 */
/* Compiler settings for .\SmileyDbCom.idl:
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

#ifndef __SmileyDbCom_h__
#define __SmileyDbCom_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISmileyEntity_FWD_DEFINED__
#define __ISmileyEntity_FWD_DEFINED__
typedef interface ISmileyEntity ISmileyEntity;
#endif 	/* __ISmileyEntity_FWD_DEFINED__ */


#ifndef __SmileyEntity_FWD_DEFINED__
#define __SmileyEntity_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmileyEntity SmileyEntity;
#else
typedef struct SmileyEntity SmileyEntity;
#endif /* __cplusplus */

#endif 	/* __SmileyEntity_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __SmileyDb_LIBRARY_DEFINED__
#define __SmileyDb_LIBRARY_DEFINED__

/* library SmileyDb */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SmileyDb;

#ifndef __ISmileyEntity_INTERFACE_DEFINED__
#define __ISmileyEntity_INTERFACE_DEFINED__

/* interface ISmileyEntity */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISmileyEntity;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("066DA2A2-CC00-11D2-B585-0010A401A37F")
    ISmileyEntity : public IAcadEntity
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ double *r) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ double r) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Center( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Center( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Normal( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Normal( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesApart( 
            /* [retval][out] */ double *d) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesApart( 
            /* [in] */ double d) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesHeight( 
            /* [retval][out] */ double *h) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesHeight( 
            /* [in] */ double h) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesSize( 
            /* [retval][out] */ double *s) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesSize( 
            /* [in] */ double s) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthCenter( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthLeft( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthLeft( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthBottom( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthBottom( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthRight( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthRight( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleRadius( 
            double r) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundColor( 
            /* [retval][out] */ VARIANT *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundColor( 
            /* [in] */ VARIANT var) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISmileyEntityVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ISmileyEntity * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ISmileyEntity * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISmileyEntity * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISmileyEntity * This,
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
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectName )( 
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetXData )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BSTR AppName,
            /* [out][idldescattr] */ VARIANT *XDataType,
            /* [out][idldescattr] */ VARIANT *XDataValue,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *SetXData )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT XDataType,
            /* [in][idldescattr] */ VARIANT XDataValue,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            ISmileyEntity * This,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectID )( 
            ISmileyEntity * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ISmileyEntity * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            ISmileyEntity * This,
            /* [retval][out] */ IAcadDatabase **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_HasExtensionDictionary )( 
            ISmileyEntity * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetExtensionDictionary )( 
            ISmileyEntity * This,
            /* [retval][out] */ IAcadDictionary **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_OwnerID )( 
            ISmileyEntity * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            ISmileyEntity * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Erase )( 
            ISmileyEntity * This,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_TrueColor )( 
            ISmileyEntity * This,
            /* [retval][out] */ IAcadAcCmColor **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_TrueColor )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ IAcadAcCmColor *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Layer )( 
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Layer )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Linetype )( 
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Linetype )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_LinetypeScale )( 
            ISmileyEntity * This,
            /* [retval][out] */ ACAD_NOUNITS *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_LinetypeScale )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ ACAD_NOUNITS noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            ISmileyEntity * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BOOLEAN noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ArrayPolar )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ signed INT NumberOfObjects,
            /* [in][idldescattr] */ double AngleToFill,
            /* [in][idldescattr] */ VARIANT CenterPoint,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ArrayRectangular )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ signed INT NumberOfRows,
            /* [in][idldescattr] */ signed INT NumberOfColumns,
            /* [in][idldescattr] */ signed INT NumberOfLevels,
            /* [in][idldescattr] */ double DistBetweenRows,
            /* [in][idldescattr] */ double DistBetweenCols,
            /* [in][idldescattr] */ double DistBetweenLevels,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Highlight )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BOOLEAN HighlightFlag,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Copy )( 
            ISmileyEntity * This,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT FromPoint,
            /* [in][idldescattr] */ VARIANT ToPoint,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Rotate3D )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Mirror )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Mirror3D )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ VARIANT point3,
            /* [retval][out] */ IDispatch **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ScaleEntity )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double ScaleFactor,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *TransformBy )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ VARIANT TransformationMatrix,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            ISmileyEntity * This,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingBox )( 
            ISmileyEntity * This,
            /* [out][idldescattr] */ VARIANT *MinPoint,
            /* [out][idldescattr] */ VARIANT *MaxPoint,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IntersectWith )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ IDispatch *IntersectObject,
            /* [in][idldescattr] */ enum AcExtendOption option,
            /* [retval][out] */ VARIANT *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_PlotStyleName )( 
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_PlotStyleName )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Lineweight )( 
            ISmileyEntity * This,
            /* [retval][out] */ ACAD_LWEIGHT *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Lineweight )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ ACAD_LWEIGHT noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Hyperlinks )( 
            ISmileyEntity * This,
            /* [retval][out] */ IAcadHyperlinks **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_EntityName )( 
            ISmileyEntity * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_EntityType )( 
            ISmileyEntity * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_color )( 
            ISmileyEntity * This,
            /* [retval][out] */ ACAD_COLOR *retval);
        
        /* [id][propput][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_color )( 
            ISmileyEntity * This,
            /* [in][idldescattr] */ ACAD_COLOR noname,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            ISmileyEntity * This,
            /* [retval][out] */ double *r);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            ISmileyEntity * This,
            /* [in] */ double r);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Center )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Center )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Normal )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Normal )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EyesApart )( 
            ISmileyEntity * This,
            /* [retval][out] */ double *d);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EyesApart )( 
            ISmileyEntity * This,
            /* [in] */ double d);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EyesHeight )( 
            ISmileyEntity * This,
            /* [retval][out] */ double *h);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EyesHeight )( 
            ISmileyEntity * This,
            /* [in] */ double h);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EyesSize )( 
            ISmileyEntity * This,
            /* [retval][out] */ double *s);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EyesSize )( 
            ISmileyEntity * This,
            /* [in] */ double s);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouthCenter )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouthLeft )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouthLeft )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouthBottom )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouthBottom )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouthRight )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouthRight )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleRadius )( 
            ISmileyEntity * This,
            double r);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackgroundColor )( 
            ISmileyEntity * This,
            /* [retval][out] */ VARIANT *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackgroundColor )( 
            ISmileyEntity * This,
            /* [in] */ VARIANT var);
        
        END_INTERFACE
    } ISmileyEntityVtbl;

    interface ISmileyEntity
    {
        CONST_VTBL struct ISmileyEntityVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISmileyEntity_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ISmileyEntity_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ISmileyEntity_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ISmileyEntity_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ISmileyEntity_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ISmileyEntity_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ISmileyEntity_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ISmileyEntity_get_Handle(This,retval)	\
    (This)->lpVtbl -> get_Handle(This,retval)

#define ISmileyEntity_get_ObjectName(This,retval)	\
    (This)->lpVtbl -> get_ObjectName(This,retval)

#define ISmileyEntity_GetXData(This,AppName,XDataType,XDataValue,retval)	\
    (This)->lpVtbl -> GetXData(This,AppName,XDataType,XDataValue,retval)

#define ISmileyEntity_SetXData(This,XDataType,XDataValue,retval)	\
    (This)->lpVtbl -> SetXData(This,XDataType,XDataValue,retval)

#define ISmileyEntity_Delete(This,retval)	\
    (This)->lpVtbl -> Delete(This,retval)

#define ISmileyEntity_get_ObjectID(This,retval)	\
    (This)->lpVtbl -> get_ObjectID(This,retval)

#define ISmileyEntity_get_Application(This,retval)	\
    (This)->lpVtbl -> get_Application(This,retval)

#define ISmileyEntity_get_Database(This,retval)	\
    (This)->lpVtbl -> get_Database(This,retval)

#define ISmileyEntity_get_HasExtensionDictionary(This,retval)	\
    (This)->lpVtbl -> get_HasExtensionDictionary(This,retval)

#define ISmileyEntity_GetExtensionDictionary(This,retval)	\
    (This)->lpVtbl -> GetExtensionDictionary(This,retval)

#define ISmileyEntity_get_OwnerID(This,retval)	\
    (This)->lpVtbl -> get_OwnerID(This,retval)

#define ISmileyEntity_get_Document(This,retval)	\
    (This)->lpVtbl -> get_Document(This,retval)

#define ISmileyEntity_Erase(This,retval)	\
    (This)->lpVtbl -> Erase(This,retval)

#define ISmileyEntity_get_TrueColor(This,retval)	\
    (This)->lpVtbl -> get_TrueColor(This,retval)

#define ISmileyEntity_put_TrueColor(This,noname,retval)	\
    (This)->lpVtbl -> put_TrueColor(This,noname,retval)

#define ISmileyEntity_get_Layer(This,retval)	\
    (This)->lpVtbl -> get_Layer(This,retval)

#define ISmileyEntity_put_Layer(This,noname,retval)	\
    (This)->lpVtbl -> put_Layer(This,noname,retval)

#define ISmileyEntity_get_Linetype(This,retval)	\
    (This)->lpVtbl -> get_Linetype(This,retval)

#define ISmileyEntity_put_Linetype(This,noname,retval)	\
    (This)->lpVtbl -> put_Linetype(This,noname,retval)

#define ISmileyEntity_get_LinetypeScale(This,retval)	\
    (This)->lpVtbl -> get_LinetypeScale(This,retval)

#define ISmileyEntity_put_LinetypeScale(This,noname,retval)	\
    (This)->lpVtbl -> put_LinetypeScale(This,noname,retval)

#define ISmileyEntity_get_Visible(This,retval)	\
    (This)->lpVtbl -> get_Visible(This,retval)

#define ISmileyEntity_put_Visible(This,noname,retval)	\
    (This)->lpVtbl -> put_Visible(This,noname,retval)

#define ISmileyEntity_ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)	\
    (This)->lpVtbl -> ArrayPolar(This,NumberOfObjects,AngleToFill,CenterPoint,retval)

#define ISmileyEntity_ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)	\
    (This)->lpVtbl -> ArrayRectangular(This,NumberOfRows,NumberOfColumns,NumberOfLevels,DistBetweenRows,DistBetweenCols,DistBetweenLevels,retval)

#define ISmileyEntity_Highlight(This,HighlightFlag,retval)	\
    (This)->lpVtbl -> Highlight(This,HighlightFlag,retval)

#define ISmileyEntity_Copy(This,retval)	\
    (This)->lpVtbl -> Copy(This,retval)

#define ISmileyEntity_Move(This,FromPoint,ToPoint,retval)	\
    (This)->lpVtbl -> Move(This,FromPoint,ToPoint,retval)

#define ISmileyEntity_Rotate(This,BasePoint,RotationAngle,retval)	\
    (This)->lpVtbl -> Rotate(This,BasePoint,RotationAngle,retval)

#define ISmileyEntity_Rotate3D(This,Point1,Point2,RotationAngle,retval)	\
    (This)->lpVtbl -> Rotate3D(This,Point1,Point2,RotationAngle,retval)

#define ISmileyEntity_Mirror(This,Point1,Point2,retval)	\
    (This)->lpVtbl -> Mirror(This,Point1,Point2,retval)

#define ISmileyEntity_Mirror3D(This,Point1,Point2,point3,retval)	\
    (This)->lpVtbl -> Mirror3D(This,Point1,Point2,point3,retval)

#define ISmileyEntity_ScaleEntity(This,BasePoint,ScaleFactor,retval)	\
    (This)->lpVtbl -> ScaleEntity(This,BasePoint,ScaleFactor,retval)

#define ISmileyEntity_TransformBy(This,TransformationMatrix,retval)	\
    (This)->lpVtbl -> TransformBy(This,TransformationMatrix,retval)

#define ISmileyEntity_Update(This,retval)	\
    (This)->lpVtbl -> Update(This,retval)

#define ISmileyEntity_GetBoundingBox(This,MinPoint,MaxPoint,retval)	\
    (This)->lpVtbl -> GetBoundingBox(This,MinPoint,MaxPoint,retval)

#define ISmileyEntity_IntersectWith(This,IntersectObject,option,retval)	\
    (This)->lpVtbl -> IntersectWith(This,IntersectObject,option,retval)

#define ISmileyEntity_get_PlotStyleName(This,retval)	\
    (This)->lpVtbl -> get_PlotStyleName(This,retval)

#define ISmileyEntity_put_PlotStyleName(This,noname,retval)	\
    (This)->lpVtbl -> put_PlotStyleName(This,noname,retval)

#define ISmileyEntity_get_Lineweight(This,retval)	\
    (This)->lpVtbl -> get_Lineweight(This,retval)

#define ISmileyEntity_put_Lineweight(This,noname,retval)	\
    (This)->lpVtbl -> put_Lineweight(This,noname,retval)

#define ISmileyEntity_get_Hyperlinks(This,retval)	\
    (This)->lpVtbl -> get_Hyperlinks(This,retval)

#define ISmileyEntity_get_EntityName(This,retval)	\
    (This)->lpVtbl -> get_EntityName(This,retval)

#define ISmileyEntity_get_EntityType(This,retval)	\
    (This)->lpVtbl -> get_EntityType(This,retval)

#define ISmileyEntity_get_color(This,retval)	\
    (This)->lpVtbl -> get_color(This,retval)

#define ISmileyEntity_put_color(This,noname,retval)	\
    (This)->lpVtbl -> put_color(This,noname,retval)


#define ISmileyEntity_get_Radius(This,r)	\
    (This)->lpVtbl -> get_Radius(This,r)

#define ISmileyEntity_put_Radius(This,r)	\
    (This)->lpVtbl -> put_Radius(This,r)

#define ISmileyEntity_get_Center(This,pv)	\
    (This)->lpVtbl -> get_Center(This,pv)

#define ISmileyEntity_put_Center(This,var)	\
    (This)->lpVtbl -> put_Center(This,var)

#define ISmileyEntity_get_Normal(This,pv)	\
    (This)->lpVtbl -> get_Normal(This,pv)

#define ISmileyEntity_put_Normal(This,var)	\
    (This)->lpVtbl -> put_Normal(This,var)

#define ISmileyEntity_get_EyesApart(This,d)	\
    (This)->lpVtbl -> get_EyesApart(This,d)

#define ISmileyEntity_put_EyesApart(This,d)	\
    (This)->lpVtbl -> put_EyesApart(This,d)

#define ISmileyEntity_get_EyesHeight(This,h)	\
    (This)->lpVtbl -> get_EyesHeight(This,h)

#define ISmileyEntity_put_EyesHeight(This,h)	\
    (This)->lpVtbl -> put_EyesHeight(This,h)

#define ISmileyEntity_get_EyesSize(This,s)	\
    (This)->lpVtbl -> get_EyesSize(This,s)

#define ISmileyEntity_put_EyesSize(This,s)	\
    (This)->lpVtbl -> put_EyesSize(This,s)

#define ISmileyEntity_get_MouthCenter(This,pv)	\
    (This)->lpVtbl -> get_MouthCenter(This,pv)

#define ISmileyEntity_get_MouthLeft(This,pv)	\
    (This)->lpVtbl -> get_MouthLeft(This,pv)

#define ISmileyEntity_put_MouthLeft(This,var)	\
    (This)->lpVtbl -> put_MouthLeft(This,var)

#define ISmileyEntity_get_MouthBottom(This,pv)	\
    (This)->lpVtbl -> get_MouthBottom(This,pv)

#define ISmileyEntity_put_MouthBottom(This,var)	\
    (This)->lpVtbl -> put_MouthBottom(This,var)

#define ISmileyEntity_get_MouthRight(This,pv)	\
    (This)->lpVtbl -> get_MouthRight(This,pv)

#define ISmileyEntity_put_MouthRight(This,var)	\
    (This)->lpVtbl -> put_MouthRight(This,var)

#define ISmileyEntity_ScaleRadius(This,r)	\
    (This)->lpVtbl -> ScaleRadius(This,r)

#define ISmileyEntity_get_BackgroundColor(This,pv)	\
    (This)->lpVtbl -> get_BackgroundColor(This,pv)

#define ISmileyEntity_put_BackgroundColor(This,var)	\
    (This)->lpVtbl -> put_BackgroundColor(This,var)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Radius_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ double *r);


void __RPC_STUB ISmileyEntity_get_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Radius_Proxy( 
    ISmileyEntity * This,
    /* [in] */ double r);


void __RPC_STUB ISmileyEntity_put_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Center_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_Center_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Center_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_Center_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Normal_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_Normal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Normal_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_Normal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesApart_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ double *d);


void __RPC_STUB ISmileyEntity_get_EyesApart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesApart_Proxy( 
    ISmileyEntity * This,
    /* [in] */ double d);


void __RPC_STUB ISmileyEntity_put_EyesApart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesHeight_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ double *h);


void __RPC_STUB ISmileyEntity_get_EyesHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesHeight_Proxy( 
    ISmileyEntity * This,
    /* [in] */ double h);


void __RPC_STUB ISmileyEntity_put_EyesHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesSize_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ double *s);


void __RPC_STUB ISmileyEntity_get_EyesSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesSize_Proxy( 
    ISmileyEntity * This,
    /* [in] */ double s);


void __RPC_STUB ISmileyEntity_put_EyesSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthCenter_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_MouthCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthLeft_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_MouthLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthLeft_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthBottom_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_MouthBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthBottom_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthRight_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_MouthRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthRight_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_ScaleRadius_Proxy( 
    ISmileyEntity * This,
    double r);


void __RPC_STUB ISmileyEntity_ScaleRadius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_BackgroundColor_Proxy( 
    ISmileyEntity * This,
    /* [retval][out] */ VARIANT *pv);


void __RPC_STUB ISmileyEntity_get_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_BackgroundColor_Proxy( 
    ISmileyEntity * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_BackgroundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISmileyEntity_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SmileyEntity;

#ifdef __cplusplus

class DECLSPEC_UUID("46765BA4-C4CD-11D2-B579-0010A401A3C5")
SmileyEntity;
#endif
#endif /* __SmileyDb_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


