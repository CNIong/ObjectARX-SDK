//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <map>
#include "dbidmap.h"
#include "geassign.h"
#include "acgs.h"
#include "gs.h"
#include "AcGsManager.h"
#include "MaterialCmd.h"



const TCHAR *kImageFile = _T("3d.tga"); // found in the AutoCAD Textures directory

typedef std::map<AcDbDatabase *,MaterialCmd> CmdMap;
static CmdMap matCmds;

const AcRxFunctionPtr MaterialCmd::kCmdHandlers[kCmdCt] = 
    { listCmd, addCmd, addTexturedCmd, deleteCmd, modifyCmd, replaceCmd, createCmd };
const TCHAR *MaterialCmd::kCmdNames[kCmdCt] = 
    { _T("MATLIST"), _T("MATADD"), _T("TEXMATADD"), _T("MATDELETE"), _T("MATMODIFY"), _T("MATREPLACE"), _T("MATCREATE") };
const TCHAR *MaterialCmd::kCmdPrompts[kMatCmdCt] =
{ _T("\nEnter name of material to list, or <enter> to list all materials: "),
_T("\nEnter name of material to add: "),
_T("\nEnter name of textured material to add: "),
_T("\nEnter name of material to delete, or <enter> to delete all materials: "),
_T("\nEnter name of material to modify, or <enter> to modify all materials: "),
_T("\nEnter name of material to replace (wblock copy), or <enter> to replace all materials: "),
    };
const TSTDSTRING MaterialCmd::kDbGlobalName = _T("_GLOBAL_");
const TSTDSTRING MaterialCmd::kRendGlobalName = _T("*GLOBAL*");

// Unload database
void MaterialCmd::unload(void)
{
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds.erase(pDb);
}

// List a material or all materials
void MaterialCmd::listCmd(void)   
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kList);   
}

// Add a material
void MaterialCmd::addCmd(void)    
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAdd);    
}

// Add a material
void MaterialCmd::addTexturedCmd(void)    
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddTextured);    
}

// Delete a material or all materials
void MaterialCmd::deleteCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kDelete); 
}

// Modify a material or all materials
void MaterialCmd::modifyCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kModify); 
}

// Replace a material or all materials
void MaterialCmd::replaceCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kReplace); 
}

// Create a custom entity with subentity material assignment
void MaterialCmd::createCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kCreate);
}

MaterialCmd::MaterialCmd()
    : mCurrMaterialId(AcDbObjectId::kNull)
{
}

// Perform a material operation
void MaterialCmd::invokeCmd(Action cmd)
{
    // Create the material entity
    if (cmd == kCreate) {
        addMaterialEntity();
        return;
    }

    // Or, perform a material operation
    const TCHAR *prompt = kCmdPrompts[cmd];
    TCHAR result[133] = _T("");
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
            if (*result)
                bResultOk = singleMaterialCmd(cmd, result);
            else
                allMaterialsCmd(cmd);
            break;
        }
    } while (!bResultOk);
}

// Create a custom entity with subentity materials assigned to it
void MaterialCmd::addMaterialEntity(void)
{
    AcGePoint3d cen;
    struct resbuf rbFrom, rbTo;

    AcDbObjectId materialObjId = getCurrentMaterial();

    acedGetPoint(NULL, _T("\nCenter point: "), asDblArray( cen ));
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0;   // to WCS
    acedTrans(asDblArray( cen ), &rbFrom, &rbTo, Adesk::kFalse, asDblArray( cen ));

    MaterialJig jig(cen, materialObjId);
    jig.start();
}

// Perform an operation on all materials
void MaterialCmd::allMaterialsCmd(Action cmd)
{
    switch (cmd) {
    case kList:
        listAllMaterials();
        break;
    case kAdd:
    case kAddTextured:
        // no add all materials command 
        break;
    case kDelete:
        deleteAllMaterials();
        break;
    case kModify:
        modifyAllMaterials();
        break;
    case kReplace:
        replaceAllMaterials();
        break;
    }
}

// Perform an operation on a single material
bool MaterialCmd::singleMaterialCmd(Action cmd, TCHAR *materialName)
{
    bool bMaterialExists = true;

    TSTDSTRING name(materialName);

    // Execute the command
    switch (cmd) {
    case kList:
        if (bMaterialExists = materialExists(name))
            listMaterial(name);
        break;
    case kAdd:
        addMaterial(name);
        break;
    case kAddTextured:
        addMaterial(name, true);
        break;
    case kDelete:
        if (bMaterialExists = materialExists(name))
            deleteMaterial(name);
        break;
    case kModify:
        if (bMaterialExists = materialExists(name))
            modifyMaterial(name);
        break;
    case kReplace:
        if (bMaterialExists = materialExists(name))
            replaceMaterial(name);
        break;
    }

    if (!bMaterialExists)
        acutPrintf(_T("Error: Material '%s' does not exist.\n"), name.c_str());

    return bMaterialExists;
}

// List all material names, in both render and database
void MaterialCmd::listAllMaterials(void)
{
    StringSet dbNames; 
    getDatabaseMaterialNames(dbNames);

    StringSet::const_iterator dbMat;

    acutPrintf(_T("\n"));
    acutPrintf(_T("--------------BEGIN MATERIAL LIST---------------\n"));
    acutPrintf(_T("    Database (%3d)\n"), 
               dbNames.size());
    acutPrintf(_T("--------------------        --------------------\n"));

    for (dbMat = dbNames.begin();dbMat != dbNames.end();) 
    {
        if (dbMat != dbNames.end()) {
            acutPrintf(_T("%20s\n"), (*dbMat).c_str());
            ++dbMat;
        }
        else
            acutPrintf(_T("%20s\n"), _T("****"));
    }
    acutPrintf(_T("--------------END MATERIAL LIST-----------------\n"));
    acutPrintf(_T("\n"));
}

// Delete all materials
void MaterialCmd::deleteAllMaterials(void)
{
    StringSet dbNames; 
    getDatabaseMaterialNames(dbNames);

    AcDbDictionary *pMaterialDict;
    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForWrite) == Acad::eOk)
    {
        // Add all unique database materials to render
        Acad::ErrorStatus dbStatus = Acad::eOk;
        StringSet::const_iterator mat;
        for (mat = dbNames.begin(); 
             mat != dbNames.end(); 
             ++mat) 
        {
            if (*mat != kDbGlobalName)
                dbStatus = pMaterialDict->remove((*mat).c_str());
            assert(dbStatus == Acad::eOk);
        }

        pMaterialDict->close();
    }
}

// Modify all materials
void MaterialCmd::modifyAllMaterials(void)
{
    StringSet dbNames; 
    getDatabaseMaterialNames(dbNames);

    AcDbDictionary *pMaterialDict;
    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        StringSet::const_iterator mat;
        const TCHAR *matName;

        // Add all unique database materials to render
        AcDbMaterial *pMaterialObj;
        Acad::ErrorStatus dbStatus;

        for (mat = dbNames.begin(); 
             mat != dbNames.end(); 
             ++mat) 
        {
            if ((*mat) != kDbGlobalName)
            {
                matName = (*mat).c_str();
                dbStatus = pMaterialDict->getAt(matName, 
                    (AcDbObject *&)pMaterialObj, AcDb::kForWrite);
                assert (dbStatus == Acad::eOk);
                if (dbStatus == Acad::eOk) {
                    AcGiMaterialColor color;
                    AcGiMaterialMap map;
                    color.setMethod(AcGiMaterialColor::kOverride);
                    color.setColor(getModifyColor());
                    pMaterialObj->setDiffuse(color,  AcGiMaterialMap::kNull);
                    pMaterialObj->close();
                }
            }
        }

        pMaterialDict->close();
    }
}

// List a material's properties
void MaterialCmd::listMaterial(TSTDSTRING &name)
{
    // Open the material dictionary for reading
    AcDbDictionary *pMaterialDict;
    Acad::ErrorStatus dbStatus;
    AcDbMaterial *pMaterialObj;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        // Get the material
        dbStatus = pMaterialDict->getAt(name.c_str(),
            (AcDbObject *&)pMaterialObj, AcDb::kForRead);
        assert (dbStatus == Acad::eOk);

        // Diffuse color
        AcGiMaterialColor color;
        AcGiMaterialMap map;
        pMaterialObj->diffuse(color, map);

        acutPrintf(_T("\n"));
        acutPrintf(_T("--------------LIST MATERIAL---------------\n"));
        acutPrintf(_T("Name: %s\n"), pMaterialObj->name());
        acutPrintf(_T("Diffuse:\n"));
        acutPrintf(_T("    Method: %s\n"), colorMethod(color));
        acutPrintf(_T("    Color:  %s\n"), colorValue(color));
        acutPrintf(_T("    Factor: %f\n"), color.factor());
        acutPrintf(_T("------------------------------------------\n"));
        acutPrintf(_T("\n"));

        // Close the material and dictionary
        pMaterialObj->close();
        pMaterialDict->close();
    }    
}

// Create a material of the given name and it to the material dictionary
void MaterialCmd::addMaterial(TSTDSTRING &name, bool bTextured)
{
    // Open the material dictionary for writing
    AcDbDictionary *pMaterialDict;
    Acad::ErrorStatus dbStatus;

    if (acdbHostApplicationServices()->workingDatabase()
            ->getMaterialDictionary(pMaterialDict, AcDb::kForWrite) == Acad::eOk)
    {
        // Create and initialize the material
        AcDbMaterial *pMaterialObj = new AcDbMaterial();

        // Name
        pMaterialObj->setName(name.c_str());

        // Diffuse color
        AcGiMaterialColor color;
        color.setMethod(AcGiMaterialColor::kOverride);
        color.setFactor(1.0);
        color.setColor(getAddColor());

        // Diffuse texture
        AcGiMaterialMap map;
        if (bTextured)
        {
            map.setSource(AcGiMaterialMap::kFile);
            map.setSourceFileName(kImageFile);
        }
        pMaterialObj->setDiffuse(color, map);

        // Ambient and specular color
        AcGiMaterialColor inheritColor;
        color.setFactor(0.5);
        pMaterialObj->setAmbient(color);
        pMaterialObj->setSpecular(color, AcGiMaterialMap(), 0.5);

        // Add material to dictionary
        dbStatus = pMaterialDict->setAt(name.c_str(), pMaterialObj, mCurrMaterialId);
        assert (dbStatus == Acad::eOk);

        // Close the material and dictionary
        pMaterialObj->close();
        pMaterialDict->close();
    }
}

// Delete the material of the given name by removing it from the dictionary
void MaterialCmd::deleteMaterial(TSTDSTRING &name)
{
    // Do not delete the global material
    if (name == kDbGlobalName)
        return;

    // Open the material dictionary for writing
    AcDbDictionary *pMaterialDict;
    Acad::ErrorStatus dbStatus;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        // Erase the material, this deletes it from the dictionary
        AcDbMaterial *pMaterialObj;
        dbStatus = pMaterialDict->getAt(name.c_str(), 
                                       (AcDbObject *&)pMaterialObj, 
                                       AcDb::kForWrite);
        pMaterialDict->close();

        assert(dbStatus == Acad::eOk);
        pMaterialObj->erase();
        pMaterialObj->close();
    }
}

// Modify the material of the given name by getting it from the dictionary
void MaterialCmd::modifyMaterial(TSTDSTRING &name)
{
    // Open the material dictionary for reading
    AcDbDictionary *pMaterialDict;
    Acad::ErrorStatus dbStatus;
    AcDbMaterial *pMaterialObj;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        // Get the material
        dbStatus = pMaterialDict->getAt(name.c_str(),
            (AcDbObject *&)pMaterialObj, AcDb::kForWrite);

        assert (dbStatus == Acad::eOk);

        // Set the diffuse color 
        if (dbStatus == Acad::eOk) {
            AcGiMaterialColor color;
            color.setMethod(AcGiMaterialColor::kOverride);
            color.setColor(getModifyColor());
            pMaterialObj->setDiffuse(color, AcGiMaterialMap::kNull);
            pMaterialObj->close();
        }

        pMaterialDict->close();
    }
}

void MaterialCmd::replaceMaterialHelper(AcDbDatabase *pSourceDb, AcDbObjectIdArray &sourceDbMaterialIds)
{
    if (!sourceDbMaterialIds.isEmpty())
    {
        // Get the destination database - just pick the first database which is not
        // the source database
        AcDbDatabase *pDestDb = NULL;
        AcApDocument *pDoc, *pDestDoc = NULL;
        AcApDocumentIterator* pDocIter = acDocManager->newAcApDocumentIterator();
        assert(pDocIter);
        for ( ; !pDocIter->done() && !pDestDb; pDocIter->step())
        {
            pDoc = pDocIter->document();
            if (pDoc) 
            {
                AcDbDatabase* pDb = pDoc->database();
                if (pDb && pDb != pSourceDb) 
                {
                    pDestDoc = pDoc;
                    pDestDb = pDb;
                }
            }
        }
        delete pDocIter;

        if (pDestDb) 
        {
            // Get the destination database material dictionary id
            AcDbObjectId destDbMaterialDictId = pDestDb->materialDictionaryId();

            // Lock the destination doc for modification
            if (acDocManager->lockDocument(pDestDoc) == Acad::eOk) 
            {
                // Clone the source database materials into the destination database.
                // Duplicates in the destination are replaced by the source material.
                AcDbIdMapping idMapping;
                Acad::ErrorStatus status = 
                    pSourceDb->wblockCloneObjects(sourceDbMaterialIds, 
                                                  destDbMaterialDictId, 
                                                  idMapping, 
                                                  AcDb::kDrcReplace);
                assert (status == Acad::eOk);

                // Update the display on the destination document here now, otherwise 
                // it won't be updated until the document is activated or a window 
                // repaint event occurs.
                CDocument *pDocument = pDestDoc->cDoc();
                if (pDocument) {
                    POSITION posView = pDocument->GetFirstViewPosition();
                    while (posView != NULL) {
                        CView * pView = pDocument->GetNextView(posView);
                        if (pView) {
                            AcGsManager * pManager = acgsGetGsManager (pView);
                            if (pManager) {
                                AcGsDevice *pDevice = pManager->getGUIDevice();
                                if (pDevice)
                                    pDevice->update();
                            }
                        }
                    }
                }

                // Unlock the doc
                acDocManager->unlockDocument(pDestDoc);
            }
        }
        else
            acutPrintf(_T("\n*** No destination database to clone materials into.  Open another drawing. ***\n"));
    }
    else
        acutPrintf(_T("\n*** No materials to clone.  Create a material. ***\n"));
}

// Replace a material in one drawing with an identically-named material from another drawing.
// For this to work, at least two drawings should be open in AutoCAD, and the two drawings 
// should contain an identically-named material, whose name is passed in here.
void MaterialCmd::replaceMaterial(TSTDSTRING &name)
{
    AcDbObjectId materialId;

    if (materialExists(name, &materialId))
    {
        // Get the material id from the source database (the working database)
        AcDbDatabase* pSourceDb = acdbHostApplicationServices()->workingDatabase();
        AcDbObjectIdArray sourceDbMaterialIds; 
        sourceDbMaterialIds.append(materialId);
        replaceMaterialHelper(pSourceDb, sourceDbMaterialIds);
    }
}

void MaterialCmd::replaceAllMaterials(void)
{
    // Get all the material ids from the source database (the working database)
    AcDbDatabase* pSourceDb = acdbHostApplicationServices()->workingDatabase();
    AcDbObjectIdArray sourceDbMaterialIds; 
    AcDbObjectId materialId;
    AcDbDictionary *pMaterialDict;

    if (pSourceDb->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        AcDbDictionaryIterator *pDictIter = pMaterialDict->newIterator();
        for (; !pDictIter->done(); pDictIter->next()) 
        {
            materialId = pDictIter->objectId();
            if (!materialId.isNull())
                sourceDbMaterialIds.append(materialId);
        }
        delete pDictIter;
        pMaterialDict->close();
    }

    replaceMaterialHelper(pSourceDb, sourceDbMaterialIds);
}

// Return the current material; a new one will be created if none exists
AcDbObjectId MaterialCmd::getCurrentMaterial(void)
{
    Acad::ErrorStatus status;

    // Get or create the material named "DEFAULT" if no current
    // material is available
    if (mCurrMaterialId == AcDbObjectId::kNull) 
    {
        // Open the material dictionary for reading
        AcDbDictionary *pMaterialDict;
        status = acdbHostApplicationServices()->workingDatabase()->
                     getMaterialDictionary(pMaterialDict, AcDb::kForRead);
        if (status == Acad::eOk)
        {
            // Check that the DEFAULT material exists in the dictionary
            AcDbObjectId materialId;
            if (pMaterialDict->getAt(_T("DEFAULT"), materialId) == Acad::eOk)
                mCurrMaterialId = materialId;
            pMaterialDict->close();
        }

        // If it wasn't found, add the DEFAULT material
        if (mCurrMaterialId == AcDbObjectId::kNull)
            addMaterial(TSTDSTRING(_T("DEFAULT")));
    }
    
    else {
        AcDbMaterial *pMatObj = NULL;
        status = acdbOpenObject(pMatObj, mCurrMaterialId, AcDb::kForRead);
        if (status == Acad::eOk)
            pMatObj->close();
        else {
            // If it wasn't openable (for example, it was erased), 
            // then add the DEFAULT material
            addMaterial(TSTDSTRING(_T("DEFAULT")));
        }
    }

    return mCurrMaterialId;
}

// Return true if material exists in dictionary, otherwise 
// print error message and return false
bool MaterialCmd::materialExists(TSTDSTRING &name, AcDbObjectId *pMaterialId)
{
    bool bExists = false;

    // Open the material dictionary for reading
    AcDbDictionary *pMaterialDict;
    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        // Check that the material exists in the dictionary
        AcDbObjectId materialId;
        bExists = 
            (pMaterialDict->getAt(name.c_str(), materialId) == Acad::eOk);

        // Return material id if storage provided
        if (pMaterialId)
            *pMaterialId = materialId;

        // Close the dictionary
        pMaterialDict->close();
    }

    return bExists;
}



// Get database material names
void MaterialCmd::getDatabaseMaterialNames(StringSet &dbNames)
{
    dbNames.clear();

    AcDbDictionary *pMaterialDict;
    if (acdbHostApplicationServices()->workingDatabase()
            ->getMaterialDictionary(pMaterialDict, AcDb::kForRead) == Acad::eOk)
    {
        AcDbMaterial *pMaterialObj;
        AcDbDictionaryIterator *pDictIter = pMaterialDict->newIterator();
        for (; !pDictIter->done(); pDictIter->next()) 
        {
            if (pDictIter->getObject((AcDbObject *&)pMaterialObj, 
                    AcDb::kForRead) == Acad::eOk) 
            {
                dbNames.insert(pMaterialObj->name());
                pMaterialObj->close();
            }
        }
        delete pDictIter;
        pMaterialDict->close();
    }
}


// Cycle through blue, green, and red colors for adding materials
AcCmEntityColor MaterialCmd::getAddColor(void)
{
    static int cycle = 0;
    const AcCmEntityColor kAddColors[3] = {
        AcCmEntityColor(0,0,255), // blue
        AcCmEntityColor(0,255,0), // green
        AcCmEntityColor(255,0,0), // red
    };
    cycle = (cycle + 1) % 3;
    return kAddColors[cycle];
}

// Cycle through yellow, magenta, and cyan colors for modifying materials
AcCmEntityColor MaterialCmd::getModifyColor(void)
{
    static int cycle = 0;
    const AcCmEntityColor kModifyColors[3] = {
        AcCmEntityColor(255,255,0), // yellow
        AcCmEntityColor(255,0,255), // magenta
        AcCmEntityColor(0,255,255), // cyan
    };
    cycle = (cycle + 1) % 3;
    return kModifyColors[cycle];
}

// Return the color method string
const TCHAR *MaterialCmd::colorMethod (const AcGiMaterialColor &color)
{
    static TSTDSTRING method;

    switch (color.method()) {
    case AcGiMaterialColor::kInherit:
        method = _T("Inherit");
        break;
    case AcGiMaterialColor::kOverride:
        method = _T("Override");
        break;
    }

    return method.c_str();
}

// Return the color value string
const TCHAR *MaterialCmd::colorValue (const AcGiMaterialColor &color)
{
    std::basic_ostringstream<TCHAR> oss;
    static TSTDSTRING result;

    switch (color.method()) {
    case AcGiMaterialColor::kInherit:
        result = _T("Does not apply");
        break;
    case AcGiMaterialColor::kOverride:
        {
            int red = color.color().red(),
                green = color.color().green(),
                blue = color.color().blue();
            oss << _T("(") << red << _T(",") << green << _T(",") << blue << _T(")");
            result = oss.str();
        }
        break;
    }

    return result.c_str();
}
