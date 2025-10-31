//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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

/// <summary>
/// An interface implemented by a client of the AcGsView::renderToImage function
/// to get progress reports during the rendering process.
/// </summary>
class AcGsRenderProgressMonitor
{
public:
    virtual ~AcGsRenderProgressMonitor() { }

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
        kRender,

        /// <summary>
        /// This phase only happens when client's machine is relative low-end,
        /// and we will use tile rendering to resolve limited computer recourses.
        /// This phase is for generating tile preview for each tile before the
        /// normal rendering phase.
        /// </summary>
        kDraft,

        /// <summary>
        /// This the first stage of rendering, used for rendering initialization.
        /// </summary>
        kInitialize,
    };

    /// <summary>
    /// The status of the rendering process. 
    /// </summary>
    enum RenderingStatus
    {
        /// <summary>
        /// Current rendering process is running.
        /// </summary>
        kRendering,

        /// <summary>
        /// Current rendering process is paused.
        /// </summary>
        kPaused,

        /// <summary>
        /// Current rendering process is finished.
        /// </summary>
		kFinished,

        /// <summary>
        /// Current rendering process is canceled.
        /// </summary>
		kAborted,

		/// <summary>
		/// Won't start rendering, for current available memory does not meet rendering requirement.
		/// </summary>
		kWillNotRender,

		/// <summary>
		/// Current rendering is approaching out of memory situation, and rendering should be aborted.
		/// </summary>
		kSoftOutOfMemory,

		/// <summary>
		/// Memory allocation fails during rendering, and AutoCAD has to be restarted right now.
		/// </summary>
		kHardOutOfMemory,

        /// <summary>
        /// Current rendering process is aborted due to unknown errors.
        /// </summary>
        kError,
    };

    /// <summary>
    /// Called during the the rendering period to report the current rendering
    /// progress, which includes the rendering phase, overall rendering progress
    /// of the current phase, rendering time already spent, render level already
    /// achieved, and the progress of the current level. The last three parameters
    /// are only valid for rendering phase.
    /// </summary>
    ///
    /// <param name="ePhase">
    /// The phase of rendering for which progress is being reported.
    /// </param>
    ///
    /// <param name="fOverallProgress">
    /// The percentage complete for the current rendering phase, as a floating-
    /// point number between 0.0 and 100.0.
    /// </param>
    ///
    /// <param name="iRenderTimeSpent">
    /// The time spent on rendering, which is measured by second.
    /// </param>
    ///
    /// <param name="iCurrentRenderLevel">
    /// The render level of rendering for which progress is being reported.
    /// </param>
    ///
    /// <param name="fCurrentLevelProgress">
    /// The percentage complete for the current render level, as a floating-
    /// point number between 0.0 and 100.0.
    /// </param>
    ///
    /// <param name="iTileIndex">
    /// This parameter only be valid when tile rendering is on, used to indicating
    /// which tile is being rendered.
    /// </param>
    ///
    /// <returns>
    /// The return value is only valid when called in AcGsView::renderToImage()
    /// function. Returning false means it's informing the caller to abort the
    /// current rendering. Or else, it will return true.
    /// </returns>
    ///
    /// <remarks>
    /// The implementation can use calls to this function to update a progress
    /// indicator.  It is recommended to be called at least once per second 
    /// during rendering.
    /// </remarks>
    virtual bool OnProgress(Phase ePhase,
                            float fOverallProgress,
                            int iRenderTimeSpent,
                            int iCurrentRenderLevel,
                            float fCurrentLevelProgress,
                            int iTileIndex = 0) = 0;

    /// <summary>
    /// Called during the AcGsView::renderToImage() call to provide preview image
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
    /// Called to provide rendering status.
    /// </summary>
    ///
    /// <param name="status">
    /// Status of current rendering process.
    /// </param>
    ///
    /// <remarks>
    /// This is called when status is changed.
    /// </remarks>
    virtual void OnStatusChanged(RenderingStatus status) = 0;

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

    /// <summary>
    /// Called to determine whether the monitor is still eligible to receive notifications
    /// </summary>
    /// <remarks>
    /// Can be used to terminate asynchronous rendering
    /// </remarks>
    virtual bool IsValid() { return true; }

    /// <summary>
    /// Called to determine whether the rendering process is synchronous or asynchronous
    /// </summary>
    /// <remarks>
    /// If async, renderToImage returns immediately.
    /// </remarks>
    virtual bool IsAsync() { return false; }

    /// <summary>
    /// Output image is top-down by default.
    /// Called to determine whether the image should be bottom-up instead.
    /// </summary>
    virtual bool IsOutputImageFlipped() { return false; }
};
