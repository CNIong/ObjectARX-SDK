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


#ifndef SUBREGIONROWITERATORINTERFACE_H
#include "SubRegionRowIteratorInterface.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif

#ifndef SUBSAMPLINGROWITERATORINTERFACE_H
#define SUBSAMPLINGROWITERATORINTERFACE_H

namespace Atil
{

/// <summary>
/// This class specifies an aggregate of the <c>SubRegionRowIteratorInterface</c>.
/// It specifies that the <c>SubRegionRowIteratorInterface</c> can return scaled 
/// versions of the data.
/// </summary>
///
/// <remarks>
/// To be used the <c>RowIteratorInterface</c> derivant must derive from
/// this class. This is multiple derivation however the parents are both pure abstract
/// API specification classes. RTTI will be used to identify if your class implements
/// this Interface.
/// </remarks>
///
class SubSamplingRowIteratorInterface : public SubRegionRowIteratorInterface
{
public:
    /// <summary>
    /// This is a trivial destructor.
    /// </summary>
    virtual ~SubSamplingRowIteratorInterface ();

    /// <summary>
    /// This sets the desired output size.
    /// </summary>
    /// 
    /// <param name="scaledSize"> The size of the area at scale to be returned.
    /// </param>
    ///
    virtual void setScaledSize (const Size& scaledSize)  = 0;

    /// <summary>
    /// This sets the scale to 1:1 (unscaled).
    /// </summary>
    virtual void resetScaleFactor () = 0;

    /// <summary>
    /// A trivial constructor.
    /// </summary>
    SubSamplingRowIteratorInterface ();
};

} //end of namespace

#endif
