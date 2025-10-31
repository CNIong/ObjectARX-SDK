//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#ifndef ARXDBGUIPRANGLE_H
#define ARXDBGUIPRANGLE_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrAngle:
**
**  **jma
**
*************************************/

class ArxDbgUiPrAngle : public ArxDbgUiPrBase {

public:

    enum AngleType {
        kAny    = 0,
        kNoZero,
        kRange
    };

                    ArxDbgUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type);
                    ArxDbgUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, const AcGePoint3d& basePt);
    virtual         ~ArxDbgUiPrAngle();

    virtual Status  go();       // issue the prompt
    double          value();

    void            setAngleType(AngleType newType);
    void            setRange(double minVal, double maxVal);
    void            setBasePt(const AcGePoint3d& basePt);
    void            setUseBasePt(bool useIt);
    void            setUseDashedLine(bool useIt);
    void            setUnit(int unit);
    void            setPrecision(int precision);

    void            setAllowNone(bool allowIt);

protected:
        // helper functions
    bool		    inRange();

        // data memebers
    bool			m_allowNone;
    double          m_value;
    double          m_minVal;
    double          m_maxVal;
    AngleType       m_angType;
    AcGePoint3d     m_basePt;
    bool			m_useBasePt;
    bool			m_useDashedLine;
    int             m_unit;
    int             m_precision;

private:
        // helper functions
    void            init();

        // outlawed functions
						ArxDbgUiPrAngle(const ArxDbgUiPrAngle&);
    ArxDbgUiPrAngle&	operator=(const ArxDbgUiPrAngle&);
};

#endif  // ARXDBGUIPRANGLE_H
