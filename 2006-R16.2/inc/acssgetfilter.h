//
//
//  ssgetfilter.h - Header file for AcEdSelectionSetService and AcEdSSGetFilter
//
// (C) Copyright 1998-2004 by Autodesk, Inc.
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

#ifndef _SSGETFILTER_H
#define _SSGETFILTER_H


class AcApDocument;


class AcEdSelectionSetService
{
public:

    virtual Acad::ErrorStatus ssNameX(
        bool bIsSubSelectionIndex,
    	int index,
        resbuf*& result) = 0;

    virtual Acad::ErrorStatus add(
        resbuf *ssnameXList,
        const AcDbFullSubentPath *pPath = NULL,
        const AcDbObjectId* pEntselSubent = NULL) = 0;

    virtual Acad::ErrorStatus remove(
        int index) = 0;

    virtual Acad::ErrorStatus highlight(
    	int subSelectionIndex,
        const AcDbFullSubentPath& path) = 0;
};


class AcEdSSGetFilter: public AcEdInputContextReactor
{
public:

    virtual void
    ssgetAddFilter(
	    int ssgetFlags,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
	    const AcDbObjectIdArray& subSelectionSet)
    {  }

    virtual void
    ssgetRemoveFilter(
	    int ssgetFlags,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
	    const AcDbObjectIdArray& subSelectionSet,
        AcDbIntArray& removeIndexes)
    {  }

    virtual void
    ssgetAddFailed(
	    int ssgetFlags,
	    int ssgetMode,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
        resbuf *rbPoints)
    {  }

    virtual void
    ssgetRemoveFailed(
	    int ssgetFlags,
	    int ssgetMode,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
	    resbuf *rbPoints,
        AcDbIntArray& removeIndexes)
    {  }

    virtual void
    endSSGet(
	    Acad::PromptStatus returnStatus,
	    int ssgetFlags,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet)
    {  }

    virtual void
    endEntsel(
        Acad::PromptStatus       returnStatus,
        const AcDbObjectId&      pickedEntity,
        const AcGePoint3d&       pickedPoint,
        AcEdSelectionSetService& service)
    {  }
};


Acad::ErrorStatus addSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter *pFilter);

Acad::ErrorStatus removeSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter *pFilter);

Acad::ErrorStatus setAllowDuplicateSelection(
                        AcApDocument *pDoc, boolean flag);

bool              duplicateSelectionsAllowed(AcApDocument *pDoc);


namespace AcEdSSGet {

enum AcEdSSGetFlags {
    kNormal         =  0,
    kPickPoints     =  1,
    kDuplicates     =  2,
    kNestedEntities =  4,
    kSubEntities    =  8,
    kSinglePick     = 16,
    kPickfirstSet   = 32,
    kPreviousSet    = 64
};

enum AcEdSSGetModes {
    kWin = 1,   //  (Window spec)
    kCross,     //  (Crossing spec)
    kBox,       //  (Box spec)
    kLast,      //  (Last)
    kEntity,    //  (Explicit entity name)
    kAll,       //  (Select all)
    kFence,     //  (Fence Selection)
    kCPoly,     //  (Crossing Poly)
    kWPoly,     //  (Window Poly)
    kPick,      //  (Single pick)
    kEvery,     //  (every entity on single pick)
    kXten,      //  (ssget "X")
    kGroup,     //  (selection set from "group" specification)
    kPrevious   //  (previous selectionset)
};

};

class AcEdSSGetFilter2 : public AcEdSSGetFilter
{
public:

    virtual void
    ssgetRolloverFilter(
        const AcDbFullSubentPath &subEntityPath, 
        AcDbFullSubentPath &highlightPath)
    {  }
};

Acad::ErrorStatus addSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter2 *pFilter);

Acad::ErrorStatus removeSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter2 *pFilter);

#endif  // _SSGETFILTER_H

