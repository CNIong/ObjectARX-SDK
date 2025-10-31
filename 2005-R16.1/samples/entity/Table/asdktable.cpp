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

// Last modified date: 03 Dec 2003

#include "StdAfx.h"

// Header File
#include "asdktable.h"

//-----------------------------------------------------------------------------
//----- Clean up routines
void deleteFieldData(FieldData *pFldData)
{
	// delete char pointers since they were created on the heap
	for (int i = 0; i < pFldData->length(); i++) delete[](char *)pFldData->at(i);
	delete pFldData;
}

void deleteRowData(RowData *pRwData)
{
	// delete pointers
	for (int i = 0; i < pRwData->length(); i++) deleteFieldData(pRwData->at(i));
	delete pRwData;
}

void deleteHdrRwMap(HdrRwMap *pHdrRw)
{
	HdrRwMap::const_iterator itr = pHdrRw->begin();

	while(!(itr == pHdrRw->end()))
	{
		delete[] itr->second;
		delete[] itr->first;
		itr++;
	}
	
	delete pHdrRw;
}

//-----------------------------------------------------------------------------
//----- Add entity to the database
Acad::ErrorStatus addEntToDwg(AcDbDatabase *pDb, AcDbEntity *pEnt )
{
	Acad::ErrorStatus es;
	if( pEnt )
	{
		AcDbBlockTable *pBtbl = NULL;

		es = pDb->getBlockTable(pBtbl, AcDb::kForRead );
		if( pBtbl )
		{
			AcDbBlockTableRecord *pBtblRcd = NULL;
			Acad::ErrorStatus openStatus = pBtbl->getAt( ACDB_MODEL_SPACE, pBtblRcd, AcDb::kForWrite );

			if( pBtbl )
				es = pBtbl->close();

			if( pBtblRcd )
			{
				es = pBtblRcd->appendAcDbEntity( pEnt );
				pBtblRcd->close();
			}
		}
	}

	return es;
}

//-----------------------------------------------------------------------------
//----- Select entity on the screen
AcDbEntity* selectEntity(const char *pPrompt)
{
	AcDbEntity *pEnt = NULL;
	AcDbObjectId mId;
	ads_point mPt;
	ads_name mEname;

	if ( RTNORM == acedEntSel(pPrompt, mEname, mPt))
	{
		if ( Acad::eOk == acdbGetObjectId(mId, mEname ))
		{
			if ( Acad::eOk == acdbOpenAcDbEntity(pEnt, mId, AcDb::kForWrite))
				return pEnt;
		}
	}
	return pEnt;
}

//-----------------------------------------------------------------------------
//----- Main function to create a new table for a given block definition
void buildTableFromBlock(const char *pBlkName, const char *pStyleName, bool bLink)
{
	
	// To hold table data
	RowData *pRwData = new RowData();
	
	if (Acad::eOk == generateTableFromBlock(pBlkName, pRwData,bLink))
	{
		// Create the table
		AcDbTable *pTbl = NULL;

		// Note that first two rows contain data for title and header
		// Hence use the third row for the correct column length
		if(Acad::eOk == createTable(pTbl,pStyleName,pRwData->at(2)->length(),pRwData->length()))
		{
			// Populate the table with data
			populateTable(pTbl, pRwData);

			// Add the Table Object to the Model Space of the current drawing
			if(Acad::eOk == addEntToDwg(acdbHostApplicationServices()->workingDatabase(),pTbl))
			{
				// Merge cells
				mergeCellsForTitleAndHeader(pTbl,pBlkName);
				
				// Fit the columns
				fitColumnWidth(pTbl,200); // 200 - arbitrary upper limit value
				
				// Fit the rows
				fitRowHeight(pTbl,50); // 50 - arbitrary upper limit value
				
				// Ask for the pick point
				ads_point pt;
				if(RTNORM == acedGetPoint(NULL,"\nSelect insertion point: ",pt))
				{
					pTbl->setPosition(AcGePoint3d(pt[X],pt[Y],pt[Z]));
				}
				// Close the table
				pTbl->close();
			}
			else
			{
				// Clean up, if pTbl is not added to the model space
				delete pTbl;
			}

		}
		else
		{
			acutPrintf("\nUnable to create new table");
		}
	}

	
	// Clean up
	deleteRowData(pRwData);
}

//-----------------------------------------------------------------------------
//----- Main function to update existing table
void updateExistingTable(const char *pBlkName, const char *pStyleName, bool bLink)
{

	AcDbTable *pTbl = NULL;
	
	if(NULL == (pTbl = AcDbTable::cast(selectEntity("\nSelect table to be updated...")))) 
											PRTMSGRET("Selected entity was not a table")
	
	// To hold table data
	RowData *pRwData = new RowData();
	
	if (Acad::eOk == generateTableFromBlock(pBlkName, pRwData,bLink))
	{
		if(Acad::eOk == updateTable(pTbl,pStyleName,pRwData->at(2)->length(),pRwData->length()))
		{
			// Populate the table with data
			populateTable(pTbl, pRwData);
			
			// Merge cells
			mergeCellsForTitleAndHeader(pTbl,pBlkName);
			
			// Fit the columns
			fitColumnWidth(pTbl,200);
			
			// Fit the rows
			fitRowHeight(pTbl,100);
		}
		else
		{
			acutPrintf("\nUnable to update new table");
		}
	}
	
	// Close the entity
	pTbl->close();
	
	// Clean up
	delete pRwData;
}

//-----------------------------------------------------------------------------
//----- Create new Table Style
Acad::ErrorStatus addTableStyle(const char *pStyleName)
{
	AcDbDictionary *pDict = NULL;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict,AcDb::kForRead);
	
	// Check if the Table Style is already existing
	if(pDict->has(pStyleName))
	{ 
		pDict->close();
		acdbFail("Table Style already available");
		PRTMSGRETES(Acad::eCreateInvalidName);
	}
	
	// Create new Table Style
	AcDbTableStyle *pTblStyle = new AcDbTableStyle();
	pDict->upgradeOpen();

	// You can also use the utility function postTableStyleToDb()	
	AcDbObjectId mObjId;
	Acad::ErrorStatus es;
	if(Acad::eOk != (es = pDict->setAt(pStyleName,pTblStyle,mObjId)))
	{
		pDict->close();
		delete pTblStyle;
		acdbFail("\nUnable to add new Table Style");
		PRTMSGRETES(es);
	}
	
	// Close the dictionary
	pDict->close();
	
	// Settings for the new Table Style
	pTblStyle->setFlowDirection(AcDb::FlowDirection::kTtoB);
	pTblStyle->setName(pStyleName);
	
	// Set the title color
	AcCmColor col;
	col.setColorIndex(1); // Red color
	pTblStyle->setColor(col,AcDb::kTitleRow);
	
	// Set the header color
	col.setColorIndex(2); // Yellow color
	pTblStyle->setColor(col,AcDb::kHeaderRow);
	
	// Alignment kMiddleCenter for all rows
	pTblStyle->setAlignment(AcDb::CellAlignment::kMiddleCenter,AcDb::kAllRows);
	pTblStyle->close();

	return Acad::eOk;
}

//-----------------------------------------------------------------------------
//----- Create a new table
Acad::ErrorStatus createTable(AcDbTable *&pTbl,const char *pTblStyle, 
							  const int nColLen, const int nRowLen)
{
	pTbl = new AcDbTable();
	Acad::ErrorStatus es;
	
	// Set the Table Style
	AcDbDictionary *pDict = NULL;
	AcDbObjectId idTblStyle;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict,AcDb::kForRead);
	es = pDict->getAt(pTblStyle,idTblStyle);
	pDict->close();
	
	if(Acad::eOk == es)	pTbl->setTableStyle(idTblStyle);
	
	pTbl->setNumColumns(nColLen); 
	pTbl->setNumRows(nRowLen); // you can also use insertRows() at later point
	pTbl->generateLayout(); // Very very important, else expect crashes later on
	
	return es;
}

//-----------------------------------------------------------------------------
//----- Update existing table
Acad::ErrorStatus updateTable(AcDbTable *&pTbl, const char *pTblStyle , 
							  const int nColLen, const int nRowLen)
{
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled())) PRTMSGRETES(Acad::eNotOpenForWrite)

	Acad::ErrorStatus es;
	
	// Set the Table Style
	AcDbDictionary *pDict = NULL;
	AcDbObjectId idTblStyle;
	acdbHostApplicationServices()->workingDatabase()->getTableStyleDictionary(pDict,AcDb::kForRead);
	es = pDict->getAt(pTblStyle,idTblStyle);
	pDict->close();

	if(Acad::eOk == es)	pTbl->setTableStyle(idTblStyle);
	
	// Clear existing rows and columns
	// On existing table we cannot use setNumRows and setNumColumns
	return setTableColAndRows(pTbl,nColLen,nRowLen);
}

//-----------------------------------------------------------------------------
//----- 
Acad::ErrorStatus setTableColAndRows(AcDbTable *&pTbl, int nColLen, int nRowLen)
{
	Acad::ErrorStatus es;
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled())) PRTMSGRETES(Acad::eNotOpenForWrite)
	
	// It is not possible to clear the column and row number on existing table
	// Cannot use setNumColumns on a existing table, it will return eNotApplicable
	// Delete the columns and rows and then recreate,but again cannot really delete all the rows and columns
	
	if(1 < pTbl->numRows())
	{
		es = pTbl->deleteRows(1,pTbl->numRows() - 1);// Leave one row
	}
	
	if(1 < pTbl->numColumns())
	{
		es = pTbl->deleteColumns(1,pTbl->numColumns() - 1);// Leave one column
	}
	pTbl->generateLayout();
	
	// Insert columns
	es = pTbl->insertColumns(1,pTbl->columnWidth(0),nColLen - 1);
	// Insert rows
	es = pTbl->insertRows(1,pTbl->rowHeight(0),nRowLen - 1);

	return pTbl->generateLayout();
}

//-----------------------------------------------------------------------------
//----- Populate the new table
void populateTable(AcDbTable *&pTbl, const RowData *pRwData)
{
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled()) || 
		(NULL == pRwData) || (0 == pRwData->length())) PRTMSGRET("eNotOpenForWrite")

	if ((pRwData->at(2)->length() != pTbl->numColumns()) || 
		(pRwData->length() != pTbl->numRows()))PRTMSGRET("Table and data does not match")
	
	// Populate the table / Rows
	for(int nCtr1 = 0;nCtr1 < pRwData->length();nCtr1++)
	{
		FieldData *pColData = pRwData->at(nCtr1);
		for(int nCtr2 = 0;nCtr2 < pColData->length();nCtr2++)
		{
			pTbl->setTextString(nCtr1,nCtr2,pColData->at(nCtr2));
		}
	}
}

//-----------------------------------------------------------------------------
//----- Generate data for the selected Block
Acad::ErrorStatus generateTableFromBlock(const char *pBlkName, RowData *&pRwData, bool bLink)
{
	// Sanity check
	if((NULL == pRwData) || (NULL == pBlkName))PRTMSGRETES(Acad::eNotApplicable)
	
	AcDbBlockTable *pBT = NULL;
	AcDbBlockTableRecord *pBTR = NULL;
	Acad::ErrorStatus es;

	// Get the block table	
	PRTMSGRETES(acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBT,AcDb::kForRead));
	
	// Get the blocktablerecord
	es = pBT->getAt(pBlkName,pBTR,AcDb::kForRead);
	pBT->close();
	
	PRTMSGRETES(es)
	
	// Check for all attributes
	if (!pBTR->hasAttributeDefinitions())
	{
		pBTR->close();
		PRTMSGRETES(Acad::eNotApplicable)
	}
	
	// Iterate for all attribute definitions
	// Build the header, this means find out how many attribute definitions are available
	AcDbBlockTableRecordIterator *pBTRItr = NULL;
	pBTR->newIterator(pBTRItr);
	
	// Add Data

	// Add Title in first row
	FieldData *pTitleData = new FieldData();
	
	char *pTitle = new char[256];
	memset(pTitle,0,256);
	sprintf(pTitle,"Block Name: %s",pBlkName);
	pTitleData->append(pTitle);
	
	pRwData->append(pTitleData);

	// Add header data in second row
	FieldData *pHdrData = new FieldData();

	// First column is Sl number
	pHdrData->append(strdup("Sl.No."));

	// Second column is Block Reference Handle number
	pHdrData->append(strdup("Block Handle"));
	
	// Get the remaining Column names from the block definition's AcDbAttributeDefinition
	while (!pBTRItr->done())
	{
		AcDbEntity *pEnt = NULL;
		pBTRItr->getEntity(pEnt,AcDb::kForRead);
		
		AcDbAttributeDefinition *pAttDef = NULL;
		pAttDef = AcDbAttributeDefinition::cast(pEnt);
		
		if(NULL != pAttDef)
		{
			if (Adesk::kFalse == pAttDef->isConstant())
			{
				pHdrData->append(pAttDef->tag()); // Append the attribute TAG for header
			}
		}
		
		pEnt->close();
		pBTRItr->step();
	}
	
	pRwData->append(pHdrData);
	
	// Clean up
	delete pBTRItr;

	// Get the attribute data for every block reference
	AcDbObjectIdArray idObjs;
	pBTR->getBlockReferenceIds(idObjs,true);
	
	// Done with the block table record
	pBTR->close();
	
	// Some sanity check, check if the block references are in anonymous blocks
	for(int nCtr1 = 0;nCtr1 < idObjs.length(); nCtr1++)
	{
		bool bValid = true;
		AcDbBlockReference *pBlkRef = NULL;
		if(Acad::eOk == acdbOpenObject((AcDbEntity *&)pBlkRef,idObjs.at(nCtr1),AcDb::kForRead,false))
		{
			AcDbObject *pObj = NULL;

			if(Acad::eOk == acdbOpenObject(pObj,pBlkRef->ownerId(),AcDb::kForRead,false))
			{
				if (!pObj->objectId().isValid()) bValid = false;
				
				AcDbBlockTableRecord *pBTR;
				if(NULL != (pBTR = AcDbBlockTableRecord::cast(pObj)))
				{
					const char *pName;
					pBTR->getName(pName);
					if((!pBTR->isLayout()) && ('*' == (int)*pName)) bValid = false;
				}
				pObj->close();
			}
			pBlkRef->close();
		}
		
		if(!bValid) idObjs.remove(idObjs.at(nCtr1));
	}

	if(0 == idObjs.length())
	{
		acutPrintf("\nNo block references found");
		return Acad::eNotApplicable;
	}
	
	// Start iterating all the valid block references for the attribute data
	int nSlNoCtr = 1;
	for(int nCtr1 = 0;nCtr1 < idObjs.length(); nCtr1++)
	{
		AcDbBlockReference *pBlkRef = NULL;
		if(Acad::eOk == acdbOpenObject((AcDbEntity *&)pBlkRef,idObjs.at(nCtr1),AcDb::kForRead,false))
		{
			FieldData *pFldData = new FieldData();
			
			// Add the Sl No
			char *pSlNo = new char[8];
			memset(pSlNo,0,8);
			sprintf(pSlNo,"%d",nSlNoCtr);
			pFldData->append(pSlNo);
			
			// Add the block reference handle
			char *pHndNo = new char[17];
			memset(pHndNo,0,17);
			AcDbHandle hnd;
			pBlkRef->getAcDbHandle(hnd);
			hnd.getIntoAsciiBuffer(pHndNo);
			
			pFldData->append(pHndNo);
			
			// Get the attribute data from the block reference. Create attribute name<->value map
			// this is required to fill data in correct sequence
			// irrespective of how we read the attributes
			HdrRwMap *pHdrRw = new HdrRwMap(); 
			
			AcDbObjectIterator *pAttItr = NULL;
			pAttItr = pBlkRef->attributeIterator();

			while (!pAttItr->done())
			{
				AcDbAttribute *pAtt;
				if (Acad::eOk == acdbOpenObject((AcDbEntity *&)pAtt,pAttItr->objectId(),AcDb::kForRead))
				{
					// If link is true then add a field
					if(bLink)
					{
						char *pAcFld = new char[512];
						memset(pAcFld,0,512);
						sprintf(pAcFld,"%%<\\AcObjProp Object(%%<\\_ObjId %d>%%).TextString>%%",pAttItr->objectId().asOldId());
						
						pHdrRw->insert(Char_Pair(pAtt->tag(),pAcFld));
					}
					else
					{
						pHdrRw->insert(Char_Pair(pAtt->tag(),pAtt->textString()));
					}
					pAtt->close();
				}

				pAttItr->step();
			}
			
			// Note start filling in from index 2 as we already filled the first two column data
			for(int nCtr2 = 2; nCtr2 < pHdrData->length();nCtr2++)
			{
				HdrRwMap::const_iterator itr = pHdrRw->begin();
				
				while(!(itr == pHdrRw->end()))
				{
					if(!strcmp(itr->first,pHdrData->at(nCtr2))) break;
					itr++;
				}
				
				// Duplicate the string as the pHdrRw will be deleted within this function scope
				char *pAttText = strdup(itr->second);
				pFldData->append((NULL == pAttText?"-":pAttText));
			}
			
			pRwData->append(pFldData);
			nSlNoCtr++; // Increment the block reference counter
			
			pBlkRef->close(); // Close the block reference
			
			delete pAttItr; // Clean up
			deleteHdrRwMap(pHdrRw);
		}
	}
	
	return Acad::eOk;
}

//-----------------------------------------------------------------------------
//----- Merge cells
Acad::ErrorStatus mergeCellsForTitleAndHeader(AcDbTable *&pTbl, const char *pBlkName)
{
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled())) PRTMSGRETES(Acad::eNotOpenForWrite)

	// Merge Title row. Note that when you create table using UI the title row is merged
	// automatically but when adding using API, we will have to explicitly merge the cells
	pTbl->mergeCells(0,0,0,pTbl->numColumns() - 1);
	
	// Merge for showing header
	// Still more sanity check, we will merge third and fourth row
	if (3 > pTbl->numRows()) return Acad::eNotApplicable;

	// Lets add a row and then merge
	pTbl->insertRows(1,pTbl->rowHeight(1));

	// Merge the cells in steps
	pTbl->mergeCells(1,1,0,1);
	pTbl->mergeCells(1,1,2,pTbl->numColumns() - 1);
	
	// Type in the 'Attributes'
	pTbl->setTextString(1,2,"Attributes");
	
	// Show the block in the cell 1,0
	// Set the block id
	AcDbBlockTable *pBT = NULL;
	AcDbBlockTableRecord *pBTR = NULL;

	// Get the block table	
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBT,AcDb::kForRead);
	// Get the blocktablerecordid
	AcDbObjectId objId;
	pBT->getAt(pBlkName,objId);
	pBT->close();
	
	pTbl->setBlockTableRecordId(1,0,objId,true);
	
	// Lets copy the header rows properties to the third row
	// since we cannot specify a row to be a header row
	AcCmColor col = pTbl->contentColor(AcDb::kHeaderRow);
	AcDbObjectId objID =  pTbl->textStyle(AcDb::kHeaderRow);
	double nHt = pTbl->textHeight(AcDb::kHeaderRow);
	
	for(int nCtr1 = 0;nCtr1 < pTbl->numColumns(); nCtr1++)
	{
		pTbl->setContentColor(2,nCtr1,col);
		pTbl->setTextStyle(objID);
		pTbl->setTextHeight(nHt);
	}	
	
	pTbl->recomputeTableBlock();
	
	return Acad::eOk;
}

//-----------------------------------------------------------------------------
//----- Fit column width with text width
Acad::ErrorStatus fitColumnWidth(AcDbTable *&pTbl,double maxWidth)
{
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled())) PRTMSGRETES(Acad::eNotOpenForWrite)

	for(int nCtr1 = 0;nCtr1 < pTbl->numColumns();nCtr1++)
	{
		double nWidth;
		for(int nCtr2 = 2;nCtr2 < pTbl->numRows();nCtr2++) // Include the second header row
		{
			// Get the textstyle for the data cells
			AcGiTextStyle txtStyle;
			fromAcDbTextStyle(txtStyle,pTbl->textStyle(nCtr2,nCtr1));
			txtStyle.setTextSize(pTbl->textHeight(nCtr2,nCtr1));
			
			// Get the text width
			AcGePoint2d pt = txtStyle.extents(pTbl->textString(nCtr2,nCtr1),Adesk::kTrue,-1,Adesk::kFalse);
			
			if (2 == nCtr2)	
				nWidth = pt.x; 
			else 
				nWidth = (pt.x > nWidth?pt.x:nWidth);	
		}
		
		// Set the column width as we should have the widest width by now
		pTbl->setColumnWidth(nCtr1,(nWidth > maxWidth?maxWidth:nWidth) * 1.2);
	}	
	
	pTbl->recomputeTableBlock();
		
	return Acad::eOk;
}

//-----------------------------------------------------------------------------
//----- Fit row height with text height
Acad::ErrorStatus fitRowHeight(AcDbTable *&pTbl,double maxHeight)
{
	// Sanity check
	if ((NULL == pTbl) || (!pTbl->isWriteEnabled())) PRTMSGRETES(Acad::eNotOpenForWrite)

		for(int nCtr1 = 0;nCtr1 < pTbl->numRows();nCtr1++) // Include all the rows
		{
			double nHeight = pTbl->textHeight(nCtr1,0); // Height of the first column
			for(int nCtr2 = 1;nCtr2 < pTbl->numColumns();nCtr2++) 
			{
				// Get the text height for this cell
				double nCurHeight = pTbl->textHeight(nCtr1,nCtr2);
				nHeight = (nCurHeight > nHeight?nCurHeight:nHeight);	
			}

			// Set the row height with the maximum height
			pTbl->setRowHeight(nCtr1,(nHeight > maxHeight?maxHeight:nHeight) * 3);
		}	

		pTbl->recomputeTableBlock();

		return Acad::eOk;
}