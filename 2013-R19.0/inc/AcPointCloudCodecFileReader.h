//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//         AcPointCloudCodecFileReader.h
//
//   Point Cloud Decimation Engine Codec File Reader class definition
//
#ifndef __ACPOINTCLOUD_CODECFILEREADER_H__
#define __ACPOINTCLOUD_CODECFILEREADER_H__

#pragma once

/// <Summary>
/// This class is the base interface for codec readers
/// </Summary>
class CodecFileReader
{
public:
    virtual ~CodecFileReader() {}

    /// <Summary>
    /// This method opens the data file
    /// </Summary>
    /// <param name="sourceFile">The raw scan file to be indexed.</param>
    ///
    /// <returns>
    /// true if file is opened and is readable.
    /// </returns>
    virtual bool open(const wchar_t* sourceFile) = 0;

    /// <Summary>
    /// This methods closes the data file
    /// </Summary>
    virtual void close() = 0;

    /// <Summary>
    /// This method gets the boundary and point number information from data file.
    /// </Summary>
    /// <param name="minPt">minPt[0], minPt[1], minPt[2] to min x, y, z of all points in the file</param>
    /// <param name="maxPt">maxPt[0], maxPt[1], maxPt[2] to max x, y, z of all points in the file</param>
    /// <param name="numPoints">The total number of the points in the file</param>
    /// <param name="flags">
    /// The flag describes the attributes which the codec reader supports from data files:
    ///     0x0001 - Color attribute
    ///     0x0002 - Intensity attribute
    ///     0x0004 - Normal value attribute
    ///     0x0008 - Classification attribute
    /// </param>
    virtual void fileStats(double* minPt, double* maxPt, unsigned long long& numPoints, unsigned int& flags) = 0;

    /// <Summary>
    /// This method reads first valid point in the file
    /// </Summary>
    /// <param name="x">The X coordinate value of the point position</param>
    /// <param name="y">The Y coordinate value of the point position</param>
    /// <param name="z">The Z coordinate value of the point position</param>
    /// <param name="red">The red value of the point color attribute, range from 0 to 255</param>
    /// <param name="green">The green value of the point color attribute, range from 0 to 255</param>
    /// <param name="blue">The blue value of the point color attribute, range from 0 to 255</param>
    /// <param name="classification">The classification attribute of the point, range from 0 to 255</param>
    /// <param name="intensity">The intensity attribute of the point, range from 0.0 to 1.0</param>
    /// <param name="nx">The X vector value of the point normal</param>
    /// <param name="ny">The Y vector value of the point normal</param>
    /// <param name="nz">The Z vector value of the point normal</param>
    ///
    /// <returns>
    /// Returns false when there are no more point.
    /// </returns>
    ///
    /// <remarks>
    ///     if point doesn't have color, set red, green, blue as 0x00.
    ///     if point isn't classified, set classification as 0x00.
    ///     if point doesn't have intensity, set intensity to 0.
    ///     if point doesn't have normal, set nx, ny, nz to 0.
    /// </remarks>
    virtual bool readFirstPoint(double& x, double& y, double& z,
        unsigned char& red, unsigned char& green, unsigned char& blue,
        unsigned char& classification, float& intensity, float& nx, float& ny, float& nz) = 0;

    /// <Summary>
    /// This method sequentially reads all the valid points in the file
    /// </Summary>
    /// <param name="x">The X coordinate value of the point position</param>
    /// <param name="y">The Y coordinate value of the point position</param>
    /// <param name="z">The Z coordinate value of the point position</param>
    /// <param name="red">The red value of the point color attribute, range from 0 to 255</param>
    /// <param name="green">The green value of the point color attribute, range from 0 to 255</param>
    /// <param name="blue">The blue value of the point color attribute, range from 0 to 255</param>
    /// <param name="classification">The classification attribute of the point, range from 0 to 255</param>
    /// <param name="intensity">The intensity attribute of the point, range from 0.0 to 1.0</param>
    /// <param name="nx">The X vector value of the point normal</param>
    /// <param name="ny">The Y vector value of the point normal</param>
    /// <param name="nz">The Z vector value of the point normal</param>
    /// <param name=""></param>
    ///
    /// <returns>
    /// Returns false when there are no more point.
    /// </returns>
    ///
    /// <remarks>
    ///     if point doesn't have color, set red, green, blue as 0x00.
    ///     if point isn't classified, set classification as 0x00.
    ///     if point doesn't have intensity, set intensity to 0.
    ///     if point doesn't have normal, set nx, ny, nz to 0.
    /// </remarks>
    virtual bool readNextPoint(double& x, double& y, double& z,
        unsigned char& red, unsigned char& green, unsigned char& blue,
        unsigned char& classification, float& intensity, float& nx, float& ny, float& nz) = 0;
};



/// <Summary>
/// This class is the base interface for codec plugin, which manages the codec readers
/// </Summary>

class IIndexerPlugin
{
public:
    /// <Summary>
    /// virtual deconstructor
    /// </Summary>
    virtual ~IIndexerPlugin() {}

    /// <Summary>
    /// This method gets the semi-colon delimited list of "codecs" (Extensions) supported by the plugin
    /// i.e. (.ptg;.ptx)
    /// </Summary>
    ///
    /// <returns>
    /// Retruns the supported "codecs" (Extensions) list, i.e. (.ptg;.ptx)
    /// </returns>
    virtual const wchar_t* getCodecs() = 0;

    /// <Summary>
    /// This method gets the reader for the specified codec.
    /// </Summary>
    /// <param name="codec">The codec name (Extension)</param>
    ///
    /// <returns>
    /// Return the pointer of the codec reader for the specifited codec
    /// </returns>
    virtual CodecFileReader* getFileReader(const wchar_t* codec) = 0;

    /// <Summary>
    /// This method checks if the specified file/codec is supported by the plugin
    /// </Summary>
    /// <param name="inputFile">The specified file / codec</param>
    ///
    /// <returns>
    /// Returns true if support.
    /// </returns>
    virtual bool canImport(const wchar_t* inputFile) = 0;

    /// <Summary>
    /// This method destroys itself and all resources when we are done with the plugin.
    /// </Summary>
    virtual void destroy() = 0;
};

/// <Summary>
/// This function should be implemented by plugin provider to return plugin implementation for the indexer
/// </Summary>
IIndexerPlugin* getIndexerPlugin();

#endif 
