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
#ifndef IMAGEPIXEL_H
#include "ImagePixel.h"
#endif

#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef  FORMATCODECCOLORPROPERTY_H
#define  FORMATCODECCOLORPROPERTY_H

namespace Atil
{
class FormatCodecColorProperty : public FormatCodecPropertyInterface
{
public:
    enum ColorType { kTransparent, kForeground, kBackground, kCustom };
public:
    FormatCodecColorProperty (ColorType type);
    virtual ~FormatCodecColorProperty ();

    virtual FormatCodecPropertyInterface* clone () const;

    virtual ImagePixel getColor ( ) const;
    virtual ColorType  getType ( ) const;

    virtual bool setColor (ImagePixel color, ColorType type );

protected:
    ImagePixel mColor;
    ColorType mColorType;
};

} // end of namespace Atil
#endif
