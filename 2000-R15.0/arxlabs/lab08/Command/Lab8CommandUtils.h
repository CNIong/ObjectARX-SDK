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
#ifndef _LAB8UTILS_H
#define _LAB8UTILS_H

Acad::ErrorStatus 
postToDatabase(/*[in]*/AcDbEntity* pEnt,/*[out]*/AcDbObjectId& idObj);

Acad::ErrorStatus
RTtoStatus(/*[in]*/int rt);

//disable the compiler warning complaining
//about the ignored throw specification
#if _MSC_VER <= 1200
#pragma warning(disable:4290)
#endif

inline void ADSOK(int what) throw(Acad::ErrorStatus)
{
    Acad::ErrorStatus es=RTtoStatus(what);
    if (es!=Acad::eOk) 
        throw es;
}
 
inline void ARXOK(Acad::ErrorStatus what) throw(Acad::ErrorStatus)
{
    if (what!=Acad::eOk) 
        throw what;
}

#ifdef _DEBUG
#define ACADTRACE acutPrintf
#else
#define ACADTRACE 
#endif

inline Acad::ErrorStatus
getNOD(/*[out]*/ AcDbDictionary*& pNOD, const /*[in]*/AcDb::OpenMode mode){
    AcDbObjectId idO = acdbHostApplicationServices()->workingDatabase()->namedObjectsDictionaryId();
    return actrTransactionManager->getObject((AcDbObject*&)pNOD,idO,mode);
}

void 
addDictAndEntry(/*[in]*/const char* strDictKey, /*[in]*/AcDbDictionary* pParent, 
                /*[in]*/const char* strEmpKey, /*[in]*/AcDbObject* pEmployee) throw(Acad::ErrorStatus);

void
removeEntryFromDict(/*[in]*/const char* strDictKey, /*[in]*/AcDbDictionary* pParent, 
                    /*[in]*/const char* strEmpKey) throw(Acad::ErrorStatus);
void
getExtDictOfObject(/*[out]*/AcDbDictionary*& pExtDict) throw(Acad::ErrorStatus);

#endif //_LAB8UTILS_H