//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  AcCmColor.h
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION: AcCmColor Definitions

// headers
#pragma once

#include "adesk.h"
#include "dbcolor.h"
#include "acutAcString.h"
#include "acdb.h"

extern const wchar_t kszAutoCAD_Color_Index[];
extern const wchar_t kszUNNAMED[];

class AcDbDxfFiler;
class AcDbAuditInfo;
class AcDbDwgFiler;
class AcCmColor : public AcCmColorBase
{
public:
    ACDBCORE2D_PORT AcCmColor();
    ACDBCORE2D_PORT AcCmColor(const AcCmColor&);
    ACDBCORE2D_PORT AcCmColor(const AcCmColorBase&);
    ACDBCORE2D_PORT AcCmColor& operator=(const AcCmColor& inputColor);
    AcCmColor& operator=(const AcCmColorBase& inputColor);
    ACDBCORE2D_PORT AcCmColor(const AcCmEntityColor&);
    ACDBCORE2D_PORT AcCmColor& operator=(const AcCmEntityColor& inputColor);
    ACDBCORE2D_PORT ~AcCmColor();

    ACDBCORE2D_PORT bool operator ==(const AcCmColor& color) const;
    ACDBCORE2D_PORT bool operator !=(const AcCmColor& color) const;
    bool operator ==(const AcCmColorBase& color) const;
    bool operator !=(const AcCmColorBase& color) const;

    ACDBCORE2D_PORT Acad::ErrorStatus getDescription(AcString& desc) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getExplanation(AcString& expl) const;
#define AcCmColor_Deprecated_ACHAR_Methods
#ifdef AcCmColor_Deprecated_ACHAR_Methods
    // deprecated methods, please use the above overloads
    Acad::ErrorStatus getDescription(ACHAR*& desc) const;
    Acad::ErrorStatus getExplanation(ACHAR*& expl) const;
#endif
    AcCmEntityColor::ColorMethod  colorMethod() const override;

    void setNone() override {
        mColor.setNone();
    }
    void setByBlock() override {
        mColor.setByBlock();
    }
    void setForeground() override {
        mColor.setForeground();
    }
    void setLayerOff() override {
        mColor.setLayerOff();
    }
    void setByLayer() override {
        mColor.setByLayer();
    }
    bool    isByColor() const override;
    bool    isByLayer() const override;
    bool    isByBlock() const override;
    bool    isByACI()   const override;
    bool    isByPen() const override;
    bool    isForeground()   const override;

    bool            isNone() const;

    Acad::ErrorStatus setRGB(Adesk::UInt8 red,
        Adesk::UInt8 green,
        Adesk::UInt8 blue) override;

    ACDBCORE2D_PORT Adesk::UInt8      red() const override;
    ACDBCORE2D_PORT Adesk::UInt8      green() const override;
    ACDBCORE2D_PORT Adesk::UInt8      blue() const override;

    // 32-bit RGB value in Win32 COLORREF format 0x00bbggrr
    ACDBCORE2D_PORT Acad::ErrorStatus   setCOLORREF(Adesk::ColorRef cref) override;
    ACDBCORE2D_PORT Adesk::ColorRef     getCOLORREF() const override;

    // 32-bit RGB value with Win32 RGBQUAD format 0x00rrggbb 
    ACDBCORE2D_PORT Acad::ErrorStatus   setRGB(Adesk::RGBQuad rgbquad) override;
    ACDBCORE2D_PORT Adesk::RGBQuad      getRGB() const override;

    // 32-bit color value in AutoCAD RGBM format 0xmmrrggbb
    ACDBCORE2D_PORT Acad::ErrorStatus   setRGBM(Adesk::UInt32 rgbmValue) override;
    ACDBCORE2D_PORT Adesk::UInt32       getRGBM() const override;

    Adesk::UInt16     colorIndex() const override;
    ACDBCORE2D_PORT Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex) override;
    Adesk::UInt16     penIndex() const override;
    Acad::ErrorStatus setPenIndex(Adesk::UInt16 penIndex) override;

    Acad::ErrorStatus setNames(const ACHAR* colorName,
        const ACHAR* bookName = nullptr) override;
    const ACHAR* colorName(void) const override;
    const ACHAR* bookName(void) const override;
    const ACHAR* colorNameForDisplay(void) override;
    bool              hasColorName(void) const override;
    bool              hasBookName(void) const override;

    AcCmEntityColor           entityColor(void) const;
    int                       dictionaryKeyLength(void) const;

    ACDBCORE2D_PORT Acad::ErrorStatus getDictionaryKey(AcString& sKey) const;
#ifdef AcCmColor_Deprecated_ACHAR_Methods
    Acad::ErrorStatus       getDictionaryKey(ACHAR* pKey, size_t nLen) const;   // deprecated
#endif
    Acad::ErrorStatus       setNamesFromDictionaryKey(const ACHAR* pKey);

    Acad::ErrorStatus dwgIn(AcDbDwgFiler* pInputFiler);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler* pOutputFiler) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler, int groupCodeOffset = 0);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler, int groupCodeOffset = 0) const;

    Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    // If pBuff is null, then still compute number of output bytes to be written
    // pBuflen cannot be null.  Points to the location receiving number of output bytes
    // Note: there is currently no input size arg provided for the output buffer
    // For now, is is assumed that the output will fit in the buffer
    ACDBCORE2D_PORT Acad::ErrorStatus serializeOut(void* pBuff, int* pBuflen,
        AcDb::AcDbDwgVersion ver = AcDb::kDHL_CURRENT) const;

    // nDataSizeIn is number of input data bytes
    // PDataSizeOut, if not null, receives number of data bytes used
    ACDBCORE2D_PORT Acad::ErrorStatus serializeIn(const void* pBuff,
                                                  size_t nDataSizeIn, int* pDataSizeOut = nullptr);
    // Deprecated, please use above overload
    // Fails if pBuflen is null
    ACDBCORE2D_PORT Acad::ErrorStatus serializeIn(const void* pBuff, int* pBuflen);

    static const Adesk::UInt16 MaxColorIndex;

    Acad::ErrorStatus dwgInAsTrueColor(AcDbDwgFiler* pInputFiler); // For internal use only
    Acad::ErrorStatus dwgOutAsTrueColor(AcDbDwgFiler* pOutputFiler) const; // For internal use only

private:

    enum NameFlags {
        kNoNames = 0x00,
        kHasColorName = 0x01,
        kHasBookName = 0x02
    };

    static const Adesk::UInt16 ComplexColorFlag;

    AcCmEntityColor         mColor;
    AcString                msColorName;
    AcString                msBookName;
    Adesk::UInt8            mNameFlags = 0;
#ifdef AcCmColor_DEPRECATED_METHODS
public:
    [[deprecated("Prefer specific setMethod() calls to this generic call")]] ACDBCORE2D_PORT Acad::ErrorStatus setColorMethod(AcCmEntityColor::ColorMethod eColorMethod) override;
    [[deprecated("Use getRGBM() or getRGB()")]] ACDBCORE2D_PORT Adesk::UInt32 color() const override;
    [[deprecated("Use setRGBM() or setRGB()")]] ACDBCORE2D_PORT Acad::ErrorStatus setColor(Adesk::UInt32 color) override;
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT Acad::ErrorStatus setRed(Adesk::UInt8 red) override;
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT Acad::ErrorStatus setGreen(Adesk::UInt8 green) override;
    [[deprecated("Use setRGB()")]] ACDBCORE2D_PORT Acad::ErrorStatus setBlue(Adesk::UInt8 blue) override;
#endif
};

#ifdef AcCmColor_Deprecated_ACHAR_Methods
inline Acad::ErrorStatus AcCmColor::getDescription(ACHAR*& desc) const
{
    return ::acutGetAcStringConvertToAChar<AcCmColor>(this, &AcCmColor::getDescription, desc);
}

inline Acad::ErrorStatus AcCmColor::getExplanation(ACHAR*& expl) const
{
    return ::acutGetAcStringConvertToAChar<AcCmColor>(this, &AcCmColor::getExplanation, expl);
}

inline Acad::ErrorStatus AcCmColor::getDictionaryKey(ACHAR* pKey, size_t nLen) const
{
    if (nLen <= 0 || pKey == nullptr)
        return Acad::eInvalidInput;
    AcString sRet;
    const Acad::ErrorStatus es = this->getDictionaryKey(sRet);
    if (es != Acad::eOk) {
        pKey[0] = 0;
        return es;
    }
    for (size_t i = 0; ; i++) {
        if (i == nLen) {
            pKey[i - 1] = 0;
            return Acad::eBufferTooSmall;
        }
        pKey[i] = sRet[i];
        if (sRet[i] == 0)
            return Acad::eOk;
    }
}

#endif

