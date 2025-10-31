
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

//-----------------------------------------------------------------------------
//----- AcDbSun.h : Declaration of the AcDbSun class
//-----------------------------------------------------------------------------
// DESCRIPTION:
//
// This API extends AcDb to support creation of the Sun object

//  AcDbObject
//      AcDbSun


#pragma once

#include "dbmain.h"
#pragma warning( disable: 4275 4251 )

#ifdef SCENEOE
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

#include "AcGiLightTraits.h"
#include "rxboiler.h"
#include "dbLight.h"

//forward declaration for the imp class
class AcDbImpSun;


/// <summary>
/// Container for all properties relating to a sun object.
/// A sun exists as a hard-owned child of an AcDbViewportTableRecord
/// or an AcDbViewport object.  It is created when a sun-related operation 
/// is first performed (for example, changing a property on the Sun Properties
/// ESW or a sun-related parameter in the 3DUI dashboard).  It is set and
/// accessed by the methods setSun() and sunId() defined on both viewport classes.
/// The properties defined in this class correspond to fields on the Sun property
/// palette, but may also be set and queried by other clients.
/// </summary>
class LIGHTDLLIMPEXP AcDbSun : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSun);
private:
    static Adesk::UInt32 kCurrentVersionNumber;
public:
    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbSun();
    /// <summary>
    /// Destructor.
    /// </summary>
    ~AcDbSun();

    // AcGiDrawable methods
    virtual AcGiDrawable* drawable();
    virtual DrawableType  drawableType() const { return AcGiDrawable::kDistantLight; }
    virtual void          setGsNode(AcGsNode* gsnode);
    virtual AcGsNode*     gsNode() const;

    // AcDbObject methods
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler *pFiler) const;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler);

    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler *pFiler) const;

    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

    virtual Acad::ErrorStatus decomposeForSave(
            AcDb::AcDbDwgVersion ver,
            AcDbObject*& replaceObj, 
            AcDbObjectId& replaceId, 
            Adesk::Boolean& exchangeXData);

    /// <summary>
    /// Gets the Sun's on/off state.
    /// </summary>
    ///
    /// <returns>
    /// True if the Sun status is on.
    /// </returns>
    virtual bool isOn() const;

    /// <summary>
    /// Sets the Sun on/off status.
    /// </summary>
    ///
    /// <param name="value">
    /// If true, the Sun status is "turned on"; it adds light to the model.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setOn(bool value);

    /// <summary>
    /// Gets the Sun light intensity.
    /// </summary>
    ///
    /// <returns>
    /// The intensity of the Sun's light.
    /// </returns>
    virtual double intensity() const;

    /// <summary>
    /// Sets the Sun's light intensity.
    /// </summary>
    ///
    /// <param name="intensity">
    /// The intensity of the Sun light. A value of 0.0 effectively
    /// turns the Sun light off.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setIntensity(double intensity);

    /// <summary>
    /// Gets the color of the Sun's light.
    /// </summary>
    ///
    /// <returns>
    /// The color of the Sun's light.
    /// </returns>
    virtual const AcCmColor& sunColor() const;

    /// <summary>
    /// Sets the color of the Sun's light.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the emitted light from the Sun object.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setSunColor(const AcCmColor& color);

    /// <summary>
    /// Gets the shadow parameters: shadow type, map size, edge softness, and on/off state.
    /// </summary>
    ///
    /// <returns>
    /// A reference to a const AcGiShadowParameters object, containing shadow parameters
    /// such as shadow type, map size, edge softness, and on/off state.
    /// </returns>
    virtual const AcGiShadowParameters& shadowParameters() const;

    /// <summary>
    /// Sets the shadow parameters: shadow type, map size, edge softness, and on/off state.
    /// </summary>
    ///
    /// <param name="params">
    /// The shadow parameters contained in an instance of an AcGiShadowParameters object.
    /// </param>
    virtual void setShadowParameters(const AcGiShadowParameters& params);

    /// <summary>
    /// Sets the Date and Time for the Sun, which affects its position relative to the model.
    /// </summary>
    ///
    /// <param name="datetime">
    /// The date and time of the sun.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    ///
    /// <remarks>
    /// Other parameters that affect the position of the sun: latitude, longitude, 
    /// north direction, and time zone.
    /// </remarks>
    virtual Acad::ErrorStatus setDateTime(const AcDbDate& datetime);

    /// <summary>
    /// Gets the Date and Time for the Sun, two of the factors affecting the position 
    /// of the sun relative to the model.
    /// </summary>
    ///
    /// <returns>
    /// The date and the time of the sun.
    /// </returns>
    ///
    /// <remarks>
    /// Other parameters that affect the position of the sun: latitude, longitude, 
    /// north direction, and time zone.
    /// </remarks>
    virtual const AcDbDate& dateTime() const;

    /// <summary>
    /// Turns on and off Daylight Saving Time. This affects the interpretation 
    /// of the Sun Time parameter.
    /// </summary>
    ///
    /// <param name="value">
    /// True to turn on Daylight Saving time.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setDayLightSavingsOn(bool value);
    
    /// <summary>
    /// Gets the Daylight Saving Time on/off status.
    /// </summary>
    ///
    /// <returns>
    /// True if Daylight Saving Time is On.
    /// </returns>
    virtual bool isDayLightSavingsOn() const;
    
    /// <summary>
    /// For internal use only.
    /// </summary>
    virtual Acad::ErrorStatus setAzimuth(double azimuth);
    
    /// <summary>
    /// For internal use only.
    /// </summary>
    virtual double azimuth() const;
    
    /// <summary>
    /// For internal use only.
    /// </summary>
    virtual Acad::ErrorStatus setAltitude(double altitude);
    
    /// <summary>
    /// For internal use only.
    /// </summary>
    virtual double altitude() const;

    /// <summary>
    /// Gets the direction (vector) of the sun's light rays.
    /// </summary>
    ///
    /// <returns>
    /// The direction vector of sunlight, from the Sun to the model.
    /// </returns>
    virtual const AcGeVector3d& sunDirection() const;

    /// <summary>
    /// For internal use only.
    /// </summary>
    virtual void setSunDirection(const AcGeVector3d& sundir);

    /// <summary>
    /// Sets the sky parameters: render sky, multiplier, haze, horizon height,
    /// horizon blur, ground color, night color, aerial perspective on/off, 
    /// visibility
    /// </summary>
    ///
    /// <param name="params">
    /// Input sky parameters: render sky, multiplier, haze, horizon height,
    /// horizon blur, ground color, night color, aerial perspective on/off, 
    /// visibility
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the sky parameter 
    /// information could not be set, or if any of the values passed in are
    /// invalid.
    /// </returns>
    Acad::ErrorStatus setSkyParameters(const AcGiSkyParameters& params);
    
    /// <summary>
    /// Gets the sky parameters: render sky, multiplier, haze, horizon height,
    /// horizon blur, ground color, night color, aerial perspective on/off, 
    /// visibility
    /// </summary>
    ///
    /// <param name="params">
    /// Output sky parameters: render sky, multiplier, haze, horizon height,
    /// horizon blur, ground color, night color, aerial perspective on/off, 
    /// visibility
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the sky parameter 
    /// information could not be retrieved.
    /// </returns>
    Acad::ErrorStatus skyParameters(AcGiSkyParameters& params) const;
    
protected:
    // AcGiDrawable methods
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits);

private:
    AcDbImpSun * mpAcDbImpSun;
};
