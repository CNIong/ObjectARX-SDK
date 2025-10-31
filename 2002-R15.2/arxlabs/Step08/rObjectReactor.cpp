/////////////////////////////////////////////
// AcDbObjectReactor reactors.

#include "StdAfx.h"
#include "StdArx.h"


void AsdkEmployeeReactor::openedForModify(const AcDbObject* dbObj)
{
	// TODO: implement this function.

	if ( DocVars.docData ().m_doRepositioning )
		return ;

	// If none of our monitored commands is active return
	if ( !DocVars.docData ().m_editCommand )
		return ;

    // dbObj should be of type AcDbBlockReference
	// whose name is "EMPLOYEE". This check is not absolutely necessary,
	// since our application is adding the reactor to employee objects
	// only, we know this notificatin can only come from such an object.

	AcDbBlockReference *pInsert =AcDbBlockReference::cast (dbObj) ;
	if ( !pInsert )
		return ;

	// Get the ObjectId of the BlockTableRecord where the reference is defined
	AcDbObjectId blockId =pInsert->blockTableRecord () ;
	AcDbBlockTableRecord *pBlockTableRecord ;
	if ( acdbOpenAcDbObject ((AcDbObject *&)pBlockTableRecord, blockId, AcDb::kForRead) != Acad::eOk ) {
		acutPrintf ("\nCannot open block table record!") ;
		return ;
	}

	const char *blockName ;
	pBlockTableRecord->getName (blockName) ;
	pBlockTableRecord->close () ;

	if ( strcmp (blockName, "EMPLOYEE") )
		return ; // Not an employee

    // Store the objectID and the position
	DocVars.docData ().m_changedObjects.append (pInsert->objectId ()) ;
	DocVars.docData ().m_employeePositions.append (pInsert->position ()) ;
}

