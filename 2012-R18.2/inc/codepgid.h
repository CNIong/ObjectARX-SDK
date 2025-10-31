#ifndef _CODEPGID_H
#define _CODEPGID_H
//
//
// (C) Copyright 2007-2008 by Autodesk, Inc.
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

#pragma pack (push, 8)

/* This list contains identifiers for all of the code pages used with
   AutoCAD.  You can add entries (before the CODE_PAGE_CNT item), but
   don't ever delete one.
*/
typedef enum {
    CODE_PAGE_UNDEFINED = 0,
    CODE_PAGE_ASCII,
    CODE_PAGE_8859_1,
    CODE_PAGE_8859_2,
    CODE_PAGE_8859_3,
    CODE_PAGE_8859_4,
    CODE_PAGE_8859_5,
    CODE_PAGE_8859_6,
    CODE_PAGE_8859_7,
    CODE_PAGE_8859_8,
    CODE_PAGE_8859_9,
    CODE_PAGE_DOS437,
    CODE_PAGE_DOS850,
    CODE_PAGE_DOS852,
    CODE_PAGE_DOS855,
    CODE_PAGE_DOS857,
    CODE_PAGE_DOS860,
    CODE_PAGE_DOS861,
    CODE_PAGE_DOS863,
    CODE_PAGE_DOS864,
    CODE_PAGE_DOS865,
    CODE_PAGE_DOS869,
    CODE_PAGE_DOS932,
    CODE_PAGE_MACINTOSH,
    CODE_PAGE_BIG5,
    CODE_PAGE_KSC5601,
    CODE_PAGE_JOHAB,
    CODE_PAGE_DOS866,
    CODE_PAGE_ANSI_1250,
    CODE_PAGE_ANSI_1251,
    CODE_PAGE_ANSI_1252,
    CODE_PAGE_GB2312,
    CODE_PAGE_ANSI_1253,
    CODE_PAGE_ANSI_1254,
    CODE_PAGE_ANSI_1255,
    CODE_PAGE_ANSI_1256,
    CODE_PAGE_ANSI_1257,
    CODE_PAGE_ANSI_874,
    CODE_PAGE_ANSI_932,
    CODE_PAGE_ANSI_936,
    CODE_PAGE_ANSI_949,
    CODE_PAGE_ANSI_950,
    CODE_PAGE_ANSI_1361,
    CODE_PAGE_ANSI_1200,
    CODE_PAGE_ANSI_1258,
    CODE_PAGE_CNT
} code_page_id;

#pragma pack (pop)

inline bool
isValidCodePageId(code_page_id value)
{
    return ((int)value >= 0) && ((int)value < CODE_PAGE_CNT);
}

#endif // CODEPGID_H_
