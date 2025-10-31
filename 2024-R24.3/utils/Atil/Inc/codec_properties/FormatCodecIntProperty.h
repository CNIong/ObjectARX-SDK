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

#ifndef FORMATCODECINTPROPERTY_H
#define FORMATCODECINTPROPERTY_H

namespace Atil
{

/// <summary>
/// This class holds an integer value. 
/// </summary>
///
/// <remarks>
/// The double value is most often used in conjunction with other simple
/// data type properties in a set grouping that forms something analogous to
/// a structure in 'c'.
/// </remarks>
///
class FormatCodecIntProperty : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecIntProperty ();

    /// <summary>
    /// This method is an artificial copy constructor. It will make a complete
    /// and accurate copy of the class.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a new <c>FormatCodecIntProperty</c> instance as a 
    /// <c>FormatCodecPropertyInterface</c> pointer.
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This method will return the default value of the property.
    /// </summary>
    ///
    /// <param name="defaultValue">
    /// An integer reference which will be set to the default value of the instance.
    /// </param>
    ///
    virtual void getDefaultValue (int& defaultValue);

    /// <summary>
    /// This method will get the integer.
    /// </summary>
    ///
    /// <returns>
    /// This will return the value held by the instance.
    /// </returns>
    ///
    virtual int getValue () const;

    /// <summary>
    /// This method will set the integer.
    /// </summary>
    ///
    /// <param name="value">
    /// The const integer reference which will be used to set the value held by the instance.
    /// </param>
    ///
    /// <returns>
    /// This will return true on success.
    /// </returns>
    ///
    virtual bool setValue (int value);

    /// <summary>
    /// This method will return the upper and lower bounds of the value.
    /// </summary>
    ///
    /// <param name="nMinimum">
    /// An integer reference that will be set to the minimal valid value.
    /// </param>
    ///
    /// <param name="nMaximum">
    /// An integer reference that will be set to the maximum valid value.
    /// </param>
    ///
    virtual void getPropertyLimits (int& nMinimum, int& nMaximum) const;

protected:

    /// <summary>
    /// (Protected) The constructor for the class.
    /// </summary>
    ///
    /// <param name="nMinValue">
    /// The minimal valid value.
    /// </param>
    ///
    /// <param name="nMaxValue">
    /// The maximum valid value.
    /// </param>
    ///
    /// <param name="nDefaultValue">
    /// The default value.
    /// </param>
    ///
    FormatCodecIntProperty (int nMinValue, int nMaxValue, int nDefaultValue);

protected:
    /// <summary>
    /// (Protected) The integer value.
    /// </summary>
    int mnValue;

    /// <summary>
    /// (Protected) The integer default value.
    /// </summary>
    int mnDefaultValue;

    /// <summary>
    /// (Protected) The maximum value the property can have.
    /// </summary>
    int mnMaxValue;

    /// <summary>
    /// (Protected)The minimum value the property can have.
    /// </summary>
    int mnMinValue;
};

} // end of namespace Atil

#endif
