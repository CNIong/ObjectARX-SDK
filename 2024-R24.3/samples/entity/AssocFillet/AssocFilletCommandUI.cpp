//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Simple command-line UI for the ASSOCFILLET command. Look at the 
// implementation of the assocFilletCommandUI() function.
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "acedsubsel.h"
#include "dbobjptr2.h"
#include "eoktest.h"
#include "AssocFilletActionBody.h"
#include "AcDbAssocManager.h"
#include "acdbabb.h"   // AcDb::  abbreviations
#include "adeskabb.h"  // Adesk:: abbreviations

// Always use AcDbSmartObjectPointer
//
#define AcDbObjectPointer AcDbSmartObjectPointer


static ErrorStatus promptForFilletRadius(double          defaultRadius,
                                         const AcString& defaultRadiusExpression,
                                         double&         radiusOut,
                                         AcString&       radiusExpressionOut)
{
    radiusOut           = defaultRadius;
    radiusExpressionOut = defaultRadiusExpression;

    AcString prompt;
    if (defaultRadiusExpression.isEmpty())
        prompt.format(L"\nFillet radius [Expression] <%g>: ", defaultRadius);
    else
        prompt.format(L"\nFillet radius [Expression] <%s>: ", (const wchar_t*)defaultRadiusExpression);

    double radius = 0.0;
    acedInitGet(RSG_NONEG, L"Expression");
    int ret = acedGetDist(nullptr, prompt, &radius);

    ErrorStatus err = eOk;
    switch (ret)
    {
    case RTNONE:
        break;
    case RTNORM:
        radiusOut = radius;
        radiusExpressionOut = L"";
        break;
    case RTKWORD:
        {
            wchar_t expression[133];
            acedInitGet(RSG_NONULL, nullptr);
            ret = acedGetString(1, L"\nFillet radius expression: ", expression);
            if (ret == RTNORM)
                radiusExpressionOut = expression;
            else
                err = eInvalidInput;
        }
        break;
    default:
        err = eInvalidInput;
        break;
    }
    return err;
}


static ErrorStatus promptForTrimInputEdge(int             index, 
                                          bool            defaultTrimInputEdge, 
                                          const AcString& defaultTrimInputEdgeExpression,
                                          bool&           trimInputEdgeOut, 
                                          AcString&       trimInputEdgeExpressionOut)
{
    trimInputEdgeOut           = defaultTrimInputEdge;
    trimInputEdgeExpressionOut = defaultTrimInputEdgeExpression;

    AcString prompt;
    const AcString defaultString = !defaultTrimInputEdgeExpression.isEmpty() ? defaultTrimInputEdgeExpression 
                                   : defaultTrimInputEdge ? L"Yes" : L"No";
    prompt.format(L"\nTrim %s curve [Yes/No/Expression] <%s>: ", index == 0 ? L"first " : L"second", (const wchar_t*)defaultString);

    wchar_t kword[133];
    acedInitGet(0, L"Yes No Expression");
    int ret = acedGetKword(prompt, kword);

    ErrorStatus err = eOk;
    switch (ret)
    {
    case RTNONE:
        break;
    case RTNORM:
        if (AcString(kword) == L"Expression")
        {
            wchar_t expression[133];
            acedInitGet(RSG_NONULL, nullptr);
            ret = acedGetString(1, L"\nExpression: ", expression);
            if (ret == RTNORM)
                trimInputEdgeExpressionOut = expression;
            else
                err = eInvalidInput;
        }
        else
        {
            trimInputEdgeOut = AcString(kword) == L"Yes";
            trimInputEdgeExpressionOut = L"";
        }
        break;
    default:
        err = eInvalidInput;
        break;
    }
    return err;
}


static void printDefaults(double          radius, 
                          const AcString& radiusExpression, 
                          const bool      trimInputEdge[2], 
                          const AcString  trimInputEdgeExpression[2])
{
    AcString msg;
    msg.format(L"\nFillet radius=%g", radius);
    if (!radiusExpression.isEmpty())
    {
        msg += L", Expression=" + radiusExpression;
    }
    for (int i = 0; i < 2; i++)
    {
        msg += AcString(L", Trim ") + (i == 0 ? L"first" : L"second") + AcString(L" edge=") + (trimInputEdge[i] ? L"Yes" : L"No");
        if (!trimInputEdgeExpression[i].isEmpty())
        {
            msg += L", Expression=" + trimInputEdgeExpression[i];
        }
    }
    msg += L"\n";
    const wchar_t* const pMsg = (const wchar_t*)msg;
    acutPrintf(pMsg);
}


class SelectionSetFreeer
{
public:
    explicit SelectionSetFreeer(ads_name selectionSet)
    {
        mSelectionSet[0] = selectionSet[0];
        mSelectionSet[1] = selectionSet[1];
    }
    ~SelectionSetFreeer()
    {
        acedSSFree(mSelectionSet);
    }
private:
    ads_name mSelectionSet;
};


static ErrorStatus extractPickPoint(resbuf* pSelInfo, AcGePoint3d& pickPoint)
{
    resbuf* pRb = pSelInfo;
    while (pRb != nullptr && pRb->restype != RT3DPOINT)
    {
        pRb = pRb->rbnext;
    }
    if (pRb == nullptr)
        return eInvalidResBuf;

    pickPoint = AcGePoint3d(pRb->resval.rpoint[0], pRb->resval.rpoint[1], pRb->resval.rpoint[2]);
    return eOk;
}


static ErrorStatus selectEdge(const AcString& prompt, AcDbEdgeRef& selectedEdge, AcGePoint3d& pickPoint)
{
    selectedEdge.reset();
    pickPoint = AcGePoint3d::kOrigin;

    AcDbFullSubentPath fullSubentPath;

    const wchar_t* prompts[2] = { prompt.kACharPtr(), L"", };
    ads_name selectionSet;
    if (acedSSGet(L"_:$:S:U", prompts, nullptr, nullptr, selectionSet) != RTNORM)
        return eInvalidInput;
    SelectionSetFreeer freeer(selectionSet);

    Adesk::Int32 entityCount = -1;
    if (acedSSLength(selectionSet, &entityCount) != RTNORM || entityCount <= 0)
        return eInvalidInput;

    Adesk::Int32 subEntityCount = -1;
    if (acedSSSubentLength(selectionSet, 0, &subEntityCount) == RTNORM && subEntityCount > 0)
    {
        // Subentity selected, choose the edge subentity in case other
        // subentity types have also been selected

        for (int i = 0; i < subEntityCount; i++)
        {
            AcDbFullSubentPath fullSubentPath1;
            if (!VERIFY(acedSSSubentName(selectionSet, 0, i, fullSubentPath1) == RTNORM))
                continue;
            if (fullSubentPath1.subentId().type() != kEdgeSubentType)
                continue;

            resbuf* pSelInfo = nullptr;
            if (!VERIFY(acedSSSubentNameX(&pSelInfo, selectionSet, 0, i, 0) == RTNORM))
                return eInvalidInput;
            extractPickPoint(pSelInfo, pickPoint);
            acutRelRb(pSelInfo);

            fullSubentPath = fullSubentPath1;
            break;
        }
    }
    else
    {
        // Whole entity selected
        
        ads_name ent;
        if (!VERIFY(acedSSName(selectionSet, 0, ent) == RTNORM))
            return eInvalidInput;
        AcDbObjectId entityId;
        eOkVerify(acdbGetObjectId(entityId, ent));

        // AcDbAssocPersSubentIdPEs on entities than only expose a single edge
        // subentitiy (such as AcDbLine, AcDbArc, AcDbCircle, AcDbEllipse, 
        // AcDbSpline) ignore the index, but when asked for subentity ids,
        // they return index 1
        //
        //const AcDbSubentId singleEdgeSubentId(kEdgeSubentType, 1);

        fullSubentPath = AcDbFullSubentPath(entityId, AcDbSubentId() /*singleEdgeSubentId*/);

        resbuf* pSelInfo = nullptr;
        if (!VERIFY(acedSSNameX(&pSelInfo, selectionSet, 0) == RTNORM))
            return eInvalidInput;
        extractPickPoint(pSelInfo, pickPoint);
        acutRelRb(pSelInfo);
    }
    if (fullSubentPath.objectIds().isEmpty())
        return eInvalidInput;

    selectedEdge = AcDbEdgeRef(fullSubentPath);
    return eOk;
}


void getVars(double& filletRadius, bool& filletTrimEdge)
{
    resbuf rb;
    acedGetVar(L"FILLETRAD", &rb);
    filletRadius = rb.resval.rreal;
    acedGetVar(L"TRIMMODE", &rb);
    filletTrimEdge = rb.resval.rint != 0;
}


void setVars(double filletRadius, bool filletTrimEdge)
{
    resbuf rb;
    rb.restype = RTREAL;
    rb.resval.rreal = filletRadius;
    acedSetVar(L"FILLETRAD", &rb);
    rb.restype = RTSHORT;
    rb.resval.rint = filletTrimEdge ? 1 : 0;
    acedSetVar(L"TRIMMODE", &rb);
}


// Simple command-line UI for the associative fillet functionality. It allows 
// to either create a new associative fillet, or edit an existing one
//
void assocFilletCommandUI()
{
    AcDbEdgeRef selectedEdge[2];
    AcGePoint3d pickPoint[2];

    ErrorStatus err = eOk;
    if ((err = selectEdge(L"\nSelect first entity to fillet or an associative fillet arc: ", 
                          selectedEdge[0], pickPoint[0])) != eOk)
        return;

    AcDbObjectId filletActionId;

    double   defaultRadius = 0.0;
    AcString defaultRadiusExpression;
    bool     defaultTrimInputEdge[2] = { true, true, };
    AcString defaultTrimInputEdgeExpression[2];

    if (AssocFilletActionBody::isFilletArc(selectedEdge[0].entity().topId(), filletActionId))
    {
        //////////////////////////////////////////////////////////////////////
        // An associative fillet arc has been selected, edit the existing 
        // associative fillet action
        //////////////////////////////////////////////////////////////////////

        AcDbObjectPointer<AssocFilletActionBody> pFilletActionBody(AcDbAssocAction::actionBody(filletActionId), kForWrite);
        if (!eOkVerify(pFilletActionBody.openStatus()))
            return;

        defaultRadius = pFilletActionBody->getRadius(defaultRadiusExpression);
        defaultTrimInputEdge[0] = pFilletActionBody->isTrimInputEdge(0, defaultTrimInputEdgeExpression[0]); 
        defaultTrimInputEdge[1] = pFilletActionBody->isTrimInputEdge(1, defaultTrimInputEdgeExpression[1]); 

        printDefaults(defaultRadius, defaultRadiusExpression, defaultTrimInputEdge, defaultTrimInputEdgeExpression);

        double   radius = 0.0;
        AcString radiusExpression;
        if (promptForFilletRadius(defaultRadius, defaultRadiusExpression, radius, radiusExpression) != eOk)
            return;

        bool     trimInputEdge[2];
        AcString trimInputEdgeExpression[2];
        for (int i = 0; i < 2; i++)
        {
            if (promptForTrimInputEdge(i, defaultTrimInputEdge[i], defaultTrimInputEdgeExpression[i], 
                                       trimInputEdge[i], trimInputEdgeExpression[i]) != eOk)
                return;
        }

        // Update the associative fillet action
        //
        pFilletActionBody->setRadius(radius, radiusExpression);
        pFilletActionBody->setTrimInputEdge(0, trimInputEdge[0], trimInputEdgeExpression[0]);
        pFilletActionBody->setTrimInputEdge(1, trimInputEdge[1], trimInputEdgeExpression[1]);
    }
    else 
    {
        //////////////////////////////////////////////////////////////////////
        // An edge geometry has been selected, create a new associative fillet 
        // action
        //////////////////////////////////////////////////////////////////////

        if ((err = selectEdge(L"\nSelect second entity to fillet: ", selectedEdge[1], pickPoint[1])) != eOk)
            return;

        getVars(defaultRadius, defaultTrimInputEdge[0]);
        defaultTrimInputEdge[1] = defaultTrimInputEdge[0];

        printDefaults(defaultRadius, L"", defaultTrimInputEdge, defaultTrimInputEdgeExpression);

        double   radius = 0.0;
        AcString radiusExpression;
        if (promptForFilletRadius(defaultRadius, L"", radius, radiusExpression) != eOk)
            return;

        bool       trimInputEdge[2];
        AcString   trimInputEdgeExpression[2];
        for (int i = 0; i < 2; i++)
        {
            if (promptForTrimInputEdge(i, defaultTrimInputEdge[i], L"", trimInputEdge[i], trimInputEdgeExpression[i]) != eOk)
                return;
        }

        // Create the action and fillet action body and set it up
        //
        err = AssocFilletActionBody::createAndPostToDatabase(selectedEdge, 
                                                             trimInputEdge, 
                                                             trimInputEdgeExpression,
                                                             pickPoint, 
                                                             radius, 
                                                             radiusExpression, 
                                                             filletActionId);

        if (err != eOk) // Probably a wrong expression provided
        {
            acutPrintf(L"\nThe associative fillet cannot be created.\n"); 
            return;
        }

        // The newly created action will be automatically evaluated at the end
        // of the command.
        //
        // If we want to know whether the evaluation is going to succeed, we can
        // evaluate the network explicitly and check the evaluation status 
        // of the action
        //
        AcDbAssocManager::evaluateTopLevelNetwork(filletActionId.database());

        AcDbObjectPointer<AcDbAssocAction> pFilletAction(filletActionId, kForWrite);
        if (!eOkVerify(pFilletAction.openStatus()))
            return; // The action likely erased because of broken dependencies

        AcDbObjectPointer<AssocFilletActionBody> pFilletActionBody(pFilletAction->actionBody(), kForWrite);
        if (!eOkVerify(pFilletActionBody.openStatus()))
            return; // This should never happen

        // If the newly created associative fillet action hasn't properly evaluated, erase it
        //
        if (pFilletAction->status() != kIsUpToDateAssocStatus)
        {
            acutPrintf(L"\nThe associative fillet cannot be evaluated.\n");
            pFilletActionBody->eraseFilletArcEntity();
            pFilletAction->erase();
            return;
        }

        // We can update AutoCAD sysvars with the current values. It can be done 
        // only after the action has been evaluated, because the fillet radius and 
        // the trim flag may be specified by an expression, and the expressions 
        // need to be evaluated
        //
        setVars(pFilletActionBody->getRadius(), pFilletActionBody->isTrimInputEdge(0));
    }
}
