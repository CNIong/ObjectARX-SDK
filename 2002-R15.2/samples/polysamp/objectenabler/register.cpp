//
// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// This file demonstrates how to make an Object Enabler Registrar.
//
// It creates register.dbx, an ObjectDBX applet used to update the
// system registry for an accompanying Object Enabler - AsdkPolyOBJ.dbx
// in this case.
// 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <objbase.h>

#include "rxregsvc.h"

#include "assert.h"
#include "dbproxy.h"
#include "../poly.h"

extern "C" {

// locally defined entry point invoked by Rx.

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);

}

//*************************************************************************
// Code for the Class Body. 
//*************************************************************************

class AsdkPolyRegistrar : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AsdkPolyRegistrar);
};

ACRX_DXF_DEFINE_MEMBERS(AsdkPolyRegistrar, AcRxObject,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
AcDbProxyEntity::kAllAllowedBits, POLYGON, 
"AsdkPolyOBJ\
|Product Desc:     PolyCAD ARX App For Polygon Entity\
|Company:          Autodesk,Inc.\
|WEB Address:      www.autodesk.com");

// This function swaps the name "asdkpolyobj.dbx" for "register.dbx"
// so that we update the registry to load the Object Enabler.
//
int
swapName(char *name, const char *swap)
{
    char *p;
    if ((p = strstr(name, "register.dbx")))
        sprintf( p, "%s", swap );
    else
        // Windows95/98 always fails even if the string is converted to lowercase. Only
        // working solution was to compare with an UPPERCASE string.
        if ((p = strstr(name, "REGISTER.DBX")))
            sprintf( p, "%s", swap );

    return strlen(name);
}

void
updateRegistry()
{
    // Represents your company's Registry location
    const char pAppInfoLoc[] = 
        "Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\PolySamp";

    // The final argument of Adesk::kTrue means that this app will be
    // registered under the Autodesk/ObjectDBX area of the registry
    // All ObjectDBX apps can search for it there, in addition to AutoCAD
    //
    acrxRegisterApp((AcadApp::LoadReasons)(AcadApp::kOnProxyDetection), 
                     "AsdkPolyOBJ", pAppInfoLoc  , 2, Adesk::kTrue);

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
    status = RegCreateKeyEx(rkey, "AsdkPolyOBJ", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &prodKey, &result);
    RegCloseKey(rkey);
    if (status != ERROR_SUCCESS)
        return;

    HKEY loaderKey;
    status = RegCreateKeyEx(prodKey, "Loader", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &loaderKey, &result);
    
    if (status == ERROR_SUCCESS) {
        HMODULE modHandle = GetModuleHandle("register.dbx");
        if (modHandle) {
            // long filenames have a max length of 255.  total directory path
            // length is also 255 or less,  so a buffer of 512 bytes should be
            // fine.
            // 
            char modulePath[512];
            char fullPath[512];
            char* pFile;
            
            DWORD pathLength = GetModuleFileName(modHandle, modulePath, 512);
            if (pathLength) {

                // WIN95 can return 8.3 path which will fail in swapName. Beforre calling swap
                // name the path is converted to a full path.
                GetFullPathName(  modulePath,   // pointer to name of file to find path for
                                  512,          // size, in characters, of path buffer
                                  fullPath,     // pointer to path buffer
                                  &pFile );      // pointer to filename in path

                // fix up the modulePath to NOT specify register.dbx
                pathLength = swapName(fullPath, "asdkpolyobj.dbx");

                RegSetValueEx(loaderKey, "MODULE", 0, REG_SZ,
                    (const unsigned char*)fullPath, pathLength + 1);
            }

        }
        RegCloseKey(loaderKey);
    }

    HKEY nameKey;
    status = RegCreateKeyEx(prodKey, "Name", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &nameKey, &result);
    RegCloseKey(prodKey);
    if (status != ERROR_SUCCESS)
        return;

    RegSetValueEx(nameKey, "AsdkPolyOBJ", 0, REG_SZ,
        (const unsigned char*)"AsdkPolyOBJ", 12);
    RegCloseKey(nameKey);
}

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    

    switch(msg) {

    case AcRx::kInitAppMsg:

        acrxUnlockApplication(pkt);		// Try to allow unloading

        acrxRegisterAppMDIAware(pkt);

        AsdkPolyRegistrar::rxInit();
        updateRegistry();
        break;

    case AcRx::kUnloadAppMsg:

        deleteAcRxClass(AsdkPolyRegistrar::desc());
        break;
	}
    return AcRx::kRetOK;
}
