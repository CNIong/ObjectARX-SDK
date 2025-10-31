//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


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

