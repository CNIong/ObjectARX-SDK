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
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif
#ifndef RGBCOLOR_H
namespace Atil { struct RgbColor; }
#endif


// Model::k32BitAlpha -- set if the alpha channel of a rgba image holds valid
//                       alpha information.
//
// Model::kPaletteAlpha -- if this is set then there is an alpha list of values
//                         of at least the number of colors in the palette, but
//                         no more than 256, 8 byte alpha values. Each value 
//                         gives an alpha for the corresponding palette index.
//
// Model::kGrayAlpha -- if this is set then there is an alpha list of 256 8 byte
//                      entries where each entry specifies an alpha value for the
//                      corresponding gray intensity.
//
// Model::kKeyColorList -- if this is set then there is a number of rgb color
//                         triplets or other key color data values where each
//                         specifies an rgb triplet or bit pattern which is to
//                         be made transparent.
//

#ifndef FORMATCODECTRANSPARENCY_H
#define FORMATCODECTRANSPARENCY_H

namespace Atil
{

/// <summary>
/// This is used by <c>ImageFormatCodec</c> instances to return information
/// about specific values that in the returned data, can or should be treated
/// as transparent.
/// </summary>
///
class FormatCodecTransparency : public FormatCodecPropertyInterface
{
public:
    enum Model { k32BitAlpha, kPaletteAlpha, kGrayAlpha, kKeyColorList };

public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecTransparency ();

    /// <summary>
    /// The implementation of the clone method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a pointer to a new object of the same type
    /// initialize to the same values. The caller must "delete" the returned
    /// pointer. 
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;
    
    /// <summary>
    /// Retrieves the type of or model used to represent the transparent values.
    /// </summary>
    ///
    virtual Model getTransparencyModel ( ) const;
    
    virtual int numKeyColors () const;
    virtual int keyColorComponentBits () const;
    virtual bool getKeyColors (UInt8* aTransparentRgbTriplets) const;
    virtual bool getKeyColors (RgbColor* aTransparentColors) const;
    virtual bool getKeyColors (Data16* aKeyColorData) const;
    virtual bool getKeyColors (Data32* aKeyColorData) const;
    virtual bool getKeyColors (Data64* aKeyColorData) const;
    virtual void setKeyColors (int nKeyColors, const UInt8* aTransparentRgbTriplets);
    virtual void setKeyColors (int nKeyColors, const Data16* aKeyColorData);
    virtual void setKeyColors (int nKeyColors, const Data32* aKeyColorData);
    virtual void setKeyColors (int nKeyColors, const Data64* aKeyColorData);


    virtual bool getPaletteAlphas (UInt8* aAlphas) const;
    virtual void setPaletteAlphas (UInt8* aAlphas);

    virtual bool getGrayAlphas (UInt8* aAlphas) const;
    virtual void setGrayAlphas (UInt8* aAlphas);

protected:
	FormatCodecTransparency ( Model transparencyType );
    FormatCodecTransparency ( const FormatCodecTransparency& other );

protected:
    Model mModel;
    int   mnColors;
    int   mnBytes;
    int   mnComponentBits;

    UInt8* maTransparencies;
};

} // end of namespace Atil

#endif
