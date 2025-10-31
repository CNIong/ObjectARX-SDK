//
//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
//
#pragma once

#include "MaterialJig.h"
#include "AcCmd.h"

#ifdef _UNICODE
#define TSTDSTRING std::wstring
#else
#define TSTDSTRING std::string
#endif

#include <string>
#include <set>
typedef std::set<TSTDSTRING> StringSet;

class MaterialCmd
{
public:
    enum Action 
    { 
        // Material commands
        kList, 
        kAddUntextured, 
        kAddTextured, 
        kAddLandscape, 
        kDelete, 
        kModify, 
        kReplace, 
        kAddSpeckle,
        kAddWave,
        kAddTile,        
        kAddChecker,
        kModifyFilter,

        // Entity commands
        kAddEntity, 
        kAddLandscapeEntity,

        kCmdCt, 
        kMatCmdCt = kCmdCt -2
    };

    MaterialCmd();

    static const TCHAR *cmdName(int cmd);
    static const AcRxFunctionPtr cmdHandler(int cmd);

    static void unload(void);

private:
    static void listCmd(void);
    static void addCmd(void);
    static void addTexturedCmd(void);
    static void addLandscapeCmd(void);
    static void deleteCmd(void);
    static void modifyCmd(void);
    static void replaceCmd(void);
    static void entAddCmd(void);
    static void lsEntAddCmd(void);
    static void addTileCmd(void); 
    static void addWaveCmd(void);
    static void addSpeckleCmd(void);
    static void addCheckerCmd(void);
    static void modifyFilterCmd(void);
    

    void invokeCmd(Action cmd);

    void addMaterialEntity(Action cmd);

    void allMaterialsCmd(Action cmd);
    bool singleMaterialCmd(Action cmd, TCHAR *result);

    void listAllMaterials(void);
    void modifyAllMaterials(void);
    void deleteAllMaterials(void);
    void replaceAllMaterials(void);

    void listMaterial(TSTDSTRING &name, Action cmd);
    void listTextureInfo(TSTDSTRING &name); 
    void writeSpaces(int nIndent);
    void dumpVariant(ACHAR* name, AcGiVariant* pVariant, int nIndent);
    void dumpTexture(ACHAR* szNode, AcGiGenericTexture * pTexture);

    void addMaterial(TSTDSTRING &name, 
                     Action cmd);
    void deleteMaterial(TSTDSTRING &name);
    void modifyMaterial(TSTDSTRING &name);
    void replaceMaterial(TSTDSTRING &name);
    void modifyMaterialFilter(TSTDSTRING &name);

    void replaceMaterialHelper(AcDbDatabase *pSourceDb, AcDbObjectIdArray &sourceDbMaterialIds);

    void getDatabaseMaterialNames(StringSet &dbNames);

    AcCmEntityColor getAddColor(void);
    AcCmEntityColor getModifyColor(void);

    const TCHAR *colorMethod (const AcGiMaterialColor &color);
    const TCHAR *colorValue (const AcGiMaterialColor &color);

    void enableMaterialSync(void);
    bool materialExists(TSTDSTRING &name, AcDbObjectId *pMaterialId = NULL);

    AcDbObjectId getCurrentMaterial(bool bLandscape = false);
    AcDbObjectId mCurrMaterialId;
    AcDbObjectId mCurrLandscapeMaterialId;

    static const TCHAR *kCmdNames[kCmdCt];
    static const AcRxFunctionPtr kCmdHandlers[kCmdCt];
    static const TCHAR *kCmdPrompts[kMatCmdCt];

    static const TSTDSTRING kDbGlobalName;
    static const TCHAR *kDefaultMaterialName;
    static const TCHAR *kDefaultLandscapeMaterialName;

    static const TCHAR *kSampleTextureFile; 
    static const TCHAR *kDiffuseMapFile;
    static const TCHAR *kOpacityMapFile;
    static const TCHAR *kNormalMapFile;
    static const TCHAR *kBumpMapFile;
};

// Return the command name
inline const TCHAR *MaterialCmd::cmdName(int cmd)
{
    return kCmdNames[cmd];
}

// Return the command handler
inline const AcRxFunctionPtr MaterialCmd::cmdHandler(int cmd)
{
    return kCmdHandlers[cmd];
}

