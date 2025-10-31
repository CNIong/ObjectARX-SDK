//
//  (C) Copyright 1992-2009 by Autodesk, Inc.  All rights reserved.
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

#ifndef   _ID_H
#define   _ID_H

/*              ID.H

    Define AutoCAD version numbers       

    !!! IMPORTANT !!! IMPORTANT !!! IMPORTANT !!!

        Text-filtering scripts process this file to extract the version
        information.  You should only change the values for the ACADV_*,
        ACADVFULL, and ACADVNUM macros.

        DO NOT MAKE OTHER CHANGES TO THIS FILE.

    The ACADV_* macros below have the following valid ranges. 
    They implement a specific naming convention (see R160BPLT1 for
    details).  Changing the naming convention will require changing
    IDVER.H, which depends on these ACADV_* values.
    (The ranges that include letters are case-sensitive.)

    !!! All numbers need to be expressed as decimal numbers.
        Not octal, 03, and not hexadecimal, 0x03.

    ACADV_RELMAJOR  a nonnegative number, e.g., 13, 14, 15.
    ACADV_RELMINOR  0 .. 9
    
    ACADV_BLDSTREAM A .. Z
    ACADV_BLDMAJOR  0 .. 9 .. 99
    ACADV_BLDMINOR  0 .. 9 .. 99
    

 */

#define ACADV_RELMAJOR  18 /*ReleaseMajor*/
#define ACADV_RELMINOR  0  /*ReleaseMinor*/

#define ACADV_BLDSTREAM D   /*BuildStream*/
#define ACADV_BLDMAJOR  55   /*BuildMajor*/
#define ACADV_BLDMINOR  0   /*BuildMinor*/
#define ACADV_BLDBRANCH 0   //BuildBranch


/* The ASM_ values below should be updated whenever we get a new ASM drop.
   Check the File Version and Product Version on any asm dll. */
#define ASM_FILE_RELMAJOR  215
#define ASM_FILE_RELMINOR  0
#define ASM_FILE_RELPOINT  0
#define ASM_FILE_RELPATCH  4214
#define ASM_PROD_RELMAJOR  215
#define ASM_PROD_RELMINOR  0
#define ASM_PROD_RELPOINT  0
#define ASM_PROD_RELPATCH  4214
#endif /* _ID_H */
