// (C) Copyright 1993-1998 by Autodesk, Inc.
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

#ifndef CURVETEXT_HELPER_H
#define CURVETEXT_HELPER_H


void curveTextMulti();
void curvetextEdit(AcDbObjectIdArray& curvesArray);
void setStart();
void setStart(AcDbObjectId id);
void setEnd();
void setEnd(AcDbObjectId id);
void reverse();
void reverse(AcDbObjectIdArray& idArray);
void ShowCurve();
void HideCurve();
void ShowCurve(bool show);
void ShowCurve(bool show, AcDbObjectIdArray& curvesArray);
void ShowText();
void HideText();
void ShowText(bool show);
void ShowText(bool show, AcDbObjectIdArray& curvesArray);
void fit();
void DoNotFit();
void setFit(bool fit);
void setFit(bool fit, AcDbObjectIdArray& curvesArray);
void RepeatText();
void DoNotRepeatText();
void repeatText(bool repeat);
void repeatText(bool repeat, AcDbObjectIdArray& curvesArray);



#endif