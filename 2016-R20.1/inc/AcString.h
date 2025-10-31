
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _Ac_String_h_
#define _Ac_String_h_

#include "acbasedefs.h"
#include "adesk.h"
#include "AcHeapOpers.h"
#include "AdAChar.h"
#pragma pack (push, 1)

class AcDbHandle;

// Notes:
// 1. All "char" arguments are assumed to be ansi codes in the current
//    code page, unless otherwise specified to be utf-8.
//
// 2. In places where a single (ansi) char value is passed, the value
//    cannot be a leading byte of a double-byte char, except
//    where noted.
//
// 3. All wchar_t arguments are assumed to be "widechar" Unicode values.
//
// 4. Many methods and operators taking ansi (const char *) arguments may
//    be phased out in the future. Clients should use Unicode strings.
//
class AcString : public AcHeapOperators
{
  public:
    //
    // Constructors and destructor
    //
    // Default ctor, initializes to empty string.
    ACBASE_PORT AcString();

    // Initialize with a single character.
    // ch : input (ansi) character
    ACBASE_PORT AcString(char ch);

    // Initialize with a single Unicode character
    // wch : input character
    ACBASE_PORT AcString(wchar_t wch);

    // Initialize from an ansi or utf-8 string.
    // psz : input pointer to source string.
    ACBASE_PORT AcString(const char *psz, bool bUtf8 = false);

    // Initialize from a Unicode string
    // wpsz : input pointer to source string
    ACBASE_PORT AcString(const wchar_t *pwsz);

    // Copy constructor
    // acs : input reference to an existing AcString object
    ACBASE_PORT AcString(const AcString & acs);

    // Values for the nCtorFlags arg of the following constructor
    enum {
        kAppRes = 0x0001,   // use app's default resource dll
        kSigned = 0x0002,   // format the arg as signed int
        kUnSigned = 0x0003, // format the arg as unsigned int
        kHex      = 0x0004  // format the arg as hex
    };

    // Multi-purpose constructor, takes an unsigned argument and
    // uses it either to load a resource string or to create a
    // numerical string (base 10 or hex).
    //
    // nCtorFlags : input flags, indicating type of construction
    // nArg : input argument value, interpreted according to flags
    ACBASE_PORT AcString(int nCtorFlags, unsigned nArg);

    // Formats an AcDbHandle value in hex, as in: "a2f".
    // h : input reference to an acdb handle value
    ACBASE_PORT AcString(const AcDbHandle &h);

#if defined(_WINBASE_) || defined(_ADESK_MAC_)
    // Loads a resource string from the specified dll handle.
    // hDll : input windows handle to a loaded resource dll
    // nId : input int id of the resource string to load
    ACBASE_PORT AcString(HINSTANCE hDll, unsigned nId);
#endif

    // Destructor: frees up memory.
    ACBASE_PORT ~AcString();

    //
    // Querying methods
    //

    // Get a pointer to the current string (code page based).  This
    // pointer is only valid until the AcString object is next modified!
    ACBASE_PORT const char * ansiPtr() const;

    // Deprecated. Please use ansiPtr() or utf8Ptr() instead
    const char * kszPtr() const;

    // Get a pointer to the current string as Unicode UTF-8.  This
    // pointer is only valid until the AcString object is modified!
    ACBASE_PORT const char * utf8Ptr() const;

    // Get a pointer to the current string (in Unicode).  This pointer
    // is only valid until this AcString object is next modified!
    ACBASE_PORT const wchar_t * kwszPtr() const;

    // Get a pointer to the current string as a TCHAR pointer.
    // Pointer is only valid until this AcString is next modified.
#ifdef UNICODE
    const wchar_t *  constPtr() const;
    const wchar_t * kTCharPtr() const;
#else
    const char *  constPtr() const;
    const char * kTCharPtr() const;
#endif

    // Get a pointer to the current string in ACHARs.
    const ACHAR * kACharPtr() const;

    // Get a pointer to the current string (in Unicode).  Pointer
    // is valid only until this AcString is next modified.
    operator const wchar_t * () const;

    // Test whether the current string value is empty.  I.e.,
    // logical length is zero.
    ACBASE_PORT bool isEmpty() const;

    // Return logical length of (i.e. number of characters in) the string.
    //
    ACBASE_PORT unsigned length() const;

    // Return length of the current string, in TCHAR units.
    // Deprecated. Please use length() instead
    unsigned tcharLength() const;

    // Returns true if all chars are in the ascii range: 0x20..0x7f
    ACBASE_PORT bool isAscii() const;


    //
    // Parsing methods.
    //
    enum {
        // Enum value allowing caller to specify how to handle errors
        // (invalid chars or overflow) during string parsing.
        kParseZero = 0,       // return zero on errors
        kParseMinus1 = 0x01,  // return -1 or ffff
        kParseAssert = 0x02,  // pop an assert in debug build
        kParseExcept = 0x04,  // throw an int exception
        kParseNoEmpty = 0x08, // treat empty string as error
        kParseDefault = (kParseAssert | kParseZero)
    };

    // Parse the current string as decimal, return a signed int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int asDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int asHex (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT unsigned int asUDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT unsigned int asUHex (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT __int64 asDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT __int64 asHex64 (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT Adesk::UInt64 asUDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT Adesk::UInt64 asUHex64 (int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal.  Return the handle.
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT AcDbHandle asAcDbHandle(int nFlags = kParseDefault) const;

    //
    // Find char/string/one of a string of chars, from front or back
    // Return the position (index) at which the character or substring
    // was found.
    //
    // The find methods which start at the end of the string return
    // an index relative to the front of the string.

    // Find a single char in the string.
    // ch : input char to search for
    int find(ACHAR ch) const;

    // Find a substring in the string
    // psz : input string to search for
    ACBASE_PORT int find(const ACHAR *psz) const;

    // Find an AcString in the string.
    // acs : input string object to search for
    ACBASE_PORT int find(const AcString & acs) const;

    // Find any of a group of chars in the string.
    // psz : input pointer to string of chars to search for
    ACBASE_PORT int findOneOf(const ACHAR *psz) const;

    // Find last occurrence of a char in the string
    // ch : input char to search for
    int findRev(ACHAR ch) const;

    // Find last occurrence of any of a group of chars in the string
    // psz : input pointer to string of chars to search for
    ACBASE_PORT int findRev(const ACHAR *psz) const;

    // Find last occurrence of a group of chars in the string
    // psz : input ptr to the string of chars to search for
    ACBASE_PORT int findOneOfRev(const ACHAR *psz) const;

    // Find last occurrence of a string in the string
    // acs : input reference to the string to search for
    ACBASE_PORT int findRev(const AcString & acs) const;

    //
    // Extraction methods
    // Note: mid() and substr() are the same thing - we define both
    //       for compatibility with CString and std::string
    //
    // The input index arguments are byte indices into the string.

    // Get a substring from the string.  (same as substr() method)
    // nStart : input index (in bytes) from the start of the string
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    AcString mid(int nStart, int nNumChars) const;

    // Get a substring from the start of string.
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    AcString substr(int numChars) const;

    // Get a substring from the string.  (same as mid() method)
    // nStart : input index (in bytes) from the start of the string
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    ACBASE_PORT AcString substr(int nStart, int nNumChars) const;

    // Get a substring from the end of string.
    // nNumChars : input number of chars (not bytes) to retrieve.
    ACBASE_PORT AcString substrRev(int numChars) const;

    //
    // Assignment operators and methods
    //

    // assign a char to the string
    // ch : input (ansi) char to assign
    AcString & assign(char ch);

    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & assign(wchar_t wch);

    // assign a string of (ansi) chars to the string
    // psz : input pointer to the string of chars to assign
   ACBASE_PORT  AcString & assign(const char *psz);

    // assign a string of Unicode chars to the string
    // pwsz : input pointer to the string of chars to assign
    ACBASE_PORT AcString & assign(const wchar_t *pwsz);

    // assign an AcString object to the string
    // acs : input reference to the AcString
    ACBASE_PORT AcString & assign(const AcString & acs);

    // assign an AcDbHandle object to the string (format it as hex)
    // h : input reference to the AcDbHandle object
    ACBASE_PORT AcString & assign(const AcDbHandle & h);

    // assign a char to the string
    // ch : input (ansi) char to assign
    AcString & operator = (char ch);

    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & operator = (wchar_t wch);

    // assign a string of (ansi) chars to the string
    // psz : input pointer to the string of chars to assign
    AcString & operator = (const char *psz);

    // assign a string of Unicode chars to the string
    // pwsz : input pointer to the string of chars to assign
    AcString & operator = (const wchar_t *pwsz);

    // assign an AcString object to the string
    // acs : input reference to the AcString
    AcString & operator = (const AcString & acs);

    // assign an AcDbHandle object to the string (format it as hex)
    // h : input reference to the AcDbHandle object
    AcString & operator = (const AcDbHandle & h);

    // Set the string to be empty.
    ACBASE_PORT AcString & setEmpty();

    // Set the string from a resource string
    // nId : input id of the string resource in the current mfc resource dll
    ACBASE_PORT bool loadString(unsigned nId);

#if defined(_WINBASE_) || defined(_ADESK_MAC_)
    // Set the string from a resource string
    // hDll : input windows handle to a loaded resource dll
    // nId : input id of the string resource in the specified resource dll
    ACBASE_PORT bool loadString(HINSTANCE hDll, unsigned nId);
#endif

    // Format the string using "printf" rules.
    // pszFmt : input pointer to the printf format string
    ACBASE_PORT void format (const ACHAR    *pszFmt,  ...);

    // Format the string using "printf" rules
    // pszFmt : input pointer to the printf format string
    // args : input variable args list, containing values to be formatted
    ACBASE_PORT void formatV(const ACHAR   *pszFmt,  va_list args);

    //
    // Modifying operators and methods
    //

    // append an ansi char to the end of the string
    // ch : input (ansi) char to append
    AcString & operator += (char ch);

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & operator += (wchar_t wch);

    // append a char string to the end of the string
    // psz : input pointer to the (ansi) char string
    AcString & operator += (const char * psz);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    AcString & operator += (const wchar_t * pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    AcString & operator += (const AcString & acs);

    // append an ansi char to the end of the string
    // ch : input char to append
    AcString & append(char ch);

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & append(wchar_t wch);

    // append a char string to the end of the string
    // psz : input pointer to the (ansi) char string
    ACBASE_PORT AcString & append(const char *psz);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    ACBASE_PORT AcString & append(const wchar_t *pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    ACBASE_PORT AcString & append(const AcString & acs);

    // Catenation operators and methods  These are like append,
    // but they do not modify the current string.  They return a
    // new combined string.

    // Copy the string and append a char to it
    // ch : input (ansi) char to append to the string copy
    AcString operator + (char ch) const;

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString operator + (wchar_t wch) const;

    // Copy the string and append a string of chars to it
    // psz : input pointer to the (ansi) string to append
    AcString operator + (const char * psz) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    AcString operator + (const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    AcString operator + (const AcString & acs) const;

    // Copy the string and append a char to it
    // ch : input (ansi) char to append to the string copy
    AcString concat(char ch) const;

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString concat(wchar_t wch) const;

    // Copy the string and append a string of chars to it
    // psz : input pointer to the (ansi) string to append
    ACBASE_PORT AcString concat(const char * psz) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    ACBASE_PORT AcString concat(const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    ACBASE_PORT AcString concat(const AcString & acs) const;

    // These copy the current string and then insert the char or
    // string in front of it.  They're used by the global "+" operators.

    // Copy the string and insert a char in front of it
    // ch : input char to insert
    AcString precat(ACHAR ch) const;

    // Copy the string and insert a string of chars in front of it
    // psz : input pointer to the string of (ansi) chars to insert
    ACBASE_PORT AcString precat(const char * psz) const;

    // Copy the string and insert a string of chars in front of it
    // psz : input pointer to the string of chars to insert
    ACBASE_PORT AcString precat(const wchar_t * psz) const;

    //
    // Comparison operators and methods
    // The int return value is -1, 0 or 1, indicating <, == or >
    //

    // Compare the string to a single Unicode char
    // wch : input char to compare to
    int  compare(wchar_t wch) const;

    // Compare the string to a string of (ansi) chars
    // psz : input pointer to the string of chars to compare to
    ACBASE_PORT int  compare(const char *psz) const;

    // Compare the string to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    ACBASE_PORT int  compare(const wchar_t *pwsz) const;

    // Compare the string to a string of Unicode chars
    // acs : input reference of the other AcString to compare to
    ACBASE_PORT int  compare(const AcString & acs) const;

    // Compare the string case-independently to a Unicode char
    // wch : input char to compare to
    int  compareNoCase(wchar_t wch) const;

    // Compare the string case-independently to a string of chars
    // psz : input pointer to the string of (ansi) chars to compare to
    ACBASE_PORT int  compareNoCase(const char *psz) const;

    // Compare the string case-independently to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    ACBASE_PORT int  compareNoCase(const wchar_t *pwsz) const;

    // Compare the string case-independently to another AcString
    // acs : input reference to the other AcString
    ACBASE_PORT int  compareNoCase(const AcString & acs) const;

    // Compare the string for equality with a Unicode char
    // wch : input char to compare to
    bool operator == (wchar_t wch) const;

    // Compare the string for equality with a string of chars
    // psz : input pointer to the string of (ansi) chars
    bool operator == (const char *psz) const;

    // Compare the string for equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator == (const wchar_t *pwsz) const;

    // Compare the string for equality with another AcString
    // acs : input reference to the other AcString
    bool operator == (const AcString & acs) const;

    // Compare the string for non-equality with a Unicode char
    // wch : input char to compare to
    bool operator != (wchar_t wch) const;

    // Compare the string for non-equality with a string of chars
    // psz : input pointer to the string of (ansi) chars
    bool operator != (const char *psz) const;

    // Compare the string for non-equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator != (const wchar_t *pwsz) const;

    // Compare the string for non-equality with another AcString
    // acs : input reference to the other AcString
    bool operator != (const AcString & acs) const;

    // Compare the string for greater than a Unicode char
    // wch : input char to compare to
    bool operator >  (wchar_t wch) const;

    // Compare the string for greater than a string of chars
    // psz : input pointer to the string of (ansi) chars to compare to
    bool operator >  (const char *psz) const;

    // Compare the string for greater than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator >  (const wchar_t *pwsz) const;

    // Compare the string for greater than another AcString
    // acs : input reference to the other AcString
    bool operator >  (const AcString & acs) const;

    // Compare the string for greater than or equal to a Unicode char
    // wch : input char to compare to
    bool operator >= (wchar_t wch) const;

    // Compare the string for greater than or equal to a string of chars
    // psz : input pointer to the string of (ansi) chars
    bool operator >= (const char *psz) const;

    // Compare the string for greater than/equal to a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator >= (const wchar_t *pwsz) const;

    // Compare the string for greater than or equal to another AcString
    // acs : input reference to the other AcString
    bool operator >= (const AcString & acs) const;

    // Compare the string for less than a Unicode char
    // wch : input char to compare to
    bool operator <  (wchar_t wch) const;

    // Compare the string for less than a string of chars
    // psz : input pointer to the string of (ansi) chars to compare to
    bool operator <  (const char *psz) const;

    // Compare the string for less than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator <  (const wchar_t *pwsz) const;

    // Compare the string for less than another AcString
    // acs : input reference to the other AcString
    bool operator <  (const AcString & acs) const;

    // Compare the string for less than or equal to a char
    // ch : input (ansi) char to compare to
    bool operator <= (char ch) const;

    // Compare the string for less than or equal to a Unicode char
    // wch : input char to compare to
    bool operator <= (wchar_t wch) const;

    // Compare the string for less than or equal to a string of chars
    // psz : input pointer to the string of (ansi) chars
    bool operator <= (const char *psz) const;

    // Compare the string for less than/equal to a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator <= (const wchar_t *pwsz) const;

    // Compare the string for less or equal to than another AcString
    // acs : input reference to the other AcString
    bool operator <= (const AcString & acs) const;

    // The match() methods return how many chars (not bytes) match
    // between two strings.  Not fully implemented yet (non-ascii
    // chars not supported yet).

    // Return the number of chars that match a string of chars
    // psz : input pointer to the string of (ansi) chars
    ACBASE_PORT int  match(const char *psz) const;

    // Return the number of chars matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    ACBASE_PORT int  match(const wchar_t *pwsz) const;

    // Return the number of chars matching another AcString
    // acs : input reference to the other AcString
    ACBASE_PORT int  match(const AcString & acs) const;

    // Return number of chars case-independently matching a string of chars
    // psz : input pointer to the string of (ansi) chars
    ACBASE_PORT int  matchNoCase(const char *psz) const;

    // Return number of chars case-indep'ly matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    ACBASE_PORT int  matchNoCase(const wchar_t *pwsz) const;

    // Return number of chars case-indep'ly matching another AcString
    // acs : input reference to the other AcString
    ACBASE_PORT int  matchNoCase(const AcString & acs) const;

#if  defined(_AFX) || defined (_ADESK_MAC_) || defined(__ATLSTR_H__)
    //
    // MFC CString-using methods.  The CStringA class is the ansi
    // code page based CString, while CStringW is Unicode based.
    // CString maps to one or the other depending on whether the
    // UNICODE preprocessor symbol is defined.
    //

    // Construct an AcString from a CStringW
    // csw : input reference to the CStringW
    AcString(const CStringW &csw);

    // Initialize this AcString from a CStringW
    // csw : input reference to the CStringW
    AcString & operator = (const CStringW &csw);

    // Append a CStringW to this AcString
    // csa : input reference to the CStringW
    AcString & operator += (const CStringW &csw);

    // Compare this string to a CStringW
    // csw : input reference to the CStringW
    int  compare(const CStringW & csw) const;

    // Compare this string case independently to a CStringW
    // csw : input reference to the CStringW
    int  compareNoCase(const CStringW & csw) const;

    // Compare for equality with a CStringW
    // csw : input reference to the CStringW
    bool operator == (const CStringW & ) const;

    // Compare for non-equality with a CStringW
    // csw : input reference to the CStringW
    bool operator != (const CStringW & ) const;

    // Compare for less than a CStringW
    // csw : input reference to the CStringW
    bool operator <  (const CStringW & ) const;

    // Compare for less than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator <= (const CStringW & ) const;

    // Compare for greater than a CStringW
    // csw : input reference to the CStringW
    bool operator >  (const CStringW & ) const;
    // Compare for greater than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator >= (const CStringW & ) const;

    // Return number of chars matching a CStringW
    // csw : input reference to the CStringW
    int  match(const CStringW & csw) const;

    // Return number of chars case-independently matching a CStringW
    // csw : input reference to the CStringW
    int  matchNoCase(const CStringW & csw) const;

    // Note: unfortunately there is not now an assignment operator for
    // assigning AcStrings to CStrings, as in CString cs = AcString("x");
#endif

  private:
    // size is 8 bytes in 32-bit build, 16 in 64-bit build.
#if !defined(_WIN64) && !defined (_AC64)
    enum {
#ifdef _ADESK_MAC_
        kObjSize = 14,
#else
        kObjSize = 8,
#endif
        kMbArrSize = 7,
        kUCArrSize = 3,
        kPadArrSize = 3
    };
#else
    enum {
#ifdef _ADESK_MAC_
        kObjSize = 30,
#else
        kObjSize = 16,
#endif
        kMbArrSize = 15,
        kUCArrSize = 7,
        kPadArrSize = 7
    };
#endif
    void clearAll();
    struct PtrAndData;
    unsigned char mnFlags;
    union {
        struct {
            unsigned char mnPad2[kPadArrSize];
            union {
                wchar_t *mpwszData;
                char *mpszData;
                PtrAndData *mpPtrAndData;
            };
        }mptr;
        struct {
            unsigned char mnPad1;
            wchar_t mwszStr[kUCArrSize];
        }mchr;
        char mszStr[kMbArrSize];
    };
    friend class AcStringImp;
};

#ifdef AC_ACARRAY_H
typedef
AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#endif

#pragma pack (pop)

//
// Global operators
//

// Compare an AcString and a Unicode char for equality
// wch : input char to compare
// acs : input reference to the AcString
bool operator == (wchar_t wch, const AcString & acs);

// Compare an AcString and a string of chars char for equality
// psz : input pointer to the string of chars
// acs : input reference to the AcString
bool operator == (const char *psz, const AcString & acs);

// Compare an AcString and a string of Unicode chars for equality
// pwsz : input char to the string of Unicode chars
// acs : input reference to the AcString
bool operator == (const wchar_t *pwsz, const AcString & acs);

// Compare an AcString and a Unicode char for non-equality
// wch : input char to compare
// acs : input reference to the AcString
bool operator != (wchar_t wch, const AcString & acs);

// Compare an AcString and a string of chars char for non-equality
// psz : input pointer to the string of chars
// acs : input reference to the AcString
bool operator != (const char *psz, const AcString & acs);

// Compare an AcString and a string of Unicode chars for non-equality
// pwsz : input char to the string of Unicode chars
// acs : input reference to the AcString
bool operator != (const wchar_t *pwsz, const AcString & acs);

// Return whether a Unicode char is greater than an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator >  (wchar_t wch, const AcString & acs);

// Return whether a string of chars is greater than an AcString
// psz : input pointer to the string of chars
// acs : input reference to the AcString
bool operator >  (const char *psz, const AcString & acs);

// Return whether a string of Unicode chars is greater than an AcString
// pwsz : input pointer to the string of Unicode chars
// acs : input reference to the AcString
bool operator >  (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being greater than or equal to an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator >= (wchar_t wch, const AcString & acs);

// Check for a string of chars being greater than or equal to an AcString
// psz : input char to compare
// acs : input reference to the AcString
bool operator >= (const char *psz, const AcString & acs);

// Check for a string of Unicode chars being greater than/equal to an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator >= (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being less than an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator <  (wchar_t wch, const AcString & acs);

// Check for a string of chars being less than an AcString
// psz : input char to compare
// acs : input reference to the AcString
bool operator <  (const char *psz, const AcString & acs);

// Check for a string of Unicode chars being less than an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator <  (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being less than or equal to an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator <= (wchar_t wch, const AcString & acs);

// Check for a string of chars being less than or equal to an AcString
// psz : input char to compare
// acs : input reference to the AcString
bool operator <= (const char *psz, const AcString & acs);

// Check for a string of Unicode chars being less than/equal to an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator <= (const wchar_t *pwsz, const AcString & acs);

// Copy an AcString and insert a Unicode char in front of it
// wch : input char to insert
AcString operator + (wchar_t wch, const AcString & acs);

// Copy an AcString and insert a string of chars in front of it
// psz : input pointer to the string of chars to insert
AcString operator + (const char *psz, const AcString & acs);

// Copy an AcString and insert a string of Unicode chars in front of it
// pwsz : input pointer to the string of chars to insert
AcString operator + (const wchar_t *pwsz, const AcString & acs);

#if defined(_AFX) || defined(__ATLSTR_H__)

// Compare a CStringW for equality with an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator == (const CStringW & csw, const AcString & acs);

// Compare a CStringW for in-equality with an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator != (const CStringW & csw, const AcString & acs);

// Compare a CStringW for greater than an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator >  (const CStringW & csw, const AcString & acs);

// Compare a CStringW for greater than or equal to an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator >= (const CStringW & csw, const AcString & acs);

// Compare a CStringW for less than an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator <  (const CStringW & csw, const AcString & acs);

// Compare a CStringW for less than or equal to an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator <= (const CStringW & csw, const AcString & acs);

#define DISABLE_CSTRING_PLUS_ACSTRING 1
#ifndef DISABLE_CSTRING_PLUS_ACSTRING
// For now, these are disabled to avoid ambiguities.  If someone
// says CString cs = CString("a") + "b", then the "b" could get
// implicitly converted into an AcString or a CString, so it
// won't compile.
//
AcString operator + (const CStringW & csw, const AcString & acs);
#endif
#endif

// Accessing inlines
//
// Deprecated. Please use ansiPtr() or utf8Ptr()
//
inline const char * AcString::kszPtr() const
{
    return this->ansiPtr();
}

inline AcString::operator const wchar_t *() const
{
    return this->kwszPtr();
}

#ifdef UNICODE
inline const wchar_t * AcString::constPtr() const
{
    return this->kwszPtr();
}

inline const wchar_t * AcString::kTCharPtr() const
{
    return this->kwszPtr();
}

// This method only supported for apps built in same way as acad.
inline unsigned AcString::tcharLength() const
{
    return this->length();
}

#elif _UNICODE
#error "Unexpected _UNICODE definition"
#else
inline const char * AcString::constPtr() const
{
    return this->kszPtr();
}

inline const char * AcString::kTCharPtr() const
{
    return this->kszPtr();
}

#endif

inline const ACHAR * AcString::kACharPtr() const
{
#if defined (_ADESK_WINDOWS_)
    return this->kwszPtr();
#else
    return (const ACHAR*)this->kwszPtr();
#endif
}

inline void AcString::clearAll()
{
    this->mnFlags = 0;
    this->mchr.mnPad1 = 0;
    this->mchr.mwszStr[0] = 0;
    this->mptr.mpszData = nullptr;
}

// Searching inlines
//
inline int AcString::find(ACHAR ch) const
{
    const ACHAR str[2] = {ch, '\0'};
    return this->findOneOf(str);
}

inline int AcString::findRev(ACHAR ch) const
{
    const ACHAR str[2] = {ch, '\0'};
    return this->findOneOfRev(str);
}

// Extraction inlines
//
inline AcString AcString::mid(int nStart, int nNumChars) const
{
    return this->substr(nStart, nNumChars);
}

inline AcString AcString::substr(int nNumChars) const
{
    return this->substr(0, nNumChars);
}

// Assignment inlines
//
inline AcString & AcString::assign(char ch)
{
    const char str[2] = {ch, '\0'};
    return this->assign(str);
}

inline AcString & AcString::assign(wchar_t wch)
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->assign(wstr);
}

inline AcString & AcString::operator = (char ch)
{
    return this->assign(ch);
}

inline AcString & AcString::operator = (wchar_t wch)
{
    return this->assign(wch);
}

inline AcString & AcString::operator = (const char *psz)
{
    return this->assign(psz);
}

inline AcString & AcString::operator = (const wchar_t *pwsz)
{
    return this->assign(pwsz);
}

inline AcString & AcString::operator = (const AcString & acs)
{
    return this->assign(acs);
}

inline AcString & AcString::operator = (const AcDbHandle & h)
{
    return this->assign(h);
}

// Modifying inlines
//
inline AcString & AcString::operator += (char ch)
{
    return this->append(ch);
}

inline AcString & AcString::operator += (wchar_t wch)
{
    return this->append(wch);
}

inline AcString & AcString::operator += (const char *psz)
{
    return this->append(psz);
}

inline AcString & AcString::operator += (const wchar_t *pwsz)
{
    return this->append(pwsz);
}

inline AcString & AcString::operator += (const AcString & acs)
{
    return this->append(acs);
}

inline AcString & AcString::append(char ch)
{
    const char str[2] = {ch, '\0'};
    return this->append(str);
}

inline AcString & AcString::append(wchar_t wch)
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->append(wstr);
}

// Concatenation inlines
inline AcString AcString::operator + (char ch) const
{
    return this->concat(ch);
}

inline AcString AcString::operator + (wchar_t wch) const
{
    return this->concat(wch);
}

inline AcString AcString::operator + (const char * psz) const
{
    return this->concat(psz);
}

inline AcString AcString::operator + (const wchar_t * pwsz) const
{
    return this->concat(pwsz);
}

inline AcString AcString::operator + (const AcString & acs) const
{
    return this->concat(acs);
}

inline AcString AcString::concat(char ch) const
{
    const char str[2] = {ch, '\0'};
    return this->concat(str);
}

inline AcString AcString::concat(wchar_t wch) const
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->concat(wstr);
}

inline AcString AcString::precat(ACHAR ch) const
{
    const ACHAR str[2] = {ch, '\0'};
    return this->precat(str);
}

// Comparison inlines
//

inline int AcString::compare(wchar_t wch) const
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->compare(wstr);
}

inline int AcString::compareNoCase(wchar_t wch) const
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->compareNoCase(wstr);
}

inline bool AcString::operator == (wchar_t wch) const
{
    return this->compare(wch) == 0;
}

inline bool AcString::operator == (const char *psz) const
{
    return this->compare(psz) == 0;
}

inline bool AcString::operator == (const wchar_t *pwsz) const
{
    return this->compare(pwsz) == 0;
}

inline bool AcString::operator == (const AcString & acs) const
{
    return this->compare(acs) == 0;
}

inline bool AcString::operator != (wchar_t wch) const
{
    return this->compare(wch) != 0;
}

inline bool AcString::operator != (const char *psz) const
{
    return this->compare(psz) != 0;
}

inline bool AcString::operator != (const wchar_t *pwsz) const
{
    return this->compare(pwsz) != 0;
}

inline bool AcString::operator != (const AcString & acs) const
{
    return this->compare(acs) != 0;
}

inline bool AcString::operator > (wchar_t wch) const
{
    return this->compare(wch) > 0;
}

inline bool AcString::operator > (const char *psz) const
{
    return this->compare(psz) > 0;
}

inline bool AcString::operator > (const wchar_t *pwsz) const
{
    return this->compare(pwsz) > 0;
}

inline bool AcString::operator > (const AcString & acs) const
{
    return this->compare(acs) > 0;
}

inline bool AcString::operator >= (wchar_t wch) const
{
    return this->compare(wch) >= 0;
}

inline bool AcString::operator >= (const char *psz) const
{
    return this->compare(psz) >= 0;
}

inline bool AcString::operator >= (const wchar_t *pwsz) const
{
    return this->compare(pwsz) >= 0;
}

inline bool AcString::operator >= (const AcString & acs) const
{
    return this->compare(acs) >= 0;
}

inline bool AcString::operator < (wchar_t wch) const
{
    return this->compare(wch) < 0;
}

inline bool AcString::operator < (const char *psz) const
{
    return this->compare(psz) < 0;
}

inline bool AcString::operator < (const wchar_t *pwsz) const
{
    return this->compare(pwsz) < 0;
}

inline bool AcString::operator < (const AcString & acs) const
{
    return this->compare(acs) < 0;
}

inline bool AcString::operator <= (char ch) const
{
    return this->compare(ch) <= 0;
}

inline bool AcString::operator <= (wchar_t wch) const
{
    return this->compare(wch) <= 0;
}

inline bool AcString::operator <= (const char *psz) const
{
    return this->compare(psz) <= 0;
}

inline bool AcString::operator <= (const wchar_t *pwsz) const
{
    return this->compare(pwsz) <= 0;
}

inline bool AcString::operator <= (const AcString & acs) const
{
    return this->compare(acs) <= 0;
}


// We can do inline operators that deal with CStrings, without getting
// into binary format dependencies.  Don't make these out-of-line
// functions, because then we'll have a dependency between our
// components and CString-using clients.
//
#if defined(_AFX) || defined(_ADESK_MAC_) || defined(__ATLSTR_H__)

inline AcString::AcString(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    this->clearAll();
    *this = pwsz;
}

inline AcString & AcString::operator=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->assign(pwsz);
}

inline AcString & AcString::operator+=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->append(pwsz);
}

inline int AcString::compare(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compare(pwsz);
}

inline int AcString::compareNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compareNoCase(pwsz);
}

inline int AcString::match(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->match(pwsz);
}

inline int AcString::matchNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->matchNoCase(pwsz);
}

inline bool AcString::operator == (const CStringW & csw) const
{
    return this->compare(csw) == 0;
}

inline bool AcString::operator != (const CStringW & csw) const
{
    return this->compare(csw) != 0;
}

inline bool AcString::operator > (const CStringW & csw) const
{
    return this->compare(csw) > 0;
}

inline bool AcString::operator >= (const CStringW & csw) const
{
    return this->compare(csw) >= 0;
}

inline bool AcString::operator < (const CStringW & csw) const
{
    return this->compare(csw) < 0;
}

inline bool AcString::operator <= (const CStringW & csw) const
{
    return this->compare(csw) <= 0;
}
#endif

#ifdef _AFX
// Global CString-related operators
inline bool operator == (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) == 0;
}

inline bool operator != (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) != 0;
}

inline bool operator >  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) < 0;
}

inline bool operator >= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) <= 0;
}

inline bool operator <  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) > 0;
}

inline bool operator <= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) >= 0;
}

#ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline AcString operator + (const CStringW & csw, const AcString & acs)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return acs.precat(pwsz);
}
#endif


#endif // _AFX

// Inline global operators

inline bool operator == (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) == 0;
}

inline bool operator == (const char *psz, const AcString & acs)
{
    return acs.compare(psz) == 0;
}

inline bool operator == (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) == 0;
}

inline bool operator != (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) != 0;
}

inline bool operator != (const char *psz, const AcString & acs)
{
    return acs.compare(psz) != 0;
}

inline bool operator != (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) != 0;
}

inline bool operator > (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) < 0;
}

inline bool operator > (const char *psz, const AcString & acs)
{
    return acs.compare(psz) < 0;
}

inline bool operator > (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) < 0;
}

inline bool operator >= (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) <= 0;
}

inline bool operator >= (const char *psz, const AcString & acs)
{
    return acs.compare(psz) <= 0;
}

inline bool operator >= (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) <= 0;
}

inline bool operator < (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) > 0;
}

inline bool operator < (const char *psz, const AcString & acs)
{
    return acs.compare(psz) > 0;
}

inline bool operator < (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) > 0;
}

inline bool operator <= (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) >= 0;
}

inline bool operator <= (const char *psz, const AcString & acs)
{
    return acs.compare(psz) >= 0;
}

inline bool operator <= (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) >= 0;
}

// These don't modify the AcString.  They return a copy.
inline AcString operator + (ACHAR ch, const AcString & acs)
{
    return acs.precat(ch);
}

inline AcString operator + (const char *psz, const AcString & acs)
{
    return acs.precat(psz);
}

inline AcString operator + (const wchar_t *pwsz, const AcString & acs)
{
    return acs.precat(pwsz);
}

// Return a unique identifier (pointer) for the input string, to allow fast compares
// Strings containing the exact same chars will return the same AcUniqueString
// AcUniqueString pointers are valid for the process's lifetime
//
class AcUniqueString
{
public:
    ACBASE_PORT static const AcUniqueString *Intern(const wchar_t *);
};

#endif // !_Ac_String_h

