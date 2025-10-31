//

#pragma once
//
// (C) Copyright 2005-2009 by Autodesk, Inc.
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

#include "dbmain.h"
#include "acgi.h"

#pragma pack (push, 8)

// Legacy (shademode) styles
const ACHAR kszVSFlat[]                 = /*MSG0*/ACRX_T("Flat");
const ACHAR kszVSFlatWithEdges[]        = /*MSG0*/ACRX_T("FlatWithEdges");
const ACHAR kszVSGouraud[]              = /*MSG0*/ACRX_T("Gouraud");
const ACHAR kszVSGouraudWithEdges[]     = /*MSG0*/ACRX_T("GouraudWithEdges");

// Visual Styles
const ACHAR kszVS2DWireframe[]   = /*MSG0*/ACRX_T("2dWireframe");
const ACHAR kszVS3DWireframe[]   = /*MSG0*/ACRX_T("3dWireframe");
const ACHAR kszVSBasic[]         = /*MSG0*/ACRX_T("Basic");
const ACHAR kszVSHidden[]        = /*MSG0*/ACRX_T("3D Hidden");
const ACHAR kszVSRealistic[]     = /*MSG0*/ACRX_T("Realistic");
const ACHAR kszVSConceptual[]    = /*MSG0*/ACRX_T("Conceptual");
const ACHAR kszVSCustom[]        = /*MSG0*/ACRX_T("Custom");

// Highlight Visual Styles (internal use only)
const ACHAR kszVSDim[]           = /*MSG0*/ACRX_T("Dim");
const ACHAR kszVSBrighten[]      = /*MSG0*/ACRX_T("Brighten");
const ACHAR kszVSThicken[]       = /*MSG0*/ACRX_T("Thicken");
const ACHAR kszVSTransparent[]   = /*MSG0*/ACRX_T("Transparent");
const ACHAR kszVSLinePattern[]   = /*MSG0*/ACRX_T("Linepattern");
const ACHAR kszVSFacePattern[]   = /*MSG0*/ACRX_T("Facepattern");
const ACHAR kszVSColorChange[]   = /*MSG0*/ACRX_T("ColorChange");

// Edge Style Override Visual Styles (internal use only)
const ACHAR kszVSJitterOff[]     = /*MSG0*/ACRX_T("JitterOff");
const ACHAR kszVSOverhangOff[]   = /*MSG0*/ACRX_T("OverhangOff");
const ACHAR kszVSEdgeColorOff[]  = /*MSG0*/ACRX_T("EdgeColorOff");

////////////////////////////////////////////////////////////////////////
// class AcDbVisualStyle
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class describes the visual style database object, which contains
/// a collection of properties that can be applied to faces, edges and the
/// display.
/// </summary>
class AcDbVisualStyle : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbVisualStyle);

    /// <summary>
    /// Default constructor.  Initializes members to reasonable default values.
    /// </summary>
    AcDbVisualStyle();

    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the visual style.
    /// </summary>
    virtual ~AcDbVisualStyle();

    /// <summary>
    /// Sets the visual style description
    /// </summary>
    /// <param name="pDescription">
    /// Input ACHAR* const pointer to the description of the visual style.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus eOk.
    /// </returns>
    Acad::ErrorStatus   setDescription (const ACHAR* pDescription);
    /// <summary>
    /// Reports the description of this visual style.
    /// </summary>
    /// <returns>
    /// Returns ACHAR* const pointer to the description of the visual style.
    /// </returns>
    const ACHAR*        description    (void) const;

    
    
    /// <summary>
    /// Sets the visual style type from the given AcGiVisualStyle::Type 
    /// enumerator.
    /// </summary>
    /// <param name="type">
    /// Input ACHAR* const pointer to the type of the visual style.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus eOk.
    /// </returns>
    Acad::ErrorStatus setType(AcGiVisualStyle::Type type);
    /// <summary>
    /// Reports the visual style type via the AcGiVisualStyle::Type 
    /// enumerator.
    /// </summary>
    /// <returns>
    /// Returns AcGiVisualStyle::Type, the type of this visual style 
    /// as a value from the AcGiVisualStyle::Type enumeration.
    /// </returns>
    AcGiVisualStyle::Type type() const;

// Disable the "Deprecated" warnings for now, until the AcGiFaceStyle,
// AcGiEdgeStyle, and AcGiDisplayStyle classes are actually removed.
#pragma warning (push)
#pragma warning (disable:4996)

    /// <summary>
    /// Sets the AcGiFaceStyle of the visual style.
    /// </summary>
    /// <param name="faceStyle">
    /// Input AcGiFaceStyle const reference to the collection of properties
    /// pertaining to drawable faces.
    /// </param>
    ADESK_DEPRECATED void setFaceStyle(const AcGiFaceStyle& faceStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to faces.
    /// </summary>
    /// <returns>
    /// Returns AcGiFaceStyle const reference to the collection of 
    /// properties that are applied to faces.
    /// </returns>
    ADESK_DEPRECATED const AcGiFaceStyle& faceStyle() const;
    
    /// <summary>
    /// Sets the AcGiEdgeStyle of the visual style.
    /// </summary>
    /// <param name="edgeStyle">
    /// Input AcGiEdgeStyle const reference to the collection of properties
    /// pertaining to drawable edges.
    /// </param>
    ADESK_DEPRECATED void setEdgeStyle(const AcGiEdgeStyle& edgeStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to edges.
    /// </summary>
    /// <returns>
    /// Returns AcGiEdgeStyle const reference to the collection of 
    /// properties that are applied to edges.
    /// </returns>
    ADESK_DEPRECATED const AcGiEdgeStyle& edgeStyle() const;

    /// <summary>
    /// Sets the AcGiDisplayStyle of the visual style.
    /// </summary>
    /// <param name="displayStyle">
    /// Input AcGiDisplayStyle const reference to the collection of properties
    /// pertaining to the display.
    /// </param>
    ADESK_DEPRECATED Acad::ErrorStatus setDisplayStyle(const AcGiDisplayStyle& displayStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to the display.
    /// </summary>
    /// <returns>
    /// Returns AcGiDisplayStyle const reference to the collection of 
    /// properties that are applied to the display.
    /// </returns>
    ADESK_DEPRECATED const AcGiDisplayStyle& displayStyle() const;

#pragma warning (pop)

    /// <summary>
    /// Sets a property of the visual style.  
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.
    /// </param>                               
    /// <param name="pVal">
    /// Input AcGiVariant property value to set into the visual style.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    /// <example>
    ///
    /// // Set brightness to 1.0
    /// AcGiVariant displayBrightness.set(1.0);
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kDisplayBrightness, displayBrightness);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                               const AcGiVariant *pVal,
                               AcGiVisualStyleOperations::Operation op 
                               = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets an integer property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceLightingModel
    ////    kFaceLightingQuality
    ////    kFaceColorMode
    ////    kFaceModifier
    ////    kEdgeModel
    ////    kEdgeStyle
    ////    kEdgeObscuredLinePattern
    ////    kEdgeIntersectionLinePattern
    ////    kEdgeModifier
    ////    kEdgeWidth
    ////    kEdgeOverhang
    ////    kEdgeJitter
    ////    kEdgeSilhouetteWidth
    ////    kEdgeHaloGap
    ////    kEdgeIsolines
    ////    kDisplayStyle
    ////    kDisplayShadowType
    /// </param>                               
    /// <param name="nVal">
    /// Input integer property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// // Set lighting model to kGooch
    /// using namespace AcGiVisualStyleProperties;
    /// acgiVisualStyle.setTrait (kFaceLightingModel, kGooch);
    ///
    /// // Set halogap to 20
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeHaloGap, 20);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                               int nVal,
                               AcGiVisualStyleOperations::Operation op
                               = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a boolean property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kEdgeHidePrecision
    /// </param>                               
    /// <param name="bVal">
    /// Input boolean property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// // Set hide precision to false
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeHidePrecision, false);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                               bool bVal,
                               AcGiVisualStyleOperations::Operation op
                               = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a double property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceOpacity
    ////    kFaceSpecular
    ////    kEdgeCreaseAngle
    ////    kEdgeOpacity
    ////    kDisplayBrightness
    /// </param>                               
    /// <param name="dVal">
    /// Input double property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// // Set brightness to 1.0
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kDisplayBrightness, 1.0);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                              double dVal,
                              AcGiVisualStyleOperations::Operation op
                              = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a color property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceMonoColor
    ////    kEdgeIntersectionColor
    ////    kEdgeObscuredColor
    ////    kEdgeColor
    ////    kEdgeSilhouetteColor
    /// </param>
    /// <param name="red">
    /// Input red color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="green">
    /// Input green color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="blue">
    /// Input blue color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// // Set edge intersection color to 110% red
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeIntersectionColor, 1.1, 1.0, 1.0);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                               double red,
                               double green,
                               double blue,
                               AcGiVisualStyleOperations::Operation op
                               = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a color property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceMonoColor
    ////    kEdgeIntersectionColor
    ////    kEdgeObscuredColor
    ////    kEdgeColor
    ////    kEdgeSilhouetteColor
    /// </param>
    /// <param name="pColor">
    /// Input AcCmColor property value to set into the visual style.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// // Set monoColor to white
    /// AcCmColor monoColor;
    /// monoColor.setRGB(255,255,255);
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kFaceMonoColor, &monoColor);
    ///
    /// </example>
    Acad::ErrorStatus setTrait(AcGiVisualStyleProperties::Property prop, 
                               const AcCmColor *pColor,
                               AcGiVisualStyleOperations::Operation op
                               = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Gets a property of the visual style.  
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to get from the visual style.
    /// </param>                               
    /// <param name="pOp">
    /// Output AcGiVisualStyleOperations::Operation to get the operation currently in effect for this property.  If NULL, nothing is returned.
    /// </param>                               
    /// <returns>
    /// Returns the AcGiVariant value of the property if successful; otherwise,
    /// returns an AcGiVariant of type AcGiVariant::kUndefined.
    /// </returns>   
    /// <example>
    ///
    /// AcGiVariant displayBrightness = 
    ///     acgiVisualStyle.trait (AcGiVisualStyleProperties::kDisplayBrightness);
    ///
    /// </example>
    const AcGiVariant& trait(AcGiVisualStyleProperties::Property prop, 
                             AcGiVisualStyleOperations::Operation *pOp = NULL) const;

    /// <summary>
    /// Sets a property flag into the visual style, for properties which are bitfield enums.
    /// </summary>
    /// <param name="flagProp">
    /// Input bitfield enum AcGiVisualStyleProperties::Property to set into the visual style.
    /// </param>                               
    /// <param name="flagVal">
    /// Input bit flag enum unsigned long property to set into the visual style.
    /// </param>                               
    /// <param name="bEnable">
    /// Input bool set to true to enable the flag, false to disable. 
    /// </param>    
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// acgiVisualStyle.setTraitFlag (AcGiVisualStyleProperties::kEdgeModifier, 
    ///                               AcGiVisualStyle::kJitter,
    ///                               true);
    ///
    /// </example>
    Acad::ErrorStatus setTraitFlag(AcGiVisualStyleProperties::Property flagProp,
                                   unsigned long flagVal,
                                   bool bEnable = true);

    /// <summary>
    /// Gets a property flag from the visual style, for properties which are bitfield enums.
    /// </summary>
    /// <param name="flagProp">
    /// Input bitfield enum AcGiVisualStyleProperties::Property to get from the visual style.
    /// </param>                               
    /// <param name="flagVal">
    /// Input bit flag enum unsigned long property to get from the visual style.
    /// </param>                               
    /// <returns>
    /// Returns true if flag is enabled, false otherwise. 
    /// </returns>    
    /// <example>
    ///
    /// bool bJitterEnabled = 
    ///     acgiVisualStyle.traitFlag(AcGiVisualStyleProperties::kEdgeModifier, 
    ///                               AcGiVisualStyle::kJitter);
    ///
    /// </example>
    bool traitFlag(AcGiVisualStyleProperties::Property flagProp,
                   unsigned long flagVal) const;

    // AcDbObject protocol
    //
    /// <summary>
    /// Files in the visual style properties from a .dwg format file.
    /// </summary>
    /// <param name="pFiler">
    /// Input AcDbDwgFiler* pointer to the .dwg file filer.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus value of Acad::eOk if successful,
    /// otherwise an error status return indicating type of failure.
    /// </returns>
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    /// <summary>
    /// Files out the visual style properties to a .dwg format file.
    /// </summary>
    /// <param name="pFiler">
    /// Input AcDbDwgFiler* pointer to the .dwg file filer.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus value of Acad::eOk if successful,
    /// otherwise an error status return indicating type of failure.
    /// </returns>
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    /// <summary>
    /// Files in the visual style properties from a .dxf format file.
    /// </summary>
    /// <param name="pFiler">
    /// Input AcDbDxfFiler* pointer to the .dxf file filer.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus value of Acad::eOk if successful,
    /// otherwise an error status return indicating type of failure.
    /// </returns>
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    /// <summary>
    /// Files out the visual style properties to a .dxf format file.
    /// </summary>
    /// <param name="pFiler">
    /// Input AcDbDxfFiler* pointer to the .dxf file filer.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus value of Acad::eOk if successful,
    /// otherwise an error status return indicating type of failure.
    /// </returns>
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    // AcGiDrawable protocol
    //
    /// <summary>
    /// Returns a pointer to this visual style object.
    /// </summary>
    /// <returns>
    /// Returns AcGiDrawable* pointer to this object.
    /// </returns>
    virtual AcGiDrawable*     drawable     (void);

    /// <summary>
    /// Sets the GsNode associated with this object.
    /// </summary>
    /// <param name="pNode">
    /// Input AcGsNode* pointer to the GsNode to associate with this
    /// object.
    /// </param>
    virtual void              setGsNode    (AcGsNode* pNode);
    /// <summary>
    /// Returns a pointer to the GsNode associated with this object.
    /// </summary>
    /// <returns>
    /// Returns AcGsNode* pointer to the GsNode associated with this object.
    /// </returns>
    virtual AcGsNode*         gsNode       (void) const;
    /// <summary>
    /// Reports whether this visual style is for internal use only
    /// </summary>
    /// <returns>
    /// Returns boolean indicating whether this visual style is for
    /// internal use only and will not be exposed in any UI.
    /// </returns>
    virtual bool              isInternalUseOnly() const;
    /// <summary>
    /// Sets a flag indicating that this visual style is for internal use
    /// only and will not be exposed in any UI.
    /// </summary>
    /// <param name="bInternalUseOnly">
    /// Input boolean indicating this visual style is for internal use only.
    /// </param>
    virtual void              setInternalUseOnly(bool bInternalUseOnly);

    // Utility functions to map between AcDbVisualStyle and AcGiVisualStyle
    /// <summary>
    /// Copies this visual style to the given destination visual style.
    /// </summary>
    /// <param name="pDest">
    /// Input AcGiVisualStyle* pointer to the desination visual style.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus Acad::eOk for success, otherwise an error
    /// return value Acad::eInvalidInput if the parameter passed is null.
    /// </returns>
    virtual Acad::ErrorStatus copyTo(AcGiVisualStyle * pDest) const;
    /// <summary>
    /// Copies the given visual style to this visual style.
    /// </summary>
    /// <param name="pSrc">
    /// Input AcGiVisualStyle* pointer to the visual style to copy from.
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus Acad::eOk for success, otherwise an error
    /// return value Acad::eInvalidInput if the parameter passed is null.
    /// </returns>
    virtual Acad::ErrorStatus copyFrom(const AcGiVisualStyle * pSrc);
    /// <summary>
    /// Prepares the visual style for saving to previous AutoCAD versions.
    /// </summary>
    /// <param name="ver">
    /// Drawing version to which the visual style is being saved.
    /// </param>
    /// <param name="replaceObj">
    /// 
    /// </param>
    /// <param name="replaceId">
    /// 
    /// </param>
    /// <param name="exchangeXData">
    /// 
    /// </param>
    /// <returns>
    /// Returns Acad::ErrorStatus Acad::eOk for success, otherwise an error
    /// return value.
    /// </returns>
    virtual Acad::ErrorStatus decomposeForSave(
                                  AcDb::AcDbDwgVersion ver,
                                  AcDbObject*&         replaceObj,
                                  AcDbObjectId&        replaceId,
                                  Adesk::Boolean&      exchangeXData);

protected:
};

#pragma pack (pop)


