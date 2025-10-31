/*
   (C) Copyright 1999 by Autodesk, Inc. 
  
   Permission to use, copy, modify, and distribute this software in
   object code form for any purpose and without fee is hereby granted, 
   provided that the above copyright notice appears in all copies and 
   that both that copyright notice and the limited warranty and
   restricted rights notice below appear in all supporting 
   documentation.
  
   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
   UNINTERRUPTED OR ERROR FREE.
  
   Use, duplication, or disclosure by the U.S. Government is subject to 
   restrictions set forth in FAR 52.227-19 (Commercial Computer
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
   (Rights in Technical Data and Computer Software), as applicable.
  
  
*/
/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 23 01:38:47 2001
 */
/* Compiler settings for csp.idl:
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

#ifndef __csptypes_h__
#define __csptypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __CSPLib_LIBRARY_DEFINED__
#define __CSPLib_LIBRARY_DEFINED__

/* library CSPLib */
/* [helpstring][version][uuid] */ 

typedef /* [uuid] */ 
enum tagStatement
    {	kAsiTYPE_UNDEFINED	= 0,
	kAsiALLOC_CURSOR	= kAsiTYPE_UNDEFINED + 1,
	kAsiALLOC_STATEMENT	= kAsiALLOC_CURSOR + 1,
	kAsiALTER_DOMAIN	= kAsiALLOC_STATEMENT + 1,
	kAsiALTER_TABLE	= kAsiALTER_DOMAIN + 1,
	kAsiCREATE_ASSERTION	= kAsiALTER_TABLE + 1,
	kAsiCREATE_CATALOG	= kAsiCREATE_ASSERTION + 1,
	kAsiCREATE_CHARACTER_SET	= kAsiCREATE_CATALOG + 1,
	kAsiCREATE_COLLATION	= kAsiCREATE_CHARACTER_SET + 1,
	kAsiCREATE_DOMAIN	= kAsiCREATE_COLLATION + 1,
	kAsiCLOSE_CURSOR	= kAsiCREATE_DOMAIN + 1,
	kAsiCOMMIT	= kAsiCLOSE_CURSOR + 1,
	kAsiCONNECT	= kAsiCOMMIT + 1,
	kAsiCREATE_SCHEMA	= kAsiCONNECT + 1,
	kAsiCREATE_TABLE	= kAsiCREATE_SCHEMA + 1,
	kAsiCREATE_VIEW	= kAsiCREATE_TABLE + 1,
	kAsiCREATE_INDEX	= kAsiCREATE_VIEW + 1,
	kAsiCREATE_TRANSLATION	= kAsiCREATE_INDEX + 1,
	kAsiCURSOR	= kAsiCREATE_TRANSLATION + 1,
	kAsiDELETE_CURSOR	= kAsiCURSOR + 1,
	kAsiDELETE_WHERE	= kAsiDELETE_CURSOR + 1,
	kAsiDEALLOCATE_STATEMENT	= kAsiDELETE_WHERE + 1,
	kAsiDISCONNECT	= kAsiDEALLOCATE_STATEMENT + 1,
	kAsiDROP_ASSERTION	= kAsiDISCONNECT + 1,
	kAsiDROP_CATALOG	= kAsiDROP_ASSERTION + 1,
	kAsiDROP_CHARACTER_SET	= kAsiDROP_CATALOG + 1,
	kAsiDROP_COLLATION	= kAsiDROP_CHARACTER_SET + 1,
	kAsiDROP_DOMAIN	= kAsiDROP_COLLATION + 1,
	kAsiDROP_SCHEMA	= kAsiDROP_DOMAIN + 1,
	kAsiDROP_TABLE	= kAsiDROP_SCHEMA + 1,
	kAsiDROP_TRANSLATION	= kAsiDROP_TABLE + 1,
	kAsiDROP_VIEW	= kAsiDROP_TRANSLATION + 1,
	kAsiDROP_INDEX	= kAsiDROP_VIEW + 1,
	kAsiEXECUTE_IMMEDIATE	= kAsiDROP_INDEX + 1,
	kAsiEXECUTE	= kAsiEXECUTE_IMMEDIATE + 1,
	kAsiFETCH	= kAsiEXECUTE + 1,
	kAsiGRANT	= kAsiFETCH + 1,
	kAsiINSERT	= kAsiGRANT + 1,
	kAsiOPEN	= kAsiINSERT + 1,
	kAsiPREPARE	= kAsiOPEN + 1,
	kAsiREVOKE	= kAsiPREPARE + 1,
	kAsiROLLBACK	= kAsiREVOKE + 1,
	kAsiSELECT	= kAsiROLLBACK + 1,
	kAsiSET_CATALOG	= kAsiSELECT + 1,
	kAsiSET_SCHEMA	= kAsiSET_CATALOG + 1,
	kAsiSET_TIME_ZONE	= kAsiSET_SCHEMA + 1,
	kAsiSET_NAMES	= kAsiSET_TIME_ZONE + 1,
	kAsiSET_TRANSACTION	= kAsiSET_NAMES + 1,
	kAsiSET_CONSTRAINT	= kAsiSET_TRANSACTION + 1,
	kAsiSET_AUTHORIZATION	= kAsiSET_CONSTRAINT + 1,
	kAsiUPDATE_CURSOR	= kAsiSET_AUTHORIZATION + 1,
	kAsiUPDATE_WHERE	= kAsiUPDATE_CURSOR + 1
    }	EAsiStatement;


EXTERN_C const IID LIBID_CSPLib;
#endif /* __CSPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
