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


#ifndef FORMATCODECPROPERTYSETITERATOR_H
#include <FormatCodecPropertySetIterator.h>
#endif
#ifndef IMAGEFORMATCODEC_H
#include <ImageFormatCodec.h>
#endif
#ifndef FILESPECIFIER_H
#include <FileSpecifier.h>
#endif
#ifndef FINDFILEINTERFACE_H
namespace Atil { class FindFileInterface; }
#endif

#ifndef CORRELATIONPROPERTYSETITERATOR_H
#define CORRELATIONPROPERTYSETITERATOR_H

/// <summary>
/// This class is the typed implementation of the <c>FormatCodecPropertySetIterator</c>
/// base class. It holds properties related to intrafile and external correlation sources.</summary>
class CorrelationPropertySetIterator : public Atil::FormatCodecPropertySetIterator
{
public:
    /// <summary>Describes how the class will be used.</summary>
    enum Mode { 
        /// <summary>Opened for read.</summary>
        kForRead, 
        /// <summary>Opened for writing.</summary>
        kForWrite 
    };

    /// <summary> The constructor. </summary>
    /// <param name="mode">The description of the usage of the instance.</param>
    /// <param name="requestingCodec">A const reference to the <c>ImageFormatCodec</c> of the image
    ///file that is acquiring or writing the properties.</param>
    /// <param name="fsImage">A const reference to a <c>FileSpecifier</c> instance that 
    ///holds the name of the image file for reference to possible sources of correlation.</param>
    /// <param name="pFFI">The NULL defaulted pointer to an instance of the <c>FindFileInterface</c> 
    /// which can be used to locate files that may have correlation information.</param>
    CorrelationPropertySetIterator (Mode mode, const Atil::ImageFormatCodec& requestingCodec, 
        const Atil::FileSpecifier& fsImage, Atil::FindFileInterface* pFFI = (Atil::FindFileInterface*) NULL);
};


#endif
