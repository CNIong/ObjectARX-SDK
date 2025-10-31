// (C) Copyright 2003 by Autodesk, Inc. 
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

#include "dbtable.h"
#include "dbTablestyle.h"
#include "acgiutil.h"

#define NEWTBLSTYLE "<New Table Style>"

// Vector classes to hold the table data
typedef AcArray <char *> FieldData;
typedef AcArray <FieldData *> RowData;

typedef std::map <char *,char *> HdrRwMap;
typedef std::pair <char *,char *> Char_Pair;

void deleteFieldData(FieldData *pFldData);
void deleteRowData(RowData *pRwData);
void deleteHdrRwMap(HdrRwMap *pHdrRw);

// To Print error messages
#define PRTMSGRETES(es) if (Acad::eOk != es){acutPrintf("\n%s.",acadErrorStatusText(es));return es;}
#define PRTMSGRET(msg) {acutPrintf("\n%s.",msg);return;}

// Main function to create a new table for a block definition
void buildTableFromBlock(const char *pBlkName, const char *pStyleName, bool bLink);

// Update existing table
void updateExistingTable(const char *pBlkName, const char *pStyleName, bool bLink);

// Adds new Table style
Acad::ErrorStatus addTableStyle(const char *pStyleName);

// Create table for the Block's BOM
Acad::ErrorStatus generateTableFromBlock(const char *pBlkName, RowData *&pRwData, bool bLink);

// Get the attribute object given the TAG value
char *getAttTextByTag(const char*pAttTag,AcDbObjectIterator *&pAttItr);

// Create an empty table
Acad::ErrorStatus createTable(AcDbTable *&pTbl, const char *pTblStyle, 
							  const int nColLen, const int nRowLen);
// Update existing table
Acad::ErrorStatus updateTable(AcDbTable *&pTbl, const char *pTblStyle, 
							  const int nColLen, const int nRowLen);
							  							  
// Set the number of columns and rows
Acad::ErrorStatus setTableColAndRows(AcDbTable *&pTbl, int nColLen, int nRowLen);
							  							  
// Create the table with the data provided
void populateTable(AcDbTable *&pTbl, const RowData *pRwData);

// add entity to the database
Acad::ErrorStatus addEntToDwg(AcDbDatabase *pDb, AcDbEntity *pEnt );

// Select entity on the screen
AcDbEntity* selectEntity(const char *pPrompt);

// Merge cells for Title and Header for sample table
Acad::ErrorStatus mergeCellsForTitleAndHeader(AcDbTable *&pTbl, const char *pBlkName);

// Set fit column with text width
Acad::ErrorStatus fitColumnWidth(AcDbTable *&pTbl,double maxWidth);

// Set fit row height with text height
Acad::ErrorStatus fitRowHeight(AcDbTable *&pTbl,double maxHeight);