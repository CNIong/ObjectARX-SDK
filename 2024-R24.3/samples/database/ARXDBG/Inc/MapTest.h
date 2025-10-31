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

#ifndef ARXDBG_MAPTEST_H
#define ARXDBG_MAPTEST_H


/****************************************************************************
**
**  CLASS ObjIdMapNode:
**		This simple class keeps track of an object's transformation from the
**	original source drawing, through temporary databases, and into and back
**	out of the host drawing.  Without this, there would be no way to know
**	what current objectIds matched with the original ones that they were cloned
**	from  (unless you rely on some Handle/DwgName scheme).
**
**  **jma
**
*************************************/

class ObjIdMapNode {

public:

	enum IndexType {
		kOrigExt	= 0,
		kTmpImport,
		kNewCur,
		kTmpExport,
		kNewExt,
	};

	AcDbObjectId	m_origExtId;		// original id in source drawing
	AcDbObjectId	m_tmpImportId;		// id in tmp database after wblock on import
	AcDbObjectId	m_newCurId;			// id in cur dwg after insert of tmp database
	AcDbObjectId	m_tmpExportId;		// id in tmp database after wblock on export
	AcDbObjectId	m_newExtId;			// id in source drawing after insert on export
};

/****************************************************************************
**
**  CLASS MapTestReactor:
**
**  **jma
**
*************************************/

class MapTestReactor : public AcEditorReactor {

public:

	enum CloneState {
		kNull			= 0,	// we arent' currently driving the clone op
		kImportWblock,
		kImportInsert,
		kExportWblock,
		kExportInsert,
	};

	virtual void	endDeepClone(AcDbIdMapping& IdMap);
    virtual void	endInsert(AcDbDatabase* pTo);

	void			reset();

		// data members public... we don't really care for this test
	CString				m_dwgName;
	AcDbDatabase*		m_extDatabase; 
	CloneState          m_cloneState;
	AcDbVoidPtrArray	m_objIdMap;

private:
        // singleton class, so no one can call constructor/destructors
				MapTestReactor();
    virtual     ~MapTestReactor();

		// helper functions
	ObjIdMapNode*	findObjIdMapNode(const AcDbObjectId& objId, ObjIdMapNode::IndexType type);
	void			printObj(LPCTSTR event, const AcDbObjectId& objId) const;
	void			printObj(LPCTSTR event, const AcDbObject* obj) const;

        // outlawed functions
    MapTestReactor(const MapTestReactor &copy);
    MapTestReactor& operator=(const MapTestReactor &copy);


    // static functions for constructing/retrieving/destroying singleton instance
public:
    static MapTestReactor*  getInstance();
    static void             destroyInstance();

private:
    static MapTestReactor*  m_instance;        // singleton instance
     
};

#endif // ARXDBG_MAPTEST_H
