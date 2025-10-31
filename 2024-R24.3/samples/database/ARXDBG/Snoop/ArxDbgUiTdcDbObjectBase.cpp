//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  ArxDbgUiTdcDbObjectBase.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUiTdcDbObjectBase.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiDlgDxf.h"
#include "ArxDbgUiDlgReactors.h"
#include "ArxDbgUiDlgXdata.h"
#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiTdmEditor.h"
#include "ArxDbgUiTdmObjects.h"
#include "ArxDbgUiTdmReferences.h"
#include "ArxDbgUiDlgObjectId.h"
#include "ArxDbgAppEditorReactor.h"
#include "ArxDbgReferenceFiler.h"
#include "AcExtensionModule.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::ArxDbgUiTdcDbObjectBase
**
**  **jma
**
*************************************/

ArxDbgUiTdcDbObjectBase::ArxDbgUiTdcDbObjectBase()
:   ArxDbgUiTdcRxObjectBase()
{
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcDbObjectBase)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDbObjectBase message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcDbObjectBase, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcDbObjectBase)
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(ARXDBG_BN_DXF, OnDxf)
    ON_BN_CLICKED(ARXDBG_BN_EXTDICT, OnExtdict)
    ON_BN_CLICKED(ARXDBG_BN_REACTORS, OnReactors)
    ON_BN_CLICKED(ARXDBG_BN_XDATA, OnXdata)
    ON_BN_CLICKED(ARXDBG_BN_DOCUMENT, OnDocument)
    ON_BN_CLICKED(ARXDBG_BN_REFERENCED_OBJS, OnReferencedObjects)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDbObjectBase message handlers

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnDxf
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnDxf() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxDbgUiDlgDxf dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnExtdict
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnExtdict() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbObjectId extDictId = obj->extensionDictionary();
        obj->close();

        ArxDbgUiTdmDatabase dbox(extDictId, this, _T("Extension Dictionary"));
        dbox.DoModal();
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnReactors
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnReactors() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxDbgUiDlgReactors dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnXdata
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnXdata() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxDbgUiDlgXdata dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnDatabase
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnDatabase() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbDatabase* db = obj->database();
        obj->close();

        if (db != NULL) {
            ArxDbgUiTdmDatabase dbox(db, this, _T("Database For Object"));
            dbox.DoModal();
        }
        else {
            ASSERT(0);    // button should have been disabled!
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnReferencedObjects
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnReferencedObjects() 
{
    AcDbObjectIdArray hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds;
    if (getReferencedObjects(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds)) {
        ArxDbgUiTdmReferences dbox(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds, this);
        dbox.DoModal();
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::getReferencedObjects
**
**  **jma
**
*************************************/

bool
ArxDbgUiTdcDbObjectBase::getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
                                              AcDbObjectIdArray& softPointerIds,
                                              AcDbObjectIdArray& hardOwnershipIds,
                                              AcDbObjectIdArray& softOwnershipIds) 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxDbgReferenceFiler filer;
        obj->dwgOut(&filer);
        obj->close();

        hardPointerIds = filer.m_hardPointerIds;
        softPointerIds = filer.m_softPointerIds;
        hardOwnershipIds = filer.m_hardOwnershipIds;
        softOwnershipIds = filer.m_softOwnershipIds;

        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnDocument
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnDocument() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbDatabase* db = obj->database();
        obj->close();

        AcApDocument* doc = acDocManager->document(db);
        if (doc) {
            ArxDbgUiTdmEditor dbox(this, doc);
            dbox.DoModal();
        }
        else {
            ASSERT(0);    // this button should have been disabled!
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::setExtensionButtons
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::setExtensionButtons(AcDbObject* obj)
{
    bool hasDbButton  = (this->GetDlgItem(ARXDBG_BN_DATABASE) != NULL) ? true : false;
    bool hasDocButton = (this->GetDlgItem(ARXDBG_BN_DOCUMENT) != NULL) ? true : false;

    if (obj != NULL) {
            // enable Xdata button if Xdata is present
        resbuf* xdata = obj->xData();
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_XDATA, (xdata != NULL));
        acutRelRb(xdata);

            // enable ExtDictionary and Reactor buttons if present
        int reactorCount = 0;
        const AcDbVoidPtrArray* reactors = obj->reactors();
        if (reactors != nullptr)
            reactorCount = reactors->length();

        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_EXTDICT, (obj->extensionDictionary() != AcDbObjectId::kNull));
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_REACTORS, (reactorCount != 0));

            // always make sure DXF button is enabled
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DXF, TRUE);

            // check for references
        AcDbObjectIdArray hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds;
        getReferencedObjects(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds);
        bool hasReferences = false;
        if (!hardPointerIds.isEmpty() || !softPointerIds.isEmpty() || !hardOwnershipIds.isEmpty() || !softOwnershipIds.isEmpty())
            hasReferences = true;

        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_REFERENCED_OBJS, hasReferences);

        AcDbDatabase* db = obj->database();

        if (hasDbButton)
            ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DATABASE, (db != NULL));
        if (hasDocButton)
            ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DOCUMENT, (db && (acDocManager->document(db) != NULL)));
    }
    else {
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_XDATA, FALSE);
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_EXTDICT, FALSE);
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_REACTORS, FALSE);
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DXF, FALSE);
        ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_REFERENCED_OBJS, FALSE);

        if (hasDbButton)
            ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DATABASE, FALSE);
        if (hasDocButton)
            ArxDbgUtils::enableDlgItem(this, ARXDBG_BN_DOCUMENT, FALSE);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::openCurrentItem
**
**  **jma
**
*************************************/

AcDbObject*
ArxDbgUiTdcDbObjectBase::openCurrentItem()
{
    if (m_currentObjId == AcDbObjectId::kNull)
        return NULL;

    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead, true);    // might want to open erased
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorAlert(es);
        return NULL;
    }
    else
        return obj;
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::addToSet
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::addToSet()
{
    ArxDbgAppEditorReactor* edReactor = ArxDbgAppEditorReactor::getInstance();
    if (edReactor)
        edReactor->cloneSet().addObject(m_currentObjId);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::delFromSet
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::delFromSet()
{
    ArxDbgAppEditorReactor* edReactor = ArxDbgAppEditorReactor::getInstance();
    if (edReactor)
        edReactor->cloneSet().removeObject(m_currentObjId);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::showObjIdDetails
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::showObjIdDetails()
{
    ArxDbgUiDlgObjectId dbox(m_currentObjId, this);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnCmdMsg
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcDbObjectBase::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    if (nCode == 0) {
        if (nID == ARXDBG_APPCMD_ADDTOSET) {
            addToSet();
            return TRUE;
        }
        else if (nID == ARXDBG_APPCMD_DELFROMSET) {
            delFromSet();
            return TRUE;
        }
        else if (nID == ARXDBG_APPCMD_OBJID_INFO) {
            showObjIdDetails();
            return TRUE;
        }
    }
    
    return ArxDbgUiTdcRxObjectBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::OnRButtonDown
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (m_currentObjId.isNull()) {
        ArxDbgUiTdcRxObjectBase::OnRButtonDown(nFlags, point);
        return;
    }

    CMenu menu;
    CAcModuleResourceOverride(ArxDbgApp::getApp()->dllInstance());

    if (menu.LoadMenu(ARXDBG_MNU_OBJSET)) {
        CMenu* pContextMenu = menu.GetSubMenu(0);
        
        if (pContextMenu) {
            ClientToScreen(&point);
            pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
            return;
        }
    }

    ArxDbgUiTdcRxObjectBase::OnRButtonDown(nFlags, point);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbObject* obj)
{
    ASSERT(obj != NULL);

    CString str, str2;

    addSeperatorLine(_T("AcDbObject"));

    addToDataList(_T("Class Name"), ArxDbgUtils::objToClassStr(obj));
    addToDataList(_T("Entity Name"), ArxDbgUtils::objToEnameStr(obj, str));
    addToDataList(_T("Handle"), ArxDbgUtils::objToHandleStr(obj, str));
    addToDataList(_T("Database"), ArxDbgUtils::dbToStr(obj->database(), str));

    AcDbObject* ownerObj;
    Acad::ErrorStatus es = acdbOpenObject(ownerObj, obj->ownerId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        ArxDbgUtils::objToClassAndHandleStr(ownerObj, str);
        ownerObj->close();
        addToDataList(_T("Owner"), str);
    }
    else
        addToDataList(_T("Owner"), ArxDbgUtils::rxErrorStr(es));

    addToDataList(_T("Merge Style"), ArxDbgUtils::mergeStyleToStr(obj->mergeStyle(), str));
    addToDataList(_T("Has Save Version Override"), ArxDbgUtils::booleanToStr(obj->hasSaveVersionOverride(), str));

    AcDb::AcDbDwgVersion dwgVer;
    AcDb::MaintenanceReleaseVersion maintVer;
    es = obj->getObjectBirthVersion(dwgVer, maintVer);
    if (es == Acad::eOk) {
        addToDataList(_T("Birth DWG Version"), ArxDbgUtils::dwgVersionToStr(dwgVer, str));
        addToDataList(_T("Birth Maintenance Version"), ArxDbgUtils::intToStr(maintVer, str));
    }
    else
        addToDataList(_T("Birth Version"), ArxDbgUtils::rxErrorStr(es));

        // now try to get more specific with classes that we know are derived from us
    AcDbDictionary* dict;
    AcDbEntity* ent;
    AcDbFilter* filter;
    AcDbGroup* group;
    AcDbIndex* index;
    AcDbLongTransaction* longTrans;
    AcDbMlineStyle* mlineStyle;
    AcDbPlaceHolder* placeHolder;
    AcDbPlotSettings* plotSettings;
    AcDbProxyObject* proxy;
    AcDbSymbolTable* symTbl;
    AcDbSymbolTableRecord* symTblRec;
    AcDbXrecord* xrec;

    if ((dict = AcDbDictionary::cast(obj)) != NULL)
        display(dict);
    else if ((ent = AcDbEntity::cast(obj)) != NULL)
        display(ent);
    else if ((filter = AcDbFilter::cast(obj)) != NULL)
        display(filter);
    else if ((group = AcDbGroup::cast(obj)) != NULL)
        display(group);
    else if ((index = AcDbIndex::cast(obj)) != NULL)
        display(index);
    else if ((longTrans = AcDbLongTransaction::cast(obj)) != NULL)
        display(longTrans);
    else if ((mlineStyle = AcDbMlineStyle::cast(obj)) != NULL)
        display(mlineStyle);
    else if ((placeHolder = AcDbPlaceHolder::cast(obj)) != NULL)
        display(placeHolder);
    else if ((plotSettings = AcDbPlotSettings::cast(obj)) != NULL)
        display(plotSettings);
    else if ((proxy = AcDbProxyObject::cast(obj)) != NULL)
        display(proxy);
    else if ((symTbl = AcDbSymbolTable::cast(obj)) != NULL)
        display(symTbl);
    else if ((symTblRec = AcDbSymbolTableRecord::cast(obj)) != NULL)
        display(symTblRec);
    else if ((xrec = AcDbXrecord::cast(obj)) != NULL)
        display(xrec);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display (DICTIONARY)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbDictionary* dict)
{
    CString str;

    ASSERT(dict != NULL);

    addSeperatorLine(_T("AcDbDictionary"));

    addToDataList(_T("Treat Elements As Hard"), ArxDbgUtils::booleanToStr(dict->isTreatElementsAsHard(), str));

    AcDbDictionaryWithDefault* dictWithDef;

    if ((dictWithDef = AcDbDictionaryWithDefault::cast(dict)) != NULL)
        display(dictWithDef);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display (ENTITY)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbEntity* ent)
{
    ASSERT(ent != NULL);

    CString str, str2;

    addSeperatorLine(_T("AcDbEntity"));

    ArxDbgUtils::symbolIdToName(ent->layerId(), str);
    addToDataList(_T("Layer"), str);

    addToDataList(_T("Color"), ArxDbgUtils::colorToStr(ent->colorIndex(), str));

    ArxDbgUtils::symbolIdToName(ent->linetypeId(), str);
    addToDataList(_T("Linetype"), str);

    addToDataList(_T("Lineweight"), ArxDbgUtils::lineWeightTypeToStr(ent->lineWeight(), str));
    addToDataList(_T("Linetype Scale"), ArxDbgUtils::doubleToStr(ent->linetypeScale(), str));

    TCHAR *tmpStr = ent->plotStyleName();
    addToDataList(_T("Plot Style"), tmpStr);
    acutDelString(tmpStr);

    addToDataList(_T("Visible"), ArxDbgUtils::booleanToStr((ent->visibility() == AcDb::kVisible), str));

    ArxDbgUtils::symbolIdToName(ent->blockId(), str);
    addToDataList(_T("Block"), str);

    addToDataList(_T("Is Planar"), ArxDbgUtils::booleanToStr(ent->isPlanar(), str));
    addToDataList(_T("Clone For Dragging"), ArxDbgUtils::booleanToStr(ent->cloneMeForDragging(), str));

    AcDb3dSolid* solid;
    AcDbBlockBegin* blkBegin;
    AcDbBlockEnd* blkEnd;
    AcDbBlockReference* blkRef;
    AcDbBody* body;
    AcDbCurve* curve;
    AcDbDimension* dim;
    AcDbFace* face;
    AcDbFaceRecord* vface;
    AcDbFcf* fcf;
    AcDbFrame* frame;
    AcDbHatch* hatch;
    AcDbImage* image;
    AcDbMline* mline;
    AcDbMText* mtext;
    AcDbPoint* point;
    AcDbPolyFaceMesh* pface;
    AcDbPolygonMesh* mesh;
    AcDbProxyEntity* proxy;
    AcDbRegion* region;
    AcDbSequenceEnd* seqEnd;
    AcDbShape* shape;
    AcDbSolid* solid2d;
    AcDbText* text;
    AcDbTrace* trace;
    AcDbVertex* vertex;
    AcDbViewport* viewport;

    if ((solid = AcDb3dSolid::cast(ent)) != NULL)
        display(solid);
    else if ((blkBegin = AcDbBlockBegin::cast(ent)) != NULL)
        display(blkBegin);
    else if ((blkEnd = AcDbBlockEnd::cast(ent)) != NULL)
        display(blkEnd);
    else if ((blkRef = AcDbBlockReference::cast(ent)) != NULL)
        display(blkRef);
    else if ((body = AcDbBody::cast(ent)) != NULL)
        display(body);
    else if ((curve = AcDbCurve::cast(ent)) != NULL)
        display(curve);
    else if ((dim = AcDbDimension::cast(ent)) != NULL)
        display(dim);
    else if ((face = AcDbFace::cast(ent)) != NULL)
        display(face);
    else if ((vface = AcDbFaceRecord::cast(ent)) != NULL)
        display(vface);
    else if ((fcf = AcDbFcf::cast(ent)) != NULL)
        display(fcf);
    else if ((frame = AcDbFrame::cast(ent)) != NULL)
        display(frame);
    else if ((hatch = AcDbHatch::cast(ent)) != NULL)
        display(hatch);
    else if ((image = AcDbImage::cast(ent)) != NULL)
        display(image);
    else if ((mline = AcDbMline::cast(ent)) != NULL)
        display(mline);
    else if ((mtext = AcDbMText::cast(ent)) != NULL)
        display(mtext);
    else if ((point = AcDbPoint::cast(ent)) != NULL)
        display(point);
    else if ((pface = AcDbPolyFaceMesh::cast(ent)) != NULL)
        display(pface);
    else if ((mesh = AcDbPolygonMesh::cast(ent)) != NULL)
        display(mesh);
    else if ((proxy = AcDbProxyEntity::cast(ent)) != NULL)
        display(proxy);
    else if ((region = AcDbRegion::cast(ent)) != NULL)
        display(region);
    else if ((seqEnd = AcDbSequenceEnd::cast(ent)) != NULL)
        display(seqEnd);
    else if ((shape = AcDbShape::cast(ent)) != NULL)
        display(shape);
    else if ((solid2d = AcDbSolid::cast(ent)) != NULL)
        display(solid2d);
    else if ((text = AcDbText::cast(ent)) != NULL)
        display(text);
    else if ((trace = AcDbTrace::cast(ent)) != NULL)
        display(trace);
    else if ((vertex = AcDbVertex::cast(ent)) != NULL)
        display(vertex);
    else if ((viewport = AcDbViewport::cast(ent)) != NULL)
        display(viewport);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display (FILTER)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbFilter"));

    AcDbLayerFilter* layFilter;
    AcDbSpatialFilter* spatialFilter;

    if ((layFilter = AcDbLayerFilter::cast(filter)) != NULL)
        display(layFilter);
    else if ((spatialFilter = AcDbSpatialFilter::cast(filter)) != NULL)
        display(spatialFilter);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    (GROUP)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbGroup* group)
{
    CString str;

    ASSERT(group != NULL);

    addSeperatorLine(_T("AcDbGroup"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    (INDEX)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbIndex"));

// TBD: doesn't link for some reason
    //AcDbLayerIndex* layIndex;
    //AcDbSpatialIndex* spatialIndex;

    //if ((layIndex = AcDbLayerIndex::cast(index)) != NULL)
    //    display(layIndex);
    //else if ((spatialIndex = AcDbSpatialIndex::cast(index)) != NULL)
    //    display(spatialIndex);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    LONG TRANSACTION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLongTransaction* lt)
{
    CString str;

    ASSERT(lt != NULL);

    addSeperatorLine(_T("AcDbLongTransaction"));

    TCHAR* tmpName = NULL;
	Acad::ErrorStatus es = lt->getLongTransactionName(tmpName);
	if (es == Acad::eOk) {
		str = tmpName;
		acutDelString(tmpName);
	}
	else
		str = ArxDbgUtils::rxErrorStr(es);

    addToDataList(_T("Name"), str);
    addToDataList(_T("Type"), ArxDbgUtils::longTransactionTypeToStr(lt->type(), str));

	ArxDbgUtils::symbolIdToName(lt->originBlock(), str);
    addToDataList(_T("Origin Block"), str);

	ArxDbgUtils::symbolIdToName(lt->destinationBlock(), str);
    addToDataList(_T("Destination Block"), str);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(MLINE STYLE)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbMlineStyle* mlStyle)
{
    CString str;

    ASSERT(mlStyle != NULL);

    addSeperatorLine(_T("AcDbMlineStyle"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(PLACE HOLDER)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPlaceHolder* placeHolder)
{
    CString str;

    ASSERT(placeHolder != NULL);

    addSeperatorLine(_T("AcDbPlaceHolder"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(PLOT SETTINGS)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPlotSettings* plotSettings)
{
    CString str;

    ASSERT(plotSettings != NULL);

    addSeperatorLine(_T("AcDbPlotSettings"));

	AcDbLayout* layout;
	if ((layout = AcDbLayout::cast(plotSettings)) != NULL)
		display(layout);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    PROXY
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbProxyObject* proxy)
{
    CString str;

    ASSERT(proxy != NULL);

    addSeperatorLine(_T("AcDbProxyObject"));

    addToDataList(_T("Original Class Name"), proxy->originalClassName());
    addToDataList(_T("Original DXF Name"), proxy->originalDxfName());
    addToDataList(_T("Application Description"), proxy->applicationDescription());
    addToDataList(_T("Proxy Flags"), ArxDbgUtils::intToStr(proxy->proxyFlags(), str));
    int flags = proxy->proxyFlags();
    if (flags & AcDbProxyObject::kEraseAllowed)
        addToDataList(NULL, _T("Erase Allowed"));
    if (flags & AcDbProxyObject::kCloningAllowed)
        addToDataList(NULL, _T("Cloning Allowed"));
	if (flags & AcDbProxyObject::kMergeIgnore)
		addToDataList(NULL, _T("Merge Ignore"));
	if (flags & AcDbProxyObject::kMergeReplace)
		addToDataList(NULL, _T("Merge Replace"));
	if (flags & AcDbProxyObject::kMergeMangleName)
		addToDataList(NULL, _T("Merge Mangle Name"));

    AcDbObjectIdArray refIds;
	AcDbIntArray intIds;
	Acad::ErrorStatus es = proxy->getReferences(refIds, intIds);
    if ((es == Acad::eOk) && (refIds.isEmpty() == false)) {
        addSeperatorLine(_T("References"));
        int len = refIds.length();
		AcDbObject* tmpObj;
        for (int i=0; i<len; i++) {
			if (refIds[i].isNull())
				addToDataList(NULL, _T("AcDbObjectId::kNull"));
			else {
				es = acdbOpenObject(tmpObj, refIds[i], AcDb::kForRead);
				if (es == Acad::eOk) {
					ArxDbgUtils::objToClassAndHandleStr(tmpObj, str);
					addToDataList(NULL, str);
					tmpObj->close();
				}
				else
					addToDataList(NULL, ArxDbgUtils::rxErrorStr(es));
			}
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(SYMBOL TABLE)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSymbolTable* symTbl)
{
    CString str;

    ASSERT(symTbl != NULL);

    addSeperatorLine(_T("AcDbSymbolTable"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(SYMBOL TABLE RECORD)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSymbolTableRecord* tblRec)
{
	ASSERT(tblRec != NULL);

    CString str;

	addSeperatorLine(_T("AcDbSymbolTableRecord"));

        // add entries common to all symbol table records
	addToDataList(_T("Is Dependent"), ArxDbgUtils::booleanToStr(tblRec->isDependent(), str));
	addToDataList(_T("Is Resolved"), ArxDbgUtils::booleanToStr(tblRec->isResolved(), str));

        // dispatch the appropriate display routine (wouldn't a virtual be nice!)
	AcDbAbstractViewTableRecord* abstractViewRecord;
    AcDbBlockTableRecord*  blkRecord;
    AcDbDimStyleTableRecord*  dimStyleRecord;
    AcDbLayerTableRecord*  layerRecord;
    AcDbLinetypeTableRecord*  linetypeRecord;
    AcDbRegAppTableRecord*  regAppRecord;
    AcDbTextStyleTableRecord*  textStyleRecord;
    AcDbUCSTableRecord*  ucsRecord;

    if ((abstractViewRecord = AcDbAbstractViewTableRecord::cast(tblRec)) != NULL)
        display(abstractViewRecord);
    else if ((blkRecord = AcDbBlockTableRecord::cast(tblRec)) != NULL)
        display(blkRecord);
    else if ((dimStyleRecord = AcDbDimStyleTableRecord::cast(tblRec)) != NULL)
        display(dimStyleRecord);
    else if ((layerRecord = AcDbLayerTableRecord::cast(tblRec)) != NULL)
        display(layerRecord);
    else if ((linetypeRecord = AcDbLinetypeTableRecord::cast(tblRec)) != NULL)
        display(linetypeRecord);
    else if ((regAppRecord = AcDbRegAppTableRecord::cast(tblRec)) != NULL)
        display(regAppRecord);
    else if ((textStyleRecord = AcDbTextStyleTableRecord::cast(tblRec)) != NULL)
        display(textStyleRecord);
    else if ((ucsRecord = AcDbUCSTableRecord::cast(tblRec)) != NULL)
        display(ucsRecord);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(XRECORD)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbXrecord* xrec)
{
    CString str;

    ASSERT(xrec != NULL);

    addSeperatorLine(_T("AcDbXrecord"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(DICTIONARY WITH DEFAULT)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbDictionaryWithDefault* dict)
{
    CString str;

    ASSERT(dict != NULL);

    addSeperatorLine(_T("AcDbDictionaryWithDefault"));

	AcDbObject* tmpObj;
	Acad::ErrorStatus es = acdbOpenObject(tmpObj, dict->defaultId(), AcDb::kForRead);
	if (es == Acad::eOk) {
		ArxDbgUtils::objToClassAndHandleStr(tmpObj, str);
		addToDataList(_T("Default Object"), str);
		tmpObj->close();
	}
	else
		addToDataList(_T("Default Object"), ArxDbgUtils::rxErrorStr(es));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    3DSOLID
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb3dSolid* solid)
{
    CString str;
    double area, volume;
    AcGePoint3d centroid;
    double momInertia[3];
    double prodInertia[3];
    double prinMoments[3];
    AcGeVector3d prinAxes[3];
    double radiiGyration[3];
    AcDbExtents extents;
    Acad::ErrorStatus es;

    ASSERT(solid != NULL);

    addSeperatorLine(_T("AcDb3dSolid"));

    es = solid->getArea(area);
    if (es == Acad::eOk)
        addToDataList(_T("Area"), ArxDbgUtils::doubleToStr(area, str));

    es = solid->getMassProp(volume, centroid, momInertia,
                prodInertia, prinMoments,
                prinAxes, radiiGyration, extents);
    if (es == Acad::eOk) {
        addToDataList(_T("Volume"), ArxDbgUtils::doubleToStr(volume, str));
        addToDataList(_T("Centroid"), ArxDbgUtils::ptToStr(centroid, str));
        addToDataList(_T("Mom. Of Inertia"), ArxDbgUtils::doubleArray3dToStr(momInertia, str));
        addToDataList(_T("Prod. Of Inertia"), ArxDbgUtils::doubleArray3dToStr(prodInertia,str));
        addToDataList(_T("Priciple Moments"), ArxDbgUtils::doubleArray3dToStr(prinMoments, str));
        addToDataList(_T("Radii Gyration"), ArxDbgUtils::doubleArray3dToStr(radiiGyration, str));
        addToDataList(_T("Principle Axes:"), _T(""));
        addToDataList(_T("   X Axis"), ArxDbgUtils::vectorToStr(prinAxes[0], str));
        addToDataList(_T("   Y Axis"), ArxDbgUtils::vectorToStr(prinAxes[1], str));
        addToDataList(_T("   Z Axis"), ArxDbgUtils::vectorToStr(prinAxes[2], str));
        addToDataList(_T("Extmin"), ArxDbgUtils::ptToStr(extents.minPoint(), str));
        addToDataList(_T("Extmax"), ArxDbgUtils::ptToStr(extents.maxPoint(), str));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(BLOCK BEGIN)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbBlockBegin* blkBegin)
{
    CString str;

    ASSERT(blkBegin != NULL);

    addSeperatorLine(_T("AcDbBlockBegin"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(BLOCK END)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbBlockEnd* blkEnd)
{
    CString str;

    ASSERT(blkEnd != NULL);

    addSeperatorLine(_T("AcDbBlockEnd"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    BLOCK REFERENCE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbBlockReference* blockRef)
{
    CString str;

    ASSERT(blockRef != NULL);

    addSeperatorLine(_T("AcDbBlockReference"));

    ArxDbgUtils::symbolIdToName(blockRef->blockTableRecord(), str);
    addToDataList(_T("Block Name"), str);
    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(blockRef->position(), str));
    AcGeScale3d scales = blockRef->scaleFactors();
    addToDataList(_T("X Scale"), ArxDbgUtils::doubleToStr(scales.sx, str));
    addToDataList(_T("Y Scale"), ArxDbgUtils::doubleToStr(scales.sy, str));
    addToDataList(_T("Z Scale"), ArxDbgUtils::doubleToStr(scales.sz, str));
    addToDataList(_T("Rotation"), ArxDbgUtils::angleToStr(blockRef->rotation(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(blockRef->normal(), str));
    addToDataList(_T("Treat As BlockRef For Explode"), ArxDbgUtils::booleanToStr(blockRef->treatAsAcDbBlockRefForExplode(), str));

    AcDbMInsertBlock* minsert;
    if ((minsert = AcDbMInsertBlock::cast(blockRef)) != NULL)
        display(minsert);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(BODY)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbBody* body)
{
    CString str;

    ASSERT(body != NULL);

    addSeperatorLine(_T("AcDbBody"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    CURVE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbCurve* curve)
{
    ASSERT(curve != NULL);

        // print out curve generic info
    AcGePlane plane;
    AcDb::Planarity planeType;
    double area;
    Acad::ErrorStatus es;
    CString str;

    addSeperatorLine(_T("AcDbCurve"));

    addToDataList(_T("Is Closed"), ArxDbgUtils::booleanToStr(curve->isClosed(), str));
    addToDataList(_T("Is Periodic"), ArxDbgUtils::booleanToStr(curve->isPeriodic(), str));

    curve->getPlane(plane, planeType);
    if (planeType == AcDb::kNonPlanar)
        str, _T("Non-Planar");
    else if (planeType == AcDb::kPlanar)
        str, _T("Planar");
    else
        str, _T("Linear");
    addToDataList(_T("Plane Type"), str);

    es = curve->getArea(area);
    if (es != Acad::eOk)
        addToDataList(_T("Area"), ArxDbgUtils::doubleToStr(area, str));

    AcDb2dPolyline* pline2d;
    AcDb3dPolyline* pline3d;
    AcDbArc* arc;
    AcDbCircle* circle;
    AcDbEllipse* ellipse;
    AcDbLeader* leader;
    AcDbLine* line;
    AcDbPolyline* pline;
    AcDbRay* ray;
    AcDbSpline* spline;
    AcDbXline* xline;

    if ((pline2d = AcDb2dPolyline::cast(curve)) != NULL)
        display(pline2d);
    else if ((pline3d = AcDb3dPolyline::cast(curve)) != NULL)
        display(pline3d);
    else if ((arc = AcDbArc::cast(curve)) != NULL)
        display(arc);
    else if ((circle = AcDbCircle::cast(curve)) != NULL)
        display(circle);
    else if ((ellipse = AcDbEllipse::cast(curve)) != NULL)
        display(ellipse);
    else if ((leader = AcDbLeader::cast(curve)) != NULL)
        display(leader);
    else if ((line = AcDbLine::cast(curve)) != NULL)
        display(line);
    else if ((pline = AcDbPolyline::cast(curve)) != NULL)
        display(pline);
    else if ((ray = AcDbRay::cast(curve)) != NULL)
        display(ray);
    else if ((spline = AcDbSpline::cast(curve)) != NULL)
        display(spline);
    else if ((xline = AcDbXline::cast(curve)) != NULL)
        display(xline);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbDimension"));

    ArxDbgUtils::symbolIdToName(dim->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);
    addToDataList(_T("Text Position"), ArxDbgUtils::ptToStr(dim->textPosition(), str));
    addToDataList(_T("Is Def Position"), ArxDbgUtils::booleanToStr(dim->isUsingDefaultTextPosition(), str));
    ArxDbgUtils::symbolIdToName(dim->dimBlockId(), str);
    addToDataList(_T("Block Name"), str);
    addToDataList(_T("Block Insert Pt"), ArxDbgUtils::ptToStr(dim->dimBlockPosition(), str));

	TCHAR* tmpStr = dim->dimensionText();
    addToDataList(_T("Dimtext"), tmpStr, true);
	acutDelString(tmpStr);

	addToDataList(_T("Text Attachment"), ArxDbgUtils::mtextAttachmentTypeToStr(dim->textAttachment(), str));
	addToDataList(_T("Text Line Spacing Style"), ArxDbgUtils::lineSpacingTypeToStr(dim->textLineSpacingStyle(), str));
	addToDataList(_T("Text Line Spacing Factor"), ArxDbgUtils::doubleToStr(dim->textLineSpacingFactor(), str));

    addToDataList(_T("Text Rotation"), ArxDbgUtils::angleToStr(dim->textRotation(), str));
    addToDataList(_T("Horiz Rotation"), ArxDbgUtils::angleToStr(dim->horizontalRotation(), str));
    addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(dim->elevation(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(dim->normal(), str));

        // dipatch appropriate display routine
    AcDb2LineAngularDimension* dim2Line;
    AcDb3PointAngularDimension* dim3Pt;
    AcDbDiametricDimension* dimDiam;
    AcDbAlignedDimension* dimAligned;    AcDbOrdinateDimension* dimOrdinate;

    AcDbRadialDimension* dimRadial;
    AcDbRotatedDimension* dimRotated;

    if ((dimAligned = AcDbAlignedDimension::cast(dim)) != NULL)
        display(dimAligned);
    else if ((dim3Pt = AcDb3PointAngularDimension::cast(dim)) != NULL)
        display(dim3Pt);
    else if ((dim2Line = AcDb2LineAngularDimension::cast(dim)) != NULL)
        display(dim2Line);
    else if ((dimDiam = AcDbDiametricDimension::cast(dim)) != NULL)
        display(dimDiam);
    else if ((dimRadial = AcDbRadialDimension::cast(dim)) != NULL)
        display(dimRadial);
    else if ((dimRotated = AcDbRotatedDimension::cast(dim)) != NULL)
        display(dimRotated);
    else if ((dimOrdinate = AcDbOrdinateDimension::cast(dim)) != NULL)
        display(dimOrdinate);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    FACE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbFace* face)
{
    CString str, str2;
    AcGePoint3d pt;
    int i;
    Adesk::Boolean visible;

    ASSERT(face != NULL);

    for (i=0;i<4;i++) {
        if (face->getVertexAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxDbgUtils::ptToStr(pt, str));
        }
    }
    for (i=0;i<4;i++) {
        if (face->isEdgeVisibleAt(i, visible) == Acad::eOk) {
            str2.Format(_T("Edge #%2d Visible"), i+1);
            addToDataList(str2, ArxDbgUtils::booleanToStr(visible, str));
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    FACE RECORD
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbFaceRecord* vface)
{
    int i;
    Acad::ErrorStatus es1, es2;
    Adesk::Int16 vtxIndex;
    Adesk::Boolean visible;
    CString str, str2, str3;

    ASSERT(vface != NULL);

    addSeperatorLine(_T("AcDbFaceRecord"));

    for (i=0;i<4;i++) {
        es1 = vface->getVertexAt(i, vtxIndex);
        es2 = vface->isEdgeVisibleAt(i, visible);    
        if ((es1 == Acad::eOk) && (es2 == Acad::eOk)) {
            str.Format(_T("Vface Pt #%2d"), i+1);
            str2.Format(_T("(index=%d, visible=%s)"), vtxIndex,
                        ArxDbgUtils::booleanToStr(visible, str3));
            addToDataList(str, str2);
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    FCF
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbFcf* fcf)
{
    CString str, str2;

    ASSERT(fcf != NULL);

    addSeperatorLine(_T("AcDbFcf"));

    addToDataList(_T("Location"), ArxDbgUtils::ptToStr(fcf->location(), str));
    ArxDbgUtils::symbolIdToName(fcf->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);

    AcGePoint3dArray ptArray;
    fcf->getBoundingPoints(ptArray);
    int i, len;
    len = ptArray.length();
    for (i=0;i<len;i++) {
        str2.Format(_T("Bouding Pt #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(ptArray.at(i), str));
    }

    addToDataList(_T("Direction"), ArxDbgUtils::vectorToStr(fcf->direction(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(fcf->normal(), str));

    TCHAR* tmpTxt = fcf->text();
    if (tmpTxt) {
        addToDataList(_T("Text"), tmpTxt, true);
        acutDelString(tmpTxt);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(FRAME)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbFrame* frame)
{
    CString str;

    ASSERT(frame != NULL);

    addSeperatorLine(_T("AcDbFrame"));

	AcDbOleFrame* oleFrame;
	AcDbOle2Frame* ole2Frame;

	if ((oleFrame = AcDbOleFrame::cast(frame)) != NULL)
		display(oleFrame);
	else if ((ole2Frame = AcDbOle2Frame::cast(frame)) != NULL)
		display(ole2Frame);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(IMAGE)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbImage* image)
{
    CString str;

    ASSERT(image != NULL);

    addSeperatorLine(_T("AcDbImage"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    HATCH
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbHatch* hatch)
{
    CString str, str2;
    Adesk::Int32 loopType;
    AcGeVoidPointerArray edgePtrs;
    AcGeIntArray edgeTypes;
    Acad::ErrorStatus es;

	ASSERT(hatch != NULL);

    addSeperatorLine(_T("AcDbHatch"));

        // basic info
    addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(hatch->elevation(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(hatch->normal(), str));
    addToDataList(_T("Is Associative"), ArxDbgUtils::booleanToStr(hatch->associative(), str));

        // pattern info
    addToDataList(_T("Hatch Pattern Type"), ArxDbgUtils::hatchTypeToStr(hatch->patternType(), str));
    addToDataList(_T("Pattern Name"), hatch->patternName(), true);
    addToDataList(_T("Pattern Angle"), ArxDbgUtils::angleToStr(hatch->patternAngle(), str));
    addToDataList(_T("Pattern Space"), ArxDbgUtils::doubleToStr(hatch->patternSpace(), str));
    addToDataList(_T("Pattern Scale"), ArxDbgUtils::doubleToStr(hatch->patternScale(), str));
    addToDataList(_T("Is Pattern Double"), ArxDbgUtils::booleanToStr(hatch->patternDouble(), str));

        // style info
    addToDataList(_T("Hatch Style"), ArxDbgUtils::hatchStyleToStr(hatch->hatchStyle(), str));

        // loop info
    for (int i=0; i<hatch->numLoops(); i++) {
        str2.Format(_T("Loop #%d"), i+1);
        addSeperatorLine(str2);

        es = hatch->getLoopAt(i, loopType, edgePtrs, edgeTypes);
        if (es == Acad::eOk) {
            addToDataList(_T("Loop Type"), ArxDbgUtils::hatchLoopTypeToStr(loopType, str));

            int len = edgePtrs.length();
            for (int j=0; j<len; j++) {
                str2.Format(_T("Edge #%d"), j+1);
                addSeperatorLine(str2);
                displayGeCurve2d(static_cast<AcGeCurve2d*>(edgePtrs[j]), edgeTypes[j]);
            }

            edgePtrs.setLogicalLength(0);
            edgeTypes.setLogicalLength(0);
        }
        else
            addToDataList(_T("ERROR"), _T("Could not get loop"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    MLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbMline* mline)
{
    CString str, str2;

    ASSERT(mline != NULL);

    addSeperatorLine(_T("AcDbMline"));

    ArxDbgUtils::mlineStyleIdToName(mline->style(), str);
    addToDataList(_T("Style"), str, true);
    Mline::MlineJustification justif = mline->justification();
    if (justif == Mline::kTop)
        str = _T("Top");
    else if (justif == Mline::kZero)
        str = _T("Zero");
    else if (justif == Mline::kBottom)
        str = _T("Bottom");
    else {
        ASSERT(0);
    }
    addToDataList(_T("Justification"), str);
    addToDataList(_T("Scale"), ArxDbgUtils::doubleToStr(mline->scale(), str));
    addToDataList(_T("Is Closed"), ArxDbgUtils::booleanToStr(mline->closedMline(), str));
    addToDataList(_T("Suppress Start Caps"), ArxDbgUtils::booleanToStr(mline->supressStartCaps(), str));
    addToDataList(_T("Suppress End Caps"), ArxDbgUtils::booleanToStr(mline->supressEndCaps(), str));
    int len = mline->numVertices();
    for (int i=0;i<len;i++) {
        str2.Format(_T("Vertex #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(mline->vertexAt(i), str));
    }
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(mline->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    MTEXT
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbMText* mtext)
{
    CString str, str2;

    ASSERT(mtext != NULL);

    addSeperatorLine(_T("AcDbMText"));

    addToDataList(_T("Location"), ArxDbgUtils::ptToStr(mtext->location(), str));
    addToDataList(_T("Rotation"), ArxDbgUtils::angleToStr(mtext->rotation(), str));
    addToDataList(_T("Width"), ArxDbgUtils::doubleToStr(mtext->width(), str));
    addToDataList(_T("Text Height"), ArxDbgUtils::doubleToStr(mtext->textHeight(), str));
    ArxDbgUtils::symbolIdToName(mtext->textStyle(), str);
    addToDataList(_T("Text Style"), str);

	addToDataList(_T("Attachment"), ArxDbgUtils::mtextAttachmentTypeToStr(mtext->attachment(), str));
    addToDataList(_T("Flow Dir"), ArxDbgUtils::mtextFlowDirTypeToStr(mtext->flowDirection(), str));

    AcGePoint3dArray ptArray;
    mtext->getBoundingPoints(ptArray);
    int i, len;
    len = ptArray.length();
    for (i=0;i<len;i++) {
        str2.Format(_T("Bounding Pt #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(ptArray.at(i), str));
    }

    addToDataList(_T("Actual Height"), ArxDbgUtils::doubleToStr(mtext->actualHeight(), str));
    addToDataList(_T("Actual Width"), ArxDbgUtils::doubleToStr(mtext->actualWidth(), str));
    addToDataList(_T("Contents"), mtext->contents());
    addToDataList(_T("Line Spacing Style"), ArxDbgUtils::lineSpacingTypeToStr(mtext->lineSpacingStyle(), str));
    addToDataList(_T("Line Spacing Factor"), ArxDbgUtils::doubleToStr(mtext->lineSpacingFactor(), str));

    addToDataList(_T("Direction"), ArxDbgUtils::vectorToStr(mtext->direction(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(mtext->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    POINT
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPoint* point)
{
    AcGePoint3d pt;
    CString str;

    ASSERT(point != NULL);

    addSeperatorLine(_T("AcDbPoint"));

    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(point->position(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(point->thickness(), str));
    addToDataList(_T("ECS Rotation"), ArxDbgUtils::angleToStr(point->ecsRotation(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(point->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    PFACE MESH
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPolyFaceMesh* pface)
{
    CString str;

    ASSERT(pface != NULL);

    addSeperatorLine(_T("AcDbPolyFaceMesh"));

    addToDataList(_T("Vertex Count"), ArxDbgUtils::intToStr(pface->numVertices(), str));
    addToDataList(_T("Face Count"), ArxDbgUtils::intToStr(pface->numFaces(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    POLYGON MESH
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPolygonMesh* mesh)
{
    CString str;

    ASSERT(mesh != NULL);

    addSeperatorLine(_T("AcDbPolygonMesh"));

    AcDb::PolyMeshType pmeshType = mesh->polyMeshType();
    if (pmeshType == AcDb::kSimpleMesh)
        str = _T("Simple Mesh");
    else if (pmeshType == AcDb::kQuadSurfaceMesh)
        str = _T("Quad Surface Mesh");
    else if (pmeshType == AcDb::kCubicSurfaceMesh)
        str = _T("Cubic Surface Mesh");
    else if (pmeshType == AcDb::kBezierSurfaceMesh)
        str = _T("Bezier Surface Mesh");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("Pmesh Type"), str);
    addToDataList(_T("M Size"), ArxDbgUtils::intToStr(mesh->mSize(), str));
    addToDataList(_T("N Size"), ArxDbgUtils::intToStr(mesh->nSize(), str));
    addToDataList(_T("M Is Closed"), ArxDbgUtils::booleanToStr(mesh->isMClosed(), str));
    addToDataList(_T("N Is Closed"), ArxDbgUtils::booleanToStr(mesh->isNClosed(), str));
    addToDataList(_T("M Surface Density"), ArxDbgUtils::intToStr(mesh->mSurfaceDensity(), str));
    addToDataList(_T("N Surface Density"), ArxDbgUtils::intToStr(mesh->nSurfaceDensity(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    PROXY
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbProxyEntity* proxy)
{
    CString str;

    ASSERT(proxy != NULL);

    addSeperatorLine(_T("AcDbProxyEntity"));

    addToDataList(_T("Original Class Name"), proxy->originalClassName());
    addToDataList(_T("Original DXF Name"), proxy->originalDxfName());
    addToDataList(_T("Application Description"), proxy->applicationDescription());
    addToDataList(_T("Has Graphics Metafile"), ArxDbgUtils::proxyMetafileTypeToStr(proxy->graphicsMetafileType(), str));
    addToDataList(_T("Proxy Flags"), ArxDbgUtils::intToStr(proxy->proxyFlags(), str));
    int flags = proxy->proxyFlags();
    if (flags & AcDbProxyEntity::kEraseAllowed)
        addToDataList(_T(""), _T("Erase Allowed"));
    if (flags & AcDbProxyEntity::kTransformAllowed)
        addToDataList(_T(""), _T("Transform Allowed"));
    if (flags & AcDbProxyEntity::kColorChangeAllowed)
        addToDataList(_T(""), _T("Color Change Allowed"));
    if (flags & AcDbProxyEntity::kLayerChangeAllowed)
        addToDataList(_T(""), _T("Layer Change Allowed"));
    if (flags & AcDbProxyEntity::kLinetypeChangeAllowed)
        addToDataList(_T(""), _T("Linetype Change Allowed"));
    if (flags & AcDbProxyEntity::kLinetypeScaleChangeAllowed)
        addToDataList(_T(""), _T("Linetype Scale Change Allowed"));
    if (flags & AcDbProxyEntity::kLineWeightChangeAllowed)
        addToDataList(_T(""), _T("Line Weight Change Allowed"));
    if (flags & AcDbProxyEntity::kPlotStyleNameChangeAllowed)
        addToDataList(_T(""), _T("Plot Style Name Change Allowed"));
    if (flags & AcDbProxyEntity::kVisibilityChangeAllowed)
        addToDataList(_T(""), _T("Visibility Change Allowed"));
    if (flags & AcDbProxyEntity::kCloningAllowed)
        addToDataList(_T(""), _T("Cloning Allowed"));

    AcDbObjectIdArray refIds;
	AcDbIntArray intIds;
	Acad::ErrorStatus es = proxy->getReferences(refIds, intIds);
    if ((es == Acad::eOk) && (refIds.isEmpty() == false)) {
        addSeperatorLine(_T("References"));
        int len = refIds.length();
		AcDbObject* tmpObj;
        for (int i=0; i<len; i++) {
			if (refIds[i].isNull())
				addToDataList(_T(""), _T("AcDbObjectId::kNull"));
			else {
				es = acdbOpenObject(tmpObj, refIds[i], AcDb::kForRead);
				if (es == Acad::eOk) {
					ArxDbgUtils::objToClassAndHandleStr(tmpObj, str);
					addToDataList(_T(""), str);
					tmpObj->close();
				}
				else
					addToDataList(_T(""), ArxDbgUtils::rxErrorStr(es));
			}
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    REGION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbRegion* pRegion)
{
    CString str;
    double perimeter, area;
    Acad::ErrorStatus es;
    AcGePoint3d origin;
    AcGeVector3d xAxis, yAxis;
    AcGePoint2d centroid;
    double momInertia[2], prodInertia, prinMoments[2], radiiGyration[2];
    AcGeVector2d prinAxes[2];
    AcGePoint2d extentsLow, extentsHigh;

    ASSERT(pRegion != NULL);

    addSeperatorLine(_T("AcDbRegion"));

    es = pRegion->getPerimeter(perimeter);
    if (es == Acad::eOk)
        addToDataList(_T("Perimeter"), ArxDbgUtils::doubleToStr(perimeter, str));

    es = pRegion->getArea(area);
    if (es == Acad::eOk)
        addToDataList(_T("Area"), ArxDbgUtils::doubleToStr(area, str));

	// the following 3 lines of code are added to
	// get the proper info (for getAreaProp()) from the plane it is in
	// see solution #44949 for more explanation
	AcGePlane plane;
	pRegion->getPlane(plane);
	plane.getCoordSystem(origin, xAxis, yAxis);

    es = pRegion->getAreaProp(origin, xAxis, yAxis, perimeter, area, centroid, momInertia,
                prodInertia, prinMoments,
                prinAxes, radiiGyration, extentsLow, extentsHigh);
    if (es == Acad::eOk) {
        addToDataList(_T("Origin"), ArxDbgUtils::ptToStr(origin, str));
        addToDataList(_T("X Axis"), ArxDbgUtils::vectorToStr(xAxis, str));
        addToDataList(_T("Y Axis"), ArxDbgUtils::vectorToStr(yAxis, str));
        addToDataList(_T("Perimeter"), ArxDbgUtils::doubleToStr(perimeter, str));
        addToDataList(_T("Area"), ArxDbgUtils::doubleToStr(area, str));
        addToDataList(_T("Centroid"), ArxDbgUtils::ptToStr(centroid, str));
        addToDataList(_T("Mom. Of Inertia"), ArxDbgUtils::doubleArray2dToStr(momInertia, str));
        addToDataList(_T("Prod. Of Inertia"), ArxDbgUtils::doubleToStr(prodInertia, str));
        addToDataList(_T("Principle Moments"), ArxDbgUtils::doubleArray2dToStr(prinMoments, str));
        addToDataList(_T("Radii Gyration"), ArxDbgUtils::doubleArray2dToStr(radiiGyration, str));
        addToDataList(_T("Principle Axes:"), _T(""));
        addToDataList(_T("   X Axis"), ArxDbgUtils::vectorToStr(prinAxes[0], str));
        addToDataList(_T("   Y Axis"), ArxDbgUtils::vectorToStr(prinAxes[1], str));
        addToDataList(_T("Extents Low"), ArxDbgUtils::ptToStr(extentsLow, str));
        addToDataList(_T("Extents High"), ArxDbgUtils::ptToStr(extentsHigh, str));
    }
    else {
        ArxDbgUtils::stopAlertBox(_T("ERROR calling AcDbRegion::getAreaProp()"));
        ArxDbgUtils::rxErrorAlert(es);
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    SEQUENCE END
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSequenceEnd* seqEnd)
{
    ASSERT(seqEnd != NULL);

    addSeperatorLine(_T("AcDbSequenceEnd"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    SHAPE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbShape* shape)
{
    CString str;

    ASSERT(shape != NULL);

    addSeperatorLine(_T("AcDbShape"));

    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(shape->position(), str));
    addToDataList(_T("Size"), ArxDbgUtils::doubleToStr(shape->size(), str));
    addToDataList(_T("Name"), shape->name(), true);
    addToDataList(_T("Rotation"), ArxDbgUtils::angleToStr(shape->rotation(), str));
    addToDataList(_T("Width Factor"), ArxDbgUtils::doubleToStr(shape->widthFactor(), str));
    addToDataList(_T("Oblique"), ArxDbgUtils::angleToStr(shape->oblique(), str));
    addToDataList(_T("Thickness:"), ArxDbgUtils::doubleToStr(shape->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(shape->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    SOLID
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSolid* solid)
{
    AcGePoint3d pt;
    int i;
    CString str, str2;

    ASSERT(solid != NULL);

    addSeperatorLine(_T("AcDbSolid"));

    for (i=0;i<4;i++) {
        if (solid->getPointAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxDbgUtils::ptToStr(pt, str));
        }
    }
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(solid->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(solid->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    TEXT
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbText* text)
{
    CString str;
    CString tmpStr;

    ASSERT(text != NULL);

    addSeperatorLine(_T("AcDbText"));

    const TCHAR* tmpStr2 = text->textStringConst();
    addToDataList(_T("Text"), tmpStr2, true);

    ArxDbgUtils::symbolIdToName(text->textStyle(), str);
    addToDataList(_T("Text Style"), str);
    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(text->position(), str));
    addToDataList(_T("Is Def Alignment"), ArxDbgUtils::booleanToStr(text->isDefaultAlignment(), str));
    if (text->isDefaultAlignment() == Adesk::kFalse)
        addToDataList(_T("Alignment Pt"), ArxDbgUtils::ptToStr(text->alignmentPoint(), str));

    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(text->thickness(), str));
    addToDataList(_T("Oblique Angle"), ArxDbgUtils::angleToStr(text->oblique(), str));
    addToDataList(_T("Rotation"), ArxDbgUtils::angleToStr(text->rotation(), str));
    addToDataList(_T("Height"), ArxDbgUtils::doubleToStr(text->height(), str));
    addToDataList(_T("Width Factor"), ArxDbgUtils::doubleToStr(text->widthFactor(), str));
    addToDataList(_T("Is Mirrored In X"), ArxDbgUtils::booleanToStr(text->isMirroredInX(), str));
    addToDataList(_T("Is Mirrored In Y"), ArxDbgUtils::booleanToStr(text->isMirroredInY(), str));
    addToDataList(_T("Horizontal Mode"), ArxDbgUtils::textModeToStr(text->horizontalMode(), str));
    addToDataList(_T("Vertical Mode"), ArxDbgUtils::textModeToStr(text->verticalMode(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(text->normal(), str));

    AcDbAttribute* attrib;
    AcDbAttributeDefinition* attdef;
    if ((attrib = AcDbAttribute::cast(text)) != NULL)
        display(attrib);
    else if ((attdef = AcDbAttributeDefinition::cast(text)) != NULL)
        display(attdef);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    TRACE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbTrace* trace)
{
    AcGePoint3d pt;
    int i;
    CString str, str2;

    ASSERT(trace != NULL);

    addSeperatorLine(_T("AcDbTrace"));

    for (i=0;i<4;i++) {
        if (trace->getPointAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxDbgUtils::ptToStr(pt, str));
        }
    }
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(trace->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(trace->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    VERTEX
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbVertex* vertex)
{
    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbVertex"));

    AcDb2dVertex* vertex2d;
    AcDb3dPolylineVertex* vertex3d;
    AcDbPolyFaceMeshVertex* pface;
    AcDbPolygonMeshVertex* mesh;

    if ((vertex2d = AcDb2dVertex::cast(vertex)) != NULL)
        display(vertex2d);
    else if ((vertex3d = AcDb3dPolylineVertex::cast(vertex)) != NULL)
        display(vertex3d);
    else if ((pface = AcDbPolyFaceMeshVertex::cast(vertex)) != NULL)
        display(pface);
    else if ((mesh = AcDbPolygonMeshVertex::cast(vertex)) != NULL)
        display(mesh);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    VIEWPORT
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbViewport* viewport)
{
    CString str;

    ASSERT(viewport != NULL);

    addSeperatorLine(_T("AcDbViewport"));

    //if (viewport->database() != acdbHostApplicationServices()->workingDatabase()) {
    //    ArxDbgUtils::stopAlertBox(_T("This AcDbViewport belongs to a database not currently loaded in the AutoCAD editor.  AutoCAD does not like this, request for info ignored to prevent crash!"));
    //    return;
    //}

    addToDataList(_T("Height"), ArxDbgUtils::doubleToStr(viewport->height(), str));
    addToDataList(_T("Width"), ArxDbgUtils::doubleToStr(viewport->width(), str));
    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(viewport->centerPoint(), str));
    addToDataList(_T("Number"), ArxDbgUtils::intToStr(viewport->number(), str));
    addToDataList(_T("Is On"), ArxDbgUtils::booleanToStr(viewport->isOn(), str));
    addToDataList(_T("View Target"), ArxDbgUtils::ptToStr(viewport->viewTarget(), str));
    addToDataList(_T("View Dir"), ArxDbgUtils::vectorToStr(viewport->viewDirection(), str));
    addToDataList(_T("View Height"), ArxDbgUtils::doubleToStr(viewport->viewHeight(), str));
    addToDataList(_T("View Center"), ArxDbgUtils::ptToStr(viewport->viewCenter(), str));
    addToDataList(_T("Twist Angle"), ArxDbgUtils::angleToStr(viewport->twistAngle(), str));
    addToDataList(_T("Lens Length"), ArxDbgUtils::doubleToStr(viewport->lensLength(), str));
    addToDataList(_T("Front Clip On"), ArxDbgUtils::booleanToStr(viewport->isFrontClipOn(), str));
    addToDataList(_T("Back Clip On"), ArxDbgUtils::booleanToStr(viewport->isBackClipOn(), str));
    addToDataList(_T("Front Clip At Eye"), ArxDbgUtils::booleanToStr(viewport->isFrontClipAtEyeOn(), str));
    addToDataList(_T("Front Clip Dist"), ArxDbgUtils::doubleToStr(viewport->frontClipDistance(), str));
    addToDataList(_T("Back Clip Dist"), ArxDbgUtils::doubleToStr(viewport->backClipDistance(), str));
    addToDataList(_T("Perspective On"), ArxDbgUtils::booleanToStr(viewport->isPerspectiveOn(), str));
    addToDataList(_T("UCS Follow On"), ArxDbgUtils::booleanToStr(viewport->isUcsFollowModeOn(), str));
    addToDataList(_T("UCS Icon Visible"), ArxDbgUtils::booleanToStr(viewport->isUcsIconVisible(), str));
    addToDataList(_T("UCS Icon At Origin"), ArxDbgUtils::booleanToStr(viewport->isUcsIconAtOrigin(), str));
    addToDataList(_T("Fast Zoom On"), ArxDbgUtils::booleanToStr(viewport->isFastZoomOn(), str));
    addToDataList(_T("Circle Sides"), ArxDbgUtils::intToStr(viewport->circleSides(), str));
    addToDataList(_T("Snap On"), ArxDbgUtils::booleanToStr(viewport->isSnapOn(), str));
    addToDataList(_T("Snap Isometric"), ArxDbgUtils::booleanToStr(viewport->isSnapIsometric(), str));
    addToDataList(_T("Snap Angle"), ArxDbgUtils::angleToStr(viewport->snapAngle(), str));
    addToDataList(_T("Snap Base Pt"), ArxDbgUtils::ptToStr(viewport->snapBasePoint(), str));
    addToDataList(_T("Snap Increment"), ArxDbgUtils::vectorToStr(viewport->snapIncrement(), str));
    addToDataList(_T("Snap Iso Pair"), ArxDbgUtils::intToStr(viewport->snapIsoPair(), str));
    addToDataList(_T("Grid On"), ArxDbgUtils::booleanToStr(viewport->isGridOn(), str));
    addToDataList(_T("Grid Increment"), ArxDbgUtils::vectorToStr(viewport->gridIncrement(), str));
    addToDataList(_T("Hidden Lines"), ArxDbgUtils::booleanToStr(viewport->hiddenLinesRemoved(), str));
    addToDataList(_T("Is Locked"), ArxDbgUtils::booleanToStr(viewport->isLocked(), str));
    addToDataList(_T("Is Transparent"), ArxDbgUtils::booleanToStr(viewport->isTransparent(), str));
    addToDataList(_T("Custom Scale"), ArxDbgUtils::doubleToStr(viewport->customScale(), str));
    addToDataList(_T("Standard Scale Type"), ArxDbgUtils::standardScaleTypeToStr(viewport->standardScale(), str));

    const TCHAR* tmpStr = NULL;
    Acad::ErrorStatus es = viewport->plotStyleSheet(tmpStr);
    if (es == Acad::eOk)
        addToDataList(_T("Plot Style Sheet"), tmpStr, true);
	else
        addToDataList(_T("Plot Style Sheet"), ArxDbgUtils::rxErrorStr(es));

    es = viewport->effectivePlotStyleSheet(tmpStr);
    if (es == Acad::eOk)
        addToDataList(_T("Effective Plot Style Sheet"), tmpStr, true);
	else
        addToDataList(_T("Effective Plot Style Sheet"), ArxDbgUtils::rxErrorStr(es));

    addToDataList(_T("Non-Rect Clip On"), ArxDbgUtils::booleanToStr(viewport->isNonRectClipOn(), str));

	AcDbObject* tmpObj;
	es = acdbOpenObject(tmpObj, viewport->nonRectClipEntityId(), AcDb::kForRead);
	if (es == Acad::eOk) {
		addToDataList(_T("Non-Rect Clip Entity"), ArxDbgUtils::objToClassAndHandleStr(tmpObj, str));
		tmpObj->close();
	}
	else
		addToDataList(_T("Non-Rect Clip Entity"), ArxDbgUtils::rxErrorStr(es));

	AcGePoint3d origin;
	AcGeVector3d xAxis, yAxis;
	es = viewport->getUcs(origin, xAxis, yAxis);
	if (es == Acad::eOk) {
		addToDataList(_T("UCS Origin"), ArxDbgUtils::ptToStr(origin, str));
		addToDataList(_T("UCS X Axis"), ArxDbgUtils::vectorToStr(xAxis, str));
		addToDataList(_T("UCS Y Axis"), ArxDbgUtils::vectorToStr(yAxis, str));
	}
	else
		addToDataList(_T("UCS Info"), ArxDbgUtils::rxErrorStr(es));

	AcDb::OrthographicView orthoView;
	bool ucsIsOrtho = viewport->isUcsOrthographic(orthoView);
	addToDataList(_T("Is UCS Orthographic"), ArxDbgUtils::booleanToStr(ucsIsOrtho, str));
	if (ucsIsOrtho)
		addToDataList(_T("UCS Orthographic View"), ArxDbgUtils::orthoViewToStr(orthoView, str));
    
	ArxDbgUtils::symbolIdToName(viewport->ucsName(), str);
	addToDataList(_T("UCS Name"), str);
	addToDataList(_T("Is UCS Saved With Viewport"), ArxDbgUtils::booleanToStr(viewport->isUcsSavedWithViewport(), str));
	addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(viewport->elevation(), str));

	bool viewIsOrtho = viewport->isViewOrthographic(orthoView);
	addToDataList(_T("Is View Orthographic"), ArxDbgUtils::booleanToStr(viewIsOrtho, str));
	if (viewIsOrtho)
		addToDataList(_T("Orthographic View"), ArxDbgUtils::orthoViewToStr(orthoView, str));

    AcDbObjectIdArray frozenLayers;
    es = viewport->getFrozenLayerList(frozenLayers);
    if ((es == Acad::eOk) && (frozenLayers.isEmpty() == Adesk::kFalse)) {
        addSeperatorLine(_T("Frozen Layers"));
        int len = frozenLayers.length();
        for (int i=0; i<len; i++) {
            ArxDbgUtils::symbolIdToName(frozenLayers[i], str);
            addToDataList(_T(""), str);
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display:    MINSERT BLOCK
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbMInsertBlock* mInsert)
{
    CString str;

    ASSERT(mInsert != NULL);

    addSeperatorLine(_T("AcDbMInsertBlock"));

    addToDataList(_T("Columns"), ArxDbgUtils::intToStr(mInsert->columns(), str));
    addToDataList(_T("Rows"), ArxDbgUtils::intToStr(mInsert->rows(), str));
    addToDataList(_T("Column Spacing"), ArxDbgUtils::doubleToStr(mInsert->columnSpacing(), str));
    addToDataList(_T("Row Spacing"), ArxDbgUtils::doubleToStr(mInsert->rowSpacing(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    2D POLYLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb2dPolyline* pline)
{
    CString str;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDb2dPolyline"));

    AcDb::Poly2dType ptype = pline->polyType();
    if (ptype == AcDb::k2dSimplePoly)
        str = _T("Simple");
    else if (ptype == AcDb::k2dFitCurvePoly)
        str = _T("Fit Curve");
    else if (ptype == AcDb::k2dQuadSplinePoly)
        str = _T("Quadratic Spline");
    else if (ptype == AcDb::k2dCubicSplinePoly)
        str = _T("Cubic Spline");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("2D Pline Type"), str);
    addToDataList(_T("Def Start Width"), ArxDbgUtils::doubleToStr(pline->defaultStartWidth(), str));
    addToDataList(_T("Def End Width"), ArxDbgUtils::doubleToStr(pline->defaultEndWidth(), str));
    addToDataList(_T("Linetype Gen On"), ArxDbgUtils::doubleToStr(pline->isLinetypeGenerationOn(), str));
    addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(pline->elevation(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(pline->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(pline->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    3D POLYLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb3dPolyline* pline)
{
    CString str;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDb3dPolyline"));

    AcDb::Poly3dType ptype = pline->polyType();
    if (ptype == AcDb::k3dSimplePoly)
        str = _T("Simple");
    else if (ptype == AcDb::k3dQuadSplinePoly)
        str = _T("Quadratic Spline");
    else if (ptype == AcDb::k3dCubicSplinePoly)
        str = _T("Cubic Spline");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("3D Pline Type"), str);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ARC
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbArc* arc)
{
    CString str;

    ASSERT(arc != NULL);

    addSeperatorLine(_T("AcDbArc"));

    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(arc->center(), str));
    addToDataList(_T("Radius"), ArxDbgUtils::doubleToStr(arc->radius(), str));
    addToDataList(_T("Start Angle"), ArxDbgUtils::angleToStr(arc->startAngle(), str));
    addToDataList(_T("End Angle"), ArxDbgUtils::angleToStr(arc->endAngle(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(arc->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(arc->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    CIRCLE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbCircle* circle)
{
    CString str;

    ASSERT(circle != NULL);

    addSeperatorLine(_T("AcDbCircle"));

    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(circle->center(), str));
    addToDataList(_T("Radius"), ArxDbgUtils::doubleToStr(circle->radius(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(circle->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(circle->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ELLIPSE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbEllipse* ellipse)
{
    CString str;

    ASSERT(ellipse != NULL);

    addSeperatorLine(_T("AcDbEllipse"));

    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(ellipse->center(), str));
    addToDataList(_T("Major Axis"), ArxDbgUtils::vectorToStr(ellipse->majorAxis(), str));
    addToDataList(_T("Minor Axis"), ArxDbgUtils::vectorToStr(ellipse->minorAxis(), str));
    addToDataList(_T("Radius Ratio"), ArxDbgUtils::doubleToStr(ellipse->radiusRatio(), str));
    addToDataList(_T("Start Angle"), ArxDbgUtils::angleToStr(ellipse->startAngle(), str));
    addToDataList(_T("End Angle"), ArxDbgUtils::angleToStr(ellipse->endAngle(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(ellipse->normal(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    LEADER
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLeader* leader)
{
    CString str, str2;

    ASSERT(leader != NULL);

    addSeperatorLine(_T("AcDbLeader"));

    int numVerts = leader->numVertices();
    for (int i=0;i<numVerts;i++) {
        str2.Format(_T("Vertex #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(leader->vertexAt(i), str));
    }
    ArxDbgUtils::symbolIdToName(leader->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);
    addToDataList(_T("Has Arrow Head"), ArxDbgUtils::booleanToStr(leader->hasArrowHead(), str));
    addToDataList(_T("Has Hook Line"), ArxDbgUtils::booleanToStr(leader->hasHookLine(), str));
    addToDataList(_T("Is Splined"), ArxDbgUtils::booleanToStr(leader->isSplined(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(leader->normal(), str));

	AcDbLeader::AnnoType type = leader->annoType();
	if (type == AcDbLeader::kMText)
		str = _T("Mtext");
	else if (type == AcDbLeader::kFcf)
		str = _T("Fcf");
	else if (type == AcDbLeader::kBlockRef)
		str = _T("Block Ref");
	else if (type == AcDbLeader::kNoAnno)
		str = _T("None");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

	addToDataList(_T("Annotation"), str);

	if (type != AcDbLeader::kNoAnno) {
		AcDbObject* annoObj;
		Acad::ErrorStatus es = acdbOpenObject(annoObj, leader->annotationObjId(), AcDb::kForRead);
		if (es == Acad::eOk) {
			addToDataList(_T("Annotation"), ArxDbgUtils::objToClassAndHandleStr(annoObj, str));
			annoObj->close();
		}
		else 
			addToDataList(_T("Annotation"), ArxDbgUtils::rxErrorStr(es));

		addToDataList(_T("Annotation Offset"), ArxDbgUtils::vectorToStr(leader->annotationOffset(), str));
		addToDataList(_T("Annotation Width"), ArxDbgUtils::doubleToStr(leader->annoWidth(), str));
		addToDataList(_T("Annotation Height"), ArxDbgUtils::doubleToStr(leader->annoHeight(), str));
	}

// TBD: still need the dimvars to be complete!
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    POLYLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPolyline* pline)
{
    CString str, str2;
    double tmpDouble;
    AcGePoint3d tmpPt;
    Acad::ErrorStatus es;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDbPolyline"));

    addToDataList(_T("Is Only Lines"), ArxDbgUtils::booleanToStr(pline->isOnlyLines(), str));
    addToDataList(_T("Is Closed"), ArxDbgUtils::booleanToStr(pline->isClosed(), str));
    addToDataList(_T("Has Pline Gen"), ArxDbgUtils::booleanToStr(pline->hasPlinegen(), str));
    addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(pline->elevation(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(pline->thickness(), str));
    if (pline->getConstantWidth(tmpDouble) == Acad::eOk)
        addToDataList(_T("Constant Width"), ArxDbgUtils::doubleToStr(tmpDouble, str));
    else
        addToDataList(_T("Constant Width"), _T("False"));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(pline->normal(), str));

    addSeperatorLine(_T("Vertices"));
    unsigned int i;
    for (i=0; i<pline->numVerts(); i++) {
        es = pline->getPointAt(i, tmpPt);
        if (es == Acad::eOk) {
            str2.Format(_T("Vertex #%d"), i+1);
            addToDataList(str2, ArxDbgUtils::ptToStr(tmpPt, str));
        }
    }
    AcDbPolyline::SegType segType;
    double bulge, startWidth, endWidth;

    unsigned int numSegs;
    if (pline->isClosed())
        numSegs = pline->numVerts();
    else
        numSegs = pline->numVerts() - 1;

    for (i=0; i<numSegs; i++) {
        str2.Format(_T("Segment #%d"), i+1);
        addSeperatorLine(str2);

        segType = pline->segType(i);
        if (segType == AcDbPolyline::kLine) {
            addToDataList(_T("Type"), _T("Line"));
            AcGeLineSeg3d line;
            es = pline->getLineSegAt(i, line);
            if (es == Acad::eOk) {
                addToDataList(_T("Start Point"), ArxDbgUtils::ptToStr(line.startPoint(), str));
                addToDataList(_T("End Point"), ArxDbgUtils::ptToStr(line.endPoint(), str));
            }
            else
                addToDataList(_T("ERROR"), _T("Could not get Line segment"));
        }
        else if (segType == AcDbPolyline::kArc) {
            addToDataList(_T("Type"), _T("Arc"));
            AcGeCircArc3d arc;
            es = pline->getArcSegAt(i, arc);
            if (es == Acad::eOk) {
                addToDataList(_T("Center Point"), ArxDbgUtils::ptToStr(arc.center(), str));
                addToDataList(_T("Start Point"), ArxDbgUtils::ptToStr(arc.startPoint(), str));
                addToDataList(_T("End Point"), ArxDbgUtils::ptToStr(arc.endPoint(), str));
                addToDataList(_T("Radius"), ArxDbgUtils::doubleToStr(arc.radius(), str));
                addToDataList(_T("Start Angle"), ArxDbgUtils::angleToStr(arc.startAng(), str));
                addToDataList(_T("End Angle"), ArxDbgUtils::angleToStr(arc.endAng(), str));
                addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(arc.normal(), str));
            }
            else
                addToDataList(_T("ERROR"), _T("Could not get Line segment"));
        }
        else if (segType == AcDbPolyline::kCoincident) {
            addToDataList(_T("Type"), _T("Coincident"));

        }
        else if (segType == AcDbPolyline::kPoint) {
            addToDataList(_T("Type"), _T("Point"));
            if (pline->getPointAt(i, tmpPt) == Acad::eOk)
                addToDataList(_T("Point"), ArxDbgUtils::ptToStr(tmpPt, str));
            else
                addToDataList(_T("ERROR"), _T("Could not get point"));
        }
        else if (segType == AcDbPolyline::kEmpty) {
            addToDataList(_T("Type"), _T("Empty"));
        }
        else {
            ASSERT(0);
            addToDataList(_T("Type"), _T("*Unknown"));
        }

        es = pline->getBulgeAt(i, bulge);
        if (es == Acad::eOk)
            addToDataList(_T("Bulge"), ArxDbgUtils::doubleToStr(bulge, str));
        else
            addToDataList(_T("ERROR"), _T("Could not get bulge"));

        es = pline->getWidthsAt(i, startWidth, endWidth);
        if (es == Acad::eOk) {
            addToDataList(_T("Start Width"), ArxDbgUtils::doubleToStr(startWidth, str));
            addToDataList(_T("End Width"), ArxDbgUtils::doubleToStr(endWidth, str));
        }
        else
            addToDataList(_T("ERROR"), _T("Could not get widths"));
    }
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    LINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLine* line)
{
    CString str;

    ASSERT(line != NULL);

    addSeperatorLine(_T("AcDbLine"));

    addToDataList(_T("Start Pt"), ArxDbgUtils::ptToStr(line->startPoint(), str));
    addToDataList(_T("End Pt"), ArxDbgUtils::ptToStr(line->endPoint(), str));
    addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(line->thickness(), str));
    addToDataList(_T("Normal"), ArxDbgUtils::vectorToStr(line->normal(), str));
}


/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    RAY
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbRay* ray)
{
    CString str;

    ASSERT(ray != NULL);

    addSeperatorLine(_T("AcDbRay"));

    addToDataList(_T("Base Pt"), ArxDbgUtils::ptToStr(ray->basePoint(), str));
    addToDataList(_T("Unit Dir"), ArxDbgUtils::vectorToStr(ray->unitDir(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    SPLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSpline* spline)
{
    CString str, str2;
    AcGePoint3d pt;
    AcGeVector3d startTan, endTan;
    int i, count;

    ASSERT(spline != NULL);

    addSeperatorLine(_T("AcDbSpline"));

    int degree;
    Adesk::Boolean rational, closed, periodic;
    AcGePoint3dArray controlPoints; 
    AcGeDoubleArray  knots; 
    AcGeDoubleArray  weights;
    double controlPtTol, knotTol;
    spline->getNurbsData(degree, rational, closed, periodic, controlPoints, 
                                    knots, weights, controlPtTol, knotTol);


    addToDataList(_T("Is Rational"), ArxDbgUtils::booleanToStr(rational, str));
    addToDataList(_T("Degree"), ArxDbgUtils::intToStr(degree, str));

    count = controlPoints.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Control Pt #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(controlPoints[i], str));
    }

    count = knots.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Knot #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::doubleToStr(knots[i], str));
    }

    AcGePoint3dArray  fitPoints; 
    Adesk::Boolean    tangentsExist;
    AcGeVector3d      startTangent;
    AcGeVector3d      endTangent;
    AcGe::KnotParameterization  knotParam;
    double            fitTolerance;
        
    if (!spline->hasFitData())
        return;

    spline->getFitData(fitPoints, tangentsExist, startTangent, endTangent, knotParam, degree, fitTolerance); 

    count = fitPoints.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Fit Pt #%2d"), i+1);
        addToDataList(str2, ArxDbgUtils::ptToStr(fitPoints[i], str));
    }
    addToDataList(_T("Fit Tolerance"), ArxDbgUtils::doubleToStr(fitTolerance, str));
    addToDataList(_T("Start Tangent"), ArxDbgUtils::vectorToStr(startTan, str));
    addToDataList(_T("End Tangent"), ArxDbgUtils::vectorToStr(endTan, str));
    addToDataList(_T("Knot Param"), ArxDbgUtils::intToStr(knotParam, str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    XLINE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbXline* xline)
{
    CString str;

    ASSERT(xline != NULL);

    addSeperatorLine(_T("AcDbXline"));

    addToDataList(_T("Base Pt"), ArxDbgUtils::ptToStr(xline->basePoint(), str));
    addToDataList(_T("Unit Dir"), ArxDbgUtils::vectorToStr(xline->unitDir(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    2 LINE ANGULAR DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb2LineAngularDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDb2LineAngularDimension"));

    addToDataList(_T("Arc Pt"), ArxDbgUtils::ptToStr(dim->arcPoint(), str));
    addToDataList(_T("Xline1 Start"), ArxDbgUtils::ptToStr(dim->xLine1Start(), str));
    addToDataList(_T("Xline1 End"), ArxDbgUtils::ptToStr(dim->xLine1End(), str));
    addToDataList(_T("Xline2 Start"), ArxDbgUtils::ptToStr(dim->xLine2Start(), str));
    addToDataList(_T("Xline2 End"), ArxDbgUtils::ptToStr(dim->xLine2End(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    3 POINT ANGULAR DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb3PointAngularDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDb3PointAngularDimension"));

    addToDataList(_T("Arc Pt"), ArxDbgUtils::ptToStr(dim->arcPoint(), str));
    addToDataList(_T("Xline Pt1"), ArxDbgUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxDbgUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(dim->centerPoint(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ALIGNED DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbAlignedDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbAlignedDimension"));

    addToDataList(_T("Xline Pt1"), ArxDbgUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxDbgUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Dimline Pt"), ArxDbgUtils::ptToStr(dim->dimLinePoint(), str));
    addToDataList(_T("Oblique Angle"), ArxDbgUtils::angleToStr(dim->oblique(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    DIAMETRIC DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbDiametricDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbDiametricDimension"));

    addToDataList(_T("Leader Length"), ArxDbgUtils::doubleToStr(dim->leaderLength(), str));
    addToDataList(_T("Chord Pt"), ArxDbgUtils::ptToStr(dim->chordPoint(), str));
    addToDataList(_T("Far Chord Pt"), ArxDbgUtils::ptToStr(dim->farChordPoint(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ORDINATE DIMENION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbOrdinateDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbOrdinateDimension"));

    addToDataList(_T("Is Using X Axis"), ArxDbgUtils::booleanToStr(dim->isUsingXAxis(), str));
    addToDataList(_T("Is Using Y Axis"), ArxDbgUtils::booleanToStr(dim->isUsingYAxis(), str));
    addToDataList(_T("Origin Pt"), ArxDbgUtils::ptToStr(dim->origin(), str));
    addToDataList(_T("Defining Pt"), ArxDbgUtils::ptToStr(dim->definingPoint(), str));
    addToDataList(_T("Leader End Pt"), ArxDbgUtils::ptToStr(dim->leaderEndPoint(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    RADIAL DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbRadialDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbRadialDimension"));

    addToDataList(_T("Leader Length"), ArxDbgUtils::doubleToStr(dim->leaderLength(), str));
    addToDataList(_T("Center"), ArxDbgUtils::ptToStr(dim->center(), str));
    addToDataList(_T("Chord Pt"), ArxDbgUtils::ptToStr(dim->chordPoint(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ROTATED DIMENSION
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbRotatedDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbRotatedDimension"));

    addToDataList(_T("Xline Pt1"), ArxDbgUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxDbgUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Dimline Pt"), ArxDbgUtils::ptToStr(dim->dimLinePoint(), str));
    addToDataList(_T("Oblique Angle"), ArxDbgUtils::angleToStr(dim->oblique(), str));
    addToDataList(_T("Rotation"), ArxDbgUtils::angleToStr(dim->rotation(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(OLE FRAME)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbOleFrame* oleFrame)
{
    CString str;

    ASSERT(oleFrame != NULL);

    addSeperatorLine(_T("AcDbOleFrame"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(OLE 2 FRAME)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbOle2Frame* ole2Frame)
{
    CString str;

    ASSERT(ole2Frame != NULL);

    addSeperatorLine(_T("AcDbOle2Frame"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ATTRIBUTE
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbAttribute* attrib)
{
    CString str;

    ASSERT(attrib != NULL);

    addSeperatorLine(_T("AcDbAttribute"));

    const TCHAR* tmpStr = attrib->tagConst();
    addToDataList(_T("Tag"), tmpStr, true);

    addToDataList(_T("Invisible"), ArxDbgUtils::booleanToStr(attrib->isInvisible(), str));
    addToDataList(_T("Constant"), ArxDbgUtils::booleanToStr(attrib->isConstant(), str));
    addToDataList(_T("Verifiable"), ArxDbgUtils::booleanToStr(attrib->isVerifiable(), str));
    addToDataList(_T("Preset"), ArxDbgUtils::booleanToStr(attrib->isPreset(), str));
    addToDataList(_T("Field Length"), ArxDbgUtils::intToStr(attrib->fieldLength(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    ATTDEF
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbAttributeDefinition* attdef)
{
    CString str;

    ASSERT(attdef != NULL);

    addSeperatorLine(_T("AcDbAttributeDefinition"));

    const TCHAR* tmpStr = attdef->promptConst();
    addToDataList(_T("Prompt"), tmpStr, true);

    tmpStr = attdef->tagConst();
    addToDataList(_T("Tag"), tmpStr, true);

    addToDataList(_T("Invisible"), ArxDbgUtils::booleanToStr(attdef->isInvisible(), str));
    addToDataList(_T("Constant"), ArxDbgUtils::booleanToStr(attdef->isConstant(), str));
    addToDataList(_T("Verifiable"), ArxDbgUtils::booleanToStr(attdef->isVerifiable(), str));
    addToDataList(_T("Preset"), ArxDbgUtils::booleanToStr(attdef->isPreset(), str));
    addToDataList(_T("Field Length"), ArxDbgUtils::intToStr(attdef->fieldLength(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    2D VERTEX
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb2dVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDb2dVertex"));

    AcDb::Vertex2dType vertexType = vertex->vertexType();
    if (vertexType == AcDb::k2dVertex)
        str = _T("2D Vertex");
    else if (vertexType == AcDb::k2dSplineCtlVertex)
        str = _T("Spline Control Vertex");
    else if (vertexType == AcDb::k2dSplineFitVertex)
        str = _T("Spline Fit Vertex");
    else if (vertexType == AcDb::k2dCurveFitVertex)
        str = _T("Curve Fit Vertex");
    else
        str = _T("");

    addToDataList(_T("Vertex Type"), str);
    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(vertex->position(), str));
    addToDataList(_T("Start Width"), ArxDbgUtils::doubleToStr(vertex->startWidth(), str));
    addToDataList(_T("End Width"), ArxDbgUtils::doubleToStr(vertex->endWidth(), str));
    addToDataList(_T("Bulge"), ArxDbgUtils::doubleToStr(vertex->bulge(), str));
    addToDataList(_T("Is Tangent Used"), ArxDbgUtils::booleanToStr(vertex->isTangentUsed(), str));
    if (vertex->isTangentUsed())
        addToDataList(_T("Tangent"), ArxDbgUtils::doubleToStr(vertex->tangent(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    3D POLYLINE VERTEX
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDb3dPolylineVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDb3dPolylineVertex"));

    addToDataList(_T("Vertex Type"), ArxDbgUtils::vertexTypeToStr(vertex->vertexType(), str));
    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(vertex->position(), str));
}


/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    POLYFACE MESH VERTEX
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPolyFaceMeshVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbPolyFaceMeshVertex"));

    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(vertex->position(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display    POLYGON MESH VERTEX
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbPolygonMeshVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbPolygonMeshVertex"));

    addToDataList(_T("Vertex Type"), ArxDbgUtils::vertexTypeToStr(vertex->vertexType(), str));
    addToDataList(_T("Position"), ArxDbgUtils::ptToStr(vertex->position(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(LAYER FILTER)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLayerFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbLayerFilter"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(SPATIAL FILTER)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSpatialFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbSpatialFilter"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(LAYER INDEX)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLayerIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbLayerIndex"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(SPATIAL INDEX)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbSpatialIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbSpatialIndex"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display	(LAYOUT)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLayout* layout)
{
    CString str;

    ASSERT(layout != NULL);

    addSeperatorLine(_T("AcDbLayout"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbAbstractViewTableRecord* view)
{
    CString str;

	addSeperatorLine(_T("AcDbAbstractViewTableRecord"));

    addToDataList(_T("Center Pt"), ArxDbgUtils::ptToStr(view->centerPoint(), str));
    addToDataList(_T("Height"), ArxDbgUtils::doubleToStr(view->height(), str));
    addToDataList(_T("Width"), ArxDbgUtils::doubleToStr(view->width(), str));
    addToDataList(_T("Target"), ArxDbgUtils::ptToStr(view->target(), str));
    addToDataList(_T("View Dir"), ArxDbgUtils::vectorToStr(view->viewDirection(), str));
    addToDataList(_T("View Twist"), ArxDbgUtils::doubleToStr(view->viewTwist(), str));
    addToDataList(_T("Lens Length"), ArxDbgUtils::doubleToStr(view->lensLength(), str));
    addToDataList(_T("Front Clip Dist"), ArxDbgUtils::doubleToStr(view->frontClipDistance(), str));
    addToDataList(_T("Back Clip Dist"), ArxDbgUtils::doubleToStr(view->backClipDistance(), str));
    addToDataList(_T("Perspective On"), ArxDbgUtils::booleanToStr(view->perspectiveEnabled(), str));
    addToDataList(_T("Front Clip On"), ArxDbgUtils::booleanToStr(view->frontClipEnabled(), str));
    addToDataList(_T("Back Clip On"), ArxDbgUtils::booleanToStr(view->backClipEnabled(), str));
    addToDataList(_T("Front Clip At Eye"), ArxDbgUtils::booleanToStr(view->frontClipAtEye(), str));

	AcGePoint3d origin;
	AcGeVector3d xAxis, yAxis;
	Acad::ErrorStatus es = view->getUcs(origin, xAxis, yAxis);
	if (es == Acad::eOk) {
		addToDataList(_T("UCS Origin"), ArxDbgUtils::ptToStr(origin, str));
		addToDataList(_T("UCS X Axis"), ArxDbgUtils::vectorToStr(xAxis, str));
		addToDataList(_T("UCS Y Axis"), ArxDbgUtils::vectorToStr(yAxis, str));
	}
	else
		addToDataList(_T("UCS Info"), ArxDbgUtils::rxErrorStr(es));

	AcDb::OrthographicView orthoView;
	bool ucsIsOrtho = view->isUcsOrthographic(orthoView);
	addToDataList(_T("Is UCS Orthographic"), ArxDbgUtils::booleanToStr(ucsIsOrtho, str));
	if (ucsIsOrtho)
		addToDataList(_T("UCS Orthographic View"), ArxDbgUtils::orthoViewToStr(orthoView, str));
    
	ArxDbgUtils::symbolIdToName(view->ucsName(), str);
	addToDataList(_T("UCS Name"), str);
	addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(view->elevation(), str));

	bool viewIsOrtho = view->isViewOrthographic(orthoView);
	addToDataList(_T("Is View Orthographic"), ArxDbgUtils::booleanToStr(viewIsOrtho, str));
	if (viewIsOrtho)
		addToDataList(_T("Orthographic View"), ArxDbgUtils::orthoViewToStr(orthoView, str));

	AcDbViewportTableRecord* vportRec;
	AcDbViewTableRecord* viewRec;

	if ((vportRec = AcDbViewportTableRecord::cast(view)) != NULL)
		display(vportRec);
	else if ((viewRec = AcDbViewTableRecord::cast(view)) != NULL)
		display(viewRec);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (BLOCK)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbBlockTableRecord* blk)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbBlockTableRecord"));

    es = blk->pathName(locName);
    if (es == Acad::eOk) {
        addToDataList(_T("Path Name"), locName, true);
    }

    addToDataList(_T("Origin"), ArxDbgUtils::ptToStr(blk->origin(), str));
    addToDataList(_T("Has Attribute Defs"), ArxDbgUtils::booleanToStr(blk->hasAttributeDefinitions(), str));
    addToDataList(_T("Has Preview Icon"), ArxDbgUtils::booleanToStr(blk->hasPreviewIcon(), str));
    addToDataList(_T("Is Anonymous"), ArxDbgUtils::booleanToStr(blk->isAnonymous(), str));
    addToDataList(_T("Is From Xref"), ArxDbgUtils::booleanToStr(blk->isFromExternalReference(), str));
    addToDataList(_T("Is From Overlay Ref"), ArxDbgUtils::booleanToStr(blk->isFromOverlayReference(), str));
    addToDataList(_T("Is Layout"), ArxDbgUtils::booleanToStr(blk->isLayout(), str));

    AcDbObject* tmpObj;
    es = acdbOpenObject(tmpObj, blk->getLayoutId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        addToDataList(_T("Layout Object"), ArxDbgUtils::objToClassAndHandleStr(tmpObj, str));
        tmpObj->close();
    }
    else
        addToDataList(_T("Layout Object"), ArxDbgUtils::rxErrorStr(es));

    addToDataList(_T("Xref Database"), ArxDbgUtils::ptrToStr(blk->xrefDatabase(), str));
    addToDataList(_T("Is Unloaded"), ArxDbgUtils::booleanToStr(blk->isUnloaded(), str));
    addToDataList(_T("Xref Status"), ArxDbgUtils::xrefStatusToStr(blk->xrefStatus(), str));

    const TCHAR* tmpStr;
    es = blk->comments(tmpStr);
    if (es == Acad::eOk)
        str = tmpStr;
    else
        ArxDbgUtils::rxErrorStr(es);

    addToDataList(_T("Comments"), str, true);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (DIMSTYLE)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbDimStyleTableRecord* dimStyle)
{
    CString str;

    addSeperatorLine(_T("AcDbDimStyleTableRecord"));

    ArxDbgUtils::symbolIdToName(dimStyle->arrowId(AcDb::kFirstArrow), str);
    addToDataList(_T("First Arrow"), str);

    ArxDbgUtils::symbolIdToName(dimStyle->arrowId(AcDb::kSecondArrow), str);
    addToDataList(_T("Second Arrow"), str);

    addToDataList(_T("DIMADEC"), ArxDbgUtils::intToStr(dimStyle->dimadec(), str));
    addToDataList(_T("DIMALT"), ArxDbgUtils::booleanToStr(dimStyle->dimalt(), str));
    addToDataList(_T("DIMALTD"), ArxDbgUtils::intToStr(dimStyle->dimaltd(), str));
    addToDataList(_T("DIMALTF"), ArxDbgUtils::doubleToStr(dimStyle->dimaltf(), str));
    addToDataList(_T("DIMALTRND"), ArxDbgUtils::doubleToStr(dimStyle->dimaltrnd(), str));
    addToDataList(_T("DIMALTTD"), ArxDbgUtils::intToStr(dimStyle->dimalttd(), str));
    addToDataList(_T("DIMALTU"), ArxDbgUtils::intToStr(dimStyle->dimaltu(), str));
    addToDataList(_T("DIMALTTZ"), ArxDbgUtils::intToStr(dimStyle->dimalttz(), str));
    addToDataList(_T("DIMALTZ"), ArxDbgUtils::intToStr(dimStyle->dimaltz(), str));
    addToDataList(_T("DIMAPOST"), dimStyle->dimapost(), true);
    addToDataList(_T("DIMASZ"), ArxDbgUtils::doubleToStr(dimStyle->dimasz(), str));
    addToDataList(_T("DIMAUNIT"), ArxDbgUtils::intToStr(dimStyle->dimaunit(), str));
    addToDataList(_T("DIMAZIN"), ArxDbgUtils::intToStr(dimStyle->dimazin(), str));

    ArxDbgUtils::symbolIdToName(dimStyle->dimblk(), str);
    addToDataList(_T("DIMBLK"), str);

    ArxDbgUtils::symbolIdToName(dimStyle->dimblk1(), str);
    addToDataList(_T("DIMBLK1"), str);

    ArxDbgUtils::symbolIdToName(dimStyle->dimblk2(), str);
    addToDataList(_T("DIMBLK2"), str);

    addToDataList(_T("DIMCEN"), ArxDbgUtils::doubleToStr(dimStyle->dimcen(), str));
    addToDataList(_T("DIMCLRD"), ArxDbgUtils::colorToStr(dimStyle->dimclrd().colorIndex(), str, true));
    addToDataList(_T("DIMCLRE"), ArxDbgUtils::colorToStr(dimStyle->dimclre().colorIndex(), str, true));
    addToDataList(_T("DIMCLRT"), ArxDbgUtils::colorToStr(dimStyle->dimclrt().colorIndex(), str, true));
    addToDataList(_T("DIMDEC"), ArxDbgUtils::intToStr(dimStyle->dimdec(), str));
    addToDataList(_T("DIMDLE"), ArxDbgUtils::doubleToStr(dimStyle->dimdle(), str));
    addToDataList(_T("DIMDLI"), ArxDbgUtils::doubleToStr(dimStyle->dimdli(), str));
    addToDataList(_T("DIMDSEP"), ArxDbgUtils::intToStr(dimStyle->dimdsep(), str));
    addToDataList(_T("DIMEXE"), ArxDbgUtils::doubleToStr(dimStyle->dimexe(), str));
    addToDataList(_T("DIMEXO"), ArxDbgUtils::doubleToStr(dimStyle->dimexo(), str));
    addToDataList(_T("DIMATFIT"), ArxDbgUtils::intToStr(dimStyle->dimatfit(), str));
    addToDataList(_T("DIMFRAC"), ArxDbgUtils::intToStr(dimStyle->dimfrac(), str));
    addToDataList(_T("DIMGAP"), ArxDbgUtils::doubleToStr(dimStyle->dimgap(), str));
    addToDataList(_T("DIMJUST"), ArxDbgUtils::intToStr(dimStyle->dimjust(), str));

    ArxDbgUtils::symbolIdToName(dimStyle->dimldrblk(), str);
    addToDataList(_T("DIMLDRBLK"), str);

    addToDataList(_T("DIMLFAC"), ArxDbgUtils::doubleToStr(dimStyle->dimlfac(), str));
    addToDataList(_T("DIMLIM"), ArxDbgUtils::booleanToStr(dimStyle->dimlim(), str));
    addToDataList(_T("DIMLUNIT"), ArxDbgUtils::intToStr(dimStyle->dimlunit(), str));
    addToDataList(_T("DIMLWD"), ArxDbgUtils::lineWeightTypeToStr(dimStyle->dimlwd(), str));
    addToDataList(_T("DIMLWE"), ArxDbgUtils::lineWeightTypeToStr(dimStyle->dimlwe(), str));
    addToDataList(_T("DIMPOST"), dimStyle->dimpost(), true);
    addToDataList(_T("DIMRND"), ArxDbgUtils::doubleToStr(dimStyle->dimrnd(), str));
    addToDataList(_T("DIMSAH"), ArxDbgUtils::booleanToStr(dimStyle->dimsah(), str));
    addToDataList(_T("DIMSCALE"), ArxDbgUtils::doubleToStr(dimStyle->dimscale(), str));
    addToDataList(_T("DIMSD1"), ArxDbgUtils::booleanToStr(dimStyle->dimsd1(), str));
    addToDataList(_T("DIMSD2"), ArxDbgUtils::booleanToStr(dimStyle->dimsd2(), str));
    addToDataList(_T("DIMSE1"), ArxDbgUtils::booleanToStr(dimStyle->dimse1(), str));
    addToDataList(_T("DIMSE2"), ArxDbgUtils::booleanToStr(dimStyle->dimse2(), str));
    addToDataList(_T("DIMSOXD"), ArxDbgUtils::booleanToStr(dimStyle->dimsoxd(), str));
    addToDataList(_T("DIMTAD"), ArxDbgUtils::intToStr(dimStyle->dimtad(), str));
    addToDataList(_T("DIMTDEC"), ArxDbgUtils::intToStr(dimStyle->dimtdec(), str));
    addToDataList(_T("DIMTFAC"), ArxDbgUtils::doubleToStr(dimStyle->dimtfac(), str));
    addToDataList(_T("DIMTIH"), ArxDbgUtils::booleanToStr(dimStyle->dimtih(), str));
    addToDataList(_T("DIMTIX"), ArxDbgUtils::booleanToStr(dimStyle->dimtix(), str));
    addToDataList(_T("DIMTM"), ArxDbgUtils::doubleToStr(dimStyle->dimtm(), str));
    addToDataList(_T("DIMTMOVE"), ArxDbgUtils::intToStr(dimStyle->dimtmove(), str));
    addToDataList(_T("DIMTOFL"), ArxDbgUtils::booleanToStr(dimStyle->dimtofl(), str));
    addToDataList(_T("DIMTOH"), ArxDbgUtils::booleanToStr(dimStyle->dimtoh(), str));
    addToDataList(_T("DIMTOL"), ArxDbgUtils::booleanToStr(dimStyle->dimtol(), str));
    addToDataList(_T("DIMTOLJ"), ArxDbgUtils::intToStr(dimStyle->dimtolj(), str));
    addToDataList(_T("DIMTP"), ArxDbgUtils::doubleToStr(dimStyle->dimtp(), str));
    addToDataList(_T("DIMTSZ"), ArxDbgUtils::doubleToStr(dimStyle->dimtsz(), str));
    addToDataList(_T("DIMTVP"), ArxDbgUtils::doubleToStr(dimStyle->dimtvp(), str));

    ArxDbgUtils::symbolIdToName(dimStyle->dimtxsty(), str);
    addToDataList(_T("DIMTXSTY"), str);

    addToDataList(_T("DIMTXT"), ArxDbgUtils::doubleToStr(dimStyle->dimtxt(), str));
    addToDataList(_T("DIMTZIN"), ArxDbgUtils::intToStr(dimStyle->dimtzin(), str));
    addToDataList(_T("DIMUPT"), ArxDbgUtils::booleanToStr(dimStyle->dimupt(), str));
    addToDataList(_T("DIMZIN"), ArxDbgUtils::intToStr(dimStyle->dimzin(), str));

    addToDataList(_T("DIMFIT (Deprecated)"), ArxDbgUtils::intToStr(dimStyle->dimfit(), str));
    addToDataList(_T("DIMUNIT (Deprecated)"), ArxDbgUtils::intToStr(dimStyle->dimunit(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (LAYER)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLayerTableRecord* layer)
{
    CString str;

    addSeperatorLine(_T("AcDbLayerTableRecord"));
    addToDataList(_T("Is Hidden"), ArxDbgUtils::booleanToStr(layer->isHidden(), str));
    addToDataList(_T("Is Frozen"), ArxDbgUtils::booleanToStr(layer->isFrozen(), str));
    addToDataList(_T("Is Off"), ArxDbgUtils::booleanToStr(layer->isOff(), str));
    addToDataList(_T("Is Locked"), ArxDbgUtils::booleanToStr(layer->isLocked(), str));
    addToDataList(_T("Is VP Default"), ArxDbgUtils::booleanToStr(layer->VPDFLT(), str));
    addToDataList(_T("Color"), ArxDbgUtils::intToStr(layer->color().colorIndex(), str));

    ArxDbgUtils::symbolIdToName(layer->linetypeObjectId(), str);
    addToDataList(_T("Linetype"), str);

    addToDataList(_T("Lineweight"), ArxDbgUtils::lineWeightTypeToStr(layer->lineWeight(), str));
    addToDataList(_T("Is Plottable"), ArxDbgUtils::booleanToStr(layer->isPlottable(), str));

    TCHAR* name = layer->plotStyleName();
    addToDataList(_T("Plot Style Name"), name);
    acutDelString(name);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (LINETYPE)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbLinetypeTableRecord* linetype)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbLinetypeTableRecord"));

    es = linetype->asciiDescription(locName);
    if (es == Acad::eOk) {
        str = locName;
    }
    else
        str = ArxDbgUtils::rxErrorStr(es);
    addToDataList(_T("Description"), str);

    addToDataList(_T("Pattern Length"), ArxDbgUtils::doubleToStr(linetype->patternLength(), str));

    AcDbObjectId shapeStyleId;
    const TCHAR* tmpTxt;
    int i, len;
    len = linetype->numDashes();
    for (i=0;i<len;i++) {
        str.Format(_T("--- DASH #%2d ---"), i+1);
        addToDataList(str, _T(""));
        addToDataList(_T("Length"), ArxDbgUtils::doubleToStr(linetype->dashLengthAt(i), str));

        shapeStyleId = linetype->shapeStyleAt(i);
        if (shapeStyleId != AcDbObjectId::kNull) {
            if (ArxDbgUtils::symbolIdToName(shapeStyleId, str) != Acad::eOk)
                str = _T("*ERROR*");
            addToDataList(_T("Shape Style"), str);
            addToDataList(_T("Shape Number"), ArxDbgUtils::intToStr(linetype->shapeNumberAt(i), str));
            addToDataList(_T("Shape Offset"), ArxDbgUtils::vectorToStr(linetype->shapeOffsetAt(i), str));
            addToDataList(_T("Shape Scale"), ArxDbgUtils::doubleToStr(linetype->shapeScaleAt(i), str));
            addToDataList(_T("Shape UCS Oriented"), ArxDbgUtils::booleanToStr(linetype->shapeIsUcsOrientedAt(i), str));
            addToDataList(_T("Shape Rotation"), ArxDbgUtils::angleToStr(linetype->shapeRotationAt(i), str));
            es = linetype->textAt(i, tmpTxt);
            if (es == Acad::eOk)
                addToDataList(_T("Text"), tmpTxt, true);
            else
                addToDataList(_T("Text"), ArxDbgUtils::rxErrorStr(es));
        }
    }

    addToDataList(_T("Is Scaled To Fit"), ArxDbgUtils::booleanToStr(linetype->isScaledToFit(), str));

    const TCHAR* tmpStr;
    es = linetype->comments(tmpStr);
    if (es == Acad::eOk)
        str = tmpStr;
    else
        ArxDbgUtils::rxErrorStr(es);

    addToDataList(_T("Comments"), str, true);
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (REGAPP)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbRegAppTableRecord* regApp)
{
    addSeperatorLine(_T("AcDbRegAppTableRecord"));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (TextStyle)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbTextStyleTableRecord* textStyle)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbTextStyleTableRecord"));

    es = textStyle->fileName(locName);
    if (es == Acad::eOk)
        str = locName;
    else
        str = ArxDbgUtils::rxErrorStr(es);
    addToDataList(_T("File Name"), str, true);

    es = textStyle->bigFontFileName(locName);
    if (es == Acad::eOk)
        str = locName;
    else
        str = ArxDbgUtils::rxErrorStr(es);
    addToDataList(_T("Big Font File"), str, true);

    TCHAR* typeFace;
    Adesk::Boolean isBold, isItalic;
    Charset charset;
    using namespace Autodesk::AutoCAD::PAL;
    FontUtils::FontPitch  pitch = FontUtils::FontPitch::kDefault;
    FontUtils::FontFamily family = FontUtils::FontFamily::kDoNotCare;
    es = textStyle->font(typeFace, isBold, isItalic, charset, pitch, family);
    if (es == Acad::eOk) {
        addToDataList(_T("Font Typeface"), typeFace, true);
        addToDataList(_T("Font Is Bold"), ArxDbgUtils::booleanToStr(isBold, str));
        addToDataList(_T("Font Is Italic"), ArxDbgUtils::booleanToStr(isItalic, str));
        addToDataList(_T("Font Charset"), ArxDbgUtils::intToStr(charset, str));
        int pitchAndFamily = 0;
        pitchAndFamily |= (int)pitch;
        pitchAndFamily |= (int)family;
        addToDataList(_T("Font Pitch/Family"), ArxDbgUtils::intToStr(pitchAndFamily, str));
        acutDelString(typeFace);
    }
    else
        addToDataList(_T("Font"), ArxDbgUtils::rxErrorStr(es));

    addToDataList(_T("Is Shape File"), ArxDbgUtils::booleanToStr(textStyle->isShapeFile(), str));
    addToDataList(_T("Is Vertical"), ArxDbgUtils::booleanToStr(textStyle->isVertical(), str));
    addToDataList(_T("Text Size"), ArxDbgUtils::doubleToStr(textStyle->textSize(), str));
    addToDataList(_T("Prior Size"), ArxDbgUtils::doubleToStr(textStyle->priorSize(), str));
    addToDataList(_T("X Scale"), ArxDbgUtils::doubleToStr(textStyle->xScale(), str));
    addToDataList(_T("Oblique Angle"), ArxDbgUtils::angleToStr(textStyle->obliquingAngle(), str));
    addToDataList(_T("Flag Bits"), ArxDbgUtils::intToStr(textStyle->flagBits(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (UCS)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbUCSTableRecord* ucs)
{
    CString str;

    addSeperatorLine(_T("AcDbUCSTableRecord"));

    addToDataList(_T("Origin"), ArxDbgUtils::ptToStr(ucs->origin(), str));
    addToDataList(_T("X Axis"), ArxDbgUtils::vectorToStr(ucs->xAxis(), str));
    addToDataList(_T("Y Axis"), ArxDbgUtils::vectorToStr(ucs->yAxis(), str));

// TBD: not sure how to call ucsBaseOrigin()
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (VIEW)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbViewTableRecord* view)
{
    CString str;

    addSeperatorLine(_T("AcDbViewTableRecord"));

    addToDataList(_T("Is PaperSpace View"), ArxDbgUtils::booleanToStr(view->isPaperspaceView(), str));
    addToDataList(_T("Is UCS Associated View"), ArxDbgUtils::booleanToStr(view->isUcsAssociatedToView(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::display        (VIEWPORT)
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::display(AcDbViewportTableRecord* viewport)
{
    CString str;

    addSeperatorLine(_T("AcDbViewportTableRecord"));

    addToDataList(_T("Lower Left"), ArxDbgUtils::ptToStr(viewport->lowerLeftCorner(), str));
    addToDataList(_T("Upper Right"), ArxDbgUtils::ptToStr(viewport->upperRightCorner(), str));
    addToDataList(_T("UCS Follow"), ArxDbgUtils::booleanToStr(viewport->ucsFollowMode(), str));
    addToDataList(_T("Circle Sides"), ArxDbgUtils::intToStr(viewport->circleSides(), str));
    addToDataList(_T("Fast Zooms"), ArxDbgUtils::booleanToStr(viewport->fastZoomsEnabled(), str));
    addToDataList(_T("Icon Enabled"), ArxDbgUtils::booleanToStr(viewport->iconEnabled(), str));
    addToDataList(_T("Icon At Origin"), ArxDbgUtils::booleanToStr(viewport->iconAtOrigin(), str));
    addToDataList(_T("Grid On"), ArxDbgUtils::booleanToStr(viewport->gridEnabled(), str));
    addToDataList(_T("Grid Incr"), ArxDbgUtils::ptToStr(viewport->gridIncrements(), str));
    addToDataList(_T("Snap On"), ArxDbgUtils::booleanToStr(viewport->snapEnabled(), str));
    addToDataList(_T("ISO Snap On"), ArxDbgUtils::booleanToStr(viewport->isometricSnapEnabled(), str));
    addToDataList(_T("Snap Pair"), ArxDbgUtils::intToStr(viewport->snapPair(), str));
    addToDataList(_T("Snap Angle"), ArxDbgUtils::angleToStr(viewport->snapAngle(), str));
    addToDataList(_T("Snap Base"), ArxDbgUtils::ptToStr(viewport->snapBase(), str));
    addToDataList(_T("Snap Incr"), ArxDbgUtils::ptToStr(viewport->snapIncrements(), str));
    addToDataList(_T("Is UCS Saved WIth Viewport"), ArxDbgUtils::booleanToStr(viewport->isUcsSavedWithViewport(), str));
}

/****************************************************************************
**
**  ArxDbgUiTdcDbObjectBase::displayGeCurve3d
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDbObjectBase::displayGeCurve2d(const AcGeCurve2d* curve, int edgeType)
{
    CString curveStr = _T("Curve Type");
    CString str, str2;

    if (curve->isKindOf(AcGe::kLineSeg2d)) {
        ASSERT(edgeType == AcDbHatch::kLine);
        const AcGeLineSeg2d* line = static_cast<const AcGeLineSeg2d*>(curve);
        addToDataList(curveStr, _T("Line"));
        addToDataList(_T("Start Point"), ArxDbgUtils::ptToStr(line->startPoint(), str));
        addToDataList(_T("End Point"), ArxDbgUtils::ptToStr(line->endPoint(), str));
    }
    else if (curve->isKindOf(AcGe::kCircArc2d)) {
        ASSERT(edgeType == AcDbHatch::kCirArc);
        const AcGeCircArc2d* arc = static_cast<const AcGeCircArc2d*>(curve);
        if (arc->isClosed()) {
            addToDataList(curveStr, _T("Circle"));
            addToDataList(_T("Center"), ArxDbgUtils::ptToStr(arc->center(), str));
            addToDataList(_T("Radius"), ArxDbgUtils::doubleToStr(arc->radius(), str));

        }
        else {
            addToDataList(curveStr, _T("Arc"));
            addToDataList(_T("Center"), ArxDbgUtils::ptToStr(arc->center(), str));
            addToDataList(_T("Radius"), ArxDbgUtils::doubleToStr(arc->radius(), str));
            addToDataList(_T("Start Angle"), ArxDbgUtils::angleToStr(arc->startAng(), str));
            addToDataList(_T("End Angle"), ArxDbgUtils::angleToStr(arc->endAng(), str));
        }
    }
    else if (curve->isKindOf(AcGe::kEllipArc2d)) {
        ASSERT(edgeType == AcDbHatch::kEllArc);
        const AcGeEllipArc2d* ellip = static_cast<const AcGeEllipArc2d*>(curve);
        if (ellip->isClosed()) {
            addToDataList(curveStr, _T("Ellipse"));
            addToDataList(_T("Center"), ArxDbgUtils::ptToStr(ellip->center(), str));
            addToDataList(_T("Minor Radius"), ArxDbgUtils::doubleToStr(ellip->minorRadius(), str));
            addToDataList(_T("Major Radius"), ArxDbgUtils::doubleToStr(ellip->majorRadius(), str));
            addToDataList(_T("Minor Axis"), ArxDbgUtils::vectorToStr(ellip->minorAxis(), str));
            addToDataList(_T("Major Axis"), ArxDbgUtils::vectorToStr(ellip->majorAxis(), str));
        }
        else {
            addToDataList(curveStr, _T("Elliptical Arc"));
            addToDataList(_T("Center"), ArxDbgUtils::ptToStr(ellip->center(), str));
            addToDataList(_T("Minor Radius"), ArxDbgUtils::doubleToStr(ellip->minorRadius(), str));
            addToDataList(_T("Major Radius"), ArxDbgUtils::doubleToStr(ellip->majorRadius(), str));
            addToDataList(_T("Minor Axis"), ArxDbgUtils::vectorToStr(ellip->minorAxis(), str));
            addToDataList(_T("Major Axis"), ArxDbgUtils::vectorToStr(ellip->majorAxis(), str));
            addToDataList(_T("Start Angle"), ArxDbgUtils::angleToStr(ellip->startAng(), str));
            addToDataList(_T("End Angle"), ArxDbgUtils::angleToStr(ellip->endAng(), str));
            addToDataList(_T("Start Point"), ArxDbgUtils::ptToStr(ellip->startPoint(), str));
            addToDataList(_T("End Point"), ArxDbgUtils::ptToStr(ellip->endPoint(), str));
        }
    }
    else if (curve->isKindOf(AcGe::kSplineEnt2d)) {
        ASSERT(edgeType == AcDbHatch::kSpline);
        const AcGeSplineEnt2d* spline = static_cast<const AcGeSplineEnt2d*>(curve);
        addToDataList(curveStr, _T("Spline"));
        addToDataList(_T("Is Rational"), ArxDbgUtils::booleanToStr(spline->isRational(), str));
        addToDataList(_T("Has Fit Data"), ArxDbgUtils::booleanToStr(spline->hasFitData(), str));
        addToDataList(_T("Degree"), ArxDbgUtils::intToStr(spline->degree(), str));
        addToDataList(_T("Order"), ArxDbgUtils::intToStr(spline->order(), str));
        addSeperatorLine(_T("Knots"));
        for (int i=0; i<spline->numKnots(); i++) {
            str2.Format(_T("Knot #%d"), i+1);
            addToDataList(str2, ArxDbgUtils::doubleToStr(spline->knotAt(i), str));
        }
        addSeperatorLine(_T("Control Points"));
        for (int ii=0; ii<spline->numControlPoints(); ii++) {
            str2.Format(_T("Control Pt #%d"), ii+1);
            addToDataList(str2, ArxDbgUtils::ptToStr(spline->controlPointAt(ii), str));
        }
    }
    else {
        addToDataList(_T("Curve Type"), _T("*Unknown*"));
    }
}


