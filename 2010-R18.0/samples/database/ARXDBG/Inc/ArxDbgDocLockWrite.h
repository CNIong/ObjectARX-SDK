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
