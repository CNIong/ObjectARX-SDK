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
