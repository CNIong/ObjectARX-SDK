
//
// (C) Copyright 2003-2004 by Autodesk, Inc. 
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
//  DESCRIPTION:
//

#ifndef _Ac_String_h_
#define _Ac_String_h_

#include "AcHeapOpers.h"
#pragma pack (push, 1)

class AcDbHandle;

// Notes:
// 1. All "char" arguments are assumed to be codes in the current
//    code page, unless otherwise specified.
//
// 2. In places where a single char value is passed, the value
//    cannot be a leading byte of a double-byte char, except
//    where noted.
//
// 3. All wchar_t arguments are assumed to be Unicode values.
//
class AcString : public AcHeapOperators
{
  public:
    //
    // Constructors and destructor 
    //
    // Default ctor, initializes to empty string.
    AcString();

    // Initialize with a single character.
    // ch : input character
    AcString(char ch);

    // Initialize with a double byte character.
    // leadbyte : input leading byte of the double-byte char
    // ch : input trailing byte
    AcString(char leadbyte, char ch);

    // Initialize with a single Unicode character
    // wch : input character
    AcString(wchar_t wch);

    // Initialize from an ansi string.
    // psz : input pointer to source string.
    AcString(const char *psz);

    // Initialize from a Unicode string
    // wpsz : input pointer to source string
    AcString(const wchar_t *pwsz);

    // Copy constructor
    // acs : input reference to an existing AcString object
    AcString(const AcString & acs);

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
    AcString(int nCtorFlags, unsigned nArg);

    // Formats an AcDbHandle value in hex, as in: "a2f".
    // h : input reference to an acdb handle value
    AcString(const AcDbHandle &h);

#ifdef _WINBASE_
    // Loads a resource string from the specified dll handle.
    // hDll : input windows handle to a loaded resource dll
    // nId : input int id of the resource string to load
    AcString(HINSTANCE hDll, unsigned nId);
#endif
    
    // Destructor: frees up memory.
    ~AcString();

    //
    // Querying methods
    //

    // Get a pointer to the current string (code page based).  This
    // pointer is only valid until the AcString object is next modified!
    const    char * kszPtr() const;

    // Get a pointer to the current string (in Unicode).  This pointer
    // is only valid until this AcString object is next modified!
    const wchar_t * kwszPtr() const;

    // Get a pointer to the current string as a TCHAR pointer.  In
    // Unicode builds, this will be Unicode, and in multibyte builds
    // it will be code page dependent.
#ifdef UNICODE
    const wchar_t * kTCharPtr() const;
#else
    const    char * kTCharPtr() const;
#endif

    // Get a pointer to the current string (code page based).  Pointer
    // is valid only until this AcString is next modified.
    operator const char * () const;

    // Get a pointer to the current string (in Unicode).  Pointer
    // is valid only until this AcString is next modified.
    operator const wchar_t * () const;

    // Test whether the current string value is empty.  I.e.,
    // logical length is zero.
    bool isEmpty() const;

    // Return logical length of (i.e. number of chars in) the string.
    // WARNING!!!  Double-byte chars count as a single character.
    // This method does *not* return the *byte* length of the string.
    // If the string contains doublebyte chars, then this method will
    // return a smaller length than the byte length.
    // To get the byte length, please call tcharLength() or lengthA().
    //
    size_t length() const;

    // Return length of the current string, in TCHAR units.
    // In ansi build, call lengthA(), returning number of bytes.
    // In Unicode build, call lengthW(), returning number of widechars.
    size_t tcharLength() const;

    // Return length in bytes of the current ansi string
    // Null terminator is not counted in the length.
    size_t lengthA() const;

    // Return length in widechars of the current Unicode string
    // Null terminator is not counted in the length.
    size_t lengthW() const;

    // Return physical length (number of bytes) in the string.
    // Note: this also includes the null terminator.
    // Note also: this function will be removed in a future release.
    size_t physMbBytes() const;

    // Returns true if the string contains a MIF sequence (\M+nxxyy)
    bool hasMIF() const;

    // Returns true if the string contains a CIF sequence (\U+xxxx)
    bool hasCIF() const;
    
    // Returns true if all chars are in the ascii range: 0x20..0x7f
    bool isAscii() const;


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
    int asDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int
    // nFlags : input bits specifying how to do the parsing
    int asHex (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    unsigned int asUDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    unsigned int asUHex (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    __int64 asDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    __int64 asHex64 (int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    unsigned __int64 asUDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    unsigned __int64 asUHex64 (int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal.  Return the handle.
    // nFlags : input bits specifying how to do the parsing
    AcDbHandle asAcDbHandle(int nFlags = kParseDefault) const;

    //
    // Find char/string/one of a string of chars, from front or back
    // Note: the find methods taking a char arg return the byte position
    // at which the character was found, not the character position.
    //
    // The find methods which take a wchar_t arg return the word
    // (not byte) position at which the char was found.
    //
    // The find methods which start at the end of the string return
    // an index relative to the front of the string.

    // Find a single char in the string.
    // ch : input char to search for
    int find(char ch) const;

    // Find a double byte ansi char in the current string.
    // Calls findA() in multibyte build and returns a byte position.
    // Calls findW() in Unicode build and returns a widechar position.
    // chLead : input leading byte of the double byte ansi char
    // chTrail : input trailing byte
    // If chLead is zero, then chTrail is treated as single byte ansi
    int find(char chLead, char chTrail) const;

    // Find a double byte ansi char in the current ansi string.
    // Returns a byte position of the ansi char.
    // chLead : input leading byte of the double byte ansi char
    // chTrail : input trailing byte
    // If chLead is zero, then chTrail is treated as single byte ansi
    int findA(char chLead, char chTrail) const;

    // Find a double byte ansi char in the current Unicode string.
    // Converts the double byte char into Unicode before searching.
    // Returns a widechar position of the Unicode char.
    // chLead : input leading byte of the double byte ansi char
    // chTrail : input trailing byte
    // If chLead is zero, then chTrail is treated as single byte ansi
    int findW(char chLead, char chTrail) const;

    // Find a Unicode char in the string.
    // wch : input char to search for
    int find(wchar_t wch) const;

    // Find a substring in the string
    // psz : input string to search for
    int find(const char *psz) const;

    // Find a Unicode substring in the string.
    // pwsz : input string to search for
    int find(const wchar_t *pwsz) const;

    // Find an AcString in the string.
    // acs : input string object to search for
    int find(const AcString & acs) const;

    // Find any of a group of chars in the string.
    // psz : input pointer to string of chars to search for
    int findOneOf(const char *psz) const;

    // Find any of a group of Unicode chars in the string
    // pwsz : input pointer to string of Unicode chars to search for
    int findOneOf(const wchar_t *pwsz) const;

    // Find last occurrence of a char in the string
    // ch : input char to search for
    int findRev(char ch) const;

    // Find last occurrence of a Unicode char in the string
    // wch : input char to search for
    int findRev(wchar_t wch) const;

    // Find last occurrence of any of a group of chars in the string
    // psz : input pointer to string of chars to search for
    int findRev(const char *psz) const;

    // Find last occurrence of any of a group of Unicode chars in the string
    // pwsz : input pointer to string of chars to search for
    int findRev(const wchar_t *pwsz) const;

    // Find last occurrence of a string in the string
    // acs : input reference to the string to search for
    int findRev(const AcString & acs) const;

    // Find last occurrence of a group of chars in the string
    // psz : input ptr to the string of chars to search for
    int findOneOfRev(const char *psz) const;

    // Find last occurrence of a group of Unicode chars in the string
    // pwsz : input ptr to the string of chars to search for
    int findOneOfRev(const wchar_t *pwsz) const;

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
    AcString substr(int nStart, int nNumChars) const;

    // Get a substring from the end of string.
    // nNumChars : input number of chars (not bytes) to retrieve.
    AcString substrRev(int numChars) const;

    //
    // Assignment operators and methods
    //

    // assign a char to the string
    // ch : input char to assign
    AcString & assign(char ch);

    // assign a double byte char to the string
    // leader : input leading byte of the double byte char
    // leader : input trailing byte
    AcString & assign(char leader, char trailer);

    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & assign(wchar_t wch);

    // assign a string of chars to the string
    // psz : input pointer to the string of chars to assign
    AcString & assign(const char *psz);

    // assign a string of Unicode chars to the string
    // pwsz : input pointer to the string of chars to assign
    AcString & assign(const wchar_t *pwsz);

    // assign an AcString object to the string
    // acs : input reference to the AcString
    AcString & assign(const AcString & acs);

    // assign an AcDbHandle object to the string (format it as hex)
    // h : input reference to the AcDbHandle object
    AcString & assign(const AcDbHandle & h);

    // assign a char to the string
    // ch : input char to assign
    AcString & operator = (char ch);

    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & operator = (wchar_t wch);

    // assign a string of chars to the string
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
    AcString & setEmpty();

    // Set the string from a resource string
    // nId : input id of the string resource in the current mfc resource dll
    bool loadString(unsigned nId);

#ifdef _WINBASE_
    // Set the string from a resource string
    // hDll : input windows handle to a loaded resource dll
    // nId : input id of the string resource in the specified resource dll
    bool loadString(HINSTANCE hDll, unsigned nId);
#endif

    // Format the string using "printf" rules.
    // pszFmt : input pointer to the printf format string
    void format (const char    *pszFmt,  ...);

    // Format the string using "printf" rules
    // pszFmt : input pointer to the UNICODE printf format string
    void format (const wchar_t *pwszFmt, ...);

    // Format the string using "printf" rules
    // pszFmt : input pointer to the printf format string
    // args : input variable args list, containing values to be formatted
    void formatV(const char    *pszFmt,  va_list args);

    // Format the string using "printf" rules
    // pwszFmt : input pointer to the UNICODE printf format string
    // args : input variable args list, containing values to be formatted
    void formatV(const wchar_t *pwszFmt, va_list args);

    //
    // Modifying operators and methods
    //

    // append a char to the end of the string
    // ch : input char to append
    AcString & operator += (char ch);

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & operator += (wchar_t wch);

    // append a char string to the end of the string
    // psz : input pointer to the char string
    AcString & operator += (const char * psz);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    AcString & operator += (const wchar_t * pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    AcString & operator += (const AcString & acs);

    // append a char to the end of the string
    // ch : input char to append
    AcString & append(char ch);

    // append a double byte char to the end of the string
    // leader : input leading byte of the double byte char
    // trailer : input trailing byte
    AcString & append(char leader, char trailer);

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & append(wchar_t wch);

    // append a char string to the end of the string
    // psz : input pointer to the char string
    AcString & append(const char *psz);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    AcString & append(const wchar_t *pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    AcString & append(const AcString & acs);

    // Catenation operators and methods  These are like append,
    // but they do not modify the current string.  They return a
    // new combined string.

    // Copy the string and append a char to it
    // ch : input char to append to the string copy
    AcString operator + (char ch) const;

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString operator + (wchar_t wch) const;

    // Copy the string and append a string of chars to it
    // psz : input pointer to the string to append
    AcString operator + (const char * psz) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    AcString operator + (const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    AcString operator + (const AcString & acs) const;

    // Copy the string and append a char to it
    // ch : input char to append to the string copy
    AcString concat(char ch) const;

    // Copy the string and append a double byte char to it
    // leader : input leading byte of the double byte char to append
    // trailer : input trailing byte
    AcString concat(char leader, char trailer) const;

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString concat(wchar_t wch) const;

    // Copy the string and append a string of chars to it
    // psz : input pointer to the string to append
    AcString concat(const char * psz) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    AcString concat(const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    AcString concat(const AcString & acs) const;

    // These copy the current string and then insert the char or
    // string in front of it.  They're used by the global "+" operators.

    // Copy the string and insert a char in front of it
    // ch : input char to insert
    AcString precat(char ch) const;

    // Copy the string and insert a double byte char in front of it
    // leader : input leading byte of the double byte char to insert
    // trailer : input trailing byte
    AcString precat(char leader, char trailer) const;

    // Copy the string and insert a Unicode char in front of it
    // wch : input char to insert
    AcString precat(wchar_t wch) const;

    // Copy the string and insert a string of chars in front of it
    // psz : input pointer to the string of chars to insert
    AcString precat(const char * psz) const;

    // Copy the string and insert a string of Unicode chars in front of it
    // pwsz : input pointer to the string of chars to insert
    AcString precat(const wchar_t * pwsz) const;

    //
    // Comparison operators and methods
    // The int return value is -1, 0 or 1, indicating <, == or >
    //

    // Compare the string to a single char
    // ch : input char to compare to
    int  compare(char ch) const;

    // Compare the string to a double byte char
    // leader : input leading byte of the double byte char to compare
    // trailer : input trailing byte
    int  compare(char leader, char trailer) const;

    // Compare the string to a single Unicode char
    // wch : input char to compare to
    int  compare(wchar_t wch) const;

    // Compare the string to a string of chars
    // psz : input pointer to the string of chars to compare to
    int  compare(const char *psz) const;

    // Compare the string to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    int  compare(const wchar_t *pwsz) const;

    // Compare the string to a string of Unicode chars
    // acs : input reference of the other AcString to compare to
    int  compare(const AcString & acs) const;

    // Compare the string case-independently to a char
    // ch : input char to compare to
    int  compareNoCase(char ch) const;

    // Compare the string case-independently to a double byte char
    // leader : input leading byte of the double byte char to compare to
    // trailer : input trailing byte
    int  compareNoCase(char leader, char trailer) const;

    // Compare the string case-independently to a Unicode char
    // wch : input char to compare to
    int  compareNoCase(wchar_t wch) const;

    // Compare the string case-independently to a string of chars
    // psz : input pointer to the string of chars to compare to
    int  compareNoCase(const char *psz) const;

    // Compare the string case-independently to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    int  compareNoCase(const wchar_t *pwsz) const;

    // Compare the string case-independently to another AcString
    // acs : input reference to the other AcString
    int  compareNoCase(const AcString & acs) const;

    // Compare the string for equality with a char
    // ch : input char to compare to
    bool operator == (char ch) const;

    // Compare the string for equality with a Unicode char
    // wch : input char to compare to
    bool operator == (wchar_t wch) const;

    // Compare the string for equality with a string of chars
    // psz : input pointer to the string of chars
    bool operator == (const char *psz) const;

    // Compare the string for equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator == (const wchar_t *pwsz) const;

    // Compare the string for equality with another AcString
    // acs : input reference to the other AcString
    bool operator == (const AcString & acs) const;

    // Compare the string for non-equality with a char
    // ch : input char to compare to
    bool operator != (char ch) const;

    // Compare the string for non-equality with a Unicode char
    // wch : input char to compare to
    bool operator != (wchar_t wch) const;

    // Compare the string for non-equality with a string of chars
    // psz : input pointer to the string of chars
    bool operator != (const char *psz) const;

    // Compare the string for non-equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator != (const wchar_t *pwsz) const;

    // Compare the string for non-equality with another AcString
    // acs : input reference to the other AcString
    bool operator != (const AcString & acs) const;

    // Compare the string for greater than a char
    // ch : input char to compare to
    bool operator >  (char ch) const;

    // Compare the string for greater than a Unicode char
    // wch : input char to compare to
    bool operator >  (wchar_t wch) const;

    // Compare the string for greater than a string of chars
    // psz : input pointer to the string of chars to compare to
    bool operator >  (const char *psz) const;

    // Compare the string for greater than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator >  (const wchar_t *pwsz) const;

    // Compare the string for greater than another AcString
    // acs : input reference to the other AcString
    bool operator >  (const AcString & acs) const;

    // Compare the string for greater than or equal to a char
    // ch : input char to compare to
    bool operator >= (char ch) const;

    // Compare the string for greater than or equal to a Unicode char
    // wch : input char to compare to
    bool operator >= (wchar_t wch) const;

    // Compare the string for greater than or equal to a string of chars
    // psz : input pointer to the string of chars
    bool operator >= (const char *psz) const;

    // Compare the string for greater than/equal to a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator >= (const wchar_t *pwsz) const;

    // Compare the string for greater than or equal to another AcString
    // acs : input reference to the other AcString
    bool operator >= (const AcString & acs) const;

    // Compare the string for less than a char
    // ch : input char to compare to
    bool operator <  (char ch) const;

    // Compare the string for less than a Unicode char
    // wch : input char to compare to
    bool operator <  (wchar_t wch) const;

    // Compare the string for less than a string of chars
    // psz : input pointer to the string of chars to compare to
    bool operator <  (const char *psz) const;

    // Compare the string for less than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator <  (const wchar_t *pwsz) const;

    // Compare the string for less than another AcString
    // acs : input reference to the other AcString
    bool operator <  (const AcString & acs) const;

    // Compare the string for less than or equal to a char
    // ch : input char to compare to
    bool operator <= (const char ch) const;

    // Compare the string for less than or equal to a Unicode char
    // wch : input char to compare to
    bool operator <= (const wchar_t wch) const;

    // Compare the string for less than or equal to a string of chars
    // psz : input pointer to the string of chars
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
    // psz : input pointer to the string of chars
    int  match(const char *psz) const;

    // Return the number of chars matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    int  match(const wchar_t *pwsz) const;

    // Return the number of chars matching another AcString
    // acs : input reference to the other AcString
    int  match(const AcString & acs) const;

    // Return number of chars case-independently matching a string of chars
    // psz : input pointer to the string of chars
    int  matchNoCase(const char *psz) const;

    // Return number of chars case-indep'ly matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    int  matchNoCase(const wchar_t *pwsz) const;

    // Return number of chars case-indep'ly matching another AcString
    // acs : input reference to the other AcString
    int  matchNoCase(const AcString & acs) const;

#ifdef _AFX
    //
    // MFC CString-using methods.  The CStringA class is the ansi
    // code page based CString, while CStringW is Unicode based.
    // CString maps to one or the other depending on whether the
    // UNICODE preprocessor symbol is defined.
    //

    // Construct an AcString from a CStringA
    // csa : input reference to the CStringA
    AcString(const CStringA &csa);

    // Construct an AcString from a CStringW
    // csw : input reference to the CStringW
    AcString(const CStringW &csw);

    // Initialize this AcString from a CStringA
    // csa : input reference to the CStringA
    AcString & operator = (const CStringA &csa);

    // Initialize this AcString from a CStringW
    // csw : input reference to the CStringW
    AcString & operator = (const CStringW &csw);

    // Append a CStringA to this AcString
    // csa : input reference to the CStringA
    AcString & operator += (const CStringA &csa);

    // Append a CStringW to this AcString
    // csa : input reference to the CStringW
    AcString & operator += (const CStringW &csw);

    //
    // comparisons to CStrings.  Return -1, 0 or 1 to
    // indicate less than, equal to or greater than
    //

    // Compare this string to a CStringA
    // csa : input reference to the CStringA
    int  compare(const CStringA & csa) const;

    // Compare this string to a CStringW
    // csw : input reference to the CStringW
    int  compare(const CStringW & csw) const;

    // Compare this string case independently to a CStringA
    // csa : input reference to the CStringA
    int  compareNoCase(const CStringA & csa) const;

    // Compare this string case independently to a CStringW
    // csw : input reference to the CStringW
    int  compareNoCase(const CStringW & csw) const;

    // Compare for equality with a CStringA
    // csa : input reference to the CStringA
    bool operator == (const CStringA & ) const;

    // Compare for equality with a CStringW
    // csw : input reference to the CStringW
    bool operator == (const CStringW & ) const;

    // Compare for non-equality with a CStringA
    // csa : input reference to the CStringA
    bool operator != (const CStringA & ) const;

    // Compare for non-equality with a CStringW
    // csw : input reference to the CStringW
    bool operator != (const CStringW & ) const;

    // Compare for less than a CStringA
    // csa : input reference to the CStringA
    bool operator <  (const CStringA & ) const;

    // Compare for less than a CStringW
    // csw : input reference to the CStringW
    bool operator <  (const CStringW & ) const;

    // Compare for less than or equal to a CStringA
    // csa : input reference to the CStringA
    bool operator <= (const CStringA & ) const;

    // Compare for less than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator <= (const CStringW & ) const;

    // Compare for greater than a CStringA
    // csa : input reference to the CStringA
    bool operator >  (const CStringA & ) const;

    // Compare for greater than a CStringW
    // csw : input reference to the CStringW
    bool operator >  (const CStringW & ) const;

    // Compare for greater than or equal to a CStringA
    // csa : input reference to the CStringA
    bool operator >= (const CStringA & ) const;

    // Compare for greater than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator >= (const CStringW & ) const;

    // Return number of chars matching a CStringA
    // csa : input reference to the CStringA
    int  match(const CStringA & csa) const;

    // Return number of chars matching a CStringW
    // csw : input reference to the CStringW
    int  match(const CStringW & csw) const;

    // Return number of chars case-independently matching a CStringA
    // csa : input reference to the CStringA
    int  matchNoCase(const CStringA & csa) const;

    // Return number of chars case-independently matching a CStringW
    // csw : input reference to the CStringW
    int  matchNoCase(const CStringW & csw) const;

    // Note: unfortunately there is not now an assignment operator for
    // assigning AcStrings to CStrings, as in CString cs = AcString("x");
#endif

  private:
    void clearAll();
    struct PtrAndData;
    unsigned char mnFlags;
    union {
        char mszStr[7];
        struct {
            char mnPad1;
            wchar_t mwszStr[3];
        };
        struct {
            char mnPad2[3];
            union {
                char *mpszData;
                wchar_t *mpwszData;
                PtrAndData *mpPtrAndData;
            };
        };
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

// Compare an AcString and a char for equality
// ch : input char to compare
// acs : input reference to the AcString
bool operator == (char ch, const AcString & acs);

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

// Compare an AcString and a char for non-equality
// ch : input char to compare
// acs : input reference to the AcString
bool operator != (char ch, const AcString & acs);

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

// Return whether a char is greater than an AcString
// ch : input char to compare
// acs : input reference to the AcString
bool operator >  (char ch, const AcString & acs);

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

// Check for a char being greater than or equal to an AcString
// ch : input char to compare
// acs : input reference to the AcString
bool operator >= (char ch, const AcString & acs);

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

// Check for a char being less than an AcString
// ch : input char to compare
// acs : input reference to the AcString
bool operator <  (char ch, const AcString & acs);

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

// Check for a char being less than or equal to an AcString
// ch : input char to compare
// acs : input reference to the AcString
bool operator <= (char ch, const AcString & acs);

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

// Copy an AcString and insert a char in front of it
// ch : input char to insert
AcString operator + (char ch, const AcString & acs);

// Copy an AcString and insert a Unicode char in front of it
// wch : input char to insert
AcString operator + (wchar_t wch, const AcString & acs);

// Copy an AcString and insert a string of chars in front of it
// psz : input pointer to the string of chars to insert
AcString operator + (const char *psz, const AcString & acs);

// Copy an AcString and insert a string of Unicode chars in front of it
// pwsz : input pointer to the string of chars to insert
AcString operator + (const wchar_t *pwsz, const AcString & acs);

#ifdef _AFX
// Compare a CStringA for equality with an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator == (const CStringA & csa, const AcString & acs);

// Compare a CStringW for equality with an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator == (const CStringW & csw, const AcString & acs);

// Compare a CStringA for in-equality with an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator != (const CStringA & csa, const AcString & acs);

// Compare a CStringW for in-equality with an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator != (const CStringW & csw, const AcString & acs);

// Compare a CStringA for greater than an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator >  (const CStringA & csa, const AcString & acs);

// Compare a CStringW for greater than an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator >  (const CStringW & csw, const AcString & acs);

// Compare a CStringA for greater than or equal to an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator >= (const CStringA & csa, const AcString & acs);

// Compare a CStringW for greater than or equal to an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator >= (const CStringW & csw, const AcString & acs);

// Compare a CStringA for less than to an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator <  (const CStringA & csa, const AcString & acs);

// Compare a CStringW for less than an AcString
// csw : input reference to the CStringW
// acs : input reference to the AcString
bool operator <  (const CStringW & csw, const AcString & acs);

// Compare a CStringA for less than or equal to an AcString
// csa : input reference to the CStringA
// acs : input reference to the AcString
bool operator <= (const CStringA & csa, const AcString & acs);

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
AcString operator + (const CStringA & csa, const AcString & acs);
AcString operator + (const CStringW & csw, const AcString & acs);
#endif
#endif

// Accessing inlines
//
inline AcString::operator const char *() const
{
    return this->kszPtr();
}

inline AcString::operator const wchar_t *() const
{
    return this->kwszPtr();
}

#ifdef UNICODE
inline const wchar_t * AcString::kTCharPtr() const
{
    return this->kwszPtr();
}

inline size_t AcString::tcharLength() const
{
    return this->lengthW();
}

inline int AcString::find(char chLead, char chTrail) const
{
    return this->findW(chLead, chTrail);
}

#elif _UNICODE
#error "Unexpected _UNICODE definition"
#else
inline const char * AcString::kTCharPtr() const
{
    return this->kszPtr();
}

inline size_t AcString::tcharLength() const
{
    return this->lengthA();
}

inline int AcString::find(char chLead, char chTrail) const
{
    return this->findA(chLead, chTrail);
}

#endif

inline void AcString::clearAll()
{
    this->mnFlags = 0;
    this->mnPad1 = 0;
    this->mwszStr[0] = 0;
    this->mpszData = NULL;
}

// Extraction inlines
//
inline AcString AcString::mid(int nStart, int nNumChars) const
{
    return this->substr(nStart, nNumChars);
}

// Assignment inlines
//
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

// Comparison inlines
//
inline bool AcString::operator == (char ch) const
{
    return this->compare(ch) == 0;
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

inline bool AcString::operator != (char ch) const
{
    return this->compare(ch) != 0;
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

inline bool AcString::operator > (char ch) const
{
    return this->compare(ch) > 0;
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

inline bool AcString::operator >= (char ch) const
{
    return this->compare(ch) >= 0;
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

inline bool AcString::operator < (char ch) const
{
    return this->compare(ch) < 0;
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
#ifdef _AFX

inline AcString::AcString(const CStringA &csa)
{
    const char *psz = (const char *)csa;
    this->clearAll();
    *this = psz;
}

inline AcString::AcString(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    this->clearAll();
    *this = pwsz;
}

inline AcString & AcString::operator=(const CStringA &csa)
{
    const char *psz = (const char *)csa;
    return this->assign(psz);
}
inline AcString & AcString::operator=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->assign(pwsz);
}

inline AcString & AcString::operator+=(const CStringA &csa)
{
    const char *psz = (const char *)csa;
    return this->append(psz);
}
inline AcString & AcString::operator+=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->append(pwsz);
}

inline int AcString::compare(const CStringA &csa) const
{
    const char *psz = (const char *)csa;
    return this->compare(psz);
}

inline int AcString::compare(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compare(pwsz);
}

inline int AcString::compareNoCase(const CStringA &csa) const
{
    const char *psz = (const char *)csa;
    return this->compareNoCase(psz);
}

inline int AcString::compareNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compareNoCase(pwsz);
}

inline int AcString::match(const CStringA &csa) const
{
    const char *psz = (const char *)csa;
    return this->match(psz);
}

inline int AcString::match(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->match(pwsz);
}

inline int AcString::matchNoCase(const CStringA &csa) const
{
    const char *psz = (const char *)csa;
    return this->matchNoCase(psz);
}

inline int AcString::matchNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->matchNoCase(pwsz);
}

inline bool AcString::operator == (const CStringA & csa) const
{
    return this->compare(csa) == 0;
}

inline bool AcString::operator != (const CStringA & csa) const
{
    return this->compare(csa) != 0;
}

inline bool AcString::operator > (const CStringA & csa) const
{
    return this->compare(csa) > 0;
}

inline bool AcString::operator >= (const CStringA & csa) const
{
    return this->compare(csa) >= 0;
}

inline bool AcString::operator < (const CStringA & csa) const
{
    return this->compare(csa) < 0;
}

inline bool AcString::operator <= (const CStringA & csa) const
{
    return this->compare(csa) <= 0;
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

// Global CString-related operators
inline bool operator == (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) == 0;
}

inline bool operator == (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) == 0;
}

inline bool operator != (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) != 0;
}

inline bool operator != (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) != 0;
}

inline bool operator >  (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) < 0;
}

inline bool operator >  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) < 0;
}

inline bool operator >= (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) <= 0;
}

inline bool operator >= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) <= 0;
}

inline bool operator <  (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) > 0;
}

inline bool operator <  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) > 0;
}

inline bool operator <= (const CStringA & csa, const AcString & acs)
{
    return acs.compare(csa) >= 0;
}

inline bool operator <= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) >= 0;
}

#ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline AcString operator + (const CStringA & csa, const AcString & acs)
{
    const char *psz = (const char *)csa;
    return acs.precat(psz);
}

inline AcString operator + (const CStringW & csw, const AcString & acs)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return acs.precat(pwsz);
}
#endif


#endif // _AFX

// Inline global operators
inline bool operator == (char ch, const AcString & acs)
{
    return acs.compare(ch) == 0;
}

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

inline bool operator != (char ch, const AcString & acs)
{
    return acs.compare(ch) != 0;
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

inline bool operator > (char ch, const AcString & acs)
{
    return acs.compare(ch) < 0;
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

inline bool operator >= (char ch, const AcString & acs)
{
    return acs.compare(ch) <= 0;
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

inline bool operator < (char ch, const AcString & acs)
{
    return acs.compare(ch) > 0;
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

inline bool operator <= (char ch, const AcString & acs)
{
    return acs.compare(ch) >= 0;
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
inline AcString operator + (char ch, const AcString & acs)
{
    return acs.precat(ch);
}

inline AcString operator + (wchar_t wch, const AcString & acs)
{
    return acs.precat(wch);
}

inline AcString operator + (const char *psz, const AcString & acs)
{
    return acs.precat(psz);
}

inline AcString operator + (const wchar_t *pwsz, const AcString & acs)
{
    return acs.precat(pwsz);
}

#endif // !_Ac_String_h

