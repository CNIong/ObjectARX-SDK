//
// (C) Copyright 1997-2008 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  
//
//  AcDbHostApplicationServices provides a mechanism for a client of 
//  AcDb.dll to provide runtime information to the database engine.
//  For example when the database (or a dll client) needs to find
//  a specific file, the services can dictate the search that will
//  be followed.
// 
//  A client application (.exe) (there can be only one 'application' 
//  client) in a given session may chose to override the default services
//  with their own custom version implementation.
//

#ifndef AcDbHostApplicationServices_INC
#define AcDbHostApplicationServices_INC

#include "adesk.h"
#include "acdb.h"
#include "acarray.h"
#include "codepgid.h"
#include "acdlflagbits.h"

// Internet-related status codes
#include "inetstrc.h"
#include "rxdlinkr.h"

#pragma pack (push, 8)

class AcDbAuditInfo;
class AcDbDatabase;
class AcDbUndoController;
class AcDbTransactionManager;
class AcDbGlobals;
class AcDbAppSystemVariables;
class COleClientItem;
class CArchive;
class AcadInternalServices;
struct flagmat;

class AcDbAbstractClipBoundaryDefinition;
class ClipBoundaryArray;

class AcDbPlotSettingsValidator;
class AcDbLayoutManager;
class AcPwdCache;

struct _EXCEPTION_POINTERS;

#ifndef ACUTIL_API
#    ifdef ACUTIL_INTERNAL
#        define ACUTIL_API __declspec(dllexport)
#    else
#        define ACUTIL_API __declspec(dllimport)
#    endif
#endif

typedef unsigned long LCID;

enum  AcSDIValues {
    kMDIEnabled = 0,
    kSDIUserEnforced,
    kSDIAppEnforced,
    kSDIUserAndAppEnforced
};

enum ProdIdCode {
    kProd_ACAD = 1,
    kProd_LT,
    kProd_OEM,
    kProd_AcDb
};

int acdbHostAppMinorVersion();

class AcDbHostApplicationProgressMeter {
public:
    AcDbHostApplicationProgressMeter();
    virtual ~AcDbHostApplicationProgressMeter();

    virtual void start(const ACHAR * displayString = NULL);
    virtual void stop();
    
    virtual void meterProgress();

    virtual void setLimit(int max);

};

typedef Acad::ErrorStatus (*SELECTFILEPROC )(/*[out]*/ short *userCancel, 
                                             /*[out]*/ ACHAR *& chosenPath,
                                             void* h, // HWND
                                             const int nFlags,
                                             const ACHAR * prompt,
                                             const ACHAR * dir,
                                             const ACHAR * name,
                                             const ACHAR * type,
                                             int* pnChoice,
                                             bool* pbReadOnly,
                                             const ACHAR * pszWSTags,
                                             void* pReserved);

typedef Acad::ErrorStatus (* REMAPPROC) (/*[out]*/ ACHAR *& newName,
                                         const ACHAR * filename,
                                         int context,
                                         void* pReserved);

typedef void (* MAPFILENOTIFYPROC) (const ACHAR * filename,
                                    const ACHAR * newName,
                                    int context,
                                    void* pReserved);


class ADESK_NO_VTABLE AcDbHostApplicationServices : public AcRxObject
{
    friend AcadInternalServices;
public:    
    ACRX_DECLARE_MEMBERS(AcDbHostApplicationServices);
    AcDbHostApplicationServices( int createGlobals = 1 );
    virtual ~AcDbHostApplicationServices();

    enum FindFileHint
    {
        kDefault = 0,
        kFontFile,              // Could be either
        kCompiledShapeFile,     // shx
        kTrueTypeFontFile,      // ttf
        kEmbeddedImageFile,
        kXRefDrawing,
        kPatternFile,
        kARXApplication,
        kFontMapFile,
        kUnderlayFile
    };
    
    enum RemapFileContext
    {
        kDrawingOpen,
        kXrefResolution,
        kRasterResolution,
        kAfterXrefResolution
    };

    // When a file path is required
    //
    virtual Acad::ErrorStatus findFile(ACHAR * pcFullPathOut,
                 int   nBufferLength,
                 const ACHAR * pcFilename,
                 AcDbDatabase * pDb = NULL, // When this search 
                                            // is related to a db
                 AcDbHostApplicationServices::FindFileHint hint = kDefault) = 0;

    // These two functions return the full path to the root folder where roamable/local 
    // customizable files were installed. The default implementation is to return the
    // directory where the EXE is located.  These methods can be overridden by DBX
    // applications for their own install structure.  Note that the user may have 
    // reconfigured the location of some of the customizable files using the Options 
    // Dialog, therefore these functions should not be used to locate all customizable 
    // files. To locate customizable files either use the findFile function or the 
    // appropriate system variable for the given file type. 
    //
    virtual Acad::ErrorStatus getRoamableRootFolder(const ACHAR *& folder);
    virtual Acad::ErrorStatus getLocalRootFolder(const ACHAR *& folder);

    // Select File APIs
    virtual Acad::ErrorStatus   selectFile(short *userCancel, 
                                           ACHAR *& chosenPath,
                                           void* h, // HWND
                                           const int nFlags,
                                           const ACHAR * prompt,
                                           const ACHAR * dir,
                                           const ACHAR * name,
                                           const ACHAR * type,
                                           int* pnChoice,
                                           bool* pbReadOnly,
                                           const ACHAR * pszWSTags,
                                           void* pReserved) ;
    virtual Acad::ErrorStatus   registerSelectFileCallback(const ACHAR * appName,
                                                   SELECTFILEPROC proc, 
                                                   bool unRegister = false, 
                                                   bool asPrimary  = false);
    virtual const ACHAR *       primaryClientForSelectFileCallback();
    virtual Acad::ErrorStatus   getRegisteredSelectFileClients(
                                            AcArray<const ACHAR *>& clients);

    // File remapping
    virtual Acad::ErrorStatus   mapFile(/*out*/ ACHAR *& newName,
                                        const ACHAR * filename,
                                        int context,
                                        void* pReserved);
    virtual Acad::ErrorStatus   registerMapFileCallback(const ACHAR * appName,
                                                REMAPPROC  proc,
                                                bool unRegister = false, 
                                                bool asPrimary  = false);
    virtual const ACHAR *       primaryClientForMapFileCallback();
    virtual bool                setMapFlag(bool setIt);
    virtual Acad::ErrorStatus   getRegisteredFileMapClients(
                                            AcArray<const ACHAR *>& clients);
    virtual Acad::ErrorStatus   registerMapFileNotification(const ACHAR * appName, 
                                                MAPFILENOTIFYPROC,
                                                bool unRegister = false);

    // When a fatal error is encountered this function may be called
    // to notify you.
    //
    virtual void fatalError(const ACHAR *format, ...);

    // Called when an unhandled exception occurs in an arx command or message.
    // The EXCEPTION_POINTERS pointer is obtained from the win32 api:
    // GetExceptionInformation().
    //
    virtual void reportUnhandledArxException(const _EXCEPTION_POINTERS *pExcPtrs,
                                             const ACHAR *pAppName);

    // The equivalent of ads_usrbrk()
    //
    virtual Adesk::Boolean userBreak(bool updCtrlsWhenEnteringIdle = true) const;

    virtual void displayChar(ACHAR c) const;
    virtual void displayString(const ACHAR* string, int count) const;

    // This function will be called to check if the application
    // wants to show text messages. Default implementation is always 
    // returning true;
    virtual Adesk::Boolean readyToDisplayMessages();

    // This function can be used to used to programmatically change the
    // state of readyToDisplayMessages.  
    virtual void enableMessageDisplay(Adesk::Boolean);

    // Instructs the system to run fulltime CRC checking on database
    // filing operations.
    virtual Adesk::Boolean doFullCRCCheck();

    // Indicates where temporary files are to be located.  See WINSDK 
    // function GetTempPath() for details on the argument and the return
    // value.
    virtual unsigned int getTempPath(Adesk::UInt32 lBufferSize, 
                                                ACHAR* pcBuffer);

    // gets the value of a command switch, or an environment variable, or
    // registry entry (the search is in that order).  This is the same
    // behavior as the LISP (getenv) function).  Default implementation
    // is to return NULL.
    //
    virtual const ACHAR* getEnv(const ACHAR * var);

    // Whenever AcDb.dll needs to instantiate a progress meter, it will
    // call this method.
    // If you want to create your own progress meter, derive from
    // AcDbHostApplicationProgressMeter, and override this method to
    // to return a progress meter of your derived type.
    //
    virtual AcDbHostApplicationProgressMeter* newProgressMeter();

    // In other cases, AcDb.dll expects to make use of one global
    // instance of a progress meter that is always available.  To
    // set that progress meter to one of your own type, instantiate
    // your meter and pass it to the following function.
    void setWorkingProgressMeter(AcDbHostApplicationProgressMeter* pNewMeter);

    virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryRectangular();
    virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryPolygonal();
    virtual ClipBoundaryArray* newClipBoundaryArray();

    // Should point to a viable database.  The application is free to
    // reset this according to its need.  Some entites will require
    // access to information within a database in order to function
    // properly when they are not yet database-resident.
    //
    AcDbDatabase* workingDatabase() const;
    void setWorkingDatabase(AcDbDatabase* pDatabase);

    virtual AcDbUndoController* defaultUndoController();
    void setDefaultUndoController(AcDbUndoController* pUndoCtrl);

    virtual AcDbTransactionManager* workingTransactionManager();
    void setWorkingTransactionManager(AcDbTransactionManager* pTM);

    virtual AcDbGlobals * createWorkingGlobals();
    AcDbGlobals * workingGlobals() const;
    void setWorkingGlobals(AcDbGlobals* pGlobals);
    
    AcDbAppSystemVariables * workingAppSysvars() const;
    void setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars);

    virtual const ACHAR * program ();
    virtual const ACHAR * product ();
    virtual const ACHAR * companyName();
    virtual const ProdIdCode prodcode();
    virtual const ACHAR * releaseMajorMinorString();
    virtual int   releaseMajorVersion();
    virtual int   releaseMinorVersion();
    virtual const ACHAR * versionString();
    virtual const ACHAR * getRegistryProductRootKey ();
    virtual LCID  getRegistryProductLCID() ;
    virtual bool  supportsMultiRedo() const { return false; }
    enum ModelerFlavor {kModelerFull=0, kModelerRegionsOnly=1, kModelerObjectsOnly=2};
    virtual ModelerFlavor  getModelerFlavor() const { return AcDbHostApplicationServices::kModelerFull; }

    code_page_id getSystemCodePage() const;

    // Deprecated: do not use this function!
    void setSystemCodePage(code_page_id);

    virtual AcadInternalServices* acadInternalServices();

    void * acadInternalGetvar (const ACHAR *name);

    // BEGIN: Internet-related services

    // Determine whether a given string ('pszURL') is a valid URL.
    //
    virtual Adesk::Boolean isURL(const ACHAR * pszURL) const;

    // 'isRemoteFile()' is the inverse of 'isURL()'--it provides a mapping
    // from a local file to the corresponding URL that the file was down-
    // loaded from. The URL, if any, is returned via 'pszURL.'
    //
    virtual Adesk::Boolean isRemoteFile(const ACHAR * pszLocalFile,
                                          ACHAR * pszURL) const;

    // Download a resource (file) identified by the URL 'pszURL' to a local
    // file, and return its name in the buffer pointed to by 'pszLocalFile.' 
    // The boolean argument 'bIgnoreCache' determines whether the file should 
    // be downloaded even if it has already been transferred earlier in the 
    // session.
    //
    virtual Acad::ErrorStatus getRemoteFile(const ACHAR * pszURL,
     ACHAR * pszLocalFile, Adesk::Boolean bIgnoreCache = Adesk::kFalse) const;

    // Upload a local resource (file) identified by the pathname 'pszLocalFile'
    // to the remote location specified by the URL 'pszURL.'
    //
    virtual Acad::ErrorStatus putRemoteFile(const ACHAR * pszURL, 
        const ACHAR * pszLocalFile) const;

    // Launch the Web Browser dialog that allows the user to navigate to any 
    // site and select a URL. The selected URL is returned in 'pszSelectedURL,' 
    // which must point to a buffer large enough to hold the return value. 
    // 'pszDialogTitle' and 'pszOpenButtonCaption' allow developers to supply 
    // text for the dialog title and the button caption, that is more 
    // meaningful in the context in which the dialog is being invoked. The 
    // parameter 'pszStartURL' is a URL that the Web Browser uses as its start 
    // page. The fifth argument is optional, and identifies the product root 
    // key under which the Web Browser dialog's size and position information 
    // is stored for persistence across sessions.
    // The last parameter determines whether the user can select HTML links
    // in addition to files that are "downloadable."
    //
    virtual Adesk::Boolean launchBrowserDialog(
                 ACHAR *          pszSelectedURL,
                 const ACHAR *    pszDialogTitle,
                 const ACHAR *    pszOpenButtonCaption,
                 const ACHAR *    pszStartURL, 
                 const ACHAR *    pszRegistryRootKey = 0,
                 Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const;

    // OLE Embedded Objects 
    // Draw OLE object using given HDC, objectID and rectangle in screen 
    // coordinate.
    //
    virtual void drawOleOwnerDrawItem(COleClientItem* pItem,
                                      Adesk::LongPtr hdc, 
        long left, long top, long right, long bottom);

    // Get COleClientItem from Host application.
    virtual Acad::ErrorStatus getNewOleClientItem(COleClientItem*& pItem);

    // Called by AcDb when it needs to translate an OLE embedded object.
    virtual Acad::ErrorStatus serializeOleItem(COleClientItem* pItem,
        CArchive*);

    // This method is renamed from entToWorldTransform() because it is for
    // Internal Use only and will be removed in future.
    // 
    virtual Adesk::Boolean _entToWorldTransform(double normal[3], 
                                                flagmat *tran);

    virtual void terminateScript(); // end any running scripts

    // get substitute font for unfound font
    virtual Adesk::Boolean getSubstituteFont(ACHAR **pFileName,
                                             ACHAR *prompt, 
                                             int type, int fontAlt); 
    virtual void alert(const ACHAR * string) const;

    virtual void auditPrintReport(AcDbAuditInfo * pAuditInfo,
                                             const ACHAR *    line,
                                             int             both) const;

    virtual ACHAR * getAlternateFontName() const { return ACRX_T(""); }

    virtual ACHAR * getFontMapFileName() const { return ACRX_T(""); }

    virtual bool cacheSymbolIndices() const { return false; }

    virtual AcDbPlotSettingsValidator* plotSettingsValidator() const; 
    virtual AcDbLayoutManager* layoutManager() const;
    virtual bool loadApp(const ACHAR * appName, 
                         AcadApp::LoadReasons why, 
                         bool printit, 
                         bool asCmd);
    virtual void getDefaultPlotCfgInfo(ACHAR * plotDeviceName,
                                       ACHAR * plotStyleName); 

    // BEGIN: DWG Security-related services
    virtual Acad::ErrorStatus signingComplete(Acad::ErrorStatus es,
                                              const ACHAR * msg,
                                              bool* result);

    enum PasswordOptions {kPasswordOptionDefault = 0, kPasswordOptionUpperCase =1, kPasswordOptionIsExternalReference = 2};
    virtual bool getPassword(const ACHAR * dwgName,
                             PasswordOptions options,
                             wchar_t *password, 
                             const size_t bufSize);

    virtual void usedPasswordFromCacheMsg(const ACHAR *dwgName);
    virtual void missingCryptoProviderMsg();

    virtual const ACHAR * getColorBookLocation() const { return NULL; }

    AcPwdCache * getPasswordCache() const;

    virtual short getKeyState(int nVirtKey) const { return 0; }

protected:
    
    // This method is used by the Internet-related methods of all classes that
    // derive from AcDbHostApplicationServices, to map a status code returned by
    // an Internet operation to an Acad::ErrorStatus value.
    //
    Acad::ErrorStatus mapInetStatusToAcadStatus(
        const AcadInet::Status status) const;

    // END: Internet-related services

protected:

    void * mp_sessionVars;

    void acadInternalSetvar (const ACHAR *name, void * var);

private:
    // NOTES:
    // As session-specific globals are gathered up during the AcDb.DLL and
    // MDI projects, if the DB requires them, they should be contained here,
    // and appropriate get/set methods created above.  References to those 
    // globals should be replaced by references to methods on this class or 
    // a derived class.  This header will ship with Tahoe Unplugged, but not 
    // Tahoe ARX.  These comments to be deleted before FCS.

    AcDbDatabase* mpWorkingDatabase;
    AcDbUndoController* mpDefaultUndoController;
    AcDbTransactionManager* mpWorkingTransactionManager;
    AcDbGlobals * mpWorkingGlobals;
    AcDbAppSystemVariables * mpWorkingAppSysvars;

    code_page_id m_eSystemCodePage;
                                // Formerly "system_code_page".
                                // Moved from module xstring.cpp.
    Adesk::Boolean mbDisplayMessages;

    AcPwdCache * mpPasswordCache;
};

// Use this method to replace the default services, you should do this 
// early on, in the InitInstance of your application for example.
//
Acad::ErrorStatus acdbSetHostApplicationServices(AcDbHostApplicationServices * pServices);

// Use this method to access the services
//
AcDbHostApplicationServices * acdbHostApplicationServices();

// A host application would use this function to send notification to
// clients, e.g. Object Enablers, when it's done reading the initial
// set of objects from a dwg file. This is different from what 
// readDwgFile() would read. readDwgFile() reads the basic set,
// but a host application would, depending on the functionality it's
// implementing, read some more objects, and let everyone know that
// it's done. 
//
Acad::ErrorStatus acdbSendInitialDwgFileOpenComplete(AcDbDatabase* pDb);

extern AcDbGlobals* getDefaultGlobals();

inline AcDbGlobals *
AcDbHostApplicationServices::workingGlobals() const
{
    return mpWorkingGlobals ? mpWorkingGlobals : getDefaultGlobals();
}

inline code_page_id
AcDbHostApplicationServices::getSystemCodePage() const
{
    return this->m_eSystemCodePage;
}

inline AcDbUndoController *
AcDbHostApplicationServices::defaultUndoController()
{
    return mpDefaultUndoController;
}

inline AcDbTransactionManager *
AcDbHostApplicationServices::workingTransactionManager()
{
    return mpWorkingTransactionManager;
}

inline AcDbDatabase *
AcDbHostApplicationServices::workingDatabase() const
{
    return mpWorkingDatabase;
}

inline AcDbAppSystemVariables * 
AcDbHostApplicationServices::workingAppSysvars() const
{
    return mpWorkingAppSysvars;
}

inline void 
AcDbHostApplicationServices::setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars)
{
    mpWorkingAppSysvars = pSysvars;
}

inline void 
AcDbHostApplicationServices::terminateScript()
{
    return;
}

inline void 
AcDbHostApplicationServices::reportUnhandledArxException(
                    const _EXCEPTION_POINTERS *pExcPtrs,
                    const ACHAR *pAppName)
{
    return;
}

inline Acad::ErrorStatus
AcDbHostApplicationServices::selectFile(/*[out]*/ short *userCancel,
                                        /*[out]*/ ACHAR *& chosenPath,
                                        void* h, // HWND
                                        const int nFlags,
                                        const ACHAR * prompt,
                                        const ACHAR * dir,
                                        const ACHAR * name,
                                        const ACHAR * type,
                                        int* pnChoice,
                                        bool* pbReadOnly,
                                        const ACHAR * pszWSTags,
                                        void* pReserved) 
{ 
    return Acad::eNotHandled;
}

inline Acad::ErrorStatus   
AcDbHostApplicationServices::registerSelectFileCallback(const ACHAR * appName,
                                                        SELECTFILEPROC proc, 
                                                        bool unRegister, 
                                                        bool asPrimary)
{
    return Acad::eNotImplemented;
}
inline const ACHAR *
AcDbHostApplicationServices::primaryClientForSelectFileCallback() 
{
    return NULL;
}

    // File remapping
inline Acad::ErrorStatus 
AcDbHostApplicationServices::mapFile(ACHAR *& newName,
                                     const ACHAR * filename,
                                     int context,
                                     void* pReserved) 
{
    return Acad::eNotHandled;
}
    
inline Acad::ErrorStatus
AcDbHostApplicationServices::registerMapFileCallback(const ACHAR *, REMAPPROC,
                                                     bool unRegister,
                                                     bool asPrimary)
{
    return Acad::eNotImplemented;
}
    
inline const ACHAR *
AcDbHostApplicationServices::primaryClientForMapFileCallback() 
{
    return NULL;
}

inline
Acad::ErrorStatus
AcDbHostApplicationServices::getRegisteredSelectFileClients(
                                            AcArray<const ACHAR *>& clients)
{
    return Acad::eNotImplemented;
}

inline
Acad::ErrorStatus
AcDbHostApplicationServices::getRegisteredFileMapClients(
                                            AcArray<const ACHAR *>& clients)
{
    return Acad::eNotImplemented;
}

inline Acad::ErrorStatus
AcDbHostApplicationServices::registerMapFileNotification(const ACHAR * appName, 
                                                         MAPFILENOTIFYPROC,
                                                         bool unRegister)
{
    return Acad::eNotImplemented;
}

inline bool
AcDbHostApplicationServices::setMapFlag(bool setIt)
{
    return false;
}

inline AcPwdCache * 
AcDbHostApplicationServices::getPasswordCache() const
{
    return mpPasswordCache;
}

// acdbTriggerAcadOctTreeReclassification
//
// *** For Internal Use Only ***
// 
void acdbTriggerAcadOctTreeReclassification();

// acdbSetBreak3dQueueForRegen
//
// *** For Internal Use Only ***
// 
Acad::ErrorStatus acdbSetBreak3dQueueForRegen(bool);


//Derived classes are expected to override tryPassword and cache a
//file moniker (file name, file handle etc.) during construction so
//they can try the passwords passed to tryPassword. 
// Here are the possible conditions for wszPassword:
// NULL     = check the password cache first then prompt for password
// "value"  = try the supplied value then the cache but don't prompt for another password if it fails
// ""       = skip the cache and the prompt and just fail if encrypted
class ADESK_NO_VTABLE AcDbPasswordedFile
{
protected:
    virtual Acad::ErrorStatus tryPassword(const wchar_t* wzPassword) = 0;
    virtual const ACHAR* getFullPath() = 0;
public:
    Acad::ErrorStatus open(const wchar_t* wszPassword, AcDbHostApplicationServices::PasswordOptions options);
};

#pragma pack (pop)

#endif


