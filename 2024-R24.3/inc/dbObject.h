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
//
#pragma once
#include "adesk.h"
#include "AcDbCore2dDefs.h"
#include "drawable.h"
#include "AcHeapOpers.h"
#include "rxobject.h"
#include "acdb.h"
#include "dbboiler.h"
#include "dbptrar.h"
#include "dbidar.h"

class AcDbIdMapping;
class AcDbAuditInfo;
class AcDbDwgFiler;
class AcDbDxfFiler;
struct resbuf;
class AcDbObjectReactor;
class AcDbImpObject;
class AcDbField;
class AcDbDictionary;
class AcGeMatrix3d;
class AcDbEntity;
class AcDbObject;

// For getClassID without pulling in wtypes.h
//
struct _GUID;
typedef struct _GUID CLSID;

// Object Open Functions:  Exchange an object Id and 
// open mode for a pointer to the corresponding object.
//

/// <summary>
/// This function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <param name="pClass"> The expected type of the object. If null, then any object type is
///              accepted. Else eWrongType is returned if the object is not derived from
///              the passed in AcRxClass type.</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
/// <remarks> If your pObj pointer variable is not of type AcDbObject *, then do NOT cast
///           it to type (AcDbObject * &) when calling this function. Just pass your
///           variable as is and the template override defined below will be invoked
/// </remarks>
///
ACDBCORE2D_PORT Acad::ErrorStatus
acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode,
    bool openErased, const AcRxClass* pClass);

/// <summary>
/// This function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="pfDesc"> Pointer to an AcRxClass's static desc method</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
/// <remarks> This is the worker function for the acdbOpenObject template func.
///           Returns Acad::eNullPtr error if pfDesc is null.
/// </remarks>
///
ACDBCORE2D_PORT Acad::ErrorStatus
acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id, AcRxClass* (*pfDesc)(),
    AcDb::OpenMode mode, bool openErased);

// To be deprecated. Please use acdbOpenObject() instead
inline Acad::ErrorStatus
acdbOpenAcDbObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode,
    bool openErasedObject = false)
{
    return ::acdbOpenObject(pObj, id, mode, openErasedObject, /*pClass*/nullptr);
}

/// <summary>
/// This template function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
///
template<class T_OBJECT> inline Acad::ErrorStatus
acdbOpenObject(
    T_OBJECT*& pObj, AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead,
    bool openErased = false)
{
    return ::acdbOpenObject((AcDbObject*&)pObj, id, &T_OBJECT::desc,
        mode, openErased);
}

// Special overload for the base AcDbObject * type
// Works with smart pointers
inline Acad::ErrorStatus acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id,
    AcDb::OpenMode mode = AcDb::kForRead,
    bool openErased = false)
{
    return ::acdbOpenObject(pObj, id, mode, openErased, /*pClass*/nullptr);
}


class ADESK_NO_VTABLE AcDbObject : public AcGiDrawable, public AcHeapOperators
{
public:
    ACDB_DECLARE_MEMBERS(AcDbObject);

    ~AcDbObject();

    // Associated Objects
    //
    ACDBCORE2D_PORT
        AcDbObjectId      objectId() const;
    ACDBCORE2D_PORT
        AcDbObjectId      ownerId() const;
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus setOwnerId(AcDbObjectId objId);
    void              getAcDbHandle(AcDbHandle& handle) const;
    ACDBCORE2D_PORT
        /// <summary>This method returns a pointer to the AcDbDatabase object that contains
        ///          the AcDbObject.</summary>
        ///
        AcDbDatabase* database() const;
    /// <summary>This method returns a pointer to a AcDbDatabase object that can be
    ///          used with this AcDbObject.  If the AcDbObject is in an AcDbDatabase,
    ///          then a pointer to the AcDbDatabase returned by the object's database()
    ///          method will be returned, otherwise, if the AcDbObject has a non-nullptr
    ///          intendedDatabase, then a pointer to that AcDbDatabase will be returned,
    //           otherwise a pointer to the current AcDbHostApplicationServices'
    ///          workingDatabase will be returned.</summary>
    ///
    AcDbDatabase* databaseToUse() const;
    /// <summary>If this AcDbObject is not yet in an AcDbDatabase, and it has had its
    ///          intended AcDbDatabase set, then this method will return a pointer to that
    ///          intended AcDbDatabase.  The intended AcDbDatabase may be set when a database
    ///          specific property (such as the layer or linetype on entities) is set on this
    ///          AcDbObject, or if this AcDbObject's setIntendedDatabase() method has been called
    ///          to explicitly set the intended AcDbDatabase.
    ///
    ///          After this AcDbObject is added to an AcDbDatabase, this method will always return
    ///          nullptr.</summary>
    ///
    AcDbDatabase* intendedDatabase() const;
    /// <summary>This method allows setting an intended AcDbDatabase for this AcDbObject as
    ///          long as this AcDbObject is not yet in an AcDbDatabase.
    ///
    ///          When this AcDbObject is added to an AcDbDatabase, the intendedDatabase
    ///          will automatically become nullptr and this method will not allow setting
    ///          to anything else.
    ///
    ///          The intended AcDbDatabase is the AcDbDatabase that this object is expected
    ///          to be added to or associated with (such as if this AcDbObject is embedded
    ///          in another AcDbObject that is in an AcDbDatabase).
    ///
    ///          For AcDbEntities not yet in an AcDbDatabase, the intended AcDbDatabase is
    ///          automatically set when their layer, linetype, or material is set.
    ///
    ///          Custom object implementations should set the intended database whenever
    ///          any custom database specific property (i.e. associated with an AcDbObjectId)
    ///          on their object is set.</summary>
    /// <param name="pDb">Input pointer to desired intended AcDbDatabase.</param>
    /// <returns>Returns Acad::eOk if successful or Acad::eInvalidContext if this AcDbObject
    ///          is already in an AcDbDatabase and pDb != nullptr.</returns>
    ///
    Acad::ErrorStatus setIntendedDatabase(AcDbDatabase* pDb);

    Acad::ErrorStatus createExtensionDictionary();
    AcDbObjectId      extensionDictionary() const;
    Acad::ErrorStatus releaseExtensionDictionary();

    // Open/Close/Cancel/Undo/Erase
    //
    Acad::ErrorStatus upgradeOpen();
    Acad::ErrorStatus upgradeFromNotify(Adesk::Boolean& wasWritable);
    Acad::ErrorStatus downgradeOpen();
    Acad::ErrorStatus downgradeToNotify(Adesk::Boolean wasWritable);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subOpen(AcDb::OpenMode mode);

    Acad::ErrorStatus cancel();
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subCancel();

    ACDBCORE2D_PORT
        Acad::ErrorStatus close();
    Acad::ErrorStatus closeAndPage(Adesk::Boolean onlyWhenClean = true);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subClose();

    Acad::ErrorStatus erase(Adesk::Boolean erasing = true);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing);

    Acad::ErrorStatus handOverTo(AcDbObject* newObject,
        Adesk::Boolean keepXData = true,
        Adesk::Boolean keepExtDict = true);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subHandOverTo(AcDbObject* newObject);

    Acad::ErrorStatus swapIdWith(AcDbObjectId otherId,
        Adesk::Boolean swapXdata = false,
        Adesk::Boolean swapExtDict = false);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId,
            Adesk::Boolean swapXdata = false,
            Adesk::Boolean swapExtDict = false);

    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus swapReferences(const AcDbIdMapping& idMap);

    // Audit
    //
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    // Filing
    //
    Acad::ErrorStatus         dwgIn(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus         dwgOut(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    Acad::ErrorStatus         dxfIn(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    /// <summary>
    /// This function does some internal bookkeeping, calls the object's AcDbObject::dxfOutFields()
    /// function, and then uses bAllXdata and pRegAppIds to determine what, if any xdata should be
    /// written out. If bAllXdata == true, then all xdata is written out. If bAllXdata == false and
    /// pRegAppIds == nullptr or points to an empty array, then no xdata is written out.  If
    /// bAllXdata == false and pRegAppIds points to a non-empty array, then the xdata (if any) for
    /// those regapp objectIds is written out.
    /// </summary>
    /// <param name="pFiler">Input pointer to DXF filer to be used for this filing operation</param>    
    /// <param name="bAllXdata">Input bool to specify whether or not all xdata should be written out</param>
    /// <param name="pRegAppIds">Input pointer to array of regapp objectIds</param>    
    /// <returns>Returns the filer's status, which is Acad::eOk if successful.</returns>    
    ACDBCORE2D_PORT
        Acad::ErrorStatus         dxfOut(AcDbDxfFiler* pFiler,
            bool bAllXdata,
            const AcDbObjectIdArray* pRegAppIds) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    // Merge style for insert-style operations. Defaults to kDrcIgnore.
    //
    ACDBCORE2D_PORT
        virtual AcDb::DuplicateRecordCloning mergeStyle() const;

    // XData
    //
    ACDBCORE2D_PORT
        virtual resbuf* xData(const ACHAR* regappName = nullptr) const;
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus setXData(const resbuf* xdata);
    Acad::ErrorStatus xDataTransformBy(const AcGeMatrix3d& xform);

    // Binary chunks.  Note: the data args should be void *.  We'll
    // change those in an upcoming release... 

    /// <summary>This function copies the binary chunk pointed to by data into
    /// this object's extension dictionary. It looks for key in the dictionary,
    /// and either creates or overwrites a resbuf chain on an xrecord at that key.
    /// The binary data is broken into 127-byte chunks for storage in the resbuf chain.
    ///
    /// The caller is responsible for opening the object for write.</summary>
    /// <param name="key">Input extension dictionary key to be used</param>
    /// <param name="size">Input size of the binary data, in bytes</param>
    /// <param name="data">Input pointer to a flat data buffer whose size, in bytes
    /// is at least as large as size</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus         setBinaryData(const ACHAR* key,
        Adesk::Int32 size,
        const char* data);
    /// <summary>This function reads a chunk of binary data from this object's extension
    /// dictionary. It assumes that the data has been stored as a resbuf chain of 127-byte
    /// pieces, which it concatenates into the larger data buffer that is returned. If the
    /// data has been stored in any other type of resbuf, this function returns eBadDxfCode.
    ///
    /// A null pointer should be passed to the data parameter. If this function succeeds,
    /// it allocates the appropriate memory to contain the requested data, copies the data
    /// into the memory, sets data to point to that memory, and returns the size of the data
    /// in size. 
    ///
    /// The caller is responsible for freeing the allocated data buffer. The caller also is
    /// responsible for opening the object for read.</summary>
    /// <param name="key">Input extension dictionary key under which the data is stored</param>
    /// <param name="size">Output size of the returned data in bytes</param>
    /// <param name="data">Output requested data in an allocated buffer</param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eBadDxfCode if data is stored
    /// in resbufs that are not binary data chunks</returns>
    Acad::ErrorStatus         getBinaryData(const ACHAR* key,
        Adesk::Int32& size,
        char*& data) const;

    // XObject
    // Open/Notify/Undo/Modified State Predicates
    //
    Adesk::Boolean isEraseStatusToggled() const;
    Adesk::Boolean isErased() const;
    ACDBCORE2D_PORT
        Adesk::Boolean isReadEnabled() const;
    Adesk::Boolean isWriteEnabled() const;
    Adesk::Boolean isNotifyEnabled() const;
    Adesk::Boolean isModified() const;
    Adesk::Boolean isModifiedXData() const;
    Adesk::Boolean isModifiedGraphics() const;
    Adesk::Boolean isNewObject() const;
    Adesk::Boolean isNotifying() const;
    Adesk::Boolean isUndoing() const;
    Adesk::Boolean isCancelling() const;
    Adesk::Boolean isReallyClosing() const;
    Adesk::Boolean isTransactionResident() const;

    // Formerly isAZombie()
    //
    Adesk::Boolean isAProxy() const;

    // Access State Assertions
    //
    void assertReadEnabled() const;
    void assertWriteEnabled(Adesk::Boolean autoUndo = true,
        Adesk::Boolean recordModified = true);
    void assertNotifyEnabled() const;

    // Undo 
    //
    bool                      isUndoRecordingDisabled() const;
    void                      disableUndoRecording(Adesk::Boolean disable);
    AcDbDwgFiler* undoFiler();
    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler,
        AcRxClass* classObj);

    // Notification
    //
/// <summary>
/// Adds a non-persistent reactor to the currently open object
/// </summary>
/// <returns> Returns Acad::eOk if the reactor is added successfully.
///           Returns eNullObjectPointer if incoming argument is null.
///           Returns eInvalidInput if incoming argument is not a valid pointer.
///           Returns eDuplicateKey if reactor is already attached to this object.
/// </returns>
/// <remarks> Current object may be open for notify, read or write. </remarks>
///
    ACDBCORE2D_PORT Acad::ErrorStatus addReactor(AcDbObjectReactor* pReactor) const;

    /// <summary>
    /// Removes the non-persistent reactor from the currently open object
    /// </summary>
    /// <returns> Returns Acad::eOk if the reactor is removed successfully.
    ///           Returns eNullObjectPointer if incoming argument is null.
    ///           Returns eInvalidInput if incoming argument is not a valid pointer.
    ///           Returns eKeyNotFound if reactor is not attached to this object.
    /// </returns>
    /// <remarks> Current object may be open for notify, read or write. </remarks>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus removeReactor(AcDbObjectReactor* pReactor) const;

    /// <summary>
    /// Adds a persistent reactor to the currently open object
    /// </summary>
    /// <returns> Returns Acad::eOk if the reactor is added successfully.
    ///           Returns eNullObjectId if id argument is null.
    ///           Returns eInvalidInput if id argument does not have valid format.
    ///           Returns eWrongDatabase if id argument is not in same database as object.
    ///           Returns eSelfReference if id argument is same as this object's.
    ///           Returns eDuplicateKey if reactor is already attached to this object.
    /// </returns>
    /// <remarks> Current object must be open for write. </remarks>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus addPersistentReactor(AcDbObjectId objId);

    /// <summary>
    /// Removes the persistent reactor from the currently open object
    /// </summary>
    /// <returns> Returns Acad::eOk if the reactor is removed successfully.
    ///           Returns eNullObjectId if id argument is null.
    ///           Returns eInvalidInput if id argument does not have valid format.
    ///           Returns eWasNotifying if object is open for notify but not for write.
    ///           Returns eKeyNotFound if reactor id is not attached to this object.
    /// </returns>
    /// <remarks> Current object must be open for write. </remarks>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus removePersistentReactor(AcDbObjectId objId);

    ACDBCORE2D_PORT bool hasReactor(const AcDbObjectReactor* pReactor) const;
    ACDBCORE2D_PORT bool hasPersistentReactor(AcDbObjectId objId) const;

    // Note: May return nullptr. Also, each array entry's value is actually an
    // AcDbObjectReactor * or a mangled AcDbObjectId. 
    ACDBCORE2D_PORT const AcDbVoidPtrArray* reactors() const;

    ACDBCORE2D_PORT
        virtual void              recvPropagateModify(const AcDbObject* subObj);
    ACDBCORE2D_PORT
        virtual void              xmitPropagateModify() const;

    // virtual method for callers who pass an AcDbObject pointer
    //
    // Note: AcDbProxyEntity's which disallow cloning can return eOk status
    // with pClonedObject set to nullptr
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus deepClone(AcDbObject* pOwnerObject,
        AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap,
        bool isPrimary = true) const final;

    // template method for callers who pass a pointer to a derived type
    template<typename CloneType> Acad::ErrorStatus deepClone(AcDbObject* pOwner,
        CloneType*& pClone,
        AcDbIdMapping& idMap,
        bool isPrimary = true) const
    {
        AcDbObject* pNewObj = nullptr;
        Acad::ErrorStatus es = this->deepClone(pOwner, pNewObj, idMap, isPrimary);
        if (pNewObj == nullptr || es != Acad::eOk)
            pClone = nullptr;
        else {
            pClone = CloneType::cast(pNewObj);
            if (pClone == nullptr) {
                es = Acad::eWrongObjectType;    // unexpected
                pNewObj->erase();
                pNewObj->close();
            }
        }
        return es;
    }

    // virtual method for callers who pass an AcDbObject pointer
    //
    // Note: AcDbProxyEntity's which disallow cloning can return eOk status
    // with pClonedObject set to nullptr
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject,
        AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap,
        bool isPrimary = true) const final;

    // template method for callers who pass a pointer to a derived type
    template<typename CloneType> Acad::ErrorStatus wblockClone(AcRxObject* pOwner,
        CloneType*& pClone,
        AcDbIdMapping& idMap,
        bool isPrimary = true) const
    {
        AcDbObject* pNewObj = nullptr;
        Acad::ErrorStatus es = this->wblockClone(pOwner, pNewObj, idMap, isPrimary);
        if (pNewObj == nullptr || es != Acad::eOk)
            pClone = nullptr;
        else {
            pClone = CloneType::cast(pNewObj);
            if (pClone == nullptr) {
                es = Acad::eWrongObjectType;    // unexpected
                pNewObj->erase();
                pNewObj->close();
            }
        }
        return es;
    }

    void              setAcDbObjectIdsInFlux();
    Adesk::Boolean    isAcDbObjectIdsInFlux() const;

    // Notification for persistent reactors.
    //
    ACDBCORE2D_PORT
        virtual void cancelled(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void copied(const AcDbObject* dbObj,
            const AcDbObject* newObj);
    ACDBCORE2D_PORT
        virtual void erased(const AcDbObject* dbObj,
            Adesk::Boolean bErasing);
    ACDBCORE2D_PORT
        virtual void goodbye(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void openedForModify(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void modified(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void subObjModified(const AcDbObject* dbObj,
            const AcDbObject* subObj);
    ACDBCORE2D_PORT
        virtual void modifyUndone(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void modifiedXData(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void unappended(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void reappended(const AcDbObject* dbObj);
    ACDBCORE2D_PORT
        virtual void objectClosed(const AcDbObjectId objId);
    ACDBCORE2D_PORT
        virtual void modifiedGraphics(const AcDbEntity* dbEnt);

    // AcRxObject Protocol
    // Derived classes should not override these member implementations.
    //
    ACDBCORE2D_PORT AcRxObject* clone() const override;
    ACDBCORE2D_PORT Acad::ErrorStatus  copyFrom(const AcRxObject* pSrc) override;

    // Save to previous versions.
    //
    bool       hasSaveVersionOverride();
    void       setHasSaveVersionOverride(bool bSetIt);

    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDwgFiler* pFiler,
            AcDb::AcDbDwgVersion& ver,
            AcDb::MaintenanceReleaseVersion& maintVer);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDxfFiler* pFiler,
            AcDb::AcDbDwgVersion& ver,
            AcDb::MaintenanceReleaseVersion& maintVer);
    Acad::ErrorStatus getObjectBirthVersion(
        AcDb::AcDbDwgVersion& ver,
        AcDb::MaintenanceReleaseVersion& maintVer);

    // Saving as previous versions.
    //
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus   decomposeForSave(
            AcDb::AcDbDwgVersion ver,
            AcDbObject*& replaceObj,
            AcDbObjectId& replaceId,
            Adesk::Boolean& exchangeXData);

    virtual AcGiDrawable* drawable();

    // AcGiDrawable interface
    //
    ACDBCORE2D_PORT Adesk::Boolean      isPersistent() const override;
    ACDBCORE2D_PORT AcDbObjectId        id() const override;    // same as objectId()

    // Get corresponding COM wrapper class ID
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const final;

    bool              hasFields(void) const;
    Acad::ErrorStatus getField(const ACHAR* pszPropName,
        AcDbObjectId& fieldId) const;
    Acad::ErrorStatus getField(const ACHAR* pszPropName, AcDbField*& pField,
        AcDb::OpenMode mode = AcDb::kForRead) const;

    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus setField(const ACHAR* pszPropName, AcDbField* pField,
            AcDbObjectId& fieldId);

    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus removeField(AcDbObjectId fieldId);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus removeField(const ACHAR* pszPropName, AcDbObjectId& returnId);
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus removeField(const ACHAR* pszPropName);
    AcDbObjectId      getFieldDictionary(void) const;
    Acad::ErrorStatus getFieldDictionary(AcDbDictionary*& pFieldDict,
        AcDb::OpenMode mode = AcDb::kForRead) const;

protected:
    AcDbObject();

    // AcGiDrawable interface
    ACDBCORE2D_PORT Adesk::UInt32       subSetAttributes(AcGiDrawableTraits* pTraits) override;
    ACDBCORE2D_PORT Adesk::Boolean      subWorldDraw(AcGiWorldDraw* pWd) override;
    ACDBCORE2D_PORT void                subViewportDraw(AcGiViewportDraw* pVd) override;

    // AcDbPropertiesOverrule related
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;

    // AcDbObjectOverrule related
    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwnerObject,
            AcDbObject*& pClonedObject,
            AcDbIdMapping& idMap,
            Adesk::Boolean isPrimary = true) const;

    ACDBCORE2D_PORT
        virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject,
            AcDbObject*& pClonedObject,
            AcDbIdMapping& idMap,
            Adesk::Boolean isPrimary = true) const;

private:
    //friend class AcDbSystemInternals;
    friend class AcDbPropertiesOverrule;
    friend class AcDbObjectOverrule;
    AcDbImpObject* mpImpObject = nullptr;

    // No copy construction or assignment (but there is a copyFrom method)
    AcDbObject(const AcDbObject&) = delete;
    AcDbObject& operator = (const AcDbObject&) = delete;
};
