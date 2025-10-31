//
// (C) Copyright 2005-2007 by Autodesk, Inc. 
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
#include "StdAfx.h"
//
#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <map>
#include "dbidmap.h"
#include "dbxutil.h"
#include "geassign.h"
#include "acgs.h"
#include "gs.h"
#include "AcGsManager.h"
#include "dbxutil.h"
#include "VisualStyleCmd.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

typedef std::map<AcDbDatabase *,VisualStyleCmd> CmdMap;
static CmdMap vstyleCmds;

const AcRxFunctionPtr VisualStyleCmd::kCmdHandlers[kCmdCt] = 
    { setCurrentCmd, 
      deleteCmd, 
      renameCmd, 
      currentInfoCmd, 
      listCmd, 
      createCmd,
      createWithAskCmd,
      };

const ACHAR *VisualStyleCmd::kCmdNames[kCmdCt] = 
    { ACRX_T("VSSETCURRENT"),   // assign existing visual style to current viewport
      ACRX_T("VSDELETE"),       // delete a visual style
      ACRX_T("VSRENAME"),       // rename a visual style
      ACRX_T("VSCURRENTINFO"),  // list visual style properties on current viewport
      ACRX_T("VSLIST"),         // list all visual styles in the visual style dictionary
      ACRX_T("VSTYLE"),         // create a custom entity with current visual style 
      ACRX_T("VSTYLEASK")       // create a custom entity with visual style specified by user
    };      

const ACHAR *VisualStyleCmd::kCmdPrompts[kCmdCt] =
    { ACRX_T("\nEnter name of visual style to set for the current viewport (or * for none): "),
      ACRX_T("\nEnter name of visual style to delete: "),
      ACRX_T("\nEnter name of visual style to rename: "),
      ACRX_T(" "),              // no prompt for VSCURRENTINFO
      ACRX_T(" "),              // no prompt for VSLIST
      ACRX_T(" "),              // no prompt for VSTYLE
      ACRX_T("\nEnter name of visual style to apply to custom entity: ")
    };

// Unload database
void VisualStyleCmd::unload(void)
{
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds.erase(pDb);
}

// Set the visual style for the current viewport
void VisualStyleCmd::setCurrentCmd(void)    
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kSetCurrent);    
}

// Display the info for the visual style assigned to the current viewport
void VisualStyleCmd::currentInfoCmd(void)   
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kCurrentInfo);   
}

// Delete a visual style or all visual styles
void VisualStyleCmd::deleteCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kDelete); 
}

// Rename a visual style or all visual styles
void VisualStyleCmd::renameCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kRename); 
}

// List a visual style or all visual styles
void VisualStyleCmd::listCmd(void)   
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kList);   
}

// Create a custom entity with current visual style 
void VisualStyleCmd::createCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kCreate);
}

// Create a custom entity with visual style specified by user
void VisualStyleCmd::createWithAskCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    vstyleCmds[pDb].invokeCmd(kCreateWithAsk);
}

VisualStyleCmd::VisualStyleCmd()
    : mCurrVisualStyleId(AcDbObjectId::kNull)
{
}

// Perform a visual style operation
void VisualStyleCmd::invokeCmd(Action cmd)
{
    // Create the visual style entity
    if (cmd == kCreate) {
        addVisualStyleEntity();
        return;
    }

    // List all visual styles
    if (cmd == kList) {
        listAllVisualStyles();
        return;
    }

    // Display info for the current viewport's visual style
    if (cmd == kCurrentInfo) {
        displayViewportVStyleInfo();
        return;
    }

    // Or, perform a visual style operation
    const ACHAR *prompt = kCmdPrompts[cmd];
    ACHAR result[133] = ACRX_T("");
    int resultCode;
    bool bResultOk = true;

    do {
        bResultOk = true;
        resultCode = acedGetString(true, prompt, result);
        switch (resultCode) {
        case RTERROR:
            break;
        case RTCAN:
            break;
        default:
        case RTNORM:
            bResultOk = visualStyleCmd(cmd, result);
            break;
        }
    } while (!bResultOk);
}

// Create a custom entity with entity and subentity visual styles assigned to it
void VisualStyleCmd::addVisualStyleEntity(AcDbObjectId visualStyleObjId)
{
    AcGePoint3d cen;
    struct resbuf rbFrom, rbTo;

    // Use the current visual style if no visual style id is supplied.
    if (visualStyleObjId.isNull())
        visualStyleObjId = getCurrentVisualStyle();

    acedGetPoint(NULL, ACRX_T("\nCenter point: "), asDblArray( cen ));
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0;   // to WCS
    acedTrans(asDblArray( cen ), &rbFrom, &rbTo, Adesk::kFalse, asDblArray( cen ));

    // Start up the jig creating the custom entity with the supplied visual style
    VisualStyleJig jig(cen, visualStyleObjId);
    jig.start();
}

// List all visual style names, in both render and database
void VisualStyleCmd::listAllVisualStyles(void)
{
    acutPrintf(ACRX_T("\n"));
    acutPrintf(ACRX_T("--------------BEGIN VISUAL STYLE LIST---------------\n"));
    
    int index;
    AcArray<const TCHAR *> visualStyleList;
    if (acdbHostApplicationServices()->workingDatabase()
            ->getVisualStyleList(visualStyleList) == Acad::eOk) {
        for (index = 0; index < visualStyleList.length(); index++)
            acutPrintf(ACRX_T("%s\n"), visualStyleList[index]);
    }
    
    acutPrintf(ACRX_T("--------------END VISUAL STYLE LIST-----------------\n"));
    acutPrintf(ACRX_T("\n"));
}

void VisualStyleCmd::displayViewportVStyleInfo()
{
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    AcDbObjectId visualStyleId = acdbGetViewportVisualStyle();

    if (!visualStyleId.isNull()) 
    {
        AcDbVisualStyle * pVisualStyle = NULL;
        if (acdbOpenObject(pVisualStyle, visualStyleId, AcDb::kForRead) == Acad::eOk)
        {                
            AcGiFaceStyle faceStyle(pVisualStyle->faceStyle());
            AcGiEdgeStyle edgeStyle(pVisualStyle->edgeStyle());


            // Name
			AcDbDictionary *pVisualStyleDict;
			Acad::ErrorStatus dbStatus;

			if (pDb->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead) == Acad::eOk)
			{
				// Get the visual style
				TCHAR * name = NULL;
				dbStatus = pVisualStyleDict->nameAt(visualStyleId, name);
			
				acutPrintf(ACRX_T(/*MSG0*/"Visual Style:\n"));
				acutPrintf(ACRX_T(/*MSG0*/"     Name:               %s\n"), name);
				pVisualStyleDict->close();
			}

            // Lighting model
            acutPrintf(ACRX_T(/*MSG0*/"     Lighting Model:     "));
            switch (faceStyle.lightingModel())
            {
            case AcGiFaceStyle::kInvisible:    // faces not drawn, no lighting
                acutPrintf(ACRX_T(/*MSG0*/"Invisible - No Faces\n"));
                break;
            case AcGiFaceStyle::kConstant:     // faces drawn, constant color
                acutPrintf(ACRX_T(/*MSG0*/"Constant\n"));
                break;
            case AcGiFaceStyle::kPhong:        // faces drawn, normal shading
                acutPrintf(ACRX_T(/*MSG0*/"Phong\n"));
                break;
            case AcGiFaceStyle::kGooch:        // faces drawn, gooch shading
                acutPrintf(ACRX_T(/*MSG0*/"Gooch\n"));
                break;
            }

            // Lighting quality
            acutPrintf(ACRX_T(/*MSG0*/"     Lighting Quality:   "));
            switch (faceStyle.lightingQuality())
            {
            case AcGiFaceStyle::kNoLighting:
                acutPrintf(ACRX_T(/*MSG0*/"No lighting\n"));
                break;
            case AcGiFaceStyle::kPerFaceLighting:
                acutPrintf(ACRX_T(/*MSG0*/"Per-face lighting\n"));
                break;
            case AcGiFaceStyle::kPerVertexLighting:
                acutPrintf(ACRX_T(/*MSG0*/"Per-vertex lighting\n"));
                break;
            }        

            // Face color mode
            unsigned long colorMode = faceStyle.faceColorMode();
            acutPrintf(ACRX_T(/*MSG0*/"     Face Color Mode:    "));
            if (colorMode == AcGiFaceStyle::kNoColorMode)
                acutPrintf(ACRX_T(/*MSG0*/"None "));
            else {
                if (colorMode & AcGiFaceStyle::kObjectColor)
                    acutPrintf(ACRX_T(/*MSG0*/"Object "));
                if (colorMode & AcGiFaceStyle::kBackgroundColor)
                    acutPrintf(ACRX_T(/*MSG0*/"Background "));
                if (colorMode & AcGiFaceStyle::kMono)
                    acutPrintf(ACRX_T(/*MSG0*/"Mono "));
                if (colorMode & AcGiFaceStyle::kTint)
                    acutPrintf(ACRX_T(/*MSG0*/"Tint "));
                if (colorMode & AcGiFaceStyle::kDesaturate)
                    acutPrintf(ACRX_T(/*MSG0*/"Desaturate "));
            }
            acutPrintf(ACRX_T(/*MSG0*/"\n"));

            // Edge model
            acutPrintf(ACRX_T(/*MSG0*/"     Edge Model:         "));
            switch (edgeStyle.edgeModel())
            {
            case AcGiEdgeStyle::kNoEdges:
                acutPrintf(ACRX_T(/*MSG0*/"No edges\n"));
                break;
            case AcGiEdgeStyle::kIsolines:
                acutPrintf(ACRX_T(/*MSG0*/"Isolines\n"));
                break;
            case AcGiEdgeStyle::kFacetEdges:
                acutPrintf(ACRX_T(/*MSG0*/"Facet edges\n"));
                break;
            }  

            acutPrintf(ACRX_T(/*MSG0*/"     Intersection Edges: %s\n"), 
                (edgeStyle.edgeStyles() & AcGiEdgeStyle::kIntersection) ? ACRX_T(/*MSG0*/"True") : ACRX_T(/*MSG0*/"False"));
            acutPrintf(ACRX_T(/*MSG0*/"     Silhouette Color:   %u %u %u\n"),
                                            edgeStyle.silhouetteColor().red(),
                                            edgeStyle.silhouetteColor().green(),
                                            edgeStyle.silhouetteColor().blue());  
            acutPrintf(ACRX_T(/*MSG0*/"     Silhouette Width:   %d\n"), edgeStyle.silhouetteWidth());
            acutPrintf(ACRX_T(/*MSG0*/"     Edge Color:         %u %u %u\n"),
                                            edgeStyle.edgeColor().red(),
                                            edgeStyle.edgeColor().green(),
                                            edgeStyle.edgeColor().blue());  
            acutPrintf(ACRX_T(/*MSG0*/"     Edge Width:         %d\n"), edgeStyle.edgeWidth());

            pVisualStyle->close(); 
        }
    }
    else {
        // Otherwise, a visual style is not assigned to the current viewport.
        acutPrintf(ACRX_T("A visual style is not assigned to the current viewport.\n"));
    }
}

// Perform an operation on a single visual style
bool VisualStyleCmd::visualStyleCmd(Action cmd, ACHAR *visualStyleName)
{
    bool bVisualStyleExists = true;
    AcDbObjectId visualStyleId = AcDbObjectId::kNull;

    // Execute the command
    switch (cmd) {
    case kSetCurrent:
        if ((_tcscmp((const TCHAR*)(visualStyleName), (const TCHAR*)(ACRX_T("*"))) == 0) ||
            (bVisualStyleExists = visualStyleExists(visualStyleName, &visualStyleId)))
            setVisualStyleCurrent(visualStyleName, visualStyleId);
        break;
    case kDelete:
        if (bVisualStyleExists = visualStyleExists(visualStyleName))
            deleteVisualStyle(visualStyleName);
        break;
    case kRename:
        if (bVisualStyleExists = visualStyleExists(visualStyleName))
            renameVisualStyle(visualStyleName);
        break;
    case kCreateWithAsk:
        if (bVisualStyleExists = visualStyleExists(visualStyleName, &visualStyleId))
            addVisualStyleEntity(visualStyleId);
        break;
    }

    if (!bVisualStyleExists)
        acutPrintf(ACRX_T("Error: Visual style '%s' does not exist.\n"), visualStyleName);

    return bVisualStyleExists;
}

// Set the current viewport's visual style to the specified visual style
void VisualStyleCmd::setVisualStyleCurrent(ACHAR *name, AcDbObjectId visualStyleId)
{
    if (_tcscmp((const TCHAR*)(name), (const TCHAR*)(ACRX_T("*"))) == 0)
    {
        // Set the visual style id to null so that we can clear the visual
        // style in the current viewport
        visualStyleId = AcDbObjectId::kNull;
    }
    else if (visualStyleId.isNull())
    {
        // Open the visual style dictionary for reading
        AcDbDictionary *pVisualStyleDict;
        Acad::ErrorStatus dbStatus;
        AcDbVisualStyle *pVisualStyleObj;

        if (acdbHostApplicationServices()->workingDatabase()
            ->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead) == Acad::eOk)
        {
            // Get the visual style
            dbStatus = pVisualStyleDict->getAt(name,
                (AcDbObject *&)pVisualStyleObj, AcDb::kForWrite);

            assert (dbStatus == Acad::eOk);

            if (dbStatus == Acad::eOk) {
                // Get the visual style's object ID
                visualStyleId = pVisualStyleObj->objectId();
                pVisualStyleObj->close();
            }

            pVisualStyleDict->close();
        }
    }

    Acad::ErrorStatus es = acdbSetViewportVisualStyle(visualStyleId);
    ASSERT (es == Acad::eOk);
    displayViewportVStyleInfo();
}

// Create a visual style of the given name and it to the visual style dictionary
void VisualStyleCmd::addVisualStyle(ACHAR *name)
{
    // Open the visual style dictionary for writing
    AcDbDictionary *pVisualStyleDict;
    Acad::ErrorStatus dbStatus;

    if (acdbHostApplicationServices()->workingDatabase()
            ->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForWrite) == Acad::eOk)
    {
        // Create and initialize the visual style
        AcDbVisualStyle *pVisualStyleObj = new AcDbVisualStyle();

        // Visual Style type
        pVisualStyleObj->setType(AcGiVisualStyle::kCustom);

        // Face style
        AcGiFaceStyle faceStyle = pVisualStyleObj->faceStyle();
        faceStyle.setLightingModel(AcGiFaceStyle::kPhong); // or kGooch, etc...
        faceStyle.setLightingQuality(AcGiFaceStyle::kPerVertexLighting);
        AcCmColor custColor;
        custColor.setColorIndex(5);
        faceStyle.setMonoColor(custColor, true);
        pVisualStyleObj->setFaceStyle(faceStyle);

        // Edge style
        AcGiEdgeStyle edgeStyle = pVisualStyleObj->edgeStyle();
        edgeStyle.setEdgeModel(AcGiEdgeStyle::kFacetEdges); // or whatever...
        edgeStyle.setEdgeColor(custColor, true);
        pVisualStyleObj->setEdgeStyle(edgeStyle);

        // Add visual style to dictionary
        dbStatus = pVisualStyleDict->setAt(name, pVisualStyleObj, mCurrVisualStyleId);
        assert (dbStatus == Acad::eOk);

        // Close the visual style and dictionary
        pVisualStyleObj->close();
        pVisualStyleDict->close();
    }
}

// Delete the visual style of the given name by removing it from the dictionary
void VisualStyleCmd::deleteVisualStyle(ACHAR *name)
{
    // Open the visual style dictionary for reading
    AcDbDictionary *pVisualStyleDict;
    Acad::ErrorStatus dbStatus = Acad::eOk;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead) == Acad::eOk)
    {
        // Erase the visual style, this deletes it from the dictionary
        AcDbVisualStyle *pVisualStyleObj;
        dbStatus = pVisualStyleDict->getAt(name, 
                                       (AcDbObject *&)pVisualStyleObj, 
                                       AcDb::kForWrite);
        pVisualStyleDict->close();
        assert(dbStatus == Acad::eOk);
        
        // Attempt to erase
        CString szMessage;
        CString szFormat;
        szFormat = ACRX_T(/*MSG0*/"The visual style \"%s\"");

        if (dbStatus == Acad::eOk)  {
            dbStatus = pVisualStyleObj->erase();
            if (Acad::eOk != dbStatus)  {
                if (Acad::eVSIsInUse == dbStatus) {
                    szFormat += ACRX_T(/*MSG0*/" is in use and cannot be deleted.");
                    szMessage.Format(szFormat, name);
                    acutPrintf(szMessage);
                }   else if (Acad::eVSIsAcadDefault == dbStatus)    {
                    szFormat += ACRX_T(/*MSG0*/" is a default visual style and cannot be deleted.");
                    szMessage.Format(szFormat, name);
                    acutPrintf(szMessage);            
                }   else    {
                    szFormat += ACRX_T(/*MSG0*/" cannot be deleted due to an unknown error: %d.");
                    szMessage.Format(szFormat, name, dbStatus);
                    acutPrintf(szMessage);
                }
            }
        }
        pVisualStyleObj->close();
    }
}

// Rename the visual style of the given name by getting it from the dictionary
void VisualStyleCmd::renameVisualStyle(ACHAR *name)
{
    const ACHAR *prompt = ACRX_T("\nEnter new visual style name: ");
    ACHAR newName[133] = ACRX_T("");
    int resultCode;
    bool bResultOk = true;

    resultCode = acedGetString(true, prompt, newName);

    if (resultCode != RTNORM || !(*newName))
        return;

    // Open the visual style dictionary for reading
    AcDbDictionary *pVisualStyleDict;
    Acad::ErrorStatus dbStatus;
    AcDbVisualStyle *pVisualStyleObj;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForWrite) == Acad::eOk)
    {
        // Get the visual style
        dbStatus = pVisualStyleDict->getAt(name,
            (AcDbObject *&)pVisualStyleObj, AcDb::kForWrite);

        assert (dbStatus == Acad::eOk);

        if (dbStatus == Acad::eOk) {
            // Rename the visual style object
            pVisualStyleObj->close();

            // Rename the dictionary entry
            pVisualStyleDict->setName(name, newName);
        }

        pVisualStyleDict->close();
    }
}

// Return the current visual style; a new one will be created if none exists
AcDbObjectId VisualStyleCmd::getCurrentVisualStyle(void)
{
    Acad::ErrorStatus status;

    // Get or create the visual style named "JITTEREDGOOCH" if no current
    // visual style is available
    if (mCurrVisualStyleId == AcDbObjectId::kNull) 
    {
        // Open the visual style dictionary for reading
        AcDbDictionary *pVisualStyleDict;
        status = acdbHostApplicationServices()->workingDatabase()->
                     getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead);
        if (status == Acad::eOk)
        {
            // Check that the JITTEREDGOOCH visual style exists in the dictionary
            AcDbObjectId visualStyleId;
            if (pVisualStyleDict->getAt(ACRX_T("JITTEREDGOOCH"), visualStyleId) == Acad::eOk)
                mCurrVisualStyleId = visualStyleId;
            pVisualStyleDict->close();
        }

        // If it wasn't found, add the JITTEREDGOOCH visual style
        if (mCurrVisualStyleId == AcDbObjectId::kNull)
            addVisualStyle(ACRX_T("JITTEREDGOOCH"));
    }
    
    else {
        AcDbVisualStyle *pVisualStyleObj = NULL;
        status = acdbOpenObject(pVisualStyleObj, mCurrVisualStyleId, AcDb::kForRead);
        if (status == Acad::eOk)
            pVisualStyleObj->close();
        else {
            // If it wasn't openable (for example, it was erased), 
            // then add the JITTEREDGOOCH visual style
            addVisualStyle(ACRX_T("JITTEREDGOOCH"));
        }
    }

    return mCurrVisualStyleId;
}

// Return true if visual style exists in dictionary, otherwise 
// print error message and return false
bool VisualStyleCmd::visualStyleExists(ACHAR *name, AcDbObjectId *pVisualStyleId)
{
    bool bExists = false;

    // Open the visual style dictionary for reading
    AcDbDictionary *pVisualStyleDict;
    if (acdbHostApplicationServices()->workingDatabase()
        ->getVisualStyleDictionary(pVisualStyleDict, AcDb::kForRead) == Acad::eOk)
    {
        // Check that the visual style exists in the dictionary
        AcDbObjectId visualStyleId;
        bExists = 
            (pVisualStyleDict->getAt(name, visualStyleId) == Acad::eOk);

        // Return visual style id if storage provided
        if (pVisualStyleId)
            *pVisualStyleId = visualStyleId;

        // Close the dictionary
        pVisualStyleDict->close();
    }

    return bExists;
}
