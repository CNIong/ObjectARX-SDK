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
//

#ifndef ARXDBG_UTILS_H
#define ARXDBG_UTILS_H

#include "SdStrList.h"
#include "SdStrObjId.h"
#include "ArxDbgUiPrompts.h"


struct ArxDbgUtils {

    enum Color {
        kByblock    = 0,
        kRed        = 1,
        kYellow     = 2,
        kGreen      = 3,
        kCyan       = 4,
        kBlue       = 5,
        kMagenta    = 6,
        kWhite      = 7,
        kBylayer    = 256
    };

    enum LinetypeFile {
        kStandardLinetypes,
        kComplexLinetypes,
        kAllLinetypes
    };

    enum LinearUnit {
        kCurrentLU      = -1,
        kScientific     = 1,
        kDecimal        = 2,
        kEngineering    = 3,
        kArchitectural  = 4,
        kFractional     = 5
    };

    enum AngularUnit {
        kCurrentAU      = -1,
        kDegrees        = 0,
        kDegMinSec      = 1,
        kGrads          = 2,
        kRadians        = 3,
        kSurveyor       = 4
    };

    enum Precision {
        kCurrentPrecLU   = -1,
        kCurrentPrecAU   = -1
    };


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// ACAD UI UTILITIES ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void         rxErrorMsg(Acad::ErrorStatus msgId);
static void         rxErrorAlert(Acad::ErrorStatus msgId);
static const TCHAR*	rxErrorStr(Acad::ErrorStatus msgId);
static void			stubMsg(LPCTSTR msg);

static Acad::ErrorStatus    findStandardAcadFile(LPCTSTR fileToFind, CString& foundFile);

static AcDbEntity*	selectEntity(LPCTSTR prompt, AcDb::OpenMode openMode = AcDb::kForRead);
static bool         selectEntity(LPCTSTR prompt, AcDbObjectId& objId);
static bool         selectEntityOrObject(AcDbObjectId& objId);

static LPCTSTR      ptToStr(const AcGePoint3d& pt, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      ptToStr(const AcGePoint2d& pt, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      vectorToStr(const AcGeVector3d& vec, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      vectorToStr(const AcGeVector2d& vec, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      angleToStr(const double angle, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      doubleToStr(const double realVal, CString& str, int unit = -1, int prec = -1);
static LPCTSTR      intToStr(const int intVal, CString& str);
static LPCTSTR      intDbIdToStr(const Adesk::IntDbId intVal, CString& str);
static LPCTSTR      ptrToStr(void* ptr, CString& str);
static LPCTSTR		dbToStr(AcDbDatabase* db, CString& str);
static LPCTSTR      booleanToStr(bool b, CString& str);
static LPCTSTR      colorToStr(int color, CString& str, bool convertStandard = true);
static LPCTSTR      objToHandleStr(const AcDbObject* obj, CString& str);
static LPCTSTR      objToEnameStr(const AcDbObject* obj, CString& str);
static LPCTSTR      objToClassStr(const AcRxObject* obj);
static LPCTSTR		objToClassAndHandleStr(const AcDbObjectId& objId, CString& str);
static LPCTSTR		objToClassAndHandleStr(const AcDbObject* obj, CString& str);
static LPCTSTR		textModeToStr(AcDb::TextHorzMode horizMode, CString& str);
static LPCTSTR		textModeToStr(AcDb::TextVertMode vertMode, CString& str);
static LPCTSTR		vertexTypeToStr(AcDb::Vertex3dType vertexType, CString& str);
static LPCTSTR		hatchTypeToStr(AcDbHatch::HatchPatternType hatchType, CString& str);
static LPCTSTR		hatchStyleToStr(AcDbHatch::HatchStyle style, CString& str);
static LPCTSTR		hatchLoopTypeToStr(Adesk::Int32 loopType, CString& str);
static LPCTSTR		mtextAttachmentTypeToStr(AcDbMText::AttachmentPoint type, CString& str);
static LPCTSTR		mtextFlowDirTypeToStr(AcDbMText::FlowDirection type, CString& str);
static LPCTSTR		lineSpacingTypeToStr(AcDb::LineSpacingStyle type, CString& str);
static LPCTSTR		proxyMetafileTypeToStr(AcDbProxyEntity::GraphicsMetafileType type, CString& str);
static LPCTSTR		lineWeightTypeToStr(AcDb::LineWeight type, CString& str);
static LPCTSTR		mergeStyleToStr(AcDb::DuplicateRecordCloning type, CString& str);
static LPCTSTR		standardScaleTypeToStr(AcDbViewport::StandardScaleType type, CString& str);
static LPCTSTR		dwgVersionToStr(AcDb::AcDbDwgVersion type, CString& str);
static LPCTSTR		orthoViewToStr(AcDb::OrthographicView type, CString& str);
static LPCTSTR		measurementTypeToStr(AcDb::MeasurementValue type, CString& str);
static LPCTSTR		unitTypeToStr(AcDb::UnitsValue type, CString& str);
static LPCTSTR		xrefStatusToStr(AcDb::XrefStatus stat, CString& str);
static LPCTSTR		saveFormatToStr(AcApDocument::SaveFormat type, CString& str);
static LPCTSTR		longTransactionTypeToStr(int type, CString& str);
static LPCTSTR		docLockModeToStr(AcAp::DocLockMode activity, CString& str);
static LPCTSTR		dateToStr(const AcDbDate& date, CString& str);
static LPCTSTR		promptStatusToStr(Acad::PromptStatus stat, CString& str);
static LPCTSTR		initFlagsToStr(int initFlags, CString& str);
static LPCTSTR		deepCloneContextToStr(AcDb::DeepCloneType context, CString& str);
static LPCTSTR		filerTypeToStr(AcDb::FilerType type, CString& str);
static LPCTSTR		osnapToStr(int osnapMode, CString& str);
static LPCTSTR		doubleArray3dToStr(double array[], CString& str);
static LPCTSTR		doubleArray2dToStr(double array[], CString& str);

static void			stuffAcadCmdLine(const CString& str);
static void         clearAcadCmdLine();

static void			printIdMap(AcDbIdMapping* idMap, LPCTSTR msgStr);

static Acad::ErrorStatus	getPlinePointArrayFromUser(AcGePoint3dArray& vertices);
static void                 grdrawPline(const AcGePoint3dArray& pts, BOOL close, BOOL hilite);

static void                 debugPause(LPCTSTR msg);

static Acad::ErrorStatus    getFileName(bool isForWrite, LPCTSTR prompt,
                                    LPCTSTR def, LPCTSTR ext, CString& fname,
                                    bool defIsDirectory = true,
                                    bool allowArbitraryExt = false);
static Acad::ErrorStatus    getFileNameForRead(LPCTSTR prompt, LPCTSTR def,
                                    LPCTSTR ext, CString& fname,
                                    bool defIsDirectory = true,
                                    bool allowArbitraryExt = false);
static Acad::ErrorStatus    getFileNameForWrite(LPCTSTR prompt, LPCTSTR def,
                                    LPCTSTR ext, CString& fname,
                                    bool defIsDirectory = true,
                                    bool allowArbitraryExt = false);

static ArxDbgUiPrBase::Status    yesNoPrompt(LPCTSTR msg, bool& answer);
static ArxDbgUiPrBase::Status    yesNoPromptDef(LPCTSTR msg, bool& answer, bool def);
static ArxDbgUiPrBase::Status    getNewSymbolName(LPCTSTR msg, AcRxClass* symType, CString& symName);
static ArxDbgUiPrBase::Status    getExistingSymbolName(LPCTSTR msg, AcRxClass* symType,
										CString& symName, bool allowPipes = true);
static bool       getEntityOrObject(AcDbObjectId& objId);


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// UI UTILITIES /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void    alertBox(LPCTSTR msg);
static void    stopAlertBox(LPCTSTR msg);
static void    infoAlertBox(LPCTSTR msg);
static void    stubAlert(LPCTSTR msg);
static UINT    yesNoAlert(LPCTSTR msg, UINT defButton = IDYES);
static UINT    yesNoCancelAlert(LPCTSTR msg, UINT defButton = IDCANCEL);

    // wrappers for common list box operations
static void    fillListBox(const SdStrList& slist, CListBox& lb, int defIndex = 0);
static void    fillListBox(const SdStrObjIdList& slist, CListBox& lb, int defIndex = 0);
static void    fillListBox(const SdStrObjIdList& slist, CComboBox& cb, int defIndex = 0);

    // wrappers for enabling/hiding dialog items
static void    enableDlgItem(CWnd* parentWnd, UINT resId, BOOL enableIt);
static void    hideDlgItem(CWnd* parentWnd, UINT resId, BOOL hideIt);

static int		getCurSel(const CListCtrl& listCtrl);
static BOOL		setCurSel(CListCtrl& listCtrl, int index);

    // wrapper for CFileDialog
static BOOL    getFname(LPCTSTR title, LPCTSTR ext, LPCTSTR defFname, CString& fname);


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// ACAD DB UTILITIES ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static Acad::ErrorStatus    objIdToEname(const AcDbObjectId& objId, ads_name& ent);
static Acad::ErrorStatus    enameToObjId(ads_name ent, AcDbObjectId& objId);
static Acad::ErrorStatus    handleStrToObjId(AcDbDatabase* db, LPCTSTR handleStr, AcDbObjectId& objId, bool speak = true);

static LPCTSTR				objIdToHandleStr(const AcDbObjectId& objId, CString& str);

    // clone wrappers
static Acad::ErrorStatus    cloneObjects(AcDbDatabase* db, const AcDbObjectId& entToClone,
                                        const AcDbObjectId& ownerBlockId,
                                        bool debugSpeak = false);
static Acad::ErrorStatus    cloneObjects(AcDbDatabase* db, const AcDbObjectIdArray& entsToClone,
                                        const AcDbObjectId& ownerBlockId,
                                        bool debugSpeak = false);
static Acad::ErrorStatus    cloneAndXformObjects(AcDbDatabase* db, const AcDbObjectId& entToClone,
                                        const AcDbObjectId& ownerBlockId, const AcGeMatrix3d& xformMat,
                                        bool debugSpeak = false);
static Acad::ErrorStatus    cloneAndXformObjects(AcDbDatabase* db, const AcDbObjectIdArray& entsToClone,
                                        const AcDbObjectId& ownerBlockId, const AcGeMatrix3d& xformMat,
                                        bool debugSpeak = false);
    // polyline utility functions
static bool			plineHasWidth(const AcDb2dPolyline* pline);
static bool			plineHasWidth(const AcDbPolyline* pline);
static bool			plineHasZeroLengthSegments(const AcDbPolyline* pline);
static int			numSegments(const AcDbPolyline* pline);
static void			collectVertices(const AcDb2dPolyline* pline, AcGePoint3dArray& pts,
                                        AcGeDoubleArray& bulges, bool asWcsPts = true);
static void			collectVertices(const AcDb2dPolyline* pline, AcGePoint3dArray& pts, AcDbIntArray& types,
                                        AcGeDoubleArray& bulges, AcGeDoubleArray& startWidths, 
                                        AcGeDoubleArray& endWidths, bool& hasWidth);
static void			collectVertices(const AcDb3dPolyline* pline, AcGePoint3dArray& pts);
static void			collectVertices(const AcDbPolyFaceMesh* pface, AcDbObjectIdArray& vfaces, AcGePoint3dArray& pts);
static bool			collectVertices(const AcDbPolygonMesh* pmesh, AcGePoint3dArray& pts, int& mSize, int& nSize);

static bool         isPaperSpace(AcDbDatabase* db);

    // UCS/Geometry stuff relative to a particular database
static void             transformToWcs(AcDbEntity* ent, AcDbDatabase* db);
static void             transformToUcs(AcDbEntity* ent, AcDbDatabase* db);

static AcGeVector3d		getUcsXAxis(AcDbDatabase* pDb);
static AcGeVector3d     getUcsYAxis(AcDbDatabase* pDb);
static AcGeVector3d     getUcsZAxis(AcDbDatabase* pDb);

static AcGePlane		getUcsPlane(AcDbDatabase* pDb);
static void             getUcsToWcsMatrix(AcGeMatrix3d& m, AcDbDatabase* pDb);
static void             getWcsToUcsMatrix(AcGeMatrix3d& m, AcDbDatabase* pDb);
static void             getUcsToWcsOriginMatrix(AcGeMatrix3d& m, const AcGePoint3d& wcsBasePt, AcDbDatabase* pDb);
static void             getEcsPlane(const AcGeVector3d& entNormal, AcGePlane& ecsPlane);
static void             getEcsPlane(const AcGePoint3d& origin, const AcGeVector3d& entNormal, AcGePlane& ecsPlane, AcGeVector3d& ecsXAxis);
static void             getEcsXAxis(const AcGeVector3d& ecsZAxis, AcGeVector3d& xAxis);
static void             getEcsToWcsMatrix(const AcGePoint3d& origin, const AcGeVector3d& zAxis, AcGeMatrix3d& mat);

	// these functions all assume current document for the AcDbDatabase*
static AcGePoint3d      wcsToUcs(const AcGePoint3d& pt);
static AcGeVector3d     wcsToUcs(const AcGeVector3d& vec);
static void             wcsToUcs(AcGePoint3dArray& ptArray);
static AcGePoint3d      ucsToWcs(const AcGePoint3d& pt);
static AcGeVector3d     ucsToWcs(const AcGeVector3d& vec);
static void             ucsToWcs(AcGePoint3dArray& ptArray);
static AcGePoint3d      ecsToWcs(const AcGePoint3d& pt, const AcGeVector3d& entNormal);
static AcGeVector3d     ecsToWcs(const AcGeVector3d& vec, const AcGeVector3d& entNormal);
static AcGePoint2d      ucsToDcs(const AcGePoint3d& pt);
static AcGePoint3d      dcsToUcs(const AcGePoint2d& pt);

static void             getAllDocuments(AcDbVoidPtrArray& docPtrs);

static Acad::ErrorStatus    verifyClassType(const AcDbObject* obj, AcRxClass* classType);
static Acad::ErrorStatus    verifyEntityReference(const AcDbEntity* ent,
    const AcDbObjectId& idToValidate,
    AcRxClass* classType, bool allowNull,
    bool allowErased);

/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ACAD DICTIONARY UTILITIES //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static AcDbObjectId		getRegularDictionaryId(LPCTSTR dictName, bool createIfNotFound, AcDbDatabase* db);
static AcDbObjectId		getSubDictionaryId(LPCTSTR dictName, bool createIfNotFound,
                                AcDbDictionary* parentDict);

static AcDbDictionary*	openDictionaryForRead(LPCTSTR dictName, AcDbDatabase* db);
static AcDbDictionary*  openDictionaryForRead(LPCTSTR dictName, const AcDbObjectId& parentDict);
static AcDbDictionary*  openDictionaryForRead(LPCTSTR dictName, AcDbDictionary* parentDict);

static AcDbDictionary*  openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound, AcDbDatabase* db);
static AcDbDictionary*  openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound, const AcDbObjectId& parentDict);
static AcDbDictionary*  openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound, AcDbDictionary* parentDict);

static Acad::ErrorStatus	collectDictionaryEntryNames(const AcDbObjectId& dictId, SdStrObjIdList& list, AcRxClass* classType);
static bool    lookUpDictEntryName(const AcDbObjectId& objId, CString& entryName);

    // extension dictionary routines
static AcDbDictionary*    openExtDictForRead(const AcDbObject* obj);
static AcDbDictionary*    openExtDictForWrite(AcDbObject* obj, bool createIfNotFound);


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// ACAD SYMBOL TABLE UTILITIES //////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static Acad::ErrorStatus    symbolIdToName(const AcDbObjectId& symbolId, CString& name);
static Acad::ErrorStatus    mlineStyleIdToName(const AcDbObjectId& mlineStyleId, CString& name);
static Acad::ErrorStatus    nameToSymbolId(AcRxClass* symTblClass, LPCTSTR name,
                                        AcDbObjectId& symbolId, AcDbDatabase* db);

static bool                 symbolExists(AcRxClass* symTblClass, LPCTSTR name, AcDbDatabase* db);
static AcDbSymbolTable*     openSymbolTable(AcRxClass* classType, AcDb::OpenMode mode, AcDbDatabase* db);
static Acad::ErrorStatus    collectSymbolIds(AcRxClass* symTblClass, AcDbObjectIdArray& objIds, AcDbDatabase* db);
static Acad::ErrorStatus	collectBlockIds(SdStrObjIdList& list, bool excludeMsPs,
											bool excludeXref,
											bool excludeAnonymous, AcDbDatabase* db);
static Acad::ErrorStatus    addNewSymbolAndClose(AcDbSymbolTable* symTbl, AcDbSymbolTableRecord* newRecord);

static Acad::ErrorStatus    addNewLayer(LPCTSTR layerName, AcDbDatabase* db);

static Acad::ErrorStatus    defineNewBlock(LPCTSTR blkName, AcDbBlockTableRecord*& newBlkRec,
                                        AcDbObjectId& newBlkRecId, AcDbDatabase* db);
static Acad::ErrorStatus    defineNewBlock(LPCTSTR blkName, AcDbBlockTableRecord*& newBlkRec,
                                        AcDbDatabase* db);
static Acad::ErrorStatus    defineNewBlock(LPCTSTR blkName, AcDbObjectId& newBlkRecId,
                                        AcDbDatabase* db);
static Acad::ErrorStatus    defineNewAnonymousBlock(AcDbBlockTableRecord*& newBlkRec,
                                        AcDbObjectId& newBlkRecId, AcDbDatabase* db);
static Acad::ErrorStatus    defineNewAnonymousBlock(AcDbBlockTableRecord*& newBlkRec,
                                        AcDbDatabase* db);
static Acad::ErrorStatus    defineNewAnonymousBlock(AcDbObjectId& newBlkRecId,
                                        AcDbDatabase* db);

static Acad::ErrorStatus        openBlockDef(LPCTSTR blkName, AcDbBlockTableRecord*& blkRec,
                                            AcDb::OpenMode mode, AcDbDatabase* db);
static AcDbBlockTableRecord*    openCurrentSpaceBlock(AcDb::OpenMode mode, AcDbDatabase* db);

static Acad::ErrorStatus    addToCurrentSpace(AcDbEntity* newEnt, AcDbDatabase* db);
static Acad::ErrorStatus    addToCurrentSpace(AcDbEntity* newEnt);
static Acad::ErrorStatus    addToCurrentSpaceAndClose(AcDbEntity* newEnt, AcDbDatabase* db);
static Acad::ErrorStatus    addToCurrentSpaceAndClose(AcDbEntity* newEnt);

static bool					isOnLockedLayer(AcDbObjectId& id, bool printMsg);
static bool					isOnLockedLayer(AcDbEntity* ent, bool printMsg);

};


/////////////////////////////////////////////////////////////////////

inline void
copyAdsPt(ads_point pt1, ads_point pt2)
{
    pt1[0] = pt2[0];
    pt1[1] = pt2[1];
    pt1[2] = pt2[2];
}

/////////////////////////////////////////////////////////////////////

inline void
copyEname(ads_name ename1, ads_name ename2)
{
    ename1[0] = ename2[0];
    ename1[1] = ename2[1];
}

/////////////////////////////////////////////////////////////////////



#endif    // ARXDBG_UTILS_H
