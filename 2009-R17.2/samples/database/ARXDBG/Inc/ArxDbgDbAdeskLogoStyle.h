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
