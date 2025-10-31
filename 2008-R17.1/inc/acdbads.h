//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

int            acdbXdRoom (const ads_name ent, long *result);
int            acdbXdSize (const struct resbuf *rb, long *result);

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

