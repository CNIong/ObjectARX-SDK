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

#ifndef FORMATCODECASSOCIATION_H
#define FORMATCODECASSOCIATION_H

namespace Atil
{
/// <summary>
/// This property class is used to represent a relationship between two
/// frames (image instance) within an image file. A frame may return more than one
/// Association where each Association indicates an unigue relationship to another frame.
/// </summary>
///
class FormatCodecAssociation : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// An enum of entries that describe the nature of the relationship between
    /// the frames of the image.
    /// </summary>
    ///
    enum AssociationType { 
        /// <summary>
        /// This frame is a reduced resolution copy of the other that should be
        /// used to as a quickly loading preview of the main image.
        /// </summary>
        ///
        kThumbnail, 
        
        /// <summary>
        /// This entry describes the frame as a page of a number of pages. This
        /// is used for an image file that contains the scanned pages of documents.
        /// </summary>
        ///
        kPage,

        /// <summary>
        /// This entry describes the frame as a plane of data that holds a transparency
        /// or alpha mask that is the same size as the referenced frame.
        /// </summary>
        ///
        kTransparencyMask, 
        
        /// <summary>
        /// This entry is for those relationships that can not be accurately represented
        /// by any other enum entry type.
        /// </summary>
        ///
        kOther,

        /// <summary>
        /// This entry is used to express an ordering relationship between two frames 
        /// with respect to the display. The frame returning the property should be displayed
        /// on top of the frame indicated in the property value.
        /// </summary>
        ///
        kDisplayAbove,

        /// <summary>
        /// This entry is used to express a static positional relationship akin to a piece in a puzzle.
        /// This frame and the other specified should be considered as a single entity when transforming
        /// (rot,scale,translate) either image. This might be used to force the stitching of two images
        /// to create an entire scene. 
        /// </summary>
        ///
        kSpatialLink
    };

public:

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecAssociation ();

    /// <summary>
    /// This method is an artificial copy constructor. It will make a complete
    /// and accurate copy of the class.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecAssociation</c> instance as a 
    /// <c>FormatCodecPropertyInterface</c> pointer.
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This method will retrieve the enum entry that describes the relationship.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the <c>AssociationType</c> enum.
    /// </returns>
    ///
    virtual AssociationType getType () const;

    /// <summary>
    /// This method sets the <c>AssociationType</c> enum value.
    /// </summary>
    /// 
    /// <param name="type">
    /// An entry for the <c>AssociationType</c> enum that is to describe the relationship.
    /// </param>
    ///
    virtual void setType ( AssociationType type );

    /// <summary>
    /// This method will retrieve the frame index of the related image frame.
    /// </summary>
    ///
    /// <returns>
    /// The integer index of the related image frame.
    /// </returns>
    ///
    virtual int associatedTo () const;

    /// <summary>
    /// This method will set the frame index of the related image frame.
    /// </summary>
    ///
    /// <param name="nFrameIndex">
    /// The integer index of the related frame.
    /// </param>
    ///    
    virtual void setAssociatedFrameIndex ( int nFrameIndex );

protected:

    /// <summary>
    /// (Protected) The constructor for the class.
    /// </summary>
    ///
    /// <param name="type">
    /// An entry for the <c>AssociationType</c> enum that is to describe the relationship.
    /// </param>
    ///
    /// <param name="nFrameIndex">
    /// The integer index of the related frame.
    /// </param>
    /// 
    FormatCodecAssociation (AssociationType type, int nFrameIndex);

protected:
    /// <summary>
    /// (Protected) The entry for the <c>AssociationType</c> enum that describes the relationship.
    /// </summary>
    ///
    AssociationType mAType;

    /// <summary>
    /// (Protected) The integer index of the related frame.
    /// </summary>
    ///
    int mnFrameIndex;
};


} // end of namespace Atil

#endif




