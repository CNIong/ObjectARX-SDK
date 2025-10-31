// (C) Copyright 1996,1998 by Autodesk, Inc. 
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

#include "stdafx.h"

#include "acdb.h"
#include "adslib.h"
#include "rxregsvc.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "acdocman.h"

extern "C" void acedPostCommandPrompt();

Adesk::Boolean
append(AcDbDatabase*pDb, AcDbEntity* pEntity, int vport)
{
    AcDbBlockTable *pBlockTable;
    Acad::ErrorStatus es = pDb->getSymbolTable(pBlockTable,
        AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table!");
        return Adesk::kFalse;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(vport == 1 ?  ACDB_PAPER_SPACE : ACDB_MODEL_SPACE ,
      pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table record!");
        pBlockTable->close();
        return Adesk::kFalse;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
    if (es != Acad::eOk) {
        ads_alert("Failed to append entity!");
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return Adesk::kFalse;
    }
    pBlockRec->close();
    pBlockTable->close();
    return Adesk::kTrue;

}


BOOL PasteFromData(COleDataObject* pDataObject, CRect& resRect, int& objType)
{
    STGMEDIUM medium;

    if (!SUCCEEDED(pDataObject->GetData(CF_TEXT, &medium)))
	    return FALSE;

    CRect rect;
    int type, left, top, right, bottom;
      
    char * pstr = (char*) GlobalLock (medium.hGlobal);
    if (sscanf(pstr, "%d %d %d %d %d", &type, &left, &top, &right, &bottom) != 5)
	    TRACE("Getting incorrect ObjType & CRect information\n");
    GlobalUnlock(medium.hGlobal);

    rect.SetRect(left, top, right, bottom);
    rect.NormalizeRect();
    resRect = rect;
    objType = type;

    ReleaseStgMedium(&medium);
    return TRUE;
}

CMyOverrideDropTarget::CMyOverrideDropTarget()
{
    m_rad = 0;
}

CMyOverrideDropTarget::~CMyOverrideDropTarget()
{
}

DROPEFFECT  
CMyOverrideDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point)
{
    if (! pDataObject->IsDataAvailable(CF_TEXT))
        return DROPEFFECT_NONE;

    // set the tracker size.         
    CRect rSize;
    int objType;
    if (!::PasteFromData(pDataObject, rSize, objType) || rSize.IsRectEmpty() == TRUE)
        m_rad = 50;
    else 
        m_rad = min(rSize.Width(), rSize.Height());

    return OnDragOver(pWnd, pDataObject, dwKeyState, point); 
}


DROPEFFECT 
CMyOverrideDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point)
{
    // find the tracker size
    CSize trackerSize;
    int rectSize;
    acedDwgPoint ptIn, ptIn2;

    if (NULL==pDataObject)
        return DROPEFFECT_NONE;;

    CPoint lowerLeft, lowerRight;
    ptIn[0]= ptIn[1] = ptIn[2]=0;
    ptIn2[0]= (2*m_rad);
    ptIn2[1]= ptIn2[2]=0;

    int windnum = acedGetWinNum(point.x, point.y);
    if (windnum == 0)
    {
      if (m_prevDropEffect != DROPEFFECT_NONE)
      {   // erase the prev tracker
         pWnd->GetDC()->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize));
      }     
      return DROPEFFECT_NONE; 
    }

    acedCoordFromWorldToPixel(windnum, ptIn,  lowerLeft);
    acedCoordFromWorldToPixel(windnum, ptIn2, lowerRight);

    rectSize = lowerRight.x - lowerLeft.x;
    TRACE("rectSize is %d\n", rectSize);

    trackerSize = CSize(rectSize,rectSize);

    CPoint trackerCenterPt (point.x - trackerSize.cx/2, 
        point.y - trackerSize.cx/2);

    // check if it's the same point
    if (point == m_lastDragPt)
         return DROPEFFECT_COPY;
    
    CDC *pDC = pWnd->GetDC();
    ASSERT(pDC);
    if (m_prevDropEffect != DROPEFFECT_NONE)
    {   // erase the prev tracker
        pDC->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize));

        // draw new tracker
        pDC->DrawFocusRect(CRect(trackerCenterPt, trackerSize));
        m_lastDragPt = trackerCenterPt;
        m_trackerSize = trackerSize;
    }

	return DROPEFFECT_COPY;
}


void 
CMyOverrideDropTarget::OnDragLeave(CWnd* pWnd)
{
    if (m_prevDropEffect != DROPEFFECT_NONE)
    {
        CDC* pDC = pWnd->GetDC();
        ASSERT(pDC);
        // erase previous focus rect
        pDC->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize)); 
        m_prevDropEffect = DROPEFFECT_NONE;
    }
}
 
DROPEFFECT CMyOverrideDropTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
{
    return -1; // calls OnDrop();
}


BOOL 
CMyOverrideDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropEffect, CPoint point)
{
    BOOL fRet=TRUE;
    
    if (NULL == pDataObject)
        return FALSE;

    OnDragLeave(pWnd);

    CRect rSize;
    int objType;
    fRet = ::PasteFromData(pDataObject, rSize, objType);
    
    if (rSize.IsRectEmpty() == TRUE)
        return FALSE;

    acedDwgPoint dwgPt;

    int windnum = acedGetWinNum(point.x, point.y);
    if (windnum == 0)
		return FALSE;

    acedCoordFromPixelToWorld(windnum, point, dwgPt);
   
    // lock DB
    AcDbDatabase *pDb = AcApGetDatabase((CView*)pWnd);
    acDocManager->lockDocument(acDocManager->document(pDb));

    switch (objType) 
    {
        case 0 :  // circle
        {
            double rad = min(rSize.Width(), rSize.Height());
    
            AcGeVector3d mnormal(0,0,1);
            AcGePoint3d center(dwgPt[0], dwgPt[1], 0);
            AcDbCircle *pCircle = new AcDbCircle(center, mnormal, rad);
            if (::append(pDb, pCircle, windnum) == Adesk::kTrue)
                pCircle->close();
        }
        break;

        case 1 : // square
        {
            double half = rSize.Width();

            AcGePoint3dArray  sqrPts;
            double x = dwgPt[0];
            double y = dwgPt[1];

            sqrPts.append(AcGePoint3d(x-half, y-half,0));
            sqrPts.append(AcGePoint3d(x-half, y+half,0));
            sqrPts.append(AcGePoint3d(x+half, y+half,0));
            sqrPts.append(AcGePoint3d(x+half, y-half,0));

            AcDb2dPolyline *pSquare = new AcDb2dPolyline(AcDb::k2dSimplePoly, sqrPts);
            pSquare->makeClosed();
            if (::append(pDb, pSquare, windnum) == Adesk::kTrue)
                pSquare->close();
            
        }
        break;

        case 2 :  // triangle
        {
            AcGePoint3dArray  tri;
            double x = dwgPt[0];
            double y = dwgPt[1];
            double size = rSize.Width();
            tri.append(AcGePoint3d(x, y+size,0));
            tri.append(AcGePoint3d(x-size, y-size,0));
            tri.append(AcGePoint3d(x+size, y-size,0));

            AcDb2dPolyline *pUp = new AcDb2dPolyline(AcDb::k2dSimplePoly, tri);
            pUp->makeClosed();
            if (::append(pDb, pUp, windnum) == Adesk::kTrue)
                pUp->close();

        }
        break;

        case 3 :
        {
            AcGePoint3dArray  tri;
            double x = dwgPt[0];
            double y = dwgPt[1];
            double size = rSize.Width();

            tri.append(AcGePoint3d(x, y-size,0));
            tri.append(AcGePoint3d(x-size, y+size,0));
            tri.append(AcGePoint3d(x+size, y+size,0));

            AcDb2dPolyline *pDown = new AcDb2dPolyline(AcDb::k2dSimplePoly, tri);
            pDown->makeClosed();
            if (::append(pDb, pDown,windnum) == Adesk::kTrue)
                pDown->close();

        }
        break;

    }
    acDocManager->unlockDocument(acDocManager->document(pDb));

    // Set Focus to AutoCAD because AutoCAD doesn't update its
    // display if it's not in focus.
    acedGetAcadFrame()->SetActiveWindow();

    return TRUE;
}

// get all files in hDrop and ads_print them 
void processDrop(HDROP hDrop)
{
    char fileName[MAX_PATH];
    // Get the number of files dropped on us.
    int nFiles = ::DragQueryFile( hDrop, 0xFFFFFFFF, NULL, 0 ); 

    acutPrintf("Files dropped:\n");
    // get filename(s) and insert them print them
    for (int i=0; i < nFiles; i++) {
        if (::DragQueryFile(hDrop, i, fileName, MAX_PATH) !=0) 
            acutPrintf("%s\n",fileName);
    }
    acutPrintf("\n");
    acedPostCommandPrompt();
}

void InitFormatEtc(FORMATETC& formatEtc, ULONG tymed, CLIPFORMAT cfFormat)
{
    memset(&formatEtc, 0, sizeof(FORMATETC));
    formatEtc.tymed = tymed;
    formatEtc.cfFormat = cfFormat;
    formatEtc.dwAspect = DVASPECT_CONTENT;
    formatEtc.lindex = -1;
}

BOOL processDrop(COleDataObject* pDataObject)
{
    // Check for File Manager/Explorer File Drop
    // 
    BOOL bFile = pDataObject->IsDataAvailable(CF_HDROP);
    if (bFile) {

        STGMEDIUM stgMedium;
        FORMATETC formatEtc;
        ::InitFormatEtc(formatEtc, TYMED_HGLOBAL, CF_HDROP);

        pDataObject->GetData(CF_HDROP, &stgMedium, &formatEtc);
        if (stgMedium.hGlobal != NULL) {
            HDROP hDrop = (HDROP)::GlobalLock(stgMedium.hGlobal);
            if (hDrop != (HDROP)0) {
                processDrop(hDrop);
                ::GlobalUnlock(stgMedium.hGlobal);
            }
            ::ReleaseStgMedium(&stgMedium);
        }
        return TRUE;
    }
    return FALSE;
}


// Special Note:
// This Popup Menu mechanism is totaly unsafe.
// It's possible that two different apps will define
// the same command id. In order to prevent this,
// I will provide an API to do popup menu.
// Something like AcApTrackPopupMenu(CWnd*, CPoint, UIContext*);
// UIContext is the same callback class used in ARX context menu.
// 
#define  ID_PRINTFILE   0xDFFF
#define  ID_CANCELDROPX 0xDFFE

BOOL wmCommandHook(MSG *pMsg)
{

    BOOL bRes = FALSE; // continue

    // Remove letter x or X
    if (pMsg->message == WM_COMMAND) {

        // This filter hook is short live to prevent
        // conflicting apps looking for the same event
        acedRemoveFilterWinMsg(wmCommandHook); 
    }

    return bRes; 
}


BOOL
CMyFileDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
						  DROPEFFECT dropEffect, CPoint point)
{
    processDrop(pDataObject);
    return TRUE; // take care of drop, doesn't let anyone handle it.
                 // Return False, if you want other apps to also
                 // get the drop event
}

DROPEFFECT 
CMyFileDropTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
							DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
{

	CMenu dropMenu;
    dropMenu.CreatePopupMenu();
	
	dropMenu.AppendMenu(MF_ENABLED, ID_PRINTFILE, "List Files" );
	dropMenu.AppendMenu(MF_SEPARATOR);
	dropMenu.AppendMenu(MF_ENABLED, ID_CANCELDROPX, "Cancel");

    pWnd->ClientToScreen(&point);
    UINT cmdID = dropMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, point.x, point.y, pWnd);

    switch(cmdID) 
    {
    case ID_PRINTFILE: 
        {
            processDrop(pDataObject);
            break;
        }
        
    case ID_CANCELDROPX:
        // no op
        break;
    }

    return DROPEFFECT_MOVE; // return other than NONE in order to prevent it
                            // from calling ::onDrop();
}

DROPEFFECT 
CMyFileDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point)
{
    // need to override this method to prevent calling AutoCAD's view
    // OnDragEnter() which can cause infinite recursive calls.
    return DROPEFFECT_MOVE;
}

DROPEFFECT 
CMyFileDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
                              DWORD dwKeyState, CPoint point)
{
    // need to override this method to prevent calling AutoCAD's view
    // onDragOver() which can cause infinite recursive calls.
    return DROPEFFECT_MOVE;
}

void 
CMyFileDropTarget::OnDragLeave(CWnd* pWnd)
{
}
