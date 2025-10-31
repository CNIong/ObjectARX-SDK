
/*
   Copyright (C) 1997-2004 by Autodesk, Inc.
   Permission to use, copy, modify, and distribute this software in
   object code form for any purpose and without fee is hereby granted,
   provided that the above copyright notice appears in all copies and
   that both that copyright notice and the limited warranty and
   restricted rights notice below appear in all supporting
   documentation.

   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
   UNINTERRUPTED OR ERROR FREE.

   Use, duplication, or disclosure by the U.S. Government is subject to
   restrictions set forth in FAR 52.227-19 (Commercial Computer
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
   (Rights in Technical Data and Computer Software), as applicable.

/* ========= cmdcount.cpp:  AutoCAD Command and LISP expression counter    & timer

    This program counts the number of times each AutoCAD command, AcEd-registered
    command, or unique LISP expression through its first white space, is invoked,
    and records it in a file named whatever STAT_FILENAME is defined to
    below, along with the elapsed time in seconds spent in each command.

    Note that elapsed time is recorded to 0.1 second, and additional invocation
    times are truncated to 0.1 second.  In theory, this program is measuring
    human interactive time, for which 0.1 second precision should suffice.
    
    It attempts to find the stat file on the %ACAD% path, and if it cannot,
    will attempt to create the stat file in the same directory as ACAD.EXE (again,
    the first occurence of such on the %ACAD% path).  If it cannot find ACAD.EXE,
    it will create the stat file in the current working directory.

*/

/*    Notes on modifications made subsequent to program's creation

  STAT_FILENAME_VERSION = 1.0 of STAT_FILENAME:

  v01.0
  Created:                 [date]
  Last modified:         [date]
  AUTOCad serial number: [###-########]
  [Command name]        [Hits]        [Total elapsed time, to 1/100 seconds]
  ...                    ...            ...

  =======================

  STAT_FILENAME_VERSION = 1.1 of STAT_FILENAME:

  v01.1
  Created:                 [date]
  Last modified:         [date]
  LOGINNAME:             [LOGINNAME]
  AUTOCad serial number: [###-########]
  [Command name]        [Hits]        [Total elapsed time, to 1/100 seconds]
  ...                    ...            ...

  Write STAT_FILE to location of ACAD_NT_CFG or ACAD_CFG, if they can be found.
  (They should be in the path specified by the system variable ACADCFG,
  which is not necessarily on the ACAD search path.
  statFileName is now <LOGINNAME>.txt, where LOGINNAME is set by each user
  at initial configuration, or using "config" from the command prompt.

  ========================

  STAT_FILENAME_VERSION = 1.2 of STAT_FILENAME:

  v01.2
  Created:                 [date]
  Last modified:         [date]
  LOGINNAME:             [LOGINNAME]
  AutoCAD serial number: [###-########]
  AutoCAD version:         [S.0.37, for example]
  [Command name]        [Hits]        [Total elapsed time, to 1/100 seconds]
  ...                    ...            ...

  Also, write accumulated statistics after each SAVE, SAVEAS, WBLOCK,
  and AUTOSAVE, using AcEditorReactor's member functions.
  
 ========================
  
  v01.4 Updated to fix some weird apparent compiler bug in MSVC 4.2x and 5.0
        via a logic-neutral change for Pinetop.  WCA 2/18/98

 ========================
  
  v01.5 Updated Pinetop fix to Tahoe, made MDI changes (to track command/lisp
        execution separately in each document), added code to track document
        activations and switches.  Modified dictionaries to print sorted
        lists again.  WCA 7/15/98.

  ========================

  v01.6 Updated to write log file to MyDocuments. (szilvaa 9/16/2002)

*/

#ifdef ACAD_OBJID_INLINE_INTERNAL
#include "arxapps_pch.h"
#else
    #ifdef _DEBUG
    #undef _DEBUG
    #define DEBUG_WAS_DEFINE
    #endif 
    #include "afxwin.h"
    #ifdef DEBUG_WAS_DEFINE
    #define _DEBUG
    #endif
#include "rxregsvc.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "adslib.h"
#include "rxobject.h"
#include "rxdict.h"
#include "rxkernel.h"
#include "rxditer.h"

#include "aced.h"
#include "adesk.h"
#include "dbmain.h"
#include "dbsymtb.h"
#include "dbidmap.h"
#include "dbents.h"
#include "dbidar.h"

#include "acdocman.h"
#include <appinfo.h>

static const TCHAR *kpszCmdModule = _T(/*MSG0*/" Command Module");  // MDI Safeb

static struct
{
    const TCHAR *strGlobal;        // string for globalized command name
    const TCHAR *strLocal;        // string for localized command name
} gCommands[] =
    {
        {_T(/*MSG0*/"CMDSTAT"),     _T("CMDSTAT")   },
        {_T(/*MSG0*/"CMDCOUNT"),    _T("CMDCOUNT")  },
        {NULL,                  NULL        }
    };


const TCHAR* gAppSubKey = _T("AcadCmdCount");
const TCHAR* gAppFileName = _T("CmdCount.arx");
// Forward declarations

class AsdkCommandReactor;
Adesk::Boolean updateCumulativeStats();
TCHAR *getProductName();
TCHAR *getProgramFiles(TCHAR *ext);
//********* AsdkCommandRecord --  Simple AcRxObject stored in stat dictionaries
//                                to maintain statistics.

class AsdkCommandRecord : public AcRxObject
{
  public:
    int count;
    double elapsedTime;     // Including tenths of seconds.

    AsdkCommandRecord(int initialCount, double initialTime);
};

AsdkCommandRecord::AsdkCommandRecord(int initialCount, double initialTime)
  : count(initialCount),
    elapsedTime(initialTime)
{  }

//********* Defined values

#define MAX_PATH_LENGTH            512   // based on acedFindFile() documentation

/* maximum length of recorded command strings and LISP expressions.
   Should suffice for commands of most languages, but beware of Kelvinated
   (or otherwise compressed) LISP files.  We truncate strings that aren't
   turally broken by this length. */
#define MAX_CMD_LENGTH ACRX_MAX_CMDNAME_LEN
#define DATE_TIME_LENGTH        1024  // More than enough for date/time string
// For example: Created:               11/25/2003 13:30:20\0
#define MAX_STR_LENGTH        4*1024  // More than enough for any string... (see  aclinedb.cpp's k_nCharBufferMaxLen)
#define SECONDS_PER_DAY        86400  // Number of seconds in a day
#define STAT_FILENAME_VERSION    1.3  // Version of statistics file format
#define VERSION_LENGTH           100  // Length of version string
#define LOGINNAME_LENGTH        1024  // Length of LOGINNAME that we use.
//********* Static Structures

AsdkCommandReactor* cmdr = NULL;     // Gets notification of command and LISP
                                     // evaluation events.  Always in use.
                                     // MDI-Safe

AcRxDictionary* sessionStats = NULL; // Running statistics for this AutoCAD
                                     // session, or since last query.
                                     // Always in use.
                                     // MDI-Safe

AcRxDictionary* cumulativeStats = NULL;
                                     /* Cumulative Invocation counts.  All
                                        queries of cumulative stats are
                                        preceded by a merge, and resetting
                                        of session stats.  Active only
                                        during query and update operations.
                                        NULL otherwise. */
                                     // MDI-Safe

#define PRODUCTL 21

static char product[PRODUCTL] = {NULL};  // MDI-Safe
static char abort_msg[255];              // MDI-Safe

//********* AsdkCommandReactor --  Command Event Notification class

class AsdkCommandReactor : public AcEditorReactor {

  public:

    virtual void commandWillStart(const char * cmdStr);
    virtual void commandEnded(const char * cmdStr);
    virtual void commandCancelled(const char * cmdStr);
    virtual void commandFailed(const char * cmdStr);

    virtual void lispWillStart(const char * firstLine);
    virtual void lispEnded();
    virtual void lispCancelled();

    virtual void beginSave(AcDbDatabase* pDwg, const char* pIntendedName);

    virtual void beginWblock(AcDbDatabase* pTo,
                             AcDbDatabase* pFrom,
                             const AcGePoint3d*& insertionPoint);
    virtual void beginWblock(AcDbDatabase* pTo,
                             AcDbDatabase* pFrom,
                             AcDbObjectId blockId);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom);

};

// BUMPcOUNT:  common guts for commands and lisp expressions. Returns pointer
//             to affected CommandRcd, for use by caller.

AsdkCommandRecord* bumpCount(const char* cmdStr, Adesk::Boolean positive)
{
    AsdkCommandRecord* cmdRcd = (AsdkCommandRecord*) sessionStats->at(cmdStr);

    if (cmdRcd) {
        if (positive)
            cmdRcd->count++;
        else
            cmdRcd->count--;
    } else {
        // here is where we create the official command stat entry names, so
        // we apply da rules here:
        // 1)  Keep it short
        // 2) first blank or tab termintates the string.
        char truncatedStr[MAX_CMD_LENGTH + 1];
        if (strlen(cmdStr) > MAX_CMD_LENGTH) {
            strncpy(truncatedStr, cmdStr, MAX_CMD_LENGTH);
            truncatedStr[MAX_CMD_LENGTH] = EOS;   // Not all implementations
                                                  //  of strncpy() add the 
                                                  // EOS.
        } else
            strcpy(truncatedStr, cmdStr);
        // Truncate string at first blank or tab.
        char* blankChar = strchr(truncatedStr, ' ');
        if (blankChar)
            *blankChar = EOS;
        /* Now look for a TAB character. If you have detabbed the file,
           the character in the quote probably needs fixing. */
        blankChar = strchr(truncatedStr, '    ');
        if (blankChar)
            *blankChar = EOS;
        
        // Put in dictionary, with a count of (positive ? 1 : -1)
        sessionStats->atPut(truncatedStr, cmdRcd =
            (new AsdkCommandRecord((positive ? 1 : -1), 0)));
    }

    return cmdRcd;
}

// GETcURtIME:  return double representing Julian Date, values of which
//              may be directly subtracted for elapsed time measurement.
double getCurTime()
{
    resbuf currentTime;

    if (acedGetVar(/*NOXLATE*/"DATE", &currentTime) != RTNORM) {
        // This should never happen.
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    return currentTime.resval.rreal;
}

// ELAPSEDtIMEiNsECONDS:
//               return an integer indicating number of elased time in
//               seconds between input startTime and endTime, which are
//               assumed to represent Julian dates, as described in
//               Autodesk Customization guides, as the "DATE" variable format
//               as opposed to "CDATE" format.
//
double elapsedTimeInSeconds(double endTime, double startTime)
{
    return ((endTime - startTime) * SECONDS_PER_DAY);
}

#define MAX_CMD_DEPTH 5               // Max combination I think we now
                                      // support is 3 (main->dim->xparent),
                                      // So am playing it safe.

#define MAX_LOCK_DEPTH 32             // No real Limit, but this should be plenty...

struct AsdkCmdCountDocData {
    AsdkCmdCountDocData();
    AsdkCmdCountDocData(const AsdkCmdCountDocData&);
    AsdkCmdCountDocData& operator=(const AsdkCmdCountDocData&);

    void recordAndPop();

    AcApDocument*  doc;

    // handle "nested" commands
    int                cmdIndex;   // To handle "nested" commands
    AsdkCommandRecord* cmdRcd[MAX_CMD_DEPTH];
    double             cmdStartTime[MAX_CMD_DEPTH];

    // LISP is its own, non-reentrant, beast.
    AsdkCommandRecord* lispRcd;
    double             lispStartTime;
};

AsdkCmdCountDocData::AsdkCmdCountDocData()
{
    doc = NULL;
    cmdIndex = 0;
    lispRcd = NULL;
}


AsdkCmdCountDocData::AsdkCmdCountDocData(const AsdkCmdCountDocData& src)
{
    doc = src.doc;

    cmdIndex = src.cmdIndex;
    int i;
    for (i = 0; i < cmdIndex; i++) {
        cmdRcd[i] = src.cmdRcd[i];
        cmdStartTime[i] = src.cmdStartTime[i];
    }
    lispRcd = src.lispRcd;
    lispStartTime = src.lispStartTime;
}

AsdkCmdCountDocData& AsdkCmdCountDocData::operator=(const AsdkCmdCountDocData& src)
{
    doc = src.doc;

    cmdIndex = src.cmdIndex;
    int i;
    for (i = 0; i < cmdIndex; i++) {
        cmdRcd[i] = src.cmdRcd[i];
        cmdStartTime[i] = src.cmdStartTime[i];
    }
    lispRcd = src.lispRcd;
    lispStartTime = src.lispStartTime;

    return *this;
}

AsdkCmdCountDocData curDocGlobals; // MDI-Safe

// The entire array of document-realted global structs.
static AcArray<AsdkCmdCountDocData>    docData; // MDI-Safe

// Indicates that a SAVE/WBLOCK has occurred, which we take as a signal to
// save the stats file also, after waiting for active commands to finish up
// JMC
Adesk::Boolean bStatsFileUpdatePending; // MDI-Safe

// create date for cumulative file
static char createDate[DATE_TIME_LENGTH + 1]; // MDI-Safe
// Name of stat file.  "+5" means one for EOS, four for .txt
static char statFileName[LOGINNAME_LENGTH + 5];  // MDI-Safe


void recordElapsedCmdTime(AsdkCommandRecord*& commandRecord, double startTime)
{
    commandRecord->elapsedTime += elapsedTimeInSeconds(getCurTime(),
                                                       startTime); 
}

void countCommand(const char* cmdStr)
{
    // If nesting a command, record the time spent in the pushed command, and
    // stop counting it.
    if (curDocGlobals.cmdIndex > 0)
        recordElapsedCmdTime(curDocGlobals.cmdRcd[curDocGlobals.cmdIndex - 1],
                             curDocGlobals.cmdStartTime[curDocGlobals.cmdIndex - 1]);
    curDocGlobals.cmdRcd[curDocGlobals.cmdIndex] = bumpCount(cmdStr, Adesk::kTrue);
    curDocGlobals.cmdStartTime[curDocGlobals.cmdIndex++] = getCurTime();
}

void AsdkCommandReactor::commandWillStart(const char* cmdStr)
{
    countCommand(cmdStr);
}

int lookupDoc(AcApDocument* pDoc);

void AsdkCmdCountDocData::recordAndPop()
{
    cmdIndex--;

    // Record the time spent in the ended command
    recordElapsedCmdTime(cmdRcd[cmdIndex],
                         cmdStartTime[cmdIndex]);
    // restart the clock in the suspended command, if there is one.
    if (cmdIndex > 0)
        cmdStartTime[cmdIndex - 1] = getCurTime();
}

void recordCommandDuration(const char* pszCmdStr)
{
    if (curDocGlobals.doc == NULL)
        return;

    // Verify that the command ending is the one on the top of the stack in the current
    // document.  If not, go fish through other documents.  If we are still empty handed,
    // give up.
    AsdkCommandRecord* curCmdRcd = NULL;
    if (pszCmdStr != NULL)
        curCmdRcd = (AsdkCommandRecord*) sessionStats->at(pszCmdStr);
    else if (curDocGlobals.cmdIndex > 0)
        curCmdRcd = curDocGlobals.cmdRcd[curDocGlobals.cmdIndex-1];
    bool swappedCurDoc = false;

    if ((curDocGlobals.cmdIndex <= 0) ||
        (curCmdRcd != curDocGlobals.cmdRcd[curDocGlobals.cmdIndex-1])) {
        bool foundDoc = false;
        int i = 0;
        for (; !foundDoc && (i < docData.length()); i++) {
            foundDoc = (docData[i].cmdIndex > 0) &&
                (docData[i].cmdRcd[docData[i].cmdIndex - 1] == curCmdRcd);
        }
        if (foundDoc)
            docData[i - 1].recordAndPop();
    } else {
        if (curDocGlobals.cmdIndex > 0)
            curDocGlobals.recordAndPop();
        int i = lookupDoc(curDocGlobals.doc);
        assert(i >= 0);
        docData[i] = curDocGlobals;
    }
    // Active command stack has been fully popped and we have a pending
    // statistics file update?
    if (bStatsFileUpdatePending && ::updateCumulativeStats())
        /* We have completed an operation such as SAVE or WBLOCK since
           this lisp expression began, and this is a convenient time to
           at least try to update the
           stats file with the current counts.  This must be marked pending
           and done after command completion because cmdRcd[] points to a
           CommandRecord object in *sessionStats which is deleted in
           updateCumulativeStats()called below.  updateCumulativeStats
           will return kFalse if any documents have any active command
           or LISP expressions, in which case, this will have to wait.
           JMC, WCA 7/15/98 */
         bStatsFileUpdatePending = Adesk::kFalse;
}

// Note that we COULD verify the string input to these "end of command/lisp"
// against the string passed into the "balancing" xxxWillStart() call, but
// there is no known reason why they wouldn't be, short of corrupted memory.
// So we assume our cmdRcd and lispRcd static pointers are being accurately
// maintained.
// UPDATE (11/15/02 WCA):
//            Well, there's a known reason now!  Use of a "Session Fiber"
//            command to create a new document, thus causing the command
//            (XOPEN) to begin in one document and end in another!  So now, we
//            need to verify that the command ending is the same one
//            at the top of the current document stack.  If not, look through
//            the other documents for it on the top, and for the case at
//            hand, as soon as you find one, finish it off.
// CAUTION (11/15/02 WCA): Remaining hazards:
//            1. Note that this
//            solution is limited to the scope of problem caused by XOPEN.  A
//            more general solution would support, say, the command
//            doing a prompt in the new document, therefore allowing multiple
//            invocations of it to exist concurrently, in which case we would
//            need more info than the reactors currently provide to match up
//            the beginnings and endings.
//            2. Also, I sincrely doubt that LISP can (or should be able to) invoke
//            a command that changes documents, but since it doesn't even pass
//            in a string when it completes, I dont' see much we can do without
//            A fair amount of work.

void AsdkCommandReactor::commandEnded(const char* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::commandCancelled(const char* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::commandFailed(const char* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::lispWillStart(const char* firstLine)
{
    curDocGlobals.lispRcd = bumpCount(firstLine, Adesk::kTrue);
    curDocGlobals.lispStartTime = getCurTime();
}

void AsdkCommandReactor::lispEnded()
{
    if (curDocGlobals.lispRcd != NULL)
        recordElapsedCmdTime(curDocGlobals.lispRcd, curDocGlobals.lispStartTime); 
    curDocGlobals.lispRcd = NULL;
    if (bStatsFileUpdatePending && ::updateCumulativeStats())
       /* We have completed an operation such as SAVE or WBLOCK since
          this lisp expression began, and this is a convenient time to
          at least try to update the
          stats file with the current counts.  This must be marked pending
          and done after command completion because cmdRcd[] points to a
          CommandRecord object in *sessionStats which is deleted in
          updateCumulativeStats()called below.  updateCumulativeStats
          will return kFalse if any documents have any active command
          or LISP expressions, in which case, this will have to wait.
          JMC, WCA 7/15/98 */
        bStatsFileUpdatePending = Adesk::kFalse;
}

void AsdkCommandReactor::lispCancelled()
{
    lispEnded();  // Same thing, really.
}

void AsdkCommandReactor::beginSave(AcDbDatabase* pDwg, const TCHAR* pIntendedName)
{
    // Set pending flag for update
    // in recordCommandDuration() JMC
    bStatsFileUpdatePending = Adesk::kTrue;
}

void AsdkCommandReactor::beginWblock(      AcDbDatabase* pTo,
                                       AcDbDatabase* pFrom,
                                 const AcGePoint3d*& insertionPoint)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

void AsdkCommandReactor::beginWblock(AcDbDatabase* pTo,
                                 AcDbDatabase* pFrom,
                                 AcDbObjectId blockId)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

void AsdkCommandReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

//********* AsdkDocReactor

// This class records document switches, and currently reflects the problems
// in the notification as of July 14, 1998, which are:
// 1. documentToBeActivated gets fired *way* too often, so for now, this implementation
//    is self-filtering.
// 2. documentCreated is currently fired *after* a documentToBeActivated callback
//    that it is literally useless for standard operation, but this app can use it to
//    tell which document switches were really just creations, and thus not necessarily
//    worth counting.as "switches".
//
class AsdkDocReactor : public AcApDocManagerReactor
{
public:
    virtual void documentCreated(AcApDocument* pDoc);
    virtual void documentToBeActivated(AcApDocument* pDoc);
    virtual void documentToBeDestroyed(AcApDocument* pDoc);

};

static void addDoc(AcApDocument* pDoc) {

    AsdkCmdCountDocData newData;
    newData.doc = pDoc;
    docData.append(newData);
}

int lookupDoc(AcApDocument* pDoc) {
    // NULL documents are not acceptable here...
    if (pDoc == NULL)
        return -1;

    int i;
    for (i = 0; i < docData.length(); i++) {
        if (docData[i].doc == pDoc)
            return i;
    }

    // Not Found.
    //
    // If AcApDocManagerReactor::documentCreated() were sent
    // before AcApDocumentReactor::documentToBeActivated,
    // this wouldn't be necessary!
    addDoc(pDoc);
    return docData.length()-1;
}

void
AsdkDocReactor::documentToBeActivated(AcApDocument* pDoc)
{
    if (pDoc == curDocGlobals.doc)
        bumpCount(/*NOXLATE*/"#DOC_ACTIVATED(SAME)", Adesk::kTrue);
    else {
        // If switching documents, record the time spent on the
        // current document's active command/lisp and reset the
        // start time in the new document's active command/lisp.
        int i;
        if (curDocGlobals.doc != NULL) {
            if ((i = curDocGlobals.cmdIndex - 1) >= 0)
                recordElapsedCmdTime(curDocGlobals.cmdRcd[i],
                                     curDocGlobals.cmdStartTime[i]);
            if (curDocGlobals.lispRcd != NULL)
                recordElapsedCmdTime(curDocGlobals.lispRcd,
                                     curDocGlobals.lispStartTime);
            docData[lookupDoc(curDocGlobals.doc)] = curDocGlobals;
        }
        if (pDoc == NULL) {
            // This isn't supposed to happen...
            assert(pDoc!=NULL);
            // But in production, just log it and keep going...
            bumpCount(/*NOXLATE*/"#NULL_DOC_ACTIVATED", Adesk::kTrue);
            curDocGlobals.doc = NULL;
            return;
        }
        curDocGlobals = (docData[lookupDoc(pDoc)]);
        double currentTime = getCurTime();
        if ((i = curDocGlobals.cmdIndex - 1) >= 0)
            curDocGlobals.cmdStartTime[i] = currentTime;
        curDocGlobals.lispStartTime = currentTime;
        bumpCount(/*NOXLATE*/"#DOC_SWITCHED", Adesk::kTrue);
    }
}

void
AsdkDocReactor::documentToBeDestroyed(AcApDocument *pDoc)
{
    if (pDoc == NULL) {
        // This isn't supposed to happen...
        assert(pDoc!=NULL);
        // But in production, just log it and keep going...
        bumpCount(/*NOXLATE*/"#NULL_DOC_DESTROYED", Adesk::kTrue);
        return;
    }
    int i = lookupDoc(pDoc);
    // The current document being destroyed?
    if (pDoc == curDocGlobals.doc) {
        // If Anything is still active in the document being destroyed,
        // log it as done now.
        if (curDocGlobals.lispRcd != NULL) {
            recordElapsedCmdTime(curDocGlobals.lispRcd, curDocGlobals.lispStartTime);
            curDocGlobals.lispRcd = NULL;
        }
        recordCommandDuration(NULL);
        curDocGlobals.doc = NULL;
    }
    // Remove the document data
     docData.removeAt(i);
}


void
AsdkDocReactor::documentCreated(AcApDocument* pDoc)
{
    // Log document creations, for the heck of it..
    // Note that bumpCount is independent of document-specific data.
    bumpCount(/*NOXLATE*/"#DOC_CREATED", Adesk::kTrue);

    // add an entry for the document, if some other notification hasn't
    // already done so.
    lookupDoc(pDoc);
}

static AsdkDocReactor* pDocReactor;

//********* Utility Functions

// cmdcount_findfile: Searches for the stat file as follows:
// 1. Searches the location of StatPath. 
// 2. If this key is not present it searches MyDocuments
// 3. It searches the AutoCAD search path.
// Note that MyDocuments and StatPath are mutually exclusive.
int cmdcount_findfile (const TCHAR *fname, TCHAR *result, bool returnDefault)
{
    TCHAR statFilePath[MAX_PATH_LENGTH] = "\0";
    TCHAR buf[512];
    _tcscpy(buf,acrxProductKey());
    _tcscat(buf,/*NOXLATE*/_T("\\Applications\\AcadCmdCount"));
    HKEY hKey;
    if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,buf,0,KEY_QUERY_VALUE,&hKey))
    {
        DWORD dwType = 0;
        DWORD dwDataSize = sizeof(buf);
        if (ERROR_SUCCESS == RegQueryValueEx(hKey, _T(/*MSG0*/"StatPath"), NULL, &dwType, (LPBYTE)buf, &dwDataSize))
        {
            _tcscpy(statFilePath,buf);
        }
        RegCloseKey(hKey);
    }
    if (statFilePath[0]==0)
    {
        resbuf rb;
        if (acedGetVar(/*NOXLATE*/"MYDOCUMENTSPREFIX", &rb) != RTNORM) {
            sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                    PRODUCTL, getProductName());
            acrx_abort(abort_msg);
        }
        _tcscpy(statFilePath,rb.resval.rstring);
        acdbFree(rb.resval.rstring);
    }
    if (statFilePath[strlen(statFilePath) - 1] != '\\') 
        strcat(statFilePath, "\\");
    strcat(statFilePath, fname);
    FILE* f;
    if ((f = fopen(statFilePath, /*NOXLATE*/"r")) != NULL) {
        fclose(f);
        strcpy(result, statFilePath);
        return RTNORM;
    }
    else 
    {
        int ret = acedFindFile(fname, result);
        if (ret!=RTNORM && returnDefault)
        {
            ret= RTNORM;
            strcpy(result,statFilePath);
        }
        return ret;
    }
}

// INITsTATdICTIONARY:  create a dictionary that will delete its content
//                      objects when it is deleted.
AcRxDictionary* initStatDictionary() {
    return acrxKernel->newAcRxDictionary(0, Adesk::kTrue, Adesk::kTrue);
}

// READcUMULATIVEsTATS: Read ACCOUNT.TXT into the cumulativeStats dictionary
//                      or if that can't be done, return an empty dictionary.
Adesk::Boolean readCumulativeStats()
{
    // If we got any hanging around, get rid of 'em.
    if (cumulativeStats)
        delete cumulativeStats;

    cumulativeStats = initStatDictionary();

    // Open the file
    FILE* statFile = NULL;
    TCHAR statFilePath[MAX_PATH_LENGTH];

    if (cmdcount_findfile(statFileName, statFilePath,false) == RTNORM)
        // find it, open it
        statFile = fopen(statFilePath, /*NOXLATE*/"r");
    else {
        *createDate = NULL;
        return Adesk::kFalse; // Most likely, it hasn't been created yet.
                              // one other likely reason is 
                              // that another process has it open for write,
                              // but we're talkin' a millisecond window...
    }

    char cmdName[MAX_CMD_LENGTH + 1 /*for the EOS*/ ];
    int cmdCount;
    double cmdElapsedTime;

    char dummyString[MAX_STR_LENGTH + 1];

    char versionString[VERSION_LENGTH + 1];
    
    // Read line containing STAT_FILENAME_VERSION
    fscanf(statFile, "%s", versionString);

    // Cazart!  The old test below fails after VBA is loaded and
    // the VBAIDE command executed.
    // It is reproducible, but all attempts to change code to
    // watch for interim failure makes test work again.
    // Smells like a compiler bug, although
    // being in both MSVC 4.2b and 5.0sp2 is rather amazing. Still
    // a logic-neutral code change that gums up code optimization
    // makes the reproducible bug go away, so break out the
    // headless chickens and voodoo dolls...  code by
    // Kevin Vandecar, commentary by WCA  2/18/98.
    //
#define badJuJu 1
#if defined(badJuJu)
    char stat_buf[10];
    sprintf(stat_buf, "v0%1.1f", STAT_FILENAME_VERSION);
    if (strcmp(versionString, stat_buf) != 0)
#else
    if (  (  (versionString[1] - '0') * 10.0
           + (versionString[2] - '0')
           + (versionString[4] - '0') / 10.0)
        != STAT_FILENAME_VERSION)
#endif
    {
   
        // Whoops, you've got an old version of the statfile...
        acutPrintf("\nWarning: Incompatible version of STATFILE.\n");
        fclose(statFile);
        return Adesk::kFalse;
    }
   
    // Read line containing Date File Created
    fscanf(statFile, "\n%[^\n]", createDate);

    // Read line containing Date File Last Modified
    fscanf(statFile, "\n%[^\n]", dummyString);

    // Read line containing LOGINNAME 
    fscanf(statFile, "\n%[^\n]", dummyString);


    // Read line containing AutoCAD serial number
    fscanf(statFile, "\n%[^\n]", dummyString);

    // Read line containing AutoCAD version
    fscanf(statFile, "\n%[^\n]", dummyString);
    fscanf(statFile, "%[\n]", dummyString);
       
    while (fscanf(statFile, "%s %i %le", cmdName, &cmdCount, &cmdElapsedTime)
           != EOF) {
        if (cumulativeStats->atPut(cmdName,
                                   new AsdkCommandRecord(cmdCount,
                                   cmdElapsedTime)))
            // Shake 'em up a little, but don't die over it.
            // But hell, this suggests sabatoge or stupidity...
            acutPrintf("\nCommand Statistics Error 1:  Duplicate Entry.\n");
    }
    fclose(statFile);
    return Adesk::kTrue;
}

void printCurrentDateTime(FILE* statFile)
{
    resbuf tempRes;
    int jtd_day;
    double jtd_msec;
    int ctd_year, ctd_month, ctd_day, ctd_hour, ctd_minute, ctd_second;
    double rem;
    long t, j, y, d;

    // Get Julian date and convert it to calendar time and date
    // As in Calendar Time and Date, in case you were wondering what
    // the "ctd_" prefix used pervasively in this routine stands for.
    if (acedGetVar(/*NOXLATE*/"DATE", &tempRes) != RTNORM) {
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 2",
                    PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    jtd_day = (int)tempRes.resval.rreal;
    jtd_msec = tempRes.resval.rreal - (int)tempRes.resval.rreal;
    j = jtd_day - 1721119L;
    t = 4 * j - 1;
    y = t / 146097L;
    j = t - 146097L * y;
    d = j / 4;
    j = (4 * d + 3) / 1461;
    d = (4 * d - 1461L * j + 7) / 4;
    ctd_month = (5 * d - 3) / 153;
    ctd_day = ((5 * d) - 3 - 153 * ctd_month + 5) / 5;
    ctd_year = (short)((100 * y) + j);
    if (ctd_month >= 10) {
        ctd_month -= 9;
        ctd_year++;
    } else
        ctd_month += 3;

    ctd_hour = (short)(jtd_msec * 24);
    rem = (jtd_msec * 24) - ctd_hour;
    ctd_minute = (short)(rem * 60);
    rem = (rem * 60) - ctd_minute;
    ctd_second = (short)(rem * 60);
    
    // print current date and time
    fprintf(statFile, "%0*d/%0*d/%0*d %0*d:%0*d:%0*d", 
            2, ctd_month,
            2, ctd_day,
            4, ctd_year,
            2, ctd_hour,
            2, ctd_minute,
            2, ctd_second);
}

Adesk::Boolean updateCumulativeStats()
{
    // If anything is going on in any document, now is NOT a good
    // time to accumulate stats, because each command/LISP expression
    // in progress has pointers into session stats.
    // This could be fixed with more recoding than I have time to do
    // now.  WCA 7/15/98
    for (int i = docData.length() - 1; i >= 0; i--) {
        // Make sure our info is up to date.
        if (docData[i].doc == curDocGlobals.doc)
            docData[i] = curDocGlobals;
        if ((docData[i].cmdIndex > 0) ||
            (docData[i].lispRcd != NULL))
            return Adesk::kFalse;
    }

    if (!readCumulativeStats()) {
        acutPrintf("\nWarning: Could not find Command Statistics file.\n");
        acutPrintf("Will try to create it.\n");
    }

    AcRxDictionaryIterator* iter;

    // Loop over current session stats, and merge them into cumulative stats.
    for (iter = sessionStats->newIterator(); !iter->done(); iter->next()) {
        AsdkCommandRecord* sessionCmdRcd = (AsdkCommandRecord*) iter->object();
        AsdkCommandRecord* cumulativeCmdRcd = (AsdkCommandRecord*)
                                          cumulativeStats->at(iter->key());
        if (!cumulativeCmdRcd)
            // First time, add it.
            cumulativeStats->atPut(iter->key(),
                                   new AsdkCommandRecord(sessionCmdRcd->count,
                                                     sessionCmdRcd->elapsedTime));
        else {
            // Not the first time, so bump it.
            cumulativeCmdRcd->count += sessionCmdRcd->count;
            cumulativeCmdRcd->elapsedTime += sessionCmdRcd->elapsedTime;
        }
    }

    delete iter;

    // Now that it has been added in, wipe out the current session Stats;
    delete sessionStats;
    sessionStats = initStatDictionary();

    // Open the cumulative stat file, creating it if necessary.
    char statFilePath[MAX_PATH_LENGTH];
    
    int ret = cmdcount_findfile(statFileName, statFilePath,true);
    assert(ret==RTNORM);//this should always succeed

    // Open the file
    FILE* statFile = fopen(statFilePath, /*NOXLATE*/"w");

    if (statFile == NULL) {
        // Bad permission in our chosen directory.  Give up.
        acedAlert("Warning: Could not create Command Statistics file.");
        return Adesk::kTrue;
    }

    // Print version number of STATFILE
    fprintf(statFile, "v%04.1f\n", STAT_FILENAME_VERSION);

    // Print create date of STATFILE
    if (!*createDate) {
        fprintf(statFile, "Created:               ");
        printCurrentDateTime(statFile);
        fprintf(statFile, "\n");
    } else
        fprintf(statFile, "%s\n", createDate);

    // Print date last modified for STATFILE
    fprintf(statFile, "Last Modified:         ");
    printCurrentDateTime(statFile);
    fprintf(statFile, "\n");
    
    resbuf tempRes;
    // Print LOGINNAME
    if (acedGetVar(/*NOXLATE*/"LOGINNAME", &tempRes) != RTNORM) {
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    fprintf(statFile, /*NOXLATE*/"LOGINNAME:             %s\n", tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;
    // Print ACAD serial number
    if (acedGetVar(/*NOXLATE*/"_PKSER", &tempRes) != RTNORM) {
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    fprintf(statFile, /*NOXLATE*/"%.*s Serial Number: %s\n", PRODUCTL, getProductName(),
                            tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;

    // Print ACAD version
    if (acedGetVar(/*NOXLATE*/"_VERNUM", &tempRes) != RTNORM) {
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    fprintf(statFile, /*NOXLATE*/"%.*s version:       %s\n", PRODUCTL, getProductName(),
                        tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;


    for (iter = cumulativeStats->newIterator(AcRx::kDictSorted); !iter->done(); iter->next()) {
        // Write out the command string.
        fprintf(statFile, "%s", iter->key());

        // Try for reasonable text alignment, such as allowing 24 chars
        // for the command name.  But have at least 1 space as a delimiter.
        int nbrOfSpaces = 24 - strlen(iter->key());
        do
            fprintf(statFile, " ");
        while (--nbrOfSpaces > 0);

        // Now the count and elapsed time in seconds (assume 1 billion seconds
        // maximum, which should exceed a typical beta survey period).
        fprintf(statFile, "%7i   %12.2f\n",
                ((AsdkCommandRecord*) iter->object())->count,
                ((AsdkCommandRecord*) iter->object())->elapsedTime);
    }

    fclose(statFile);

    delete iter;
    return Adesk::kTrue;
}

void printStats(AcRxDictionary* statDict) {
    AcRxDictionaryIterator* iter;
    
    acutPrintf("\n\nCommand                 Count     Elapsed Time\n");
    acutPrintf("----------------------  -------   ----------\n");
    for (iter = statDict->newIterator(AcRx::kDictSorted); !iter->done(); iter->next()) {
        // Write out the command string.
        acutPrintf("%s", iter->key());

    // Try for a little reasonable text alignment,
    // assuming 24 characters for a command or lisp name is sufficient.
    // But, we'll go to the MAX_CMD_LENGTH, plus one blank, if we must.
    int nbrOfSpaces = 24 - strlen(iter->key());
    do
        acutPrintf(" ");
    while (--nbrOfSpaces > 0);

        // Now the count, plus elapsed time, in primate-comprehensible form.
    int TempElapsedTime = (int)
                          (((AsdkCommandRecord*) iter->object())->elapsedTime);
    int hours = TempElapsedTime / 3600;
    int minutes = (TempElapsedTime % 3600) / 60;
    acutPrintf("%7i   %4d:%0*d:%0*.*f\n",
               ((AsdkCommandRecord*)iter->object())->count,
               hours,
               2, minutes,
               5, 2,
               ((AsdkCommandRecord*) iter->object())->elapsedTime
               - (hours * 3600) - (minutes * 60));
           
    }

    delete iter;
}


void commandStats() {

    char option_str[132];

    // specific prompt.
    acedInitGet(0, "Cumulative Session");

    option_str[0] = 'S';
    option_str[1] = '\0';

    switch (acedGetKword("\nCumulative/<Session>:", option_str)) {
        case RTKWORD:
            acedGetInput(option_str);
        /* Deliberate fallthrough */
        default:
            break;
    } 

    if (((option_str[0] == 'C') || (option_str[0] == 'c'))) {
        // record this command's duration now, so updateCumulativeStats will
        // wipe it out.  How this didn't cause continual crashes before is
        // beyond me.  WCA 7/15/98  After this call, the current doc command
        // stack should also be empty.
        recordCommandDuration(NULL);
        if (!updateCumulativeStats()) {
            acutPrintf("\nA Command or LISP expression is active");
            acutPrintf(" in at least one document,");
            acutPrintf("\nSession Statistics may not be printed or saved now.\n");
            return;
        }
        acutPrintf("\n\nCumulative Command Usage Statistics");
        printStats(cumulativeStats);
        acutPrintf("\nNOTE: Session Statistics have been recorded and reset.\n");
        delete cumulativeStats;
        cumulativeStats = NULL;
    } else {
        acutPrintf("\n\nCurrent Session Command Usage Statistics");
        printStats(sessionStats);
    }
}

//////**registry utility stuff for managing demand loading**
const TCHAR *
RegGetString(HKEY hKey, const TCHAR *subKey, const TCHAR *name)
{
    HKEY hSubKey;
    DWORD type;
    static TCHAR value[4096];
    DWORD size = sizeof(value);

    value[0] = '\0';
    if ( RegOpenKeyEx(hKey, subKey, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS )
    {
        if ( (RegQueryValueEx(hSubKey, name, 0, &type, (LPBYTE)value, &size) != ERROR_SUCCESS) ||
             (type != REG_SZ) )
            value[0] = '\0';
        RegCloseKey(hSubKey);
    }

    return value;
}

int
RegPutString(HKEY hKey, const TCHAR *subKey, const TCHAR *name, const TCHAR *value)
{
    HKEY hSubKey;
    DWORD disp;
    int retval = 0;

    if ( RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubKey, &disp) == ERROR_SUCCESS )
    {
        if ( RegSetValueEx(hSubKey, name, 0, REG_SZ, (LPBYTE)value, strlen(value) + 1) == ERROR_SUCCESS )
            retval = 1;
        RegCloseKey(hSubKey);
    }
    return retval;
}

int
RegGetInt(HKEY hKey, const TCHAR *subKey, const TCHAR *name)
{
    HKEY hSubKey;
    DWORD type;
    DWORD value = 0;
    DWORD size = sizeof(value);
    if ( RegOpenKeyEx(hKey, subKey, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS )
    {
        if ( (RegQueryValueEx(hSubKey, name, 0, &type, (LPBYTE)&value, &size) != ERROR_SUCCESS) ||
             (type != REG_DWORD) )
            value = 0;
        RegCloseKey(hSubKey);
    }
    return value;
}

int
RegPutInt(HKEY hKey, const TCHAR *subKey, const TCHAR *name, int value)
{
    HKEY hSubKey;
    DWORD disp;
    int retval = 0;
    if ( RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubKey, &disp) == ERROR_SUCCESS )
    {
        if ( RegSetValueEx(hSubKey, name, 0, REG_DWORD, (LPBYTE)&value, sizeof(value)) == ERROR_SUCCESS )
            retval = 1;
        RegCloseKey(hSubKey);
    }
    return retval;
}


// set whether the app loads on AutoCAD startup or not.
void setStartUpLoad(bool loadOnStartUp)
{
    char appKey[1024];
    wsprintf(appKey, "%s\\Applications\\%s", acrxProductKey(), gAppSubKey);
    //  register app
    int r = (AcadApp::kOnCommandInvocation | AcadApp::kOnLoadRequest);
    if (loadOnStartUp)
        r = (r | AcadApp::kOnAutoCADStartup);
    RegPutInt(HKEY_CURRENT_USER, appKey, _T("LOADCTRLS"), r);
}

// set whether the app loads on AutoCAD startup or not.
bool getStartUpLoad()
{
    char appKey[1024];
    wsprintf(appKey, "%s\\Applications\\%s", acrxProductKey(), gAppSubKey);
    return (0 != (AcadApp::kOnAutoCADStartup & RegGetInt(HKEY_CURRENT_USER, appKey, "LOADCTRLS")));
}


void updateRegistry()
{
    AcadAppInfo appInfo;
   
    appInfo.setAppName(gAppSubKey);
   
    appInfo.setModuleName(ads_getappname());

    CString appDesc(gAppSubKey);
    appDesc += kpszCmdModule;
    appInfo.setAppDesc(appDesc);

    int nLoadReasons = AcadApp::kOnAutoCADStartup
        | AcadApp::kOnCommandInvocation
        | AcadApp::kOnLoadRequest;

    appInfo.setLoadReason(AcadApp::LoadReasons(nLoadReasons));    

    appInfo.writeToRegistry(false,true);

    for (int i = 0; gCommands[i].strGlobal; i++)
    {
        appInfo.writeCommandNameToRegistry(gCommands[i].strGlobal, gCommands[i].strLocal);
    }

    CString groupName = _T(/*MSG0*/"ACAD_CMDCOUNT");
    appInfo.writeGroupNameToRegistry(groupName);
}

//use this command to control whether this app gets loaded on startup or not.
void cmdCommandCount()
{
    char reply[50];
    char prompt[255];
    sprintf(prompt, "\nLoad CmdCount on start up? <%s>: ", getStartUpLoad() ? "Y" : "N");
    //"Load command count on start up?"
    acedInitGet(0, "Yes No _ Yes No");
    if ( acedGetKword(prompt, reply) == RTNORM )
        setStartUpLoad(!strcmp(reply, "Yes"));
}

//********* Main Functions & Session Control

// commandStats:  Print out current Session and Cumulative Stats
void initStats()
{
    cmdr   = new AsdkCommandReactor();
    statFileName[0] = EOS;

    // Define dictionary to delete all its entries when it is deleted.
    sessionStats = initStatDictionary();
    acedEditor->addReactor(cmdr);
    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_COMMAND_STATS",
                            /*NOXLATE*/"ASDK_CMDSTAT",
                            "CMDSTAT",
                            ACRX_CMD_MODAL,
                            &commandStats);
    acedRegCmds->addCommand(/*NOXLATE*/"ASDK_COMMAND_STATS",
                            /*NOXLATE*/"ASDK_CMDCOUNT",
                            "CMDCOUNT",
                            ACRX_CMD_MODAL,
                            &cmdCommandCount);

    bStatsFileUpdatePending = Adesk::kFalse;

    // Initialize Global struct array
    docData.setLogicalLength(0);

    // Fill array from existing documents
    AcApDocumentIterator* pDocIter = acDocManager->newAcApDocumentIterator();

    for (;!pDocIter->done(); pDocIter->step())
        // add an entry for the document, if some other notification hasn't
        // already done so.
        lookupDoc(pDocIter->document());

    delete pDocIter;

    // Establish current document, if there is one yet.
    if ((docData.length() > 0) && (acDocManager->curDocument() != NULL))
        curDocGlobals = docData[lookupDoc(acDocManager->curDocument())];
    else
        curDocGlobals.doc = NULL;

    pDocReactor = new AsdkDocReactor;
    acDocManager->addReactor(pDocReactor);


    resbuf tempRes;
    int i, j;
    // set the statFileName to be <LOGINNAME>.txt
    // remove blanks and tabs from LOGINNAME, so we have a more 
    // reasonable statFileName.
    if (acedGetVar(/*NOXLATE*/"LOGINNAME", &tempRes) != RTNORM) {
        sprintf(abort_msg, "%.*s Command\nStatistics Gatherer\nFailure 1",
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    strcpy(statFileName, tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;
    for (i = 0, j = 0;
         (statFileName[i] != EOS) && (j < LOGINNAME_LENGTH);
         i++) {
        if ((statFileName[i] != ' ') && (statFileName[i] != '\t')) {
            statFileName[j] = statFileName[i];
            j++;
        }
    }
    statFileName[j] = EOS;
    strcat(statFileName, /*NOXLATE*/".txt");
}

void termStats()
{
    // If the current document is still valid, record what it was
    // last doing.  It should be gone, however.
    if (curDocGlobals.doc != NULL)
        pDocReactor->documentToBeDestroyed(curDocGlobals.doc);
    acDocManager->removeReactor(pDocReactor);
    delete pDocReactor;

    // Add 'em in, if you can.
    ::updateCumulativeStats();
    delete cumulativeStats;
    cumulativeStats = NULL;

    acedEditor->removeReactor(cmdr);
    delete cmdr;
    
    acedRegCmds->removeGroup(/*NOXLATE*/"ASDK_COMMAND_STATS");
}

TCHAR *getProductName( )
{
   /* Save the Product Name is a static variable, so that we only need
      to actually get it the first time we execute. */
   if (product[0] == NULL)  {
       struct resbuf result;
       if (acedGetVar(/*NOXLATE*/"PRODUCT", &result) != RTNORM) {
            /* If we can't get the "PRODUCT" name, assume "AutoCAD" */
            strcpy(product, /*NOXLATE*/"AutoCAD");
       } else {
            strcpy(product, result.resval.rstring); 
            acdbFree (result.resval.rstring) ;
       }
   }
   return product;  
}

/* Utility function to replace hardcoded references to acad.exe, acadnt.cfg, etc.
   Pass in the extension of the desired file and get back the product specific file name. */
TCHAR *getProgramFiles(TCHAR *ext)
{
    struct resbuf result;
    static char program[13];
    if (acedGetVar(/*NOXLATE*/"PROGRAM", &result) != RTNORM) {
        /* If we can't get the "PRODUCT" name, assume "acad" */
        sprintf(program, /*NOXLATE*/"acad%.*s", 8, ext);
    } else {
        sprintf(program, /*NOXLATE*/"%.*s%.*s", 4, result.resval.rstring, 8, ext);
        acdbFree (result.resval.rstring) ;
    }
    return program;    
}




/* =================== Arx Interface Functions ================ */
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pAppId) {
    switch(msg) {
        case AcRx::kInitAppMsg:
            // Tell system that we are MDI-aware.
            acrxDynamicLinker->registerAppMDIAware(pAppId);
            initStats();
            updateRegistry();
            break;
        case AcRx::kUnloadAppMsg:
            termStats();
        default:
        break;
    }
    return AcRx::kRetOK;
}

// Exports (API)

extern "C" void StartCountingCmd(const char* cmdStr)
{
    countCommand(cmdStr);
}

extern "C" void EndCountingCmd(const char* cmdStr)
{
    recordCommandDuration(cmdStr);
}
