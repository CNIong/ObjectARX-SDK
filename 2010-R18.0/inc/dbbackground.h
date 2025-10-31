
#pragma once
//
// (C) Copyright 2005-2009 by Autodesk, Inc. 
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

#include "dbmain.h"
#include "acgienvironment.h"
#include "dbcolor.h"
#include "AdAChar.h"

#pragma pack(push, 8)

// The following is part of the code used to export a API
// and/or use the exported API.
//
#pragma warning( disable: 4275 4251 )

#ifdef SCENEDLLIMPEXP
#undef SCENEDLLIMPEXP
#endif
#ifdef SCENEOE
#define SCENEDLLIMPEXP __declspec( dllexport )
#else
// Note: we don't use __declspec(dllimport) here, because of the
// "local vtable" problem with msvc.  If you use __declspec(dllimport),
// then, when a client dll does a new on the class, the object's
// vtable pointer points to a vtable allocated in that client
// dll.  If the client dll then passes the object to another dll,
// and the client dll is then unloaded, the vtable becomes invalid
// and any virtual calls on the object will access invalid memory.
//
// By not using __declspec(dllimport), we guarantee that the
// vtable is allocated in the server dll during the ctor and the
// client dll does not overwrite the vtable pointer after calling
// the ctor.  And, since we expect the server dll to remain in
// memory indefinitely, there is no problem with vtables unexpectedly
// going away.
// 
#define SCENEDLLIMPEXP //__declspec( dllimport )
#endif

const ACHAR ACDB_BACKGROUND_DICTIONARY[]  = /*MSG0*/ACRX_T("ACAD_BACKGROUND");

Acad::ErrorStatus SCENEDLLIMPEXP getBackgroundDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                             AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP getBackgroundDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                             AcDb::OpenMode mode);

class AcDbImpBackground;

class SCENEDLLIMPEXP AcDbBackground : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbBackground);
    virtual ~AcDbBackground();
    virtual AcGiDrawable*  drawable ();

protected:
    AcDbBackground(AcDbImpBackground* pImp);
    AcDbImpBackground* imp() const; 

private:
    friend class AcDbImpBackground;
    AcDbImpBackground* mpImp;
};

class SCENEDLLIMPEXP AcDbSolidBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSolidBackground);
    AcDbSolidBackground();
    virtual ~AcDbSolidBackground();

    // Solid Background Property
    void            setColorSolid   (const AcCmEntityColor & color);
    AcCmEntityColor colorSolid      (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other);

    virtual AcGiDrawable::DrawableType    drawableType() const;

protected:
    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpSolidBackground;
};

class SCENEDLLIMPEXP AcDbGradientBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGradientBackground);
    AcDbGradientBackground();
    virtual ~AcDbGradientBackground();

    // Gradient Background Properties
    void            setColorTop    (const AcCmEntityColor & color);
    AcCmEntityColor colorTop       (void) const;
    void            setColorMiddle (const AcCmEntityColor & color);
    AcCmEntityColor colorMiddle    (void) const;
    void            setColorBottom (const AcCmEntityColor & color);
    AcCmEntityColor colorBottom    (void) const;
    void            setHorizon     (double horizon);
    double          horizon        (void) const;
    void            setHeight      (double height);
    double          height         (void) const ;
    void            setRotation    (double rotation);
    double          rotation       (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other);

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpGradientBackground;
};

class SCENEDLLIMPEXP AcDbImageBackground : public AcDbBackground
{
public:

    ACRX_DECLARE_MEMBERS(AcDbImageBackground);
    AcDbImageBackground();
    virtual ~AcDbImageBackground();

    // Image Background Properties
    void            setImageFilename        (const ACHAR* filename);
    const ACHAR *   imageFilename           (void) const;
    void            setFitToScreen          (bool bFitToScreen);
    bool            fitToScreen             (void) const;
    void            setMaintainAspectRatio  (bool bMaintainAspectRatio);
    bool            maintainAspectRatio     (void) const;
    void            setUseTiling            (bool bUseTiling);
    bool            useTiling               (void) const;
    void            setXOffset              (double xOffset);
    double          xOffset                 (void) const;
    void            setYOffset              (double yOffset);
    double          yOffset                 (void) const;
    void            setXScale               (double xScale);
    double          xScale                  (void) const;
    void            setYScale               (double yScale);
    double          yScale                  (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other);

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpImageBackground;
};

class SCENEDLLIMPEXP AcDbGroundPlaneBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGroundPlaneBackground);
    AcDbGroundPlaneBackground();
    virtual ~AcDbGroundPlaneBackground();

    // GroundPlane Background Properties
    void            setColorSkyZenith       (const AcCmEntityColor & color);
    AcCmEntityColor colorSkyZenith          (void) const;
    void            setColorSkyHorizon      (const AcCmEntityColor & color);
    AcCmEntityColor colorSkyHorizon         (void) const;
    void            setColorUndergroundHorizon  (const AcCmEntityColor & color);
    AcCmEntityColor colorUndergroundHorizon     (void) const;
    void            setColorUndergroundAzimuth  (const AcCmEntityColor & color);
    AcCmEntityColor colorUndergroundAzimuth     (void) const;
    void            setColorGroundPlaneNear (const AcCmEntityColor & color);
    AcCmEntityColor colorGroundPlaneNear    (void) const;
    void            setColorGroundPlaneFar  (const AcCmEntityColor & color);
    AcCmEntityColor colorGroundPlaneFar     (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other);

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpGroundPlaneBackground;
};

class SCENEDLLIMPEXP AcDbSkyBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSkyBackground);
    AcDbSkyBackground();
    virtual ~AcDbSkyBackground();

    // Sky Background Property
    Acad::ErrorStatus         setSunId     (AcDbObjectId sunId);
    AcDbObjectId              sunId        (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other);

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpSkyBackground;
};

#pragma pack (pop)
