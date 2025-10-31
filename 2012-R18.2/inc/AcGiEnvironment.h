//
// (C) Copyright 2006-2008 by Autodesk, Inc. 
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
// This API extends AcGi to support backgrounds, environmental objects
// and render settings
//

#pragma once

#include "acgi.h"
#include "AcGiLightTraits.h"
#pragma pack (push, 8)

#ifdef ACGIENVIRONMENT_IMPL
#define ACGIENV_IMPEXP __declspec(dllexport)
#else
#define ACGIENV_IMPEXP __declspec(dllimport)
#endif


class AcGiSolidBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables solid background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSolidBackgroundTraits);

    // solid background
    virtual void            setColorSolid           (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSolid              (void) const            = 0;
};

class AcGiGradientBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables gradient background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGradientBackgroundTraits);

    virtual void            setColorTop             (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorTop                (void) const           = 0;
    virtual void            setColorMiddle          (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorMiddle             (void) const           = 0;
    virtual void            setColorBottom          (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorBottom             (void) const           = 0;
    virtual void            setHorizon              (double horizon)       = 0;
    virtual double          horizon                 (void) const           = 0;
    virtual void            setHeight               (double height)        = 0;
    virtual double          height                  (void) const           = 0;
    virtual void            setRotation             (double rotation)      = 0;
    virtual double          rotation                (void) const           = 0;
};

class AcGiImageBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables image background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiImageBackgroundTraits);

    virtual void            setImageFilename        (const ACHAR* filename) = 0;
    virtual const ACHAR *   imageFilename           (void) const           = 0;
    virtual void            setFitToScreen          (bool bFitToScreen)    = 0;
    virtual bool            fitToScreen             (void) const           = 0;
    virtual void            setMaintainAspectRatio  (bool bMaintainAspectRatio) = 0;
    virtual bool            maintainAspectRatio     (void) const           = 0;
    virtual void            setUseTiling            (bool bUseTiling)      = 0;
    virtual bool            useTiling               (void) const           = 0;
    virtual void            setXOffset              (double xOffset)       = 0;
    virtual double          xOffset                 (void) const           = 0;
    virtual void            setYOffset              (double yOffset)       = 0;
    virtual double          yOffset                 (void) const           = 0;
    virtual void            setXScale               (double xScale)        = 0;
    virtual double          xScale                  (void) const           = 0;
    virtual void            setYScale               (double yScale)        = 0;
    virtual double          yScale                  (void) const           = 0;
};

class AcGiGroundPlaneBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables ground plane background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGroundPlaneBackgroundTraits);

    virtual void            setColorSkyZenith       (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSkyZenith          (void) const           = 0;
    virtual void            setColorSkyHorizon      (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSkyHorizon         (void) const           = 0;
    virtual void            setColorUndergroundHorizon  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorUndergroundHorizon     (void) const           = 0;
    virtual void            setColorUndergroundAzimuth  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorUndergroundAzimuth     (void) const           = 0;
    virtual void            setColorGroundPlaneNear (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorGroundPlaneNear    (void) const           = 0;
    virtual void            setColorGroundPlaneFar  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorGroundPlaneFar     (void) const           = 0;
};

/// <summary>
/// This class enables sky background definitions to be elaborated to 
/// AcGi implementations.
/// </summary>
///
class AcGiSkyBackgroundTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSkyBackgroundTraits);

    /// <summary>
    /// Sets the sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties used
    /// by this background.
    /// </param>
    virtual void setSkyParameters(const AcGiSkyParameters& params) = 0;

    /// <summary>
    /// Provides access to sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties used
    /// by this background.
    /// </param>
    virtual void skyParameters(AcGiSkyParameters& params) const = 0;
};

class AcGiMaterialTexture;

class AcGiRenderEnvironmentTraits : public AcGiNonEntityTraits
// 
// This class enables render environment definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiRenderEnvironmentTraits);

    virtual void            setEnable               (const bool bEnable)    = 0;
    virtual bool            enable                  (void) const            = 0;
    virtual void            setIsBackground         (const bool bEnable)    = 0;
    virtual bool            isBackground            (void) const            = 0;
    virtual void            setFogColor             (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor fogColor                (void) const            = 0;
    virtual void            setNearDistance         (const double nearDist) = 0;
    virtual double          nearDistance            (void) const            = 0;
    virtual void            setFarDistance          (const double farDist)  = 0;
    virtual double          farDistance             (void) const            = 0;
    virtual void            setNearPercentage       (const double nearPct)  = 0;
    virtual double          nearPercentage          (void) const            = 0;
    virtual void            setFarPercentage        (const double farPct)   = 0;
    virtual double          farPercentage           (void) const            = 0;
    virtual void            setEnvironmentMap       (const AcGiMaterialTexture * map) = 0;
    virtual AcGiMaterialTexture * environmentMap    (void) const = 0;
};

class AcGiRenderSettingsTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiRenderSettingsTraits);

    virtual void setMaterialEnabled(bool enabled) = 0;
    virtual bool materialEnabled() const = 0;

    virtual void setTextureSampling(bool enabled) = 0;
    virtual bool textureSampling() const = 0;

    virtual void setBackFacesEnabled(bool enabled) = 0;
    virtual bool backFacesEnabled() const = 0;

    virtual void setShadowsEnabled(bool enabled) = 0;
    virtual bool shadowsEnabled() const = 0;

    virtual void setDiagnosticBackgroundEnabled(bool enabled) = 0;
    virtual bool diagnosticBackgroundEnabled() const = 0;

    // Model scale relative to meters. For example, if model is drawn in mm,
    // scaleFactor is 0.001.
    virtual void            setModelScaleFactor     (double scaleFactor)    = 0;
    virtual double          modelScaleFactor        (void) const            = 0;
};

// The available filtering methods (kernels) used to combine samples into
// a pixel color.
//
typedef enum {
    krBox = 0,
    krTriangle,
    krGauss,
    krMitchell,
    krLanczos
} AcGiMrFilter;

// The available methods for computing ray-traced shadows.
// 
typedef enum {
    krSimple = 0,
    krSorted,
    krSegments
} AcGiMrShadowMode;

typedef enum {
    krOff = 0,
    krGrid,
    krPhoton,
    krSamples,
    krBSP
} AcGiMrDiagnosticMode;

typedef enum {
    krObject = 0,
    krWorld,
    krCamera
} AcGiMrDiagnosticGridMode;

typedef enum {
    krDensity = 0,
    krIrradiance
} AcGiMrDiagnosticPhotonMode;

typedef enum {
    krDepth = 0,
    krSize
} AcGiMrDiagnosticBSPMode;

typedef enum {
    krHilbert = 0,
    krSpiral,
    krLeftToRight,
    krRightToLeft,
    krTopToBottom,
    krBottomToTop
} AcGiMrTileOrder;

typedef enum {
    krAutomatic = 0,
    krLogarithmic
} AcGiMrExposureType;

typedef enum {
    krFinalGatherOff = 0,
    krFinalGatherOn,
    krFinalGatherAuto
} AcGiMrFinalGatheringMode;

typedef enum {
    krExportMIOff = 0,
    krExportMIWithRender,
    krExportMIOnly
} AcGiMrExportMIMode;

class AcGiMentalRayRenderSettingsTraits : public AcGiRenderSettingsTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMentalRayRenderSettingsTraits);

    virtual void setSampling(int min, int max) = 0;
    virtual void sampling(int& min, int& max) const = 0;

    virtual void setSamplingFilter(AcGiMrFilter filter, double width, double height) = 0;
    virtual void SamplingFilter(AcGiMrFilter& filter, double& width, double& height) const = 0;

    virtual void setSamplingContrastColor(float r, float g, float b, float a) = 0;
    virtual void samplingContrastColor(float& r, float& g, float& b, float& a) const = 0;

    virtual void setShadowMode(AcGiMrShadowMode mode) = 0;
    virtual AcGiMrShadowMode shadowMode() const = 0;
    
    virtual void setShadowMapEnabled(bool enabled) = 0;
    virtual bool shadowMapEnabled() const = 0;
    
    virtual void setRayTraceEnabled(bool enabled) = 0;
    virtual bool rayTraceEnabled() const = 0;
    
    virtual void setRayTraceDepth(int reflection, int refraction, int sum) = 0;
    virtual void rayTraceDepth(int& reflection, int& refraction, int& sum) const = 0;

    virtual void setGlobalIlluminationEnabled(bool enabled) = 0;
    virtual bool globalIlluminationEnabled() const = 0;
    
    virtual void setGISampleCount(int num) = 0;
    virtual int giSampleCount() const = 0;
    
    virtual void setGISampleRadiusEnabled(bool enabled) = 0;
    virtual bool giSampleRadiusEnabled() const = 0;
    
    virtual void setGISampleRadius(double radius) = 0;
    virtual double giSampleRadius() const = 0;

    virtual void setGIPhotonsPerLight(int num) = 0;
    virtual int giPhotonsPerLight() const = 0;
    
    virtual void setPhotonTraceDepth(int reflection, int refraction, int sum) = 0;
    virtual void photonTraceDepth(int& reflection, int& refraction, int& sum) const = 0;
    
    virtual void setFinalGatheringEnabled(bool enabled) = 0;
    virtual bool finalGatheringEnabled() const = 0;
    
    virtual void setFGRayCount(int num) = 0;
    virtual int fgRayCount() const = 0;

    virtual void setFGRadiusState(bool bMin, bool bMax, bool bPixels) = 0;
    virtual void fgSampleRadiusState(bool& bMin, bool& bMax, bool& bPixels) = 0;
    
    virtual void setFGSampleRadius(double min, double max) = 0;
    virtual void fgSampleRadius(double& min, double& max) const = 0;
    
    virtual void setLightLuminanceScale(double luminance) = 0;
    virtual double lightLuminanceScale() const = 0;
    
    virtual void setDiagnosticMode(AcGiMrDiagnosticMode mode) = 0;
    virtual AcGiMrDiagnosticMode diagnosticMode() const = 0;

    virtual void setDiagnosticGridMode(AcGiMrDiagnosticGridMode mode, float fSize) = 0;
    virtual void diagnosticGridMode(AcGiMrDiagnosticGridMode& mode, float& fSize) const = 0;

    virtual void setDiagnosticPhotonMode(AcGiMrDiagnosticPhotonMode mode) = 0;
    virtual AcGiMrDiagnosticPhotonMode diagnosticPhotonMode() const = 0;
    
    virtual void setDiagnosticBSPMode(AcGiMrDiagnosticBSPMode mode) = 0;
    virtual AcGiMrDiagnosticBSPMode diagnosticBSPMode() const = 0;
    
    virtual void setExportMIEnabled(bool enabled) = 0;
    virtual bool exportMIEnabled() const = 0;
    
    virtual void setExportMIFileName(const ACHAR* miName) = 0;
    virtual const ACHAR* exportMIFileName() const = 0;

    virtual void setTileSize(int size) = 0;
    virtual int tileSize() const = 0;

    virtual void setTileOrder(AcGiMrTileOrder order) = 0;
    virtual AcGiMrTileOrder tileOrder() const = 0;

    virtual void setMemoryLimit(int limit) = 0;
    virtual int memoryLimit() const = 0;

    virtual void setEnergyMultiplier(float fScale) = 0;
    virtual float energyMultiplier() const = 0;

    virtual void setProgressMonitor(void* pMonitor) = 0;
    virtual const void* progressMonitor(void) const = 0;
};

class AcGiMentalRayRenderSettingsTraits2 : public AcGiMentalRayRenderSettingsTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMentalRayRenderSettingsTraits2);

    virtual void setExposureType(AcGiMrExposureType type) = 0;
    virtual AcGiMrExposureType exposureType() const = 0;

    virtual void setFinalGatheringMode(AcGiMrFinalGatheringMode mode) = 0;
    virtual AcGiMrFinalGatheringMode finalGatheringMode() const = 0;

    virtual void setShadowSamplingMultiplier(double multiplier) = 0;
    virtual double shadowSamplingMultiplier() const = 0;
};

class AcGiMentalRayRenderSettingsTraits3 : public AcGiMentalRayRenderSettingsTraits2
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMentalRayRenderSettingsTraits3);

    virtual void setExportMIMode(AcGiMrExportMIMode mode) = 0;
    virtual AcGiMrExportMIMode exportMIMode() const = 0;
};

/// <summary>
/// Container class for all tone operator parameters.
/// </summary>
///
class AcGiToneOperatorParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiToneOperatorParameters);

    AcGiToneOperatorParameters();
    virtual ~AcGiToneOperatorParameters();

    bool operator==(const AcGiToneOperatorParameters& params) const;

    /// <summary>
    /// Indicates whether or not the tone operator is active.
    /// </summary>
    ///
    /// <param name="active">
    /// If true, the tone operator is active.
    /// </param>
    virtual void setIsActive(bool active);

    /// <summary>
    /// Is the tone operator active?
    /// </summary>
    ///
    /// <returns>
    /// True if the tone operator is active.
    /// </returns>
    virtual bool isActive() const;

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setChromaticAdaptation(bool enable);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual bool chromaticAdaptation() const;
    
    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setColorDifferentiation(bool enable);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual bool colorDifferentiation() const;

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setWhiteColor(const AcCmColor& color);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual AcCmColor whiteColor() const;
    
    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setProcessBackground(bool processBG);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual bool processBackground() const;

    /// <summary>
    /// Sets the brightness for the tone operator.
    /// </summary>
    ///
    /// <param name="brightness">
    /// The brightness for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid brightness value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setBrightness(double brightness);

    /// <summary>
    /// The brightness for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The brightness for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double brightness() const;

    /// <summary>
    /// Sets the contrast for the tone operator.
    /// </summary>
    ///
    /// <param name="contrast">
    /// The contrast for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid contrast value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setContrast(double contrast);

    /// <summary>
    /// The contrast for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The contrast for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double contrast() const;

    /// <summary>
    /// Sets the mid tones for the tone operator.
    /// </summary>
    ///
    /// <param name="midTones">
    /// The mid tones for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid midtones value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setMidTones(double midTones);

    /// <summary>
    /// The mid tones for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The mid tones for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double midTones() const;
    
    /// <summary>
    /// The exterior daylight mode.
    /// </summary>
    enum ExteriorDaylightMode {
        /// <summary>
        /// Off.
        /// </summary>
        kDaylightOff = 0,
        /// <summary>
        /// On.
        /// </summary>
        kDaylightOn,
        /// <summary>
        /// Auto - key off of the Sun status.
        /// </summary>
        kDaylightAuto
    };

    /// <summary>
    /// Indicates whether or not exterior daylight is enabled.
    /// </summary>
    ///
    /// <param name="enable">
    /// If true, exterior daylight is enabled.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid exterior daylight mode is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setExteriorDaylight(ExteriorDaylightMode mode);

    /// <summary>
    /// Is exterior daylight enabled?
    /// </summary>
    ///
    /// <returns>
    /// True if exterior daylight is enabled.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual ExteriorDaylightMode exteriorDaylight() const;
    
private:
    bool                    mbIsActive;
    bool                    mbChromaticAdaptation;
    bool                    mbColorDifferentiation;
    AcCmColor               mWhiteColor;
    bool                    mbProcessBackground;
    double                  mBrightness;
    double                  mContrast;
    double                  mMidTones;
    ExteriorDaylightMode    mExteriorDaylight;
};

#pragma pack (pop)
