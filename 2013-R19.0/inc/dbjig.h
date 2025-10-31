
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//  
// DESCRIPTION:
//      Definition of class AcEdJig, an object onto which you clamp an
//      AcDbEntity while bending it into shape.  Comes with slots for a
//      few standard dragging attachments and a built-in tool or two.
//  

#ifndef   _DBJIG_H_
#define   _DBJIG_H_ 1

#if defined(__cplusplus)
#ifndef _AD_ACDB_H
#include "acdb.h"
#endif

#include "dbdimdata.h"  // for dynamic dimensions

#pragma pack (push, 8)

class	AcEdImpJig;
class	AcDbEntity;

class AcEdJig: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcEdJig);

    typedef enum UserInputControls {
        kGovernedByOrthoMode            = 0x000001,
        kNullResponseAccepted           = 0x000002,
        kDontEchoCancelForCtrlC         = 0x000004,
        kDontUpdateLastPoint            = 0x000008,
        kNoDwgLimitsChecking            = 0x000010,
        kNoZeroResponseAccepted         = 0x000020,
        kNoNegativeResponseAccepted     = 0x000040,
        kAccept3dCoordinates            = 0x000080,
        kAcceptMouseUpAsPoint           = 0x000100,
        kAnyBlankTerminatesInput        = 0x000200,
        kInitialBlankTerminatesInput    = 0x000400,
        kAcceptOtherInputString         = 0x000800,
        kGovernedByUCSDetect            = 0x001000,
        kNoZDirectionOrtho              = 0x002000,
        kImpliedFaceForUCSChange        = 0x004000,
        kUseBasePointElevation          = 0x008000,

        ///<summary> Disables direct distance input. When this flag is ON a
        ///distance input such as integer or real will not be accepted unless
        ///kAcceptOtherInputString is ON, in that case returned DragStatus is
        ///kOther. </summary>
        kDisableDirectDistanceInput     = 0x010000,
    };

    typedef enum DragStatus {
        kModeless       = -17,
        kNoChange       = -6,
        kCancel         = -4,
        kOther          = -3,
        kNull           = -1,
        kNormal         = 0,
        kKW1,
        kKW2,
        kKW3,
        kKW4,
        kKW5,
        kKW6,
        kKW7,
        kKW8,
        kKW9
    };

    typedef enum CursorType {
        kNoSpecialCursor = -1,           // No Special Cursor Specified
        kCrosshair = 0,                  // Full Screen Cross Hair. 
        kRectCursor,                     // Rectangular cursor. 
        kRubberBand,                     // Rubber band line. 
        kNotRotated,                     // NotRotated Type. 
        kTargetBox,                      // Target Box Type. 
        kRotatedCrosshair,               // Rotated Crosshair w/ rubber band. 
        kCrosshairNoRotate,              // Crosshairs forced non-rotated. 
        kInvisible,                      // Invisible cursor. 
        kEntitySelect,                   // Entity selection target cursor. 
        kParallelogram,                  // Parallelogram cursor. 
        kEntitySelectNoPersp,            // Pickbox, suppressed in persp. 
        kPkfirstOrGrips,                 // Auto-select cursor. 
        kCrosshairDashed                 // 15 dashed style crosshair cursor

    };
    AcEdJig();
    virtual ~AcEdJig();

    DragStatus	drag();
    virtual DragStatus	sampler(); 
    virtual Adesk::Boolean  update();
    AcDbObjectId append();

    const ACHAR* keywordList();
    void        setKeywordList(const ACHAR*);

    const ACHAR* dispPrompt();
    void        setDispPrompt(const ACHAR*, ...);


    DragStatus acquireString(ACHAR *str);
    DragStatus acquireAngle(double &ang);
    DragStatus acquireAngle(double &ang, const AcGePoint3d& basePnt);
    DragStatus acquireDist(double &dist);
    DragStatus acquireDist(double &dist, const AcGePoint3d& basePnt);
    DragStatus acquirePoint(AcGePoint3d&);
    DragStatus acquirePoint(AcGePoint3d&, const AcGePoint3d&basePnt);

    AcEdJig::CursorType specialCursorType();
    void                setSpecialCursorType(CursorType);

    AcEdJig::UserInputControls userInputControls();
    void                       setUserInputControls(AcEdJig::UserInputControls);

    virtual AcDbEntity* entity() const;
    virtual AcDbDimDataPtrArray * dimData(const double dimScale);
    virtual Acad::ErrorStatus setDimValue(const AcDbDimData* dimData,
                                          const double dimValue); 

private:
    AcEdImpJig*  mpImpJig;
};

#pragma pack (pop)
#endif // cplusplus
#endif
