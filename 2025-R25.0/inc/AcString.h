//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//  AcString.h
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _Ac_String_h_
#define _Ac_String_h_

#include "acbasedefs.h"
#include "adesk.h"
#include "AcHeapOpers.h"
#include "AdAChar.h"
#include <cstddef>    // offsetof
#include <cstdarg>    // va_list
#include <cctype>     // std::tolower, std::toupper
#include <cwctype>    // std::iswspace
#include <string>     // std::wstring
#include <functional> // std::hash

// string_view is C++17+
#if (__cplusplus >= 201703L)  // vault is still using C++14, so C++17+ features have to check
    #if (__cplusplus < 202002L)  // prior to c++20 use ciso646
        #include <ciso646>
    #else
        #include <version>      // c++20 and later use version
    #endif
    #include <string_view>
#endif

#define AcStringSSO   // do not remove or undefine this - used by unit tests

#define AcStringMBCS    // define this to enable methods that support const char *

class AcDbHandle;
class AcRxResourceInstance;

// Notes:
// 1. All wchar_t arguments are assumed to be "widechar" Unicode values.
// 2. Short strings are saved directly into the class using small object optimization.
// 3. All ref-counting was removed, allowing AcString to be used in threads much more safely
// 4. The pointer returned from utf8Ptr() is now saved and has a long lifespan but it is not
//    updated as the string is modified. Users should use it as before - consider it invalid
//    after any modification - but the long life span will help prevent user lifetime bugs.
//    This storage is around until destructor, setEmpty(), or copy assignment.
//    Move constructor or assignment will move the utf8ptr storage to the new container.
// 5. Never cast away const from a pointer returned in order to modify the buffer directly.
//    If you must modify the contents, use GetBuffer/ReleaseBuffer or make a copy.
// 6. Legacy has utf8Ptr() as a const member function however internally it must modify internal data
//    It is the only method that is const that modifies internal data.
// 7. c_str() is the preferred method to get a pointer to the null term string. All other
//    methods are just wrappers to c_str() for legacy purposes. It will never return a nullptr.
// 8. All index values (also known as position values) are 0-based.  For example, in
//    the string "abcd", the 'c' character has position 2
//    Note that for performance, some methods in release mode do not check for valid ranges.
//    This is similar to std::wstring. Non-prod has full range checking.
// 9. Input wchar_t * or char * can be nullstr or point to empty string - both are considered
//    an empty string.
//10. An internal private assert system is used avoiding any conflict with assert/ASSERT

// private assert ensures no conflict with other assert systems
#if !defined(NDEBUG)
#define AcStrASSERT(x) (void)((!!(x)) || (AcString::iASSERTMsg( ACRX_T(#x), ACRX_T(__FILE__), __LINE__)))
#else
#define AcStrASSERT(x)
#endif

//#define AcStrLogging      // for developer use only define to enable private logging system
#if defined(AcStrLogging)
#define AcStrLOG(...)    AcString::iLogMsg iMsg( __VA_ARGS__ )
#define AcStrLOGADD(...) iMsg.addDMsg(__VA_ARGS__)
#else
#define AcStrLOG(...)
#define AcStrLOGADD(...) 
#endif

// if defined this will insert a const string at beginning of class to help catch passing by value to variadic functions like wprintf
// On windows the string is L"!!!"  On other platforms it is L"!" since they are 4 byte/char and we only reserve 8 bytes for this.
// Do not have different settings between prod and non-prod since some TD utilities are non-prod in a prod environment and we must
// have identical memory layout.
// make sure to disable prior to Beta.
//#define AcStringBADSTRDebug

class AcString : public AcHeapOperators
{
  public:
    /// <summary>Types of narrow char encoding supported.</summary>
    enum Encoding {
        /// <summary>Unicode utf-8 encoding.</summary>
        Utf8
    };

    //
    // Constructors and destructor
    //
    /// <summary>Default ctor, initializes to empty string.</summary>
    AcString() : m_empty(0) // sets nullstr bytes and m_len to 0
    {
        m_buffer = nullptr; // m_ssoBuff[0] = 0; but faster than word write
    #if !defined(NDEBUG)  // debug mode init all data to pass code analysis. In prod we only need the above init
        for (int i = 0; i < m_ssoSize;m_ssoBuff[i++] = 0);
    #endif
    #ifdef AcStringBADSTRDebug
        // doing it this way so works with vault C++14
        for (int i = 0; i < (sizeof(m_badstr)/sizeof(wchar_t))-1; m_badstr[i++] = '!');
        m_badstr[(sizeof(m_badstr)/sizeof(wchar_t))-1] = 0; // null term string
    #endif
    }

    /// <summary>Initialize with a single Unicode character</summary>
    /// <param name="wch">input character</param>
    AcString(wchar_t wch) : AcString()
    {
        AcStrLOG(this,iLogMsg::dStr, L"AcString(wchar_t) : %d",wch);
        m_len = wch ? 1 : 0;          // single char string in sso mode
        m_ssoBuff[0] = wch;
        m_ssoBuff[1] = 0;
    }

    /// <summary>Initialize to empty by passing nullptr
    /// <param name="nullptr">Only value allowed.</param>
    /// <remarks>Same as the default constructor</remarks>
    AcString(std::nullptr_t) : AcString()
    {
        AcStrLOG(this,0, L"AcString(std::nullptr_t) :");
    }

#ifdef AcStringMBCS
    /// <summary>Initialize from a narrow char string.</summary>
    /// <param name="psz">Input narrow string. Null terminated.</param>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString(const char *psz) : AcString( psz, Utf8 )
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const char *) : \"%hs\"",psz?psz:"(nullptr)");
    }
#endif

    /// <summary>Initialize from a narrow char string.</summary>
    /// <param name="psz">Input narrow string. Null terminated.</param>
    /// <param name="encoding"> Input string's encoding format.</param>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString(const char *psz, Encoding encoding) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning
        if (psz && *psz) // nullptr or empty string are empty string
        {
            UTF8converter wide((const Adesk::UInt8 *)psz, m_maxStrLen, *this );
            Adesk::UInt32 len = wide.getLen();
            initWithLen( wide.getBuff(), len, len );
        }
        AcStrASSERT(DBGverify());
    }

    /// <summary>Initialize from a narrow char.</summary>
    /// <param name="ch">Input character.</param>
    /// <param name="encoding"> Value is ignored.</param>
    /// <remarks>Used to work around legacy code that expected a single char to be
    /// automatically converted to a const char *.</remarks>
    AcString(char ch, Encoding ) : AcString( static_cast<wchar_t>(static_cast<Adesk::UInt8>(ch)) )
    {
    }
    
    /// <summary>Initialize from a narrow char string.</summary>
    /// <param name="psz">Input narrow string. Null terminated.</param>
    /// <param name="encoding">Input string's encoding format.</param>
    /// <param name="nByteCount">Number of input bytes from psz to use.</param>
    /// <remarks>Currently, only Utf8 encoding is supported.
    /// <remarks> psz is not required to be null terminated.
    ///           If bytecount causes last multi-byte utf8 char in psz to be
    ///           truncated, then the behavior is undefined.
    ///           This can be used to construct from std::string_view
    /// </remarks>
    AcString(const char *psz, Encoding encoding, Adesk::UInt32 nByteCount) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const char *, Encoding, Adesk::UInt32) : \"%hs\", %d, %d",psz?psz:"(nullptr)",(int)encoding,nByteCount);
        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning
        if (psz && *psz)   // nullptr or empty string are empty string
        {
            UTF8converter wide((const Adesk::UInt8 *)psz, nByteCount, *this );
            Adesk::UInt32 len = wide.getLen();
            initWithLen( wide.getBuff(), len, len );
        }
        AcStrASSERT(DBGverify());
    }

    /// <summary>Initialize from a Unicode string</summary>
    /// <param name="wpsz">input pointer to zero terminated source string</param>
    AcString(const wchar_t *pwsz) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        if (pwsz)   // not nullptr
        {
            Adesk::UInt32 len = cstrLen(pwsz);
            initWithLen( pwsz, len, len );
        }
        AcStrASSERT(DBGverify());
    }

    /// <summary>Initialize from a Unicode string</summary>
    /// <param name="wpsz">input pointer to source</param>
    /// <param name="count"> maximum number of characters to use from the input string</param>
    /// <remarks> Useful for constructing from a std::wstring_view.</remarks>
    AcString(const wchar_t *pwsz, Adesk::UInt32 count) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const wchar_t *, Adesk::UInt32) : \"%ls\", %d",pwsz?pwsz:L"(nullptr)",count);
        if (pwsz)  // not nullptr
        {
            Adesk::UInt32 len = cstrLen(pwsz,count);
            initWithLen( pwsz, len, len );
        }
        AcStrASSERT(DBGverify());
    }

    /// <summary>Copy constructor</summary>
    /// <param name="acs">input reference to an existing AcString object</param>
    AcString(const AcString & acs) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const AcString &) : \"%ls\"",acs.iGetBuff());
        AcStrASSERT(acs.DBGverify());
        // if acs is in getBuffer mode, we have to compute length
        Adesk::UInt32 len = acs.isGetBuffer() ? cstrLen(acs.iGetBuff()) : acs.iGetLen();
        initWithLen( acs.iGetBuff(), len, len );
        AcStrASSERT(DBGverify());
    }

    /// <summary>Move constructor</summary>
    /// <param name="acs">input reference to an existing temp AcString object.
    ///  source will be converted to empty, destination will contain all data
    ///  that source had including GetBuffer and utf8 data.</param>
    AcString(AcString && acs) noexcept : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(AcString &&) : \"%ls\"",acs.iGetBuff());
        AcStrASSERT(acs.DBGverify());
        AcStrASSERT(!acs.isGetBuffer());
        AcStrASSERT(!isSelf(acs));  // not possible to be yourself
        iMove( acs );
        AcStrASSERT(acs.isEmpty());
        AcStrASSERT(DBGverify());
    }

    enum eFormat
    {
        /// <summary>Values for the nCtorFlags arg of the following constructor.</summary>
        /// <summary>Format the arg as signed</summary>
        kSigned = 1,
        /// <summary>Format the arg as unsigned/summary>
        kUnSigned,
        /// <summary>Format the arg as unsigned hexadecimal</summary>
        kHex,
        /// <summary>Format the arg as signed hexadecimal</summary>
        kHexSigned
    };

    /// <summary>
    ///  convert input integer value into either a hex or decimal string
    /// </summary>
    /// <param name="nCtorFlags">input flags, indicating type of construction</param>
    /// <param name="nArg">Adesk::Int32, Adesk::UInt32, Adesk::Int64, Adesk::UInt64 input argument value</param>
    AcString(eFormat nCtorFlags, Adesk::Int32 nArg) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(eFormat, number) : %d, %d",(int)nCtorFlags, (int)nArg);
        Adesk::Int64 val = ((nCtorFlags == kUnSigned) || (nCtorFlags == kHex)) ? (Adesk::Int64)((Adesk::UInt32)nArg) : (Adesk::Int64)nArg; // up-convert based on input flags
        valToString valconvert( mapeFormat(nCtorFlags), val );
        Adesk::UInt32 len = valconvert.getLen();
        initWithLen( valconvert.getBuff(), len, len );
        AcStrASSERT(DBGverify());
    }
    AcString(eFormat nCtorFlags, Adesk::UInt32 nArg) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(eFormat, number) : %d, %d",(int)nCtorFlags, (int)nArg);
        Adesk::Int64 val = ((nCtorFlags == kUnSigned) || (nCtorFlags == kHex)) ? (Adesk::Int64)nArg : (Adesk::Int64)((Adesk::Int32)nArg); // up-convert based on input flags
        valToString valconvert( mapeFormat(nCtorFlags), val );
        Adesk::UInt32 len = valconvert.getLen();
        initWithLen( valconvert.getBuff(), len, len );
        AcStrASSERT(DBGverify());
    }
    AcString(eFormat nCtorFlags, Adesk::Int64 nArg) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(eFormat, number) : %d, %lld",(int)nCtorFlags, (int64_t)nArg);
        valToString valconvert( mapeFormat(nCtorFlags), nArg );
        Adesk::UInt32 len = valconvert.getLen();
        initWithLen( valconvert.getBuff(), len, len );
        AcStrASSERT(DBGverify());
    }
    AcString(eFormat nCtorFlags, Adesk::UInt64 nArg) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(eFormat, number) : %d, %lld",(int)nCtorFlags, (int64_t)nArg);
        valToString valconvert( mapeFormat(nCtorFlags), (Adesk::Int64)nArg );
        Adesk::UInt32 len = valconvert.getLen();
        initWithLen( valconvert.getBuff(), len, len );
        AcStrASSERT(DBGverify());
    }

    /// <summary>repeat a character n times.</summary>
    /// <param name="ch">character value</param>
    /// <param name="nRepeatTimes">repeat times</param>
    AcString(wchar_t ch, Adesk::UInt32 nRepeatTimes) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(wchar_t, Adesk::UInt32) : %d, %d",ch, nRepeatTimes);
        emptyReserve( nRepeatTimes );   // have room for this number of chars (will also leave room for null)
        wchar_t *p = iGetBuff();        // get the buffer
        for (Adesk::UInt32 i = 0; i < nRepeatTimes; p[i++] = ch );     // fill the values
        p[nRepeatTimes] = 0;              // null term
        iSetLen( ch ? nRepeatTimes: 0 );  // set length - check for null sent
        AcStrASSERT(DBGverify());
    }

    /// <summary>Formats an AcDbHandle value in hex, as in: "a2f".</summary>
    /// <param name="h">input reference to an acdb handle value</param>
    AcString(const AcDbHandle &h) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const AcDbHandle &h) :");
        valToString valconvert( kHowHex, convertHandleToU64( h ) );
        Adesk::UInt32 len = valconvert.getLen();
        initWithLen( valconvert.getBuff(), len, len );
        AcStrASSERT(DBGverify());
    }

    /// <summary>Load String from resource instance.</summary>
    /// <param name="hDll">AxResourceInstance object to load string</param>
    /// <param name="nId">input id of the string resource in the specified resource dll</param>
    AcString(const AcRxResourceInstance& hDll, Adesk::UInt32 nId) : AcString()
    {
        AcStrLOG(this, iLogMsg::dStr, L"AcString(const AcRxResourceInstance&, Adesk::UInt32) : %d",nId);
        loadString(hDll, nId);
        AcStrASSERT(DBGverify());
    }

    /// <summary>Destructor: releases memory used by the string.</summary>
    ~AcString()
    {
        AcStrLOG(this, iLogMsg::destructor, L"~AcString()");
        setEmpty();
    }

    //
    // Querying methods
    //

    /// <summary>Get the string as utf-8.</summary>
    /// <returns>A pointer to a null-terminated utf8 string.</returns>
    /// <remarks> The pointer is valid until setEmpty or move assignment.
    /// pointer is created during this call and not updated if the string changes.</remarks>
    const char * utf8Ptr() const
    {
        AcStrLOG(this, iLogMsg::dStr, L"utf8Ptr() :");
        const char *retval = const_cast<AcString *>(this)->iutf8Ptr();
        AcStrLOGADD(L"\"%hs\"",retval);
        return retval;
    }

    /// <summary>Get the string as utf-8.</summary>
    /// <returns>std::string with the utf8 string.</returns>
    std::string utf8Str() const
    {
        AcStrLOG(this, iLogMsg::dStr, L"utf8Ptr() :");
        std::string retval(const_cast<AcString *>(this)->iutf8Ptr());
        AcStrLOGADD(L"\"%hs\"",retval.c_str());
        return retval;
    }

    /// <summary>Get the string as widechar unicode.</summary>
    /// <returns>A pointer to a null-terminated widechar string.</returns>
    /// <remarks> The pointer is only valid until this object is next modified.</remarks>
    const wchar_t * c_str() const    // what std uses
    {
        return iGetBuff();
    }
    const wchar_t * kwszPtr() const  // legacy 
    {
        return c_str();
    }
    const wchar_t * constPtr() const // legacy
    {
        return c_str();
    }
    const wchar_t * kTCharPtr() const // legacy
    {
        return c_str();
    }
    const wchar_t * kACharPtr() const // legacy
    {
        return c_str();
    }

    /// <summary>Operator for casting this string to a widechar unicode string pointer.</summary>
    /// <returns>A pointer to a null terminated widechar string.</returns>
    /// <remarks>Pointer is valid only until this AcString is next modified.</remarks>
    operator const wchar_t * () const
    {
        return c_str();
    }

    /// <summary>Test whether this string is null, i.e. has logical length zero.</summary>
    /// <returns>True if the string is empty, else false.</returns>
    /// <remarks> if called during getBuffer mode, returns original unmodified empty status</remarks>
    bool isEmpty() const
    {
        bool retval = iGetLen() == 0;
        return retval;
    }

    /// <summary>Test whether this string is null, i.e. has logical length zero.</summary>
    /// <returns>True if the string is empty, else false.</returns>
    /// <remarks> if called during getBuffer mode, returns original unmodified empty status</remarks>
    bool empty() const
    {
        return isEmpty();
    }


    /// <summary>Get logical length of this string.</summary>
    /// <returns>The number of characters in the string. Zero if it's empty.</returns>
    /// <remarks>Null terminator is not counted in logical length.</remarks>
    /// <remarks> if called during getBuffer mode, returns original unmodified length</remarks>
    Adesk::UInt32 length() const
    {
        // we are not logging length, it is used by logging system
        Adesk::UInt32 retval = iGetLen();
        return retval;
    }

    /// <summary>Get logical length of this string.</summary>
    /// <returns>The number of characters in the string. Zero if it's empty.</returns>
    /// <remarks>This method is dDeprecated. Please use length() instead.
    /// if called during getBuffer mode, returns original unmodified length</remarks>
    Adesk::UInt32 tcharLength() const
    {
        return length();
    }

    /// <summary>Get the maximum logical length that this string can currently achieve
    //           without growing or reallocating its buffer.</summary>
    /// <returns>Number of characters the current buffer can hold.</returns>
    /// <remarks>Null terminator is not counted in logical length.</remarks>
    Adesk::UInt32 capacity() const
    {
        return isSSO() ? m_ssoSize-1 : m_allocated-1;
    }

    /// <summary>Grows buffer to match the requested capacity .</summary>
    /// <param name="nCapacity">Number of characters of space needed not including null terminator.</param>
    /// <returns>True if the buffer was re-allocated, else false.</returns>
    /// <remarks>Shrink requests are ignored.</remarks>
    bool reserve(Adesk::UInt32 nCapacity)
    {
        AcStrLOG(this, iLogMsg::dStr, L"reserve(Adesk::UInt32) : %d",nCapacity);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        bool retval = false;
        if (isSSO())
        {
            if (nCapacity >= m_ssoSize)
            {
                convertSSOtoBuffer( nCapacity );
                retval = true;
            }
        }
        else if (nCapacity >= m_allocated)
        {
            bufferResize( nCapacity );
            retval = true;
        }
        AcStrASSERT(DBGverify());
        return retval;  // not logging return value
    }

    /// <summary>Check if all characters are in the ascii range: 0x20..0x7f.</summary>
    /// <returns>True if all characters in the ASCII range, else false.</returns>
    /// <remarks>Codes 0x..0x1f are considered control characters and cause this method
    ///          to return false, for historical reasons.</remarks>
    bool isAscii() const
    {
        AcStrLOG(this, iLogMsg::dStr, L"isAscii() :");
        AcStrASSERT(DBGverify());
        bool retval = isAscii( iGetBuff(), (Adesk::UInt32)((Adesk::Int32)-1) ); // works in getBuffer mode
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Check if all characters are in the range 0x01 through 0x7f.</summary>
    /// <returns>True if all characters have their high bit (0x80) clear.</returns>
    /// <remarks>Codes in 0x01 through 0x7f tend to have the same meaning across
    ///          all encoding schemes (ansi code pages, utf-8, utf-16, etc.
    ///          Empty string returns true</remarks>
    bool is7Bit() const
    {
        AcStrLOG(this, iLogMsg::dStr, L"is7Bit() :");
        AcStrASSERT(DBGverify());
        bool retval = is7Bit( iGetBuff(), (Adesk::UInt32)((Adesk::Int32)-1) );  // works in getBuffer mode
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    //
    // Parsing methods.
    //

    /// <summary>Flag values specifying how to handle errors such as
    ///          invalid characters or overflow during string parsing.
    ///
    static constexpr Adesk::UInt32 kParseZero = 0;

    ///<summary>Return -1 or ffff.</summary>
    ///
    static constexpr Adesk::UInt32 kParseMinus1 = 0x01;

    ///<summary>Pop an assert in debug build.</summary>
    ///
    static constexpr Adesk::UInt32 kParseAssert = 0x02;

    ///<summary>Throw an int exception.</summary>
    ///
    static constexpr Adesk::UInt32 kParseExcept = 0x04;

    ///<summary>Treat empty string as error.</summary>
    ///
    static constexpr Adesk::UInt32 kParseNoEmpty = 0x08;

    ///<summary>Default error handling behavior.</summary>
    ///
    static constexpr Adesk::UInt32 kParseDefault = (kParseAssert | kParseZero);

    /// <summary>Parse the current string as decimal, return a signed int.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::Int32 asDeci(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asDeci(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::Int32 retval = (Adesk::Int32)parseVal( kHowSigned | kHowDeci, nFlags);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Parse the current string as hexadecimal, return a signed int.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::Int32 asHex(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asHex(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::Int32 retval = (Adesk::Int32)parseVal( kHowSigned | kHowHex, nFlags);
        AcStrLOGADD(L"%x",retval);
        return retval;
    }

    /// <summary>Parse the current string as decimal, return an Adesk::UInt32.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::UInt32 asUDeci(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asUDeci(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::UInt32 retval = (Adesk::UInt32)parseVal( kHowDeci, nFlags);
        AcStrLOGADD(L"%u",retval);
        return retval;
    }

    /// <summary>Parse the current string as hexadecimal, return an Adesk::UInt32.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::UInt32 asUHex(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asUHex(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::UInt32 retval = (Adesk::UInt32)parseVal( kHowHex, nFlags);
        AcStrLOGADD(L"%x",retval);
        return retval;
    }

    /// <summary>Parse the current string as decimal, return a signed int64.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::Int64 asDeci64(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asDeci64(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::Int64 retval = (Adesk::Int64)parseVal( kHowSigned | kHowDeci, nFlags);
        AcStrLOGADD(L"%lld",retval);
        return retval;
    }

    /// <summary>Parse the current string as hexadecimal, return a signed int64.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::Int64 asHex64(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asHex64(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::Int64 retval = (Adesk::Int64)parseVal( kHowSigned | kHowHex, nFlags);
        AcStrLOGADD(L"%llx",retval);
        return retval;
    }

    /// <summary>Parse the current string as decimal, return an unsigned int64.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    /// <remarks>Works during getBuffer mode.</remarks>
    Adesk::UInt64 asUDeci64(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asUDeci64(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::UInt64 retval = (Adesk::UInt64)parseVal( kHowDeci, nFlags);
        AcStrLOGADD(L"%llu",retval);
        return retval;
    }

    /// <summary>Parse the current string as hexadecimal, return an unsigned int64.</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The int value parsed from the string.</returns>
    Adesk::UInt64 asUHex64(Adesk::UInt32 nFlags = kParseDefault) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"asUHex64(Adesk::UInt32) : %d", nFlags);
        AcStrASSERT(DBGverify());

        Adesk::UInt64 retval = (Adesk::UInt64)parseVal( kHowHex, nFlags);
        AcStrLOGADD(L"%llx",retval);
        return retval;
    }

    /// <summary>Parse the current string as hexadecimal.  Return the handle..</summary>
    /// <param name="nFlags">input bits specifying how to do the parsing</param>
    /// <returns>The handle value parsed from the string.</returns>
    ACBASE_PORT AcDbHandle asAcDbHandle(Adesk::UInt32 nFlags = kParseDefault) const;
    
    //
    // Find methods:
    //   Search for a character, a substring or for any of a group of characters,
    //   or for any character not in the group.
    //   Search for first or last occurrence.
    //

    /// <summary>Find a single character in the string..</summary>
    /// <param name="ch">input character to search for</param>
    /// <returns>The position of the found character. -1 if not found.</returns>
    /// <remarks>The first character position is zero.</remarks>
    Adesk::Int32 find(ACHAR ch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"find(ACHAR ch) : %d", ch);
        Adesk::Int32 retval = find(ch, 0);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find a single character in the string.  </summary>
    /// <param name="ch">input character to search for</param>
    /// <param name="nStartPos">zero based first character position to look at</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    /// <remarks> invalid nStartPos will return -1 </remarks>
    Adesk::Int32 find(ACHAR ch, Adesk::Int32 nStartPos) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"find(ACHAR ch, Adesk::Int32) : %d, %d", ch, nStartPos);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::UInt32 len = iGetLen();
        const wchar_t *src = iGetBuff();
        Adesk::Int32 retval = -1;
        for (Adesk::UInt32 i = (Adesk::UInt32)nStartPos; i < len; i++) // handles neg values so they wont crash
        {
            if (src[i] == ch)
            {
                retval = (Adesk::Int32)i;
                break;
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find a substring in the string </summary>
    /// <param name="psz">input string to search for</param>
    /// <param name="nStartPos">zero first character position in this string to look at</param>
    /// <returns> The position of the found substring. -1 if not found.</returns>
    /// <remarks> invalid nStartPos will return -1
    /// legacy: passing in nullptr or empty string will return string length</remarks>
    Adesk::Int32 find(const ACHAR *pwsz, Adesk::Int32 nStartPos = 0) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"find(const ACHAR*, Adesk::Int32) : \"%ls\", %d", pwsz?pwsz:L"(nullptr)", nStartPos);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 len = (Adesk::Int32)iGetLen();
        Adesk::Int32 retval = len;
        if (pwsz && *pwsz)  // legacy, nullptr or empty returns len.
        {
            retval = -1;
            if ((Adesk::UInt32)nStartPos < (Adesk::UInt32)len)   // have input string and a non-negative start and not empty
            {
                Adesk::Int32 endlen = len - (Adesk::Int32)cstrLen(pwsz);       // last possible start index to match substr
                const wchar_t *src = iGetBuff();
                for (Adesk::Int32 i = nStartPos; i <= endlen; i++)
                {
                    if (isSubStr(src+i,pwsz))
                    {
                        retval = i;
                        break;
                    }
                }
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Find an AcString in the string..</summary>
    /// <param name="acs">input string object to search for
    /// <returns>The position of the found string, -1 if not found.</returns>
    /// <remarks> acs getBuffer mode supported </remarks>
    /// legacy: passing in empty string will return string length</remarks>
    Adesk::Int32 find(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"find(const AcString &) : \"%ls\"", acs.kwszPtr());
        Adesk::Int32 retval = find( acs.iGetBuff(), 0);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find a substring in the string, case-independently </summary>
    /// <param name="psz">input string to search for</param>
    /// <param name="nStartPos">first character position in this string to look at</param>
    /// <returns> The position of the found substring. -1 if not found.</returns>
    /// <remarks> invalid nStartPos will return -1
    /// legacy: passing in nullptr or empty string will return string length</remarks>
Adesk::Int32 findNoCase(const ACHAR *pwsz, Adesk::Int32 nStartPos = 0) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findNoCase(const ACHAR *, Adesk::Int32) : \"%hs\", %d",pwsz?pwsz:L"(nullptr)",nStartPos);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 len = (Adesk::Int32)iGetLen();
        Adesk::Int32 retval = len;
        if (pwsz && *pwsz)  // legacy, nullptr or empty returns len.
        {
            retval = -1;
            if (((Adesk::UInt32)nStartPos < (Adesk::UInt32)len))   // have input string and a non-negative start and not empty
            {
                Adesk::Int32 endlen = len - (Adesk::Int32)cstrLen(pwsz);       // last possible start index to match substr
                const wchar_t* src = iGetBuff();
                for (Adesk::Int32 i = nStartPos; i <= endlen; i++)
                {
                    if (isSubStrLC(src + i, pwsz))  // is substring ignoring case
                    {
                        retval = i;
                        break;
                    }
                }
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find first character in this string which matches any in a group of
    ///           input characters</summary>
    /// <param name="psz">input group of characters to search for</param>
    /// <param name="nStartPos">first character position in this string to look at</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    /// <remarks> If psz is nullptr, then we search for whitespace.</remarks>
    /// <remarks> invalid nStartPos will return -1 </remarks>
    Adesk::Int32 findOneOf(const ACHAR *pwsz, Adesk::Int32 nStartPos = 0) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findOneOf(const ACHAR *, Adesk::Int32) : \"%hs\", %d",pwsz?pwsz:L"(nullptr)",nStartPos);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::UInt32 len = iGetLen();
        Adesk::Int32 retval = -1;    
        if ((Adesk::UInt32)nStartPos <= (Adesk::UInt32)len)   // handles negative nStartPos and too big
        {
            const wchar_t * p = iGetBuff();
            if (pwsz)  // valid - not whitespace
            {
                if (*pwsz)  // something to find
                {
                    for (Adesk::UInt32 i = (Adesk::UInt32)nStartPos; i < len; i++)
                        if (isOneOf(p[i],pwsz))
                        {
                            retval = (Adesk::Int32)i;
                            break;
                        }
                }
            }
            else  // whitespace
            {
                for (Adesk::UInt32 i = (Adesk::UInt32)nStartPos; i < len; i++)
                    if (std::iswspace(p[i]))
                    {
                        retval = (Adesk::Int32)i;
                        break;
                    }
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find first character in this string which does not match any in a group
    ///           of input characters</summary>
    /// <param name="psz">input group of characters to search for</param>
    /// <param name="nStartPos">first character position to look at</param>
    /// <returns> The position of the "not found" character. -1 if all were found.</returns>
    /// <remarks> If psz is nullptr, then we search for not whitespace.</remarks>
    Adesk::Int32 findNoneOf(const ACHAR *pwsz, Adesk::Int32 nStartPos = 0) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findNoneOf(const ACHAR *, Adesk::Int32) : \"%hs\", %d",pwsz?pwsz:L"(nullptr)",nStartPos);
        AcStrASSERT( nStartPos >= 0 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::UInt32 len = iGetLen();
        Adesk::Int32 retval = -1;
        if ((Adesk::UInt32)nStartPos <= (Adesk::UInt32)len)   // handles negative nStartPos and too big
        {
            const wchar_t * p = iGetBuff();
            if (pwsz)  // valid - not whitespace
            {
                if (*pwsz)  // something to search for
                {
                    for (Adesk::UInt32 i = (Adesk::UInt32)nStartPos; i < len; i++)
                        if (!isOneOf(p[i],pwsz))
                        {
                            retval = (Adesk::Int32)i;
                            break;
                        }
                }
            }
            else  // whitespace
            {
                for (Adesk::UInt32 i = (Adesk::UInt32)nStartPos; i < len; i++)
                    if (!std::iswspace(p[i]))
                    {
                        retval = (Adesk::Int32)i;
                        break;
                    }
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }


    /// <summary> Find last occurrence of a character in the string</summary>
    /// <param name="ch">input character to search for</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    /// <remarks> This method is DEPRECATED. Please use findLast() instead.</remarks>
    Adesk::Int32 findRev(ACHAR ch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findRev(ACHAR) : %d", ch);
        Adesk::Int32 retval = findLast(ch);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last occurrence of a substring in the string</summary>
    /// <param name="psz">input substring to search for</param>
    /// <returns> The position of the found substring result. -1 if not found.</returns>
    /// <remarks> This method is DEPRECATED. Please use findLast() instead.</remarks>
    Adesk::Int32 findRev(const ACHAR *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findRev(const ACHAR *) : \"%hs\"",pwsz?pwsz:L"(nullptr)");
        Adesk::Int32 retval = findLast(pwsz);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last occurrence of a substring in the string</summary>
    /// <param name="acs">input substring to search for</param>
    /// <returns> The position of the found substring result. -1 if not found.</returns>
    /// <remarks> This method is DEPRECATED. Please use findLast() instead.</remarks>
    Adesk::Int32 findRev(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findRev(const AcString &) : \"%hs\"",acs.kwszPtr());
        Adesk::Int32 retval = findLast( acs.iGetBuff() );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last character in this string from a group of characters</summary>
    /// <param name="psz">input group of characters to match</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    /// <remarks> This method is DEPRECATED. Please use findLast() instead.</remarks>
    Adesk::Int32 findOneOfRev(const ACHAR *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findOneOfRev(const ACHAR *) : \"%hs\"",pwsz?pwsz:L"(nullptr)");
        Adesk::Int32 retval = findLastOneOf( pwsz );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last occurrence of a character in the string</summary>
    /// <param name="ch">input character to search for</param>
    /// <param name="nEndPos">Last character position to look at
    /// -1 to start at end of string</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    Adesk::Int32 findLast(ACHAR ch, Adesk::Int32 nEndPos = -1) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findLast(ACHAR, Adesk::Int32) : %d, %d", ch,nEndPos);
        wchar_t str[2] = { ch, 0 };
        Adesk::Int32 retval = findLast(str, nEndPos );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last occurrence of a substring in the string</summary>
    /// <param name="psz">input substring to search for</param>
    /// <param name="nEndPos">Last character position to look at
    /// -1 to start at end of string</param>
    /// <returns> The position of the found substring result. -1 if not found.
    /// legacy: if pwsz nullptr or empty return string length </returns>
    Adesk::Int32 findLast(const ACHAR *pwsz, Adesk::Int32 nEndPos = -1) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findLast(const ACHAR *, Adesk::Int32) : \"%ls\", %d", pwsz?pwsz:L"(nullptr)",nEndPos);
        AcStrASSERT( nEndPos >= -1 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 len = (Adesk::Int32)iGetLen();  // out length
        Adesk::Int32 retval = len;
        if (pwsz && *pwsz)   // have input string
        {
            retval = -1;
            Adesk::Int32 findLen = cstrLen(pwsz);         // length of what we are looking for
            if (nEndPos < 0)                        // if neg
                nEndPos = len-1;                    // start at end of string
            if ((len-findLen) < nEndPos)            // our length - find len is last possible match position
                nEndPos = len-findLen;              // use it to start search
            const wchar_t *src = iGetBuff();
            for (Adesk::Int32 i = nEndPos; i >= 0; i--)
            {
                if (isSubStr(src+i,pwsz))
                {
                    retval = i;
                    break;
                }
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last character in this string from a group of characters</summary>
    /// <param name="pwsz">input group of characters to match</param>
    /// <param name="nEndPos">Last character position to look at</param>
    /// <returns> The position of the found character. -1 if not found.</returns>
    /// <remarks> If pwsz is nullptr, then we search for whitespace.</remarks>
    Adesk::Int32 findLastOneOf(const ACHAR *pwsz, Adesk::Int32 nEndPos = -1) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findLastOneOf(const ACHAR *, Adesk::Int32) : \"%ls\", %d", pwsz?pwsz:L"(nullptr)",nEndPos);
        AcStrASSERT( nEndPos >= -1 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 len = iGetLen();
        if (nEndPos < 0)                    // neg, use last char
            nEndPos = len - 1;              // last char
        else if (nEndPos > (len-1))
            nEndPos = len-1;
        
        const wchar_t * p = iGetBuff();
        Adesk::Int32 retval = -1;
        if ((pwsz && *pwsz))  // valid - not whitespace
        {
            for (Adesk::Int32 i = nEndPos; i >= 0; i--)
                if (isOneOf(p[i],pwsz))
                {
                    retval = i;
                    break;
                }
        }
        else  // whitespace
        {
            for (Adesk::Int32 i = nEndPos; i >= 0; i--)
                if (std::iswspace(p[i]))
                {
                    retval = i;
                    break;
                }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Find last character in this string which does not match any in a group
    ///           of characters</summary>
    /// <param name="psz">input group of characters to search for</param>
    /// <param name="nEndPos">first character position to look at</param>
    /// <returns> The position of the "not found" character. -1 if all were found.</returns>
    /// <remarks> If psz is null, then we search for not whitespace.</remarks>
    Adesk::Int32 findLastNoneOf(const ACHAR *pwsz, Adesk::Int32 nEndPos = -1) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"findLastNoneOf(const ACHAR *, Adesk::Int32) : \"%ls\", %d", pwsz?pwsz:L"(nullptr)",nEndPos);
        AcStrASSERT( nEndPos >= -1 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 len = iGetLen();
        if (nEndPos < 0)                    // neg, use last char
            nEndPos = len - 1;              // last char
        else if (nEndPos > (len-1))
            nEndPos = len-1;
        
        const wchar_t * p = iGetBuff();
        Adesk::Int32 retval = -1;
        if ((pwsz && *pwsz))  // valid - not whitespace
        {
            for (Adesk::Int32 i = nEndPos; i >= 0; i--)
                if (!isOneOf(p[i],pwsz))
                {
                    retval = i;
                    break;
                }
        }
        else  // whitespace
        {
            for (Adesk::Int32 i = nEndPos; i >= 0; i--)
                if (!std::iswspace(p[i]))
                {
                    retval = i;
                    break;
                }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    //
    // Extraction methods
    // Note: mid() and substr() are the same thing - we define both
    //       for compatibility with CString and std::string
    //
    // The input index arguments are character indices into the string.

    /// <summary>Get substring from the a specified position to the string's end.</summary>
    /// <param name="nStart">The zero-based start position of the substring to get.</param>
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks> negative nStart is treated as 0</remarks>
    AcString mid(Adesk::Int32 nStart) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"mid(Adesk::Int32) : %d", nStart);
        AcString retval = mid(nStart,-1);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Get a substring from the string.  (same as substr() method).</summary>
    /// <param name="nStart">input index (in characters) from the start of the string</param>
    /// <param name="nNumChars">input maximum number of characters to retrieve.
    //              If nNumChars is -1, then return the rest of the string.</param>
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks> negative nStart is treated as 0.
    /// negative nNumChars is treated as -1 meaning rest of string</remarks>
    AcString mid(Adesk::Int32 nStart, Adesk::Int32 nNumChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"mid(Adesk::Int32, Adesk::Int32) : %d, %d", nStart, nNumChars);
        // don't assert on nStart negative, right can send neg and is counting on it being treated as 0.
        //AcStrASSERT( nNumChars >= -1 ); // can't assert, many subd tests (40106,40110,40111, 40112 and more) send neg down. Treat as -1
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        if (nStart < 0) nStart = 0;  // unit test fix

        AcString retval;      // start return with empty
        Adesk::UInt32 len = iGetLen();
        if ((Adesk::UInt32)nStart < len)    // valid start
        {
            // clamp length to be valid make sure to deal with overflow (neg nNumChars) by using 64 bit
            Adesk::UInt32 clen = ((Adesk::UInt64)nStart + (Adesk::UInt64)((Adesk::UInt32)nNumChars)) <= (Adesk::UInt64)len ?
                                    (Adesk::UInt32)nNumChars : len - (Adesk::UInt32)nStart;
            retval.initWithLen( iGetBuff() + nStart, clen, clen );
        }
        AcStrASSERT(retval.DBGverify());
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Get a substring from the start of string..</summary>
    /// <param name="nNumChars">input number of characters to retrieve.</param>
    //             if nNumChars is -1, then return entire string
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks>Negative numChars are treated as -1 and return a copy of the string</remarks>
    AcString substr(Adesk::Int32 numChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"substr(Adesk::Int32) : %d", numChars);
        AcString retval = mid( 0, numChars );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Get a substring from the string.  (same as mid() method).</summary>
    /// <param name="nStart">input 0-based index from the start of the string</param>
    /// <param name="nNumChars">input number of characters to retrieve.</param>
    //             if nNumChars is -1, then return the rest of the string
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks> negative nStart is treated as 0</remarks>
AcString substr(Adesk::Int32 nStart, Adesk::Int32 nNumChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"mid(Adesk::Int32, Adesk::Int32) : %d, %d", nStart, nNumChars);
        AcString retval = mid( nStart, nNumChars );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Get a substring from the end of string..</summary>
    /// <param name="nNumChars">input number of characters to retrieve.</param>
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks>Negative nNumChars returns empty string</remarks>
    AcString substrRev(Adesk::Int32 numChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"substrRev(Adesk::Int32) : %d", numChars);
        AcString retval = right( numChars );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>
    /// Return a nNumChars length substring from the start of string.
    /// </summary>
    /// <param name="nNumChars">The count of characters of the substring to get.</param>
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks>Negative nNumChars are treated as returning the entire string</remarks>
    AcString left(Adesk::Int32 nNumChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"left(Adesk::Int32) : %d", nNumChars);
        AcString retval;
        if (nNumChars < 0)  // if negative return the entire string.
            retval = *this;
        else
            retval = mid(0,nNumChars);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>
    /// Return a nNumChars length substring from the end of string.
    /// </summary>
    /// <param name="nNumChars">The count of characters of the substring to get.</param>
    /// <returns>An AcString consisting of the specified substring</returns>
    /// <remarks>Negative nNumChars returns empty string.
    /// if nNumChars >= string length, entire string returned</remarks>
    AcString right(Adesk::Int32 nNumChars) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"right(Adesk::Int32) : %d", nNumChars);
        AcString retval;    // unit test wants null with negative count
        if (nNumChars > 0)  // relying on mid treating negative nStart as 0
            retval = mid( (Adesk::Int32)iGetLen() - nNumChars, nNumChars );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    //
    // Assignment operators and methods
    //
    
    /// <summary>assign a Unicode character to the string.</summary>
    /// <param name="wch">input character to assign</param>
    /// <returns>A reference to this string object.</returns>
    AcString & assign(wchar_t wch)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(wchar_t) : %d", wch);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        wchar_t *p = iGetBuff();
        *p = wch;
        *(p+1) = 0;
        iSetLen(wch ? 1 : 0);
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign nullptr to a string, setting the string to empty.</summary>
    /// <param name="std::nullptr_t">only allowed value</param>
    /// <returns>A reference to this empty string object.</returns>
    AcString & assign(std::nullptr_t)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(std::nullptr_t");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        setEmpty();     // make empty
        return *this;
    }

#ifdef AcStringMBCS
    /// <summary>assign a string of Utf8 narrow chars to the string.</summary>
    /// <param name="psz">input pointer to the string of Utf8 chars to assign</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString & assign(const char *psz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const char *) : \"%hs\"", psz?psz:"(nullptr)");
        assign( psz, Utf8 );
        return *this;
    }
#endif

    /// <summary>assign a string of narrow chars to the string.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to assign</param>
    /// <param name="encoding"> input Encoding type</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString & assign(const char *psz, Encoding encoding)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const char *, Encoding) : \"%hs\", %d", psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning
        setNull();  // clear out but keep SSO/Buffer mode
        if (psz && *psz)
        {
            UTF8converter wide((const Adesk::UInt8 *)psz, m_maxStrLen, *this);
            copyWithLen( wide.getBuff(), wide.getLen());
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign a string of narrow chars to the string.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to assign</param>
    /// <param name="encoding"> input Encoding type</param>
    /// <param name="nLen"> input maximum length</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.
    /// This is useful from assigning from an std::string_view</remarks>
    AcString & assign(const char *psz, Encoding encoding, Adesk::UInt32 nLen)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const char *, Encoding, Adesk::UInt32) : \"%hs\", %d, %d", psz?psz:"(nullptr)",(int)encoding, nLen);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning
        setNull();  // clear out but keep SSO/Buffer mode
        if (psz && *psz)
        {
            UTF8converter wide((const Adesk::UInt8 *)psz, nLen, *this);
            copyWithLen( wide.getBuff(), wide.getLen());
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign a string of Unicode characters to the string.</summary>
    /// <param name="pwsz">input pointer to the string of characters to assign</param>
    /// <returns>A reference to this string object.</returns>
    AcString & assign(const wchar_t *pwsz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const wchar_t *) : \"%ls\"", pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        if (pwsz)
        {
            Adesk::UInt32 len = cstrLen(pwsz);
            if (isSelf(pwsz))            // self reference
            {
                //ACD-41122 full self assignment should be ignored keeping current buffer
                if ((len != iGetLen()) || (pwsz != iGetBuff())) // test for sub-string self assignment
                {
                    AcString temp;                       // partial self reference, use new string storage
                    temp.initWithLen( pwsz, len, len );  // make copy
                    setEmpty();                          // clear out
                    iMove( temp );                       // transfer ownership
                }
            }
            else
                copyWithLen( pwsz, len);      // no overlap, safe to copy
        }
        else
            setEmpty();
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign a string of Unicode characters to the string.</summary>
    /// <param name="pwsz">input pointer to the string of characters to assign</param>
    /// <param name="len">max input length of pwsz</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Useful to assign from std::wstring_view.</remarks>
    AcString & assign(const wchar_t *pwsz, Adesk::UInt32 len)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const wchar_t *, Adesk::UInt32) : \"%ls\", %d", pwsz?pwsz:L"(nullptr)",len);

        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        if (pwsz && len)   // we may be assigning ourself or a substring of ourself so do the assign but save data first
        {
            Adesk::UInt32 clen = cstrLen(pwsz,len);
            if (isSelf(pwsz))            // self reference (could be a manual substring so must process)
            {
                AcString temp;                    // in case of self reference
                temp.initWithLen( pwsz, clen, clen );   // make copy
                setEmpty();                       // clear out
                iMove( temp );                   // transfer ownership
            }
            else
                copyWithLen( pwsz, clen);
        }
        else // nothing to assign so clear out
            setEmpty();
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign an AcString object to the string.</summary>
    /// <param name="acs">input reference to the AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & assign(const AcString & acs)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const AcString &) : \"%ls\"", acs.kwszPtr());
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        if (!isSelf(acs))     // not self reference
        {
            const wchar_t *p = acs.iGetBuff();
            copyWithLen( p,
                         acs.isGetBuffer() ? cstrLen(p) : acs.iGetLen());
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>Move assign an AcString object to the string.</summary>
    /// <param name="acs">input reference to the movable AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & assign(AcString && acs) noexcept   // move assignment
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(AcString &&) : \"%ls\"", acs.kwszPtr());
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(!acs.isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        if (!isSelf(acs))
        {
            setEmpty();     // clear out
            iMove( acs );   // move the string
            AcStrASSERT(acs.isEmpty());
            AcStrASSERT(acs.DBGverify());
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign an AcDbHandle object to the string (format it as hex).</summary>
    /// <param name="h">input reference to the AcDbHandle object</param>
    /// <returns>A reference to this string object.</returns>
    AcString & assign(const AcDbHandle & h)
    {
        AcStrLOG(this, iLogMsg::dStr, L"assign(const AcDbHandle &) :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        valToString valconvert( kHowHex, convertHandleToU64(h));
        copyWithLen( valconvert.getBuff(), valconvert.getLen() );
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign a Unicode character to the string.</summary>
    /// <param name="wch">input character to assign</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator = (wchar_t wch)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (wchar_t) : %d",wch);
        assign( wch );
        return *this;
    }

    /// <summary>Initialize this AcString to empty.</summary>
    /// <param name="std::nullptr_t">only allowed value</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString& operator = (std::nullptr_t)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (std::nullptr_t) :");
        setEmpty();
        return *this;
    }

#ifdef AcStringMBCS
    /// <summary>assign a string of mbcs characters to the string.</summary>
    /// <param name="pwsz">input pointer to the string of characters to assign</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>The mbcs is treated as Utf8</remarks>
    AcString & operator = (const char *psz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        assign(psz, Utf8);
        return *this;
    }
#endif

    /// <summary>assign a string of Unicode characters to the string.</summary>
    /// <param name="pwsz">input pointer to the string of characters to assign</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator = (const wchar_t *pwsz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        assign(pwsz);
        return *this;
    }

    /// <summary>assign an AcString object to the string.</summary>
    /// <param name="acs">input reference to the AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator = (const AcString & acs)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (const AcString &) : \"%ls\"",acs.kwszPtr());
        assign( acs );
        return *this;
    }

    /// <summary>move a temp AcString object to the string.</summary>
    /// <param name="acs">input reference to the temp AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator = (AcString && acs) noexcept
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (AcString &&) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(!acs.isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        if (!isSelf(acs))   // ignore moving to ourself
        {
            setEmpty();     // clear out to empty
            iMove( acs );   // move from src
            AcStrASSERT(acs.DBGverify());
            AcStrASSERT(acs.isEmpty());
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>assign an AcDbHandle object to the string (format it as hex).</summary>
    /// <param name="h">input reference to the AcDbHandle object</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator = (const AcDbHandle & h)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator = (const AcDbHandle &) :");
        assign( h );
        return *this;
    }

    /// <summary>Set the string to be empty..</summary>
    /// <returns>A reference to this string object.</returns>
    AcString & setEmpty()
    {
        AcStrLOG(this, iLogMsg::dStr, L"setEmpty() :");
        if (!isSSO())
        {
            if (m_buffer)
                ::acHeapFree(nullptr, m_buffer);
            if (m_utf8)
                ::acHeapFree(nullptr, m_utf8);
        }
        m_empty = 0;   // sso mode, 0 length
        m_buffer = nullptr;  // m_ssoBuff[0] = 0; but faster than word write
        AcStrASSERT(DBGverify());
        AcStrASSERT(isEmpty());
        return *this;
    }

    /// <summary>Set the string from a resource string.</summary>
    /// <param name="hDll">AxResourceInstance object to load string</param>
    /// <param name="nId">input id of the string resource in the specified resource dll</param>
    /// <returns>bool. false if string failed, true if string loaded.</returns>
    ACBASE_PORT bool loadString(const AcRxResourceInstance& hDll, unsigned nId);

    /// <summary>Format the string using "printf" rules..</summary>
    /// <param name="pszFmt">input pointer to the printf format string</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>null format string will clear to empty</remarks>
    ACBASE_PORT AcString & format (const ACHAR    *pszFmt,  ...);

    /// <summary>Format the string using "printf" rules.</summary>
    /// <param name="pszFmt">input pointer to the printf format string</param>
    /// <param name="args">input variable args list, containing values to be formatted</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>null format string will clear to empty</remarks>
    ACBASE_PORT AcString & formatV(const ACHAR   *pszFmt,  va_list args);

    /// <summary>
    /// Append formatted data to this string using "printf" rules
    /// </summary>
    /// <param name="pszFmt">input pointer to the printf format string</param>
    /// <param name="args">input variable args list, containing values to be formatted</param>
    /// <returns> Reference to this AcString.</returns>
    ACBASE_PORT AcString & appendFormat(const ACHAR   *pszFmt, ...);

    //
    // Modifying operators and methods
    //

    /// <summary>append a Unicode character to the end of the string.</summary>
    /// <param name="wch">input character to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator += (wchar_t wch)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator += (wchar_t) : %d",wch);
        append(wch);
        return *this;
    }

    /// <summary>just returns itself unmodified</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator += (std::nullptr_t)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator += (std::nullptr_t) :");
        return *this;
    }

#ifdef AcStringMBCS
    /// <summary>append a Utf8 string to the end of the string.</summary>
    /// <param name="pwsz">input pointer to the Unicode string</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator += (const char * psz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator += (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        append( psz, Utf8 );
        return *this;
    }
#endif

    /// <summary>append a Unicode string to the end of the string.</summary>
    /// <param name="pwsz">input pointer to the Unicode string</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator += (const wchar_t * pwsz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator += (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        append( pwsz );
        return *this;
    }

    /// <summary>append an AcString object to the end of the string.</summary>
    /// <param name="acs">input reference to the AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & operator += (const AcString & acs)
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator += (const AcString &) : \"%ls\"",acs.kwszPtr());
        append( acs );
        return *this;
    }

    /// <summary>append a Unicode character to the end of the string.</summary>
    /// <param name="wch">input character to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString & append(wchar_t wch)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(wchar_t) : %d",wch);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        if (wch)
        {
            wchar_t buff[2] = { wch, 0 };
            iappend( buff, 1 );
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>returns itself.</summary>
    /// <param name="std::nullptr_t">only allowed value</param>
    /// <returns>A reference to this string object.</returns>
    AcString & append(std::nullptr_t)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        return *this;
    }

#ifdef AcStringMBCS
    /// <summary>append an Utf8 string to the end of the string.</summary>
    /// <param name="psz">input pointer to the Utf8 string</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString & append(const char *psz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(const char *) : \"%hs\"",psz?psz:"(nullptr)");
        append( psz, Utf8 );
        return *this;
    }
#endif
    /// <summary>append a char string to the end of the string.</summary>
    /// <param name="psz">input pointer to the narrow char string</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString & append(const char *psz, Encoding encoding)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning
        if (psz && *psz)
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this );
            iappend( wide.getBuff(), wide.getLen() );
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>append a Unicode string to the end of the string.</summary>
    /// <param name="pwsz">input pointer to the Unicode string</param>
    /// <returns>A reference to this string object.</returns>
    AcString & append(const wchar_t *pwsz)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        if (pwsz)
        {
            // it is possible that input is ourself or a substring of ourself.
            // if so we must make a copy in case we have to realloc
            if (isSelf(pwsz))
            {
                AcString temp( pwsz );      // make a copy
                iappend( temp.iGetBuff(), temp.iGetLen() ); // append the copy
            }
            else
                iappend( pwsz, cstrLen(pwsz)); // append the new space
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>append an AcString object to the end of the string.</summary>
    /// <param name="acs">input reference to the AcString</param>
    /// <returns>A reference to this string object.</returns>
    AcString & append(const AcString & acs)
    {
        AcStrLOG(this, iLogMsg::dStr, L"append(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        if (isSelf(acs))    // appending to ourselves, have to make a copy
        {
            AcString temp(acs);     // make copy (cannot be in getBuffer mode)
            iappend( temp.iGetBuff(), temp.iGetLen() );
        }
        else
        {
            const wchar_t *p = acs.iGetBuff();
            iappend( p, acs.isGetBuffer() ? cstrLen(p) : acs.iGetLen() );
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    // Catenation operators and methods  These are like append,
    // but they do not modify the current string.  They return a
    // new combined string.

    /// <summary>Copy the string and append a Unicode character to it.</summary>
    /// <param name="ch">input character to append to the string copy</param>
    /// <returns>A new string object</returns>
    AcString operator + (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator + (wchar_t) : %d",wch);
        AcString retval = concat(wch);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>return a copy of existing string</summary>
    /// <param name="nullptr">Only allowed value</param>
    /// <returns>A reference to this string object.</returns>
    AcString operator + (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator + (std::nullptr_t) :");
        AcString retval(*this);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Append Utf8 string to current string.</summary>
    /// <param name="psz">input pointer to Utf8 string to append</param>
    /// <returns>A a new string object.</returns>
    AcString operator + (const char * psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator + (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        AcString retval = concat( psz, Utf8);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }
#endif

    /// <summary>Copy the string and append a string of Unicode characters to it.</summary>
    /// <param name="pwsz">input pointer to the string to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString operator + (const wchar_t * pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator + (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcString retval = concat(pwsz);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and append an AcString to it.</summary>
    /// <param name="pwsz">input reference to the AcString to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString operator + (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator + (const AcString &) : \"%ls\"",acs.kwszPtr());
        AcString retval = concat(acs);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and append a Unicode character to it.</summary>
    /// <param name="ch">input character to append to the string copy</param>
    /// <returns>A new string object.</returns>
    AcString concat(wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"concat(const wchar_t) : %d",wch);
        wchar_t str[2] = { wch, 0 };
        AcString retval = concat( str );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string.</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>A new string object.</returns>
    AcString concat(std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"concat(std::nullptr_t) :");
        AcString retval(*this);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and append a string of narrow chars to it.</summary>
    /// <param name="psz">input pointer to the narrow string to append</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString concat(const char * psz, Encoding encoding) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"concat(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcString retval(*this);
        retval.append(psz, encoding);
        AcStrASSERT(retval.DBGverify());
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and append a string of Unicode characters to it.</summary>
    /// <param name="pwsz">input pointer to the string to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString concat(const wchar_t * pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"concat(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcString retval;
        Adesk::UInt32 len = iGetLen();  // current length
        Adesk::UInt32 appendLen = pwsz ? cstrLen(pwsz) : 0;  // length to add
        retval.initWithLen( iGetBuff(), len, len + appendLen );
        if (appendLen) // don't allow null pwszm this checks for that and empty
            retval.iappendWillFit(pwsz,appendLen); // append new
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and append an AcString to it.</summary>
    /// <param name="pwsz">input reference to the AcString to append</param>
    /// <returns>A reference to this string object.</returns>
    AcString concat(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"concat(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcString retval;
        Adesk::UInt32 len = iGetLen();            // current length
        const wchar_t *p = acs.iGetBuff();
        Adesk::UInt32 appendLen = acs.isGetBuffer() ? cstrLen(p) : acs.iGetLen();  // length to add
        retval.initWithLen( iGetBuff(), len, len + appendLen );
        retval.iappendWillFit( p, appendLen );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    // These copy the current string and then insert the character or
    // string in front of it.  They're used by the global "+" operators.

    /// <summary>Copy the string and insert a character in front of it.</summary>
    /// <param name="ch">input character to insert</param>
    /// <returns>A reference to this string object.</returns>
    AcString precat(ACHAR ch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"precat(ACHAR ch) : %d",ch);
        wchar_t str[2] = { ch, 0};
        AcString retval = precat( str );
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string.</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>A new string object.</returns>
    AcString precat(std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"precat(str::nullptr) :");
        AcString retval(*this);
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and insert a string of narrow chars in front of it.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to insert</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>A reference to this string object.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    AcString precat(const char * psz, Encoding encoding) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"precat(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        (encoding);     // prevent unused variable warning

        AcString retval;
        Adesk::UInt32 len = iGetLen();
        if (psz && *psz)
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this);
            Adesk::UInt32 widelen = wide.getLen();
            retval.initWithLen( wide.getBuff(), widelen, widelen+len);
        }
        retval.iappend( iGetBuff(), len);
        AcStrASSERT(retval.DBGverify());
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    /// <summary>Copy the string and insert a string of characters in front of it.</summary>
    /// <param name="psz">input pointer to the string of characters to insert</param>
    /// <returns>A reference to this string object.</returns>
    AcString precat(const wchar_t * pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"precat(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcString retval;
        Adesk::UInt32 len = iGetLen();
        if (pwsz)
        {
            Adesk::UInt32 addlen = cstrLen(pwsz);
            retval.initWithLen( pwsz, addlen, len + addlen );
        }
        retval.iappend( iGetBuff(), len);
        AcStrASSERT(retval.DBGverify());
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }

    //
    // Comparison operators and methods
    // The int return value is -1, 0 or 1, indicating <, == or >
    //

    /// <summary>Compare the string to a single Unicode char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>0 if this string equals wch, a value < 0 if this string is less
    ///          than wch and a value > 0 if this string is greater than wch.</returns>
    Adesk::Int32  compare(wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(wchar_t) : %d",wch);
        wchar_t str[2] = { wch, 0 };
        Adesk::Int32 retval = compare( str );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string to nullptr.</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>1 if this string is not empty, 0 if empty</returns>
    Adesk::Int32  compare(std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        Adesk::Int32 retval = isEmpty() ? 0 : 1;
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

 #ifdef AcStringMBCS
    /// <summary>Compare the string to a string of narrow chars.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to compare to</param>
    /// <returns>0 if this string equals psz, a value < 0 if this string is less
    ///          than psz and a value > 0 if this string is greater than psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32 compare(const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(const char *) : \"%hs\"",psz?psz:"(nullptr)");
        Adesk::Int32 retval = compare(psz,Utf8);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }
#endif

    /// <summary>Compare the string to a string of narrow chars.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to compare to</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>0 if this string equals psz, a value < 0 if this string is less
    ///          than psz and a value > 0 if this string is greater than psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  compare(const char *psz, Encoding encoding) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(const char *, Encoding) : \"%hs\"",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT( encoding == Utf8 );
        (encoding);     // prevent unused variable warning

        Adesk::Int32 retval;
        if (!psz || !*psz)
            retval = isEmpty() ? 0 : 1;
        else
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this);
            retval = compare( wide.getBuff());
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string to a string of Unicode characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>0 if this string equals pwsz, a value < 0 if this string is less
    ///          than pwsz and a value > 0 if this string is greater than pwsz.</returns>
    Adesk::Int32  compare(const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        // if arg is empty, then we must be >= to it.
        Adesk::Int32 retval;

        if (!pwsz || !pwsz[0])
            retval = isEmpty() ? 0 : 1;
        // if we are empty, then we must be < arg.
        else if (isEmpty())
            retval = -1;
        else
            // We don't bother to optimize for ascii, because wcscmp() implementations don't
            // seem to have the performance issues that _wcsicmp() ones do..
            //
            retval = ::wcscmp(c_str(), pwsz);

        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string to a string of Unicode characters.</summary>
    /// <param name="acs">input reference of the other AcString to compare to</param>
    /// <returns>0 if this string equals acs, a value < 0 if this string is less
    ///          than acs and a value > 0 if this string is greater than acs.</returns>
    Adesk::Int32  compare(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compare(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(acs.DBGverify());

        Adesk::Int32 retval = compare(acs.iGetBuff());
        AcStrLOGADD(L"%d",retval);
        return retval;
    }


    /// <summary>Compare the string to another string using collation.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>0 if this string equals pwsz, a value < 0 if this string is less
    ///          than pwsz and a value > 0 if this string is greater than pwsz.</returns>
    Adesk::Int32  collate (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"collate(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 retval;
        if (isEmpty())  // left side empty
            retval = (!pwsz || !*pwsz) ? 0 : -1;  // either right side empty or not empty
        else if (!pwsz || !*pwsz)  // left side not empty, right side empty
            retval = 1;
        else
            retval = std::wcscoll( iGetBuff(), pwsz );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }
    
    /// <summary>Compare the string to another AcString object using collation.</summary>
    /// <param name="acs">input AcString object to compare to </param>
    /// <returns>0 if this string equals acs, a value < 0 if this string is less
    ///          than acs and a value > 0 if this string is greater than acs.</returns>
    Adesk::Int32  collate(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"collate(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        AcStrASSERT(!isGetBuffer());

        const wchar_t *acsp = acs.iGetBuff();
        Adesk::Int32 retval;
        if (isEmpty())  // left side empty
            retval = *acsp ? -1 : 0;  // either right side empty or not empty
        else if (!*acsp)  // left side not empty, right side empty
            retval = 1;
        else
            retval = std::wcscoll( iGetBuff(), acsp );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Static method to compare two strings case-independently.</summary>
    /// <param name="pwsz1">input pointer to the left-hand string</param>
    /// <param name="pwsz2">input pointer to the right-hand string</param>
    /// <returns>0 if pwsz1 equals pwsz2, a value < 0 if less then
    ///          and a value > 0 if pwsz1 is greater than pwsz2.</returns>
    /// <remarks> strings are compared converted to lower case </remarks>
    static Adesk::Int32  compareNoCase(const wchar_t *pwsz1, const wchar_t *pwsz2)
    {
        AcStrLOG(nullptr, 0, L"compareNoCase(const wchar_t *, const wchar_t *) : \"%ls\", \"%ls\"",pwsz1?pwsz1:L"(nullptr)",pwsz2?pwsz2:L"(nullptr)");
        Adesk::Int32 retval = 0;
        if (!pwsz1 || !*pwsz1)  // left side empty
            retval = (!pwsz2 || !*pwsz2) ? 0 : -1;  // either right side empty or not empty
        else if (!pwsz2 || !*pwsz2)  // left side not empty, right side empty
            retval = 1;
        else
        {
            do
            {
                Adesk::UInt32 c1 = *pwsz1++;
                Adesk::UInt32 c2 = *pwsz2++;
                if (c2 == 0)
                {
                    retval = (Adesk::Int32)c1 - (Adesk::Int32)c2;
                    break;
                }
                retval = compareLCtoLC( c1, c2);  // compare using lower case
            }
            while (retval == 0);
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Static method to compare two strings case-independently with max length.</summary>
    /// <param name="pwsz1">input pointer to the left-hand string</param>
    /// <param name="pwsz2">input pointer to the right-hand string</param>
    /// <param name="nLen">max length to compare strings</param>
    /// <returns>0 if pwsz1 equals pwsz2, a value < 0 if less then
    ///          and a value > 0 if pwsz1 is greater than pwsz2.</returns>
    /// <remarks> strings are compared converted to lower case </remarks>
    static Adesk::Int32 compareNoCase(const wchar_t *pwsz1, const wchar_t *pwsz2, size_t nLen)
    {
        AcStrLOG(nullptr, 0, L"compareNoCase(const wchar_t *, const wchar_t *, size_t) : \"%ls\", \"%ls\", %d",pwsz1?pwsz1:L"(nullptr)",pwsz2?pwsz2:L"(nullptr)",(int)nLen);
        Adesk::Int32 retval = 0;
        if (!pwsz1 || !*pwsz1)  // left side empty
            retval = (!pwsz2 || !*pwsz2) ? 0 : -1;  // either right side empty or not empty
        else if (!pwsz2 || !*pwsz2)  // left side not empty, right side empty
            retval = 1;
        else
        {
            for (;nLen && (retval == 0);nLen--)
            {
                Adesk::UInt32 c1 = *pwsz1++;
                Adesk::UInt32 c2 = *pwsz2++;
                if (c2 == 0)
                {
	                retval = static_cast<Adesk::Int32>(c1) - static_cast<Adesk::Int32>(c2);
                    break;
                }
                retval = compareLCtoLC( c1, c2);   // compare using lower case
            }
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string case-independently to a Unicode char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>0 if this string equals wch, a value < 0 if this string is less
    ///          than wch and a value > 0 if this string is greater than wch.</returns>
    Adesk::Int32  compareNoCase(wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(const wchar) : %d",wch);
        wchar_t str[2] = { wch, 0 };
        Adesk::Int32 retval = compareNoCase( str );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>compare to empty, return 0 if empty, 1 if not empty</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>0 if empty, 1 if not empty
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  compareNoCase(std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        
        Adesk::Int32 retval = isEmpty() ? 0 : 1;
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string case-independently to a string of narrow chars.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to compare to</param>
    /// <returns>0 if this string equals psz, a value < 0 if this string is less
    ///          than psz and a value > 0 if this string is greater than psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  compareNoCase(const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(const char *) : \"%hs\"",psz?psz:"(nullptr)");
        Adesk::Int32 retval = compareNoCase(psz,Utf8);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }
#endif

    /// <summary>Compare the string case-independently to a string of narrow chars.</summary>
    /// <param name="psz">input pointer to the string of narrow chars to compare to</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>0 if this string equals psz, a value < 0 if this string is less
    ///          than psz and a value > 0 if this string is greater than psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  compareNoCase(const char *psz, Encoding encoding) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(const char *, Encoding) : \"%hs\"",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        (encoding);     // prevent unused variable warning

        Adesk::Int32 retval;
        if (!psz || !*psz)
            retval = isEmpty() ? 0 : 1;
        else
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this );
            retval = compareNoCase( wide.getBuff() );
        }
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string case-independently to a string of Unicode characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>0 if this string equals pwsz, a value < 0 if this string is less
    ///          than pwsz and a value > 0 if this string is greater than pwsz.</returns>
    Adesk::Int32  compareNoCase(const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());

        Adesk::Int32 retval = compareNoCase( (const wchar_t *)iGetBuff(), pwsz );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// Compare up to nLen chars
    Adesk::Int32  compareNoCase(const wchar_t *pwsz, size_t nLen) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compareNoCase(const wchar_t *, size_t) : \"%ls\", %d",pwsz?pwsz:L"(nullptr)",(int)nLen);
        AcStrASSERT(DBGverify());

        Adesk::Int32 retval = compareNoCase((const wchar_t *)iGetBuff(), pwsz, nLen );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare the string case-independently to another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>0 if this string equals acs, a value < 0 if this string is less
    ///          than acs and a value > 0 if this string is greater than acs.</returns>
    Adesk::Int32  compareNoCase(const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compaeNoCase(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        Adesk::Int32 retval = compareNoCase( iGetBuff(), acs.iGetBuff() );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// Compare up to nLen chars
    Adesk::Int32  compareNoCase(const AcString & acs, size_t nLen) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"compaeNoCase(const AcString &, size_t) : \"%ls\", %d",acs.kwszPtr(),(int)nLen);
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        Adesk::Int32 retval = compareNoCase( iGetBuff(), acs.iGetBuff(), nLen );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compares two AcStrings for equality, ignoring case.</summary>
    /// <param name="left"> one AcString object </param>
    /// <param name="right"> another AcString object </param>
    /// <returns>true if left equals right, else false.</returns>
    /// <remarks>May be useful as a comparator function for STL functions.</remarks>
    static bool equalsNoCase(const AcString& left, const AcString& right)
    {
        AcStrLOG(nullptr, 0, L"equalsNoCase(const AcString &, const AcString &) : \"%ls\", \"%ls\"",left.kwszPtr(), right.kwszPtr());
        bool retval = left.compareNoCase( right ) == 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare case-independently to another string using collation.</summary>
    /// <param name="psz">input pointer to the string of characters to compare to </param>
    /// <returns>0 if this string equals psz, a value < 0 if this string is less
    ///          than psz and a value > 0 if this string is greater than psz.</returns>
    Adesk::Int32 collateNoCase(const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"collateNoCase(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());
        Adesk::Int32 retval;
        if (isEmpty())  // left side empty
            retval = (!pwsz || !*pwsz) ? 0 : -1;  // either right side empty or not empty
        else if (!pwsz || !*pwsz)  // left side not empty, right side empty
            retval = 1;
        else
            retval = collateNoCaseGeneric(iGetBuff(),pwsz);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare case-independently to another AcString using collation./// </summary>
    /// <param name="acs"> input reference to the other AcString to compare to </param>
    /// <returns>0 if this string equals acs, a value < 0 if this string is less
    ///          than acs and a value > 0 if this string is greater than acs.</returns>
    Adesk::Int32 collateNoCase(const AcString& acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"collateNoCase(const wchar_t *) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
        AcStrASSERT(!isGetBuffer());
        Adesk::Int32 retval = collateNoCase( acs.iGetBuff() );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Compare this string for equality with a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string equals wch, else false.</returns>
    bool operator == (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator == (wchar_t) : %d",wch);
        bool retval = (compare( wch ) == 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare to empty string. Same as calling isEmpty or empty.</summary>
    /// <param name="nullptr">only allowed input</param>
    /// <returns>True if this string is empty.</returns>
    bool operator == (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator == (std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        bool retval = isEmpty();
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string for equality with a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>True if this string equals pwsz, else false.</returns>
    bool operator == (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator == (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = (compare( psz, Utf8 ) == 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare the string for equality with a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>True if this string equals pwsz, else false.</returns>
    bool operator == (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator == (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = compare( pwsz ) == 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for equality with another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string equals acs, else false.</returns>
    bool operator == (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator == (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = (compare( acs ) == 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for non-equality with a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string does not equal wch, false if they are equal.</returns>
    bool operator != (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator != (wchar_t) : %d",wch);
        bool retval = (compare( wch ) != 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for not empty</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>True if this string is not empty, false if empty</returns>
    bool operator != (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator != (std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        bool retval = !isEmpty();
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string for non-equality with a string of utf8 characters.</summary>
    /// <param name="psz">input pointer to the string of characters</param>
    /// <returns>True if this string does not equal psz, false if they are equal.</returns>
    bool operator != (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator != (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = (compare( psz, Utf8 ) != 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare the string for non-equality with a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>True if this string does not equal pwsz, false if they are equal.</returns>
    bool operator != (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator != (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = (compare( pwsz ) != 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for non-equality with another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string does not equal acs, false if they are equal.</returns>
    bool operator != (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator != (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = (compare( acs ) != 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for greater than a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string is greater than wch, false otherwise.</returns>
    bool operator >  (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator > (wchar_t) : %d",wch);
        bool retval = (compare( wch ) > 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>compare to empty.</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>True if this string is not empty, false if empty</returns>
    bool operator >  (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator > (std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        bool retval = !isEmpty();
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string for greater than a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>True if this string is greater than pwsz, false otherwise.</returns>
    bool operator >  (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator > (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = (compare( psz, Utf8 ) > 0);
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare the string for greater than a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>True if this string is greater than pwsz, false otherwise.</returns>
    bool operator >  (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator > (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = compare( pwsz ) > 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for greater than another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string is greater than acs, false otherwise.</returns>
    bool operator >  (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator > (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = compare( acs ) > 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for greater than or equal to a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string is greater than or equal to wch, false otherwise.</returns>
    bool operator >= (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator >= (wchar_t) : %d",wch);
        bool retval = compare( wch ) >= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>always returns true</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>True</returns>
    bool operator >=  (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator >= (std::nullptr_t) :");
        bool retval = true;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare for greater than/equal to a string of Utf8 characters.</summary>
    /// <param name="psz">input pointer to the string of characters</param>
    /// <returns>True if this string is greater than or equal to pwsz, false otherwise.</returns>
    bool operator >= (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator >= (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = compare( psz, Utf8 ) >= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare for greater than/equal to a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>True if this string is greater than or equal to pwsz, false otherwise.</returns>
    bool operator >= (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator >= (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = compare( pwsz ) >= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for greater than or equal to another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string is greater than or equal to acs, false otherwise.</returns>
    bool operator >= (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator >= (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = compare( acs ) >= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for less than a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string is less than wch, false otherwise.</returns>
    bool operator <  (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator < (wchar_t) : %d",wch);
        bool retval = compare( wch ) < 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>always returns false</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>false</returns>
    bool operator <  (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator < (std::nullptr_t) :");
        bool retval = false;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string for less than a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>True if this string is less than pwsz, false otherwise.</returns>
    bool operator < (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator < (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = compare( psz, Utf8 ) < 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare the string for less than a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters to compare to</param>
    /// <returns>True if this string is less than pwsz, false otherwise.</returns>
    bool operator <  (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator < (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = compare( pwsz ) < 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for less than another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string is less than acs, false otherwise.</returns>
    bool operator <  (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator < (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = compare( acs ) < 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for less than or equal to a wide char.</summary>
    /// <param name="wch">input character to compare to</param>
    /// <returns>True if this string is less than or equal to wch, false otherwise.</returns>
    bool operator <= (wchar_t wch) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator <= (wchar_t) : %d",wch);
        bool retval = compare( wch ) <= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>less then or equal compared to empty</summary>
    /// <param name="nullptr">only allowed value</param>
    /// <returns>True if empty, false if non-empty</returns>
    bool operator <=  (std::nullptr_t) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator <= (std::nullptr_t) :");
        AcStrASSERT(!isGetBuffer());
        bool retval = isEmpty();
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

#ifdef AcStringMBCS
    /// <summary>Compare the string for less than/equal to a utf8 string.</summary>
    /// <param name="psz">input pointer to the string of Utf8 characters</param>
    /// <returns>True if this string is less than or equal to pwsz, false otherwise.</returns>
    bool operator <= (const char *psz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator <= (const char *) : \"%hs\"",psz?psz:"(nullptr)");
        bool retval = compare( psz, Utf8 ) <= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }
#endif

    /// <summary>Compare the string for less than/equal to a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>True if this string is less than or equal to pwsz, false otherwise.</returns>
    bool operator <= (const wchar_t *pwsz) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator <= (const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        bool retval = compare( pwsz ) <= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare the string for less or equal to than another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>True if this string is less than or equal to acs, false otherwise.</returns>
    bool operator <= (const AcString & acs) const
    {
        AcStrLOG(this, iLogMsg::dStr, L"operator <= (const AcString &) : \"%ls\"",acs.kwszPtr());
        bool retval = compare( acs ) <= 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    // The match() methods return the number of positions in the string that have the same
    // character value as that position in the other string.  E.g., matching "abcd" and
    // "abxyz" returns 2.  Matching "abc" and "xyz" returns 0.

    /// <summary>See how many characters match a string of narrow chars.</summary>
    /// <param name="psz">input pointer to the string of narrow chars</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>The number of characters that match psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  match(const char *psz, Encoding encoding) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"match(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        (encoding);     // prevent unused variable warning
        Adesk::Int32 retval = 0;    
        if (psz && *psz)
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this );
            retval = match( wide.getBuff());
        }            
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>See how many characters match a string of wide characters.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>The number of characters that match pwsz.</returns>
    Adesk::Int32  match(const wchar_t *pwsz) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"match(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 count = 0;
        if (pwsz && *pwsz)
        {
            const wchar_t *src = iGetBuff();
            Adesk::UInt32 len = iGetLen();
            for (;src[count] == pwsz[count] && count < (Adesk::Int32)len; count++);
        }
        AcStrLOGADD(L"%d",count);
        return count;
    }

    /// <summary>See how many characters match another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>The number of characters that match pwsz.</returns>
    Adesk::Int32  match(const AcString & acs) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"match(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(acs.DBGverify());
        Adesk::Int32 retval = match(acs.iGetBuff());
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>See how many characters case-independently match a narrow string.</summary>
    /// <param name="psz">input pointer to the string of narrow chars</param>
    /// <param name="encoding">input Encoding type</param>
    /// <returns>The number of characters that match psz.</returns>
    /// <remarks>Currently, only Utf8 encoding is supported.</remarks>
    Adesk::Int32  matchNoCase(const char *psz, Encoding encoding) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"matchNoCase(const char *, Encoding) : \"%hs\", %d",psz?psz:"(nullptr)",(int)encoding);
        AcStrASSERT( encoding == Utf8 );
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        (encoding);     // prevent unused variable warning
        Adesk::Int32 retval = 0;
        if (psz && *psz)
        {
            UTF8converter wide( (const Adesk::UInt8 *)psz, m_maxStrLen, *this );
            retval = matchNoCase( wide.getBuff());
        }            
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>See how many characters case-independently match a wide string.</summary>
    /// <param name="pwsz">input pointer to the string of characters</param>
    /// <returns>The number of characters that match pwsz.</returns>
    Adesk::Int32  matchNoCase(const wchar_t *pwsz) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"matchNoCase(const wchar_t *) : \"%ls\"",pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        Adesk::Int32 count = 0;
        if (pwsz && *pwsz)
        {
            const wchar_t *src = iGetBuff();
            Adesk::UInt32 len = iGetLen();
            for (;toLower(src[count]) == toLower(pwsz[count]) && count < (Adesk::Int32)len; count++);
        }
        AcStrLOGADD(L"%d",count);
        return count;
    }

    /// <summary>See how many characters case-independently match another AcString.</summary>
    /// <param name="acs">input reference to the other AcString</param>
    /// <returns>The number of characters that match acs.</returns>
    Adesk::Int32  matchNoCase(const AcString & acs) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"matchNoCase(const AcString &) : \"%ls\"",acs.kwszPtr());
        AcStrASSERT(acs.DBGverify());
        Adesk::Int32 retval = matchNoCase(acs.iGetBuff());
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Convert this string's lowercase characters to upper case.</summary>
    /// <returns> Reference to this AcString.</returns>
    AcString & makeUpper()
    {
        AcStrLOG(this,iLogMsg::dStr,L"makeUpper() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        wchar_t *pstr = iGetBuff();
        Adesk::UInt32 len = iGetLen();
        for (Adesk::UInt32 i = 0; i < len; i++)
            pstr[i] = static_cast<wchar_t>(toUpper(pstr[i]));
        AcStrASSERT(DBGverify());
        return *this;
    }
    
    /// <summary>Convert this string's uppercase characters to lower case.</summary>
    /// <returns> Reference to this AcString.</returns>
    AcString & makeLower()
    {
        AcStrLOG(this,iLogMsg::dStr,L"makeLower() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        wchar_t *pstr = iGetBuff();
        Adesk::UInt32 len = iGetLen();
        for (Adesk::UInt32 i = 0; i < len; i++)
            pstr[i] = static_cast<wchar_t>(toLower(pstr[i]));
        AcStrASSERT(DBGverify());
        return *this;
    }

    
    /// <summary>Reverse the characters in this string./// </summary>
    /// <returns>A reference to this AcString.</returns>
    AcString& makeReverse()
    {
        AcStrLOG(this,iLogMsg::dStr,L"makeReverse() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        AcString dstr;                          // temp to build reverse
        Adesk::UInt32 len = iGetLen();               // current length
        dstr.emptyReserve(len);                      // make sure it can hold the string
        const wchar_t * __restrict src = iGetBuff();  // src buffer
        wchar_t * __restrict dest = dstr.iGetBuff();  // dest buffer - it builds backwards

        for (Adesk::UInt32 i = 0; i < len; i++)
            dest[len-i-1] = src[i];             // reverse the order
        dest[len] = 0;                          // set the end null
        dstr.iSetLen(len);                      // set the length
        setEmpty();                             // clear out
        iMove(dstr);                       // take owership, now in reverse
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary> Remove initial matching characters from left side of string.</summary>
    /// <param name="wch"> non-null character to match.</param name>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Stops removing on first char that does not match.
    /// does nothing if wch arg is null character.</remarks>
    ///
    AcString & trimLeft(wchar_t wch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimLeft(wchar_t) : %d",wch);
        if (wch) // must have char to find
        {
            const wchar_t str[2] = { wch, 0 };
            trimLeft(str);
        }
        return *this;
    }

    /// <summary> Remove initial matching characters from right side of string.</summary>
    /// <param name="wch"> non-null character to match.</param name>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Stops removing on first char that does not match.
    /// does nothing if wch arg is null character.</remarks>
    ///
    AcString & trimRight(wchar_t wch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimRight(wchar_t) : %d",wch);
        if (wch)  // must have char to find
        {
            const wchar_t str[2] = { wch, 0 };
            trimRight(str);
        }
        return *this;
    }

    /// <summary> Remove initial matching characters from both sides of string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Stops removing on each side on first char that does not match.
    /// does nothing if wch arg is null character.</remarks>
    ///
    AcString & trim(wchar_t wch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trim(wchar_t) : %d",wch);
        if (wch)
        {
            wchar_t str[2] = { wch, 0 };
            trim(str);
        }
        return *this;
    }

    /// <summary> Remove all whitespace characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trimLeft()
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimLeft() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        // remove whitespace from beginning of string
        Adesk::Int32 len = (Adesk::Int32)iGetLen();
        Adesk::Int32 start = 0;
        wchar_t *src = iGetBuff();
        for(;start < len;start++)
            if (!std::iswspace(src[start]))
                break;                  // found end that is not whitespace
        // three cases. 1) no changes, 2) everything removed, 3) sub-string
        if (start >= len)
            setNull();        // entire string was white space
        else if (start > 0)   // we have something to trim - not full string
        {
            Adesk::Int32 newlen = len - start;
            for (Adesk::Int32 i = 0; i < newlen; i++ ) src[i] = src[i+start];   // pack down
            src[newlen] = 0;    // new end
            iSetLen(newlen);
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary> Remove all designated characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is nullptr.
    /// Does nothing if pwszChars is an empty string</remarks>
    ///
    AcString & trimLeft(const wchar_t *pwszChars)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimLeft(const wchar_t *) : \"%ls\"",pwszChars?pwszChars:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        if (!pwszChars)
            trimLeft();  // remove white space
        else if (*pwszChars)    // we have something
        {
            // remove whitespace from beginning of string
            Adesk::Int32 len = (Adesk::Int32)iGetLen();
            Adesk::Int32 start = 0;
            wchar_t *src = iGetBuff();
            for(;start < len;start++)
                if (!isOneOf(src[start],pwszChars))
                    break;                              // found end that is not whitespace
            // three cases. 1) no changes, 2) everything removed, 3) sub-string
            if (start >= len)
                setNull();        // entire string matched one of the chars
            else if (start > 0)   // we have something to trim - not full string
            {
                Adesk::Int32 newlen = len - start;
                for (Adesk::Int32 i = 0; i < newlen; i++ ) src[i] = src[i+start];   // pack down
                src[newlen] = 0;    // new end
                iSetLen(newlen);
            }
        }
        AcStrASSERT(DBGverify());
        return *this;
    }


    /// <summary> Remove all whitespace characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trimRight()
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimRight() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        // substring starts at beginning and is trimmed back from the end
        Adesk::Int32 len = (Adesk::Int32)iGetLen();
        Adesk::Int32 end = len -1;
        wchar_t *src = iGetBuff();
        for(;end >= 0;end--)
            if (!std::iswspace(src[end]))
                break;                              // found end that is not whitespace
        // three cases. 1) no changes, 2) everything removed, 3) sub-string
        if (end < 0)
            setNull();          // entire string is whitespace
        else if (end < len-1)   // we have something to trim - not full string
        {
            src[end+1] = 0; // truncate
            iSetLen(end+1);   // set new length
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary> Remove all designated characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is nullptr.
    /// Does nothing if pwszChars is an empty string.</remarks>
    ///
    AcString & trimRight(const wchar_t *pwszChars)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trimRight(const wchar_t *) : \"%ls\"",pwszChars?pwszChars:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        if (!pwszChars)
            trimRight();  // remove white space
        else if (*pwszChars)    // have something to process
        {
            // substring starts at beginning and is trimmed back from the end
            Adesk::Int32 len = (Adesk::Int32)iGetLen();
            Adesk::Int32 end = len -1;
            wchar_t *src = iGetBuff();
            for(;end >= 0;end--)
                if (!isOneOf(src[end],pwszChars))
                    break;                              // found end that is not one of list of chars
            // three cases. 1) no changes, 2) everything removed, 3) sub-string
            if (end < 0)
                setNull();          // entire string matched one of the chars
            else if (end < len-1)   // we have something to trim - not full string
            {
                src[end+1] = 0; // truncate
                iSetLen(end+1);   // set new length
            }
        }
        AcStrASSERT(DBGverify());
        return *this;
    }


    /// <summary> Remove all whitespace characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trim()
    {
        AcStrLOG(this,iLogMsg::dStr,L"trim() :");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        Adesk::Int32 len = (Adesk::Int32)iGetLen();
        Adesk::Int32 start = 0;
        Adesk::Int32 end = len -1;
        wchar_t *src = iGetBuff();
        for (;start <= len; start++)    // do left side
            if (!std::iswspace(src[start])) // break on non-whitespace
                break;
        for (;end >= start; end--)      // do right side
            if (!std::iswspace(src[end]))   // break on non-whitespace
                break;
        if (start > end)
            setNull();      // entire string of of the chars
        else if ((start > 0) || (end < (len-1)))   // trimming something
        {
            Adesk::Int32 newlen = end - start + 1;
            if (start)  // only pack if we had whitespace on left side
                for (Adesk::Int32 i = 0; i < newlen; i++ ) src[i] = src[i+start];   // pack down
            src[newlen] = 0;    // new end
            iSetLen(newlen);
        }
        return *this;
    }

    /// <summary> Remove all designated characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is nullptr.
    /// Does nothing if pwszChars is an empty string</remarks>
    ///
    AcString & trim(const wchar_t *pwszChars)
    {
        AcStrLOG(this,iLogMsg::dStr,L"trim(const wchar_t *) : \"%ls\"",pwszChars?pwszChars:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        if (!pwszChars)
            trim();  // remove white space
        else if (*pwszChars)    // have something
        {
            Adesk::Int32 len = (Adesk::Int32)iGetLen();
            Adesk::Int32 start = 0;
            Adesk::Int32 end = len -1;
            wchar_t *src = iGetBuff();
            for (;start <= len; start++)    // do left side
                if (!isOneOf(src[start],pwszChars))
                    break;
            for (;end >= start; end--)      // do right side
                if (!isOneOf(src[end],pwszChars))
                    break;
            if (start > end)
                setNull();      // entire string of of the chars
            else if ((start > 0) || (end < (len-1)))   // trimming something
            {
                Adesk::Int32 newlen = end - start + 1;
                if (start)  // only pack if we had whitespace on left side
                    for (Adesk::Int32 i = 0; i < newlen; i++ ) src[i] = src[i+start];   // pack down
                src[newlen] = 0;    // new end
                iSetLen(newlen);
            }
        }
        return *this;
    }

    /// <summary> Remove all occurrences of the specified character in the string.</summary>
    /// <returns> Number of characters removed. Zero if the string was not changed.</returns>
    /// <remarks> Removes whitespace characters if wch arg is zero.</remarks>
    ///
    Adesk::Int32 remove(wchar_t wch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"remove(wchar_t) : %d",wch);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        AcString newStr;                    // single pass, build new string as we go. If no change, we toss it
        Adesk::UInt32 slen = iGetLen();          // current length
        newStr.emptyReserve( slen );             // new string can be up to the current length

        Adesk::UInt32 newLen = 0;
        const wchar_t * __restrict src = iGetBuff();
        wchar_t * __restrict dest = newStr.iGetBuff();  // source and dest do not overlap

        if (wch)    // match this char
        {
            for (Adesk::UInt32 i = 0; i < slen; i++)     // process all chars
                if (src[i] != wch)              // not match
                    dest[newLen++] = src[i];    // copy it
        }
        else    // wch == 0 is remove white space
        {
            for (Adesk::UInt32 i = 0; i < slen; i++)     // process all chars
                if (!std::iswspace(src[i]))         // not white space
                    dest[newLen++] = src[i];        // copy it
        }
        if (slen > newLen)  // something was removed
        {
            dest[newLen] = 0;   // null term
            newStr.iSetLen( newLen );   // set length
            setEmpty();          // clear out
            iMove(newStr);  // take ownership of new string
        }
        AcStrASSERT(DBGverify());
        Adesk::Int32 retval = slen - newLen;   // number of chars removed
        AcStrLOGADD(L"%d",retval);
        return retval;
    }


    /// <summary> Remove all occurrences of whitespace anywhere in the string.</summary>
    /// <returns> Number of characters removed. Zero if the string was not changed.</returns>
    ///
    Adesk::Int32 remove()
    {
        AcStrLOG(this,iLogMsg::dStr,L"remove() :");
        Adesk::Int32 retval = remove(0);
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary> Extract substring up to the first instance of a designated character.</summary>
    /// <param name="pwszChars"> Null terminated string of chars at which to stop scanning</param>
    /// <returns> AcString that contains the substring. if pwszChars is nullptr or empty
    /// returns entire string</returns>
    ///
    AcString spanExcluding(const wchar_t *pwszChars) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"spanExcluding(const wchar_t *) : \"%ls\"",pwszChars?pwszChars:L"(nullptr)");
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        const wchar_t *src = iGetBuff();
        Adesk::UInt32 len = iGetLen();
        if (pwszChars && *pwszChars && len) // something to scan and return
        {
            for (Adesk::UInt32 i = 0; i < len; i++)
            {
                if (isOneOf(src[i],pwszChars))
                {
                    len = i;
                    break;
                }
            }
        }
        AcString retval(src,len);   // repacked string
        AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
        return retval;
    }


#if defined(_AFX) || defined(__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)
#if !defined (_ADESK_CROSS_PLATFORM_)  // not allowed in cross-platform code
#define ENABLE_ACSTRING_CSTRING_OPERATORS
#endif
#endif

#if defined(ENABLE_ACSTRING_CSTRING_OPERATORS)
    //
    // MFC CString-using methods.  The CStringA class is the ansi
    // code page based CString, while CStringW is Unicode based.
    // CString maps to one or the other depending on whether the
    // UNICODE preprocessor symbol is defined.
    //

    /// <summary>Construct an AcString from a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    AcString(const CStringW &csw) : AcString( (const wchar_t *)csw )
    {
        AcStrLOG(this,iLogMsg::dStr,L"AcString(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
    }

    /// <summary>Initialize this AcString from a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString & operator = (const CStringW &csw)
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator = (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        assign( (const wchar_t *)csw );
        return *this;
    }        

    /// <summary>Append a CStringW to this AcString.</summary>
    /// <param name="csa">input reference to the CStringW</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString & operator += (const CStringW &csw)
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator += (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        append( (const wchar_t *)csw );
        return *this;
    }

    /// <summary>Compare this string to a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>0 if this string equal csw, a value < 0 if tihs string is
    ///          is less than csw, a value > 0 if this string is greater than csw.</returns>
    Adesk::Int32  compare(const CStringW & csw) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"compare(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        Adesk::Int32 retval = compare((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare this string case independently to a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>0 if this string equal csw, a value < 0 if tihs string is
    ///          is less than csw, a value > 0 if this string is greater than csw.</returns>
    Adesk::Int32  compareNoCase(const CStringW & csw) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"compareNoCase(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        Adesk::Int32 retval = compareNoCase((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for equality with a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string equals the CStringW, else false.</returns>
    bool operator == (const CStringW & csw) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator == (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator == ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for non-equality with a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string does not equal the CStringW, false if they're equal.</returns>
    bool operator != (const CStringW &csw ) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator != (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator != ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for less than a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string is less than the CStringW, else false.</returns>
    bool operator <  (const CStringW & csw ) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator < (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator < ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for less than or equal to a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string is less than or equal to the CStringW, else false.</returns>
    bool operator <= (const CStringW & csw ) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator <= (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator <= ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for greater than a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string is greater than the CStringW, else false.</returns>
    bool operator > (const CStringW & csw ) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator > (const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator > ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Compare for greater than or equal to a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>True if this string is greater than or equal to the CStringW, else false.</returns>
    bool operator >= (const CStringW & csw ) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator >=(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        bool retval = operator >= ((const wchar_t *)csw );
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary>Get number of characters matching a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>The number of characters in this string matching csw.</returns>
    Adesk::Int32  match(const CStringW & csw) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"match(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        Adesk::Int32 retval = match((const wchar_t *)csw );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }

    /// <summary>Return number of characters case-independently matching a CStringW.</summary>
    /// <param name="csw">input reference to the CStringW</param>
    /// <returns>The number of characters in this string matching csw.</returns>
    Adesk::Int32  matchNoCase(const CStringW & csw) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"matchNoCase(const CStringW &) : \"%ls\"",(const wchar_t *)csw);
        Adesk::Int32 retval = matchNoCase((const wchar_t *)csw );
        AcStrLOGADD(L"%d",retval);
        return retval;
    }
#endif  // ENABLE_ACSTRING_CSTRING_OPERATORS


#ifdef __cpp_lib_string_view  // defined in <version>
    /// <summary>Construct an AcString from a std::wstring_view.</summary>
    /// <param name="csw">input std::wstring_view</param>
    explicit AcString(std::wstring_view str) : AcString( str.data(), (Adesk::UInt32)str.length() )
    {
        AcStrLOG(this,iLogMsg::dStr,L"AcString(std::wstring_view)");
    }

    /// <summary>Initialize this AcString from a std::wstring_view.</summary>
    /// <param name="csw">input std::wstring_view</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString& operator = (std::wstring_view csw)
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator = (std::wstring_view)");
        assign( csw.data(), (Adesk::UInt32)csw.length());
        return *this;
    }

#ifdef AcStringMBCS
    explicit AcString(std::string_view str) : AcString(str.data(), Utf8, (Adesk::UInt32)str.length())
    {
        AcStrLOG(this,iLogMsg::dStr,L"AcString(std::string_view)");
    }

    explicit AcString(const std::string & str) : AcString(str.c_str(), Utf8)
    {
        AcStrLOG(this,iLogMsg::dStr,L"AcString(const std::string &)");
    }
#endif // AcStringMBCS

#endif  //  __cpp_lib_string_view

    /// <summary>Construct an AcString from a std::wstring.</summary>
    /// <param name="csw">input reference to the std::wstring</param>
    explicit AcString(const std::wstring& str) : AcString( str.c_str(), (Adesk::UInt32)str.length())
    {
        AcStrLOG(this,iLogMsg::dStr,L"AcString(const std::wstring&): \"%ls\"",str.c_str());
    }

    /// <summary>Initialize this AcString from a std::wstring.</summary>
    /// <param name="csw">input reference to the std::wstring</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString& operator = (const std::wstring& csw)
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator = (const std::wstring&): \"%ls\"",csw.c_str());
        assign( csw.c_str(), (Adesk::UInt32)csw.length());
        return *this;
    }

    /// <summary>
    /// Replaces instances of the substring with instances of the new string 
    /// </summary>
    /// <param name="pwszOld"> A pointer to a string containing the string to be replaced by pwszNew. </param>
    /// <param name="pwszNew"> A pointer to a string containing the string replacing pwszOld. </param>
    /// <returns>The number of replaced instances of the substring.
    ///          Zero if the string is not changed.</returns>
    Adesk::Int32 replace(const wchar_t* pwszOld, const wchar_t* pwszNew)
    {
        AcStrLOG(this,iLogMsg::dStr,L"replace(const wchar_t*, const wchar_t*): \"%ls\", \"%ls\"",pwszOld?pwszOld:L"(nullptr)",pwszNew?pwszNew:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        Adesk::Int32 count = 0;

        if (pwszOld && *pwszOld)    // something to find
        {
            Adesk::UInt32 findlen = pwszOld ? cstrLen(pwszOld) : 0;
            Adesk::UInt32 len = iGetLen();    // length of our string
            if ((findlen > 0) && (findlen <= len))    // have string to search and its possible for one to match
            {
                Adesk::UInt32 newlen = pwszNew ? cstrLen(pwszNew) : 0;  // length to replace it with - can be 0

                // because we have move abiliy, it makes it easy to deal with self referencing
                AcString result;    // easiest way is to build into new string and assume ownership of it when done

                const wchar_t *src = iGetBuff();
                Adesk::UInt32 start = 0;
                Adesk::UInt32 end = 0;
                for (;end < len;)  // scan looking for matches
                {
                    if (isSubStr(src+end,pwszOld))  // found a match
                    {
                        count++;    // doing a replacement
                        if (end > start)
                            result.iappend( src+start, end-start );  // append chars prior to match
                        if (newlen)                                  // something to replace it with
                            result.iappend(pwszNew, newlen);         // append replacement
                        start = end + findlen;                       // where next match could possible start
                        end = start;
                    }
                    else
                        end++;  // check next char
                }
                if (count)  // something was replaced
                {
                    if (end > start)    // leftover to copy
                        result.iappend(src+start, end-start);
                    setEmpty();          // clear out
                    iMove(result);  // take ownership of the result
                }
            }
        }
        AcStrASSERT(DBGverify());
        AcStrLOGADD(L"%d",count);
        return count;
    }

    /// <summary>
    /// Replace a character with another.
    /// </summary>
    /// <param name="wchOld"> character that will be replaced </param>
    /// <param name="wchNew"> new character that will be replaced with </param>
    /// <returns>The number of replaced instances of the wchOld.
    ///          Zero if the string is not changed.</returns>
    Adesk::Int32 replace(wchar_t wchOld, wchar_t wchNew)
    {
        AcStrLOG(this,iLogMsg::dStr,L"replace(wchar_t, wchar_t): %d, %d",(int)wchOld, wchNew);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());

        Adesk::Int32 count = 0;
        if (wchOld)     // can't match null char
        {
            Adesk::UInt32 len = iGetLen();
            wchar_t *p = iGetBuff();
            for (Adesk::UInt32 i = 0; i < len; i++)
            {
                if (wchOld == p[i])
                {
                    p[i] = wchNew;
                    count++;
                }
            }
            if (!wchNew && count)   // if we set nulls, now compute new length
                iSetLen(cstrLen(p));    
        }
        AcStrASSERT(DBGverify());
        AcStrLOGADD(L"%d",count);
        return count;
    }

    /// <summary>
    /// Deletes character(s) from a string starting with the character at given index.
    /// </summary>
    /// <param name="iIndex"> Zero-based position from which to start deleting </param>
    /// <param name="nCount"> character number to be deleted. If -1, delete to end </param>
    /// <returns>Return the length of the changed string.</returns>
    /// <remarks> Truncates the string if nCount is negative.
    /// no change to string if nCount is 0.
    /// no change to string if iIndex is invalid</remarks>
    Adesk::Int32 deleteAtIndex(Adesk::Int32 iIndex, Adesk::Int32 nCount = 1)
    {
        AcStrLOG(this,iLogMsg::dStr,L"deleteAtIndex(Adesk::Int32, Adesk::Int32): %d, %d",(int)iIndex, nCount);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(nCount >= -1);
        AcStrASSERT( iIndex >= 0 );

        Adesk::UInt32 len = iGetLen();
        if (((Adesk::UInt32)iIndex >= len) || (nCount == 0))   // outside range or no count
            iIndex = (Adesk::Int32)len;
        else
        {
            wchar_t *dest = iGetBuff();
            if ((nCount >= 0) && ((Adesk::UInt32)(iIndex + nCount) < len))      // no truncation
            {
                // pack the right side into the space where we deleted from
                Adesk::UInt32 end = (Adesk::UInt32)iIndex + (Adesk::UInt32)nCount;
                AcStrASSERT( end < len );
                for (;end < len; end++,iIndex++)
                    dest[iIndex] = dest[end];
            }
            dest[iIndex] = 0;       // handle truncation and setting new end
            iSetLen(iIndex);        // set the new length
        }
        AcStrASSERT(DBGverify());
        AcStrLOGADD(L"%d",iIndex);
        return iIndex;          // return new length
    }

    /// <summary>
    /// Truncates the string from the given index
    /// </summary>
    /// <param name="nIndex"> Zero-based position at which to start deleting from</param>
    /// <returns>Return a reference to this string object.</returns>
    AcString & truncate(Adesk::Int32 nIndex)
    {
        AcStrLOG(this,iLogMsg::dStr,L"truncate(Adesk::Int32): %d",(int)nIndex);
        AcStrASSERT( !isGetBuffer() );
        AcStrASSERT( (nIndex >= 0) && (nIndex < (Adesk::Int32)iGetLen()) );
        AcStrASSERT(DBGverify());
        if (nIndex < 0) // negative index we are empty
            setNull();
        else if ((Adesk::UInt32)nIndex < iGetLen())    // in range so truncate
        {
            iGetBuff()[nIndex] = 0;
            iSetLen( nIndex );
        }

        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>
    /// Finds the next token in a target string
    /// </summary>
    /// <param name="pszTokens">A string containing token delimiters.
    ///              The order of these delimiters is not important.</param>
    /// <param name="iStart">The zero-based index at which to begin the search.</param>
    /// <returns>An AcString containing the current token value.</returns>
    /// <remarks> Returned string does not contain the delimiter
    ///           empty string returned if no more tokens or invalid iStart
    ///           iStart is updated to next position after the delimiter
    ///           iStart will be set to -1 if there are no more tokens
    ///           consecutive tokens will be skipped
    ///           empty pszTokens will return remaining string from iStart
    ///           clients processing in a loop can use either empty return string
    ///           or iStart == -1 to end tokenization</remarks>

    AcString tokenize(const wchar_t* pszTokens, Adesk::Int32& iStart) const
    {
        AcStrLOG(this,0,L"tokenize: \"%ls\", %d",pszTokens?pszTokens:L"(nullptr)", iStart);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcString result;                // what we return
        Adesk::UInt32 len = iGetLen();  // length
        Adesk::UInt32 ustart = (Adesk::UInt32)iStart;

        if (ustart < len) // valid start (rejects negative iStart)
        {
            const wchar_t *src = iGetBuff();
            // if nothing to match, then just return remaining string from iStart
            if (!pszTokens || !*pszTokens)
            {
                Adesk::UInt32 clen = len - ustart;
                iStart = (Adesk::Int32)len;   // next start beyond end
                result.initWithLen( src+ustart, clen, clen);
            }
            else
            {
                Adesk::UInt32 i = ustart;
                for (; i < len; )
                {
                    // find token or end of string
                    for (;(i < len) && !isOneOf(src[i],pszTokens);i++);
                    if (i > ustart) // we have a token
                        break;
                    ustart = ++i;   // skip empty string, check next char
                }
                if (i > ustart) // have token to return
                {
                    iStart = (Adesk::Int32)(i+1);  // next possible token start
                    Adesk::UInt32 clen = i - ustart;
                    result.initWithLen( src+ustart, clen, clen );
                }
                else
                    iStart = -1;    // at end of string, no non-null tokens, indicate all done
            }
        }
        else
        {
            iStart = -1;    // -1 means no more tokens and return empty string
        }
        AcStrASSERT(result.DBGverify());
        AcStrLOGADD(L"%d, \"%ls\"",iStart,result.kwszPtr());
        return result;
    }

    /// <summary>Set the character at the given postion to the specified character.</summary>
    /// <param name="nIndex">Zero-based postion of character in the string.</param>
    /// <param name="ch">The new character to replace the old one.</param>
    /// <returns>A reference to this AcString object.</returns>
    /// <remarks>if nIndex is out of range, string is not modified.
    /// if ch is 0 and nIndex is valid, this will truncate the string
    /// This method will never increase the string length</remarks>
    AcString& setAt(Adesk::Int32 nIndex, ACHAR ch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"setAt(Adesk::Int32, ACHAR): %d, %d",(int)nIndex, (int)ch);
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT( (nIndex >= 0) && (nIndex < (Adesk::Int32)iGetLen()) );

        Adesk::UInt32 len = iGetLen();
        if ((Adesk::UInt32)nIndex < len)
        {
            iGetBuff()[nIndex] = ch;
            if (!ch)        // setting a new end of string
                iSetLen((Adesk::UInt32)nIndex);  // update length
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary> Get one character at the given postion from the string. </summary>
    /// <param name="nIndex">Zero-based postion of character in the string.</param>
    /// <returns> Return the character at the specified position in the string </returns>
    /// <remarks> returns 0 if nIndex out of range</remarks>
    wchar_t getAt(Adesk::Int32 nIndex) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"getAt(Adesk::Int32): %d",(int)nIndex);
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcStrASSERT((nIndex >= 0) && (nIndex <= (Adesk::Int32)iGetLen()) );
        wchar_t retval = ((Adesk::UInt32)nIndex < iGetLen()) ? iGetBuff()[nIndex] : 0;
        AcStrLOGADD(L"%d",(int)retval);
        return retval;
    }

    /// <summary> return const reference to character at the given postion in the string. </summary>
    /// <param name="nIndex">Zero-based postion of character in the string.</param>
    /// <returns> Returns const reference to character index </returns>
    /// <remarks> returns const reference to static null string if index is invalid</remarks>
    template <class T>
    const wchar_t & operator [](T nIndex) const
    {
        AcStrLOG(this,iLogMsg::dStr,L"operator [](T): %d",(int)nIndex);
        const wchar_t &ref = refAt( (Adesk::UInt32) nIndex);
        AcStrLOGADD(L"%d",(int)ref);
        return ref;
    }
    
    /// <summary>
    /// Inserts a single character at the given index within the string.
    /// </summary>
    /// <param name="nIndex">The index of the character before which the insertion will take place.</param>
    /// <param name="ch">The character to be inserted.</param>
    /// <returns>A reference to this AcString object.</returns>
    AcString& insert(Adesk::Int32 nIndex, wchar_t ch)
    {
        AcStrLOG(this,iLogMsg::dStr,L"insert(Adesk::Int32, wchar_t): %d, %d",nIndex,ch);
        wchar_t str[2] = { ch, 0 };
        insert(nIndex,str);
        return *this;
    }

    /// <summary>
    /// Inserts a substring at the given index within the string.
    /// </summary>
    /// <param name="nIndex">The index of the character before which the insertion will take place.</param>
    /// <param name="ch">A pointer to the substring to be inserted.</param>
    /// <returns>A reference to this AcString object.</returns>
    /// <remarks> using 0 will insert at the beginning of string
    //  using length of string will append to the end of the string</remarks>
    AcString& insert(Adesk::Int32 nIndex, const wchar_t* pwsz)
    {
        AcStrLOG(this,iLogMsg::dStr,L"insert(Adesk::Int32, const wchar_t*): %d, \"%ls\"",nIndex,pwsz?pwsz:L"(nullptr)");
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT( (nIndex >= 0) && nIndex <= (Adesk::Int32)iGetLen() );
        AcStrASSERT(DBGverify());

        if (pwsz && *pwsz)
        {
            Adesk::UInt32 len = iGetLen();
            Adesk::UInt32 ipos = (Adesk::UInt32)nIndex;
            if (ipos <= len) // prevent crash from bad input
            {
                Adesk::UInt32 sublen = cstrLen( pwsz );     // length to insert
                if (ipos == len)    // this is just appending at end, don't need a new string
                {
                    iappend(pwsz, sublen);
                }
                else
                {
                    AcString result;
                    result.emptyReserve(sublen+len);           // make sure we have enough room
                    wchar_t *p = iGetBuff();    // start of our string
                    if (ipos)   // not inserting at front
                        result.copyWithLen( p, ipos );  // bring in the pre insert substring
                    result.iappend( pwsz, sublen );         // insert the substring
                    AcStrASSERT( ((Adesk::Int32)len - (Adesk::Int32)nIndex) > 0);     // must not be appending at end
                    result.iappend(p+nIndex,len-nIndex);
                    setEmpty();            // clear out
                    iMove( result );  // take ownership of new string
                }
            }
        }
        AcStrASSERT(DBGverify());
        return *this;
    }

    /// <summary>
    /// Returns a pointer to the internal character buffer of the string object, allowing
    /// direct access to and modification of the string contents.
    /// The returned buffer contains the entire string contents and is null terminated.
    /// The buffer is at least large enough to hold nMinBufferLength characters plus
    /// a null terminator. If nNumBufferLength is smaller than the length of the string,
    /// it is ignored and the entire string is available. If it is larger than string length,
    /// a larger buffer is allocated and user is able to modify that many characters and may 
    /// grow the string.
    /// Clients should call releaseBuffer() when they're done accessing the buffer, and they
    /// should not call any other methods (except an implicit call to the dtor) before then.
    /// But it's okay if the string is destroyed without releaseBuffer() having been called.
    /// </summary>
    /// <param name="nMinBufferLength">Number of characters that should fit in the buffer,
    /// not including the null terminator. 0 or negative will use the current string size</param>
    /// <returns>wchar_t pointer to the AcString's (null-terminated) character buffer.
    /// </returns>
    wchar_t *getBuffer( Adesk::Int32 nMinBufferLength = 0 )  // not including null . 0 = current string size
    {
        AcStrLOG(this,iLogMsg::dStr,L"getBuffer: %d",nMinBufferLength);

        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());    // should not be in getbuffer mode

        Adesk::UInt32 len = (Adesk::Int32)iGetLen();

        if ((nMinBufferLength > 0) && ((Adesk::UInt32)nMinBufferLength > len)) // growing the buffer
        {
            reserve((Adesk::UInt32)nMinBufferLength);
        }
        SetGetBuffer();    // flag we are in GetBuffer mode
        AcStrASSERT(DBGverify());
        return iGetBuff();
    }

    /// <summary>
    /// Use releaseBuffer() to end the use of a buffer allocated by the getBuffer() method.
    /// The pointer returned by getBuffer() is invalid after the call to releaseBuffer().
    /// </summary>
    /// <param name="nMinBufferLength">Sets the new length of the AcString.
    /// If -1 or any negative value, then the string's length is determined by the null terminator's index.
    /// Otherwise the new length is set to the minimum of nNewLength and the null
    /// terminator's index.
    /// </param>
    /// <returns>True if success, false on errors such as invalid length args or
    /// no previous call to getBuffer().</returns>
    bool releaseBuffer( Adesk::Int32 nNewLength = -1 )
    {
        AcStrLOG(this,iLogMsg::dStr,L"releaseBuffer: %d",nNewLength);

        AcStrASSERT( isGetBuffer() );    // must be in GetBuffer mode

        Adesk::UInt32 maxLen = (Adesk::UInt32) nNewLength;
        if (isSSO())    // getBuffer used a small size so we only have to look at our internal buffer
        {   // ignore invalid lengths, always clamp to max possible sso size
            if (maxLen >= (m_ssoSize-1))
                maxLen = m_ssoSize-1;
            Adesk::UInt32 len = 0;
            for (;(len < maxLen) && m_ssoBuff[len]; len++);
            m_ssoBuff[len] = 0; // set end of string
            m_len = len;        // save new length in sso mode This also clears getBuffer mode
        }
        else    // in buffer mode. Ignore invalid lengths, clamp to max allocated size
        {
            if (maxLen >= m_allocated)
                maxLen = m_allocated-1;
            Adesk::UInt32 len = 0;  // no matter what we will not overrun our buffer
            for (;(len < maxLen) && m_buffer[len]; len++);  // find end of string or clamp to nNewLength
            m_buffer[len] = 0; // set end of string
            setBuffLen(len);    // save len in buffer mode, clears getBuffer mode
        }
        //ClrGetBuffer();    // setting m_len above took care of this for non-prod
        AcStrASSERT(DBGverify());   // make sure we did all of this correctly
        return true;
    }

    // hash function can be used to generate hash for the string contents
    // note, see near header bottom, we provide specialization for std::hash
    Adesk::UInt64 hash() const noexcept
    {
        Adesk::UInt64 retval = computeHash(iGetBuff());
        return retval;
    }

#if defined(AcStrLogging)
    bool hasUTF8() const  // used for internal logging
    {
        return (!isSSO() && m_utf8) ? true : false;
    }

    class iLogMsg
    {
      public:
        static constexpr Adesk::UInt32 dStr       = 0x01;  // at destructor output string length and string
        static constexpr Adesk::UInt32 destructor = 0x02;  // this is a destructor call (used to track lifespan for statistics)

        ACBASE_PORT iLogMsg(const AcString *p, Adesk::UInt32 flags, const wchar_t *fmt, ...);
        ACBASE_PORT ~iLogMsg();

        ACBASE_PORT void addDMsg( const wchar_t *fmt, ...);
      private:
        const AcString *m_acstring = nullptr;
        std::wstring    m_addmsg;   // add message to display at destruction
        Adesk::UInt32   m_flags    = 0;
    };
#endif


private:
    // private data. ref counting removed. A string is either stored:
    //   SSO inline as part of this data up to m_ssoSize-1 characters (leaving room for null)
    //   as a pointer to an allocated buffer.  On the size, m_buffMode bit will tell you if in SSO mode or allocated buffer mode.
    // When asked to return an utf8 pointer - we always switch to buffer mode. the UTF8 string data allocated and stored in m_utf8
    // that data is valid until the next modification of this class.

    // set class size in bytes. Everything computes from that.
    // for platforms that have 4 byte wchar_t we use a larger class but it holds less characters. Tradeoff.
    static constexpr Adesk::UInt32 m_ClassSize    = (sizeof(wchar_t) == 4) ? 64 : 48;  // this is the size of the class.
    static constexpr Adesk::UInt32 m_ssoSize      = (m_ClassSize - sizeof(Adesk::UInt64)) / sizeof(wchar_t);  // num of sso wchar_t includes null
    static constexpr Adesk::UInt32 m_alignAlloc   = 32;  // MUST be power of 2. buffer mode alignment size. Align on 32 wchar_t boundary
    static constexpr Adesk::UInt32 m_bufferMode   = 0x80000000;  // high bit length set when using allocated buffer
    static constexpr Adesk::UInt32 m_getBuffMode  = 0x40000000;  // bit set when in GetBuffer mode (non-prod only)
    static constexpr Adesk::UInt32 m_maxStrLen    = m_getBuffMode-1;

    // m_len always has the length of the current string not including the trailing null char. 
    // m_len == 0 means empty string, a null char is stored in sso and c_str will return pointer to it.
    // if m_buffMode bit is set, then this is not using SSO mode and we have a pointer to the buffer
    // generally a string size < m_ssoSize will be in SSO mode but calls from GetBuffer and a utf8 pointer
    // will switch into buffer mode. Thus you must look at the m_buffMode bit on m_len
    //
    // note. if AcStringBADSTRDebug is defined, the first 8 bytes are the debug string, followed by the normal data
    // memory layout:       Bytes 0 - 3: Always 0. Used as string by [] operator for invalid index
    //                      Bytes 4-7: is the length of the stored string. Upper 2 bits are control
    //      sso mode:       Bytes 8 - mClassSize-1: wchar_t's null terminated for the string.
    //   buffer mode:       Bytes 8-15 (8-11 32 bit wasm):  pointer to allocated buffer
    //                      Bytes 16-23 (12-15 32 bit wasm): pointer to utf8 buffer
    //                      Bytes 24-27 (16-19 32 bit wasm): number of wchar_t's allocated including null in buffer

    // debugging aid. Start class data with string to cover the case of variadic printf type of usage
    #ifdef AcStringBADSTRDebug
    union
    {
        Adesk::UInt64 m_bad64;       // ensure 8 byte aligned
        wchar_t       m_badstr[sizeof(Adesk::UInt64)/sizeof(wchar_t)];
    };
    #endif
    union   // first 8 bytes. First 4 are always 0
    {
        Adesk::UInt64  m_empty;         // gives fast way clear m_nullstr and m_len and ensures 8 byte alignment
        struct {
            Adesk::UInt32  m_nullstr;       // always 0 empty string for refAt and variadic printf if passed by value by accident
            Adesk::UInt32  m_len;           // next 4 bytes are the len of string and control bits
        };
    };
    union
    {
        wchar_t       m_ssoBuff[m_ssoSize]; // sso string starts on 8 byte boundary
        struct  // buffer mode view of data. 
        {
            wchar_t       *m_buffer;      // array of wchar_t
            Adesk::UInt32 *m_utf8;        // if used, first 4 bytes is allocated size
            Adesk::UInt32  m_allocated;   // size of m_buffer in wchar_t (includes null char space)
        };
    };

    void checkSize()    // not used, just here for static_assert to check that we are correctly aligned
    {
    #ifdef AcStringBADSTRDebug
        static_assert(sizeof(AcString) == m_ClassSize+sizeof(Adesk::UInt64),"Invalid AcString class size"); // make sure class size is correct
        static_assert(offsetof(AcString,m_len)       == 4+sizeof(Adesk::UInt64),"Invalid AcString m_len offset");
    #else
        static_assert(sizeof(AcString) == m_ClassSize,"Invalid AcString class size"); // make sure class size is correct
        static_assert(offsetof(AcString,m_len)       == 4,"Invalid AcString m_len offset");
    #endif
        static_assert(offsetof(AcString,m_empty)     == offsetof(AcString,m_nullstr), "Invalid AcString m_empty/m_nullstr offset");
        static_assert(offsetof(AcString,m_ssoBuff)   == offsetof(AcString,m_buffer), "Invalid AcString m_ssoBuff/m_buffer offset");
    }

    // leaving in all builds since some td utils are in non-prod. Implementation in AcString.cpp does nothing in prod
    ACBASE_PORT static bool iASSERTMsg( const wchar_t *msg, const wchar_t *file, Adesk::Int32 linenum );

    // return true if provided number of character can be stored in SSO mode
    static constexpr bool canSSO( Adesk::UInt32 newlen ) noexcept { return newlen < m_ssoSize; } 

    // return current length of string.
    Adesk::UInt32 iGetLen() const noexcept { return (m_len & ~(m_bufferMode | m_getBuffMode)); }

    // set length and buffer mode. Getbuffer mode is cleared
    void setBuffLen( Adesk::UInt32 len)
    {
        AcStrASSERT( len < m_maxStrLen ); // check for too long and it overrides the control bits
         m_len = len | m_bufferMode;
    }
    void iSetLen( Adesk::UInt32 len )
    {
        AcStrASSERT( len < m_maxStrLen ); // check for too long and it overrides the control bits
        m_len = (m_len & (m_bufferMode | m_getBuffMode)) | len;
    }

    // look at external pointer and see if it is within our storage to detect self reference
    bool isSelf( const wchar_t *p ) const noexcept
    {
        if (isSSO())
            return (p >= m_ssoBuff) && (p < &(m_ssoBuff[m_ssoSize]));
        return (p >= m_buffer) && (p < (m_buffer + iGetLen()));
    }

    // return true if we are the same object
    bool isSelf( const AcString & object ) const noexcept
    {
        return this == &object;     // true if same object
    }

    // set to empty string, don't change sso/buffer mode
    void setNull() noexcept
    {
        iSetLen(0);         // empty
        *iGetBuff() = 0;    // empty string
    }

    // return const pointer to internal beginning of string, either sso or buffer mode
    const wchar_t * iGetBuff() const noexcept
    {
        return isSSO() ? m_ssoBuff : m_buffer;
    }

    // return non-const pointer to internal beginning of string, either SSO or buffer mode
    wchar_t * iGetBuff() noexcept
    {
        return isSSO() ? m_ssoBuff : m_buffer;
    }

    // return true SSO mode, false buffer mode
    bool isSSO() const noexcept
    {
        return (m_len & m_bufferMode) == 0;
    }

    // release utf8 pointer if we have one. Must be in buffer mode
    void releaseUTF8()
    {
        AcStrASSERT( !isSSO() );
        if (m_utf8)
        {
            ::acHeapFree(nullptr, m_utf8);
            m_utf8 = nullptr;
        }
    }

    // return false if none of the chars match, true if ch is in the string
    static constexpr bool isOneOf( wchar_t ch, const wchar_t * __restrict pwsz ) noexcept
    {
        for(;*pwsz;pwsz++)
            if (*pwsz == ch)
                return true;
        return false;
    }

    // return true if sub is a substring of src
    static constexpr bool isSubStr( const wchar_t * __restrict src, const wchar_t * __restrict sub ) noexcept
    {
        for (;*sub;src++,sub++)
        {
            if (*src != *sub)
                return false;
        }
        return true;
    }

    // return true if sub is a substring of src ignoring case. 
    static constexpr bool isSubStrLC( const wchar_t * __restrict src, const wchar_t * __restrict sub ) noexcept
    {
        for (;*sub;src++,sub++)
        {
            if (toLower(*src) != toLower(*sub))
                return false;
        }
        return true;
    }

    // return true if all chars are <= 0x7f
    // pass in valid length to scan
    static constexpr bool is7Bit( const wchar_t * pwsz, Adesk::UInt32 len) noexcept
    {
        for (Adesk::UInt32 i = 0; (i < len) && pwsz[i]; i++)
        {
            if (pwsz[i] > 0x7f)
                return false;
        }
        return true;
    }

    // return true if all chars >= 0x20 and <= 0x7f
    // pass in valid length to scan
    static constexpr bool isAscii( const wchar_t *pwsz, Adesk::UInt32 len ) noexcept
    {
        for (Adesk::UInt32 i = 0; (i < len) && pwsz[i]; i++)
        {
            if ((pwsz[i] < 0x20) || (pwsz[i] > 0x7f))
                return false;
        }
        return true;
    }

    // compilers don't like this being in template with constexpr so we have both versions
    // return C style string length, not exceeding maxlen chars. Does not include null
    static constexpr Adesk::UInt32 cstrLen( const wchar_t * __restrict str, Adesk::UInt32 maxlen ) noexcept
    {
        Adesk::UInt32 len = 0;
        for (;(len < maxlen) && str[len]; len++);
        return len;
    }

    // return C style string length, not exceeding maxlen chars. Does not include null
    static constexpr Adesk::UInt32 cstrLen( const uint8_t * __restrict str, Adesk::UInt32 maxlen ) noexcept
    {
        Adesk::UInt32 len = 0;
        for (;(len < maxlen) && str[len]; len++);
        return len;
    }

    // return C style string length. Does not include null
    static constexpr Adesk::UInt32 cstrLen( const wchar_t * __restrict str ) noexcept
    {
        Adesk::UInt32 len = 0;
        for (;str[len]; len++);
        return len;
    }

    // align on m_alignAlloc chars boundary
    static constexpr Adesk::UInt32 alignLen( Adesk::UInt32 len ) noexcept
    {
        return (len + m_alignAlloc - 1) & ~(m_alignAlloc - 1);
    }

    // if debug mode we keep track of the getbuffer mode to make sure a GetBuffer has a matching ReleaseBuffer
    bool ClrGetBuffer()
    {
        m_len &= ~m_getBuffMode;
        return true;
    }
    bool SetGetBuffer()
    {
        m_len |= m_getBuffMode;
        return true;
    }
    bool isGetBuffer() const
    {
        return m_len & m_getBuffMode;
    }


    // These high speed string copy methods promise the compiler that source and destination never overlap in any way.
    // This gives the compiler complete freedom in how to generate code and reorder any of the logic
    // fast copy of len characters - no null checks. does nothing with 0 length
    // note that some compilers don't like template with constexpr so we define the ones we need
    
    static constexpr void fstrcpy( wchar_t * __restrict dest, const wchar_t * __restrict src, Adesk::UInt32 len ) noexcept
    {
        for (Adesk::UInt32 i = 0; i < len; dest[i] = src[i], i++);
    }

    static constexpr void fstrcpy( uint8_t * __restrict dest, const wchar_t * __restrict src, Adesk::UInt32 len ) noexcept
    {
        for (Adesk::UInt32 i = 0; i < len; dest[i] = (uint8_t) src[i], i++);
    }

    static constexpr void fstrcpy( uint8_t * __restrict dest, const uint8_t * __restrict src, Adesk::UInt32 len ) noexcept
    {
        for (Adesk::UInt32 i = 0; i < len; dest[i] = src[i], i++);
    }

    // string copy, no length, stop (and copy) at the null. Correctly copies null char of empty string
    static constexpr void fstrcpy( wchar_t * __restrict dest, const wchar_t * __restrict src) noexcept
    {
        for (; (*dest++ = *src++) != 0;);
    }

    // return const ref to character at nIndex
    // if ivalid index, return const ref to null string
    const wchar_t &refAt( Adesk::UInt32 nIndex ) const
    {
        AcStrASSERT(DBGverify());
        AcStrASSERT(!isGetBuffer());

        AcStrASSERT((Adesk::UInt32)nIndex <= iGetLen() );
        return (nIndex < iGetLen()) ? iGetBuff()[nIndex] : *((const wchar_t *)(&m_nullstr));
    }

    // move given dest empty
    // client wchar_t and utf8 pointers are still valid after move
    void iMove( AcString & acs )
    {
        AcStrASSERT( isSSO() );
        AcStrASSERT( isEmpty() );  // callers must clear out any allocated buffers
        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());

        m_len = acs.m_len;  // get length and what mode
        ClrGetBuffer();     // asserted on this but make sure its off
        if (isSSO())        // SSO mode, just copy the chars and null
        {
            Adesk::UInt32 len = iGetLen();    // just in case utf8 data
            fstrcpy( m_ssoBuff, acs.m_ssoBuff, len ); // use getLen just in case non-prod and in GetBuffer mode
            m_ssoBuff[len] = 0;         // force null term - handles 0 length
        }
        else  // source was in buffer mode so dest will stay in buffer mode
        {
            m_allocated = acs.m_allocated;  // keep same allocated size
            m_buffer    = acs.m_buffer;     // take ownership of the buffer
            m_utf8      = acs.m_utf8;       // keep utf8 data valid
        }
        acs.m_empty = 0;         // source is empty in SSO mode
        acs.m_buffer = nullptr;  // m_ssoBuff[0] = 0; but faster than a word write

        AcStrASSERT(DBGverify());
        AcStrASSERT(acs.DBGverify());
    }

    // from an empty container reserve the following size
    // useful when callers create an empty string object to then fit
    void emptyReserve(Adesk::UInt32 nCapacity)
    {
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        AcStrASSERT(isSSO());

        if (nCapacity >= m_ssoSize)
        {
            reserveBufferFromEmpty( nCapacity );
            AcStrASSERT(DBGverify());
        }
    }

    // in SSO mode. We want to reserve size chars which is too large to fit in SSO mode, so 
    // switch to buffer mode reserving size chars and copy existing string into buffer
    // size does not include null char
    // we can pass in the existing length when converting to use utf8 mode
    void convertSSOtoBuffer( Adesk::UInt32 size )
    {
        AcStrASSERT(isSSO());           // must be in sso mode
        AcStrASSERT( !isGetBuffer() );  // cannot be in GetBuffer mode
        AcStrASSERT( size >= iGetLen() );
        makeAndCopy( m_ssoBuff, m_len, size );
    }

    
    // make a buffer at least the allocSize chars + 1 for null. Copy the string into it, make that buffer the class
    // working in buffer mode
    // src may be our current m_ssoBuff so copy first before setting the non-sso mode variables
    void makeAndCopy( const wchar_t *src, Adesk::UInt32 len, Adesk::UInt32 iallocSize )
    {
        AcStrASSERT(DBGverify());
        Adesk::UInt32 allocSize = alignLen(iallocSize+1);  // size we will allocate in wchars. Add 1 for null, and align
        AcStrASSERT( allocSize < m_maxStrLen );
        wchar_t *p = (wchar_t *)::acHeapAlloc(nullptr,allocSize * sizeof(wchar_t));
        fstrcpy(p, src, len);  // copy string but no null
        p[len] = 0;       // set null

        // now that data has been copied, its ok to set these (they share same space as sso chars)
        setBuffLen(len);          // set length as buffer mode, GetBuffer clear
        m_buffer = p;             // save pointer
        m_utf8 = nullptr;         // caller must have deleted if in that mode
        m_allocated = allocSize;  // allocated size
        AcStrASSERT(DBGverify());
    }

    // Used to reserve from empty
    void reserveBufferFromEmpty( Adesk::UInt32 size )
    {
        AcStrASSERT( isSSO() );
        AcStrASSERT( isEmpty() );
        AcStrASSERT( size < m_maxStrLen );
        setBuffLen(0);        // set 0 length buffer mode
        m_utf8 = nullptr;    // make sure cleared out now in buffer mode
        m_allocated = alignLen(size+1);  // size we will allocate in wchars. Add 1 for null, and align
        AcStrASSERT( m_allocated  < m_maxStrLen );
        m_buffer = (wchar_t *)::acHeapAlloc(nullptr, m_allocated * sizeof(wchar_t));
        m_buffer[0] = 0;    // put initial end of string.
    }

    // in buffer mode. New size is greater than allocated size. size provided does not include null char
    // make a new buffer and copy the string. Size provided does not include the null char
    // given this is a resize, the input size does not take into account any exponential growth
    // so it gets adjusted here
    void bufferResize( Adesk::UInt32 size )
    {
        AcStrASSERT(!isSSO());              // no longer in GetBuffer mode in non-prod
        AcStrASSERT( !isGetBuffer() );  // must not be in GetBuffer mode
        AcStrASSERT( size > iGetLen() );
        AcStrASSERT( size >= m_allocated );
        releaseUTF8();  // we are losing the utf8 buffer

        // exponential growth just in case we are hitting edge case of string that grows really large
        Adesk::UInt32 allocsize = (m_allocated * 3) >> 1;  // current size * 1.5 - it will not overflow our space since max size is 1GB
        if (allocsize < size)
            allocsize = size;   // makeAndCopy will then add one for null and align up this size on boundary

        void *p = m_buffer;     // save old buffer
        makeAndCopy( m_buffer, iGetLen(), allocsize );
        ::acHeapFree(nullptr,p);     // free old pointer
    }

    // internal bits for parseVal() and copyFromInt. eFormat enums must be converted by mapeFormat
    static constexpr Adesk::UInt32 kHowSigned = 0x01;   // set if signed, clear for unsigned
    static constexpr Adesk::UInt32 kHowDeci   = 0x02;   // set if decimal
    static constexpr Adesk::UInt32 kHowHex    = 0x04;   // set if hex
    static constexpr Adesk::UInt32 kHowBinary = 0x08;   // no longer used or supported
    static constexpr Adesk::UInt32 kHow64     = 0x10;   // no longer used, ignored all ints are considered 64 bit

    // empty class setup using given number of chars. Manually put the null term
    // len is the actual number of chars in pwsz not including null. It may be smaller
    // to truncate the string, never larger
    void initWithLen( const wchar_t * __restrict pwsz, Adesk::UInt32 len, Adesk::UInt32 allocLen )
    {
        AcStrASSERT( pwsz );
        AcStrASSERT( len <= cstrLen(pwsz) );
        AcStrASSERT( len <= allocLen );
        AcStrASSERT( DBGverify() ); 

        if (canSSO(allocLen) && canSSO(len)) // added 2nd test for len due to MSVC release compile issue.
        {
            fstrcpy(m_ssoBuff,pwsz,len);
            m_ssoBuff[len] = 0;
            m_len = len;
        }
        else
        {
            makeAndCopy( pwsz, len, allocLen );
        }
        AcStrASSERT(DBGverify());
    }

    // existing but replace with the provided string.
    // mainly used from assignment
    // utf8 data is removed from dest
    // pwsz will never self reference so its safe to modify our variables before copy
    void copyWithLen( const wchar_t * __restrict pwsz, Adesk::UInt32 len )
    {
        AcStrASSERT( pwsz );
        AcStrASSERT( len <= cstrLen(pwsz) );
        AcStrASSERT(DBGverify());

        if (isSSO())    // dest is currently in sso
        {
            m_empty = 0;    // start off empty
            m_buffer = nullptr; 
            initWithLen( pwsz, len, len);  // and treat as a copy
        }
        else    // currently in buffer mode
        {
            AcStrASSERT( !isGetBuffer());     // must not be in get buffer mode
            if (len >= m_allocated)             // existing buffer too small
            {
                ::acHeapFree(nullptr, m_buffer);
                m_buffer = nullptr;     // no buffer
                releaseUTF8();         // going to lose the utf8 data
                m_empty = 0;     // sso mode, empty

                initWithLen( pwsz, len, len);  // and treat as a fresh copy
            }
            else    // fits in existing buffer
            {
                setBuffLen(len);
                fstrcpy(m_buffer,pwsz,len);
                m_buffer[len] = 0;
            }
        }
        AcStrASSERT(DBGverify());
    }

    // append the string to our end
    // it is possible that the source is ourself or a self substring!
    void iappend( const wchar_t *src, Adesk::UInt32 len )
    {
        AcStrASSERT( src );
        AcStrASSERT(DBGverify());

        if (len)    // must have something to append
        {
            Adesk::UInt32 curlen = iGetLen();
            Adesk::UInt32 newlen = curlen + len;  // new combined length
            if (isSSO())
            {
                if (newlen < m_ssoSize)
                {
                    fstrcpy(m_ssoBuff+curlen,src,len);  // copy to end
                    m_ssoBuff[newlen] = 0;              // set new end null
                    iSetLen( newlen );                  // set length
                    AcStrASSERT(DBGverify());
                    return;
                }
                convertSSOtoBuffer( newlen );       // after append it does not fit, so switch to buffer, reserve enough space
            }
            else if (m_allocated <= newlen)
                bufferResize( newlen );             // not enough room, grow buffer
            fstrcpy(m_buffer+curlen,src,len);       // append
            m_buffer[newlen] = 0;                   // set new end null
            iSetLen( newlen );                      // set new length
        }
        AcStrASSERT(DBGverify());
    }

    // append string to current. It will fit, no mode change, no reallocation
    // you are ensured to have a valid input and length to append
    // useful after a resize to avoid fit checks
    void iappendWillFit(const wchar_t *src, Adesk::UInt32 addlen)
    {
        AcStrASSERT( src );
        AcStrASSERT(DBGverify());
        Adesk::UInt32 len = iGetLen();
        wchar_t *buff = iGetBuff();
        fstrcpy(buff+len,src,addlen); // append, does not copy null
        buff[len + addlen] = 0;       // set new string end
        iSetLen(len + addlen);        // set new length
        AcStrASSERT(DBGverify());
    }

    // return utf8 pointer. We hold onto the pointer and manage its lifespan
    const char *iutf8Ptr()
    {
        AcStrASSERT(!isGetBuffer());
        AcStrASSERT(DBGverify());
        if (isEmpty())
            return "";

        Adesk::UInt32 slen = iGetLen();    // wide length
        if (isSSO())                  // if in SSO mode convert to buffer mode to hold utf8 data
            convertSSOtoBuffer(slen);

        if (is7Bit(m_buffer,slen))   // we can convert to utf8 manually, 1:1
        {
            if (m_utf8 && (*m_utf8 < slen)) // have one but not big enough
            {
                releaseUTF8();
            }
            if (m_utf8 == nullptr)  // need to allocate
            {
                Adesk::UInt32 allocSize = alignLen(slen+1+sizeof(Adesk::UInt32));   // room for null and allocated size
                m_utf8 = (Adesk::UInt32 *)::acHeapAlloc(nullptr, allocSize);
                *m_utf8 = allocSize - 1 - sizeof(Adesk::UInt32);             // max number of utf8 chars it can hold not including null
            }

            fstrcpy(reinterpret_cast<uint8_t *>(m_utf8+1),m_buffer,slen+1);  // +1 also copies the null
            AcStrASSERT(DBGverify());
            return reinterpret_cast<const char *>(m_utf8+1);
        }
        else  // unicode data requires utf8 conversion
        {
            return genericUTF8Ptr();    // generic, use pal to convert
        }
    }

    // lower case support. Use std if not 7bit
    // will not constexpr if chars > 0x7f
    static constexpr Adesk::UInt32 toLower( Adesk::UInt32 ch ) noexcept
    {
        if ((ch >= 'A') && (ch <= 'Z'))
            ch += ('a' - 'A');       // latin upper case to lower case
        else if (ch > 0x7f)
            ch = static_cast<Adesk::UInt32>(std::towlower( static_cast<std::wint_t>(ch) ));
        return ch;
    }

    // upper case support. Use std if not 7bit
    // will not constexpr if chars > 0x7f
    static constexpr Adesk::UInt32 toUpper( Adesk::UInt32 ch ) noexcept
    {
        if ((ch >= 'a') && (ch <= 'z'))
            ch -= ('a' - 'A');      // latin lower case to upper case
        else if (ch > 0x7f)
            ch = static_cast<Adesk::UInt32>(std::towupper( static_cast<std::wint_t>(ch) ));
        return ch;
    }

    // compare left to right converting to lower case. <0: left < right, 0: left == right, >0: left > right
    // will not constexpr if chars > 0x7f
    static constexpr Adesk::Int32 compareLCtoLC( Adesk::UInt32 left, Adesk::UInt32 right ) noexcept
    {
        return static_cast<Adesk::Int32>(toLower(left)) - static_cast<Adesk::Int32>(toLower(right));
    }

    // map from eFormat to  the parse bits. Can be done at compile time
    static constexpr Adesk::UInt32 mapeFormat( eFormat flags ) noexcept
    {
        switch (flags)
        {
            case kSigned:
                return kHowSigned;
            case kUnSigned:
                return 0;
            case kHex:
                return kHowHex;
            case kHexSigned:
                return kHowHex | kHowSigned;
        }
        return 0;
    }

    // computes 64 bit hash using FNV1a 64 bit.
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    // http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a
    // nullptr is not allowed
    static constexpr Adesk::UInt64 computeHash( const wchar_t *pws ) noexcept
    {
        Adesk::UInt64 hash = 14695981039346656037ULL; // 64 bit offset_basis
        for (;*pws; pws++)
        {
            Adesk::UInt64 ch = static_cast<Adesk::UInt64>(*pws);
            hash = fnv1a64char((ch & 0xff), hash);          // low word low byte
            hash = fnv1a64char(((ch >> 8) & 0xff), hash );  // low word high byte
            #if (__cplusplus >= 201703L)    // C++17 or higher
                if constexpr (sizeof(wchar_t)==4)  // compile time large wchar_t
                {
                    hash = fnv1a64char(((ch >> 16) & 0xff), hash );  // high word low byte
                    hash = fnv1a64char(((ch >> 24) & 0xff), hash );  // high word high byte
                }
            #else   // not C++17, we treat it as 4 byte wchar_t, no portable way to compile time exclude without compiler specific warnings
                hash = fnv1a64char(((ch >> 16) & 0xff), hash );  // high word low byte
                hash = fnv1a64char(((ch >> 24) & 0xff), hash );  // high word high byte
            #endif
        }
        return hash;
    }

    // FNV-1a hash function - combine the next byte
    static constexpr Adesk::UInt64 fnv1a64char(Adesk::UInt64 ch, Adesk::UInt64 hash) noexcept
    {
        // 64 bit FNV_prime
        return (hash ^ ch) * 1099511628211ULL;
    }


    #if !defined(NDEBUG)
    // non-prod verify integrity
    bool DBGverify( void ) const
    {
        Adesk::UInt32 len = 0;
        // make sure the current string fits in the allowed space
        // there must be a null char terminating the string
        if (isSSO())
        {
            len = cstrLen( m_ssoBuff, m_ssoSize ); // should find null
            AcStrASSERT( len < m_ssoSize ); // make sure we found null
        }
        else
        {
            len = cstrLen( m_buffer, m_allocated ); // should find null
            AcStrASSERT( len < m_allocated );    // make sure we found null
            if (m_utf8)
            {
                Adesk::UInt32 u8alloc = *m_utf8;  // size of buffer
                Adesk::UInt32 u8clen = cstrLen((const uint8_t *)(m_utf8+1),u8alloc+1); // should find null
                AcStrASSERT( u8clen <= u8alloc ); // must have found null
            }
        }
      
        if (!isGetBuffer()) // only have valid len if not in getbuffer mode
        {
            AcStrASSERT( len == iGetLen() );
        }
        return true;
    }
    #endif


    // utility class to turn UTF8 input into wchar_t buffers
    // only allocates memory if output is too large
    class UTF8converter
    {
      public:
        UTF8converter( const Adesk::UInt8 * __restrict src, Adesk::UInt32 maxlen, const AcString & AcS )  // fast conversion for reasonable length ascii strings
        {
            Adesk::UInt32 len = 0;
            Adesk::UInt32 maxLoop = maxlen;
            if (maxLoop >= m_maxOutSize-1)
                maxLoop = m_maxOutSize-1;   // largest offset for final null char
            // try and manually convert. if all ascii and fits in our output buffer, then we can. Otherwise, have to use generic version
            for (;;len++)
            {
                Adesk::UInt8 ch = *src;
                if (!ch)
                    break;  // done
                if ((ch > 0x7f) || (len >= maxLoop))   // does not fit or non ascii
                {
                    genericConverter( src, maxlen, AcS );  // handles long strings, non-ascii
                    return;
                }
                m_outputBuff[len] = ch;
            }
            m_outputBuff[len] = 0;
            m_outlen = len; 
        }

        ~UTF8converter()
        {
            if (m_outputPtr) // only set by genericConverter for long strings
                ::acHeapFree( nullptr, m_outputPtr );
            if (m_in8ptr)   // only set by generic Converter for long strings
                ::acHeapFree( nullptr, m_in8ptr );
        }

        const wchar_t *getBuff() const { return m_outputPtr ? m_outputPtr : m_outputBuff; }
        Adesk::UInt32  getLen() const { return m_outlen; }
      private:
        ACBASE_PORT void genericConverter( const Adesk::UInt8 *src, Adesk::UInt32 maxlen, const AcString &AcS ); // AcString.cpp

        static constexpr Adesk::UInt32 m_maxOutSize = 512;   // largest we store locally without allocating result
        Adesk::UInt8 *m_in8ptr    = nullptr;      // only used if we had to truncate input and its too long
        wchar_t      *m_outputPtr = nullptr;      // wide output if too long
        Adesk::UInt32 m_outlen    = 0;            // output size

        wchar_t       m_outputBuff[m_maxOutSize];  // wide output
        Adesk::UInt8  m_in8buff[m_maxOutSize];     // only used if we truncated input
    };

    // convert 64 bit int into wide char string based on flags.
    // can be computed entirely at compile time for literal values
    class valToString
    {
      public: 
        constexpr valToString( Adesk::UInt32 nFlags, Adesk::Int64 sval )
        {
            Adesk::Int32 i = kBufSiz - 1;   // build backwards from
            m_outBuf[kBufSiz-1] = 0;        // set null end
            bool bInsertMinus = false;
            if (nFlags & kHowSigned)  // user wants value treated as signed
            {
                if (sval < 0)
                {
                    sval = -sval;
                    bInsertMinus = true;
                }
            }
            Adesk::UInt64 val = (Adesk::UInt64)sval;    // now only work with unsigned
            do
            {
                --i;
                if (nFlags & kHowHex)
                {
                    Adesk::UInt32 n = (Adesk::UInt32)(val % 16);
                    m_outBuf[i] = (wchar_t)((n > 9) ? (n + L'a' - 10) : (n + L'0'));
                    val >>= 4;
                }
                else
                {
                    Adesk::UInt32 n = (Adesk::UInt32)(val % 10);
                    m_outBuf[i] = (wchar_t)(n + L'0');
                    val /= 10;
                }
            }
            while (val);

            if (bInsertMinus) {
                m_outBuf[--i] = '-';
            }
            m_StartIndex = (Adesk::UInt32) i;
        }

        constexpr const wchar_t *getBuff() const
        {
            return m_outBuf + m_StartIndex;
        }

        constexpr Adesk::UInt32 getLen() const
        {
            return kBufSiz - m_StartIndex - 1;
        }


      private:
        static constexpr Adesk::Int32 kBufSiz = 32; // 32 is more than needed for all formats
        wchar_t       m_outBuf[kBufSiz] = { 0 };     // plenty of room to build result without overflow
        Adesk::UInt32 m_StartIndex = kBufSiz -1;
    };

    // string parsing support - internal only.
    ACBASE_PORT Adesk::Int64 parseVal( Adesk::UInt32 nHow, Adesk::UInt32 nFlags) const;
    Adesk::Int64 parseError( const char *pszErrString, Adesk::UInt32 nFlags ) const;
    Adesk::Int64 parseEmpty( Adesk::UInt32 nflags ) const;
    Adesk::Int64 parseInvalidChar( Adesk::UInt32 nflags ) const;

    static Adesk::Int32 fmtHelper(void *pCookie, const wchar_t *pszFrom, size_t nLen); // internal AcString.cpp
    AcString iformatV(const wchar_t *pszFmt,  va_list args) const;   // internal AcString.cpp

    ACBASE_PORT static Adesk::Int32 collateNoCaseGeneric(const wchar_t *left, const wchar_t *right);

    ACBASE_PORT Adesk::UInt64 convertHandleToU64( const AcDbHandle &h );

    ACBASE_PORT const char *genericUTF8Ptr();

};


#ifdef AC_ACARRAY_H
typedef
AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#endif

//
// Global operator declarations
//

/// <summary>Compare an AcString and a Unicode character for equality.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch and acs are equal, else false.</returns>
inline bool operator == (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator == (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) == 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Compare an AcString and a string of Unicode characters for equality.</summary>
/// <param name="pwsz">input character to the string of Unicode characters</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz and acs are equal, else false.</returns>
inline bool operator == (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator == (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) == 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Compare an AcString and a Unicode character for non-equality.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch and acs are not equal, else false.</returns>
inline bool operator != (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator != (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) != 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Compare an AcString and a string of Unicode characters for non-equality.</summary>
/// <param name="pwsz">input ptr to the string of Unicode characters</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz and acs are not equal, else false.</returns>
inline bool operator != (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator != (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) != 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Return whether a Unicode character is greater than an AcString.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch is greater than acs, else false.</returns>
inline bool operator >  (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator > (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) < 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Return whether a string of Unicode characters is greater than an AcString.</summary>
/// <param name="pwsz">input pointer to the string of Unicode characters</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz is greater than acs, else false.</returns>
inline bool operator >  (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator > (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) < 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a Unicode character being greater than or equal to an AcString.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch is greater than or equal to acs, else false.</returns>
inline bool operator >= (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator >= (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) <= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a string of Unicode characters being greater than/equal to an AcString.</summary>
/// <param name="pwsz">input string to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz is greater than or equal to acs, else false.</returns>
inline bool operator >= (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator >= (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) <= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a Unicode character being less than an AcString.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch is less than acs, else false.</returns>
inline bool operator <  (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator < (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) > 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a string of Unicode characters being less than an AcString.</summary>
/// <param name="pwsz">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz is less than acs, else false.</returns>
inline bool operator <  (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator < (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) > 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a Unicode character being less than or equal to an AcString.</summary>
/// <param name="wch">input character to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if wch is less than or equal to acs, else false.</returns>
inline bool operator <= (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator <= (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    bool retval = acs.compare(wch) >= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Check for a string of Unicode characters being less than/equal to an AcString.</summary>
/// <param name="pwsz">input characters to compare</param>
/// <param name="acs">input reference to the AcString</param>
/// <returns>True if pwsz is less than or equal to acs, else false.</returns>
inline bool operator <= (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator <= (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    bool retval = acs.compare(pwsz) >= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

/// <summary>Copy an AcString and insert a Unicode characters in front of it.</summary>
/// <param name="wch">input characters to insert</param>
/// <returns>An AcString consisting of the concatenation of wch and acs.</returns>
inline AcString operator + (wchar_t wch, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator + (wchar_t, const AcString &): %d, \"%ls\"",wch, acs.kwszPtr());
    AcString retval = acs.precat(wch);
    AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
    return retval;
}

/// <summary>Copy an AcString and insert a string of Unicode characters in front of it.</summary>
/// <param name="pwsz">input pointer to the string of characters to insert</param>
/// <returns>An AcString consisting of the concatenation of pwsz and acs.</returns>
inline AcString operator + (const wchar_t *pwsz, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator + (const wchar_t *, const AcString &): \"%ls\", \"%ls\"",pwsz?pwsz:L"(nullptr)", acs.kwszPtr());
    AcString retval = acs.precat(pwsz);
    AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
    return retval;
}

// We can do inline operators that deal with CStrings, without getting
// into binary format dependencies.  Don't make these out-of-line
// functions, because then we'll have a dependency between our
// components and CString-using clients.
//
#if defined(ENABLE_ACSTRING_CSTRING_OPERATORS)
#if defined(_AFX) && !defined(__cplusplus_cli)
// Global CString-related operators
inline bool operator == (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator == (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) == 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

inline bool operator != (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator != (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) != 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

inline bool operator >  (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator > (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) < 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

inline bool operator >= (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator >= (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) <= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

inline bool operator <  (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator < (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) > 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

inline bool operator <= (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator <= (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    bool retval = acs.compare(csw) >= 0;
    AcStrLOGADD(L"%d",(int)retval);
    return retval;
}

#ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline AcString operator + (const CStringW & csw, const AcString & acs)
{
    AcStrLOG(nullptr,0,L"operator + (const CStringW &, const AcString &): \"%ls\", \"%ls\"",(const wchar_t *)csw, acs.kwszPtr());
    AcString retval = acs.precat((const wchar_t *)csw);
    AcStrLOGADD(L"\"%ls\"",retval.kwszPtr());
    return retval;
}
#endif // DISABLE_CSTRING_PLUS_ACSTRING
#endif // defined(_AFX) && !defined(__cplusplus_cli)
#endif // ENABLE_ACSTRING_CSTRING_OPERATORS

// specialization of std::hash so AcString can be used directly with std containers that use hash
// without having to define a custom hasher
// meets all requirments from https://en.cppreference.com/w/cpp/utility/hash
template <>
struct std::hash<AcString>
{
    std::size_t operator()(const AcString &key) const noexcept
    {
        return static_cast<std::size_t>(key.hash());
    }
};


#endif // !_Ac_String_h
