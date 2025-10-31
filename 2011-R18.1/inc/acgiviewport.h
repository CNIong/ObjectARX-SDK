#pragma once
//
// (C) Copyright 2005-2007 by Autodesk, Inc. 
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
//

#include "acgienvironment.h"

class AcGiViewportTraits : public AcGiDrawableTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportTraits);
 
    virtual void setBackground(const AcDbObjectId backgroundId) = 0;
    virtual AcDbObjectId        background () const = 0;

    enum DefaultLightingType {
        kOneDistantLight = 0,
        kTwoDistantLights,
        kBackLighting,
    };
    virtual bool isDefaultLightingOn() const = 0;
    virtual void setDefaultLightingOn(bool on) = 0;
    virtual DefaultLightingType defaultLightingType() const = 0;
    virtual void setDefaultLightingType(DefaultLightingType typ) = 0;

    virtual void setAmbientLightColor(const AcCmColor& clr) = 0;
    virtual AcCmColor ambientLightColor() const = 0;

    virtual void setBrightness (double brightness) = 0;
    virtual double brightness() const = 0;

    virtual void setContrast (double contrast) = 0;
    virtual double contrast() const = 0;

    virtual void setRenderEnvironment (const AcDbObjectId renderEnvId) = 0;
    virtual AcDbObjectId renderEnvironment () const = 0;

    virtual void setRenderSettings (const AcDbObjectId renderSettingsId) = 0;
    virtual AcDbObjectId renderSettings () const = 0;
};

/// <summary>
/// Extended viewport interface allowing for tone operator traits.
/// </summary>
///
class AcGiViewportTraits2 : public AcGiViewportTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportTraits2);

    /// <summary>
    /// Sets the tone operator parameters for this viewport.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiToneOperatorParameters object that contains the tone operator
    /// properties of this viewport.
    /// </param>
    virtual void setToneOperatorParameters(const AcGiToneOperatorParameters& params) = 0;

    /// <summary>
    /// Provides access to tone operator parameters for this viewport.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiToneOperatorParameters object that contains the tone operator
    /// properties of this viewport.
    /// </param>
    virtual void toneOperatorParameters(AcGiToneOperatorParameters& params) const = 0;
};
