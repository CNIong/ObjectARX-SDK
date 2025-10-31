/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 28 12:27:27 2000
 */
/* Compiler settings for C:\ObjectARX 2000\Samples\Smiley\SmileyDbCom\SmileyDbCom.idl:
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

#ifndef __SmileyDbCom_h__
#define __SmileyDbCom_h__

#ifdef __cplusplus
extern "C"{
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


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __AsdkSmileyDbComLib_LIBRARY_DEFINED__
#define __AsdkSmileyDbComLib_LIBRARY_DEFINED__

/* library AsdkSmileyDbComLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AsdkSmileyDbComLib;

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
            /* [retval][out] */ double __RPC_FAR *r) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ double r) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Center( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Center( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Normal( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Normal( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesApart( 
            /* [retval][out] */ double __RPC_FAR *d) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesApart( 
            /* [in] */ double d) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesHeight( 
            /* [retval][out] */ double __RPC_FAR *h) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesHeight( 
            /* [in] */ double h) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EyesSize( 
            /* [retval][out] */ double __RPC_FAR *s) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EyesSize( 
            /* [in] */ double s) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthCenter( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthLeft( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthLeft( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthBottom( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthBottom( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouthRight( 
            /* [retval][out] */ VARIANT __RPC_FAR *pv) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouthRight( 
            /* [in] */ VARIANT var) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleRadius( 
            double r) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISmileyEntityVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ struct GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISmileyEntity __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ struct GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISmileyEntity __RPC_FAR * This,
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
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ObjectName )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXData )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR AppName,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *XDataType,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *XDataValue,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXData )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT XDataType,
            /* [in][idldescattr] */ VARIANT XDataValue,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ObjectID )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Database )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IAcadDatabase __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasExtensionDictionary )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BOOLEAN __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtensionDictionary )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IAcadDictionary __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OwnerID )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Document )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][hidden][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erase )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ ACAD_COLOR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_COLOR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Layer )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Layer )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Linetype )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Linetype )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LinetypeScale )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ ACAD_NOUNITS __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LinetypeScale )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_NOUNITS noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BOOLEAN __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BOOLEAN noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArrayPolar )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ signed INT NumberOfObjects,
            /* [in][idldescattr] */ double AngleToFill,
            /* [in][idldescattr] */ VARIANT CenterPoint,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArrayRectangular )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ signed INT NumberOfRows,
            /* [in][idldescattr] */ signed INT NumberOfColumns,
            /* [in][idldescattr] */ signed INT NumberOfLevels,
            /* [in][idldescattr] */ double DistBetweenRows,
            /* [in][idldescattr] */ double DistBetweenCols,
            /* [in][idldescattr] */ double DistBetweenLevels,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Highlight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BOOLEAN HighlightFlag,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT FromPoint,
            /* [in][idldescattr] */ VARIANT ToPoint,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate3D )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ double RotationAngle,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror3D )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT Point1,
            /* [in][idldescattr] */ VARIANT Point2,
            /* [in][idldescattr] */ VARIANT point3,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleEntity )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT BasePoint,
            /* [in][idldescattr] */ double ScaleFactor,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformBy )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ VARIANT TransformationMatrix,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBoundingBox )( 
            ISmileyEntity __RPC_FAR * This,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *MinPoint,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *MaxPoint,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntersectWith )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ IDispatch __RPC_FAR *IntersectObject,
            /* [in][idldescattr] */ enum AcExtendOption option,
            /* [retval][out] */ VARIANT __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PlotStyleName )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PlotStyleName )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lineweight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ ACAD_LWEIGHT __RPC_FAR *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Lineweight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in][idldescattr] */ ACAD_LWEIGHT noname,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ IAcadHyperlinks __RPC_FAR *__RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntityName )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntityType )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ signed long __RPC_FAR *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Radius )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *r);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Radius )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ double r);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Center )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Center )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Normal )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Normal )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EyesApart )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *d);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EyesApart )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ double d);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EyesHeight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *h);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EyesHeight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ double h);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EyesSize )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *s);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EyesSize )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ double s);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MouthCenter )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MouthLeft )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MouthLeft )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MouthBottom )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MouthBottom )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MouthRight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pv);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MouthRight )( 
            ISmileyEntity __RPC_FAR * This,
            /* [in] */ VARIANT var);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleRadius )( 
            ISmileyEntity __RPC_FAR * This,
            double r);
        
        END_INTERFACE
    } ISmileyEntityVtbl;

    interface ISmileyEntity
    {
        CONST_VTBL struct ISmileyEntityVtbl __RPC_FAR *lpVtbl;
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

#define ISmileyEntity_get_Color(This,retval)	\
    (This)->lpVtbl -> get_Color(This,retval)

#define ISmileyEntity_put_Color(This,noname,retval)	\
    (This)->lpVtbl -> put_Color(This,noname,retval)

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

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Radius_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *r);


void __RPC_STUB ISmileyEntity_get_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Radius_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ double r);


void __RPC_STUB ISmileyEntity_put_Radius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Center_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_Center_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Center_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_Center_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_Normal_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_Normal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_Normal_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_Normal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesApart_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *d);


void __RPC_STUB ISmileyEntity_get_EyesApart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesApart_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ double d);


void __RPC_STUB ISmileyEntity_put_EyesApart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesHeight_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *h);


void __RPC_STUB ISmileyEntity_get_EyesHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesHeight_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ double h);


void __RPC_STUB ISmileyEntity_put_EyesHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_EyesSize_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *s);


void __RPC_STUB ISmileyEntity_get_EyesSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_EyesSize_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ double s);


void __RPC_STUB ISmileyEntity_put_EyesSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthCenter_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_MouthCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthLeft_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_MouthLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthLeft_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthBottom_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_MouthBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthBottom_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthBottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_get_MouthRight_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pv);


void __RPC_STUB ISmileyEntity_get_MouthRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_put_MouthRight_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    /* [in] */ VARIANT var);


void __RPC_STUB ISmileyEntity_put_MouthRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISmileyEntity_ScaleRadius_Proxy( 
    ISmileyEntity __RPC_FAR * This,
    double r);


void __RPC_STUB ISmileyEntity_ScaleRadius_Stub(
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
#endif /* __AsdkSmileyDbComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
