//
// Copyright (C) 1993-1998 by Autodesk, Inc.
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
// ief.h - IE/API filter class definitions

#ifndef    _ief_h
#define    _ief_h

//static const char sccsid[] = "@(#)ief.h 2.3 (95/06/02 14:31:35)";

/*** IeBuffer ***/
class IeBuffer;

class IeBuffer
{
  public:
    virtual ~IeBuffer() {}
    
    virtual Int numBytes() const = 0;
    virtual const void *dataPtr() const = 0; //read access for input data
    virtual IeBuffer& operator=(const IeBuffer& rhs) = 0;
    
    // these must be used only by the filter that owns the buffer
    virtual void *dataPtr() = 0;
    virtual void setDataPtr(void *dataPtr) = 0;
};

IEDLLEXPORT IeBuffer *  newIeBuffer(Int numBytes, void *pData=NULL);


/*** Ief ***/
class IEDLLEXPORT Ief       // because IeFilter is derived from this class
{                           // a warning is produced in an app using the dll
  public:
    virtual ~Ief();

    virtual const IeSize& size() const = 0;
    virtual const IePixTyp& pixTyp() const = 0;
    virtual const CsSpace& colorSpace() const = 0;
    virtual void setColorSpace(const CsSpace& colorSpace) = 0;
    
    virtual Int bytesPerRow() const = 0;
    virtual const void *getNextRow() = 0;
    virtual void restore() = 0;
    virtual Int rowsRemaining() const = 0;

    virtual AiBoolean isValid() const {
        return TRUE;
    }

    enum Quality { lowQuality=1, normalQuality, highQuality };
    enum AlphaOp { alphaAoverB, alphaAinB, alphaAoutB, alphaAatopB, 
               alphaAxorB, alphaAinCoverB, alphaAplusB,
               alphaDarken=16, alphaDissolve, alphaOpaque };
    enum Gradient { lineGradient, ellipseGradient, rectGradient };
    enum GradientType { rgbGradient, clockwiseHsvGradient, hsvGradient };
    enum BitOp { bitB, bitNotB, bitA, bitNotA, bitAorB, bitAorNotB, 
             bitNotAorB, bitAnandB, bitAandB, bitAandNotB, bitNotAandB,
             bitAnorB, bitAxorB, bitAequivB };
    enum Filter { boxFilter, triangleFilter, cubicFilter, 
                 gaussianFilter };
    enum Softedge { insideSoftedge, outsideSoftedge, inOutSoftedge };

//private:
    virtual class IeReadContext *castToReadContext() = 0;
};

IEDLLEXPORT void ieExecute(Ief* input);       //execute pipeline and discard output


/*** IeFilter ***/
class IEDLLEXPORT IeFilter : public Ief
{
  public:
    const IeSize& size() const;
    const IePixTyp& pixTyp() const;
    const CsSpace& colorSpace() const;
    void setColorSpace(const CsSpace& colorSpace);

    Int bytesPerRow() const;
    const void *getNextRow();
    void restore();
    Int rowsRemaining() const;

#if defined(CS_APP) && defined(CS_WIN16)
    void *operator new(size_t s) { return csNew(s); }
    void operator delete(void *p) { csDelete(p); }
#endif

  protected:
    IeFilter(Int numInputs);
    ~IeFilter();

    void init(const IeSize& size,
              const IePixTyp& pixTyp,
              const CsSpace& colorSpace);

    virtual const IeBuffer *processRow() = 0;    //must be defined by filter
    virtual void processRestore() {};        //may be defined by filter

    //ACCESS TO INPUT DATA
    Int numInputs() const;
    Ief *input(Int inputIndex) const;
    void connectInput(Int inputIndex, 
                      Ief *input,
                      const IePixTyp& pixTyp,
                      const CsSpace& colorSpace);
    Int inputRowsRemaining(Int inputIndex) const;
    const IeBuffer *getNextInputRow(Int inputIndex);
    
  private:
    friend class IieFilter;
    friend class IePlaneFilter;
    
    class IieFilter *mpImp;
    class IeReadContext *mpRc;
      public: //consider private
    class IeReadContext *castToReadContext();
};

/////////////////////////////////////////////
// Floating point utility functions for use
// with IeAnyAffine, etc.
/////////////////////////////////////////////

/*** IeSizeReal ***/

class IeSizeReal
{
  public:
    IeSizeReal() {}            //uninitialized
    IeSizeReal(Real x, Real y) { mX = x; mY = y; }
    IeSizeReal(const IeSize &intSize) { mX = intSize.x(); mY = intSize.y(); }

    Real x() const { return mX; }
    Real y() const { return mY; }
    Real& x() { return mX; }
    Real& y() { return mY; }
    void setX(Real x) { mX = x; }
    void setY(Real y) { mY = y; }

    IeSizeReal& operator+=(const IeSizeReal& rhs) 
        { mX += rhs.mX; mY += rhs.mY; return *this; }
    IeSizeReal& operator-=(const IeSizeReal& rhs)
        { mX -= rhs.mX; mY -= rhs.mY; return *this; }
    IeSizeReal& operator*=(const IeSizeReal& rhs)
        { mX *= rhs.mX; mY *= rhs.mY; return *this; }
    IeSizeReal& operator/=(const IeSizeReal& rhs)
        { mX /= rhs.mX; mY /= rhs.mY; return *this; }
    IeSizeReal operator+(const IeSizeReal& rhs) const
        { return IeSizeReal(mX + rhs.mX, mY + rhs.mY); }
    IeSizeReal operator-(const IeSizeReal& rhs) const
        { return IeSizeReal(mX - rhs.mX, mY - rhs.mY); }
    IeSizeReal operator*(const IeSizeReal& rhs) const
        { return IeSizeReal(mX * rhs.mX, mY * rhs.mY); }
    IeSizeReal operator/(const IeSizeReal& rhs) const
        { return IeSizeReal(mX / rhs.mX, mY / rhs.mY); }
    AiBoolean operator==(const IeSizeReal& r) const
        { return mX == r.mX && mY == r.mY; }
    AiBoolean operator!=(const IeSizeReal& r) const
        { return mX != r.mX || mY != r.mY; }
    AiBoolean operator<(const IeSizeReal& r) const
        { return mX < r.mX && mY < r.mY; }
    AiBoolean operator<=(const IeSizeReal& r) const
        { return mX <= r.mX && mY <= r.mY; }
    AiBoolean operator>(const IeSizeReal& r) const
        { return mX > r.mX || mY > r.mY; }
    AiBoolean operator>=(const IeSizeReal& r) const
        { return mX >= r.mX || mY >= r.mY; }

    IeSizeReal& operator+=(const Real r) 
        { mX += r; mY += r; return *this; }
    IeSizeReal& operator-=(const Real r)
        { mX -= r; mY -= r; return *this; }
    IeSizeReal& operator*=(const Real r)
        { mX *= r; mY *= r; return *this; }
    IeSizeReal& operator/=(const Real r)
        { mX /= r; mY /= r; return *this; }
    IeSizeReal operator+(const Real r) const
        { return IeSizeReal(mX + r, mY + r); }
    IeSizeReal operator-(const Real r) const
        { return IeSizeReal(mX - r, mY - r); }
    IeSizeReal operator*(const Real r) const
        { return IeSizeReal(mX * r, mY * r); }
    IeSizeReal operator/(const Real r) const
        { return IeSizeReal(mX / r, mY / r); }
    AiBoolean operator==(const Real r) const
        { return mX == r && mY == r; }
    AiBoolean operator!=(const Real r) const
        { return mX != r || mY != r; }
    AiBoolean operator<(const Real r) const
        { return mX < r && mY < r; }
    AiBoolean operator<=(const Real r) const
        { return mX <= r && mY <= r; }
    AiBoolean operator>(const Real r) const
        { return mX > r || mY > r; }
    AiBoolean operator>=(const Real r) const
        { return mX >= r || mY >= r; }
    
    operator IeSize() const;    // Properly rounds to nearest integer point.

  private:
    Real mX, mY;
};

typedef IeSizeReal IeOffsetReal;

class IEDLLEXPORT Ie2DTransform {
public:
    Ie2DTransform() {}

    // Initialize to "Xout = scale * Xin + offset.x" etc.
    Ie2DTransform(Real scale, 
                  const IeOffsetReal& offset = ieOffsetOrigin);

    // "rotation" in radians.  "center" is fixed point of scale/rotation.
    Ie2DTransform(Real scale, 
                  Real rotRadians,
                  const IeOffsetReal& center = ieOffsetOrigin);

    Real    operator () (const UInt row, const UInt col) const;
    Real&   operator () (const UInt row, const UInt col);
    void    debugPrint() const;

    Ie2DTransform   inverse() const;
    AiBoolean       isSingular() const;
    AiBoolean       isNonOrthoRotation() const; // True iff ((rotation mod 90 deg) != 0)

private:
    Real    mat[3][3];
};    

inline Real Ie2DTransform::operator () (const UInt row, const UInt col) const 
{
    return mat[row][col];
}

inline Real& Ie2DTransform::operator () (const UInt row, const UInt col) 
{
    return (Real&)(mat[row][col]);
}

IEDLLEXPORT Ie2DTransform operator * (const Ie2DTransform& left, const Ie2DTransform& right);

IEDLLEXPORT IeOffsetReal operator * (const Ie2DTransform&, const IeOffsetReal&);


class IeChunkEncoder
{
//	A Chunk Rank is made of a row of IeVirtualChunkEncoder.
//	Every IeVirtualChunkEncoder contains a list of all IeActualChunkEncoder one for every codec.
public:
	//	Initialization

	//	if input is 1Bpp, ieSizeChunk must be a multiple of 8
	virtual	~IeChunkEncoder() {}

	virtual	AiBoolean				isValid() const = 0;

	//	operations 
	virtual	IeSize					getActualChunkSizeUsed() const = 0;	//	returns the 32 bit aligned chunk size

	virtual	const	void*			getNextEncodedChunk(const char*& pszCodecName, unsigned long& ulNumBytes) = 0;

	virtual	unsigned	long	numChunkCols() const = 0;				//	Number of cols of chunks to produce
	virtual	unsigned	long	numChunkRows() const = 0;				//	Number of rows of chunks to produce

	virtual	unsigned	long	numChunksTotal() const  = 0;		//	Tolal number of chunks
	virtual	unsigned	long	numChunksRemaining() const = 0;	//	Chunks remaining to process

	virtual	unsigned	long	currentChunkIndex()  const = 0;	//	the current chunk index 0 based
	virtual	unsigned	long	currentChunkIndexX() const = 0;	//	the current chunk Width  index 0 based
	virtual	unsigned	long	currentChunkIndexY() const = 0;	//	the current chunk Height index 0 based
};

IEDLLEXPORT IeChunkEncoder* newIeChunkEncoder(Ief* piefInput, const IeSize& ieSizeChunkRequested, const char** ppcszEncorderNameList);


// The IeColorAdjustTable is used with IefColorAdjust.  This object can be built once and 
// reused to avoid recomputation of the contrast and brightness functions.
//
class IEDLLEXPORT IeColorAdjustTable {
public:
    virtual                 ~IeColorAdjustTable() {};
	virtual void	        makeAdjustedColorSpace(const CsSpace& inCs, CsSpace& outCs) const = 0;
	virtual CsRgb8	        adjustColor(const CsRgb8& inColor) const = 0;

	virtual Real	        brightness() const = 0;
	virtual Real	        contrast() const = 0;
	virtual Real	        fade() const = 0;
	virtual CsRgb8	        fadeToColor() const = 0;
    virtual const UInt8*    tablePtr() const = 0;

    // Parameters defining the valid brightness, contrast and fade control ranges.
    //
    static const Real       maxControlValue;    // zero is min control value
    static const Real       neutralBrightness;
    static const Real       neutralContrast;
    static const Real       neutralFade;
};

// Basic constructor
IEDLLEXPORT IeColorAdjustTable *  
                    newIeColorAdjustTable(Real brightness, 
										  Real contrast = IeColorAdjustTable::neutralContrast, 
										  Real fade = IeColorAdjustTable::neutralFade, 
										  const CsRgb8& fadeToColor = csBlack);

// Combines effects to support WYSIWYG editing with contrast and brightness adjustment.
IEDLLEXPORT IeColorAdjustTable *  
                    newCombinedIeColorAdjustTable(const IeColorAdjustTable& copyFrom, 
                                                  const IeColorAdjustTable& pasteTo);

// Palette map table used with newIefColorToAnyPaletteConvert().  Create it
// using newIePaletteMapTable() below.
//
class IePaletteMapTable {
public:
    virtual                 ~IePaletteMapTable() {};
    virtual AiBoolean       isValid() const = 0;
    virtual const CsSpace&  getColorSpace() const = 0;
    virtual UInt8           getClosePaletteIndex(const CsRgb8 targetColor) const = 0;

    virtual UInt8           getKeyInx() const = 0;

	virtual AiBoolean		isGrayPalette() const = 0;
	virtual AiBoolean		hasGrayValues() const = 0;
    virtual UInt8           getCloseGrayIndex(const UInt8 targetGray) const = 0;

    virtual void			printTableToFile(char *pSaveFile) = 0;

};


IEDLLEXPORT IePaletteMapTable *  newIePaletteMapTable(const CsSpace& outCs, 
                                                                const UInt8 nDontUseInx = 255);


/*** BUILT-IN FILTERS ***/
IEDLLEXPORT Ief *  newIefABCtoXYZ(Ief *input,
                                 Real32 *sampleCube,
                                 Int *dim,
                                 Real32 *aLut,
                                 Real32 *bLut,
                                 Real32 *cLut,
                                 Ief::Quality quality);

IEDLLEXPORT Ief *  newIefAdaptiveDiffuse(Ief *input, 
                                 Int numColors,
                                 const CsSpace& palette=csNone);

#define newIefAffine newIefAnyAffine    // temporary construct 

IEDLLEXPORT Ief *  newIefAlphaComposite(Ief::AlphaOp op,
                                 Ief *inputA,
                                 Ief *inputB,
                                 Ief *inputC = NULL);

IEDLLEXPORT Ief *  newIefAlphaUnary(Ief::AlphaOp op,
                                 Ief *input,
                                 UInt val);
// !!!!!!!!!!!!!
//
// The following prototype corresponds to a non-existent function.  It is
// provided to avoid the common error of invoking newIefAnyAffine with an
// Ief * rather than a const IeImg&.  Without this "dummy" prototype, the
// compiler will construct a temporary const IeImg& from an Ief *, which will
// result in a run-time exception.
//
// The effect of this prototype is to generate an "unresolved external symbol"
// error when linking if an Ief * is used rather than a const IeImg&.
//
// !!!!!!!!!!!!!

Ief * newIefAnyAffine(Ief *input,
                      const Ie2DTransform& srcToDest,
                      const IeSize& destSize,
                      Ief::Quality quality,
                      const IePixel& clearVal=iePixelZero);

// !!!!!!!!!!!!!
//
//  Note that newIefAnyAffine isn't a true pipeline element.  It must be
//  connected directly to the input image.  This allows it to use the pixel
//  access API to efficiently rotate images.
//
// !!!!!!!!!!!!!

IEDLLEXPORT Ief *  newIefAnyAffine(const class IeImg& srcImg,
                                const Ie2DTransform& srcToDest,
                                const IeSize& destSize,
                                Ief::Quality quality,
                                const IePixel& clearVal=iePixelZero);

IEDLLEXPORT Ief *  newIefBitwise(Ief *inputF,
                                Ief *inputB,
                                Ief::BitOp op);

IEDLLEXPORT Ief *  newIefClipToPolygon(Ief* pInput, 
                                const Real *pClipPolygon, 
                                Int numVerticies, 
                                const IePixel& clearVal=iePixelZero);

IEDLLEXPORT Ief *  newIefColorAdjust(Ief *input, const IeColorAdjustTable& table);


IEDLLEXPORT Ief *  newIefColorToAnyPaletteConvert(Ief *pInput,
                                Ief::Quality quality,
                                const IePaletteMapTable *pUserMapTable,
                                AiBoolean bDoKeyColorTransparency=FALSE,
                                UInt8 grayInputTransparentValue=0);

IEDLLEXPORT Ief *  newIefConst(const IeSize& size,
                                const IePixTyp& pix,
                                const CsSpace& cs,
                                const IePixel& val);

IEDLLEXPORT Ief *  newIefConstBlend(Ief *input0, 
                                Ief *input1, 
                                Real factor);

IEDLLEXPORT Ief *  newIefControlPointWarp(Ief *input,
                                 const Real* pSrcColControl, 
                                 const Real* pSrcRowControl,
                                 const Real* pDestColControl, 
                                 const Real* pDestRowControl,
                                 Int numCols, 
                                 Int numRows,
                                 Ief::Quality quality); 

IEDLLEXPORT Ief *  newIefConvert(Ief *input, 
                                 const CsSpace& colorSpace,
                                 const IePixTyp& pixTyp=IePixTyp::none,
                                 const IePixel& grayOutputTransparentVal=iePixelNull);

IEDLLEXPORT Ief *  newIefDiffuse(Ief *input, 
                                 const CsSpace& colorCube);

IEDLLEXPORT Ief *  newIefGradient(const IeSize& fillRegion,
                                 const IePixTyp& outPixType,
                                 Ief::Gradient gradient,
                                 Ief::GradientType type,                    
                                 const IeOffset& pt0,
                                 const IeOffset& pt1,
                                 const CsSpace& colors,
                                 const Real *posTable=NULL,
                                 IeGradientFunc *pFunc=NULL);

IEDLLEXPORT Ief *  newIefLowPass(Ief *input,
                                 Ief::Filter filter,
                                 UInt kernelSize); 

IEDLLEXPORT Ief *  newIefLut32(Ief *input, 
                                 const CsRgb8 *pTable,
                                 UInt numEntries);

IEDLLEXPORT Ief *  newIefLut8(Ief *input, 
                                 const UInt8 *pTable,
                                 UInt numEntries);

IEDLLEXPORT Ief *  newIefMatteBlend(Ief *input0, 
                                 Ief *input1, 
                                 Ief *matte);

IEDLLEXPORT Ief *  newIefOrderedDither(Ief *input, 
                                 const CsSpace& colorCube,
                                 Int maskSize=8,
                                 const IeOffset& maskOffset=ieOffsetOrigin,
                                 const Int *pDitherMask=NULL);


IEDLLEXPORT Ief *  newIefPerspective(Ief *input, 
                                 const Real *pVertices,  // 4 corner points
                                 Ief::Quality quality, 
                                 const IePixel& clearVal=iePixelZero);

IEDLLEXPORT Ief *  newIefScale(Ief *input,
                                 Real xScale,
                                 Real yScale,
                                 Ief::Quality quality);

IEDLLEXPORT Ief* newIefScale(Ief* input, const IeSize& outSize);

IEDLLEXPORT Ief* newIefScale(Ief* input, Real xScale, Real yScale);


/*** OBSOLETE ***/
#define IeQuality Ief::Quality
#define IEQ_LOW Ief::lowQuality
#define IEQ_NORMAL Ief::normalQuality
#define IEQ_HIGH Ief::highQuality
enum IeSoftType { IE_SOFT_IN, IE_SOFT_OUT, IE_SOFT_INOUT };

#endif /* _ief_h */
