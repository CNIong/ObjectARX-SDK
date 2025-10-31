#ifndef ACPLPLOTLOGGINGERRORHANDLER_H
#define ACPLPLOTLOGGINGERRORHANDLER_H
//
//  (C) Copyright 2003-2007 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Interface for Plot Logging Error Handler.
//

class AcPlPlotLogger;
class AcPlSystenInternals;

class AcPlPlotLoggingErrorHandler : public AcPlPlotErrorHandler
{
public:
    ACPL_PORT AcPlPlotLoggingErrorHandler();
    ACPL_PORT AcPlPlotLoggingErrorHandler(AcPlPlotLogger *);
    ACPL_PORT virtual ~AcPlPlotLoggingErrorHandler();

    ACPL_DECLARE_MEMBERS(AcPlPlotLoggingErrorHandler);

public:

    ACPL_PORT virtual void infoMessage(const ACHAR *pMessage);

    ACPL_PORT virtual int messageBox(const ACHAR *pText, 
                                     const ACHAR *pCaption,
                                     unsigned int uType, 
                                     int defaultReturn);

    //info error handler.
    ACPL_PORT virtual void info(ULONG_PTR category, 
                                const unsigned int specific,
                                const ACHAR *pLocation, 
                                const ACHAR *pContextData,
                                const ACHAR *pRevision);

    //warning error handler.
    ACPL_PORT virtual ErrorResult warning(ULONG_PTR category, 
                                          const unsigned int specific,
                                          const ACHAR *pLocation,
                                          const ACHAR *pContextData, 
                                          const ACHAR *pRevision);

    //Severe handler
    ACPL_PORT virtual void severeError(ULONG_PTR category, 
                                       const unsigned int specific, 
                                       const ACHAR *pLocation, 
                                       const ACHAR *pContextData, 
                                       const ACHAR *pRevision);

    //Error handler
    ACPL_PORT virtual ErrorResult error(ULONG_PTR category,
                                        const unsigned int specific, 
                                        const ACHAR *pLocation, 
                                        const ACHAR *pContextData, 
                                        const ACHAR *pRevision);

    //Abort/Retry/Ignore handler
    ACPL_PORT virtual ErrorResult ariError(ULONG_PTR category,
                                           const unsigned int specific,
                                           const ACHAR *pLocation,
                                           const ACHAR *pContextData,
                                           const ACHAR *pRevision);

    // Terminal error handler
    ACPL_PORT virtual void terminalError(ULONG_PTR category,
                                         const unsigned int specific,
                                         const ACHAR *pLocation,
                                         const ACHAR *pContextData,
                                         const ACHAR *pRevision);

    // log a message to the log file
    ACPL_PORT virtual void logMessage(const ACHAR *pTitle, const ACHAR *pMsg);

};

#endif // ACPLPLOTLOGGINGERRORHANDLER_H
