//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//  AcUniqueString.h
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _Ac_UniqueString_h_
#define _Ac_UniqueString_h_

#include <cstddef>
#include <cstdint>

// Return a unique identifier for the input string, to allow fast compares
// using hash values instead of strings.  This is a 64 bit hash on the input string
// Input null or null strings are treated as an empty string, both will return valid hashes
// for legacy, input strings are converted to lower case BUT ONLY ASCII CHARS ARE CONVERTED.
// Thus the only characters converted to lower case are 'A' - 'Z' NO OTHER CHARS ARE CONVERTED
// Note that this is now constexpr so providing a literal string is computed at compile time
class AcUniqueString
{
  public:
    typedef uint64_t value; // strongly type the return value

    static constexpr value Intern( const wchar_t *pws )
    {
        return (value)computeHash(pws);
    }

    // compile time predefined strings used in the AutoCAD graphics system.
    static constexpr const value drawing2D()          { return Intern(L"2D Drawing"); }
    static constexpr const value drawing3D()          { return Intern(L"3D Drawing"); }
    static constexpr const value drawing3D2()         { return Intern(L"3D Drawing2"); }
    static constexpr const value selection3D()        { return Intern(L"3D Selection"); }
    static constexpr const value rapidRTRendering3D() { return Intern(L"RapidRT Rendering"); }

  private:

    // computes 64 bit hash using FNV1a 64 bit.
    // literals will be converted at compile time!
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    // http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
    static constexpr uint64_t computeHash( const wchar_t *pws )
    {
        uint64_t hash = 14695981039346656037ULL; // 64 bit offset_basis
        if (pws && *pws)    // non null wide string
        {
            for (;*pws; pws++)
            {
                wchar_t ch = *pws;
                if ((ch >= 'A') && (ch <= 'Z')) // only convert ASCII upper case to lower case
                    ch += 'a' - 'A';    // ascii to lower case
                hash = fnv1a64char((uint8_t)(ch & 0xff), hash);          // low byte
                hash = fnv1a64char((uint8_t)((ch >> 8) & 0xff), hash );  // high byte
            }
        }
        return hash;
    }

    // FNV-1a hash function - combine the next byte
    static constexpr uint64_t fnv1a64char(uint8_t ch, uint64_t hash)
    {
        // 64 bit FNV_prime
        return (hash ^ ch) * 1099511628211ULL;
    }
};

#endif // !_Ac_UniqueString_h

