//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#ifndef _DYNPROPS_H
#define _DYNPROPS_H

interface IPropertyManager;
interface IDynamicProperty;
//--------------------------
// OPMPropertyExtension interface
// This class is implemented by AutoCAD and available through
// GET_OPMEXTENSION_PROTOCOL(). Once you have the OPMPropertyExtension*
// you can either add your own property manager via SetPropertyManager
// or use the one provided by us via GetPropertyManager 
//--------------------------
class OPMPropertyExtension : public AcRxObject  
{
public:
    ACRX_DECLARE_MEMBERS(OPMPropertyExtension);
    virtual ~OPMPropertyExtension(){}
    //Get the property manager for this extension, if one is not
    //available, it will be created. This is a real COM object so
    //you will need to release the IPropertyManager* when you 
    //are done with it.
    virtual IPropertyManager* GetPropertyManager() = 0;
    //This function allows you to provide your own property manager
    virtual void SetPropertyManager(IPropertyManager* pPropManager) = 0;
};

//--------------------------
// OPMPropertyExtension interface
// This class is implemented by AutoCAD and available through
// GET_OPMEXTENSION_CREATE_PROTOCOL. You can add property classes 
// by calling GET_OPMPROPERTY_MANAGER for a particular AcRxClass 
// to get the property manager for that class. 
// You can also enumerate the dynamic properties which have
// been added to that class as well as its base class(es) via 
// GetPropertyCount and GetPropertyClassArray
//--------------------------
class OPMPropertyExtensionFactory: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(OPMPropertyExtensionFactory);
    virtual ~OPMPropertyExtensionFactory(){}

    //Retrieves the OPMPropertyExtension for the specified class, if the
    //extension has not been added before, it creates it. Note: the implementation
    //of this class manages the lifetime of OPMPropertyExtension, as such you don't 
    //need to delete them.
    virtual OPMPropertyExtension* CreateOPMObjectProtocol(AcRxClass* pClass, 
                                                             LONG lReserved = NULL) = 0;
    
    virtual OPMPropertyExtension* CreateOPMCommandProtocol(const char* pGlobalCommand, 
                                                             LONG lReserved = NULL) = 0;
    
    //gets the property manager for a particular command that been registered
    //with CreateOPMCommandProtocol. Returns TRUE if successful, FALSE if no
    //no manager for that command exists.
    virtual BOOL GetOPMManager(const char* pGlobalCommand, IPropertyManager** pManager) = 0;
    //Retrieves the total number of IDynamicProperty classes that have been
    //added to this class, including properties which have been added to 
    //base classes.
    virtual BOOL GetPropertyCount(AcRxClass* pClass, LONG* pPropCount) = 0;
    //Fills an array of CALLER ALLOCATED IDynamicPropety*s. The return value 
    //indicates the number of IDynamicProperty pointers actually written to 
    //the array. This *should* be the same as the value returned by 
    //GetPropertyCount
    virtual LONG GetPropertyClassArray(AcRxClass* pClass, 
                                       IDynamicProperty** pPropertyArray) = 0; 
};

#define GET_OPMEXTENSION_CREATE_PROTOCOL() \
OPMPropertyExtensionFactory::cast(AcDbDatabase::desc()->queryX(OPMPropertyExtensionFactory::desc()))

//This macro is the main entry point for getting the property manager for a
//particular class. Note: This returns an IPropertyManager for the class which 
//must be released after it's used
#define GET_OPMPROPERTY_MANAGER(pAcRxClass) \
GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMObjectProtocol(pAcRxClass)->GetPropertyManager() 

//This macro allocates an OPMPropertyExtension and returns its property
//manager for a given global command name. Use it to register commands
//which wish to provide dynamic properties for the OPM.
//Note: This returns an IPropertyManager for the class which 
//must be released after it's used
#define GET_OPM_COMMAND_PROPERTY_MANAGER(pCommandName) \
GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMCommandProtocol(pCommandName)->GetPropertyManager() 

typedef BOOL (*OPMDIALOGPROC)(void);

const int MAX_OPMSTRLEN = 256;

DEFINE_GUID(IID_IDynamicPropertyNotify, 0x8B384028, 0xACA8, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA8-11d1-A2B4-080009DC639A")
IDynamicPropertyNotify : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicPropertyNotify methods ***
    
    // Call this when your property changes
    STDMETHOD(OnChanged)(THIS_ /*[in]*/IDynamicProperty* pDynamicProperty) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of LONGs representing the objectIDs of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetCurrentSelectionSet)(THIS_ /*[out*/VARIANT* pSelection) PURE;
};

typedef IDynamicPropertyNotify FAR* LPDYNAMICPROPERTYNOTIFY;

//--------------------------
// IDynamicProperty interface
// Implement this class to create dynamic properties for the OPM
// it defines the base set of property attributes as well as
// the name/type/data tuples. 
//--------------------------
// {8B384028-ACA9-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicProperty, 0x8B384028, 0xACA9, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A")
IDynamicProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicProperty methods ***
    //Unique property ID
    STDMETHOD(GetGUID)(THIS_ /*[out]*/GUID* propGUID) PURE;
    // Property display name
    STDMETHOD(GetDisplayName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)(THIS_ /*[in]*/LONG objectID,
                                      /*[out]*/BOOL* pbEnabled) PURE;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)(THIS_ /*[out]*/BOOL* pbReadonly) PURE;
    // Get the property description string
    STDMETHOD(GetDescription)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    
    // *** Basic property value information ***
    // OPM will typically display these in an edit field
    
    // optional: meta data representing property type name, ex. ACAD_ANGLE
    STDMETHOD(GetCurrentValueName)(THIS_ /*[out]*/BSTR* pbstrName) PURE;
    // What is the property type, ex. VT_R8
    STDMETHOD(GetCurrentValueType)(THIS_ /*[out]*/VARTYPE* pVarType) PURE;
    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)(THIS_ /*in*/LONG objectID, 
                                      /*[out]*/VARIANT* pvarData) PURE;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)(THIS_ /*[in]*/LONG objectID, 
                                         /*[in]*/const VARIANT varData) PURE;

    //*** Notifications ***
    //OPM passes its implementation of IDynamicPropertyNotify, you
    //cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)(THIS_ /*[in]*/IDynamicPropertyNotify* pSink) PURE;
    STDMETHOD(Disconnect)(THIS_ ) PURE;
};

typedef IDynamicProperty FAR* LPDYNAMICPROPERTY;

const int DISPID_DYNAMIC = -23; //majic DISPID

//--------------------------
// IDynamicEnumProperty interface
// components can implement this interface to create an enumerated property
// which will usually be displayed as a drop-down list in the OPM
//--------------------------
// {8B384028-ACB1-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicEnumProperty, 0x8B384028, 0xACB1, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB1-11d1-A2B4-080009DC639A")
IDynamicEnumProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicEnumProperty methods ***    
    // *** Extended property value infomation ***
    // - for properties types which are enums or finite valued but dynamic
    // OPM will typically display these in a dropdown list
    
    // total number of values this property can have, or currently has
    STDMETHOD(GetNumPropertyValues)(THIS_ /*[out]*/LONG* numValues) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueName)(THIS_ /*in*/LONG index, 
                                   /*[out]*/BSTR* valueName) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueData)(THIS_ /*in*/LONG index, 
                                   /*[out]*/VARIANT* valueName) PURE;
};

typedef IDynamicEnumProperty FAR* LPDYNAMICENUMPROPERTY;

//--------------------------
// IDynamicDialogProperty interface
// components can implement this interface to support ellipsis
// button properties
//--------------------------
// {8B384028-ACB2-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicDialogProperty, 0x8B384028, 0xACB2, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB2-11d1-A2B4-080009DC639A")
IDynamicDialogProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // If implemented, OPM will call the function passed back here
    STDMETHOD(GetCustomDialogProc)(THIS_ /*[out]*/OPMDIALOGPROC* pDialogProc) PURE;
    // Or, pass us the name of the VBA macro to run to edit this property
    STDMETHOD(GetMacroName)(THIS_ /*[out]*/BSTR* bstrName) PURE;

};

typedef IDynamicDialogProperty FAR* LPDYNAMICDIALOGPROPERTY;

//--------------------------
// IPropertyManager interface
// This is the main property manager class. Use this to add your
// property classes for a given type of entity. You can get this interface
// using GET_AUTOMATION_PROTOCOL(pEnt)->GetPropertyManager().
//--------------------------
// {8B384028-ACA9-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IPropertyManager, 0x8B384028, 0xACB0, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A")
IPropertyManager : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IPropertyManager methods ***
    STDMETHOD(AddProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(RemoveProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(GetDynamicProperty)(THIS_ /*[in]*/LONG index,
                                     /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyByName)(THIS_ /*[in]*/BSTR propName,
                                           /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyCount)(THIS_ /*[out]*/LONG* count) PURE;
    //For COM Wrappers to generate dynamic property typeinfo
    STDMETHOD(GetDynamicClassInfo)(THIS_ /*[in]*/IUnknown* pObj,
                                        /*[out]*/ITypeInfo** pptiDynamic,
                                        /*[out]*/DWORD* dwCookie) PURE;
};

typedef IPropertyManager FAR* LPPROPERTYMANAGER;


#endif //_DYNPROPS_H