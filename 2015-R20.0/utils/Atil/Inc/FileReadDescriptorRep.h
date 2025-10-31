//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FILEREADDESCRIPTOR_H
#include "FileReadDescriptor.h"
#endif
#ifndef DATASTREAMINTERFACE_H
#include "DataStreamInterface.h"
#endif
#ifndef TRANSFORMS_H
#include "Transforms.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef FINDFILEINTERFACE_H
namespace Atil { class FindFileInterface; }
#endif

#ifndef FILEREADDESCRIPTORREP_H
#define FILEREADDESCRIPTORREP_H

namespace Atil
{

/// <summary>
/// This class serves as an abstract base class for the <c>FileReadDescriptor</c>.
/// </summary>
class FileReadDescriptorRep 
{
public:
    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'fs'>   
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    /// <param name= 'pFF'>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// 
    virtual void construct (const FileSpecifier& fs, FindFileInterface* pFF ) = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    /// <param name= 'fs'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// <param name= 'useThisCodec'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// <param name= 'pFF'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/> 
    /// </param>
    /// 
    virtual void construct (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec, FindFileInterface* pFF ) = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'pdsStream'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// <param name= 'useThisCodec'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// 
    virtual void construct (DataStreamInterface* pdsStream, const ImageFormatCodec* useThisCodec) = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'pCloneRep'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// 
    virtual void construct (FileReadDescriptorRep* pCloneRep) = 0;
    
    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    virtual void open () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    virtual void close () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'fs'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    virtual void getFileSpecifier (FileSpecifier& fs) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'size'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    virtual void getDataSize (Size& size) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual Atil::Orientation dataOrientation() const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    /// 
    /// <param name= 'size'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// 
    virtual void getOrientedSize (Size& size) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual const DataModel& dataModel () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual const ImageFormatCodec * formatCodec () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual int numFrames () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    /// 
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual int selectedFrame () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'frame'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param> 
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual bool setFrame (int frame) = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    ///
    virtual FileReadDescriptor::MethodType loadMethod () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/> 
    /// </returns> 
    ///
    virtual FormatCodecPropertySetIterator* newPropertySetIterator () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'id'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    /// 
    virtual FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'sbPropertyName'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    ///
    virtual FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    /// 
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    ///
    virtual RowProviderInterface* read () = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'dScale'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    /// <param name= 'filterMethod'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    ///
    virtual RowProviderInterface* scaledRead (const double& dScale, Resample::FilterTypes filterMethod) = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns>
    ///
    virtual int numClosureSetFiles () const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    ///
    /// <param name= 'nIndex'> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </param>
    ///
    /// <returns> See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </returns> 
    ///
    virtual FileSpecifier getClosureSetFilename (int nIndex) const = 0;

    /// <summary>
    /// See <c>FileReadDescriptor</c>. <see cref="FileReadDescriptor"/>
    /// </summary>
    virtual ~FileReadDescriptorRep ();

};

} // end of namespace Atil
#endif

