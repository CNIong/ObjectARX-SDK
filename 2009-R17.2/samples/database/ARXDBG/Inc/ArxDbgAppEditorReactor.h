//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

#ifndef ARXDBG_ARXDBGAPPEDREACTOR_H
#define ARXDBG_ARXDBGAPPEDREACTOR_H

#include "ArxDbgCloneSet.h"

/****************************************************************************
**
**  CLASS ArxDbgAppEditorReactor:
**      needed for our app itself to track when databases are constructed,
**  or destructed so we can put our db reactor on it.
**
**  **jma
**
*************************************/

class ArxDbgAppEditorReactor : public AcEditorReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgAppEditorReactor);

        // messages that are sent by notification
    virtual void    databaseConstructed(AcDbDatabase*);
    virtual void    databaseToBeDestroyed(AcDbDatabase* pDwg);

	virtual void	endDeepClone(AcDbIdMapping& idMap);

    virtual void    beginDeepCloneXlation(AcDbIdMapping& pIdMap, Acad::ErrorStatus* pRetStatus);

		// used by our test function to add extra objects to the cloneSet of things
		// to be included in Wblock.
	ArxDbgCloneSet&	cloneSet()		{ return m_cloneSet; }

private:
        // singleton class, so no one can call constructor/destructors
                ArxDbgAppEditorReactor();
    virtual     ~ArxDbgAppEditorReactor();

        // data members
    ArxDbgCloneSet		m_cloneSet;
    AcDbObjectIdArray	m_didTheseDicts;

		// helper functions
    void    insertCloneOwnerDict(const AcDbObjectId& dictId, AcDbDatabase* destDb,
                                        AcDbIdMapping& idMap);
    void    insertCloneMergeDicts(AcDbDictionary* srcDict, AcDbDictionary* destDict,
                                        AcDbIdMapping& idMap);
    void    collectAllDictRecords(AcDbDatabase* db, AcDbObjectIdArray& objIds);
    void    searchOneDictionary(AcDbDictionary* dict, AcDbObjectIdArray& objIds);

	void	verifyClonedReferences(AcDbIdMapping& idMap);

        // outlawed functions
    ArxDbgAppEditorReactor(const ArxDbgAppEditorReactor &copy);
    ArxDbgAppEditorReactor& operator=(const ArxDbgAppEditorReactor &copy);


    // static functions for constructing/retrieving/destroying singleton instance
public:
    static ArxDbgAppEditorReactor*  getInstance();
    static void                     destroyInstance();

private:
    static ArxDbgAppEditorReactor*  m_instance;        // singleton instance

};

#endif    // ARXDBG_ARXDBGAPPEDREACTOR_H
