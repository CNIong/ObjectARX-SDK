#ifndef AD_DBDICT_H
#define AD_DBDICT_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// DESCRIPTION:  Class header for AcDbDictionary, a database-resident
//               dictionary.  A concerete API class whose implementation
//               can be inherited at runtime.
//
//               An instance of this class represents a single
//               "Drawing Symbol Table"-like object, to which
//               AcDbObject instances can be added, accessed and
//               removed.
//
//               Object pointers retrieved from the database represent
//               indivudual object are currently opened in the requested
//               mode.
//               The return status indicates the status for opening
//               the entry object.  If the status is not AcDb::eOpenOK,
//               the returned pointer is NULL.
//
// CONTRACTS:
//               Objects added to an AcDbDictionary instance must not
//               have a presence in the database, i.e. they must have
//               null handles.
//
//               Objects removed or replaced in the dictionary are 
//               erased via AcDbObject::erase().
//

#include "dbmain.h"

#pragma pack(push, 8)

class AcDbImpDictionary;
class AcString;

class ADESK_NO_VTABLE AcDbDictionaryIterator: public AcRxObject
//
// This class allows one to sequentially retrieve the objects in
// the dictionary, and keeps track of what the last object retrieved was.
//
// It is similar to AcRxDictionary Iterator, except the casting
// of returned elements is stronger, and it has a member which
// returns the status of the entry member when the attempt to
// open it was made.  If the status is Acad::ErrorStatus eOk, then
// AcDbDictionaryIterator::getValue() will return a non-null
// pointer, otherwise not.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDictionaryIterator);
    virtual ~AcDbDictionaryIterator() {}

    virtual const ACHAR*      name       () const = 0;

    virtual Acad::ErrorStatus getObject  (AcDbObject*&   pObject,
                                          AcDb::OpenMode mode) = 0;
    virtual AcDbObjectId      objectId   () const = 0;

    virtual bool              done       () const = 0;
    virtual bool              next       () = 0;
    virtual bool              setPosition(AcDbObjectId objId) = 0;

protected:
    AcDbDictionaryIterator() {}
};

class AcDbDictionary: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDictionary);
    AcDbDictionary();
    virtual ~AcDbDictionary();

    // Get an entry by name.
    //
    Acad::ErrorStatus getAt(const ACHAR*   entryName,
                            AcDbObject*&   entryObj,
                            AcDb::OpenMode mode) const;
    Acad::ErrorStatus getAt(const ACHAR*   entryName,
                            AcDbObjectId&  entryObj) const;

    // Find name corresponding to object id.
    //
    Acad::ErrorStatus nameAt(AcDbObjectId objId,
                             ACHAR*&      name) const;
    Acad::ErrorStatus nameAt(AcDbObjectId objId,
                             AcString &   name) const;
 
    // Query contents of dictionary
    //
    bool              has       (const ACHAR*  entryName) const;
    bool              has       (AcDbObjectId objId) const;
    Adesk::UInt32     numEntries() const;

    // Remove entries.
    //
    Acad::ErrorStatus remove(const ACHAR *  key);
    Acad::ErrorStatus remove(const ACHAR *  key,
                             AcDbObjectId& returnId);
    Acad::ErrorStatus remove(AcDbObjectId  objId);

    // Reset an entry.
    //
    bool              setName(const ACHAR*   oldName,
                              const ACHAR*   newName);
    Acad::ErrorStatus setAt  (const ACHAR*   srchKey,
                              AcDbObject*   newValue,
                              AcDbObjectId& retObjId);

    // Test/Set treatment of elements.
    //
    bool              isTreatElementsAsHard () const;
    void              setTreatElementsAsHard(bool doIt);

    // Get an iterator for this dictionary.
    //
    AcDbDictionaryIterator* newIterator() const;

    // AcDbObject Protocol
    //
    virtual Acad::ErrorStatus subErase     (Adesk::Boolean pErasing
                                                = Adesk::kTrue);
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual AcDb::DuplicateRecordCloning mergeStyle() const;
    virtual void  setMergeStyle(AcDb::DuplicateRecordCloning style);

    // Support for persistant reactor to annotation.
    //
    virtual void goodbye(const AcDbObject* pObject);
    virtual void erased (const AcDbObject* pObject,
                         Adesk::Boolean pErasing = Adesk::kTrue);

    // Support for saving to previous releases' formats.
    //
    virtual Acad::ErrorStatus decomposeForSave(
                                  AcDb::AcDbDwgVersion ver,
                                  AcDbObject*&         replaceObj,
                                  AcDbObjectId&        replaceId,
                                  Adesk::Boolean&      exchangeXData);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
