//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
// acgiLightTraits.h
//
//   AcRxObject
//     AcGiSubEntityTraits
//       AcGiDrawableTraits
//         AcGiNonEntityTraits
//
//           AcGiLightTraits
//             AcGiStandardLightTraits
//               AcGiPointLightTraits
//               AcGiSpotLightTraits
//               AcGiDistantLightTraits
//     AcGiShadowParameters
//     AcGiLightAttenuation
//
//
// DESCRIPTION:
//
// This API extends AcGi to support light and illumination definition.
// Light entities pass their illumination information along to the graphics
// system and renderer through the AcGiLightTraits interfaces.
//

#pragma once

#include "acgi.h"

#pragma pack (push, 8)


////////////////////////////////////////////////////////////////////////
// class AcGiLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Parent class for interfaces passed to AcDbLight objects in the
/// implementation of setAttributes(). The light first down-casts the
/// traits class to the specific type, specified earlier in the addLight()
/// call. It then sets specific light properties.
///
/// This class derives (indirectly) from AcGiDrawableTraits, as that is what
/// is passed into AcGiDrawable::setAttributes().
///
/// Lights on frozen layers will not be processed; their light will not
/// illuminate the model.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class should not rely on any
/// default values.
/// </remarks>
///
class AcGiLightTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLightTraits);

    /// <summary>
    /// Turns the light on or off in the viewport or render. If the light
    /// is off, the other properties here may simply be ignored. However,
    /// lights that are turned off may still "draw" graphics for display
    /// in the viewport.
    ///
    /// Lights on frozen layers are not processed at all, so your light
    /// object does not have to check that condition.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, the light is "turned on".
    /// </param>
    virtual void setOn(bool on) = 0;

    /// <summary>
    /// Light on/off state.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is on.
    /// </returns>
    virtual bool isOn() const = 0;
};

/// <summary>
/// Container class for all shadow-related light properties.
/// </summary>
///
class AcGiShadowParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiShadowParameters);

    AcGiShadowParameters();
    virtual ~AcGiShadowParameters();

    bool operator==(const AcGiShadowParameters& params) const;

    /// <summary>
    /// Turns shadow casting from this light on and off.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, this light casts shadows.
    /// </param>
    virtual void setShadowsOn(bool on);

    /// <summary>
    /// Does the light cast shadows?
    /// </summary>
    ///
    /// <returns>
    /// True if the light casts shadows.
    /// </returns>
    virtual bool shadowsOn() const;

    /// <summary>
    /// The method used to calculate shadows.
    /// </summary>
    enum ShadowType {
        /// <summary>
        /// Shadows are calculated using a ray-trace algorithm.
        /// </summary>
        kShadowsRayTraced = 0,
        /// <summary>
        /// Shadow maps are created for each light.
        /// </summary>
        kShadowMaps
    };

    /// <summary>
    /// Sets the method used to calculate shadows cast by this light.
    /// </summary>
    ///
    /// <param name="typ">
    /// One of: kShadowsRayTraced, kShadowMaps
    /// </param>
    ///
    /// <remarks>
    /// When shadows are ray-traced, shadow map size and softness parameters
    /// are ignored.
    /// </remarks>
    virtual void setShadowType(ShadowType typ);

    /// <summary>
    /// The method used to calculate shadows cast by this light.
    /// </summary>
    ///
    /// <returns>
    /// One of: kShadowsRayTraced, kShadowMaps
    /// </returns>
    virtual ShadowType shadowType() const;

    /// <summary>
    /// Sets the shadow map size, in pixels. Larger numbers produce more 
    /// accurate shadows, but require more memory and take longer to render.
    /// </summary>
    ///
    /// <param name="sz">
    /// Valid values are 64, 128, 256, 512, 1024, 2048, and 4096.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid size is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual bool setShadowMapSize(Adesk::UInt16 sz);

    /// <summary>
    /// The size of the shadow map, in pixels.
    /// </summary>
    ///
    /// <returns>
    /// The size of the shadow map, in pixels.
    /// Should be one of: 64, 128, 256, 512, 1024, 2048, or 4096.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual Adesk::UInt16 shadowMapSize() const;

    /// <summary>
    /// Sets the softness (or fuzziness) of shadow-mapped shadows. The value
    /// represents the number of pixels at the edge of the shadow that are 
    /// blended into the underlying image.
    /// </summary>
    ///
    /// <param name="soft">
    /// The value can range from 1 to 10.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid softness value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual bool setShadowMapSoftness(Adesk::UInt8 soft);

    /// <summary>
    /// The softness (or fuzziness) of the edge of the shadow. The value
    /// represents the number of pixels at the edge of the shadow that are
    /// blended into the underlying image.
    /// </summary>
    ///
    /// <returns>
    /// The number of pixels at the edge of the shadow to blend.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual Adesk::UInt8 shadowMapSoftness() const;

private:
    bool            mShadowsOn;
    ShadowType      mShadowType;
    Adesk::UInt16   mShadowMapSize;
    Adesk::UInt8    mShadowMapSoftness;
};

/// <summary>
/// Container class for light attenuation parameters.
/// </summary>
///
class AcGiLightAttenuation : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLightAttenuation);

    AcGiLightAttenuation();
    virtual ~AcGiLightAttenuation();

    bool operator==(const AcGiLightAttenuation& atten) const;

    /// <summary>
    /// The type of attenuation, or decay, for this light. This only applies
    /// to point and spot lights. Distant lights always have no attenuation.
    /// </summary>
    enum AttenuationType {
        /// <summary>
        /// No attenuation; emitted light has the same brightness (intensity)
        /// regardless of the distance to the source.
        /// </summary>
        kNone = 0,
        /// <summary>
        /// Sets attenuation to be the inverse of the linear distance from the
        /// light. 
        /// </summary>
        kInverseLinear,
        /// <summary>
        /// Sets attenuation to be the inverse of the square of the distance
        /// from the light. 
        /// </summary>
        kInverseSquare
    };

    /// <summary>
    /// Sets the attenuation type for the light.
    /// </summary>
    ///
    /// <param name="typ">
    /// One of: kNone, kInverseLinear, kInverseSquare
    /// </param>
    virtual void setAttenuationType(AttenuationType typ);

    /// <summary>
    /// The attenuation type for the light.
    /// </summary>
    ///
    /// <returns>
    /// One of: kNone, kInverseLinear, kInverseSquare
    /// </returns>
    virtual AttenuationType attenuationType() const;

    /// <summary>
    /// Turns on and off application of any attenuation limits.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, both start and end limits will be used.
    /// </param>
    virtual void setUseLimits(bool on);

    /// <summary>
    /// Are the start and end limits used by this light?
    /// </summary>
    ///
    /// <returns>
    /// True if start and end attenuation limits are used.
    /// </returns>
    virtual bool useLimits() const;

    /// <summary>
    /// Sets the distances (a range) from the light source where emitted light
    /// affects the model.
    /// </summary>
    ///
    /// <param name="startlim">
    /// The distance from the light source where light begins to affect the
    /// model; objects closer than this are not affected by the light.
    /// </param>
    /// <param name="endlim">
    /// The distance from the light source beyond which the light has no affect.
    /// </param>
    ///
    /// <remarks>
    /// Start limit must be less than end limit, and both numbers must
    /// greater than or equal to zero.
    /// </remarks>
    virtual void setLimits(double startlim, double endlim);

    /// <summary>
    /// The distance from the light source where light begins to affect the
    /// model; objects closer than this are not affected by the light.
    /// </summary>
    ///
    /// <returns>
    /// A distance.
    /// </returns>
    virtual double startLimit() const;

    /// <summary>
    /// The distance from the light source beyond which the light has no affect.
    /// </summary>
    ///
    /// <returns>
    /// A distance.
    /// </returns>
    virtual double endLimit() const;

private:
    AttenuationType mAttenType;
    bool            mUseAttenLimits;
    double          mAttenStartLimit;
    double          mAttenEndLimit;
};

/// <summary>
/// This intermediate class represents a standard, or non-photometric light.
/// It defines properties common to all non-photometric lights.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
///
class AcGiStandardLightTraits : public AcGiLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiStandardLightTraits);

    /// <summary>
    /// Sets the intensity of the light. Intensity must be greater than or equal
    /// to zero. A value of 0.0 turns the light off.
    /// </summary>
    ///
    /// <param name="inten">
    /// The intensity, or brightness, of the light. A value of 0.0 effectively
    /// turns the light off.
    /// </param>
    virtual void setIntensity(double inten) = 0;

    /// <summary>
    /// The intensity of the light.
    /// </summary>
    ///
    /// <returns>
    /// Light intensity. The value will always be greater than or equal to zero.
    /// </returns>
    virtual double intensity() const = 0;

    /// <summary>
    /// Sets the color of the light.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the emitted light. AcCmColor supports all color models
    /// within AutoCAD, including color book colors.
    /// </param>
    virtual void setLightColor(const AcCmColor& color) = 0;

    /// <summary>
    /// The color of the light.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of emitted light.
    /// </returns>
    virtual AcCmColor lightColor() const = 0;

    /// <summary>
    /// Sets the shadow parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// The AcGiShadowParameters object that defines the way shadows are cast from this light.
    /// </param>
    virtual void setShadowParameters(const AcGiShadowParameters& params) = 0;

    /// <summary>
    /// Provides access to shadow parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiShadowParameters object that will contain the current shadow 
    /// properties of this light.
    /// </param>
    virtual void shadowParameters(AcGiShadowParameters& params) const = 0;
};

/// <summary>
/// This class represents a point light source, whose light is emitted in all
/// directions.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiPointLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiPointLightTraits);

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// The position of the light source.
    /// </param>
    virtual void setPosition(const AcGePoint3d& pos) = 0;

    /// <summary>
    /// The position of the light source, in the coordinate space of the
    /// current context.
    /// </summary>
    ///
    /// <returns>
    /// The position as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d position() const = 0;

    /// <summary>
    /// Provides access to attenuation parameters for this light.
    /// </summary>
    ///
    /// <param name="atten">
    /// An AcGiLightAttenuation object that will contain the current attenuation
    /// parameters of this light. 
    /// </param>
    virtual void lightAttenuation(AcGiLightAttenuation& atten) const = 0;

    /// <summary>
    /// Sets the attenuation parameters of this point light.
    /// </summary>
    ///
    /// <param name="atten">
    /// The AcGiLightAttenuation object that defines the way light attenuates from this light.
    /// </param>
    virtual void setAttenuation(const AcGiLightAttenuation& atten) = 0;
};

/// <summary>
/// This class represents a spot light source, whose light is emitted in a
/// specific direction, and has an associated "light cone".
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiSpotLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSpotLightTraits);

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// The position of the light source.
    /// </param>
    virtual void setPosition(const AcGePoint3d& pos) = 0;

    /// <summary>
    /// The position of the light source, in the coordinate space of the
    /// current context.
    /// </summary>
    ///
    /// <returns>
    /// The position as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d position() const = 0;

    /// <summary>
    /// Sets the location of the target point for a spot light. This, in
    /// combination with the position, determine the direction that the spot
    /// light is "pointing". The coordinate space for this point is defined by
    /// the current context.
    /// </summary>
    ///
    /// <param name="loc">
    /// Location (point) of the spot light's target. It should not be exactly
    /// the same as the position.
    /// </param>
    virtual void setTargetLocation(const AcGePoint3d& loc) = 0;

    /// <summary>
    /// The location (position) towards which the spot light is pointing, in 
    /// the coordinate space of the current context.
    /// </summary>
    ///
    /// <returns>
    /// The location as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d targetLocation() const = 0;

    /// <summary>
    /// Sets the hotspot and falloff angles.
    ///
    /// The region between the hotspot and falloff angles is sometimes 
    /// referred to as the rapid decay area.
    ///
    /// The greater the difference between the hotspot and falloff angles,
    /// the softer the edge of the light beam. If the hotspot and falloff 
    /// angles are equal, the edge of the light beam is sharp. Both values
    /// can range from 0 to 160 degrees. You cannot set the hotspot angle
    /// to be greater than the falloff angle.
    /// </summary>
    ///
    /// <param name="hotspot">
    /// The hotspot cone angle, in radians. Defines the brightest part of the
    /// spot light beam. Must be smaller than or equal to the falloff.
    /// </param>
    /// <param name="falloff">
    /// The falloff cone angle, in radians. Defines the full cone of light. This
    /// is also known as the field angle. Must be larger than or equal to the
    /// hotspot.
    /// </param>
    ///
    /// <returns>
    /// Returns true if valid angles are passed in.
    /// </returns>
    virtual bool setHotspotAndFalloff(double hotspot, double falloff) = 0;

    /// <summary>
    /// The hotspot angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The hotspot angle, in radians.
    /// </returns>
    virtual double hotspot() const = 0;

    /// <summary>
    /// The falloff angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The falloff angle, in radians.
    /// </returns>
    virtual double falloff() const = 0;

    /// <summary>
    /// Provides access to attenuation parameters for this light.
    /// </summary>
    ///
    /// <param name="atten">
    /// An AcGiLightAttenuation object that will contain the current attenuation
    /// parameters of this light. 
    /// </param>
    virtual void lightAttenuation(AcGiLightAttenuation& atten) const = 0;

    /// <summary>
    /// Sets the attenuation parameters of this spot light.
    /// </summary>
    ///
    /// <param name="atten">
    /// The AcGiLightAttenuation object that defines the way light attenuates from this light.
    /// </param>
    virtual void setAttenuation(const AcGiLightAttenuation& atten) = 0;
};

/// <summary>
/// This class represents a distant light source, whose light is emitted in
/// parallel rays, with an infinite distance between the light source and
/// the model.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiDistantLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiDistantLightTraits);

    /// <summary>
    /// Sets the direction the light rays travel in. This vector is in the
    /// direction of the light rays (from light to model).
    /// </summary>
    ///
    /// <param name="vec">
    /// The vector for the light rays.
    /// </param>
    ///
    /// <remarks>
    /// This same interface is used for the sun; all of the other parameters
    /// used to set the location of the sun, such as latitude, longitude, date,
    /// and time, boil down to a vector, which is sent to the graphics system
    /// through this method.
    /// </remarks>
    virtual void setLightDirection(const AcGeVector3d& vec) = 0;

    /// <summary>
    /// The direction (vector) that the light rays travel in.
    /// </summary>
    ///
    /// <returns>
    /// The direction, as a vector; the positive direction of this vector is
    /// from light to model.
    /// </returns>
    virtual AcGeVector3d lightDirection() const = 0;

    /// <summary>
    /// Tells the system to render this distant light as sunlight. Some
    /// rendering systems use special algorithms to render sunlight, as its
    /// intensity is so high.
    /// </summary>
    ///
    /// <param name="isSunlight">
    /// If true, this distant light may be rendered as sunlight.
    /// </param>
    virtual void setIsSunlight(bool isSunlight) = 0;

    /// <summary>
    /// Does this distant light represent sunlight?
    /// </summary>
    ///
    /// <returns>
    /// True if the light will be rendered as sunlight.
    /// </returns>
    virtual bool isSunlight() const = 0;
};

#pragma pack (pop)
