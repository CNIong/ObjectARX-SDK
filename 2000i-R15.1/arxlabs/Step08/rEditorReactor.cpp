/////////////////////////////////////////////
// AcEditorReactor reactors.

#include "StdAfx.h"
#include "StdArx.h"


AsdkEdEmployeeReactor::AsdkEdEmployeeReactor(const bool autoInitAndRelease)
{
	m_autoInitAndRelease = autoInitAndRelease;
	if (m_autoInitAndRelease)
		if (NULL != acedEditor)
			acedEditor->addReactor(this);
		else
			m_autoInitAndRelease = false;
}

AsdkEdEmployeeReactor::~AsdkEdEmployeeReactor()
{
	if (m_autoInitAndRelease)
		if (NULL != acedEditor)
			acedEditor->removeReactor(this);
}

void AsdkEdEmployeeReactor::commandWillStart(const char* cmdStr)
{
	// TODO: implement this function.

	// Check whether one of our monitored commands starts
    if (   strcmp (cmdStr, "MOVE") && strcmp (cmdStr, "ROTATE")
		&& strcmp (cmdStr, "SCALE") && strcmp (cmdStr, "STRETCH")
		&& strcmp (cmdStr, "GRIP_STRETCH")
	) {
		return ;
	}

    // Set the global variable...
	DocVars.docData ().m_editCommand =true ;
	DocVars.docData ().m_doRepositioning =false ;

    // ...and delete all stored information
	DocVars.docData ().m_changedObjects.setLogicalLength (0) ;
	DocVars.docData ().m_employeePositions.setLogicalLength (0) ;
}

void AsdkEdEmployeeReactor::commandEnded(const char* cmdStr)
{
	// TODO: implement this function.

	// Was one of our monitored commands active
	if ( DocVars.docData ().m_editCommand == false )
		return;

	DocVars.docData ().m_editCommand =false ;

	// disable the object reactor
	// (so the object reactor knows that we are changing the object)
	DocVars.docData ().m_doRepositioning =true ;

	// Reset to previous position
	AcDbBlockReference *pInsert ;
	for ( int i =0 ; i < DocVars.docData ().m_changedObjects.length () ; ++i ) {
		if ( acdbOpenObject (pInsert, DocVars.docData ().m_changedObjects.at (i), AcDb::kForWrite) == Acad::eOk ) {
			AcGePoint3d newPos =pInsert->position () ;
			AcGePoint3d oldPos =DocVars.docData ().m_employeePositions.at (i) ;
			// Resetting the position to the original one
			if ( newPos != oldPos ) {
				pInsert->setPosition (oldPos) ;
				acutPrintf ("\nEMPLOYEE has been reset to its original location.") ;
			}
			pInsert->close () ;
		}
	}
}

