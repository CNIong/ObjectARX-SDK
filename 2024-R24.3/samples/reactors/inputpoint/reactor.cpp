//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// AsdkInputContextReactor methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _MSC_VER
#include <Windows.h>
#endif
#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "tchar.h"

#include "reactor.h"



void
AsdkInputContextReactor::beginGetPoint(const AcGePoint3d* pointIn,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetPoint:"));
    if ( pointIn )
        acutPrintf( _T("\nin: %.2f, %.2f, %.2f"), pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetPoint(Acad::PromptStatus returnStatus,
                             const AcGePoint3d& pointOut,
                             const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetPoint:\nstatus %d\nout: %.2f, %.2f, %.2f"), returnStatus, pointOut[X], pointOut[Y], pointOut[Z] );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}


void
AsdkInputContextReactor::beginGetAngle(const AcGePoint3d* pointIn,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetAngle:") );
    if ( pointIn )
        acutPrintf( _T("\nin: %.2f, %.2f, %.2f"), pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetAngle(Acad::PromptStatus returnStatus,
                             double& angle,
                             const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetAngle:\nstatus %d\nangle: %.4f"), returnStatus, angle );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetDistance(const AcGePoint3d* pointIn,
                                  const TCHAR* promptString,
                                  int   initGetFlags,
                                  const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetDistance:") );
    if ( pointIn )
        acutPrintf( _T("\nin: %.2f, %.2f, %.2f"), pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetDistance:\nstatus %d\ndistance: %.4f"), returnStatus, distance );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetOrientation(const AcGePoint3d* pointIn,
                                     const TCHAR* promptString,
                                     int   initGetFlags,
                                     const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetOrientation:") );
    if ( pointIn )
        acutPrintf( _T("\nin: %.2f, %.2f, %.2f"), pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetOrientation(Acad::PromptStatus returnStatus,
                                   double& angle,
                                   const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetOrientation:\nstatus %d\ndistance: %.4f"), returnStatus, angle );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetCorner(const AcGePoint3d* firstCorner,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetCorner:") );
    if ( firstCorner )
        acutPrintf( _T("\nfirst: %.2f, %.2f, %.2f"), firstCorner->x, firstCorner->y, firstCorner->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}
    
void
AsdkInputContextReactor::endGetCorner(Acad::PromptStatus returnStatus,
                              AcGePoint3d& secondCorner,
                              const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetCorner:\nstatus %d\nsecond: %.2f, %.2f, %.2f"),
        returnStatus, secondCorner[X], secondCorner[Y], secondCorner[Z] );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetScaleFactor(const AcGePoint3d* pointIn,
                                     const TCHAR* promptString,
                                     int   initGetFlags,
                                     const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetScaleFactor:") );
    if ( pointIn )
        acutPrintf( _T("\nin: %.2f, %.2f, %.2f"), pointIn->x, pointIn->y, pointIn->z );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetScaleFactor(Acad::PromptStatus returnStatus,
                                   double& distance,
                                   const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetScaleFactor:\nstatus %d\ndistance: %.4f"), returnStatus, distance );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetString(const TCHAR* promptString,
                                int   initGetFlags)
{
    acutPrintf( _T("\nbeginGetString:") );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetString (Acad::PromptStatus returnStatus,
                               TCHAR* pString)
{
    acutPrintf( _T("\nendGetString:\nstatus %d"), returnStatus );
    if ( pString )
        acutPrintf( _T("\nstring: \"%s\""), pString );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetKeyword(const TCHAR* promptString,
                                 int   initGetFlags,
                                 const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetKeyword:") );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetKeyword (Acad::PromptStatus returnStatus,
                                const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetKeyword:\nstatus: %d"), returnStatus );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetInteger(const int* dfault,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetInteger:") );
    if ( dfault )
        acutPrintf( _T("\ndefault: %d"), dfault );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetInteger(Acad::PromptStatus returnStatus,
                               int& retValue,
                               const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetInteger:\nstatus: %d\ninteger: %d"), returnStatus, retValue );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetColor(const int* dfault,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetColor:") );
    if ( dfault )
        acutPrintf( _T("\ndefault: %d"), dfault );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetColor(Acad::PromptStatus returnStatus,
                             int& retValue,
                             const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetColor:\nstatus: %d\ninteger: %d"), returnStatus, retValue );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginGetReal(const double* dfault,
                              const TCHAR* promptString,
                              int   initGetFlags,
                              const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginGetReal:") );
    if ( dfault )
        acutPrintf( _T("\ndefault: %d"), dfault );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endGetReal(Acad::PromptStatus returnStatus,
                            double& returnValue,
                            const TCHAR*& pKeyword)
{
    acutPrintf( _T("\nendGetReal:\nstatus: %d\ninteger: %d"), returnStatus, returnValue );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginEntsel(const TCHAR* promptString,
                             int   initGetFlags,
                             const TCHAR* pKeywords)
{
    acutPrintf( _T("\nbeginEntsel:") );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endEntsel(Acad::PromptStatus returnStatus,
                           AcDbObjectId& entPicked,
                           AcGePoint3d& pickPoint,
                           const TCHAR* pKeyword)
{
    acutPrintf( _T("\nendEntsel:\nstatus: %d\nentity: <%x>\npick: %.2f, %.2f, %.2f"),
        returnStatus, entPicked.asOldId(), pickPoint[X], pickPoint[Y], pickPoint[Z] );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginNentsel(const TCHAR*    promptString,
                              Adesk::Boolean pickFlag,
                              int            initGetFlags,
                              const TCHAR*    pKeywords)
{
    acutPrintf( _T("\nbeginNentsel:") );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\npickflag %d, initget %d"), pickFlag, initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endNentsel(Acad::PromptStatus returnStatus,
                            AcDbObjectId entPicked,
                            const AcGePoint3d&  pickPoint,
                            const AcGeMatrix3d& xform,
                            const resbuf* referenceStack,
                            const TCHAR*   pKeyword)
{
    acutPrintf( _T("\nendNentsel:\nstatus: %d\nentity: <%x>\npick: %.2f, %.2f, %.2f"),
        returnStatus, entPicked.asOldId(), pickPoint[X], pickPoint[Y], pickPoint[Z] );
    if ( pKeyword )
        acutPrintf( _T("\nkeyword: %s"), pKeyword );
    acutPrintf( _T(" (also xform & ref stack)") );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::beginSSGet(const TCHAR*  pPrompt,
                            int          initGetFlags,
                            const TCHAR*  pKeywords,
                            const TCHAR*  pSSControls,
                            const AcArray<AcGePoint3d>& points,
                            const resbuf*               entMask)
{
    acutPrintf( _T("\nbeginSSGet:") );
    if ( pPrompt )
        acutPrintf( _T("\nprompt: \"%s\""), pPrompt );
    acutPrintf( _T("\ninitget %d"), initGetFlags );
    if ( pKeywords )
        acutPrintf( _T("\nkeywords: \"%s\""), pKeywords );
    if ( pSSControls )
        acutPrintf( _T("\nSS controls: \"%s\""), pSSControls );
    acutPrintf( _T(" (also points & entMask)") );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endSSGet(Acad::PromptStatus returnStatus,
                          const AcArray<AcDbObjectId>& ss)
{
    acutPrintf( _T("\nendSSGet:\nstatus: %d\narray of %d object IDs\n"), returnStatus, ss.length() );
}
                    
void
AsdkInputContextReactor::beginDragSequence(const TCHAR*  promptString)
{
    acutPrintf( _T("\nbeginDragSequence:") );
    if ( promptString )
        acutPrintf( _T("\nprompt: \"%s\""), promptString );
    acutPrintf( _T("\n") );
}

void
AsdkInputContextReactor::endDragSequence(Acad::PromptStatus returnStatus,
                                 AcGePoint3d&  pickPoint,
                                 AcGeVector3d& vec)
{
    acutPrintf( _T("\nendDragSequence:\nstatus: %d\npick: %.2f, %.2f, %.2f, vec: %.2f, %.2f, %.2f\n"),
        returnStatus, pickPoint[X], pickPoint[Y], pickPoint[Z], vec[X], vec[Y], vec[Z] );
}

void
AsdkInputContextReactor::beginQuiescentState()
{
    acutPrintf( _T("\nbeginQuiescentState\n") );
}

void
AsdkInputContextReactor::endQuiescentState()
{
    acutPrintf( _T("\nendQuiescentState\n") );
}
