#ifndef _adsdef_h
#define _adsdef_h 1
//
// (C) Copyright 1994-2007 by Autodesk, Inc. 
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
#include "AdAChar.h"

#define TRUE    1
#define FALSE   0
#ifndef EOS
#define EOS     ACRX_T('\0')
#endif

#pragma pack(push, 8)

typedef double   ads_real;
typedef ads_real ads_point[3];
#ifndef _WIN64
// We don't use Adesk::IntPtr here because this file is included
// by .c files, and they can't handle the adesk.h header.
typedef __w64 long ads_name[2];
typedef __w64 long *ads_namep;
#else
typedef __int64 ads_name[2];
typedef __int64 *ads_namep;
#endif
typedef ads_real ads_matrix[4][4];

/* When you want something that's explicitly a pointer type and not an array
   type, use ads_pointp and ads_namep.  Remember that if your function takes an
   *array* of points, it still declares ads_point[] foo; */
typedef ads_real *ads_pointp;

/* To protect macro-redefinition of the X, Y, Z, and T enumerated
   constants by legacy #define's, we remove their definition. */

#ifdef X
#undef X
#endif
#ifdef Y
#undef Y
#endif
#ifdef Z
#undef Z
#endif
#ifdef T
#undef T
#endif

#ifndef _XYZT_DEFINED
#define _XYZT_DEFINED
enum { X = 0, Y = 1, Z = 2 }; /* The coordinates of a point. */
enum { T = 3 };               /* The translation vector of a 3D matrix */
#endif // !_XYZT_DEFINED

/* The PAUSE token for ads_command and ads_cmd
 */
#define PAUSE ACRX_T("\\")

/* The ADS_INITGET control bits
 */

enum {
    RSG_NONULL      = 0x01,  // Disallow null input 
    RSG_NOZERO      = 0x02,  // Disallow zero input 
    RSG_NONEG       = 0x04,  // Disallow negative input
    RSG_NOLIM       = 0x08,  // Do not check limits
    RSG_GETZ        = 0x10,  // Get Z coordinate
    RSG_DASH        = 0x20,  // Draw dashed rubber band/box
                             // (not a GEDIT control bit)
    RSG_2D          = 0x40,  // Restrict (getdist) to 2D (causes the
                             // UD_GETZ control bit to be cleared)
    RSG_OTHER       = 0x80,  // Return input string if unknown 
    RSG_DDISTFIRST  = 0x100, // Give DD entry precedence over arbitrary input
    RSG_TRACKUCS    = 0x200, // Allow UCS tracking for faces 
                             // (causes the UD_TRACKUCS control bit to be set)
    RSG_NOORTHOZ    = 0x400, // Disables polar/ortho tracking in the Z direction 
                             // (causes the UD_NOORTHOZ control bit to be set)
    RSG_NOOSNAP     = 0x800  // Disables object snaps
};

/* The following control bits are the old names for the RSG_
   control bits above.  These names are provided for
   backward compatibility.  You should use the RSG_ names
   above.
 */

enum {
    INP_NNULL   = RSG_NONULL,
    INP_NZERO   = RSG_NOZERO,
    INP_NNEG    = RSG_NONEG,
    INP_NLIM    = RSG_NOLIM,
    INP_DASH    = RSG_DASH,
    INP_NZCOORD = RSG_2D
};

enum SelectorType {
    SELECT_TYPE_FREE = 0,
    SELECT_TYPE_PICK,
    SELECT_TYPE_WPOLY,
    SELECT_TYPE_CPOLY,
    SELECT_TYPE_FENCE,
    SELECT_TYPE_SUBENTITY,
    SELECT_TYPE_BAG,
    SELECT_TYPE_LAST,
    SELECT_TYPE_LEAF,
    SELECT_TYPE_GROUP,
    SELECT_TYPE_PASTE,
    SELECT_TYPE_HATCHASC,
    SELECT_TYPE_NRVP,
    SELECT_TYPE_OCCLASS
};

/* Binary data stream structure
 */

struct ads_binary {    // Binary data chunk structure
    short clen;        // length of chunk in bytes (change to int?)
    // Unicode: leaving as char * for now, so that clients doing pointer
    // arithmetic with it will continue to work.  But it really should be 
    // a void *.
    char *buf;         // binary data
};

/*  Union for storing different ADS data types.
 */
 
union ads_u_val {
    ads_real rreal;
    ads_real rpoint[3];
    short rint;
    ACHAR *rstring;
#ifndef _WIN64
    __w64 long  rlname[2];
    __w64 long  mnLongPtr;  // use this instead of rlong for pointers
#else
    __int64     rlname[2];
    __int64     mnLongPtr;  // use this instead of rlong for pointers
#endif
    long rlong;             // a 32-bit integer value
    __int64     mnInt64;    // a 64-bit integer value
    struct ads_binary rbinary;
/* TEMPORARY probably, for internal use only at the moment */
    // Unicode: leave as unsigned char for now
    unsigned char ihandle[8];
}; 
 
/* The following is the structure definition of the general result buffer.
   This is used for both passing back results from functions, as well
   as exotic applications like entity lists, and command function lists.
   It is as close as we come to the AutoLISP node structure.
 */
struct resbuf {                                                  
        struct resbuf *rbnext; // Allows them to be "linked"
        short restype;
        union ads_u_val resval;
};

typedef struct resbuf *pResbuf;
typedef const struct resbuf *kpResbuf;  // for declarations

#pragma pack(pop)

#endif
