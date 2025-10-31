//
// (C) Copyright 1998-2002,2004 by Autodesk, Inc. 
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

# ifndef ACRECTJIG_H
# define ACRECTJIG_H

#include "dbjig.h"
#include "gemat3d.h"
#include "dbxutil.h"
#include "AcDynDimCommon.h"
#pragma once

class AcRectangle;

//
// AcRectJig class Definition.
//
class AcRectJig : public AcDynDimCommon , public AcEdJig 
{
public:

    enum DimType {
        kNone           = 0,
        kHorizontalDim  = 1,
        kVerticalDim    = 2
    };

    AcRectJig() {};
    AcRectJig(AcDbDatabase* pDb, AcRectangle* pRect);
    virtual ~AcRectJig();

    Acad::ErrorStatus acquireDefPoints();
	Acad::ErrorStatus setPlane();
    virtual void prepRect();
    bool addDimData(int which, double dimScale = 1.0);
    bool appendDimData(int which, double dimScale = 1.0);
    bool updateDimData();
    void keywordHandler(AcEdJig::DragStatus& kword);
    void dragIt();
    virtual DragStatus sampler();
    virtual Adesk::Boolean update();

protected:
    virtual AcDbEntity* entity() const;
    virtual AcDbDimDataPtrArray* dimData(const double dimScale);
    virtual AcDbDimDataPtrArray* dimData() const;


    virtual Acad::ErrorStatus setDimValue(const AcDbDimData* dimData,
                                          const double dimValue);


private:
    AcDbDatabase *mpDb;
    AcRectangle *mpRect;
    AcGePoint3d mWcsPt1;
    AcGePoint3d mWcsPt2;
    AcGeVector3d mNormal;
    AcGeVector3d mHorizDir;
    AcGeVector3d mVertDir;
    AcGeMatrix3d mUcsToWcsMat;
    AcGeMatrix3d mWcsToUcsMat;
    double mElevation;
    bool mLockWidth;
    bool mLockHeight;
    int mKeyword;
    AcDbDimDataPtrArray *mpDimData;
};

# endif  // ACRECTJIG_H
