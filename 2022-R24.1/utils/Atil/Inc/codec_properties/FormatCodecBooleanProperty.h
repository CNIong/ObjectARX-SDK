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

///////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECBOOLEANPROPERTY_H
#define FORMATCODECBOOLEANPROPERTY_H

namespace Atil
{

/// <summary>
/// This class holds a boolean value. 
/// </summary>
///
/// <remarks>
/// The boolean value is most often used in conjunction with other simple
/// data type properties in a set grouping that forms something analogous to
/// a structure in 'c'.
///
/// An example may be a format that has compression that may or may not be
/// lossy. A boolean together with an integer may be a way to expose the
/// option of lossy vs lossless compression.
/// </remarks>
///
class FormatCodecBooleanProperty : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// The constructor for the class.
    /// </summary>
    ///
    /// <param name="bDefault">
    /// A boolean which will set the initial state of the class.
    /// </param>
    ///
    FormatCodecBooleanProperty (bool bDefault);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecBooleanProperty ();

    /// <summary>
    /// This method is an artificial copy constructor. It will make a complete
    /// and accurate copy of the class.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecBooleanProperty</c> instance as a 
    /// <c>FormatCodecPropertyInterface</c> pointer.
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This method will return the default value of the property.
    /// </summary>
    ///
    /// <param name="bDefault">
    /// A boolean reference which will be set to the default state of the class.
    /// </param>
    ///
    /// <returns>
    /// The boolean return indicates whether the class has a valid default.
    /// </returns>
    ///
    bool getDefaultValue (bool& bDefault) const;

    /// <summary>
    /// This method will set the state of the boolean.
    /// </summary>
    ///
    /// <param name="bState">
    /// A boolean which will be used to set the state of the class.
    /// </param>
    ///
    void setValue (bool bState);

    /// <summary>
    /// This method will get the state of the boolean.
    /// </summary>
    ///
    /// <param name="bState">
    /// A boolean reference which will set to set the state of the class.
    /// </param>
    ///
    void getValue (bool& bState) const;

protected:

    /// <summary>
    /// (Protected) The default value.
    /// </summary>
    bool mbDefault;

    /// <summary>
    /// (Protected) The value of the class.
    /// </summary>
    bool mbValue;
};

} // end of namespace Atil

#endif
