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

#ifndef FORMATCODECAPIVERSIONINTERFACE_H
#define FORMATCODECAPIVERSIONINTERFACE_H

#ifndef ATILVERSIONS_H
#include "AtilVersions.h"
#endif

namespace Atil
{

/// <summary>
/// This class references the 'define'd API version of ATIL and encodes it returning
/// the version in its member methods. When Image File Format Codecs are compiled against
/// a version of the ATIL library, they refer to this class which then returns the
/// the API version that the Codecs "talk". 
/// </summary>
///
/// <remarks>
/// ATIL has versions for the API that it exports as well as the library itself.
/// </remarks>
///
class FormatCodecApiVersionInterface
{
public:

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecApiVersionInterface();

    /// <summary>
    /// This returns the major revision of the ATIL Format Codec API.
    /// </summary>
    ///
    /// <returns>
    /// The integral revision number.
    /// </returns>
    ///
    virtual int majorVersion () const;

    /// <summary>
    /// This returns the minor revision of the ATIL Format Codec API.
    /// </summary>
    ///
    /// <returns>
    /// The integral revision number.
    /// </returns>
    ///
    virtual int minorVersion () const;
};

}

#endif
