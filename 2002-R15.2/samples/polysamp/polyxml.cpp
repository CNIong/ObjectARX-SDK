//
// (C) Copyright 2000 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// This file contains the code for interfacing to AutoCAD's XML protocol ext.
//----------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "objbase.h"

#include "rxregsvc.h"
#include "aced.h"
#include "poly.h"
#include "dbapserv.h"
#include "dbXmlProtocol.h"

#include "acdbabb.h"

//----------------------------------------------------------------------------
// XML I/O 
// Define the AcDbXmlPoly class with xmlIn and xmlOut methods via the
// ACDB_DECLARE_XMLOBJECTPROTOCOL macro from dbXmlProtocol.h
ACDB_DECLARE_XMLOBJECTPROTOCOL(AcDbXmlPoly);

// Add this global to keep track of the runtime protocol extension object
AcDbXmlPoly* gpPolyXmlExtension = NULL;

#define MY_SCHEMA "x-schema:http://www.DesignXML.org/schema/AcDbPoly_V_100.xdr"

// Names used in the registry for autoloading support.
#define MY_APPLOC       "Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\PolySamp"
#define MY_APPNAME      "AsdkPolyOBJXML"
#define MY_MODULE_NAME  "asdkPolyXMLObj.dbx"


//----------------------------------------------------------------------------
// XML protocol extension implementation
Acad::ErrorStatus
AcDbXmlPoly::xmlIn(
    AcDbObject* pObj,
    AcDbXmlInFiler* pFiler)
{
    if (pObj == NULL || pFiler == NULL)
        return eInvalidInput;

    AsdkPoly* pPoly = AsdkPoly::cast(pObj);
    if (pPoly == NULL)
        return eInvalidInput;

    AcUtXMLDOMNode* pFirstNode = pFiler->getCurrentNode(); // don't delete
    if (pFirstNode == NULL)
        return eInvalidInput;

    AcUtXMLDOMNode* pCurrent = NULL;
    AcUtXMLDOMNode* pChild = NULL;
    AcUtXMLDOMElement* pElement = NULL;
    AcUtXMLDOMResult hr;
    Acad::ErrorStatus es = eOk;
    AcGePoint2d centerPt;
    AcGePoint3d centerPt3d;
    AcGePoint2d startPt;
    AcGePoint3d startPt3d;
    AcGeVector3d normal;
    AcDbObjectId textStyleId;
    AcUtString name;
    int numSides;
    double elevation = 0;
    AcUtString nodeName = pFiler->getCurrentNodeName();

    try {
        // first child should be asdk:Poly
        hr = pFirstNode->get_firstChild(pCurrent);
        if (hr != S_OK)
            throw eInvalidInput;

        // make it current
        pFiler->setCurrentNode(pCurrent);

        // verify node name is Poly
        nodeName = pFiler->getCurrentNodeName();
        if (nodeName.compare(L"asdk:Poly") != 0)
            throw eInvalidInput;

        // Get the numSides and name atributes
        pElement = new AcUtXMLDOMElement(pCurrent);
        if (pElement == NULL)
            throw eOutOfMemory;

        es = pFiler->readAttribute(pElement, L"numSides", numSides);
        if (es != eOk)
            throw es;

        es = pFiler->readAttribute(pElement, L"name", name);
        if (es != eOk)
            throw es;

        // Get the first child element of the asdk:Poly
        hr = pCurrent->get_firstChild(pChild);
        if (hr != S_OK)
            throw eInvalidInput;

        // Make it current
        pFiler->setCurrentNode(pChild);
        delete pCurrent;
        pCurrent = pChild;
        pChild = NULL;
        nodeName = pFiler->getCurrentNodeName();

        // This first child node might be an optional acdb:Entity
        if (nodeName.compare(AcUtString(L"acdb:Entity")) == 0)
        {
            // Read the acdb:Entity node
            es = superXmlIn(pObj, pFiler);
            if (es != eOk)
                throw es;

            hr = pCurrent->get_nextSibling(pChild);
            if (hr != S_OK)
                throw eInvalidInput;

            pFiler->setCurrentNode(pChild);
            delete pCurrent;
            pCurrent = pChild;
            pChild = NULL;
        }

        // Expect the current node to be a dxml:CenterPoint.
        es = pFiler->readPoint(L"dxml:CenterPoint", centerPt3d);
        if (es != eOk)
            throw es;

        // Get the next sibiling to the circle - expect StartPoint.
        hr = pCurrent->get_nextSibling(pChild);
        if (hr != S_OK)
            throw eInvalidInput;

        pFiler->setCurrentNode(pChild);
        delete pCurrent;
        pCurrent = pChild;
        pChild = NULL;

        es = pFiler->readPoint(L"dxml:StartPoint", startPt3d);
        if (es != eOk)
            throw es;

        // Get the next sibiling to the circle - expect NormalVector.
        hr = pCurrent->get_nextSibling(pChild);
        if (hr != S_OK)
            throw eInvalidInput;

        pFiler->setCurrentNode(pChild);
        delete pCurrent;
        pCurrent = pChild;
        pChild = NULL;

        es = pFiler->readNormalVector(normal);
        if (es != eOk)
            throw es;

        // Get the next sibiling to the circle - expect TextStyleTableRecordId.
        hr = pCurrent->get_nextSibling(pChild);
        if (hr != S_OK)
            throw eInvalidInput;

        pFiler->setCurrentNode(pChild);
        delete pCurrent;
        pCurrent = pChild;
        pChild = NULL;

        es = pFiler->readObjectId(L"acdb:TextStyleTableRecordId", textStyleId);
        if (es != eOk)
            throw es;

        es = pPoly->setTextStyle(textStyleId);
        if (es != eOk)
            throw es;

        // Convert the center point from WCS to ECS
        acdbWcs2Ecs(asDblArray(centerPt3d), asDblArray(centerPt3d),
            asDblArray(normal), true);

        centerPt.x = centerPt3d.x;
        centerPt.y = centerPt3d.y;
        elevation = centerPt3d.z;

        // Convert the start point from WCS to ECS
        acdbWcs2Ecs(asDblArray(startPt3d), asDblArray(startPt3d),
            asDblArray(normal), true);

        startPt.x = startPt3d.x;
        startPt.y = startPt3d.y;

        es = pPoly->set(centerPt, startPt, numSides, normal, name, elevation);
        if (es != eOk)
            throw es;
    }

    catch (Acad::ErrorStatus thrownEs) {
        es = thrownEs;
    }

    // restore first node
    pFiler->setCurrentNode(pFirstNode);

    if (pElement)
        delete pElement;
    if (pCurrent && pCurrent != pFiler->getCurrentNode())
        delete pCurrent;
    if (pChild)
        delete pChild;

    return es;
}


Acad::ErrorStatus
AcDbXmlPoly::xmlOut(
    AcDbObject* pObj,
    AcDbXmlOutFiler* pFiler)
{
    Acad::ErrorStatus es = eOk;

    AsdkPoly* pPoly = AsdkPoly::cast(pObj);
    if (!pPoly)
        return eInvalidInput;

    AcUtXMLDOMNode* pNode = NULL;
    AcUtXMLDOMElement* pElement = NULL;
    AcUtXMLDOMAttribute* pAttribute = NULL;

    try {
        es = pFiler->pushNode(L"asdk:Poly", MY_SCHEMA, pNode);
        if (es != eOk)
            throw es;

        pElement = new AcUtXMLDOMElement(pNode);
        if (pElement == NULL)
            throw eOutOfMemory;

        es = superXmlOut(pObj, pFiler);
        if (es != eOk)
            throw es;

        es = pFiler->appendAttribute(pPoly->numSides(), L"numSides", 
            pElement);
        if (es != eOk)
            throw es;

        AcUtString name=pPoly->name();
        es = pFiler->appendAttribute(name, L"name", pElement);
        if (es != eOk)
            throw es;

        AcGePoint2d pt2d = pPoly->center();
        AcGePoint3d centerPt(pt2d.x, pt2d.y, pPoly->elevation());

        // Convert the point from ECS to WCS
        acdbEcs2Wcs(asDblArray(centerPt), asDblArray(centerPt),
            asDblArray(pPoly->normal()), true);

        es = pFiler->writePoint(L"dxml:CenterPoint", centerPt);
        if (es != eOk)
            throw es;

        pt2d = pPoly->startPoint();
        AcGePoint3d startPt(pt2d.x, pt2d.y, pPoly->elevation());
        // Convert the point from ECS to WCS
        acdbEcs2Wcs(asDblArray(startPt), asDblArray(startPt),
            asDblArray(pPoly->normal()), true);

        es = pFiler->writePoint(L"dxml:StartPoint", startPt);
        if (es != eOk)
            throw es;

        es = pFiler->writeNormalVector(pPoly->normal());
        if (es != eOk)
            throw es;

        es = pFiler->writeHardPointerId(L"acdb:TextStyleTableRecordId", 
            pPoly->styleId());
        if (es != eOk)
            throw es;

        es = pFiler->popNode();
        if (es != eOk)
            throw es;
    }

    catch (Acad::ErrorStatus thrownEs) {
        es = thrownEs;
    }

    if (pAttribute)
        delete pAttribute;
    if (pElement)
        delete pElement;
    if (pNode && pNode != pFiler->getCurrentNode())
        delete pNode;

    return es;
}

void
updateRegistry()
{
    // Represents your company's Registry location
    const char pAppInfoLoc[] = MY_APPLOC;

    // The final argument of Adesk::kTrue means that this app will be
    // registered under the Autodesk/ObjectDBX area of the registry
    // All ObjectDBX apps can search for it there, in addition to AutoCAD
    //
    acrxRegisterApp((AcadApp::LoadReasons)(AcadApp::kOnProxyDetection), 
        MY_APPNAME, pAppInfoLoc  , 2, Adesk::kTrue);

    // Now to write out the application specific information
    //
    // We will install our "application specific" data in:
    // Software\Autodesk\ObjectARX\3.0\SampleApps\Polysamp

    HKEY rkey;
    DWORD result;
    LONG status = RegCreateKeyEx(HKEY_LOCAL_MACHINE, pAppInfoLoc, 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rkey, &result);
    if (status != ERROR_SUCCESS)
        return;

    HKEY prodKey;
    status = RegCreateKeyEx(rkey, MY_APPNAME, 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &prodKey, &result);
    RegCloseKey(rkey);
    if (status != ERROR_SUCCESS)
        return;

    HKEY loaderKey;
    status = RegCreateKeyEx(prodKey, "Loader", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &loaderKey, &result);
    
    if (status == ERROR_SUCCESS) {
        HMODULE modHandle = GetModuleHandle(MY_MODULE_NAME);
        if (modHandle) {
            // long filenames have a max length of 255.  total directory path
            // length is also 255 or less,  so a buffer of 512 bytes should be
            // fine.
            //
            char modulePath[512];
            DWORD pathLength = GetModuleFileName(modHandle, modulePath, 512);
            if (pathLength)
                RegSetValueEx(loaderKey, "MODULE", 0, REG_SZ,
                    (const unsigned char*)modulePath, pathLength + 1);
        }
        RegCloseKey(loaderKey);
    }

    HKEY nameKey;
    status = RegCreateKeyEx(prodKey, "Name", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &nameKey, &result);
    RegCloseKey(prodKey);
    if (status != ERROR_SUCCESS)
        return;

    RegSetValueEx(nameKey, MY_APPNAME, 0, REG_SZ,
        (const unsigned char*)MY_APPNAME, 12);
    RegCloseKey(nameKey);
}

extern "C" 
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch(msg) {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(pkt);        // Try to allow unloading
        acrxRegisterAppMDIAware(pkt);

        if (acrxServiceIsRegistered("AsdkPoly") 
            && AsdkPoly::desc() != NULL
            && AcDbXmlObjectProtocol::desc() != NULL) {
            // add XML I/O protocol extension to AsdkPoly
            //
            gpPolyXmlExtension = new AcDbXmlPoly(AsdkPoly::desc());
            AsdkPoly::desc()->addX(AcDbXmlObjectProtocol::desc(), gpPolyXmlExtension);

            acrxBuildClassHierarchy();
            updateRegistry();
        }
        break;

    case AcRx::kUnloadAppMsg:
        if (acrxServiceIsRegistered("AsdkPoly") 
            && AsdkPoly::desc() != NULL
            && AcDbXmlObjectProtocol::desc() != NULL) {
            AsdkPoly::desc()->delX(AcDbXmlObjectProtocol::desc());
        }
        if (gpPolyXmlExtension)
            delete gpPolyXmlExtension;
        break;
    }
    return AcRx::kRetOK;
}
