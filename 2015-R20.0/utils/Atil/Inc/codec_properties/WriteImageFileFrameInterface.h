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

#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef ROWITERATORINTERFACE_H
namespace Atil { class RowIteratorInterface; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif

#ifndef WRITEIMAGEFILEFRAMEINTERFACE_H
#define WRITEIMAGEFILEFRAMEINTERFACE_H

namespace Atil
{
///<summary>This interface class serves as the base for writing image data into files.</summary>
///<remarks>This is the frame writing class to deriver from for codec writers.</remarks>
class WriteImageFileFrameInterface 
{
public:
    ///<summary>The destructor.</summary>
    virtual ~WriteImageFileFrameInterface ();
    
    ///<summary>Used to set the size in pixels of the image being written.</summary>
    ///<param name='nRows'>The number of rows to be written.</param>
    ///<param name='nColumns'>The number of columns to be written.</param>
    virtual void setDimensions (int nRows, int nColumns) = 0;

    ///<summary>Used to set the <c>DataModelType</c> of the image being written.</summary>
    ///<param name='dataModelType'>The type of image being written.</param>
    virtual void setDataModel (DataModelAttributes::DataModelType dataModelType) = 0;

    ///<summary>Used to set the number of bits used per sample (pixel).</summary>
    ///<param name='bitsPerPixel'>The number of bits per sample (pixel) in the image being written.</param>
    virtual void setBitsPerPixel (int bitsPerPixel) = 0;

    ///<summary>Used to set the number of used bits per pixel. This is always less than or equal to the Bits Per Pixel.</summary>
    ///<param name='bitsUsedPerPixel'>The number bits used from the bits per sample.</param>
    virtual void setBitsUsedPerPixel (int bitsUsedPerPixel) = 0;

    ///<summary>Used to set the number palette entries if the image to be written is paletted.</summary>
    ///<param name='nPaletteEntries'>The number of colors in the palette should always be less than 256.</param>
    virtual void setNumPaletteEntries (int nPaletteEntries) = 0;

    ///<summary>Used to send the colors of the palette to the image.</summary>
    ///<param name='palette'>A pointer to an array of packed r,g,b triples (as bytes) the length set by <c>setNumPaletteEntries</c>.</param> 
    virtual void setPaletteEntries (UInt8* palette) = 0;

    ///<summary>This allocates a property set iterator for setting properties into the image.</summary>
    ///<returns>This returns a <c>FormatCodecPropertySetIterator</c> with the properties that can be set into the image frame.</returns>
    virtual FormatCodecPropertySetIterator* newPropertySetIterator () = 0;

    ///<summary>This retrieves a property by its identifier.</summary>
    ///<param name='id'>An instance of <c>FormatCodecPropertySetIterator</c> that is the identifier of the property desired.</param>
    ///<returns>This returns the desired property or NULL if it is not available.</returns>
    virtual FormatCodecPropertyInterface* getProperty (FormatCodecPropertyInterface::PropertyIdentifier id) = 0;

    ///<summary>This retrieves a property by its name.</summary>
    ///<param name='sbPropertyName'>An instance of <c>StringBuffer</c> that is the name of the property desired.</param>
    ///<returns>This returns the desired property or NULL if it is not available.</returns>
    virtual FormatCodecPropertyInterface* getProperty (const StringBuffer& sbPropertyName) = 0;

    ///<summary>This sets a property into an image frame for writing.</summary>
    ///<param name='pThisProp'>A const pointer to the property to be written to the image frame.</param>
    ///<returns>This should return true if the property was successfully added to the image frame.</returns>
    virtual bool setProperty (const FormatCodecPropertyInterface* pThisProp) = 0;

    ///<summary>This causes all the properties of an image frame to be reset to their default values.</summary>
    virtual void resetProperties () = 0;

    ///<summary>This tests to be sure that any properties that are needed to complete the frame have been set.</summary>
    ///<returns>This will return true if the image frame has no outstanding properties it needs and is ready to recieve image data for the frame.</returns>
    virtual bool requiredPropertiesSet () const = 0;
};

} //end of namespace

#endif


