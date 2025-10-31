//
#ifndef AD_DBMTEXT_H
#define AD_DBMTEXT_H
//
//  Copyright 1996-2009 by Autodesk, Inc.
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
    ACHAR*        text;

    //  font names
    //
    ACHAR*        font;
    ACHAR*        bigfont;

    //  metrics
    //
    AcGePoint2d  extents;
    double       capsHeight;
    double       widthFactor;
    double       obliqueAngle;
    double       trackingFactor;
    AcCmEntityColor color;

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
    ACHAR *  fontname;
    bool    bold;
    bool    italic;

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
    AcGePoint3d     location() const;
    Acad::ErrorStatus   setLocation(const AcGePoint3d&);

    //  Normal vector
    // 
    AcGeVector3d    normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    //  Direction vector
    //
    AcGeVector3d    direction() const;
    Acad::ErrorStatus   setDirection(const AcGeVector3d&);

    //  Rotation angle (radians)
    // 
    double      rotation() const;
    Acad::ErrorStatus   setRotation(double);

    //  Entity width (constraining value)
    // 
    double      width() const;
    Acad::ErrorStatus   setWidth(double);

    //  Descent/Ascent
    // 
    double      ascent() const;
    double      descent() const;

    //  Text Style (sets initial font)
    //
    AcDbObjectId        textStyle() const;
    Acad::ErrorStatus   setTextStyle(AcDbObjectId);

    //  Initial text height (caps height)
    //
    double      textHeight() const;
    Acad::ErrorStatus   setTextHeight(double);

    enum AttachmentPoint {
    kTopLeft    = 1,
    kTopCenter  = 2,
    kTopRight   = 3,
    kMiddleLeft = 4,
    kMiddleCenter   = 5,
    kMiddleRight    = 6,
    kBottomLeft = 7,
    kBottomCenter   = 8,
    kBottomRight    = 9,
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
    AttachmentPoint attachment() const;
    Acad::ErrorStatus   setAttachment(AttachmentPoint);
    Acad::ErrorStatus   setAttachmentMovingLocation(AttachmentPoint);
    // This latter method will implicitly setLocation based on the
    // relationship of current and new attachment values in order
    // to keep the extents of the MText object constant.

    //  Text flow direction
    //
    enum FlowDirection {
    kLtoR       = 1,
    kRtoL       = 2,    //  not currently supported
    kTtoB       = 3,
    kBtoT       = 4,    //  not currently supported
    kByStyle    = 5
    };
    FlowDirection   flowDirection() const;
    Acad::ErrorStatus   setFlowDirection(FlowDirection);

    //  Text contents
    //
    ACHAR        *contents() const;
    int         setContents(const ACHAR *);
    int         setContentsRTF(const ACHAR *);

    ACHAR        *text() const;

    //  Actual extents
    //
    double      actualHeight(AcGiWorldDraw *ctxt = NULL) const;
    double      actualWidth() const;

    int         correctSpelling();

    //  Return points marking text box
    //
    void        getBoundingPoints(AcGePoint3dArray&) const;

    //  Explode text fragments
    //
    void        explodeFragments(AcDbMTextEnum, void *, AcGiWorldDraw *ctxt = NULL) const;

    //  These strings can be used instead of sprinkling your code 
    //  with string constants.
    static const ACHAR* const nonBreakSpace();   //  \~
    static const ACHAR* const overlineOn();  //  \O
    static const ACHAR* const overlineOff(); //  \o
    static const ACHAR* const underlineOn(); //  \L
    static const ACHAR* const underlineOff();    //  \l
    static const ACHAR* const colorChange(); //  \C
    static const ACHAR* const fontChange();  //  \F
    static const ACHAR* const heightChange();    //  \H
    static const ACHAR* const widthChange(); //  \W
    static const ACHAR* const obliqueChange();   //  \Q
    static const ACHAR* const trackChange(); //  \T
    static const ACHAR* const lineBreak();   //  \p
    static const ACHAR* const paragraphBreak();  //  \P
    static const ACHAR* const stackStart();  //  \S
    static const ACHAR* const alignChange(); //  \A
    static const ACHAR* const blockBegin();  //  {
    static const ACHAR* const blockEnd();    //  }

    Acad::ErrorStatus   setLineSpacingStyle(AcDb::LineSpacingStyle eStyle);
    AcDb::LineSpacingStyle lineSpacingStyle() const;

    // 1.0 = single spaced (default), 2.0 = double-spaced, etc.
    Acad::ErrorStatus   setLineSpacingFactor(double dFactor);
    double              lineSpacingFactor() const;
    
    void                getEcs(AcGeMatrix3d& retVal) const;

    bool backgroundFillOn() const;
    Acad::ErrorStatus setBackgroundFill(bool enable);

    Acad::ErrorStatus getBackgroundFillColor(AcCmColor& color) const;
    Acad::ErrorStatus setBackgroundFillColor(const AcCmColor& color);

    Acad::ErrorStatus getBackgroundScaleFactor(double& scale) const;
    Acad::ErrorStatus setBackgroundScaleFactor(const double scale);

    Acad::ErrorStatus getBackgroundTransparency(AcCmTransparency& transp) const;
    Acad::ErrorStatus setBackgroundTransparency(const AcCmTransparency& transp);

    bool useBackgroundColorOn() const;
    Acad::ErrorStatus setUseBackgroundColor(bool enable);
    
    Acad::ErrorStatus   setField(const ACHAR* pszPropName, AcDbField* pField,
                                 AcDbObjectId& fieldId);

    Acad::ErrorStatus   removeField(AcDbObjectId fieldId);
    Acad::ErrorStatus   removeField(const ACHAR* pszPropName, AcDbObjectId& returnId);
    Acad::ErrorStatus   removeField(const ACHAR* pszPropName);

    Acad::ErrorStatus   convertFieldToText();

    enum ColumnType {
        kNoColumns,
        kStaticColumns,
        kDynamicColumns,
    };

    Acad::ErrorStatus setDynamicColumns(double width, double gutter, bool auto_height);
    Acad::ErrorStatus setStaticColumns(double width, double gutter, int count);
    Acad::ErrorStatus getColumnType(ColumnType&) const;
    Acad::ErrorStatus setColumnType(ColumnType);
    Acad::ErrorStatus getColumnAutoHeight(bool&) const;
    Acad::ErrorStatus setColumnAutoHeight(bool);
    Acad::ErrorStatus getColumnCount(int&) const;
    Acad::ErrorStatus setColumnCount(int);
    Acad::ErrorStatus getColumnWidth(double&) const;
    Acad::ErrorStatus setColumnWidth(double);
    Acad::ErrorStatus getColumnGutterWidth(double&) const;
    Acad::ErrorStatus setColumnGutterWidth(double);
    Acad::ErrorStatus getColumnFlowReversed(bool&) const;
    Acad::ErrorStatus setColumnFlowReversed(bool);
    Acad::ErrorStatus getColumnHeight(int, double&) const;
    Acad::ErrorStatus setColumnHeight(int, double);

    // FOR INTERNAL USE ONLY
    Acad::ErrorStatus   setUseWordBreak(bool bEnable);
    bool useWordBreak() const;
    // FOR INTERNAL USE ONLY
    
    // FOR INTERNAL USE ONLY
    //  Entity height (constraining value)
    // 
    double      height() const;
    Acad::ErrorStatus   setHeight(double);

    // FOR INTERNAL USE ONLY

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
