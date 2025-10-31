//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2005-2011  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

/// <summary>
/// A container for various statistics describing the data used to render an
/// image.
/// </summary>
struct AcGsRenderStatistics
{
public:
    /// <summary>
    /// The time it took to render the image, in seconds.
    /// </summary>
    float fRenderTime;
  
    /// <summary>
    /// The amount of memory in KB used by the renderer.
    /// </summary>
    size_t iMemory;

    /// <summary>
    /// The number of materials used to render the image.
    /// </summary>
    size_t iMaterialCount;

    /// <summary>
    /// The number of lights used to render the image.
    /// </summary>
    size_t iLightCount;

    /// <summary>
    /// The number of triangles used to render the image.
    /// </summary>
    size_t iTriangleCount;
};

#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning
/// <summary>
/// An interface implemented by a client of the AcGsView.RenderToImage function
/// to get progress reports during the rendering process.
/// </summary>
class AcGsRenderProgressMonitor
{
public:
    /// <summary>
    /// The phases of the rendering process.  They are listed in sequential
    /// order from the first phase of rendering to the last phase.
    /// </summary>
    enum Phase
    {
        /// <summary>
        /// The scene translation phase, where AutoCAD entities are converted
        /// into a format suitable for rendering.
        /// </summary>
        kTranslation,

        /// <summary>
        /// The photon emission phase, which runs if global illumination is
        /// active in the render settings.
        /// </summary>
        kPhotonEmission,

        /// <summary>
        /// The final gathering phase, if final gathering is active in the
        /// render settings.
        /// </summary>
        kFinalGather,

        /// <summary>
        /// The normal rendering phase, which always happens.  Preview image
        /// tiles are generated during this phase only.
        /// </summary>
        kRender
    };

    /// <summary>
    /// Called during the AcGsView.RenderToImage() call to report the current
    /// percentage complete for the current phase of rendering.
    /// </summary>
    ///
    /// <param name="ePhase">
    /// The phase of rendering for which progress is being reported.
    /// </param>
    ///
    /// <param name="fProgress">
    /// The percentage complete for the current rendering phase, as a floating-
    /// point number between 0.0 and 100.0.
    /// </param>
    ///
    /// <returns>
    /// The implementation should return false to continue rendering and true
    /// to abort rendering.  The call to AcGsView.RenderToImage() will complete
    /// shortly after rendering is aborted.
    /// </returns>
    ///
    /// <remarks>
    /// The implementation can use calls to this function to update a progress
    /// indicator.  It is called at least once per second during rendering.
    /// </remarks>
    virtual bool OnProgress(Phase ePhase, float fProgress) = 0;

    /// <summary>
    /// Called during the AcGsView.RenderToImage() call to provide preview image
    /// tiles to the implementation.
    /// </summary>
    ///
    /// <param name="x">
    /// The x-coordinate of the lower left corner of the image tile, in pixels.
    /// The lower left corner of the full image is (0,0).
    /// </param>
    ///
    /// <param name="y">
    /// The y-coordinate of the lower left corner of the image tile, in pixels.
    /// The bottom left corner of the full image is at (0,0).
    /// </param>
    ///
    /// <param name="w">
    /// The width of the image tile, in pixels.
    /// </param>
    ///
    /// <param name="h">
    /// The height of the image tile, in pixels.
    /// </param>
    ///
    /// <param name="pPixels">
    /// The image tile pixel data, as an array of bytes with four pixels per
    /// byte in BGRA order.  The size of the array is w * h * 4, and the first
    /// pixel in the array is at the bottom left corner of the image tile.
    /// </param>
    ///
    /// <remarks>
    /// This is only called during the render (kRender) phase.  The function is
    /// called twice for each tile: once before the tile is rendered to indicate
    /// the location and size of the upcoming tile (with parameter pPixels set
    /// to NULL) and again after the tile is rendered, with pixel data.  The
    /// implementation can use the first call to draw a preview bracket
    /// indicating where the tile will appear in the rendered image, and the
    /// second call to actually show the resulting tile.  It make seconds or
    /// even minutes to render each tile.  Each tile lies within the bounds of
    /// the output image.
    /// </remarks>
    virtual void OnTile(int x, int y, int w, int h, const BYTE* pPixels) = 0;

    /// <summary>
    /// Called to provide rendering statistics to the implementation for the
    /// last rendered image.
    /// </summary>
    ///
    /// <param name="pStats">
    /// A pointer to the statistics object containing information about the
    /// last rendered image.
    /// </param>
    ///
    /// <remarks>
    /// This is called after rendering is complete, and isn't called if
    /// rendering is aborted.
    /// </remarks>
    virtual void SetStatistics(const AcGsRenderStatistics* pStats) = 0;

    /// <summary>
    /// Called to determine whether the database should be reused for the next
    /// rendered image.
    /// </summary>
    ///
    /// <returns>
    /// The implementation should return true to reuse the rendering database
    /// for the next image.  If false is returned, the database is deleted.
    /// </returns>
    ///
    /// <remarks>
    /// This is called after rendering is completed, and isn't called if
    /// rendering is aborted.  This gives the implementation a chance to render
    /// the same scene without having to regenerate the rendering database,
    /// which is useful for animation where only the camera is changing.
    /// Only the camera will be updated if true is returned: all other data is
    /// reused for the next image.
    /// </remarks>
    virtual bool ShouldReuseDatabase() { return false; }
};
#pragma warning(pop) // C4265
