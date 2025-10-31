//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1982-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//

// Name:            AcTc.h
//
// Description:     Header for all the published API classes
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTC_H__
#define __ACTC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AcTcTool;
class AcTcStockTool;
class AcTcCatalog;
class AcTcCatalogItem;
class AcTcSystemInternals;
class AcTcImpCatalogItem;

// Context flags
#define ACTC_IMAGE_NORMAL                   (0x1 << 0)
#define ACTC_IMAGE_SELECTED                 (0x1 << 1)
#define ACTC_IMAGE_HALO                     (0x1 << 2)
#define ACTC_IMAGE_SHADOW                   (0x1 << 3)

// Buffer sizes
#define ACTC_MAX_CATALOG_ITEM_NAME          256
#define ACTC_MAX_CATALOG_ITEM_DESCRIPTION   2048
#define ACTC_MAX_CATALOG_ITEM_KEYWORDS      1024
#define ACTC_MAX_CATALOG_ITEM_TOOLTIP_TEXT  1024
#define ACTC_MAX_CATALOG_ITEM_LINK_NAME     256
#define ACTC_MAX_TOOL_NAME                  ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_STOCKTOOL_NAME             ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_PALETTE_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_PACKAGE_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_CATEGORY_NAME              ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_CATALOG_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_URL                        1024
#define ACTC_MAX_PATH                       MAX_PATH
#define ACTC_MAX_COMMAND_NAME               256
#define ACTC_MAX_COMMAND_ARGS               1024
#define ACTC_MAX_HELPINFO_FILE              ACTC_MAX_URL
#define ACTC_MAX_HELPINFO_COMMAND           256
#define ACTC_MAX_HELPINFO_DATA              ACTC_MAX_URL
#define ACTC_MAX_PARENT_DOCUMENT_NAME       256
#define ACTC_MAX_PUBLISHER_NAME             256


// Commands to execute after downloading stock tool binary files
#define ACTC_POSTDOWNLOADCMD_EXECUTE        "Execute"


namespace AcTc
{
    enum AccessRight
    {
        kAccessRead             = (0x1 << 0),
        kAccessReadWrite        = (0x1 << 1),
        kAccessReadOnlyFile     = (0x1 << 2),
    };

    enum CatalogItemType
    {
        kItemUnknown            = 0,
        kItemTool               = (0x1 << 0),
        kItemPackage            = (0x1 << 1),
        kItemPalette            = (0x1 << 2),
        kItemCategory           = (0x1 << 3),
        kItemCatalog            = (0x1 << 4),
        kItemStockTool          = (0x1 << 5),
    };

    enum ReferencePath
    {
        kLoadRefPath            = 1,
        kSaveRefPath            = 2,
    };

    enum ImageType
    { 
        kImageTypeUninitialized = -1,
        kImageTypeBitmap        = 1,
        kImageTypeMetaFile      = 2,
        kImageTypeIcon          = 3,
        kImageTypeEnhMetaFile   = 4,
        kImageTypeJpeg          = 5,
        kImageTypePng           = 6,
        kImageTypeGif           = 7,
        kImageTypeTif           = 8
    };

    enum LoadOption
    { 
        kLoadLinks              = (0x1 << 0),
        kLoadImages             = (0x1 << 1),
    };

    enum SaveOption
    {
        kSaveLinksAsLinks       = (0x1 << 0),
        kSaveLinksAsEmbedded    = (0x1 << 1),
        kSaveImages             = (0x1 << 2),
        kSaveAs                 = (0x1 << 3),       // For internal use
    };

    enum DownloadOption
    { 
        kDownloadItem           = (0x1 << 0),
        kDownloadLinkedItem     = (0x1 << 1),
        kDownloadImage          = (0x1 << 2),
        kDownloadStockTool      = (0x1 << 3),
        kDownloadChildren       = (0x1 << 4),
        kDownloadAll            = kDownloadItem | kDownloadLinkedItem |
                                  kDownloadImage | kDownloadStockTool |
                                  kDownloadChildren,
        kDownloadCleanDownloadDir = (0x1 << 5),
        kDownloadShowProgress   = (0x1 << 6),
        kDownloadUseNewIds      = (0x1 << 7),       // For internal use
        kDownloadNotifyTool     = (0x1 << 12)       // For internal use. Note: kDownloadNotifyTool 
                                                    // and kRefreshNotifyTool must have different values.
    };

    enum RefreshOption
    { 
        kRefreshItem            = kDownloadItem,
        kRefreshLinkedItem      = kDownloadLinkedItem,
        kRefreshImage           = kDownloadImage,
        kRefreshStockTool       = kDownloadStockTool,
        kRefreshChildren        = kDownloadChildren,
        kRefreshAll             = kDownloadAll,
        kRefreshShowProgress    = kDownloadShowProgress,
        kRefreshNotifyTool      = (0x1 << 16)       // For internal use. Note: kDownloadNotifyTool 
                                                    // and kRefreshNotifyTool must have different values.
    };

    enum CatalogType
    {
        kCatalog                = (0x1 << 0),
        kStockToolCatalog       = (0x1 << 1),
    };
};


using namespace AcTc;

struct ACTC_IMAGE_INFO
{
    SIZE                mSize;
    TCHAR               mszResourceName[MAX_PATH];
    TCHAR               mszSourceFile[MAX_PATH];
};

//
// Classes
//

class __declspec(dllexport) AcTcImage
{
public:
    AcTcImage();
    AcTcImage(const AcTcImage& srcImage);
    virtual ~AcTcImage();

    AcTcImage&          operator=           (const AcTcImage& acTcImage);
    BOOL                Load                (LPCTSTR pszFile);
    BOOL                Save                (LPCTSTR pszFile);
    BOOL                Load                (IStream* pStream);
    BOOL                Save                (IStream* pStream);
    BOOL                Load                (HBITMAP hBitmap);
    BOOL                Render              (HDC hDC, 
                                             int xPos, 
                                             int yPos, 
                                             int nWidth, 
                                             int nHeight,
                                             UINT nStyle = ACTC_IMAGE_NORMAL,
                                             BOOL bTransparentBitmap = TRUE);
    BOOL                GetSize             (LPSIZE pSize) const;
    ImageType           GetType             (void) const;
    BOOL                IsImageLoaded       (void) const;

protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class __declspec(dllexport) AcTcImageList
{
    friend AcTcImpCatalogItem;
public:
    virtual ~AcTcImageList();

    AcTcImageList&      operator=           (const AcTcImageList& acTcImageList);
    int                 GetImageCount       (void) const;
    BOOL                GetImageInfo        (int iIndex, 
                                             ACTC_IMAGE_INFO* pImageInfo) const;
    BOOL                SetImageInfo        (int iIndex, 
                                             const ACTC_IMAGE_INFO* pImageInfo);
    AcTcImage*          GetImage            (int iIndex);
    int                 SetImage            (int iIndex, 
                                             const AcTcImage* pImage);
    int                 Add                 (const AcTcImage* pImage);
	int                 Add                 (const ACTC_IMAGE_INFO* pImageInfo);
	int                 UpdateImage         (const AcTcImage* pImage);
    BOOL                Delete              (int iIndex);
    BOOL                DeleteAllImages     (void);
    BOOL                LoadImage           (int iIndex);
    int                 GetImageIndex       (const SIZE* pSize, 
                                             BOOL bExactMatch = FALSE);

protected:
    AcTcImageList(AcTcCatalogItem* pCatalogItem);
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;

};


class __declspec(dllexport) AcTcManager
{
public:
    AcTcManager();
    virtual ~AcTcManager();

    int                 GetStockToolCatalogCount(void) const;
    AcTcCatalogItem *   GetStockToolCatalog (int nIndex) const;
    AcTcStockTool   *   FindStockTool       (const GUID& id) const;

    int                 GetCatalogCount     (void) const;
    AcTcCatalogItem *   GetCatalog          (int nIndex) const;
    AcTcCatalogItem *   FindItem            (const GUID& id) const;
    
    int                 GetStockToolCatalogPath(LPTSTR pszString,
                                                int cbSize) const;
    BOOL                SetStockToolCatalogPath(LPCTSTR pszPath);
    int                 GetCatalogPath      (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetCatalogPath      (LPCTSTR pszPath);
    int                 AddStockToolCatalog (AcTcCatalogItem* pCatalogItem);
    int                 AddCatalog          (AcTcCatalogItem* pCatalogItem);
    BOOL                LoadCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
                                             DWORD dwLoadOption = kLoadLinks);
    BOOL                UnloadCatalogs      (DWORD dwCatalogType= kCatalog | kStockToolCatalog);
    BOOL                SaveCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class __declspec(dllexport) AcTcCatalogItem 
{
    // For protected funcion access from imp class
    friend AcTcImpCatalogItem;

public:
    static AcTcCatalogItem * FromFile       (LPCTSTR pszFile, 
                                             BOOL bLoad         = FALSE, 
                                             DWORD dwLoadOption = kLoadLinks);
    static CatalogItemType   GetType        (LPCTSTR pszFile);

public:
    virtual ~AcTcCatalogItem();

    BOOL                Load                (LPCTSTR pszUrl, 
                                             DWORD dwLoadOption = kLoadLinks);
    BOOL                LoadLink            (void);
    BOOL                Save                (LPCTSTR pszUrl,
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    int                 AddChild            (AcTcCatalogItem* pNewItem);
    BOOL                InsertChild         (int iIndex, 
                                             AcTcCatalogItem* pNewItem);
    BOOL                DeleteChild         (AcTcCatalogItem* pItem);
    BOOL                DetachChild         (AcTcCatalogItem* pItem);
    int                 GetChildCount       (void) const;
    int                 GetChildCount       (CatalogItemType nType) const;
    AcTcCatalogItem *   GetChild            (int iIndex) const;
    AcTcCatalogItem *   GetNextChild        (int iIndex, 
                                             CatalogItemType nType) const;
    BOOL                DeleteAllChildren   (void);
    BOOL                HasChildren         (void) const;

    BOOL                GetID               (GUID* pId) const;
    BOOL                SetID               (const GUID* pId);
    AcTc::AccessRight   GetAccessRight      (void) const;
    BOOL                SetAccessRight      (AcTc::AccessRight nAccessRight);
    BOOL                IsReadOnly          (void) const;
    int                 GetName             (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetName             (LPCTSTR pszString);
    int                 GetDescription      (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetDescription      (LPCTSTR pszString);
    int                 GetToolTipText      (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetToolTipText      (LPCTSTR pszString);
    int                 GetImageFilePath    (int iIndex,
                                             LPTSTR pszString,
                                             int cbSize) const;    
    BOOL                GetHelpInfo         (LPTSTR pszFile, 
                                             LPTSTR pszCommand, 
                                             LPTSTR pszData) const;
    BOOL                SetHelpInfo         (LPCTSTR pszFile, 
                                             LPCTSTR pszCommand, 
                                             LPCTSTR pszData);
    int                 GetKeywords         (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetKeywords         (LPCTSTR pszString);
    int                 GetLinkUrl          (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetLinkUrl          (LPCTSTR pszString);
    int                 GetSourceUrl        (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetSourceUrl        (LPCTSTR pszString);
    int                 GetParentDocumentName(LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetParentDocumentName(LPCTSTR pszString);
    int                 GetParentDocumentDescription(LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetParentDocumentDescription(LPCTSTR pszString);
    int                 GetParentDocumentUrl(LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetParentDocumentUrl(LPCTSTR pszString);
    int                 GetPublisherName    (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetPublisherName    (LPCTSTR pszString);
    int                 GetPublisherDescription(LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetPublisherDescription(LPCTSTR pszString);
    int                 GetPublisherCountry (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetPublisherCountry (LPCTSTR pszString);
    int                 GetPublisherEmail   (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetPublisherEmail   (LPCTSTR pszString);
    int                 GetPublisherUrl     (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetPublisherUrl     (LPCTSTR pszString);
    int                 GetUrl              (LPTSTR pszString, 
                                             int cbSize) const;
    int                 GetLocalFile        (LPTSTR pszString, 
                                             int cbSize) const;
    AcTcCatalogItem *   GetRoot             (void) const;
    AcTcCatalogItem *   GetParent           (void) const;
    BOOL                SetParent           (AcTcCatalogItem* pParent);
    BOOL                IsRoot              (void) const;
    BOOL                IsLink              (void) const;
    BOOL                IsLinkLoaded        (void) const;
    AcTcImageList   *   GetImageList        (void) const;
    AcTcImage       *   GetImage            (const SIZE* pSize);
    int                 GetXml              (LPTSTR pszString, 
                                             int cbSize, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual AcTcCatalogItem *   FindInChildren(const GUID& id, 
                                             BOOL bRecursive = TRUE);
    BOOL                GetTime             (time_t* pCreated, 
                                             time_t* pLastModified, 
                                             time_t* pLastRefreshed) const;
    BOOL                SetTime             (const time_t* pCreated, 
                                             const time_t* pLastModified, 
                                             const time_t* pLastRefreshed);
    BOOL                CanRefresh          (void) const;
    BOOL                SetRefresh          (BOOL bRefresh);
    BOOL                GetRefresh          (void) const;
    virtual BOOL        Refresh             (DWORD dwRefreshFlag    = kRefreshAll);
    virtual BOOL        Download            (LPCTSTR pszUrl, 
                                             DWORD dwDownloadFlag  = kDownloadAll, 
                                             LPCTSTR pszDownloadPath        = NULL);
    BOOL                SetAutoRefresh       (BOOL bAutoRefresh);
    BOOL                GetAutoRefresh      (void) const;
    int                 GetReferencePath    (LPTSTR pszString, 
                                             int cbSize, 
                                             int nFlag) const;
    BOOL                SetReferencePath    (LPCTSTR pszString, 
                                             int nFlag);
    BOOL                GetCustomData       (IUnknown** ppCustomData);
    BOOL                SetNewID            (BOOL bRecursive = FALSE);
    BOOL                DeleteImageFile     (BOOL bRecursive = FALSE);
    int                 GetLinkFilePath     (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                DeleteLinkFile      (BOOL bRecursive = FALSE);
    BOOL                GetSourceID         (GUID* pId) const;
    BOOL                SetSourceID         (const GUID* pId);

public:
    // Overridables
    virtual AcTcCatalogItem&    operator=   (const AcTcCatalogItem& srcItem);
    virtual BOOL        Reset               (void);

    virtual CatalogItemType GetType         (void) const;
    virtual int         GetTypeString       (LPTSTR pszString, 
                                             int cbSize,
                                             BOOL bLocalized    = FALSE, 
                                             BOOL bPluralForm   = FALSE) const;
    virtual int         GetTagName          (LPTSTR pszString, 
                                             int cbSize) const;

    virtual BOOL        Load                (IUnknown* pUnknown, 
                                             DWORD dwLoadOption = kLoadLinks);
    virtual BOOL        Load                (IStream* pStream, 
                                             DWORD dwLoadOption = kLoadLinks);
    virtual BOOL        Save                (IUnknown* pUnknown, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual BOOL        Save                (IStream* pStream, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual BOOL        Clone               (BOOL bDeep, 
                                             AcTcCatalogItem*& pClone,
                                             BOOL bCopyId = FALSE) const;
    virtual BOOL        CopyFrom            (const AcTcCatalogItem* pSrcItem, 
                                             BOOL bCopyId = FALSE);
    virtual BOOL        IsValidChild        (const CatalogItemType nType) const;

protected:
    // Overridables
    virtual AcTcCatalogItem * CreateObject  (void) const;

protected:
    // Protected constructor
    AcTcCatalogItem(AcTcSystemInternals*);
    
protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class __declspec(dllexport) AcTcCategory : public AcTcCatalogItem
{
public:
    AcTcCategory();
    AcTcCategory(const AcTcCategory& srcItem);
    virtual ~AcTcCategory();

protected:
    // Protected constructor
    AcTcCategory(AcTcSystemInternals*);
};


class __declspec(dllexport) AcTcCatalog : public AcTcCategory
{
public:
    AcTcCatalog();
    AcTcCatalog(const AcTcCatalog& srcItem);
    virtual ~AcTcCatalog();

protected:
    // Protected constructor
    AcTcCatalog(AcTcSystemInternals*);
};


class __declspec(dllexport) AcTcStockTool : public AcTcCatalogItem
{
public:
    AcTcStockTool();
    AcTcStockTool(const AcTcStockTool& srcItem);
    virtual ~AcTcStockTool();

    AcTcTool        *   CreateTool          (BOOL bSetDefaults = TRUE);

    BOOL                CreateAcadStockTool (IUnknown** ppStockTool);
    BOOL                CreateAcadTool      (IUnknown** ppUnknown);

    BOOL                GetComClassID       (CLSID& clsid) const;
    BOOL                SetComClassID       (const  CLSID& clsid);
    int                 GetModuleFileName   (LPTSTR pszString, 
                                            int cbSize) const;
    BOOL                SetModuleFileName   (LPCTSTR pszString);
    int                 GetModuleInstallUrl (LPTSTR pszString,
                                             int cbSize) const;
    BOOL                SetModuleInstallUrl (LPCTSTR pszString);
    int                 GetModuleInstallArguments(LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetModuleInstallArguments(LPCTSTR pszString);

protected:
    // Protected constructor
    AcTcStockTool(AcTcSystemInternals*);

private:
    friend class AcTcSystemInternals;
};


class  __declspec(dllexport) AcTcTool : public AcTcCatalogItem  
{
public:
    AcTcTool();
    AcTcTool(const AcTcTool& srcItem);
    virtual ~AcTcTool();

    virtual BOOL        Execute             (int nFlag, 
                                             HWND hWnd, 
                                             POINT point, 
                                             DWORD dwKeyState);
    BOOL                GetToolData         (IUnknown** ppUnknown);
    AcTcStockTool *     GetStockTool        (void) const;
    BOOL                CreateAcadTool      (IUnknown** ppTool, 
                                             BOOL bLoadData = TRUE);
    BOOL                GetStockToolID      (GUID* pId) const;
    BOOL                SetStockToolID      (const GUID* pId);
    int                 GetStockToolFileUrl (LPTSTR pszString, 
                                             int cbSize) const;
    BOOL                SetStockToolFileUrl (LPCTSTR pszString);

protected:
    // Protected constructor
    AcTcTool(AcTcSystemInternals*);
};


class __declspec(dllexport) AcTcPackage : public AcTcCatalogItem  
{
public:
    AcTcPackage();
    AcTcPackage(const AcTcPackage& srcItem);
    virtual ~AcTcPackage();

protected:
    // Protected constructor
    AcTcPackage(AcTcSystemInternals*);
};


class __declspec(dllexport) AcTcPalette : public AcTcPackage
{
public:
    AcTcPalette();
    AcTcPalette(const AcTcPalette& srcItem);
    virtual ~AcTcPalette();

protected:
    // Protected constructor
    AcTcPalette(AcTcSystemInternals*);
};

//
// Global exported functions
//
__declspec(dllexport) BOOL AcTcInitialize   (void);
__declspec(dllexport) BOOL AcTcUninitialize (void);
__declspec(dllexport) AcTcManager* AcTcGetManager(void);
__declspec(dllexport) BOOL AcTcDownloadItem (LPCTSTR pszUrl, 
                                             AcTcCatalogItem*& pNewItem, 
                                             DWORD dwItemTypes      = -1,
                                             DWORD dwDownloadFlag   = kDownloadAll,
                                             LPCTSTR pszDownloadPath= NULL);
__declspec(dllexport) int AcTcDownloadItem  (LPTSTR* pUrls, 
                                             int nNumUrls, 
                                             AcTcCatalogItem** pItems, 
                                             DWORD dwItemTypes      = -1,
                                             DWORD dwDownloadFlag   = kDownloadAll, 
                                             LPCTSTR pszDownloadPath= NULL);
__declspec(dllexport) BOOL AcTcRefreshItem  (AcTcCatalogItem** pItems,
                                             int nNumItems,
                                             DWORD dwItemTypes      = -1,
                                             DWORD dwRefreshFlag    = kRefreshAll);


#endif //__ACTC_H__
