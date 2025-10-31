// (C) Copyright 1993-2007 by Autodesk, Inc.
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

#ifndef AsdkCurveText_H
#define AsdkCurveText_H

#include "stdafx.h"
#include <dbcurve.h>

//CURVETEXTDBX is defined in the curveText DB project
//export or import the class depending on the
//CURVETEXTDBX symbol
class 
#ifdef CURVETEXTDBX
    _declspec(dllexport)
#endif
AsdkCurveText : public AcDbCurve
{
public:
    // constructors / destructor
    AsdkCurveText();
    AsdkCurveText(AcDbCurve *pCurve);
    AsdkCurveText(AcDbCurve *pCurve, const AsdkCurveText *pCurveText);
    ~AsdkCurveText();

    // AcRxObject methods
    ACRX_DECLARE_MEMBERS(AsdkCurveText);

    // AcDbEntity methods
    Acad::ErrorStatus	setLayer			(AcDbObjectId newVal,
        Adesk::Boolean doSubents = Adesk::kTrue,
        bool allowHiddenLayer = false);
    Acad::ErrorStatus	setLayer			(const TCHAR* newVal,
        Adesk::Boolean doSubents = Adesk::kTrue,
        bool allowHiddenLayer = false);

    Acad::ErrorStatus	setLinetype			(AcDbObjectId newVal,
        Adesk::Boolean doSubents = Adesk::kTrue);
    Acad::ErrorStatus	setLinetype			(const TCHAR* newVal,
        Adesk::Boolean doSubents = Adesk::kTrue);

    Acad::ErrorStatus	setColor			(const AcCmColor& color,
        Adesk::Boolean doSubents = Adesk::kTrue);

    Acad::ErrorStatus	setLinetypeScale	(double ltscale,
        Adesk::Boolean doSubents = Adesk::kTrue);

    Acad::ErrorStatus	setLineWeight		(AcDb::LineWeight newVal,
        Adesk::Boolean doSubents = Adesk::kTrue);

    Adesk::Boolean		worldDraw			(AcGiWorldDraw* pMode);

    Acad::ErrorStatus	dxfInFields			(AcDbDxfFiler* filer);

    Acad::ErrorStatus	dxfOutFields		(AcDbDxfFiler* filer) const;

    Acad::ErrorStatus	dwgInFields			(AcDbDwgFiler* filer);

    Acad::ErrorStatus	dwgOutFields		(AcDbDwgFiler* filer) const;

    Acad::ErrorStatus	transformBy			(const AcGeMatrix3d& xform);

    void				getEcs				(AcGeMatrix3d& retVal) const;

    AcDbEntity*			subentPtr			(const AcDbFullSubentPath& path) const;

    void				saveAs				(AcGiWorldDraw* wd, AcDb::SaveType st);

    Acad::ErrorStatus	getGripPoints		(AcGePoint3dArray& gripPoints,
        AcDbIntArray&     osnapModes,
        AcDbIntArray&     geomIds) const;

    Acad::ErrorStatus	getStretchPoints	(AcGePoint3dArray& stretchPoints) const;

    Acad::ErrorStatus	getOsnapPoints		(AcDb::OsnapMode   osnapMode,
        int gsSelectionMark,
        const AcGePoint3d& pickPoint,
        const AcGePoint3d& lastPoint,
        const AcGeMatrix3d& viewXform,
        AcGePoint3dArray& snapPoints,
        AcDbIntArray&     geomIds) const;

    Acad::ErrorStatus	moveGripPointsAt	(const AcDbIntArray& indices,
        const AcGeVector3d& offset);
    Acad::ErrorStatus	moveStretchPointsAt	(const AcDbIntArray& indices,
        const AcGeVector3d& offset);
    Acad::ErrorStatus   getTransformedCopy	(const AcGeMatrix3d& xform,
        AcDbEntity*&  pEnt) const;
    Acad::ErrorStatus	getGeomExtents		(AcDbExtents& extents) const;

    Acad::ErrorStatus	explode				(AcDbVoidPtrArray& entitySet) const;

    Acad::ErrorStatus getGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath,
        AcDbIntPtrArray&       gsMarkers) const;

    Acad::ErrorStatus getSubentPathsAtGsMarker(AcDb::SubentType    type,
        Adesk::GsMarker     gsMark,
        const AcGePoint3d&  pickPoint,
        const AcGeMatrix3d& viewXform,
        int&                numPaths,
        AcDbFullSubentPath* subentPaths,
        int                 numInserts = 0,
        AcDbObjectId*       entAndInsertStack = NULL) const;


    Acad::ErrorStatus boundingBoxIntersectWith(const AcDbEntity* pEnt,
        AcDb::Intersect   intType,
        AcGePoint3dArray& points,
        int               thisGsMarker,
        int               otherGsMarker) const;

    Acad::ErrorStatus boundingBoxIntersectWith	(const AcDbEntity*	pEnt,
        AcDb::Intersect	intType,
        const AcGePlane&	projPlane,
        AcGePoint3dArray&	points,
        int				thisGsMarker,
        int				otherGsMarker) const;

    Acad::ErrorStatus intersectWith				(const AcDbEntity* pEnt,
        AcDb::Intersect   intType,
        AcGePoint3dArray& points,
        int               thisGsMarker = 0,
        int               otherGsMarker= 0) const;

    Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
        AcDb::Intersect   intType,
        const AcGePlane&  projPlane,
        AcGePoint3dArray& points,
        int               thisGsMarker = 0,
        int               otherGsMarker= 0) const;

    void				list() const;

    // AcDbCurve methods
    DBCURVE_METHODS

        // AsdkCurveText specific methods
        Adesk::Boolean		AcGiFiler			(AcGiWorldDraw* wd, AcDb::SaveType st, AcDbVoidPtrArray&) const ;

    AcGeVector3d		getNormal()		const {assertReadEnabled(); return m_normal;}
    CString				getString()		const {assertReadEnabled(); return m_string;}
    Acad::ErrorStatus	getStyle(CString styleName)	const;
    AcDbObjectId		getStyle()		const {assertReadEnabled(); return m_styleId;}
    double				getSize()		const {assertReadEnabled(); return m_size;}
    double				getSpace()		const {assertReadEnabled(); return m_space;}
    bool				isCurveShown()	const {assertReadEnabled(); return m_showCurve;}
    bool				isTextShown()	const {assertReadEnabled(); return m_showText;}
    bool				isFit()			const {assertReadEnabled(); return m_fit;}
    bool				isRepeatText()	const {assertReadEnabled(); return m_repeat;}
    double				getStartDist()	const {assertReadEnabled(); return m_startDist;}
    double				getLength()		const {assertReadEnabled(); return m_length; }
    Adesk::Int8			getPosition()	const {assertReadEnabled(); return m_position; }
    bool				isReversed()	const {assertReadEnabled(); return m_reverse; }

    void				setNormal(AcGeVector3d normal)	{assertWriteEnabled(); m_normal = normal;}
    void				setString(CString string)		{assertWriteEnabled(); m_string = string;}
    void				setStyle(AcDbObjectId styleId)	{assertWriteEnabled(); m_styleId = styleId;}
    Acad::ErrorStatus	setStyle(CString stylerName);
    void				setSize(double size)			{assertWriteEnabled(); m_size = size;}
    void				setSpace(double space)			{assertWriteEnabled(); m_space = space;}
    void				showCurve(bool show)			{assertWriteEnabled(); m_showCurve = show;}
    void				showText(bool show)				{assertWriteEnabled(); m_showText = show;}
    void				setFit(bool fit)				{assertWriteEnabled(); m_fit = fit;}
    void				setRepeatText(bool repeat)		{assertWriteEnabled(); m_repeat = repeat;}
    void				setRepeatText(BOOL repeat)		{assertWriteEnabled(); m_repeat = repeat? true : false;}
    void				setReverse(BOOL reverse)		{assertWriteEnabled(); m_reverse = reverse? true : false;}
    void				setReverse(bool reverse)		{assertWriteEnabled(); m_reverse = reverse;}
    void				setStartDist(double dist)		{assertWriteEnabled(); m_startDist = dist;}
    void				setLength(double dist)			{assertWriteEnabled(); m_length = dist;}
    void				setPosition(Adesk::Int8 pos)	{assertWriteEnabled(); m_position = pos;}
    void				setCurvePtr(AcDbCurve *pCurve);
    Acad::ErrorStatus	setProperties();
    void				setInJig(bool isInJig)			{m_isInJig = isInJig;}

private:

    AcGeVector3d		m_normal;
    CString				m_string;
    AcDbHardPointerId	m_styleId;
    bool                m_showCurve;
    bool				m_showText;
    bool				m_fit;
    bool				m_reverse;
    bool                m_repeat;
    double              m_size;
    double              m_space;
    double              m_startDist;
    double				m_length;
    Adesk::Int8			m_position;
    AcDbCurve*			m_pCurve;
    bool				m_isInJig;
};

#endif