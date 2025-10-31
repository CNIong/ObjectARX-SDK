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
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef READIMAGEFILEFRAMEINTERFACE_H
namespace Atil { class ReadImageFileFrameInterface; }
#endif

#ifndef READIMAGEFILEINTERFACE_H
#define READIMAGEFILEINTERFACE_H

namespace Atil
{

///<summary>This interface class is the base class for image file handlers to implement image file reading.</summary>
class ReadImageFileInterface 
{
public:
    ///<summary>The destructor.</summary>
    virtual ~ReadImageFileInterface ();

    ///<summary>This queries the <c>ImageFormatCodec</c> instance that created this instance.</summary>
    ///<returns>This will return the <c>ImageFormatCodec</c> instance that created the instance.</returns>   
    virtual const ImageFormatCodec* formatCodec () const = 0;

    ///<summary>This queuries the name of the image file that is opened.</summary>
    ///<returns>This returns a const reference to a <c>FileSpecifier</c> that points to the image source.</returns>
    ///<remarks><c>FileSpecifier</c> can hold references to sources other than file paths.</remarks>
    virtual const FileSpecifier& fileName () const = 0;

    ///<summary>This queuries the number of files that are opened to read the image.</summary>
    ///<returns>The integer count of files that are opened.</returns>
    ///<remarks>Some formats consist of multiple files. This call exposes that.</remarks>
    virtual int numFilesInClosureSet () const = 0;

    ///<summary>This queuries the file name of the open file.</summary>
    ///<param name='nMemberIndex'>The integer index of the file path to return.</param>
    ///<returns>This returns the <c>FileSpecifier</c> holding the name and path of the file.</returns>
    virtual FileSpecifier getClosureSetMember (int nMemberIndex) const = 0;

    ///<summary>This queuries the number of images within the open image file source.</summary>
    ///<returns>This returns the integer count of images in the file.</returns>
    ///<remarks>ATIL refers to images within a file as "frames".</remarks>
    virtual int numFrames () const = 0;

    ///<summary>This retrieves a <c>ReadImageFileFrameInterface</c> to read a frame image from the file.</summary>
    ///<param name='nFrameIndex'>The integer index of the image frame to retrieve where 0 is the first image frame in a file.</param>
    ///<returns>This returns a pointer to a <c>ReadImageFileFrameInterface</c> instance that represents the image frame.</returns>
    virtual ReadImageFileFrameInterface* getFrame (int nFrameIndex) = 0;
};

} //end of namespace

#endif



