///////////////////////////////////////////////////////////////////////////////
//
// (c) Autodesk, Inc. 2007-2008. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef OFFSET_INL
#define OFFSET_INL
#if  __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif

namespace Atil
{
// The methods of the Offset class have been inlined for performance.
// Refer to the Offset.h header file for documentation of the methods.
//
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset::Offset () : x(0), y(0)
{
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset::Offset ( int nX, int nY ) : x(nX), y(nY)
{
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset::~Offset ()
{
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline const Offset& Offset::set( Int32 nX, Int32 nY)
{
    x = nX; y = nY;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator=( const Offset& rhs )
{
    x = rhs.x; y = rhs.y;
    return *this;
}   
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset Offset::operator+( Int32 nOffset ) const
{
    return Offset( x + nOffset, y + nOffset );
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator+=( Int32 nOffset )
{
    x += nOffset; y += nOffset;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset Offset::operator-( Int32 nOffset ) const
{
    return Offset( x - nOffset, y - nOffset );
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator-=( Int32 nOffset )
{
    x -= nOffset; y -= nOffset;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset Offset::operator*( Int32 nValue ) const
{
    return Offset(x*nValue, y*nValue);
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator*=( Int32 nValue )
{
    x *= nValue; y *= nValue;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset Offset::operator+( const Offset& rhs ) const
{
    return Offset(x+rhs.x, y+rhs.y);
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator+=( const Offset& rhs )
{
    x += rhs.x; y += rhs.y;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset Offset::operator-( const Offset& rhs ) const
{
    return Offset(x-rhs.x, y-rhs.y);
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline Offset& Offset::operator-=( const Offset& rhs )
{
    x -= rhs.x; y -= rhs.y;
    return *this;
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline bool Offset::operator==( const Offset& rhs ) const
{
    return (x == rhs.x && y == rhs.y);
}
/// <summary>
/// This inlined method is defined in Offset.h. <see cref="Offset">
/// </summary>
///
inline bool Offset::operator!=( const Offset& rhs ) const
{
    return (x != rhs.x || y != rhs.y);
}

} //end of namespace
#if  __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif
