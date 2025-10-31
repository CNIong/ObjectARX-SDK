#ifndef DBFCF_H
#define DBFCF_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
// The AcDbFcf class represents a geometric tolerance as defined by
// ANSI Y14.5

#include "dbmain.h"

#pragma pack(push, 8)

class AcDbFcf: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFcf);
                              AcDbFcf();
                              AcDbFcf(const char*, const AcGePoint3d&,
                              const AcGeVector3d&, const AcGeVector3d&);
    virtual ~AcDbFcf();

    // Required for AcDbEntity protocol.
    //
    virtual Acad::ErrorStatus getGripPoints   (AcGePoint3dArray&,
                                               AcDbIntArray&,
                                               AcDbIntArray&) const;
    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray&,
	                                           const AcGeVector3d&);
    virtual void              list            () const;

    // Geometric or visual properties.
    
    enum whichLine {kAll = -1};
    virtual void              setText          (const char*);
    virtual char*             text             (const int lineNo = kAll) const;
    virtual void              setLocation      (const AcGePoint3d&);
    virtual AcGePoint3d       location         () const;
    virtual void              setOrientation   (const AcGeVector3d& norm,
                                                const AcGeVector3d& dir);
    virtual AcGeVector3d normal()    const;
    virtual AcGeVector3d direction() const;
    
    virtual void getBoundingPoints(AcGePoint3dArray&) const;
    virtual void getBoundingPline(AcGePoint3dArray&)  const;
    
    virtual void              setDimensionStyle(AcDbHardPointerId);
    virtual AcDbHardPointerId dimensionStyle() const;
    
    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& pRecord) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* pNewData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newDataId);

    virtual void        setDimVars();

    // Dimension variable get methods in alphabetic order:
    //
    AcCmColor      dimclrd () const;
    AcCmColor      dimclrt () const;
    double         dimgap  () const;
    double         dimscale() const;
    AcDbObjectId   dimtxsty() const;
    double         dimtxt  () const;

    // Dimension variable set methods in alphabetic order:
    //
    Acad::ErrorStatus setDimclrd (AcCmColor&     val);
    Acad::ErrorStatus setDimclrt (AcCmColor&     val);
    Acad::ErrorStatus setDimgap  (double         val);
    Acad::ErrorStatus setDimscale(double         val);
    Acad::ErrorStatus setDimtxsty(AcDbObjectId   val);
    Acad::ErrorStatus setDimtxt  (double         val);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
