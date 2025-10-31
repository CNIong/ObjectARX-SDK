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
#ifndef OFFSET_H
#include "Offset.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif
#ifndef IMAGEFILTER_H
#include "ImageFilter.h"
#endif
#ifndef DATABUFFER_H
#include "DataBuffer.h"
#endif
#ifndef IMAGE_H
#include "Image.h"
#endif
#ifndef POINT2D_H
#include "Point2d.h"
#endif
#ifndef VECTOR2D_H
#include "Vector2d.h"
#endif
#ifndef MATRIX2D_H
#include "Matrix2d.h"
#endif
#ifndef BOUNDINGBOX_H
#include "BoundingBox.h"
#endif

#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#ifndef PIXELCOPIER_H
namespace Atil { class PixelCopier; }
#endif
namespace Atil {

/// <summary>
/// This method is used to construct a new scaling filter. The scaling filter uses
/// an integral nearest neighbor pixel multiplication like method to resample the data. 
/// </summary>
/// 
/// <param name="pInput">A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the row data to be scaled.
/// </param>
/// 
/// <param name="output">A constant reference to a <c>Size</c> instance that dictates the
/// desired output size (in pixels). The difference between the input and output sizes
/// determines the needed scale factor.
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the scaled row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newScaleFilter ( RowProviderInterface* pInput,
    const Size& output );

/// <summary>
/// This method is used to construct a new scaling filter from an Image. The scaling 
/// will use format resolution if available and appropriate and an integral nearest neighbor
/// pixel multiplication like method to resample the data. 
/// </summary>
/// 
/// <param name="pImage">A pointer to an <c>Image</c> object that should be scaled.
/// </param>
/// 
/// <param name="szOutput">A constant reference to a <c>Size</c> instance that dictates the
/// desired output size (in pixels). The difference between the input and output sizes
/// determines the needed scale factor.
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the scaled row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newScaleFilter ( const Image* pImage,
                                                  const Size& szOutput );

/// <summary>
/// This method is used to construct a new scaling filter from an Image. The scaling 
/// will use format resolution if available and appropriate and an integral nearest neighbor
/// pixel multiplication like method to resample the data. 
/// </summary>
/// 
/// <param name="pImage">A pointer to an <c>Image</c> object that should be scaled.
/// </param>
/// 
/// <param name="size">The size of the sub-region of the image to be read which may
/// be up to the full size of the image. 
/// </param>
///
/// <param name="offset">The pixel offset from the upper left corner of the image
/// to begin reading the requested <c>size</c> region.
/// </param>
/// 
/// <param name="szOutput">A constant reference to a <c>Size</c> instance that dictates the
/// desired output size (in pixels). The difference between the input and output sizes
/// determines the needed scale factor.
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the scaled row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newScaleFilter ( const Image* pImage,
                const Size& size, const Offset& offset, const Size& szOutput );


/// <summary>
/// This structure enclose the definition of an enum that declares the differing methods
/// of interpolation during resampling that are available with the ATIL resample filters.
/// </summary>
///
struct Resample {

    /// <summary>
    /// This enum declares the resampling methods available in ATIL's resample filter.
    /// The name of each indicates something of the method or curve that is used to 
    /// redistribute the error introduced by the resampling.
    /// </summary>
    ///
    enum FilterTypes { 
        /// <summary>
        /// This method is relatively fast, the fastest of them all, but has the
        /// crudest selection method that simply selects an approximate pixel for output.
        /// </summary>
        ///
        kNearest, 
        /// <summary>
        /// This method is slightly better than <c>kNearest</c> in that some input of 
        /// neighboring pixels is referenced in the output. It does not give the speed
        /// advantages of <c>kNearest</c> however.
        /// </summary>
        ///
        kTriangle, 
        /// <summary>
        /// This method interpolates with a biCubic method.
        /// The formula applied is <c>f(t) = 2|t|^3 - 3|t|^2 + 1, 
        /// -1 [less than or equal to] t [less than or equal to] 1</c>
        /// </summary>
        ///
        kCubic, 
        /// <summary>
        /// This method interpolates similarly to the <c>kTriangle</c>, but with a 
        /// a wider curve distributing the influence. This can be a good compromise between
        /// interpolation quality and speed. 
        /// </summary>
        ///
        kBell, 
        /// <summary>
        /// This method is the most computationally expensive of all the resamplers.
        /// It can have a blurring effect of the data and introduce some artifacts. It
        /// can be effective for some classes of imagery, but it not widely used.
        /// It is a differing form of the <c>kCubic</c> method.
        /// </summary>
        ///
        kBSpline, 
        /// <summary>
        /// This method is based on the "sinc" values. It is effective in some images
        /// but can introduce artifacts. Not as computationally as expensive as <c>kBSpline</c>
        /// it use of the geometric function "sin" limits its performance.
        /// </summary>
        ///
        kLanczos3, 
        /// <summary>
        /// This method gives output that is not as fuzzy as <c>kBSpline</c> and considerably
        /// smoother than <c>kNearest</c> without the computation expense. It is a cubic form
        /// that is a blend between <c>kBSpline</c> and <c>kCubic</c> and is a reasonable
        /// choice where the type of data being sampled is not known in advance.
        /// </summary>
        ///
        kMitchell, 
        /// <summary>
        /// This method is for binary images. It is a modified Bell resampling that simply
        /// scales the curve of the bell higher giving an output intensity promotion.
        /// </summary>
        ///
        kBellBinary
    };
};
/// <summary>
/// This method is used to construct a new resampling filter. The resample filter uses
/// one of the <c>FilterTypes</c> methods to resample the data. 
/// </summary>
/// 
/// <param name="pImage">A pointer to a <c>Image</c> derived object that
/// will provide the source data to be resampled.
/// </param>
/// 
/// <param name="size">The size of the sub-region of the image to be read which may
/// be up to the full size of the image. 
/// </param>
///
/// <param name="offset">The pixel offset from the upper left corner of the image
/// to begin reading the requested <c>size</c> region.
/// </param>
/// 
/// <param name="filterMethod">An instance of the <c>FilterTypes</c> enum that indicates 
/// the resampling method to be used.
/// </param>
///
/// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
/// sampling method for a small percentage of the total scale to produce faster output with
/// little loss of image fidelity.
/// </param>
///
/// <param name="bProcessAlpa">A boolean that if true then color promotion to RGBA 
/// may occur to preserve the locality of alpha transparency as pixel colors will be altered.
/// </param>
///
/// <param name="output">A constant reference to a <c>Size</c> instance that dictates the
/// desired output size (in pixels). The difference between the input and output sizes
/// determines the needed scale factor.
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the resampled row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newResampleFilter ( const Image* pImage
    , const Size& size, const Offset& offset, Resample::FilterTypes filterMethod
    , bool bAdaptive, bool bProcessAlpha, const Size& szOutput );

/// <summary>
/// This method is used to construct a new resampling filter. The resample filter uses
/// one of the <c>FilterTypes</c> methods to resample the data. 
/// </summary>
/// 
/// <param name="pInput">A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the row data to be resampled.
/// </param>
/// 
/// <param name="output">A constant reference to a <c>Size</c> instance that dictates the
/// desired output size (in pixels). The difference between the input and output sizes
/// determines the needed scale factor.
/// </param>
///
/// <param name="filterMethod">An instance of the <c>FilterTypes</c> enum that indicates 
/// the resampling method to be used.
/// </param>
///
/// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
/// sampling method for a small percentage of the total scale to produce faster output with
/// little loss of image fidelity.
/// </param>
///
/// <param name="bProcessAlpa">A boolean that if true then color promotion to RGBA 
/// may occur to preserve the locality of alpha transparency as pixel colors will be altered.
/// </param>
///
/// <param name="bReturnRaw">If true this will disable the conversion of non-displayable
/// data type types into RGB for processing. This is desirable when resampling "data" images
/// like DEMs for output (saving).
/// </param>
///
/// <param name="pVoidPixel">An <c>ImagePixel</c> pointer that may have a special value
/// to be used for "slack" areas of output caused by rotation or clipping.
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the resampled row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newResampleFilter ( RowProviderInterface* pInput
    , const Size& output, Resample::FilterTypes filterMethod
    , bool bAdaptive = false, bool bProcessAlpha = false, bool bReturnRaw = false
    , ImagePixel const* pVoidPixel = NULL);

/// <summary>
/// This structure enclose the definition of an enum that declares the differing methods
/// of shearing that are available with the ATIL shear filters.
/// </summary>
///
struct Shear {
    /// <summary>
    /// This enum declares the methods available in ATIL's shear filter.
    /// </summary>
    ///
    enum Quality {
        /// <summary>
        /// The data will be interpolated to better represent a true output
        /// intensity when the data is shift a non-integral number of pixels.
        /// </summary>
        ///
        kInterpolate,

        /// <summary>
        /// The data shift will be rounded to an integral number of pixels.
        /// </summary>
        ///
        kRound
    };
};

/// <summary>
/// This method will create a x shear filter.
/// </summary>
///
/// <param name="pInput">A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the row data to be sheared.
/// </param>
/// 
/// <param name="dXShear">A const double reference with the shear factor to be applied.
/// </param>
///
/// <param name="clearColor">An <c>ImagePixel</c> that holds the color to be used to 
/// fill "slack" areas left by the shearing.
/// </param>
///
/// <param name="quality">An instance of the <c>Shear::Quality</c> enum indicating
/// the shearing method to be used.
/// </param>
///
/// <param name="bProcessAlpa">A boolean that if true then color promotion to RGBA 
/// may occur to preserve the locality of alpha transparency as pixel colors will be altered.
/// </param>
///
/// <param name="bReturnRaw">If true this will disable the conversion of non-displayable
/// data type types into RGB for processing. This is desirable when resampling "data" images
/// like DEMs for output (saving).
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the sheared row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newXShearFilter ( RowProviderInterface* pInput,
    const double& dXShear, ImagePixel clearColor, Shear::Quality quality,
    bool bProcessAlpha = false , bool bReturnRaw = false );

/// <summary>
/// This method will create a y shear filter.
/// </summary>
///
/// <param name="pInput">A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the row data to be sheared.
/// </param>
/// 
/// <param name="dYShear">A const double reference with the shear factor to be applied.
/// </param>
///
/// <param name="clearColor">An <c>ImagePixel</c> that holds the color to be used to 
/// fill "slack" areas left by the shearing.
/// </param>
///
/// <param name="quality">An instance of the <c>Shear::Quality</c> enum indicating
/// the shearing method to be used.
/// </param>
///
/// <param name="bProcessAlpa">A boolean that if true then color promotion to RGBA 
/// may occur to preserve the locality of alpha transparency as pixel colors will be altered.
/// </param>
///
/// <param name="bReturnRaw">If true this will disable the conversion of non-displayable
/// data type types into RGB for processing. This is desirable when resampling "data" images
/// like DEMs for output (saving).
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the sheared row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newYShearFilter ( RowProviderInterface* pInput,
    const double& dYShear, ImagePixel clearColor, Shear::Quality quality,
    bool bProcessAlpha = false , bool bReturnRaw = false );

/// <summary>
/// This method will create a rotation filter.
/// </summary>
///
/// <param name="pInput">A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the row data to be rotated.
/// </param>
/// 
/// <param name="dAngle">A const double reference with the rotation angle
/// in radians to be applied.
/// </param>
///
/// <param name="clearColor">An <c>ImagePixel</c> that holds the color to be used to 
/// fill "slack" areas left by the rotation.
/// </param>
///
/// <param name="method">An instance of the <c>Shear::Quality</c> enum indicating
/// the shearing method to be used.
/// </param>
///
/// <param name="bProcessAlpa">A boolean that if true then color promotion to RGBA 
/// may occur to preserve the locality of alpha transparency as pixel colors will be altered.
/// </param>
///
/// <param name="bReturnRaw">If true this will disable the conversion of non-displayable
/// data type types into RGB for processing. This is desirable when resampling "data" images
/// like DEMs for output (saving).
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the rotated row data.
/// </returns>
///
RowProviderInterface* ATIL_EXPORT newRotateFilter ( RowProviderInterface* pInput,
    const double& dAngle, ImagePixel clearColor, Shear::Quality method,
    bool bProcessAlpha = false, bool bReturnRaw = false );


/// <summary>
/// ImageView makes rotating and scaling an image for viewing relatively easy. 
/// The placement of the associated image in the output space is determined by a set of vectors
/// and a point of origin. The vectors describe the progress and length of the image row and 
/// column axis with respect to the output rectangle.
/// </summary>
/// 
/// <remarks>
/// If the vectors are half the length of the size of the number of rows or columns in the image
/// and are rotated by 45 degrees, then the image will be scaled to fit the length of the vectors and 
/// rotated and offset to the point of origin.
/// </remarks>
/// 
class ImageView
{
public:
    /// <summary>
    /// This enum defines the methods that can be used to rotating data. 
    /// </summary>
    enum RotationMethod { 
        /// <summary>
        /// This method preserves the overall intensity of the row data as it is rotated.
        /// It is the recommended method of rotation as it will often give the best result.
        /// </summary>
        /// 
        kInterpolated, 
        /// <summary>
        /// This method takes the color of the nearest pixel and does not preserve 
        /// the image integrity as well. It is the recommended method of rotation as
        /// it will often give the best result.
        /// </summary>
        /// 
        kNearestNeighbor 
    };

public:

    /// <summary>
    /// An initializing constructor that binds the class to the image data to be transformed.
    /// </summary>
    ///
    /// <param name="image">A reference to an instance of the <c>Image</c> class that
    /// will be viewed.
    /// </param>
    /// 
    /// <param name="output">The size of the view to output.
    /// </param>
    ///
    /// <remarks>
    /// The output argument specifies the size of the window in which the image will be 
    /// viewed as well as the size of the image that will be output.
    /// </remarks>
    ///
    ImageView ( const Image& image, const Size& output );

    /// <summary>
    /// An initializing constructor. This constructor can be used in testing 
    /// a view parameters.
    /// </summary>
    ///
    /// <param name="input"> The size of the "input" area to be considered. 
    /// </param>
    /// 
    /// <param name="clearColor">An <c>ImagePixel</c> that holds the color to be used to 
    /// fill "slack" areas.
    /// </param>
    ///
    /// <param name="output">The size of the view to output.
    /// </param>
    ///
    /// <remarks>
    /// The output argument specifies the size of the window in which the image will be 
    /// viewed as well as the size of the image that will be output.
    /// </remarks>
    ///
    ImageView ( const Size& input, ImagePixel clearColor, const Size& output );

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~ImageView ();

    /// <summary>
    /// The output method for ImageView. This method will return the transformed data.
    /// </summary>
    ///
    /// <param name="filter">An instance of the <c>FilterTypes</c> enum that indicates 
    /// the resampling method to be used.
    /// </param>
    ///
    /// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
    /// sampling method for a small percentage of the total scale to produce faster output with
    /// little loss of image fidelity.
    /// </param>
    ///
    /// <param name="rotate">An instance of the <c>RotationMethod</c> enum indicating the 
    /// rotation method to use.
    /// </param>
    ///
    /// <returns>
    /// A pointer to a <c>RowProviderInterface</c> derived object that
    /// will provide the transformed data. The viewed rectangle (in output coords) is defined to be from 0,0 to output size.
    /// </returns>
    ///
    /// <exception cref="ImageException">This method will through exceptions if the
    /// transform selects no image data or if the color selected to be the clear color
    /// does not conform to the image being transformed.
    /// </exception>
    ///
    RowProviderInterface* getViewedImageData (
        Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
        RotationMethod rotate = kInterpolated );

    /// <summary>
    /// An output method for ImageView. This method will transform data provided by
    /// a <c>RowProviderInterface</c>. Using the <c>RowProviderInterface</c> input imposes
    /// the requirement that the getInputOrienataion method must have been called
    /// so that the data being input is in the correct orientation for rotation to take place. 
    /// </summary>
    ///
    /// <param name="pInput">A <c>RowProviderInterface</c> pointer that will provide
    /// the data to be transformed.
    /// </param>
    ///
    /// <param name="filter">An instance of the <c>FilterTypes</c> enum that indicates 
    /// the resampling method to be used.
    /// </param>
    ///
    /// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
    /// sampling method for a small percentage of the total scale to produce faster output with
    /// little loss of image fidelity.
    /// </param>
    ///
    /// <param name="rotate">An instance of the <c>RotationMethod</c> enum indicating the 
    /// rotation method to use.
    /// </param>
    ///
    /// <returns>
    /// A pointer to a <c>RowProviderInterface</c> derived object that
    /// will provide the transformed data. The viewed rectangle (in output coords) is defined to be from 0,0 to output size.
    /// </returns>
    ///
    /// <exception cref="ImageException">This method will through exceptions if the
    /// transform selects no image data or if the color selected to be the clear color
    /// does not conform to the image being transformed.
    /// </exception>
    ///
    RowProviderInterface* getViewedImageData ( RowProviderInterface* pInput,
        Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
        RotationMethod rotate = kInterpolated );

    /// <summary>
    /// This method returns the size of the configured output which is the viewed
    /// area in the output image coordinate system.
    /// </summary>
    ///
    const Size& output ( ) const;
    
    /// <summary>
    /// This method returns the origin of the image in the output space.
    /// </summary>
    ///
    Point2d origin () const;

    /// <summary>
    /// This method returns the rotation of the image in output space.
    /// </summary>
    ///
    double rotation ( ) const;

    /// <summary>
    /// This method returns the x axis vector that corresponds to the horizontal
    /// axis of the input image as it relates to the output space.
    /// </summary>
    ///
    Vector2d xAxis ( ) const;

    /// <summary>
    /// This method returns the y axis vector that corresponds to the vertical
    /// axis of the input image as it relates to the output space.
    /// </summary>
    ///
    Vector2d yAxis ( ) const;

    /// <summary>
    /// This method returns the color that will be used to fill in any image 
    /// any "slack space" created by rotating the image.
    /// </summary>
    ///
    ImagePixel fillColor () const;

    /// <summary>
    /// This method returns a bool indicating whether or not 
    /// transparency will be respected.
    /// </summary>
    ///
    bool transparency () const;

    /// <summary>
    /// This method returns a bool indicating whether or not raw 
    /// data will be returned.
    /// </summary>
    ///
    bool returnRawData () const;

    /// <summary>
    /// This method will set the rotation of the image with respect to the output rectangle.
    /// </summary>
    ///
    /// <param name="dRads">A constant double reference to the angle to rotate through
    /// specified in radians.
    /// </param>
    ///
    void setRotation ( const double& dRads );

    /// <summary>
    /// This method will set the rotation of the image with respect to the output rectangle.
    /// It will only rotate in 90 degree increments.
    /// </summary>
    ///
    /// <param name="n90DegreeIncrements">An integer that indicates the number of 90 increments
    /// to rotate the data through.
    /// </param>
    ///
    void setRotation ( int n90DegreeIncrements );

    /// <summary>
    /// This method will rotate the image from its current position through
    /// an additional angle.
    /// </summary>
    ///
    /// <param name="dRads">A constant double reference to the angle to rotate through
    /// specified in radians.
    /// </param>
    ///
    void rotateBy ( const double& dRads );

    /// <summary>
    /// This method will rotate the image from its current position through
    /// an additional angle. It will only rotate in 90 degree increments.
    /// </summary>
    ///
    /// <param name="n90DegreeIncrements">An integer that indicates the number of 90 increments
    /// to rotate the data through.
    /// </param>
    ///
    void rotateBy ( int n90DegreeIncrements );

    /// <summary>
    /// This method sets the color that should be used to fill areas that are
    /// created by the rotation or clipping of the image.
    /// </summary>
    ///
    /// <param name="color">An <c>ImagePixel</c> that holds the color to be used to 
    /// fill "slack" areas left by the shearing.
    /// </param>
    ///
    void setFillColor ( ImagePixel color );

    /// <summary>
    /// This method is used to turn on or off respect for transparency in the input.
    /// </summary>
    ///
    /// <param name="bTurnOn">A bool that will set the transparency respect flag.
    /// </param>
    ///
    void setTransparency ( bool bTurnOn );

    /// <summary>
    /// This method is used to turn on or off the transformation of data from the original
    /// type to a displayable RGB type.
    /// </summary>
    ///
    /// <param name="bReturnRaw">A bool that will set the return original data type respect flag.
    /// </param>
    ///
    /// <remarks>
    /// By default, the return from getViewedImageData() will be in a displayable format.
    /// To skip the displayable conversion, pass true to this method.
    /// </remarks>
    ///
    void setReturnRawData ( bool bReturnRaw );

    /// <summary>
    /// This method sets the size of the image with in the rectangle of the output.
    /// </summary>
    /// 
    /// <param name="dXLength">A constant double reference that specifies the desired length
    /// of the x axis of the image in image pixels.
    /// </param>
    /// 
    /// <param name="dYLength">A constant double reference that specifies the desired length
    /// of the y axis of the image in image pixels.
    /// </param>
    ///
    void setSize ( const double& dXLength, const double& dYLength );

    /// <summary>
    /// This method will apply a scale factor to the current size of the image in the view.
    /// </summary>
    /// 
    /// <param name="dScale">A constant double reference that specifies the desired scale
    /// factor to apply to the image.
    /// </param>
    /// 
    void scaleBy ( const double& dScale );

    /// <summary>
    /// This method will position the image in the output space by the input amount.
    /// </summary>
    ///
    /// <param name="origin">A constant reference to a <c>Point2d</c> instance that specifies
    /// the desired origin of the image in the view.
    /// </param>
    ///
    void moveTo ( const Point2d& origin );

    /// <summary>
    /// This image will translate the position the of image in the output space
    /// by the input amount.
    /// </summary>
    ///
    /// <param name="dPanX">A constant double reference that specifies the desired 
    /// distance to offset the image in the x.
    /// </param>
    ///
    /// <param name="dPanY">A constant double reference that specifies the desired 
    /// distance to offset the image in the y.
    /// </param>
    ///
    void moveBy ( const double& dPanX, const double& dPanY );

    /// <summary>
    /// This method will place the image within the view output rectangle.
    /// It is the recommended method for setting viewing parameters.
    /// </summary>
    ///
    /// <param name="origin">A constant reference to a <c>Point2d</c> instance that specifies
    /// the desired origin of the image in the view.
    /// </param>
    ///
    /// <param name="xAxis">A constant reference to a <c>Vector2d</c> instance that specifies
    /// the size and angle of the image x axis in the view.
    /// </param>
    ///
    /// <param name="yAxis">A constant reference to a <c>Vector2d</c> instance that specifies
    /// the size and angle of the image y axis in the view.
    /// </param>
    ///
    void setByVectors ( const Point2d& origin, const Vector2d& xAxis,
        const Vector2d& yAxis );

    /// <summary>
    /// This method sets the size and offset of an area of the image to draw in the view.
    /// It can be used for clipping or pre-clipping an image to a subset within
    /// the output view. The size and offset are in image coordinates.
    /// </summary>
    /// 
    /// <param name="size">A const reference to a <c>Size</c> instance that contains
    /// the size of the rectangle.
    /// </param>
    ///
    /// <param name="offset">A const reference to a <c>Offset</c> instance that is
    /// the origin of the rectangle.
    /// </param>
    ///
    /// <remarks>
    /// The region of interest is specified in untransformed image coordinates. This setting
    /// effectively masks the area outside of the specified box in the image from being drawn
    /// through the transform.
    /// </remarks>
    ///
    void setRegionOfInterest ( const Size& size, const Offset& offset );

    /// <summary>
    /// This method returns the size and offset of the oriented image in the output rectangle. 
    /// </summary>
    /// 
    /// <param name="size">A reference to a <c>Size</c> instance that will be set to
    /// the size of the rectangle containing the image within the view output.
    /// </param>
    ///
    /// <param name="offset">A reference to a <c>Offset</c> instance that will be set to
    /// the origin of the rectangle containing the image within the view output.
    /// </param>
    ///
    /// <returns>
    /// This method will return if some part of the image is within the view output.
    /// </returns>
    ///
    bool imageInView ( Size& size, Offset& offset );

    /// <summary>
    /// This method can be used to transform a point as the image will be transformed.
    /// </summary>
    ///
    /// <param name="imageOffset">A constant reference to a <c>Point2d</c> instance 
    /// that specifies the point to be transformed.
    /// </param>
    ///
    /// <returns>
    /// This method returns a <c>Point2d</c> contains the result of the transformation.
    /// </returns>
    ///
    Point2d transform ( Point2d imageOffset ) const;

    /// <summary>
    /// This method will return the matrix created by ImageView according to the
    /// origin and vectors that have been set. 
    /// </summary>
    ///
    /// <returns>
    /// This method returns an instance of the <c>Matrix2d</c> class that has been set
    /// the transformation used by the view.
    /// </returns>
    ///
    Matrix2d getTransformation () const;

    /// <summary>
    /// This method returns the orientation that the data if pipeline input is used
    /// needs to be supplied in.
    /// </summary>
    ///
    /// <param name="origin">A reference to a <c>Offset</c> instance that will be set to
    /// the origin to be read from the image.
    /// </param>
    ///
    /// <param name="size">A reference to a <c>Size</c> instance that will be set to
    /// the size of the rectangle to be read from the image.
    /// </param>
    ///
    /// <param name="orientation">An instance of the <c>Orientation</c> enum dictating
    /// the orientation that the date should be read from the image.
    /// </param>
    ///
    /// <returns>
    /// This method returns a bool that will be true if the transformation is valid.
    /// </returns>
    ///
    /// <remarks>
    /// This method is used to get the parameters needed for the read from the image
    /// to be properly set up for the <c>RowProviderInterface</c> based version of 
    /// <c>getViewedImageData</c>.
    /// </remarks>
    ///
    bool getInputandOrientation (Offset& origin, Size& size,
        Atil::Orientation& orientation) const;

// ---------------------------  Binary compatibility line ---------------------------

    /// <summary>
    /// The output method for ImageView. This method will return the transformed data.
    /// </summary>
    ///
    /// <param name="voidPixel">An <c>ImagePixel</c> that holds the void pixel value to be used to 
    /// tell resamplers which pixel is void. 
    /// </param>
    ///
    /// <param name="filter">An instance of the <c>FilterTypes</c> enum that indicates 
    /// the resampling method to be used.
    /// </param>
    ///
    /// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
    /// sampling method for a small percentage of the total scale to produce faster output with
    /// little loss of image fidelity.
    /// </param>
    ///
    /// <param name="rotate">An instance of the <c>RotationMethod</c> enum indicating the 
    /// rotation method to use.
    /// </param>
    ///
    /// <returns>
    /// A pointer to a <c>RowProviderInterface</c> derived object that
    /// will provide the transformed data. The viewed rectangle (in output coords) is defined to be from 0,0 to output size.
    /// </returns>
    ///
    /// <exception cref="ImageException">This method will through exceptions if the
    /// transform selects no image data or if the color selected to be the clear color
    /// does not conform to the image being transformed.
    /// </exception>
    ///
    RowProviderInterface* getViewedImageData ( ImagePixel voidPixel,
        Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
        RotationMethod rotate = kInterpolated );

    /// <summary>
    /// An output method for ImageView. This method will transform data provided by
    /// a <c>RowProviderInterface</c>. Using the <c>RowProviderInterface</c> input imposes
    /// the requirement that the getInputOrienataion method must have been called
    /// so that the data being input is in the correct orientation for rotation to take place. 
    /// </summary>
    ///
    /// <param name="pInput">A <c>RowProviderInterface</c> pointer that will provide
    /// the data to be transformed.
    /// </param>
    ///
    /// <param name="voidPixel">An <c>ImagePixel</c> that holds the void pixel value to be used to 
    /// tell resamplers which pixel is void. 
    /// </param>
    ///
    /// <param name="filter">An instance of the <c>FilterTypes</c> enum that indicates 
    /// the resampling method to be used.
    /// </param>
    ///
    /// <param name="bAdaptive">A boolean that if true allows the uses of the <c>kNearest</c>
    /// sampling method for a small percentage of the total scale to produce faster output with
    /// little loss of image fidelity.
    /// </param>
    ///
    /// <param name="rotate">An instance of the <c>RotationMethod</c> enum indicating the 
    /// rotation method to use.
    /// </param>
    ///
    /// <returns>
    /// A pointer to a <c>RowProviderInterface</c> derived object that
    /// will provide the transformed data. The viewed rectangle (in output coords) is defined to be from 0,0 to output size.
    /// </returns>
    ///
    /// <exception cref="ImageException">This method will through exceptions if the
    /// transform selects no image data or if the color selected to be the clear color
    /// does not conform to the image being transformed.
    /// </exception>
    ///
    RowProviderInterface* getViewedImageData ( RowProviderInterface* pInput, ImagePixel voidPixel,
        Resample::FilterTypes filter = Resample::kNearest, bool bAdaptive = false,
        RotationMethod rotate = kInterpolated );

private:
    RowProviderInterface* getViewedImageDataImp ( const ImagePixel*, Resample::FilterTypes, bool, RotationMethod );
    RowProviderInterface* getViewedImageDataImp ( RowProviderInterface*, const ImagePixel*,
        Resample::FilterTypes, bool, RotationMethod );

    BoundingBox mbbRegion;
    const Image* mpImage;
    ImagePixel mFillColor;
    Point2d mOrigin;
    Vector2d mvXAxis;
    Vector2d mvYAxis;

    Size mImageSize;
    Size mOutput;
    bool mbFillColorSet;
    bool mbTransparencyOn;
    bool mbReturnRawData;
};


/// <summary>
/// This method does a nearest neighbor transform of the image to simulate
/// the usage of the <c>ImageView</c> class. It is not recommended for general use.
/// </summary>
///
/// <param name="pSrcImage">A constant pointer to the image to be transformed.
/// </param>
/// 
/// <param name="szOutput">A constant reference to a <c>Size</c> object that specifies
/// the size of the output view rectangle.
/// </param>
/// 
/// <param name="srcOrigin">A constant reference to a <c>Point2d</c> instance that specifies
/// the desired origin of the image in the view.
/// </param>
///
/// <param name="srcUAxis">A constant reference to a <c>Vector2d</c> instance that specifies
/// the size and angle of the image x axis in the view.
/// </param>
///
/// <param name="srcVAxis">A constant reference to a <c>Vector2d</c> instance that specifies
/// the size and angle of the image y axis in the view.
/// </param>
///
/// <param name="bReturnRaw">If true this will disable the conversion of non-displayable
/// data type types into RGB for processing. This is desirable when resampling "data" images
/// like DEMs for output (saving).
/// </param>
///
/// <returns>
/// A pointer to a <c>RowProviderInterface</c> derived object that
/// will provide the transformed data.
/// </returns>
///
RowProviderInterface* applyAffine(const Image* pSrcImage, const Size& szOutput,
                                  const Point2d& srcOrigin,
                                  const Vector2d& srcUAxis, const Vector2d& srcVAxis,
                                  bool bReturnRawData);

/// <summary>
/// A static construction method to aid in pasting pipes into images
/// in a Windows DIB format (bottom up).
/// </summary>
///
/// <param name="pImage">A pointer to an instance of the <c>Image</c> class that
/// will "pasted" into.
/// </param>
/// 
/// <param name="pPipe">The <c>RowProviderInterface</c> that is the source of
/// of data.
/// </param>
///
/// <param name="at">A reference to a <c>Offset</c> instance that will be set to
/// the origin to paste into image.
/// </param>
///
/// <param name="bTransparently">A bool that will set the transparency respect flag.
/// </param>
///
/// <returns>
/// This method will return true if the operation is successful.
/// </returns>
///
bool ATIL_EXPORT bufferedImageBottomUpPaste( Image* pImage,
    RowProviderInterface* pPipe, const Offset& at, bool bTransparently = false);

}

#endif
