//

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

    /// <summary>
    /// Sets the AcGiFaceStyle of the visual style.
    /// </summary>
    /// <param name="faceStyle">
    /// Input AcGiFaceStyle const reference to the collection of properties
    /// pertaining to drawable faces.
    /// </param>
    void setFaceStyle(const AcGiFaceStyle& faceStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to faces.
    /// </summary>
    /// <returns>
    /// Returns AcGiFaceStyle const reference to the collection of 
    /// properties that are applied to faces.
    /// </returns>
    const AcGiFaceStyle& faceStyle() const;
    
    /// <summary>
    /// Sets the AcGiEdgeStyle of the visual style.
    /// </summary>
    /// <param name="edgeStyle">
    /// Input AcGiEdgeStyle const reference to the collection of properties
    /// pertaining to drawable edges.
    /// </param>
    void setEdgeStyle(const AcGiEdgeStyle& edgeStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to edges.
    /// </summary>
    /// <returns>
    /// Returns AcGiEdgeStyle const reference to the collection of 
    /// properties that are applied to edges.
    /// </returns>
    const AcGiEdgeStyle& edgeStyle() const;

    /// <summary>
    /// Sets the AcGiDisplayStyle of the visual style.
    /// </summary>
    /// <param name="displayStyle">
    /// Input AcGiDisplayStyle const reference to the collection of properties
    /// pertaining to the display.
    /// </param>
    Acad::ErrorStatus setDisplayStyle(const AcGiDisplayStyle& displayStyle);
    /// <summary>
    /// Reports the collection of properties that are applied to the display.
    /// </summary>
    /// <returns>
    /// Returns AcGiDisplayStyle const reference to the collection of 
    /// properties that are applied to the display.
    /// </returns>
    const AcGiDisplayStyle& displayStyle() const;

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
    /// Sets the given AcGiDrawableTraits object with the attributes
    /// of this visual style.
    /// </summary>
    /// <param name="pTraits">
    /// Input AcGiDrawableTraits* pointer to properties of this object. 
    /// This is called by the GS to setup the visual style node for this
    /// visual style.
    /// </param>
    /// <returns>
    /// Returns Adesk::UInt32 status code AcGiDrawable::kDrawableNone if
    /// successful, or AcGiDrawable::kDrawableIsInvisible if the given
    /// AcGiDrawableTraits could not be cast to a visual style.
    /// </returns>
    virtual Adesk::UInt32     setAttributes (AcGiDrawableTraits* pTraits);
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

};

#pragma pack (pop)


