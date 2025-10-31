//
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
//
// DESCRIPTION:
//
// The AcDbFcf class represents a geometric tolerance as defined by
// ANSI Y14.5

#ifndef DBFCF_H
#define DBFCF_H

#include "dbmain.h"

#pragma pack(push, 8)

class AcDbFcf: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFcf);
                              AcDbFcf();
                              AcDbFcf(const ACHAR *, const AcGePoint3d&,
                              const AcGeVector3d&, const AcGeVector3d&);
    virtual ~AcDbFcf();

    // Geometric or visual properties.
    
    enum whichLine {kAll = -1};
    virtual void              setText          (const ACHAR *);
    virtual ACHAR *           text             (const int lineNo = kAll) const;
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

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;

};

#pragma pack(pop)

#endif
