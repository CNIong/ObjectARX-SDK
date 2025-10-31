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

#ifndef ARXDBGEVENTREACTOR_H
#define ARXDBGEVENTREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgEventReactor:
**
**  **jma
**
*************************************/

class ArxDbgEventReactor : public AcRxEventReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgEventReactor);

                    ArxDbgEventReactor();
    virtual         ~ArxDbgEventReactor();

        // messages that are sent by notification
    virtual void    dwgFileOpened(AcDbDatabase* pDwg, const TCHAR* fileName) override;
    virtual void	initialDwgFileOpenComplete(AcDbDatabase* pDwg);

    virtual void    databaseConstructed(AcDbDatabase*);
    virtual void    databaseToBeDestroyed(AcDbDatabase* pDwg);

    virtual void    beginSave(AcDbDatabase* pDwg, const TCHAR* pIntendedName);
    virtual void    saveComplete(AcDbDatabase* pDwg, const TCHAR* pActualName);
    virtual void	abortSave(AcDbDatabase* pDwg);

    virtual void    beginDxfIn(AcDbDatabase* db);
    virtual void    abortDxfIn(AcDbDatabase* db);
    virtual void    dxfInComplete(AcDbDatabase* db);

    virtual void    beginDxfOut(AcDbDatabase* pDwg);
    virtual void    abortDxfOut(AcDbDatabase* pDwg);
    virtual void    dxfOutComplete(AcDbDatabase* pDwg);

    virtual void    beginInsert(AcDbDatabase* pTo, const TCHAR* pBlockName, AcDbDatabase* pFrom);
    virtual void    beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom);
    virtual void    otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom);
    virtual void    abortInsert(AcDbDatabase* pTo);
    virtual void    endInsert(AcDbDatabase* pTo);

    virtual void    wblockNotice(AcDbDatabase* pDb);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom); 
    virtual void    otherWblock(AcDbDatabase* pTo, AcDbIdMapping& pIdMap, AcDbDatabase* pFrom);
    virtual void    abortWblock(AcDbDatabase* pTo);
    virtual void    endWblock(AcDbDatabase* pTo);
    virtual void    beginWblockObjects(AcDbDatabase* db, AcDbIdMapping& map);

    virtual void    beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& pIdMap);
    virtual void    beginDeepCloneXlation(AcDbIdMapping& pIdMap, Acad::ErrorStatus* pRetStatus);
    virtual void    abortDeepClone(AcDbIdMapping& pIdMap);
    virtual void    endDeepClone(AcDbIdMapping& pIdMap);

    virtual void    partialOpenNotice(AcDbDatabase* pDb);


	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

		// helper functions
    void    printReactorMessage(LPCTSTR event) const;
    void    printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const;
    void    printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const;
    void    printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const;


    // outlawed functions
    ArxDbgEventReactor(const ArxDbgEventReactor &copy);
    ArxDbgEventReactor&	operator=(const ArxDbgEventReactor &copy);        
};

#endif    // ARXDBGEVENTREACTOR_H
