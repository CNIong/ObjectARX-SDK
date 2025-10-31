//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _acdbads_h
#define _acdbads_h 1

#include "adsdef.h"

#include "acmem.h"
#include "AdAChar.h"

#pragma pack (push, 8)

// Note: some day we may drop .c support and remove extern "C"
#ifdef __cplusplus
extern "C" {
#endif
void           acdbFail (const ACHAR *str);

#ifdef __LP64__
int            acdbXdRoom (const ads_name ent, int *result);
int            acdbXdSize (const struct resbuf *rb, int *result);
#else
int            acdbXdRoom (const ads_name ent, long *result);
int            acdbXdSize (const struct resbuf *rb, long *result);
#endif

int            acdbHandEnt (const ACHAR *handle, ads_name entres);

/* Function to save a string ensuring no buffer overflow if, */
/* when converted, characters expand to \U+ sequences */
ACHAR *        acdbXStrSave (ACHAR *pSource, ACHAR **pDest);

/* Function to uppercase a table name */
int            acdbXStrCase (ACHAR *str);
#ifdef __cplusplus
}
#endif

/* Define macros to copy them.  NOTE that the result is the SECOND argument,
   consistent with ADS usage.  The standard C ones require <string.h> */
#ifdef __STDC__
#define acdbNameSet(from, to)  (memcpy(to, from, sizeof(ads_name)))
#define acdbPointSet(from,to)  (memcpy(to, from, sizeof(ads_point)))
#else
#define acdbNameSet(from, to)  (*(to)= *(from), (to)[1]=(from)[1])
#define acdbPointSet(from, to) (*(to)= *(from), (to)[1]=(from)[1], (to)[2]=(from)[2])
#endif  /* !__STDC__ */

/* Define null value for ads_names.  These values are NOT guaranteed valid;
   that is, there is no actual guarantee (such as C gives with NULL) that the
   system will never under any circumstances generate the values as valid data.
   The correct values will be created as part of the Lisp reinitialization
   project, if we go through with that one, and will then be inserted here.
   */
#define acdbNameClear(name)    name[0] = name[1] = 0
#define acdbNameNil(name)      (name[0] == 0 && name[1] == 0)
#define acdbNameEqual(name1, name2)  (name1[0]==name2[0] \
                                       && name1[1]==name2[1])
#pragma pack (pop)

#endif // !acdbads.h

