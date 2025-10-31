#ifndef __DBMLEADER_H__
#define __DBMLEADER_H__

#pragma once

//
//  (C) Copyright 2006-2007 by Autodesk, Inc.  All rights reserved.
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

#include <dbgrip.h>
#include "dbmleaderstyle.h"
#include "dbents.h"

const int MAX_LEADER_NUMBER     = 5000;
const int MAX_LEADERLINE_NUMBER = 5000;

class AcDbMLeaderObjectContextData;

////////////////////////////////////////////////////////////////////////
// class AcDbMLeader
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class is the main class used for the multiple leader object. 
/// </summary>
///
/// <remarks>
/// </remarks>
///

class AcDbMLeader : public AcDbEntity
{
public:
    /// <summary>
    /// This enum is the move type use for move mleader object.
    /// </summary>
    ///
    enum MoveType {
        /// <summary>
        /// move all mleader points
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kMoveAllPoints                  = 0,
        /// <summary>
        /// move all mleader points except leaderline's arrowhead points
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kMoveAllExceptArrowHeaderPoints = 1,
        /// <summary>
        /// move dogleg and mleader content points
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kMoveContentAndDoglegPoints     = 2
    };

    /// <summary>
    /// This enum is the gs mark of mleader object.
    /// </summary>
    ///
    enum gsMarkType {
        /// <summary>
        /// Null gs mark.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kNone               = 0,
        /// <summary>
        /// arrow symbol gs mark.
        /// </summary>
        ///
        /// <value>
        /// from 1 to MAX_LEADERLINE_NUMBER
        /// </value>
        kArrowMark          = 1,
        /// <summary>
        /// leaderLine gs mark.
        /// </summary>
        ///
        /// <value>
        /// from kArrowMark  + MAX_LEADERLINE_NUMBER to MAX_LEADERLINE_NUMBER
        /// </value>
        kLeaderLineMark     = kArrowMark  + MAX_LEADERLINE_NUMBER,
        /// <summary>
        /// dogleg gs mark.
        /// </summary>
        ///
        /// <value>
        /// from kLeaderLineMark + MAX_LEADERLINE_NUMBE to MAX_LEADER_NUMBER
        /// </value>
        kDoglegMark         = kLeaderLineMark + MAX_LEADERLINE_NUMBER,
        /// <summary>
        /// mtext content gs mark.
        /// </summary>
        ///
        /// <value>
        /// kDoglegMark + MAX_LEADER_NUMBER
        /// </value>
        kMTextMark          = kDoglegMark + MAX_LEADER_NUMBER,
        /// <summary>
        /// mtext underline content gs mark, include text frame if mleader has.
        /// </summary>
        ///
        /// <value>
        /// kMTextMark + 1
        /// </value>
        kMTextUnderLineMark = kMTextMark + 1,
        /// <summary>
        /// Tolerance content gs mark
        /// </summary>
        ///
        /// <value>
        /// kMTextUnderLineMark + 1
        /// </value>
        kToleranceMark      = kMTextUnderLineMark + 1,
        /// <summary>
        /// Block content gs mark
        /// </summary>
        ///
        /// <value>
        /// kToleranceMark + 1
        /// </value>
        kBlockMark          = kToleranceMark + 1,
        /// <summary>
        /// BlockAttribute content gs mark
        /// </summary>
        ///
        /// <value>
        /// from kBlockMark + 1 to 2^(8*sizeof(unsigned short))
        /// </value>
        kBlockAttribute     = kBlockMark + 1
    };

    /// <summary>
    /// This enum is the properties could be overrided in mleader object.
    /// </summary>
    ///
    enum PropertyOverrideType {
        /// <summary>
        /// type of leaderLine
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kLeaderLineType         = 0,
        /// <summary>
        /// color of leaderLine
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kLeaderLineColor        = 1,
        /// <summary>
        /// line type id of leaderLine
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kLeaderLineTypeId       = 2,
        /// <summary>
        /// line weight id of leaderLine
        /// </summary>
        ///
        /// <value>
        /// 3
        /// </value>
        kLeaderLineWeight       = 3,
        /// <summary>
        /// if enable landing
        /// </summary>
        ///
        /// <value>
        /// 4
        /// </value>
        kEnableLanding          = 4,
        /// <summary>
        /// landing gap
        /// </summary>
        ///
        /// <value>
        /// 5
        /// </value>
        kLandingGap             = 5,
        /// <summary>
        /// if enable dogleg
        /// </summary>
        ///
        /// <value>
        /// 6
        /// </value>
        kEnableDogleg           = 6,
        /// <summary>
        /// dogleg length
        /// </summary>
        ///
        /// <value>
        /// 7
        /// </value>
        kDoglegLength           = 7,
        /// <summary>
        /// block id of arrowSymbol
        /// </summary>
        ///
        /// <value>
        /// 8
        /// </value>
        kArrowSymbolId          = 8,
        /// <summary>
        /// size of arrowSymbol
        /// </summary>
        ///
        /// <value>
        /// 9
        /// </value>
        kArrowSize              = 9,
        /// <summary>
        /// content type of mleader
        /// </summary>
        ///
        /// <value>
        /// 10
        /// </value>
        kContentType            = 10,
        /// <summary>
        /// text style id of mtext content
        /// </summary>
        ///
        /// <value>
        /// 11
        /// </value>
        kTextStyleId            = 11,
        /// <summary>
        /// text left attachment type of mtext content
        /// </summary>
        ///
        /// <value>
        /// 12
        /// </value>
        kTextLeftAttachmentType     = 12,
        /// <summary>
        /// text angle type of mtext content
        /// </summary>
        ///
        /// <value>
        /// 13
        /// </value>
        kTextAngleType          = 13,
        /// <summary>
        /// text alignment type of mtext content
        /// </summary>
        ///
        /// <value>
        /// 14
        /// </value>
        kTextAlignmentType      = 14,
        /// <summary>
        /// text color of mtext content
        /// </summary>
        ///
        /// <value>
        /// 15
        /// </value>
        kTextColor              = 15,
        /// <summary>
        /// text height of mtext content
        /// </summary>
        ///
        /// <value>
        /// 16
        /// </value>
        kTextHeight             = 16,
        /// <summary>
        /// if enable frame text
        /// </summary>
        ///
        /// <value>
        /// 17
        /// </value>
        kEnableFrameText        = 17,
        /// <summary>
        /// if use default mtext defined in mleaderStyle
        /// </summary>
        ///
        /// <value>
        /// 18
        /// </value>
        kDefaultMText           = 18,
        /// <summary>
        /// block table record id of block content
        /// </summary>
        ///
        /// <value>
        /// 19
        /// </value>
        kBlockId                = 19,
        /// <summary>
        /// color of block content
        /// </summary>
        ///
        /// <value>
        /// 20
        /// </value>
        kBlockColor             = 20,
        /// <summary>
        /// scale of block content
        /// </summary>
        ///
        /// <value>
        /// 21
        /// </value>
        kBlockScale             = 21,
        /// <summary>
        /// rotation of block content
        /// </summary>
        ///
        /// <value>
        /// 22
        /// </value>
        kBlockRotation          = 22,
        /// <summary>
        /// connection type of block content
        /// </summary>
        ///
        /// <value>
        /// 23
        /// </value>
        kBlockConnectionType    = 23,
        /// <summary>
        /// scale of mleader
        /// </summary>
        ///
        /// <value>
        /// 24
        /// </value>
        kScale                  = 24,
        /// <summary>
        /// text right attachment type of mtext content
        /// </summary>
        ///
        /// <value>
        /// 25
        /// </value>
        kTextRightAttachmentType = 25,

        /// <summary>
        /// text switch alignment type of mtext content
        /// if set this override, drag grip point of mleader will not changed text alignment type
        /// </summary>
        ///
        /// <value>
        /// 26
        /// </value>
        kTextSwitchAlignmentType = 26,

        //add more here...
        /// <summary>
        /// bitset size
        /// </summary>
        ///
        /// <value>
        /// 27
        /// </value>
        kSize = kTextSwitchAlignmentType + 1
    };

    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default constructor.
    /// </remarks>
    ///
    AcDbMLeader();
    /// <summary>
    /// Default destructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default destructor.
    /// </remarks>
    ///
    ~AcDbMLeader();

    ACDB_DECLARE_MEMBERS(AcDbMLeader);

    /// <summary>
    /// Used to read in an AcDbMLeader's data from a DWG file.
    /// </summary>
    ///
    /// <param name="filer">
    /// Actual filer used to read in an AcDbMLeader's data from a DWG file.
    /// </param>
    ///
    /// <remarks>
    /// Used to read in an AcDbMLeader's data from a DWG file.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* filer);


    /// <summary>
    /// Used to persist the AcDbMLeader's data to a DWG file.
    /// </summary>
    ///
    /// <param name="filer">
    /// Actual filer used to persist the AcDbMLeader's data to a DWG file.
    /// </param>
    ///
    /// <remarks>
    /// Used to persist the AcDbMLeader's data to a DWG file.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    /// <summary>
    /// Used to read in an AcDbMLeader's data from a DXF file.
    /// </summary>
    ///
    /// <param name="filer">
    /// Actual filer used to read in an AcDbMLeader's data from a DXF file.
    /// </param>
    ///
    /// <remarks>
    /// Used to read in an AcDbMLeader's data from a DXF file.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* filer);

    /// <summary>
    /// Used to persist the AcDbMLeader's data to a DXF file.
    /// </summary>
    ///
    /// <param name="filer">
    /// Actual filer used to persist the AcDbMLeader's data to a DXF file.
    /// </param>
    ///
    /// <remarks>
    /// Used to persist the AcDbMLeader's data to a DXF file.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    /// <summary>
    /// Used to generate the graphics primitives that will represent this entity on screen.
    /// </summary>
    ///
    /// <param name="mode">
    /// Input pointer to fully initialized AcGiWorldDraw object.
    /// </param>
    ///
    /// <returns>
    /// If it returns Adesk::kFalse, then AutoCAD calls the viewportDraw() function once for each viewport
    /// that is currently active in the AutoCAD editor.
    /// </returns>
    ///
    virtual Adesk::Boolean    worldDraw   (AcGiWorldDraw* mode);

    /// <summary>
    /// Used to generate the graphics primitives independently for each viewport.
    /// </summary>
    ///
    /// <param name="mode">
    /// Input pointer to fully initialized AcGiViewportDraw object.
    /// </param>
    ///
    /// <remarks>
    /// Used to generate the graphics primitives independently for each viewport.
    /// </remarks>
    ///
    virtual void              viewportDraw(AcGiViewportDraw* mode);

    /// <summary>
    /// Used to apply a transformation matrix to itself.
    /// </summary>
    ///
    /// <param name="xform">
    /// Input transformation matrix to be applied to the entity 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus transformBy (const AcGeMatrix3d& xform);

    /// <summary>
    /// Used to append to the stretchPoints that are to treated as stretch points for the entity.
    /// </summary>
    ///
    /// <param name="stretchPoints">
    /// Input pre-existing array to append the stretch points to;
    /// output with the entity's stretch points appended.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getStretchPoints           (AcGePoint3dArray& stretchPoints) const;

    
    /// <summary>
    /// Used to stretch the entity by stretch points decided by indices.
    /// </summary>
    ///
    /// <param name="indices">
    /// Input array containing index values that indicate which stretch points are being translated 
    /// </param>
    /// <param name="offset">
    /// Input vector (in WCS coordinates) indicating the direction
    /// and magnitude that the stretch points have been translated.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus moveStretchPoints          (const AcDbIntArray& indices,
                                                          const AcGeVector3d& offset);

    /// <summary>
    /// Return the grip information for an MLEADER object
    /// </summary>
    ///
    /// <param name="grips">
    /// Array of pointers to dynamically allocated AnnotationGripAppData objects.
    /// </param>
    /// <param name="curViewUnitSize">
    /// Size, in pixels, of one drawing unit in the current viewport.
    /// </param>
    /// <param name="gripSize">
    /// Current grip size, in pixels.
    /// </param>
    /// <param name="curViewDir">
    /// Vector describing the view direction in the current viewport.
    /// </param>
    /// <param name="bitflags">
    /// Bitmap of one or more flags specified by the GetGripPointsFlags enumeration.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getGripPoints              (AcDbGripDataPtrArray& grips,
                                                          const double curViewUnitSize,
                                                          const int gripSize,
                                                          const AcGeVector3d& curViewDir,
                                                          const int bitflags) const;

    /// <summary>
    /// Move the grip points for an MLEADER object
    /// </summary>
    ///
    /// <param name="gripAppData">
    /// Input array of pointers to be moved, thesse are AnnotationGripAppData objects.
    /// </param>
    /// <param name="offset">
    /// Vector, in WCS coordinates, indicating the direction and magnitude of the translation to be applied
    /// to the grips.
    /// </param>
    /// <param name="bitflags">
    /// Reserved for future use, currently zero.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus moveGripPointsAt           (const AcDbVoidPtrArray& gripAppData,
                                                          const AcGeVector3d& offset,
                                                          const int bitflags);

    /// <summary>
    /// This function uses the gsMark and other information
    ///.to determine which subentPaths within the entity are appropriate
    /// </summary>
    ///
    /// <param name="type">
    /// Input subentity type defined in AcDb::SubentType.
    /// </param>
    /// <param name="gsMark">
    /// Input GS marker representing a specific subentity 
    /// </param>
    /// <param name="pickPoint">
    /// Input point (in WCS coordinates) picked during selection of the entity 
    /// </param>
    /// <param name="viewXform">
    /// Input transformation matrix to transform from WCS to DCS.
    /// </param>
    /// <param name="numPaths">
    /// Output number of AcDbFullSubentPath objects in the subentPaths array.
    /// </param>
    /// <param name="subentPaths">
    /// Output address of a dynamically allocated array of one or more AcDbFullSubentPaths
    /// generated from the GS marker and other information passed into this function.
    /// </param>
    /// <param name="numInserts">
    /// Input number of object IDs for AcDbBlockReferences in entAndInsertStack.
    /// </param>
    /// <param name="entAndInsertStack">
    /// Input array of objectIds of the objects that are the nested containers of the subentity.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getSubentPathsAtGsMarker   (AcDb::SubentType     type, 
                                                          Adesk::GsMarker      gsMark, 
                                                          const AcGePoint3d&   pickPoint, 
                                                          const AcGeMatrix3d&  viewXform, 
                                                          int&                 numPaths, 
                                                          AcDbFullSubentPath*& subentPaths, 
                                                          int                  numInserts = 0, 
                                                          AcDbObjectId*        entAndInsertStack = NULL) const;

    /// <summary>
    /// This function uses the AcDbSubentId object within the subPath object
    ///.to determine which GS markers within the entity are appropriate
    /// </summary>
    ///
    /// <param name="subPath">
    /// Input AcDbFullSubentPath object that contains an AcDbSubentId object
    /// with the information necessary to determine the subentity for which the GS Marker is requested.
    /// </param>
    /// <param name="gsMarkers">
    /// Output array with the GSMarker
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getGsMarkersAtSubentPath   (const AcDbFullSubentPath& subPath,
                                                          AcArray<Adesk::GsMarker>& gsMarkers) const;

    /// <summary>
    /// Returns grip information about a subentity on MLeader object
    /// </summary>
    ///
    /// <param name="path">
    /// Input the AcDbFullSubentPath to the subentity.
    /// </param>
    /// <param name="grips">
    /// Output an array of pointers to dynamically allocated AnnotationGripAppData objects,
    /// one for each grip point in the subentity
    /// </param>
    /// <param name="curViewUnitSize">
    /// Input size, in pixels, of one drawing unit in the current viewport.
    /// </param>
    /// <param name="gripSize">
    /// Input current grip size, in pixels.
    /// </param>
    /// <param name="curViewDir">
    /// Input vector describing the view direction in the current viewport.
    /// </param>
    /// <param name="bitflags">
    /// Input bitmap of one or more flags specified by the GetGripPointsFlags enumeration.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getGripPointsAtSubentPath  (const AcDbFullSubentPath& path,
                                                          AcDbGripDataPtrArray& grips,
                                                          const double curViewUnitSize,
                                                          const int gripSize,
                                                          const AcGeVector3d& curViewDir,
                                                          const int bitflags) const;

    /// <summary>
    /// Moves grip points for a subentity on MLeader object
    /// </summary>
    ///
    /// <param name="path">
    /// Input an array of one or more AcDbFullSubentPath objects exposing the grips to move.
    /// </param>
    /// <param name="gripAppData">
    /// Input an array of pointers, one for each grip point to be moved;
    /// these are the appData pointers from the AnnotationGripAppData objects for the grip points to be moved
    /// </param>
    /// <param name="offset">
    /// Input the vector, in WCS coordinates, indicating the direction and magnitude
    /// of the translation to be applied to the grips
    /// </param>
    /// <param name="bitflags">
    /// Reserved for future use; currently zero.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus moveGripPointsAtSubentPaths(const AcDbFullSubentPathArray& paths,
                                                          const AcDbVoidPtrArray& gripAppData,
                                                          const AcGeVector3d& offset,
                                                          const int bitflags);

    /// <summary>
    /// Deletes one or more subentities from an entity.
    /// </summary>
    ///
    /// <param name="path">
    /// Input an array of AcDbFullSubentPath identifiers to delete from the entity.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus deleteSubentPaths          (const AcDbFullSubentPathArray& paths);

    /// <summary>
    /// Gets copy of entity determined by AcDbFullSubentPath.
    /// </summary>
    ///
    /// <param name="path">
    /// Input AcDbFullSubentPath that identifies the subentity to be copied.
    /// </param>
    ///
    /// <returns>
    /// If the function succeeds then a pointer to the resulting copy is returned,
    /// otherwise NULL is returned.
    /// </returns>
    ///
    virtual AcDbEntity*       subentPtr                  (const AcDbFullSubentPath& path) const;

    /// <summary>
    /// Appends all osnap points determined by input parameters to snapPoints.
    /// </summary>
    ///
    /// <param name="osnapMode">
    /// Input osnap mode being requested.
    /// </param>
    /// <param name="gsSelectionMark">
    /// Input GS marker of the subentity involved in the object snap operation.
    /// </param>
    /// <param name="pickPoint">
    /// Input point (in WCS coordinates) picked during the object snap operation.
    /// </param>
    /// <param name="lastPoint">
    /// Input point (in WCS coordinates) selected just before pickPoint.
    /// </param>
    /// <param name="viewXform">
    /// Input transformation matrix to transform from WCS to DCS.
    /// </param>
    /// <param name="snapPoints">
    /// Input pre-existing array to append osnap points to (may already contain points);
    /// output with object snap points appended.
    /// </param>
    /// <param name="geomIds">
    /// Not in use.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getOsnapPoints             (AcDb::OsnapMode     osnapMode,
                                                          Adesk::GsMarker     gsSelectionMark,
                                                          const AcGePoint3d&  pickPoint,
                                                          const AcGePoint3d&  lastPoint,
                                                          const AcGeMatrix3d& viewXform,
                                                          AcGePoint3dArray&   snapPoints,
                                                          AcDbIntArray&       geomIds) const;

    /// <summary>
    /// Appends all points pEnt intersected with this mleader to points. All the points are in projPlane.
    /// </summary>
    ///
    /// <param name="pEnt">
    /// Input entity with which "this" entity is to intersect.
    /// </param>
    /// <param name="intType">
    /// Input type of intersection requested, it defined in AcDb::Intersect.
    /// </param>
    /// <param name="projPlane">
    /// Input projection plane for the apparent intersection of the two entities.
    /// </param>
    /// <param name="points">
    /// Output with the points of intersection appended.
    /// </param>
    /// <param name="thisGsMarker">
    /// Input GS marker of subentity of "this" entity that's involved in the intersection operation.
    /// Use the 0 default if not applicable.
    /// </param>
    /// <param name="otherGsMarker">
    /// Input GS marker of subentity of the entity pointed to by pEnt
    /// that's involved in the intersection operation.
    /// Use the 0 default if not applicable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus intersectWith              (const AcDbEntity* pEnt,
                                                          AcDb::Intersect intType,
                                                          const AcGePlane& projPlane,
                                                          AcGePoint3dArray& points,
                                                          Adesk::GsMarker thisGsMarker = 0,
                                                          Adesk::GsMarker otherGsMarker = 0) const;

    /// <summary>
    /// Appends all points pEnt intersected with this mleader to points.
    /// </summary>
    ///
    /// <param name="pEnt">
    /// Input entity with which "this" entity is to intersect.
    /// </param>
    /// <param name="intType">
    /// Input type of intersection requested, it defined in AcDb::Intersect.
    /// </param>
    /// <param name="points">
    /// Output with the points of intersection appended.
    /// </param>
    /// <param name="thisGsMarker">
    /// Input GS marker of subentity of "this" entity that's involved in the intersection operation.
    /// Use the 0 default if not applicable.
    /// </param>
    /// <param name="otherGsMarker">
    /// Input GS marker of subentity of the entity pointed to by pEnt
    /// that's involved in the intersection operation.
    /// Use the 0 default if not applicable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus intersectWith              (const AcDbEntity* pEnt,
                                                          AcDb::Intersect intType,
                                                          AcGePoint3dArray& points,
                                                          Adesk::GsMarker thisGsMarker = 0,
                                                          Adesk::GsMarker otherGsMarker = 0) const;

    /// <summary>
    /// Obtains an array of pointers to non-database-resident mleader sub entities.
    /// </summary>
    ///
    /// <param name="entitySet">
    /// Input array to contain pointers to new entities;
    /// this array may already contain pointers from other entities explode() methods;
    /// output with all entities that result from exploding this entity, appended to the array.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus explode                     (AcDbVoidPtrArray& entitySet) const;

    /// <summary>
    /// Prints entity specific information to the AutoCAD command line..
    /// </summary>
    ///
    virtual void              list                        () const;

    /// <summary>
    /// Gets the extents of this mleader object.
    /// </summary>
    ///
    /// <param name="extents">
    /// Output mleader's extents.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getGeomExtents              (AcDbExtents& extents) const;

    /// <summary>
    /// Called from within close() before anything else is done.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus subClose                    ();

    /// <summary>
    /// Called from within erase() before anything else is done.
    /// </summary>
    ///
    /// <param name="erasing">
    /// Passed in copy of the erasing argument that was passed into the erase() function call
    /// that triggered this subErase() call.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus subErase                    (Adesk::Boolean erasing);

    /// <summary>
    /// Called whenever the object sending notification was closed.
    /// </summary>
    ///
    /// <param name="dbObjId">
    /// Passed in objectId of the object sending the notification.
    /// </param>
    ///
    virtual void              objectClosed                (const AcDbObjectId dbObjId);

    /// <summary>
    /// Called whenever the object sending notification has been modified and the object is being closed.
    /// </summary>
    ///
    /// <param name="dbObj">
    /// Passed in pointer to object which has been modified.
    /// </param>
    ///
    virtual void              modified                    (const AcDbObject* dbObj);

    /// <summary>
    /// Gets corresponding COM wrapper class ID.
    /// </summary>
    ///
    /// <param name="pClsid">
    /// OutPut corresponding COM wrapper class ID.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getClassID                  (CLSID* pClsid) const;

    /// <summary>
    /// Gets UCS of input grip point.
    /// </summary>
    ///
    /// <param name="pGripAppData">
    /// Input grip point, it from GripAppData.
    /// </param>
    /// <param name="normalVec">
    /// OutPut UCS's normal.
    /// </param>
    /// <param name="origin">
    /// OutPut UCS's origin point.
    /// </param>
    /// <param name="xAxis">
    /// OutPut UCS's x axis.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getGripEntityUCS            (const void* pGripAppData,
                                                           AcGeVector3d& normalVec,
                                                           AcGePoint3d& origin,
                                                           AcGeVector3d& xAxis) const;

    /// <summary>
    /// Called with a status value of kGripsToBeDeleted
    /// when the grips for the entity are about to be deleted in the host application.
    /// </summary>
    ///
    /// <param name="status">
    /// Value describing the status of the grip operation;
    /// one of the values from the GripStatus enumeration.
    /// </param>
    ///
    virtual void              gripStatus                  (const AcDb::GripStat status);

    /// <summary>
    /// Highlights the subentity determined by subId.
    /// If no AcDbFullSubentPath argument is provided, then the entire entity will be highlighted.
    /// </summary>
    ///
    /// <param name="subId">
    /// Input AcDbFullSubentPath that identifies the subentity to highlight.
    /// </param>
    /// <param name="highlightAll">
    /// Input Boolean indicating whether to highlight in all viewports.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus highlight                   (const AcDbFullSubentPath& subId = kNullSubent,
                                                           const Adesk::Boolean highlightAll = false) const;

    /// <summary>
    /// Unhighlight the subentity determined by subId.
    /// If no AcDbFullSubentPath argument is provided, then the entire entity will be unhighlight.
    /// </summary>
    ///
    /// <param name="subId">
    /// Input AcDbFullSubentPath that identifies the subentity to unhighlight.
    /// </param>
    /// <param name="highlightAll">
    /// Input Boolean indicating whether to unhighlight in all viewports.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus unhighlight                 (const AcDbFullSubentPath& subId = kNullSubent,
                                                           const Adesk::Boolean highlightAll = false) const;

    /// <summary>
    /// This function creates a clone of the entity, applies the xform transformation matrix to the clone, 
    /// and then returns with pEnt pointing to the transformed clone.
    /// </summary>
    ///
    /// <param name="xform">
    /// Input matrix by which to transform the copy of the entity.
    /// </param>
    /// <param name="pEnt">
    /// Input reference to an "empty" pointer; output pointing to the transformed copy of the entity.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus getTransformedCopy          (const AcGeMatrix3d& xform,
                                                           AcDbEntity*& pEnt) const;

    /// <summary>
    /// Sets input propertyType is override or not.
    /// </summary>
    ///
    /// <param name="propertyType">
    /// Input PropertyOverrideType which will be set.
    /// </param>
    /// <param name="isOverride">
    /// Input bool indicate whether overrided or not.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus         setOverride                 (PropertyOverrideType propertyType,
                                                           bool isOverride = true);

    /// <summary>
    /// Test if the propertyType has been overrided.
    /// </summary>
    ///
    /// <param name="propertyType">
    /// Input PropertyOverrideType to test if it is overrided.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the input PropertyOverrideType is override by this mleader object.
    /// Otherwise, return false.
    /// </returns>
    ///
    bool                      isOverride                  (PropertyOverrideType propertyType) const;

    /// <summary>
    /// Sets mleader scale, it will affect arrowhead size and content scale.
    /// </summary>
    ///
    /// <param name="scale">
    /// Input scale value.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kScale override.
    /// </remarks>
    ///
    Acad::ErrorStatus         setScale                    (double scale);

    /// <summary>
    /// Gets mleader scale value.
    /// </summary>
    ///
    /// <returns>
    /// Returns mleader scale value.
    /// </returns>
    ///
    double                    scale                       () const;

    /// <summary>
    /// Gets attribute in block content determined by attribute definition id.
    /// </summary>
    ///
    /// <param name="attdefId">
    /// Input attribute definition id.
    /// </param>
    /// <param name="pAtt">
    /// OutPut attribute object determined by attribute definition id.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// Attribute define id is the AcDbAttributeDefinition object id
    /// that is defined in AcDbBlockTableRecord refernced by this mleader object.
    /// The attribute object should be deleted when it is no longer needed.
    /// </remarks>
    /// 
    Acad::ErrorStatus         getBlockAttributeValue(const AcDbObjectId& attdefId,
                                                     AcDbAttribute*& pAtt) const;

    /// <summary>
    /// Set attribute in block content with attribute definition id.
    /// </summary>
    ///
    /// <param name="attdefId">
    /// Input attribute definition id.
    /// </param>
    /// <param name="pAtt">
    /// Iutputs attribute.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus         setBlockAttributeValue(const AcDbObjectId& attdefId,
                                                     const AcDbAttribute* pAtt);

    //todo tobe removed
    Acad::ErrorStatus         getBlockAttributeValue      (const AcDbObjectId& attdefId,
                                                           ACHAR*& value) const;
    Acad::ErrorStatus         setBlockAttributeValue      (const AcDbObjectId& attdefId,
                                                           const ACHAR* value);

    /// <summary>
    /// Gets the WCS plane which the MLeader resides on.
    /// </summary>
    ///
    /// <returns>
    /// Returns the WCS plane which the MLeader resides on.
    /// </returns>
    ///
    AcGePlane         plane               () const;

    /// <summary>
    /// Sets the WCS plane which the MLeader resides on.
    /// </summary>
    ///
    /// <param name="plane">
    /// Input desired plane within which the mleader will reside.
    /// </param>
    ///
    /// <remarks>
    /// Sets the plane that will contain the mleader object.
    /// This leader's data members will be updated to reflect the change of plane.
    /// To do this, a transformation matrix will be created that will translate all points
    /// from the current plane's coordinate system to the new plane's coordinate
    /// system--a projection is not used.
    /// If doesn't set plane, mleader use default AcGePlane::kXYPlane
    /// </remarks>
    ///
    void              setPlane            (const AcGePlane& plane);


    /// <summary>
    /// Gets the normal of the plane which the MLeader resides on.
    /// </summary>
    ///
    /// <returns>
    /// Returns the unit normal vector (in WCS coordinates) of the plane that contains the leader.
    /// </returns>
    ///
    AcGeVector3d      normal              () const;

    /// <summary>
    /// Moves mleader according to input vector.
    /// </summary>
    ///
    /// <param name="vector">
    /// Input vector indicate direction and distance the mleader will be moved.
    /// </param>
    /// <param name="moveType">
    /// Input MoveType indicate how the mleader will be moved. This enumeration define in MoveType.
    /// </param>
    /// <param name="bAutoSwitchDogleg">
    /// Input bool to indicate whether automatically switch leader lines after mleader is moved.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus moveMLeader         (const AcGeVector3d& vector,
                                           MoveType moveType,
                                           bool bAutoSwitchDogleg = true);

    /// <summary>
    /// Gets the extents of content in this mleader object.
    /// </summary>
    ///
    /// <param name="extents">
    /// Output content's extents.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getContentGeomExtents(AcDbExtents& extents) const;

    //todo remove this function
    int               numLeaders          () const;

    /// <summary>
    /// Gets the indexes of leaders.
    /// </summary>
    ///
    /// <param name="leaderIndexes">
    /// Output indexes of leaders.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getLeaderIndexes(AcArray<int>& leaderIndexes) const;

    /// <summary>
    /// Adds a new leader cluster to this AcDbMLeader object. 
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Output the index of added leader cluster.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// A leader cluster is made up by a dog-leg and some leaderLines.
    /// </remarks>
    ///
    Acad::ErrorStatus addLeader           (int& leaderIndex);

    /// <summary>
    /// Removes the leader cluster with specified index.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input the index of the leader to be removed.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// A leader cluster is made up by a dog-leg and some leaderLines.
    /// </remarks>
    ///
    Acad::ErrorStatus removeLeader        (int leaderIndex);

    //todo remove this function
    int               numLeaderLines      () const;

    /// <summary>
    /// Gets the indexes of leaderLines.
    /// </summary>
    ///
    /// <param name="leaderIndexes">
    /// Output indexes of leadersLines.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getLeaderLineIndexes(AcArray<int>& leaderLineIndexes) const;

    /// <summary>
    /// Adds a leaderline to the leader cluster with specified index.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input index of the leader cluster.
    /// </param>
    /// <param name="leaderLineIndex">
    /// Output the index of the added leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// A leaderLine cluster is made up by leaderline segment and arrowhead.
    /// </remarks>
    ///
    Acad::ErrorStatus addLeaderLine       (int leaderIndex, int& leaderLineIndex);

    /// <summary>
    /// Adds a new leader line to this mleader object determined by input point
    /// which will be the first point of new leaderline.
    /// </summary>
    ///
    /// <param name="point">
    /// Input point of the first(head) vertex of the new leader line.
    /// </param>
    /// <param name="leaderLineIndex">
    /// Output the index of added leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// A leaderLine cluster is made up by leaderline segment and arrowhead.
    /// This function can be invoked when the mleader already have a content.
    /// If the input point is on the side of exist leader cluster,
    /// a new leaderline will be added, the new leaderline’s last point have already exist,
    /// the input point will be the first point of the new leaderline.
    /// If no leader cluster exists on the input point side,
    /// a new leader will be added automatically, then add a new leaderline.
    /// </remarks>
    ///
    Acad::ErrorStatus addLeaderLine       (const AcGePoint3d& point, int& leaderLineIndex);

    /// <summary>
    /// Removes the leader line with specified index.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input the index of leaderLine cluster.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// A leaderLine cluster is made up by leaderline segment and arrowhead.
    /// If after remove lieaderine, the leader has no leaderline, the leader will be removed too.
    /// </remarks>
    ///
    Acad::ErrorStatus removeLeaderLine    (int leaderLineIndex);

    /// <summary>
    /// Inserts a vertex to the leader line with specified index as new leader head.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Input the vertex position.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus addFirstVertex      (int leaderLineIndex, const AcGePoint3d& point);

    /// <summary>
    /// Removes the head of the leader line with specified index.
    /// The second vertex in this leader line becomes the new head.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus removeFirstVertex   (int leaderLineIndex);

    /// <summary>
    /// Gets head point of specified leader line.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Output the leaderline head point.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getFirstVertex      (int leaderLineIndex, AcGePoint3d& point) const;

    /// <summary>
    /// Sets the leader head with specified point.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Iutput the leaderline head point.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus setFirstVertex      (int leaderLineIndex, const AcGePoint3d& point);

    /// <summary>
    /// Appends a vertex to the specified leader line as the new leader tail.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Input the vertex position.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus addLastVertex       (int leaderLineIndex, const AcGePoint3d& point);

    /// <summary>
    /// Removes the leader tail of specified leader line.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus removeLastVertex    (int leaderLineIndex);

    /// <summary>
    /// Gets the tail vertex position of specified leader line.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Output the leaderline tail point.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getLastVertex       (int leaderLineIndex, AcGePoint3d& point) const;

    /// <summary>
    /// Sets leader tail with specified point.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="point">
    /// Iutput the leaderline tail point.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus setLastVertex       (int leaderLineIndex, const AcGePoint3d& point);

    /// <summary>
    /// Gets the number of vertices in the specified leader line.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="num">
    /// Ouput the number of vertices in the leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus numVertices         (int leaderLineIndex, int& num) const;

    /// <summary>
    /// Sets the vertex with specified index in the leader line with a new position specified by point.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="index">
    /// Input the index of vertex.
    /// </param>
    /// <param name="point">
    /// Input the new position of this vertex.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus setVertex           (int leaderLineIndex, int index, const AcGePoint3d& point);

    /// <summary>
    /// Gets position of the vertex with specified index in the leader line
    /// with a new position specified by point.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="index">
    /// Input the index of vertex.
    /// </param>
    /// <param name="point">
    /// Ouput position of the vertex.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getVertex           (int leaderLineIndex, int index, AcGePoint3d& point) const;

    /// <summary>
    /// Gets the index of leader cluster which the specified leader line is in.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input index of the leader line.
    /// </param>
    /// <param name="leaderIndex">
    /// Output index of leader owned the input leaderline.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getLeaderIndex      (int leaderLineIndex, int& leaderIndex) const;

    /// <summary>
    /// Gets the indexes of leaderlines of the specific leader.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input leader index.
    /// </param>
    /// <param name="leaderLineIndexes">
    /// Output indexes of leaderlines owned by the input leader.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getLeaderLineIndexes(int leaderIndex, AcArray<int>& leaderLineIndexes) const;

    /// <summary>
    /// Sets the dog-leg in the leader cluster specified by leaderIndex with vector.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input leader index.
    /// </param>
    /// <param name="vector">
    /// Input the vector represents the new length and new direction of dog-leg.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus setDoglegDirection           (int leaderIndex, const AcGeVector3d& vector);

    /// <summary>
    /// Gets the vector represents the length and direction of the dog-leg in specified leader cluster.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input leader index.
    /// </param>
    /// <param name="vector">
    /// Ouput the vector represents the length and direction of the dog-leg in specified leader cluster.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus getDoglegDirection           (int leaderIndex, AcGeVector3d& vector) const;

    /// <summary>
    /// Sets the leader type to this mleader object.
    /// </summary>
    ///
    /// <param name="leaderLineType">
    /// Input the leader type. leaderLineType is defined in AcDbMLeaderStyle::LeaderType
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kLeaderLineType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setLeaderLineType      (AcDbMLeaderStyle::LeaderType leaderLineType);

    /// <summary>
    /// Gets the leader type of this mleader object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the leader line type of this mleader object.
    /// </returns>
    ///
    AcDbMLeaderStyle::LeaderType          leaderLineType         () const;

    /// <summary>
    /// Sets the color of leader lines.
    /// </summary>
    ///
    /// <param name="leaderLineColor">
    /// Input the color of leader lines.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kLeaderLineColor override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setLeaderLineColor     (const AcCmColor& leaderLineColor);

    /// <summary>
    /// Gets the color of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of leader lines.
    /// </returns>
    ///
    AcCmColor                             leaderLineColor        () const;

    /// <summary>
    /// Sets  the objectId of leader line type.
    /// </summary>
    ///
    /// <param name="leaderLineTypeId">
    /// Input  the objectId of leader line type.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kLeaderLineTypeId override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setLeaderLineTypeId    (AcDbObjectId leaderLineTypeId);

    /// <summary>
    /// Gets the objectId of leader line type.
    /// </summary>
    ///
    /// <returns>
    /// Returns the objectId of leader line type.
    /// </returns>
    ///
    AcDbObjectId                          leaderLineTypeId       () const;

    /// <summary>
    /// Sets the line weight of leader lines.
    /// </summary>
    ///
    /// <param name="leaderLineWeight">
    /// Input the line weight of leader lines.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kLeaderLineWeight override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setLeaderLineWeight    (AcDb::LineWeight leaderLineWeight);

    /// <summary>
    /// Gets the line weight of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of leader lines.
    /// </returns>
    ///
    AcDb::LineWeight                      leaderLineWeight       () const;

    /// <summary>
    /// Sets the gap between leader tail and MText.
    /// </summary>
    ///
    /// <param name="landingGap">
    /// Input the gap between leader tail and MText.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kLandingGap override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setLandingGap          (double landingGap);

    /// <summary>
    /// Gets the gap between leader tail and MText.
    /// </summary>
    ///
    /// <returns>
    /// Returns the gap between leader tail and MText.
    /// </returns>
    ///
    double                                landingGap             () const;

    /// <summary>
    /// Used to enable/disable landing of leader line.
    /// </summary>
    ///
    /// <param name="enableLanding">
    /// Input boolean to enable/disable landing of leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kEnableLanding override.
    /// If disable landing, the landing gap will be ignored.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setEnableLanding       (bool enableLanding);

    /// <summary>
    /// Indicates whether landing of leader line is enabled.
    /// </summary>
    ///
    /// <returns>
    /// If landing of leader line is enabled, returns true; otherwise, returns false.
    /// </returns>
    ///
    bool                                  enableLanding          () const;

    /// <summary>
    /// Used to enable/disable dog-leg leader line.
    /// </summary>
    ///
    /// <param name="enableDogleg">
    /// Input boolean to enable/disable dog-leg leader line.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kEnableDogleg override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setEnableDogleg        (bool enableDogleg);

    /// <summary>
    /// Indicates whether dog-leg leader line is enabled.
    /// </summary>
    ///
    /// <returns>
    /// If dog-leg leader line is enabled, returns true; otherwise, returns false.
    /// </returns>
    ///
    bool                                  enableDogleg           () const;

    /// <summary>
    /// Set the length of doglegs in the leader cluster specified by leaderIndex.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input leader index.
    /// </param>
    /// <param name="doglegLength">
    /// Input the length of doglegs.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kDoglegLength override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setDoglegLength        (int leaderIndex, double doglegLength);

    /// <summary>
    /// Gets the length of doglegs in the leader cluster specified by leaderIndex.
    /// </summary>
    ///
    /// <param name="leaderIndex">
    /// Input leader index.
    /// </param>
    /// <param name="doglegLength">
    /// Output leader index.
    /// </param>
    ///
    /// <returns>
    /// Returns the length of doglegs.
    /// </returns>
    ///
    Acad::ErrorStatus                     doglegLength           (int leaderIndex, double& doglegLength) const;

    //old interface to be removed
    Acad::ErrorStatus                     setDoglegLength        (double doglegLength);
    double                                doglegLength           () const;

    /// <summary>
    /// Sets default arrow symbol id.
    /// </summary>
    ///
    /// <param name="arrowSymbolId">
    /// Input the objectId of arrow symbol.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kArrowSymbolId override.
    /// If doesn't set arrow symbol id for specific leaderline,
    /// the leaderline will use this default arrowSymbolId.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setArrowSymbolId       (AcDbObjectId arrowSymbolId);

    /// <summary>
    /// Gets the default arrow symbol id
    /// </summary>
    ///
    /// <returns>
    /// Returns the default arrow symbol id
    /// </returns>
    ///
    AcDbObjectId                          arrowSymbolId          () const;

    /// <summary>
    /// Sets arrow size of this mleader object.
    /// </summary>
    ///
    /// <param name="arrowSize">
    /// Input size of arrow.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kArrowSize override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setArrowSize           (double arrowSize);

    /// <summary>
    /// Gets the arrow size of this mleader object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the arrow size of this mleader object.
    /// </returns>
    ///
    double                                arrowSize              () const;

    /// <summary>
    /// Sets the content type of this mleader object.
    /// </summary>
    ///
    /// <param name="contentType">
    /// Input text content type. The content type is defined in AcDbMLeaderStyle::ContentType.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kContentType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setContentType         (AcDbMLeaderStyle::ContentType contentType);

    /// <summary>
    /// Gets the content type of this mleader object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the content type of this mleader object.
    /// </returns>
    ///
    AcDbMLeaderStyle::ContentType         contentType            () const;

    /// <summary>
    /// Sets the MText content in mleader content to use the textStyle specified by textStyleId.
    /// </summary>
    ///
    /// <param name="textStyleId">
    /// Input AcDbTextStyle objectId.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextStyleId override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextStyleId         (AcDbObjectId textStyleId);

    /// <summary>
    /// Gets MText content textStyle objectId.
    /// </summary>
    ///
    /// <returns>
    /// Returns MText content textStyle objectId.
    /// </returns>
    ///
    AcDbObjectId                          textStyleId            () const;

    /// <summary>
    /// Sets text attachment type of MText content to specific direction leader.
    /// </summary>
    ///
    /// <param name="textAttachmentType">
    /// Input text attachment type defined in AcDbMLeaderStyle::TextAttachmentType.
    /// </param>
    /// <param name="leaderDirection">
    /// Input text leader direction type defined in AcDbMLeaderStyle::LeaderDirectionType.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextLeft/RightAttachmentType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextAttachmentType  (AcDbMLeaderStyle::TextAttachmentType textAttachmentType,
                                                                  AcDbMLeaderStyle::LeaderDirectionType leaderDirection);

    /// <summary>
    /// Gets text attachment type of MText content from specific direction leader.
    /// </summary>
    ///
    /// <param name="leaderDirection">
    /// Input text leader direction type defined in AcDbMLeaderStyle::LeaderDirectionType.
    /// </param>
    ///
    /// <returns>
    /// Returns text attachment type of MText content.
    /// </returns>
    ///
    AcDbMLeaderStyle::TextAttachmentType  textAttachmentType     (AcDbMLeaderStyle::LeaderDirectionType leaderDirection) const;

    //todo remove this api
    Acad::ErrorStatus                     setTextAttachmentType  (AcDbMLeaderStyle::TextAttachmentType textAttachmentType);
    AcDbMLeaderStyle::TextAttachmentType  textAttachmentType     () const;

    /// <summary>
    /// Sets the angle type of MText content which respect to the last leader line segment.
    /// </summary>
    ///
    /// <param name="textAngleType">
    /// Input text textAngleType type defined in AcDbMLeaderStyle::TextAngleType.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextAngleType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextAngleType       (AcDbMLeaderStyle::TextAngleType textAngleType);

    /// <summary>
    /// Gets the angle type of MText content.
    /// </summary>
    ///
    /// <returns>
    /// Returns the angle type of MText content.
    /// </returns>
    ///
    AcDbMLeaderStyle::TextAngleType       textAngleType          () const;

    /// <summary>
    /// Sets text alignment type of MText content.
    /// </summary>
    ///
    /// <param name="textAlignmentType">
    /// Input textAlignmentType defined in AcDbMLeaderStyle::TextAlignmentType.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextAlignmentType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextAlignmentType   (AcDbMLeaderStyle::TextAlignmentType textAlignmentType);

    /// <summary>
    /// Gets text alignment type of MText content.
    /// </summary>
    ///
    /// <returns>
    /// Returns text alignment type of MText content.
    /// </returns>
    ///
    AcDbMLeaderStyle::TextAlignmentType   textAlignmentType      () const;

    /// <summary>
    /// Sets text color of MText content.
    /// </summary>
    ///
    /// <param name="textColor">
    /// Input text color.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextColor override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextColor           (const AcCmColor& textColor);

    /// <summary>
    /// Gets text color of MText content.
    /// </summary>
    ///
    /// <returns>
    /// Returns text color of MText content.
    /// </returns>
    ///
    AcCmColor                             textColor              () const;

    /// <summary>
    /// Sets text height of MText content.
    /// </summary>
    ///
    /// <param name="textHeight">
    /// Input text height.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kTextHeight override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setTextHeight          (double textHeight);

    /// <summary>
    /// Gets text height of MText content.
    /// </summary>
    ///
    /// <returns>
    /// Returns text height of MText content.
    /// </returns>
    ///
    double                                textHeight             () const;

    /// <summary>
    /// Sets the text frame visible or invisible.
    /// </summary>
    ///
    /// <param name="enableFrameText">
    /// Input boolean to make the frame text visible/invisible.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kEnableFrameText override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setEnableFrameText     (bool enableFrameText);

    /// <summary>
    /// Indicates whether text frame of MText is visible.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if text frame is visible; otherwise, returns false.
    /// </returns>
    ///
    bool                                  enableFrameText        () const;

    /// <summary>
    /// Sets a MText object to mleader.
    /// </summary>
    ///
    /// <param name="pMText">
    /// Input the pointer of MText object.
    /// If input NULL, mleader use the default mtext defined in mleaderStyle.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kDefaultMText override.
    /// Mleader will not change the input pMText,
    /// and doesn’t mind whether the pMText is database resident.
    /// If input NULL, mleader use the default mtext defined in mleaderStyle,
    /// and kDefaultMText will not be overrided.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setMText               (const AcDbMText* pMText);

    /// <summary>
    /// Gets a copy of mleader’s mtext content
    /// </summary>
    ///
    /// <returns>
    /// Returns the copy of mtext content. If there is no mtext content, it returns NULL.
    /// </returns>
    ///
    /// <remarks>
    /// The returned mtext should be delete when it is no longer needed.
    /// </remarks>
    ///
    AcDbMText*                            mtext                  () const;

    /// <summary>
    /// Sets the id of referenced block, it's a block table record id.
    /// </summary>
    ///
    /// <param name="blockId">
    /// Input block table record Id.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kBlockId override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setBlockContentId             (AcDbObjectId blockId);

    /// <summary>
    /// Gets the id of referenced block, it's a block table record id.
    /// </summary>
    ///
    /// <returns>
    /// Returns the id of referenced block, it's a block table record id.
    /// </returns>
    ///
    AcDbObjectId                          blockContentId                () const;

    /// <summary>
    /// Sets block color in block content.
    /// </summary>
    ///
    /// <param name="blockColor">
    /// Input block color.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kBlockColor override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setBlockColor          (const AcCmColor& blockColor);

    /// <summary>
    /// Gets block color in block content.
    /// </summary>
    ///
    /// <returns>
    /// Returns block color in block content.
    /// </returns>
    ///
    AcCmColor                             blockColor             () const;

    /// <summary>
    /// Sets the scale of referenced block.
    /// </summary>
    ///
    /// <param name="scale">
    /// Input scale of referenced block.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kBlockScale override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setBlockScale          (const AcGeScale3d& scale);

    /// <summary>
    /// Gets the scale of referenced block.
    /// </summary>
    ///
    /// <returns>
    /// Returns the sacle of referenced block.
    /// </returns>
    ///
    AcGeScale3d                           blockScale             () const;

    /// <summary>
    /// Sets the rotation of referenced block.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Input rotation of referenced block.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kBlockRotation override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setBlockRotation       (double rotation);

    /// <summary>
    /// Gets the rotation of referenced block.
    /// </summary>
    ///
    /// <returns>
    /// Returns the rotation of referenced block.
    /// </returns>
    ///
    double                                blockRotation          () const;

    /// <summary>
    /// Sets the type of how the block is connected with leader lines.
    /// </summary>
    ///
    /// <param name="blockConnectionType">
    /// Input the connection type defined in AcDbMLeaderStyle::BlockConnectionType.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    /// <remarks>
    /// This function will set PropertyOverrideType kBlockConnectionType override.
    /// </remarks>
    ///
    Acad::ErrorStatus                     setBlockConnectionType (AcDbMLeaderStyle::BlockConnectionType blockConnectionType);

    /// <summary>
    /// Gets the type of how the block is connected with leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Returns the type of how the block is connected with leader lines.
    /// </returns>
    ///
    AcDbMLeaderStyle::BlockConnectionType blockConnectionType    () const;

    /// <summary>
    /// Use this function to make the annotation scale enable or disable.
    /// </summary>
    ///
    /// <param name="enableAnnotationScale">
    /// Input boolean to make the annotation scale enable/disable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setEnableAnnotationScale(bool enableAnnotationScale);

    /// <summary>
    /// Indicates whether annotation scale is enable.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if annotation scale is enable; otherwise, returns false.
    /// </returns>
    ///
    bool                                  enableAnnotationScale   () const;

    /// <summary>
    /// Sets the style of this MLeader object.
    /// </summary>
    ///
    /// <param name="newStyleId">
    /// Input objectId of the new style.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setMLeaderStyle        (AcDbObjectId newStyleId);

    /// <summary>
    /// Gets the object ID of current mleader object style.
    /// </summary>
    ///
    /// <returns>
    /// Returns the object ID of current mleader object style.
    /// </returns>
    ///
    AcDbObjectId                          MLeaderStyle           ();

    /// <summary>
    /// Gets the current mleader's properties, include override properties.
    /// </summary>
    ///
    /// <param name="mleaderStyle">
    /// Input a reference of mleaderStyle, mleader object will set its properties to this object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     getOverridedMLeaderStyle(AcDbMLeaderStyle& mleaderStyle);

    /// <summary>
    /// Sets the context data manager to mleader.
    /// </summary>
    ///
    /// <param name="pContextDataManager">
    /// Input the pointer of context data manager.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setContextDataManager  (void* pContextDataManager);

    /// <summary>
    /// Gets the context data manager in mleader.
    /// </summary>
    ///
    /// <returns>
    /// Returns the context data manager in mleader.
    /// </returns>
    ///
    void*                                 getContextDataManager  () const;

    /// <summary>
    /// Sets the position of mleader block content.
    /// </summary>
    ///
    /// <param name="position">
    /// Input the position of mleader block content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setBlockPosition       (const AcGePoint3d& position);

    /// <summary>
    /// Gets the position of mleader block content.
    /// </summary>
    ///
    /// <param name="position">
    /// OutPut the position of mleader block content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     getBlockPosition       (AcGePoint3d& position) const;

    /// <summary>
    /// Sets the location of mleader mtext content.
    /// </summary>
    ///
    /// <param name="location">
    /// Input the location of mleader mtext content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setTextLocation        (const AcGePoint3d& location);

    /// <summary>
    /// Gets the location of mleader mtext content.
    /// </summary>
    ///
    /// <param name="location">
    /// OutPut the location of mleader mtext content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     getTextLocation        (AcGePoint3d& location) const;

    /// <summary>
    /// Sets the location of mleader tolerance content.
    /// </summary>
    ///
    /// <param name="location">
    /// Input the location of mleader tolerance content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setToleranceLocation   (const AcGePoint3d& location);

    /// <summary>
    /// Gets the location of mleader tolerance content.
    /// </summary>
    ///
    /// <param name="location">
    /// OutPut the location of mleader tolerance content.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     getToleranceLocation   (AcGePoint3d& location) const;

    /// <summary>
    /// Sets the arrow head symbol id for the specific leaderline.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input the index of the specific leaderline.
    /// </param>
    /// <param name="arrowSymbolId">
    /// Input the object id of the arrow head symbol.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     setArrowSymbolId       (int leaderLineIndex,
                                                                  AcDbObjectId arrowSymbolId);

    /// <summary>
    /// Gets the arrow head symbol id for the specific leaderline.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input the index of the specific leaderline.
    /// </param>
    ///
    /// <returns>
    /// Returns the object id of the arrow head symbol of the specific leaderline.
    /// </returns>
    ///
    AcDbObjectId                          arrowSymbolId          (int leaderLineIndex) const;

    /// <summary>
    /// Indicates whether mleader has content.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if mleader has content; otherwise, returns false.
    /// </returns>
    ///
    bool                                  hasContent             () const;

    /// <summary>
    /// Gets the leader connection point of the specific direction.
    /// </summary>
    ///
    /// <param name="vect">
    /// Input the specific direction.
    /// </param>
    /// <param name="point">
    /// Output the connection point.
    /// </param>
    ///
    /// <returns>
    /// Returns the object id of the arrow head symbol of the specific leaderline.
    /// </returns>
    ///
    Acad::ErrorStatus                     connectionPoint        (const AcGeVector3d& vect,
                                                                  AcGePoint3d& point) const;

    /// <summary>
    /// Recaculate the dim break point.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     recomputeBreakPoints   ();

    /// <summary>
    /// Adds current mleader object to the modal space of input database.
    /// </summary>
    ///
    /// <param name="pDb">
    /// Input database into which the current mleader object should be added.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     postMLeaderToDb        (AcDbDatabase* pDb);

    // support dim associativity

    /// <summary>
    /// Update leaderLine position if leaderLine is associate with geometries
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     updateLeaderLinePosition();

    /// <summary>
    /// Remove the input leaderline's association with geometries.
    /// </summary>
    ///
    /// <param name="leaderLineIndex">
    /// Input leaderline index.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     removeLeaderLineRefAssoc(int leaderLineIndex) const;

    /// <summary>
    /// Update the mleader context's arrowhead, landing gap, dogleg length and textHeight or blockScale.
    /// </summary>
    ///
    /// <param name="pContext">
    /// Input pointer to mleader context data.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus                     updateContentScale(AcDbMLeaderObjectContextData* pContext);
};

#endif // __DBMLEADER_H__

