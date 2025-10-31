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
#ifndef FORMATCODECPROPERTYSETITERATOR_H
#include <FormatCodecPropertySetIterator.h>
#endif
#ifndef FORMATCODECSTRINGPROPERTY_H
#include <FormatCodecStringProperty.h>
#endif
#ifndef FORMATCODECDENSITY_H
#include <FormatCodecDensity.h>
#endif
#ifndef FORMATCODECASSOCIATION_H
#include <FormatCodecAssociation.h>
#endif
#ifndef STRINGBUFFER_H
#include <StringBuffer.h>
#endif
#ifndef FORMATCODECEXCLUSIVEPROPERTYSETINTERFACE_H
#include <FormatCodecExclusivePropertySetInterface.h>
#endif
#ifndef FORMATCODECTRANSPARENCY_H
#include <FormatCodecTransparency.h>
#endif
#ifndef TIFFFORMATCODEC_H
#include <TiffFormatCodec.h>
#endif

#ifndef TIFFCUSTOMPROPERTIES_H
#define TIFFCUSTOMPROPERTIES_H

struct tiff;

class TiffProperty 
{
public:
    virtual ~TiffProperty () {};
	virtual TiffFormatCodec::TiffId getTiffId () const { return mTiffId; }

protected:
	TiffFormatCodec::TiffId	mTiffId;

public:
   // treat as private please....
    virtual bool write( struct tiff* pTIFF ) const = 0;
};

//--------------------------------------------------------------------
// TiffCompression
//--------------------------------------------------------------------
class TiffCompressionType : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
    enum Compression { kNone = 0, kCCITT_RLE, kCCITT_RLEW, kCCITT_FAX3, kCCITT_FAX4,
        kLZW, kPackbits, kJPEG, kDeflate };
public:
    TiffCompressionType ( Compression type );
    ~TiffCompressionType ( );
    virtual Atil::FormatCodecPropertyInterface* clone () const;
    
    Compression type ();

    bool write ( struct tiff* pTIFF ) const;
private:
    Compression mCompressionType;
};

class TiffCompression : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:
    TiffCompression (int nBitsPerPixel, unsigned short usPhotometric, unsigned short usSamplesPerPixel
        , TiffCompressionType::Compression selected = TiffCompressionType::kNone
        , bool bWriting = false, bool bPatentedEncoding = false );

    ~TiffCompression ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;
    TiffCompressionType::Compression getCompressionType (int nIndex) const;
    bool selectCompression (TiffCompressionType::Compression use);

    bool write ( struct tiff* pTIFF ) const;
};

class TiffPhotometricInterpretation : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:
    enum Interpretation { kMinIsWhite, kMinIsBlack };
public:
    TiffPhotometricInterpretation ( 
        TiffPhotometricInterpretation::Interpretation interp =
        TiffPhotometricInterpretation::kMinIsWhite );

    ~TiffPhotometricInterpretation ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    Interpretation photometricInterpretation () const;
    bool write ( struct tiff* pTIFF ) const;
};

class TiffFillOrder : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:
    enum Order { kMSBtoLSB, kLSBtoMSB };
public:
    TiffFillOrder ( TiffFillOrder::Order order = TiffFillOrder::kMSBtoLSB );
    ~TiffFillOrder ();
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    Order fillOrder () const;
    bool write ( struct tiff* pTIFF ) const;

private:
    Order mOrder;
};

class TiffGrayResponseCurve : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
    TiffGrayResponseCurve ( );
    virtual ~TiffGrayResponseCurve ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;
    virtual int responseLevels () const;
    virtual void getResponseLevels ( float* pValues ) const;

    virtual void setResponseLevels ( int nLevels, unsigned short* pValues, int nTenthDivisor );   
    virtual unsigned short tenthDivisor () const { return (short) mnTenthScaler; }
    virtual unsigned short* unscaledData () const { return mpScaledLevels; }
    
    bool write ( struct tiff* pTIFF ) const;
private:
    unsigned short * mpScaledLevels;
    int mnLevels;
    int mnTenthScaler;
};

class TiffText : public Atil::FormatCodecStringProperty, public TiffProperty
{
public:
    TiffText (TiffFormatCodec::TiffId tiffId);
    TiffText (TiffFormatCodec::TiffId tiffId, Atil::StringBuffer* psbText);
    ~TiffText ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;
    bool setValue (const Atil::StringBuffer& sbValue);
    bool write ( struct tiff* pTIFF ) const;
};

class TiffPrivateTag : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
	enum TiffDataType 
	{
		  kUnknown	// Should never get but...
		, kByte
		, kAscii
		, kShort
		, kLong
		, kRational
		, kSignedByte
		, kUndefined
		, kSignedShort
		, kSignedLong
		, kSignedRational
		, kFloat
		, kDouble
	};

	typedef	unsigned char		TTiffByte;
	typedef	unsigned char		TTiffAscii;
	typedef unsigned short		TTiffShort;
	typedef unsigned long		TTiffLong;
	typedef	float				TTiffRational;
	typedef	char				TTiffSignedByte;
	typedef	unsigned char		TTiffUndefined;
	typedef short				TTiffSignedShort;
	typedef	long				TTiffSignedLong;
	typedef	float				TTiffSignedRational;
	typedef	float				TTiffFloat;
	typedef	double				TTiffDouble;

	// Construction/destruction
public:
	TiffPrivateTag(unsigned short tagId, TiffDataType dataType);
	virtual	~TiffPrivateTag();

	// Methods
public:
	virtual Atil::FormatCodecPropertyInterface* clone () const;
	virtual bool write(struct tiff* pTiff) const;

	bool			isValid() const;
	TiffDataType	dataType() const;
//	void			setDataType(const TiffDataType type);

	unsigned short	tagId() const;
	unsigned long	numItems() const;
	unsigned long	numDataBytes() const;

	// Access to tag data
	//
	// kByte
	bool getValue(TTiffByte* pData, const unsigned long nItems);
	bool setValue(TTiffByte const * pData, const unsigned long nItems);

	// kAscii	(see kByte)
//	bool getValue(TTiffAscii* pData, const unsigned long nItems);
//	bool setValue(TTiffAscii* const pData, const unsigned long nItems);

	// kShort
	bool getValue(TTiffShort* pData, const unsigned long nItems);
	bool setValue(TTiffShort const * pData, const unsigned long nItems);

	// kLong
	bool getValue(TTiffLong* pData, const unsigned long nItems);
	bool setValue(TTiffLong const * pData, const unsigned long nItems);

	// kRational  (see kFloat)
//	bool getValue(TTiffRational* pData, const unsigned long nItems);
//	bool setValue(TTiffRational const * pData, const unsigned long nItems);

	// kSignedByte
	bool getValue(TTiffSignedByte* pData, const unsigned long nItems);
	bool setValue(TTiffSignedByte const * pData, const unsigned long nItems);

	// kUndefined  (see kByte)
//	bool getValue(TTiffUndefined* pData, const unsigned long nItems);
//	bool setValue(TTiffUndefined const * pData, const unsigned long nItems);

	// kSignedShort
	bool getValue(TTiffSignedShort* pData, const unsigned long nItems);
	bool setValue(TTiffSignedShort const * pData, const unsigned long nItems);

	// kSignedLong
	bool getValue(TTiffSignedLong* pData, const unsigned long nItems);
	bool setValue(TTiffSignedLong const * pData, const unsigned long nItems);

	// kSignedRational  (see kFloat)
//	bool getValue(TTiffSignedRational* pData, const unsigned long nItems);
//	bool setValue(TTiffSignedRational const * pData, const unsigned long nItems);

	// kFloat
	bool getValue(TTiffFloat* pData, const unsigned long nItems);
	bool setValue(TTiffFloat const * pData, const unsigned long nItems);

	// kDouble
	bool getValue(TTiffDouble* pData, const unsigned long nItems);
	bool setValue(TTiffDouble const * pData, const unsigned long nItems);


	// Internals
private:
	bool storeValue(void const * pData, const unsigned long numBytes);
	bool retrieveValue(void* pData, const unsigned long numBytes);

	bool			mbValid;
	unsigned short	mTagId;
	TiffDataType	mDataType;
	unsigned long	mNumItems;
	void*			mpTagValue;
};


class TiffSampleRange : public Atil::FormatCodecInclusivePropertySetInterface, public TiffProperty
{
public:
	TiffSampleRange ();
	virtual ~TiffSampleRange ();

	virtual Atil::FormatCodecPropertyInterface* clone () const;

	virtual void getRange (unsigned short& nMinValue, unsigned short& nMaxValue) const;
	virtual void setRange (unsigned short nMinValue, unsigned short nMaxValue);

	bool write ( struct tiff* pTIFF ) const;
};


class TiffPageInformation : public Atil::FormatCodecInclusivePropertySetInterface, public TiffProperty
{
public:
    TiffPageInformation (Atil::StringBuffer* pDoc, Atil::StringBuffer* pPage,
        int nPage, int nPages, double* pX, double* pY );
    virtual ~TiffPageInformation ();

    virtual Atil::FormatCodecPropertyInterface* clone () const;

    // A return of false indicates that the tag containing that value was not 
    // present in the set of tags for the current frame (IFD). The return value will
    // be the default for that member.
    virtual bool getDocumentName ( Atil::StringBuffer& sbName ) const;
    virtual bool getPageName ( Atil::StringBuffer& sbName ) const;
    virtual bool getPageNumber ( int& nNumber ) const;
    virtual bool getPosition ( double& dX, double& dY ) const;


private:
    bool write ( struct tiff* pTIFF ) const;
};

#endif
