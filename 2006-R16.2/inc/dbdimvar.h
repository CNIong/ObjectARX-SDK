#ifndef DBDIMVAR_H
#define DBDIMVAR_H
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
// The api for dimensioning variables shared by 
//  AcDbDatabase, 
//  AcDbDimstyleTableRecord, and 
//  AcDbDimension
    
    //  -------------------------  Dimension Style get methods
    //
    virtual int              dimadec  () const;  // new to R15
    virtual bool             dimalt   () const;
    virtual int              dimaltd  () const;
    virtual double           dimaltf  () const;
    virtual double           dimaltrnd() const;  // new to R15
    virtual int              dimalttd () const;
    virtual int              dimalttz () const;
    virtual int              dimaltu  () const;
    virtual int              dimaltz  () const;
    virtual const char*      dimapost () const;
    virtual double           dimasz   () const;
    virtual int              dimatfit () const;  // new to R15
    virtual int              dimaunit () const;
    virtual int              dimazin  () const;  // new to R15
    virtual AcDbObjectId     dimblk   () const;
    virtual AcDbObjectId     dimblk1  () const;
    virtual AcDbObjectId     dimblk2  () const;
    virtual double           dimcen   () const;
    virtual AcCmColor        dimclrd  () const;
    virtual AcCmColor        dimclre  () const;
    virtual AcCmColor        dimclrt  () const;
    virtual int              dimdec   () const;
    virtual double           dimdle   () const;
    virtual double           dimdli   () const;
    virtual char             dimdsep  () const;  // new to R15
    virtual double           dimexe   () const;
    virtual double           dimexo   () const;
    virtual int              dimfrac  () const;  // new to R15
    virtual double           dimgap   () const;
    virtual int              dimjust  () const;
    virtual AcDbObjectId     dimldrblk() const;  // new to R15
    virtual double           dimlfac  () const;
    virtual bool             dimlim   () const;
    virtual int              dimlunit () const;  // new to R15
    virtual AcDb::LineWeight dimlwd   () const;  // new to R15
    virtual AcDb::LineWeight dimlwe   () const;  // new to R15
    virtual const char*      dimpost  () const;
    virtual double           dimrnd   () const;
    virtual bool             dimsah   () const;
    virtual double           dimscale () const;
    virtual bool             dimsd1   () const;
    virtual bool             dimsd2   () const;
    virtual bool             dimse1   () const;
    virtual bool             dimse2   () const;
    virtual bool             dimsoxd  () const;
    virtual int              dimtad   () const;
    virtual int              dimtdec  () const;
    virtual double           dimtfac  () const;
    virtual bool             dimtih   () const;
    virtual bool             dimtix   () const;
    virtual double           dimtm    () const;
    virtual int              dimtmove () const;  // new to R15
    virtual bool             dimtofl  () const;
    virtual bool             dimtoh   () const;
    virtual bool             dimtol   () const;
    virtual int              dimtolj  () const;
    virtual double           dimtp    () const;
    virtual double           dimtsz   () const;
    virtual double           dimtvp   () const;
    virtual AcDbObjectId     dimtxsty () const;
    virtual double           dimtxt   () const;
    virtual int              dimtzin  () const;
    virtual bool             dimupt   () const;
    virtual int              dimzin   () const;

    //  -------------------------  Dimension Style set methods
    //
    virtual Acad::ErrorStatus setDimadec  (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimalt   (bool             v);
    virtual Acad::ErrorStatus setDimaltd  (int              v);
    virtual Acad::ErrorStatus setDimaltf  (double           v);
    virtual Acad::ErrorStatus setDimaltrnd(double           v);  // new to R15
    virtual Acad::ErrorStatus setDimalttd (int              v);
    virtual Acad::ErrorStatus setDimalttz (int              v);
    virtual Acad::ErrorStatus setDimaltu  (int              v);
    virtual Acad::ErrorStatus setDimaltz  (int              v);
    virtual Acad::ErrorStatus setDimapost (const char*      v);
    virtual Acad::ErrorStatus setDimasz   (double           v);
    virtual Acad::ErrorStatus setDimatfit (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimaunit (int              v);
    virtual Acad::ErrorStatus setDimazin  (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimblk   (AcDbObjectId     v);  // new to R15
    virtual Acad::ErrorStatus setDimblk1  (AcDbObjectId     v);  // new to R15
    virtual Acad::ErrorStatus setDimblk2  (AcDbObjectId     v);  // new to R15
    virtual Acad::ErrorStatus setDimcen   (double           v);
    virtual Acad::ErrorStatus setDimclrd  (const AcCmColor& v);
    virtual Acad::ErrorStatus setDimclre  (const AcCmColor& v);
    virtual Acad::ErrorStatus setDimclrt  (const AcCmColor& v);
    virtual Acad::ErrorStatus setDimdec   (int              v);
    virtual Acad::ErrorStatus setDimdle   (double           v);
    virtual Acad::ErrorStatus setDimdli   (double           v);
    virtual Acad::ErrorStatus setDimdsep  (char             v);  // new to R15
    virtual Acad::ErrorStatus setDimexe   (double           v);
    virtual Acad::ErrorStatus setDimexo   (double           v);
    virtual Acad::ErrorStatus setDimfrac  (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimgap   (double           v);
    virtual Acad::ErrorStatus setDimjust  (int              v);
    virtual Acad::ErrorStatus setDimldrblk(AcDbObjectId     v);  // new to R15
    virtual Acad::ErrorStatus setDimlfac  (double           v);
    virtual Acad::ErrorStatus setDimlim   (bool             v);
    virtual Acad::ErrorStatus setDimlunit (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimlwd   (AcDb::LineWeight v);  // new to R15
    virtual Acad::ErrorStatus setDimlwe   (AcDb::LineWeight v);  // new to R15
    virtual Acad::ErrorStatus setDimpost  (const char*      v);
    virtual Acad::ErrorStatus setDimrnd   (double           v);
    virtual Acad::ErrorStatus setDimsah   (bool             v);
    virtual Acad::ErrorStatus setDimscale (double           v);
    virtual Acad::ErrorStatus setDimsd1   (bool             v);
    virtual Acad::ErrorStatus setDimsd2   (bool             v);
    virtual Acad::ErrorStatus setDimse1   (bool             v);
    virtual Acad::ErrorStatus setDimse2   (bool             v);
    virtual Acad::ErrorStatus setDimsoxd  (bool             v);
    virtual Acad::ErrorStatus setDimtad   (int              v);
    virtual Acad::ErrorStatus setDimtdec  (int              v);
    virtual Acad::ErrorStatus setDimtfac  (double           v);
    virtual Acad::ErrorStatus setDimtih   (bool             v);
    virtual Acad::ErrorStatus setDimtix   (bool             v);
    virtual Acad::ErrorStatus setDimtm    (double           v);
    virtual Acad::ErrorStatus setDimtmove (int              v);  // new to R15
    virtual Acad::ErrorStatus setDimtofl  (bool             v);
    virtual Acad::ErrorStatus setDimtoh   (bool             v);
    virtual Acad::ErrorStatus setDimtol   (bool             v);
    virtual Acad::ErrorStatus setDimtolj  (int              v);
    virtual Acad::ErrorStatus setDimtp    (double           v);
    virtual Acad::ErrorStatus setDimtsz   (double           v);
    virtual Acad::ErrorStatus setDimtvp   (double           v);
    virtual Acad::ErrorStatus setDimtxsty (AcDbObjectId     v);
    virtual Acad::ErrorStatus setDimtxt   (double           v);
    virtual Acad::ErrorStatus setDimtzin  (int              v);
    virtual Acad::ErrorStatus setDimupt   (bool             v);
    virtual Acad::ErrorStatus setDimzin   (int              v);

    virtual Acad::ErrorStatus setDimblk   (const char*      v);
    virtual Acad::ErrorStatus setDimblk1  (const char*      v);
    virtual Acad::ErrorStatus setDimblk2  (const char*      v);
    virtual Acad::ErrorStatus setDimldrblk(const char*      v);  // new to R15

#endif      // ifndef DBDIMVAR_H

