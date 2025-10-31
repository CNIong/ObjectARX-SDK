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
#include "lab8ObjectEmployeeEntry.h"
#include "dbproxy.h"

long EmployeeEntry::version = 1;



//this macro defines the member functions declared by 
//the ACRX_DECLARE_MEMBERS macro. Refer to the on-line help for details
ACRX_DXF_DEFINE_MEMBERS(EmployeeEntry,AcDbObject,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
AcDbProxyEntity::kNoOperation,OARXLABS_EMPLOYEEENTRY,lab8);

const AcDbObjectId EmployeeEntry::employee()const{
    assertReadEnabled();
    return m_idEmp;
}

Acad::ErrorStatus EmployeeEntry::setEmployee(const AcDbObjectId& idEmp){
    assertWriteEnabled();
    m_idEmp = idEmp;
    return Acad::eOk;
}

//AcDbObject overrides
Acad::ErrorStatus EmployeeEntry::dwgInFields (AcDbDwgFiler* filer){
    assertWriteEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbObject::dwgInFields(filer))!=Acad::eOk)
        return es;
    long ver;
    filer->readInt32(&ver);
    //we won't be able to read the staff if its
    //version is greater than the one we were compiled with
    if (ver>EmployeeEntry::version)
        return Acad::eMakeMeProxy;
    //this is how we read ver1
    if (ver==1){
        filer->readSoftPointerId(reinterpret_cast<AcDbSoftPointerId*>(&m_idEmp));
    }  
    return filer->filerStatus();
}

Acad::ErrorStatus EmployeeEntry::dwgOutFields(AcDbDwgFiler* filer) const{
    assertReadEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbObject::dwgOutFields(filer))!=Acad::eOk)
        return es;
    filer->writeInt32( EmployeeEntry::version );
    filer->writeSoftPointerId(m_idEmp);
    return filer->filerStatus();
}
