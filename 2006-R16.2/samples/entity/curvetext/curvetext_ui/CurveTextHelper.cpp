// (C) Copyright 1993-2002 by Autodesk, Inc.
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

#include <acarray.h>

#include "CurveTextDialog.h"
#include "utils.h"
#include "CurveTextJig.h"
#include "CurvetextHelper.h"

///////////////////////////////////////////////////////////////////////////////
// sets the start point of the text along the curve
// uses the Jig
//
void setStart()
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;

	setStart(curvesArray[0]);
}

void setStart(AcDbObjectId id)
{
	acDocManager->disableDocumentActivation();
	actrTransactionManager->startTransaction();
	AsdkCurveText* pCurvetext;
	actrTransactionManager->getObject((AcDbObject*&)pCurvetext, id, AcDb::kForWrite);
	CCurveTextJig *pJig = new CCurveTextJig(TRUE, pCurvetext);
	pJig->doIt();
	actrTransactionManager->endTransaction();
	delete pJig;
	acDocManager->enableDocumentActivation();
}

///////////////////////////////////////////////////////////////////////////////
// sets the end point of the text along the curve
// uses the Jig
//
void setEnd()
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;

	setEnd(curvesArray[0]);
}

void setEnd(AcDbObjectId id)
{
	acDocManager->disableDocumentActivation();
	actrTransactionManager->startTransaction();
	AsdkCurveText* pCurvetext;
	actrTransactionManager->getObject((AcDbObject*&)pCurvetext, id, AcDb::kForWrite);
	CCurveTextJig *pJig = new CCurveTextJig(FALSE, pCurvetext);
	pJig->doIt();
	actrTransactionManager->endTransaction();
	delete pJig;
	acDocManager->enableDocumentActivation();
}

///////////////////////////////////////////////////////////////////////////////
//
void reverse()
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;
	reverse(curvesArray);
}

void reverse(AcDbObjectIdArray& curvesArray)
{
	AsdkCurveText *pCurveText;
	Acad::ErrorStatus es;
	for(long i=0; i<curvesArray.length(); i++)
	{
		es = acdbOpenObject(pCurveText, curvesArray[i], AcDb::kForWrite);
		if(es == Acad::eNotThatKindOfClass)
		{
			acutPrintf("\nNot a curvetext, sorry.");
			continue;
		}
		pCurveText->setReverse(!pCurveText->isReversed());
		pCurveText->close();
	}
}

///////////////////////////////////////////////////////////////////////////////
//

void RepeatText()
{
	repeatText(true);
}

void DoNotRepeatText()
{
	repeatText(false);
}

void repeatText(bool repeat)
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;
	repeatText(repeat, curvesArray);
}

void repeatText(bool repeat, AcDbObjectIdArray& curvesArray)
{
	AsdkCurveText *pCurveText;
	Acad::ErrorStatus es;
	for(long i=0; i<curvesArray.length(); i++)
	{
		es = acdbOpenObject(pCurveText, curvesArray[i], AcDb::kForWrite);
		if(es == Acad::eNotThatKindOfClass)
		{
			acutPrintf("\nNot a curvetext, sorry.");
			continue;
		}
		pCurveText->setRepeatText(repeat);
		pCurveText->close();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
void fit()
{
	setFit(true);
}

void DoNotFit()
{
	setFit(false);
}

void setFit(bool fit)
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;
	setFit(fit, curvesArray);
}

void setFit(bool fit, AcDbObjectIdArray& curvesArray)
{
	AsdkCurveText *pCurveText;
	for(long i=0; i<curvesArray.length(); i++)
	{
		AOK(acdbOpenObject(pCurveText, curvesArray[i], AcDb::kForWrite));
		pCurveText->setFit(fit);
		pCurveText->close();
	}
}

///////////////////////////////////////////////////////////////////////////////
//

void ShowCurve()
{
	ShowCurve(true);
}

void HideCurve()
{
	ShowCurve(false);
}

void
ShowCurve(bool show)
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;
	ShowCurve(show, curvesArray);
}

void
ShowCurve(bool show, AcDbObjectIdArray& curvesArray)
{
	AsdkCurveText *pCurveText;
	for(long i=0; i<curvesArray.length(); i++)
	{
		AOK(acdbOpenObject(pCurveText, curvesArray[i], AcDb::kForWrite));
		pCurveText->showCurve(show);
		pCurveText->close();
	}
}

///////////////////////////////////////////////////////////////////////////////
//

void ShowText()
{
	ShowText(true);
}

void HideText()
{
	ShowText(false);
}

void
ShowText(bool show)
{
	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;
	ShowText(show, curvesArray);
}

void
ShowText(bool show, AcDbObjectIdArray& curvesArray)
{
	AsdkCurveText *pCurveText;
	for(long i=0; i<curvesArray.length(); i++)
	{
		AOK(acdbOpenObject(pCurveText, curvesArray[i], AcDb::kForWrite));
		pCurveText->showText(show);
		pCurveText->close();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
void curveTextMulti()
{

	AcDbObjectIdArray curvesArray;

	Acad::ErrorStatus es = getCurvesSelection(curvesArray);
	if(es != Acad::eOk)
		return;

	curvetextEdit(curvesArray);
}


///////////////////////////////////////////////////////////////////////////////
//
void curvetextEdit(AcDbObjectIdArray& curvesIdArray)
{
	AcDbEntity *pEnt;
	AsdkCurveText *pCurveText;
	AcDbCurve *pCurve;
 	bool isDefault = true;
	setInitialValues(global);
	AcArray<AsdkCurveText *> newCurvetextArray;
	AcArray<AcDbCurve *> curvesArray;
	Acad::ErrorStatus es;
	class GLOBALS originalValues = global;

	// The curvesArray argument can contain 2 type of entities:
	// AsdkCurvetext and curves not already converted.
	// First, get the AsdkCurveText entities and set the default
	// values to the first one found. If there is more than one
	// AsdkCurveText entity, the other ones are compared to the
	// first one, and if their values (string, tezt size, etc.)
	// are different, then the dialog box will display "Varies"


	// Get all the AsdkCurveText entities in the array.
	//
	long i;
	for(i=0; i<curvesIdArray.length(); i++)
	{
		acdbOpenAcDbEntity(pEnt, curvesIdArray[i], AcDb::kForRead);
		pCurveText = AsdkCurveText::cast(pEnt);
		if(NULL != pCurveText)
		{
			// Initialize the default values of the global structure
			// "global" and therfore of the dialog bo if "isDefault"
			// is true. If not, compare the values of the current 
			// AsdkCurveText entity with the first one.
			//
			setInitialValues(pCurveText, global, isDefault);
			isDefault = false;
			pCurveText->close();
		}
		else
		{
			pCurve = AcDbCurve::cast(pEnt);
			if(NULL == pCurve)
				  acrx_abort("!%s@%d: %s", __FILE__, __LINE__, "Unexpected entity type");
			curvesArray.append(pCurve);
		}
	}
	// convert the non already curvetext entity into curvetext
	//
	for(i=0; i<curvesArray.length(); i++)
	{
		pCurveText = new AsdkCurveText();
		assert(pCurveText);
		// Initialize the curve with values stored in "global"
		//
		setDefaultValues(pCurveText);
		setInitialValues(pCurveText, global, isDefault);
		isDefault = false;
		pCurve = curvesArray[i];
		// The curve pointer, vital for our
		// curveText entity, has to be set BEFORE
		// calling handOverTo.
		//
		pCurveText->setCurvePtr(pCurve);
		// We switch the curve with the curvetext
		//
		es = pCurve->upgradeOpen();
		Acad::ErrorStatus es;
		es = pCurve->handOverTo(pCurveText);
		if(es != Acad::eObjectToBeDeleted)
		{
			delete pCurveText;
			pCurve->close();
			// try to restore everything to the original state
			for(int k=0; k<newCurvetextArray.length(); k++)
			{
				AOK(newCurvetextArray.at(k)->handOverTo(newCurvetextArray.at(k)));
				curvesArray.at(k)->close();
				delete newCurvetextArray.at(k);
			}
			return;
		}
		newCurvetextArray.append(pCurveText);
	}

	// create our dialog object. 
	//
	CAcModuleResourceOverride thisResource;
	CCurveTextDia dialog(CWnd::FromHandle(adsw_acadMainWnd()));

	dialog.curveTextIdArray = curvesIdArray;
	// initializes dialog default with values stored in "global"
	//
	dialog.copyGlobalState();

	AcTransaction* pTrans;
	pTrans = actrTransactionManager->startTransaction();
	dialog.pTrans = pTrans;

	if(dialog.DoModal() == IDOK)
	{
		// update the global values with the latest
		// commited changes.
		//
		dialog.updateGlobalState();
		actrTransactionManager->endTransaction();
		for(int k=0; k<newCurvetextArray.length(); k++)
			newCurvetextArray.at(k)->close();
	}
	else
	{
		// The user canceled the changes, we're setting back what
		// we've cached before calling DoModal();
		//
		actrTransactionManager->abortTransaction();
		for(int k=0; k<newCurvetextArray.length(); k++)
		{
			newCurvetextArray.at(k)->handOverTo(curvesArray.at(k));
			curvesArray.at(k)->close();
			delete newCurvetextArray.at(k);
		}
		global = originalValues;
	}
}

