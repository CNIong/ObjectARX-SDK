#ifndef ACPLPLOTLOGGER_H
#define ACPLPLOTLOGGER_H
//
//  (C) Copyright 2003-2006 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Interface for Plot Logging service.
//

class ADESK_NO_VTABLE AcPlPlotLogger
{
public:

    AcPlPlotLogger(){};
    virtual ~AcPlPlotLogger(){};

    // informs the logging service that a job has started
    virtual Acad::ErrorStatus startJob(void) = 0;

    // informs the logging service that a sheet within a job has started
    virtual Acad::ErrorStatus startSheet(void) = 0;

    // log a terminal error
    virtual Acad::ErrorStatus logTerminalError(const ACHAR *pErrorString) = 0;

    // log an Abort, Retry, Ignore error
    virtual Acad::ErrorStatus logARIError(const ACHAR *pErrorString) = 0;

    // log a severe error
    virtual Acad::ErrorStatus logSevereError(const ACHAR *pErrorString) = 0;

    // log an error
    virtual Acad::ErrorStatus logError(const ACHAR *pErrorString) = 0;

    // log a warning
    virtual Acad::ErrorStatus logWarning(const ACHAR *pWarningString) = 0;


    // log a message
    virtual Acad::ErrorStatus logMessage(const ACHAR *pMessageString) = 0;

    // log an informational message
    virtual Acad::ErrorStatus logInformation(const ACHAR *pMessageString) = 0;

    // informs the logging service that a sheet within a job has ended
    virtual Acad::ErrorStatus endSheet(void) = 0;

    // returns whether an error was logged during the sheet
    virtual bool errorHasHappenedInSheet(void) const = 0;

    // returns whether a warning was logged during the sheet
    virtual bool warningHasHappenedInSheet(void) const = 0;

    // informs the logging service that a job has ended
    virtual Acad::ErrorStatus endJob(void) = 0;

    // returns whether an error was logged during the job
    virtual bool errorHasHappenedInJob(void) const = 0;

    // returns whether a warning was logged during the job
    virtual bool warningHasHappenedInJob(void) const = 0;
};

#endif // ACPLPLOTLOGGER_H
