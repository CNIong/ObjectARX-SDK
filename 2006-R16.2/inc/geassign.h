#ifndef AC_GEASSIGN_H
#define AC_GEASSIGN_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
//     Useful macros for converting from various C-struct definitions
//     of points and vectors to their equivalent acgelib definitions.
//
//     This header file should ONLY be included in source files,
//     never headers as it is only intended to be an internal utility
//     for interfacing to old AutoCad C-code and other 3rd party libraries.
#pragma pack (push, 8)
class AcGePoint2d;
class AcGeVector2d;
class AcGePoint3d;
class AcGeVector3d;

inline AcGePoint2d&
asPnt2d(const double* pnt)
{
    return *((AcGePoint2d*)pnt);
}

inline AcGeVector2d&
asVec2d(const double* vec)
{
    return *((AcGeVector2d*)vec);
}

inline double*
asDblArray(const AcGePoint2d& pnt)
{
    return (double*)&pnt;
}

inline double*
asDblArray(const AcGeVector2d& vec)
{
    return (double*)&vec;
}

inline AcGePoint3d&
asPnt3d(const double* pnt)
{
    return *((AcGePoint3d*)pnt);
}

inline AcGeVector3d&
asVec3d(const double* vec)
{
    return *((AcGeVector3d*)vec);
}

inline double*
asDblArray(const AcGePoint3d& pnt)
{
    return (double*)&pnt;
}

inline double*
asDblArray(const AcGeVector3d& vec)
{
    return (double*)&vec;
}

#pragma pack (pop)
#endif
