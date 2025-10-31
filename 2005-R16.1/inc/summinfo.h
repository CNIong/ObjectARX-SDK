//
//  (C) Copyright 1998-2000,2002 by Autodesk, Inc.
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
//  DESCRIPTION:  Header for Summary Info API
//

#ifndef _SUMMINFO_H_
#define _SUMMINFO_H_

#include "adesk.h"

#pragma pack (push, 8)

// Note that this class is an AcRxObject, not an AcDbObject.
// Rather than doing open() and close() calls on it, we do get
// and put operations on a database, passing instances of this
// class as values.
//
class ADESK_NO_VTABLE AcDbDatabaseSummaryInfo : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabaseSummaryInfo);

    virtual Acad::ErrorStatus getTitle(char*& title) const = 0;
    virtual Acad::ErrorStatus setTitle(const char* title) = 0;

    virtual Acad::ErrorStatus getSubject(char*& subject) const = 0;
    virtual Acad::ErrorStatus setSubject(const char* subject) = 0;

    virtual Acad::ErrorStatus getAuthor(char*& author) const = 0;
    virtual Acad::ErrorStatus setAuthor(const char* author) = 0;

    virtual Acad::ErrorStatus getKeywords(char*& keywordlist) const = 0;
    virtual Acad::ErrorStatus setKeywords(const char* keywordlist) = 0;

    virtual Acad::ErrorStatus getComments(char*& comments) const = 0;
    virtual Acad::ErrorStatus setComments(const char* comments) = 0;

    virtual Acad::ErrorStatus getLastSavedBy(char*& lastSavedBy) const = 0;
    virtual Acad::ErrorStatus setLastSavedBy(const char* lastSavedBy) = 0;

    virtual Acad::ErrorStatus getRevisionNumber(char*& revisionNumber) const = 0;
    virtual Acad::ErrorStatus setRevisionNumber(const char* revisionNumber) = 0;

    virtual Acad::ErrorStatus getHyperlinkBase(char*& HyperlinkBase) const = 0;
    virtual Acad::ErrorStatus setHyperlinkBase(const char* HyperlinkBase) = 0;

    virtual int numCustomInfo() const = 0;

    virtual Acad::ErrorStatus addCustomSummaryInfo(const char* key, const char* value ) = 0;

    virtual Acad::ErrorStatus deleteCustomSummaryInfo(const int index) = 0;
    virtual Acad::ErrorStatus deleteCustomSummaryInfo(const char* key) = 0;

    virtual Acad::ErrorStatus getCustomSummaryInfo(const int index, char*& key,
                               char *& value ) const = 0;

    virtual Acad::ErrorStatus setCustomSummaryInfo (const int index, const char* key,
                               const char *value ) = 0;

    virtual Acad::ErrorStatus getCustomSummaryInfo(const char *customInfoKey,
                               char *& value ) const = 0;

    virtual Acad::ErrorStatus setCustomSummaryInfo (const char *customInfoKey,
                               const char *value ) = 0;

    // Note: database() and setDatabase() may become obsolete
    // in a future release.
    //
    virtual AcDbDatabase* database() const = 0; 
    virtual void setDatabase(AcDbDatabase *pDb) = 0; 

    virtual ~AcDbDatabaseSummaryInfo() {};
  protected:
    AcDbDatabaseSummaryInfo();
};

Acad::ErrorStatus ADESK_STDCALL acdbGetSummaryInfo(
                                 AcDbDatabase* pDb, 
                                 AcDbDatabaseSummaryInfo*& pInfo);

Acad::ErrorStatus ADESK_STDCALL acdbPutSummaryInfo(
                                const AcDbDatabaseSummaryInfo* pInfo,
                                AcDbDatabase *pDb);

// Note: this acdbPutSummaryInfo() overload which does not take a
// database argument may become obsolete in a future release.
//
inline Acad::ErrorStatus acdbPutSummaryInfo(
                                const AcDbDatabaseSummaryInfo* pInfo)
{
    return ::acdbPutSummaryInfo(pInfo, pInfo->database());
}


//
class ADESK_NO_VTABLE AcDbSummaryInfoReactor {
public:
    virtual void summaryInfoHasChanged(
                     const AcDbDatabase* pDb, 
                     const AcDbDatabaseSummaryInfo* pDbProp) {};
    virtual ~AcDbSummaryInfoReactor() {};
};

class ADESK_NO_VTABLE AcDbSummaryInfoManager {
public:
    virtual void  addReactor(AcDbSummaryInfoReactor* pReact) = 0;
    virtual void  removeReactor(AcDbSummaryInfoReactor* pReact) = 0;
};

// Stand-alone function to return the manager
//

AcDbSummaryInfoManager* ADESK_STDCALL acdbSummaryInfoManager();

// Obsolete methods.  These will be removed in
// a future release.
//
inline void initAcDbSummaryInfoManager() {};
inline void deleteAcDbSummaryInfoManager() {};

#pragma pack (pop)
#endif // _SUMMINFO_H_


