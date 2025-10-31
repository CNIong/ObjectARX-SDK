//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ACPLPLOTLOGGINGERRORHANDLER_H
#define ACPLPLOTLOGGINGERRORHANDLER_H

class AcPlPlotLogger;
class AcPlSystenInternals;

class AcPlPlotLoggingErrorHandler : public AcPlPlotErrorHandler
{
public:
    ACPL_PORT AcPlPlotLoggingErrorHandler();
    ACPL_PORT AcPlPlotLoggingErrorHandler(AcPlPlotLogger *);
    ACPL_PORT ~AcPlPlotLoggingErrorHandler();

    ACPL_DECLARE_MEMBERS(AcPlPlotLoggingErrorHandler);

public:

    ACPL_PORT void infoMessage(const ACHAR *pMessage) override;

    ACPL_PORT int messageBox(
        const ACHAR *pText, 
        const ACHAR *pCaption,
        unsigned int uType, 
        int defaultReturn) override;

    //info error handler.
    ACPL_PORT void info(
        ACPL_ULONG_PTR category, 
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    //warning error handler.
    ACPL_PORT ErrorResult warning(
        ACPL_ULONG_PTR category, 
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    //Severe handler
    ACPL_PORT void severeError(
        ACPL_ULONG_PTR category, 
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    //Error handler
    ACPL_PORT ErrorResult error(
        ACPL_ULONG_PTR category,
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    //Abort/Retry/Ignore handler
    ACPL_PORT ErrorResult ariError(
        ACPL_ULONG_PTR category,
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    // Terminal error handler
    ACPL_PORT void terminalError(
        ACPL_ULONG_PTR category,
        const unsigned int specific,
        const ACHAR *      pLocation,
        const ACHAR *      pContextData,
        const ACHAR *      pRevision) override;

    // log a message to the log file
    ACPL_PORT void logMessage(const ACHAR *pTitle, const ACHAR *pMsg) override;

};

#endif // ACPLPLOTLOGGINGERRORHANDLER_H
