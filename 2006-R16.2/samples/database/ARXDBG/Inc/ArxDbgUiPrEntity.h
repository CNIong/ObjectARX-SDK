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

#ifndef ARXDBGUIPRENTITY_H
#define ARXDBGUIPRENTITY_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrEntity:
**
**  **jma
**
*************************************/

class ArxDbgUiPrEntity : public ArxDbgUiPrBase {

public:
                        ArxDbgUiPrEntity(LPCTSTR msg, LPCTSTR keyWordList);
    virtual             ~ArxDbgUiPrEntity();

    virtual Status      go();       // issue the prompt

    Acad::ErrorStatus   addAllowedClass(AcRxClass* classType, bool doIsATest = false);

    bool		        filterLockedLayers() const;
    Acad::ErrorStatus   setFilterLockedLayers(bool filterThem);

    AcDbObjectId        objectId() const;
    AcGePoint3d         pickPoint() const;

    void                setAllowNone(bool allowIt);

protected:
        // data members
    bool			    m_filterLockedLayers;
    AcDbVoidPtrArray    m_allowedClassTypes;
    AcDbIntArray        m_doIsATest;
    AcDbObjectId        m_objId;
    bool			    m_allowNone;
    AcGePoint3d         m_pickPt;

        // helper functions
    bool		        correctClass(AcDbEntity* ent);

private:
        // outlawed functions
                        ArxDbgUiPrEntity(const ArxDbgUiPrEntity&);
    ArxDbgUiPrEntity&	operator=(const ArxDbgUiPrEntity&);
};


#endif  // ARXDBGUIPRENTITY_H
