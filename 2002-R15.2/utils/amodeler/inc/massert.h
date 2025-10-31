#ifndef AMODELER_INC_MASSERT_H
#define AMODELER_INC_MASSERT_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//
// CREATED BY:  Jiri Kripac                     January-1-1996
//
// DESCRIPTION:
//
// Our own assert function. We can set a break point inside the assertFunction
// so that the execution will stop just before the assertion kills the process 
// and we can investigate all variables at that point. We can also choose not 
// to kill the process at that time.
//
///////////////////////////////////////////////////////////////////////////////

AMODELER_NAMESPACE_BEGIN


#ifndef NDEBUG

#define MASSERT(x) AMODELER_NAMESPACE::assertFunction(x, __FILE__, __LINE__, #x)
#define FAIL       AMODELER_NAMESPACE::assertFunction(0, __FILE__, __LINE__, "FAIL")
#define TODO       AMODELER_NAMESPACE::assertFunction(0, __FILE__, __LINE__, "TODO")

#else

#define MASSERT(x)
#define FAIL
#define TODO

#endif


DllImpExp extern void assertFunction(int ex, char* file, int line, char* str = 0);


AMODELER_NAMESPACE_END
#endif






