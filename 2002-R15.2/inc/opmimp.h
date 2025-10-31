//
// (C) Copyright 1997-1999 by Autodesk, Inc.
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
#ifndef _OPMIMP_H
#define _OPMIMP_H

#include <category.h>
#pragma pack (push, 8)

struct ACAD_OPMPROPMAP_ENTRY
{
    UINT nDescID;                  //Alternate property name
    DISPID dispid;                 //ID of the property
    PROPCAT  catid;                //categoryID
    UINT nCatNameID;               //category Name
    UINT nElementStrID;            //expanded property name list (for pts, ex.)
    UINT nPredefinedStrID;         //IPerPropertyBrowsing enumeration strings
    LPCSTR    predefinedValues;    //IPerPropertyBrowsing enumeration values
    unsigned short grouping;       //expanded property name grouping
    bool      editable;            //show property override
    const CLSID* pclsidOther;      //CLSID for Other.. combo item dlg (not used)
    const CLSID* pclsidPropPage;   //IPerPropertyBrowsing dialog CLSID
    const IID* piidDispatch;       //dispatch pointer for property
    LPCOLESTR szEllipsesTxt;       //IPerPropertyBrowsing display string
};

#define BEGIN_OPMPROP_MAP()                                 \
	static ACAD_OPMPROPMAP_ENTRY* GetOPMPropertyMap()               \
	{                                                               \
		static ACAD_OPMPROPMAP_ENTRY pPropMap[] =                   \
		{

// DescriptionID, dispID, catagoryID, catagoryNameID, elements string list ID (semi-colon separator), predefined strings ID (semi-colon separator), predefined values, grouping, editable property, other, proppage
#define OPMPROP_ENTRY(nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, other, clsid, ellipsesTxt)      \
		{nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, &other, &clsid, &IID_IDispatch, OLESTR(ellipsesTxt)},

#define OPMPROP_CAT_ENTRY(nDesID, dpid, ctid, ctNameID)      \
		{nDesID, dpid, ctid, ctNameID, 0, 0, "", 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_DESC_ENTRY(nDesID, dpid)      \
		{nDesID, dpid, -2, 0, 0, 0, "", 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PREDEFINED_ENTRY(nDesID, dpid, predefID, values, other)      \
		{nDesID, dpid, -2, 0, 0, predefID, values, 0, 1, &other, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_ELEMENT_ENTRY(dpid, ctid, ctNameID, elementsID, grouping)      \
		{0, dpid, ctid, ctNameID, elementsID, 0, "", grouping, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PAGE(nDesID, dpid, ctid, ctNameID, clsid)      \
		{nDesID, dpid, ctid, ctNameID, 0, 0, "", 0, 1, &IID_NULL, &clsid, &IID_IDispatch, OLESTR("")},

#define END_OPMPROP_MAP()                                           \
			{0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL, NULL, &IID_NULL, NULL}            \
		};                                                          \
		return pPropMap;                                            \
	}

#pragma pack (pop)
#include "opmdrvr.h"

#endif // _OPMIMP_H
