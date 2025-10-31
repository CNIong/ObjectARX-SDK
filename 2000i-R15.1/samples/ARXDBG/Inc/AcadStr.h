//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
    static const char* adserr;
    static const char* cmdecho;
    static const char* cvport;
    static const char* filedia;
    static const char* snapang;
    static const char* viewdir;
    static const char* viewsize;
};

struct AcadString {
    static const char* continuous;        // needs to be translated
    static const char* bylayer;            // needs to be translated
    static const char* byblock;            // needs to be translated
    static const char* zero;            // default layer
    static const char* wcAll;            // wild card for all
    static const char* nullStr;            // ""
    static const char* openBrace;        // "{"
    static const char* endBrace;        // "}"
    static const char* standard;        // STANDARD
    static const char* none;            // *NONE*
    static const char* varies1;            // *VARIES*
    static const char* varies2;            // VARIES
};

struct AcadFile {
    static const char* ltypesStandard;    // "acad.lin"
    static const char* ltypesComplex;    // "ltypeshp.lin"
};

#endif    // ARXDBG_ACADSTR_H

