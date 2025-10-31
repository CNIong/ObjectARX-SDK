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

#ifndef AEC_AECUIPRSUBENTITY_H
#define AEC_AECUIPRSUBENTITY_H

#include "AecUiPrEntitySet.h"

/****************************************************************************
**
**  CLASS AecUiPrSubentity:
**
**  **jma
**
*************************************/

class AecUiPrSubentity : public AecUiPrEntitySet {

public:
                        AecUiPrSubentity(LPCTSTR msg);
    virtual             ~AecUiPrSubentity();

    Acad::ErrorStatus   setAllowNone(Adesk::Boolean allowIt);
    Acad::ErrorStatus   setAllowMultipleSelect(Adesk::Boolean allowIt);

    Acad::ErrorStatus   setMainEntity(const AcDbObjectId& objId);
    Acad::ErrorStatus   setFilterType(int type);        // NOTE: currently ignored!

    virtual Status      go();

    AcDbObjectId        objectId() const;

    Adesk::Boolean      isValidSubEntData() const;

    int                 pickCount() const;
    Adesk::Int32        gsMarkerAt(int index) const;
    AcGePoint3d         pickPointAt(int index) const;
    AcGeVector3d        pickVectorAt(int index) const;

    const AcDbIntArray& gsMarkers() const;

private:
        // data members
    AcDbIntArray        m_filterArray;
    int                 m_filterType;
    Adesk::Boolean      m_allowNone;
    Adesk::Boolean      m_allowMultipleSelect;
    Adesk::Boolean      m_isValidssnamexData;
    AcDbIntArray        m_gsMarkers;
    AcGePoint3dArray    m_pickPts;
    AcGeVector3dArray   m_pickVecs;
    AcDbObjectId        m_mainEnt;

        // helper functions
    Adesk::Boolean      doHighlight(const AcDbObjectId& objId);
    Adesk::Boolean      doUnHighlight(const AcDbObjectId& objId);
    Adesk::Boolean      retrievePickDataAt(long index);

};

#endif  // AEC_AECUIPRSUBENTITY_H
