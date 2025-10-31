// (C) Copyright 1993-1998 by Autodesk, Inc.
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

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include "stdafx.h"

class curvetextContextMenu : public AcEdUIContext
{
public:
    curvetextContextMenu();
    ~curvetextContextMenu();
    virtual void* getMenuContext(const AcRxClass *pClass, const AcDbObjectIdArray& ids) ;
    virtual void  onCommand(Adesk::UInt32 cmdIndex);
    virtual void  OnUpdateMenu();

private:
    CMenu *m_pMenu;
    HMENU m_HMenu;
	bool uniqueEntity;
};

class curveContextMenu : public AcEdUIContext
{
public:
    curveContextMenu();
    ~curveContextMenu();
    virtual void* getMenuContext(const AcRxClass *pClass, const AcDbObjectIdArray& ids) ;
    virtual void  onCommand(Adesk::UInt32 cmdIndex);
    virtual void  OnUpdateMenu();

private:
    CMenu *m_pMenu;
    HMENU m_HMenu;
};
#endif