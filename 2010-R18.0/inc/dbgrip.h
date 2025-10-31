#ifndef AD_DBGRIP_H
#define AD_DBGRIP_H
//
// (C) Copyright 2002-2009 by Autodesk, Inc.
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

#include "acdb.h"
#include "acarray.h"
#include "dbDimData.h"

class AcGiViewport;
class AcDbEntity;
class AcDbGripData;
class AcGiWorldDraw;
class AcGiViewportDraw;
class AcDbCustomOsnapMode;

namespace AcDbGripOperations {
    enum ReturnValue {
        eOk         = 0,
        eFailure,
        eNoRedrawGrip,
        eGripHotToWarm,
        eGetNewGripPoints
    };

    enum DrawType {
        kWarmGrip  = 0,
        kHoverGrip,
        kHotGrip,
        kDragImageGrip
    };

    enum GripStatus {
        kGripStart = 0,
        kGripEnd,
        kGripAbort,
        kStretch,
        kMove,
        kRotate,
        kScale,
        kMirror,
        kDimFocusChanged,
        kPopUpMenu
    };

    enum GripFlags {
        kSkipWhenShared           = 0x1,
        kDisableRubberBandLine    = 0x2,
        kDisableModeKeywords      = 0x4,
        kDrawAtDragImageGripPoint = 0x8,
        kTriggerGrip              = 0x10,
        kTurnOnForcedPick         = 0x20,
        kMapGripHotToRtClk        = 0x40,
        kGizmosEnabled            = 0x80,
        kGripIsPerViewport        = 0x100,
        kGripEditTip              = 0x200, // INTERNAL USE ONLY
    };

    enum GripContextFlags {
        kSharedGrip    = 0x1,
        kMultiHotGrip  = 0x2
    };

    enum GetGripPointsFlags {
        kGripPointsOnly = 0x1,
        kCyclableGripsOnly = 0x02,
        kDynamicDimMode = 0x04
    };

    // The following are used by the moveGripPointsAt() bitflags parameter,
    // and refer to how the offset parameter was determined.
    enum MoveGripPointsFlags {
        kOsnapped                = 0x1,  // offset is result of osnap
        kPolar                   = 0x2,  // offset is result of polar
        kOtrack                  = 0x4,  // offset is result of otrack
        kZdir                    = 0x8,  // offset polar or otrack value is in Z direction
        kKeyboard                = 0x10  // offset is result of keyboard entry
    };

};

typedef AcArray<AcDbGripData*, AcArrayMemCopyReallocator<AcDbGripData*> > AcDbGripDataPtrArray;
typedef AcArray<AcDbGripData, AcArrayObjectCopyReallocator<AcDbGripData> > AcDbGripDataArray;

typedef AcDbGripOperations::ReturnValue (*GripOperationPtr)(AcDbGripData* pThis,
    const AcDbObjectId& entId, int contextFlags);

typedef void (*ContextMenuItemIndexPtr)(unsigned int itemIndex);

typedef AcDbGripOperations::ReturnValue (*GripRtClkHandler)(AcDbGripDataArray& hotGrips,
    const AcDbObjectIdArray& ents, ACHAR *& menuName, HMENU& menu,
    ContextMenuItemIndexPtr& cb);

typedef bool (*GripWorldDrawPtr)(AcDbGripData* pThis, AcGiWorldDraw* pWd,
    const AcDbObjectId& entId, AcDbGripOperations::DrawType type,
    AcGePoint3d* imageGripPoint, double dGripSize);

typedef void (*GripViewportDrawPtr)(AcDbGripData* pThis, AcGiViewportDraw* pWd,
    const AcDbObjectId& entId, AcDbGripOperations::DrawType type,
    AcGePoint3d* imageGripPoint, int gripSize);

typedef void (*GripOpStatusPtr)(AcDbGripData* pThis, const AcDbObjectId& entId,
    AcDbGripOperations::GripStatus stat);

typedef const ACHAR * (*GripToolTipPtr)(AcDbGripData* pThis);

typedef void (*GripDimensionPtr)(AcDbGripData* pThis, const AcDbObjectId& entId,
    double dimScale, AcDbDimDataPtrArray& dimData); 

typedef AcDbGripOperations::ReturnValue (*GripInputPointPtr)(
    AcDbGripData* pThis, const AcDbObjectId& entId, bool& changedPoint,
    AcGePoint3d& newPoint, const AcGiViewport& viewContext,
    const AcDbObjectId& viewportId, bool pointComputed, int history,
    const AcGePoint3d& lastPoint, const AcGePoint3d& rawPoint,
    const AcGePoint3d& grippedPoint, const AcGePoint3d& cartesianSnappedPoint,
    const AcGePoint3d& osnappedPoint, AcDb::OsnapMask osnapMask,
    const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
    AcDb::OsnapMask osnapOverrides,
    const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
    const AcArray<AcDbObjectId>& pickedEntities,
    const AcArray< AcDbObjectIdArray,
        AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedPickedEntities,
    const AcArray<Adesk::GsMarker>& gsSelectionMark,
    const AcArray<AcDbObjectId>& keyPointEntities,
    const AcArray< AcDbObjectIdArray,
        AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedKeyPointEntities,
    const AcArray<Adesk::GsMarker>& keyPointGsSelectionMark,
    const AcArray<AcGeCurve3d*>& alignmentPaths, const AcGePoint3d& computedPoint); 

class AcDbGripData {
public:
    AcDbGripData();
    AcDbGripData(const AcGePoint3d&, void*, GripOperationPtr hotGrip = NULL,
        GripOperationPtr hoverGrip = NULL, GripRtClkHandler RtClk = NULL,
        GripWorldDrawPtr wd = NULL, GripViewportDrawPtr vd = NULL,
        GripOpStatusPtr stat = NULL, GripToolTipPtr tt = NULL,
        GripDimensionPtr hoverDim = NULL, GripDimensionPtr hotGripDim = NULL,
        unsigned int bitFlags = 0,
        AcGePoint3d* altBasePt = NULL, GripInputPointPtr inputPointFunc = NULL);

    AcDbGripData(const AcGePoint3d&, void*, AcRxClass*, 
        GripOperationPtr hotGrip = NULL,
        GripOperationPtr hoverGrip = NULL, GripRtClkHandler RtClk = NULL,
        GripWorldDrawPtr wd = NULL, GripViewportDrawPtr vd = NULL,
        GripOpStatusPtr stat = NULL, GripToolTipPtr tt = NULL,
        GripDimensionPtr hoverDim = NULL, GripDimensionPtr hotGripDim = NULL,
        unsigned int bitFlags = 0,
        AcGePoint3d* altBasePt = NULL, GripInputPointPtr inputPointFunc = NULL);

    ~AcDbGripData() {}

    AcDbGripData(const AcDbGripData&);

    AcDbGripData&             operator = (const AcDbGripData&);

    void                      setAllData(const AcGePoint3d&, void*,
        GripOperationPtr hotGrip = NULL, GripOperationPtr hoverGrip = NULL,
        GripRtClkHandler RtClk = NULL, GripWorldDrawPtr wd = NULL,
        GripViewportDrawPtr vd = NULL, GripOpStatusPtr stat = NULL,
        GripToolTipPtr tt = NULL, GripDimensionPtr hoverDim = NULL,
        GripDimensionPtr hotGripDim = NULL,
        unsigned int bitFlags = 0, AcGePoint3d* altBasePt = NULL,
        GripInputPointPtr inputPointFunc = NULL,
        AcRxClass* appDataAcRxClass = NULL);

    const AcGePoint3d&        gripPoint() const;
    void                      setGripPoint(const AcGePoint3d& pt);

    void*                     appData() const;
    void                      setAppData(void* appData);

    AcRxClass*                appDataAcRxClass() const;
    void                      setAppDataAcRxClass(AcRxClass* pClass);

    GripOperationPtr          hotGripFunc() const;
    void                      setHotGripFunc(GripOperationPtr pFunc);

    GripOperationPtr          hoverFunc() const;
    void                      setHoverFunc(GripOperationPtr pFunc);
    
    GripRtClkHandler          rtClk() const;
    void                      setRtClk(GripRtClkHandler pFunc);
    
    GripWorldDrawPtr          worldDraw() const;
    void                      setWorldDraw(GripWorldDrawPtr pFunc);
    
    GripViewportDrawPtr       viewportDraw() const;
    void                      setViewportDraw(GripViewportDrawPtr pFunc);
    
    GripOpStatusPtr           gripOpStatFunc() const;
    void                      setGripOpStatFunc(GripOpStatusPtr pFunc);

    GripToolTipPtr            toolTipFunc() const;
    void                      setToolTipFunc(GripToolTipPtr pFunc);

    GripDimensionPtr          hoverDimensionFunc() const;
    void                      setHoverDimensionFunc(GripDimensionPtr pFunc);

    GripDimensionPtr          hotGripDimensionFunc() const;
    void                      setHotGripDimensionFunc(GripDimensionPtr pFunc);

    AcGePoint3d*              alternateBasePoint() const;
    void                      setAlternateBasePoint(AcGePoint3d* altBasePt);

    unsigned int              bitFlags() const;
    void                      setBitFlags(unsigned int flags);

    // Utility functions for individual bit flag bits

    bool                      skipWhenShared() const;
    void                      setSkipWhenShared(bool skip);

    bool                      isRubberBandLineDisabled() const;
    void                      disableRubberBandLine(bool disable);

    bool                      areModeKeywordsDisabled() const;
    void                      disableModeKeywords(bool disable);

    bool                      drawAtDragImageGripPoint() const;
    void                      setDrawAtDragImageGripPoint(bool atDragPoint);

    bool                      triggerGrip() const;
    void                      setTriggerGrip(bool trigger);

    GripInputPointPtr         inputPointFunc() const;
    void                      setInputPointFunc(GripInputPointPtr pFunc);

    bool                      forcedPickOn() const;
    void                      setForcedPickOn(bool on);

    bool                      mapGripHotToRtClk() const;
    void                      setMapGripHotToRtClk(bool on);

    bool                      gizmosEnabled() const;
    void                      setGizmosEnabled(bool on);

    bool                      gripIsPerViewport() const;
    void                      setGripIsPerViewport(bool on);

private:
    AcGePoint3d         m_gripPt;
    AcGePoint3d*        m_pAltBasePt;
    void*               m_pAppData;
    GripOperationPtr    m_pHotGripFunc;
    GripOperationPtr    m_pHoverFunc;
    GripRtClkHandler    m_pRtClk;
    GripWorldDrawPtr    m_pWorldDraw;
    GripViewportDrawPtr m_pViewportDraw;
    GripOpStatusPtr     m_pGripOpStatFunc;
    GripToolTipPtr      m_pToolTipFunc;
    GripDimensionPtr    m_pHoverDimensionFunc;
    GripDimensionPtr    m_pHotGripDimensionFunc;
    unsigned int        m_bitFlags;
    GripInputPointPtr   m_pInputPointFunc;
    AcRxClass*          m_pAppDataClass;
};

inline AcDbGripData::AcDbGripData() : m_pAppData(NULL), m_pAppDataClass(NULL),
    m_pHotGripFunc(NULL), m_pHoverFunc(NULL), m_pRtClk(NULL), 
    m_pWorldDraw(NULL), m_pViewportDraw(NULL), m_pGripOpStatFunc(NULL), 
    m_pToolTipFunc(NULL), m_pHoverDimensionFunc(NULL), 
    m_pHotGripDimensionFunc(NULL), m_bitFlags(0), m_pAltBasePt(NULL),
    m_pInputPointFunc(NULL)
{}

inline AcDbGripData::AcDbGripData(const AcGePoint3d& pt, void* AppData,
    GripOperationPtr hotGrip, GripOperationPtr hoverGrip,
    GripRtClkHandler RtClk, GripWorldDrawPtr wd,
    GripViewportDrawPtr vd, GripOpStatusPtr stat,
    GripToolTipPtr tt, GripDimensionPtr hoverDim,
    GripDimensionPtr hotGripDim,
    unsigned int bitFlags, AcGePoint3d* altBasePt,
    GripInputPointPtr inputPointFunc) :
    m_gripPt(pt), m_pAppData(AppData), m_pAppDataClass(NULL), m_pHotGripFunc(hotGrip),
    m_pHoverFunc(hoverGrip), m_pRtClk(RtClk), m_pWorldDraw(wd),
    m_pViewportDraw(vd), m_pGripOpStatFunc(stat),
    m_pToolTipFunc(tt), m_pHoverDimensionFunc(hoverDim),
    m_pHotGripDimensionFunc(hotGripDim),
    m_bitFlags(bitFlags), m_pAltBasePt(altBasePt),
    m_pInputPointFunc(inputPointFunc)
{
}

inline AcDbGripData::AcDbGripData(const AcGePoint3d& pt, void* AppData,
    AcRxClass* pAppDataClass,
    GripOperationPtr hotGrip, GripOperationPtr hoverGrip,
    GripRtClkHandler RtClk, GripWorldDrawPtr wd,
    GripViewportDrawPtr vd, GripOpStatusPtr stat,
    GripToolTipPtr tt, GripDimensionPtr hoverDim,
    GripDimensionPtr hotGripDim,
    unsigned int bitFlags, AcGePoint3d* altBasePt,
    GripInputPointPtr inputPointFunc) :
    m_gripPt(pt), m_pAppData(AppData), m_pAppDataClass(pAppDataClass),
    m_pHotGripFunc(hotGrip), m_pHoverFunc(hoverGrip), m_pRtClk(RtClk), 
    m_pWorldDraw(wd), m_pViewportDraw(vd), m_pGripOpStatFunc(stat),
    m_pToolTipFunc(tt), m_pHoverDimensionFunc(hoverDim),
    m_pHotGripDimensionFunc(hotGripDim),
    m_bitFlags(bitFlags), m_pAltBasePt(altBasePt),
    m_pInputPointFunc(inputPointFunc)
{
}
inline AcDbGripData::AcDbGripData(const AcDbGripData& src)
{
    m_gripPt = src.gripPoint();
    m_pAppData = src.appData();
    m_pAppDataClass = src.appDataAcRxClass();
    m_pHotGripFunc = src.hotGripFunc();
    m_pHoverFunc = src.hoverFunc();
    m_pRtClk = src.rtClk();
    m_pWorldDraw = src.worldDraw();
    m_pViewportDraw = src.viewportDraw();
    m_pGripOpStatFunc = src.gripOpStatFunc();
    m_pToolTipFunc= src.toolTipFunc();
    m_pHoverDimensionFunc= src.hoverDimensionFunc();
    m_pHotGripDimensionFunc= src.hotGripDimensionFunc();
    m_bitFlags = src.bitFlags();
    m_pAltBasePt = src.alternateBasePoint();
    m_pInputPointFunc = src.inputPointFunc();
}

inline AcDbGripData& AcDbGripData::operator = (const AcDbGripData& rtSide)
{
    m_gripPt = rtSide.gripPoint();
    m_pAppData = rtSide.appData();
    m_pAppDataClass = rtSide.appDataAcRxClass();
    m_pHotGripFunc = rtSide.hotGripFunc();
    m_pHoverFunc = rtSide.hoverFunc();
    m_pRtClk = rtSide.rtClk();
    m_pWorldDraw = rtSide.worldDraw();
    m_pViewportDraw = rtSide.viewportDraw();
    m_pGripOpStatFunc = rtSide.gripOpStatFunc();
    m_pToolTipFunc= rtSide.toolTipFunc();
    m_pHoverDimensionFunc= rtSide.hoverDimensionFunc();
    m_pHotGripDimensionFunc= rtSide.hotGripDimensionFunc();
    m_bitFlags = rtSide.bitFlags();
    m_pAltBasePt = rtSide.alternateBasePoint();
    m_pInputPointFunc = rtSide.inputPointFunc();

    return *this;
}

inline void AcDbGripData::setAllData(const AcGePoint3d& pt, void* AppData,
        GripOperationPtr hotGrip, GripOperationPtr hoverGrip,
        GripRtClkHandler RtClk, GripWorldDrawPtr wd,
        GripViewportDrawPtr vd, GripOpStatusPtr stat,
        GripToolTipPtr tt, GripDimensionPtr hoverDim,
        GripDimensionPtr hotGripDim,
        unsigned int bitFlags, AcGePoint3d* altBasePt,
        GripInputPointPtr inputPointFunc, 
        AcRxClass* pAppDataClass)
{
    m_gripPt = pt;
    m_pAppData = AppData;
    m_pAppDataClass = pAppDataClass;
    m_pHotGripFunc = hotGrip;
    m_pHoverFunc = hoverGrip;
    m_pRtClk = RtClk;
    m_pWorldDraw = wd;
    m_pViewportDraw = vd;
    m_pGripOpStatFunc = stat;
    m_pToolTipFunc= tt;
    m_pHoverDimensionFunc = hoverDim;
    m_pHotGripDimensionFunc = hotGripDim;
    m_bitFlags = bitFlags;
    m_pAltBasePt = altBasePt;
    m_pInputPointFunc = inputPointFunc;
}


inline const AcGePoint3d&
AcDbGripData::gripPoint() const
{
    return m_gripPt;
}

inline void
AcDbGripData::setGripPoint(const AcGePoint3d& pt)
{
    m_gripPt = pt;
}

inline void*
AcDbGripData::appData() const
{
    return m_pAppData;
}

inline void
AcDbGripData::setAppData(void* appData)
{
    m_pAppData = appData;
}

inline AcRxClass*
AcDbGripData::appDataAcRxClass() const
{
    return m_pAppDataClass;
}

inline void
AcDbGripData::setAppDataAcRxClass(AcRxClass* appDataClass)
{
    m_pAppDataClass = appDataClass;
}

inline GripOperationPtr
AcDbGripData::hotGripFunc() const
{
    return m_pHotGripFunc;
}

inline void
AcDbGripData::setHotGripFunc(GripOperationPtr pFunc)
{
    m_pHotGripFunc = pFunc;
}

inline GripOperationPtr
AcDbGripData::hoverFunc() const
{
    return m_pHoverFunc;
}

inline void
AcDbGripData::setHoverFunc(GripOperationPtr pFunc)
{
    m_pHoverFunc = pFunc;
}

inline GripRtClkHandler
AcDbGripData::rtClk() const
{
    return m_pRtClk;
}

inline void
AcDbGripData::setRtClk(GripRtClkHandler pFunc)
{
    m_pRtClk = pFunc;
}

inline GripWorldDrawPtr
AcDbGripData::worldDraw() const
{
    return m_pWorldDraw;
}

inline void
AcDbGripData::setWorldDraw(GripWorldDrawPtr pFunc)
{
    m_pWorldDraw = pFunc;
}

inline GripViewportDrawPtr
AcDbGripData::viewportDraw() const
{
    return m_pViewportDraw;
}

inline void
AcDbGripData::setViewportDraw(GripViewportDrawPtr pFunc)
{
    m_pViewportDraw = pFunc;
}

inline GripOpStatusPtr
AcDbGripData::gripOpStatFunc() const
{
    return m_pGripOpStatFunc;
}

inline void
AcDbGripData::setGripOpStatFunc(GripOpStatusPtr pFunc)
{
    m_pGripOpStatFunc = pFunc;
}
 
inline GripToolTipPtr
AcDbGripData::toolTipFunc() const
{
    return m_pToolTipFunc;
}

inline void
AcDbGripData::setToolTipFunc(GripToolTipPtr pFunc)
{
    m_pToolTipFunc = pFunc;
}

inline GripDimensionPtr
AcDbGripData::hoverDimensionFunc() const
{
    return m_pHoverDimensionFunc;
}

inline void
AcDbGripData::setHoverDimensionFunc(GripDimensionPtr pFunc)
{
    m_pHoverDimensionFunc = pFunc;
}

inline GripDimensionPtr
AcDbGripData::hotGripDimensionFunc() const
{
    return m_pHotGripDimensionFunc;
}

inline void
AcDbGripData::setHotGripDimensionFunc(GripDimensionPtr pFunc)
{
    m_pHotGripDimensionFunc = pFunc;
}

inline AcGePoint3d*
AcDbGripData::alternateBasePoint() const
{
    return m_pAltBasePt;
}

inline void
AcDbGripData::setAlternateBasePoint(AcGePoint3d* altBasePt)
{
    m_pAltBasePt = altBasePt;
}

inline unsigned int
AcDbGripData::bitFlags() const
{
    return m_bitFlags;
}

inline void
AcDbGripData::setBitFlags(unsigned int flags)
{
    m_bitFlags = flags;
}

inline bool
AcDbGripData::skipWhenShared() const
{
    return !!(m_bitFlags & AcDbGripOperations::kSkipWhenShared);
}

inline void
AcDbGripData::setSkipWhenShared(bool skip)
{
    if (skip)
        m_bitFlags |= AcDbGripOperations::kSkipWhenShared;
    else
        m_bitFlags &= ~AcDbGripOperations::kSkipWhenShared;
}

inline bool
AcDbGripData::isRubberBandLineDisabled() const
{
    return !!(m_bitFlags & AcDbGripOperations::kDisableRubberBandLine);
}

inline void
AcDbGripData::disableRubberBandLine(bool disable)
{
    if (disable)
        m_bitFlags |= AcDbGripOperations::kDisableRubberBandLine;
    else
        m_bitFlags &= ~AcDbGripOperations::kDisableRubberBandLine;
}

inline bool
AcDbGripData::areModeKeywordsDisabled() const
{
    return !!(m_bitFlags & AcDbGripOperations::kDisableModeKeywords);
}

inline void
AcDbGripData::disableModeKeywords(bool disable)
{
    if (disable)
        m_bitFlags |= AcDbGripOperations::kDisableModeKeywords;
    else
        m_bitFlags &= ~AcDbGripOperations::kDisableModeKeywords;
}

inline bool
AcDbGripData::drawAtDragImageGripPoint() const
{
    return !!(m_bitFlags & AcDbGripOperations::kDrawAtDragImageGripPoint);
}

inline void
AcDbGripData::setDrawAtDragImageGripPoint(bool atDragPoint)
{
    if (atDragPoint)
        m_bitFlags |= AcDbGripOperations::kDrawAtDragImageGripPoint;
    else
        m_bitFlags &= ~AcDbGripOperations::kDrawAtDragImageGripPoint;
}

inline bool
AcDbGripData::triggerGrip() const
{
    return !!(m_bitFlags & AcDbGripOperations::kTriggerGrip);
}

inline void
AcDbGripData::setTriggerGrip(bool trigger)
{
    if (trigger)
        m_bitFlags |= AcDbGripOperations::kTriggerGrip
            | AcDbGripOperations::kSkipWhenShared;
    else
        m_bitFlags &= ~(AcDbGripOperations::kTriggerGrip
            | AcDbGripOperations::kSkipWhenShared);
}

inline GripInputPointPtr
AcDbGripData::inputPointFunc() const
{
    return m_pInputPointFunc;
}

inline void
AcDbGripData::setInputPointFunc(GripInputPointPtr pFunc)
{
    m_pInputPointFunc = pFunc;
}

inline bool
AcDbGripData::forcedPickOn() const
{
    return !!(m_bitFlags & AcDbGripOperations::kTurnOnForcedPick);
}

inline void
AcDbGripData::setForcedPickOn(bool on)
{
    if (on)
        m_bitFlags |= AcDbGripOperations::kTurnOnForcedPick;
    else
        m_bitFlags &= ~AcDbGripOperations::kTurnOnForcedPick;
}

inline bool
AcDbGripData::mapGripHotToRtClk() const
{
    return !!(m_bitFlags & AcDbGripOperations::kMapGripHotToRtClk);
}

inline void
AcDbGripData::setMapGripHotToRtClk(bool on)
{
    if (on)
        m_bitFlags |= AcDbGripOperations::kMapGripHotToRtClk;
    else
        m_bitFlags &= ~AcDbGripOperations::kMapGripHotToRtClk;
}

inline bool
AcDbGripData::gizmosEnabled() const
{
    return !!(m_bitFlags & AcDbGripOperations::kGizmosEnabled);
}

inline void
AcDbGripData::setGizmosEnabled(bool on)
{
    if (on)
        m_bitFlags |= AcDbGripOperations::kGizmosEnabled;
    else
        m_bitFlags &= ~AcDbGripOperations::kGizmosEnabled;
}

inline bool
AcDbGripData::gripIsPerViewport() const
{
    return !!(m_bitFlags & AcDbGripOperations::kGripIsPerViewport);
}

inline void
AcDbGripData::setGripIsPerViewport(bool on)
{
    if (on)
        m_bitFlags |= AcDbGripOperations::kGripIsPerViewport;
    else
        m_bitFlags &= ~AcDbGripOperations::kGripIsPerViewport;
}

#endif // AD_DBGRIP_H



