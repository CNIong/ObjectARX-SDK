#pragma once

//
// (C) Copyright 2002 by Autodesk, Inc. 
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
// This API extends AcGi to support material definition and assignment
//

#include "acgi.h"
#pragma pack (push, 8)

#ifdef ACGIMATERIAL_IMPL
#define ACGIMAT_IMPEXP __declspec(dllexport)
#else
#define ACGIMAT_IMPEXP __declspec(dllimport)
#endif

class AcGiNonEntityTraits : public AcGiDrawableTraits
// 
// This class implements empty AcGiDrawableTraits and AcGiSubEntityTraits
// interfaces, to allow non-entity drawables such as materials to elaborate 
// their unique properties through AcGiDrawableTraits
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiNonEntityTraits);

    // AcGiDrawableTraits interface
    virtual void                setupForEntity      (AcDbEntity* pEntity);

    // AcGiSubEntityTraits interface
    virtual void                setColor            (const Adesk::UInt16 color);
    virtual Adesk::UInt16       color               (void) const;
    virtual void                setTrueColor        (const AcCmEntityColor& color);
    virtual AcCmEntityColor     trueColor           (void) const;
    virtual void                setLayer            (const AcDbObjectId layerId);
    virtual AcDbObjectId        layerId             (void) const;
    virtual void                setLineType         (const AcDbObjectId linetypeId);
    virtual AcDbObjectId        lineTypeId          (void) const;
    virtual void                setSelectionMarker  (const Adesk::Int32 markerId);
    virtual void                setFillType         (const AcGiFillType fillType);
    virtual AcGiFillType        fillType            (void) const;
    virtual void                setLineWeight       (const AcDb::LineWeight lw);
    virtual AcDb::LineWeight    lineWeight          (void) const;
    virtual void                setThickness        (double thickness);
    virtual double              thickness           (void) const;
    virtual void                setLineTypeScale    (double dScale);
    virtual double              lineTypeScale       (void) const;
};

class AcGiMaterialColor;
class AcGiMaterialMap;

class AcGiMaterialTraits : public AcGiNonEntityTraits
// 
// This class enables material definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialTraits);

    // Set material properties
    //
    virtual void setAmbient     (const AcGiMaterialColor & color)   = 0;
    virtual void setDiffuse     (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map)       = 0;
    virtual void setSpecular    (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map,
                                 double dGloss)                     = 0;
    virtual void setReflection  (const AcGiMaterialMap & map)       = 0;
    virtual void setOpacity     (double dPercentage, 
                                 const AcGiMaterialMap & map)       = 0;
    virtual void setBump        (const AcGiMaterialMap & map)       = 0;
    virtual void setRefraction  (double dIndex, 
                                 const AcGiMaterialMap & map)       = 0;

    // Return material properties
    //
    virtual void ambient        (AcGiMaterialColor & color) const   = 0;
    virtual void diffuse        (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map) const       = 0;
    virtual void specular       (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map,
                                 double & dGloss) const             = 0;
    virtual void reflection     (AcGiMaterialMap & map) const       = 0;
    virtual void opacity        (double & dPercentage, 
                                 AcGiMaterialMap & map) const       = 0;
    virtual void bump           (AcGiMaterialMap & map) const       = 0;
    virtual void refraction     (double & dIndex, 
                                 AcGiMaterialMap & map) const       = 0;
};

class AcGiImpMaterialColor;

class AcGiMaterialColor: public AcRxObject
//
// This class defines material component colors by
// method, color value, and factor. 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialColor);

    enum Method {
        kInherit = 0,
        kOverride,     
    };

    ACGIMAT_IMPEXP static const AcGiMaterialColor kNull;

    AcGiMaterialColor             (void);
    virtual ~AcGiMaterialColor    (void);

    AcGiMaterialColor             (const AcGiMaterialColor &matColor);
    AcGiMaterialColor & operator= (const AcGiMaterialColor &matColor);

    // Set properties of material color.
    //
    virtual void set       (const AcGiMaterialColor &matColor);
    virtual void setMethod (Method method);
    virtual void setFactor (double dFactor);
    virtual void setColor  (const AcCmEntityColor& color);

    // Return current settings.
    //
    virtual Method                  method (void) const;
    virtual double                  factor (void) const;
    virtual const AcCmEntityColor & color  (void) const;

private:
    AcGiImpMaterialColor * mpAcGiImpMaterialColor;
};

class AcGiMapper;
class AcGiImpMaterialMap;

class AcGiMaterialMap: public AcRxObject 
//
// This class defines material component maps by 
// source, blend factor, and mapper.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialMap);

    enum Source {
        kScene = 0,
        kFile
    };

    ACGIMAT_IMPEXP static const AcGiMaterialMap kNull;

    AcGiMaterialMap             (void);
    virtual ~AcGiMaterialMap    (void);

    AcGiMaterialMap             (const AcGiMaterialMap &matMap);
    AcGiMaterialMap & operator= (const AcGiMaterialMap &matMap);

    // Set properties of material map.
    //
    virtual void set               (const AcGiMaterialMap &matMap);
    virtual void setSource         (Source source);
    virtual void setSourceFileName (const char * fileName);
    virtual void setBlendFactor    (double blendFactor);
    virtual void setMapper         (const AcGiMapper &mapper);

    // Return current settings.
    //
    virtual Source                  source         (void) const;
    virtual const char *            sourceFileName (void) const;
    virtual double                  blendFactor    (void) const;
    virtual const AcGiMapper &      mapper         (void) const;

private:
    AcGiImpMaterialMap * mpAcGiImpMaterialMap;
};

  
class AcGiImpMapper;

class AcGiMapper: public AcRxObject 
//
// This class defines material component mappers by 
// projection, tiling, auto transform, and transform.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMapper);

    enum Projection {
        kInheritProjection = 0,
        kPlanar,
        kBox,
        kCylinder,
        kSphere
    };

    enum Tiling {
        kInheritTiling = 0,
        kTile,
        kCrop,
        kClamp
    };

    enum AutoTransform {
        kInheritAutoTransform = 0x0,
        kNone                 = 0x1,
        kObject               = 0x2,
        kModel                = 0x4
    };

    ACGIMAT_IMPEXP static const AcGiMapper kIdentity;

    AcGiMapper             (void);
    virtual ~AcGiMapper    (void);

    AcGiMapper             (const AcGiMapper &mapper);
    AcGiMapper & operator= (const AcGiMapper &mapper);

    // Set properties of material mapper.
    //
    virtual void set               (const AcGiMapper &mapper);
    virtual void setProjection     (Projection projection);
    virtual void setTiling         (Tiling tiling);
    virtual void setAutoTransform  (AutoTransform autoTransform);
    virtual void setTransform      (const AcGeMatrix3d &transform);

    // Return current settings.
    //
    virtual Projection             projection    (void) const;
    virtual Tiling                 tiling        (void) const;
    virtual AutoTransform          autoTransform (void) const;
    virtual const AcGeMatrix3d&    transform     (void) const;

private:
    AcGiImpMapper * mpAcGiImpMapper;
};

#pragma pack (pop)