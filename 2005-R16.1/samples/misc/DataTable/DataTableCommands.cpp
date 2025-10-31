//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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

#define DATATABLES_DICT "ASDK_DATATABLES_DICT"

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
		acutPrintf( "\nThere are no tables in the drawing." );
		pNOD->close();
	}
	else
	{
		acutPrintf( "\nTables: " );
		pNOD->close();
		AcDbDictionaryIterator* pDTIter = pDT->newIterator();
		for (; !pDTIter->done(); )
		{
			AcDbDataTable* pTable;
			pDTIter->getObject( (AcDbObject*&)pTable, AcDb::kForRead );
			acutPrintf( "%s", pTable->tableName() );
			pTable->close();
			pDTIter->next();
			if( pDTIter->done() )
				acutPrintf( "." );
			else
				acutPrintf( ", " );
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
	char colName[133];
	char type[133];
	//Get column name
	if( acedGetString( 1, "Enter column name: ",  colName ) == RTNORM )
	{
		
		acedInitGet( 0, "Int Double Char Point Objectid Bool Vector" );
		//Get column type
		int ret = acedGetKword( "\nEnter column type [Int/Double/Char/Point/Objectid/Bool/Vector]: ", type );
		if( ret == RTNORM )
		{
			Acad::ErrorStatus es;
		    if( !strcmp( type,"Int" ))
				es = pTable->appendColumn( AcDbDataCell::kInteger, colName );
			else if( !strcmp(  type, "Double" ))
				es = pTable->appendColumn( AcDbDataCell::kDouble, colName );
			else if( !strcmp( type, "Char" ))
				es = pTable->appendColumn( AcDbDataCell::kCharPtr, colName );
			else if( !strcmp( type, "Point" ))
				es = pTable->appendColumn( AcDbDataCell::kPoint, colName );
			else if( !strcmp( type,"Objectid" ))
				es = pTable->appendColumn( AcDbDataCell::kObjectId, colName );
			else if( !strcmp( type, "Bool" ))
				es = pTable->appendColumn( AcDbDataCell::kBool, colName );
			else if( !strcmp( type, "Vector" ))
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
	char tableName[133];
	AcDbDataTable* pTable = NULL;
	do {
		//Get the name of the table from user
		if( acedGetString ( 1, "\nEnter table name: ", tableName ) == RTNORM )
		{
			//If the table name is empty string, ask user for a different name.
			if( !strcmp( tableName, "" ))
				acutPrintf("\nName cannot be blank. Please enter a name.");
			else
			{
				//If the table already exist, ask user for a different name.
				if( getDataTableId( tableName )!= AcDbObjectId::kNull )
					acutPrintf( "\nTable %s already exists, please enter another name.", tableName );
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
	if( acedGetInt( "\nNumber of columns: ", &nCols ) != RTNORM )
	{
		delete pTable;
		return;
	}

	//Add each column to the table.
	for( int i=0; i < nCols ;i++ )
	{
		acutPrintf( "\nColumn %d: ", i );
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
			acutPrintf("\nCould not open named objects dictionary for write." );
		else {
			pDT = new AcDbDictionary;
			AcDbObjectId dictId;
			if( pNOD->setAt( DATATABLES_DICT, pDT, dictId ) != Acad::eOk )
			{
				acutPrintf("\nCould not add dictionary to named objects dictionary." );
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
		acutPrintf( "\nCould not add table to named objects dictionary." );
		pDT->close();
		delete pTable;
		return;
	}
	else
		acutPrintf( "\nSuccessfully added table %s.", tableName );
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
	char tableName[133];
	if( acedGetString ( 1, "\nEnter table name: ",  tableName ) == RTNORM )
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
						acutPrintf( "\nSuccessfully deleted table %s.", tableName );
				}
			}
			pDT->close();
		}		 
	}
	else
		acutPrintf( "\nTable %s not found.", tableName );
}

//Print table info, such as number of rows, column names and types.
void listColumnInfo( AcDbDataTable *pTable )
{
	// Print the number of columns
	Adesk::UInt32 numCols = pTable->numColumns();
	acutPrintf( "\nNumber of columns: %d", numCols );

	// Print the column names & types
	for ( Adesk::UInt32 j = 0; j < numCols; j++ )
	{
		if( j == 0 )
			acutPrintf( "\nColumn names & types: " );
		else if( j > 0 )
			acutPrintf( ", " );
		 AcDbDataColumn* pCol = NULL;
		 pTable->getColumnAt( j, pCol );
		 acutPrintf( pCol->columnName() );
		 switch ( pCol->columnType() )
		 {
			case AcDbDataCell::kBool:
				acutPrintf( "(bool)" );
				break;
			case AcDbDataCell::kInteger:
				acutPrintf( "(int)" );
				break;
			case AcDbDataCell::kDouble:
				acutPrintf( "(double)" );
				break;
			case AcDbDataCell::kCharPtr:
				acutPrintf( "(char)");
				break;
			case AcDbDataCell::kPoint:
				acutPrintf( "(point)" );
				break;
			case AcDbDataCell::kVector:
				acutPrintf( "(vector)" );
				break;
			case AcDbDataCell::kObjectId:
				acutPrintf( "(oId)" );
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
	char tableName[133];
	if( acedGetString ( 1, "\nEnter table name: ",  tableName ) == RTNORM )
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
				acutPrintf( "\nCould not open table %s.", tableName );
		}
		else
			acutPrintf( "\nTable %s not found.", tableName );
		}
	else
		return;
}

//-----------------------------------------------------------------------------
// This is command ADDCOLUMN
void AsdkAddColumn()
{
	AsdkListTables();

	char tableName[133];
	AcDbDataTable* pTable = NULL;
	Acad::ErrorStatus es;
	if( acedGetString( 1, "\nEnter table name: ", tableName ) == RTNORM )
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
				acutPrintf( "\n" );
				if( addColumn( pTable ))
					acutPrintf( "\nColumn added successfully to table %s.", pTable->tableName() );
				pTable->close();	
			}
			else
				acutPrintf( "\nCould not open table %s.", tableName );	
		}
		else
			acutPrintf( "\nTable %s not found.", tableName );
	}
	return;
}

//Print the contents of a datatable.
void listRowInfo( AcDbDataTable* pTable )
{
	// Print the number of rows
	Adesk::UInt32 numRows = pTable->numRows();
	acutPrintf( "\nNumber of rows: %d", numRows );
    
	// Print rows
	for( Adesk::UInt32 i = 0; i < pTable->numRows(); i++ )
	{
		AcDbDataCellArray row;
		pTable->getRowAt( i, row );
		acutPrintf( "\nRow %d: ", i );
		for( Adesk::UInt32 j = 0; j < pTable->numColumns(); j++ )
		{
			if( j > 0 )
				acutPrintf( ", " );
			// Print the row values
			AcDbDataCell cell;
			cell = row.at( j );
			switch ( cell.type() )
			{
				case AcDbDataCell::kBool:
					if( (bool)cell )
						acutPrintf( "true" );
					else
						acutPrintf( "false" );
					break;
				case AcDbDataCell::kInteger:
					acutPrintf( "%d", (int)cell );
					break;
				case AcDbDataCell::kDouble:
					acutPrintf( "%lf", (double)cell );
					break;
				case AcDbDataCell::kCharPtr:
					acutPrintf( "%s", (const char*)cell );
					break;
				case AcDbDataCell::kPoint:
					{ 
						AcGePoint3d& pt = (AcGePoint3d&)cell;
						acutPrintf( "(%lf, %lf, %lf)", pt.x, pt.y, pt.z );
					}
					break;
				case AcDbDataCell::kVector:
					{ 
						AcGeVector3d vec = (AcGeVector3d&)cell;
						acutPrintf( "(%lf, %lf, %lf)", vec.x, vec.y, vec.z );
					}
					break;
				case AcDbDataCell::kObjectId:
					{
						AcDbObjectId id = (AcDbObjectId) cell;
						acutPrintf( "%ld\t", id.asOldId() );
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

	char tableName[133];
	//Ask users to input the name of the table he want to print.
	if( acedGetString ( 1, "\nEnter table name: ",  tableName ) == RTNORM)
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
			acutPrintf( "\nTable %s not found.", tableName );
	}
}

//-----------------------------------------------------------------------------
// This is command ADDROW
void AsdkAddRow()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	char tableName[133];
	if( acedGetString ( 1, "\nEnter table name: ", tableName ) == RTNORM )
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
					AcDbDataColumn* pCol = NULL;
					pTable->getColumnAt( i, pCol );
					acutPrintf( "\nColumn %i - ", i );
					switch ( pCol->columnType() )
					{
						case AcDbDataCell::kBool:
							{
								bool bValue;
								char Input[10];
								acedInitGet( 0, "True False" );
								ret = acedGetKword( "enter boolean [True/False]: ", Input );
								if( ret == RTNORM )
								{
									if( !strcmp( Input, "True" ))
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
								ret = acedGetInt( "enter integer: ", &iValue );
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
								ret = acedGetReal( "enter real: ", &dValue );
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
								char cValue[100];
								ret = acedGetString( 1, "enter string: ", cValue );
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
								ret = acedGetPoint( NULL, "enter point: ", pt );
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
								if( acedGetReal( "enter X value of vector: ", &XX ) == RTNORM )
								{
									acutPrintf( "\nColumn %i - ", i );
									if( acedGetReal( "enter Y value of vector: ", &YY ) == RTNORM )
									{
										acutPrintf( "\nColumn %i - ", i );
										if( acedGetReal( "enter Z value of vector: ", &ZZ ) == RTNORM )
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
								if( acedEntSel( "select entity: ", ename, pt ) == RTNORM )
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
						acutPrintf( "\nCommand cancelled - row not added successfully to table %s.", pTable->tableName() );
						break;
					}
				}
				if( !bBreakLoop )
				{
					es = pTable->appendRow( row );
					if( es == Acad::eOk )
					{
						acutPrintf( "\nRow added successfully to table %s.", pTable->tableName() );
					}
				}
				pTable->close();
			}
			else
				acutPrintf( "\nCould not open the table." );
		}
		else
			acutPrintf( "\nTable %s not found.", tableName );
	}
}

//-----------------------------------------------------------------------------
//This is the command DELETEROW
void AsdkDeleteRow()
{
	AsdkListTables();

	Acad::ErrorStatus es;
	char tableName[133];
	if( acedGetString ( 1, "\nEnter table name: ",  tableName ) == RTNORM )
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
				if( acedGetInt( "\nEnter the number of the row to delete: ", &row ) == RTNORM )
				{
					//Delete row.
					Adesk::UInt32 row2 = row;	
					if( pTable->removeRowAt( row2 ) == Acad::eOk )
						acutPrintf( "\nSuccessfully deleted row %d from table %s.", row, pTable->tableName() );
					else
						acutPrintf( "\nThis row is out of the range of the table." );
					pTable->close();
				}
				else
					acutPrintf( "\nCould not open the table." );
			}
			else
				acutPrintf( "\nTable %s not found.", tableName );
		}
	}
}
