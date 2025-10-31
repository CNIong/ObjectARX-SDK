//
//  (C) Copyright 2003 by Autodesk, Inc.
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

#pragma once

#pragma pack (push, 8)

/* Define an error type for this package */
typedef enum {
    PATH_NOERR = 0,
    PATH_INVALID,        /* invalid pathname    */
    PATH_BADOP,          /* invalid operation for path type */
    PATH_REFUSED,        /* operation refused.  This    error code is
                           returned when an operation (other than
                           Empty) would leave an empty path. */
    PATH_ERR            /* catchall error code */
} PathErr;

typedef enum {
    NO_PATH = 0,        /* new pathname object, no data yet    */
    NEW_PATH,           /* the path doesn't represent an existing file/dir */
    WC_PATH,            /* the path represents a wildcard specification */
    FILE_PATH,          /* the path represents a file */
    DIR_PATH,           /* the path represents a directory */
    DEV_PATH,           /* the path represents a device (LPT1: etc.) */
} path_type;

// What kind of path?
enum path_category {
    DRIVE_TYPE,         // ie. "c:\\" drive letter, colon, single backslash.
    UNC_TYPE,           // ie. \\jackl\public. A double backslash machine name backslash share name
    ROOT_TYPE,          // ie. a single backslash.
    RELATIVE_TYPE       
};

#pragma pack (pop)

