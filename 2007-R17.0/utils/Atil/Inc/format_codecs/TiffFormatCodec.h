///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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

#ifndef IMAGEFORMATCODEC_H
#include "ImageFormatCodec.h"
#endif
#ifndef DATASTREAMINTERFACE_H
#include "DataStreamInterface.h"
#endif

#ifndef FORMATCODECAPIVERSIONINTERFACE_H
namespace Atil { class FormatCodecApiVersionInterface; }
#endif

#ifndef TIFFFORMATCODEC_H
#define TIFFFORMATCODEC_H

extern "C"
{
    const Atil::FormatCodecApiVersionInterface* ATIL_EXPORT tiffApiVersion ();
}

class TiffFormatCodec : public Atil::ImageFormatCodec, public Atil::ImageFormatCodecStreamingInterface
{
//    enum FormatDecodabilityType { kStronglyTyped,
//                                  kMultiFileStronglyTyped,
//                                  kLooselyTyped
//                                };

public:
	// These enums need to be replicated in MsGeoTiffFormatCodec in the same order
    enum TiffId { kMember, kByteOrder, kPhotometricInterpretation, kArtist
		, kCopyright, kDateTime, kFillOrder, kGrayResponse, kHostComputer
		, kImageDescription, kScannerMake, kScannerModel, kSoftware
		, kCompressionType, kPrivateTag, kSampleRange, kPageInformation
    };
public:

    TiffFormatCodec (int enabledPatentedEncoding = 0);
    virtual ~TiffFormatCodec ();

    virtual void getLibVersionInfo (unsigned int& nLibMajor,
        unsigned int& nLibMinor, unsigned int& nBuild) const;
    virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;

    virtual Atil::ImageFormatCodec::CodecCapability codecCapability () const;

    virtual bool isValidFileName (const Atil::FileSpecifier& fs) const;
    virtual ImageFormatCodec::FormatType getFormatDecodabilityType () const;

    virtual bool getTiffPropertyName(TiffId id, Atil::StringBuffer& sbName) const;

    virtual bool isFormatFeature ( FormatFeature feature ) const;

    virtual FormatOrganization getFormatOrganization () const;
    virtual FormatFrameType getFormatFrameType () const;

    virtual bool isSupportedProperty (
        Atil::FormatCodecPropertyInterface::PropertyIdentifier propId,
        Atil::StringBuffer* pCustomPropertyName = NULL) const;

    virtual int getNumExtensions () const;
    virtual void getExtensionText (int nExtensionIndex,
        Atil::StringBuffer& sbExtension) const;

    virtual void getFormatName (Atil::StringBuffer& sbFormatName) const;
    virtual void getDescriptionText (Atil::StringBuffer& sbDescription) const;
    virtual void getCopyrightText (Atil::StringBuffer& sbCopyright) const;

    void getPrivateTagName(unsigned short tagID, Atil::StringBuffer& TagName) const;

    virtual ImageFormatCodec::FormatDecodability isDecodableFile (
        const Atil::FileSpecifier& fileSpecifier, Atil::FindFileInterface * ff = NULL) const;

    virtual bool isEncodableImage (const Atil::DataModelAttributes& allAboutImageData,
        Atil::Size size ) const;

    virtual Atil::ReadImageFileInterface* openImage (
        const Atil::FileSpecifier* fsThisImage) const;

    virtual Atil::ReadImageFileInterface * openImage (
        const Atil::FileSpecifier* fsThisImage, Atil::FindFileInterface& ff) const;

    virtual Atil::WriteImageFileInterface* writeImage () const;

    // Clone the open image file. It is used by FileReadDescriptor when cloning.
    // Not recommended for developers. FileReadDescriptor should be used instead.
    virtual Atil::ReadImageFileInterface* cloneOpenImage (
        const Atil::ReadImageFileInterface* pOpenImage ) const;

    // ImageFormatCodecStreamInterface::openImage method 
    // for creating images from streamed sources.
    // NOTE:: The DataStreamInterface classes must be SeekableDataStreamInterface classes!
    virtual Atil::ReadImageFileInterface* openImage (
        Atil::DataStreamInterface* pdsStream) const;

    // ImageFormatCodecStreamInterface::writeImage method for saving images 
    /// to streamed destinations
    // NOTE:: The DataStreamInterface classes must be SeekableDataStreamInterface classes!
    virtual Atil::WriteImageFileInterface* writeImage (
        Atil::DataStreamInterface* pdsStream) const;

    virtual int patentedEncodingEnabled () const;

	// Apps wishing to utilize the LibGeoTIFF CSV files need to call the
	// "setPathToCsvFiles" with the location of the CSV files.
	void setPathToCsvFiles(const Atil::StringBuffer& sbPath);
	void getPathToCsvFiles(Atil::StringBuffer& sbPath) const;

private:
    bool mbPatentedReadEnabled;
    bool mbPatentedWriteEnabled;

	static Atil::StringBuffer	msbCsvPath;	// Shared by all instances of the codec
};

#endif

