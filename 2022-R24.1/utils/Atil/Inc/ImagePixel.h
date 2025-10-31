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


#ifndef IMAGEPIXEL_H
#define IMAGEPIXEL_H

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef RGBCOLOR_H
#include "RgbColor.h"
#endif
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef DATAMODEL_H
#include "DataModel.h"
#endif

namespace Atil
{
/// <summary>
/// This struct can hold a pixel of any "type" that is supported within ATIL. As such
/// it is at least 64 bits wide. It is used to pass around pixel values where the code 
/// can be applied to any type of image. 
/// </summary>
///
struct ImagePixel 
{
    /// <summary>
    /// A union of all pixel bit sizes and the data model types.
    /// </summary>
    ///
    union {
        /// <summary> union member </summary>
        Data8  data1;
        /// <summary> union member </summary>
        Data8  data8;
        /// <summary> union member </summary>
        Data16 data16;
        /// <summary> union member </summary>
        Data32 data32;
        /// <summary> union member </summary>
        Data64 data64;
        /// <summary> union member </summary>
        Data128 data128;
        /// <summary> union member </summary>
        Data8  bitonal;
        /// <summary> union member </summary>
        Data8  gray;
        /// <summary> union member </summary>
        Data8  index;
        /// <summary> union member </summary>
        Data32 rgba;
        /// <summary> union member </summary>
        float  gray32f;
    } value;

    /// <summary>
    /// The "type" of the pixel as declared by <c>DataModelAttributes::PixelType</c> 
    /// <see cref="DataModelAttributes"/>
    /// </summary>
    ///
    DataModelAttributes::PixelType type;

    /// <summary>
    /// The constructor which set the <c>DataModelAttributes::PixelType</c> of 
    /// the pixel that will be set into the <c>value</c>.
    /// </summary>
    ///
    /// <param name='pixTpe'>The <c>DataModelAttributes::PixelType</c> of data that 
    /// the <c>ImagePixel</c> will hold.
    /// </param>
    ///
    ImagePixel (DataModelAttributes::PixelType pixTpe = DataModelAttributes::kData1);

    /// <summary>
    /// This method will set the <c>value</c> union to zero. Zero is one value that
    /// is always valid for each pixel type and so makes a safe initializer.
    /// </summary>
    ///
    /// <returns>
    /// A const reference to <c>*this</c>.
    /// </returns>
    ///
    const ImagePixel& setToZero ();

    /// <summary>
    /// The equals operator will test the <c>DataModelAttributes::PixelType</c> and the
    /// <c>value</c> union and return true if they match.
    /// </summary>
    ///
    /// <param name= 'rhs'>
    /// A const reference to the pixel value to be compared.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the objects are equivalent.
    /// </returns>
    ///
    bool operator==(const ImagePixel& rhs) const;

    /// <summary>
    /// The equals operator will test the <c>DataModelAttributes::PixelType</c> and the
    /// <c>value</c> union and return false if they match.
    /// </summary>
    ///
    /// <param name= 'rhs'>
    /// A const reference to the pixel value to be compared.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the objects are equivalent.
    /// </returns>
    ///
    bool operator!=(const ImagePixel& rhs) const;
};

} // end of namespace Atil

#endif
