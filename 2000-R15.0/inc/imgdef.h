//
//  (C) Copyright 1996-1999 by Autodesk, Inc.
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
//  
#ifndef __IMGDEF_H
#define __IMGDEF_H    1

#include "dbmain.h"
#include "acgi.h"
#include "gept2dar.h"
#include "gemat2d.h"
#pragma pack (push, 8)

// Forward declarations
//
class  RasterImageDefImp;                // Opaque type
class  AcDbImpRasterImageDefReactor;     // Opaque type
class  IeImg;                            // IE Image Handle
class  IeFileDesc;						 // IE File Descriptor
struct CFileStatus;                      // MFC
class  CPalette;                         // MFC
class  CString;                          // MFC

enum ClassVersion
{
    kVersion1   = 0,    // S039 Oct 21, 1996
    kVersion2   = 1,    // S052 Jan 16, 1996
    kVersion3   = 2     // S061 Mar 21, 1997
};


// Make compiler shut up
//
#pragma warning( disable : 4275 ) 

#ifdef ISMDLLACCESS
#undef ISMDLLACCESS
#endif
#ifdef ISMDLLACCESSDATA
#undef ISMDLLACCESSDATA
#endif
#ifdef ISM_OBJ // For DwgUnplugged ISMobj.arx:
// Classes to be exported have to have ISMDLLACCESS definition in its header.
//		Example: class ISMDLLACCESS AcDbImpRasterImageDef
#define ISMDLLACCESS __declspec(dllexport)
#define ISMDLLACCESSDATA
#else
#define ISMDLLACCESS 
#define ISMDLLACCESSDATA __declspec(dllimport)
#endif


// The AcDbRasterImageDef object controls the actual image data
// associated with one or more AcDbRasterImage entities.  These objects
// hold image data in one of two ways.  The first way is through
// "linking" the raster file to the dwg file as with Xrefs.  The second
// way is through "embedding" as with block insert.
//
class ISMDLLACCESS AcDbRasterImageDef : public AcDbObject 
{
public:

    static ClassVersion         classVersion();

    ACRX_DECLARE_MEMBERS(AcDbRasterImageDef);

			                    AcDbRasterImageDef();
    virtual						~AcDbRasterImageDef();

    RasterImageDefImp*          ptrImp() const;
	RasterImageDefImp*          setPtrImp(RasterImageDefImp* pImp);

	// AcDbObject overridden methods
	//
    virtual Acad::ErrorStatus   subErase(Adesk::Boolean erasing);
	virtual Acad::ErrorStatus	subClose();

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;

	// AcDbRasterImageDef specific methods
    //
	virtual AcGiSentScanLines*	makeScanLines(	
                                    const AcGiRequestScanLines* pReq,
									const AcGeMatrix2d& pixToScreen,
									AcGePoint2dArray* pActiveClipBndy = 0,     // Data will be modified!
                                    Adesk::Boolean draftQuality = Adesk::kFalse,
                                    Adesk::Boolean isTransparent = Adesk::kFalse,
                                    const double brightness = 50.0,
                                    const double contrast = 50.0,
                                    const double fade = 0.0
                                ) const;

	virtual Acad::ErrorStatus	setSourceFileName(const char* pPathName);
	virtual Acad::ErrorStatus	setActiveFileName(const char* pPathName);
	virtual const char*			searchForActivePath();

	virtual const char*	        sourceFileName() const;
	virtual const char*			activeFileName() const;

	virtual Acad::ErrorStatus	embed();
	virtual Adesk::Boolean		isEmbedded() const;

	virtual Acad::ErrorStatus   load();
	virtual Acad::ErrorStatus   unload(Adesk::Boolean modifyDatabase = Adesk::kTrue);
    virtual Adesk::Boolean		isLoaded() const;

	virtual AcGeVector2d		size() const;

    // The following two methods require the image to be loaded, 
	// otherwise they return default values that may not be correct
	// for the image.
    //
    virtual AcGiImageOrg        organization() const;
    virtual int                 colorDepth() const;

	virtual const char*			fileType() const;
	virtual int					entityCount(
									Adesk::Boolean* pbLocked = 0
								) const;
	virtual void				updateEntities() const;

	enum Units 
	{			
		kNone			= 0,
		kMillimeter		= 1,
		kCentimeter		= 2,
		kMeter			= 3,
		kKilometer		= 4,
		kInch			= 5,
		kFoot			= 6,
		kYard			= 7,
		kMile			= 8,
        kMicroinches    = 9,
        kMils           = 10,
        kAngstroms      = 11,
        kNanometers     = 12,
        kMicrons        = 13,
        kDecimeters     = 14,
        kDekameters     = 15,
        kHectometers    = 16,
        kGigameters     = 17,
        kAstronomical   = 18,
        kLightYears     = 19,
        kParsecs        = 20
	};

    virtual Acad::ErrorStatus   setResolutionMMPerPixel(
                                    const AcGeVector2d& resMMPerPixel);
	virtual AcGeVector2d		resolutionMMPerPixel() const;
    virtual void                setResolutionUnits(
                                    AcDbRasterImageDef::Units units);
	virtual Units				resolutionUnits() const;

	// Thumbnail functions
	//
	virtual Acad::ErrorStatus	loadThumbnail(
									Adesk::UInt16& maxWidth,
									Adesk::UInt16& maxHeight,
									Adesk::UInt8* pPalette = 0,
									int nPaletteEntries = 0
								);
	virtual Acad::ErrorStatus	unloadThumbnail();
	virtual void*				createThumbnailBitmap(
									BITMAPINFO*& pBitmapInfo,
									Adesk::UInt8 brightness = 50,
									Adesk::UInt8 contrast = 50,
									Adesk::UInt8 fade = 0
								);

    ////////////////////////////////////////////////
    // Image engine access
    ////////////////////////////////////////////////

    // Obtain copy of image
    //
    virtual IeImg*			    imageCopy(Adesk::Boolean bForceImageLoad = Adesk::kTrue) const;
    virtual IeFileDesc*		    fileDescCopy() const;

    // Open direct access to current image
    //
    virtual Acad::ErrorStatus	openImage(IeImg*& pImage);

    // Close direct access
    //
    virtual Acad::ErrorStatus	closeImage();

    // Create directly from in-memory IE image and/or file descriptor.
	//
	virtual Acad::ErrorStatus	setImage(const IeImg* pImage, 
                                    const IeFileDesc* pFileDesc, 
                                    Adesk::Boolean modifyDatabase = Adesk::kTrue);

    // Set undo store size
    //
    virtual Acad::ErrorStatus	setUndoStoreSize(
					                unsigned int maxImages = 10
				                );
    virtual unsigned int		undoStoreSize() const;

    // Get/set "image modified" flag
    //
    virtual Adesk::Boolean       imageModified() const;
    virtual Acad::ErrorStatus    setImageModified(Adesk::Boolean modified);

    ////////////////////////////////////////////////
    // Image dictionary access
    ////////////////////////////////////////////////

    // Create/get image dictionary
    //
    static Acad::ErrorStatus     createImageDictionary(AcDbDatabase* pDb, AcDbObjectId& dictId);
    static AcDbObjectId          imageDictionary(AcDbDatabase* pDb); 

    // Derive image def. name from file name. Handles duplicates.
    // Use the following enum constant for the buffer size of
    // of newImageName.
    //
    enum { kMaxSuggestNameSize = 2049 };
    static Acad::ErrorStatus     suggestName(
                                     AcDbDictionary* pImageDictionary, 
                                        const TCHAR* pNewImagePathName, 
                                        TCHAR* newImageName
                                 );

private:

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them private
    // in order to prevent usage of them.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](unsigned nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](unsigned nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

	// Data members
	//
	RasterImageDefImp*		     mpImp;
    static ClassVersion          mVersion;
};

//gets the implementation class pointer
inline RasterImageDefImp*
AcDbRasterImageDef::ptrImp() const
{
    return mpImp;
}

//sets the implementation class pointer
inline RasterImageDefImp*             
AcDbRasterImageDef::setPtrImp(RasterImageDefImp* pImp)
{
	RasterImageDefImp* oldImp=mpImp;
	mpImp=pImp;
	return oldImp;
}


    

// Persistent reactor used to connect AcDbRasterImage entities to 
// AcDbRasterImageDef objects.  It can be used by other applications
// as a persistent reactor to receive the special "imageSave" notification.
//
class ISMDLLACCESS AcDbRasterImageDefReactor : public AcDbObject 
{
public:

    static ClassVersion         classVersion();

    ACRX_DECLARE_MEMBERS(AcDbRasterImageDefReactor);

								AcDbRasterImageDefReactor();
    virtual					    ~AcDbRasterImageDefReactor();


    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

	// Notification
	//
    virtual void				erased(const AcDbObject* dbObj,
									Adesk::Boolean pErasing = Adesk::kTrue
								);
	virtual void				modified(const AcDbObject* dbObj);

    // Delete image notification.
    //
    enum DeleteImageEvent
    {
        kUnload     = 1,
        kErase      = 2,
    };

    virtual Adesk::Boolean      onDeleteImage(
                                    const AcDbRasterImageDef* pImageDef, 
                                    IeImg* pImage,
                                    DeleteImageEvent event,
                                    Adesk::Boolean cancelAllowed);

	// Enable/disable notification actions
	//
	static void					setEnable(Adesk::Boolean enable);

private:

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them private
    // in order to prevent usage of them.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](unsigned nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](unsigned nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

    // Data members
    //
    AcDbImpRasterImageDefReactor*	mpImp;
    static ClassVersion             mVersion;
};


// Transient reactor to receive the special "onDeleteImage" notification from
// AcDbRasterImageDef objects.  This is a pure virtual class, so the developer
// must derive from this and override the onDeleteImage function.
//
class ISMDLLACCESS AcDbRasterImageDefTransReactor : public AcDbObjectReactor 
{
public:
	
    ACRX_DECLARE_MEMBERS(AcDbRasterImageDefTransReactor);

    virtual						~AcDbRasterImageDefTransReactor();

	// Custom notification
	//
    virtual Adesk::Boolean      onDeleteImage(const AcDbRasterImageDef* pImageDef, 
                                          IeImg* pImage,
										  AcDbRasterImageDefReactor::DeleteImageEvent event,
                                          Adesk::Boolean cancelAllowed) = 0;

};

class ISMDLLACCESS AcDbRasterImageDefFileAccessReactor : public AcDbObjectReactor 
{
public:
	
    ACRX_DECLARE_MEMBERS(AcDbRasterImageDefFileAccessReactor);

    virtual						~AcDbRasterImageDefFileAccessReactor();

    virtual void                onAttach(
                                    const AcDbRasterImageDef*, 
                                    const char* pPath) = 0;
    virtual void                onDetach(
                                    const AcDbRasterImageDef*, 
                                    const char* pPath) = 0;
    virtual Adesk::Boolean      onOpen(
                                    const AcDbRasterImageDef*,
                                    const char* pPath, 
                                    const char* pActivePath,
                                    Adesk::Boolean& replacePath,
                                    CString& replacementPath) = 0;
    virtual Adesk::Boolean      onPathChange(
                                    const AcDbRasterImageDef*,
                                    const char* pPath, 
                                    const char* pActivePath,
                                    Adesk::Boolean& replacePath,
                                    CString& replacementPath) = 0;
    virtual void                onClose(
                                    const AcDbRasterImageDef*,
                                    const char* pPath) = 0;

    virtual void                onDialog(
                                     AcDbRasterImageDef*,
                                     const char* pCaption, 
                                     const char* pFileExtensions
                                 ) = 0;
};

//////////////////// inlines ////////////////////
//
inline ClassVersion
AcDbRasterImageDef::classVersion()
{   return mVersion; }

inline ClassVersion
AcDbRasterImageDefReactor::classVersion()
{   return mVersion; }

#pragma warning( default : 4275 ) 

#pragma pack (pop)
#endif // __IMGDEF_H
