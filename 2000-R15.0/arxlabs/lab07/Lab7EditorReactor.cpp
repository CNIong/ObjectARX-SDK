//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#include "acdb.h"
#include "adslib.h"
#include "dbents.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbsymtb.h"
//#include "dbidmap.h"
#include "Lab7EditorReactor.h"
#include "Lab7DatabaseReactor.h"
#include "Lab7ObjectReactor.h"
#include "lab7Utils.h"

#include "Lab7PerDocData.h"

///////////////////////////////////////////////////////
// editor reactor AsdkLab7EditorReactor

static AsdkLab7EditorReactor* pAsdkLab7EditorReactor = NULL;

//call this function to
//create the reactor AsdkLab7EditorReactor
void CreateMyEditorReactor()
{
    pAsdkLab7EditorReactor = new AsdkLab7EditorReactor();
    acedEditor->addReactor( pAsdkLab7EditorReactor);
}

//call this function to
//erase the reactor AsdkLab7EditorReactor
void EraseMyEditorReactor()
{
    acedEditor->removeReactor(pAsdkLab7EditorReactor);
    delete pAsdkLab7EditorReactor;
}

/////////////////////////////////////////////////////
//editor reactor notifications

void AsdkLab7EditorReactor::commandWillStart(const char* cmdStr)
{

	acutPrintf( "\nExecuted command name is [%s]\n", cmdStr );
	
	// Should do a better job by checking the gipedit commands,
	// probably using ads_wcmatch(). 
	// 
    if (stricmp(cmdStr, "move") && stricmp(cmdStr, "rotate")
		&& stricmp(cmdStr, "scale") && stricmp(cmdStr, "stretch"))
      return;   

    //set the global variable...
    chEmployeesInfo.EditCommand = true;

    //...and delete all stored information
	chEmployeesInfo.ChangedIds.setLogicalLength(0);
	chEmployeesInfo.EmployeePositions.setLogicalLength(0);
}

void AsdkLab7EditorReactor::commandEnded(const char* cmdStr)
{
	if( chEmployeesInfo.EditCommand == false)
		return;

    chEmployeesInfo.EditCommand = false;

    //show the previous position
    AcDbBlockReference *pInsert;

    //disable the object reactor
    //(so the object reactor knows that
    // we are changing the object)
	chEmployeesInfo.NoObjReactor = true;

    for (int i = 0; i < chEmployeesInfo.ChangedIds.length(); ++i) {
        if (Acad::eOk == acdbOpenObject(pInsert, chEmployeesInfo.ChangedIds.at(i), AcDb::kForWrite)) {
            AcGePoint3d newPos = pInsert->position(),
                        oldPos = chEmployeesInfo.EmployeePositions.at(i);
			// resetting the position to the original one
			//
			if(newPos != oldPos)
			{
				pInsert->setPosition(oldPos);
				ads_printf("\nEMPLOYEE has been reset to its original location.");
			}
            //now we can get the employee extension dictionary
            //to get more information about this EMPLOYEE.
            AcDbDictionary* pExtDictEmp;
            if (Acad::eOk == getExtDictEmpOfObj(pExtDictEmp, pInsert)) {
                //iterate this dictionary and get all entries
                AcDbDictionaryIterator* pDictIter = pExtDictEmp->newIterator();
                if (pDictIter) {
                    AcDbObject* pExtDictEmpObj;
                    for (; !pDictIter->done(); pDictIter->next()) {
                        if (Acad::eOk != pDictIter->getObject(pExtDictEmpObj, AcDb::kForRead))
                            continue;
                        ads_printf("\nExtension dictionary contains: %s",
                                    pExtDictEmpObj->isA()->name());
                        pExtDictEmpObj->close();
                    }
                    delete pDictIter;
                } 
                pExtDictEmp->close();
            }
			else{
				ads_printf("\nNo employee extension dictionary found.");
			}
            pInsert->close();
        }
    }

    //enable the database reactor
    chEmployeesInfo.NoObjReactor = false;
}


