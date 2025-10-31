/////////////////////////////////////////////
// AcDbDatabaseReactor reactors.

#include "StdAfx.h"
#include "StdArx.h"


AsdkDbEmployeeReactor::AsdkDbEmployeeReactor(const bool storeInDocVars, AcApDocument* pDoc)
{
	if (storeInDocVars) {

		assert(DocVars.docData(pDoc).m_pAsdkDbEmployeeReactor == NULL);

		m_pDoc = pDoc;
		m_pDoc->database()->addReactor(this);
		DocVars.docData(m_pDoc).m_pAsdkDbEmployeeReactor = this;

	} else
		m_pDoc = NULL;
}

AsdkDbEmployeeReactor::~AsdkDbEmployeeReactor()
{
	if (m_pDoc) {
		if (DocVars.docData(m_pDoc).m_pAsdkDbEmployeeReactor)
			DocVars.docData(m_pDoc).m_pAsdkDbEmployeeReactor = NULL;
		m_pDoc->database()->removeReactor(this);
		m_pDoc = NULL;
	}
}

void AsdkDbEmployeeReactor::objectAppended(const AcDbDatabase* dwg,
                                           const AcDbObject* dbObj)
{
	// TODO: implement this function.

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
	
    // Ok, this is an employee. Attach the object reactor
	dbObj->addReactor (pEmployeeReactor) ;
}

