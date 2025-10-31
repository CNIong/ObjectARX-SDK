#ifndef   _XREFLOCK_H
#define   _XREFLOCK_H
//
//  (C) Copyright 1997-2008 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION: Header for Xref FileLock & Consistency Check

#include "rxnames.h"
#include "dbidar.h"
#pragma pack (push, 8)

class AcDbDatabase;
class AcDbIdMapping;
class AcDwgFileHandle;

class AcEdXrefFileLock
{
public:
     AcEdXrefFileLock();
    ~AcEdXrefFileLock();


    Acad::ErrorStatus lockFile(
                         int& retstatus,
                         const AcDbObjectId& selectedBTRid);

    Acad::ErrorStatus releaseFile(
                        int& retstatus,
                        bool bSkipSaveback = false,
                        bool bReload = true);

    Acad::ErrorStatus consistencyCheck(
                         int& retstatus,
                         const AcDbObjectId& selectedBTRid,
                         AcDbObjectIdArray& outofSyncBTRids);

    Acad::ErrorStatus consistencyCheck(
                         int& retstatus,
                         const AcDbObjectId& selectedBTRid);

    Acad::ErrorStatus consistencyChecklocal(
                         int& retstatus,
                         const AcDbObjectId& selectedBTRid);

    Acad::ErrorStatus xloadctlType(
                         int& retstatus,
                         const AcDbObjectId& selectedBTRid);

    int               getlockxloadctlType() const { return mXldctltype; }

    const AcDbObjectIdArray& getoutofSyncIdArray() const { return mXBTRidArray; }

    Acad::ErrorStatus reloadFile(
                         int& retstatus,
                         const AcDbObjectIdArray& BTRids,
                         const int xldctltype = -1);

    Acad::ErrorStatus reloadFile(
                         int& retstatus,
                         const int xldctltype = -1);

    void              setInternalTNmgmt(bool bTNmgmt);
    AcDbObjectId      getLockBtrId() {return mXBTRid;}
private:
    AcDwgFileHandle*    mdwgfile;
    AcDbDatabase*       mpXDB;
    AcDbDatabase*       mpXDBlockFile;
    int                 mXldctltype;
    AcDbObjectId        mXBTRid;
    AcDbObjectIdArray   mXBTRidArray;
    bool                mbIntTNmgmt;

};


#pragma pack (pop)
#endif  // !_XREFLOCK_H
