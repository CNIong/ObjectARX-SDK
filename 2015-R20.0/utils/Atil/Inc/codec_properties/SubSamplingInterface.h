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


#ifndef READIMAGEFILEFRAMEINTERFACE_H
#include "ReadImageFileFrameInterface.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif

#ifndef SUBSAMPLINGINTERFACE_H
#define SUBSAMPLINGINTERFACE_H

namespace Atil
{

/// <summary>
/// This class specifies an aggregate of the <c>ReadImagFileFrameInterface</c>.
/// It specifies that the <c>ReadImagFileFrameInterface</c> can return scaled 
/// versions of the data.
/// </summary>
///
/// <remarks>
/// To be used the <c>ReadImagFileFrameInterface</c> derivant must also derive from
/// this class. This is multiple derivation however the parents are both pure abstract
/// API specification classes. RTTI will be used to identify if your class implements
/// this Interface.
/// </remarks>
///
class SubSamplingInterface
{
public:
    /// <summary>
    /// This is a trivial destructor.
    /// </summary>
    virtual ~SubSamplingInterface ();

    /// <summary>
    /// This is a negotiation. It attempts to get a specific scale for the data and
    /// the method returns the bracket of what is available for return. 
    /// </summary>
    /// 
    /// <param name="srcSize"> 
    /// A const reference to a <c>Size</c> object that holds the size in unscaled pixels.
    /// </param>
    ///
    /// <param name="outputSize"> 
    /// A const reference to a <c>Size</c> object that holds the desired output size in pixels.
    /// </param>
    ///
    /// <param name="lowerResSize"> 
    /// A reference to a <c>Size</c> object that will be set to the nearest resolution available
    /// that is lower than or equal to the desired scale.
    /// </param>
    ///
    /// <param name="higherResSize"> 
    /// A reference to a <c>Size</c> object that will be set to the nearest resolution available
    /// that is higher than or equal to the desired scale.
    /// </param>
    /// 
    /// <returns>
    /// This will return true if the lowerResSize and higherResSize have been correctly set.
    /// </returns>
    virtual bool getAvailableResolution (const Size& srcSize,
        const Size& outputSize, Size& lowerResSize, Size& higherResSize) = 0;
    
    /// <summary>
    /// A trivial constructor.
    /// </summary>
    SubSamplingInterface ();
};

} //end of namespace

#endif
