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

#ifndef ARXDBGCLONESET_H
#define ARXDBGCLONESET_H

/****************************************************************************
**
**  CLASS ArxDbgCloneSet:
**
**  **jma
**
*************************************/

class ArxDbgCloneSet {

public:
					ArxDbgCloneSet();
	virtual			~ArxDbgCloneSet();

	void			getAllDatabases(AcDbVoidPtrArray& dbPtrs);

	bool			getObjectsForDatabase(AcDbDatabase* db, AcDbObjectIdArray& objIds);
	void			databaseConstructed(AcDbDatabase* db);
	void			databaseDestroyed(AcDbDatabase* db);

	void			addObject(const AcDbObjectId& objId);
	void			addObjects(const AcDbObjectIdArray& objIds);

	void			removeObject(const AcDbObjectId& objId);
	void			removeObjects(const AcDbObjectIdArray& objIds);
	void			removeAll(AcDbDatabase* db);

private:
		// data members
	CMapPtrToPtr		m_dbMap;
};


#endif    // ARXDBGCLONESET_H
