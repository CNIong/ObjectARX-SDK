//
// (C) Copyright 1997-2002 by Autodesk, Inc. 
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

#ifndef _AVLIB_H
#define _AVLIB_H

#include "adslib.h"
#include "adscodes.h" 

#if defined(__cplusplus)
extern "C" {
#endif

#include "averror.h"
#include "adsmigr.h"
#include "acutads.h"

#define AvLibVersion 0.03  // Updated from 0.02

typedef int AvBoolean;

/* Color System type. */
typedef enum {
    AvRGB = 0,
    AvHLS
} AvColorSystem;

/*
 * AvColor  RGB or HLS colors
 */
typedef struct {
    AvColorSystem system;
    ads_point     color;
} AvColor;


/*******************************************************************
 *  The av_light() command
 *******************************************************************/

typedef enum {
    AvLightIntensity    = 0x000001,
    AvLightColor        = 0x000002,
    AvLightName         = 0x000004,
    AvLightFrom         = 0x000008,
    AvLightTo           = 0x000010,
    AvLightShadowmap    = 0x000020,
    AvLightHotspot      = 0x000040,
    AvLightFalloff      = 0x000080,
    AvLightShadowsoft   = 0x000100,
    AvLightShadowObject = 0x000200,
    AvLightShadows      = 0x000400,
    AvLightMonth        = 0x000800,
    AvLightDay          = 0x001000,
    AvLightHour         = 0x002000,
    AvLightMinute       = 0x004000,
    AvLightDaylight     = 0x008000,
    AvLightLatitude     = 0x010000,
    AvLightLongitude    = 0x020000,
    AvLightTimezone     = 0x040000,
    AvLightAttenuation  = 0x080000,
    AvLightNewName      = 0x100000,
    AvLightNorthUCS     = 0x200000,
    AvLightNRotation    = 0x400000,
    AvLightTypeFlag     = 0x800000
} AvLightFlags;

typedef enum {
    AvLightNewDistant = 0,
    AvLightNewPoint,
    AvLightNewSpot,
    AvLightAmbient,
    AvLightAmbientList,
    AvLightModify,
    AvLightDelete,
    AvLightRename,
    AvLightNorthLocator,
    AvLightNorthLocatorList,
    AvLightList,
    AvLightListAll,
    AvLightUI
} AvLightMode;

typedef enum {
    AvAttenuationNone,
    AvAttenuationInverse,
    AvAttenuationInverseSquare
} AvAttenType;

typedef enum {
    AvLightDistant,
    AvLightPoint,
    AvLightSpot
} AvLightType;

typedef struct {
    AvLightMode    mode;
    double         intensity;
    AvColor        color;
    char          *name;
    ads_point      from;
    ads_point      to;
    int            shadowmapSize;
    double         hotspot;
    double         falloff;
    double         shadowSoftness;
    AvBoolean      shadows;
    ads_name       shadowObjects;
    int            month;
    int            day;
    int            hour;
    int            minute;
    AvBoolean      daylight;
    double         latitude;
    double         longitude;
    int            timezone;
    AvAttenType    attenuation;
    char          *newName;
    char          *northUCS;
    double         northRotation;
    AvLightType    type;
    struct resbuf *stringList;
    unsigned long  flags;
} AvLightParam;

/*******************************************************************
 *  The av_rmat() command
 *******************************************************************/

typedef enum {
    AvMapName   = 0x01,
    AvMapValue  = 0x02,
    AvMapRepeat = 0x04,
    AvMapScale  = 0x08,
    AvMapOffset = 0x10,
    AvMapAngle  = 0x20,
    AvMapStyle  = 0x40          // Added for AVLIB 0.02 
} AvRmatMapFlags;

typedef enum {
    AvTileTile = 0,
    AvTileCrop,
    AvTileDefault
} AvTileType;

typedef struct {
    char         *name;
    double        value;
    AvTileType    tile;
    ads_point     scale;
    ads_point     offset;
    double        angle;
    int           mappingFlags; // Added for AVLIB 0.02 
    unsigned long flags;
} AvRmatMap;

typedef enum {
    AvStandardColor        = 0x01,
    AvStandardColorWeight  = 0x02,
    AvStandardPatternMap   = 0x04,
    AvStandardAmbient      = 0x08,
    AvStandardAmbWeight    = 0x10,
    AvStandardTransparency = 0x20,
    AvStandardOpacityMap   = 0x40,
    AvStandardRefraction   = 0x80
} AvRmatStandardFlags;

/* structure of the standard material type description. */
typedef struct {
    AvColor       color;
    double        colorWeight;
    AvRmatMap     patternMap;
    AvColor       ambient;
    double        ambWeight;
    double        transparency;
    AvRmatMap     opacityMap;
    double        refraction;
    unsigned long flags;
} AvRmatStandard;

typedef enum {
    AvMarbleStoneColor = 0x01,
    AvMarbleVeinColor  = 0x02,
    AvMarbleTurbulence = 0x04,
    AvMarbleSharpness  = 0x08,
    AvMarbleScale      = 0x10
} AvRmatMarbleFlags;

/* structure of the marble material type description. */
typedef struct {
    AvColor       stoneColor;
    AvColor       veinColor;
    int           turbulence;
    double        sharpness;
    double        scale;
    unsigned long flags;
} AvRmatMarble;

typedef enum {
    AvGraniteColor1    = 0x001,
    AvGraniteAmount1   = 0x002,
    AvGraniteColor2    = 0x004,
    AvGraniteAmount2   = 0x008,
    AvGraniteColor3    = 0x010,
    AvGraniteAmount3   = 0x020,
    AvGraniteColor4    = 0x040,
    AvGraniteAmount4   = 0x080,
    AvGraniteSharpness = 0x100,
    AvGraniteScale     = 0x200
} AvRmatGraniteFlags;

/* structure of the Granite material type description*/
typedef struct {
    AvColor       color1;
    double        amount1;
    AvColor       color2;
    double        amount2;
    AvColor       color3;
    double        amount3;
    AvColor       color4;
    double        amount4;
    double        sharpness;
    double        scale;
    unsigned long flags;
} AvRmatGranite;

typedef enum {
    AvWoodLightColor = 0x01,
    AvWoodDarkColor  = 0x02,
    AvWoodRatio      = 0x04,
    AvWoodDensity    = 0x08,
    AvWoodWidth      = 0x10,
    AvWoodShape      = 0x20,
    AvWoodScale      = 0x40
} AvRmatWoodFlags;

typedef struct {
    AvColor       lightColor;
    AvColor       darkColor;
    double        ratio;
    double        density;
    double        width;
    double        shape;
    double        scale;
    unsigned long flags;
} AvRmatWood;

typedef enum {
    AvRmatMatType    = 0x0001,
    AvRmatName       = 0x0002,
    AvRmatAci        = 0x0004,
    AvRmatSelSet     = 0x0008,
    AvRmatLayerName  = 0x0010,
    AvRmatNewName    = 0x0020,
    AvRmatBumpMap    = 0x0040,
    AvRmatReflMirror = 0x0080,
    AvRmatReflColor  = 0x0100,
    AvRmatReflWeight = 0x0200,
    AvRmatReflMap    = 0x0400,
    AvRmatRoughness  = 0x0800,
    AvRmatRb         = 0x1000,
    AvRmatMatParams  = 0x2000,
    AvRmatEntity     = 0x4000,
    AvRmatAttachment = 0x8000
} AvRmatFlags;

typedef enum {
    AvRmatStandardMaterial,
    AvRmatWoodMaterial,
    AvRmatGraniteMaterial,
    AvRmatMarbleMaterial
} AvMaterialType;

typedef enum {
    AvRmatByObject = 0,
    AvRmatByACI,
    AvRmatByLayer,
    AvRmatByDefault
} AvRmatAttachMethod;

typedef enum {
    AvRmatNew = 0,
    AvRmatModify,
    AvRmatCopy,
    AvRmatAttach,
    AvRmatAttachResbuf,
    AvRmatDetach,
    AvRmatList,
    AvRmatShowMat,
    AvRmatUI,
    AvRmatToDbName,     // Added for AVLIB 0.03
    AvRmatFromDbName    // Added for AVLIB 0.03
} AvRmatMode; 

/* structure of the material command */
typedef struct {
    AvRmatMode         mode;
    AvMaterialType     matType;
    char              *name;
    int                aci;
    ads_name           selectionSet;
    ads_name           entity;
    char              *layerName;
    char              *newName;
    AvRmatMap          bumpMap;
    AvBoolean          reflMirror;
    AvColor            reflColor;
    double             reflWeight;
    AvRmatMap          reflMap;
    double             roughness;
    struct resbuf      *rb;
    AvRmatAttachMethod attachment;
    union {
        AvRmatStandard standard;
        AvRmatMarble   marble;
        AvRmatGranite  granite;
        AvRmatWood     wood;
    } matParams;
    unsigned long      flags;
} AvRmatParam;

/*******************************************************************
 *  The av_matlib() command
 *******************************************************************/

typedef enum {
    AvMatlibMaterial    = 0x000001,
    AvMatlibLibrary     = 0x000002,
    AvMatlibMatList     = 0x000004
} AvMatlibFlags;

/* All Possible modes for MATLIB command */
typedef enum {
    AvMatlibImport = 0,
    AvMatlibExport,
    AvMatlibDelete,
    AvMatlibPurge,
    AvMatlibList,
    AvMatlibName,
    AvMatlibSet,
    AvMatlibRemove,
    AvMatlibUI
} AvMatlibMode;

/* Structure for the MATLIB command to be passed in */
typedef struct {
    AvMatlibMode   mode;
    char          *materialName;
    char          *libraryName;
    struct resbuf *stringList;
    unsigned long  flags;
} AvMatlibParam;

/*******************************************************************
 *  The av_fog() command
 *******************************************************************/

typedef enum {
    AvFogEnabled        = 0x000001,
    AvFogColor          = 0x000002,
    AvFogNearDistance   = 0x000004,
    AvFogFarDistance    = 0x000008,
    AvFogNearPercent    = 0x000010,
    AvFogFarPercent     = 0x000020,
    AvFogBackground     = 0x000040
} AvFogFlags;

typedef enum {
    AvFogSet = 0,
    AvFogList,
    AvFogUI
} AvFogMode;

typedef struct {
    AvFogMode      mode;
    AvBoolean      enabled;
    AvColor        color;
    double         nearDistance;
    double         farDistance;
    double         nearPercent;
    double         farPercent;
    AvBoolean      background;
    unsigned long  flags;
} AvFogParam;

/*******************************************************************
 *  The av_scene() command
 *******************************************************************/

typedef enum {
    AvSceneName         = 0x000001,
    AvSceneNewName      = 0x000002,
    AvSceneView         = 0x000004,
    AvSceneLights       = 0x000008,
    AvSceneNames        = 0x000010
} AvSceneFlags;

typedef enum {
    AvSceneNew = 0,
    AvSceneModify,
    AvSceneDelete,
    AvSceneSet,
    AvSceneList,
    AvSceneUI
} AvSceneMode;

typedef struct {
    AvSceneMode     mode;
    char           *sceneName;
    char           *sceneNewName;
    char           *view;
    struct resbuf  *lights;
    char           *selectedScene;
    struct resbuf  *scenes;
    unsigned long   flags;
} AvSceneParam;

/*******************************************************************
 *  The av_render() command
 *******************************************************************/

typedef enum {
    AvRenderFilename    = 0x000001,
    AvRenderCropWindow  = 0x000002,
    AvRenderMemory      = 0x000004   // Added for AVLIB 0.03
} AvRenderFlags;

/* All Possible modes for RENDER command */
typedef enum {
    AvRender = 0,
    AvRenderUI
} AvRenderMode;

/* Structure for the RENDER command to be passed in */
typedef struct {
    AvRenderMode   mode;
    char          *fileName;
    void          *memory;  // Added for AVLIB 0.03
    ads_point      point1;
    ads_point      point2;
    unsigned long  flags;
} AvRenderParam;

/*******************************************************************
 *  The av_rpref() command
 *******************************************************************/

typedef enum {
    AvRprefPalette      = 0x000001,
    AvRprefDestination  = 0x000002,
    AvRprefIconScale    = 0x000004,
    AvRprefRenderType   = 0x000008,
    AvRprefQuality      = 0x000010,
    AvRprefAntiAlias    = 0x000020,
    AvRprefTextureSamp  = 0x000040,
    AvRprefShadMinBias  = 0x000080,
    AvRprefShadMaxBias  = 0x000100,
    AvRprefBackFacing   = 0x000200,
    AvRprefBackNormNeg  = 0x000400,
    AvRprefAdaptSample  = 0x000800,
    AvRprefContrastThr  = 0x001000,
    AvRprefMaxDepth     = 0x002000,
    AvRprefCutoffThr    = 0x004000,
    AvRprefEntitySel    = 0x008000,
    AvRprefSmoothAngle  = 0x010000,
    AvRprefSubsample    = 0x020000,
    AvRprefToggle       = 0x040000
} AvRprefFlags;

typedef enum {
    AvRprefSmooth       = 0x000001,
    AvRprefMerge        = 0x000002,
    AvRprefFinish       = 0x000004,
    AvRprefShadow       = 0x000008,
    AvRprefSkipRdlg     = 0x000010,
    AvRprefCropwindow   = 0x000020,
    AvRprefSyncDatabase = 0x000040,  // Added for AVLIB 0.03
    AvRprefCache        = 0x000080   // Added for AVLIB 0.03
} AvRprefToggleFlags;

typedef struct {
    AvBoolean       AvRprefSmoothToggle;
    AvBoolean       AvRprefMergeToggle;    
    AvBoolean       AvRprefFinishToggle;    
    AvBoolean       AvRprefShadowToggle;    
    AvBoolean       AvRprefSkipRdlgToggle;    
    AvBoolean       AvRprefCropwindowToggle; 
    AvBoolean       AvRprefSyncDatabaseToggle; // Added for AVLIB 0.03
    AvBoolean       AvRprefCacheToggle;        // Added for AVLIB 0.03
    unsigned long   flags; 
} AvRprefToggleParam;
  
/* All Possible modes for RPREF command */
typedef enum {
    AvRprefSet = 0,
    AvRprefRopt,
    AvRprefList,
    AvRprefUI
} AvRprefMode;

typedef enum {
    AvRprefAcadPalette,
    AvRprefFoldPalette,
    AvRprefNofoldPalette
} AvRprefPaletteType;

typedef enum {
    AvRprefDestFramebuffer,
    AvRprefDestHardcopy,
    AvRprefDestFile
} AvRprefDestType;

typedef enum {
    AvRprefRenderAcad,
    AvRprefRenderAvis,
    AvRprefRenderRaytrace
} AvRprefRenderTypeParam;

typedef enum {
    AvRprefGouraud,
    AvRprefPhong
} AvRprefQualityType;

typedef enum {
    AvRprefAntiAliasNone = 1,
    AvRprefAntiAliasMinimal,
    AvRprefAntiAliasLow,
    AvRprefAntiAliasMedium,
    AvRprefAntiAliasHigh
} AvRprefAntiAliasType;

typedef enum {
    AvRprefSamplePoint = 1,
    AvRprefSampleLinear,
    AvRprefSampleMipmap
} AvRprefSampleType;

/* Structure for the RPREF command to be passed in */
typedef struct {
    AvRprefMode             mode;
    AvRprefPaletteType      palette;
    AvRprefDestType         destination;
    double                  iconScale;
    AvRprefRenderTypeParam  renderType;
    AvRprefQualityType      quality;
    AvRprefAntiAliasType    antiAlias;
    AvRprefSampleType       textureSample;
    double                  minimumBias;
    double                  maximumBias;
    AvBoolean               discardBackfaces;
    AvBoolean               backfaceNormalNegative;
    AvBoolean               adaptiveSampling;
    double                  contrastThreshold;
    int                     maximumDepth;
    double                  cutoffThreshold;
    AvBoolean               selectEntities;
    double                  smoothingAngle;
    int                     subSampling;
    AvRprefToggleParam      toggle;
    unsigned long           flags;
} AvRprefParam;

/*******************************************************************
 *  The av_lsobj() command.
 *******************************************************************/

typedef enum {
    AvLsCameraAlignedOnePoly, 
    AvLsOnePoly,
    AvLsTwoPolys,
    AvLsCameraAlignedTwoPolys 
} AvLsAlign;

typedef enum {
    AvLsNew = 0,
    AvLsEdit,
    AvLsList,
    AvLsLibOpen,
    AvLsLibDelete,
    AvLsLibModify,
    AvLsLibAdd,
    AvLsLibList,
    AvLsLibSave,
    AvLsNewUI,
    AvLsEditUI,
    AvLsLibUI
} AvLsMode;

typedef enum {
    AvLsEntity     = 0x01,
    AvLsName       = 0x02,
    AvLsHeight     = 0x04,
    AvLsPosition   = 0x08,
    AvLsAlignment  = 0x10,
    AvLsTexture    = 0x20,
    AvLsOpacity    = 0x40,
    AvLsStringList = 0x80
} AvLsFlags;

typedef struct {
    AvLsMode       mode;
    ads_name       entity;
    char          *name;
    double         height;
    ads_point      position;
    AvLsAlign      alignment;
    char          *texture;
    char          *opacity;
    struct resbuf *stringList;
    unsigned long  flags;
} AvLsParam;

/*******************************************************************
 *  The av_setuv() command.
 *******************************************************************/

typedef enum{
    AvSetuvPlanar,
    AvSetuvCylindrical,
    AvSetuvSpherical,
    AvSetuvSolid
} AvSetuvType;

typedef enum {
    AvSetuvAssign = 0,
    AvSetuvAssignResbuf,
    AvSetuvDetach,
    AvSetuvList,
    AvSetuvUI
} AvSetuvMode;

typedef enum {
    AvSetuvSelectionSet = 0x001,
    AvSetuvMappingType  = 0x002,
    AvSetuvP1           = 0x004,
    AvSetuvP2           = 0x008,
    AvSetuvP3           = 0x010,
    AvSetuvP4           = 0x020,
    AvSetuvTiling       = 0x040,
    AvSetuvScale        = 0x080,
    AvSetuvOffset       = 0x100,
    AvSetuvEntity       = 0x200
} AvSetuvFlags;

typedef struct {
    AvSetuvMode    mode;
    ads_name       selectionSet;
    ads_name       entity;
    AvSetuvType    mappingType;
    ads_point      p1;
    ads_point      p2;
    ads_point      p3;
    ads_point      p4;
    AvTileType     tile;
    ads_point      scale;
    ads_point      offset;
    struct resbuf *rb;
    unsigned long  flags;
} AvSetuvParam;

/*******************************************************************
 *  The av_renderupdate() command.
 *******************************************************************/

typedef enum {
    AvRenderUpdateAlways = 0,
    AvRenderUpdateOff,
    AvRenderUpdateNext,
    AvRenderUpdateNotNext
} AvRenderUpdateMode;

typedef struct {
    AvRenderUpdateMode mode;
} AvRenderUpdateParam;

/*******************************************************************
 *  The av_background() command.
 *******************************************************************/

typedef enum {
    AvBackgroundSolid = 0,
    AvBackgroundGradient,
    AvBackgroundImage,
    AvBackgroundMerge,
    AvBackgroundEnv,
    AvBackgroundList,
    AvBackgroundUI
} AvBackgroundMode;

typedef enum {
    AvBackgroundFitScale,
    AvBackgroundFitAspect
} AvBgFit;

typedef enum {
    AvBackgroundLock       = 0x001,
    AvBackgroundSolidColor = 0x002,
    AvBackgroundColor1     = 0x004,
    AvBackgroundColor2     = 0x008,
    AvBackgroundColor3     = 0x010,
    AvBackgroundAngle      = 0x020,
    AvBackgroundHorizon    = 0x040,
    AvBackgroundHeight     = 0x080,
    AvBackgroundFit        = 0x100,
    AvBackgroundImageFile  = 0x200,
    AvBackgroundEnvFile    = 0x400,
    AvBackgroundEnvLock    = 0x800
} AvBackgroundFlags;

typedef struct {
    AvBackgroundMode mode;
    AvBoolean        lock;
    AvColor          solid;
    AvColor          color1;
    AvColor          color2;
    AvColor          color3;
    double           angle;
    double           horizon;
    double           height;
    AvBgFit          fit;
    AvRmatMap        imageFile;
    char            *envFile;
    AvBoolean        envLock;
    unsigned long    flags;
} AvBackgroundParam;

/*******************************************************************
 *  The av_rfileopt() command.
 *******************************************************************/

typedef enum {
    AvFileOptColorModeMono,
    AvFileOptColorModeG8,
    AvFileOptColorModeC8,
    AvFileOptColorModeC16,
    AvFileOptColorModeC24,
    AvFileOptColorModeC32
} AvFileOptColor;

typedef enum {
    AvFileOptGIF = 0,
    AvFileOptX11,
    AvFileOptPBM,
    AvFileOptPGM,
    AvFileOptPPM,
    AvFileOptTGA,
    AvFileOptPCX,
    AvFileOptSUN,
    AvFileOptBMP,
    AvFileOptPS,
    AvFileOptTIFF,
    AvFileOptFAX,
    AvFileOptIFF,
    AvFileOptFITS,
    AvFileOptMemory, // Added for AVLIB 0.03
    AvFileOptList
} AvFileOptMode;

typedef enum {
    AvFileOptAuto,
    AvFileOptImage,
    AvFileOptCustom
} AvImageSize;

typedef enum {
    AvFileOptXRes        = 0x0001,
    AvFileOptYRes        = 0x0002,
    AvFileOptAspectRatio = 0x0004,
    AvFileOptColorMode   = 0x0008,
    AvFileOptInterlace   = 0x0010,
    AvFileOptBinary      = 0x0020,
    AvFileOptCompression = 0x0040,
    AvFileOptBottomUp    = 0x0080,
    AvFileOptPortrait    = 0x0100,
    AvFileOptImageSize   = 0x0200,
    AvFileOptSize        = 0x0400,
    AvFileOptOrientation = 0x0800, // Added for AVLIB 0.03
    AvFileOptPixelFormat = 0x1000  // Added for AVLIB 0.03
} AvFileOptFlags; 

typedef enum {
    AvFileOptRowTopLeft,
    AvFileOptRowTopRight,
    AvFileOptRowBottomLeft,
    AvFileOptRowBottomRight,
    AvFileOptColTopLeft,
    AvFileOptColTopRight,
    AvFileOptColBottomLeft,
    AvFileOptColBottomRight
} AvOrientation;                   // Added for AVLIB 0.03

typedef enum {
    AvRGBA,
    AvBGRA
} AvPixelFormat;                   // Added for AVLIB 0.03

typedef struct {
    AvFileOptMode  mode;
    int            xRes;
    int            yRes;
    double         aspectRatio;
    AvFileOptColor colorMode;
    int            interlace;
    AvBoolean      binary;
    AvBoolean      compression;
    AvBoolean      bottomUp;
    AvBoolean      portrait;
    AvBoolean      ascii;
    AvImageSize    imageSize;
    int            size;
    AvOrientation  orientation;    // Added for AVLIB 0.03
    AvPixelFormat  pixelFormat;    // Added for AVLIB 0.03
    unsigned long  flags;
} AvFileOptParam;

/*******************************************************************
 *  The av_stats() command.
 *******************************************************************/


typedef enum {
    AvStats = 0,
    AvStatsList,
    AvStatsUI
} AvStatsMode;

typedef enum {
    AvStatsFilename      = 0x0001,
    AvStatsRenderType    = 0x0002,
    AvStatsSceneName     = 0x0004,
    AvStatsRenderFile    = 0x0008,
    AvStatsTotalTime     = 0x0010,
    AvStatsShadowTime    = 0x0020,
    AvStatsInitTime      = 0x0040,
    AvStatsTraversalTime = 0x0080,
    AvStatsRenderTime    = 0x0100,
    AvStatsDisplayTime   = 0x0200,
    AvStatsCleanupTime   = 0x0400,
    AvStatsFaces         = 0x0800,
    AvStatsTriangles     = 0x1000,
    AvStatsWidth         = 0x2000,
    AvStatsHeight        = 0x4000,
    AvStatsColors        = 0x8000
} AvStatsFlags;

typedef struct {
    AvStatsMode             mode;
    char                   *filename;
    AvRprefRenderTypeParam  renderType;
    char                   *sceneName;
    char                   *renderFile;
    double                  totalTime;
    double                  shadowTime;
    double                  initTime;
    double                  traversalTime;
    double                  renderTime;
    double                  displayTime;
    double                  cleanupTime;
    unsigned long           faces;
    unsigned long           triangles;
    int                     width;
    int                     height;
    int                     colors;
    unsigned long           flags;
} AvStatsParam;

/*******************************************************************
 *  The av_replay() command.
 *******************************************************************/

typedef enum {
    AvReplayGIF,
    AvReplayTGA,
    AvReplayTIFF
} AvReplayFileType;

typedef enum {
    AvReplay = 0,
    AvReplayUI
} AvReplayMode;

typedef enum {
    AvReplayFilename = 0x01,
    AvReplayType     = 0x02,
    AvReplayXoff     = 0x04,
    AvReplayYoff     = 0x08,
    AvReplayXsize    = 0x10,
    AvReplayYsize    = 0x20
} AvReplayFlags;

typedef struct {
    AvReplayMode     mode;
    char            *filename;
    AvReplayFileType type;
    int              xoff;
    int              yoff;
    int              xsize;
    int              ysize;
    unsigned long    flags;
} AvReplayParam;

/*******************************************************************
 *  The av_saveimg() command.
 *******************************************************************/

typedef enum {
    AvSaveimgGIF,
    AvSaveimgTGA,
    AvSaveimgTIFF
} AvSaveimgFileType;

typedef enum {
    AvSaveimgActive,
    AvSaveimgDrawingArea,
    AvSaveimgFullScreen
} AvSaveimgPortion;

typedef enum {
    AvSaveimgNone,
    AvSaveimgPack,
    AvSaveimgLZW,
    AvSaveimgRLE
} AvSaveimgCompress;

typedef enum {
    AvSaveimg = 0,
    AvSaveimgUI
} AvSaveimgMode;

typedef enum {
    AvSaveimgFilename    = 0x01,
    AvSaveimgType        = 0x02,
    AvSaveimgPor         = 0x04,
    AvSaveimgXoff        = 0x08,
    AvSaveimgYoff        = 0x10,
    AvSaveimgXsize       = 0x20,
    AvSaveimgYsize       = 0x40,
    AvSaveimgCompression = 0x80
} AvSaveimgFlags;

typedef struct {
    AvSaveimgMode     mode;
    char             *filename;
    AvSaveimgFileType type;
    AvSaveimgPortion  portion;
    int               xoff;
    int               yoff;
    int               xsize;
    int               ysize;
    AvSaveimgCompress compression;
    unsigned long     flags;
} AvSaveimgParam;

/*******************************************************************
 *  The av_colormap() command.
 *******************************************************************/
typedef enum {
    AvInitAndSave = 0,
    AvRestoreAndForget
} AvColormapMode;


typedef struct {
    AvColormapMode    mode;
    unsigned long     flags;
} AvColormapParam;


/*******************************************************************
 *  Function Prototypes.
 *******************************************************************/

AvErrorCode av_loadlib(void);
AvErrorCode av_initialize(void);


char *av_errorstr(AvErrorCode);

#ifdef _DEBUG

// These routines provide access to the command line
// buffer, which is maintained in the _DEBUG version,
// only.
//
// Use av_getCurrentCommandLineLength to get the proper
// size for the current buffer (including the NULL terminator).
//
// The format of the command line buffer is AutoLISP-like, and
// includes enclosing parentheses.
// 
// Note that the "errorstr" commands are *not* stored in the
// command line buffer.
// 
void av_getCurrentCommandLine(char *s);
size_t av_getCurrentCommandLineLength();

#endif

AvErrorCode av_background(AvBackgroundParam *);
AvErrorCode av_colormap(AvColormapParam *);
AvErrorCode av_fog(AvFogParam *);
AvErrorCode av_light(AvLightParam *);
AvErrorCode av_lsobj(AvLsParam *);
AvErrorCode av_matlib(AvMatlibParam *);
AvErrorCode av_rconfig(void);
AvErrorCode av_render(AvRenderParam *);
AvErrorCode av_renderupdate(AvRenderUpdateParam *);
AvErrorCode av_replay(AvReplayParam *);
AvErrorCode av_rfileopt(AvFileOptParam *);
AvErrorCode av_rmat(AvRmatParam *);
AvErrorCode av_rpref(AvRprefParam *);
AvErrorCode av_saveimg(AvSaveimgParam *);
AvErrorCode av_scene(AvSceneParam *);
AvErrorCode av_setuv(AvSetuvParam *);
AvErrorCode av_stats(AvStatsParam *);

#if defined(__cplusplus)
}
#endif

#endif
