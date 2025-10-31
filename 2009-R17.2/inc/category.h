//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 2001-2007 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
//-------------------------------------------------------------------------
//  ICategorizeProperties interface
//    components can implement this interface to categorize an
//    object's properties.
//-------------------------------------------------------------------------
#ifndef OPM_CATEGORY_H
#define OPM_CATEGORY_H
// {4D07FC10-F931-11ce-B001-00AA006884E5}
DEFINE_GUID(IID_ICategorizeProperties, 0x4d07fc10, 0xf931, 0x11ce, 0xb0, 0x1, 0x0, 0xaa, 0x0, 0x68, 0x84, 0xe5);

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

#endif
