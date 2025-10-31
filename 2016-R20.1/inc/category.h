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
//-------------------------------------------------------------------------
//  ICategorizeProperties interface
//    components can implement this interface to categorize an
//    object's properties.
//-------------------------------------------------------------------------
#ifndef OPM_CATEGORY_H
#define OPM_CATEGORY_H

// category ID: negative values are 'standard' categories,  positive are control-specific
#define PROPCAT_Nil -1
#define PROPCAT_Misc -2
#define PROPCAT_Font -3
#define PROPCAT_Position -4
#define PROPCAT_Appearance -5
#define PROPCAT_Behavior -6
#define PROPCAT_Data -7
#define PROPCAT_List -8
#define PROPCAT_Text -9
#define PROPCAT_Scale -10
#define PROPCAT_DDE -11
#define PROPCAT_General -12
#define PROPCAT_Mass -13
#define PROPCAT_Pattern -14
#define PROPCAT_DataPoints -15
#define PROPCAT_Mesh -16
#define PROPCAT_ImageAdjust -17
#define PROPCAT_ControlPoints -18
#define PROPCAT_PrimaryUnits -19
#define PROPCAT_AltUnits -20
#define PROPCAT_Fit -21
#define PROPCAT_LinesArrows -22
#define PROPCAT_Tolerances -23
#define PROPCAT_Table     -24
#define PROPCAT_Geometry -25
#define PROPCAT_Section -26
#define PROPCAT_UnderlayAdjust -27
#define PROPCAT_Solid_History -28
#define PROPCAT_Fillet -29
#define PROPCAT_Chamfer -30
#define PROPCAT_3DVisualization -31
#define PROPCAT_Table_Breaks -32
#define PROPCAT_SURFACE_ASSOCIATIVITY -33
#define PROPCAT_SURFACE_TRIM -34
#define PROPCAT_ViewDefinition -35
#define PROPCAT_Annotation -36
#define PROPCAT_ReferenceData -37
#define PROPCAT_Representation -38
#define PROPCAT_PointcloudAdjust -39
#define PROPCAT_GeomapImageAdjust -40

#ifndef _ADESK_MAC_
// {4D07FC10-F931-11ce-B001-00AA006884E5}
DEFINE_GUID(IID_ICategorizeProperties, 0x4d07fc10, 0xf931, 0x11ce, 0xb0, 0x1, 0x0, 0xaa, 0x0, 0x68, 0x84, 0xe5);

typedef int PROPCAT;

#undef  INTERFACE
#define INTERFACE  ICategorizeProperties
interface DECLSPEC_UUID("4D07FC10-F931-11ce-B001-00AA006884E5") ICategorizeProperties : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** ICategorizeProperties ***
    //Provide a category ID for the property, provide your own or see standards
    STDMETHOD(MapPropertyToCategory)(THIS_ 
                                     /* [in]  */ DISPID dispid,
                                     /* [out] */ PROPCAT* ppropcat) PURE;
    // Get the name for the category ID
    STDMETHOD(GetCategoryName)(THIS_
                               /* [in]  */ PROPCAT propcat, 
                               /* [in]  */ LCID lcid,
                               /* [out] */ BSTR* pbstrName) PURE;
};

typedef ICategorizeProperties FAR* LPCATEGORIZEPROPERTIES;
#endif // _ADESK_MAC_

#endif

