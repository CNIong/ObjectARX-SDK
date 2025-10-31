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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgCmdAdeskLogo.h"
#include "ArxDbgDbAdeskLogo.h"
#include "ArxDbgDbAdeskLogoStyle.h"
#include "ArxDbgUtils.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgKeywordArray.h"
#include "ArxDbgApp.h"
#include "ArxDbgUiDlgGenericDefId.h"



/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogo"),            _T("AdeskLogo"),            ACRX_CMD_MODAL, &cmdLineMain);
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoAdd"),         _T("AdeskLogoAdd"),         ACRX_CMD_MODAL, &add);
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoModify"),      _T("AdeskLogoModify"),      ACRX_CMD_MODAL, &modify);

	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoStyle"),		_T("AdeskLogoStyle"),       ACRX_CMD_MODAL, &styles);
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoStyleAdd"),    _T("AdeskLogoStyleAdd"),    ACRX_CMD_MODAL, &styleAdd);
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoStyleModify"), _T("AdeskLogoStyleModify"), ACRX_CMD_MODAL, &styleModify);

	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoHardwire1"),   _T("AdeskLogoHardwire1"),   ACRX_CMD_MODAL, &hardwire);
	cmdStack->addCommand(appname, _T("ArxDbgAdeskLogoHardwire2"),   _T("AdeskLogoHardwire2"),   ACRX_CMD_MODAL, &hardwire2);
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::cmdLineMain
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::cmdLineMain()
{
		// ArxDbgKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxDbgKeywordArray for more details.
	ArxDbgKeywordArray kwords(ArxDbgApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));
    kwords.append(_T("Styles"), _T("Styles"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Adesk Logo options %s"), optionsStr);

    ArxDbgUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxDbgUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        add();
    else if (keywordIndex == 1)
        modify();
    else if (keywordIndex == 2)
        styles();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::add
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::add()
{
    AcDbObjectId styleId;
    if (!getLogoStyle(styleId))
        return;

    ArxDbgUiPrPoint prPt(_T("Location"), NULL);
    if (prPt.go() != ArxDbgUiPrBase::kOk)
        return;

    ArxDbgUiPrDistDef prScale(_T("Scale "), NULL, ArxDbgUiPrDist::kNoNegNoZero, prPt.value(), 1.0);
    if (prScale.go() != ArxDbgUiPrBase::kOk)
        return;

	ArxDbgUiPrEntity prEnt(_T("Select an arbitrary entity to reference (or RETURN for NONE)"), NULL);
	prEnt.setAllowNone(true);
	if (prEnt.go() == ArxDbgUiPrBase::kCancel)
		return;

    ArxDbgDbAdeskLogo* logo = new ArxDbgDbAdeskLogo;
    logo->setLocation(prPt.value());
    if (styleId != AcDbObjectId::kNull)
        logo->setLogoStyleId(styleId);

    logo->setScale(prScale.value());
	
	if (prEnt.objectId().isNull() == false)
		logo->setArbitraryReferenceId(prEnt.objectId());

    ArxDbgUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxDbgUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::modify
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::modify()
{
	ArxDbgUiPrEntity prEnt(_T("Select Adesk Logo to modify"), NULL);
	prEnt.addAllowedClass(ArxDbgDbAdeskLogo::desc());
	prEnt.setFilterLockedLayers(true);

	if (prEnt.go() != ArxDbgUiPrBase::kOk)
		return;

	ArxDbgDbAdeskLogo* logo;
	Acad::ErrorStatus es = acdbOpenObject(logo, prEnt.objectId(), AcDb::kForRead);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return;
	}
		// get current values and close (they might pick our object again!)
    AcDbObjectId styleId = logo->logoStyleId();
	AcGeScale3d curScale = logo->scale();
	AcDbObjectId curRefId = logo->arbitraryReferenceId();
	logo->close();

		// get the logo style they want
    if (!getLogoStyle(styleId))
        return;

		// get the individual scale factors
	ArxDbgUiPrDistDef prScaleX(_T("Scale X "), NULL, ArxDbgUiPrDist::kNoNegNoZero, curScale.sx);
	ArxDbgUiPrDistDef prScaleY(_T("Scale Y "), NULL, ArxDbgUiPrDist::kNoNegNoZero, curScale.sy);
	ArxDbgUiPrDistDef prScaleZ(_T("Scale Z "), NULL, ArxDbgUiPrDist::kNoNegNoZero, curScale.sz);
	
	if ((prScaleX.go() != ArxDbgUiPrBase::kOk) ||
		(prScaleY.go() != ArxDbgUiPrBase::kOk) ||
		(prScaleZ.go() != ArxDbgUiPrBase::kOk)) {
		return;
	}

	curScale.sx = prScaleX.value();
	curScale.sy = prScaleY.value();
	curScale.sz = prScaleZ.value();

	ArxDbgUiPrEntity prRefEnt(_T("Select an arbitrary entity to reference (or RETURN for NONE)"), _T("Same"));
	prRefEnt.setAllowNone(true);

	ArxDbgUiPrBase::Status stat = prRefEnt.go();
	if (stat == ArxDbgUiPrBase::kNone) 
		;	// keep same one
	else if (stat == ArxDbgUiPrBase::kOk)
		curRefId = prRefEnt.objectId();
	else
		return;

	es = acdbOpenObject(logo, prEnt.objectId(), AcDb::kForWrite);
	if (es == Acad::eOk) {
		logo->setLogoStyleId(styleId);
		logo->setScale(curScale);
		logo->setArbitraryReferenceId(curRefId);
		logo->close();
	}
	else
		ArxDbgUtils::rxErrorMsg(es);
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::styles
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::styles()
{
	ArxDbgKeywordArray kwords(ArxDbgApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Adesk Logo Style options %s"), optionsStr);

    ArxDbgUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxDbgUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        styleAdd();
    else if (keywordIndex == 1)
        styleModify();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::hardwire
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::hardwire()
{
	AcDbObjectId aecStyleId, gisStyleId;

    AcDbDictionary* testDict = ArxDbgUtils::openDictionaryForWrite(
						ArxDbgDbAdeskLogoStyle::dictName(), true,
						acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->getAt(_T("AEC"), aecStyleId) != Acad::eOk) {
            ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
            newRec->setLabel(_T("AEC"));
            newRec->setSolidFill(true);

            es = testDict->setAt(_T("AEC"), newRec, aecStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxDbgUtils::rxErrorAlert(es);
                delete newRec;
				aecStyleId = AcDbObjectId::kNull;
            }
        }
        if (testDict->getAt(_T("GIS"), gisStyleId) != Acad::eOk) {
            ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
            newRec->setLabel(_T("GIS"));
            newRec->setSolidFill(false);

            es = testDict->setAt(_T("GIS"), newRec, gisStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxDbgUtils::rxErrorAlert(es);
                delete newRec;
				gisStyleId = AcDbObjectId::kNull;
            }
        }
        testDict->close();
    }
	else {
		acutPrintf(_T("\nHardwire test failed!"));
		return;
	}

	ArxDbgDbAdeskLogo* logo;

		// add test AEC logo
	logo = new ArxDbgDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 2.0, 0.0));
	logo->setLogoStyleId(aecStyleId);
	logo->setScale(AcGeScale3d(2.0));

    ArxDbgUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxDbgUtils::addToCurrentSpaceAndClose(logo);

		// add test GIS logo
	logo = new ArxDbgDbAdeskLogo;
    logo->setLocation(AcGePoint3d::kOrigin);
	logo->setLogoStyleId(gisStyleId);

    ArxDbgUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxDbgUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::hardwire2
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::hardwire2()
{
	AcDbObjectId aecStyleId, gisStyleId;

    AcDbDictionary* testDict = ArxDbgUtils::openDictionaryForWrite(
						ArxDbgDbAdeskLogoStyle::dictName(), true,
						acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->getAt(_T("AEC"), aecStyleId) != Acad::eOk) {
            ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
            newRec->setLabel(_T("AEC 2"));
            newRec->setSolidFill(true);

            es = testDict->setAt(_T("AEC"), newRec, aecStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxDbgUtils::rxErrorAlert(es);
                delete newRec;
				aecStyleId = AcDbObjectId::kNull;
            }
        }
        if (testDict->getAt(_T("GIS"), gisStyleId) != Acad::eOk) {
            ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
            newRec->setLabel(_T("GIS 2"));
            newRec->setSolidFill(false);

            es = testDict->setAt(_T("GIS"), newRec, gisStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxDbgUtils::rxErrorAlert(es);
                delete newRec;
				gisStyleId = AcDbObjectId::kNull;
            }
        }
        testDict->close();
    }
	else {
		acutPrintf(_T("\nHardwire test failed!"));
		return;
	}

	ArxDbgDbAdeskLogo* logo;

		// add test AEC logo
	logo = new ArxDbgDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 10.0, 0.0));
	logo->setLogoStyleId(aecStyleId);
	logo->setScale(AcGeScale3d(2.0));

    ArxDbgUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxDbgUtils::addToCurrentSpaceAndClose(logo);

		// add test GIS logo
	logo = new ArxDbgDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 8.0, 0.0));
	logo->setLogoStyleId(gisStyleId);

    ArxDbgUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxDbgUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::getLogoStyle
**
**  **jma
**
*************************************/

bool
ArxDbgCmdAdeskLogo::getLogoStyle(AcDbObjectId& styleId)
{
		// try to get the standard style, which will hardwire it if it doesn't
		// yet exist
	AcDbObjectId standardStyleId =
				ArxDbgDbAdeskLogoStyle::getStandardStyle(acdbHostApplicationServices()->workingDatabase(), true);

	SdStrObjIdList logoStyles;
	AcDbObjectId logoStyleDictId = ArxDbgUtils::getRegularDictionaryId(
						ArxDbgDbAdeskLogoStyle::dictName(), true, acdbHostApplicationServices()->workingDatabase());

	ArxDbgUtils::collectDictionaryEntryNames(logoStyleDictId, logoStyles, ArxDbgDbAdeskLogoStyle::desc());

	if (logoStyles.Count() == 0) {
		ArxDbgUtils::alertBox(_T("There are no Adesk Logo Styles to choose from."));
		return false;
	}

	ArxDbgUiDlgGenericDefId dbox(acedGetAcadDwgView(),
									logoStyles, styleId, false);
	dbox.setDboxTitle(_T("Autodesk Logo Styles"));

	if (dbox.DoModal() == IDOK) {
		styleId = dbox.getSelectedId();
		return true;
	}

	return false;
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::styleAdd
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::styleAdd()
{
    ArxDbgUiPrString prName(_T("Logo Style Name"), false);
    ArxDbgUiPrString prLabel(_T("Label"), true);

    if ((prName.go() != ArxDbgUiPrBase::kOk) ||
        (prLabel.go() != ArxDbgUiPrBase::kOk))
        return;

    if (acdbSNValid(prName.value(), false) != RTNORM) {
        acedAlert(_T("Invalid symbol name!"));
        return;
    }

    bool doSolidFill = true;
    if (ArxDbgUtils::yesNoPromptDef(_T("Use solid fill "), doSolidFill, true) != ArxDbgUiPrBase::kOk)
        return;

    AcDbDictionary* testDict = ArxDbgUtils::openDictionaryForWrite(ArxDbgDbAdeskLogoStyle::dictName(), true, acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->has(prName.value()))
            ArxDbgUtils::stopAlertBox(_T("Sorry, there is already an entry with that name."));
        else {
            ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
            newRec->setLabel(prLabel.value());
            newRec->setSolidFill(doSolidFill);

            AcDbObjectId objId;
            es = testDict->setAt(prName.value(), newRec, objId);
            if (es == Acad::eOk) {
                ArxDbgUtils::alertBox(_T("Added Logo Style successfully!"));
                newRec->close();
            }
            else {
                ArxDbgUtils::rxErrorAlert(es);
                delete newRec;
            }
        }
        testDict->close();
    }
}

/****************************************************************************
**
**  ArxDbgCmdAdeskLogo::styleModify
**
**  **jma
**
*************************************/

void
ArxDbgCmdAdeskLogo::styleModify()
{
	AcDbObjectId styleId;

		// get the logo style they want to modify
    if (!getLogoStyle(styleId))
        return;

	ArxDbgDbAdeskLogoStyle* logoStyle;
	Acad::ErrorStatus es = acdbOpenObject(logoStyle, styleId, AcDb::kForWrite);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return;
	}

    ArxDbgUiPrStringDef prLabel(_T("Label "), logoStyle->label(), true);

    if (prLabel.go() != ArxDbgUiPrBase::kOk) {
		logoStyle->close();
        return;
	}

    bool doSolidFill = true;
    if (ArxDbgUtils::yesNoPromptDef(_T("Use solid fill "), doSolidFill, logoStyle->isSolidFill()) != ArxDbgUiPrBase::kOk) {
		logoStyle->close();
        return;
	}

	logoStyle->setLabel(prLabel.value());
	logoStyle->setSolidFill(doSolidFill);
	logoStyle->close();
}
