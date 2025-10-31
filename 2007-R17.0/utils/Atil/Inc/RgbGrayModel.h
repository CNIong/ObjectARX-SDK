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

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef RGBMODEL_H
#include "RgbModel.h"
#endif
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif

#ifndef  RGBGRAYMODEL_H
#define  RGBGRAYMODEL_H

namespace Atil
{
// Derived from RgbModel, RgbGrayModel is the base class of BitonalModel. 
// The data in RgbGrayModel is always 8 bits of intensity as a vector from (0,0,0) 
// to (255,255,255) in the RGB color cube. 
//
// As with all DataModel-derived types, this data model is the basis for images. 
// This class is used for 8-bit grayscale images. 
//
class RgbGrayModel : public RgbModel
{
public:
    RgbGrayModel ();
    RgbGrayModel (DataModelAttributes::DataModelType dm, DataModelAttributes::BitsPerPixel bpp);
    virtual ~RgbGrayModel ();

    virtual DataModel* clone () const;

    virtual DataModelAttributes::DataModelType dataModelType () const;
    virtual DataModelAttributes::PixelType pixelType () const;

    virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionTo (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionFrom (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    // Tests whether the value at the index specified by the intensity argument is set to transparent.
    bool  isTransparent ( Data8 intensity ) const;
    
    // Sets the value at the index specified by the intensity argument to transparent.
    void  setTransparent ( Data8 intensity ) const;

    // Tests whether the value at the index specified by the intensity argument
    // is set to opaque (non-tranparent).
    bool  isOpaque (Data8 intensity) const;

    // Sets the value at the index specified by the intensity argument to opaque (non-tranparent).
    void  setOpaque (Data8 intensity) const;

    // Returns the value of the alpha at the index specified by the intensity argument.
    Data8 alpha ( Data8 intensity ) const;

    // Sets the alpha associated with the intensity.
    void  setAlpha ( Data8 intensity, Data8 alpha ) const;

protected:
    // 256 transparency (alpha) values
    mutable Data8 maAlphas[256];
};

} //end of namespace
#endif
