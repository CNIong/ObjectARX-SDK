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

#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif

#ifndef FILEHANDLEINTERFACE_H
#define FILEHANDLEINTERFACE_H

namespace Atil
{
 
/// <summary>
/// This class has no purpose at this time. It may be used in the future.
/// </summary>
///
class FileHandleInterface 
{
public:
    enum Basis { 
        /// <summary> Not used. </summary>
        kBegin, 
        /// <summary> Not used. </summary>
        kCurrent, 
        /// <summary> Not used. </summary>
        kEnd 
    };

public:
    /// <summary> Not used. </summary>
    virtual ~FileHandleInterface ();
    /// <summary> Not used. </summary>
    /// <returns> Not used. </returns>
    virtual const FileSpecifier& name () = 0;
    /// <summary> Not used. </summary>
    /// <returns> Not used. </returns>
    virtual Int64 size () = 0;
    /// <summary> Not used. </summary>
    /// <param name="nOffset" Not used. </param>
    /// <param name="from" Not used. </param>
    /// <returns> Not used. </returns>
    virtual Int64 seek (Int64 nOffset, enum Basis from) = 0;
    /// <summary> Not used. </summary>
    /// <returns> Not used. </returns>
    virtual Int64 position () = 0;
    /// <summary> Not used. </summary>
    /// <param name="pBuffer"> Not used. </param>
    /// <param name="bytesToRead"> Not used. </param>
    /// <returns> Not used. </returns>
    virtual Int64 read (Byte* pBuffer, Int64 bytesToRead) = 0;
    /// <summary> Not used. </summary>
    /// <param name="pData"> Not used. </param>
    /// <param name="bytesToWrite"> Not used. </param>
    /// <returns> Not used. </returns>
    virtual Int64 write (const Byte* pData, Int64 bytesToWrite) = 0;
};

} // end of namespace Atil

#endif
