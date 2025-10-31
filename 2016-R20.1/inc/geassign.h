//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
//     Useful macros for converting from various C-struct definitions
//     of points and vectors to their equivalent acgelib definitions.
//
//     This header file should ONLY be included in source files,
//     never headers as it is only intended to be an internal utility
//     for interfacing to old AutoCad C-code and other 3rd party libraries.

#ifndef AC_GEASSIGN_H
#define AC_GEASSIGN_H

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
