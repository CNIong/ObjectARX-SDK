//
// (C) Copyright 1997-1999 by Autodesk, Inc.  All rights reserved.
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

ACUTIL_API extern class AcDbHostApplicationServices * s_pServices;

class AcDbHostApplicationProgressMeter{
public:
    AcDbHostApplicationProgressMeter();
    virtual ~AcDbHostApplicationProgressMeter();

    virtual void start(char* displayString = NULL);
    virtual void stop();
    
    virtual void meterProgress();

    virtual void setLimit(int max);

};

typedef Acad::ErrorStatus (*SELECTFILEPROC )(/*[out]*/ short *userCancel, 
                                             /*[out]*/ char*& chosenPath,
                                             void* h, // HWND
                                             const int nFlags,
                                             const char* prompt,
                                             const char* dir,
                                             const char* name,
                                             const char* type,
                                             int* pnChoice,
                                             bool* pbReadOnly,
                                             const char* pszWSTags,
                                             void* pReserved);

typedef Acad::ErrorStatus (* REMAPPROC) (/*[out]*/ char*& newName,
                                         const char* filename,
                                         int context,
                                         void* pReserved);

typedef void (* MAPFILENOTIFYPROC) (const char* filename,
                                    const char* newName,
                                    int context,
                                    void* pReserved);


class AcDbHostApplicationServices : public AcRxObject
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
        kFontMapFile
    };
    
    enum RemapFileContext
    {
        kDrawingOpen,
        kXrefResolution,
        kRasterResolution
    };

    // When a file path is required
    //
    virtual Acad::ErrorStatus findFile(char* pcFullPathOut,
                 int   nBufferLength,
                 const char* pcFilename,
                 AcDbDatabase * pDb = NULL, // When this search 
                                            // is related to a db
                 AcDbHostApplicationServices::FindFileHint hint = kDefault) = 0;

    // Select File APIs
    virtual Acad::ErrorStatus   selectFile(short *userCancel, 
                                           char*& chosenPath,
                                           void* h, // HWND
                                           const int nFlags,
                                           const char* prompt,
                                           const char* dir,
                                           const char* name,
                                           const char* type,
                                           int* pnChoice,
                                           bool* pbReadOnly,
                                           const char* pszWSTags,
                                           void* pReserved) ;
    virtual Acad::ErrorStatus   registerSelectFileCallback(const char* appName,
                                                   SELECTFILEPROC proc, 
                                                   bool unRegister = false, 
                                                   bool asPrimary  = false);
    virtual const char*         primaryClientForSelectFileCallback();
    virtual Acad::ErrorStatus   getRegisteredSelectFileClients(
                                            AcArray<const char*>& clients);

    // File remapping
    virtual Acad::ErrorStatus   mapFile(/*out*/ char*& newName,
                                        const char* filename,
                                        int context,
                                        void* pReserved);
    virtual Acad::ErrorStatus   registerMapFileCallback(const char* appName,
                                                REMAPPROC  proc,
                                                bool unRegister = false, 
                                                bool asPrimary  = false);
    virtual const char*         primaryClientForMapFileCallback();
    virtual bool                setMapFlag(bool setIt);
    virtual Acad::ErrorStatus   getRegisteredFileMapClients(
                                            AcArray<const char*>& clients);
    virtual Acad::ErrorStatus   registerMapFileNotification(const char* appName, 
                                                MAPFILENOTIFYPROC,
                                                bool unRegister = false);

    // When a fatal error is encountered this function may be called
    // to notify you.
    //
    virtual void fatalError(const char *format, ...);

    // Called when an unhandled exception occurs in an arx command or message.
    // The EXCEPTION_POINTERS pointer is obtained from the win32 api:
    // GetExceptionInformation().
    //
    virtual void reportUnhandledArxException(const _EXCEPTION_POINTERS *pExcPtrs,
                                             const char *pAppName);

    // The equivalent of ads_usrbrk()
    //
    virtual Adesk::Boolean userBreak(bool updCtrlsWhenEnteringIdle = true) const;

    virtual void displayChar(char c) const;
    virtual void displayString(const char* string, int count) const;

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
                                                char* pcBuffer);

    // gets the value of a command switch, or an environment variable, or
    // registry entry (the search is in that order).  This is the same
    // behavior as the LISP (getenv) function).  Default implementation
    // is to return NULL.
    //
    virtual const char* getEnv(const char* var);

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

    virtual const char * program ();
    virtual const char * product ();
    virtual const char * companyName();
    virtual const ProdIdCode prodcode();
    virtual const char * releaseMajorMinorString();
    virtual int   releaseMajorVersion();
    virtual int   releaseMinorVersion();
    virtual const char * versionString();
    virtual const char * getRegistryProductRootKey ();
    virtual LCID  getRegistryProductLCID() ;

    void setSystemCodePage(code_page_id);
    code_page_id getSystemCodePage();

    virtual AcadInternalServices* acadInternalServices();

    void * acadInternalGetvar (const char *name);

    // BEGIN: Internet-related services

    // Determine whether a given string ('pszURL') is a valid URL.
    //
    virtual Adesk::Boolean isURL(const char* pszURL) const;

    // 'isRemoteFile()' is the inverse of 'isURL()'--it provides a mapping
    // from a local file to the corresponding URL that the file was down-
    // loaded from. The URL, if any, is returned via 'pszURL.'
    //
    virtual Adesk::Boolean isRemoteFile(const char* pszLocalFile,
                                          char* pszURL) const;

    // Download a resource (file) identified by the URL 'pszURL' to a local
    // file, and return its name in the buffer pointed to by 'pszLocalFile.' 
    // The boolean argument 'bIgnoreCache' determines whether the file should 
    // be downloaded even if it has already been transferred earlier in the 
    // session.
    //
    virtual Acad::ErrorStatus getRemoteFile(const char* pszURL,
     char* pszLocalFile, Adesk::Boolean bIgnoreCache = Adesk::kFalse) const;

    // Upload a local resource (file) identified by the pathname 'pszLocalFile'
    // to the remote location specified by the URL 'pszURL.'
    //
    virtual Acad::ErrorStatus putRemoteFile(const char* pszURL, 
        const char* pszLocalFile) const;

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
                 char*          pszSelectedURL,
                 const char*    pszDialogTitle,
                 const char*    pszOpenButtonCaption,
                 const char*    pszStartURL, 
                 const char*    pszRegistryRootKey = 0,
                 Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const;

    // OLE Embedded Objects 
    // Draw OLE object using given HDC, objectID and rectangle in screen 
    // coordinate.
    //
    virtual void drawOleOwnerDrawItem(COleClientItem* pItem, long hdc, 
        long left, long top, long right, long bottom);

    // Get COleClientItem from Host application.
    virtual Acad::ErrorStatus getNewOleClientItem(COleClientItem*& pItem);

    // Called by AcDb when it needs to translate an OLE embedded object.
    virtual Acad::ErrorStatus serializeOleItem(COleClientItem* pItem,
        CArchive*);

    virtual Adesk::Boolean entToWorldTransform(double normal[3], flagmat *tran);

    virtual void terminateScript(); // end any running scripts

    // get substitute font for unfound font
    virtual Adesk::Boolean getSubstituteFont(char **pFileName, char *prompt, 
                                                        int type, int fontAlt); 
    virtual void alert(const char* string) const;

    virtual void auditPrintReport(AcDbAuditInfo * pAuditInfo,
                                             const char *    line,
                                             int             both) const;

    virtual char * getAlternateFontName() const { return ""; }

    virtual char * getFontMapFileName() const { return ""; }

    virtual bool cacheSymbolIndices() const { return false; }

    virtual AcDbPlotSettingsValidator* plotSettingsValidator() const; 
    virtual AcDbLayoutManager* layoutManager() const;
    virtual bool loadApp(const char* appName, 
                         AcadApp::LoadReasons why, 
                         bool printit, 
                         bool asCmd);
    virtual void getDefaultPlotCfgInfo(char* plotDeviceName, char* plotStyleName); 

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

    void acadInternalSetvar (const char *name, void * var);

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
};

// Use this method to replace the default services, you should do this 
// early on, in the InitInstance of your application for example.
//
Acad::ErrorStatus acdbSetHostApplicationServices(AcDbHostApplicationServices * pServices);

// Use this method to access the services
//
inline AcDbHostApplicationServices * 
acdbHostApplicationServices()
{
    return s_pServices;
}
extern AcDbGlobals* getDefaultGlobals();

inline AcDbGlobals *
AcDbHostApplicationServices::workingGlobals() const
{
    return mpWorkingGlobals ? mpWorkingGlobals : getDefaultGlobals();
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
                    const _EXCEPTION_POINTERS *pExcPtrs, const char *pAppName)
{
    return;
}

inline Acad::ErrorStatus
AcDbHostApplicationServices::selectFile(/*[out]*/ short *userCancel,
                                        /*[out]*/ char*& chosenPath,
                                        void* h, // HWND
                                        const int nFlags,
                                        const char* prompt,
                                        const char* dir,
                                        const char* name,
                                        const char* type,
                                        int* pnChoice,
                                        bool* pbReadOnly,
                                        const char* pszWSTags,
                                        void* pReserved) 
{ 
    return Acad::eNotHandled;
}

inline Acad::ErrorStatus   
AcDbHostApplicationServices::registerSelectFileCallback(const char* appName,
                                                        SELECTFILEPROC proc, 
                                                        bool unRegister, 
                                                        bool asPrimary)
{
    return Acad::eNotImplemented;
}
inline const char*
AcDbHostApplicationServices::primaryClientForSelectFileCallback() 
{
    return NULL;
}

    // File remapping
inline Acad::ErrorStatus 
AcDbHostApplicationServices::mapFile(char*& newName,
                                     const char* filename,
                                     int context,
                                     void* pReserved) 
{
    return Acad::eNotHandled;
}
    
inline Acad::ErrorStatus
AcDbHostApplicationServices::registerMapFileCallback(const char*, REMAPPROC,
                                                     bool unRegister,
                                                     bool asPrimary)
{
    return Acad::eNotImplemented;
}
    
inline const char*
AcDbHostApplicationServices::primaryClientForMapFileCallback() 
{
    return NULL;
}

inline
Acad::ErrorStatus
AcDbHostApplicationServices::getRegisteredSelectFileClients(
                                            AcArray<const char*>& clients)
{
    return Acad::eNotImplemented;
}

inline
Acad::ErrorStatus
AcDbHostApplicationServices::getRegisteredFileMapClients(
                                            AcArray<const char*>& clients)
{
    return Acad::eNotImplemented;
}

inline Acad::ErrorStatus
AcDbHostApplicationServices::registerMapFileNotification(const char* appName, 
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

#pragma pack (pop)

#endif


