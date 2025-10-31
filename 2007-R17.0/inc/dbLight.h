
//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
//----- AcDbLight.h : Declaration of the AcDbLight class
//-----------------------------------------------------------------------------
// DESCRIPTION:
//
// This API extends AcDb to support creation of the light objects (SpotLight, PointLight, and the DistantLight)

//   AcDbEntity
//		AcDbLight
//			AcDbPointLight
//			AcDbSpotLight
//			AcDbDistantLight


#pragma once
#include "dbmain.h"
#include "dbents.h"
#pragma warning( disable: 4275 4251 )
#ifdef SCENEOE
#define LIGHTDLLIMPEXP __declspec(dllexport)
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
#define LIGHTDLLIMPEXP
#endif

#include "dbgrip.h"
#include "AcGiLightTraits.h"
//-----------------------------------------------------------------------------

//forward declaration of the imp class
class AcDbImpLight;

/// <summary>
/// Container for all properties relating to a generic light.
/// A dictionary of these objects is resident in the database, in the named
/// object dictionary as ACAD_LIGHTS.  They are indexed by the name
/// of the setting objects.  In the user interface, the contents of this
/// dictionary correspond to user-defined light properties (displayed on a
/// property palette accessible by selection of the light using a variety of
/// methods.
/// </summary>
class LIGHTDLLIMPEXP AcDbLight : public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLight);
    
private:
    static Adesk::UInt32 kCurrentVersionNumber ;
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbLight ();
    /// <summary>
    /// Destructor.
    /// </summary>
    ~AcDbLight();

    virtual Acad::ErrorStatus subClose();

    //----- AcDbEntity protocols
    //- Dwg Filing protocol
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    virtual Acad::ErrorStatus getGripPoints (AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d &curViewDir, const int bitflags) const ;
    virtual Acad::ErrorStatus moveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) ;

    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const ;

    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);

    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus highlight(const AcDbFullSubentPath& subId, 
        const Adesk::Boolean highlightAll) const;

    virtual Acad::ErrorStatus unhighlight(const AcDbFullSubentPath& subId, 
        const Adesk::Boolean highlightAll) const;
    virtual void list() const;

    virtual Acad::ErrorStatus decomposeForSave(
            AcDb::AcDbDwgVersion ver,
            AcDbObject*& replaceObj, 
            AcDbObjectId& replaceId, 
            Adesk::Boolean& exchangeXData);

    //----- AcDbEntity protocols
    //- Graphics protocol
    virtual void viewportDraw (AcGiViewportDraw *mode) ;
    virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;
    virtual Adesk::UInt32  setAttributes(AcGiDrawableTraits* pTraits);
    virtual AcGiDrawable::DrawableType    drawableType() const;
    virtual bool castShadows() const;
    virtual void setCastShadows(bool newVal);
    virtual bool receiveShadows() const;
    virtual void setReceiveShadows(bool newVal);


	virtual Acad::ErrorStatus deepClone(AcDbObject* pOwner,AcDbObject*& pClonedObject,
										AcDbIdMapping& idMap,Adesk::Boolean isPrimary = true) const;

	virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, 
										AcDbIdMapping& idMap, Adesk::Boolean isPrimary /* = true */) const;

  
    ///<summary>
    ///Calculates the corner points (in WCS coordinates) of a box that  
    ///encloses the 3D extents of the light entity
    ///</summary>
    ///
    ///<param name="extents">
    /// a box enclosing the 3D extents of the entity
    ///</param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the extents are valid.
    /// </returns>
    virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;
    
    /// <summary>
    /// Gets the name of the Light object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the name of the light object.
    /// </returns>
    virtual const AcString& name() const;

    /// <summary>
    /// Sets the name of the light object.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the light object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the name is valid.
    /// </returns>
    virtual Acad::ErrorStatus setName(const AcString & name);

    /// <summary>
    /// Gets the type of Light object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the type of the light object. Possible values are: SpotLight, PointLight and DistantLight.
    /// </returns>
    virtual AcGiDrawable::DrawableType lightType() const;

    /// <summary>
    /// Sets the type of the light object.
    /// </summary>
    ///
    /// <param name="type">
    /// Light object type.  Possible choices are: SpotLight, PointLight and DistantLight.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the type is valid.
    /// </returns>
    virtual Acad::ErrorStatus setLightType(AcGiDrawable::DrawableType type);

    /// <summary>
    /// Gets the Light on/off state.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is on.
    /// </returns>
    virtual  bool isOn() const;

    /// <summary>
    /// Sets whether the Light is On/Off.
    /// </summary>
    ///
    /// <param name="value">
    /// If true, the light is on.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk.
    /// </returns>
    virtual Acad::ErrorStatus setOn(bool value);

    /// <summary>
    /// Gets the plottable state of the light.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is plottable.
    /// </returns>
    virtual bool isPlottable() const;

    /// <summary>
    /// Sets the plottable state of the light.
    /// </summary>
    ///
    /// <param name="plot">
    /// If true, the light is plottable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk.
    /// </returns>
    virtual Acad::ErrorStatus setIsPlottable(bool plot);

    /// <summary>
    /// Gets the emitted color of the light.
    /// </summary>
    ///
    /// <returns>
    /// The light color.
    /// </returns>	
    virtual const AcCmColor& lightColor() const;

    /// <summary>
    /// Sets the emitted light color.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the emitted light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the color is valid.
    /// </returns>
    virtual Acad::ErrorStatus setLightColor(const AcCmColor& color);
    
    
    /// <summary>
    /// Gets the light intensity.
    /// </summary>
    ///
    /// <returns>
    /// The light intensity.  A value of 0.0 indicates 
    /// that the light is off. 
    /// </returns>
    virtual double intensity() const;

    /// <summary>
    /// Sets the light intensity.
    /// </summary>
    /// <param name="intensity">
    /// The intensity of the light. A value of 0.0 
    /// turns the light off.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid intensity value is passed in.
    /// </returns>
    virtual Acad::ErrorStatus setIntensity(double intensity);
    

    /// <summary>
    /// Sets the shadow parameters: shadows on/off, shadow type, mapsize, softness
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if all values passed in are valid.
    /// </returns>
    virtual void setShadowParameters(const AcGiShadowParameters& params);


    /// <summary>
    /// Gets the shadow parameters:shadow type, mapsize, softness, on/off
    /// </summary>
    ///
    /// <returns>
    /// The shadow parameters:shadow type, mapsize, softness, on/off
    /// </returns>
    virtual const AcGiShadowParameters& shadowParameters() const;


    /// <summary>
    /// Sets the light attenuation:attenuation type, use limits, start limits, end limits
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the attenuation parameters are valid.
    /// </returns>
    virtual void setLightAttenuation(const AcGiLightAttenuation& params);

    /// <summary>
    /// Gets the light attenuation:attenuation type, use limits, start limits, end limits
    /// </summary>
    ///
    /// <returns>
    /// The light attenuation:attenuation type, use limits, start limits, end limits
    /// </returns>
    virtual const AcGiLightAttenuation& lightAttenuation() const;

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// Sets the position of the light source.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setPosition(const AcGePoint3d& pos);

    /// <summary>
    /// Gets the position of the light source, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// The light source position.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot and point light types only.
    /// </remarks>
    virtual const AcGePoint3d& position() const;
    
    /// <summary>
    /// Gets the position of the light target location, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// The light target position.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual const AcGePoint3d& targetLocation() const;

    /// <summary>
    /// Sets the position of the light target location, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual Acad::ErrorStatus setTargetLocation(const AcGePoint3d& newVal);
    /// <summary>
    /// Sets the hotspot and falloff angles.
    ///
    /// The region between the hotspot and falloff angles is sometimes 
    /// referred to as the rapid decay area.
    ///
    /// The greater the difference between the hotspot and falloff angles,
    /// the softer the edge of the light beam. If the hotspot and falloff 
    /// angles are equal, the edge of the light beam is sharp. Both values
    /// can range from 0 to 160 degrees. You cannot set the hotspot angle
    /// to be greater than the falloff angle.
    /// </summary>
    ///
    /// <param name="hotspot">
    /// The hotspot cone angle, in radians. Defines the brightest part of the
    /// spot light beam. Must be smaller than or equal to the falloff.
    /// </param>
    /// <param name="falloff">
    /// The falloff cone angle, in radians. Defines the full cone of light. This
    /// is also known as the field angle. Must be larger than or equal to the
    /// hotspot.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk always.
    /// Note that the method automatically adjusts invalid values for the hotspot and falloff angles.
    /// See Remarks for details.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.  
    /// The method automatically adjusts the hotspot and falloff angle to be within acceptable ranges as follows:
    ///
    /// If new Hotspot angle != current Hotspot Angle and new Hotspot >= current Falloff, new Falloff angle is changed to (new Hotspot + 1 degree)
    /// If new Falloff angle != current Falloff Angle and new Falloff <= current Hotspot, new hotspot angle is changed to (new Falloff - 1 degree) 
    /// If new Hotspot Angle > 159 degrees, it is set to 159 degrees.
    /// If new Falloff Angle > 160 degrees, it is set to 160 degrees.
    /// If new Hotspot Angle < 0 degrees, it is set to 0 degrees.
    /// If new Falloff Angle < 1 degree, it is set to 1 degrees.
    ///
    /// Note that all checks (and any adjustments) are executed in sequence during every call to the method.


    /// </remarks>
    virtual Acad::ErrorStatus setHotspotAndFalloff(double hotspot, double falloff);

    /// <summary>
    /// Gets the hotspot angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The hotspot angle, in radians.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual double hotspotAngle() const;
    
    /// <summary>
    /// The falloff angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The falloff angle, in radians.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual double falloffAngle() const;

    /// <summary>
    /// Gets the direction (vector) that the rays of a distant light travel in.
    /// </summary>
    ///
    /// <returns>
    /// The direction, as a vector; the positive direction of this vector is
    /// from light to object.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for distant light type only.
    /// </remarks>
    virtual const AcGeVector3d& lightDirection() const;

    /// <summary>
    /// Sets the direction the light rays of a distant light travel in. This vector is in the
    /// direction of the light rays (from light to object).
    /// </summary>
    ///
    /// <param name="lightvec">
    /// The vector for the light rays.
    /// </param>
    ///
    /// <remarks>
    /// Valid for distant light type only.
    /// </remarks>
    virtual Acad::ErrorStatus setLightDirection(const AcGeVector3d& lightvec);

private:
    friend class AcDbImpLight;
    AcDbImpLight * mpAcDbImpLight;
    bool mSelected;
};






