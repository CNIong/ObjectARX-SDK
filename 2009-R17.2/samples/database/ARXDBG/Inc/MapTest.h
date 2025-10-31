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
