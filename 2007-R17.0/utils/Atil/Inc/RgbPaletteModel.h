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
#ifndef  RGBPALETTEMODEL_H
#define  RGBPALETTEMODEL_H

namespace Atil
{

// Represents an eight-bit indexed color space. It is used to construct eight-bit color 
// images. The DataModel holds an array of colors, called a palette, such that the indexes of the 
// data refer to the entries in the palette of colors. Each entry in the palette is an instance of 
// the structure RgbColor. 
// The pixel values in the image represent indexes into the palette array held by the RgbPaletteModel. 
//
class RgbPaletteModel : public RgbModel
{
public:
    RgbPaletteModel (int nPaletteEntries = 256);
    RgbPaletteModel (int nEntries, const RgbColor* colors);
    RgbPaletteModel (int nBitsUsedPerPixel, int nEntries, const RgbColor* colors);

    virtual ~RgbPaletteModel ();

    virtual DataModel* clone () const;
    virtual DataModelAttributes::DataModelType dataModelType () const;
    virtual DataModelAttributes::PixelType pixelType () const;

    virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionTo (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionFrom (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    // Returns the number of colors in the palette.
    virtual int numEntries () const;

    // Sets the colors in the palette to those specified.
    virtual void setEntries (int startAt, int numEntries, const RgbColor* colors);

    // Copies the colors in the palette to the specified array.
    virtual void getEntries (int startAt, int numEntries, RgbColor* colors) const;

    // Tests whether the value at the specified index is set to transparent.
    bool  isTransparent (int index) const;

    // Make the value at the specified index transparent.
    void  setTransparent (int index) const;
    
    // Tests whether the value at the specified index is set to opaque (non-tranparent).
    bool  isOpaque (int index) const;

    // Make the value at the specified index opaque (non-transparent).
    void  setOpaque (int index) const;
    
    // Returns the the alpha value of the element at the specified index.
    Data8 alpha (int index) const;

    // Sets the alpha value of the element at the specified index.
    void  setAlpha (int index, Data8 alpha) const;
    
    virtual bool operator==(const DataModel& rhs) const;
    virtual bool operator!=(const DataModel& rhs) const;

    Atil::UInt8 nearestColorIndex (Atil::RgbColor color ) const;

protected:
    RgbPaletteModel (DataModelAttributes::DataModelType dm,
        DataModelAttributes::BitsPerPixel bpp, int nEntries );

    mutable RgbColor maPalette[256];
    // From 1 through 256.
    int mnEntries;
};


class RgbPaletteModelException : public ATILException
{
public:
    enum ExceptionType { kInvalidPaletteIndex };
public:
    RgbPaletteModelException (const StringBuffer& sbMessage,
        ExceptionType eType = kInvalidPaletteIndex );
    RgbPaletteModelException (const RgbPaletteModelException& x);
    virtual ~RgbPaletteModelException ();

    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;
};

} //end of namespace
#endif

//#ifndef RGBCOLOR_H
//#include <RgbColor.h>
//#endif
