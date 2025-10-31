//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2006-2007  by Autodesk, Inc.
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
// Name:            DbFormattedTableData.h
//
// Description:     Contains the following classes: 
//                      AcDbFormattedTableData
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DbLinkedTableData.h"
#include "DbTableIterator.h"


//*************************************************************************
// AcGridProperty
//*************************************************************************

struct AcGridProperty
{
    AcDb::GridProperty  mnPropMask;
    AcDb::GridLineStyle mnLineStyle;
    AcDb::LineWeight    mnLineWeight;
    AcDbHardPointerId   mLinetype;
    AcCmColor           mColor;
    AcDb::Visibility    mnVisibility;
    double              mfDoubleLineSpacing;
};


//*************************************************************************
// AcDbFormattedTableData
//*************************************************************************

class AcDbFormattedTableData : public AcDbLinkedTableData
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFormattedTableData);

    ACDB_PORT AcDbFormattedTableData(void);
    ACDB_PORT ~AcDbFormattedTableData(void);

    ACDB_PORT virtual int insertRowAndInherit(int nIndex, 
                                             int nInheritFrom,
                                             int nNumRows);
    ACDB_PORT virtual int insertColumnAndInherit(int nIndex, 
                                             int nInheritFrom,
                                             int nNumCols);

    ACDB_PORT virtual Acad::ErrorStatus setFieldId(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idField, 
                                             AcDb::CellOption nFlag);
    ACDB_PORT virtual Acad::ErrorStatus setFieldId(int nRow, 
                                             int nCol, 
                                             int nIndex, 
                                             const AcDbObjectId& idField, 
                                             AcDb::CellOption nFlag);

    ACDB_PORT virtual Acad::ErrorStatus merge(const AcCellRange& range);
    ACDB_PORT virtual Acad::ErrorStatus unmerge(const AcCellRange& range);
    ACDB_PORT virtual bool isMerged         (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcCellRange getMergeRange(int nRow, 
                                             int nCol) const;

    ACDB_PORT virtual bool isFormatEditable (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual double rotation       (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual double rotation       (int nRow, 
                                             int nCol,
                                             int nIndex) const;
    ACDB_PORT virtual Acad::ErrorStatus setRotation(int nRow, 
                                             int nCol, 
                                             double fRotation);
    ACDB_PORT virtual Acad::ErrorStatus setRotation(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             double fRotation);
    ACDB_PORT virtual double scale          (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual double scale          (int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setScale(int nRow, 
                                             int nCol, 
                                             double fScale);
    ACDB_PORT virtual Acad::ErrorStatus setScale(int nRow, 
                                             int nCol, 
                                             int nIndex,
                                             double fScale);
    ACDB_PORT virtual bool isAutoScale      (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual bool isAutoScale      (int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setAutoScale(int nRow, 
                                             int nCol, 
                                             bool bAutoScale);
    ACDB_PORT virtual Acad::ErrorStatus setAutoScale(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             bool bAutoScale);
    ACDB_PORT virtual AcDb::CellAlignment alignment(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setAlignment(int nRow, 
                                             int nCol, 
                                             AcDb::CellAlignment nAlignment);
    ACDB_PORT virtual AcCmColor contentColor(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcCmColor contentColor(int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setContentColor(int nRow, 
                                             int nCol, 
                                             const AcCmColor& color);
    ACDB_PORT virtual Acad::ErrorStatus setContentColor(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             const AcCmColor& color);
    ACDB_PORT virtual AcDbObjectId textStyle(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDbObjectId textStyle(int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setTextStyle(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idTextStyle);
    ACDB_PORT virtual Acad::ErrorStatus setTextStyle(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             const AcDbObjectId& idTextStyle);
    ACDB_PORT virtual double textHeight     (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual double textHeight     (int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setTextHeight(int nRow, 
                                             int nCol, 
                                             double fTextHeight);
    ACDB_PORT virtual Acad::ErrorStatus setTextHeight(int nRow, 
                                             int nCol,
                                             int nContent,
                                             double fTextHeight);
    ACDB_PORT virtual AcCmColor backgroundColor(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setBackgroundColor(int nRow, 
                                             int nCol, 
                                             const AcCmColor& color);
    ACDB_PORT virtual AcDb::CellContentLayout contentLayout(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setContentLayout(int nRow, 
                                             int nCol, 
                                             AcDb::CellContentLayout nLayout);

    ACDB_PORT virtual AcDb::FlowDirection flowDirection(void) const;
    ACDB_PORT virtual Acad::ErrorStatus setFlowDirection(AcDb::FlowDirection nDir);
    ACDB_PORT virtual double margin         (int nRow, 
                                             int nCol, 
                                             AcDb::CellMargin nMargin) const;
    ACDB_PORT virtual Acad::ErrorStatus setMargin(int nRow, 
                                             int nCol, 
                                             AcDb::CellMargin nMargins, 
                                             double fMargin);
    ACDB_PORT virtual bool isMergeAllEnabled(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus enableMergeAll(int nRow, 
                                             int nCol,
                                             bool bEnable);

    ACDB_PORT virtual AcDb::GridLineStyle gridLineStyle(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridLineStyle(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes,
                                             AcDb::GridLineStyle nLineStyle);
    ACDB_PORT virtual AcDb::LineWeight gridLineWeight(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridLineWeight(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             AcDb::LineWeight nLineWeight);
    ACDB_PORT virtual AcDbObjectId gridLinetype(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridLinetype(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcDbObjectId& idLinetype);
    ACDB_PORT virtual AcCmColor gridColor   (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridColor(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcCmColor& color);
    ACDB_PORT virtual AcDb::Visibility gridVisibility(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridVisibility(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             AcDb::Visibility nVisibility);
    ACDB_PORT virtual double gridDoubleLineSpacing(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridDoubleLineSpacing(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             double fSpacing);
    ACDB_PORT virtual Acad::ErrorStatus getGridProperty(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType, 
                                             AcGridProperty& gridProp) const;
    ACDB_PORT virtual Acad::ErrorStatus setGridProperty(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcGridProperty& gridProp);
    ACDB_PORT virtual Acad::ErrorStatus setGridProperty(const AcCellRange& range,
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcGridProperty& gridProp);

    ACDB_PORT virtual AcDb::CellProperty getOverride(int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual AcDb::GridProperty getOverride(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    ACDB_PORT virtual Acad::ErrorStatus setOverride(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             AcDb::CellProperty nOverride);
    ACDB_PORT virtual Acad::ErrorStatus setOverride(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType, 
                                             AcDb::GridProperty nOverride);
    ACDB_PORT virtual Acad::ErrorStatus removeAllOverrides(int nRow, 
                                             int nCol);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
};
