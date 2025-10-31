//
// Copyright (C) 1996-1998 by Autodesk, Inc.
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

// Image Engine External Loadable Module Common Definitions.

/*
* Begin multiple inclusion protection...
*/
#ifndef	_ieapimod_h
#define	_ieapimod_h

// module Identification strings - entry points

static const char IE_IMAGE_MODULE_ID[]      = "moduleIdentify";
static const char IE_IMAGE_FILE_ENTRY[]     = "newIeFileAnalyzer";
static const char IE_IMAGE_CODEC_ENTRY[]    = "newIeCodecInterface";

// module Identification strings - service & service type

static const char IE_IMAGE_FILE_SERVICE[] = "IE Image File Service";
static const char IE_FILE_READER[]        = "IE Image File Reader";
static const char IE_FILE_WRITER[]        = "IE Image File Writer";
static const char IE_FILE_READER_WRITER[] = "IE Image File Reader/Writer";

static const char IE_IMAGE_CODEC_SERVICE[]  = "IE Image Codec Service";
static const char IE_CODEC_DECODER[]        = "IE Image Decoder";
static const char IE_CODEC_ENCODER[]        = "IE Image Encoder";
static const char IE_CODEC_CODEC[]          = "IE Image Codec";

enum IeModuleId {
    IE_IMAGE_SERVICE,
    IE_SERVICE_TYPE
};

// module supplied identification routine

extern "C" const char *moduleIdentify(IeModuleId moduleId);

#endif /* _ieapimod_h */
