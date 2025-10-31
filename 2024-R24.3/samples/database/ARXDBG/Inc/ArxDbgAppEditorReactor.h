//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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
