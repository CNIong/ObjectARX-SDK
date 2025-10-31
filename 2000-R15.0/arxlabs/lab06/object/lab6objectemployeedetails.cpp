//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#include "lab6objectemployeedetails.h"
#include "dbproxy.h"
#include "string.h"

//this macro defines the member functions declared by 
//the ACRX_DECLARE_MEMBERS macro. Refer to the on-line help for details
ACRX_DXF_DEFINE_MEMBERS(EmployeeDetails, AcDbObject,AcDbProxyEntity::kNoOperation,
						AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, OARXLABS_EMPLOYEEDETALS, lab5);

//don't forget to version your custom objects
//for usage see the dwgin/out methods
long EmployeeDetails::version = 1;

EmployeeDetails::EmployeeDetails(){
    m_cubeNumber=-1;
    m_ID=-1;
    m_strFirstName = NULL;
    m_strLastName = NULL;
}

EmployeeDetails::~EmployeeDetails(){
    cleanUp();
}

void EmployeeDetails::cleanUp(){
    //clean up
    if (m_strFirstName!=NULL)
        acdbFree(m_strFirstName);
    if (m_strLastName!=NULL)
        acdbFree(m_strLastName);
    m_strFirstName = NULL;
    m_strLastName = NULL;

}
//EmployeeDetails protocol
long EmployeeDetails::cubeNumber() const{
    assertReadEnabled();
    return m_cubeNumber;
}

Acad::ErrorStatus EmployeeDetails::setCubeNumber(const long cubeNumber){
    assertWriteEnabled();
    m_cubeNumber=cubeNumber;
    return Acad::eOk;
}

const char* EmployeeDetails::firstName() const{
    assertReadEnabled();
    return m_strFirstName;
}

Acad::ErrorStatus EmployeeDetails::setFirstName(const char* strFirstName){
    assertWriteEnabled();
    if (strFirstName==NULL)
        return Acad::eInvalidInput;
    size_t length = strlen(strFirstName);
    if (length==0)
        return Acad::eInvalidInput;
    char* temp = (char*)acdbAlloc(length+1);
    if (temp==NULL)
        return Acad::eOutOfMemory;
    //deallocate any previous piece
    if (m_strFirstName!=NULL)
        acdbFree(m_strFirstName);
    m_strFirstName = temp;
    strcpy(m_strFirstName,strFirstName);
    return Acad::eOk;
}

const char* EmployeeDetails::lastName() const{
    assertReadEnabled();
    return m_strLastName;
}

Acad::ErrorStatus EmployeeDetails::setLastName(const char* strLastName){
    assertWriteEnabled();
    if (strLastName==NULL)
        return Acad::eInvalidInput;
    size_t length = strlen(strLastName);
    if (length==0)
        return Acad::eInvalidInput;
    char* temp = (char*)acdbAlloc(length+1);
    if (temp==NULL)
        return Acad::eOutOfMemory;
    //deallocate any previous piece
    if (m_strLastName!=NULL)
        acdbFree(m_strLastName);
    m_strLastName = temp;
    strcpy(m_strLastName,strLastName);
    return Acad::eOk;
}

long EmployeeDetails::ID()const{
    assertReadEnabled();
    return m_ID;
}
Acad::ErrorStatus EmployeeDetails::setID(const long ID){
    assertWriteEnabled();
    m_ID = ID;
    return Acad::eOk;
}

//AcDbObject overrides
Acad::ErrorStatus EmployeeDetails::dwgInFields (AcDbDwgFiler* filer){
    assertWriteEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbObject::dwgInFields(filer))!=Acad::eOk)
        return es;
    long ver;
    filer->readInt32(&ver);
    //we won't be able to read the staff if its
    //version is greater than the one we were compiled with
    if (ver>EmployeeDetails::version)
        return Acad::eMakeMeProxy;
    //deallocate an previous strings
    cleanUp();
    //this is how we read ver1
    if (ver==1){
        filer->readInt32(&m_cubeNumber);
        filer->readInt32(&m_ID);
        filer->readString(&m_strFirstName);
        filer->readString(&m_strLastName);
    }    
    //other versions up to the current version should come here
    //if you want to maintain downward compatibility

    //these should hold by this time
    assert(m_strFirstName!=NULL);
    assert(m_strLastName!=NULL);
    assert(m_cubeNumber>=0);
    assert(m_ID>=0);
    return filer->filerStatus();
}
Acad::ErrorStatus EmployeeDetails::dwgOutFields(AcDbDwgFiler* filer) const{
    assertReadEnabled();
    //these should hold by this time
    assert(m_strFirstName!=NULL);
    assert(m_strLastName!=NULL);
    assert(m_cubeNumber>=0);
    assert(m_ID>=0);
    Acad::ErrorStatus es;
    if ((es=AcDbObject::dwgOutFields(filer))!=Acad::eOk)
        return es;
    filer->writeInt32(EmployeeDetails::version);
    filer->writeInt32(m_cubeNumber);
    filer->writeInt32(m_ID);
    filer->writeString(m_strFirstName);
    filer->writeString(m_strLastName);
    return filer->filerStatus();
}

