//
// (C) Copyright 1991-2006 by Autodesk, Inc. 
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
