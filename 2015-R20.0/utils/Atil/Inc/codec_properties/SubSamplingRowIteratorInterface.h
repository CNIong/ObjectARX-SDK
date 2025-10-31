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
