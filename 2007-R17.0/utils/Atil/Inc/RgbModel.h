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
// Derived from the basic DataMoldel class, RgbModel is the root class for RgbPaletteModel, 
// RgbGrayModel, and BitonalModel. This class declares the RGB color space. 
// The RGB color space is a three-dimensional cube where red, green, and blue form the 
// three major axis. In ATIL, each axis has 256 integral values varying from 0 to 255. 
//
class RgbModel : public DataModel, public ColorModelInterface
{
public:
    enum Channels { k3Channels, k4Channels };
public:
    RgbModel ( );
    // Construct an RgbModel object given
    // <param name='channels'>an enum value indicating that the data model will not hold a 
    // valid alpha channel.</param>
    //
    RgbModel (Channels channels);

    // (Deprecated) Construct an RgbModel object given
    // <param name='dataBits'>an integer value indicating that the data model will not hold a 
    // valid alpha channel by specifying a value of 24 bits per pixel or includes an alpha channel
    // by setting the bits per pixel to 32 (8 bits per channel * 4 channels).</param>
    RgbModel (int dataBits);

    virtual ~RgbModel ();

    virtual DataModel* clone () const;
    virtual DataModelAttributes::DataModelType dataModelType () const;
    virtual DataModelAttributes::PixelType pixelType () const;

    virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionTo (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionFrom (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

protected:
    RgbModel (DataModelAttributes::DataModelType dm,
        DataModelAttributes::BitsPerPixel bpp );
    RgbModel (DataModelAttributes::DataModelType dm,
        DataModelAttributes::BitsPerPixel bpp, int nBitsUsedPerPixel );
};

} //end of namespace
#endif
