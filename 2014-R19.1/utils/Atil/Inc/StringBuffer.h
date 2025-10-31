///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif

#ifndef STRINGBUFFER_H
#define STRINGBUFFER_H

namespace Atil
{

/// <summary>
/// The <c>StringBuffer</c> class is ATIL's class for avoiding string handling.
/// It forces all strings into a PASCAL form of byte count and array of bytes
/// model of string handling. It includes no facilities for concatenation nor
/// parsing. No searching is implemented. The purpose of the class is primarily
/// to carry strings from the application to the format codecs and vice versa.
/// </summary>
///
class StringBuffer 
{
public:
    /// <summary>
    /// This enum lists the character types that <c>StringBuffer</c> can wrap.
    /// It is up the the "user" to interpret the bytes contained as a string
    /// of one enum's type.
    /// </summary>
    ///
    enum CharacterType { 
        /// <summary> This entry indicates a specific char encoding scheme.</summary>
        kASCII, 
        /// <summary> This entry indicates a specific char encoding scheme.</summary>
        kUTF_8, 
        /// <summary> This entry indicates a specific char encoding scheme.</summary>
        kUTF_16, 
        /// <summary> This entry indicates a specific char encoding scheme.</summary>
        kUTF_32,
        /// <summary> This entry indicates a specific char encoding scheme.</summary>
        kMBCS 
    };
    
    /// <summary>
    /// This static method will calculate the number of bytes in a string
    /// of the given <c>CharacterType</c>.
    /// </summary>
    ///
    /// <param name="pString">This is a pointer to an array of bytes that
    /// holds a string.
    /// </param>
    ///
    /// <param name="type">This is a value of the <c>StringBuffer::CharacterType</c>
    /// that describes the character type of the passed in string.
    /// </param>
    ///
    /// <returns>
    /// This method returns the number of bytes needed to store the string including
    /// any needed termination character.
    /// </returns>
    ///
    static int bytesInString ( const Byte* pString, CharacterType type );

    /// <summary>
    /// This method will attempt to convert from one character type to another.
    /// </summary>
    ///
    /// <param name="sbString">The <c>StringBuffer</c> instance to be converted.
    /// </param>
    ///
    /// <param name="sbResult">A reference to a <c>StringBuffer</c> that will be set
    /// to the converted result.
    /// </param>
    ///
    /// <param name="type">The <c>CharacterType</c> that the converted string should have.
    /// </param>
    /// 
    /// <remarks>
    /// The conversion offered by this method is basic and uses the default conversion
    /// methods offered by the host operating systems. As such, it serves for file path
    /// conversions but is not appropriate for more sophisticated text.
    /// </remarks>
    ///
    static void convertString ( const StringBuffer& sbString,
        StringBuffer& sbResult, CharacterType type );

    /// <summary>
    /// This returns <c>CharacterType</c> under which ATIL was built.
    /// </summary>
    ///
    /// <returns>
    /// Returns a member of the <c>CharacterType</c> enum.
    /// </returns>
    ///
    static CharacterType defaultCharacterType ();

public:

    /// <summary>
    /// The default (empty) constructor.
    /// </summary>
    ///
    StringBuffer ();

    /// <summary>
    /// The initialization constructor.
    /// </summary>
    /// 
    /// <param name="nNumBytes">The number bytes to allocate to store the string.
    /// </param>
    /// 
    /// <param name="type">The <c>CharacterType</c> of the string that will be stored.
    /// </param>
    ///
    StringBuffer (int nNumBytes, CharacterType type = StringBuffer::kASCII);

    /// <summary>
    /// The initialization constructor.
    /// </summary>
    /// 
    /// <param name="nNumBytes">The number bytes to allocate to store the string.
    /// </param>
    ///
    /// <param name="pBytes">A const pointer to a buffer containing the number of bytes
    /// of data passed in that are to be stored.
    /// </param>
    ///
    /// <param name="type">The <c>CharacterType</c> of the string that will be stored.
    /// </param>
    ///
    StringBuffer (int nNumBytes, const Byte* pBytes, CharacterType type = StringBuffer::kASCII);

    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    /// <param name="x">
    /// A const reference to the <c>StringBuffer</c> to copy.
    /// </param>
    ///
    StringBuffer (const StringBuffer& x);

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    virtual ~StringBuffer ();

    /// <summary>
    /// This method returns a const pointer to the internal byte array that holds the string.
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to a <c>Byte</c> array.
    /// </returns>
    ///
    virtual const Byte* data () const;

    /// <summary>
    /// This method will return the size in bytes of the internal byte 
    /// array that holds the string.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of bytes held in the internal array.
    /// </returns>
    ///
    virtual int numDataBytes () const;

    /// <summary>
    /// This method returns the <c>CharacterType</c> that has been set as the encoding
    /// type of the internal byte array that holds the string.
    /// </summary>
    ///
    /// <returns>
    /// Returns a member of the <c>CharacterType</c> enum.
    /// </returns>
    ///
    virtual CharacterType type () const;

    /// <summary>
    /// Like the assignment operator this method will over write the object with the values
    /// of the argument.
    /// </summary>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual StringBuffer& set (const StringBuffer& string);

    /// <summary>
    /// This method mimics the initialization constructor and will over write the current
    /// object members with the arguments.
    /// </summary>
    /// 
    /// <param name="nNumBytes">The number bytes to allocate to store the string.
    /// </param>
    ///
    /// <param name="pChar">A const pointer to a buffer containing the number of bytes
    /// of data passed in that are to be stored.
    /// </param>
    ///
    /// <param name="type">The <c>CharacterType</c> of the string that will be stored.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual StringBuffer& set (int numBytes, const Byte* pChar, CharacterType type = StringBuffer::kASCII);

    /// <summary>
    /// This is a simplistic test that will test the all the bytes of the string 
    /// and return true if they are all zero.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the first internal array is empty.
    /// </returns>
    ///
    virtual bool isZero () const;

    /// <summary>
    /// The assignment operator will cause the current values to be over written with those
    /// of the argument.
    /// </summary>
    ///
    /// <param name="rhs">
    /// The argument to be copied.
    ///</param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    StringBuffer& operator=( const StringBuffer& rhs );

    /// <summary>
    /// The equals operator will return true if all the members of each are equal respectively.
    /// The test for equivalence is a byte wise test for each byte of the embedded buffer.
    /// </summary>
    ///
    /// <param name="rhs">
    /// The argument to be compared.
    ///</param>
    ///
    /// <returns>
    /// Returns true if the instance are equivalent.
    /// </returns>
    ///
    bool operator==( const StringBuffer& rhs ) const;

    /// <summary>
    /// The not equals operator will return true if any member does not equal that of the
    /// argument.
    /// </summary>
    ///
    /// <param name="rhs">
    /// The argument to be compared.
    ///</param>
    ///
    /// <returns>
    /// Returns true if the instance are not equivalent.
    /// </returns>
    ///
    bool operator!=( const StringBuffer& rhs ) const;

    /// <summary> Cast operator to convert to a <c>Atil::char_t</c> for use as the
    /// default string type on the platform ATIL is compiled for. </summary>
    /// <returns> This returns a <c>const char_t*</c> pointer for use as a string.</returns>
    operator const char_t*() const;
private:
    int mNumBytes;
    Byte* mpData;
    CharacterType  meCharType;
};

} //end of namespace

#endif

