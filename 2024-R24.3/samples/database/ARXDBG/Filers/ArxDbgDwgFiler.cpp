//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgDwgFiler.h"
#include "ArxDbgUtils.h"
#include "ArxDbgRbList.h"



ACRX_CONS_DEFINE_MEMBERS(ArxDbgDwgFiler, AcDbDwgFiler, 0);

/****************************************************************************
**
**  ArxDbgDwgFiler::ArxDbgDwgFiler
**
**  **jma
**
*************************************/

ArxDbgDwgFiler::ArxDbgDwgFiler()
:   m_stat(Acad::eOk),
    m_filerType(AcDb::kCopyFiler)
{
}

/****************************************************************************
**
**  ArxDbgDwgFiler::~ArxDbgDwgFiler
**
**  **jma
**
*************************************/

ArxDbgDwgFiler::~ArxDbgDwgFiler()
{
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readBytes
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxDbgDwgFiler::readBytes(void *buf, Adesk::UIntPtr cnt)
{
    m_str = _T("");
    printIt(_T("readBytes"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readAddress
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readAddress(void** pp)
{
    m_str = _T("");
    printIt(_T("readAddress"));

    return Acad::eOk;
}


/****************************************************************************
**
**  ArxDbgDwgFiler::readString
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readString(ACHAR **pVal)
{
    m_str = _T("");
    printIt(_T("readString"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::readString(AcString & s)
{
    m_str = _T("");
    printIt(_T("readString(AcString &)"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readBChunk
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readBChunk(ads_binary *pVal)
{
    m_str = _T("");
    printIt(_T("readBChunk"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readAcDbHandle
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readAcDbHandle(AcDbHandle *pVal)
{
    m_str = _T("");
    printIt(_T("readAcDbHandle"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::readInt64(Adesk::Int64 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readInt32(Adesk::Int32 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readInt16(Adesk::Int16 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt16"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::readInt8(Adesk::Int8 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt8"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::readUInt64(Adesk::UInt64 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readUInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readUInt32(Adesk::UInt32 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readUInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readUInt16(Adesk::UInt16 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt16"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readUInt8
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readUInt8(Adesk::UInt8 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt8"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readBoolean
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readBoolean(Adesk::Boolean *pVal)
{
    m_str = _T("");
    printIt(_T("readBoolean"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readBool
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readBool(bool *pVal)
{
    m_str = _T("");
    printIt(_T("readBool"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readHardOwnershipId(AcDbHardOwnershipId* pId)
{
    m_str = _T("");
    printIt(_T("readHardOwnershipId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readSoftOwnershipId(AcDbSoftOwnershipId* pId)
{
    m_str = _T("");
    printIt(_T("readSoftOwnershipId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readHardPointerId(AcDbHardPointerId* pId)
{
    m_str = _T("");
    printIt(_T("readHardPointerId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readSoftPointerId(AcDbSoftPointerId* pId)
{
    m_str = _T("");
    printIt(_T("readSoftPointerId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readDouble
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readDouble(double *pVal)
{
    m_str = _T("");
    printIt(_T("readDouble"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readPoint2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readPoint2d(AcGePoint2d *pVal)
{
    m_str = _T("");
    printIt(_T("readPoint2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readPoint3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readPoint3d(AcGePoint3d *pVal)
{
    m_str = _T("");
    printIt(_T("readPoint3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readVector2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readVector2d(AcGeVector2d *pVal)
{
    m_str = _T("");
    printIt(_T("readVector2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readVector3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readVector3d(AcGeVector3d *pVal)
{
    m_str = _T("");
    printIt(_T("readVector3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::readScale3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::readScale3d(AcGeScale3d *pVal)
{
    m_str = _T("");
    printIt(_T("readScale3d"));

    return Acad::eOk;
}



/****************************************************************************
**
**  ArxDbgDwgFiler::writeBytes
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeBytes(const void *buf, Adesk::UIntPtr cnt)
{
    m_str.Format(_T("cnt = %ld"), cnt);
    printIt(_T("writeBytes"));

    return Acad::eOk;    
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeAddress
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeAddress(const void* p)
{
    m_str = "";
    m_str.Format(_T("%p"), p);
    printIt(_T("writeAddress"));

    return Acad::eOk;
}


/****************************************************************************
**
**  ArxDbgDwgFiler::writeString
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeString(const ACHAR *pVal)
{
    m_str.Format(_T("\"%s\""), pVal);
    printIt(_T("writeString"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::writeString(const AcString &s)
{
    m_str.Format(_T("\"%s\""), s.kTCharPtr());
    printIt(_T("writeString"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeBChunk
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeBChunk(const ads_binary &val)
{
    CString hexStr;

    bytesToHexStr(val.buf, val.clen, hexStr);
    m_str.Format(_T("%s"), hexStr);
    printIt(_T("writeBChunk"));

    return Acad::eOk;
  }

/****************************************************************************
**
**  ArxDbgDwgFiler::writeAcDbHandle
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeAcDbHandle(const AcDbHandle& val)
{
    TCHAR tmpStr[256];
    val.getIntoAsciiBuffer(tmpStr);

    m_str.Format(_T("%s"), tmpStr);
    printIt(_T("writeAcDbHandle"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::writeInt64(Adesk::Int64 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeInt32(Adesk::Int32 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeInt16(Adesk::Int16 val)
{
    m_str.Format(_T("%d"), val);
    printIt(_T("writeInt16"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::writeInt8(Adesk::Int8 val)
{
    m_str.Format(_T("%d"), val);
    printIt(_T("writeInt8"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxDbgDwgFiler::writeUInt64(Adesk::UInt64 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeUInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeUInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeUInt32(Adesk::UInt32 val)
{
    m_str.Format(_T("%lu"), val);
    printIt(_T("writeUInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeUInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeUInt16(Adesk::UInt16 val)
{
    m_str.Format(_T("%hu"), val);
    printIt(_T("writeUInt16"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeUInt8
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeUInt8(Adesk::UInt8 val)
{
    m_str.Format(_T("%u"), val);
    printIt(_T("writeUInt8"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeBoolean
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeBoolean(Adesk::Boolean val)
{
    ArxDbgUtils::booleanToStr(val, m_str);
    printIt(_T("writeBoolean"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeBool
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeBool(bool val)
{
    ArxDbgUtils::booleanToStr(val, m_str);
    printIt(_T("writeBool"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeHardOwnershipId(const AcDbHardOwnershipId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeHardOwnId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeSoftOwnershipId(const AcDbSoftOwnershipId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeSoftOwnId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeHardPointerId(const AcDbHardPointerId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeHardPtrId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeSoftPointerId(const AcDbSoftPointerId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeSoftPtrId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeDouble
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeDouble(double val)
{
    m_str.Format(_T("%lf"), val);
    printIt(_T("writeDouble"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writePoint2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writePoint2d(const AcGePoint2d& val)
{
    ArxDbgUtils::ptToStr(val, m_str);
    printIt(_T("writePoint2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writePoint3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writePoint3d(const AcGePoint3d& val)
{
    ArxDbgUtils::ptToStr(val, m_str);
    printIt(_T("writePoint3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeVector2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeVector2d(const AcGeVector2d& val)
{
    ArxDbgUtils::vectorToStr(val, m_str);
    printIt(_T("writeVector2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeVector3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeVector3d(const AcGeVector3d& val)
{
    ArxDbgUtils::vectorToStr(val, m_str);
    printIt(_T("writeVector3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::writeScale3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDwgFiler::writeScale3d(const AcGeScale3d& val)
{
    m_str.Format(_T("%lf, %lf, %lf"), val.sx, val.sy, val.sz);
    printIt(_T("writeScale3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::tell
**
**  **jma
**
*************************************/

Adesk::Int64 ArxDbgDwgFiler::tell() const
{
    acutPrintf(_T("\nArxDbgDwgFiler::tell()"));
    return 0L;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::seek
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxDbgDwgFiler::seek(Adesk::Int64 nPos, int nMode)
{
    acutPrintf(_T("\nArxDbgDwgFiler::seek()"));
    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::filerStatus
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxDbgDwgFiler::filerStatus(void) const
{
    return m_stat;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::filerType
**
**  **jma
**
*************************************/

AcDb::FilerType
ArxDbgDwgFiler::filerType(void) const
{
     return m_filerType;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::setFilerStatus
**
**  **jma
**
*************************************/

void
ArxDbgDwgFiler::setFilerStatus(Acad::ErrorStatus status)
{
    m_stat = status;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::resetFilerStatus
**
**  **jma
**
*************************************/

void
ArxDbgDwgFiler::resetFilerStatus(void)
{
    m_stat = Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDwgFiler::printIt
**
**  **jma
**
*************************************/

void
ArxDbgDwgFiler::printIt(LPCTSTR labelStr)
{
    acutPrintf(_T("\n%-15s %s"), labelStr, m_str);
}

/****************************************************************************
**
**  ArxDbgDwgFiler::objIdToStr
**
**  **jma
**
*************************************/

void
ArxDbgDwgFiler::objIdToStr(const AcDbObjectId& objId, CString& str)
{
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead, Adesk::kTrue);
    if (es == Acad::eOk) {
        CString tmpStr;
        str.Format(_T("<%-25s %-4s>"),
                    ArxDbgUtils::objToClassStr(obj),
                    ArxDbgUtils::objToHandleStr(obj, tmpStr));

        if (obj->isErased())
            str += CString(_T("  ERASED"));

        obj->close();
    }
    else {
        str = ArxDbgUtils::rxErrorStr(es);
    }
}
