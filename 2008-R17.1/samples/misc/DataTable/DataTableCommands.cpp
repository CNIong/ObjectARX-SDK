//
//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
//
//
// ObjectARX defined commands
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"

#include "aced.h"
#include "acedads.h"
#include "adslib.h"
#include "acutmem.h"
#include "rxregsvc.h"
#include "dbDataTable.h"
#include "dbmain.h"
#include "dbapserv.h"
#include "dbsymutl.h"
#include "dbxrecrd.h"
#include "acdbabb.h"
#include "geassign.h"



#define DATATABLES_DICT _T("ASDK_DATATABLES_DICT")

//-----------------------------------------------------------------------------
// This is command LISTTABLES
//List the names of all the datatables in the DWG.
void AsdkListTables()
{
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbDictionary* pNOD = NULL; 
	Acad::ErrorStatus es = acdbOpenObject( pNOD, pDb->namedObjectsDictionaryId(), kForWrite);
	AcDbDictionary* pDT = NULL;
	if( pNOD->getAt( DATATABLES_DICT, (AcDbObject*&)pDT, kForRead ) == Acad::eKeyNotFound ) 
	{
		acutPrintf( _T("\nThere are no tables in the drawing.") );
		pNOD->close();
	}
	else
	{
        acutPrintf( _T("\nTables: ") );
		pNOD->close();
		AcDbDictionaryIterator* pDTIter = pDT->newIterator();
		for (; !pDTIter->done(); )
		{
			AcDbDataTable* pTable;
			pDTIter->getObject( (AcDbObject*&)pTable, AcDb::kForRead );
			acutPrintf( _T("%s"), pTable->tableName() );
			pTable->close();
			pDTIter->next();
			if( pDTIter->done() )
				acutPrintf( _T(".") );
			else
				acutPrintf( _T(", ") );
		}
		delete pDTIter;
		pDT->close();
	}   
}

//Get the object id of the DataTable using its name
AcDbObjectId getDataTableId( TCHAR* DataTableName )
{
	Acad::ErrorStatus es;
	AcDbObjectId retId = AcDbObjectId::kNull;

	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbDictionary* pNOD = NULL;
	//Open named objects dictionary
	es = acdbOpenObject( pNOD, pDb->namedObjectsDictionaryId(), kForWrite );
	if( es == Acad::eOk )
	{
		AcDbDictionary* pDT = NULL;
		//Get the dictionary DATATABLES_DICT in named objects dictionary.
		//This application stores all its DataTables in DATATABLES_DICT
		if( pNOD->getAt( DATATABLES_DICT, (AcDbObject*&)pDT, kForRead ) == Acad::eOk ) 
		{
			AcDbObjectId DataTableId;
			if( pDT->getAt( DataTableName, DataTableId ) == Acad::eOk )
				retId = DataTableId;
			pDT->close();
		}
		pNOD->close();
	}
	return retId;
}

//Add a column to a data-table. Return true if succeeds, otherwise, return false.
Adesk::Boolean addColumn( AcDbDataTable* pTable )
{
	TCHAR colName[133];
	TCHAR type[133];
	//Get column name
    if( acedGetString( 1, _T("Enter column name: "),  colName ) == RTNORM )
	{
		
		acedInitGet( 0, _T("Int Double Char Point Objectid Bool Vector") );
		//Get column type
        int ret = acedGetKword( _T("\nEnter column type [Int/Double/Char/Point/Objectid/Bool/Vector]: "), type );
		if( ret == RTNORM )
		{
			Acad::ErrorStatus es;
		    if( !_tcscmp( type,_T("Int") ))
				es = pTable->appendColumn( AcDbDataCell::kInteger, colName );
			else if( !_tcscmp(  type, _T("Double") ))
				es = pTable->appendColumn( AcDbDataCell::kDouble, colName );
			else if( !_tcscmp( type, _T("Char") ))
				es = pTable->appendColumn( AcDbDataCell::kCharPtr, colName );
			else if( !_tcscmp( type, _T("Point") ))
				es = pTable->appendColumn( AcDbDataCell::kPoint, colName );
			else if( !_tcscmp( type,_T("Objectid") ))
				es = pTable->appendColumn( AcDbDataCell::kObjectId, colName );
			else if( !_tcscmp( type, _T("Bool") ))
				es = pTable->appendColumn( AcDbDataCell::kBool, colName );
			else if( !_tcscmp( type, _T("Vector") ))
				es = pTable->appendColumn( AcDbDataCell::kVector, colName );
			if( es == Acad::eOk )
				return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
// This is command ADDTABLE
void AsdkAddTable()
{
	AsdkListTables();

	int nRows = 20;
	int nCols = 0;
	TCHAR tableName[133];
	AcDbDataTable* pTable = NULL;
	do {
		//Get the name of the table from user
        if( acedGetString ( 1, _T("\nEnter table name: "), tableName ) == RTNORM )
		{
			//If the table name is empty string, ask user for a different name.
			if( !_tcscmp( tableName, _T("") ))
				acutPrintf(_T("\nName cannot be blank. Please enter a name."));
			else
			{
				//If the table already exist, ask user for a different name.
				if( getDataTableId( tableName )!= AcDbObjectId::kNull )
					acutPrintf( _T("\nTable %s already exists, please enter another name."), tableName );
				else {
					//Create a new table with the name user specified.
					pTable = new AcDbDataTable;
					pTable->setTableName( tableName );
				}
			}
		}
		else
			return;
	}
	while( !pTable );

	//Set the default number of rows in the table and the row growing size.
	pTable->setNumRowsPhysicalSize( nRows );
	pTable->setNumRowsGrowSize( nRows );

	//Ask user for the number of columns in the table
	acedInitGet( RSG_NOZERO | RSG_NONEG, NULL );
    if( acedGetInt( _T("\nNumber of columns: "), &nCols ) != RTNORM )
	{
		delete pTable;
		return;
	}

	//Add each column to the table.
	for( int i=0; i < nCols ;i++ )
	{
        acutPrintf( _T("\nColumn %d: "), i );
		if( !addColumn( pTable ))
		{
			delete pTable;
			return;
		}
	}
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbDictionary* pNOD = NULL;
	//Get named objects dictionary
	Acad::ErrorStatus es = acdbOpenObject( pNOD, pDb->namedObjectsDictionaryId(), kForRead );
	if( es != Acad::eOk )
	{
		delete pTable;
		return;
	}
	
	AcDbDictionary* pDT = NULL;
	//Get ASDK_DATABATLES_DICT dictionary. If it doesn't exist, create one under named objects dictioanry.
	es = pNOD->getAt( DATATABLES_DICT, (AcDbObject*&)pDT, kForWrite );
	if( es == Acad::eKeyNotFound ) 
	{
		es = pNOD->upgradeOpen();
		if( es != Acad::eOk )
			acutPrintf(_T("\nCould not open named objects dictionary for write.") );
		else {
			pDT = new AcDbDictionary;
			AcDbObjectId dictId;
			if( pNOD->setAt( DATATABLES_DICT, pDT, dictId ) != Acad::eOk )
			{
				acutPrintf(_T("\nCould not add dictionary to named objects dictionary.") );
				pNOD->close();
				delete pDT;
				delete pTable;
				return;
			}
		}
	}
	pNOD->close();
	AcDbObjectId oId;

	//Add the dataTable to DATATABLE_DICT dictionary.
	if( pDT->setAt( tableName, pTable, oId ) != Acad::eOk )
	{
		acutPrintf( _T("\nCould not add table to named objects dictionary.") );
		pDT->close();
		delete pTable;
		return;
	}
	else
		acutPrintf( _T("\nSuccessfully added table %s."), tableName );
	pDT->close();
	pTable->close();
	return;	
}

//-----------------------------------------------------------------------------
// This is command DELETETABLE
void AsdkDeleteTable()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	TCHAR tableName[133];
    if( acedGetString ( 1, _T("\nEnter table name: "),  tableName ) == RTNORM )
	{
		// Look up table in the named objects dictionary 
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		AcDbDictionary* pNOD = NULL;   
		es = acdbOpenObject( pNOD, pDb->namedObjectsDictionaryId() ,kForWrite );

		//Look up DATATABLES_DICT dictionary in Named objects dictionary.
		AcDbDictionary* pDT = NULL;
		es = pNOD->getAt( DATATABLES_DICT, (AcDbObject*&)pDT, kForRead ); 
		pNOD->close();
		if( es == Acad::eOk )
		{
			//Look up the datatable in the DATATABLE_DICT dictionary
			if( pDT->has( tableName ))
			{
				//Delete the datatable
				es = pDT->upgradeOpen();
				if( es == Acad::eOk )
				{
					es = pDT->remove( tableName );
					if( es == Acad::eOk )
						acutPrintf( _T("\nSuccessfully deleted table %s."), tableName );
				}
			}
			pDT->close();
		}		 
	}
	else
		acutPrintf( _T("\nTable %s not found."), tableName );
}

//Print table info, such as number of rows, column names and types.
void listColumnInfo( AcDbDataTable *pTable )
{
	// Print the number of columns
	Adesk::UInt32 numCols = pTable->numColumns();
    acutPrintf( _T("\nNumber of columns: %d"), numCols );

	// Print the column names & types
	for ( Adesk::UInt32 j = 0; j < numCols; j++ )
	{
		if( j == 0 )
            acutPrintf( _T("\nColumn names & types: ") );
		else if( j > 0 )
			acutPrintf( _T(", ") );
		 const AcDbDataColumn* pCol = NULL;
		 pTable->getColumnAt( j, pCol );
		 acutPrintf( pCol->columnName() );
		 switch ( pCol->columnType() )
		 {
			case AcDbDataCell::kBool:
				acutPrintf( _T("(bool)") );
				break;
			case AcDbDataCell::kInteger:
				acutPrintf( _T("(int)") );
				break;
			case AcDbDataCell::kDouble:
				acutPrintf( _T("(double)") );
				break;
			case AcDbDataCell::kCharPtr:
				acutPrintf( _T("(char)"));
				break;
			case AcDbDataCell::kPoint:
				acutPrintf( _T("(point)") );
				break;
			case AcDbDataCell::kVector:
				acutPrintf( _T("(vector)") );
				break;
			case AcDbDataCell::kObjectId:
				acutPrintf( _T("(oId)") );
				break;
			default:
				RXASSERT( false );
		}
	}
}

//-----------------------------------------------------------------------------
// This is command LISTCOLUMNS
void AsdkListColumns()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	TCHAR tableName[133];
    if( acedGetString ( 1, _T("\nEnter table name: "),  tableName ) == RTNORM )
	{
		//Get the objectId of the table
		AcDbObjectId tableId = AcDbObjectId::kNull;
		tableId = getDataTableId( tableName );
		if( tableId != AcDbObjectId::kNull )
		{
			AcDbDataTable* pTable = NULL;
			es = acdbOpenObject( pTable, tableId,kForRead);
			if( es == Acad::eOk && pTable )
			{
				//Print out column names and types.
				listColumnInfo( pTable );
				pTable->close();
			}
			else
				acutPrintf( _T("\nCould not open table %s."), tableName );
		}
		else
			acutPrintf( _T("\nTable %s not found."), tableName );
		}
	else
		return;
}

//-----------------------------------------------------------------------------
// This is command ADDCOLUMN
void AsdkAddColumn()
{
	AsdkListTables();

	TCHAR tableName[133];
	AcDbDataTable* pTable = NULL;
	Acad::ErrorStatus es;
    if( acedGetString( 1, _T("\nEnter table name: "), tableName ) == RTNORM )
	{
		// Look up table in the Named Objects Dictionary
		AcDbObjectId tableId;
		tableId = getDataTableId( tableName );
		if( tableId != AcDbObjectId::kNull )
		{
			es = acdbOpenObject( pTable, tableId, kForWrite );
			if( es == Acad::eOk && pTable )
			{
				listColumnInfo( pTable );

				//Append the column
				acutPrintf( _T("\n") );
				if( addColumn( pTable ))
					acutPrintf( _T("\nColumn added successfully to table %s."), pTable->tableName() );
				pTable->close();	
			}
			else
				acutPrintf( _T("\nCould not open table %s."), tableName );	
		}
		else
			acutPrintf( _T("\nTable %s not found."), tableName );
	}
	return;
}

//Print the contents of a datatable.
void listRowInfo( AcDbDataTable* pTable )
{
	// Print the number of rows
	Adesk::UInt32 numRows = pTable->numRows();
    acutPrintf( _T("\nNumber of rows: %d"), numRows );
    
	// Print rows
	for( Adesk::UInt32 i = 0; i < pTable->numRows(); i++ )
	{
		AcDbDataCellArray row;
		pTable->getRowAt( i, row );
        acutPrintf( _T("\nRow %d: "), i );
		for( Adesk::UInt32 j = 0; j < pTable->numColumns(); j++ )
		{
			if( j > 0 )
				acutPrintf( _T(", ") );
			// Print the row values
			AcDbDataCell cell;
			cell = row.at( j );
			switch ( cell.type() )
			{
				case AcDbDataCell::kBool:
					if( (bool)cell )
						acutPrintf( _T("true") );
					else
						acutPrintf( _T("false") );
					break;
				case AcDbDataCell::kInteger:
					acutPrintf( _T("%d"), (int)cell );
					break;
				case AcDbDataCell::kDouble:
					acutPrintf( _T("%lf"), (double)cell );
					break;
				case AcDbDataCell::kCharPtr:
					acutPrintf( _T("%s"), (const TCHAR*)cell );
					break;
				case AcDbDataCell::kPoint:
					{ 
						AcGePoint3d& pt = (AcGePoint3d&)cell;
						acutPrintf( _T("(%lf, %lf, %lf)"), pt.x, pt.y, pt.z );
					}
					break;
				case AcDbDataCell::kVector:
					{ 
						AcGeVector3d vec = (AcGeVector3d&)cell;
						acutPrintf( _T("(%lf, %lf, %lf)"), vec.x, vec.y, vec.z );
					}
					break;
				case AcDbDataCell::kObjectId:
					{
						AcDbObjectId id = (AcDbObjectId) cell;
						acutPrintf( _T("%ld\t"), id.asOldId() );
					}
					break;

				default:
					RXASSERT( false );
            }
        }
    }
}

//-----------------------------------------------------------------------------
// This is command LISTROWS
void AsdkListRows()
{
	AsdkListTables();

	TCHAR tableName[133];
	//Ask users to input the name of the table he want to print.
    if( acedGetString ( 1, _T("\nEnter table name: "),  tableName ) == RTNORM)
	{
		AcDbObjectId tableId;
		//Get the object Id of the table.
		tableId = getDataTableId( tableName );
		if( tableId != AcDbObjectId::kNull )
		{
			AcDbDataTable* pTable;
			//open the table.
			acdbOpenObject( pTable, tableId, kForRead );
			if( pTable )
			{
				//Print the table.
				listRowInfo( pTable );
				pTable->close();
				return;
			}
		}
		else
			acutPrintf( _T("\nTable %s not found."), tableName );
	}
}

//-----------------------------------------------------------------------------
// This is command ADDROW
void AsdkAddRow()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	TCHAR tableName[133];
    if( acedGetString ( 1, _T("\nEnter table name: "), tableName ) == RTNORM )
	{
		AcDbObjectId tableId = AcDbObjectId::kNull;
		tableId = getDataTableId( tableName );
		if( tableId != AcDbObjectId::kNull )
		{
			AcDbDataTable* pTable = NULL;
			es = acdbOpenObject( pTable, tableId, kForWrite );
			if( es == Acad::eOk && pTable )
			{
				//List table info such as rows, column names and types.
				listColumnInfo( pTable );

				//Iterate through columns and ask user to input data for each of them one by one.
				AcDbDataCellArray row;
				AcDbDataCell cell;
				int ret;
				bool bBreakLoop = false;
				for ( Adesk::UInt32 i = 0; i < pTable->numColumns(); i++ )
				{
					const AcDbDataColumn* pCol = NULL;
					pTable->getColumnAt( i, pCol );
					acutPrintf( _T("\nColumn %i - "), i );
					switch ( pCol->columnType() )
					{
						case AcDbDataCell::kBool:
							{
								bool bValue;
								TCHAR Input[10];
								acedInitGet( 0, _T("True False") );
                                ret = acedGetKword( _T("enter boolean [True/False]: "), Input );
								if( ret == RTNORM )
								{
									if( !_tcscmp( Input, _T("True") ))
										bValue =  true;
									else
										bValue = false;
									cell = bValue;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						case AcDbDataCell::kInteger:
							{
								int iValue;
                                ret = acedGetInt( _T("enter integer: "), &iValue );
								if( ret == RTNORM )
								{
									cell = iValue;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						case AcDbDataCell::kDouble:
							{
								double dValue;
                                ret = acedGetReal( _T("enter real: "), &dValue );
								if( ret == RTNORM )
								{
									cell = dValue;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						case AcDbDataCell::kCharPtr:
							{
								TCHAR cValue[100];
                                ret = acedGetString( 1, _T("enter string: "), cValue );
								if( ret == RTNORM )
								{
									cell = cValue;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						case AcDbDataCell::kPoint:
							{
								ads_point pt;
                                ret = acedGetPoint( NULL, _T("enter point: "), pt );
								AcGePoint3d position( asPnt3d( pt ));
								if( ret == RTNORM )
								{
									cell = position;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						case AcDbDataCell::kVector:
							{ 
								double XX, YY, ZZ;
                                if( acedGetReal( _T("enter X value of vector: "), &XX ) == RTNORM )
								{
									acutPrintf( _T("\nColumn %i - "), i );
                                    if( acedGetReal( _T("enter Y value of vector: "), &YY ) == RTNORM )
									{
										acutPrintf( _T("\nColumn %i - "), i );
                                        if( acedGetReal( _T("enter Z value of vector: "), &ZZ ) == RTNORM )
										{
											AcGeVector3d vValue( XX, YY, ZZ );
											cell = vValue;
											row.append( cell );
										}
										else
											bBreakLoop = true;
									}
									else
										bBreakLoop = true;
								}
								else
									bBreakLoop = true;
							}
							break;
                        case AcDbDataCell::kObjectId:
							{
								ads_name ename; 
								ads_point pt; 
                                if( acedEntSel( _T("select entity: "), ename, pt ) == RTNORM )
								{
									AcDbObjectId objId;
									acdbGetObjectId( objId, ename );
									cell = objId;
									row.append( cell );
								}
								else
									bBreakLoop = true;
							}
							break;
						default:
							RXASSERT( false );
					}
					if( bBreakLoop )
					{
						acutPrintf( _T("\nCommand cancelled - row not added successfully to table %s."), pTable->tableName() );
						break;
					}
				}
				if( !bBreakLoop )
				{
					es = pTable->appendRow( row );
					if( es == Acad::eOk )
					{
						acutPrintf( _T("\nRow added successfully to table %s."), pTable->tableName() );
					}
				}
				pTable->close();
			}
			else
				acutPrintf( _T("\nCould not open the table.") );
		}
		else
			acutPrintf( _T("\nTable %s not found."), tableName );
	}
}

//-----------------------------------------------------------------------------
//This is the command DELETEROW
void AsdkDeleteRow()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	TCHAR tableName[133];
    if( acedGetString ( 1, _T("\nEnter table name: "),  tableName ) == RTNORM )
	{
		AcDbObjectId tableId = AcDbObjectId::kNull;
		tableId = getDataTableId( tableName );
		if( tableId != AcDbObjectId::kNull )
		{
			AcDbDataTable* pTable = NULL;
			es = acdbOpenObject( pTable, tableId, kForWrite );
			if( es == Acad::eOk && pTable ) 
			{
				//Get the row number that user wants to delete
				listRowInfo( pTable );
				int row;
				acedInitGet( RSG_NONEG, NULL );
                if( acedGetInt( _T("\nEnter the number of the row to delete: "), &row ) == RTNORM )
				{
					//Delete row.
					Adesk::UInt32 row2 = row;	
					if( pTable->removeRowAt( row2 ) == Acad::eOk )
						acutPrintf( _T("\nSuccessfully deleted row %d from table %s."), row, pTable->tableName() );
					else
						acutPrintf( _T("\nThis row is out of the range of the table.") );
					pTable->close();
				}
				else
					acutPrintf( _T("\nCould not open the table.") );
			}
			else
				acutPrintf( _T("\nTable %s not found."), tableName );
		}
	}
}
