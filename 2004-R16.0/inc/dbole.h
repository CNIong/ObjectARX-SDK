#ifndef AD_DBOLE_H
#define AD_DBOLE_H
//
// (C) Copyright 1994-2002 by Autodesk, Inc.
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
// DESCRIPTION:  Class header for AcDbOleFrame & AcDbOle2Frame, 
//               OLE 2 Container (Client) Feature for Windows/NT
//
//    AcDbEntity
//        AcDbOleFrame
//            AcDbOle2Frame  
//
//    AcDbOleFrame supports 1) non-OLE platform and 2) pre-R13 C4 OLE 1
//    storage and retrieval only.  It doesn't support OLE object
//    display or activation.  It stores
//    binary data in lists that can be scanned later using the DbId.
//    AcDbOle2Frame supports OLE 2 objects.  For non-OLE platforms,
//    the virtual methods are not overridden, so the storage methods
//    in AcDbOleFrame are used instead.  

#include "dbmain.h"
#include "dbframe.h"
#include "gepnt3d.h"

#pragma pack (push, 8)

class CRectangle3d
{
public:
    AcGePoint3d upLeft;
    AcGePoint3d upRight;
    AcGePoint3d lowLeft;
    AcGePoint3d lowRight;
};
class CRect;

class AcDbOleFrame: public AcDbFrame
{
public:
    ACDB_DECLARE_MEMBERS(AcDbOleFrame);

    AcDbOleFrame();
    virtual ~AcDbOleFrame();

    // --- AcDbObject Protocol

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    virtual void viewportDraw(AcGiViewportDraw* mode);
    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

    // OLE Specific Methods
    virtual void* getOleObject(void) const;
    virtual void setOleObject(const void *pItem);

};
 

class AcDbOle2Frame: public AcDbOleFrame
{
public:
    ACDB_DECLARE_MEMBERS(AcDbOle2Frame);
    AcDbOle2Frame();
    virtual ~AcDbOle2Frame();

    // --- AcDbObject Protocol

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    virtual void viewportDraw(AcGiViewportDraw* mode);
    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;
    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    // OLE Specific Methods
    // Get pointer to MFC COleClientItem class.
    //
    virtual void* getOleObject(void) const;
    virtual void setOleObject(const void *pItem);

    // Upper left corner of OLE object, world coordinates
    //
    virtual void getLocation(AcGePoint3d& point3d) const;

    // Get world coords of the four corners of OLE object.
    //
    virtual void position(CRectangle3d& rect3d) const;
    
    // Set world coords of the four corners of OLE object.
    //
    virtual void setPosition(const CRectangle3d& rect3d);

    // Get GDI device coords of the four corners of OLE object
    // for the current viewport.
    //
    virtual void position(RECT& rect) const;

    // Set coords according to the GDI device coords of the four corners of OLE object
    // for the current viewport.
    //
    virtual void setPosition(const RECT& rect);

    // Description, such as "Paintbrush Bitmap".
    // See MFC COleClientItem::GetUserType().
    //
    virtual void getUserType(char* pszName, int nNameSize) const;

    // Linked, embedded, or static.  See MFC COleClientItem::GetType().
    //   1 OT_LINK       The OLE item is a link.
	//   2 OT_EMBEDDED   The OLE item is embedded.
	//   3 OT_STATIC     The OLE item is static, that is, it contains only 
    //                   presentation data, not native data, and thus cannot be edited.
    //
    virtual int getType(void) const;

    // If this is a linked object, get the file and item name
    // to which it is linked.
    // Example:  C:\My Documents\link.xls!Sheet1!R5C3:R8C3
    //
    virtual Adesk::Boolean getLinkName(char* pszName, int nNameSize) const;

    // Get path name of linked object, without the item name.
    // Example:
    //   GetLinkName: C:\My Documents\link.xls!Sheet1!R5C3:R8C3
    //   GetLinkPath: C:\My Documents\link.xls
    //
    virtual Adesk::Boolean getLinkPath(char* pszPath, int nPathSize) const;

    virtual Adesk::UInt8 outputQuality() const;
    virtual void setOutputQuality(Adesk::UInt8);

};

#pragma pack (pop)

#endif  // AD_DBOLE_H_
