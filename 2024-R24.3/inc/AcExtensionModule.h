//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      inc/arxsdk/AcExtensionModule.h
//
// DESCRIPTION
//
//  This file provides two useful classes for developers of MFC extensions
// to AutoCAD (ARX applications in particular). There is no source file
// correponding to this file; the classes should be implemented in the DLL
// that includes this file (a task simplified by using the provided macros).
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CAcExtensionModule - MFC Extension Module and Resource Manager
//
//   This class serves two purposes - it provides a placeholder for an
// AFX_EXTENSION_MODULE structure (normally used to initialize or terminate
// an MFC extension DLL) and tracks two resource providers for the DLL.
//   The resource providers are the module's resources (normally the DLL
// itself, but may be set to some other module) and the default resources
// (normally the host application, actually the provider currently active
// when AttachInstance() is called). CAcExtensionModule tracks these to
// simplify switching MFC's resource lookup between the default and the
// module's.
//   A DLL should create exactly one instance of this class and provide the
// implementation for the class (use the macros included in this file and
// refer to the given example).
class CAcExtensionModule {
public:
                CAcExtensionModule ();
                ~CAcExtensionModule ();

protected:
        bool    m_bAttached;
        HINSTANCE m_hDefaultResource;
        HINSTANCE m_hModuleResource;
#ifndef _ADESK_MAC_
        AFX_EXTENSION_MODULE m_module;
#endif

public:
        bool    Attached () const;
        HINSTANCE DefaultResourceInstance () const;
        HINSTANCE ModuleResourceInstance () const;

        // Attaches the Extension DLL to MFC and updates the member extension and resource
        // dll handles.
        // hExtInst is the handle of the extension dll
        // hResInst is the handle of the resource dll (may be same as hExtInst)
        // Returns TRUE on success and FALSE otherwise. 
        // On success a corresponding call to DetachInstance() is
        // required before the DLL terminates.
        bool    AttachInstance (HINSTANCE hExtInst, HINSTANCE hResInst);

        // Use this overload if you don't have a separate resource dll
        bool    AttachInstance (HINSTANCE hExtInst)
        {
            return this->AttachInstance(hExtInst, hExtInst);
        }

        // Detaches the Extension DLL from MFC.
        void    DetachInstance ();
};

inline CAcExtensionModule::CAcExtensionModule () :
    m_bAttached(false),
    m_hDefaultResource(NULL),
    m_hModuleResource(NULL)
{
#ifndef _ADESK_MAC_
    m_module.bInitialized = FALSE;
    m_module.hModule = NULL;
    m_module.hResource = NULL;
    m_module.pFirstSharedClass = NULL;
    m_module.pFirstSharedFactory = NULL;
#endif
}

inline CAcExtensionModule::~CAcExtensionModule ()
{
}

inline bool CAcExtensionModule::Attached () const
{
    return m_bAttached;
}

inline bool CAcExtensionModule::AttachInstance (HINSTANCE hExtInst, HINSTANCE hResInst)
{
    ASSERT(hExtInst != nullptr);
    ASSERT(hResInst != nullptr);
    if (m_bAttached)
        return false;
#ifndef _ADESK_MAC_
    // Initialize m_module
    ASSERT(!m_module.bInitialized);
    m_bAttached = AfxInitExtensionModule(m_module, hExtInst) != 0;
#else
    m_bAttached = true;
#endif
    ASSERT(this->m_hDefaultResource == nullptr);
    ASSERT(this->m_hModuleResource == nullptr);
    if (m_bAttached) {
        this->m_hDefaultResource = ::AfxGetResourceHandle();
        this->m_hModuleResource = hResInst;
#ifndef _ADESK_MAC_
        ASSERT(this->m_module.hModule == hExtInst);
        ASSERT(this->m_module.hResource == hExtInst);
        this->m_module.hResource = hResInst;
        new CDynLinkLibrary(m_module);
#endif
    }
    return m_bAttached;
}

inline HINSTANCE CAcExtensionModule::DefaultResourceInstance () const
{
    return m_hDefaultResource;
}

inline void CAcExtensionModule::DetachInstance ()
{
    if (m_bAttached) {
#ifndef _ADESK_MAC_
        AfxTermExtensionModule(m_module);
#endif
        this->m_hDefaultResource = nullptr;
        this->m_hModuleResource = nullptr;
        m_bAttached = FALSE;
    }
}

inline HINSTANCE CAcExtensionModule::ModuleResourceInstance () const
{
    return m_hModuleResource;
}

/////////////////////////////////////////////////////////////////////////////
// CAcModuleResourceOverride - Switch between default and module's resources
//
//   Use an instance of this class to switch between resource providers. When
// the object is constructed a new resource provider will get switched in.
// Upon destruction the original resource provider will be restored. For
// example:
//
//      void MyFunc ()
//      {
//          CAcModuleResourceOverride myResources;
//              .
//              .
//      }
//
// Upon entry to this function the module's resources will be selected. When
// the function returns the default resources will be restored.
//   A resource override can be used in any of three ways:
//
//  o   Use the default constructor (no arguments) to switch to the module's
//      resources. The default resources will be restored by the destructor.
//      The module/default resources are those maintained by the DLL's
//      CAcExtensionModule.
//
//  o   Pass NULL (or 0) to the constructor. The DLL's resources will be
//      selected and the resources that were in effect will be restored when
//      the override object is destroyed.
//
//  o   Pass a non-NULL handle to the constructor. The associated module's
//      resources will be and the resources that were in effect will be
//      restored when the override object is destroyed.

class CAcModuleResourceOverride {
public:
                    CAcModuleResourceOverride ();
                    CAcModuleResourceOverride (HINSTANCE hInst);
                    ~CAcModuleResourceOverride ();
                    static HINSTANCE ResourceInstance() { return m_extensionModule.ModuleResourceInstance(); }
private:
static  CAcExtensionModule& m_extensionModule;
HINSTANCE m_previousResourceInstance;
};

inline CAcModuleResourceOverride::CAcModuleResourceOverride ()
    : CAcModuleResourceOverride(NULL)
{
}

inline CAcModuleResourceOverride::CAcModuleResourceOverride (HINSTANCE hInst)
{
    m_previousResourceInstance = AfxGetResourceHandle();
    HINSTANCE hInstanceToSet = m_extensionModule.ModuleResourceInstance();
    if (hInst)
        hInstanceToSet = hInst;
    AfxSetResourceHandle(hInstanceToSet);
}

inline CAcModuleResourceOverride::~CAcModuleResourceOverride ()
{
    ASSERT(m_previousResourceInstance);
    AfxSetResourceHandle(m_previousResourceInstance);
    m_previousResourceInstance = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Extension Module Decalaration and Implementation Macros
//
//  Instatiate an extension module once in a single source file in your DLL
// project. If you want to access the extension module object from other
// source files in your project then use the declaration macro as well
// (usually in an include file). For example, an ARX application's main DLL
// source file might contain:
//
//      AC_IMPLEMENT_EXTENSION_MODULE(myDLL)
//
//      extern "C" int APIENTRY
//      DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
//      {
//	        // Remove this if you use lpReserved
//	        UNREFERENCED_PARAMETER(lpReserved);
//
//	        if (dwReason == DLL_PROCESS_ATTACH)
//	        {
//               theArxDLL.AttachInstance(hInstance);
//	        }
//	        else if (dwReason == DLL_PROCESS_DETACH)
//	        {
//               theArxDLL.DetachInstance();  
//	        }
//	        return 1;   // ok
//      }
//
//
// To publicize the extension module in this example to other source files
// add the following to the module's main include file:
//
//      AC_DECLARE_EXTENSION_MODULE(myDLL)

#define AC_DECLARE_EXTENSION_MODULE(exm)        \
    extern CAcExtensionModule exm;

#define AC_IMPLEMENT_EXTENSION_MODULE(exm)      \
    CAcExtensionModule exm;                     \
    CAcExtensionModule& CAcModuleResourceOverride::m_extensionModule = exm;

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

