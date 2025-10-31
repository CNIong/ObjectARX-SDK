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

class AsdkInputPointFilter : public AcEdInputPointFilter
{
public:
    AsdkInputPointFilter(){ m_changePoint = false; };

    virtual Acad::ErrorStatus processInputPoint(
          bool&                        changedPoint,
          AcGePoint3d&                 newPoint,
          bool&                        displayOsnapGlyph,
          bool&                        changedTooltipStr,
          TCHAR*&                       newTooltipString,

          bool&                        retry,
          AcGiViewportDraw*           pDrawContext,

          AcApDocument*              document,

          bool                       pointComputed,

          int                        history,

          const AcGePoint3d&               lastPoint,

          const AcGePoint3d&               rawPoint,

          const AcGePoint3d&               grippedPoint,

          const AcGePoint3d&               cartesianSnappedPoint,

          const AcGePoint3d&               osnappedPoint,
          AcDb::OsnapMask                  osnapMasks,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
          AcDb::OsnapMask                     osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,

          const AcArray<AcDbObjectId>&     pickedEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedPickedEntities,
          const AcArray<int>&              gsSelectionMark, // of 0th element in
                                                            // pickedEntities
          // AutoSnap Info:
          const AcArray<AcDbObjectId>&     keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedKeyPointEntities,
          const AcArray<int>&                        keyPointGsSelectionMark,
          const AcArray<AcGeCurve3d*>&       alignmentPaths,

          const AcGePoint3d&               computedPoint,

          const TCHAR*                      tooltipString);

    // Non-standard protocol
    //
    void enableChanges(){ m_changePoint = true; };
    void disableChanges(){ m_changePoint = false; };

private:
    bool m_changePoint;

};
