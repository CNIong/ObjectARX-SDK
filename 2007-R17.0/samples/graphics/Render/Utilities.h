//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#pragma once

namespace RenderAPISample
{
	extern Acad::ErrorStatus postEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* ent);
	extern Acad::ErrorStatus postEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* ent, AcDbObjectId& objId);
	extern Acad::ErrorStatus addEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* ent);
	extern Acad::ErrorStatus addEntToCurrentSpace(AcDbDatabase* pDb, AcDbEntity* ent, AcDbObjectId& objId);
	extern Acad::ErrorStatus addAnEntryToADict(AcDbDatabase* pDb, const ACHAR* dictName, const ACHAR* entryName, AcDbObject* pObj);
	extern Acad::ErrorStatus addAnEntryToADict(AcDbDatabase* pDb, const ACHAR* dictName, const ACHAR* entryName, AcDbObject* pObj, AcDbObjectId& dictId, AcDbObjectId& objId);
	extern Acad::ErrorStatus renderEnvironmentOrGlobalObj(AcDbDatabase* pDb, AcRxClass* pCls, AcDbObject*& pObj);

	extern Acad::ErrorStatus addLights(void);
	extern Acad::ErrorStatus addSunAndBackground(void);
	extern Acad::ErrorStatus addObjectsToRender(void);
	

	enum ViewType {
		NoCurrentView = 0,
		ModelSpaceView,
		PaperSpaceView
	};

	extern AcDbObjectId currentViewId(AcDbDatabase* pDb, ViewType& vt);
}

