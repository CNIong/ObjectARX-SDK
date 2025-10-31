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
//

#ifndef ARXDBG_ACADSTR_H
#define ARXDBG_ACADSTR_H


struct AcadVar {
    static const TCHAR* adserr;
    static const TCHAR* cmdecho;
    static const TCHAR* cvport;
    static const TCHAR* filedia;
    static const TCHAR* snapang;
    static const TCHAR* viewdir;
    static const TCHAR* viewsize;
};

struct AcadString {
    static const TCHAR* continuous;      // needs to be translated
    static const TCHAR* bylayer;         // needs to be translated
    static const TCHAR* byblock;         // needs to be translated
    static const TCHAR* zero;            // default layer
    static const TCHAR* wcAll;           // wild card for all
    static const TCHAR* nullStr;         // ""
    static const TCHAR* openBrace;       // "{"
    static const TCHAR* endBrace;        // "}"
    static const TCHAR* standard;        // STANDARD
    static const TCHAR* none;            // *NONE*
    static const TCHAR* varies1;         // *VARIES*
    static const TCHAR* varies2;         // VARIES
};

struct AcadFile {
    static const TCHAR* ltypesStandard;  // "acad.lin"
    static const TCHAR* ltypesComplex;   // "ltypeshp.lin"
};

#endif    // ARXDBG_ACADSTR_H

