///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECDENSITY_H
#define FORMATCODECDENSITY_H

namespace Atil
{
/// <summary>
/// This ATIL property encodes density (pixels per unit of measure) of the image frame.
/// </summary>
///
class FormatCodecDensity : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// This enum describes the different configurations that density may take.
    /// </summary>
    enum Mode { 
        /// <summary>
        /// This entry describes the density as a single integral value for x and y.
        /// </summary>
        kIntegralUnified, 
        /// <summary>
        /// This entry describes the density as independent integral values for x and y.
        /// </summary>
        kIntegralDifferential,
        /// <summary>
        /// This entry describes the density as a single floating point value for x and y.
        /// </summary>
        kDoubleUnified, 
        /// <summary>
        /// This entry describes the density as independent floating point values for x and y.
        /// </summary>
        kDoubleDifferential 
    };

    /// <summary>
    /// This enum describes the units of measure of the density value.
    /// </summary>
    enum Units { 
        /// <summary>
        /// This entry indicates that the units of measure are unknown.
        /// </summary>
        kNone, 
        /// <summary>
        /// This entry indicates that the units of measure are centimeters.
        /// </summary>
        kCentimeters, 
        /// <summary>
        /// This entry indicates that the units of measure are inches.
        /// </summary>
        kInches 
    };

public:

    /// <summary>
    /// The constructor for <c>FormatCodecDensity</c>.
    /// </summary>
    ///
    /// <param name="dXDefault">
    /// This value will be set as the default X density.
    /// </param>
    ///
    /// <param name="dYDefault">
    /// This value will be set as the default Y density.
    /// </param>
    ///
    /// <param name="units">This value will be set as the default units.
    /// </param>
    ///
    FormatCodecDensity (const double& dXDefault, const double& dYDefault, Units units );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecDensity ();

    /// <summary>
    /// This method is an artificial copy constructor. It will make a complete
    /// and accurate copy of the class.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecDensity</c> instance as a 
    /// <c>FormatCodecPropertyInterface</c> pointer.
    /// </returns>
    ///
    /// <remarks>
    /// As this method remains abstract the image format codec must derive an object
    /// and implement this method to return this property.
    /// </remarks>
    ///
    virtual FormatCodecPropertyInterface* clone () const = 0;

    /// <summary>
    /// This method will return the default density values of the property.
    /// </summary>
    ///
    /// <param name="dXDefault">
    /// A double reference which will be set to the default X density.
    /// </param>
    ///
    /// <param name="dYDefault">
    /// A double reference which will be set to the default Y density.
    /// </param>
    ///
    virtual void getDefaultValue (double& dXDefault, double& dYDefault) const;

    /// <summary>
    /// This method will set the density values of the property.
    /// </summary>
    ///
    /// <param name="dXDensity">
    /// A double reference which will be set into the X density of the property.
    /// </param>
    ///
    /// <param name="dYDensity">
    /// A double reference which will be set into the Y density of the property.
    /// </param>
    ///
    /// <returns>
    /// This returns true if the setting of the values was successful.
    /// </returns>
    ///
    virtual bool setValues (double dXDensity, double dYDensity);

    /// <summary>
    /// This method will return the density values of the property.
    /// </summary>
    ///
    /// <param name="dXDensity">
    /// A double reference which will be set to the X density.
    /// </param>
    ///
    /// <param name="dYDensity">
    /// A double reference which will be set to the Y density.
    /// </param>
    ///
    virtual void getValues (double& dXDensity, double& dYDensity) const;

    /// <summary>
    /// This method will return the default units of the density values of the property.
    /// </summary>
    ///
    /// <param name="units">
    /// A reference to a <c>Units</c> entry which will be set to the default units of measure.
    /// </param>
    ///
    virtual void getDefaultUnits (Units& units) const;

    /// <summary>
    /// This method will return the units of the density values of the property.
    /// </summary>
    ///
    /// <param name="units">
    /// A reference to a <c>Units</c> entry which will be set to the units of measure.
    /// </param>
    ///
    virtual void getUnits (Units& units) const;

    /// <summary>
    /// This method will return the units of the density values of the property.
    /// </summary>
    ///
    /// <param name="units">
    /// A  <c>Units</c> entry which will be used set the units of measure.
    /// </param>
    ///
    /// <returns>
    /// This returns true if the setting of the units was successful.
    /// </returns>
    ///
    virtual bool setUnits (Units units);

    /// <summary>
    /// This describes the configuration of density.
    /// </summary>
    ///
    /// <returns>
    /// This returns the <c>Mode</c> enum entry describing the configuration of the density.
    /// </returns>
    ///
    /// <remarks>
    /// As this method is abstract the image format codec must derive an object
    /// and implement this method to return this property.
    /// </remarks>
    ///
    virtual Mode getCapabilty () const = 0;

protected:
    /// <summary>
    /// (Protected) The default X density.
    /// </summary>
    double mdXDefault;

    /// <summary>
    /// (Protected) The default Y density.
    /// </summary>
    double mdYDefault;

    /// <summary>
    /// (Protected) The X density.
    /// </summary>
    double mdXDensity;

    /// <summary>
    /// (Protected) The Y density.
    /// </summary>
    double mdYDensity;

    /// <summary>
    /// (Protected) The default units for density.
    /// </summary>
    Units  mDefaultUnits;

    /// <summary>
    /// (Protected) The \units for density.
    /// </summary>
    Units  mUnits;
};

}

#endif

