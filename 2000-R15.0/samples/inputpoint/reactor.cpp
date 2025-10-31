//   Copyright (C) 1998 by Autodesk, Inc.
//
//     Permission to use, copy, modify, and distribute this software
//     for any purpose is restricted by the VIP Subscription program
//     license agreement.  This application was developed exclusively
//     for distribution by the VIP subscription program and may not
//     be posted pubicly, modified, copied, or distributed by any other
//     methods. 
//
//     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
//     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
//     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
//     UNINTERRUPTED OR ERROR FREE.
//
//     Use, duplication, or disclosure by the U.S. Government is subject to 
//     restrictions set forth in FAR 52.227-19 (Commercial Computer 
//     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
//     (Rights in Technical Data and Computer Software), as applicable. 
//

// AsdkInputContextReactor methods
//

#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"

#include "reactor.h"

void
AsdkInputContextReactor::beginGetPoint(const AcGePoint3d* pointIn,
                               const char* promptString,
                               int   initGetFlags,
                               const char* pKeywords)
{
    acutPrintf( "\nbeginGetPoint:");
    if ( pointIn )
        acutPrintf( "\nin: %.2f, %.2f, %.2f", pointIn[X], pointIn[Y], pointIn[Z] );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetPoint(Acad::PromptStatus returnStatus,
                             const AcGePoint3d& pointOut,
                             const char*& pKeyword)
{
    acutPrintf( "\nendGetPoint:\nstatus %d\nout: %.2f, %.2f, %.2f", returnStatus, pointOut[X], pointOut[Y], pointOut[Z] );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}


void
AsdkInputContextReactor::beginGetAngle(const AcGePoint3d* pointIn,
                               const char* promptString,
                               int   initGetFlags,
                               const char* pKeywords)
{
    acutPrintf( "\nbeginGetAngle:" );
    if ( pointIn )
        acutPrintf( "\nin: %.2f, %.2f, %.2f", pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetAngle(Acad::PromptStatus returnStatus,
                             double& angle,
                             const char*& pKeyword)
{
    acutPrintf( "\nendGetAngle:\nstatus %d\nangle: %.4f", returnStatus, angle );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetDistance(const AcGePoint3d* pointIn,
                                  const char* promptString,
                                  int   initGetFlags,
                                  const char* pKeywords)
{
    acutPrintf( "\nbeginGetDistance:" );
    if ( pointIn )
        acutPrintf( "\nin: %.2f, %.2f, %.2f", pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const char*& pKeyword)
{
    acutPrintf( "\nendGetDistance:\nstatus %d\ndistance: %.4f", returnStatus, distance );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetOrientation(const AcGePoint3d* pointIn,
                                     const char* promptString,
                                     int   initGetFlags,
                                     const char* pKeywords)
{
    acutPrintf( "\nbeginGetOrientation:" );
    if ( pointIn )
        acutPrintf( "\nin: %.2f, %.2f, %.2f", pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetOrientation(Acad::PromptStatus returnStatus,
                                   double& angle,
                                   const char*& pKeyword)
{
    acutPrintf( "\nendGetOrientation:\nstatus %d\ndistance: %.4f", returnStatus, angle );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetCorner(const AcGePoint3d* firstCorner,
                                const char* promptString,
                                int   initGetFlags,
                                const char* pKeywords)
{
    acutPrintf( "\nbeginGetCorner:" );
    if ( firstCorner )
        acutPrintf( "\nfirst: %.2f, %.2f, %.2f", firstCorner->x, firstCorner->y, firstCorner->z );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}
    
void
AsdkInputContextReactor::endGetCorner(Acad::PromptStatus returnStatus,
                              AcGePoint3d& secondCorner,
                              const char*& pKeyword)
{
    acutPrintf( "\nendGetCorner:\nstatus %d\nsecond: %.2f, %.2f, %.2f",
        returnStatus, secondCorner[X], secondCorner[Y], secondCorner[Z] );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetScaleFactor(const AcGePoint3d* pointIn,
                                     const char* promptString,
                                     int   initGetFlags,
                                     const char* pKeywords)
{
    acutPrintf( "\nbeginGetScaleFactor:" );
    if ( pointIn )
        acutPrintf( "\nin: %.2f, %.2f, %.2f", pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetScaleFactor(Acad::PromptStatus returnStatus,
                                   double& distance,
                                   const char*& pKeyword)
{
    acutPrintf( "\nendGetScaleFactor:\nstatus %d\ndistance: %.4f", returnStatus, distance );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetString(const char* promptString,
                                int   initGetFlags)
{
    acutPrintf( "\nbeginGetString:" );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetString (Acad::PromptStatus returnStatus,
                               const char*& pString)
{
    acutPrintf( "\nendGetString:\nstatus %d", returnStatus );
    if ( pString )
        acutPrintf( "\nstring: \"%s\"", pString );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetKeyword(const char* promptString,
                                 int   initGetFlags,
                                 const char* pKeywords)
{
    acutPrintf( "\nbeginGetKeyword:" );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetKeyword (Acad::PromptStatus returnStatus,
                                const char*& pKeyword)
{
    acutPrintf( "\nendGetKeyword:\nstatus: %d", returnStatus );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetInteger(const int* dfault,
                                const char* promptString,
                                int   initGetFlags,
                                const char* pKeywords)
{
    acutPrintf( "\nbeginGetInteger:" );
    if ( dfault )
        acutPrintf( "\ndefault: %d", dfault );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetInteger(Acad::PromptStatus returnStatus,
                               int& retValue,
                               const char*& pKeyword)
{
    acutPrintf( "\nendGetInteger:\nstatus: %d\ninteger: %d", returnStatus, retValue );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetColor(const int* dfault,
                               const char* promptString,
                               int   initGetFlags,
                               const char* pKeywords)
{
    acutPrintf( "\nbeginGetColor:" );
    if ( dfault )
        acutPrintf( "\ndefault: %d", dfault );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetColor(Acad::PromptStatus returnStatus,
                             int& retValue,
                             const char*& pKeyword)
{
    acutPrintf( "\nendGetColor:\nstatus: %d\ninteger: %d", returnStatus, retValue );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginGetReal(const double* dfault,
                              const char* promptString,
                              int   initGetFlags,
                              const char* pKeywords)
{
    acutPrintf( "\nbeginGetReal:" );
    if ( dfault )
        acutPrintf( "\ndefault: %d", dfault );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endGetReal(Acad::PromptStatus returnStatus,
                            double& returnValue,
                            const char*& pKeyword)
{
    acutPrintf( "\nendGetReal:\nstatus: %d\ninteger: %d", returnStatus, returnValue );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginEntsel(const char* promptString,
                             int   initGetFlags,
                             const char* pKeywords)
{
    acutPrintf( "\nbeginEntsel:" );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endEntsel(Acad::PromptStatus returnStatus,
                           AcDbObjectId& entPicked,
                           AcGePoint3d& pickPoint,
                           const char* pKeyword)
{
    acutPrintf( "\nendEntsel:\nstatus: %d\nentity: <%x>\npick: %.2f, %.2f, %.2f",
        returnStatus, entPicked.asOldId(), pickPoint[X], pickPoint[Y], pickPoint[Z] );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginNentsel(const char*    promptString,
                              Adesk::Boolean pickFlag,
                              int            initGetFlags,
                              const char*    pKeywords)
{
    acutPrintf( "\nbeginNentsel:" );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\npickflag %d, initget %d", pickFlag, initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endNentsel(Acad::PromptStatus returnStatus,
                            AcDbObjectId entPicked,
                            const AcGePoint3d&  pickPoint,
                            const AcGeMatrix3d& xform,
                            const resbuf* referenceStack,
                            const char*   pKeyword)
{
    acutPrintf( "\nendNentsel:\nstatus: %d\nentity: <%x>\npick: %.2f, %.2f, %.2f",
        returnStatus, entPicked.asOldId(), pickPoint[X], pickPoint[Y], pickPoint[Z] );
    if ( pKeyword )
        acutPrintf( "\nkeyword: %s", pKeyword );
    acutPrintf( " (also xform & ref stack)" );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::beginSSGet(const char*  pPrompt,
                            int          initGetFlags,
                            const char*  pKeywords,
                            const char*  pSSControls,
                            const AcArray<AcGePoint3d>& points,
                            const resbuf*               entMask)
{
    acutPrintf( "\nbeginSSGet:" );
    if ( pPrompt )
        acutPrintf( "\nprompt: \"%s\"", pPrompt );
    acutPrintf( "\ninitget %d", initGetFlags );
    if ( pKeywords )
        acutPrintf( "\nkeywords: \"%s\"", pKeywords );
    if ( pSSControls )
        acutPrintf( "\nSS controls: \"%s\"", pSSControls );
    acutPrintf( " (also points & entMask)" );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endSSGet(Acad::PromptStatus returnStatus,
                          const AcArray<AcDbObjectId>& ss)
{
    acutPrintf( "\nendSSGet:\nstatus: %d\narray of %d object IDs\n", returnStatus, ss.length() );
}
                    
void
AsdkInputContextReactor::beginDragSequence(const char*  promptString)
{
    acutPrintf( "\nbeginDragSequence:" );
    if ( promptString )
        acutPrintf( "\nprompt: \"%s\"", promptString );
    acutPrintf( "\n" );
}

void
AsdkInputContextReactor::endDragSequence(Acad::PromptStatus returnStatus,
                                 AcGePoint3d&  pickPoint,
                                 AcGeVector3d& vec)
{
    acutPrintf( "\nendDragSequence:\nstatus: %d\npick: %.2f, %.2f, %.2f, vec: %.2f, %.2f, %.2f\n",
        returnStatus, pickPoint[X], pickPoint[Y], pickPoint[Z], vec[X], vec[Y], vec[Z] );
}

void
AsdkInputContextReactor::beginQuiescentState()
{
    acutPrintf( "\nbeginQuiescentState\n" );
}

void
AsdkInputContextReactor::endQuiescentState()
{
    acutPrintf( "\nendQuiescentState\n" );
}
