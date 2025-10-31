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

//-----------------------------------------------------------------------------
//----- AsdkTransientEntity.h : Declaration of the AsdkTransientEntity
//-----------------------------------------------------------------------------
#pragma once

#ifdef ASDKTRANSIENTGRAPHICS_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"

class AsdkTransientEntity : public AcGiDrawable
{
public:
    AsdkTransientEntity();
    virtual ~AsdkTransientEntity(void);

    // For default attributes
    virtual Adesk::UInt32   setAttributes   (AcGiDrawableTraits * traits);

    // For geometry shared between multiple viewports
    virtual Adesk::Boolean  worldDraw       (AcGiWorldDraw * wd);

    // For viewport-specific geometry
    virtual void            viewportDraw    (AcGiViewportDraw * vd);

    // Persistent/transient
    virtual Adesk::Boolean  isPersistent    (void) const;
    virtual AcDbObjectId    id              (void) const;

    // Graphics cache
    virtual void            setGsNode       (AcGsNode * gsnode);
    virtual AcGsNode*       gsNode          (void) const;

	void setPriviewEntityId(const AcDbObjectId &id);
	AcDbObjectId getPriviewEntityId();

	void setTooltipTextStyle(const AcDbObjectId &id);
	AcDbObjectId getTooltipTextStyle();

	void setCurrentMousePoint(const AcGePoint3d &point);
	AcGePoint3d getCurrentMousePoint();
	

	void setViewportsForTransientGraphics(AcArray<int> viewportNumbers);
	void getViewportsForTransientGraphics(AcArray<int> &viewportNumbers);

	double findHeightOfText(const AcGeMatrix3d &mat);
protected:
    AcGsNode *mpGsNode;

	AcDbObjectId m_entityObjectId;
	AcGePoint3d m_currentMousePoint;
	AcArray<int> m_viewportNumbers;

	AcDbMText *m_pTooltiptext;
	AcDbObjectId m_tooltipTextStyle;


};