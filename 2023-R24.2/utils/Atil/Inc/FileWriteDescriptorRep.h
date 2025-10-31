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
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif
#ifndef DATASTREAMINTERFACE_H
namespace Atil { class DataStreamInterface; }
#endif
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef FILEREADDESCRIPTOR_H
namespace Atil { class FileReadDescriptor; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef SIZE_H
namespace Atil { class Size; }
#endif

#ifndef FILEWRITEDESCRIPTORREP_H
#define FILEWRITEDESCRIPTORREP_H

namespace Atil
{

/// <summary>
/// This class serves as an abstract base class for the <c>FileWriteDescriptor</c>.
/// </summary>
class FileWriteDescriptorRep 
{
public:
    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="Atil::FileWriteDescriptor"/>
    /// </summary>
    virtual ~FileWriteDescriptorRep ();

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "codec">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    virtual void construct (const ImageFormatCodec* codec) = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual const ImageFormatCodec* formatCodec () const = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "fs">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    virtual void getFileSpecifier (FileSpecifier& fs) const = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "fs">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual bool setFileSpecifier (const FileSpecifier& fs) = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "pdsStream">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    virtual void setOutputStream (DataStreamInterface* pdsStream) = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "dataModel">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <param name= "size">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    virtual void createImageFrame (const DataModel& dataModel, Size size) = 0;
    
    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual bool requiredPropertiesSet () const = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual FormatCodecPropertySetIterator* newPropertySetIterator () = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "id">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "sbPropertyName">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "pProperty">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual bool setProperty ( const FormatCodecPropertyInterface* pProperty ) = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "fd">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual bool setProperties (const FileReadDescriptor* fd) = 0;

    /// <summary>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </summary>
    /// 
    /// <param name= "rowProvider">
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </param>
    /// 
    /// <returns>
    /// See <c>FileWriteDescriptor</c>. <see cref="FileWriteDescriptor"/>
    /// </returns>
    ///
    virtual int writeImageFrame (RowProviderInterface* rowProvider) = 0;

    /// <summary>Commits any pending writes and closes the written file </summary>
    /// <remarks>This is also called at class destruction.</remarks>
    virtual void closeFile() = 0;
};

} // end of namespace Atil

#endif
