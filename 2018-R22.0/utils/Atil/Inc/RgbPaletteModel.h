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

#ifndef RGBMODEL_H
#include "RgbModel.h"
#endif
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef RGBCOLOR_H
#include "RgbColor.h"
#endif
#ifndef ATILEXCEPTION_H
#include "ATILException.h"
#endif
#ifndef RGBPALETTEMODEL_H
#define RGBPALETTEMODEL_H

namespace Atil
{

/// <summary>
/// Represents an eight-bit indexed color space. It is used to construct eight-bit color 
/// images. The DataModel holds an array of colors, called a palette, such that the indexes of the 
/// data refer to the entries in the palette of colors. Each entry in the palette is an instance of 
/// the structure RgbColor. The pixel values in the image represent indexes into the palette array 
/// held by the RgbPaletteModel. 
/// </summary>
///
class RgbPaletteModel : public RgbModel
{
public:
    /// <summary>
    /// Blank palette constructor.
    /// </summary>
    ///
    /// <param name='nPaletteEntries'> The number of entries that will be in the palette.
    /// </param>
    ///
    RgbPaletteModel (int nPaletteEntries = 256);

    /// <summary>
    /// Palette initializing constructor.
    /// </summary>
    ///    
    /// <param name='nEntries'> The number of entries that in the palette.
    /// </param>
    ///
    /// <param name='colors'> A constant point to an array of <c>RgbColor</c> instances
    /// with at least <c>nEntries</c> members. The colors will be used to initialize the palette.
    /// </param>
    ///
    RgbPaletteModel (int nEntries, const RgbColor* colors);

    /// <summary>
    /// Palette initializing constructor.
    /// </summary>
    ///    
    /// <param name='nBitsUsedPerPixel'> The number of bits used by indexes in the image. Setting
    /// this number puts a cap on the number of color in the palette. The number of bits must be
    /// between 2 and 8.
    /// </param>
    ///
    /// <param name='nEntries'> The number of entries that in the palette.
    /// </param>
    ///
    /// <param name='colors'> A constant point to an array of <c>RgbColor</c> instances
    /// with at least <c>nEntries</c> members. The colors will be used to initialize the palette.
    /// </param>
    ///
    RgbPaletteModel (int nBitsUsedPerPixel, int nEntries, const RgbColor* colors);

    /// <summary> Palette initializing constructor.</summary>
    /// <param name='nEntries'> The number of entries that in the palette.</param>
    /// <param name='order'>an enum value indicating that the layout of channels in a pixel.
    /// It must be either kRgba or kBgra. Any other value will cause an exception.
    /// </param>
    /// <param name='colors'> A constant point to an array of <c>RgbColor</c> instances
    /// with at least <c>nEntries</c> members. The colors will be used to initialize the palette.
    /// </param>
    ///
    RgbPaletteModel (int nEntries, DataModelAttributes::ChannelOrder order, const RgbColor* colors);

    /// <summary>
    /// virtual destructor
    /// </summary>
    ///
    virtual ~RgbPaletteModel ();

    /// <summary>
    /// This method creates a full copy of the <c>RgbPaletteModel</c>.
    /// </summary>
    ///
    /// <returns>
    /// This will return an initialized copy of <c>*this</c>.
    /// </returns>
    ///
    virtual DataModel* clone () const;

    /// <summary>
    /// This query returns an entry of the DataModelType enum that indicating
    /// <c>DataModelAttributes::kPalettedRgbModel</c>
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>DataModelAttributes::kPalettedRgbModel</c>.
    /// </returns>
    ///
    virtual DataModelAttributes::DataModelType dataModelType () const;
    
    /// <summary>
    /// Query the pixel type of the data represented by this datamodel.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>DataModelAttributes::kPalettedRgb</c>.
    /// </returns>
    ///
    virtual DataModelAttributes::PixelType pixelType () const;

    /// <summary>
    /// This method test for convertibility to <c>RgbPaletteModel</c>.
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
    /// This method asks for the conversion to <c>RgbPaletteModel</c>. The <c>canConvertTo</c>
    ///  method will be called first to confirm that at a conversion is available.
    /// </summary>
    ///
    /// <param name='colorModel'> A constant instance of a another <c>ColorModelInterface</c>
    /// that is to be convert into it.
    /// </param>
    ///
    /// <param name='pInput'> An instance of a <c>RowProviderInterface</c>
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
    /// <param name='pInput'> An instance of a <c>RowProviderInterface</c>
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
    /// Simply returns the number of valid entries in the palette.
    /// </summary>
    ///
    /// <returns>
    /// The integer number of palette entries. 
    /// </returns>
    virtual int numEntries () const;

    /// <summary>
    /// This method will set the desired entries of the palette to the passed values.
    /// </summary>
    ///
    /// <param name='nStartAt'> The starting index to be set.
    /// </param>
    ///
    /// <param name='numEntries'> The number of entries to be set into the palette.
    /// </param>
    ///
    /// <param name='colors'> A constant pointer to an array of <c>RgbColor</c> instances
    /// with at least <c>nEntries</c> members. The colors will be used to initialize the palette.
    /// </param>
    ///
    /// <exception cref="RgbPaletteModelException">An exception will be thrown
    ///  if an invalid palette index is specified. <see cref="ATILException"/>.
    /// </exception>
    ///
    virtual void setEntries (int startAt, int numEntries, const RgbColor* colors);

    // 
    /// <summary>
    /// This method will copy the colors in the palette to the specified array.
    /// </summary>
    ///
    /// <param name='nStartAt'> The starting index to be set.
    /// </param>
    ///
    /// <param name='numEntries'> The number of entries to be copied from the palette.
    /// </param>
    ///
    /// <param name='colors'> A pointer to an array of <c>RgbColor</c> instances
    /// with at least <c>nEntries</c> members. The colors will be set to those in the palette.
    /// </param>
    ///
    /// <exception cref="RgbPaletteModelException">An exception will be thrown
    ///  if an invalid palette index is specified. <see cref="ATILException"/>.
    /// </exception>
    ///
    virtual void getEntries (int startAt, int numEntries, RgbColor* colors) const;

    /// <summary>
    /// This constant method tests whether the value at the specified index is set 
    /// to transparent where transparent is defined as an alpha value that has been set to zero.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be tested.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the alpha at the index is zero. 
    /// </returns>
    ///
    bool isTransparent (int index) const;


    /// <summary>
    /// This constant method sets the value at the specified index is to transparent where 
    /// transparent is defined as an alpha value that has been set to zero.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be set.
    /// </param>
    ///
    /// <remarks>
    /// This method does modify the alpha of the palette even though the method is 
    /// declared to be const. A contradiction introduced by a flaw in the API.
    /// </remarks>
    ///
    void setTransparent (int index) const;
    
    /// <summary>
    /// This constant method tests whether the value at the specified index is set 
    /// to opaque where transparent is defined as an alpha value that has been set to 255.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be tested.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the alpha at the index is 255. 
    /// </returns>
    ///    
    bool isOpaque (int index) const;

    /// <summary>
    /// This constant method sets the value at the specified index is to opaque where 
    /// opaque is defined as an alpha value that has been set to 255.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be set.
    /// </param>
    ///
    /// <remarks>
    /// This method does modify the alpha of the palette even though the method is 
    /// declared to be const. A contradiction introduced by a flaw in the API.
    /// </remarks>
    ///
    void setOpaque (int index) const;
    
    /// <summary>
    /// This constant method returns the value of alpha at the specified index.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be returned.
    /// </param>
    ///
    /// <returns>
    /// This will return the alpha at the index. 
    /// </returns>
    ///
    Data8 alpha (int index) const;

    /// <summary>
    /// This constant method sets the alpha at the specified index to passed value.
    /// </summary>
    ///
    /// <param name='index'> The index within the range of valid palette entries to be set.
    /// </param>
    ///
    /// <param name='alpha'> The value (0 to 255) to set the alpha to.
    /// </param>
    ///
    /// <remarks>
    /// This method does modify the alpha of the palette even though the method is 
    /// declared to be const. A contradiction introduced by a flaw in the API.
    /// </remarks>
    ///
    void setAlpha (int index, Data8 alpha) const;
    
    /// <summary>
    /// The equality operator.
    /// </summary>
    ///
    /// <param name='rhs'> A constant reference to a <c>RgbPaletteModel</c> to be tested.
    /// </param>
    /// 
    /// <returns>
    /// This will return true if the tested objects are considered equal.
    /// </returns>
    ///
    virtual bool operator==(const DataModel& rhs) const;

    /// <summary>
    /// The inequality operator.
    /// </summary>
    ///
    /// <param name='rhs'> A constant reference to a <c>RgbPaletteModel</c> to be tested.
    /// </param>
    /// 
    /// <returns>
    /// This will return true if the tested objects are considered not equal.
    /// </returns>
    ///
    virtual bool operator!=(const DataModel& rhs) const;

    /// <summary>
    /// This method will return the index of the palette entry color that most closely 
    /// matches the passed in color where the closest is determined by minimum euclidean distance
    /// in the RGB cube.
    /// </summary>
    ///
    /// <param name='color'> A <c>RgbColor</c> instance to be matched.
    /// </param>
    /// 
    /// <returns>
    /// This will return the index of the closest color match in the palette for the argument.
    /// </returns>
    ///
    Atil::UInt8 nearestColorIndex (Atil::RgbColor color ) const;

    /// <summary>
    /// Query the order of channels in the pixel.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the order in the <c>DataModelAttributes</c> enum.
    /// </returns>
    ///
    DataModelAttributes::ChannelOrder channelOrder() const;

protected:
    /// <summary>
    /// (Protected) Constructor that allows derived classes to create specialized
    /// implementations that implement sub-types of the RGB space such as a 
    /// gray ramp (a vector through the RGB cube).
    /// </summary>
    ///
    /// <param name="dm">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the type of the datamodel to be constructed.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    /// <param name='nEntries'> The number of entries that in the palette.
    /// </param>
    ///
    RgbPaletteModel (DataModelAttributes::DataModelType dm,
        DataModelAttributes::BitsPerPixel bpp, int nEntries );

    /// <summary>
    /// (Protected) The palette of colors used by the datamodel.
    /// </summary>
    ///
    mutable RgbColor maPalette[256];

    /// <summary>
    /// (Protected) The number of entries int he palette.
    /// </summary>
    ///
    int mnEntries;
};

/// <summary>
/// A specialization of the <c>ATILException</c> class for use by <c>RgbPaletteModel</c>
/// </summary>
///
class RgbPaletteModelException : public ATILException
{
public:
    /// <summary>
    /// This enum uses it's entries to indicate a general reason for the exception.
    /// </summary>
    ///
    enum ExceptionType { 
        /// <summary> An invalid palette index was used or referenced.
        /// </summary>
        kInvalidPaletteIndex 
    };
public:
    /// <summary>
    /// Constructor for the exception.
    /// </summary>
    ///
    /// <param name='sbMessage'> A message for the developer that may indicate the reason
    /// the exception was thrown. These are untranslated strings not intend for the end-user.
    /// </param>
    ///
    /// <param name='eType'> The enum entry indicating the reason or class of exception.
    /// </param>
    ///
    RgbPaletteModelException (const StringBuffer& sbMessage,
        ExceptionType eType = kInvalidPaletteIndex );

    /// <summary>
    /// Cloning or copy constructor.
    /// </summary>
    ///
    /// <param name='x'> A constant reference to the exception to be copied.
    /// </param>
    ///
    RgbPaletteModelException (const RgbPaletteModelException& x);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~RgbPaletteModelException ();

    /// <summary>
    /// This access method returns the enum entry indicating the reason for the exception.
    /// </summary>
    ///
    /// <returns>
    /// This method returns an entry from the enum of exception types.
    /// </returns>
    ///
    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;
};

} //end of namespace

#endif

