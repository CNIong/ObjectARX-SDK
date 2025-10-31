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
#ifndef FORMATCODECINCLUSIVEPROPERTYSETINTERFACE_H
#include "FormatCodecInclusivePropertySetInterface.h"
#endif

#ifndef FORMATCODECEXCLUSIVEPROPERTYSETINTERFACE_H
#define FORMATCODECEXCLUSIVEPROPERTYSETINTERFACE_H

namespace Atil
{

/// <summary>
/// This class groups properties into a set of properties where 
/// only one of the properties may be selected as active. This 
/// can be used to offer "menu-like" choices such as "High, Medium, Low".
/// </summary>
///
class FormatCodecExclusivePropertySetInterface : public FormatCodecInclusivePropertySetInterface
{
public:    
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecExclusivePropertySetInterface ();

    /// <summary>
    /// The index of the default selected property in the set.
    /// </summary>
    /// 
    /// <returns>
    /// The index of the default selected property.
    /// </returns>
    ///
    virtual int getDefaultPropertyIndex () const;

    /// <summary>
    /// The index of the selected property in the set.
    /// </summary>
    /// 
    /// <returns>
    /// The index of the selected property.
    /// </returns>
    ///
    virtual int getSelectedIndex () const;

    /// <summary>
    /// This sets index of the selected property in the set.
    /// </summary>
    /// 
    /// <param name="nSelectionIndex">
    /// The index of the property to that is selected.
    /// </param>
    ///
    virtual void setSelectedIndex (int nSelectionIndex);

protected:

    /// <summary>
    /// (Protected) The simple constructor.
    /// </summary>
    ///
    FormatCodecExclusivePropertySetInterface ();

    /// <summary>
    /// (Protected) The pre-allocating constructor.
    /// </summary>
    /// 
    /// <param name="nNumProperties">
    /// The number of properties that will be in the set.
    /// </param>
    ///
    FormatCodecExclusivePropertySetInterface (int nNumProperties);

    /// <summary>
    /// (Protected) Copy constructor.
    /// </summary>
    ///
    /// <param name="from">
    /// The instance to be copied.
    /// </param>
    ///
    FormatCodecExclusivePropertySetInterface (const FormatCodecExclusivePropertySetInterface& from);

    /// <summary>
    /// (Protected) The default selected property index.
    /// </summary>
    int mnDefaultPropertyIndex;

    /// <summary>
    /// (Protected) The selected property index.
    /// </summary>
    int mnSelectedIndex;

private:
    FormatCodecExclusivePropertySetInterface& operator= (const FormatCodecExclusivePropertySetInterface& from);
};

} // end of namespace Atil

#endif
