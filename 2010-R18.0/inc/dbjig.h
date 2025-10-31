#ifndef   _DBJIG_H_
#define   _DBJIG_H_ 1
//
// (C) Copyright 1994-2009 by Autodesk, Inc.  All rights reserved.
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
// DESCRIPTION:
//      Definition of class AcEdJig, an object onto which you clamp an
//      AcDbEntity while bending it into shape.  Comes with slots for a
//      few standard dragging attachments and a built-in tool or two.
//  

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
	kGovernedByOrthoMode	    = 0x0001,
	kNullResponseAccepted		= 0x0002,
	kDontEchoCancelForCtrlC		= 0x0004,
	kDontUpdateLastPoint		= 0x0008,
	kNoDwgLimitsChecking		= 0x0010,
	kNoZeroResponseAccepted		= 0x0020,
	kNoNegativeResponseAccepted	= 0x0040,
	kAccept3dCoordinates		= 0x0080,
	kAcceptMouseUpAsPoint		= 0x0100,
	kAnyBlankTerminatesInput	= 0x0200,
	kInitialBlankTerminatesInput	= 0x0400,
	kAcceptOtherInputString		= 0x0800,
    kGovernedByUCSDetect        = 0x1000,
    kNoZDirectionOrtho          = 0x2000,
    kImpliedFaceForUCSChange    = 0x4000,
    kUseBasePointElevation      = 0x8000
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
