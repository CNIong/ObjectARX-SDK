#ifndef __DBTABLESTYLE_H__
#define __DBTABLESTYLE_H__

#pragma once
//
//  Copyright 2003-2006 by Autodesk, Inc.
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
// dbTableStyle.h
//
//  DESCRIPTION: AcDbTableStyle API class declaration
//
//  AcRxObject
//    AcDbObject
//      AcDbTableStyle
//

#include "dbmain.h"
#include "AdAChar.h"
#include "AcValue.h"

#pragma pack (push, 8)

class AcDbTableStyle : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTableStyle);

    AcDbTableStyle();
    virtual ~AcDbTableStyle();

    // AcDbTableStyle protocol
    //

    // General Properties
    //
    virtual Acad::ErrorStatus   getName(ACHAR*& pszName) const;
    virtual Acad::ErrorStatus   setName(const ACHAR * pszName);

    virtual const ACHAR*         description(void) const;
    virtual Acad::ErrorStatus   setDescription(const ACHAR * pszDescription);

    virtual Adesk::UInt32       bitFlags() const;
    virtual Acad::ErrorStatus   setBitFlags(Adesk::UInt32 flags);

    virtual AcDb::FlowDirection flowDirection(void) const; 
    virtual Acad::ErrorStatus   setFlowDirection(AcDb::FlowDirection flow);

    virtual double              horzCellMargin(void) const;
    virtual Acad::ErrorStatus   setHorzCellMargin(double dCellMargin);

    virtual double              vertCellMargin(void) const;
    virtual Acad::ErrorStatus   setVertCellMargin(double dCellMargin);

    virtual bool                isTitleSuppressed(void) const;
    virtual Acad::ErrorStatus   suppressTitleRow(bool bValue);

    virtual bool                isHeaderSuppressed(void) const;
    virtual Acad::ErrorStatus   suppressHeaderRow(bool bValue);


    // Cell properties
    //
    virtual AcDbObjectId        textStyle(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextStyle(const AcDbObjectId id,
                                            int rowTypes = AcDb::kAllRows);
    
    virtual double              textHeight(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextHeight(double dHeight,
                                              int rowTypes = AcDb::kAllRows);

    virtual AcDb::CellAlignment alignment(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setAlignment(AcDb::CellAlignment alignment,
                                             int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           color(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setColor(const AcCmColor& color,
                                         int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           backgroundColor(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setBackgroundColor(const AcCmColor& color,
                                                   int rowTypes = AcDb::kAllRows);

    virtual bool                isBackgroundColorNone(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setBackgroundColorNone(bool bValue,
                                                       int rowTypes = AcDb::kAllRows);
    // For internal use only
    virtual Acad::ErrorStatus   getDataType(AcValue::DataType& nDataType,
                                            AcValue::UnitType& nUnitType) const;
    // For internal use only
    virtual Acad::ErrorStatus   getDataType(AcValue::DataType& nDataType,
                                            AcValue::UnitType& nUnitType,
                                            AcDb::RowType rowType) const;
    // For internal use only
    virtual Acad::ErrorStatus   setDataType(AcValue::DataType nDataType,
                                            AcValue::UnitType nUnitType);
    // For internal use only
    virtual Acad::ErrorStatus   setDataType(AcValue::DataType nDataType, 
                                            AcValue::UnitType nUnitType,
                                            int rowTypes);

    // For internal use only
    virtual const ACHAR* format (void) const;
    // For internal use only
    virtual const ACHAR* format (AcDb::RowType rowType) const;
    // For internal use only
    virtual Acad::ErrorStatus   setFormat(const ACHAR* pszFormat);
    // For internal use only
    virtual Acad::ErrorStatus   setFormat(const ACHAR* pszFormat,
                                          int rowTypes);


    //Gridline properties
    //
    virtual AcDb::LineWeight    gridLineWeight(AcDb::GridLineType gridLineType, 
                                               AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridLineWeight(AcDb::LineWeight lineWeight,
                                                  int gridLineTypes = AcDb::kAllGridLines, 
                                                  int rowTypes = AcDb::kAllRows);
    virtual AcCmColor           gridColor(AcDb::GridLineType gridLineType, 
                                          AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridColor(const AcCmColor color,
                                             int gridLineTypes = AcDb::kAllGridLines, 
                                             int rowTypes = AcDb::kAllRows);
    virtual AcDb::Visibility    gridVisibility(AcDb::GridLineType gridLineType, 
                                               AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridVisibility(AcDb::Visibility visible,
                                                  int gridLineTypes = AcDb::kAllGridLines, 
                                                  int rowTypes = AcDb::kAllRows);

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

    // Utility functions
    //
    virtual Acad::ErrorStatus   postTableStyleToDb(AcDbDatabase* pDb, 
                                                   const ACHAR* styleName, 
                                                   AcDbObjectId& tableStyleId);

    //********************************************************************
    // Get corresponding COM wrapper class ID
    //********************************************************************
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;

};

#pragma pack (pop)

#endif // __DBTABLESTYLE_H__
