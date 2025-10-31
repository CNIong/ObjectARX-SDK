//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

# ifndef ACMAIN_H
# define ACMAIN_H

#pragma once

#include "dbdimdata.h"

#define PI   ((double)3.14159265358979323846)



//========================================================================
// 
// Simple grip application data
//
//========================================================================

class AppData
{
public:
    AppData(const int id, const double dimScale = 1.0);
    ~AppData() {};
    int index() const;
    void setIndex(const int id);
    double dimScale() const;
    void setDimScale(const double dimScale);
    AcDbDimDataPtrArray *dimData() const;
    void appendDimData(AcDbDimData* pData);
    void resetDimData();

private:
    int mID;
    double mDimScale;
    AcDbDimDataPtrArray *mpDimData;
};

inline AppData::AppData(const int id, const double dimScale) : 
    mID(id),
    mDimScale(dimScale),
    mpDimData(NULL)
{
}

inline int AppData::index() const
{
    return mID;
}

inline void AppData::setIndex(const int id)
{
    mID = id;
}

inline double AppData::dimScale() const
{
    return mDimScale;
}

inline void AppData::setDimScale(const double dimScale)
{
    mDimScale = dimScale;
}

inline AcDbDimDataPtrArray *
AppData::dimData() const
{
    return mpDimData;
}

inline void AppData::appendDimData(AcDbDimData *pData)
{
    if (mpDimData == NULL)
        mpDimData = new AcDbDimDataPtrArray();

    int dummyIndex;
    if (!mpDimData->find(pData, dummyIndex))
        mpDimData->append(pData);
}

inline void AppData::resetDimData()
{
    if (mpDimData)
        mpDimData->setLogicalLength(0);
}


# endif // ACMAIN_H
