// (C) Copyright 1996 by Autodesk, Inc. 
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
//  arxutils.h


Adesk::Boolean  append       (AcDbEntity* pEntity);
Adesk::Boolean  append       (AcDbEntity* pEntity, AcDbObjectId& objId);
AcDbDictionary* getDict      (const char *dictName, AcDb::OpenMode mode,
                              AcDbDatabase *pDb = NULL, bool bCreateIfNotFound = true);
AcDbObjectId    getDictId    (const char *dictName, AcDbDatabase *pDb, bool bCreateIfNotFound = true);
AcDbDictionary* getExtDict   (AcDbObject *pObj, const char *dictName,
                              AcDb::OpenMode mode, bool bCreateIfNotFound = true);
AcDbObjectId    getExtDictId (AcDbObject *pObj, const char *dictName, bool bCreateIfNotFound = true);
AcDbObject*     cloneFromId  (AcDbObjectId& id);
