//
//
//  (C) Copyright 2005-2007 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Interface definition for Host Image Services.
//
//  An application (like AutoCAD) provides implementation for the 
//  AdHostImageAppServices interface to expose capabilities to
//  initialize/un-initialize the ATIL library. 
//  Using this interface, application also provides ways to 
//  register/unregister/reregister format codecs with the ATIL
//  library. With the AdHostImageAppServices inteface, applications
//  can also choose to expose some image filter/extension strings 
//  of the codec formats that its support.

#pragma once

#include "AdAChar.h"

// Forward class declarations

namespace Atil {
    class ImageFormatCodec;
    class ProgressCallbackInterface;
};

class AdHostImageAppServices;

////////////////////////////////////////////////////////////////////////
// class AdHostImageAppServices 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class defines an interface to publish the 
/// initialization/un-initialization of format codecs with the imaging 
/// library that an application (like AutoCAD) might be internally using.
/// </summary>
///
/// <remarks>
/// Applications (like AutoCAD) which are clients of some imaging library 
/// themselves can provide implementation for this interface. It is preferred 
/// to have a singleton object implementing this interface for the entire 
/// application session. Using this interface, applications can mask the
/// internals of how it initializes the imaging library it uses. 
/// </remarks>
///
class __declspec(novtable) AdHostImageAppServices
{
public:

    /// 
    /// <summary>
    /// Use this function to get the list of image file extensions
    /// supported by the currently in use imaging library.
    /// </summary>
    /// 
    /// <param name="bRefresh">
    /// If set to true would re-populate the list of format file 
    /// extensions that the underlying imaging library supports.
    /// Callers to this function would usually set bRefresh parameter to 
    /// true after registering a new format codec with the imaging library.
    /// </param>
    ///
    /// <returns> 
    /// Returns a pointer to a array of character which has semicolon 
    /// separated extension strings.
    /// Format of the returned string will be as follows:
    /// "bmp;dib;rle;tif;tiff;cal;mil;rst;cg4;gp4;cals;gif"
    /// </returns>
    ///
    virtual const ACHAR* imageFileExtensions (bool bRefresh = false) = 0;

    /// 
    /// <summary>
    /// Use this function to get the filtered list of image 
    /// file descriptions and extensions supported by the currently 
    /// in use imaging library.
    /// </summary>
    /// 
    /// <param name="bRefresh">
    /// If set to true would re-populate the filter strings 
    /// supported by the underlying imaging library.
    /// Callers to this function would usually set bRefresh parameter to 
    /// true after registering a new format codec with the imaging library.
    /// </param>
    ///
    /// <returns> 
    /// Returns a pointer to a array of character which has semicolon 
    /// separated format specific filtered strings.
    /// Format of the returned string will be as follows:
    /// "Windows Bitmap:bmp,dib,rle;Tagged Image File Format:tif,tiff;
    /// CALS MIL-R-28002A Type I Reader:cal,mil,rst,cg4,gp4,cals;
    /// Image Systems CCITT Group 4 compression:ig4;Macintosh PICT:pct,pict;RLC:rlc;
    /// TrueVision Targa Bitmap:tga;
    /// Portable Network Graphics file (PNG):png;
    /// JFIF(JPEG) 6.0:jpg;ZSoft Paint:pcx;
    /// Autodesk Animator FLI/FLC File:fli,flc;Graphic Interchange format:gif"  
    /// </returns>
    ///
    virtual const ACHAR* imageFilterString (bool bRefresh = false) = 0;

    /// 
    /// <summary>
    /// Registers the supplied format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the registration succeeded.
    /// </returns>
    ///
    virtual bool registerFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Use this method to find out if a format codec is already registered 
    /// with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the input format codec is already registered 
    /// with the imaging library.
    /// </returns>
    ///
    virtual bool formatCodecRegistered (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Re-registers the input format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the reregistration process succeeded.
    /// </returns>
    ///
    virtual bool reRegisterFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Unregisters the input format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the un-registration process succeeded.
    /// </returns>
    ///
    virtual bool unRegisterFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Registers a progress call back with the imaging library.
    /// </summary>
    ///
    /// <param name="pCallback">
    /// A pointer to an object that implements Atil::ProgressCallbackInterface 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns the pointer to the old Atil::ProgressCallbackInterface object.
    /// </returns>
    ///
    virtual Atil::ProgressCallbackInterface* registerProgressCallback (Atil::ProgressCallbackInterface* pCallback ) = 0;
};

/// 
/// <summary>
/// Gives access to the global object that implements the 
/// AdHostImageAppServices interface.
/// </summary>
/// 
/// <returns> 
/// If succeeded, returns a pointer to the AdHostImageAppServices interface.
/// Returns NULL if failed.
/// </returns>
///
AdHostImageAppServices* getAdHostImageAppServices();
