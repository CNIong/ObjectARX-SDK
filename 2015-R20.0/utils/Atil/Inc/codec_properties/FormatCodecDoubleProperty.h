//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECDOUBLEPROPERTY_H
#define FORMATCODECDOUBLEPROPERTY_H

namespace Atil
{

/// <summary>
/// This class holds a double floating point value. 
/// </summary>
///
/// <remarks>
/// The double value is most often used in conjunction with other simple
/// data type properties in a set grouping that forms something analogous to
/// a structure in 'c'.
/// </remarks>
///
class FormatCodecDoubleProperty : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecDoubleProperty ();

    /// <summary>
    /// This method is an artificial copy constructor. It will make a complete
    /// and accurate copy of the class.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a new <c>FormatCodecDoubleProperty</c> instance as a 
    /// <c>FormatCodecPropertyInterface</c> pointer.
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This method will return the default value of the property.
    /// </summary>
    ///
    /// <param name="dDefault">
    /// A double reference which will be set to the default value of the instance.
    /// </param>
    ///
    virtual void getDefaultValue (double& dDefault) const;

    /// <summary>
    /// This method will set the double.
    /// </summary>
    ///
    /// <param name="dValue">
    /// The const double reference which will be used to set the value held by the instance.
    /// </param>
    ///
    /// <returns>
    /// This will return true on success.
    /// </returns>
    ///
    virtual bool setValue (const double& dValue);

    /// <summary>
    /// This method will get the double.
    /// </summary>
    ///
    /// <param name="dValue">
    /// The double reference which will be set to the value held by the instance.
    /// </param>
    ///
    virtual void getValue (double& dValue ) const;

    /// <summary>
    /// This method will return the upper and lower bounds of the value.
    /// </summary>
    ///
    /// <param name="dMinimum">
    /// A double reference that will be set to the minimal valid double value.
    /// </param>
    ///
    /// <param name="dMaximum">
    /// A double reference that will be set to the maximum valid double value.
    /// </param>
    ///
    virtual void getPropertyLimits (double& dMinimum, double& dMaximum) const;
    
protected:

    /// <summary>
    /// (Protected) The constructor for the class.
    /// </summary>
    ///
    /// <param name="dMin">
    /// A const double reference to the minimal valid double value.
    /// </param>
    ///
    /// <param name="dMax">
    /// A const double reference to the maximum valid double value.
    /// </param>
    ///
    /// <param name="dDefault">
    /// A const double reference to the default double value.
    /// </param>
    ///
    FormatCodecDoubleProperty (const double& dMin, const double& dMax,
        const double& dDefault);

protected:
    /// <summary>
    /// (Protected) The default value.
    /// </summary>
    double mdDefault;

    /// <summary>
    /// (Protected) The upper bound of the valid range.
    /// </summary>
    double mdMax;

    /// <summary>
    /// (Protected) The lower bound of the valid range.
    /// </summary>
    double mdMin;

    /// <summary>
    /// (Protected) The value held by the instance.
    /// </summary>
    double mdValue;
};

} // end of namespace Atil

#endif
