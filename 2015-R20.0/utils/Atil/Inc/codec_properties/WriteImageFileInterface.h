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
#ifndef WRITEIMAGEFRAMEINTERFACE_H
#include "WriteImageFileFrameInterface.h"
#endif

#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif

#ifndef WRITEIMAGEFILEINTERFACE_H
#define WRITEIMAGEFILEINTERFACE_H

namespace Atil
{
///<summary>This interface class is the base class for image file handlers to implement image file creation.</summary>
class WriteImageFileInterface 
{
public:
    ///<summary>The destructor.</summary>
    virtual ~WriteImageFileInterface ();

    ///<summary>This constructs a <c>WriteImageFrameInterface</c> derivate instance for writing an image into a file.</summary>
    ///<returns>This returns a <c>WriteImageFrameInterface</c> derivate instance if successful and NULL if not.</returns>
    virtual WriteImageFileFrameInterface* newWriteImageFileFrameInterface () = 0;

    ///<summary>This queries the <c>ImageFormatCodec</c> instance that created this instance.</summary>
    ///<returns>This will return the <c>ImageFormatCodec</c> instance that created the instance.</returns>    
    virtual const ImageFormatCodec* formatCodec () const = 0;

    ///<summary>This sets the file name and path to be written.</summary>
    ///<param name='fsNewFile'>A const reference to a <c>FileSpecifier</c> that 
    ///holds the path and name of the file to be written.</param>
    ///<returns>This will return true if the path and name can be written to.</returns>
    ///<remarks>ATIL does not overwrite files. There must be no conflicts with the path for the write to suceed.</remarks>
    virtual bool setFileName (const FileSpecifier& fsNewFile) = 0;
    
    ///<summary>This queries the set file name.</summary>
    ///<returns>This returns a const reference to the set <c>FileSpecifier</c> holding the file to be written.</returns>
    virtual const FileSpecifier& fileName () const = 0;

    ///<summary>This queries the number of files that will be written.</summary>
    ///<returns>The integer count of files that will be written.</returns>
    ///<remarks>Some formats consist of multiple files. This call exposes that.</remarks>
    virtual int numFilesInClosureSet () = 0;

    ///<summary>This queries the file name of the set to be written.</summary>
    ///<param name='nMemberIndex'>The integer index of the file path in the set to be written to return.</param>
    ///<returns>This returns the <c>FileSpecifier</c> holding the name and path of the file.</returns>
    virtual FileSpecifier getClosureSetMember (int nMemberIndex) = 0;

    ///<summary>This method creates a frame to hold an image within an image file.</summary>
    ///<param name='pFrameAtts'>A pointer to a <c>WriteImageFileFrameInterface</c> instance that has the information needed to write the image.</param>
    ///<param name='pRowIterator'>A pointer to a <c>RowIteratorInterface</c> instance the will provide the data to be written.</param>
    ///<returns>This will return the index of the frame within the image file.</returns>
    virtual int writeImageFileFrame (WriteImageFileFrameInterface* pFrameAtts,
        RowIteratorInterface* pRowIterator) = 0;
};

} //end of namespace

#endif


#ifndef FILESPECIFIER_H
#include <FileSpecifier.h>
#endif

