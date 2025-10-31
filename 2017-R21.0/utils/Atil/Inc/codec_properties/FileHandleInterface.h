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
