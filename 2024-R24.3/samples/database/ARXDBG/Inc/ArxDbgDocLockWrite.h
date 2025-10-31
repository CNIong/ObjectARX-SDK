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

#ifndef ARXDBGDOCLOCKWRITE_H
#define ARXDBGDOCLOCKWRITE_H

/****************************************************************************
**
**  CLASS ArxDbgDocLockWrite:
**
**  **jma
**
*************************************/

class ArxDbgDocLockWrite {

public:
					ArxDbgDocLockWrite();
					ArxDbgDocLockWrite(AcDbDatabase* db);
    virtual			~ArxDbgDocLockWrite();

    virtual Acad::ErrorStatus   lock();
    virtual Acad::ErrorStatus   lockAndSetCurrent();

    virtual Acad::ErrorStatus   lock(AcDbDatabase* nextDb);
    virtual Acad::ErrorStatus   lockAndSetCurrent(AcDbDatabase* nextDb);

    virtual Acad::ErrorStatus   unlock();
    virtual Acad::ErrorStatus   unlockAndRestoreCurrent();

private:
        // member data
    AcDbDatabase*       m_db;
    AcApDocument*       m_doc;
    bool                m_didLock;
	bool				m_didSwitch;
    AcApDocument*       m_curDocWhenStarted;
};


#endif    // ARXDBGDOCLOCKWRITE_H
