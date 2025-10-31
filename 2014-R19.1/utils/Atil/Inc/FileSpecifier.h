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
#include "StringBuffer.h"
#endif

#ifndef FILESPECIFIER_H
#define FILESPECIFIER_H

namespace Atil
{
/// <summary>
/// This class holds an instance of a <c>StringBuffer</c> and an enum to identify
/// the source of encoded image data. 
/// </summary>
///
/// <remarks>
/// The <c>FileSpecifier</c> class is not aptly named. It is intended to allow the 
/// specification of non-filesystem resident imagery. It currently supports this 
/// minimally through the use of the <c>FileSpecifier::Type</c> enum entry <c>kOther</c>.
/// The string of bytes in the <c>StringBuffer</c> instance should be interpreted as
/// representing the type of the enum.
/// </remarks>
///
class FileSpecifier 
{
public:
    /// <summary>
    /// The <c>Type</c> enum dictates the usage of the enclosed <c>StringBuffer</c>.
    /// </summary>
    ///
    /// <remarks>
    /// Additional entries may be added with later releases.
    /// </remarks>
    ///
    enum Type { 

        /// <summary>
        /// This entry indicates that the enclosed <c>StringBuffer</c> instance holds a 
        /// file system legal string that can be used to access an encoded image in a "file".
        /// </summary>
        ///
        kFilePath, 

        /// <summary>
        /// This entry indicates that the enclosed <c>StringBuffer</c> instance holds
        /// a value that is something other than a file system legal string.
        /// </summary>
        ///
        /// <remarks>
        /// As <c>kOther</c> does not indicate anything more than denial the the string
        /// is a legal file path the interpretation of the contents of the string is
        /// up to the <c>ImageFormatCodec</c> that is passed the <c>FileSpecifier</c>.
        /// </remarks>
        ///
        kOther,

        /// <summary>
        /// This entry indicates that the string held is in the form of a protocol string that
        /// holds additional file information used for loading the image data.
        /// </summary>
        ///
        kStorageProtocol
    };

public:

    /// <summary>
    /// The empty or "NULL" constructor for an <c>Atil::FileSpecifier</c>. 
    /// </summary>
    ///
    /// <remarks>
    /// An instance of an FileSpecifier created through this constructor is intended only to facilitate
    /// the later assignment of a valid FileSpecifier. The instance created through this constructor has
    /// no internal data that can be returned. 
    /// </remarks>
    ///
    FileSpecifier ( );
    
    /// <summary>
    /// The constructor for an <c>Atil::FileSpecifier</c>. 
    /// </summary>
    ///
    /// <param name='sbString'>A <c>StringBuffer</c> instance identifying the image location.
    /// </param>
    ///
    /// <param name='type'>An <c>FileSpecifier::Type</c> enum entry identifying the 
    /// type of information contained in the string.
    /// </param>
    ///
    /// <remarks>
    /// The parameter <c>StringBuffer</c> will be copied into the instance. No reference
    /// to the parameter instance is made after the constructor has finished.
    /// </remarks>
    ///
    FileSpecifier (const StringBuffer& sbString, Type type);

    /// <summary>
    /// The copy constructor for an <c>Atil::FileSpecifier</c>. 
    /// </summary>
    ///
    /// <param name="x">A constant reference to a <c>FileSpecifier</c> instance that to be copied.
    /// </param>
    FileSpecifier ( const FileSpecifier& x );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FileSpecifier ();

    /// <summary>
    /// The query for the <c>FileSpecifier::Type</c> of the instance. 
    /// </summary>
    ///
    /// <returns>
    /// This method returns the <c>FileSpecifier::Type</c> of the instance.
    /// </returns>
    ///
    virtual FileSpecifier::Type type () const;

    /// <summary>
    /// The query for the <c>StringBuffer</c> of the instance. 
    /// </summary>
    ///
    ///
    /// <returns>
    /// This returns a const reference to the <c>StringBuffer</c> holding the instance string.
    /// </returns>
    ///
    virtual const StringBuffer& string () const;

    /// <summary>
    /// The <c>operator=</c> over writes the assigned instance 
    /// with the contents of the argument.
    /// </summary>
    ///
    /// <param name="rhs">A constant reference to a <c>FileSpecifier</c> instance that will be
    /// referenced for the <c>msbString</c> and <c>mType</c> member values to be set.
    /// </param>
    ///
    /// <returns>
    /// This method returns a constant reference of <c>*this</c> that has been modified.
    /// </returns>
    ///
    virtual const FileSpecifier& operator= ( const FileSpecifier& rhs );

    /// <summary>
    /// The <c>operator==</c> will test the <c>StringBuffer</c> and 
    /// <c>FileSpecifier::Type</c> for equality returning true if an exact match is made.
    /// </summary>
    ///
    /// <param name="rhs">A constant reference to a <c>FileSpecifier</c> instance that will be
    /// referenced for the <c>msbString</c> and <c>mType</c> member values to be compared.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two <c>FileSpecifier</c> instances are equivalent.
    /// </returns>
    ///
    virtual bool operator== ( const FileSpecifier& rhs );

    /// <summary>
    /// The <c>operator!=</c> will test the <c>StringBuffer</c> and 
    /// <c>FileSpecifier::Type</c> for equality returning true if an exact match is not made.
    /// </summary>
    ///
    /// <param name="rhs">A constant reference to a <c>FileSpecifier</c> instance that will be
    /// referenced for the <c>msbString</c> and <c>mType</c> member values to be set.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two <c>FileSpecifier</c> instances are not equivalent.
    /// </returns>
    ///
    virtual bool operator!= ( const FileSpecifier& rhs );

    /// <summary>
    /// This will set the contents of a FileSpecifier instance to the parameters over
    /// writing the current contents.
    /// </summary>
    ///
    /// <param name='sbString'>A <c>StringBuffer</c> instance identifying the image location.
    /// </param>
    ///
    /// <param name='type'>An <c>FileSpecifier::Type</c> enum entry identifying the 
    /// type of information contained in the string.
    /// </param>
    ///
    /// <remarks>
    /// The parameter <c>StringBuffer</c> will be copied into the instance. No reference
    /// to the parameter instance is made after the method has finished.
    /// </remarks>
    ///
    virtual void set (const StringBuffer& sbString, Type type);

private:
    StringBuffer msbString;
    FileSpecifier::Type mType;
};

} // end of namespace Atil

#endif

