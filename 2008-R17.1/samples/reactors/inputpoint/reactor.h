//   Copyright (C) 1998-2006 by Autodesk, Inc.
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

#include "acedinpt.h"

class AsdkInputContextReactor : public AcEdInputContextReactor
{
public:
    virtual void beginGetPoint(const AcGePoint3d* pointIn,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords);

    virtual void endGetPoint(Acad::PromptStatus returnStatus,
                             const AcGePoint3d& pointOut,
                             const TCHAR*& pKeyword);

    virtual void beginGetAngle(const AcGePoint3d* pointIn,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords);

    virtual void endGetAngle(Acad::PromptStatus returnStatus,
                             double& angle,
                             const TCHAR*& pKeyword);

    virtual void beginGetDistance(const AcGePoint3d* pointIn,
                                  const TCHAR* promptString,
                                  int   initGetFlags,
                                  const TCHAR* pKeywords);

    virtual void endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const TCHAR*& pKeyword);

    virtual void beginGetOrientation(const AcGePoint3d* pointIn,
                                     const TCHAR* promptString,
                                     int   initGetFlags,
                                     const TCHAR* pKeywords);

    virtual void endGetOrientation(Acad::PromptStatus returnStatus,
                                   double& angle,
                                   const TCHAR*& pKeyword);

    virtual void beginGetCorner(const AcGePoint3d* firstCorner,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords);
    
    virtual void endGetCorner(Acad::PromptStatus returnStatus,
                              AcGePoint3d& secondCorner,
                              const TCHAR*& pKeyword);

    virtual void beginGetScaleFactor(const AcGePoint3d* pointIn,
                                     const TCHAR* promptString,
                                     int   initGetFlags,
                                     const TCHAR* pKeywords);

    virtual void endGetScaleFactor(Acad::PromptStatus returnStatus,
                                   double& distance,
                                   const TCHAR*& pKeyword);

    virtual void beginGetString(const TCHAR* promptString,
                                int   initGetFlags);

    virtual void endGetString (Acad::PromptStatus returnStatus,
                               TCHAR* pString);

    virtual void beginGetKeyword(const TCHAR* promptString,
                                 int   initGetFlags,
                                 const TCHAR* pKeywords);

    virtual void endGetKeyword (Acad::PromptStatus returnStatus,
                                const TCHAR*& pKeyword);

    virtual void beginGetInteger(const int* dfault,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords);

    virtual void endGetInteger(Acad::PromptStatus returnStatus,
                               int& retValue,
                               const TCHAR*& pKeyword);

    virtual void beginGetColor(const int* dfault,
                               const TCHAR* promptString,
                               int   initGetFlags,
                               const TCHAR* pKeywords);

    virtual void endGetColor(Acad::PromptStatus returnStatus,
                             int& retValue,
                             const TCHAR*& pKeyword);

    virtual void beginGetReal(const double* dfault,
                              const TCHAR* promptString,
                              int   initGetFlags,
                              const TCHAR* pKeywords);

    virtual void endGetReal(Acad::PromptStatus returnStatus,
                            double& returnValue,
                            const TCHAR*& pKeyword);

    virtual void beginEntsel(const TCHAR* promptString,
                             int   initGetFlags,
                             const TCHAR* pKeywords);

    virtual void endEntsel(Acad::PromptStatus returnStatus,
                           AcDbObjectId& entPicked,
                           AcGePoint3d& pickPoint,
                           const TCHAR* pKeyword);

    virtual void beginNentsel(const TCHAR*    promptString,
                              Adesk::Boolean pickFlag,
                              int            initGetFlags,
                              const TCHAR*    pKeywords);

    virtual void endNentsel(Acad::PromptStatus returnStatus,
                            AcDbObjectId entPicked,
                            const AcGePoint3d&  pickPoint,
                            const AcGeMatrix3d& xform,
                            const resbuf* referenceStack,
                            const TCHAR*   pKeyword);

    virtual void beginSSGet(const TCHAR*  pPrompt,
                            int          initGetFlags,
                            const TCHAR*  pKeywords,
                            const TCHAR*  pSSControls,
                            const AcArray<AcGePoint3d>& points,
                            const resbuf*               entMask);

    virtual void endSSGet(Acad::PromptStatus returnStatus,
                          const AcArray<AcDbObjectId>& ss);
                    
    virtual void beginDragSequence(const TCHAR*  promptString);

    virtual void endDragSequence(Acad::PromptStatus returnStatus,
                                 AcGePoint3d&  pickPoint,
                                 AcGeVector3d& vec);

    virtual void beginQuiescentState();

    virtual void endQuiescentState();
};
