//

/*
   Copyright (C) 1997-2007 by Autodesk, Inc.
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

  ========================

  v01.7 Randy Kintzley 4/2005
   - Added a "flags" column to the data output...
     The flags column is a bitmask indicating additional detail about how 
     the command was invoked. i.e. menu, lisp, script, transparent...etc.
     Flags are #defined below.
     The command name alone is no longer unique within the file. A given
     command name may appear various times in the file with different flags.
     The combination of command name and flags can be treated as the 
     "primary key" for the table.
   - Changed output filename handling.
     The output filename now includes the date in the name and changes once 
     a week automatically.
     Also; we no longer search the AutoCAD path for the file since this
     caused some confusion among users. If the path location is explicitly 
     set in the reg, then we use it. Otherwise, we use "My Documents".
   - Bumped file version number from 1.3 to 1.4
*/

/* Unicode: Text File Output 
TODO: this module writes output to an external text file. After unicode conversion, now it writes 
to this file in UTF-16 format (16-bit chars). We might want to write them as UTF-8, which is 
a little more compact. This issue needs to be confirmed later. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif
#include <aced.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "adslib.h"
#include "rxobject.h"
#include "rxdict.h"
#include "rxkernel.h"
#include "rxditer.h"

#include "adesk.h"
#include "dbmain.h"
#include "dbsymtb.h"
#include "dbidmap.h"
#include "dbents.h"
#include "dbidar.h"

#include "acdocman.h"
#include <appinfo.h>
#include "AdAChar.h"
#include <map>

#include "AcCrtFILEWrappers.h"
#include "Ac64BitHelpers.h"

static const ACHAR *kpszCmdModule = ACRX_T(/*MSG0*/" Command Module");  // MDI Safeb

static struct
{
    const ACHAR *strGlobal;        // string for globalized command name
    const ACHAR *strLocal;        // string for localized command name
} gCommands[] =
    {
        {ACRX_T(/*MSG0*/"CMDSTAT"),     ACRX_T("CMDSTAT")   },
        {ACRX_T(/*MSG0*/"CMDCOUNT"),    ACRX_T("CMDCOUNT")  },
        {NULL,                  NULL        }
    };


const ACHAR* gAppSubKey = ACRX_T("AcadCmdCount");
const ACHAR* gAppFileName = ACRX_T("CmdCount.arx");
// Forward declarations

class AsdkCommandReactor;
Adesk::Boolean updateCumulativeStats();
ACHAR *getProductName();
ACHAR *getProgramFiles(ACHAR *ext);

class AsdkCommandSubRecord : public AcRxObject
{
  public:
    int count;
    double elapsedTime;     // Including tenths of seconds.
    AsdkCommandSubRecord();
};

AsdkCommandSubRecord::AsdkCommandSubRecord()
  : count(0)
  , elapsedTime(0)
{  }

//********* AsdkCommandRecord --  Simple AcRxObject stored in stat dictionaries
//                                to maintain statistics.

class AsdkCommandRecord : public AcRxObject
{
    typedef std::map<int, AsdkCommandSubRecord> SubRecordMap;
public:
    void add(int flags, int count, double time);
    void add(const AsdkCommandRecord* record);

    void write(LPCTSTR cmdName, AcFILE& statFilem);

    int count() const;
    double elapsedTime() const;     // Including tenths of seconds.

protected:
    SubRecordMap m_subRecords;
};


int AsdkCommandRecord::count() const
{
    int n = 0;
    for (SubRecordMap::const_iterator iter = m_subRecords.begin(); iter != m_subRecords.end(); iter++)
        n += iter->second.count;
    return n;
}

double AsdkCommandRecord::elapsedTime() const
{
    double t = 0;
    for (SubRecordMap::const_iterator iter = m_subRecords.begin(); iter != m_subRecords.end(); iter++)
        t += iter->second.elapsedTime;
    return t;
}

void AsdkCommandRecord::add(int flags, int count, double time)
{
    AsdkCommandSubRecord& subRecord = m_subRecords[flags]; // locate or create the needed subrecord.
    subRecord.count += count;
    subRecord.elapsedTime += time;
}

void AsdkCommandRecord::add(const AsdkCommandRecord* record)
{
    if (record == NULL)
        return;
    for (SubRecordMap::const_iterator iter = record->m_subRecords.begin(); 
            iter != record->m_subRecords.end(); 
            iter++) 
    {
        int flags = iter->first;
        const AsdkCommandSubRecord& subRecord = iter->second;
        add(flags, subRecord.count, subRecord.elapsedTime); //call overloaded version above
    }
}

void AsdkCommandRecord::write(LPCTSTR cmdName, AcFILE& statFile)
{
    if (!statFile.isOpen() || (cmdName == NULL) || (cmdName[0] == _T('\0')))
        return;

    for (SubRecordMap::iterator iter = m_subRecords.begin(); iter != m_subRecords.end(); iter++) {
        int flags = iter->first;
        AsdkCommandSubRecord& subRecord = iter->second;
        // Write out the command string.
        statFile.fprintf(_T(/*MSG0*/"%s\t%d\t%7i\t%12.2f\n"), cmdName, flags, subRecord.count, subRecord.elapsedTime);
    }
}

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
#define STAT_FILENAME_VERSION    1.4  // Version of statistics file format
#define VERSION_LENGTH           100  // Length of version string
#define LOGINNAME_LENGTH        1024  // Length of LOGINNAME that we use.

#define BASE_DATE            2453450  // this is: 3/20/2005 (a sunday)

// cmd active flags
#define CMDSTATE_REGULAR      0x00001;
#define CMDSTATE_TRANSPARENT  0x00002;
#define CMDSTATE_SCRIPT       0x00004;
#define CMDSTATE_DIALOG       0x00008;
#define CMDSTATE_DDE          0x00010;
#define CMDSTATE_LISP         0x00020;
#define CMDSTATE_ARX          0x00040;
                                       // additional flags
#define CMDSTATE_MENU         0x01000; //
#define CMDSTATE_MANUAL       0x02000; // this bit is set when it looks like a human invoked the command

const TCHAR* acedGetSetvarVarname(); // defined in command.cpp
// defined in rxmfcapi.cpp - (exported but not published)
DWORD       acedCommandActive();         // direct access to CMDACTIVE sysvar (avoided getvar for speed reasons)
BOOL        acedManualInputProvided(AcApDocument* pAcTargetDocument); // last token was provided by a carbon based life form
BOOL        acedMenuInputProvided();

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

static ACHAR product[PRODUCTL] = {NULL};  // MDI-Safe
static ACHAR abort_msg[255];              // MDI-Safe

//********* AsdkCommandReactor --  Command Event Notification class

class AsdkCommandReactor : public AcEditorReactor {

  public:

    virtual void commandWillStart(const ACHAR * cmdStr);
    virtual void commandEnded(const ACHAR * cmdStr);
    virtual void commandCancelled(const ACHAR * cmdStr);
    virtual void commandFailed(const ACHAR * cmdStr);

    virtual void lispWillStart(const ACHAR * firstLine);
    virtual void lispEnded();
    virtual void lispCancelled();

    virtual void beginSave(AcDbDatabase* pDwg, const ACHAR* pIntendedName);

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
  
AsdkCommandRecord* bumpCount(const TCHAR* cmdStr, int flags, Adesk::Boolean positive)
{
    AsdkCommandRecord* cmdRcd = (AsdkCommandRecord*) sessionStats->at(cmdStr);
    if (cmdRcd == NULL) {
        // here is where we create the official command stat entry names, so
        // we apply da rules here:
        // 1)  Keep it short
        // 2) first blank or tab termintates the string.
        ACHAR truncatedStr[MAX_CMD_LENGTH + 1];
        if (_tcslen(cmdStr) > MAX_CMD_LENGTH) {
            _tcsncpy(truncatedStr, cmdStr, MAX_CMD_LENGTH);
            truncatedStr[MAX_CMD_LENGTH] = EOS;   // Not all implementations
                                                  //  of strncpy() add the 
                                                  // EOS.
        } else
            _tcscpy(truncatedStr, cmdStr);
        // Truncate string at first blank or tab.
        ACHAR* blankChar = _tcschr(truncatedStr, ACRX_T(' '));
        if (blankChar)
            *blankChar = EOS;
        /* Now look for a TAB character. */
        blankChar = _tcschr(truncatedStr, ACRX_T('\t'));
        if (blankChar)
            *blankChar = EOS;
        
        cmdRcd = (AsdkCommandRecord*)sessionStats->at(truncatedStr); // try again to locate it
        if (cmdRcd == NULL) {
            cmdRcd = new AsdkCommandRecord();
            if (cmdRcd == NULL)
                return NULL;
            sessionStats->atPut(truncatedStr, cmdRcd);
        }
    }

    int offset = (positive) ? 1 : -1;
    cmdRcd->add(flags, offset, 0.0); 

    return cmdRcd;
}

// GETcURtIME:  return double representing Julian Date, values of which
//              may be directly subtracted for elapsed time measurement.
double getCurTime()
{
    resbuf currentTime;

    if (acedGetVar(ACRX_T(/*NOXLATE*/"DATE"), &currentTime) != RTNORM) {
        // This should never happen.
        _stprintf(abort_msg, ACRX_T("%.*s Command\nStatistics Gatherer\nFailure 1"),
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
    long               cmdFlags[MAX_CMD_DEPTH];

    // LISP is its own, non-reentrant, beast.
    AsdkCommandRecord* lispRcd;
    double             lispStartTime;
    long               lispFlags;
};

AsdkCmdCountDocData::AsdkCmdCountDocData()
    : doc(NULL)
    , cmdIndex(0)
    , lispRcd(NULL)
    , lispStartTime(0)
    , lispFlags(0)
{
}


AsdkCmdCountDocData::AsdkCmdCountDocData(const AsdkCmdCountDocData& src)
{
    operator=(src);
}

AsdkCmdCountDocData& AsdkCmdCountDocData::operator=(const AsdkCmdCountDocData& src)
{
    doc = src.doc;

    cmdIndex = src.cmdIndex;
    int i;
    for (i = 0; i < cmdIndex; i++) {
        cmdRcd[i] = src.cmdRcd[i];
        cmdStartTime[i] = src.cmdStartTime[i];
        cmdFlags[i] = src.cmdFlags[i];
    }
    lispRcd = src.lispRcd;
    lispStartTime = src.lispStartTime;
    lispFlags = src.lispFlags;
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
static ACHAR createDate[DATE_TIME_LENGTH + 1]; // MDI-Safe
// Name of stat file.  "+5" means one for EOS, four for .txt
static ACHAR statFileName[LOGINNAME_LENGTH + 5];  // MDI-Safe


void recordElapsedCmdTime(AsdkCommandRecord*& commandRecord, double startTime, int flags)
{
    commandRecord->add(flags, 
                        0, 
                        elapsedTimeInSeconds(getCurTime(), startTime));
}

int getCurrentStateFlags()
{
    //cmd active flags
    int flags = acedCommandActive();

    if (acedMenuInputProvided())
        flags |= CMDSTATE_MENU;

    if (acedManualInputProvided(curDoc()))
        flags |= CMDSTATE_MANUAL;

    return flags;
}

void countCommand(const ACHAR* cmdStr)
{
    // Can't handle zero-doc
    if (curDocGlobals.doc == NULL)
        return;

    // If nesting a command, record the time spent in the pushed command, and
    // stop counting it.
    if (curDocGlobals.cmdIndex > 0)
        recordElapsedCmdTime(curDocGlobals.cmdRcd[curDocGlobals.cmdIndex - 1],
                             curDocGlobals.cmdStartTime[curDocGlobals.cmdIndex - 1],
                             curDocGlobals.cmdFlags[curDocGlobals.cmdIndex - 1]
                             );
    int flags = getCurrentStateFlags();
    curDocGlobals.cmdRcd[curDocGlobals.cmdIndex] = bumpCount(cmdStr, flags, Adesk::kTrue);
    curDocGlobals.cmdFlags[curDocGlobals.cmdIndex] = flags;
    curDocGlobals.cmdStartTime[curDocGlobals.cmdIndex] = getCurTime();
    curDocGlobals.cmdIndex++;

}

void AsdkCommandReactor::commandWillStart(const ACHAR* cmdStr)
{
    countCommand(cmdStr);
}

int lookupDoc(AcApDocument* pDoc);

void AsdkCmdCountDocData::recordAndPop()
{
    cmdIndex--;

    // Record the time spent in the ended command
    recordElapsedCmdTime(cmdRcd[cmdIndex],
                         cmdStartTime[cmdIndex],
                         cmdFlags[cmdIndex]
                         );
    // restart the clock in the suspended command, if there is one.
    if (cmdIndex > 0)
        cmdStartTime[cmdIndex - 1] = getCurTime();
}

void recordCommandDuration(const ACHAR* pszCmdStr)
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

void AsdkCommandReactor::commandEnded(const ACHAR* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::commandCancelled(const ACHAR* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::commandFailed(const ACHAR* pszCmdStr)
{
    recordCommandDuration(pszCmdStr);
}

void AsdkCommandReactor::lispWillStart(const ACHAR* firstLine)
{
    int flags = getCurrentStateFlags() | CMDSTATE_LISP;
    curDocGlobals.lispRcd = bumpCount(firstLine, flags, Adesk::kTrue);
    curDocGlobals.lispFlags = flags;
    curDocGlobals.lispStartTime = getCurTime();
}

void AsdkCommandReactor::lispEnded()
{
    if (curDocGlobals.lispRcd != NULL)
        recordElapsedCmdTime(curDocGlobals.lispRcd, curDocGlobals.lispStartTime, curDocGlobals.lispFlags); 
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

void AsdkCommandReactor::beginSave(AcDbDatabase* pDwg, const ACHAR* pIntendedName)
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
        bumpCount(ACRX_T(/*NOXLATE*/"#DOC_ACTIVATED(SAME)"), getCurrentStateFlags(), Adesk::kTrue);
    else {
        // If switching documents, record the time spent on the
        // current document's active command/lisp and reset the
        // start time in the new document's active command/lisp.
        int i;
        if (curDocGlobals.doc != NULL) {
            if ((i = curDocGlobals.cmdIndex - 1) >= 0)
                recordElapsedCmdTime(curDocGlobals.cmdRcd[i],
                                     curDocGlobals.cmdStartTime[i],
                                     curDocGlobals.cmdFlags[i]);
            if (curDocGlobals.lispRcd != NULL)
                recordElapsedCmdTime(curDocGlobals.lispRcd,
                                     curDocGlobals.lispStartTime,
                                     curDocGlobals.lispFlags);
            docData[lookupDoc(curDocGlobals.doc)] = curDocGlobals;
        }
        if (pDoc == NULL) {
            // This isn't supposed to happen...
            assert(pDoc!=NULL);
            // But in production, just log it and keep going...
            bumpCount(ACRX_T(/*NOXLATE*/"#NULL_DOC_ACTIVATED"), getCurrentStateFlags(), Adesk::kTrue);
            curDocGlobals.doc = NULL;
            return;
        }
        curDocGlobals = (docData[lookupDoc(pDoc)]);
        double currentTime = getCurTime();
        if ((i = curDocGlobals.cmdIndex - 1) >= 0)
            curDocGlobals.cmdStartTime[i] = currentTime;
        curDocGlobals.lispStartTime = currentTime;
        bumpCount(ACRX_T(/*NOXLATE*/"#DOC_SWITCHED"), getCurrentStateFlags(), Adesk::kTrue);
    }
}

void
AsdkDocReactor::documentToBeDestroyed(AcApDocument *pDoc)
{
    if (pDoc == NULL) {
        // This isn't supposed to happen...
        assert(pDoc!=NULL);
        // But in production, just log it and keep going...
        bumpCount(ACRX_T(/*NOXLATE*/"#NULL_DOC_DESTROYED"), getCurrentStateFlags(), Adesk::kTrue);
        return;
    }
    int i = lookupDoc(pDoc);
    // The current document being destroyed?
    if (pDoc == curDocGlobals.doc) {
        // If Anything is still active in the document being destroyed,
        // log it as done now.
        if (curDocGlobals.lispRcd != NULL) {
            recordElapsedCmdTime(curDocGlobals.lispRcd, 
                                curDocGlobals.lispStartTime, 
                                curDocGlobals.lispFlags);
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
    bumpCount(ACRX_T(/*NOXLATE*/"#DOC_CREATED"), getCurrentStateFlags(), Adesk::kTrue);

    // add an entry for the document, if some other notification hasn't
    // already done so.
    lookupDoc(pDoc);
}

static AsdkDocReactor* pDocReactor;

//********* Utility Functions


// return filename of the form:
//  <loginname>_yyyy_mm_dd.txt
// ...where the date portion changes once every seven days.
// Note: We no longer search the AutoCAD path due to confusion 
//       among customers. (per Shaan Hurley request)
// 
LPCTSTR cmdcount_filename()
{
    static CString csFilename;

    CString csLogin;
    resbuf tempRes;
    tempRes.rbnext = NULL;
    if (acedGetVar(ACRX_T(/*NOXLATE*/"LOGINNAME"), &tempRes) == RTNORM) {
        csLogin = tempRes.resval.rstring;
        csLogin.Replace(ACRX_T(/*NOXLATE*/" "), ACRX_T(/*NOXLATE*/"")); // remove spaces and tabs.
        csLogin.Replace(ACRX_T(/*NOXLATE*/"\t"), ACRX_T(/*NOXLATE*/""));
    }
    else
        csLogin = ACRX_T(/*NOXLATE*/"Unknown");

    CString csDate;
    tempRes.restype = RTREAL;
    if (acedGetVar(_T(/*MSG0*/"DATE"), &tempRes) == RTNORM) {
        //gotta do some date voodoo... (just need year, month and day)
        int today = (int)tempRes.resval.rreal;
        int filedate = BASE_DATE + (((int)((today - BASE_DATE) / 7.0)) * 7); // round to chunks of 7 days.
        int a;
        if (filedate < 2299161)
           a = filedate;
        else {
            int alpha = (int)((filedate - 1867216.25) / 36524.25);    // Gregorian calendar
            a = (filedate + 1 + alpha) - (int)(alpha / 4);
        }

        int b = a + 1524;
        int c = (int)((b - 122.1) / 365.25);
        int d = (int)(365.25 * c);
        int e = (int)((b - d) / 30.6001);
        int m = (int)(e - ((e < 14) ? 1 : 13));
        int day = (int)(b - d - ((int)(30.6001 * e)));
        int y = (int)(c - ((m > 2) ? 4716 : 4715));
        csDate.Format(ACRX_T(/*NOXLATE*/"%0*d-%0*d-%0*d"), 4, y, 2, m, 2, day);
    }

    CString csFilePath;
    CString csRegPath;
    csRegPath.Format(ACRX_T(/*NOXLATE*/"%s\\Applications\\AcadCmdCount"), acrxProductKey());
    HKEY hKey;
    if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,csRegPath,0,KEY_QUERY_VALUE,&hKey)) {

        DWORD dwType = 0;
        DWORD dwDataSize = MAX_STR_LENGTH * sizeof(TCHAR);
        RegQueryValueEx(hKey, ACRX_T(/*NOXLATE*/"StatPath"), NULL, &dwType, (LPBYTE)csFilePath.GetBuffer(dwDataSize/sizeof(TCHAR)), &dwDataSize);
        csFilePath.ReleaseBuffer();
        RegCloseKey(hKey);
    }
    if (csFilePath.IsEmpty()) {
        //nothing found in reg so use "My Documents"
        resbuf rb;
        if (acedGetVar(ACRX_T(/*NOXLATE*/"MYDOCUMENTSPREFIX"), &rb) == RTNORM) {
            csFilePath = rb.resval.rstring;
            acdbFree(rb.resval.rstring);
        }
    }
    csFilePath.TrimRight(ACRX_T(/*NOXLATE*/"\\"));

    csFilename.Format(ACRX_T(/*NOXLATE*/"%s\\%s_%s.txt"), csFilePath, csLogin, csDate);
    return csFilename;
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
    AcFILE statFile;
    statFile.fopen(cmdcount_filename(), ACRX_T(/*NOXLATE*/"r"));
    if (!statFile.isOpen()) {
        *createDate = NULL;
        return Adesk::kFalse; // Most likely, it hasn't been created yet.
                              // one other likely reason is 
                              // that another process has it open for write,
                              // but we're talkin' a millisecond window...
    }

    ACHAR cmdName[MAX_CMD_LENGTH + 1 /*for the EOS*/ ];
    int cmdCount;
    double cmdElapsedTime;

    ACHAR dummyString[MAX_STR_LENGTH + 1];
    ACHAR newline[MAX_STR_LENGTH + 1];

    ACHAR versionString[VERSION_LENGTH + 1];
    
    // Read line containing STAT_FILENAME_VERSION
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("%s"), versionString);

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
    ACHAR stat_buf[10];
    _stprintf(stat_buf, ACRX_T("v0%1.1f"), STAT_FILENAME_VERSION);
    if (_tcscmp(versionString, stat_buf) != 0)
#else
    if (  (  (versionString[1] - ACRX_T('0')) * 10.0
           + (versionString[2] - ACRX_T('0'))
           + (versionString[4] - ACRX_T('0')) / 10.0)
        != STAT_FILENAME_VERSION)
#endif
    {
   
        // Whoops, you've got an old version of the statfile...
        acutPrintf(ACRX_T("\nWarning: Incompatible version of STATFILE.\n"));
        statFile.fclose();
        return Adesk::kFalse;
    }
   
    // Read line containing Date File Created
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("\n%[^\n]"), createDate);

    // Read line containing Date File Last Modified
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("\n%[^\n]"), dummyString);

    // Read line containing LOGINNAME 
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("\n%[^\n]"), dummyString);

    // Read line containing AutoCAD serial number
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("\n%[^\n]"), dummyString);

    // Read line containing AutoCAD version
    statFile.fgets(newline, MAX_STR_LENGTH);
    _stscanf(newline, ACRX_T("\n%[^\n]"), dummyString);

    int flags;
    while (statFile.fgets(newline, MAX_STR_LENGTH) != NULL)
    {
        _stscanf(newline, ACRX_T("%s %i %i %le"), cmdName, &flags, &cmdCount, &cmdElapsedTime);
        
        // get the record for this command, or create it on the fly if needed.
        // then add the data: flags, count, time
        AsdkCommandRecord* pRecord = (AsdkCommandRecord*)cumulativeStats->at(cmdName);
        if (pRecord == NULL) {
            pRecord = new AsdkCommandRecord();
            if (pRecord == NULL)
                break;
            cumulativeStats->atPut(cmdName, pRecord);
        }
        pRecord->add(flags, cmdCount, cmdElapsedTime);
    }
    statFile.fclose();
    return Adesk::kTrue;
}

void printCurrentDateTime(AcFILE& statFile)
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
    if (acedGetVar(ACRX_T(/*NOXLATE*/"DATE"), &tempRes) != RTNORM) {
        _stprintf(abort_msg, ACRX_T("%.*s Command\nStatistics Gatherer\nFailure 2"),
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
    statFile.fprintf(ACRX_T("%0*d/%0*d/%0*d %0*d:%0*d:%0*d"), 
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
        acutPrintf(ACRX_T("\nWarning: Could not find Command Statistics file.\n"));
        acutPrintf(ACRX_T("Will try to create it.\n"));
    }

    AcRxDictionaryIterator* iter;

    // Loop over current session stats, and merge them into cumulative stats.
    for (iter = sessionStats->newIterator(); !iter->done(); iter->next()) {
        AsdkCommandRecord* sessionCmdRcd = (AsdkCommandRecord*) iter->object();
        AsdkCommandRecord* cumulativeCmdRcd = (AsdkCommandRecord*)
                                          cumulativeStats->at(iter->key());
        if (!cumulativeCmdRcd) {
            // First time, add it.
            cumulativeCmdRcd = new AsdkCommandRecord();
            cumulativeStats->atPut(iter->key(), cumulativeCmdRcd);
        }
        // add the values
        cumulativeCmdRcd->add(sessionCmdRcd);
    }

    delete iter;

    // Now that it has been added in, wipe out the current session Stats;
    delete sessionStats;
    sessionStats = initStatDictionary();

    // Open the cumulative stat file, creating it if necessary.
    ACHAR statFilePath[MAX_PATH_LENGTH];
    
    _tcscpy(statFilePath, cmdcount_filename());
    assert(_tcslen(statFilePath) > 0);//this should always succeed

    // Open the file
    AcFILE statFile;
    statFile.fopen(statFilePath, ACRX_T(/*NOXLATE*/"w"));

    if (!statFile.isOpen()) {
        // Bad permission in our chosen directory.  Give up.
        acedAlert(ACRX_T(/*MSGO*/"Warning: Could not create Command Statistics file."));
        return Adesk::kTrue;
    }

    // Print version number of STATFILE
    statFile.fprintf(ACRX_T(/*MSGO*/"v%04.1f\n"), STAT_FILENAME_VERSION);

    // Print create date of STATFILE
    if (!*createDate) {
        statFile.fprintf(ACRX_T(/*MSGO*/"Created:               "));
        printCurrentDateTime(statFile);
        statFile.fprintf(ACRX_T(/*MSGO*/"\n"));
    } else
        statFile.fprintf(ACRX_T(/*MSGO*/"%s\n"), createDate);

    // Print date last modified for STATFILE
    statFile.fprintf(ACRX_T(/*MSGO*/"Last Modified:         "));
    printCurrentDateTime(statFile);
    statFile.fprintf(ACRX_T(/*MSGO*/"\n"));
    
    resbuf tempRes;
    // Print LOGINNAME
    if (acedGetVar(ACRX_T(/*NOXLATE*/"LOGINNAME"), &tempRes) != RTNORM) {
        _stprintf(abort_msg, ACRX_T("%.*s Command\nStatistics Gatherer\nFailure 1"),
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    statFile.fprintf(ACRX_T(/*NOXLATE*/"LOGINNAME:             %s\n"), tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;
    // Print ACAD serial number
    if (acedGetVar(ACRX_T(/*NOXLATE*/"_PKSER"), &tempRes) != RTNORM) {
        _stprintf(abort_msg, ACRX_T("%.*s Command\nStatistics Gatherer\nFailure 1"),
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    statFile.fprintf(ACRX_T(/*NOXLATE*/"%.*s Serial Number: %s\n"), PRODUCTL, getProductName(),
                            tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;

    // Print ACAD version
    if (acedGetVar(ACRX_T(/*NOXLATE*/"_VERNUM"), &tempRes) != RTNORM) {
        _stprintf(abort_msg, ACRX_T("%.*s Command\nStatistics Gatherer\nFailure 1"),
                PRODUCTL, getProductName());
        acrx_abort(abort_msg);
    }
    statFile.fprintf(ACRX_T(/*NOXLATE*/"%.*s version:       %s\n"), PRODUCTL, getProductName(),
                        tempRes.resval.rstring);
    acdbFree (tempRes.resval.rstring) ;


    for (iter = cumulativeStats->newIterator(AcRx::kDictSorted); !iter->done(); iter->next()) {
        AsdkCommandRecord* pRec = ((AsdkCommandRecord*) iter->object());
        if (pRec != NULL)
            pRec->write(iter->key(), statFile);
    }

    statFile.fclose();

    delete iter;
    return Adesk::kTrue;
}

void printStats(AcRxDictionary* statDict) {
    AcRxDictionaryIterator* iter;
    
    acutPrintf(ACRX_T("\n\nCommand                 Count     Elapsed Time\n"));
    acutPrintf(ACRX_T("----------------------  -------   ----------\n"));
    for (iter = statDict->newIterator(AcRx::kDictSorted); !iter->done(); iter->next()) {
        // Write out the command string.
        acutPrintf(ACRX_T("%s"), iter->key());

        // Try for a little reasonable text alignment,
        // assuming 24 characters for a command or lisp name is sufficient.
        // But, we'll go to the MAX_CMD_LENGTH, plus one blank, if we must.
        int nbrOfSpaces = 24 - _tcslen(iter->key());
        do
            acutPrintf(ACRX_T(" "));
        while (--nbrOfSpaces > 0);

        AsdkCommandRecord* pRecord = (AsdkCommandRecord*)iter->object();
        if (pRecord == NULL)
            break;
        // Now the count, plus elapsed time, in primate-comprehensible form.
        double eTime = pRecord->elapsedTime();
        int TempElapsedTime = (int)eTime;
        int hours = TempElapsedTime / 3600;
        int minutes = (TempElapsedTime % 3600) / 60;
        acutPrintf(ACRX_T(/*MSG0*/"%7i   %4d:%0*d:%0*.*f\n"),
                    pRecord->count(),
                    hours,
                    2, minutes,
                    5, 2,
                    eTime
                    - (hours * 3600) - (minutes * 60));

    }

    delete iter;
}


void commandStats() {

    ACHAR option_str[132];

    // specific prompt.
    acedInitGet(0, ACRX_T(/*MSGO*/"Cumulative Session"));

    option_str[0] = ACRX_T('S');
    option_str[1] = ACRX_T('\0');

    switch (acedGetKword(ACRX_T(/*MSGO*/"\nCumulative/<Session>:"), option_str)) {
        case RTKWORD:
            acedGetInput(option_str);
        /* Deliberate fallthrough */
        default:
            break;
    } 

    if (((option_str[0] == ACRX_T('C')) || (option_str[0] == ACRX_T('c')))) {
        // record this command's duration now, so updateCumulativeStats will
        // wipe it out.  How this didn't cause continual crashes before is
        // beyond me.  WCA 7/15/98  After this call, the current doc command
        // stack should also be empty.
        recordCommandDuration(NULL);
        if (!updateCumulativeStats()) {
            acutPrintf(ACRX_T(/*MSGO*/"\nA Command or LISP expression is active"));
            acutPrintf(ACRX_T(/*MSGO*/" in at least one document,"));
            acutPrintf(ACRX_T(/*MSGO*/"\nSession Statistics may not be printed or saved now.\n"));
            return;
        }
        acutPrintf(ACRX_T(/*MSGO*/"\n\nCumulative Command Usage Statistics"));
        printStats(cumulativeStats);
        acutPrintf(ACRX_T(/*MSGO*/"\nNOTE: Session Statistics have been recorded and reset.\n"));
        delete cumulativeStats;
        cumulativeStats = NULL;
    } else {
        acutPrintf(ACRX_T(/*MSGO*/"\n\nCurrent Session Command Usage Statistics"));
        printStats(sessionStats);
    }
}

//////**registry utility stuff for managing demand loading**
const ACHAR *
RegGetString(HKEY hKey, const ACHAR *subKey, const ACHAR *name)
{
    HKEY hSubKey;
    DWORD type;
    static ACHAR value[4096];
    DWORD size = sizeof(value);

    value[0] = ACRX_T('\0');
    if ( RegOpenKeyEx(hKey, subKey, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS )
    {
        if ( (RegQueryValueEx(hSubKey, name, 0, &type, (LPBYTE)value, &size) != ERROR_SUCCESS) ||
             (type != REG_SZ) )
            value[0] = ACRX_T('\0');
        RegCloseKey(hSubKey);
    }

    return value;
}

int
RegPutString(HKEY hKey, const ACHAR *subKey, const ACHAR *name, const ACHAR *value)
{
    HKEY hSubKey;
    DWORD disp;
    int retval = 0;

    if ( RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubKey, &disp) == ERROR_SUCCESS )
    {
        if ( RegSetValueEx(hSubKey, name, 0, REG_SZ, (LPBYTE)value, (_tcslen(value) + 1) * sizeof(TCHAR)) == ERROR_SUCCESS )
            retval = 1;
        RegCloseKey(hSubKey);
    }
    return retval;
}

int
RegGetInt(HKEY hKey, const ACHAR *subKey, const ACHAR *name)
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
RegPutInt(HKEY hKey, const ACHAR *subKey, const ACHAR *name, int value)
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
    ACHAR appKey[1024];
    wsprintf(appKey, ACRX_T(/*MSGO*/"%s\\Applications\\%s"), acrxProductKey(), gAppSubKey);
    //  register app
    int r = (AcadApp::kOnCommandInvocation | AcadApp::kOnLoadRequest);
    if (loadOnStartUp)
        r = (r | AcadApp::kOnAutoCADStartup);
    RegPutInt(HKEY_CURRENT_USER, appKey, ACRX_T(/*MSGO*/"LOADCTRLS"), r);
}

// set whether the app loads on AutoCAD startup or not.
bool getStartUpLoad()
{
    ACHAR appKey[1024];
    wsprintf(appKey, ACRX_T(/*MSGO*/"%s\\Applications\\%s"), acrxProductKey(), gAppSubKey);
    return (0 != (AcadApp::kOnAutoCADStartup & RegGetInt(HKEY_CURRENT_USER, appKey, ACRX_T(/*MSGO*/"LOADCTRLS"))));
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

    CString groupName = ACRX_T(/*MSG0*/"ACAD_CMDCOUNT");
    appInfo.writeGroupNameToRegistry(groupName);
}

//use this command to control whether this app gets loaded on startup or not.
void cmdCommandCount()
{
    ACHAR reply[50];
    ACHAR prompt[255];
    _stprintf(prompt, ACRX_T("\nLoad CmdCount on start up? <%s>: "), getStartUpLoad() ? _T("Y") : _T("N"));
    //"Load command count on start up?"
    acedInitGet(0, ACRX_T("Yes No _ Yes No"));
    if ( acedGetKword(prompt, reply) == RTNORM )
        setStartUpLoad(!_tcscmp(reply, ACRX_T("Yes")));
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
    acedRegCmds->addCommand(ACRX_T(/*NOXLATE*/"ASDK_COMMAND_STATS"),
                            ACRX_T(/*NOXLATE*/"ASDK_CMDSTAT"),
                            ACRX_T("CMDSTAT"),
                            ACRX_CMD_MODAL,
                            &commandStats);
    acedRegCmds->addCommand(ACRX_T(/*NOXLATE*/"ASDK_COMMAND_STATS"),
                            ACRX_T(/*NOXLATE*/"ASDK_CMDCOUNT"),
                            ACRX_T("CMDCOUNT"),
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
    
    acedRegCmds->removeGroup(ACRX_T(/*NOXLATE*/"ASDK_COMMAND_STATS"));
}

ACHAR *getProductName( )
{
   /* Save the Product Name is a static variable, so that we only need
      to actually get it the first time we execute. */
   if (product[0] == NULL)  {
       struct resbuf result;
       if (acedGetVar(ACRX_T(/*NOXLATE*/"PRODUCT"), &result) != RTNORM) {
            /* If we can't get the "PRODUCT" name, assume "AutoCAD" */
            _tcscpy(product, ACRX_T(/*NOXLATE*/"AutoCAD"));
       } else {
            _tcscpy(product, result.resval.rstring); 
            acdbFree (result.resval.rstring) ;
       }
   }
   return product;  
}

/* Utility function to replace hardcoded references to acad.exe, acadnt.cfg, etc.
   Pass in the extension of the desired file and get back the product specific file name. */
ACHAR *getProgramFiles(ACHAR *ext)
{
    struct resbuf result;
    static ACHAR program[13];
    if (acedGetVar(ACRX_T(/*NOXLATE*/"PROGRAM"), &result) != RTNORM) {
        /* If we can't get the "PRODUCT" name, assume "acad" */
        _stprintf(program, ACRX_T(/*NOXLATE*/"acad%.*s"), 8, ext);
    } else {
        _stprintf(program, ACRX_T(/*NOXLATE*/"%.*s%.*s"), 4, result.resval.rstring, 8, ext);
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

extern "C" void StartCountingCmd(const ACHAR* cmdStr)
{
    countCommand(cmdStr);
}

extern "C" void EndCountingCmd(const ACHAR* cmdStr)
{
    recordCommandDuration(cmdStr);
}
