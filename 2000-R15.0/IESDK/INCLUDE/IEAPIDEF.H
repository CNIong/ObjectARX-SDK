//
// Copyright (C) 1992-1998 by Autodesk, Inc.
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

// Definitions for file reader/writers

// See additional Copyright at end of file

//static const char sccsid[] = "%W% (%E% %U%)";

#ifndef _ieapidef_h
#define	_ieapidef_h

#define IEX	16384	//IE additions to the otherwise TIFF-based tags
// next available IEX - 523

/*** TAGS COMMON TO MOST IE READERS AND WRITERS ***/
// These attributes are controlled by IeFileDesc and must not be modified 
// by the application using IeFileDesc::setAttribute.

#define	TAG_BITSPERSAMPLE 258		// bits per component [UInt]
#define	TAG_CHUNKBYTECOUNTS 279		// strip/chunk size array [UInt*]
#define	TAG_COLORMAP 320		// color palette [UInt8*]
#define	TAG_COMPRESSION 259		// data encoding technique [char*]
#define	TAG_IMAGELENGTH 257		// image height in pixels [UInt]
#define	TAG_IMAGEWIDTH 256		// image width in pixels [UInt]
#define	TAG_PHOTOMETRIC 262		// colorspace [enum]
#define	    PHOTOMETRIC_MINISWHITE 0	   // gray or bitonal with 0=white
#define	    PHOTOMETRIC_MINISBLACK 1	   // gray or bitonal with 0=black
#define	    PHOTOMETRIC_RGB 2		   // RGB
#define	    PHOTOMETRIC_PALETTE 3	   // indexed
#define	TAG_SAMPLESPERPIXEL 277		// components per pixel [UInt]


/*** ADDITIONAL INFORMATION FOR SOME FILE FORMATS ***/
// These attributes may be accessed using IefileDesc::get/setAttribute.
// Not all file types support all attributes.

#define	TAG_CHUNKWIDTH 322		// number of columns in a tile [UInt]
#define	TAG_CHUNKLENGTH	323		// number of rows in a tile [UInt]
#define TAG_EXTRASAMPLES 338     	// type of 4th component in RGBA [enum]
#define     EXTRASAMPLES_UNKNOWN 0	   // unspecified data [default]
#define     EXTRASAMPLES_ALPHA 1	   // assoc alpha (pre-multiplied RGB)
#define     EXTRASAMPLES_MATTE 2	   // unassoc alpha (not pre-mult RGB)
#define TAG_FRAMEDELAY IEX+505		// frame-to-frame time in msec [UInt]
#define TAG_NUMFRAMES IEX+506		// number of frames in file [UInt]
#define	TAG_ROWSPERSTRIP 278		// rows per strip, same as chunklength
#define TAG_RGBFILLBYTE IEX+509		// RGB requires filler byte [none]

#define	TAG_ARTIST 315			// name of author of image [char*]
#define	TAG_CELLLENGTH 265		// dithering matrix height [UInt]
#define	TAG_CELLWIDTH 264		// dithering matrix width [UInt]
#define TAG_COPYRIGHT 33432		// copyright notice [char*]
#define	TAG_DATETIME 306		// creation date and time [char*]
#define	TAG_GRAYRESPONSECURVE 291	// optical density curve [UInt*]
#define	TAG_GRAYRESPONSEUNIT 290	// gray scale curve accuracy [enum]
#define	    GRAYRESPONSEUNIT_10S 1	   // tenths of a unit
#define	    GRAYRESPONSEUNIT_100S 2	   // hundredths of a unit (default)
#define	    GRAYRESPONSEUNIT_1000S 3	   // thousandths of a unit
#define	    GRAYRESPONSEUNIT_10000S 4	   // ten-thousandths of a unit
#define	    GRAYRESPONSEUNIT_100000S 5	   // hundred-thousandths
#define	TAG_HOSTCOMPUTER 316		// machine on which created [char*]
#define	TAG_IMAGEDESCRIPTION 270	// info about image [char*]
#define	TAG_MAKE 271			// scanner manufacturer name [char*]
#define	TAG_MAXSAMPLEVALUE 281		// maximum sample value [UInt]
#define	TAG_MINSAMPLEVALUE 280		// minimum sample value [UInt]
#define	TAG_MODEL 272			// scanner model name/number [char*]
// note: the following are not the same as the TIFF orientations
// The mapping is :     TIFF    1 2 3 4 5 6 7 8
//                      IE      0 1 3 2 4 5 7 6
// These values are chosen so that an app can use them directly as the
// access parameter in IeImg::read to produce an upright (TOPLEFT) image
// Thus, the tag describes not the orientation of the image, but the inverse
// transform required to re-orient the image.
#define	TAG_ORIENTATION 274		// image orientation
#define	    ORIENT_TOPLEFT  0              // IeImg::leftTop (default)
#define     ORIENT_TOPRIGHT 1              // IeImg::rightTop
#define     ORIENT_BOTLEFT  2              // IeImg::leftBot
#define     ORIENT_BOTRIGHT 3              // IeImg::rightBot
#define	    ORIENT_LEFTTOP  4              // IeImg::topLeft
#define     ORIENT_RIGHTTOP 5              // IeImg::topRight
#define     ORIENT_LEFTBOT  6              // IeImg::botLeft
#define     ORIENT_RIGHTBOT 7              // IeImg::botRight
#define	TAG_PRIMARYCHROMATICITIES 319	// CIE 1931 primary chromaticities 
					// xr, yr, xg, yg, xb, yb [Real32*]
#define TAG_REFERENCEBLACKWHITE 532	// reference black and white
					// br, wr, bg, wg, bb, wb [Real32*]
#define	TAG_RESOLUTIONUNIT 296		// units of resolutions [enum]
#define	    RESUNIT_NONE 1		   // no meaningful units
#define	    RESUNIT_INCH 2		   // english
#define	    RESUNIT_CENTIMETER 3	   // metric (default)
#define	TAG_SOFTWARE 305		// name/version of creating s/w [char*]
#define	TAG_THRESHHOLDING 263		// thresholding used on data [enum]
#define	    THRESHHOLD_BILEVEL 1	   // b&w art scan (default)
#define	    THRESHHOLD_HALFTONE 2	   // dithered scan
#define	    THRESHHOLD_ERRORDIFFUSE 3	   // usually Floyd-Steinberg
#define TAG_TRANSFERFUNCTION 301	// transfer func (gamma) tbls [UInt16*]
#define TAG_TRANSFERRANGE 342		// transfer function min/max [UInt16*]
#define	TAG_WHITEPOINT 318		// CIE 1931 white point x,y [Real32*]
#define TAG_XASPECT IEX+507 		// aspect ratio, horiz value [UInt]
#define	TAG_XRESOLUTION 282		// horiz pixel resolution [Real]
#define TAG_YASPECT IEX+508 		// aspect ratio, vert value [UInt]
#define	TAG_YRESOLUTION	283		// vert pixel resolution [Real]
#define TAG_TRANSPINDEX IEX+511         // index of transparent pixel
#define TAG_QUALITY     IEX+512         // "quality" of lossy codecs (0-100)
#define TAG_ACCURACY    IEX+513         // computational accuracy for JPEG
#define TAG_BACKGINDEX  IEX+514         // palette index of background color
#define TAG_GAMMA       IEX+517         // gamma of image [Real32*]
                                        // decoding (0,1) lower accuracy gives
                                        // faster decoding
#define TAG_PNGCOMPRESS     IEX+515     // PNG speed/compress ratio setting
#define     PNGCOMPRESS_BEST_SPEED 0        // fastest/poorest compression
#define     PNGCOMPRESS_BEST_COMPRESS 1     // slowest/ best compression
#define     PNGCOMPRESS_DEFAULT_COMPRESS 2  // not too fast/not too poor
#define TAG_PNGFILTER       IEX+516     // PNG predictor filter method
#define     PNGFILTER_NO_FILTERING 0        // no prediction filtering
#define     PNGFILTER_SUB 1                 // horizontal differencing
#define     PNGFILTER_UP 2                  // vertical differencing
#define     PNGFILTER_AVERAGE 3             // 2 pixel (h,v) averaging
#define     PNGFILTER_PAETH 4               // linear function of 3 adjacent
                                            // pixels (left,above,aboveleft)
#define     PNGFILTER_DEFAULT_FILTERING 100 // tries all filters on each row
#define TAG_PROGRESSIVE 343             // for JPEG 6 progressive JPEG


/*** NOT FOR PUBLIC USE ***/
// These attributes are for internal use only and are of limited interest to
// the API and extension modules

#define	TAG_SUBFILETYPE 254		// subfile data descriptor
#define	    FILETYPE_REDUCEDIMAGE 0x1	// reduced resolution version
#define	    FILETYPE_PAGE 0x2		// one page of many
#define	    FILETYPE_MASK 0x4		// transparency mask
#define	    COMPRESSION_NONE 1		   // dump mode
#define	    COMPRESSION_CCITTRLE 2	   // CCITT modified Huffman RLE
#define	    COMPRESSION_CCITTFAX3 3	   // CCITT Group 3 fax encoding
#define	    COMPRESSION_CCITTFAX4 4	   // CCITT Group 4 fax encoding
#define	    COMPRESSION_LZW 5		   // Lempel-Ziv  & Welch
#define	    COMPRESSION_NEXT 32766	   // NeXT 2-bit RLE
#define	    COMPRESSION_CCITTRLEW 32771	   // #1 w/ word alignment
#define	    COMPRESSION_PACKBITS 32773	   // Macintosh RLE
#define	    COMPRESSION_THUNDERSCAN 32809  // ThunderScan RLE
#define	    COMPRESSION_PICIO 32900	   // old Pixar picio RLE
#define	    COMPRESSION_SGIRLE 32901	   // Silicon Graphics RLE
#define	    PHOTOMETRIC_MASK 4		   // holdout mask
#define	    PHOTOMETRIC_DEPTH 32768	   // z-depth data
#define	TAG_FILLORDER 266		// data order within a byte
#define	    FILLORDER_MSB2LSB 1		   // MSB to LSB
#define	    FILLORDER_LSB2MSB 2		   // LSB to MSB
#define	TAG_CHUNKOFFSETS 273		// offsets to data strips
#define	TAG_PLANARCONFIG 284		// storage organization
#define	    PLANARCONFIG_CONTIG 1	   // single image plane
#define	    PLANARCONFIG_SEPARATE 2	   // separate planes of data
#define	TAG_FREEOFFSETS 288		// +byte offset to free block
#define	TAG_FREEBYTECOUNTS 289		// +sizes of free blocks
#define	TAG_GROUP3OPTIONS 292		// 32 flag bits
#define	    GROUP3OPT_2DENCODING 0x1	   // 2-dimensional coding
#define	    GROUP3OPT_UNCOMPRESSED 0x2	   // data not encodeed
#define	    GROUP3OPT_FILLBITS 0x4	   // fill to byte boundary
#define	TAG_GROUP4OPTIONS 293		// 32 flag bits
#define	    GROUP4OPT_UNCOMPRESSED 0x2	   // data not encodeed
#define	TAG_PREDICTOR 317		// prediction scheme w/ LZW
#define	TAG_BADFAXLINES 326		// lines w/ wrong pixel count
#define	TAG_CLEANFAXDATA 327		// regenerated line info
#define	     CLEANFAXDATA_CLEAN 0	   // no errors detected
#define	     CLEANFAXDATA_REGENERATED 1	   // receiver regenerated lines
#define	     CLEANFAXDATA_UNCLEAN 2	   // uncorrected errors exist
#define	TAG_CONSECUTIVEBADFAXLINES 328	// max consecutive bad lines
#define	TAG_MATTEING 32995		// alpha channel present (SGI-private)
#define	TAG_PALETTECONFIG IEX+284	// palette storage organization
#define     PALETTECONFIG_CONTIG 1	   // interleaved palette
#define	    PALETTECONFIG_SEPARATE 2	   // separate palette planes
#define	TAG_PALETTEORDER IEX+266	// palette color order
#define	TAG_PALETTEBITSPP IEX+258	// palette bits per channel (sample)
#define TAG_CHUNKFORMAT IEX+500 	// tile format
enum IeChunkFormat { IE_CF_ALL_SAME, IE_CF_EDGE_PACK, IE_CF_ALL_VARY };
#define	TAG_COLORORDER IEX+501		// color order
#define     COLORORDER_RGB 1		   // red-green-blue
#define	    COLORORDER_BGR 2		   // blue-green-red
#define TAG_UNCDATAWIDTH IEX+504 	// byte width of uncompressed data
#define TAG_MAXTHUMBWIDTH  IEX+510      // upper bound on thumbnail width
#define TAG_USINGIEDECODER  IEX+518     // depends on IE supplied decoder
#define TAG_TILESUPPORT IEX+519         // writer supports tiled images
#define TAG_STRIPSUPPORT IEX+520        // writer supports stripped images
#define TAG_NOCONTIGSUPPORT IEX+521     // writer doesn't do contiguous images
#define TAG_VALIDCOMPRESSION IEX+522    // writer supports these compression
                                        // schemes with current pixTyp

#ifdef getWord
#undef getWord
#endif
#ifdef getDWord
#undef getDWord
#endif
#ifdef putWord
#undef putWord
#endif
#ifdef putDWord
#undef putDWord
#endif

#if defined(CS_BIG_ENDIAN)
#define getWord(buf,n) ( buf[n] | (buf[n+1]<<8) )
#define getDWord(buf,n) ( getWord(buf,n) | (getWord(buf,n+2)<<16) )
#define putWord(item,buf,n) (buf[n]=(UInt8)item, buf[n+1]=(UInt8)((item)>>8))
#define putDWord(item,buf,n) (putWord(item,buf,n),putWord((item)>>16,buf,n+2))
#else
#define getWord(buf,n) (*(UInt16*)(buf+n)) 
#define getDWord(buf,n) (*(UInt32*)(buf+n)) 
#define putWord(item,buf,n) (*(UInt16*)(buf+n)=item)
#define putDWord(item,buf,n) (*(UInt32*)(buf+n)=item)
#endif

#ifdef ReadOK
#undef ReadOK
#endif
#define ReadOK(buf, size) (pFio->imageReadFile(buf, size) == size)

#ifdef WriteOK
#undef WriteOK
#endif
#define WriteOK(buf, size) (pFio->imageWriteFile(buf, size) == size)

#ifdef SeekOK
#undef SeekOK
#endif
#define	SeekOK(dist) (pFio->imageSeekFile(dist,IE_SEEK_SET) == dist)

/*
 * Copyright (c) 1988, 1990 by Sam Leffler.
 * All rights reserved.
 *
 * This file is provided for unrestricted use provided that this
 * legend is included on all tape media and as a part of the
 * software program in whole or part.  Users may copy, modify or
 * distribute this file at will.
 */

#endif /* _ieapidef_h */
