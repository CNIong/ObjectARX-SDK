//
// Copyright (C) 1995-1997 by Autodesk, Inc.
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

const UInt32 kMzfMagic = 0xac64f183;

struct MzfHeader
{
    
    UInt32 magic;
    UInt16 thumbWidth;
    UInt16 thumbHeight;
    UInt16 width;
    UInt16 height;
    UInt16 stripHeight;
    UInt16 encoding;
    UInt32 palette[256];
    
    MzfHeader() : magic(0), width(0), height(0), 
        thumbWidth(0), thumbHeight(0), stripHeight(0), encoding(0) {}
    AiBoolean isValid() const { return magic == kMzfMagic && width && height; }
};

struct MzfStrip
{
    UInt16 size;
    UInt32 offset;
};

/*** FILE LAYOUT ***/
/*
   header
   stripTable[(height+stripHeight-1) / stripHeight]
   imageData
   thumbnail //if (header.thumbWidth > 0)
*/
    
/*** STATIC DATA ***/
static const char *codecMethodTable[] =
{
    "UNCOMPRESSED",
    "MACPAINT PACKBITS",//IE built-in codec
    "MZF RLE",          //custom codec
    0
};
#define NUM_ENCODERS 3

static const char kFileType[] = "MZF";
static const char kVendor[] = "Autodesk";
static const char kReaderName[] = "Sample IE file reader";
static const char kWriterName[] = "Sample IE file writer";
static char * const kpFileSuffixes[] = { "mzf", 0 };
static const char kCopyrightNotice[] = "Copyright (c) 1995-1997 Autodesk, Inc.";
