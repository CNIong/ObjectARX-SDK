#ifndef AD_DBMTEXT_H
#define AD_DBMTEXT_H
//
//  Copyright 1996-2000 by Autodesk, Inc.
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
//  dbmtext.h - multi-line text entity

#include "dbmain.h"

#pragma pack(push, 8)

//  This structure is used to describe a fragment of text as 
//  extracted by the explodeFragments() member function.  Each 
//  fragment consists of a piece of text with a unique 
//  combination of style information (font, size, color, etc.)
//
struct AcDbMTextFragment
{
    //  position data
    //
    AcGePoint3d  location;
    AcGeVector3d normal;
    AcGeVector3d direction;

    //  text characters
    //
    char*        text;

    //  font names
    //
    char*        font;
    char*        bigfont;

    //  metrics
    //
    AcGePoint2d  extents;
    double       capsHeight;
    double       widthFactor;
    double       obliqueAngle;
    double       trackingFactor;
    Adesk::UInt16 colorIndex;

    //  stack flags
    //
    unsigned stackTop:1;
    unsigned stackBottom:1;

    //  underline/overline data
    //
    unsigned    underlined:1;
    unsigned    overlined:1;
    AcGePoint3d underPoints[2];
    AcGePoint3d overPoints[2];

    //  true type font data
    //
	char *	fontname;
	bool	bold;
	bool	italic;

};

//  Fragment Enumerator Callback Function Prototype
//
//  A pointer to a function of this type is expected by the explodeFragments() 
//  member function.  The elaboration function is called once for each 
//  fragment. 'frag' points to the relevant fragment structure. 'param' 
//  contains the value of the 'param' argument given to the explodeFragments()
//   member function. The elaboration function must return 1 to continue the 
//  elaboration operation, or 0 to terminate the operation.
//
typedef int (*AcDbMTextEnum)(AcDbMTextFragment *, void *);

class AcDbText;

class AcDbMText: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbMText);
    AcDbMText();
    ~AcDbMText();

    //  Insertion point
    //
    AcGePoint3d		location() const;
    Acad::ErrorStatus	setLocation(const AcGePoint3d&);

    //  Normal vector
    // 
    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);

    //  Direction vector
    //
    AcGeVector3d	direction() const;
    Acad::ErrorStatus	setDirection(const AcGeVector3d&);

    //  Rotation angle (radians)
    // 
    double		rotation() const;
    Acad::ErrorStatus	setRotation(double);

    //  Entity width (constraining value)
    // 
    double		width() const;
    Acad::ErrorStatus	setWidth(double);

    //  Text Style (sets initial font)
    //
    AcDbObjectId        textStyle() const;
    Acad::ErrorStatus	setTextStyle(AcDbObjectId);

    //  Initial text height (caps height)
    //
    double		textHeight() const;
    Acad::ErrorStatus	setTextHeight(double);

    enum AttachmentPoint {
	kTopLeft	= 1,
	kTopCenter	= 2,
	kTopRight	= 3,
	kMiddleLeft	= 4,
	kMiddleCenter	= 5,
	kMiddleRight	= 6,
	kBottomLeft	= 7,
	kBottomCenter	= 8,
	kBottomRight	= 9,
    kBaseLeft       = 10,   // Reserved for future use
    kBaseCenter     = 11,   // Reserved for future use
    kBaseRight      = 12,   // Reserved for future use
    kBaseAlign      = 13,   // Reserved for future use
    kBottomAlign    = 14,   // Reserved for future use
    kMiddleAlign    = 15,   // Reserved for future use
    kTopAlign       = 16,   // Reserved for future use
    kBaseFit        = 17,   // Reserved for future use
    kBottomFit      = 18,   // Reserved for future use
    kMiddleFit      = 19,   // Reserved for future use
    kTopFit         = 20,   // Reserved for future use
    kBaseMid        = 21,   // Reserved for future use
    kBottomMid      = 22,   // Reserved for future use
    kMiddleMid      = 23,   // Reserved for future use
    kTopMid         = 24,   // Reserved for future use
    };
    AttachmentPoint	attachment() const;
    Acad::ErrorStatus	setAttachment(AttachmentPoint);
    Acad::ErrorStatus   setAttachmentMovingLocation(AttachmentPoint);
    // This latter method will implicitly setLocation based on the
    // relationship of current and new attachment values in order
    // to keep the extents of the MText object constant.

    //  Text flow direction
    //
    enum FlowDirection {
	kLtoR		= 1,
	kRtoL		= 2,	//  not currently supported
	kTtoB		= 3,
	kBtoT		= 4,	//  not currently supported
	kByStyle	= 5
    };
    FlowDirection	flowDirection() const;
    Acad::ErrorStatus	setFlowDirection(FlowDirection);

    //  Text contents
    //
    char		*contents() const;
    int			setContents(const char *);

    //  Actual extents
    //
    double		actualHeight(AcGiWorldDraw *ctxt = NULL) const;
    double		actualWidth() const;

    int			correctSpelling();

    //  Return points marking text box
    //
    void		getBoundingPoints(AcGePoint3dArray&) const;

    //  Explode text fragments
    //
    void		explodeFragments(AcDbMTextEnum, void *, AcGiWorldDraw *ctxt = NULL) const;

    //  These strings can be used instead of sprinkling your code 
    //  with string constants.
    static const char* const nonBreakSpace();	//  \~
    static const char* const overlineOn();	//  \O
    static const char* const overlineOff();	//  \o
    static const char* const underlineOn();	//  \L
    static const char* const underlineOff();	//  \l
    static const char* const colorChange();	//  \C
    static const char* const fontChange();	//  \F
    static const char* const heightChange();	//  \H
    static const char* const widthChange();	//  \W
    static const char* const obliqueChange();	//  \Q
    static const char* const trackChange();	//  \T
    static const char* const lineBreak();	//  \p
    static const char* const paragraphBreak();	//  \P
    static const char* const stackStart();	//  \S
    static const char* const alignChange();	//  \A
    static const char* const blockBegin();	//  {
    static const char* const blockEnd();	//  }

    Acad::ErrorStatus   setLineSpacingStyle(AcDb::LineSpacingStyle eStyle);
    AcDb::LineSpacingStyle lineSpacingStyle() const;

    // 1.0 = single spaced (default), 2.0 = double-spaced, etc.
    Acad::ErrorStatus   setLineSpacingFactor(double dFactor);
    double              lineSpacingFactor() const;

    // -----  **** BEGIN **** (deprecated methods)

    // The methods from here through *** END *** are only
    // being left in for compatibility with Acad 2000 apps.
    // They will be removed in the next release.  Please do
    // not use them!

    Adesk::Boolean      isR12StyleText() const;

    AcGePoint3d         alignmentPoint() const;
    Acad::ErrorStatus   setAlignmentPoint(const AcGePoint3d&);
    Adesk::Boolean      isDefaultAlignment() const;

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    Adesk::Boolean      isMirroredInX() const;
    Acad::ErrorStatus   mirrorInX(Adesk::Boolean);
     
    Adesk::Boolean      isMirroredInY() const;
    Acad::ErrorStatus   mirrorInY(Adesk::Boolean);
     
    AcDb::TextHorzMode  horizontalMode() const;
    Acad::ErrorStatus   setHorizontalMode(AcDb::TextHorzMode);
     
    AcDb::TextVertMode  verticalMode() const;
    Acad::ErrorStatus   setVerticalMode(AcDb::TextVertMode);

    void                getEcs(AcGeMatrix3d& retVal) const;

    void                setFromTextEntity(AcDbText * const);

    // ----- *** END *** (of deprecated methods) ----- 


    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
