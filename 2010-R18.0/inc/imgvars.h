//
//  (C) Copyright 1996-2007 by Autodesk, Inc.
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
#ifndef __IMGVARS_H
#define __IMGVARS_H

#include "dbmain.h"
#include "imgdef.h"

#pragma pack (push, 8)

// Opaque types
//
class AcDbImpRasterVariables;

// Silence compiler
//
#pragma warning( disable : 4275 ) 

#ifdef ISMDLLACCESS
#undef ISMDLLACCESS
#endif
#ifdef ISMDLLACCESSDATA
#undef ISMDLLACCESSDATA
#endif
#ifdef ISM_OBJ // For DwgUnplugged ISMobj.arx:
// Classes to be exported have to have ISMDLLACCESS definition in its header.
// Example: class ISMDLLACCESS AcDbImpRasterImageDef
#define ISMDLLACCESS __declspec(dllexport)
#define ISMDLLACCESSDATA
#else
#define ISMDLLACCESS 
#define ISMDLLACCESSDATA __declspec(dllimport)
#endif

class ISMDLLACCESS AcDbRasterVariables : public AcDbObject
{
public:

    static ClassVersion        classVersion();

    ACRX_DECLARE_MEMBERS(AcDbRasterVariables);

    // Enums, for the allowable variable values
    enum FrameSettings {
        kImageFrameInvalid  = -1,
        kImageFrameOff      =  0,
        kImageFrameAbove    =  1,
        kImageFrameBelow    =  2,
        kImageFrameOnNoPlot =  3
    };
    enum ImageQuality {
        kImageQualityInvalid = -1,
        kImageQualityDraft = 0,
        kImageQualityHigh  = 1
    };

    static AcDbRasterVariables* create(); 
    AcDbRasterVariables();
    virtual     ~AcDbRasterVariables();

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

    virtual FrameSettings       imageFrame() const;
    virtual Acad::ErrorStatus   setImageFrame( FrameSettings value );

    virtual ImageQuality        imageQuality() const;
    virtual Acad::ErrorStatus   setImageQuality( ImageQuality value );

    virtual AcDbRasterImageDef::Units userScale() const;
    virtual Acad::ErrorStatus   setUserScale(
                                    AcDbRasterImageDef::Units units );

    static AcDbRasterVariables* openRasterVariables(
                                    AcDb::OpenMode mode,
                                    AcDbDatabase* pDatabase = 0
                                    );

private:

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them
    // private in order to prevent usage of them.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](size_t nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

    // Data members
    //
    AcDbImpRasterVariables*     mpImp;
    static ClassVersion         mVersion;
};

inline ClassVersion
AcDbRasterVariables::classVersion()
{   return mVersion; }

#pragma warning( default : 4275 ) 


#pragma pack (pop)
#endif  // __IMGVARS_H
