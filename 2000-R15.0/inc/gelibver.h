#ifndef AC_GELIBVERSION_H
#define AC_GELIBVERSION_H
//     
// (C) Copyright 1993-1997 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// This  file  contains  the  functionality for managing versions of 
// gelib.
//

#include "adesk.h"
#include "gedll.h"
#pragma pack (push, 8)

// Current image version.
//
#define IMAGE_MAJOR_VER          2
#define IMAGE_MINOR_VER          0
#define IMAGE_CORRECTIVE_VER     0
#define IMAGE_INTERNAL_VER       0

class 
#ifdef AC_GELIBVER_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeLibVersion {
public:
    // Constructors.
    //
    AcGeLibVersion();
    AcGeLibVersion(const AcGeLibVersion&);
    AcGeLibVersion(unsigned char major, unsigned char minor,
                   unsigned char corrective,
                   unsigned char internal_version);

    // Inquiry functions.
    //
    unsigned char     majorVersion        () const; 
    unsigned char     minorVersion        () const; 
    unsigned char     correctiveVersion   () const; 
    unsigned char     schemaVersion       () const;

    // Set functions.
    //
    AcGeLibVersion&     setMajorVersion        (unsigned char val); 
    AcGeLibVersion&     setMinorVersion        (unsigned char val); 
    AcGeLibVersion&     setCorrectiveVersion   (unsigned char val); 
    AcGeLibVersion&     setSchemaVersion       (unsigned char val);

    // Comparisons
    //
    Adesk::Boolean operator ==      (const AcGeLibVersion&) const; 
    Adesk::Boolean operator !=      (const AcGeLibVersion&) const; 
    Adesk::Boolean operator <       (const AcGeLibVersion&) const; 
    Adesk::Boolean operator <=      (const AcGeLibVersion&) const; 
    Adesk::Boolean operator >       (const AcGeLibVersion&) const; 
    Adesk::Boolean operator >=      (const AcGeLibVersion&) const;

    // Relased version objects.
    // gelib release 0 --- End of 1995.
    //
    static const AcGeLibVersion kRelease0_95;

    // gelib r14 release.
    //
    static const AcGeLibVersion kReleaseSed;

    // gelib r15 release.
    //
    static const AcGeLibVersion kReleaseTah;

private:
    unsigned char   mVersion[10];
};

#pragma pack (pop)
#endif
