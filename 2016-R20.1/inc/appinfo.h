//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// appinfo.h
//
// DESCRIPTION: Definition of class AcadAppInfo.  Used as part of the
//              unknown command demand load notification mechanism.

#ifndef _appinfo_h
#define _appinfo_h 1

//#if defined(__cplusplus)

#include "acdb.h"
#include "rxdlinkr.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcadAppInfoImp;

class AcadAppInfo: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcadAppInfo);

    enum CmdStatus {
        kNoAction    = 0,
        kRetry       = 1,
        kShowMsg     = 2,
        kNoModule    = 3
    };
#pragma warning(push)
#pragma warning(disable:4480)
    enum MgdType {
        kUnManaged   = 0,
        kManaged     = 1,
        kJavaScript  = 2
    };
#pragma warning(pop)
    typedef AcadAppInfo::CmdStatus (*LoaderFunPtr)(void *);

    AcadAppInfo();
    virtual ~AcadAppInfo();

    const ACHAR *appName() const;
    void setAppName(const ACHAR *);

    const ACHAR *moduleName() const;
    void setModuleName(const ACHAR *);

    const ACHAR *appDesc() const;
    void setAppDesc(const ACHAR *);

    bool appImplements(const ACHAR *) const;
    
    AcadAppInfo::MgdType managed() const;
    void setManaged(AcadAppInfo::MgdType mgdType);

    AcadApp::ErrorStatus writeToRegistry(bool bObjDbx = false, bool skipHKLM = false);

    AcadApp::ErrorStatus readFromRegistry();
    AcadApp::ErrorStatus delFromRegistry(bool bObjDbx = false);

    AcadAppInfo::CmdStatus runAppLoader();
    void setAppLoader(LoaderFunPtr);

    AcadApp::LoadReasons loadReason();
    void setLoadReason(AcadApp::LoadReasons);
    AcadApp::ErrorStatus status() const;

    AcadApp::ErrorStatus writeGroupNameToRegistry(const ACHAR* group);

    AcadApp::ErrorStatus writeCommandNameToRegistry(const ACHAR* globalCmdName,
                                                    const ACHAR* localCmdName);
    
private:
    AcadAppInfoImp * mpImp;
};

#pragma pack (pop)
//#endif /* defined (__cplusplus) */
#endif /* _appinfo_h */

