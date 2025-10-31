// Created by Microsoft (R) C/C++ Compiler Version 13.00.9466 (dd9a98cb).

// C++ source equivalent of Win32 type library C:\program files\common files\Autodesk shared\AcSmComponents16.tlb
// compiler-generated file created 12/10/03 at 08:51:32 - DO NOT EDIT!

//
// Cross-referenced type libraries:
//
//  #import "C:\Program Files\Common Files\Autodesk Shared\axdb16enu.tlb"
//

#pragma once
#pragma pack(push, 8)

#include <comdef.h>

//
// Forward references and typedefs
//

struct __declspec(uuid("042b7bf0-05c4-442a-adde-94428504c7fd"))
/* LIBID */ __ACSMCOMPONENTS16Lib;
struct /* coclass */ AcSmDSTFiler;
struct __declspec(uuid("8e974876-ff7f-48d3-8435-a6328ccc496f"))
/* interface */ IAcSmFiler;
struct __declspec(uuid("5585723a-4859-4dd9-9913-996484d6060d"))
/* interface */ IAcSmDatabase;
struct __declspec(uuid("0e463002-12a4-4828-b4cf-28d8cbf8c768"))
/* interface */ IAcSmComponent;
struct __declspec(uuid("ab9e4650-c3a8-4747-8d89-80731a4644a1"))
/* interface */ IAcSmPersist;
struct __declspec(uuid("42634426-cdfb-4e32-ad46-992ceb3b1596"))
/* interface */ IAcSmObjectId;
struct __declspec(uuid("fa893fe9-247c-44ec-b437-541c0f09f5fc"))
/* interface */ IAcSmCustomPropertyBag;
struct __declspec(uuid("da800d3b-975c-4381-9531-358328792650"))
/* interface */ IAcSmCustomPropertyValue;
typedef enum __MIDL___MIDL_itf_AcSmComponents_0264_0001 PropertyFlags;
enum __MIDL___MIDL_itf_AcSmComponents_0264_0001;
struct __declspec(uuid("476cbb88-8878-419d-a8c5-a9ced89d5a37"))
/* interface */ IAcSmEnumProperty;
struct __declspec(uuid("537476a6-e9e9-4e25-b6ea-fb5b8b086153"))
/* interface */ IAcSmSheetSet;
struct __declspec(uuid("8cceb838-acf5-4048-b9f0-09a843ca2ac4"))
/* interface */ IAcSmSubset;
struct __declspec(uuid("b86d90c3-7d13-4180-8f97-61c09fa15902"))
/* interface */ IAcSmFileReference;
struct __declspec(uuid("c5e0c361-9e43-4574-a0ab-defa483511e4"))
/* interface */ IAcSmNamedAcDbObjectReference;
struct __declspec(uuid("25b22534-b1f7-402c-82d6-d36fac620d69"))
/* interface */ IAcSmAcDbObjectReference;
struct __declspec(uuid("0070c60f-987a-4349-9e0a-3acba0cc9c5b"))
/* interface */ IAcSmAcDbDatabase;
struct __declspec(uuid("330cd4d2-73fe-43dc-85cc-48263863cfba"))
/* interface */ IAcSmEnumComponent;
struct __declspec(uuid("59bc91bb-fad8-44f9-86f9-5c99fa6b4edd"))
/* interface */ IAcSmSheet;
struct __declspec(uuid("5d2d1da2-97ca-48d9-93fd-bbc5b5852962"))
/* interface */ IAcSmSheetViews;
struct __declspec(uuid("07bb6db5-2198-4ea2-8752-e5a520d01a47"))
/* interface */ IAcSmEnumSheetView;
struct __declspec(uuid("f69ceaf1-819f-4b7a-b5e6-d39395415f55"))
/* interface */ IAcSmSheetView;
struct __declspec(uuid("a5b52086-a849-4a06-9b77-41d860e5a11b"))
/* interface */ IAcSmViewCategory;
struct __declspec(uuid("cfbf491d-19c4-4893-9c4b-bc3dfb6d5e64"))
/* interface */ IAcSmCalloutBlocks;
struct __declspec(uuid("b2305c6b-130a-4eb0-b89b-b5fba9f44f84"))
/* interface */ IAcSmEnumNamedAcDbObjectReference;
typedef enum __MIDL___MIDL_itf_AcSmComponents_0261_0001 AcSmEvent;
enum __MIDL___MIDL_itf_AcSmComponents_0261_0001;
struct __declspec(uuid("20786806-b251-4277-b119-94209c2ea7f9"))
/* interface */ IAcSmSheetSelSets;
struct __declspec(uuid("1bea479e-ec3a-49b8-94e5-cfcee92c4afe"))
/* interface */ IAcSmSheetSelSet;
struct __declspec(uuid("e8c8d548-3b80-4810-b866-617a7b916fe8"))
/* interface */ IAcSmEnumSheetSelSet;
struct __declspec(uuid("b448171b-d56c-4834-bf45-3d2ed0a66229"))
/* interface */ IAcSmResources;
struct __declspec(uuid("73fcecfa-6343-4630-889b-d03cbfbc2431"))
/* interface */ IAcSmEnumFileReference;
struct __declspec(uuid("b28b23eb-ff5e-4910-8ca6-ad54931013f3"))
/* interface */ IAcSmViewCategories;
struct __declspec(uuid("460b347f-c804-42f0-91d5-7ddd925e5058"))
/* interface */ IAcSmEnumViewCategory;
struct __declspec(uuid("147981d1-af77-42a1-8b91-4994a16a59fd"))
/* interface */ IAcSmPublishOptions;
struct __declspec(uuid("2760e2a6-c735-4a97-8260-f1af212c8a4d"))
/* interface */ IAcSmProjectPointLocations;
struct __declspec(uuid("0b79150e-c037-48ad-a93f-2ff6d3104d11"))
/* interface */ IAcSmProjectPointLocation;
struct __declspec(uuid("af02d3b1-a2e4-44c7-85ae-01038365dec2"))
/* interface */ IAcSmEnumProjectPointLocation;
struct __declspec(uuid("56832073-a227-43f5-b5e9-bb4f0e4c7ad4"))
/* interface */ IAcSmEvents;
enum AcSmLockStatus;
struct __declspec(uuid("746e7d4f-0024-44ae-8753-f1ccae44072c"))
/* interface */ IAcSmEnumPersist;
struct /* coclass */ AcSmDatabase;
struct /* coclass */ AcSmSheetSet;
struct /* coclass */ AcSmSubset;
struct /* coclass */ AcSmResources;
struct /* coclass */ AcSmCalloutBlocks;
struct /* coclass */ AcSmCalloutBlockReferences;
struct /* coclass */ AcSmSheetSelSet;
struct /* coclass */ AcSmSheetSelSets;
struct /* coclass */ AcSmSheet;
struct /* coclass */ AcSmSheetView;
struct /* coclass */ AcSmSheetViews;
struct /* coclass */ AcSmViewCategory;
struct /* coclass */ AcSmViewCategories;
struct /* coclass */ AcSmSheetSetMgr;
struct __declspec(uuid("4cc6fc8f-f1c6-486d-b550-838b0234e03c"))
/* interface */ IAcSmSheetSetMgr;
struct __declspec(uuid("02aacc99-5c5a-4528-a00a-73f71c51439b"))
/* interface */ IAcSmEnumDatabase;
struct /* coclass */ AcSmFileReference;
struct /* coclass */ AcSmAcDbDatabase;
struct /* coclass */ AcSmAcDbObjectReference;
struct /* coclass */ AcSmNamedAcDbObjectReference;
struct /* coclass */ AcSmCustomPropertyValue;
struct /* coclass */ AcSmCustomPropertyBag;
struct /* coclass */ AcSmPersistProxy;
struct __declspec(uuid("d5bb3e7e-2af7-4d10-94b3-213ffdaf16c8"))
/* interface */ IAcSmPersistProxy;
struct /* coclass */ AcSmObjectReference;
struct __declspec(uuid("adf37497-a661-4306-b048-a703e842d2fa"))
/* interface */ IAcSmObjectReference;
enum AcSmObjectReferenceFlags;
struct /* coclass */ AcSmPublishOptions;
struct /* coclass */ AcSmFileWatchReactor;
struct __declspec(uuid("faf2007f-ffcb-4fb3-b52e-5ae98c964d60"))
/* interface */ IAcSmFileWatchReactor;
struct __declspec(uuid("f340a8b3-2c69-4ef9-b6cd-6a08e019904d"))
/* interface */ IAdComFileWatchReactor;
enum FileNotifyAction;
enum FileNotifyFlags;
struct /* coclass */ AcSmProjectPointLocation;
struct /* coclass */ AcSmProjectPointLocations;

//
// Smart pointer typedef declarations
//

_COM_SMARTPTR_TYPEDEF(IAcSmAcDbDatabase, __uuidof(IAcSmAcDbDatabase));
_COM_SMARTPTR_TYPEDEF(IAdComFileWatchReactor, __uuidof(IAdComFileWatchReactor));
_COM_SMARTPTR_TYPEDEF(IAcSmFiler, __uuidof(IAcSmFiler));
_COM_SMARTPTR_TYPEDEF(IAcSmPersist, __uuidof(IAcSmPersist));
_COM_SMARTPTR_TYPEDEF(IAcSmCustomPropertyValue, __uuidof(IAcSmCustomPropertyValue));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumProperty, __uuidof(IAcSmEnumProperty));
_COM_SMARTPTR_TYPEDEF(IAcSmCustomPropertyBag, __uuidof(IAcSmCustomPropertyBag));
_COM_SMARTPTR_TYPEDEF(IAcSmComponent, __uuidof(IAcSmComponent));
_COM_SMARTPTR_TYPEDEF(IAcSmFileReference, __uuidof(IAcSmFileReference));
_COM_SMARTPTR_TYPEDEF(IAcSmAcDbObjectReference, __uuidof(IAcSmAcDbObjectReference));
_COM_SMARTPTR_TYPEDEF(IAcSmNamedAcDbObjectReference, __uuidof(IAcSmNamedAcDbObjectReference));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumComponent, __uuidof(IAcSmEnumComponent));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumNamedAcDbObjectReference, __uuidof(IAcSmEnumNamedAcDbObjectReference));
_COM_SMARTPTR_TYPEDEF(IAcSmCalloutBlocks, __uuidof(IAcSmCalloutBlocks));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetSelSet, __uuidof(IAcSmSheetSelSet));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumSheetSelSet, __uuidof(IAcSmEnumSheetSelSet));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetSelSets, __uuidof(IAcSmSheetSelSets));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumFileReference, __uuidof(IAcSmEnumFileReference));
_COM_SMARTPTR_TYPEDEF(IAcSmResources, __uuidof(IAcSmResources));
_COM_SMARTPTR_TYPEDEF(IAcSmPublishOptions, __uuidof(IAcSmPublishOptions));
_COM_SMARTPTR_TYPEDEF(IAcSmProjectPointLocation, __uuidof(IAcSmProjectPointLocation));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumProjectPointLocation, __uuidof(IAcSmEnumProjectPointLocation));
_COM_SMARTPTR_TYPEDEF(IAcSmProjectPointLocations, __uuidof(IAcSmProjectPointLocations));
_COM_SMARTPTR_TYPEDEF(IAcSmEvents, __uuidof(IAcSmEvents));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumPersist, __uuidof(IAcSmEnumPersist));
_COM_SMARTPTR_TYPEDEF(IAcSmPersistProxy, __uuidof(IAcSmPersistProxy));
_COM_SMARTPTR_TYPEDEF(IAcSmObjectReference, __uuidof(IAcSmObjectReference));
_COM_SMARTPTR_TYPEDEF(IAcSmDatabase, __uuidof(IAcSmDatabase));
_COM_SMARTPTR_TYPEDEF(IAcSmObjectId, __uuidof(IAcSmObjectId));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumDatabase, __uuidof(IAcSmEnumDatabase));
_COM_SMARTPTR_TYPEDEF(IAcSmFileWatchReactor, __uuidof(IAcSmFileWatchReactor));
_COM_SMARTPTR_TYPEDEF(IAcSmSubset, __uuidof(IAcSmSubset));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetSet, __uuidof(IAcSmSheetSet));
_COM_SMARTPTR_TYPEDEF(IAcSmSheet, __uuidof(IAcSmSheet));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetSetMgr, __uuidof(IAcSmSheetSetMgr));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetViews, __uuidof(IAcSmSheetViews));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumSheetView, __uuidof(IAcSmEnumSheetView));
_COM_SMARTPTR_TYPEDEF(IAcSmViewCategory, __uuidof(IAcSmViewCategory));
_COM_SMARTPTR_TYPEDEF(IAcSmSheetView, __uuidof(IAcSmSheetView));
_COM_SMARTPTR_TYPEDEF(IAcSmEnumViewCategory, __uuidof(IAcSmEnumViewCategory));
_COM_SMARTPTR_TYPEDEF(IAcSmViewCategories, __uuidof(IAcSmViewCategories));

//
// Type library items
//

struct __declspec(uuid("63eef39a-e068-474a-a5cd-d48c6151c82b"))
AcSmDSTFiler;
    // [ default ] interface IAcSmFiler

enum __MIDL___MIDL_itf_AcSmComponents_0264_0001
{
    EMPTY = 0,
    CUSTOM_SHEETSET_PROP = 1,
    CUSTOM_SHEET_PROP = 2,
    IS_CHILD = 4
};

struct __declspec(uuid("0070c60f-987a-4349-9e0a-3acba0cc9c5b"))
IAcSmAcDbDatabase : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetIAcadDatabase (
        /*[out,retval]*/ struct IAcadDatabase * * pIAcadDatabase ) = 0;
      virtual HRESULT __stdcall GetAcDbDatabase (
        /*[out,retval]*/ void * * ppAcDbDatabase ) = 0;
};

enum __MIDL___MIDL_itf_AcSmComponents_0261_0001
{
    SHEET_ADDED = 0,
    SHEET_DELETED = 1,
    SHEET_SUBSET_CREATED = 2,
    SHEET_SUBSET_DELETED = 3,
    SHEET_SELECTION_SET_CREATED = 4,
    SHEET_SELECTION_SET_DELETED = 5,
    SHEET_VIEW_CREATED = 6,
    SHEET_VIEW_DELETED = 7,
    SHEET_VIEW_CATEGORY_CREATED = 8,
    SHEET_VIEW_CATEGORY_DELETED = 9,
    MODEL_RESOURCE_ADDED = 10,
    MODEL_RESOURCE_DELETED = 11,
    CALLOUT_BLOCK_ADDED = 12,
    CALLOUT_BLOCK_DELETED = 13,
    SHEETS_RENUMBERED = 14,
    ACSM_DATABASE_CREATED = 15,
    ACSM_DATABASE_OPENED = 16,
    ACSM_DATABASE_WATCH_ERROR = 17,
    ACSM_DATABASE_LOCKED = 18,
    ACSM_DATABASE_UNLOCKED = 19,
    ACSM_DATABASE_CHANGED = 20,
    ACSM_DATABASE_INITNEW_BEGIN = 21,
    ACSM_DATABASE_INITNEW_FAILED = 22,
    ACSM_DATABASE_INITNEW_COMPLETE = 23,
    ACSM_DATABASE_LOAD_BEGIN = 24,
    ACSM_DATABASE_LOAD_FAILED = 25,
    ACSM_DATABASE_LOAD_COMPLETE = 26
};

enum __declspec(uuid("352629d3-ad04-45d5-9f78-73714132347f"))
AcSmLockStatus
{
    AcSmLockStatus_UnLocked = 0,
    AcSmLockStatus_Locked_Local = 1,
    AcSmLockStatus_Locked_Remote = 2,
    AcSmLockStatus_Locked_ReadOnly = 4,
    AcSmLockStatus_Locked_NotConnected = 8,
    AcSmLockStatus_Locked_AccessDenied = 16
};

struct __declspec(uuid("2162c6b6-0ce4-40e8-912b-46f59dfdf826"))
AcSmDatabase;
    // [ default ] interface IAcSmDatabase

struct __declspec(uuid("b20534f2-0978-418c-8d14-2e6928a077ed"))
AcSmSheetSet;
    // [ default ] interface IAcSmSheetSet

struct __declspec(uuid("076d548f-b0f5-4fe1-b35d-7f7b73b8d322"))
AcSmSubset;
    // [ default ] interface IAcSmSubset

struct __declspec(uuid("3f0faf10-09de-4eba-aed1-c4e4d6fecf5d"))
AcSmResources;
    // [ default ] interface IAcSmResources

struct __declspec(uuid("203eab46-483b-4e6b-a10b-15e9a4b210ff"))
AcSmCalloutBlocks;
    // [ default ] interface IAcSmCalloutBlocks

struct __declspec(uuid("67c52fe4-0a6b-4c82-a4cc-5e68537747b0"))
AcSmCalloutBlockReferences;
    // [ default ] interface IAcSmCalloutBlocks

struct __declspec(uuid("ebf70db8-f495-4522-ba80-43976bf35b3e"))
AcSmSheetSelSet;
    // [ default ] interface IAcSmSheetSelSet

struct __declspec(uuid("444780b8-6527-43a8-8dc4-fab41b7e48bb"))
AcSmSheetSelSets;
    // [ default ] interface IAcSmSheetSelSets

struct __declspec(uuid("16a07941-bc15-4d48-a880-9d5a211d5065"))
AcSmSheet;
    // [ default ] interface IAcSmSheet

struct __declspec(uuid("b6e09611-4659-4f0d-981d-d62b11fd8426"))
AcSmSheetView;
    // [ default ] interface IAcSmSheetView

struct __declspec(uuid("f40f931b-64bc-4b90-9fc8-a11a77d6815b"))
AcSmSheetViews;
    // [ default ] interface IAcSmSheetViews

struct __declspec(uuid("4aea81ed-c24f-477b-a534-ea69220a276a"))
AcSmViewCategory;
    // [ default ] interface IAcSmViewCategory

struct __declspec(uuid("021730df-5bea-48e9-bc7a-35087a674fd0"))
AcSmViewCategories;
    // [ default ] interface IAcSmViewCategories

struct __declspec(uuid("80caa04c-3a1e-4513-8267-59851c997655"))
AcSmSheetSetMgr;
    // [ default ] interface IAcSmSheetSetMgr

struct __declspec(uuid("6bf87ae7-1bec-4bdb-98bb-5b91f7772793"))
AcSmFileReference;
    // [ default ] interface IAcSmFileReference

struct __declspec(uuid("3750caec-9cd1-4778-b849-2a281c006956"))
AcSmAcDbDatabase;
    // [ default ] interface IAcSmAcDbDatabase

struct __declspec(uuid("7188d70d-7b73-4f29-86cf-cba1a5f4db2a"))
AcSmAcDbObjectReference;
    // [ default ] interface IAcSmAcDbObjectReference

struct __declspec(uuid("76527aac-4575-4b0a-9aeb-0a1c3b0ec855"))
AcSmNamedAcDbObjectReference;
    // [ default ] interface IAcSmNamedAcDbObjectReference

struct __declspec(uuid("8d22a2a4-1777-4d78-84cc-69ef741fe954"))
AcSmCustomPropertyValue;
    // [ default ] interface IAcSmCustomPropertyValue

struct __declspec(uuid("4d103908-8c86-4d95-bbf4-68b9a7b00731"))
AcSmCustomPropertyBag;
    // [ default ] interface IAcSmCustomPropertyBag

struct __declspec(uuid("2ed88065-05ba-483b-8d2c-59ef7c985079"))
AcSmPersistProxy;
    // [ default ] interface IAcSmPersistProxy

struct __declspec(uuid("00deb7fb-a073-4ecd-bce0-121b45c6864d"))
AcSmObjectReference;
    // [ default ] interface IAcSmObjectReference

enum __declspec(uuid("5a943186-ffc1-4708-86c8-123029970629"))
AcSmObjectReferenceFlags
{
    AcSmObjectReference_SoftPointer = 1,
    AcSmObjectReference_HardPointer = 2
};

struct __declspec(uuid("f57f96e7-0f16-4dc9-8f09-52f7bb389ab6"))
AcSmPublishOptions;
    // [ default ] interface IAcSmPublishOptions

struct __declspec(uuid("e6f88130-cd68-49ca-b722-251d583fa67e"))
AcSmFileWatchReactor;
    // [ default ] interface IAcSmFileWatchReactor

enum __declspec(uuid("e9d7f966-7ae5-4d2e-968a-88132a80492a"))
FileNotifyAction
{
    FileActionAdded = 1,
    FileActionRemoved = 2,
    FileActionModified = 3,
    FileActionRenamedOldName = 4,
    FileActionRenamedNewName = 5
};

struct __declspec(uuid("f340a8b3-2c69-4ef9-b6cd-6a08e019904d"))
IAdComFileWatchReactor : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall OnFileChange (
        /*[in]*/ enum FileNotifyAction action ) = 0;
      virtual HRESULT __stdcall OnError (
        /*[in]*/ long num,
        /*[in]*/ BSTR description ) = 0;
};

enum __declspec(uuid("17f82592-7ae4-4ffa-9bfd-31b9be9aacc0"))
FileNotifyFlags
{
    FileNotifyChangeFileName = 1,
    FileNotifyChangeDirName = 2,
    FileNotifyChangeAttributes = 4,
    FileNotifyChangeSize = 8,
    FileNotifyChangeLastWrite = 16,
    FileNotifyChangeLastAccess = 32,
    FileNotifyChangeCreation = 64,
    FileNotifyChangeSecurity = 256,
    FileNotifyChangeSizeOrDate = 24,
    FileNotifyDefault = 89
};

struct __declspec(uuid("33fd42d8-0154-4804-aca8-3ca123c2262e"))
AcSmProjectPointLocation;
    // [ default ] interface IAcSmProjectPointLocation

struct __declspec(uuid("e40ea246-bab4-4907-81a5-511ea30c16fd"))
AcSmProjectPointLocations;
    // [ default ] interface IAcSmProjectPointLocations

struct __declspec(uuid("8e974876-ff7f-48d3-8435-a6328ccc496f"))
IAcSmFiler : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Init (
        /*[in]*/ IUnknown * pUnk,
        /*[in]*/ struct IAcSmDatabase * pDb,
        /*[in]*/ VARIANT_BOOL bForWrite ) = 0;
      virtual HRESULT __stdcall Close (
        /*[in]*/ VARIANT_BOOL bSuccess ) = 0;
      virtual HRESULT __stdcall GetDatabase (
        /*[out,retval]*/ struct IAcSmDatabase * * ppDb ) = 0;
      virtual HRESULT __stdcall PushCurrentWriteObject (
        /*[in]*/ struct IAcSmPersist * pObj ) = 0;
      virtual HRESULT __stdcall PopCurrentWriteObject (
        /*[in]*/ long bSuccess ) = 0;
      virtual HRESULT __stdcall PushCurrentReadObject (
        /*[in]*/ struct IAcSmPersist * pObj ) = 0;
      virtual HRESULT __stdcall PopCurrentReadObject (
        /*[in]*/ long bSuccess ) = 0;
      virtual HRESULT __stdcall GetCurrentObject (
        /*[out,retval]*/ struct IAcSmPersist * * pVal ) = 0;
      virtual HRESULT __stdcall GetCurrentObjectHeaderInfo (
        /*[out]*/ SAFEARRAY * * names,
        /*[out]*/ SAFEARRAY * * values ) = 0;
      virtual HRESULT __stdcall GetRevisionNumber (
        /*[out,retval]*/ long * pRevisionNum ) = 0;
      virtual HRESULT __stdcall ReadObject (
        /*[out,retval]*/ struct IAcSmPersist * * ppObj ) = 0;
      virtual HRESULT __stdcall ReadProperty (
        /*[out]*/ BSTR * ppPropname,
        /*[out]*/ VARIANT * pVal ) = 0;
      virtual HRESULT __stdcall ReadRawData (
        /*[out]*/ unsigned char * * p,
        /*[out]*/ long * count ) = 0;
      virtual HRESULT __stdcall WriteObject (
        /*[in]*/ struct IAcSmPersist * pObj ) = 0;
      virtual HRESULT __stdcall WriteProperty (
        /*[in]*/ BSTR pPropname,
        /*[in]*/ VARIANT * pVal ) = 0;
      virtual HRESULT __stdcall WriteRawData (
        /*[in]*/ unsigned char * p,
        /*[in]*/ long count ) = 0;
      virtual HRESULT __stdcall ReadGuid (
        /*[out,retval]*/ GUID * pGuid ) = 0;
      virtual HRESULT __stdcall ReadInt (
        /*[out,retval]*/ long * pInt ) = 0;
      virtual HRESULT __stdcall ReadDouble (
        /*[out,retval]*/ double * pDbl ) = 0;
      virtual HRESULT __stdcall ReadString (
        /*[out,retval]*/ BSTR * pStr ) = 0;
      virtual HRESULT __stdcall ReadBytes (
        /*[out]*/ unsigned char * * p,
        /*[in,out]*/ long * count ) = 0;
      virtual HRESULT __stdcall WriteGuid (
        /*[in]*/ GUID id ) = 0;
      virtual HRESULT __stdcall WriteInt (
        /*[in]*/ long pInt ) = 0;
      virtual HRESULT __stdcall WriteDouble (
        /*[in]*/ double pDbl ) = 0;
      virtual HRESULT __stdcall WriteString (
        /*[in]*/ BSTR s ) = 0;
      virtual HRESULT __stdcall WriteBytes (
        /*[in]*/ unsigned char * p,
        /*[in]*/ long count ) = 0;
};

struct __declspec(uuid("ab9e4650-c3a8-4747-8d89-80731a4644a1"))
IAcSmPersist : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetClassID (
        /*[out,retval]*/ GUID * p ) = 0;
      virtual HRESULT __stdcall GetIsDirty (
        /*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
      virtual HRESULT __stdcall Load (
        /*[in]*/ struct IAcSmFiler * pFiler ) = 0;
      virtual HRESULT __stdcall Save (
        /*[in]*/ struct IAcSmFiler * pFiler ) = 0;
      virtual HRESULT __stdcall GetTypeName (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall InitNew (
        /*[in]*/ struct IAcSmPersist * pOwner ) = 0;
      virtual HRESULT __stdcall GetOwner (
        /*[out,retval]*/ struct IAcSmPersist * * ppOwner ) = 0;
      virtual HRESULT __stdcall SetOwner (
        /*[in]*/ struct IAcSmPersist * pOwner ) = 0;
      virtual HRESULT __stdcall GetDatabase (
        /*[out,retval]*/ struct IAcSmDatabase * * ppDb ) = 0;
      virtual HRESULT __stdcall GetObjectId (
        /*[out,retval]*/ struct IAcSmObjectId * * ppId ) = 0;
      virtual HRESULT __stdcall Clear ( ) = 0;
      virtual HRESULT __stdcall GetDirectlyOwnedObjects (
        /*[out]*/ SAFEARRAY * * objects ) = 0;
};

struct __declspec(uuid("da800d3b-975c-4381-9531-358328792650"))
IAcSmCustomPropertyValue : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetValue (
        /*[out,retval]*/ VARIANT * value ) = 0;
      virtual HRESULT __stdcall SetValue (
        /*[in]*/ VARIANT value ) = 0;
      virtual HRESULT __stdcall GetFlags (
        /*[out,retval]*/ PropertyFlags * value ) = 0;
      virtual HRESULT __stdcall SetFlags (
        /*[in]*/ PropertyFlags value ) = 0;
};

struct __declspec(uuid("476cbb88-8878-419d-a8c5-a9ced89d5a37"))
IAcSmEnumProperty : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out]*/ BSTR * propname,
        /*[out]*/ struct IAcSmCustomPropertyValue * * ppValue ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("fa893fe9-247c-44ec-b437-541c0f09f5fc"))
IAcSmCustomPropertyBag : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetProperty (
        /*[in]*/ BSTR name,
        /*[out,retval]*/ struct IAcSmCustomPropertyValue * * value ) = 0;
      virtual HRESULT __stdcall SetProperty (
        /*[in]*/ BSTR name,
        /*[in]*/ struct IAcSmCustomPropertyValue * value ) = 0;
      virtual HRESULT __stdcall GetPropertyEnumerator (
        /*[out,retval]*/ struct IAcSmEnumProperty * * enumerator ) = 0;
};

struct __declspec(uuid("0e463002-12a4-4828-b4cf-28d8cbf8c768"))
IAcSmComponent : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetName (
        /*[out,retval]*/ BSTR * name ) = 0;
      virtual HRESULT __stdcall SetName (
        /*[in]*/ BSTR name ) = 0;
      virtual HRESULT __stdcall GetDesc (
        /*[out,retval]*/ BSTR * desc ) = 0;
      virtual HRESULT __stdcall SetDesc (
        /*[in]*/ BSTR desc ) = 0;
      virtual HRESULT __stdcall GetCustomPropertyBag (
        /*[out,retval]*/ struct IAcSmCustomPropertyBag * * bag ) = 0;
};

struct __declspec(uuid("b86d90c3-7d13-4180-8f97-61c09fa15902"))
IAcSmFileReference : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall SetFileName (
        /*[in]*/ BSTR pValue ) = 0;
      virtual HRESULT __stdcall GetFileName (
        /*[out,retval]*/ BSTR * ppValue ) = 0;
      virtual HRESULT __stdcall ResolveFileName (
        /*[out,retval]*/ BSTR * pResult ) = 0;
};

struct __declspec(uuid("25b22534-b1f7-402c-82d6-d36fac620d69"))
IAcSmAcDbObjectReference : IAcSmFileReference
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall SetAcDbHandle (
        /*[in]*/ BSTR handle ) = 0;
      virtual HRESULT __stdcall GetAcDbHandle (
        /*[out,retval]*/ BSTR * phandle ) = 0;
      virtual HRESULT __stdcall GetAcSmAcDbDatabase (
        /*[out,retval]*/ struct IAcSmAcDbDatabase * * ppAcSmAcDbDatabase ) = 0;
      virtual HRESULT __stdcall SetAcDbObject (
        /*[in]*/ struct IAcadObject * pAcDbObject ) = 0;
      virtual HRESULT __stdcall ResolveAcDbObject (
        /*[in]*/ struct IAcadDatabase * pAcDbDatabase,
        /*[out,retval]*/ BSTR * phandle ) = 0;
};

struct __declspec(uuid("c5e0c361-9e43-4574-a0ab-defa483511e4"))
IAcSmNamedAcDbObjectReference : IAcSmAcDbObjectReference
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall SetName (
        /*[in]*/ BSTR name ) = 0;
      virtual HRESULT __stdcall GetName (
        /*[out,retval]*/ BSTR * phandle ) = 0;
      virtual HRESULT __stdcall SetOwnerAcDbHandle (
        /*[in]*/ BSTR handle ) = 0;
      virtual HRESULT __stdcall GetOwnerAcDbHandle (
        /*[out,retval]*/ BSTR * phandle ) = 0;
};

struct __declspec(uuid("330cd4d2-73fe-43dc-85cc-48263863cfba"))
IAcSmEnumComponent : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmComponent * * comp ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("b2305c6b-130a-4eb0-b89b-b5fba9f44f84"))
IAcSmEnumNamedAcDbObjectReference : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppRef ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("cfbf491d-19c4-4893-9c4b-bc3dfb6d5e64"))
IAcSmCalloutBlocks : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Add (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pBlkRef ) = 0;
      virtual HRESULT __stdcall Remove (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pBlkRef ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumNamedAcDbObjectReference * * enumerator ) = 0;
};

struct __declspec(uuid("1bea479e-ec3a-49b8-94e5-cfcee92c4afe"))
IAcSmSheetSelSet : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Add (
        /*[in]*/ struct IAcSmComponent * comp ) = 0;
      virtual HRESULT __stdcall Remove (
        /*[in]*/ struct IAcSmComponent * comp ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumComponent * * enumerator ) = 0;
};

struct __declspec(uuid("e8c8d548-3b80-4810-b866-617a7b916fe8"))
IAcSmEnumSheetSelSet : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmSheetSelSet * * selset ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("20786806-b251-4277-b119-94209c2ea7f9"))
IAcSmSheetSelSets : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Add (
        BSTR name,
        BSTR desc,
        struct IAcSmSheetSelSet * * selset ) = 0;
      virtual HRESULT __stdcall Remove (
        /*[in]*/ struct IAcSmSheetSelSet * selset ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumSheetSelSet * * enumerator ) = 0;
};

struct __declspec(uuid("73fcecfa-6343-4630-889b-d03cbfbc2431"))
IAcSmEnumFileReference : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmFileReference * * ppRef ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("b448171b-d56c-4834-bf45-3d2ed0a66229"))
IAcSmResources : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Add (
        /*[in]*/ struct IAcSmFileReference * pResource ) = 0;
      virtual HRESULT __stdcall Remove (
        /*[in]*/ struct IAcSmFileReference * pResource ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumFileReference * * enumerator ) = 0;
};

struct __declspec(uuid("147981d1-af77-42a1-8b91-4994a16a59fd"))
IAcSmPublishOptions : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetDefaultOutputdir (
        /*[out,retval]*/ struct IAcSmFileReference * * ppValue ) = 0;
      virtual HRESULT __stdcall SetDefaultOutputdir (
        /*[in]*/ struct IAcSmFileReference * pValue ) = 0;
      virtual HRESULT __stdcall GetDwfType (
        /*[out,retval]*/ VARIANT_BOOL * pValue ) = 0;
      virtual HRESULT __stdcall SetDwfType (
        /*[in]*/ VARIANT_BOOL value ) = 0;
      virtual HRESULT __stdcall GetPromptForName (
        /*[out,retval]*/ VARIANT_BOOL * pValue ) = 0;
      virtual HRESULT __stdcall SetPromptForName (
        /*[in]*/ VARIANT_BOOL value ) = 0;
      virtual HRESULT __stdcall GetUsePassword (
        /*[out,retval]*/ VARIANT_BOOL * pValue ) = 0;
      virtual HRESULT __stdcall SetUsePassword (
        /*[in]*/ VARIANT_BOOL value ) = 0;
      virtual HRESULT __stdcall GetPromptForPassword (
        /*[out,retval]*/ VARIANT_BOOL * pValue ) = 0;
      virtual HRESULT __stdcall SetPromptForPassword (
        /*[in]*/ VARIANT_BOOL value ) = 0;
      virtual HRESULT __stdcall GetLayerInfo (
        /*[out,retval]*/ VARIANT_BOOL * pValue ) = 0;
      virtual HRESULT __stdcall SetLayerInfo (
        /*[in]*/ VARIANT_BOOL value ) = 0;
      virtual HRESULT __stdcall GetUnrecognizedData (
        /*[out,retval]*/ struct IAcSmCustomPropertyBag * * bag ) = 0;
      virtual HRESULT __stdcall SetUnrecognizedData (
        /*[in]*/ struct IAcSmCustomPropertyBag * bag ) = 0;
      virtual HRESULT __stdcall GetUnrecognizedSections (
        /*[out,retval]*/ struct IAcSmCustomPropertyBag * * sectionArray ) = 0;
      virtual HRESULT __stdcall SetUnrecognizedSections (
        /*[in]*/ struct IAcSmCustomPropertyBag * sectionArray ) = 0;
};

struct __declspec(uuid("0b79150e-c037-48ad-a93f-2ff6d3104d11"))
IAcSmProjectPointLocation : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetName (
        /*[out]*/ BSTR * name ) = 0;
      virtual HRESULT __stdcall SetName (
        /*[in]*/ BSTR name ) = 0;
      virtual HRESULT __stdcall GetURL (
        /*[out]*/ BSTR * url ) = 0;
      virtual HRESULT __stdcall SetURL (
        /*[in]*/ BSTR url ) = 0;
      virtual HRESULT __stdcall GetFolder (
        /*[out]*/ BSTR * folder ) = 0;
      virtual HRESULT __stdcall SetFolder (
        /*[in]*/ BSTR folder ) = 0;
      virtual HRESULT __stdcall GetUsername (
        /*[out]*/ BSTR * username ) = 0;
      virtual HRESULT __stdcall SetUsername (
        /*[in]*/ BSTR username ) = 0;
      virtual HRESULT __stdcall GetPassword (
        /*[out]*/ BSTR * password ) = 0;
      virtual HRESULT __stdcall SetPassword (
        /*[in]*/ BSTR password ) = 0;
};

struct __declspec(uuid("af02d3b1-a2e4-44c7-85ae-01038365dec2"))
IAcSmEnumProjectPointLocation : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmProjectPointLocation * * location ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("2760e2a6-c735-4a97-8260-f1af212c8a4d"))
IAcSmProjectPointLocations : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetLocation (
        /*[in]*/ BSTR locationName,
        /*[out]*/ struct IAcSmProjectPointLocation * * location ) = 0;
      virtual HRESULT __stdcall RemoveLocation (
        /*[in]*/ struct IAcSmProjectPointLocation * location ) = 0;
      virtual HRESULT __stdcall AddNewLocation (
        /*[in]*/ BSTR name,
        /*[in]*/ BSTR url,
        /*[in]*/ BSTR folder,
        /*[in]*/ BSTR username,
        /*[in]*/ BSTR password,
        /*[out]*/ struct IAcSmProjectPointLocation * * location ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumProjectPointLocation * * enumerator ) = 0;
};

struct __declspec(uuid("56832073-a227-43f5-b5e9-bb4f0e4c7ad4"))
IAcSmEvents : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall OnChanged (
        /*[in]*/ AcSmEvent event,
        /*[in]*/ struct IAcSmPersist * comp ) = 0;
};

struct __declspec(uuid("746e7d4f-0024-44ae-8753-f1ccae44072c"))
IAcSmEnumPersist : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmPersist * * ppObject ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("d5bb3e7e-2af7-4d10-94b3-213ffdaf16c8"))
IAcSmPersistProxy : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall SetClassID (
        /*[in]*/ GUID classID ) = 0;
      virtual HRESULT __stdcall SetTypeName (
        /*[in]*/ BSTR value ) = 0;
      virtual HRESULT __stdcall GetRawData (
        /*[out]*/ unsigned char * * ppData,
        /*[out]*/ long * pBufSize ) = 0;
};

struct __declspec(uuid("adf37497-a661-4306-b048-a703e842d2fa"))
IAcSmObjectReference : IAcSmPersist
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall SetReferencedObject (
        /*[in]*/ struct IAcSmPersist * pObject ) = 0;
      virtual HRESULT __stdcall GetReferencedObject (
        /*[out,retval]*/ struct IAcSmPersist * * ppObject ) = 0;
      virtual HRESULT __stdcall GetReferenceFlags (
        /*[out,retval]*/ enum AcSmObjectReferenceFlags * value ) = 0;
      virtual HRESULT __stdcall SetReferenceFlags (
        /*[in]*/ enum AcSmObjectReferenceFlags value ) = 0;
};

struct __declspec(uuid("5585723a-4859-4dd9-9913-996484d6060d"))
IAcSmDatabase : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall LoadFromFile (
        /*[in]*/ BSTR templateDstFileName ) = 0;
      virtual HRESULT __stdcall GetFileName (
        /*[out,retval]*/ BSTR * pVal ) = 0;
      virtual HRESULT __stdcall SetFileName (
        /*[in]*/ BSTR newVal ) = 0;
      virtual HRESULT __stdcall GetTemplateDstFileName (
        /*[out,retval]*/ BSTR * filename ) = 0;
      virtual HRESULT __stdcall GetSheetSet (
        /*[out,retval]*/ struct IAcSmSheetSet * * pVal ) = 0;
      virtual HRESULT __stdcall LockDb (
        /*[in]*/ IUnknown * pObject ) = 0;
      virtual HRESULT __stdcall UnlockDb (
        /*[in]*/ IUnknown * pObject,
        /*[in]*/ VARIANT_BOOL bCommit ) = 0;
      virtual HRESULT __stdcall GetLockStatus (
        /*[out,retval]*/ enum AcSmLockStatus * pLockStatus ) = 0;
      virtual HRESULT __stdcall GetLockOwnerInfo (
        /*[out]*/ BSTR * pstrUserName,
        /*[out]*/ BSTR * pstrMachineName ) = 0;
      virtual HRESULT __stdcall GetNewObjectId (
        /*[in]*/ BSTR hand,
        /*[out]*/ long * idcookie,
        /*[out,retval]*/ struct IAcSmObjectId * * ppId ) = 0;
      virtual HRESULT __stdcall RegisterOwner (
        /*[in]*/ long idcookie,
        /*[in]*/ struct IAcSmPersist * pObject,
        /*[in]*/ struct IAcSmPersist * pOwner ) = 0;
      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumPersist * * ppEnum ) = 0;
      virtual HRESULT __stdcall Register (
        /*[in]*/ struct IAcSmEvents * eventHandler,
        /*[out,retval]*/ long * cookie ) = 0;
      virtual HRESULT __stdcall Unregister (
        /*[in]*/ long cookie ) = 0;
      virtual HRESULT __stdcall NotifyRegisteredEventHandlers (
        /*[in]*/ AcSmEvent event,
        /*[in]*/ struct IAcSmPersist * comp ) = 0;
      virtual HRESULT __stdcall FindObject (
        /*[in]*/ BSTR hand,
        /*[out,retval]*/ struct IAcSmPersist * * ppObject ) = 0;
      virtual HRESULT __stdcall FindAcDbObjectReferences (
        /*[in]*/ struct IAcadObject * pAcDbObject,
        /*[out,retval]*/ SAFEARRAY * * ppObjects ) = 0;
      virtual HRESULT __stdcall UpdateInMemoryDwgHints ( ) = 0;
      virtual HRESULT __stdcall GetIsTemporary (
        /*[out,retval]*/ VARIANT_BOOL * isTemporary ) = 0;
      virtual HRESULT __stdcall SetIsTemporary ( ) = 0;
};

struct __declspec(uuid("42634426-cdfb-4e32-ad46-992ceb3b1596"))
IAcSmObjectId : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetHandle (
        /*[out,retval]*/ BSTR * hand ) = 0;
      virtual HRESULT __stdcall GetDatabase (
        /*[out,retval]*/ struct IAcSmDatabase * * ppDb ) = 0;
      virtual HRESULT __stdcall GetPersistObject (
        /*[out,retval]*/ struct IAcSmPersist * * ppObj ) = 0;
      virtual HRESULT __stdcall GetOwner (
        /*[out,retval]*/ struct IAcSmPersist * * ppObj ) = 0;
      virtual HRESULT __stdcall IsEqual (
        /*[in]*/ struct IAcSmObjectId * pId,
        /*[out,retval]*/ VARIANT_BOOL * pResult ) = 0;
      virtual HRESULT __stdcall IsValid (
        /*[out,retval]*/ VARIANT_BOOL * pResult ) = 0;
};

struct __declspec(uuid("02aacc99-5c5a-4528-a00a-73f71c51439b"))
IAcSmEnumDatabase : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmDatabase * * db ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("faf2007f-ffcb-4fb3-b52e-5ae98c964d60"))
IAcSmFileWatchReactor : IAdComFileWatchReactor
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Init (
        /*[in]*/ struct IAcSmDatabase * pDb,
        /*[in]*/ VARIANT_BOOL bIsForLock,
        /*[in]*/ BSTR filename,
        /*[in]*/ enum FileNotifyFlags notifyflags ) = 0;
      virtual HRESULT __stdcall Attach ( ) = 0;
      virtual HRESULT __stdcall Detach ( ) = 0;
      virtual HRESULT __stdcall LastError (
        /*[out,retval]*/ long * pstatus ) = 0;
};

struct __declspec(uuid("8cceb838-acf5-4048-b9f0-09a843ca2ac4"))
IAcSmSubset : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetNewSheetLocation (
        /*[out,retval]*/ struct IAcSmFileReference * * ppFileRef ) = 0;
      virtual HRESULT __stdcall SetNewSheetLocation (
        /*[in]*/ struct IAcSmFileReference * pFileRef ) = 0;
      virtual HRESULT __stdcall GetDefDwtLayout (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppLayoutRef ) = 0;
      virtual HRESULT __stdcall SetDefDwtLayout (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pLayoutRef ) = 0;
      virtual HRESULT __stdcall GetPromptForDwt (
        /*[out,retval]*/ VARIANT_BOOL * askForDwt ) = 0;
      virtual HRESULT __stdcall SetPromptForDwt (
        /*[in]*/ VARIANT_BOOL askForDwt ) = 0;
      virtual HRESULT __stdcall GetSheetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumComponent * * enumerator ) = 0;
      virtual HRESULT __stdcall AddNewSheet (
        /*[in]*/ BSTR name,
        /*[in]*/ BSTR desc,
        /*[out,retval]*/ struct IAcSmSheet * * newSheet ) = 0;
      virtual HRESULT __stdcall InsertComponent (
        /*[in]*/ struct IAcSmComponent * newSheet,
        /*[in]*/ struct IAcSmComponent * beforeComp ) = 0;
      virtual HRESULT __stdcall InsertComponentAfter (
        /*[in]*/ struct IAcSmComponent * newSheet,
        /*[in]*/ struct IAcSmComponent * afterComp ) = 0;
      virtual HRESULT __stdcall ImportSheet (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pLayoutRef,
        /*[out,retval]*/ struct IAcSmSheet * * newSheet ) = 0;
      virtual HRESULT __stdcall RemoveSheet (
        struct IAcSmSheet * sheet ) = 0;
      virtual HRESULT __stdcall CreateSubset (
        /*[in]*/ BSTR name,
        /*[in]*/ BSTR desc,
        /*[out,retval]*/ struct IAcSmSubset * * subset ) = 0;
      virtual HRESULT __stdcall RemoveSubset (
        /*[in]*/ struct IAcSmSubset * subset ) = 0;
      virtual HRESULT __stdcall NotifyRegisteredEventHandlers (
        /*[in]*/ AcSmEvent event,
        /*[in]*/ struct IAcSmPersist * comp ) = 0;
      virtual HRESULT __stdcall UpdateInMemoryDwgHints ( ) = 0;
};

struct __declspec(uuid("537476a6-e9e9-4e25-b6ea-fb5b8b086153"))
IAcSmSheetSet : IAcSmSubset
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetAltPageSetups (
        /*[out,retval]*/ struct IAcSmFileReference * * ppDwtRef ) = 0;
      virtual HRESULT __stdcall SetAltPageSetups (
        /*[in]*/ struct IAcSmFileReference * pDwtRef ) = 0;
      virtual HRESULT __stdcall GetDefAltPageSetup (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppAltPageSetup ) = 0;
      virtual HRESULT __stdcall SetDefAltPageSetup (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pAltPageSetup ) = 0;
      virtual HRESULT __stdcall GetPromptForDwgName (
        /*[out,retval]*/ VARIANT_BOOL * askForName ) = 0;
      virtual HRESULT __stdcall SetPromptForDwgName (
        /*[in]*/ VARIANT_BOOL askForName ) = 0;
      virtual HRESULT __stdcall GetSheetSelSets (
        /*[out,retval]*/ struct IAcSmSheetSelSets * * ppSheetSelSets ) = 0;
      virtual HRESULT __stdcall GetResources (
        /*[out,retval]*/ struct IAcSmResources * * ppResources ) = 0;
      virtual HRESULT __stdcall GetCalloutBlocks (
        /*[out,retval]*/ struct IAcSmCalloutBlocks * * ppCalloutBlocks ) = 0;
      virtual HRESULT __stdcall GetViewCategories (
        /*[out,retval]*/ struct IAcSmViewCategories * * ppViewCategories ) = 0;
      virtual HRESULT __stdcall GetDefLabelBlk (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppLabelBlkRef ) = 0;
      virtual HRESULT __stdcall SetDefLabelBlk (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pLabelBlkRef ) = 0;
      virtual HRESULT __stdcall GetPublishOptions (
        /*[out,retval]*/ struct IAcSmPublishOptions * * ppPublishOptions ) = 0;
      virtual HRESULT __stdcall GetProjectPointLocations (
        /*[out,retval]*/ struct IAcSmProjectPointLocations * * ppLocations ) = 0;
      virtual HRESULT __stdcall Sync (
        /*[in]*/ struct IAcadDatabase * pXDb ) = 0;
      virtual HRESULT __stdcall Register (
        /*[in]*/ struct IAcSmEvents * eventHandler,
        /*[out,retval]*/ long * cookie ) = 0;
      virtual HRESULT __stdcall Unregister (
        /*[in]*/ long cookie ) = 0;
      virtual HRESULT __stdcall UpdateSheetCustomProps ( ) = 0;
};

struct __declspec(uuid("59bc91bb-fad8-44f9-86f9-5c99fa6b4edd"))
IAcSmSheet : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetNumber (
        /*[out,retval]*/ BSTR * num ) = 0;
      virtual HRESULT __stdcall SetNumber (
        /*[in]*/ BSTR num ) = 0;
      virtual HRESULT __stdcall GetTitle (
        /*[out,retval]*/ BSTR * title ) = 0;
      virtual HRESULT __stdcall SetTitle (
        /*[in]*/ BSTR title ) = 0;
      virtual HRESULT __stdcall GetLayout (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppLayoutRef ) = 0;
      virtual HRESULT __stdcall SetLayout (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pLayoutRef ) = 0;
      virtual HRESULT __stdcall GetDoNotPlot (
        /*[out,retval]*/ VARIANT_BOOL * doNotPlot ) = 0;
      virtual HRESULT __stdcall SetDoNotPlot (
        /*[in]*/ VARIANT_BOOL doNotPlot ) = 0;
      virtual HRESULT __stdcall GetSheetViews (
        /*[out,retval]*/ struct IAcSmSheetViews * * sheetviews ) = 0;
};

struct __declspec(uuid("4cc6fc8f-f1c6-486d-b550-838b0234e03c"))
IAcSmSheetSetMgr : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall CreateDatabase (
        /*[in]*/ BSTR filename,
        /*[in]*/ BSTR templatefilename,
        /*[in]*/ VARIANT_BOOL bAlwaysCreate,
        /*[out,retval]*/ struct IAcSmDatabase * * db ) = 0;
      virtual HRESULT __stdcall OpenDatabase (
        /*[in]*/ BSTR filename,
        /*[in]*/ VARIANT_BOOL bFailIfAlreadyOpen,
        /*[out,retval]*/ struct IAcSmDatabase * * db ) = 0;
      virtual HRESULT __stdcall FindOpenDatabase (
        /*[in]*/ BSTR filename,
        /*[out,retval]*/ struct IAcSmDatabase * * ppDb ) = 0;
      virtual HRESULT __stdcall CloseAll ( ) = 0;
      virtual HRESULT __stdcall Close (
        /*[in]*/ struct IAcSmDatabase * db ) = 0;
      virtual HRESULT __stdcall Register (
        /*[in]*/ struct IAcSmEvents * eventHandler,
        /*[out,retval]*/ long * cookie ) = 0;
      virtual HRESULT __stdcall Unregister (
        /*[in]*/ long cookie ) = 0;
      virtual HRESULT __stdcall GetParentSheetSet (
        /*[in]*/ BSTR dwg,
        /*[in]*/ BSTR layout,
        /*[out]*/ struct IAcSmSheetSet * * sheetSet,
        /*[out,retval]*/ struct IAcSmDatabase * * pSmDb ) = 0;
      virtual HRESULT __stdcall GetSheetFromLayout (
        /*[in]*/ struct IAcadObject * pAcDbLayout,
        /*[out]*/ struct IAcSmSheet * * sheet,
        /*[out,retval]*/ struct IAcSmDatabase * * pSmDb ) = 0;
      virtual HRESULT __stdcall GetDatabaseEnumerator (
        /*[out,retval]*/ struct IAcSmEnumDatabase * * enumerator ) = 0;
};

struct __declspec(uuid("5d2d1da2-97ca-48d9-93fd-bbc5b5852962"))
IAcSmSheetViews : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumSheetView * * enumerator ) = 0;
      virtual HRESULT __stdcall Sync (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pLayout,
        /*[in]*/ struct IAcadDatabase * pXDb ) = 0;
};

struct __declspec(uuid("07bb6db5-2198-4ea2-8752-e5a520d01a47"))
IAcSmEnumSheetView : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmSheetView * * sview ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("a5b52086-a849-4a06-9b77-41d860e5a11b"))
IAcSmViewCategory : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetSheetViewEnumerator (
        /*[out,retval]*/ struct IAcSmEnumSheetView * * enumerator ) = 0;
      virtual HRESULT __stdcall GetCalloutBlocks (
        /*[out,retval]*/ struct IAcSmCalloutBlocks * * ppCalloutBlocks ) = 0;
};

struct __declspec(uuid("f69ceaf1-819f-4b7a-b5e6-d39395415f55"))
IAcSmSheetView : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetNamedView (
        /*[out,retval]*/ struct IAcSmNamedAcDbObjectReference * * ppViewRef ) = 0;
      virtual HRESULT __stdcall SetNamedView (
        /*[in]*/ struct IAcSmNamedAcDbObjectReference * pViewRef ) = 0;
      virtual HRESULT __stdcall GetCategory (
        /*[out,retval]*/ struct IAcSmViewCategory * * ppViewCat ) = 0;
      virtual HRESULT __stdcall SetCategory (
        /*[in]*/ struct IAcSmViewCategory * pViewCat ) = 0;
      virtual HRESULT __stdcall GetNumber (
        /*[out,retval]*/ BSTR * num ) = 0;
      virtual HRESULT __stdcall SetNumber (
        /*[in]*/ BSTR num ) = 0;
      virtual HRESULT __stdcall GetTitle (
        /*[out,retval]*/ BSTR * title ) = 0;
      virtual HRESULT __stdcall SetTitle (
        /*[in]*/ BSTR title ) = 0;
};

struct __declspec(uuid("460b347f-c804-42f0-91d5-7ddd925e5058"))
IAcSmEnumViewCategory : IUnknown
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall Next (
        /*[out,retval]*/ struct IAcSmViewCategory * * viewCat ) = 0;
      virtual HRESULT __stdcall Reset ( ) = 0;
};

struct __declspec(uuid("b28b23eb-ff5e-4910-8ca6-ad54931013f3"))
IAcSmViewCategories : IAcSmComponent
{
    //
    // Raw methods provided by interface
    //

      virtual HRESULT __stdcall GetEnumerator (
        /*[out,retval]*/ struct IAcSmEnumViewCategory * * enumerator ) = 0;
      virtual HRESULT __stdcall CreateViewCategory (
        /*[in]*/ BSTR name,
        /*[in]*/ BSTR desc,
        /*[in]*/ BSTR id,
        /*[out,retval]*/ struct IAcSmViewCategory * * viewCat ) = 0;
      virtual HRESULT __stdcall RemoveViewCategory (
        /*[in]*/ struct IAcSmViewCategory * viewCat ) = 0;
      virtual HRESULT __stdcall GetDefaultViewCategory (
        /*[out,retval]*/ struct IAcSmViewCategory * * ppItem ) = 0;
};

//
// Named GUID constants initializations
//

extern "C" const GUID __declspec(selectany) LIBID_ACSMCOMPONENTS16Lib =
    {0x042b7bf0,0x05c4,0x442a,{0xad,0xde,0x94,0x42,0x85,0x04,0xc7,0xfd}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmDSTFiler =
    {0x63eef39a,0xe068,0x474a,{0xa5,0xcd,0xd4,0x8c,0x61,0x51,0xc8,0x2b}};
extern "C" const GUID __declspec(selectany) IID_IAcSmAcDbDatabase =
    {0x0070c60f,0x987a,0x4349,{0x9e,0x0a,0x3a,0xcb,0xa0,0xcc,0x9c,0x5b}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmDatabase =
    {0x2162c6b6,0x0ce4,0x40e8,{0x91,0x2b,0x46,0xf5,0x9d,0xfd,0xf8,0x26}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetSet =
    {0xb20534f2,0x0978,0x418c,{0x8d,0x14,0x2e,0x69,0x28,0xa0,0x77,0xed}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSubset =
    {0x076d548f,0xb0f5,0x4fe1,{0xb3,0x5d,0x7f,0x7b,0x73,0xb8,0xd3,0x22}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmResources =
    {0x3f0faf10,0x09de,0x4eba,{0xae,0xd1,0xc4,0xe4,0xd6,0xfe,0xcf,0x5d}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmCalloutBlocks =
    {0x203eab46,0x483b,0x4e6b,{0xa1,0x0b,0x15,0xe9,0xa4,0xb2,0x10,0xff}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmCalloutBlockReferences =
    {0x67c52fe4,0x0a6b,0x4c82,{0xa4,0xcc,0x5e,0x68,0x53,0x77,0x47,0xb0}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetSelSet =
    {0xebf70db8,0xf495,0x4522,{0xba,0x80,0x43,0x97,0x6b,0xf3,0x5b,0x3e}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetSelSets =
    {0x444780b8,0x6527,0x43a8,{0x8d,0xc4,0xfa,0xb4,0x1b,0x7e,0x48,0xbb}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheet =
    {0x16a07941,0xbc15,0x4d48,{0xa8,0x80,0x9d,0x5a,0x21,0x1d,0x50,0x65}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetView =
    {0xb6e09611,0x4659,0x4f0d,{0x98,0x1d,0xd6,0x2b,0x11,0xfd,0x84,0x26}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetViews =
    {0xf40f931b,0x64bc,0x4b90,{0x9f,0xc8,0xa1,0x1a,0x77,0xd6,0x81,0x5b}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmViewCategory =
    {0x4aea81ed,0xc24f,0x477b,{0xa5,0x34,0xea,0x69,0x22,0x0a,0x27,0x6a}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmViewCategories =
    {0x021730df,0x5bea,0x48e9,{0xbc,0x7a,0x35,0x08,0x7a,0x67,0x4f,0xd0}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmSheetSetMgr =
    {0x80caa04c,0x3a1e,0x4513,{0x82,0x67,0x59,0x85,0x1c,0x99,0x76,0x55}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmFileReference =
    {0x6bf87ae7,0x1bec,0x4bdb,{0x98,0xbb,0x5b,0x91,0xf7,0x77,0x27,0x93}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmAcDbDatabase =
    {0x3750caec,0x9cd1,0x4778,{0xb8,0x49,0x2a,0x28,0x1c,0x00,0x69,0x56}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmAcDbObjectReference =
    {0x7188d70d,0x7b73,0x4f29,{0x86,0xcf,0xcb,0xa1,0xa5,0xf4,0xdb,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmNamedAcDbObjectReference =
    {0x76527aac,0x4575,0x4b0a,{0x9a,0xeb,0x0a,0x1c,0x3b,0x0e,0xc8,0x55}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmCustomPropertyValue =
    {0x8d22a2a4,0x1777,0x4d78,{0x84,0xcc,0x69,0xef,0x74,0x1f,0xe9,0x54}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmCustomPropertyBag =
    {0x4d103908,0x8c86,0x4d95,{0xbb,0xf4,0x68,0xb9,0xa7,0xb0,0x07,0x31}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmPersistProxy =
    {0x2ed88065,0x05ba,0x483b,{0x8d,0x2c,0x59,0xef,0x7c,0x98,0x50,0x79}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmObjectReference =
    {0x00deb7fb,0xa073,0x4ecd,{0xbc,0xe0,0x12,0x1b,0x45,0xc6,0x86,0x4d}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmPublishOptions =
    {0xf57f96e7,0x0f16,0x4dc9,{0x8f,0x09,0x52,0xf7,0xbb,0x38,0x9a,0xb6}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmFileWatchReactor =
    {0xe6f88130,0xcd68,0x49ca,{0xb7,0x22,0x25,0x1d,0x58,0x3f,0xa6,0x7e}};
extern "C" const GUID __declspec(selectany) IID_IAdComFileWatchReactor =
    {0xf340a8b3,0x2c69,0x4ef9,{0xb6,0xcd,0x6a,0x08,0xe0,0x19,0x90,0x4d}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmProjectPointLocation =
    {0x33fd42d8,0x0154,0x4804,{0xac,0xa8,0x3c,0xa1,0x23,0xc2,0x26,0x2e}};
extern "C" const GUID __declspec(selectany) CLSID_AcSmProjectPointLocations =
    {0xe40ea246,0xbab4,0x4907,{0x81,0xa5,0x51,0x1e,0xa3,0x0c,0x16,0xfd}};
extern "C" const GUID __declspec(selectany) IID_IAcSmFiler =
    {0x8e974876,0xff7f,0x48d3,{0x84,0x35,0xa6,0x32,0x8c,0xcc,0x49,0x6f}};
extern "C" const GUID __declspec(selectany) IID_IAcSmPersist =
    {0xab9e4650,0xc3a8,0x4747,{0x8d,0x89,0x80,0x73,0x1a,0x46,0x44,0xa1}};
extern "C" const GUID __declspec(selectany) IID_IAcSmCustomPropertyValue =
    {0xda800d3b,0x975c,0x4381,{0x95,0x31,0x35,0x83,0x28,0x79,0x26,0x50}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumProperty =
    {0x476cbb88,0x8878,0x419d,{0xa8,0xc5,0xa9,0xce,0xd8,0x9d,0x5a,0x37}};
extern "C" const GUID __declspec(selectany) IID_IAcSmCustomPropertyBag =
    {0xfa893fe9,0x247c,0x44ec,{0xb4,0x37,0x54,0x1c,0x0f,0x09,0xf5,0xfc}};
extern "C" const GUID __declspec(selectany) IID_IAcSmComponent =
    {0x0e463002,0x12a4,0x4828,{0xb4,0xcf,0x28,0xd8,0xcb,0xf8,0xc7,0x68}};
extern "C" const GUID __declspec(selectany) IID_IAcSmFileReference =
    {0xb86d90c3,0x7d13,0x4180,{0x8f,0x97,0x61,0xc0,0x9f,0xa1,0x59,0x02}};
extern "C" const GUID __declspec(selectany) IID_IAcSmAcDbObjectReference =
    {0x25b22534,0xb1f7,0x402c,{0x82,0xd6,0xd3,0x6f,0xac,0x62,0x0d,0x69}};
extern "C" const GUID __declspec(selectany) IID_IAcSmNamedAcDbObjectReference =
    {0xc5e0c361,0x9e43,0x4574,{0xa0,0xab,0xde,0xfa,0x48,0x35,0x11,0xe4}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumComponent =
    {0x330cd4d2,0x73fe,0x43dc,{0x85,0xcc,0x48,0x26,0x38,0x63,0xcf,0xba}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumNamedAcDbObjectReference =
    {0xb2305c6b,0x130a,0x4eb0,{0xb8,0x9b,0xb5,0xfb,0xa9,0xf4,0x4f,0x84}};
extern "C" const GUID __declspec(selectany) IID_IAcSmCalloutBlocks =
    {0xcfbf491d,0x19c4,0x4893,{0x9c,0x4b,0xbc,0x3d,0xfb,0x6d,0x5e,0x64}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetSelSet =
    {0x1bea479e,0xec3a,0x49b8,{0x94,0xe5,0xcf,0xce,0xe9,0x2c,0x4a,0xfe}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumSheetSelSet =
    {0xe8c8d548,0x3b80,0x4810,{0xb8,0x66,0x61,0x7a,0x7b,0x91,0x6f,0xe8}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetSelSets =
    {0x20786806,0xb251,0x4277,{0xb1,0x19,0x94,0x20,0x9c,0x2e,0xa7,0xf9}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumFileReference =
    {0x73fcecfa,0x6343,0x4630,{0x88,0x9b,0xd0,0x3c,0xbf,0xbc,0x24,0x31}};
extern "C" const GUID __declspec(selectany) IID_IAcSmResources =
    {0xb448171b,0xd56c,0x4834,{0xbf,0x45,0x3d,0x2e,0xd0,0xa6,0x62,0x29}};
extern "C" const GUID __declspec(selectany) IID_IAcSmPublishOptions =
    {0x147981d1,0xaf77,0x42a1,{0x8b,0x91,0x49,0x94,0xa1,0x6a,0x59,0xfd}};
extern "C" const GUID __declspec(selectany) IID_IAcSmProjectPointLocation =
    {0x0b79150e,0xc037,0x48ad,{0xa9,0x3f,0x2f,0xf6,0xd3,0x10,0x4d,0x11}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumProjectPointLocation =
    {0xaf02d3b1,0xa2e4,0x44c7,{0x85,0xae,0x01,0x03,0x83,0x65,0xde,0xc2}};
extern "C" const GUID __declspec(selectany) IID_IAcSmProjectPointLocations =
    {0x2760e2a6,0xc735,0x4a97,{0x82,0x60,0xf1,0xaf,0x21,0x2c,0x8a,0x4d}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEvents =
    {0x56832073,0xa227,0x43f5,{0xb5,0xe9,0xbb,0x4f,0x0e,0x4c,0x7a,0xd4}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumPersist =
    {0x746e7d4f,0x0024,0x44ae,{0x87,0x53,0xf1,0xcc,0xae,0x44,0x07,0x2c}};
extern "C" const GUID __declspec(selectany) IID_IAcSmPersistProxy =
    {0xd5bb3e7e,0x2af7,0x4d10,{0x94,0xb3,0x21,0x3f,0xfd,0xaf,0x16,0xc8}};
extern "C" const GUID __declspec(selectany) IID_IAcSmObjectReference =
    {0xadf37497,0xa661,0x4306,{0xb0,0x48,0xa7,0x03,0xe8,0x42,0xd2,0xfa}};
extern "C" const GUID __declspec(selectany) IID_IAcSmDatabase =
    {0x5585723a,0x4859,0x4dd9,{0x99,0x13,0x99,0x64,0x84,0xd6,0x06,0x0d}};
extern "C" const GUID __declspec(selectany) IID_IAcSmObjectId =
    {0x42634426,0xcdfb,0x4e32,{0xad,0x46,0x99,0x2c,0xeb,0x3b,0x15,0x96}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumDatabase =
    {0x02aacc99,0x5c5a,0x4528,{0xa0,0x0a,0x73,0xf7,0x1c,0x51,0x43,0x9b}};
extern "C" const GUID __declspec(selectany) IID_IAcSmFileWatchReactor =
    {0xfaf2007f,0xffcb,0x4fb3,{0xb5,0x2e,0x5a,0xe9,0x8c,0x96,0x4d,0x60}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSubset =
    {0x8cceb838,0xacf5,0x4048,{0xb9,0xf0,0x09,0xa8,0x43,0xca,0x2a,0xc4}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetSet =
    {0x537476a6,0xe9e9,0x4e25,{0xb6,0xea,0xfb,0x5b,0x8b,0x08,0x61,0x53}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheet =
    {0x59bc91bb,0xfad8,0x44f9,{0x86,0xf9,0x5c,0x99,0xfa,0x6b,0x4e,0xdd}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetSetMgr =
    {0x4cc6fc8f,0xf1c6,0x486d,{0xb5,0x50,0x83,0x8b,0x02,0x34,0xe0,0x3c}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetViews =
    {0x5d2d1da2,0x97ca,0x48d9,{0x93,0xfd,0xbb,0xc5,0xb5,0x85,0x29,0x62}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumSheetView =
    {0x07bb6db5,0x2198,0x4ea2,{0x87,0x52,0xe5,0xa5,0x20,0xd0,0x1a,0x47}};
extern "C" const GUID __declspec(selectany) IID_IAcSmViewCategory =
    {0xa5b52086,0xa849,0x4a06,{0x9b,0x77,0x41,0xd8,0x60,0xe5,0xa1,0x1b}};
extern "C" const GUID __declspec(selectany) IID_IAcSmSheetView =
    {0xf69ceaf1,0x819f,0x4b7a,{0xb5,0xe6,0xd3,0x93,0x95,0x41,0x5f,0x55}};
extern "C" const GUID __declspec(selectany) IID_IAcSmEnumViewCategory =
    {0x460b347f,0xc804,0x42f0,{0x91,0xd5,0x7d,0xdd,0x92,0x5e,0x50,0x58}};
extern "C" const GUID __declspec(selectany) IID_IAcSmViewCategories =
    {0xb28b23eb,0xff5e,0x4910,{0x8c,0xa6,0xad,0x54,0x93,0x10,0x13,0xf3}};

#pragma pack(pop)
