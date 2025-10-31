//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXDBGDBADESKLOGOSTYLE_H
#define ARXDBGDBADESKLOGOSTYLE_H

#include "ArxDbgDbDictRecord.h"

/****************************************************************************
**
**  CLASS ArxDbgDbAdeskLogoStyle:
**
**  **jma
**
*************************************/

class ArxDbgDbAdeskLogoStyle : public ArxDbgDbDictRecord {

public:
                ArxDbgDbAdeskLogoStyle();
    virtual     ~ArxDbgDbAdeskLogoStyle();

    ACRX_DECLARE_MEMBERS(ArxDbgDbAdeskLogoStyle);

        // access to data members
    bool			    isSolidFill() const;
    Acad::ErrorStatus   setSolidFill(bool doIt);

    LPCTSTR             label() const;
    Acad::ErrorStatus   setLabel(LPCTSTR newLabel);

    AcDbObjectId        textStyleId() const;
    Acad::ErrorStatus   setTextStyleId(const AcDbObjectId& styleId);

    virtual void        subSetDatabaseDefaults(AcDbDatabase* pDb);

        // overridden from AcDbObject
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

private:
        // data members
    bool                m_solidFill;
    CString             m_label;
    AcDbHardPointerId   m_textStyleId;

    static Adesk::Int16 m_version;
	static LPCTSTR		m_dictName;

        // Dxf Codes
    enum {
        kDxfLabel       = 1,
        kDxfSolidFill   = 70,
        kDxfTextStyle   = 340,
    };

public:
	static LPCTSTR		dictName()	{ return m_dictName; }
	static AcDbObjectId	getStandardStyle(AcDbDatabase* db, bool makeIfNotThere);

};


#endif    // ARXDBGDBADESKLOGOSTYLE_H
