#ifndef   _ACED_H
#define   _ACED_H
//
//  (C) Copyright 1992-2002 by Autodesk, Inc.
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
//  DESCRIPTION:  Header for Rx application definitions and C
//                access to AutoCAD Editor-specific services.
//

#include "rxnames.h"
#include "rxevent.h"
#pragma pack (push, 8)

/* Name of Registered Service Object for constructing AutoCAD-specific
   instances.
*/
#define ACED_SERVICES  "AcEdServices"
#define ACED_EDITOR_OBJ "AcEditor"

// The various modes for context menus.
enum AcadContextMenuMode {
    kDefault = 0,           // No selection set, no command active.
    kEdit,                  // Select set, no command active.
    kCommand,               // Command active.
    kHotGrip,               // Hot grip exists.
    kOsnap,                 // Shift key down.    
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
#include "accmd.h"
#pragma pack (push, 8)

#if defined(__cplusplus)

struct AcEdCommandStruc;

extern "C" {
#endif

/* Given a string representing a command name, looks through stack of
 * registered command dictionaries and returns status indicating whether
 * a command of that name is registered.  If a command is found, its
 * elements are returned in retStruc.
 * Returns TRUE if a command named <cmdStr> was found, FALSE if not.
 */

int acedCmdLookup(const char* cmdStr, int globalLookup,
                  AcEdCommandStruc* retStruc,
                  int skipUndef = FALSE);

int acedCmdLookup2(const char* cmdStr, int globalLookup,
                   AcEdCommandStruc* retStruc,
                   int sf = ACRX_CMD_DEFUN);

/* Given a string representing a command name, looks throught stack of
 * registered command dictionaries and if found, changes the undefine
 * bit in the command flags.
 */
int acedCmdUndefine(const char* cmdStr, int undefIt);

/* Takes the input string and puts the command directory of that name
 * first in the search path for command name resolution by AutoCAD.
 * Returns TRUE if a dictionary named <cmdDirName> was found, FALSE if
 * not.
 */

int acedPopCommandDirectory(const char* cmdDirName);

/* Return the innermost current command for the given document */
class AcApDocument;
Acad::ErrorStatus acedGetCommandForDocument(AcApDocument* pDoc,
                                            char*& pGlobalCmdName);

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

Acad::ErrorStatus acedSyncFileOpen(const char *pszFileToOpen,
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
 */
Adesk::Boolean acedSetColorDialogTrueColor( AcCmColor& color, Adesk::Boolean bAllowMetaColor,
                                           const AcCmColor& curLayerColor, AcCm::DialogTabs tabs = (AcCm::DialogTabs)(AcCm::kACITab | AcCm::kTrueColorTab  | AcCm::kColorBookTab) );

/* Prompt the user for a color on the command line. Return TRUE on OK else FALSE.
 * promptString : Part of the string for prompting the user for a true color.  It 
 *          mesh into the form of "promptString [Truecolor/COlorbook]<byLayer>: ".
 *          If it is NULL, it will default to "New Color".
 * color : On entry the default color on exit of OK user chosen color
 *          If it is set to kNone, then it will default to the current color.
 * bAllowMetaColor : if TRUE the pseudo-colours "BYLAYER" and "BYBLOCK" will be allowed
 */
              
Adesk::Boolean acedSetColorPrompt( char* promptString,
                                   AcCmColor& color,
                                   Adesk::Boolean bAllowMetaColor);

/* Query if a specific menugroup is loaded in the current session
 * Return True if it is else False.
 */

Adesk::Boolean acedIsMenuGroupLoaded(const char *pszGroupName);


/* Informs AutoCAD when a modeless application is starting and completing
 * some significant operation identified by strContext. 
 */
void acedSendModelessOperationStart(const char* strContext);
void acedSendModelessOperationEnded(const char* strContext);

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

/* This function sets an internal flag in AutoCAD so that when a command
 * that has a dialog that is normally not activated by LISP (such as
 * the PLOT command) is run,  the dialog will be activated rather than
 * using the command line interface.
 *
 * Returns the value that the internal flag was set to before this function
 * was called.
 */
Adesk::Boolean acedInitDialog(Adesk::Boolean useDialog = Adesk::kTrue);

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
    virtual void unknownCommand  (const char* cmdStr, AcDbVoidPtrArray *al);
    virtual void commandWillStart(const char* cmdStr);
    virtual void commandEnded    (const char* cmdStr);
    virtual void commandCancelled(const char* cmdStr);
    virtual void commandFailed   (const char* cmdStr);
 
    // Lisp Events
    //
    virtual void lispWillStart   (const char* firstLine);
    virtual void lispEnded       ();
    virtual void lispCancelled   ();

    virtual void beginClose(AcDbDatabase* pDwg);

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
    virtual void beginDwgOpen    (char* filename);
    virtual void endDwgOpen      (const char* filename);
    virtual void initialDwgFileOpenComplete(AcDbDatabase* pDwg);

    // DWG/Save Events.
    //
    virtual void dwgFileOpened(AcDbDatabase*, char* fileName);
    virtual void databaseConstructed(AcDbDatabase*);
    virtual void databaseToBeDestroyed(AcDbDatabase*);
    virtual void beginSave    (AcDbDatabase*, const char* pIntendedName);
    virtual void saveComplete (AcDbDatabase*, const char* pActualName);
    virtual void abortSave    (AcDbDatabase*); 

    // Insert Events.
    //
    virtual void beginInsert(AcDbDatabase* pTo, const char* pBlockName,
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
    virtual void sysVarChanged        (const char* varName, Adesk::Boolean success);
    virtual void sysVarWillChange     (const char* varName);
 
    // XREF-related Events
    //
    virtual void beginAttach (AcDbDatabase* pTo, const char*,
                              AcDbDatabase* pFrom);
    virtual void otherAttach (AcDbDatabase* pTo, AcDbDatabase* pFrom);
    virtual void abortAttach (AcDbDatabase* pFrom);
    virtual void endAttach   (AcDbDatabase* pTo);
    virtual void redirected  (AcDbObjectId  newId, AcDbObjectId oldId);
    virtual void comandeered (AcDbDatabase* pTo, AcDbObjectId id,
                              AcDbDatabase* pFrom);
    virtual void beginRestore(AcDbDatabase* pTo, const char*,
                              AcDbDatabase* pFrom);
    virtual void abortRestore(AcDbDatabase* pTo);
    virtual void endRestore  (AcDbDatabase* pTo);

    // More XREF related Events
    // 
    virtual void xrefSubcommandBindItem   (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandAttachItem (AcDbDatabase* pHost, int activity, const char* pPath);
    virtual void xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const char* pPath);
    virtual void xrefSubcommandDetachItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandPathItem   (int activity, AcDbObjectId blockId, 
                                           const char* pNewPath);
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
    virtual void layoutSwitched(const char* newLayoutName);

    //window messages
    virtual void docFrameMovedOrResized(long hwndDocFrame, bool bMoved);
    virtual void mainFrameMovedOrResized(long hwndMainFrame, bool bMoved);

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

    virtual void modelessOperationWillStart(const char* contextStr);
    virtual void modelessOperationEnded(const char* contextStr);

    virtual void cmdIUnkModified(const char* strCommand);

protected:
    Acad::ErrorStatus veto();

private:
    Adesk::UInt8 mVeto;

friend class AcEditorImp;
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
    virtual void  onCommand(Adesk::UInt32 ) =0;
    virtual void  OnUpdateMenu();
};

Adesk::Boolean acedAddObjectContextMenu(const AcRxClass *pClass, 
                                        AcEdUIContext *pContext,
                                        const void *appId);
Adesk::Boolean acedRemoveObjectContextMenu(const AcRxClass *pClass, 
                                           AcEdUIContext *pContext);

Adesk::Boolean acedAddDefaultContextMenu(AcEdUIContext *pContext, 
                                         const void *appId, 
                                         const char* appName=NULL);
Adesk::Boolean acedRemoveDefaultContextMenu(AcEdUIContext *pContext);

bool    acedSetCMBaseAlias(LPCTSTR strAlias, AcadContextMenuMode mode);
LPCTSTR acedGetCMBaseAlias(AcadContextMenuMode mode);

Acad::ErrorStatus acedSetCurrentVPort(int vpnumber);
Acad::ErrorStatus acedSetCurrentVPort(AcDbViewport* pVp);

/* acedIsDragging
 * Indicates whether dragging is occurring in AutoCAD's editor.
 */

int acedIsDragging(void);

// Set the current view from an AcDbViewTableRecord.
Acad::ErrorStatus
acedSetCurrentView(AcDbViewTableRecord *pVwRec, AcDbViewport *pVP);

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

//  AutoCAD color to RGB conversion function
//
unsigned long     acedGetRGB(int color);

Acad::ErrorStatus acedGetCurrentSelectionSet(AcDbObjectIdArray& sset);

class AcDbHatch;
class AcDbEntity;

// Get the current viewport ObjectId for the current viewport.
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

#endif // cplusplus

#pragma pack (pop)
#include "dbjig.h"

#endif
