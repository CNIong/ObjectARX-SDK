//
#ifndef AD_DBFILER_H
#define AD_DBFILER_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// DBFILER.H  -- AutoCAD Database Filer Definitions
//
// DESCRIPTION:
//
// This file contains "filer" class definitions, which are passed to
// AcDbObject objects by their parent AcDbDatabase object to
// perform I/O operations in various contexts.
//
// Common Filer Contracts are:
//
// 1. The Database object always controls the creation of the
//    filers, and passing them to objects.  The Database object
//    itself surrounds filing calls with I/O of class name/ID/DXF_name
//    maps, and common object information such as class IDs/DXF names,
//    checksums, record lengths and other common record information.
//    The database object also handles file section and object
//    sentinels for database recovery purposes.
//
// 2. For different I/O contexts, 3 different sets of AcDbObject
//    members are defined:  DXF, DWG File, and Paging
//    While DWG File and Paging members are supplied pagers of the
//    same abstract class, implementations of some members,
//    particularly those concerned with AcDbObjectId and AcDbHandle objects,
//    are very different.  Usage contract differs as follows, reason being
//    that notification chains are NOT limited to database objects:
//
//    Paging:  For Notification chains, use "void" filer method to
//               save/restore pointer.  Do not bother to pull out
//               of other notification chains.
//
//    DWG file: Pull out of other notification chains, and record
//                what is needed for reconstruction.
//
// 3. The filer methods of AcDbObject subclasses are named the same
//    as the parent class's methods, with "Fields" appended (as in
//    dwgInFields()).  Each such method (with a few exceptions in
//    class AcDbEntity) must invoke the same method in its parent
//    *before* performing any of its own filing actions.

#include <stdarg.h>
#include "AdAChar.h"
#include "acdb.h"
#include "gepnt2d.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "gescl3d.h"
#include "adsdef.h"

#pragma pack (push, 8)

class AcDbAuditInfo;
class AcDbFilerController;
class AcDbHandle;
class AcDbIdRefQueue;
class AcString;

class ADESK_NO_VTABLE AcDbDwgFiler: public AcRxObject
// 
// Abstract class for DWG file and paging I/O.  While protocol is virtually
// the same, the implementations will be different, and so will usage.  DWG
// filer will do byte-reversal, and convert AcDbStub and AcDbHandle values
// to/from char* values
//
// This will also stand as an abstract class for common R14, R13, and R12
// backwards/forwards compatibility for DWG.
// 
// The pager would presumably direct I/O, no conversions, and directly
// copies"void*" values for things like pointers to reactor sets.
// 
// Reactor sets will remain in memory when the underlying object is paged out,
// while DWG I/O requires dissolution an entities presence on reactor chains
// when written, and reconstruction of the same when read back in.
// 
// For each filer data type Xxx, there is a pair of write functions
// writeXxx(Xxx) and writeItem(Xxx).  The writeItem() functions, defined
// inline in terms of the writeXxx() functions, can be used when it is
// convenient or appropriate to let the argument type determine which function
// to call.  The writeXxx() functions are pure-virtual, i.e., must be defined
// by all concrete subclasses.
// 
// The same applies to the read functions.
// 
// Filers may also implement CRC accumulation. 
// 
{
  public:
    ACRX_DECLARE_MEMBERS(AcDbDwgFiler);
    AcDbDwgFiler();
    virtual ~AcDbDwgFiler();

    virtual  Acad::ErrorStatus filerStatus() const = 0;
    virtual  AcDb::FilerType   filerType() const = 0;
    virtual void               setFilerStatus(Acad::ErrorStatus) = 0;
    virtual void               resetFilerStatus() = 0;

    // version of the drawing file being read or written by this filer

    virtual  Acad::ErrorStatus  dwgVersion(AcDb::AcDbDwgVersion &,
                                AcDb::MaintenanceReleaseVersion &) const;

    //        readXxx() and writeXxx() functions
    //
    virtual Acad::ErrorStatus   readHardOwnershipId(AcDbHardOwnershipId*) = 0;
    virtual Acad::ErrorStatus   writeHardOwnershipId(
                                  const AcDbHardOwnershipId&) = 0;

    virtual Acad::ErrorStatus   readSoftOwnershipId(AcDbSoftOwnershipId*) = 0;
    virtual Acad::ErrorStatus   writeSoftOwnershipId(
                                  const AcDbSoftOwnershipId&) = 0;

    virtual Acad::ErrorStatus   readHardPointerId(AcDbHardPointerId*) = 0;
    virtual Acad::ErrorStatus   writeHardPointerId(const AcDbHardPointerId&) = 0;

    virtual Acad::ErrorStatus   readSoftPointerId(AcDbSoftPointerId*) = 0;
    virtual Acad::ErrorStatus   writeSoftPointerId(const AcDbSoftPointerId&) = 0;

    virtual Acad::ErrorStatus   readInt8(Adesk::Int8 *) = 0;
    virtual Acad::ErrorStatus   writeInt8(Adesk::Int8 ) = 0;

    // These are to be removed in a future release.  Please use
    // readInt8 or writeInt8 instead.
    //
    // Todo: decide whether a readAChar() and writeAChar() are needed...
    inline  Acad::ErrorStatus   readChar(Adesk::Int8 *p) {
                                        return this->readInt8(p); }
    inline  Acad::ErrorStatus   writeChar(Adesk::Int8 c) {
                                        return this->writeInt8(c); }

    // Note: use of readString(ACHAR **) is discouraged, because
    // caller has to free the returned string.  It may be phased
    // out in a future release.
    virtual Acad::ErrorStatus   readString(ACHAR **) = 0;
    virtual Acad::ErrorStatus   writeString(const ACHAR *) = 0;

    virtual Acad::ErrorStatus   readString(AcString &) = 0;
    virtual Acad::ErrorStatus   writeString(const AcString &) = 0;

    virtual Acad::ErrorStatus   readBChunk(ads_binary *) = 0;
    virtual Acad::ErrorStatus   writeBChunk(const ads_binary&) = 0;

    virtual Acad::ErrorStatus   readAcDbHandle(AcDbHandle*) = 0;
    virtual Acad::ErrorStatus   writeAcDbHandle(const AcDbHandle&) = 0;

    virtual Acad::ErrorStatus   readInt64(Adesk::Int64*) = 0;
    virtual Acad::ErrorStatus   writeInt64(Adesk::Int64) = 0;

    virtual Acad::ErrorStatus   readInt32(Adesk::Int32*) = 0;
    virtual Acad::ErrorStatus   writeInt32(Adesk::Int32) = 0;

    virtual Acad::ErrorStatus   readInt16(Adesk::Int16*) = 0;
    virtual Acad::ErrorStatus   writeInt16(Adesk::Int16) = 0;

    virtual Acad::ErrorStatus   readUInt64(Adesk::UInt64*) = 0;
    virtual Acad::ErrorStatus   writeUInt64(Adesk::UInt64) = 0;

    virtual Acad::ErrorStatus   readUInt32(Adesk::UInt32*) = 0;
    virtual Acad::ErrorStatus   writeUInt32(Adesk::UInt32) = 0;

    virtual Acad::ErrorStatus   readUInt16(Adesk::UInt16*) = 0;
    virtual Acad::ErrorStatus   writeUInt16(Adesk::UInt16) = 0;

    virtual Acad::ErrorStatus   readUInt8(Adesk::UInt8*) = 0;
    virtual Acad::ErrorStatus   writeUInt8(Adesk::UInt8) = 0;

#ifdef Adesk_Boolean_is_bool
    virtual Acad::ErrorStatus   readInt(int*) = 0;
    virtual Acad::ErrorStatus   writeInt(int) = 0;
#endif

    virtual Acad::ErrorStatus   readBoolean(Adesk::Boolean*) = 0;
    virtual Acad::ErrorStatus   writeBoolean(Adesk::Boolean) = 0;

    virtual Acad::ErrorStatus   readBool(bool*) = 0;
    virtual Acad::ErrorStatus   writeBool(bool) = 0;

    virtual Acad::ErrorStatus   readDouble(double*) = 0;
    virtual Acad::ErrorStatus   writeDouble(double) = 0;

    virtual Acad::ErrorStatus   readPoint2d(AcGePoint2d*) = 0;
    virtual Acad::ErrorStatus   writePoint2d(const AcGePoint2d&) = 0;

    virtual Acad::ErrorStatus   readPoint3d(AcGePoint3d*) = 0;
    virtual Acad::ErrorStatus   writePoint3d(const AcGePoint3d&) = 0;

    virtual Acad::ErrorStatus   readVector2d(AcGeVector2d*) = 0;
    virtual Acad::ErrorStatus   writeVector2d(const AcGeVector2d&) = 0;

    virtual Acad::ErrorStatus   readVector3d(AcGeVector3d*) = 0;
    virtual Acad::ErrorStatus   writeVector3d(const AcGeVector3d&) = 0;

    virtual Acad::ErrorStatus   readScale3d(AcGeScale3d*) = 0;
    virtual Acad::ErrorStatus   writeScale3d(const AcGeScale3d&) = 0;

    virtual Acad::ErrorStatus   readBytes(void *, Adesk::UIntPtr) = 0;
    virtual Acad::ErrorStatus   writeBytes(const void *, Adesk::UIntPtr) = 0;

    virtual Acad::ErrorStatus   readAddress(void **);
    virtual Acad::ErrorStatus   writeAddress(const void *);

    //        readItem() and writeItem() functions
    //
            Acad::ErrorStatus   readItem(AcDbHardOwnershipId*);
            Acad::ErrorStatus   writeItem(const AcDbHardOwnershipId&);

            Acad::ErrorStatus   readItem(AcDbSoftOwnershipId*);
            Acad::ErrorStatus   writeItem(const AcDbSoftOwnershipId&);

            Acad::ErrorStatus   readItem(AcDbHardPointerId*);
            Acad::ErrorStatus   writeItem(const AcDbHardPointerId&);

            Acad::ErrorStatus   readItem(AcDbSoftPointerId*);
            Acad::ErrorStatus   writeItem(const AcDbSoftPointerId&);

            // Note: there are no filer methods for explicitly reading or
            // writing a single text character.  There are readChar() and
            // writeChar(), but these do not do any code page translation
            // on the data.  I.e., they treat it as a signed 8-bit
            // integer value.  Since they are thus the same as readInt8()
            // and writeInt8(), they are being deprecated.
            //
            Acad::ErrorStatus   readItem(ACHAR **);
            Acad::ErrorStatus   writeItem(const ACHAR *);

            Acad::ErrorStatus   readItem(ads_binary*);
            Acad::ErrorStatus   writeItem(const ads_binary&);

            Acad::ErrorStatus   readItem(AcDbHandle*);
            Acad::ErrorStatus   writeItem(const AcDbHandle&);

            Acad::ErrorStatus   readItem(Adesk::Int32*);
            Acad::ErrorStatus   writeItem(Adesk::Int32);

            Acad::ErrorStatus   readItem(Adesk::Int16*);
            Acad::ErrorStatus   writeItem(Adesk::Int16);

            Acad::ErrorStatus   readItem(Adesk::Int8 *);
            Acad::ErrorStatus   writeItem(Adesk::Int8);

            Acad::ErrorStatus   readItem(Adesk::UInt32*);
            Acad::ErrorStatus   writeItem(Adesk::UInt32);

            Acad::ErrorStatus   readItem(Adesk::UInt16*);
            Acad::ErrorStatus   writeItem(Adesk::UInt16);

            Acad::ErrorStatus   readItem(Adesk::UInt8*);
            Acad::ErrorStatus   writeItem(Adesk::UInt8);

#ifdef Adesk_Boolean_is_bool
            Acad::ErrorStatus   readItem(int*);
            Acad::ErrorStatus   writeItem(int);
#else
            Acad::ErrorStatus   readItem(Adesk::Boolean*);
            Acad::ErrorStatus   writeItem(Adesk::Boolean);
#endif

            Acad::ErrorStatus   readItem(bool*);
            Acad::ErrorStatus   writeItem(bool);

            Acad::ErrorStatus   readItem(double*);
            Acad::ErrorStatus   writeItem(double);

            Acad::ErrorStatus   readItem(AcGePoint2d*);
            Acad::ErrorStatus   writeItem(const AcGePoint2d&);

            Acad::ErrorStatus   readItem(AcGePoint3d*);
            Acad::ErrorStatus   writeItem(const AcGePoint3d&);

            Acad::ErrorStatus   readItem(AcGeVector2d*);
            Acad::ErrorStatus   writeItem(const AcGeVector2d&);

            Acad::ErrorStatus   readItem(AcGeVector3d*);
            Acad::ErrorStatus   writeItem(const AcGeVector3d&);

            Acad::ErrorStatus   readItem(AcGeScale3d*);
            Acad::ErrorStatus   writeItem(const AcGeScale3d&);

            Acad::ErrorStatus   readItem(void *, Adesk::UIntPtr);
            Acad::ErrorStatus   writeItem(const void *, Adesk::UIntPtr);

            Acad::ErrorStatus   readItem(void **);
            Acad::ErrorStatus   writeItem(const void *);

    virtual Acad::ErrorStatus   seek(Adesk::Int64 nOffset, int nMethod) = 0;
    virtual Adesk::Int64        tell() const = 0;
    virtual Acad::ErrorStatus   addReferences(AcDbIdRefQueue& /*qToAbsorb*/);
    virtual              bool   usesReferences() const;
    virtual AcDbAuditInfo *     getAuditInfo() const;

    virtual AcDbFilerController& controller() const;

private:
            AcDbFilerController& mController;
};


class ADESK_NO_VTABLE AcDbDxfFiler: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDxfFiler);

    virtual int               rewindFiler() = 0;

    virtual Acad::ErrorStatus filerStatus() const = 0;
    virtual void              resetFilerStatus() = 0;

    virtual Acad::ErrorStatus setError(Acad::ErrorStatus, const ACHAR *, ...);
    virtual Acad::ErrorStatus setError(const ACHAR *, ...);
    virtual const ACHAR * errorMessage() const;

    virtual  AcDb::FilerType filerType() const = 0;

    // working database being read or written by this filer
    virtual  AcDbDatabase*      database() const = 0;

    // version of the drawing file being read or written by this filer

    virtual  Acad::ErrorStatus  dwgVersion(AcDb::AcDbDwgVersion &,
                                AcDb::MaintenanceReleaseVersion &) const;

    virtual int                 precision() const;
    virtual void                setPrecision(int prec);

    // Number of decimal digits printed in ASCII DXF file
    //
    enum { kDfltPrec = -1, kMaxPrec  = 16 };

    //        readXxx and writeXxx functions
    //
    virtual Acad::ErrorStatus readResBuf   (resbuf*);
    virtual Acad::ErrorStatus writeResBuf  (const resbuf&);
    virtual Acad::ErrorStatus writeObjectId(AcDb::DxfCode,
                                            const AcDbObjectId&) = 0;
    virtual Acad::ErrorStatus writeInt8    (AcDb::DxfCode, Adesk::Int8) = 0;

    // This is to be removed in a future release
    inline  Acad::ErrorStatus writeChar    (AcDb::DxfCode c, Adesk::Int8 n) {
                                return this->writeInt8(c, n); }

    virtual Acad::ErrorStatus writeString  (AcDb::DxfCode, const ACHAR *) = 0;
    virtual Acad::ErrorStatus writeString  (AcDb::DxfCode, const AcString &) = 0;
    virtual Acad::ErrorStatus writeBChunk  (AcDb::DxfCode, const ads_binary&) = 0;
    virtual Acad::ErrorStatus writeAcDbHandle(AcDb::DxfCode,
                                              const AcDbHandle&) = 0;
    virtual Acad::ErrorStatus writeInt64   (AcDb::DxfCode, Adesk::Int64) = 0;
    virtual Acad::ErrorStatus writeInt32   (AcDb::DxfCode, Adesk::Int32) = 0;
    virtual Acad::ErrorStatus writeInt16   (AcDb::DxfCode, Adesk::Int16) = 0;
    virtual Acad::ErrorStatus writeUInt64  (AcDb::DxfCode, Adesk::UInt64) = 0;
    virtual Acad::ErrorStatus writeUInt32  (AcDb::DxfCode, Adesk::UInt32) = 0;
    virtual Acad::ErrorStatus writeUInt16  (AcDb::DxfCode, Adesk::UInt16) = 0;
    virtual Acad::ErrorStatus writeUInt8   (AcDb::DxfCode, Adesk::UInt8) = 0;
    virtual Acad::ErrorStatus writeBoolean (AcDb::DxfCode, Adesk::Boolean) = 0;
#ifdef Adesk_Boolean_is_bool
    virtual Acad::ErrorStatus writeInt     (AcDb::DxfCode, int) = 0;
#endif
    virtual Acad::ErrorStatus writeBool    (AcDb::DxfCode, bool) = 0;
    virtual Acad::ErrorStatus writeDouble  (AcDb::DxfCode, double,
                                            int = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writePoint2d (AcDb::DxfCode, const AcGePoint2d&,
                                            int = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writePoint3d (AcDb::DxfCode, const AcGePoint3d&,
                                               int = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeVector2d(AcDb::DxfCode, const AcGeVector2d&,
                                            int = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeVector3d(AcDb::DxfCode, const AcGeVector3d&,
                                            int = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeScale3d (AcDb::DxfCode, const AcGeScale3d&,
                                            int = kDfltPrec) = 0;

    //        readItem and writeItem functions
    //
    Acad::ErrorStatus readItem        (resbuf* pItem);
    Acad::ErrorStatus writeItem (const resbuf& pItem);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcDbObjectId&);

    Acad::ErrorStatus writeItem (AcDb::DxfCode, const ACHAR *);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const ads_binary&);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcDbHandle&);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::Int32);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::Int16);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::Int8);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::UInt32);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::UInt16);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::UInt8);
#ifdef Adesk_Boolean_is_bool
    Acad::ErrorStatus writeItem (AcDb::DxfCode, int);
#else
    // CAUTION: "int" parameters go to writeBoolean
    Acad::ErrorStatus writeItem (AcDb::DxfCode, Adesk::Boolean);
#endif
    Acad::ErrorStatus writeItem (AcDb::DxfCode, bool);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, double, int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcGePoint2d&,
                                 int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcGePoint3d&,
                                 int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcGeVector2d&,
                                 int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcGeVector3d&,
                                 int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode, const AcGeScale3d&,
                                 int = kDfltPrec);
    virtual Acad::ErrorStatus writeXDataStart ();
    virtual bool              includesDefaultValues() const = 0;

    virtual Acad::ErrorStatus pushBackItem();
    virtual bool              atEOF();
    virtual bool              atSubclassData(const ACHAR *);
    virtual bool              atExtendedData();
    virtual bool              atEndOfObject();
    virtual void              haltAtClassBoundries(bool);

    virtual Acad::ErrorStatus writeEmbeddedObjectStart();
    virtual bool              atEmbeddedObjectStart();

    virtual double elevation() const;
    virtual double thickness() const;

    virtual bool              isModifyingExistingObject() const;

    AcDbDxfFiler();
    virtual ~AcDbDxfFiler();
    AcDbFilerController& controller() const;

private:
    AcDbFilerController& mController;
    virtual Acad::ErrorStatus setVAError(Acad::ErrorStatus, const ACHAR *,
                                         va_list);
};

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHardOwnershipId* pId)
{   return readHardOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHardOwnershipId& pId)
{   return writeHardOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbSoftOwnershipId* pId)
{   return readSoftOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbSoftOwnershipId& pId)
{   return writeSoftOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHardPointerId* pId)
{   return readHardPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHardPointerId& pId)
{   return writeHardPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbSoftPointerId* pId)
{   return readSoftPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbSoftPointerId& pId)
{   return writeSoftPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(ACHAR ** pVal)
{   return readString(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const ACHAR * val)
{   return writeString(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(ads_binary* pVal)
{   return readBChunk(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const ads_binary& val)
{   return writeBChunk(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHandle* pVal)
{   return readAcDbHandle(pVal);    }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHandle& val)
{   return writeAcDbHandle(val);    }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int32* pVal)
{   return readInt32(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int32 val)
{   return writeInt32(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int16* pVal)
{   return readInt16(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int16 val)
{   return writeInt16(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int8 * pVal)
{   return this->readInt8(pVal);       }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int8 val)
{   return this->writeInt8(val);       }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt32* pVal)
{   return readUInt32(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt32 val)
{   return writeUInt32(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt16* pVal)
{   return readUInt16(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt16 val)
{   return writeUInt16(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt8* pVal)
{   return readUInt8(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt8 val)
{   return writeUInt8(val);            }

#ifdef Adesk_Boolean_is_bool
inline Acad::ErrorStatus AcDbDwgFiler::readItem(int* pVal)
{   return readInt(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(int val)
{   return writeInt(val);            }
#else
inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Boolean* pVal)
{   return readBoolean(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Boolean val)
{   return writeBoolean(val);            }
#endif

inline Acad::ErrorStatus AcDbDwgFiler::readItem(bool* pVal)
{   return readBool(pVal);              }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(bool val)
{   return writeBool(val);              }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(double* pVal)
{   return readDouble(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(double val)
{   return writeDouble(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGePoint2d* pVal)
{   return readPoint2d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGePoint2d& val)
{   return writePoint2d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGePoint3d* pVal)
{   return readPoint3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGePoint3d& val)
{   return writePoint3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeVector2d* pVal)
{   return readVector2d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeVector2d& val)
{   return writeVector2d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeVector3d* pVal)
{   return readVector3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeVector3d& val)
{   return writeVector3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeScale3d* pVal)
{   return readScale3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeScale3d& val)
{   return writeScale3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(void *buf, Adesk::UIntPtr cnt)
{   return readBytes(buf, cnt);     }

inline Acad::ErrorStatus 
AcDbDwgFiler::writeItem(const void *buf, Adesk::UIntPtr cnt)
{   return writeBytes(buf, cnt);    }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(void **pp)
{   return readAddress(pp);            }

inline Acad::ErrorStatus 
AcDbDwgFiler::writeItem(const void *p)
{   return writeAddress(p);            }

inline Acad::ErrorStatus
AcDbDxfFiler::readItem(resbuf* pVal)
{   return readResBuf(pVal);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(const resbuf& val)
{   return writeResBuf(val);            }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcDbObjectId& id)
{   return writeObjectId(dc, id); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const ACHAR * val)
{   return writeString(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const ads_binary& val)
{   return writeBChunk(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcDbHandle& val)
{   return writeAcDbHandle(dc, val);    }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int32 val)
{   return writeInt32(dc, val);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int16 val)
{   return writeInt16(dc, val);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int8 val)
{   return this->writeInt8(dc, val);    }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt32 val)
{   return writeUInt32(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt16 val)
{   return writeUInt16(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt8 val)
{   return writeUInt8(dc, val);         }

#ifdef Adesk_Boolean_is_bool
inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, int val)
{   return writeInt(dc, val);        }
#else
inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Boolean val)
{   return writeBoolean(dc, val);        }
#endif

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, bool val)
{   return writeBool(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, double val, int prec)
{   return writeDouble(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGePoint2d& val, int prec)
{   return writePoint2d(dc, val, prec); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGePoint3d& val, int prec)
{   return writePoint3d(dc, val, prec); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeVector2d& val, int prec)
{   return writeVector2d(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeVector3d& val, int prec)
{   return writeVector3d(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeScale3d& val, int prec)
{   return writeScale3d(dc, val, prec); }

#pragma pack (pop)

#endif
