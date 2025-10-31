//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
