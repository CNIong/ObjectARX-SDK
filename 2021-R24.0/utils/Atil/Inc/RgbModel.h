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


#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef DATAMODEL_H
#include "DataModel.h"
#endif
#ifndef COLORMODELINTERFACE_H
#include "ColorModelInterface.h"
#endif

#ifndef RGBMODEL_H
#define RGBMODEL_H

namespace Atil
{
/// <summary>
/// Derived from the basic <c>DataModel</c> class, <c>RgbModel</c> is the base 
/// class for <c>RgbPaletteModel</c>, <c>RgbGrayModel</c>, and <c>BitonalModel</c>.
/// </summary>
///
/// <remarks>
/// This class declares the RGB color space. The RGB color space is a three-dimensional
/// cube where red, green, and blue form the three major axis. In ATIL, each
/// axis has 256 integral values varying from 0 to 255. 
/// </remarks>
///
class RgbModel : public DataModel, public ColorModelInterface
{
public:
    ///<summary> This test the input <c>DataModelAttributes::DataModelType</c> and will return true if is RGB.</summary>
    ///<param name='dmt'> The datamodel type to be test to see if is in the RGB form.</param>
    ///<returns> This returns true of the type is of an RGB form.</returns>
    ///<remarks> This is a convenience as there are multiple RGB form <c>DataModel</c> types.  This
    /// looks for each and will return true for any of them.  Useful as a basket test.</remarks>
    static bool isRgb(DataModelAttributes::DataModelType dmt);

    ///<summary> This will convert the input stream into default <c>RgbModel</c> form.</summary>
    ///<param name="pPipe"> The input stream to be converted.</param>
    ///<returns> This returns the convert stream, or NULL if not successful.</returns>
    static RowProviderInterface* convertToRgba (RowProviderInterface* pPipe);
public:
    /// <summary>
    /// Simple constructor.
    /// </summary>
    ///
    RgbModel ();

    /// <summary>
    /// Construct an RgbModel object given the number of channels it should have.
    /// </summary>
    /// <param name='channels'>an enum value indicating that the data model will not hold a 
    /// valid alpha channel.
    ///</param>
    /// <param name='order'>an enum value indicating that the layout of channels in a pixel.
    /// It must be either kRgba or kBgra. Any other value will cause an exception.
    ///</param>
    ///
    RgbModel (RgbModelAttributes::Channels channels, DataModelAttributes::ChannelOrder order);

	/// <summary>
	/// Construct an RgbModel object specifying bits per pixel used.
	/// </summary>
	/// <param name='channels'>an enum value indicating that the data model will not hold a 
	/// valid alpha channel.
	///</param>
	/// <param name='order'>an enum value indicating that the layout of channels in a pixel.
	/// It must be either kRgba or kBgra. Any other value will cause an exception.
	///</param>
	/// 
	/// <param name="bpp">
	/// A constant enum described in <c>DataModelAttributes</c> that declares
	/// the number of bits used in a pixel.
	/// </param>
	///
	/// <param name="nDataBits">
	/// The number of bits used for a pixel. The number of bits used must be 
	/// less than or equal to the number of bits per pixel as declared in bpp.
	/// </param>
	RgbModel (RgbModelAttributes::Channels channels,  DataModelAttributes::ChannelOrder order, DataModelAttributes::BitsPerPixel bpp, int nDataBits);

    /// <summary>
    /// (Deprecated) Construct an RgbModel object given an integer number of bits.
    /// This value may only be 24 or 32 for 3 or 4 eight bit channels.
    /// </summary>
    ///
    /// <param name='dataBits'>an integer value indicating that the data model will not hold a 
    /// valid alpha channel by specifying a value of 24 bits per pixel or includes an alpha channel
    /// by setting the bits per pixel to 32 (8 bits per channel * 4 channels).
    /// </param>
    ///
    RgbModel (int dataBits);

	/// <summary>
	/// Copy constructor
	/// </summary>
	///
	RgbModel (const RgbModel &model );

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~RgbModel ();

    /// <summary>
    /// The implementation of the clone method used which is the safest way to
    /// make a copy of an existing <c>RgbModel</c> instance.
    /// </summary>
    ///
    /// <returns>
    /// This will return a copy of the instance.
    /// </returns>
    ///
    virtual DataModel* clone () const;

    /// <summary>
    /// This query returns an entry of the DataModelType enum. It will always
    /// return <c>kRgbModel</c>.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the DataModelType enum that is <c>kRgbModel</c>.
    /// </returns>
    ///
    virtual DataModelAttributes::DataModelType dataModelType () const;

    /// <summary>
    /// Query the pixel type of the data represented which is always kRgba.
    /// </summary>
    ///
    /// <returns>
    /// This method returns PixelType::kRgba.
    /// </returns>
    ///
    virtual DataModelAttributes::PixelType pixelType () const;

    /// <summary>
    /// This method test for convertibility to a given <c>ColorModelInterface</c>.
    /// </summary>
    ///
    /// <param name='colorModel'> A constant instance of a another <c>ColorModelInterface</c>
    /// that is to be tested to see if this instance can convert into it.
    /// </param>
    /// 
    /// <returns>
    /// This should return if this class can supply a conversion filter.
    /// </returns>
    ///
    virtual bool canConvertTo (const ColorModelInterface* colorModel) const;

    /// <summary>
    /// This method asks for the conversion. The <c>canConvertTo</c> method will
    /// be called first to confirm that at a conversion is available.
    /// </summary>
    ///
    /// <param name='colorModel'> A constant instance of a another <c>ColorModelInterface</c>
    /// that is to be convert into it.
    /// </param>
    ///
    /// <param name='pConvert'> An instance of a <c>RowProviderInterface</c>
    /// that represents the source of the data to be converted.
    /// </param>
    ///
    /// <returns>
    /// This returns a new filter that has the conversion hooked into it. See the
    /// <c>ImageFilter</c> base class for more information on creating and linking
    /// together filters.
    /// </returns>
    ///
    virtual RowProviderInterface* getModelConversionTo (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    /// <summary>
    /// This method test for convertibility into a given <c>ColorModelInterface</c>.
    /// </summary>
    ///
    /// <param name='colorModel'> A constant instance of a another <c>ColorModelInterface</c>
    /// that is to be tested to see if this instance can convert from it.
    /// </param>
    /// 
    /// <returns>
    /// This should return if this class can supply a conversion filter that will
    /// change the data into this instances color model.
    /// </returns>
    ///
    virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;

    /// <summary>
    /// This method asks for the conversion. The <c>canConvertTo</c> method will
    /// be called first to confirm that at a conversion is available.
    /// </summary>
    ///
    /// <param name='colorModel'> A constant instance of a another <c>ColorModelInterface</c>
    /// that is to be converted from.
    /// </param>
    ///
    /// <param name='pConvert'> An instance of a <c>RowProviderInterface</c>
    /// that represents the source of the data to be converted.
    /// </param>
    ///
    /// <returns>
    /// This returns a new filter that has the conversion hooked into it. See the
    /// <c>ImageFilter</c> base class for more information on creating and linking
    /// together filters.
    /// </returns>
    ///
    virtual RowProviderInterface* getModelConversionFrom (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    /// <summary>
    /// Query the order of channels in the pixel.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the order in the <c>DataModelAttributes</c> enum.
    /// </returns>
    ///
    DataModelAttributes::ChannelOrder channelOrder() const;

    /// <summary>
    /// The equals operator.
    /// </summary>
    ///
    /// <param name= 'dm'>
    /// A const reference to the <c>DataModel</c> to be tested.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two DataModel objects are equivalent.
    /// </returns>
    ///
    /// <remarks>
    /// Each internal ATIL derived <c>DataModel</c> will implement its own operators to 
    /// implement the correct and meaningful comparison.
    /// </remarks>
    ///
    virtual bool operator==(const DataModel& dm) const;

    /// <summary>
    /// The not equals operator.
    /// </summary>
    ///
    /// <param name= 'dm'>
    /// A const reference to the <c>DataModel</c> to be tested.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two DataModel objects are not equivalent.
    /// </returns>
    ///
    /// <remarks>
    /// Each internal ATIL derived <c>DataModel</c> will implement its own operators to 
    /// implement the correct and meaningful comparison.
    /// </remarks>
    ///
    virtual bool operator!=(const DataModel& dm) const;


protected:
    /// <summary>
    /// (Protected) Constructor that allows derived classes to create specialized
    /// implementations that implement sub-types of the RGB space such as a 
    /// gray ramp (a vector through the RGB cube).
    /// </summary>
    ///
    /// <param name="dmt">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the type of the datamodel to be constructed.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    RgbModel (DataModelAttributes::DataModelType dmt,
        DataModelAttributes::BitsPerPixel bpp );

    /// <summary>
    /// (Protected) Constructor that allows derived classes to create specialized
    /// implementations that implement sub-types of the RGB space such as a 
    /// gray ramp (a vector through the RGB cube).
    /// </summary>
    ///
    /// <param name="dmt">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the type of the datamodel to be constructed.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    /// <param name="nBitsUsedPerPixel">
    /// The number of bits used for a pixel. The number of bits used must be 
    /// less than or equal to the number of bits per pixel as declared in bpp.
    /// </param>
    ///
    RgbModel (DataModelAttributes::DataModelType dmt,
        DataModelAttributes::BitsPerPixel bpp, int nBitsUsedPerPixel );

    DataModelAttributes::ChannelOrder mOrder;
};

} //end of namespace

#endif
