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

#ifndef FORMATCODECPROPERTYINTERFACE_H
#include <FormatCodecPropertyInterface.h>
#endif
#ifndef FORMATCODECINTPROPERTY_H
#include <FormatCodecIntProperty.h>
#endif
#ifndef FORMATCODECDOUBLEPROPERTY_H
#include <FormatCodecDoubleProperty.h>
#endif
#ifndef FORMATCODECSTRINGPROPERTY_H
#include <FormatCodecStringProperty.h>
#endif
#ifndef FORMATCODECINCLUSIVEPROPERTYSETINTERFACE_H
#include <FormatCodecInclusivePropertySetInterface.h>
#endif
#ifndef FORMATCODECEXCLUSIVEPROPERTYSETINTERFACE_H
#include <FormatCodecExclusivePropertySetInterface.h>
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
#include <FormatCodecPropertySetIterator.h>
#endif
#ifndef FORMATCODECTRANSPARENCY_H
#include <FormatCodecTransparency.h>
#endif
#ifndef FORMATCODECDENSITY_H
#include <FormatCodecDensity.h>
#endif
#ifndef FORMATCODECCOLORPROPERTY_H
#include <FormatCodecColorProperty.h>
#endif
#ifndef FORMATCODECBOOLEANPROPERTY_H
#include <FormatCodecBooleanProperty.h>
#endif

#ifndef PNGFORMATCODEC_H
#include <PngFormatCodec.h>
#endif

#ifndef PNG_H
struct png_info_struct;
typedef struct png_info_struct png_info;
typedef png_info * png_infop;

struct png_struct_def;
typedef struct png_struct_def png_struct;
typedef png_struct * png_structp;
#endif

#ifndef PNGCUSTOMPROPERTIES_H
#define PNGCUSTOMPROPERTIES_H
//--------------------------------------------------------
// PngCustomProperty 
//--------------------------------------------------------
//
//--------------------------------------------------------
// Common base class for all PNG custom classes. Allows for
// easier identification of exported properties.
//--------------------------------------------------------
class PngCustomProperty
{
public:
    virtual ~PngCustomProperty();
    PngFormatCodec::PngIdentifier pngId ( ) const;
    virtual bool writeBefore ( ) const;

    virtual bool write ( png_structp pPng, png_infop pInfo ) const = 0;
protected:
    PngFormatCodec::PngIdentifier mPngId;
    bool mbWriteBeforePLTE;
};

//--------------------------------------------------------
// PngGamma 
//--------------------------------------------------------
class PngGamma : public Atil::FormatCodecDoubleProperty, public PngCustomProperty
{
public:
    PngGamma ();
    PngGamma (png_structp pPng, png_infop pInfo);
    ~PngGamma ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;
    bool write ( png_structp pPng, png_infop pInfo ) const;
};

//--------------------------------------------------------
// PngScale
//--------------------------------------------------------
class PngScale : public Atil::FormatCodecInclusivePropertySetInterface, public PngCustomProperty
{
public:
    PngScale ();
    PngScale (png_structp pPng, png_infop pInfo);
    ~PngScale ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;
    bool write ( png_structp pPng, png_infop pInfo ) const;
};

//--------------------------------------------------------
// PngPageOffset
//--------------------------------------------------------
class PngPageOffset : public Atil::FormatCodecInclusivePropertySetInterface, public PngCustomProperty
{
public:
    PngPageOffset ();
    PngPageOffset (png_structp pPng, png_infop pInfo);
    ~PngPageOffset ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;
    bool write ( png_structp pPng, png_infop pInfo ) const;
};

//--------------------------------------------------------
// PngText
//--------------------------------------------------------
class PngText : public Atil::FormatCodecStringProperty, public PngCustomProperty
{
public:
    enum Keyword { kComment = 0, kTitle, kAuthor, kDescription, kCopyright, kCreationTime,
                    kSoftware, kDisclaimer, kWarning, kSource };

    static const char* getString ( Keyword key );
public:
    PngText ( const Atil::StringBuffer& sbDefault, int nMaximumBytes, Keyword key = kComment );
    ~PngText ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    void getKeyword ( const char*& pKeyword ) const;
    bool write ( png_structp pPng, png_infop pInfo ) const;

protected:
    Keyword mKeyword;

    static char * mcpKeywords[10];
};

//--------------------------------------------------------
// PngSRGB
//--------------------------------------------------------
class PngSRGB : public Atil::FormatCodecExclusivePropertySetInterface, public PngCustomProperty
{
    enum Intent { kPerceptual = 0, kRelative, kSaturation, kAbsolute };
public:
    PngSRGB ( );
    PngSRGB ( png_structp pPng, png_infop pInfo );
    ~PngSRGB ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;
    virtual void setSelectedIndex (int nSelectionIndex);
    bool write ( png_structp pPng, png_infop pInfo ) const;
private:
    Intent mSRgbIntent;
};

//--------------------------------------------------------
// PngHistogram
//--------------------------------------------------------
class PngHistogram : public Atil::FormatCodecPropertyInterface, public PngCustomProperty
{
public:
    PngHistogram ();
    PngHistogram (png_structp pPng, png_infop pInfo);
    ~PngHistogram ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;

    int numEntries () const;
    void getHistogram ( int nEntries, unsigned short* pEntries ) const;
    
    void setHistogram ( int nEntries, unsigned short* pEntries );
    bool write ( png_structp pPng, png_infop pInfo ) const;

private:
    unsigned short * masHistogram;
    int mnEntries;
};

//--------------------------------------------------------
// PngGraySignificantBits 
//--------------------------------------------------------
class PngGraySignificantBits : public Atil::FormatCodecIntProperty, public PngCustomProperty
{
public:
    PngGraySignificantBits ();
    PngGraySignificantBits (png_structp pPng, png_infop pInfo);
    ~PngGraySignificantBits ();

    bool write ( png_structp pPng, png_infop pInfo ) const;
};

//--------------------------------------------------------------------
// PngCompression
//--------------------------------------------------------------------
class PngCompressionType : public Atil::FormatCodecPropertyInterface
{
public:
	enum Compression { kNone = 0, kLow = 1, kMedium = 3, kNormal = 6, kHigh = 9 };

public:
	PngCompressionType(Compression type);
	~PngCompressionType();
	virtual Atil::FormatCodecPropertyInterface* clone()const;

	Compression type();

private:
	Compression mCompressionType;
};

class PngCompression : public Atil::FormatCodecExclusivePropertySetInterface
{
public:
	PngCompression(PngCompressionType::Compression type = PngCompressionType::kNormal);
	~PngCompression();

public:
	virtual Atil::FormatCodecPropertyInterface* clone()const;
	
	PngCompressionType::Compression getCompressionType(int nIndex)const;
	bool selectCompression(PngCompressionType::Compression use);

	bool write(png_structp pPng, png_infop pInfo) const;
};
//--------------------------------------------------------
// PngPngInterlacing
//--------------------------------------------------------
class PngInterlacing : public Atil::FormatCodecBooleanProperty, public PngCustomProperty
{
public:
    PngInterlacing ();
    PngInterlacing (png_structp pPng, png_infop pInfo);
    ~PngInterlacing ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;
    bool write(png_structp pPng, png_infop pInfo) const;
};

#endif
