//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//   Name: asisys.h                                   ast_asi_inc_ddk_asisys_h
//
//   Description:  Header file for AutoCAD SQL Interface.
//                 Common utility functions.

#ifndef ASI_ASISYS_H
#define ASI_ASISYS_H asisysh

/***************************************************************************/
/* INCLUDES */
/***************************************************************************/

#include <tchar.h>

/***************************************************************************/
/* DEFINES */
/***************************************************************************/

#ifdef BUILD_DBCONNECT
#pragma warning(error:4700)
// TODO: As part of VC7 warning cleanup work, submission V076-nm1.txt
// changed project settings for all .vcproj files in the autocad
// build tree. Doing this for AST generated the following two
// warnings which were treated as errors. Since this submission was
// made late in the RedDeer game, it was decided to keep the 
// changes minimal. So, for time being these two warnings are being
// with pragmas. This has to be re-visited for Neo and the pragmas
// will have to be removed.
#pragma warning(disable:4290)
#pragma warning(disable:4297)
#endif

#ifdef DLL_EXPORT
#define DLLScope __declspec( dllexport )
#else
#define DLLScope __declspec( dllimport )
#endif

#ifdef DBINITCONSTANTS
#define GLOBAL_(type, name, val) 	type name = val
#else
#define GLOBAL_(type, name, val)	extern type name
#endif

#ifndef  MAX
# define MIN(a,b)  ( (a) < (b) ? (a) : (b) )
# define MAX(a,b)  ( (a) > (b) ? (a) : (b) )
#endif

#ifndef NUMELEM
# define NUMELEM(x) (sizeof(x)/sizeof(*x))
#endif


// Error processing macros

#define RETURN_IF_FAILED(hr)  {			\
	HRESULT			tmpHr;				\
	tmpHr = (hr);					 	\
	if(FAILED((tmpHr))) return tmpHr;	\
	}

#define THROW_IF_FAILED(hr) {			\
	HRESULT			tmpHr;				\
	tmpHr = (hr);					 	\
	if(FAILED((tmpHr))) throw (tmpHr);	\
	}



/***************************************************************************/
/* FUNCTION PROTOTYPES */
/***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#pragma pack (push, 8)
/* Memory functions */
DLLScope long   AsiObjectsInUse (void);
DLLScope void * AsiMemoryMalloc (size_t);
DLLScope void   AsiMemoryFree (void*);
DLLScope void * AsiMemoryRealloc (void*,size_t);
DLLScope void * AsiMemoryAddMsg (void*,const TCHAR *);
#pragma pack (pop)
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ASI_ASISYS_H */
/*EOF*/
