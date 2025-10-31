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

#ifndef ARXDBGUIPRENTITYSETSINGLE_H
#define ARXDBGUIPRENTITYSETSINGLE_H

#include "ArxDbgUiPrEntitySet.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrEntitySetSingle:
**
**  **jma
**
****************************/

class ArxDbgUiPrEntitySetSingle : public ArxDbgUiPrEntitySet {

friend class ArxDbgUiPrSubentity;

public:
                    ArxDbgUiPrEntitySetSingle(LPCTSTR msg);
    virtual         ~ArxDbgUiPrEntitySetSingle();

    virtual Status  go();

    AcDbObjectId    objectId() const;

    void            setAllowNone(bool allowIt);

protected:
        // data members
    bool			m_allowNone;

private:
        // outlawed functions
								ArxDbgUiPrEntitySetSingle(const ArxDbgUiPrEntitySetSingle&);
    ArxDbgUiPrEntitySetSingle&	operator=(const ArxDbgUiPrEntitySetSingle&);
};


#endif    // ARXDBGUIPRENTITYSETSINGLE_H

