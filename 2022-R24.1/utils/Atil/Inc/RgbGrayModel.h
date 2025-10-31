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
#ifndef RGBMODEL_H
#include "RgbModel.h"
#endif
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif

#ifndef RGBGRAYMODEL_H
#define RGBGRAYMODEL_H

namespace Atil
{
/// <summary>
/// Derived from RgbModel, RgbGrayModel is the base class of BitonalModel. 
/// The data in RgbGrayModel is always 8 bits of intensity as a vector from (0,0,0) 
/// to (255,255,255) in the RGB color cube. 
///
/// As with all DataModel-derived types, this data model is the basis for images. 
/// This class is used for 8-bit grayscale images. 
/// </summary>
///     
class RgbGrayModel : public RgbModel
{
public:
    /// <summary>
    /// The class constructor will create an instance of the class.
    /// </summary>
    ///
    RgbGrayModel ();

    /// <summary>
    /// (Protected) This constructor is made available for usage by classes that
    /// derive from this class.
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
    RgbGrayModel (DataModelAttributes::DataModelType dm, DataModelAttributes::BitsPerPixel bpp);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~RgbGrayModel ();

    /// <summary>
    /// The implementation of the clone method used which is the safest way to
    /// make a copy of an existing <c>RgbGrayModel</c> instance.
    /// </summary>
    ///
    /// <returns>
    /// This will return a copy of the instance.
    /// </returns>
    ///
    virtual DataModel* clone () const;

    /// <summary>
    /// This query returns an entry of the DataModelType enum. It will always
    /// return <c>kRgbGrayModel</c>.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the DataModelType enum that is <c>kRgbGrayModel</c>.
    /// </returns>
    ///
    virtual DataModelAttributes::DataModelType dataModelType () const;

    /// <summary>
    /// Query the pixel type of the data represented which is always kGray.
    /// </summary>
    ///
    /// <returns>
    /// This method returns PixelType::kGray.
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
    /// This constant method tests whether the value at the specified intensity is set 
    /// to transparent where transparent is defined as an alpha value that has been set to zero.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be tested.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the alpha at the intensity is zero. 
    /// </returns>
    ///
    bool isTransparent ( Data8 intensity ) const;
    
    /// <summary>
    /// This constant method sets the value at the specified intensity is to transparent where 
    /// transparent is defined as an alpha value that has been set to zero.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be set.
    /// </param>
    ///
    /// <remarks>
    /// This method does modify the alpha of the palette even though the method is 
    /// declared to be const. A contradiction introduced by a flaw in the API.
    /// </remarks>
    ///
    void setTransparent ( Data8 intensity ) const;

    /// <summary>
    /// This constant method tests whether the value at the specified intensity is set 
    /// to opaque where transparent is defined as an alpha value that has been set to 255.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be tested.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the alpha at the intensity is 255. 
    /// </returns>
    ///    
    bool isOpaque (Data8 intensity) const;

    /// <summary>
    /// This constant method sets the value at the specified intensity is to opaque where 
    /// opaque is defined as an alpha value that has been set to 255.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be set.
    /// </param>
    ///
    /// <remarks>
    /// This method does modify the alpha of the palette even though the method is 
    /// declared to be const. A contradiction introduced by a flaw in the API.
    /// </remarks>
    ///
    void setOpaque (Data8 intensity) const;

    /// <summary>
    /// This constant method returns the value of alpha at the specified intensity.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be returned.
    /// </param>
    ///
    /// <returns>
    /// This will return the alpha at the intensity. 
    /// </returns>
    ///
    Data8 alpha ( Data8 intensity ) const;

    /// <summary>
    /// This constant method sets the alpha at the specified intensity to passed value.
    /// </summary>
    ///
    /// <param name='intensity'> The intensity within the range of valid palette entries to be set.
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
    void setAlpha ( Data8 intensity, Data8 alpha ) const;

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
    /// (Protected) The array of alphas used by the datamodel.
    /// </summary>
    ///
    mutable Data8 maAlphas[256];
};

} //end of namespace

#endif
