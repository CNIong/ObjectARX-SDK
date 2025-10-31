//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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

