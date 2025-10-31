//
//
// (C) Copyright 2002,2004 by Autodesk, Inc. 
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

#include <string>
#include <set>
typedef std::set<std::string> StringSet;

class MaterialCmd
{
public:
    enum Action { 
        kList, kAdd, kAddTextured, kDelete, kModify, kReplace,
        kCreate, 
        kCmdCt, kMatCmdCt = kCmdCt - 1 };

    MaterialCmd();

    static const char *cmdName(int cmd);
    static const AcRxFunctionPtr cmdHandler(int cmd);

    static void unload(void);

private:
    static void listCmd(void);
    static void addCmd(void);
    static void addTexturedCmd(void);
    static void deleteCmd(void);
    static void modifyCmd(void);
    static void replaceCmd(void);
    static void createCmd(void);

    void invokeCmd(Action cmd);

    void addMaterialEntity(void);

    void allMaterialsCmd(Action cmd);
    bool singleMaterialCmd(Action cmd, char *result);

    void listAllMaterials(void);
    void modifyAllMaterials(void);
    void deleteAllMaterials(void);
    void replaceAllMaterials(void);

    void listMaterial(std::string &name);
    void addMaterial(std::string &name, bool bTextured = false);
    void deleteMaterial(std::string &name);
    void modifyMaterial(std::string &name);
    void replaceMaterial(std::string &name);

    void replaceMaterialHelper(AcDbDatabase *pSourceDb, AcDbObjectIdArray &sourceDbMaterialIds);

    void getRenderMaterialNames(StringSet &rendNames);
    void getDatabaseMaterialNames(StringSet &dbNames);

    AcCmEntityColor getAddColor(void);
    AcCmEntityColor getModifyColor(void);

    const char *colorMethod (const AcGiMaterialColor &color);
    const char *colorValue (const AcGiMaterialColor &color);

    void enableMaterialSync(void);
    bool materialExists(std::string &name, AcDbObjectId *pMaterialId = NULL);
    bool initAvLib(void);

    AcDbObjectId getCurrentMaterial(void);
    AcDbObjectId mCurrMaterialId;

    static const char *kCmdNames[kCmdCt];
    static const AcRxFunctionPtr kCmdHandlers[kCmdCt];
    static const char *kCmdPrompts[kMatCmdCt];

    static const std::string kDbGlobalName;
    static const std::string kRendGlobalName;
};

// Return the command name
inline const char *MaterialCmd::cmdName(int cmd)
{
    return kCmdNames[cmd];
}

// Return the command handler
inline const AcRxFunctionPtr MaterialCmd::cmdHandler(int cmd)
{
    return kCmdHandlers[cmd];
}

