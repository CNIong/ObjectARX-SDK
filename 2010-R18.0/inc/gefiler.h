//
#ifndef AC_GEFILER_H
#define AC_GEFILER_H
//
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
// Description:
//
// This file implements the class AcGeFiler, which defines the
// abstract interface for serialization requirements of ge entities. 
// An application that requires input/output of the definition of
// ge entities in a format defined by the application should provide 
// an implementation of this class.  An instance of this class is
// provided as an argument to the entity serialization functions, 
// thus allowing the input/output format to be controlled by the 
// client of gelib. An example of usage would be as follows.
//
// AcRfDwgFiler  format;
// AcGeVersion   dbVersion;
// AcGeLine3d    newLine;
// if (acmeGetGelibImageVersion(entity, dbVersion) == AcMe::eOk) 
// {
//     AcGeDwgIO::read(format, dbVersion, newLine) 
//     AcGeDwgIO::write(format, newLine)
// }
//
     
#include "AdAChar.h"
#include "AcString.h"
#include "gegbl.h"
#include "acdb.h"
#pragma pack (push, 8)
     
     
class AcDbDwgFiler;
     
class 
GE_DLLEXPIMPORT ADESK_NO_VTABLE
AcGeFiler
{
protected:
    AcGeFiler();
public:
    // Read/write functions.
    //
    virtual
    Acad::ErrorStatus      readBoolean(Adesk::Boolean*) = 0; 
    virtual
    Acad::ErrorStatus      writeBoolean(Adesk::Boolean) = 0;

    virtual
    Acad::ErrorStatus      readBool(bool*) = 0; 
    virtual
    Acad::ErrorStatus      writeBool(bool) = 0;

    virtual
    Acad::ErrorStatus      readSignedByte(char *) = 0; 
    virtual
    Acad::ErrorStatus      writeSignedByte(char) = 0;
     
    virtual
    Acad::ErrorStatus      readString(AcString &) = 0; 
    virtual
    Acad::ErrorStatus      writeString(const AcString &) = 0;
     
    virtual
    Acad::ErrorStatus      readShort(short*) = 0; 
    virtual
    Acad::ErrorStatus      writeShort(short) = 0;
     
    virtual
    Acad::ErrorStatus      readLong(long*) = 0; 
    virtual
    Acad::ErrorStatus      writeLong(long) = 0;
     
    // Unicode: this is assumed to be a binary value, not a text character!
    virtual
    Acad::ErrorStatus      readUChar(unsigned char*) = 0; 
    virtual
    Acad::ErrorStatus      writeUChar(unsigned char) = 0;
     
    virtual
    Acad::ErrorStatus      readUShort(unsigned short*) = 0; 
    virtual
    Acad::ErrorStatus      writeUShort(unsigned short) = 0;
     
    virtual
    Acad::ErrorStatus      readULong(unsigned long*) = 0; 
    virtual
    Acad::ErrorStatus      writeULong(unsigned long) = 0;
          
    virtual
    Acad::ErrorStatus      readDouble(double*) = 0; 
    virtual
    Acad::ErrorStatus      writeDouble(double) = 0;
     
    virtual
    Acad::ErrorStatus      readPoint2d(AcGePoint2d*) = 0; 
    virtual
    Acad::ErrorStatus      writePoint2d(const AcGePoint2d&) = 0;
     
    virtual
    Acad::ErrorStatus      readPoint3d(AcGePoint3d*) = 0; 
    virtual
    Acad::ErrorStatus      writePoint3d(const AcGePoint3d&) = 0;
     
    virtual
    Acad::ErrorStatus      readVector2d(AcGeVector2d*) = 0; 
    virtual
    Acad::ErrorStatus      writeVector2d(const AcGeVector2d&) = 0;
     
    virtual
    Acad::ErrorStatus      readVector3d(AcGeVector3d*) = 0; 
    virtual
    Acad::ErrorStatus      writeVector3d(const AcGeVector3d&) = 0;
     
    // This method must be implemented in order to read/write 
    // external curves and surfaces (and nurb surfaces). 
    virtual
    AcDbDwgFiler*          dwgFiler();

    virtual
    Acad::ErrorStatus      readBytes(void*, unsigned long) = 0;
    virtual
    Acad::ErrorStatus      writeBytes(const void*, unsigned long) = 0;
};

__forceinline
AcDbDwgFiler* AcGeFiler::dwgFiler()
{
    return NULL;
}
     
     
#pragma pack (pop)
#endif
