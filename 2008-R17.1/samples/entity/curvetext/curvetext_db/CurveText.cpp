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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "CurveText.h"
#include "utils.h"
#include "curvetextIterator.h"

#include <sys/types.h>
#include <sys/timeb.h>



// Object Version
#define VERSION 1
#define kClassName _T("AsdkCurveText")

ACRX_DXF_DEFINE_MEMBERS(AsdkCurveText, AcDbCurve,  
                        AcDb::kDHL_CURRENT, 
                        AcDb::kMReleaseCurrent, 
                        0,
                        ASDKCURVETEXT, 
                        "CurveTextDBX\
                        |Product Desc:     curvetext object enabler\
                        |Company:          Autodesk,Inc.\
                        |WEB Address:      www.autodesk.com");

////////////////////////////////////////////////////////////////////
// constructors / destructor
////////////////////////////////////////////////////////////////////

AsdkCurveText::AsdkCurveText()
{
    m_normal	=	AcGeVector3d(0.0, 0.0, 1.0);
    m_string	=	_T("");
    m_showCurve	=	true;                        
    m_showText	=	true;
    m_fit		=	false;
    m_reverse	=	false;
    m_repeat	=	false;
    m_size		=	1.0;
    m_space		=	1.0;
    m_startDist	=	m_length = 0.0;
    m_position	=	ABOVE;
    m_isInJig	=	false;
    setStyle(_T("standard"));

    // The curve pointer is set to NULL.
    // This implies that an AcDbCurve object created using
    // this constructor is not usable until this pointer,
    // is set.
    // 
    m_pCurve	=	NULL;
}

AsdkCurveText::AsdkCurveText(AcDbCurve *pCurve)
{
    m_normal	=	AcGeVector3d(0.0, 0.0, 1.0);
    m_string	=	_T("");
    m_showCurve	=	true;                        
    m_showText	=	true;
    m_fit		=	false;
    m_reverse	=	false;
    m_repeat	=	false;
    m_size		=	1.0;
    m_space		=	1.0;
    m_startDist	=	m_length = 0.0;
    m_position	=	ABOVE;
    m_isInJig	=	false;

    // Make sure the curve pointer is not NULL
    // since we need this object to live...
    //
    assert(pCurve);

    m_pCurve	=	pCurve;

    // common properties
    //
    setProperties();
}

AsdkCurveText::AsdkCurveText(AcDbCurve *pCurve, const AsdkCurveText *pCurveText)
{
    m_normal	=	pCurveText->getNormal();
    m_string	=	pCurveText->getString();
    m_styleId	=	pCurveText->getStyle();
    m_showCurve	=	pCurveText->isCurveShown();
    m_showText	=	pCurveText->isTextShown();
    m_fit		=	pCurveText->isFit();
    m_reverse	=	pCurveText->isReversed();
    m_space		=	pCurveText->getSpace();
    m_startDist	=	pCurveText->getStartDist();
    m_position	=	pCurveText->getPosition();
    m_repeat	=	pCurveText->isRepeatText();
    m_length	=	pCurveText->getLength();
    m_size		=	pCurveText->getSize();
    m_isInJig	=	false;

    // Make sure the curve pointer is not NULL
    // since we need this object to live...
    //
    assert(pCurve);
    m_pCurve	=	pCurve;
    // common properties
    //
    setProperties();
}

AsdkCurveText::~AsdkCurveText()
{
    // We delete the curve if it is not in the database.
    // (which should always be the case).
    //
    if(m_pCurve != NULL && 
        m_pCurve->objectId() == AcDbObjectId::kNull)
    {
        delete m_pCurve;
        m_pCurve = NULL;
    }
}



////////////////////////////////////////////////////////////////////
// AcDbEntity methods
////////////////////////////////////////////////////////////////////

Adesk::Boolean
AsdkCurveText::worldDraw(AcGiWorldDraw* wd)
{
    if(!m_showText && !wd->isDragging() && !m_isInJig)
        m_showCurve = TRUE;

    // if m_space is 0, then force it to 1 !
    // m_space is the scale factor applied to the space
    // betwee n two characters. If m_space is 0, than all the 
    // characters will display on top of each other.
    //
    if(!m_space)
        m_space = 1.0;

    AcDbVoidPtrArray ptrArray;

    // AcGiFiler is a general purpose function used for worldDraw()
    // but also for explode() and saveAs().
    //
    return AcGiFiler(wd, AcDb::kNoSave, ptrArray);
}

void
AsdkCurveText::saveAs(AcGiWorldDraw* wd, AcDb::SaveType st )
{
    // if m_space is 0, then force it to 1 !
    if(!m_space)
        m_space = 1.0;

    // see comment in AsdkCurveText::worldDraw about
    // AcGiFiler
    //
    AcDbVoidPtrArray ptrArray;
    AcGiFiler(wd, st, ptrArray);
}

Acad::ErrorStatus
AsdkCurveText::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    // apply the transformation to the curve
    //
    assert(m_pCurve);
    ISOK(m_pCurve->transformBy(xform));
    // and to our normal
    //
    if(m_normal.isUnitLength() != Acad::eOk)
        m_normal.normalize();
    m_normal.transformBy(xform);

    // In case of scaling, update the character
    // size and spacement.
    //
    double length = m_normal.length();
    m_size *= length;
    m_normal.normalize();
    // if space between characters is default,
    // leave it this way.
    //
    if(m_space != 1.0)
        m_space *= length;
    return Acad::eOk;
}

Acad::ErrorStatus
AsdkCurveText::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();
    // super message to the parent class
    //
    ISOK(AcDbCurve::dxfInFields(filer));
    // swallow the subclass marker
    //
    if (!filer->atSubclassData(kClassName)) 
        return Acad::eBadDxfSequence;

    // get the curvetext information
    // being order independant
    //
    struct resbuf rb;
    Acad::ErrorStatus es = Acad::eOk;
    while (es == Acad::eOk)
    {
        // when we will reach the embedded object,
        // readItem will return eEndOfFile
        //
        if ((es = filer->readItem(&rb)) == Acad::eOk)
        {
            switch(rb.restype) {
                // Object Version
                //
    case AcDb::kDxfInt16:
        Adesk::Int16 version;
        version = rb.resval.rint;
        if (version > VERSION)
            return Acad::eMakeMeProxy;
        break;
        // Normal
        //
    case AcDb::kDxfNormalX:
        m_normal.set(rb.resval.rpoint[0],
            rb.resval.rpoint[1],
            rb.resval.rpoint[2]);
        break;
        // string
        //
    case AcDb::kDxfXTextString:
        m_string = rb.resval.rstring;
        break;
        // text style Id
        //
    case AcDb::kDxfHardPointerId:
        ads_name styleEname;
        styleEname[0] = rb.resval.rlname[0];
        styleEname[1] = rb.resval.rlname[1];
        acdbGetObjectId(m_styleId, styleEname);
        break;
        // text size
        //
    case AcDb::kDxfTxtSize:
        m_size = rb.resval.rreal;
        break;
        // space between characters
        //
    case AcDb::kDxfReal+1:
        m_space = rb.resval.rreal;
        break;
        // start distance
        //
    case AcDb::kDxfReal+2:
        m_startDist = rb.resval.rreal;
        break;
        // length along the curve
        // to display the string
        //
    case AcDb::kDxfReal+3:
        m_length = rb.resval.rreal;
        break;
        // position w/r/t/ the curve (Above, on or below)
        //
    case AcDb::kDxfInt8:
        // Unicode: Leaving as char type
        m_position = (char)rb.resval.rint;
        break;
        // repeat the text ?
        //
    case AcDb::kDxfBool:
        if(rb.resval.rint)
            m_repeat = true;
        else
            m_repeat = false;
        break;
        // show the curve ?
        //
    case AcDb::kDxfBool+1:
        if(rb.resval.rint)
            m_showCurve = true;
        else
            m_showCurve = false;
        break;
        // show the text?
        //
    case AcDb::kDxfBool+2:
        if(rb.resval.rint)
            m_showText = true;
        else
            m_showText = false;
        break;
        // fit the text?
        //
    case AcDb::kDxfBool+3:
        if(rb.resval.rint)
            m_fit = true;
        else
            m_fit = false;
        break;
        // reverse the text?
        //
    case AcDb::kDxfBool+4:
        if(rb.resval.rint)
            m_reverse = true;
        else
            m_reverse = false;
        break;
        // curve class name
        //
    case AcDb::kDxfXTextString +1:
        // All we know is that the embedded object is a curve
        // (AcDbCurve) which is an abstract class.
        // We need to get the class descriptor object using the
        // class name we saved to reconstruct the exact object.
        //
        CString className;
        className = rb.resval.rstring;
        AcRxClass *pRxClass;
        pRxClass = AcRxClass::cast(acrxClassDictionary->at(className));
        m_pCurve = AcDbCurve::cast(pRxClass->create());
        break;
            }
        }
    }

    // Swallow the embedded object marker
    //
    if (!filer->atEmbeddedObjectStart()) 
        return Acad::eBadDxfSequence;
    // file the information in.
    //
    assert(m_pCurve);
    ISOK(m_pCurve->dxfInFields(filer));
    // We need to ensure that the common properties
    // (like color, layer, line weight, etc.)
    // are properly set for the curve itself.
    //
    ISOK(m_pCurve->setPropertiesFrom(this));
    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkCurveText::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();
    ISOK(AcDbCurve::dxfOutFields(filer));
    ISOK(filer->writeItem(AcDb::kDxfSubclass, kClassName));
    // Object Version
    Adesk::Int16 version = VERSION;
    ISOK(filer->writeItem(AcDb::kDxfInt16, version));
    ISOK(filer->writeItem(AcDb::kDxfNormalX, m_normal));
    ISOK(filer->writeItem(AcDb::kDxfXTextString, m_string));
    ISOK(filer->writeItem(AcDb::kDxfHardPointerId, m_styleId));
    ISOK(filer->writeItem(AcDb::kDxfTxtSize, m_size));
    ISOK(filer->writeItem(AcDb::kDxfReal +1, m_space));
    ISOK(filer->writeItem(AcDb::kDxfReal +2, m_startDist));
    ISOK(filer->writeItem(AcDb::kDxfReal +3, m_length));
    ISOK(filer->writeItem(AcDb::kDxfInt8, m_position));
    ISOK(filer->writeItem(AcDb::kDxfBool, m_repeat));
    ISOK(filer->writeItem(AcDb::kDxfBool +1, m_showCurve));
    ISOK(filer->writeItem(AcDb::kDxfBool +2, m_showText));
    ISOK(filer->writeItem(AcDb::kDxfBool +3, m_fit));
    ISOK(filer->writeItem(AcDb::kDxfBool +4, m_reverse));
    // We need to save what kind of curve we are pointing to.
    // to be able to recreate the object on the other side
    //
    assert(m_pCurve);
    ISOK(filer->writeItem(AcDb::kDxfXTextString+1, m_pCurve->isA()->name()));
    ISOK(filer->writeEmbeddedObjectStart());
    ISOK(m_pCurve->dxfOutFields(filer));
    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkCurveText::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
    ISOK(AcDbCurve::dwgInFields(filer));
    TCHAR *buffer = NULL;
    if (filer->filerType() == AcDb::kIdXlateFiler)
    {
        ISOK(filer->readItem(&m_styleId));
        // Apply Xlate into embedded object
        ISOK(m_pCurve->setPropertiesFrom(this));
        return filer->filerStatus();
    }

    // Object Version
    //
    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > VERSION)
        return Acad::eMakeMeProxy;
    // Normal
    //
    ISOK(filer->readItem(&m_normal));
    // get the text string
    //
    buffer = NULL;
    ISOK(filer->readItem(&buffer));
    m_string = buffer;
    acdbFree(buffer);
    ISOK(filer->readItem(&m_styleId));
    ISOK(filer->readItem(&m_size));
    ISOK(filer->readItem(&m_space));
    ISOK(filer->readItem(&m_startDist));
    ISOK(filer->readItem(&m_length));
    ISOK(filer->readInt8(&m_position));
    ISOK(filer->readItem(&m_repeat));
    ISOK(filer->readItem(&m_showCurve));
    ISOK(filer->readItem(&m_showText));
    ISOK(filer->readItem(&m_fit));
    ISOK(filer->readItem(&m_reverse));

    // Get a pointer of the class
    // descriptor object using the class name
    // saved.
    //
    buffer = NULL;
    filer->readItem(&buffer);
    AcRxClass *pRxClass;
    pRxClass = AcRxClass::cast(acrxClassDictionary->at(buffer));
    acdbFree(buffer);

    // Create an instance of this class if we have to.
    // In case of kIdXlateFiler, there is not need to recreate the object.
    //
    m_pCurve = AcDbCurve::cast(pRxClass->create());

    assert(m_pCurve);
    // Fill it with the information saved
    //
    ISOK(m_pCurve->dwgInFields(filer));
    ISOK(m_pCurve->setPropertiesFrom(this));
    return filer->filerStatus();
}



Acad::ErrorStatus
AsdkCurveText::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();
    ISOK(AcDbCurve::dwgOutFields(filer));

    if (filer->filerType() == AcDb::kIdXlateFiler)
    {
        ISOK(filer->writeItem(m_styleId));
        return filer->filerStatus();
    }

    // Object Version
    //
    Adesk::Int16 version = VERSION;
    ISOK(filer->writeItem(version));

    ISOK(filer->writeItem(m_normal));
    ISOK(filer->writeItem(m_string));
    ISOK(filer->writeItem(m_styleId));
    ISOK(filer->writeItem(m_size)); 
    ISOK(filer->writeItem(m_space));
    ISOK(filer->writeItem(m_startDist));
    ISOK(filer->writeItem(m_length));
    ISOK(filer->writeInt8(m_position));
    ISOK(filer->writeItem(m_repeat));
    ISOK(filer->writeItem(m_showCurve));
    ISOK(filer->writeItem(m_showText));
    ISOK(filer->writeItem(m_fit));
    ISOK(filer->writeItem(m_reverse));
    // We need to tell which curve we are dealing with
    //
    ISOK(filer->writeItem(m_pCurve->isA()->name()));
    ISOK(m_pCurve->dwgOutFields(filer));
    return filer->filerStatus();
}

void
AsdkCurveText::list() const
{
    assertReadEnabled();
    AcDbCurve::list();

    acutPrintf(_T("                           string: %s\n"), m_string);
    CString textStyleName;
    getTextStyleName(textStyleName, m_styleId);
    acutPrintf(_T("                            style: %s\n"), textStyleName);
    acutPrintf(_T("                   start distance: %f\n"), m_startDist);
    acutPrintf(_T("                     end distance: %f\n"), m_startDist + m_length);
    acutPrintf(_T("                        test size: %f\n"), m_size);
    if(m_space != 1.0)
        acutPrintf(_T("         space between characters: %f\n"), m_space);
    else
        acutPrintf(_T("          space between caracters: default\n"));
    if(m_reverse)
        acutPrintf(_T("                         reversed: true\n"), m_size);
    else
        acutPrintf(_T("                         reversed: false\n"), m_size);
    if(m_showCurve)
        acutPrintf(_T("                    curve visible: true\n"), m_size);
    else
        acutPrintf(_T("                    curve visible: false\n"), m_size);
    if(m_showText)
        acutPrintf(_T("                     text visible: true\n"), m_size);
    else
        acutPrintf(_T("                     text visible: false\n"), m_size);
    if(m_fit)
        acutPrintf(_T("                           fit: true\n"), m_size);
    else
        acutPrintf(_T("                              fit: false\n"), m_size);
    if(m_repeat)
        acutPrintf(_T("                  text repetition: true\n"), m_size);
    else
        acutPrintf(_T("                  text repetition: false\n"), m_size);
    acutPrintf(_T("                  EMBEDED CURVE:\n"), m_size);
    m_pCurve->list();
}

/////////////////////////////////////////////////////////
// Many AcDbEntity and AcDbCurve methods simply delegate
// to the embedded curve.
/////////////////////////////////////////////////////////

Acad::ErrorStatus
AsdkCurveText::getGeomExtents(AcDbExtents& extents) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getGeomExtents(extents);
}


Acad::ErrorStatus 
AsdkCurveText::explode(AcDbVoidPtrArray& entitySet) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->explode(entitySet);
    // If the curve does not explode, than it became itself
    // (or actually its clone), a part of the entity set
    // resulting from the opreration
    //
    if(entitySet.isEmpty())
    {
        AcDbCurve *pNewCurve;
        pNewCurve = AcDbCurve::cast(m_pCurve->clone());
        entitySet.append(pNewCurve);
    }
    AcGiFiler(NULL, AcDb::kR12Save, entitySet);
    return Acad::eOk;
}

Acad::ErrorStatus 
AsdkCurveText::getGripPoints(AcGePoint3dArray& gripPoints,
                             AcDbIntArray&     osnapModes,
                             AcDbIntArray&     geomIds) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getGripPoints(gripPoints, osnapModes, geomIds);
}

Acad::ErrorStatus
AsdkCurveText::getOsnapPoints(AcDb::OsnapMode     osnapMode,
                              int                 gsSelectionMark,
                              const AcGePoint3d&  pickPoint,
                              const AcGePoint3d&  lastPoint,
                              const AcGeMatrix3d& viewXform,
                              AcGePoint3dArray&   snapPoints,
                              AcDbIntArray&       geomIds) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint,
        viewXform, snapPoints, geomIds);
}

Acad::ErrorStatus
AsdkCurveText::getGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath,
                                        AcDbIntPtrArray&       gsMarkers) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getGsMarkersAtSubentPath(subPath, gsMarkers);
}

Acad::ErrorStatus
AsdkCurveText::getSubentPathsAtGsMarker(AcDb::SubentType    type,
                                        Adesk::GsMarker     gsMark,
                                        const AcGePoint3d&  pickPoint,
                                        const AcGeMatrix3d& viewXform,
                                        int&                numPaths,
                                        AcDbFullSubentPath* subentPaths,
                                        int                 numInserts,
                                        AcDbObjectId*       entAndInsertStack) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getSubentPathsAtGsMarker(type, gsMark, pickPoint, viewXform, numPaths,
        subentPaths, numInserts, entAndInsertStack);
}



Acad::ErrorStatus 
AsdkCurveText::getStretchPoints(AcGePoint3dArray& stretchPoints) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getStretchPoints(stretchPoints);
}

Acad::ErrorStatus
AsdkCurveText::moveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset)
{
    assertWriteEnabled();
    assert(m_pCurve);
    return m_pCurve->moveGripPointsAt(indices, offset);
}

Acad::ErrorStatus
AsdkCurveText::moveStretchPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset)
{
    assertWriteEnabled();
    assert(m_pCurve);
    return m_pCurve->moveStretchPointsAt(indices, offset);
}

Acad::ErrorStatus 
AsdkCurveText::boundingBoxIntersectWith(const AcDbEntity* pEnt,
                                        AcDb::Intersect   intType,
                                        AcGePoint3dArray& points,
                                        int               thisGsMarker,
                                        int               otherGsMarker) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->boundingBoxIntersectWith(pEnt, intType, points, 
        thisGsMarker, otherGsMarker);
}

Acad::ErrorStatus
AsdkCurveText::boundingBoxIntersectWith(const AcDbEntity* pEnt,
                                        AcDb::Intersect   intType,
                                        const AcGePlane&  projPlane,
                                        AcGePoint3dArray& points,
                                        int               thisGsMarker,
                                        int               otherGsMarker) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->boundingBoxIntersectWith(pEnt, intType, projPlane,
        points, thisGsMarker, otherGsMarker);
}

Acad::ErrorStatus
AsdkCurveText::intersectWith(const AcDbEntity* pEnt,
                             AcDb::Intersect   intType,
                             const AcGePlane&  projPlane,
                             AcGePoint3dArray& points,
                             int               thisGsMarker,
                             int               otherGsMarker) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->intersectWith(pEnt, intType, projPlane, points, thisGsMarker, otherGsMarker);
}

Acad::ErrorStatus
AsdkCurveText::intersectWith(const AcDbEntity* pEnt,
                             AcDb::Intersect   intType,
                             AcGePoint3dArray& points,
                             int               thisGsMarker,
                             int               otherGsMarker) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->intersectWith(pEnt, intType, points, thisGsMarker, otherGsMarker);
}

AcDbEntity* 
AsdkCurveText::subentPtr(const AcDbFullSubentPath& path) const
{
    assertReadEnabled();
    assert(m_pCurve);
    AcDbEntity *pEnt = m_pCurve->subentPtr(path);
    return pEnt;
}

Acad::ErrorStatus 
AsdkCurveText::getTransformedCopy(const AcGeMatrix3d& xform,
                                  AcDbEntity*&  pEnt) const
{
    assertReadEnabled();
    // We need to check the value returned
    // by the curve getTransformedCopy because
    // for example AcDbPolyline will return
    // eExplodeBeforeTransform.
    // In es is not eOk, we simply return es;
    //
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getTransformedCopy(xform, pEnt);
    if(es != Acad::eOk)
        return es;
    AsdkCurveText *pCurveText = new AsdkCurveText(AcDbCurve::cast(pEnt), this);
    pEnt = AcDbEntity::cast(pCurveText);
    return Acad::eOk;
}


void
AsdkCurveText::getEcs(AcGeMatrix3d& retVal) const
{
    assertReadEnabled();
    assert(m_pCurve);
    m_pCurve->getEcs(retVal);
}


////////////////////////////////////////////////////////////////////
// AcDbCurve methods
////////////////////////////////////////////////////////////////////
Adesk::Boolean 
AsdkCurveText::isClosed() const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->isClosed();
}

Adesk::Boolean
AsdkCurveText::isPeriodic() const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->isPeriodic();
}

Adesk::Boolean
AsdkCurveText::isPlanar() const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->isPlanar();
}

Acad::ErrorStatus
AsdkCurveText::getPlane(AcGePlane& plane, AcDb::Planarity& planarity) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getPlane(plane, planarity);
}

Acad::ErrorStatus
AsdkCurveText::getStartParam(double& param) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getStartParam(param);
}

Acad::ErrorStatus
AsdkCurveText::getEndParam(double& param) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getEndParam(param);
}

Acad::ErrorStatus 
AsdkCurveText::getStartPoint(AcGePoint3d& point) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getStartPoint(point);
}


Acad::ErrorStatus
AsdkCurveText::getEndPoint(AcGePoint3d& point) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getEndPoint(point);
}


Acad::ErrorStatus
AsdkCurveText::getPointAtParam(double param, AcGePoint3d& point) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getPointAtParam(param, point);
}

Acad::ErrorStatus
AsdkCurveText::getParamAtPoint(const AcGePoint3d& point, double& param) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getParamAtPoint(point, param);
}



Acad::ErrorStatus
AsdkCurveText::getDistAtParam(double param, double& dist) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getDistAtParam(param, dist);
}

Acad::ErrorStatus
AsdkCurveText::getParamAtDist(double dist , double& param) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getParamAtDist(dist, param);
}


Acad::ErrorStatus
AsdkCurveText::getDistAtPoint(const AcGePoint3d& point, double& dist) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getDistAtPoint(point, dist);
}

Acad::ErrorStatus
AsdkCurveText::getPointAtDist(double dist, AcGePoint3d& point) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getPointAtDist(dist, point);
}


Acad::ErrorStatus
AsdkCurveText::getFirstDeriv(double param, AcGeVector3d& vect) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getFirstDeriv(param, vect);
}

Acad::ErrorStatus
AsdkCurveText::getFirstDeriv(const AcGePoint3d& point, AcGeVector3d& vect)const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getFirstDeriv(point, vect);
}



Acad::ErrorStatus
AsdkCurveText::getSecondDeriv(double dist, AcGeVector3d& vect) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getSecondDeriv(dist, vect);
}



Acad::ErrorStatus
AsdkCurveText::getSecondDeriv(const AcGePoint3d& point, AcGeVector3d& vect) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getSecondDeriv(point, vect);
}


Acad::ErrorStatus
AsdkCurveText::getClosestPointTo(const AcGePoint3d& pt, AcGePoint3d& ptres,
                                 Adesk::Boolean log) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getClosestPointTo(pt, ptres, log);
}



Acad::ErrorStatus
AsdkCurveText::getClosestPointTo(const AcGePoint3d& pt, const AcGeVector3d& dir,
                                 AcGePoint3d& ptres, Adesk::Boolean log) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getClosestPointTo(pt, dir, ptres, log);
}


Acad::ErrorStatus
AsdkCurveText::getOrthoProjectedCurve(const AcGePlane& plane, AcDbCurve*& curve) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getOrthoProjectedCurve(plane, curve);
    AsdkCurveText *pCurveText;
    pCurveText = new AsdkCurveText(curve, this);
    curve = AcDbCurve::cast(pCurveText);
    return es;
}



Acad::ErrorStatus
AsdkCurveText::getProjectedCurve(const AcGePlane& plane, const AcGeVector3d& dir,
                                 AcDbCurve*& curve) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getProjectedCurve(plane, dir, curve);
    AsdkCurveText *pCurveText;
    pCurveText = new AsdkCurveText(curve, this);
    curve = AcDbCurve::cast(pCurveText);
    return es;
}



Acad::ErrorStatus
AsdkCurveText::getOffsetCurves(double offset, AcDbVoidPtrArray& offsetCurves) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getOffsetCurves(offset, offsetCurves);

    if(es != Acad::eOk)
        return es;

    int length = offsetCurves.length();
    AsdkCurveText *pCurveText;
    AcDbCurve *pOffsetCurve;

    for(int i=0; i<length; i++)
    {
        pOffsetCurve = AcDbCurve::cast((AcRxObject *)offsetCurves[i]);
        if(pOffsetCurve == NULL)
            continue;
        pCurveText = new AsdkCurveText(pOffsetCurve, this);
        offsetCurves[i] = pCurveText;
    }

    return Acad::eOk;
}


Acad::ErrorStatus
AsdkCurveText::getSpline(AcDbSpline*& spline) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getSpline(spline);
    AsdkCurveText* pCurveText;
    pCurveText = new AsdkCurveText( AcDbCurve::cast(spline), this);
    spline = AcDbSpline::cast(pCurveText);

    return es;
}



Acad::ErrorStatus
AsdkCurveText::getSplitCurves(const AcGeDoubleArray& darray,
                              AcDbVoidPtrArray& curveSegments) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getSplitCurves(darray, curveSegments);
    if(es != Acad::eOk)
        return es;
    int length = curveSegments.length();
    AsdkCurveText *pCurveText;
    for(int i =0; i<length; i++)
    {
        pCurveText = new AsdkCurveText( AcDbCurve::cast((AcRxObject *)curveSegments[i]), this);
        curveSegments[i] = pCurveText;
    }

    return Acad::eOk;
}


Acad::ErrorStatus
AsdkCurveText::getSplitCurves(const AcGePoint3dArray& parray,
                              AcDbVoidPtrArray& curveSegments) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    assert(m_pCurve);
    es = m_pCurve->getSplitCurves(parray, curveSegments);
    if(es != Acad::eOk)
        return es;

    int length = curveSegments.length();
    AsdkCurveText *pCurveText;
    for(int i =0; i<length; i++)
    {
        pCurveText = new AsdkCurveText( AcDbCurve::cast((AcRxObject *)curveSegments[i]), this);
        curveSegments[i] = pCurveText;
    }

    return Acad::eOk;
}


Acad::ErrorStatus 
AsdkCurveText::extend(double newParam)
{
    assertWriteEnabled();
    assert(m_pCurve);
    return m_pCurve->extend(newParam);
}


Acad::ErrorStatus 
AsdkCurveText::extend(Adesk::Boolean extendStart,
                      const AcGePoint3d& toPoint)
{
    assertWriteEnabled();
    assert(m_pCurve);
    return m_pCurve->extend(extendStart, toPoint);
}



Acad::ErrorStatus 
AsdkCurveText::getArea(double& area) const
{
    assertReadEnabled();
    assert(m_pCurve);
    return m_pCurve->getArea(area);
}


////////////////////////////////////////////////////////////////////
// AsdkCurveText specific methods
////////////////////////////////////////////////////////////////////


void 
AsdkCurveText::setCurvePtr(AcDbCurve* pCurve)
{
    assertWriteEnabled();
    assert(pCurve != NULL);
    m_pCurve = pCurve;
    setProperties();
}

Acad::ErrorStatus
AsdkCurveText::setProperties()
{
    assertWriteEnabled();
    // common entity properties
    //
    ISOK(setPropertiesFrom(m_pCurve));
    return Acad::eOk;
}

Acad::ErrorStatus
AsdkCurveText::setLineWeight(AcDb::LineWeight newVal, Adesk::Boolean doSubents)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLineWeight(newVal, doSubents));
    return AcDbEntity::setLineWeight(newVal, doSubents);
}

Acad::ErrorStatus
AsdkCurveText::setLayer(AcDbObjectId newVal, Adesk::Boolean doSubents, bool allowHiddenLayer)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLayer(newVal, doSubents,allowHiddenLayer));
    return AcDbEntity::setLayer(newVal, doSubents, allowHiddenLayer);
}

Acad::ErrorStatus
AsdkCurveText::setLayer(const TCHAR* newVal, Adesk::Boolean doSubents, bool allowHiddenLayer)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLayer(newVal, doSubents, allowHiddenLayer));
    return AcDbEntity::setLayer(newVal, doSubents, allowHiddenLayer);
}

Acad::ErrorStatus
AsdkCurveText::setLinetype(AcDbObjectId newVal, Adesk::Boolean doSubents)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLinetype(newVal, doSubents));
    return AcDbEntity::setLinetype(newVal, doSubents);
}

Acad::ErrorStatus
AsdkCurveText::setLinetype(const TCHAR* newVal, Adesk::Boolean doSubents)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLinetype(newVal, doSubents));
    return AcDbEntity::setLinetype(newVal, doSubents);
}

Acad::ErrorStatus
AsdkCurveText::setColor(const AcCmColor& color, Adesk::Boolean doSubents)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setColor(color, doSubents));
    return AcDbEntity::setColor(color, doSubents);
}

Acad::ErrorStatus
AsdkCurveText::setLinetypeScale(const double ltscale, Adesk::Boolean doSubents)
{
    assertWriteEnabled();
    if(m_pCurve != NULL)
        ISOK(m_pCurve->setLinetypeScale(ltscale, doSubents));
    return AcDbEntity::setLinetypeScale(ltscale, doSubents);
}



Acad::ErrorStatus
AsdkCurveText::setStyle(CString string)
{
    assertWriteEnabled();
    AcDbDatabase * pDb = database();
    if(pDb == NULL)
        pDb = acdbHostApplicationServices()->workingDatabase();
    if(pDb == NULL)
        return Acad::eNoDatabase ;
    AcDbTextStyleTable *pTsTable;
    ISOK(pDb->getTextStyleTable(pTsTable, AcDb::kForRead));
    ISOK(pTsTable->getAt(string, m_styleId));
    pTsTable->close();
    return Acad::eOk;
}

Acad::ErrorStatus
AsdkCurveText::getStyle(CString styleName) const
{
    assertReadEnabled();
    // getTextStyleName is defined in utils.h
    ISOK(getTextStyleName(styleName, m_styleId));
    return Acad::eOk;
}

Adesk::Boolean
AsdkCurveText::AcGiFiler(AcGiWorldDraw* wd, AcDb::SaveType st, AcDbVoidPtrArray &entitySet) const
{
    assertReadEnabled();

    // Checks if m_pCurve is of type AsdkCurveText.
    // in which case we'll take special precautions.
    //
    assert(m_pCurve);
    AsdkCurveText *pct = AsdkCurveText::cast(m_pCurve);
    if(NULL != pct)
    {
        pct->showCurve(isCurveShown());
        pct->showText(isTextShown());
        pct->worldDraw(wd);
    }


    // The only case where the AcGiWorldDraw parameter would be NULL
    // is when we are called from explode.
    //
    if(NULL != wd)
    {
        // This is not explode
        //
        // Draw the curve only if we have to.
        //
        if((m_showCurve && !m_isInJig) ||
            (!m_showCurve && wd->isDragging() && !m_isInJig))
        {
            if(st == AcDb::kNoSave)
            {
                if(NULL == pct)
                {
                    // Contained entity rendering.
                    // This is better than draw() for contained AcDbCurve.
                    m_pCurve->worldDraw(wd);
                }
            }
            else
                m_pCurve->saveAs(wd, st);
        }

        if(!m_showText && !wd->isDragging() && !m_isInJig)
        {
            // The text is not displayed, we are not dragging
            // and we are not being called from the jig.
            // In this case, that's all we need to do.
            //
            return Adesk::kTrue;
        }
    } 

    CcurvetextIterator* pCtIt = new CcurvetextIterator(this, wd);
    assert(pCtIt);
    AcGePoint3d currentPoint;

    short ctrl = GetKeyState(VK_CONTROL);
    ctrl = ctrl >> 1;

    // If the conditions below are satisfied, we swtich to the
    // "fast display" mode which draws the start point and end point
    // of the text instead of each character
    //
    Acad::ErrorStatus es;
    if(!ctrl && !global.dynamicDisplay && wd)
    {
        if(m_isInJig || wd->isDragging())
        {
            es = pCtIt->getCurrentPosition(currentPoint);
            if(es != Acad::eOk)
            {
                delete pCtIt;
                return Adesk::kTrue;
            }
            AcGePoint3d endPoint;
            es = pCtIt->getEndPosition(endPoint);
            if(es != Acad::eOk)
            {
                delete pCtIt;
                return Adesk::kTrue;
            }

            AcGeVector3d xAxis, yAxis;
            xAxis = m_size * acdbHostApplicationServices()->workingDatabase()->ucsxdir();
            yAxis = m_size * acdbHostApplicationServices()->workingDatabase()->ucsydir();

            // The horizontal and vertical line segments
            // for the crosses to draw.
            //
            AcGePoint3d X[2], Y[2];
            wd->subEntityTraits().setColor(1);
            X[0] = endPoint + xAxis;
            X[1] = endPoint - xAxis;
            Y[0] = endPoint + yAxis;
            Y[1] = endPoint - yAxis;
            wd->geometry().polyline(2, X);
            wd->geometry().polyline(2, Y);

            // repeat for the start point
            // with a different color (green)
            //
            wd->subEntityTraits().setColor(3);
            X[0] = currentPoint + xAxis;
            X[1] = currentPoint - xAxis;
            Y[0] = currentPoint + yAxis;
            Y[1] = currentPoint - yAxis;
            wd->geometry().polyline(2, X);
            wd->geometry().polyline(2, Y);
            delete pCtIt;
            return Adesk::kTrue;
        }
    }

    AcGeVector3d currentDirection, perp;
    TCHAR string[2];
    string[1] = _T('\0');
    AcGeMatrix3d rotate;
    if(m_position)
        rotate.setToRotation(-PI / 2.0, m_normal);

    for ( ; !pCtIt->done(); pCtIt->step())
    {
        es = pCtIt->getCurrentPosition(currentPoint);
        if(es != Acad::eOk)
        {
            delete pCtIt;
            return Adesk::kTrue;
        }
        es = pCtIt->getCurrentDirection(currentDirection);
        if(es != Acad::eOk)
        {
            delete pCtIt;
            return Adesk::kTrue;
        }
        if(m_position)
        {
            perp = currentDirection;
            perp.normalize();
            perp.transformBy(rotate);
            if(m_position == 1)
                currentPoint = currentPoint + (perp * (m_size / 2.0));
            else
                currentPoint = currentPoint + perp * m_size;
        }

        string[0] = pCtIt->getCurrentCharacter();

        if(wd != NULL)
        {
            wd->geometry().text(currentPoint, m_normal, currentDirection, string, 1, Adesk::kTrue, pCtIt->getTextStyle());
        }
        else
        {
            // case of explode
            //
            AcGePlane plane(currentPoint, m_normal);
            AcGeVector3d textXaxis, textYaxis;
            plane.getCoordSystem(currentPoint, textXaxis, textYaxis);
            double angle = textXaxis.angleTo(currentDirection, m_normal);
            AcDbText* pText = new AcDbText(currentPoint, string, m_styleId, m_size, angle);
            ASSERT(pText);
            pText->setNormal(m_normal);
            entitySet.append(pText);
        }
    }
    delete pCtIt;
    return Adesk::kTrue;
}
