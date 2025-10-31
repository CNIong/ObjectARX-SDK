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
