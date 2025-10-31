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
// Name:            DbLinkedTableData.h
//
// Description:     Contains the following classes: 
//                      AcDbLinkedTableData
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DbLinkedData.h"
#include "DbTableIterator.h"
#include "AcCell.h"


//*************************************************************************
// AcDbLinkedTableData
//*************************************************************************

class AcDbLinkedTableData : public AcDbLinkedData
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinkedTableData);

    ACDB_PORT AcDbLinkedTableData(void);
    ACDB_PORT virtual ~AcDbLinkedTableData(void);

    ACDB_PORT virtual Acad::ErrorStatus clear(void);
    ACDB_PORT virtual Acad::ErrorStatus copyFrom(const AcDbLinkedTableData* pSrc, 
                                             AcDb::TableCopyOption nOption);
    ACDB_PORT virtual Acad::ErrorStatus copyFrom(const AcDbLinkedTableData* pSrc, 
                                             AcDb::TableCopyOption nOption, 
                                             const AcCellRange& srcRange, 
                                             const AcCellRange& targetRange,
                                             AcCellRange* pNewTargetRange);
    ACDB_PORT AcDbTableIterator* getIterator(void) const;
    ACDB_PORT AcDbTableIterator* getIterator(const AcCellRange* pRange, 
                                             AcDb::TableIteratorOption nOption) const;

    ACDB_PORT virtual Acad::ErrorStatus setSize(int nRows, int nCols);
    ACDB_PORT virtual int numColumns        (void) const;
    ACDB_PORT virtual const ACHAR* getColumnName(int nIndex) const;
    ACDB_PORT virtual Acad::ErrorStatus setColumnName(int nIndex, 
                                             const ACHAR* pszName);
    ACDB_PORT virtual int appendColumn      (int nNumCols);
    ACDB_PORT virtual int insertColumn      (int nIndex, 
                                             int nNumCols);
    ACDB_PORT virtual Acad::ErrorStatus deleteColumn(int nIndex, 
                                             int nNumColsToDelete);

    ACDB_PORT virtual int numRows           (void) const;
    ACDB_PORT virtual bool canInsert        (int nIndex, 
                                             bool bRow) const;
    ACDB_PORT virtual int appendRow         (int nNumRows);
    ACDB_PORT virtual int insertRow         (int nIndex, 
                                             int nNumRows);
    ACDB_PORT virtual bool canDelete        (int nIndex, 
                                             int nCount, 
                                             bool bRow) const;
    ACDB_PORT virtual Acad::ErrorStatus deleteRow(int nIndex, 
                                             int nNumRowsToDelete);

    ACDB_PORT virtual bool isContentEditable(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDb::CellState cellState(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setCellState(int nRow, 
                                             int nCol, 
                                             AcDb::CellState nCellState);
    ACDB_PORT virtual AcString getToolTip   (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setToolTip(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszToolTip);
    ACDB_PORT virtual int getCustomData     (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setCustomData(int nRow, 
                                             int nCol, 
                                             int nData);
    ACDB_PORT virtual Acad::ErrorStatus getCustomData(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszKey, 
                                             AcValue* pData) const;
    ACDB_PORT virtual Acad::ErrorStatus setCustomData(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszKey, 
                                             const AcValue* pData);
    ACDB_PORT virtual bool isLinked         (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDbObjectId getDataLink(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus getDataLink(int nRow, 
                                             int nCol, 
                                             AcDbDataLink*& pDataLink, 
                                             AcDb::OpenMode mode) const;
    ACDB_PORT virtual int getDataLink       (const AcCellRange* pRange, 
                                             AcDbObjectIdArray& dataLinkIds) const;
    ACDB_PORT virtual Acad::ErrorStatus setDataLink(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idDataLink,
                                             bool bUpdate);
    ACDB_PORT virtual Acad::ErrorStatus setDataLink(const AcCellRange& range, 
                                             const AcDbObjectId& idDataLink,
                                             bool bUpdate);
    ACDB_PORT virtual AcCellRange getDataLinkRange(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus removeDataLink(int nRow, 
                                             int nCol);
    ACDB_PORT virtual Acad::ErrorStatus removeDataLink(void);
    ACDB_PORT virtual Acad::ErrorStatus updateDataLink(int nRow,
                                             int nCol, 
                                             AcDb::UpdateDirection nDir,
                                             AcDb::UpdateOption nOption);
    ACDB_PORT virtual Acad::ErrorStatus updateDataLink(AcDb::UpdateDirection nDir, 
                                             AcDb::UpdateOption nOption);

    ACDB_PORT virtual int numContents       (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual int createContent     (int nRow, 
                                             int nCol, 
                                             int nIndex);
    ACDB_PORT virtual Acad::ErrorStatus moveContent(int nRow, 
                                             int nCol, 
                                             int nFromIndex, 
                                             int nToIndex);
    ACDB_PORT virtual Acad::ErrorStatus deleteContent(int nRow, 
                                             int nCol, 
                                             int nContent);
    ACDB_PORT virtual Acad::ErrorStatus deleteContent(int nRow, 
                                             int nCol);
    ACDB_PORT virtual Acad::ErrorStatus deleteContent(const AcCellRange& range);

    ACDB_PORT virtual AcDb::CellContentType contentType(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDb::CellContentType contentType(int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus getDataType(int nRow, 
                                             int nCol, 
                                             AcValue::DataType& nDataType, 
                                             AcValue::UnitType& nUnitType) const;
    ACDB_PORT virtual Acad::ErrorStatus getDataType(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             AcValue::DataType& nDataType, 
                                             AcValue::UnitType& nUnitType) const;
    ACDB_PORT virtual Acad::ErrorStatus setDataType(int nRow, 
                                             int nCol, 
                                             AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType);
    ACDB_PORT virtual Acad::ErrorStatus setDataType(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType);
    ACDB_PORT virtual AcString dataFormat   (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcString dataFormat   (int nRow, 
                                             int nCol,
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setDataFormat(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszFormat);
    ACDB_PORT virtual Acad::ErrorStatus setDataFormat(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             const ACHAR* pszFormat);
    ACDB_PORT virtual Acad::ErrorStatus getValue(int nRow, 
                                             int nCol, 
                                             AcValue& value) const;
    ACDB_PORT virtual Acad::ErrorStatus getValue(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             AcValue::FormatOption nOption, 
                                             AcValue& value) const;
    ACDB_PORT virtual Acad::ErrorStatus setValue(int nRow, 
                                             int nCol, 
                                             const AcValue& value);
    ACDB_PORT virtual Acad::ErrorStatus setValue(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcValue& value);
    ACDB_PORT virtual Acad::ErrorStatus setValue(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcValue& value,
                                             AcValue::ParseOption nOption);
    ACDB_PORT virtual AcString getText      (int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcString getText      (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual AcString getText      (int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             AcValue::FormatOption nOption) const;
    ACDB_PORT virtual Acad::ErrorStatus setText(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszText);
    ACDB_PORT virtual Acad::ErrorStatus setText(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const ACHAR* pszText);
    ACDB_PORT virtual bool hasFormula       (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual AcString getFormula   (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setFormula(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const ACHAR* pszFormula);
    ACDB_PORT virtual AcDbObjectId getFieldId(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDbObjectId getFieldId(int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setFieldId(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idField);
    ACDB_PORT virtual Acad::ErrorStatus setFieldId(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcDbObjectId& idField);
    ACDB_PORT virtual Acad::ErrorStatus getField(int nRow, 
                                             int nCol, 
                                             int nContent,
                                             AcDbField*& pField,
                                             AcDb::OpenMode mode) const;
    ACDB_PORT virtual AcDbObjectId getBlockTableRecordId(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual AcDbObjectId getBlockTableRecordId(int nRow, 
                                             int nCol, 
                                             int nContent) const;
    ACDB_PORT virtual Acad::ErrorStatus setBlockTableRecordId(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idBTR);
    ACDB_PORT virtual Acad::ErrorStatus setBlockTableRecordId(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcDbObjectId& idBTR);
    ACDB_PORT virtual AcString getBlockAttributeValue(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idAttDef) const;
    ACDB_PORT virtual AcString getBlockAttributeValue(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcDbObjectId& idAttDef) const;
    ACDB_PORT virtual Acad::ErrorStatus setBlockAttributeValue(int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idAttDef, 
                                             const ACHAR* pszAttValue);
    ACDB_PORT virtual Acad::ErrorStatus setBlockAttributeValue(int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const AcDbObjectId& idAttDef, 
                                             const ACHAR* pszAttValue);

    ACDB_PORT virtual Acad::ErrorStatus evaluateFormula(void);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
};
