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
#if !defined(_INTERMEDIARY_H)
#define _INTERMEDIARY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "drawable.h"
#include "gemat3d.h"

class Intermediary : public AcGiDrawable
{
    AcGsNode* m_pNode;
	AcGeMatrix3d m_mat;
public:
    
    AcDbObjectId m_idEntity;
    void setTransform(const AcGeMatrix3d& mat)
    {
        m_mat = mat;
    }
	virtual Adesk::UInt32   setAttributes   (AcGiDrawableTraits * traits)
    {
        return kDrawableIsCompoundObject;
    }
    virtual Adesk::Boolean  worldDraw       (AcGiWorldDraw * wd)
    {
        wd->geometry().pushModelTransform(m_mat);
        AcDbEntity* pE;
        if (acdbOpenObject(pE,m_idEntity,AcDb::kForRead)==Acad::eOk)
        {
            wd->geometry().draw(pE);
			pE->close();
        }
        wd->geometry().popModelTransform();
        return Adesk::kTrue;
    }
    virtual void            viewportDraw    (AcGiViewportDraw * vd)
    {
        return;
    }
    virtual Adesk::Boolean  isPersistent    (void) const
    { 
        return Adesk::kFalse;
    };                 
    virtual AcDbObjectId    id              (void) const
    {
        return AcDbObjectId::kNull;
    }
    virtual void            setGsNode       (AcGsNode * gsnode)
    {
        m_pNode = gsnode;
    }
    virtual AcGsNode*       gsNode          (void) const
    {
        return m_pNode;
    }
};

#endif