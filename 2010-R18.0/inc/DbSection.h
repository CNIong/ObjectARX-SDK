//////////////////////////////////////////////////////////////////////////////
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
// 
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            DbSection.h
//
// Description:     Header for AcDbSection class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"
#include "dbhatch.h"
#include "acstring.h"


class AcDbSectionSettings;


//*************************************************************************
// AcDbSection
//*************************************************************************

class AcDbSection : public AcDbEntity
{
public:
    enum State
    {
        kPlane              = (0x1 << 0),
        kBoundary           = (0x1 << 1),
        kVolume             = (0x1 << 2),
    };

    enum SubItem
    {
        kNone               = 0,
        kSectionLine        = (0x1 << 0),
        kSectionLineTop     = (0x1 << 1),
        kSectionLineBottom  = (0x1 << 2),
        kBackLine           = (0x1 << 3),
        kBackLineTop        = (0x1 << 4),
        kBackLineBottom     = (0x1 << 5),
        kVerticalLineTop    = (0x1 << 6),
        kVerticalLineBottom = (0x1 << 7),
    };

    enum Height
    {
        kHeightAboveSectionLine = 0x1,
        kHeightBelowSectionLine = 0x2,
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbSection);

    ACDB_PORT AcDbSection(void);
    ACDB_PORT AcDbSection(const AcGePoint3dArray& pts,
        const AcGeVector3d& verticalDir);
    ACDB_PORT AcDbSection(const AcGePoint3dArray& pts,
        const AcGeVector3d& verticalDir, const AcGeVector3d& vecViewingDir);
    ACDB_PORT ~AcDbSection(void);

    ACDB_PORT AcDbSection::State state      (void) const;
    ACDB_PORT Acad::ErrorStatus setState    (AcDbSection::State nState);

    ACDB_PORT const ACHAR* getName          (void) const;
    ACDB_PORT Acad::ErrorStatus getName     (AcString& sName) const;
    ACDB_PORT Acad::ErrorStatus getName     (ACHAR*& pszName) const;
    ACDB_PORT Acad::ErrorStatus setName     (const ACHAR* pszName);

    ACDB_PORT AcGeVector3d viewingDirection (void) const;
    ACDB_PORT Acad::ErrorStatus setViewingDirection(const AcGeVector3d& dir);

    ACDB_PORT AcGeVector3d verticalDirection(void) const;
    ACDB_PORT Acad::ErrorStatus setVerticalDirection(const AcGeVector3d& dir);

    ACDB_PORT AcGeVector3d normal           (void) const;
    ACDB_PORT Acad::ErrorStatus plane       (AcGeVector3d& uAxis, 
                                             AcGeVector3d& vAxis) const;

    ACDB_PORT int   indicatorTransparency   (void) const;
    ACDB_PORT Acad::ErrorStatus setIndicatorTransparency(int nTransparency);

    ACDB_PORT AcCmColor indicatorFillColor  (void) const;
    ACDB_PORT Acad::ErrorStatus setIndicatorFillColor(const AcCmColor& color);

    ACDB_PORT int numVertices               (void) const;
    ACDB_PORT Acad::ErrorStatus getVertex   (int nIndex, 
                                             AcGePoint3d& pt) const;
    ACDB_PORT Acad::ErrorStatus setVertex   (int nIndex, 
                                             const AcGePoint3d& pt);
    ACDB_PORT Acad::ErrorStatus addVertex   (int nInsertAt, 
                                             const AcGePoint3d& pt);
    ACDB_PORT Acad::ErrorStatus removeVertex(int nIndex);
    ACDB_PORT Acad::ErrorStatus getVertices (AcGePoint3dArray& pts) const;
    ACDB_PORT Acad::ErrorStatus setVertices (const AcGePoint3dArray& pts);

    ACDB_PORT double height                 (AcDbSection::Height nHeightType) const;
    ACDB_PORT Acad::ErrorStatus setHeight   (AcDbSection::Height nHeightType, 
                                             double fHeight);

    ACDB_PORT bool  hitTest                 (const AcGePoint3d& ptHit, 
                                             int* pSegmentIndex, 
                                             AcGePoint3d* ptOnSegment, 
                                             AcDbSection::SubItem* pSubItem) const;

    ACDB_PORT Acad::ErrorStatus createJog   (const AcGePoint3d& ptOnSection);

    ACDB_PORT AcDbObjectId getSettings      (void) const;
    ACDB_PORT Acad::ErrorStatus getSettings (AcDbSectionSettings*& pSettings, 
                                             AcDb::OpenMode mode) const;

    ACDB_PORT bool  isLiveSectionEnabled    (void) const;
    ACDB_PORT Acad::ErrorStatus enableLiveSection(bool bEnable);

    ACDB_PORT Acad::ErrorStatus generateSectionGeometry (AcDbEntity *pEnt,
                                AcArray<AcDbEntity*>& intBoundaryEnts,
                                AcArray<AcDbEntity*>& intFillEnts,
                                AcArray<AcDbEntity*>& backgroundEnts,
                                AcArray<AcDbEntity*>& foregroundEnts,
                                AcArray<AcDbEntity*>& curveTangencyEnts) const;
    
public:
    // Base class overrides
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus subClose();


    // INTERNAL USE ONLY
    ACDB_PORT Acad::ErrorStatus generateSectionGeometry (const AcArray<AcDbEntity*>& entset,
                                AcArray<AcDbEntity*>& intBoundaryEnts,
                                AcArray<AcDbEntity*>& intFillEnts,
                                AcArray<AcDbEntity*>& backgroundEnts,
                                AcArray<AcDbEntity*>& foregroundEnts,
                                AcArray<AcDbEntity*>& curveTangencyEnts) const;
   
protected:
    ACDB_PORT virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};


//*************************************************************************
// AcDbSectionSettings
//*************************************************************************

class AcDbSectionSettings : public AcDbObject
{
public:
    enum SectionType
    {
        // Section types
        kLiveSection                = (0x1 << 0),       // Live section
        k2dSection                  = (0x1 << 1),       // 2d section
        k3dSection                  = (0x1 << 2),       // 3d section
    };

    enum Geometry
    {
        // Geometry type
        kIntersectionBoundary       = (0x1 << 0),       // Intesection boundary
        kIntersectionFill           = (0x1 << 1),       // Intesection fill
        kBackgroundGeometry         = (0x1 << 2),       // Background geometry
        kForegroundGeometry         = (0x1 << 3),       // Foreground geometry
        kCurveTangencyLines         = (0x1 << 4),       // Curve tangency lines
    };

    enum Generation
    {
        // Source geometry options (bits 0 to 3)
        kSourceAllObjects           = (0x1 << 0),       // Include all objects
        kSourceSelectedObjects      = (0x1 << 1),       // Include selected objects

        // Destination options (bits 4 to 8)
        kDestinationNewBlock        = (0x1 << 4),       // Insert as new block
        kDestinationReplaceBlock    = (0x1 << 5),       // Replace existing block
        kDestinationFile            = (0x1 << 6),       // Export to a file
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbSectionSettings);

    AcDbSectionSettings();
    ~AcDbSectionSettings();

    ACDB_PORT Acad::ErrorStatus reset(void);
    ACDB_PORT Acad::ErrorStatus reset(AcDbSectionSettings::SectionType nSecType);

    ACDB_PORT AcDbSectionSettings::SectionType currentSectionType(void) const;
    ACDB_PORT Acad::ErrorStatus setCurrentSectionType(AcDbSectionSettings::SectionType nSecType);

    ACDB_PORT AcDbSectionSettings::Generation generationOptions(AcDbSectionSettings::SectionType nSecType) const;
    ACDB_PORT Acad::ErrorStatus setGenerationOptions(AcDbSectionSettings::SectionType nSecType,
        AcDbSectionSettings::Generation nOptions);

    ACDB_PORT Acad::ErrorStatus getSourceObjects(AcDbSectionSettings::SectionType nSecType,
        AcDbObjectIdArray& ids) const;
    ACDB_PORT Acad::ErrorStatus setSourceObjects(AcDbSectionSettings::SectionType nSecType,
        const AcDbObjectIdArray& ids);
    
    ACDB_PORT AcDbObjectId destinationBlock(AcDbSectionSettings::SectionType nSecType) const;
    ACDB_PORT Acad::ErrorStatus setDestinationBlock(AcDbSectionSettings::SectionType nSecType,
        const AcDbObjectId& id);

    ACDB_PORT const ACHAR* destinationFile(AcDbSectionSettings::SectionType nSecType) const;
    ACDB_PORT Acad::ErrorStatus setDestinationFile(AcDbSectionSettings::SectionType nSecType,
        const ACHAR* pszFileName);

    ACDB_PORT bool  visibility              (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setVisibility(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bVisible);
    ACDB_PORT AcCmColor color               (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setColor    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const AcCmColor& color);
    ACDB_PORT const ACHAR* layer            (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setLayer    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszLayer);
    ACDB_PORT const ACHAR* linetype         (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setLinetype (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszLinetype);
    ACDB_PORT double linetypeScale          (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setLinetypeScale(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fScale);
    ACDB_PORT const ACHAR* plotStyleName    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setPlotStyleName(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszPlotStyleName);
    ACDB_PORT AcDb::LineWeight lineWeight   (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setLineWeight(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDb::LineWeight nLineWeight);
    ACDB_PORT int   faceTransparency        (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setFaceTransparency(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             int nTransparency);
    ACDB_PORT int   edgeTransparency        (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setEdgeTransparency(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             int nTransparency);
    ACDB_PORT bool  hatchVisibility         (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setHatchVisibility(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bVisible);
    ACDB_PORT Acad::ErrorStatus getHatchPattern(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDbHatch::HatchPatternType& nPatternType, 
                                             const ACHAR*& pszPatternName) const;
    ACDB_PORT Acad::ErrorStatus setHatchPattern(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDbHatch::HatchPatternType nPatternType, 
                                             const ACHAR* pszPatternName);
    ACDB_PORT double hatchAngle             (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setHatchAngle(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fAngle);
    ACDB_PORT double hatchSpacing           (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setHatchSpacing(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fSpacing);
    ACDB_PORT double hatchScale             (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setHatchScale(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fScale);
    ACDB_PORT bool  hiddenLine              (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setHiddenLine(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bHiddenLine);
    ACDB_PORT bool  divisionLines           (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    ACDB_PORT Acad::ErrorStatus setDivisionLines(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bShow);

protected:
    ACDB_PORT virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};
