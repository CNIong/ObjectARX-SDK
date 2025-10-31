//
//  Copyright 2003 by Autodesk, Inc.
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
// dbtable.h
//
//  DESCRIPTION: AcDbTable api class declaration
//
//  AcRxObject
//    AcDbObject
//      AcDbEntity
//        AcDbBlockReference
//          AcDbTable
//

#pragma once

#include "dbmain.h"
#include "dbents.h"

#pragma pack(push, 8)

// typedef for AcSubentPathArray
//
typedef AcArray<AcDbFullSubentPath,
        AcArrayObjectCopyReallocator<AcDbFullSubentPath> > AcSubentPathArray;


class AcDbTable: public AcDbBlockReference
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTable);

    enum TableStyleOverrides {
        //table
        kTitleSuppressed             = 1,
        kHeaderSuppressed            = 2,
        kFlowDirection               = 3,         
        kHorzCellMargin              = 4,
        kVertCellMargin              = 5,
        kTitleRowColor               = 6,
        kHeaderRowColor              = 7,
        kDataRowColor                = 8,
        kTitleRowFillNone            = 9,
        kHeaderRowFillNone           = 10,
        kDataRowFillNone             = 11,
        kTitleRowFillColor           = 12,
        kHeaderRowFillColor          = 13,
        kDataRowFillColor            = 14,
        kTitleRowAlignment           = 15,
        kHeaderRowAlignment          = 16,
        kDataRowAlignment            = 17,
        kTitleRowTextStyle           = 18,
        kHeaderRowTextStyle          = 19,
        kDataRowTextStyle            = 20,
        kTitleRowTextHeight          = 21,
        kHeaderRowTextHeight         = 22,
        kDataRowTextHeight           = 23,

        // grid color
        kTitleHorzTopColor           = 40,
        kTitleHorzInsideColor        = 41,
        kTitleHorzBottomColor        = 42,
        kTitleVertLeftColor          = 43,
        kTitleVertInsideColor        = 44,
        kTitleVertRightColor         = 45,

        kHeaderHorzTopColor          = 46,
        kHeaderHorzInsideColor       = 47,
        kHeaderHorzBottomColor       = 48,
        kHeaderVertLeftColor         = 49,
        kHeaderVertInsideColor       = 50,
        kHeaderVertRightColor        = 51,

        kDataHorzTopColor            = 52,
        kDataHorzInsideColor         = 53,
        kDataHorzBottomColor         = 54,
        kDataVertLeftColor           = 55,
        kDataVertInsideColor         = 56,
        kDataVertRightColor          = 57,

        // grid line weight
        kTitleHorzTopLineWeight      = 70,
        kTitleHorzInsideLineWeight   = 71,
        kTitleHorzBottomLineWeight   = 72,
        kTitleVertLeftLineWeight     = 73,
        kTitleVertInsideLineWeight   = 74,
        kTitleVertRightLineWeight    = 75,

        kHeaderHorzTopLineWeight     = 76,
        kHeaderHorzInsideLineWeight  = 77,
        kHeaderHorzBottomLineWeight  = 78,
        kHeaderVertLeftLineWeight    = 79,
        kHeaderVertInsideLineWeight  = 80,
        kHeaderVertRightLineWeight   = 81,

        kDataHorzTopLineWeight       = 82,
        kDataHorzInsideLineWeight    = 83,
        kDataHorzBottomLineWeight    = 84,
        kDataVertLeftLineWeight      = 85,
        kDataVertInsideLineWeight    = 86,
        kDataVertRightLineWeight     = 87,

        // grid visibility
        kTitleHorzTopVisibility      = 100,
        kTitleHorzInsideVisibility   = 101,
        kTitleHorzBottomVisibility   = 102,
        kTitleVertLeftVisibility     = 103,
        kTitleVertInsideVisibility   = 104,
        kTitleVertRightVisibility    = 105,

        kHeaderHorzTopVisibility     = 106,
        kHeaderHorzInsideVisibility  = 107,
        kHeaderHorzBottomVisibility  = 108,
        kHeaderVertLeftVisibility    = 109,
        kHeaderVertInsideVisibility  = 110,
        kHeaderVertRightVisibility   = 111,

        kDataHorzTopVisibility       = 112,
        kDataHorzInsideVisibility    = 113,
        kDataHorzBottomVisibility    = 114,
        kDataVertLeftVisibility      = 115,
        kDataVertInsideVisibility    = 116,
        kDataVertRightVisibility     = 117,

        //cell 
        //
        kCellAlignment               = 130,
        kCellBackgroundFillNone      = 131,
        kCellBackgroundColor         = 132,
        kCellContentColor            = 133,
        kCellTextStyle               = 134,
        kCellTextHeight              = 135,
        kCellTopGridColor            = 136,
        kCellRightGridColor          = 137,
        kCellBottomGridColor         = 138,
        kCellLeftGridColor           = 139,
        kCellTopGridLineWeight       = 140,
        kCellRightGridLineWeight     = 141,
        kCellBottomGridLineWeight    = 142,
        kCellLeftGridLineWeight      = 143,
        kCellTopVisibility           = 144,
        kCellRightVisibility         = 145,
        kCellBottomVisibility        = 146,
        kCellLeftVisibility          = 147    
    };

    AcDbTable();
    virtual ~AcDbTable();


    //********************************************************************
    // Get and set methods for table properties
    //********************************************************************
    //
    virtual AcDbObjectId        tableStyle() const;
    virtual Acad::ErrorStatus   setTableStyle(const AcDbObjectId& id);

    virtual AcGeVector3d        direction() const;
    virtual Acad::ErrorStatus   setDirection(const AcGeVector3d& horzVec);

    virtual Adesk::UInt32       numRows() const;
    virtual Acad::ErrorStatus   setNumRows(int nRows);

    virtual Adesk::UInt32       numColumns() const;
    virtual Acad::ErrorStatus   setNumColumns(int nCols);

    virtual double              width() const;
    virtual Acad::ErrorStatus   setWidth(double width);

    virtual double              columnWidth(int col) const;
    virtual Acad::ErrorStatus   setColumnWidth(int col, double width);
    virtual Acad::ErrorStatus   setColumnWidth(double width);

    virtual double              height() const;
    virtual Acad::ErrorStatus   setHeight(double height);

    virtual double              rowHeight(int row) const;
    virtual Acad::ErrorStatus   setRowHeight(int row, double height);
    virtual Acad::ErrorStatus   setRowHeight(double height);
	virtual double				minimumColumnWidth(int col) const;
	virtual double				minimumRowHeight(int row) const;    
	virtual double				minimumTableWidth() const;
	virtual double				minimumTableHeight() const;        

    //********************************************************************
    // Get and set methods for table style overrides
    //********************************************************************
    //
    virtual double              horzCellMargin() const;
    virtual Acad::ErrorStatus   setHorzCellMargin(double gap);

    virtual double              vertCellMargin() const;
    virtual Acad::ErrorStatus   setVertCellMargin(double gap);

    virtual AcDb::FlowDirection flowDirection() const; 
    virtual Acad::ErrorStatus   setFlowDirection(AcDb::FlowDirection flow);

    virtual bool                isTitleSuppressed() const;
    virtual Acad::ErrorStatus   suppressTitleRow(bool value);

    virtual bool                isHeaderSuppressed() const;
    virtual Acad::ErrorStatus   suppressHeaderRow(bool value);

    virtual AcDb::CellAlignment alignment(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setAlignment(AcDb::CellAlignment align,
                                          int rowTypes = AcDb::kAllRows);

    virtual bool                isBackgroundColorNone(AcDb::RowType type = 
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setBackgroundColorNone(bool value,
                                          int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           backgroundColor(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setBackgroundColor(const AcCmColor& color,
                                          int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           contentColor(AcDb::RowType type = 
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setContentColor(const AcCmColor& color,
                                          int nRowType = AcDb::kAllRows);

    virtual AcDbObjectId        textStyle(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextStyle(const AcDbObjectId& id,
                                          int rowTypes = AcDb::kAllRows);

    virtual double              textHeight(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextHeight(double height,
                                          int rowTypes = AcDb::kAllRows);

    virtual AcDb::LineWeight    gridLineWeight(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    virtual Acad::ErrorStatus   setGridLineWeight(AcDb::LineWeight lwt,
                                               int nBorders,
                                               int nRows);

    virtual AcCmColor           gridColor(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    virtual Acad::ErrorStatus   setGridColor(const AcCmColor& color,
                                               int nBorders,
                                               int nRows);

    virtual AcDb::Visibility    gridVisibility(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    virtual Acad::ErrorStatus   setGridVisibility(AcDb::Visibility visible,
                                               int nBorders,
                                               int nRows);

    virtual bool                tableStyleOverrides(
                                               AcDbIntArray& overrides) const;
    virtual void                clearTableStyleOverrides(int options = 0);

    //********************************************************************
    // Get and set methods for common cell properties
    //********************************************************************
    //
    virtual AcDb::CellType      cellType(int row, 
                                         int col) const;
    virtual Acad::ErrorStatus   setCellType(int row, 
                                         int col,
                                         AcDb::CellType type);

    virtual Acad::ErrorStatus   getCellExtents(int row, 
                                         int col,
                                         bool isOuterCell,
                                         AcGePoint3dArray& pts) const;

    virtual AcGePoint3d         attachmentPoint(int row, 
                                          int col) const; 

    virtual AcDb::CellAlignment alignment(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setAlignment(int row, 
                                          int col,
                                          AcDb::CellAlignment align);

    virtual bool                isBackgroundColorNone(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setBackgroundColorNone(int row, 
                                          int col, 
                                          bool value);

    virtual AcCmColor           backgroundColor(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setBackgroundColor(int row, 
                                          int col,
                                          const AcCmColor& color);

    virtual AcCmColor           contentColor(int row, 
                                             int col) const;
    virtual Acad::ErrorStatus   setContentColor(int row, 
                                             int col,
                                             const AcCmColor& color);

    virtual bool                cellStyleOverrides(int row, 
                                         int col, 
                                         AcDbIntArray& overrides) const;
                                         
    void                        clearCellOverrides(int row, int column);

    virtual Acad::ErrorStatus	deleteCellContent(int row, int col);
	virtual AcDb::RowType       rowType(int row) const;


    //********************************************************************
    // Get and set methods for text cell properties
    //********************************************************************
    //
    virtual const char*         textStringConst(int row, 
                                                int col) const;

    virtual char*               textString(int row, 
                                           int col) const;
    virtual Acad::ErrorStatus   setTextString(int row, 
                                           int col,
                                           const char* text);

    virtual AcDbObjectId        fieldId(int row, int col) const;
    virtual Acad::ErrorStatus   setFieldId(int row, int col, const AcDbObjectId& fieldId);

    virtual AcDbObjectId        textStyle(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setTextStyle(int row, 
                                          int col,
                                          const AcDbObjectId& id);

    virtual double              textHeight(int row,
                                           int col) const;
    virtual Acad::ErrorStatus   setTextHeight(int row, 
                                           int col,
                                           double height);

    virtual AcDb::RotationAngle textRotation(int row,
                                              int col) const;
    virtual Acad::ErrorStatus   setTextRotation(int row, 
                                              int col,
                                              AcDb::RotationAngle rot);

    //********************************************************************
    // Get and set methods for block cell properties
    //********************************************************************
    //
    virtual bool                isAutoScale(int row,
                                           int col) const;
    virtual Acad::ErrorStatus   setAutoScale(int row, 
                                           int col,
                                           bool autoFit);

    virtual AcDbObjectId        blockTableRecordId(int row, 
                                                   int col) const;

    virtual Acad::ErrorStatus   setBlockTableRecordId(int row, 
                                                   int col,
                                                   const AcDbObjectId& blkId,
                                                   bool autoFit = false);

    virtual double              blockScale(int row,
                                           int col) const;
    virtual Acad::ErrorStatus   setBlockScale(int row, 
                                           int col,
                                           double scale);

    virtual double              blockRotation(int row,
                                              int col) const;
    virtual Acad::ErrorStatus   setBlockRotation(int row, 
                                              int col,
                                              double rotAng);

    virtual Acad::ErrorStatus   getBlockAttributeValue(int row, 
                                           int col, 
                                           const AcDbObjectId& attdefId,
                                           char*& value) const;
    virtual Acad::ErrorStatus   setBlockAttributeValue(int row, 
                                           int col,
                                           const AcDbObjectId& attdefId,
                                           const char* value);

    //********************************************************************
    // Get and set methods for cell grid line properties
    //********************************************************************
    //
    virtual AcCmColor           gridColor(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridColor(int row, 
                                          int col,
                                          short nEdges,
                                          const AcCmColor& color);

    virtual AcDb::Visibility    gridVisibility(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridVisibility(int row, 
                                          int col,
                                          short nEdges,
                                          AcDb::Visibility value);

    virtual AcDb::LineWeight    gridLineWeight(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridLineWeight(int row, 
                                          int col,
                                          short nEdges,
                                          AcDb::LineWeight value);

    //********************************************************************
    // Insert and delete methods for columns and rows
    //********************************************************************
    //
    virtual Acad::ErrorStatus   insertColumns(int col, 
                                              double width,
                                              int nCols = 1);
    virtual Acad::ErrorStatus   deleteColumns(int col, 
                                              int nCols = 1);

    virtual Acad::ErrorStatus   insertRows(int row, 
                                           double height,
                                           int nRows = 1);
    virtual Acad::ErrorStatus   deleteRows(int row, 
                                           int nRows = 1);

    //********************************************************************
    // Merge and unmerge methods
    //********************************************************************
    //
    virtual Acad::ErrorStatus   mergeCells(int minRow, int maxRow,
                                           int minCol, int maxCol);
    virtual Acad::ErrorStatus   unmergeCells(int minRow, int maxRow,
                                           int minCol, int maxCol);

    virtual bool                isMergedCell(int row, int col, 
                                             int* minRow = NULL, 
                                             int* maxRow = NULL,
                                             int* minCol = NULL, 
                                             int* maxCol = NULL) const;

    //********************************************************************
    // Fields and Hyperlinks methods
    //********************************************************************
    //
    
    //********************************************************************
    // Methods to generate table layout and table block
    //********************************************************************
    //
    virtual Acad::ErrorStatus generateLayout();
    virtual Acad::ErrorStatus recomputeTableBlock(bool forceUpdate = true);

    //********************************************************************
    // Methods for sub-selection  
    //********************************************************************
    //
    virtual bool              hitTest(const AcGePoint3d& wpt, 
                                      const AcGeVector3d& wviewVec,
                                      double wxaper,
                                      double wyaper,
                                      int& resultRowIndex, 
                                      int& resultColumnIndex);

    virtual Acad::ErrorStatus select(const AcGePoint3d& wpt, 
                                     const AcGeVector3d& wvwVec, 
                                     const AcGeVector3d& wvwxVec, 
                                     double wxaper,
                                     double wyaper,
                                     bool allowOutside,
                                     bool bInPickFirst, 
                                     int& resultRowIndex, 
                                     int& resultColumnIndex,
                                     AcSubentPathArray* pPaths = NULL) const;

    virtual Acad::ErrorStatus selectSubRegion(const AcGePoint3d& wpt1, 
                                     const AcGePoint3d& wpt2,
                                     const AcGeVector3d& wvwVec, 
                                     const AcGeVector3d& wvwxVec,
                                     double wxaper,
                                     double wyaper,                             
                                     AcDb::SelectType seltype,
                                     bool bIncludeCurrentSelection,
                                     bool bInPickFirst,                             
                                     int& rowMin,
                                     int& rowMax,
                                     int& colMin,
                                     int& colMax,
                                     AcSubentPathArray* pPaths = NULL) const;

    virtual bool reselectSubRegion(AcSubentPathArray& paths) const;
            
    virtual Acad::ErrorStatus getSubSelection(int& rowMin,
                                      int& rowMax,
                                      int& colMin,
                                      int& colMax) const;

    virtual Acad::ErrorStatus setSubSelection(int rowMin,
                                      int rowMax,
                                      int colMin,
                                      int colMax);

    virtual void              clearSubSelection();

    virtual bool              hasSubSelection() const;

    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;

    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    virtual Acad::ErrorStatus subClose();
    virtual void              objectClosed(const AcDbObjectId objId);
    virtual void              erased(const AcDbObject* dbObj,
                                      Adesk::Boolean pErasing = true);

    // Get corresponding COM wrapper class ID
    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;

    //********************************************************************
    // Overridden methods from AcDbEntity
    //********************************************************************
    //
    virtual void              list() const;

    virtual Adesk::Boolean    worldDraw(AcGiWorldDraw* worldDraw);

    virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray&, 
                                            AcDbIntArray&,
                                            AcDbIntArray&) const;

    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray&,
                                               const AcGeVector3d&);

    virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& stretchPoints)
                                               const;

    virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& 
                                                 indices,
                                                 const AcGeVector3d& offset);

    virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
                                             int   gsSelectionMark,
                                             const AcGePoint3d&  pickPoint,
                                             const AcGePoint3d&  lastPoint,
                                             const AcGeMatrix3d& viewXform,
                                             AcGePoint3dArray&      snapPoints,
                                             AcDbIntArray&   geomIds)
                                             const;

    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus getTransformedCopy(const AcGeMatrix3d& xform,
                                                 AcDbEntity*& ent) const;

    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

    virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;

    //********************************************************************
    // Overridden methods from AcDbBlockReference required for AcDbTable
    //********************************************************************
    //
    // AcGePoint3d            position() const;
    virtual Acad::ErrorStatus setPosition(const AcGePoint3d&);

    // AcGeVector3d           normal() const;
    virtual Acad::ErrorStatus setNormal(const AcGeVector3d& newVal);

    //********************************************************************
    // Methods for internal use only
    //********************************************************************
    //
    // TODO: Temporary method for navigating after editing cells
    virtual Acad::ErrorStatus select_next_cell(int dir,
                                     int& resultRowIndex, 
                                     int& resultColumnIndex,
                                     AcSubentPathArray* pPaths = NULL,
                                     bool bSupportTextCellOnly = true) const;

    virtual void              setRegen();
    virtual void              suppressInvisibleGrid(bool value);
    virtual Acad::ErrorStatus getCellExtents(int row, 
                                         int col,
                                         double& cellWidth,
                                         double& cellHeight,
                                         bool bAdjustForMargins) const;

};

#pragma pack(pop)
