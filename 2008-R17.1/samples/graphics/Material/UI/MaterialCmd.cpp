//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
#include "AcString.h"

typedef std::map<AcDbDatabase *,MaterialCmd> CmdMap;
static CmdMap matCmds;

const TCHAR *MaterialCmd::kCmdNames[kCmdCt] = 
{ 
    _T("MATLIST"),      // Lists the database materials
    _T("MATADD"),       // Adds a database material
    _T("TEXMATADD"),    // Adds a database texture material (diffuse map)
    _T("LSMATADD"),     // Adds a database material with these attributes:
                        // - Diffuse map
                        // - Opacity map
                        // - Normal map
                        // - Global illumination and final gathering disabled
                        // - Advanced material mode
                        //
    _T("MATDELETE"),    // Removes a database material
    _T("MATMODIFY"),    // Demonstrates modification of materials, cycling through several presets
    _T("MATREPLACE"),   // Replaces a given material or all materials in the database
    _T("MATENTADD"),    // Adds a custom entity with the current material assigned to it
    _T("LSENTADD"),     // Adds a custom entity with the current landscape material assigned to it    
    _T("MATTILE"),        // Adds a database material witht the Tile procedural material
    _T("MATSPECKLE"),    // Adds as database material witht the Speckle procedural material with Advance lightining material properties
    _T("MATWAVE"),        // Adds as database material witht the Noise procedural material with Advance lightining material properties    
    _T("MATCHECKER")  // Adds as database material witht the Noise procedural material with Advance lightining material properties    
};

const AcRxFunctionPtr MaterialCmd::kCmdHandlers[kCmdCt] = 
{ 
    listCmd, 
    addCmd, 
    addTexturedCmd, 
    addLandscapeCmd, 
    deleteCmd, 
    modifyCmd, 
    replaceCmd, 
    entAddCmd,
    lsEntAddCmd,    
    addTile,
    addSpeckle,
    addWave,
    addChecker
};

const TCHAR *MaterialCmd::kCmdPrompts[kMatCmdCt] =
{ 
    _T("\nEnter name of material to list, or <enter> to list all materials: "),
    _T("\nEnter name of material to add: "),
    _T("\nEnter name of textured material to add: "),
    _T("\nEnter name of landscape material to add: "),
    _T("\nEnter name of material to delete, or <enter> to delete all materials: "),
    _T("\nEnter name of material to modify, or <enter> to modify all materials: "),
    _T("\nEnter name of material to replace (wblock copy), or <enter> to replace all materials: "),    
    _T("\nEnter name of the material to add of type Speckle: "),
    _T("\nEnter name of the material to add of type Wave : "),
    _T("\nEnter name of the material to add of type Tile: "),    
    _T("\nEnter name of the material to add of type Checker : ")    
};

const TSTDSTRING MaterialCmd::kDbGlobalName = _T("_GLOBAL_");
const TCHAR *MaterialCmd::kDefaultMaterialName = _T("DEFAULT");
const TCHAR *MaterialCmd::kDefaultLandscapeMaterialName = _T("DEFAULT_LANDSCAPE");

// This sample texture file is found in the sample Textures directory
const TCHAR *MaterialCmd::kSampleTextureFile = _T("Concrete.Cast-In-Place.Exposed Aggregate.Medium.jpg"); 

// These sample diffuse, opacity, and normal map files are provided in the 
// ..\Textures directory.  These files must be copied to a directory in the 
// AutoCAD Textures search path in order to be displayed.
const TCHAR *MaterialCmd::kDiffuseMapFile = _T("landscape_diffuse_map.png"); 
const TCHAR *MaterialCmd::kOpacityMapFile = _T("landscape_opacity_map.png");
const TCHAR *MaterialCmd::kNormalMapFile  = _T("landscape_normal_map.png");


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
    matCmds[pDb].invokeCmd(kAddUntextured);    
}

// Add a material
void MaterialCmd::addTexturedCmd(void)    
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddTextured);    
}

// Add a material - textured with normal map
void MaterialCmd::addLandscapeCmd(void)    
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddLandscape);    
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
void MaterialCmd::entAddCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddEntity);
}

// Create a custom entity with landscape material assignment
void MaterialCmd::lsEntAddCmd(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddLandscapeEntity);
}

void MaterialCmd::addTile(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddTile);
}

void MaterialCmd::addWave(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddWave);
}

void MaterialCmd::addSpeckle(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddSpeckle);
}

void MaterialCmd::addChecker(void) 
{ 
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    matCmds[pDb].invokeCmd(kAddChecker);
}


MaterialCmd::MaterialCmd()
    : mCurrMaterialId (AcDbObjectId::kNull)
    , mCurrLandscapeMaterialId (AcDbObjectId::kNull)
{
}

// Perform a material operation
void MaterialCmd::invokeCmd(Action cmd)
{
    // Create the material entity
    if (cmd == kAddEntity || cmd == kAddLandscapeEntity) 
    {
        addMaterialEntity(cmd);
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
void MaterialCmd::addMaterialEntity(MaterialCmd::Action cmd)
{
    AcGePoint3d cen;
    struct resbuf rbFrom, rbTo;

    bool bLandscape = (cmd == kAddLandscapeEntity);
    AcDbObjectId materialObjId = getCurrentMaterial(bLandscape);

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
    switch (cmd) 
    {
 
     case kList:
         listAllMaterials();
         break;
    case kAddUntextured:
    case kAddTextured:
    case kAddLandscape:
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
            listMaterial(name,cmd);
        break;
    case kAddUntextured:
    case kAddTextured:
    case kAddLandscape:
    case kAddSpeckle:
    case kAddWave:
    case kAddTile:
    case kAddChecker:
        addMaterial(name, cmd);
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
void MaterialCmd::listMaterial(TSTDSTRING &name, Action cmd)
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

        // Close the material and dictionary
        pMaterialObj->close();
        pMaterialDict->close();
    
        //list the texture details , if any exist for the material
        listTextureInfo(name);

        acutPrintf(_T("\n------------------------------------------\n"));
        acutPrintf(_T("\n"));

    }    
}

void MaterialCmd::listTextureInfo(TSTDSTRING &name)
{
    Acad::ErrorStatus        es;
    
    // we have our material name, so try and open it
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    if (!pDb) 
    {
        acutPrintf(_T("\nError: no database"));
        return;
    }

    // get the material dictionary
    AcDbObjectPointer<AcDbDictionary> mtlDict(pDb->materialDictionaryId(), AcDb::kForRead);
    if (Acad::eOk != mtlDict.openStatus()) 
    {
        acutPrintf(_T("\nError: unable to open material dictionary"));
        return;
    }

    // get the material
    AcDbObjectId idMtl;
    es = mtlDict->getAt(name.c_str(), idMtl);
    if (Acad::eOk != es)
    {
        acutPrintf(_T("\nError: Material '%s' not found"), name.c_str());
        return;
    }

    AcDbObjectPointer<AcDbMaterial> mtl(idMtl, AcDb::kForRead);
    if (Acad::eOk != mtl.openStatus()) 
    {
        acutPrintf(_T("\nError: Could not open material '%s' for read"), name.c_str());
        return;
    }

    // now we have the material, lets get each map and print it out..
    int nGenericCount = 0;
    AcGiMaterialColor color;
    AcGiMaterialMap   map;
    double            dValue = 0.0;
    AcGiGenericTexture * pGeneric = NULL;

    // Diffuse
    mtl->diffuse(color, map);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric)
    {
        dumpTexture(_T("Diffuse"), pGeneric);
        nGenericCount++;
    }

    // Bump
    mtl->bump(map);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric)
    {
        dumpTexture(_T("Bump"), pGeneric);
        nGenericCount++;
    }

    // Opacity
    mtl->opacity(dValue, map);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric) 
    {
        dumpTexture(_T("Opacity"), pGeneric);
        nGenericCount++;
    }


    // Reflection
    mtl->reflection(map);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric)
    {
        dumpTexture(_T("Reflection"), pGeneric);
        nGenericCount++;
    }

    // Refraction
    mtl->refraction(dValue, map);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric) 
    {
        dumpTexture(_T("Refraction"), pGeneric);
        nGenericCount++;
    }

    // Specular
    mtl->specular(color, map, dValue);
    pGeneric = AcGiGenericTexture::cast(map.texture());
    if (NULL != pGeneric) 
    {
        dumpTexture(_T("Specular"), pGeneric);
        nGenericCount++;
    }

    if (nGenericCount == 0)
    {
        acutPrintf(_T("\n Material '%s' does not contain any generic textures"), name.c_str());
        return;
    }
}

void MaterialCmd::dumpTexture(ACHAR* szNode, AcGiGenericTexture * pTexture)
{
    // firstly lets dump out the element for the texture
    acutPrintf(_T("\n%s: "), szNode);

    AcGiVariant *varDef = NULL;
    pTexture->definition(varDef);

    dumpVariant(_T("root"), varDef, 1);
}

void MaterialCmd::dumpVariant(ACHAR* name, AcGiVariant* pVariant, int nIndent)
{
    switch (pVariant->type())
    {
    case AcGiVariant::kUndefined:
        writeSpaces(nIndent);
        acutPrintf(_T("\n%s: undefined"), name);
        break;

    case AcGiVariant::kBoolean:
        writeSpaces(nIndent);
        acutPrintf(_T("%s :%s"), name, pVariant->asBoolean() ? _T("true") : _T("false"));
        break;

    case AcGiVariant::kInt:
        writeSpaces(nIndent);
        acutPrintf(_T("%s :%d "), name, pVariant->asInt());
        break;

    case AcGiVariant::kDouble:
        writeSpaces(nIndent);
        acutPrintf(_T("%s :%f "), name, pVariant->asDouble());
        break;

    case AcGiVariant::kColor:
        {
            //writeSpaces(nIndent);
            AcCmColor color = pVariant->asColor();

            writeSpaces(nIndent);
            acutPrintf(_T("Color: "));

            bool bColorRGB = false;
            TCHAR *colorKey = NULL;
            if (color.colorMethod() == AcCmEntityColor::kLayerOff ||
                color.colorMethod() == AcCmEntityColor::kLayerFrozen ||
                color.colorMethod() == AcCmEntityColor::kByColor)
            {
                bColorRGB = true;
                const int keylength = color.dictionaryKeyLength();
                if (color.hasColorName() && keylength > 0) 
                {
                    int strLength = keylength < 300 ? 301 : keylength+1;
                    colorKey = (TCHAR *)malloc((strLength) * sizeof(TCHAR));
                    color.getDictionaryKey(colorKey);
                }
            }

            acutPrintf(_T(" index=\"%d\""), color.colorIndex());
            if (bColorRGB) 
            {
                acutPrintf(_T(" rgb=\"%ld\""), color.color() & 0x00ffffff);
            }
            if (colorKey) 
            {
                acutPrintf(_T(" key=\"%s\""), colorKey);
            }            
        }
        break;

    case AcGiVariant::kString:
        writeSpaces(nIndent);
        acutPrintf(_T("%s :%s "), name, (LPCTSTR)pVariant->asString());
        break;

    case AcGiVariant::kTable:
        {
            if (nIndent > 1) 
            {
                writeSpaces(nIndent);
                acutPrintf(_T("%s :"), name);
            }
            for (int i=0; i< pVariant->getElemCount(); ++i)
            {
                ACHAR* elemName = NULL;
                AcGiVariant* pChildVariant = pVariant->getElemAt(i, elemName);
                if (pChildVariant) {
                    dumpVariant(elemName, pChildVariant, nIndent+1);
                }
                acutDelString(elemName);
            }
            if (nIndent > 1) 
            {    
                writeSpaces(nIndent);                
            }
        }
        break;
    }
}

void MaterialCmd::writeSpaces(int nIndent)
{
    acutPrintf(_T("\n"));
    for (int i=0; i<nIndent; ++i) 
    {
        acutPrintf(_T("  "));
    }
}

// Create a material of the given name and it to the material dictionary
void MaterialCmd::addMaterial(TSTDSTRING &name, 
                              Action cmd)
{
    //    Open the material dictionary for writing
    AcDbDictionary *pMaterialDict;
    Acad::ErrorStatus dbStatus;

    if (acdbHostApplicationServices()->workingDatabase()
        ->getMaterialDictionary(pMaterialDict, AcDb::kForWrite) == Acad::eOk)
    {
        // Create and initialize the material
        AcDbMaterial *pMaterialObj = new AcDbMaterial();

        // Name

        pMaterialObj->setName(name.c_str());

        // Add material to dictionary
        AcDbObjectId &currMaterialId = (cmd == kAddLandscape) 
            ? mCurrLandscapeMaterialId
            : mCurrMaterialId;
        dbStatus = pMaterialDict->setAt(name.c_str(), pMaterialObj, currMaterialId);
        assert (dbStatus == Acad::eOk);

        // Diffuse color
        AcGiMaterialColor diffuseColor;
        diffuseColor.setMethod(AcGiMaterialColor::kOverride);
        diffuseColor.setFactor(1.0);
        diffuseColor.setColor(getAddColor());

        // Diffuse map - null by default
        AcGiMaterialMap diffuseMap;

        switch (cmd)
        {
            case kAddUntextured: 
            {
                // Set diffuse color and map into material
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);
            }
            break;

            case kAddTextured:
            {
                // Image file diffuse map - sample texture
                AcGiImageFileTexture diffuseMapFile;
                diffuseMapFile.setSourceFileName(kSampleTextureFile);
                diffuseMap.setTexture(&diffuseMapFile);

                // Set diffuse color and map into material
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);
            }
            break;

            case kAddLandscape:
            {
                // Image file diffuse map - landscape texture
                AcGiImageFileTexture diffuseMapFile;
                diffuseMapFile.setSourceFileName(kDiffuseMapFile);
                diffuseMap.setTexture(&diffuseMapFile);

                // Set diffuse color and map into material
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);

                // Set material mode to realistic.  This is necessary so transparent
                // pixels on opacity maps do not receive specular highlights during
                // rendering.
                pMaterialObj->setMode(AcGiMaterialTraits::kRealistic);

                // Create an opacity map and set into the material
                AcGiImageFileTexture opacityMapFile;
                opacityMapFile.setSourceFileName(kOpacityMapFile);

                AcGiMaterialMap opacityMap;
                opacityMap.setTexture(&opacityMapFile);

                pMaterialObj->setOpacity(1.0, opacityMap);

                // Create a normal map and set into the material
                AcGiImageFileTexture normalMapFile;
                normalMapFile.setSourceFileName(kNormalMapFile);

                AcGiMaterialMap normalMap;
                normalMap.setTexture(&normalMapFile);

                pMaterialObj->setNormalMap(normalMap, 
                    AcGiMaterialTraits2::kTangentSpace, 
                    1.0);

                // Disable global illumination and final gather on material
                pMaterialObj->setGlobalIllumination(
                    AcGiMaterialTraits2::kGlobalIlluminationNone);
                pMaterialObj->setFinalGather(
                    AcGiMaterialTraits2::kFinalGatherNone);
            }
            break;

            case kAddTile:
            {
                pMaterialObj->setMode(AcGiMaterialTraits::kRealistic);
                            
                AcCmColor clr1, clr2;
                AcGiVariant vMap1, vMap2; 
                AcGiVariant varData,bumpVarData; 
                AcGiVariant subVarData,subVarData2; 
                AcGiVariant vTextureMap1, vTextureMap2; 
                AcGiMaterialMap bumpMap;    

                varData.setElem(_T("Shader"), AcGiVariant(_T("Tile")));
                        
                clr1.setColorMethod(AcCmEntityColor::kByACI);            
                clr1.setColorIndex(7);
                varData.setElem(_T("Color"), AcGiVariant(clr1)); 
            
                // subtexture 1 
                clr1.setColorMethod(AcCmEntityColor::kByACI);            
                clr1.setColorIndex(253);
                vTextureMap1.setElem(_T("Color"), AcGiVariant(clr1));

                subVarData.setElem(_T("Shader"), AcGiVariant(_T("Speckle")));
                clr1.setColorMethod(AcCmEntityColor::kByACI);
                clr1.setColorIndex(26);

                clr2.setColorMethod(AcCmEntityColor::kByACI);
                clr2.setColorIndex(22);    

                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 
                subVarData.setElem(_T("Map1"), vMap1);
                subVarData.setElem(_T("Map2"), vMap2);
                subVarData.setElem(_T("Size"), AcGiVariant(0.24f));
                vTextureMap1.setElem(_T("SubTexture"),subVarData);
                varData.setElem(_T("Map1"), vTextureMap1);

                // subtexture 2 
                clr1.setColorMethod(AcCmEntityColor::kByACI);            
                clr1.setColorIndex(250);
                vTextureMap2.setElem(_T("Color"), AcGiVariant(clr1));

                subVarData2.setElem(_T("Shader"), AcGiVariant(_T("Noise")));
                subVarData2.setElem(_T("NoiseType"), AcGiVariant(0.0f));
                clr1.setColorMethod(AcCmEntityColor::kByACI);
                clr1.setColorIndex(32);

                clr2.setColorMethod(AcCmEntityColor::kByACI);
                clr2.setColorIndex(43);                
                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 

                subVarData2.setElem(_T("Map1"), vMap1);
                subVarData2.setElem(_T("Map2"), vMap2);

                subVarData2.setElem(_T("ThresholdHigh"), AcGiVariant(1.00f));
                subVarData2.setElem(_T("Levels"), AcGiVariant(3.00f));
                subVarData2.setElem(_T("Size"), AcGiVariant(0.20f));

                vTextureMap2.setElem(_T("SubTexture"),subVarData2);
                varData.setElem(_T("Map2"), vTextureMap2);            
                
                varData.setElem(_T("HorizontalCount"),AcGiVariant(4.0f));
                varData.setElem(_T("VerticalCount"), AcGiVariant(4.0f));    
                varData.setElem(_T("VerticalGap"),AcGiVariant(0.50f));
                varData.setElem(_T("HorizontalGap"),AcGiVariant(0.50f));
                varData.setElem(_T("LineShift"),AcGiVariant(0.00f));
                varData.setElem(_T("Holes"), AcGiVariant(0.0f));
                varData.setElem(_T("RandomSeed"), AcGiVariant(55568.0f));        
                varData.setElem(_T("LockGapSymmetry "),AcGiVariant(1.0f));
                varData.setElem(_T("FadeVariance"),AcGiVariant(0.05f));
                varData.setElem(_T("EdgeRoughness"),AcGiVariant(0.00f));
                varData.setElem(_T("PerColumn"),AcGiVariant(1.0f));
                varData.setElem(_T("ChangeColumn"),AcGiVariant(0.05f));
                varData.setElem(_T(" PerRow"),AcGiVariant(2.00f));
                varData.setElem(_T("ChangeRow"),AcGiVariant(0.5f));
                varData.setElem(_T("BrickType"),AcGiVariant(1.00f));
                varData.setElem(_T("PresetPattern "),AcGiVariant(1.00f));
                varData.setElem(_T("ColorVariance"),AcGiVariant(0.40f));
                            
                // assign the data to a generic texture 
                AcGiGenericTexture texture; 
                texture.setDefinition(varData);

                pMaterialObj->diffuse(diffuseColor,diffuseMap);
                
                diffuseColor.setMethod(AcGiMaterialColor::kOverride);
                diffuseColor.setFactor(1.0);            
                diffuseColor.setColor(AcCmEntityColor(128,128,128));

                diffuseMap.setTexture(&texture);

                //Following code is not setting the U and V Tiling values for the tiles,

                AcGiMapper mapper;
                mapper = diffuseMap.mapper();
                mapper.setUTiling(AcGiMapper::kMirror);
                mapper.setVTiling(AcGiMapper::kTile);
                AcGeMatrix3d transform;
                transform.setToIdentity();            
                transform.setToScaling(10.0);
                mapper.setTransform(transform);
                diffuseMap.setMapper(mapper);
                
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);                    
                                
                // bump Texture map
                bumpVarData.setElem(_T("Shader"), AcGiVariant(_T("Tile")));
                clr1.setColorMethod(AcCmEntityColor::kByACI);            
                clr1.setColorIndex(7);
                bumpVarData.setElem(_T("Color"), AcGiVariant(clr1)); 

                clr1.setColorMethod(AcCmEntityColor::kByACI);            
                clr1.setColorIndex(254);

                clr2.setColorMethod(AcCmEntityColor::kByACI);            
                clr2.setColorIndex(251);
        
                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 
                bumpVarData.setElem(_T("Map1"), vMap1);
                bumpVarData.setElem(_T("Map2"), vMap2); 

                bumpVarData.setElem(_T("HorizontalCount"),AcGiVariant(4.0f));
                bumpVarData.setElem(_T("VerticalCount"), AcGiVariant(4.0f));    
                bumpVarData.setElem(_T("ColorVariance"),AcGiVariant(0.00f));
                bumpVarData.setElem(_T("VerticalGap"),AcGiVariant(0.50f));
                bumpVarData.setElem(_T("HorizontalGap"),AcGiVariant(0.50f));
                bumpVarData.setElem(_T("LineShift"),AcGiVariant(0.00f));
                bumpVarData.setElem(_T("Holes"), AcGiVariant(0.0f));
                bumpVarData.setElem(_T("RandomSeed"), AcGiVariant(55568.0f));        
                bumpVarData.setElem(_T("LockGapSymmetry "),AcGiVariant(1.0f));
                bumpVarData.setElem(_T("FadeVariance"),AcGiVariant(0.05f));
                bumpVarData.setElem(_T("EdgeRoughness"),AcGiVariant(0.00f));
                bumpVarData.setElem(_T("PerColumn"),AcGiVariant(1.0f));
                bumpVarData.setElem(_T("ChangeColumn"),AcGiVariant(0.05f));
                bumpVarData.setElem(_T("PerRow"),AcGiVariant(2.00f));
                bumpVarData.setElem(_T("ChangeRow"),AcGiVariant(0.5f));
                bumpVarData.setElem(_T("BrickType"),AcGiVariant(1.00f));
                bumpVarData.setElem(_T("PresetPattern "),AcGiVariant(2.00f));
                            
                AcGiGenericTexture bumpTexture;
                bumpTexture.setDefinition(bumpVarData);
                pMaterialObj->bump(bumpMap);

                bumpMap.setTexture(&bumpTexture);
                pMaterialObj->setBump(bumpMap);                        
            }
            break;

            case kAddWave:
            {
                pMaterialObj->setMode(AcGiMaterialTraits::kRealistic);

                pMaterialObj->diffuse(diffuseColor,diffuseMap);        
                diffuseColor.setMethod(AcGiMaterialColor::kOverride);
                diffuseColor.setFactor(1.0);            
                diffuseColor.setColor(AcCmEntityColor(131,198,246));
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);

                pMaterialObj->setShininess(100.0);
                pMaterialObj->setOpacity(9.0, AcGiMaterialMap());
                pMaterialObj->setRefraction(1.330, AcGiMaterialMap());            

                AcGiMaterialMap bumpMap;
                AcGiVariant varData;         
                varData.setElem(_T("Shader"), AcGiVariant(_T("Wave")));    

                varData.setElem(_T("Amplitude "), AcGiVariant(1.0f));    
                varData.setElem(_T("Phase"), AcGiVariant(0.0f));
                varData.setElem(_T("Distribution"), AcGiVariant("1.0f"));
                varData.setElem(_T("RandomSeed"), AcGiVariant(30159.0f));

                // initialize some color values 
                AcCmColor clr1, clr2;
                clr2.setRGB(0,0,0);
                clr2.setRGB(255,255,255);
                AcGiVariant vMap1, vMap2; 
                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 
                varData.setElem(_T("Map1"), vMap1);
                varData.setElem(_T("Map2"), vMap2); 

                varData.setElem(_T("NumWaveSets"), AcGiVariant(31.0f));    
                varData.setElem(_T("WaveRadius"), AcGiVariant(100.0f));
                varData.setElem(_T("WaveLenMin"), AcGiVariant(4.0f));
                varData.setElem(_T("WaveLenMax"), AcGiVariant(8.0f));

                AcGiGenericTexture texture;
                texture.setDefinition(varData);
                pMaterialObj->bump(bumpMap);
                bumpMap.setTexture(&texture);
                pMaterialObj->setBump(bumpMap);    
        
            }
            break;

            case kAddSpeckle:
            {
                pMaterialObj->setMode(AcGiMaterialTraits::kRealistic);

                pMaterialObj->diffuse(diffuseColor,diffuseMap);        
                diffuseColor.setMethod(AcGiMaterialColor::kOverride);
                diffuseColor.setFactor(1.0);            
                diffuseColor.setColor(AcCmEntityColor(128,128,128));
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);

                pMaterialObj->setShininess(90.0);            
                pMaterialObj->setRefraction(1.400,AcGiMaterialMap());            

                AcGiVariant varData; 
                varData.setElem(_T("Shader"), AcGiVariant(_T("Speckle")));

                // next set up the size of the speckle
                varData.setElem(_T("Size"), AcGiVariant(0.04f));

                // initialize some color values 
                AcCmColor clr1, clr2;

                clr1.setColorMethod(AcCmEntityColor::kByACI);
                clr1.setColorIndex(38);

                clr2.setColorMethod(AcCmEntityColor::kByACI);
                clr2.setColorIndex(43);

                AcGiVariant vMap1, vMap2; 
                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 
                varData.setElem(_T("Map1"), vMap1);
                varData.setElem(_T("Map2"), vMap2); 

                //assign the data to a generic texture 
                AcGiGenericTexture texture;
                texture.setDefinition(varData);
                pMaterialObj->diffuse(diffuseColor,diffuseMap);
                diffuseMap.setTexture(&texture);

                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);

                AcGiMaterialMap bumpMap;
                AcGiVariant bumpData; 
                bumpData.setElem(_T("Shader"), AcGiVariant(_T("Speckle")));    
                bumpData.setElem(_T("Size"), AcGiVariant(0.039370f));
                AcGiGenericTexture bumpTexture;
                bumpTexture.setDefinition(bumpData);
                pMaterialObj->bump(bumpMap);
                bumpMap.setTexture(&bumpTexture);
                pMaterialObj->setBump(bumpMap);
            }
            break;

            case kAddChecker:
            {
                pMaterialObj->setMode(AcGiMaterialTraits::kRealistic);
            
                diffuseColor.setMethod(AcGiMaterialColor::kOverride);
                diffuseColor.setFactor(1.0);            
                diffuseColor.setColor(AcCmEntityColor(131,198,246));

                pMaterialObj->setShininess(100.0);
                pMaterialObj->setOpacity(9.0,AcGiMaterialMap());
                pMaterialObj->setRefraction(1.330,AcGiMaterialMap());            

                AcGiMaterialMap bumpMap;
                AcGiVariant varData;         
                varData.setElem(_T("Shader"), AcGiVariant(_T("Checker")));    
                varData.setElem(_T("Soften"), AcGiVariant(0.0f));        
                
                //// initialize some color values 
                AcCmColor clr1, clr2;
                clr2.setRGB(0,0,0);
                clr2.setRGB(255,255,255);
                
                AcGiVariant vMap1, vMap2; 
                vMap1.setElem(_T("Color"), AcGiVariant(clr1)); 
                vMap2.setElem(_T("Color"), AcGiVariant(clr2)); 
                varData.setElem(_T("Map1"), vMap1);
                varData.setElem(_T("Map2"), vMap2); 

                AcGiGenericTexture texture;
                texture.setDefinition(varData);
                pMaterialObj->diffuse(diffuseColor,diffuseMap);        
                diffuseMap.setTexture(&texture);
                pMaterialObj->setDiffuse(diffuseColor, diffuseMap);
            }
            break;

            default:
                ASSERT (false); // Unhandled command!
                break;
        }

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
AcDbObjectId MaterialCmd::getCurrentMaterial(bool bLandscape)
{
    Acad::ErrorStatus status;

    // Get untextured or landscape material
    const TCHAR *pDefaultMaterialName = bLandscape
        ? kDefaultLandscapeMaterialName
        : kDefaultMaterialName;
    Action addCmd = bLandscape 
        ? kAddLandscape
        : kAddUntextured;
    AcDbObjectId &currMaterialId = bLandscape 
        ? mCurrLandscapeMaterialId
        : mCurrMaterialId; 

    // Get or create the material with the default name, 
    // if no current material is already available
    if (currMaterialId == AcDbObjectId::kNull) 
    {
        // Open the material dictionary for reading
        AcDbDictionary *pMaterialDict;
        status = acdbHostApplicationServices()->workingDatabase()->
                     getMaterialDictionary(pMaterialDict, AcDb::kForRead);

        if (status == Acad::eOk)
        {
            // Check that the default material exists in the dictionary
            AcDbObjectId materialId;
            if (pMaterialDict->getAt(pDefaultMaterialName, materialId) == Acad::eOk)
                currMaterialId = materialId;
            pMaterialDict->close();
        }

        // If it wasn't found, add the default material
        if (currMaterialId == AcDbObjectId::kNull)
            addMaterial(TSTDSTRING(pDefaultMaterialName), addCmd);
    }
    
    else {
        AcDbMaterial *pMatObj = NULL;
        status = acdbOpenObject(pMatObj, currMaterialId, AcDb::kForRead);

        if (status == Acad::eOk)
            pMatObj->close();
        else {
            // If it wasn't openable (for example, it was erased), 
            // then add the default material
            addMaterial(TSTDSTRING(pDefaultMaterialName), addCmd);
        }
    }

    return currMaterialId;
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
