//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  DESCRIPTION:  Header for Rx application definitions and C
//                access to AutoCAD Editor-specific services.
//

#ifndef   _ACED_H
#define   _ACED_H

#include "adesk.h"
#include "rxevent.h"    // AcRxEventReactor

#include "acedinpt.h"   //for ACAD_PORT

#pragma pack (push, 8)

struct IDispatch;

/* Name of Registered Service Object for constructing AutoCAD-specific
   instances.
*/
#define ACED_SERVICES  ACRX_T("AcEdServices")
#define ACED_EDITOR_OBJ ACRX_T("AcEditor")

// The various modes for context menus.
enum AcadContextMenuMode {
    kDefault = 0,           // No selection set, no command active.
    kEdit,                  // Select set, no command active.
    kCommand,               // Command active.
    kHotGrip,               // Hot grip exists.
    kOsnap,                 // Shift key down.   
#ifdef _ADESK_MAC_
	kCMPaperSpace           // In paper space. 
#endif
};

enum xrefSubcommandActivities
{    
    kStart = 0,
    kStartItem = 2,
    kEndItem = 3,
    kEnd = 4,
    kWillAbort = 5,
    kAborted = 6,
    kStartXBindBlock = 7,
    kStartXBindSymbol = 8
};



enum undoSubcommandActivities
{
    kNone = 0,
    kOne = 1,
    kAll = 2
};

#pragma pack (pop)
#include "accmd.h"      // ACRX_CMD_DEFUN
#pragma pack (push, 8)

#if defined(__cplusplus)

struct AcEdCommandStruc;
class AcString;
class AcRxVariable;
class AcGiImageBGRA32;
class AcEdImpSysVarIterator;

extern "C" {
#endif

/* Given a string representing a command name, looks through stack of
 * registered command dictionaries and returns status indicating whether
 * a command of that name is registered.  If a command is found, its
 * elements are returned in retStruc.
 * Returns TRUE if a command named <cmdStr> was found, FALSE if not.
 */

int acedCmdLookup(const ACHAR* cmdStr, int globalLookup,
                  AcEdCommandStruc* retStruc,
                  int skipUndef = FALSE);

int acedCmdLookup2(const ACHAR* cmdStr, int globalLookup,
                   AcEdCommandStruc* retStruc,
                   int sf = ACRX_CMD_DEFUN);

/* Given a string representing a command name, looks throught stack of
 * registered command dictionaries and if found, changes the undefine
 * bit in the command flags.
 */
int acedCmdUndefine(const ACHAR* cmdStr, int undefIt);

/* Takes the input string and puts the command directory of that name
 * first in the search path for command name resolution by AutoCAD.
 * Returns TRUE if a dictionary named <cmdDirName> was found, FALSE if
 * not.
 */

int acedPopCommandDirectory(const ACHAR* cmdDirName);

/* Return the innermost current command for the given document */
class AcApDocument;
Acad::ErrorStatus acedGetCommandForDocument(AcApDocument* pDoc,
                                            ACHAR*& pGlobalCmdName);

/* acedSetOLELock
 * Takes an integer argument as the lock code which must be used to
 * unlock the interface.  This sets a soft lock meaning that people
 * can choose to ignore it, but only if they don't care about clobbering
 * the user or another app, or AutoCAD.  If you call this function and
 * you get Adesk::kFalse, then you should not attempt to call AutoCAD
 * functions.  If you get Adesk::kTrue, it means no other app or user
 * is active and it's okay for the caller to access the AutoCAD functions.
 * The second integer argument specifies the mode in which it is acceptable
 * to grab the lock.  The mode bits are the same as those outlined in the
 * addCommand member for defining ARX commands. */

Adesk::Boolean acedSetOLELock(int handle, int flags=0);

/* acedClearOLELock
 * Takes an integer argument as the lock code which was used to set the
 * lock orriginally.  If the lock codes don't match, then the operation
 * will fail and return Adesk::kFalse;  If they match, it will return
 * Adesk::kTrue.  Once the lock is cleared, another OLE application is
 * free to set the lock, so don't attempt to use the AutoCAD ADS functions
 * outside of a acedSetOLELock/acedClearOLELock section.
 */

Adesk::Boolean acedClearOLELock(int handle);

/* acedPostCommandPrompt
 * Causes AutoCAD to repost the last command prompt message.  This is
 * used from OLE applications that are invoked without going through
 * the normal AutoCAD user interface.  Call this function just prior
 * to exit from OLE app.
 */

void acedPostCommandPrompt();
 
#if defined(__cplusplus)

}

/* acedSyncFileOpen
 * Causes the file specified by pszFileToOpen to be synchronously opened
 * within the AutoCAD editor.
 */

Acad::ErrorStatus acedSyncFileOpen(const ACHAR *pszFileToOpen,
                                   const wchar_t* wszPassword = NULL);

/* Perform the SetColor dialog. Return TRUE on OK else FALSE
 * nColor : On entry the default color on exit of OK user chosen color
 * bAllowMetaColor : if TRUE the pseudo-colours "BYLAYER" and "BYBLOCK"
 *                   will be allowed
 * nCurLayerColor : is the color of the current layer, For use in the
 *                  color swatch if the color is set to "BYLAYER"
 */

Adesk::Boolean acedSetColorDialog(int& nColor, Adesk::Boolean bAllowMetaColor,
    int nCurLayerColor);

/* Perform the SetColor dialog. Return TRUE on OK else FALSE.
 * Similar to acedSetColorDialog, but capable of returning true colors.
 * color : On entry the default color on exit of OK user chosen color
 * bAllowMetaColor : if TRUE the pseudo-colours "BYLAYER" and "BYBLOCK"
 *                   will be allowed
 * curLayerColor : is the color of the current layer, For use in the
 *                 color swatch if the color is set to "BYLAYER"
 * tabs: specifies which selection method tabs to display to the user
 */
Adesk::Boolean acedSetColorDialogTrueColor( AcCmColor& color, Adesk::Boolean bAllowMetaColor,
                                           const AcCmColor& curLayerColor, AcCm::DialogTabs tabs = (AcCm::DialogTabs)(AcCm::kACITab | AcCm::kTrueColorTab  | AcCm::kColorBookTab) );

#if defined(_ADESK_WINDOWS_)
// We don't needs these for the OSX/GCC port.
/* Defines a callback prototype to be used with the callback version of the 
 * set color dialog.
 */
typedef void (WINAPI* AcEdColorDialogCallbackFunction)(void *pCallbackData, const AcCmColor& newColor);

/* Perform the SetColor dialog but with a callback. Return TRUE on OK else FALSE.
 * Similar to acedSetColorDialogTrueColor, but the caller receives callbacks on
 * each intermediate color selection.
 * color : On entry the default color on exit of OK user chosen color
 * bAllowMetaColor : if TRUE the pseudo-colours "BYLAYER" and "BYBLOCK"
 *                   will be allowed
 * curLayerColor : is the color of the current layer, For use in the
 *                 color swatch if the color is set to "BYLAYER"
 * tabs: specifies which selection method tabs to display to the user
 * callback: a method called for intermediate color selections
 * pCallbackData: context data for the callback method
 */
Adesk::Boolean acedSetColorDialogTrueColorWithCallback( AcCmColor& color,
                                                        Adesk::Boolean bAllowMetaColor,
                                                        const AcCmColor& curLayerColor,
                                                        AcCm::DialogTabs tabs = (AcCm::DialogTabs)(AcCm::kACITab | AcCm::kTrueColorTab  | AcCm::kColorBookTab),
                                                        AcEdColorDialogCallbackFunction callback = NULL,
                                                        void * pCallbackData = NULL);
#endif
/* Prompt the user for a color on the command line. Return TRUE on OK else FALSE.
 * promptString : Part of the string for prompting the user for a true color.  It 
 *          mesh into the form of "promptString [Truecolor/COlorbook]<byLayer>: ".
 *          If it is NULL, it will default to "New Color".
 * color : On entry the default color on exit of OK user chosen color
 *          If it is set to kNone, then it will default to the current color.
 * bAllowMetaColor : if TRUE the pseudo-colours "BYLAYER" and "BYBLOCK" will be allowed
 */
              
Adesk::Boolean acedSetColorPrompt( ACHAR* promptString,
                                   AcCmColor& color,
                                   Adesk::Boolean bAllowMetaColor);

/* Query if a specific menugroup is loaded in the current session
 * Return True if it is else False.
 */

Adesk::Boolean acedIsMenuGroupLoaded(const ACHAR *pszGroupName);


/* Loads a partial menu file.
 * Returns true if partial menu is successfully loaded.
 */
bool acedLoadPartialMenu(const TCHAR* pszMenuFile);


/* Unloads a partial menu file.
 * Returns true if partial menu is successfully unloaded.
 */
bool acedUnloadPartialMenu(const TCHAR* pszMenuFile);


/* Forces a reload of the currently loaded menus.
 * bIncrementalReloading : if true, menus will be reloaded incrementally.
*/

void acedReloadMenus(bool bIncrementalReloading);


/* Informs AutoCAD when a modeless application is starting and completing
 * some significant operation identified by strContext. 
 */
void acedSendModelessOperationStart(const ACHAR* strContext);
void acedSendModelessOperationEnded(const ACHAR* strContext);

/* acedUpdateDisplay     
 * Asks AutoCAD to update its display screen immediately.
 * AutoCAD manages its display area in the most efficient way by 
 * keeping track of which portions of screen get affected as you make
 * various call to AutoCAD. In general the calls you make will not
 * immediately be reflected in screen changes because AutoCAD will 
 * conglomerate the calls and make them apparent at times that minimize 
 * disturbances to the screen. When AutoCAD is not active or has no focus,
 * it will not update its display at all. If you're in a modeless dialog
 * and adding or updating an entity, the display won't show the changes
 * immediatley. Use this function to force AutoCAD to update its display.
 * While it might initially appear to be a good idea to call acedUpdateDisplay 
 * frequently, there are two possible drawbacks.  
 * First, it might incur undue processing overhead.  
 * Secondly, frequent calls to correct the display might result in screen 
 * flashing disturbing to the user.
 */
void acedUpdateDisplay();

/* acedUpdateDisplayPause
 * This function allows turning off display updates in order to hide 
 * automated tasks from the user.  All documents are affected by this 
 * call. This call should not be enabled if any kind of drawing area 
 * input is expected from the user. There are no additional 
 * restrictions on what can be done in this paused state then there 
 * would be if the display were not paused.  Callers of this function 
 * should first save the return value from acedUpdateDisplayPaused(), 
 * then restore that value when finished pausing the display. 
 */
void acedUpdateDisplayPause (bool bEnable);

/* acedIsUpdateDisplayPaused
 * Returns true if display updates are paused, false otherwise.   This 
 * function should be used before calling acedUpdateDisplayPause, to 
 * record the current update display pause state and restore that when 
 * finished pausing the display.  This way, other users of 
 * acedUpdateDisplayPause will not have the display re-enabled 
 * prematurely. 
 */
bool acedIsUpdateDisplayPaused (void);

/* This function sets an internal flag in AutoCAD so that when a command
 * that has a dialog that is normally not activated by LISP (such as
 * the PLOT command) is run,  the dialog will be activated rather than
 * using the command line interface.
 *
 * Returns the value that the internal flag was set to before this function
 * was called.
 */
Adesk::Boolean acedInitDialog(Adesk::Boolean useDialog = Adesk::kTrue);

/////////////////////////////////////////////////////////////////////////////
// This function sets a int variable in the current document establishing the 
// version of the command that will be run next.  The return value is the 
// old version value. Calling this method will no argument will initialize the
// value to 0, which indicates that no version has been established.
/////////////////////////////////////////////////////////////////////////////
//
Adesk::UInt8 acedInitCommandVersion(Adesk::UInt8 nVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// This function is used to query the requested version of the command currently
// in progress.  It does this by querying the version set at this depth of 
// the command version stack.
/////////////////////////////////////////////////////////////////////////////
//
Adesk::UInt8 acedGetCommandVersion();

void
acedDisableDefaultARXExceptionHandler(Adesk::Boolean disable = Adesk::kTrue);

Acad::ErrorStatus acedVportTableRecords2Vports();

Acad::ErrorStatus acedVports2VportTableRecords();

Acad::ErrorStatus
acedVPLayer(const AcDbObjectId& vpId, const AcDbObjectIdArray& layerIds,
    AcDb::VpFreezeOps operation);

#define acedServices  \
AcEdServices::cast(acrxServiceDictionary->at(ACED_SERVICES))

class AcEdServices: public AcRxService 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdServices);
    virtual AcEdCommand* newAcEdCommand(AcRxFunctionPtr cmdFcnAddr,
        Adesk::Int32 cmdFlags) const = 0;
};

class AcDbDatabase;

class AcEditorReactor: public AcRxEventReactor 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEditorReactor);
    AcEditorReactor() : mVeto(0) {}

    // Command Events
    //
    virtual void unknownCommand  (const ACHAR* cmdStr, AcDbVoidPtrArray *al);
    virtual void commandWillStart(const ACHAR* cmdStr);
    virtual void commandEnded    (const ACHAR* cmdStr);
    virtual void commandCancelled(const ACHAR* cmdStr);
    virtual void commandFailed   (const ACHAR* cmdStr);
 
    // Lisp Events
    //
    virtual void lispWillStart   (const ACHAR* firstLine);
    virtual void lispEnded       ();
    virtual void lispCancelled   ();

    ADESK_DEPRECATED virtual void beginClose(AcDbDatabase* pDwg);

    // DXF In/Out Events.
    //
    virtual void beginDxfIn      (AcDbDatabase*);
    virtual void abortDxfIn      (AcDbDatabase*);
    virtual void dxfInComplete   (AcDbDatabase*);
    //
    virtual void beginDxfOut     (AcDbDatabase*);
    virtual void abortDxfOut     (AcDbDatabase*);
    virtual void dxfOutComplete  (AcDbDatabase*);

    // DWG Open Events.
    //
    virtual void beginDwgOpen    (ACHAR* filename);
    virtual void endDwgOpen      (const ACHAR* filename, AcDbDatabase* pDb);
    virtual void initialDwgFileOpenComplete(AcDbDatabase* pDwg);

    // DWG/Save Events.
    //
    virtual void dwgFileOpened(AcDbDatabase*, ACHAR* fileName);
    virtual void databaseConstructed(AcDbDatabase*);
    virtual void databaseToBeDestroyed(AcDbDatabase*);
    virtual void beginSave    (AcDbDatabase*, const ACHAR* pIntendedName);
    virtual void saveComplete (AcDbDatabase*, const ACHAR* pActualName);
    virtual void abortSave    (AcDbDatabase*); 

    // Insert Events.
    //
    virtual void beginInsert(AcDbDatabase* pTo, const ACHAR* pBlockName,
                             AcDbDatabase* pFrom);
    virtual void beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform,
                             AcDbDatabase* pFrom);
    virtual void otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap,
                             AcDbDatabase* pFrom);
    virtual void abortInsert(AcDbDatabase* pTo);
    virtual void endInsert  (AcDbDatabase* pTo);

    // Wblock Events.
    //
    virtual void wblockNotice(AcDbDatabase* pDb);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom,
                             const AcGePoint3d*& insertionPoint);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom,
                             AcDbObjectId blockId);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom); 
    virtual void otherWblock(AcDbDatabase* pTo, AcDbIdMapping&,
                             AcDbDatabase* pFrom);
    virtual void abortWblock(AcDbDatabase* pTo);
    virtual void endWblock  (AcDbDatabase* pTo);

    // Deep Clone Events.
    //
    virtual void beginDeepClone       (AcDbDatabase* pTo, AcDbIdMapping&);
    virtual void beginDeepCloneXlation(AcDbIdMapping&, Acad::ErrorStatus*);
    virtual void abortDeepClone       (AcDbIdMapping&);
    virtual void endDeepClone         (AcDbIdMapping&);

    // Sys Var Events.
    //
    virtual void sysVarChanged        (const ACHAR* varName, Adesk::Boolean success);
    virtual void sysVarWillChange     (const ACHAR* varName);
 
    // XREF-related Events
    //
    virtual void beginAttach (AcDbDatabase* pTo, const ACHAR*,
                              AcDbDatabase* pFrom);
    virtual void otherAttach (AcDbDatabase* pTo, AcDbDatabase* pFrom);
    virtual void abortAttach (AcDbDatabase* pFrom);
    virtual void endAttach   (AcDbDatabase* pTo);
    virtual void redirected  (AcDbObjectId  newId, AcDbObjectId oldId);
    virtual void comandeered (AcDbDatabase* pTo, AcDbObjectId id,
                              AcDbDatabase* pFrom);
    virtual void beginRestore(AcDbDatabase* pTo, const ACHAR*,
                              AcDbDatabase* pFrom);
    virtual void abortRestore(AcDbDatabase* pTo);
    virtual void endRestore  (AcDbDatabase* pTo);

    // More XREF related Events
    // 
    virtual void xrefSubcommandBindItem   (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandAttachItem (AcDbDatabase* pHost, int activity, const ACHAR* pPath);
    virtual void xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const ACHAR* pPath);
    virtual void xrefSubcommandDetachItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandPathItem   (int activity, AcDbObjectId blockId, 
                                           const ACHAR* pNewPath);
    virtual void xrefSubcommandReloadItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandUnloadItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);

    // UNDO Events 
    //
    virtual void undoSubcommandAuto       (int activity, Adesk::Boolean state);
    virtual void undoSubcommandControl    (int activity, int option);
    virtual void undoSubcommandBegin      (int activity);
    virtual void undoSubcommandEnd        (int activity);
    virtual void undoSubcommandMark       (int activity);
    virtual void undoSubcommandBack       (int activity);
    virtual void undoSubcommandNumber     (int activity, int num);

    virtual void pickfirstModified();
    virtual void layoutSwitched(const ACHAR* newLayoutName);

    //window messages
    virtual void docFrameMovedOrResized(Adesk::LongPtr hwndDocFrame, bool bMoved);
    virtual void mainFrameMovedOrResized(Adesk::LongPtr hwndMainFrame, bool bMoved);

    //Mouse events
    virtual void beginDoubleClick(const AcGePoint3d& clickPoint);
    virtual void beginRightClick(const AcGePoint3d& clickPoint);

    // Toolbar Size changes
    virtual void toolbarBitmapSizeWillChange(Adesk::Boolean bLarge);
    virtual void toolbarBitmapSizeChanged(Adesk::Boolean bLarge);

    // WblockObjects - begin new pFrom database
    virtual void beginWblockObjects (AcDbDatabase* pFrom, AcDbIdMapping& );

    // Partial Open Events
    //
    virtual void partialOpenNotice(AcDbDatabase* pDb);
    virtual void objectsLazyLoaded(const AcDbObjectIdArray& idArray);

    // Quit Events
    virtual void beginQuit();
    virtual void quitAborted();
    virtual void quitWillStart();

    virtual void modelessOperationWillStart(const ACHAR* contextStr);
    virtual void modelessOperationEnded(const ACHAR* contextStr);

    virtual void cmdIUnkModified(const ACHAR* strCommand);


    /// <summary>
    ///
    ///  Sends notification on the start of an xref subcommand. The xref
    ///  subcommands are the ones in the following enum (aced.h):
    ///  
    ///     enum AcXrefSubCommand {
    ///                  kAttach,
    ///                  kBind,
    ///                  kDetach,
    ///                  kOverlay,
    ///                  kPath,
    ///                  kReload,
    ///                  kResolve,
    ///                  kUnload,
    ///                  kXBind
    ///     };
    ///
    ///   An application can veto the operation by returning a bad status,
    ///   e.g. Acad::eVetoed.
    ///
    ///   There are multiple output arguments, based on the subcommand.
    ///   Subcommands like attach have all the arguments provided.
    ///   Subcommands like Bind only supply the btrids.
    ///   
    ///   The rule for checking the output arguments is: Use the BtrIds first.
    ///   The other two arguments may be empty.
    ///   In subcommands like Path - the path in the Block Table Record could
    ///   differ from the one in the paths argument - in which case - both
    ///   could be used.
    ///
    /// </summary>
    ///
    /// <param name="subcmd">
    /// The subcommand which is about to start.
    /// </param>
    ///
    /// <param name="btrIds">
    /// The xref block table record ids. The primary output argument.
    /// </param>
    ///
    /// <param name="btrNames">
    ///  Xref Block Table Record names.
    /// </param>
    ///
    /// <param name="paths">
    /// The path strings for the subcommand, if applicable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. If the application return an
    /// error status, the subcommand will be vetoed.
    /// </returns>
    ///
    /// <remarks>
    ///  Though the btr names and path arguments seem redundant at times,
    ///  they can help applications avoid open for write/open for read conflicts
    ///  in case the subcommand already has the Block Table Record open.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus xrefSubCommandStart(
            AcXrefSubCommand subcmd, 
            const AcDbObjectIdArray& btrIds,
            const ACHAR* const * btrNames,
            const ACHAR* const * paths);


    /// <summary>
    /// Notification just before an Xref is locked via 
    /// AcEdXrefFileLock::lockFile().
    /// </summary>
    ///
    /// <param name = "btrId">
    /// The xref block table record id that is to be locked.
    /// </param>
    ///
    virtual void preXrefLockFile(AcDbObjectId btrId);

    virtual void viewChanged();

protected:
    Acad::ErrorStatus veto();

private:
    Adesk::UInt8 mVeto;

friend class AcEditorImp;
};

class AcEditorReactor2 : public AcEditorReactor
{
public:
    ACRX_DECLARE_MEMBERS(AcEditorReactor2);

    // One can call veto() during this notifcation to stop
    // AutoCAD from shutting down the document
    // This notification is fired *before* the legacy beginClose event
    virtual void beginDocClose(AcDbDatabase* /*pDwg*/) {}

    // docCloseAborted is fired to all reactors that received
    // the beginDocClose event when the last reactor vetos the close
    virtual void docCloseAborted(AcDbDatabase* /*pDwg*/) {}

    // This notification is fired at the same time as the legacy beginClose event
    virtual void docCloseWillStart(AcDbDatabase* /*pDwg*/) {}

    // Layout switch is about to occur
    virtual void layoutToBeSwitched (const ACHAR * /*oldLayoutName*/, const ACHAR * /*newLayoutName*/) {}

    // Drawing area has moved or resized
    virtual void dwgViewResized (Adesk::LongPtr /*hwndDwgView*/) {}


};


class CAdUiPathname;

class AcEditorReactor3 : public AcEditorReactor2
{
public:
    ACRX_DECLARE_MEMBERS(AcEditorReactor3);

    // triggered at the end of drsubs.cpp, fullregen()
    virtual void fullRegenEnded(AcDbDatabase*  /*pDb*/, 
            const AcDbIntArray & /*regenedViewports*/) {}

    // Notify about upgrade and downgrade open. Currently upublished
    // apis.
    virtual void curDocOpenUpgraded(AcDbDatabase* /*pDb*/, 
            const CAdUiPathname& /*filename*/)
    {}

    virtual void curDocOpenDowngraded(AcDbDatabase* /*pDb*/, 
            const CAdUiPathname& /*filename*/)
    {}
};

#define acedEditor AcEditor::cast(acrxSysRegistry()->at(ACED_EDITOR_OBJ))

class AcEditor: public AcRxEvent 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEditor);
    virtual void addReactor   (AcRxEventReactor * newObj) = 0;
    virtual void removeReactor(AcRxEventReactor * delObj) = 0;
};


class AcEdUIContext : public AcRxObject 
{
public:
    ACRX_DECLARE_MEMBERS(AcEdUIContext);
    virtual void* getMenuContext(const AcRxClass *, 
                                 const AcDbObjectIdArray&)=0;
    virtual void* getMenuContext(const AcRxClass*,
                                 const AcDbObjectIdArray&,
                                 const AcArray<AcDbFullSubentPathArray, 
                                               AcArrayObjectCopyReallocator<AcDbFullSubentPathArray> >& subentIds);
        
    virtual void  onCommand(Adesk::UInt32 ) =0;
    virtual void  OnUpdateMenu();
};

Adesk::Boolean acedAddObjectContextMenu(AcRxClass *pClass, 
                                        AcEdUIContext *pContext,
                                        const void *appId);
Adesk::Boolean acedRemoveObjectContextMenu(AcRxClass *pClass, 
                                           AcEdUIContext *pContext);

Adesk::Boolean acedAddDefaultContextMenu(AcEdUIContext *pContext, 
                                         const void *appId, 
                                         const ACHAR* appName=NULL);
Adesk::Boolean acedRemoveDefaultContextMenu(AcEdUIContext *pContext);

bool    acedSetCMBaseAlias(LPCTSTR strAlias, AcadContextMenuMode mode);
LPCTSTR acedGetCMBaseAlias(AcadContextMenuMode mode);

Acad::ErrorStatus acedMspace();  // in a layout, switch to mspace
Acad::ErrorStatus acedPspace();  // in a layout, switch to pspace
Acad::ErrorStatus acedSetCurrentVPort(int vpnumber);
Acad::ErrorStatus acedSetCurrentVPort(const AcDbViewport* pVp);

/* acedIsDragging
 * Indicates whether dragging is occurring in AutoCAD's editor.
 */

int acedIsDragging(void);

// Set the current view from an AcDbViewTableRecord.
Acad::ErrorStatus
acedSetCurrentView(AcDbViewTableRecord *pVwRec, AcDbViewport *pVP);

// Restore a named view into current active viewport
Acad::ErrorStatus acedRestoreCurrentView(const AcDbObjectId& namedViewId);

short acedGetCurVportCircleSides();
Acad::ErrorStatus acedSetCurVportCircleSides(short value);

void acedGetCurVportPixelToDisplay(double& xFactor, double& yFactor);
void acedGetCurVportScreenToDisplay(double& xFactor, double& yFactor);

Acad::ErrorStatus acedSetCurrentUCS(const AcGeMatrix3d & mat);
Acad::ErrorStatus acedGetCurrentUCS(AcGeMatrix3d& mat);
Acad::ErrorStatus acedRestorePreviousUCS();

class AcDbFcf;
class AcDbMText;

// Replaces the AcDbFcf::edit() method
// pTol must be open for Write
//
void acedEditToleranceInteractive(AcDbFcf* pTol);

// Replaces the AcDbMText::edit() method
// pMText must be open at least for Read, preferably for Write
int acedEditMTextInteractive(AcDbMText* pMText, bool useNewUI = false, bool allowTabs = false);

enum DimstyleTabSuppressed {
    kSymbolsArrowsTabSuppressed   = 0x01,
    kTextTabSuppressed            = 0x02,
    kFitTabSuppressed             = 0x04,
    kPrimaryTabSuppressed         = 0x08,
    kAlternateTabSuppressed       = 0x10,
    kToleranceTabSuppressed       = 0x20
};

int acedEditDimstyleInteractiveEx(AcDbDatabase * pDb, 
                              AcDbDimStyleTableRecord * pRec, 
                              int familyType,
                              const ACHAR* title = NULL,
                              int tabCtrlFlags = 0);

//  AutoCAD color to RGB conversion function
//
Adesk::UInt32     acedGetRGB(int color);

Acad::ErrorStatus acedGetCurrentSelectionSet(AcDbObjectIdArray& sset);

// acedGetFullSubentPatsForCurrentSelection
// Obtains the selected sub-entities on the entity specified in the current 
// selection set. 
//   selectedObject - The AcDbObjectId (returned by a prior call to 
//                    acedGetCurrentSelectionSet) that may have selected
//                    sub-entities.
//   selectedSubentities - The sub-entities, if any, currently selected
//                    on the object.
//                    
// Returns Acad::eOk if successful and sub-entities are selected.  Returns
// Acad::eSubSelectionSetEmpty if the entity is in the current selection set
// but has no sub-entities selected. Returns Acad::eKeyNotFound if the entity
// is not in the current selection set. 
// 
Acad::ErrorStatus acedGetFullSubentPathsForCurrentSelection(
        const AcDbObjectId&      selectedObject,
        AcDbFullSubentPathArray& selectedSubentities);

class AcDbHatch;
class AcDbEntity;

// AutoCAD's IDispatch pointer
#define acedGetIDispatch AcadGetIDispatch
extern "C" IDispatch *acedGetIDispatch (BOOL bAddRef);

// Get the current viewport id.  Returns null id if no vports open.
// The id returned will refer to a viewport entity (AcDbViewport) if
// the editor is in layout mode.  Otherwise, in tilemode, it will
// refer to an AcDbViewportTableRecord object.
//
AcDbObjectId acedActiveViewportId();

// Converts viewport number into an id.  The id refers to a Viewport
// entity (in layout mode) or to a ViewportTableRecord (in tile mode).
// The int number is one returned by the CVPORT sysvar or by the
// AcDbViewport::number() method.
//
AcDbObjectId acedViewportIdFromNumber(int nVpNum);

// Returns the number of viewports in the current editor window.
// Includes the paperspace viewport, when we're in layout mode.
//
int acedNumberOfViewports();

// Get the current viewport ObjectId for the current layout's viewport.
// Returns null id in tile mode.  Note that acedActiveViewportId()
// has the same functionality as this when in layout mode.
AcDbObjectId acedGetCurViewportObjectId();

// Replaces AcDbHatch::convertFrom()
// pHatch must be a newly created, and open for write.
// pEnt must be an AcDbBlockReference or AcDbSolid
// If transferId is kTrue, the calling AcDbHatch will assume the 
// AcDbObjectId, handle, any extended entity data, extension dictionaries, 
// or reactors, as well as any hatch associativity of pEnt. This is the only 
// way the associativity with the boundary objects can be transferred. pEnt 
// will then be deleted and set to NULL. If transferId is kFalse, pEnt will 
// remain in the database as is and the caller is responsible for closing it. 
// The resulting AcDbHatch will not be database-resident, and as such, cannot 
// assume any of the associativity with pEnt's boundary objects. The caller 
// can later call pEnt->handOverTo() to exchange the new AcDbHatch for pEnt in 
// the database, but the associativity cannot be re-established.
Acad::ErrorStatus 
acedConvertEntityToHatch(AcDbHatch* pHatch, AcDbEntity*& pEnt, bool transferId);


enum AcHatchNotifier {
    kNobody           = 0x00,
    kImpHatch         = 0x01,
    kBoundary         = 0x02,
    kHatchAndBoundary = (kImpHatch | kBoundary),
    kAddScale         = 0x04
};

enum AcHatchEdReact
{
    kStartHatchWatcher = 1,
    kSwapHatchId,
    kUpRootHatchWatcher, 
    kDestroyHatchWatcher,
    kDisableNextStart,
    kRecomputeBoundary
};

Acad::ErrorStatus
acedManageHatchEditorReactor(AcDbObjectId hatchId,
                         AcHatchEdReact action,
                         AcDbObjectId boundaryId = AcDbObjectId::kNull,
                         AcHatchNotifier notifyType = kNobody,
                         bool transformed = false);

// DrawOrder Inheritance command type

enum AcEdDrawOrderCmdType {
    kDrawOrderNone = 0,
    kDrawOrderBottom,
    kDrawOrderTop,
    kDrawOrderBelow,
    kDrawOrderAbove
};

// acedDrawOrderInherit() is called to set DrawOrder on the new childArray object(s).
// It should be called after the childArray objects are added to the space/db, but before
// they are regen'ed, so that they are regen'ed to the proper location the first time.
// If "cmd" arg is kDrawOrderBelow or kDrawOrderAbove, then a valid parent id must be supplied, and 
// children objects are place either just below or just above the parent entity, visually.

// If cmdtype passed in is Top or Bottom, parent entity can be NULL (and any value is ignored, since
// the entity is being moving to the very top or bottom of DrawOrder.)

// The parent and all child entities must all be in the same space (Model, Paper, or a given block).

Acad::ErrorStatus  acedDrawOrderInherit(AcDbObjectId parent,
                                        AcDbObjectIdArray &childArray,
                                        AcEdDrawOrderCmdType cmd);


// acedCreateViewportByView
//
// This function creates a viewport for the given model view at the desired
// location.  It bases the size of the viewport on the scale factor and the
// size of the model view, e.g. a model view 20 feet across and a scale of
// 1 foot to 1/4 inch would yield a viewport that was 5 inches across on the
// paper of the layout.
//
// This call assumes that the viewport is being created in the current
// layout.
Acad::ErrorStatus
acedCreateViewportByView(AcDbDatabase *pDb,
                         const AcDbObjectId& view, 
                         const AcGePoint2d& location, 
                         double scale,
                         AcDbObjectId& viewportId);


// acedCreateEnhancedViewportOnDrop
//
// This function creates an AcDbViewport in the current layout of the
// current drawing database.  It takes the referred to file, XREF's it in,
// creates a viewport at the specified location at a size determined from
// the view's model size combined with the scale factor, and sets the
// viewports viewing parameters to those of the view, including the views
// layer state.  This method provides no user interaction.
Acad::ErrorStatus
acedCreateEnhancedViewportOnDrop(const ACHAR *filename,
                                 const ACHAR *viewName,
                                 const AcGePoint2d location,
                                 double scale,
                                 AcDbObjectId labelBlockId,
                                 AcDbObjectId& sheetViewId,
                                 AcDbObjectId& viewportId);


Acad::ErrorStatus
acedCreateEnhancedViewportOnDropDWG(const ACHAR *filename,
                                    AcDbExtents *extents,
                                    const AcGePoint2d location,
                                    double scale,
                                    AcDbObjectId labelBlockId,
                                    AcDbObjectId& sheetViewId,
                                    AcDbObjectId& viewportId);

// acedGetUnitsValueString 
// 
// Returns the localized string used to represent an AcDb::UnitsValue to the
// user. 
// The units parameter specifies the string to obtain the localized string for.
// The method returns NULL if the units value provided is invalid. 
// 
const AcString* acedGetUnitsValueString (AcDb::UnitsValue units);

/// <summary>
/// This function computes the conversion factor that blocks and xrefs 
/// need to be scaled duing insertion to retain their size.  So for example, 
/// if a block that is created using feet as its units is inserted into a drawing
/// with inches as its units, the conversion will be 12.
/// </summary>
/// <param name="blkInsunits">Input units that the block is created with.</param>
/// <param name="conversionFactor">Return the conversion factor between the block's
/// units and the current drawing's units.</param>
/// <returns>Returns true if a conversion factor was computed.</returns>
bool acedGetUnitsConversion(AcDb::UnitsValue blkInsunits, double& conversionFactor);

// acdbCanonicalToSystemRange 
// 
// Outputs a string to display a range of doubles, conforming to current editor settings. 
// The method returns false if the input string is empty or cannot be parsed.
// 
bool acdbCanonicalToSystemRange(int eUnits, const AcString& strIn, AcString& strOut);

// acdbSystemRangeToCanonical 
// 
// Outputs a canonical string representing a range of doubles, given a string which
// represents that range using numbers conforming to current editor settings. 
// The method returns false if the input string is empty or cannot be parsed.
// 
bool acdbSystemRangeToCanonical(int eUnits, const AcString& strIn, AcString& strOut);

void acedEnableUsrbrk();
void acedDisableUsrbrk();
bool acedIsUsrbrkDisabled();

bool acedIsInBackgroundMode();

enum BlockEditModeFlags {
    kBlkEditModeNone   = 0x0,
    kBlkEditModeActive = 0x01,
    kBlkEditModeOpen   = 0x02,
    kBlkEditModeDirty  = 0x04
};

unsigned int acedGetBlockEditMode();

void acedOpenDocWindowsMinimized( bool bMinimized );

bool acedCompareToCurrentViewport(const AcDbViewTableRecord *pVwRec);

/// <summary>
/// Provides the id of the last frame rendered in animations invoked from the 
/// ANIPATH command 
/// </summary>
/// <returns>
/// Returns 0 when ANIPATH animation is inactive.  The first frame of an
/// an ANIPATH animation returns 1, and subsequent frames increment by 1 
/// from the previous frame.  
/// </returns>
Adesk::UInt32 acedGetAnimationFrameId(void);

/// <summary>This function is used to show the constraint bars for a given 
/// set of constrained entities.</summary>
/// <param name="subentPaths">Full sub-entity paths of entities for which 
/// constraint bars are to be shown.</param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedShowConstraintBar(AcDbFullSubentPathArray &subentPaths);

/// <summary>This function is used to hide the constraint bars for a given 
/// set of constrained entities.</summary>
/// <param name="subentPaths">Full sub-entity paths of entities for which 
/// constraint bars are to be hidden.</param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedHideConstraintBar(AcDbFullSubentPathArray &subentPaths);

/// <summary>This function is used to show or hide the constraint bars for 
/// all constrained entities in the active document.</summary>
/// <param name="bToShow">Set this to true to show constraint bars,
/// set to false to hide constraint bars. </param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedShowConstraintBarForAll(bool bToShow);

Acad::ErrorStatus acedTraceBoundary(const AcGePoint3d& seedPoint,
                                    bool detectIslands,
                                    AcDbVoidPtrArray& resultingBoundarySet);

void acedSetDrawComplexShape (int val);
int acedGetDrawComplexShape ();

void acedSetRecursingLinetypeVectorGeneration (int val);
int acedGetRecursingLinetypeVectorGeneration ();

struct flagmat * acedGetComplexLineTypeTransformPtr();

ACAD_PORT Acad::ErrorStatus acedAudit(AcDbDatabase* pDb, bool bFixErrors, bool bCmdLnEcho = false);
/// <summary>
/// Adds a supplemental cursor image. Only one cursor badge image can be shown at a time.
/// If multiple features supply badges the last badge with the highest priorityOrder will 
/// be the badge shown.
/// </summary>
/// <param name="pSuppCursorImage">Input image</param>
/// <param name="priorityOrder">Stacking order badge should appear in. Higher numbers win.</param>
/// <returns>Returns true if successful.</returns>
ACAD_PORT bool acedAddSupplementalCursorImage(const AcGiImageBGRA32* pSuppCursorImage, int priorityOrder = 0);

/// <summary>
/// Removes a previously added supplemental cursor badge.
/// </summary>
/// <param name="pSuppCursorImage">Input image</param>
/// <returns>Returns true if successful.</returns>
ACAD_PORT bool acedRemoveSupplementalCursorImage(const AcGiImageBGRA32* pSuppCursorImage);

/// <summary>
/// Checks if the current supplemental cursor badge is set.
/// </summary>
/// <returns>Returns true if there is supplemental cursor badge; otherwise false.</returns>
ACAD_PORT bool acedHasSupplementalCursorImage();

/// <summary>
/// Sets <x, y> to be the cursor offset to the top right corner of the pickbox.
/// </summary>
/// <param name="x">Input X offset</param>
/// <param name="y">Input Y offset</param>
ACAD_PORT void acedSetSupplementalCursorOffset(int x, int y);

/// <summary>
/// Gets the cursor offset <x, y>, which is to the top right corner of the pickbox.
/// </summary>
/// <param name="x">X offset</param>
/// <param name="y">Y offset</param>
ACAD_PORT void acedGetSupplementalCursorOffset(int& x, int& y);

class AcEdSysVarIterator
{
public:
    ACAD_PORT AcEdSysVarIterator();
    ACAD_PORT ~AcEdSysVarIterator();

    ACAD_PORT void step();
    ACAD_PORT const AcRxVariable* getSysVar();
    ACAD_PORT void reset();
    ACAD_PORT bool done() const;
private:
    AcEdImpSysVarIterator* m_pImp;
};

#endif // cplusplus

#pragma pack (pop)

#endif
 
