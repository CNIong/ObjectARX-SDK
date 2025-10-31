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
