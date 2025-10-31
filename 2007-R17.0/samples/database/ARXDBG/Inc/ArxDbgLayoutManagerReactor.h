//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

#ifndef ARXDBGLAYOUTMANAGERREACTOR_H
#define ARXDBGLAYOUTMANAGERREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgLayoutManagerReactor:
**
**  **jma
**
*************************************/

class ArxDbgLayoutManagerReactor : public AcDbLayoutManagerReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxDbgLayoutManagerReactor);

					ArxDbgLayoutManagerReactor();
    virtual			~ArxDbgLayoutManagerReactor();

    virtual void	layoutCreated(const TCHAR* newLayoutName, const AcDbObjectId& layoutId);
    virtual void	layoutToBeRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId);
    virtual void	layoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId);
    virtual void	abortLayoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId);

    virtual void	layoutToBeCopied(const TCHAR* layoutName, const AcDbObjectId& oldLayoutId);
    virtual void	layoutCopied(const TCHAR* oldLayoutName,
							const AcDbObjectId& oldLayoutId,
							const TCHAR* newLayoutname,
							const AcDbObjectId& newLayoutId);
    virtual void	abortLayoutCopied(const TCHAR* layoutName, const AcDbObjectId& layoutId);

    virtual void	layoutToBeRenamed(const TCHAR* oldName,
							const TCHAR* newName, const AcDbObjectId& layoutId);
    virtual void	layoutRenamed(const TCHAR* oldName,
							const TCHAR* newName, const AcDbObjectId& layoutId);
    virtual void	abortLayoutRename(const TCHAR* oldName,
							const TCHAR* newName, const AcDbObjectId& layoutId);

    virtual void	layoutSwitched(const TCHAR* newLayoutname, const AcDbObjectId& newLayoutId);

    virtual void	plotStyleTableChanged(const TCHAR* newTableName, const AcDbObjectId& layoutId);
    virtual void	layoutsReordered();

private:
    void    printReactorMessage(LPCTSTR event, const TCHAR* layoutName) const;
    void    printReactorMessage(LPCTSTR event, const TCHAR* layoutName1, const TCHAR* layoutName2) const;

        // outlawed functions
	ArxDbgLayoutManagerReactor(const ArxDbgLayoutManagerReactor &copy);
    ArxDbgLayoutManagerReactor&	operator=(const ArxDbgLayoutManagerReactor &copy);        
};


#endif    // ARXDBGLAYOUTMANAGERREACTOR_H
