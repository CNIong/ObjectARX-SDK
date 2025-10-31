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
// Visual Styles AcGi interfaces
//

#include "acgi.h"

class AcGiImpFaceStyle;
class AcGiImpEdgeStyle;
class AcGiImpDisplayStyle;
class AcGiImpVisualStyle;

////////////////////////////////////////////////////////////////////////
// class AcGiFaceStyle
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines a collection of visual style properties
/// that can be applied to the faces of graphical entities.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
class AcGiFaceStyle : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiFaceStyle);

    /// <summary>
    /// Describes the type of lighting to apply to the faces of graphical
    /// entities to which this face style is applied.
    /// </summary>
    enum LightingModel {
    /// <summary>
    /// Faces are not drawn.
    /// </summary>
        kInvisible,
    /// <summary>
    /// Faces are drawn in a constant color.
    /// </summary>
        kConstant,
    /// <summary>
    /// Faces are drawn to approximate realistic direct lighting.
    /// </summary>
        kPhong,
    /// <summary>
    /// Gooch, A., Gooch, B., Shirley, P., and Cohen, E. 1998.  
    /// A non-photorealistic lighting model for automatic technical
    /// illustration.  In proceedings of the 25th Annual Conference
    /// on Computer Graphics and Interactive Techniques SIGGRAPH '98.
    /// ACM Press, New York, NY, 447-452.
    /// </summary>
        kGooch
    };

    /// <summary>
    /// Describes the calculation method used for application of
    /// lighting effects to faces.
    /// </summary>
    enum LightingQuality {
    /// <summary>
    /// Apply no lighting calculations to the faces.
    /// </summary>
        kNoLighting,
    /// <summary>
    /// Each face has a color calculated based on its orientation to the 
    /// light source(s) of the scene. 
    /// </summary>
        kPerFaceLighting,
    /// <summary>
    /// Each vertex of a face has its color calculated based on its 
    /// orientation to the light source(s) of the scene. 
    /// </summary>
        kPerVertexLighting
    };

    /// <summary>
    /// Describes modifications that affect the color of a face before 
    /// any lighting and shading (face style) calculations have been performed.
    /// </summary>
    enum FaceColorMode {
    /// <summary>
    /// No modifications are to be applied to the faces.
    /// </summary>
        kNoColorMode,
    /// <summary>
    /// Apply the color of the drawable object to the faces of the object.
    /// </summary>
        kObjectColor,
    /// <summary>
    /// Apply the display background color to the faces.
    /// </summary>
        kBackgroundColor,
    /// <summary>
    /// All faces are treated as having a specific color, resulting in a 
    /// "monochromatic" effect.
    /// </summary>
        kMono,
    /// <summary>
    /// All faces have the Hue and Saturation values of their color mapped 
    /// to the Hue and Saturation values of a specific color, resulting in
    /// a "tinted" effect.  The luminance value remains unchanged.
    /// </summary>
        kTint,
    /// <summary>
    /// Apply a desaturation percentage to the diffuse color of a material.
    /// </summary>
        kDesaturate
    };

    /// <summary>
    /// 
    /// </summary>
    enum FaceModifier {
    /// <summary>
    /// Apply no face modifiers to the faces.
    /// </summary>
        kNoFaceModifiers    = 0,
    /// <summary>
    /// Apply an opacity value to the faces.  If unset, faces are displayed with
    /// full opacity.  If set, faces are displayed with a specified degree of
    /// opacity from completely opaque to completely transparent.  Use the
	/// associated API declared as follows to set the desired degree of opacity:
	/// virtual void setOpacityLevel(double nLevel, bool bEnableModifier). 
    /// </summary>
        kOpacity            = 1,
    /// <summary>
    /// Apply a specular highlight (indicating reflection and shininess values)
	/// to a material that is applied to the faces.  Use the associated API 
	/// declared as follows to set the desired specular amount:
	/// virtual void setSpecularAmount(double nAmount, bool bEnableModifier)
    /// </summary>
        kSpecular           = 2
    };

    /// <summary>
    /// Default constructor.  Initializes members to reasonable default values.
    /// </summary>
                             AcGiFaceStyle          (void);
    /// <summary>
    /// Copy constructor.  Copies the given face style into this face style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiFaceStyle. A constant reference to the face style which will be copied  
    /// into this face style.
    /// </param>
                             AcGiFaceStyle          (const AcGiFaceStyle& style);
    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the face style.
    /// </summary>
    virtual                  ~AcGiFaceStyle         (void);

    /// <summary>
    /// Set method initializes this face style with the values of the 
    /// given face style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiFaceStyle. A constant reference to the face style 
    /// which will be copied into this face style.
    /// </param>                               
    virtual void             set                    (const AcGiFaceStyle& style);
    /// <summary>
    /// Assignment operator.  Copies the given face style into this face style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiFaceStyle. A constant reference to the face style 
    /// which will be copied into this face style.
    /// </param>                               
    /// <returns>
    /// Returns a reference to the face style into which the copy was made.
    /// </returns>
    virtual AcGiFaceStyle&   operator=              (const AcGiFaceStyle& style);
    /// <summary>
    /// Comparison operator.  Compares the given face style with this face style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiFaceStyle. A constant reference to the face style 
    /// which will be compared to this face style.
    /// </param>                               
    /// <returns>
    /// Returns boolean value representing whether the given face style is equivalent
    /// to this face style.
    /// </returns>
   virtual bool             operator==             (const AcGiFaceStyle& style) const;

    // Face styles

    /// <summary>
    /// Sets the face lighting model to one of the range of values in the given
    /// enumerator LightingModel.
    /// </summary>
    /// <param name="lightingModel">
    /// Input LightingModel. The enumerated value to set as the selected lighting model.
    /// </param>                               
    virtual void             setLightingModel       (LightingModel lightingModel);
    /// <summary>
    /// Returns the currently selected face lighting model.
    /// </summary>
    /// <returns>
    /// Returns the currently selected face lighting model in the range of 
    /// the LightingModel enumeration.
    /// </returns>
    virtual LightingModel    lightingModel          (void) const;

    // Face style modifiers

    /// <summary>
    /// Sets the face lighting quality to one of the range of values in 
    /// the given enumerator LightingQuality.
    /// </summary>
    /// <param name="lightingQuality">
    /// Input LightingQuality. The enumerated value to set as the selected 
    /// lighting quality.
    /// </param>                               
    virtual void             setLightingQuality     (LightingQuality lightingQuality);
    /// <summary>
    /// Returns the currently selected face lighting quality.
    /// </summary>
    /// <returns>
    /// Returns the currently selected face lighting quality in the range of 
    /// the LightingQuality enumeration.
    /// </returns>
    virtual LightingQuality  lightingQuality        (void) const;

    /// <summary>
    /// Sets the face color mode to one of the range of values in
    /// the given enumerator FaceColorMode.
    /// </summary>
    /// <param name="mode">
    /// Input FaceColorMode.  The enumerated value to set as the selected
    /// face color mode.
    /// </param>                               
    virtual void             setFaceColorMode       (FaceColorMode mode);
    /// <summary>
    /// Returns the currently selected face color mode.
    /// </summary>
    /// <returns>
    /// Returns the currently selected face color mode in the range of
    /// the FaceColorMode enumeration.
    /// </returns>
    virtual FaceColorMode    faceColorMode          (void) const;

    /// <summary>
    /// Sets a collection of bitflags representing the face modifiers in effect.
    /// </summary>
    /// <param name="nModifiers">
    /// Input unsigned long containing the collection of bitwise flags defined
    /// in the FaceModifier enumeration.
    /// </param>                               
    virtual void             setFaceModifiers       (unsigned long nModifiers);
    /// <summary>
    /// Enables or disables the given face modifier flag.
    /// </summary>
    /// <param name="flag">
    /// Input FaceModifier enumeration value representing which flag to enable
    /// or disable.
    /// </param>                               
    /// <param name="bEnable">
    /// Input boolean representing whether to enable or disable the given flag.
    /// </param>                               
    virtual void             setFaceModifierFlag    (FaceModifier flag, bool bEnable);
    /// <summary>
    /// Provides the collection of face modifier flags that are in effect.
    /// </summary>
    /// <returns>
    /// Returns unsigned long representing the collection of face modifier
    /// flags that are in effect.
    /// </returns>
    virtual unsigned long    faceModifiers          (void) const;
    /// <summary>
    /// Describes whether a particular face modifier flag is in effect.
    /// </summary>
    /// <param name="flag">
    /// Input FaceModifier enumeration value representing the flag which
    /// is to be checked to ascertain whether it is in effect.
    /// </param>                               
    /// <returns>
    /// Returns boolean representing whether the given face modifier flag
    /// is in effect.
    /// </returns>
    virtual bool             isFaceModifierFlagSet  (FaceModifier flag) const;

    /// <summary>
    /// Sets the level of opacity to be applied to faces.
    /// </summary>
    /// <param name="nLevel">
    /// Input double representing the desired level of opacity in the range
    /// from 0.0 to 1.0, with 1.0 representing full opacity (0% transparent) 
    /// and 0.0 representing no opacity (100% transparent).
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the FaceModifier enumeration flag
    /// enabling the opacity effect should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void             setOpacityLevel        (double nLevel, bool bEnableModifier);
    /// <summary>
    /// Reports the level of opacity that is currently in effect, providing that
    /// the FaceModifier enumeration flag representing opacity is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns double representing the opacity level.
    /// </returns>
    virtual double           opacityLevel           (void) const;

    /// <summary>
    /// Sets the specular highlight amount (indicating reflection and shininess 
    /// values) of a material that is applied to the faces.  
    /// </summary>
    /// <param name="nAmount">
    /// Input double representing the amount of specular highlight to apply to a 
    /// material that is applied to the faces.
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input bool representing whether to enable the specular face modifier.  If 
    /// true, the flag is enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void             setSpecularAmount      (double nAmount, bool bEnableModifier);
    /// <summary>
    /// Reports the amount of specular highlight that will be applied to a material
    /// that is applied to the faces.
    /// </summary>
    /// <returns>
    /// Returns double representing the amount of specular highlight that will be
    /// applied to a material that is applied to the faces.
    /// !!! Range of valid values TBD !!! - see Sam Black.
    /// </returns>
    virtual double           specularAmount         (void) const;

    /// <summary>
    /// Apply a specified color that will be applied to produce a "monochromatic"
    /// effect to the faces.
    /// </summary>
    /// <param name="color">
    /// Input AcCmColor constant reference representing the color to
    /// apply monochromatically to the faces.
    /// </param>                               
    /// <param name="bEnableMode">
    /// Input bool representing whether to enable the mono color face modifier.  If 
    /// true, the flag is enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void             setMonoColor           (const AcCmColor& color, bool bEnableMode);

    /// <summary>
    /// Reports the color value that will be applied to the faces to produce a 
    /// "monochromatic" effect.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor constant reference representing the monochromatic color that 
    /// will be applied to the faces.
    /// </returns>
    virtual const AcCmColor& monoColor              (void) const;
    
    /// <summary>
    /// Reports the color value that will be applied to the faces to produce a 
    /// "monochromatic" effect.     
    /// </summary>
    /// <returns>
    /// Returns AcCmColor non-constant reference representing the monochromatic color that 
    /// will be applied to the faces.
    /// </returns>
    virtual AcCmColor&       monoColor              (void);

private:
    AcGiImpFaceStyle* mpAcGiImpFaceStyle;
};

////////////////////////////////////////////////////////////////////////
// class AcGiEdgeStyle
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines a collection of visual style properties
/// that can be applied to the edges of graphical entities.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
class AcGiEdgeStyle : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiEdgeStyle);

    /// <summary>
    /// Describes the overall model to use for display of the edges of 
    /// drawables.
    /// </summary>
    enum  EdgeModel {
        /// <summary>
        /// No edges will be displayed.
        /// </summary>
        kNoEdges,
        /// <summary>
        /// Display Isolines, imaginary lines (edges), which represent the curvature
        /// and shape of a drawable.
        /// </summary>
        kIsolines,
        /// <summary>
        /// Display facet edges, the edges between adjoining facets.
        /// </summary>
        kFacetEdges
    };

    /// <summary>
    /// Describes a collection of bitflags representing the combination of
    /// edge styles that are in effect for display of edges.
    /// </summary>
    enum EdgeStyle {
        /// <summary>
        /// No styles will be applied to the edges.
        /// </summary>
        kNoEdgeStyle        =  0,
        /// <summary>
        /// Visible edges will be displayed.
        /// </summary>
        kVisible            =  1,
        /// <summary>
        /// Silhouette edges will be displayed.  A silhouette edge is an edge
        /// connecting a back facing polygon with a front facing polygon.
        /// </summary>
        kSilhouette         =  2,
        /// <summary>
        /// Obscured edges will be displayed.  An obscured edge is that which
        /// would not be normally be visible when in a shaded view.
        /// </summary>
        kObscured           =  4,
        /// <summary>
        /// Intersection edges will be displayed.  An intersection edges is that
        /// which is inferred from portions of different intersecting objects.
        /// </summary>
        kIntersection       = 8
    };

    /// <summary>
    /// Describes modifiers that can be applied to edges to give them various types
    /// of effects.
    /// </summary>
    enum EdgeModifier {
        /// <summary>
        /// Apply no modifiers to the edges.
        /// </summary>
        kNoEdgeModifiers    =   0,
        /// <summary>
        /// Allow an edge to overhang its start and end points by a specified amount.
        /// </summary>
        kOverhang           =   1,
        /// <summary>
        /// Apply a jitter effect to the edges.  The jitter effect is produced by drawing
        /// extra lines adjacent to the original line, with a specific amount of 
        /// perturbation away from the original line.
        /// </summary>
        kJitter             =   2,
        /// <summary>
        /// Apply a width > 1 to the edges.
        /// </summary>
        kWidth              =   4,
        /// <summary>
        /// Apply a color other than the drawable object color to the edges.
        /// </summary>
        kColor              =   8,
        /// <summary>
        /// Apply a halo gap percentage to the edges of an object that is hidden
        /// by another object, such that the specified gap is displayed between the
        /// edges of the hidden object and the edges of the object which hides it.  
        /// </summary>
        kHaloGap            =  16,
        /// <summary>
        /// Force edges to be on top.  Edges will not participate in the Z-ordering
        /// of the displayed drawables.
        /// </summary>
        kAlwaysOnTop        =  64,
        /// <summary>
        /// Apply an opacity value to the edges.  If unset, edges are displayed with
        /// full opacity.  If set, edges are displayed with a specified degree of
        /// opacity from completely opaque to completely transparent.
        /// </summary>
         kOpacity            = 128,
    };

    /// <summary>
    /// Describes an enumeration representing the amount of "jitter" to apply to edges.
    /// </summary>
    enum JitterAmount {
        /// <summary>
        /// A small amount of perturbation will be applied to the edge.
        /// </summary>
        kJitterLow = 1,
        /// <summary>
        /// A medium amount of perturbation will be applied to the edge.
        /// </summary>
        kJitterMedium,
        /// <summary>
        /// A large amount of perturbation will be applied to the edge.
        /// </summary>
        kJitterHigh,
    };

    /// <summary>
    /// Describes an enumeration representing the types of line patterns that can be 
    /// displayed to represent an edge.
    /// </summary>
    enum Linetype {
        /// <summary>
        /// Display edges with a solid line pattern.
        /// </summary>
        kSolid = 1,
        /// <summary>
        /// Display edges with a dashed line pattern.
        /// </summary>
        kDashed,
        /// <summary>
        /// Display edges with a dotted line pattern.
        /// </summary>
        kDotted,
        /// <summary>
        /// Display edges with a short dashed line pattern.
        /// </summary>
        kShortDash,
        /// <summary>
        /// Display edges with a medium dashed line pattern.
        /// </summary>
        kMediumDash,
        /// <summary>
        /// Display edges with a long dashed line pattern.
        /// </summary>
        kLongDash,
        /// <summary>
        /// Display edges with a double short dashed line pattern.
        /// </summary>
        kDoubleShortDash,
        /// <summary>
        /// Display edges with a double medium dashed line pattern.
        /// </summary>
        kDoubleMediumDash,
        /// <summary>
        /// Display edges with a double long dashed line pattern.
        /// </summary>
        kDoubleLongDash,
        /// <summary>
        /// Display edges with a medium long dashed line pattern.
        /// </summary>
        kMediumLongDash,
        /// <summary>
        /// Display edges with a sparse dotted line pattern.
        /// </summary>
        kSparseDot
    };

    /// <summary>
    /// Describes an enumeration representing the type of geometry to
	/// which the edge styles should be applied.
    /// </summary>
    enum EdgeStyleApply {
        /// <summary>
        /// Apply the edge style to the geometry as designed.
        /// </summary>
        kDefault,
        /// <summary>
        /// Apply the edge style to all geometry.
        /// </summary>
        kAll
	};

    /// <summary>
    /// Default constructor.  Initializes members to reasonable default values.
    /// </summary>
                                AcGiEdgeStyle   (void);
    /// <summary>
    /// Copy constructor.  Copies the given edge style into this edge style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiEdgeStyle. A constant reference to the edge style 
    /// which will be copied into this edge style.
    /// </param>
                                AcGiEdgeStyle   (const AcGiEdgeStyle& style);
    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the edge style.
    /// </summary>

    virtual                     ~AcGiEdgeStyle  (void);

    /// <summary>
    /// Set method initializes this edge style with the values of the 
    /// given edge style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiEdgeStyle. A constant reference to the edge style 
    /// which will be copied into this edge style.
    /// </param>                               
    virtual void                set             (const AcGiEdgeStyle& style);
    /// <summary>
    /// Assignment operator.  Copies the given edge style into this edge style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiEdgeStyle. A constant reference to the edge style 
    /// which will be copied into this edge style.
    /// </param>                               
    /// <returns>
    /// Returns a reference to the edge style into which the copy was made.
    /// </returns>
    virtual AcGiEdgeStyle&      operator=       (const AcGiEdgeStyle& style);
    /// <summary>
    /// Comparison operator.  Compares the given edge style with this edge style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiEdgeStyle. A constant reference to the edge style 
    /// which will be compared to this edge style.
    /// </param>                               
    /// <returns>
    /// Returns boolean value representing whether the given edge style is equivalent
    /// to this edge style.
    /// </returns>
    virtual bool                operator==      (const AcGiEdgeStyle& style) const;

    // Edge Style Flags

    /// <summary>
    /// Sets the edge model to one of the range of values in the given
    /// enumerator EdgeModel.
    /// </summary>
    /// <param name="model">
    /// Input EdgeModel. The enumerated value to set as the selected edge model.
    /// </param>                               
    virtual void                setEdgeModel            (EdgeModel model);
    /// <summary>
    /// Returns the currently selected edge model.
    /// </summary>
    /// <returns>
    /// Returns the currently selected edge model in the range of 
    /// the EdgeModel enumeration.
    /// </returns>
    virtual EdgeModel           edgeModel               (void) const;

    /// <summary>
    /// Sets the edge style to a collection of values in the given
    /// enumerator EdgeStyle.
    /// </summary>
    /// <param name="nStyles">
    /// Input unsigned long. The bitflags to set as the collection 
    /// of selected edge styles.
    /// </param>                               
    virtual void                setEdgeStyles           (unsigned long nStyles);
    /// <summary>
    /// Enables or disables the given edge styles flag.
    /// </summary>
    /// <param name="flag">
    /// Input EdgeStyle enumeration value representing which flag to 
    /// enable or disable.
    /// </param>                               
    /// <param name="bEnable">
    /// Input boolean representing whether to enable or disable the given flag.
    /// </param>                               
    virtual void                setEdgeStyleFlag        (EdgeStyle flag, bool bEnable);
    /// <summary>
    /// Reports the collection of edge style flags in effect.
    /// </summary>
    /// <returns>
    /// Returns unsigned long collection of edge style flags in effect.
    /// </returns>
    virtual unsigned long       edgeStyles              (void) const;
    /// <summary>
    /// Reports whether a given edge style flag is in effect.
    /// </summary>
    /// <param name="flag">
    /// Input EdgeStyle enumeration representing which flag to check for enabled
    /// status.
    /// </param>                               
    /// <returns>
    /// Returns boolean true if the given flag is enabled, 
    /// false if it is disabled.
    /// </returns>
    virtual bool                isEdgeStyleFlagSet      (EdgeStyle flag) const;

    // Edge Style settings

    /// <summary>
    /// Sets the color of intersection edges.
    /// </summary>
    /// <param name="color">
    /// Input AcCmColor const reference representing the color to set.
    /// </param>
    virtual void                setIntersectionColor    (const AcCmColor& color);
    /// <summary>
    /// Reports the current color of intersection edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor const reference to the current color of the 
    /// intersection edges.
    /// </returns>
    virtual const AcCmColor&    intersectionColor       (void) const; 
    /// <summary>
    /// Reports the current color of intersection edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor non-const reference to the current color of the 
    /// intersection edges.
    /// </returns>
    virtual AcCmColor&          intersectionColor       (void); 

    /// <summary>
    /// Sets the color of obscured edges.
    /// </summary>
    /// <param name="color">
    /// Input AcCmColor const reference representing the color to set.
    /// </param>
    virtual void                setObscuredColor        (const AcCmColor& color);
    /// <summary>
    /// Reports the current color of obscured edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor const reference to the current color of the 
    /// obscured edges.
    /// </returns>
    virtual const AcCmColor&    obscuredColor           (void) const;
    /// <summary>
    /// Reports the current color of obscured edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor non-const reference to the current color of the 
    /// obscured edges.
    /// </returns>
    virtual AcCmColor&          obscuredColor           (void);

    /// <summary>
    /// Sets the linetype of obscured edges.
    /// </summary>
    /// <param name="ltype">
    /// Input a member of the Linetype enumeration representing the 
    /// linetype to set.
    /// </param>
    virtual void                setObscuredLinetype     (Linetype ltype); 
    /// <summary>
    /// Reports the current linetype of obscured edges.
    /// </summary>
    /// <returns>
    /// Returns Linetype enumeration member representing the current 
    /// linetype of the obscured edges.
    /// </returns>
    virtual Linetype            obscuredLinetype        (void) const;

    /// <summary>
    /// Sets the linetype of intersection edges.
    /// </summary>
    /// <param name="ltype">
    /// Input a member of the Linetype enumeration representing the 
    /// linetype to set.
    /// </param>
    virtual void                setIntersectionLinetype     (Linetype ltype); 
    /// <summary>
    /// Reports the current linetype of intersection edges.
    /// </summary>
    /// <returns>
    /// Returns Linetype enumeration member representing the current 
    /// linetype of the intersection edges.
    /// </returns>
    virtual Linetype            intersectionLinetype        (void) const;

	/// <summary>
    /// Sets the angle threshold, above which a facet edge 
    /// representing adjoining facets will be displayed.
    /// </summary>
    /// <param name="nAngle">
    /// Input double threshold angle.
    /// </param>
    virtual void                setCreaseAngle          (double nAngle);
    /// <summary>
    /// Reports the angle threshold, in degrees, above which a facet edge 
    /// representing adjoining facets will be displayed.
    /// </summary>
    /// <returns>
    /// Returns double threshold angle.
    /// </returns>
    virtual double              creaseAngle             (void) const;

    // Edge Modifier Flags

    /// <summary>
    /// Sets a collection of bitflags representing the edge modifiers in effect.
    /// </summary>
    /// <param name="nModifiers">
    /// Input unsigned long containing the collection of bitwise flags defined
    /// in the EdgeModifier enumeration.
    /// </param>                               
    virtual void                setEdgeModifiers        (unsigned long nModifiers);
    /// <summary>
    /// Enables or disables the given edge modifier flag.
    /// </summary>
    /// <param name="flag">
    /// Input EdgeModifier enumeration value representing which flag to enable
    /// or disable.
    /// </param>                               
    /// <param name="bEnable">
    /// Input boolean representing whether to enable or disable the given flag.
    /// </param>                               
    virtual void                setEdgeModifierFlag     (EdgeModifier flag, bool bEnable);
    /// <summary>
    /// Provides the collection of edge modifier flags that are in effect.
    /// </summary>
    /// <returns>
    /// Returns unsigned long representing the collection of edge modifier
    /// flags that are in effect.
    /// </returns>
    virtual unsigned long       edgeModifiers           (void) const;
    /// <summary>
    /// Describes whether a particular edge modifier flag is in effect.
    /// </summary>
    /// <param name="flag">
    /// Input EdgeModifier enumeration value representing the flag which
    /// is to be checked to ascertain whether it is in effect.
    /// </param>                               
    /// <returns>
    /// Returns boolean representing whether the given edge modifier flag
    /// is in effect.
    /// </returns>
    virtual bool                isEdgeModifierFlagSet   (EdgeModifier flag) const;
 
    // Edge Modifier Settings

    /// <summary>
    /// Sets the color of edges.
    /// </summary>
    /// <param name="color">
    /// Input AcCmColor const reference representing the color to set.
    /// </param>
    /// <param name="bEnableModifier">
    /// Input boolean representing whether to enable 
    /// </param>                               
    virtual void                setEdgeColor            (const AcCmColor& color, bool bEnableModifier);
    /// <summary>
    /// Reports the current color of  edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor const reference to the current color of the edges.
    /// </returns>
    virtual const AcCmColor&    edgeColor               (void) const;
    /// <summary>
    /// Reports the current color of edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor non-const reference to the current color of the edges.
    /// </returns>
    virtual AcCmColor&          edgeColor               (void);

    /// <summary>
    /// Sets the level of opacity to be applied to edges.
    /// </summary>
    /// <param name="nLevel">
    /// Input double representing the desired level of opacity in the range
    /// from 0.0 to 1.0, with 1.0 representing full opacity (0% transparent) 
    /// and 0.0 representing no opacity (100% transparent).
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the EdgeModifier enumeration flag
    /// enabling the opacity effect should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void             setOpacityLevel        (double nLevel, bool bEnableModifier);
    /// <summary>
    /// Reports the level of opacity that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing opacity is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns double representing the opacity level.
    /// </returns>
    virtual double           opacityLevel           (void) const;

    /// <summary>
    /// Sets the edge width in pixels.
    /// </summary>
    /// <param name="nWidth">
    /// Input int representing the desired width in pixels.
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the EdgeModifier enumeration flag
    /// enabling the edge width should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void                setEdgeWidth            (int nWidth, bool bEnableModifier);
    /// <summary>
    /// Reports the edge width that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing edge width is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns int representing the edge width in pixels.
    /// </returns>
    virtual int                 edgeWidth               (void) const;

    /// <summary>
    /// Sets the amount in pixels that edges should overhang their 
    /// start and end points.  
    /// </summary>
    /// <param name="nAmount">
    /// Input int representing the desired overhang amount in pixels.
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the EdgeModifier enumeration flag
    /// enabling the edge width should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void                setOverhangAmount       (int nAmount, bool bEnableModifier);
    /// <summary>
    /// Reports the edge width that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing edge overhang is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns int representing the edge overhang amount in pixels.
    /// </returns>
    virtual int                 overhangAmount          (void) const;
 
    /// <summary>
    /// Sets the amount of jitter effect, represented as a value of the 
    /// JitterAmount enumeration, to be applied to jittered edges.
    /// </summary>
    /// <param name="amount">
    /// Input int representing the desired overhang amount in pixels.
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the EdgeModifier enumeration flag
    /// enabling the jittered effect should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void                setJitterAmount         (JitterAmount amount, bool bEnableModifier);
  
    /// <summary>
    /// Reports the jitter amount that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing edge width is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns JitterAmount enumeration representing the jitter amount in effect.
    /// </returns>
    virtual JitterAmount        jitterAmount            (void) const; 

   /// <summary>
    /// Sets the color of silhouette edges.
    /// </summary>
    /// <param name="color">
    /// Input AcCmColor const reference representing the color to set.
    /// </param>
    virtual void                setSilhouetteColor      (const AcCmColor& color);
    /// <summary>
    /// Reports the current color of silhouette edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor const reference to the current color of the 
    /// silhouette edges.
    /// </returns>
    virtual const AcCmColor&    silhouetteColor         (void) const;
    /// <summary>
    /// Reports the current color of silhouette edges.
    /// </summary>
    /// <returns>
    /// Returns AcCmColor non-const reference to the current color of 
    /// the silhouette edges.
    /// </returns>
    virtual AcCmColor&          silhouetteColor         (void);

    /// <summary>
    /// Sets the silhouette edge width in pixels.
    /// </summary>
    /// <param name="nWidth">
    /// Input int representing the desired width in pixels.
    /// </param>                               
    virtual void                setSilhouetteWidth      (short nWidth);
    /// <summary>
    /// Reports the silhouette edge width that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing edge width is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns int representing the silhouette edge width in pixels.
    /// </returns>
    virtual short               silhouetteWidth         (void) const;

    /// <summary>
    /// Sets the halo gap to apply.
    /// </summary>
    /// <param name="nHaloGap">
    /// Input int from 0 to 100 representing the desired gap.
    /// </param>                               
    /// <param name="bEnableModifier">
    /// Input boolean representing whether the EdgeModifier enumeration flag
    /// enabling the halo gap should be enabled.  If true, the flag is
    /// enabled.  If false, the flag's current value is retained.
    /// </param>                               
    virtual void                setHaloGap              (int nHaloGap, bool bEnableModifier);
    /// <summary>
    /// Reports the halo gap that is currently in effect, providing that
    /// the EdgeModifier enumeration flag representing halo gap is enabled, or that
    /// would be in effect were the flag enabled.
    /// </summary>
    /// <returns>
    /// Returns int from 0 to 100 representing the halo gap in effect.
    /// </returns>
    virtual int                 haloGap                 (void) const; 

    /// sysvar
    /// <summary>
    /// Sets the number of isolines to apply.
    /// </summary>
    /// <param name="nIsolines">
    /// Input unsigned short between 0 and 2047.
    /// </param>                               
    virtual void                setIsolines             (unsigned short nIsolines);
    /// <summary>
    /// Reports the number of isolines that are currently in effect.
    /// </summary>
    /// <returns>
    /// Returns int from 0 to 2047 representing the number of isolines in effect.
    /// </returns>
    virtual unsigned short      isolines                (void) const; 

    /// sysvar
    /// <summary>
    /// Sets the state of hide precision indicating whether hide precision 
    /// should be enabled.
    /// </summary>
    /// <param name="bHidePrecision">
    /// Input boolean representing whether hide precision should be enabled.
    /// </param>                               
    virtual void                setHidePrecision        (bool bHidePrecision);
    /// <summary>
    /// Reports whether hide precision is enabled.
    /// </summary>
    /// <returns>
    /// Returns boolean representing whether hide precision is enabled.
    /// </returns>
    virtual bool                hidePrecision           (void) const; 

    /// <summary>
    /// Sets a hint indicating to what geometry the edge style should be 
	/// applied.
    /// </summary>
    /// <param name="apply">
    /// Input enum EdgeStyleApply the type of geometry to which the edge 
	/// style applies.
    /// </param>                               
    virtual void				setEdgeStyleApply       (EdgeStyleApply apply);
	/// <summary>
    /// Reports the type of geometry to which the edge style will be applied.
    /// </summary>
    /// <returns>
    /// Returns enum EdgeStyleApply representing to which geometry the edge 
	/// style will be applied.
    /// </returns>
    virtual EdgeStyleApply      edgeStyleApply          (void) const; 

private:
    AcGiImpEdgeStyle* mpAcGiImpEdgeStyle;
};

////////////////////////////////////////////////////////////////////////
// class AcGiDisplayStyle
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines a collection of display properties
/// that can be applied to graphical entities.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>

class AcGiDisplayStyle : public AcRxObject
{
public:
    /// <summary>
    /// Describes combinations of display settings that can be enabled.
    /// </summary>
    enum DisplaySettings {
        /// <summary>
        /// No display settings are in effect
        /// </summary>
        kNone                =  0,
        /// <summary>
        /// Backgrounds are enabled
        /// </summary>
        kBackgrounds         =  1,
        /// <summary>
        /// Lighting is enabled
        /// </summary>
        kLighting            =  2,
        /// <summary>
        /// Materials are enabled
        /// </summary>
        kMaterials           =  4,
        /// <summary>
        /// Textures are enabled
        /// </summary>
        kTextures            =  8,
    };

    /// <summary>
    /// Describes the type of shadows in effect.
    /// </summary>
    enum ShadowType {
        /// <summary>
        /// No shadows are displayed.
        /// </summary>
        kShadowsNone,
        /// <summary>
        /// Ground plane shadows are displayed.
        /// </summary>
        kShadowsGroundPlane,
        /// <summary>
        /// Full shadows are displayed.
        /// </summary>
        kShadowsFull,
        /// <summary>
        /// Full shadows are displayed along with shadows on the ground plane.
        /// </summary>
        kShadowsFullAndGround,
    };

    ACRX_DECLARE_MEMBERS(AcGiDisplayStyle);

    /// <summary>
    /// Default constructor.  Initializes members to reasonable default values.
    /// </summary>
                                AcGiDisplayStyle       (void);
    /// <summary>
    /// Copy constructor.  Copies the given display style into this display style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiDisplayStyle. A constant reference to the display style 
    /// which will be copied into this display style.
    /// </param>
                                AcGiDisplayStyle       (const AcGiDisplayStyle& style);
    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the display style.
    /// </summary>
    virtual                     ~AcGiDisplayStyle      (void);

    /// <summary>
    /// Set method initializes this display style with the values of the 
    /// given display style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiDisplayStyle. A constant reference to the display style 
    /// which will be copied into this display style.
    /// </param>                               
    virtual void                set                    (const AcGiDisplayStyle& style);
    /// <summary>
    /// Assignment operator.  Copies the given display style into this display style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiDisplayStyle. A constant reference to the display style 
    /// which will be copied into this display style.
    /// </param>                               
    /// <returns>
    /// Returns a reference to the display style into which the copy was made.
    /// </returns>
    virtual AcGiDisplayStyle&   operator=              (const AcGiDisplayStyle& style);

    /// <summary>
    /// Comparison operator.  Compares the given display style with this display style.
    /// </summary>
    /// <param name="style">
    /// Input AcGiDisplayStyle. A constant reference to the display style 
    /// which will be compared to this display style.
    /// </param>                               
    /// <returns>
    /// Returns boolean value representing whether the given display style is equivalent
    /// to this display style.
    /// </returns>
    virtual bool                operator==             (const AcGiDisplayStyle& style) const;

    // Display settings flags

    /// <summary>
    /// Sets a collection of bitflags representing the display settings in effect.
    /// </summary>
    /// <param name="nSettings">
    /// Input unsigned long containing the collection of bitwise flags defined
    /// in the DisplaySettings enumeration.
    /// </param>                               
    virtual void                setDisplaySettings     (unsigned long nSettings);
    /// <summary>
    /// Enables or disables the given display settings flag.
    /// </summary>
    /// <param name="flag">
    /// Input DisplaySettings enumeration value representing which flag to enable
    /// or disable.
    /// </param>                               
    /// <param name="bEnable">
    /// Input boolean representing whether to enable or disable the given flag.
    /// </param>                               
    virtual void                setDisplaySettingsFlag (DisplaySettings flag, bool bEnable);
    /// <summary>
    /// Provides the collection of display settings flags that are in effect.
    /// </summary>
    /// <returns>
    /// Returns unsigned long representing the collection of display settings
    /// flags that are in effect.
    /// </returns>
    virtual unsigned long       displaySettings        (void) const;
    /// <summary>
    /// Describes whether a particular display settings flag is in effect.
    /// </summary>
    /// <param name="flag">
    /// Input DisplaySettings enumeration value representing the flag which
    /// is to be checked to ascertain whether it is in effect.
    /// </param>                               
    /// <returns>
    /// Returns boolean representing whether the given display settings flag
    /// is in effect.
    /// </returns>
    virtual bool                isDisplaySettingsFlagSet(DisplaySettings flag) const;

    // Display Modifier Settings
    /// <summary>
    /// Sets the brightness value to apply.
    /// </summary>
    /// <param name="value">
    /// Input double brightness level to apply.
    /// </param>                               
    virtual void                setBrightness          (double value);
    /// <summary>
    /// Reports the brightness value that is currently in effect.
    /// </summary>
    /// <returns>
    /// Returns double the brightness value that is currently in effect.
    /// </returns>
    virtual double              brightness             (void) const;

    /// <summary>
    /// Sets the shadow type to apply.
    /// </summary>
    /// <param name="type">
    /// Input ShadowType entry to apply, from the ShadowType enumeration.
    /// </param>                               
    virtual void                setShadowType          (ShadowType type);
    /// <summary>
    /// Reports the shadow type that is currently in effect.
    /// </summary>
    /// <returns>
    /// Returns ShadowType the value from the ShadowType enumeration that 
    /// is currently in effect.
    /// </returns>
    virtual ShadowType          shadowType             (void) const;

private:
    AcGiImpDisplayStyle* mpAcGiImpDisplayStyle;
};

////////////////////////////////////////////////////////////////////////
// class AcGiVisualStyle
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines a Visual Style - a collection of visual properties
/// that can be applied to graphical entities.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
class AcGiVisualStyle : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiVisualStyle);

    /// <summary>
    /// Describes the type of Visual Style that is in effect.
    /// </summary>
    enum Type {
        // Legacy (shademode) styles
        /// <summary>
        /// Flat shaded visual style.
        /// </summary>
        kFlat,
        /// <summary>
        /// Flat shaded visual style with edges displayed.
        /// </summary>
        kFlatWithEdges,
        /// <summary>
        /// Gouraud shaded visual style.
        /// </summary>
        kGouraud,
        /// <summary>
        /// Gouraud shaded visual style with edges displayed.
        /// </summary>
        kGouraudWithEdges,
        /// <summary>
        /// 2D wireframe visual style (using 2D graphics system).
        /// </summary>
        k2DWireframe,
        /// <summary>
        /// 3D wireframe visual style (using 3D graphics system).
        /// </summary>
        k3DWireframe,
        /// <summary>
        /// Hidden visual style.
        /// </summary>
        kHidden,
        // Visual Styles
        /// <summary>
        /// Basic default visual style.
        /// </summary>
        kBasic,
        /// <summary>
        /// Phong shaded visual style.
        /// </summary>
        kRealistic,
        /// <summary>
        /// Gooch shaded visual style.
        /// </summary>
        kConceptual,
        /// <summary>
        /// Custom, user defined visual visual style.
        /// </summary>
        kCustom,
        // Highlight visual styles
        /// <summary>
        /// Visual style used for a dimming effect.
        /// </summary>
        kDim,
        /// <summary>
        /// Visual style used for a brightening effect.
        /// </summary>
        kBrighten,
        /// <summary>
        /// Visual style used for a thickening effect.
        /// </summary>
        kThicken,
        /// <summary>
        /// Visual style used to apply a line pattern.
        /// </summary>
        kLinePattern,
        /// <summary>
        /// Visual style used to apply a face pattern.
        /// </summary>
        kFacePattern,
        /// <summary>
        /// Visual style used to apply a change of color.
        /// </summary>
        kColorChange
    };

    /// <summary>
    /// Default constructor.  Initializes members to reasonable default values.
    /// </summary>
                            AcGiVisualStyle     (void);
    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="type">
    /// Input Type. The type of visual style to configure - a built-in type or
    /// custom.
    /// </param>
                            AcGiVisualStyle     (Type type);
    /// <summary>
    /// Copy constructor.  Copies the given visual style into this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be copied into this visual style.
    /// </param>
                            AcGiVisualStyle     (const AcGiVisualStyle& visualStyle);
    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the visual style.
    /// </summary>
                            ~AcGiVisualStyle    (void);

    /// <summary>
    /// Assignment operator.  Copies the given visual style into this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be copied into this visual style.
    /// </param>                               
    /// <returns>
    /// Returns a reference to the visual style into which the copy was made.
    /// </returns>
    AcGiVisualStyle& operator=(const AcGiVisualStyle& visualStyle);
    /// <summary>
    /// Comparison operator.  Compares the given visual style with this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be compared to this visual style.
    /// </param>                               
    /// <returns>
    /// Returns boolean value representing whether the given visual style is equivalent
    /// to this visual style.
    /// </returns>
    bool operator==(const AcGiVisualStyle& visualStyle) const;
	
	/// <summary>
    /// Configures a visual style of the given type.  
    /// </summary>
    /// <param name="type">
    /// Input Type value enumeration value to configure.
    /// </param>                               
    void                    configureForType    (Type type);

    /// <summary>
    /// Reports the face style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiFaceStyle reference to the face style of this visual style.
    /// </returns>
    AcGiFaceStyle&          faceStyle    (void)       { return mFaceStyle; }
    /// <summary>
    /// Reports the edge style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiEdgeStyle reference to the edge style of this visual style.
    /// </returns>
    AcGiEdgeStyle&          edgeStyle    (void)       { return mEdgeStyle; }
    /// <summary>
    /// Reports the display style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiDisplayStyle reference to the display style of this visual style.
    /// </returns>
    AcGiDisplayStyle&       displayStyle (void)       { return mDisplayStyle; }

    /// <summary>
    /// Reports the face style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiFaceStyle const reference to the face style of this visual style.
    /// </returns>
    const AcGiFaceStyle&    faceStyle    (void) const { return mFaceStyle; }
    /// <summary>
    /// Reports the edge style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiEdgeStyle const reference to the edge style of this visual style.
    /// </returns>
    const AcGiEdgeStyle&    edgeStyle    (void) const { return mEdgeStyle; }
    /// <summary>
    /// Reports the display style of this visual style.
    /// </summary>
    /// <returns>
    /// Returns AcGiDisplayStyle const reference to the display style of this visual style.
    /// </returns>
    const AcGiDisplayStyle& displayStyle (void) const { return mDisplayStyle; }

    /// <summary>
    /// Sets the face style of this visual style to the given face style.  
    /// </summary>
    /// <param name="style">
    /// Input AcGiFaceStyle const reference to the face style to set in this
    /// visual style.
    /// </param>                               
    void  setFaceStyle      (const AcGiFaceStyle& style)    { mFaceStyle = style; }
    /// <summary>
    /// Sets the edge style of this visual style to the given edgestyle.  
    /// </summary>
    /// <param name="style">
    /// Input AcGiEdgeStyle const reference to the edge style to set in this
    /// visual style.
    /// </param>                               
    void  setEdgeStyle      (const AcGiEdgeStyle& style)    { mEdgeStyle = style; }
    /// <summary>
    /// Sets the display style of this visual style to the given display style.  
    /// </summary>
    /// <param name="style">
    /// Input AcGiDisplayStyle const reference to the display style to set in this
    /// visual style.
    /// </param>                               
    void  setDisplayStyle   (const AcGiDisplayStyle& style) { mDisplayStyle = style; }
    
private:

    // Configure built-in types
    void configureForFlat();
    void configureForFlatWithEdges();
    void configureForGouraud();
    void configureForGouraudWithEdges();
    void configureForBasic();
    void configureFor2DWireframe();
    void configureFor3DWireframe();
    void configureForHidden();
    void configureForRealistic();
    void configureForConceptual();
    void configureForDim();
    void configureForBrighten();
    void configureForThicken();
    void configureForLinePattern();
    void configureForFacePattern();
    void configureForColorChange();

    AcGiFaceStyle       mFaceStyle;
    AcGiEdgeStyle       mEdgeStyle;
    AcGiDisplayStyle    mDisplayStyle;
};

////////////////////////////////////////////////////////////////////////
// class AcGiVisualStyleTraits
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines the visual style traits.  Derived from AcGiDrawableTraits,
/// this class provides the interfaces to implement for setting and returning the
/// visual style via drawable traits.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
class AcGiVisualStyleTraits : public AcGiDrawableTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiVisualStyleTraits);

    /// <summary>
    /// Sets the visual style to capture in the drawable traits.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle const reference to the visual style to capture.
    /// </param>                               
    virtual void                   setAcGiVisualStyle   (const AcGiVisualStyle& visualStyle) = 0;

    /// <summary>
    /// Reports the visual style that is currently captured in this drawable traits.
    /// </summary>
    /// <returns>
    /// Returns AcGiVisualStyle const reference to the visual style that is 
    /// currently captured in this drawable traits.
    /// </returns>
    virtual const AcGiVisualStyle& acgiVisualStyle      (void) const = 0;
};
