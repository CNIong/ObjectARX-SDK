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
#ifndef _LAB8EMPLOYEEENTRY_H
#define _LAB8EMPLOYEEENTRY_H

#include "dbmain.h"
#define EMPLOYEE_ENTRY_SERVICE "OARXLABS_EMP_ENTRY_SVC"


// Note: Because of the "local vtable" problem with msvc if 
// you use __declspec(dllimport), then, when a client dll 
// does a new on the class, the object's vtable pointer points 
// to a vtable allocated in that client dll. If the client dll 
// then passes the object to another dll, and the client dll is 
// then unloaded, the vtable becomes invalid and any virtual 
// calls on the object will access invalid memory.
//
// There is a workaround for the case that you are not using
// static variables in your class declaration:
// By not using __declspec(dllimport), we guarantee that the
// vtable is allocated in the server dll during the ctor and the
// client dll does not overwrite the vtable pointer after calling
// the ctor.  And, since we expect the server dll to remain in
// memory indefinitely, there is no problem with vtables 
// unexpectedly going away.
//
// In our case we are using a static member variable to store 
// the version information. This means that we have to use 
// __declspec(dllimport) and we cannot pass an object created 
// in a client of this dll to another dll.


//we don't want this warning
//AcDbObject *IS* exported
#pragma warning( disable : 4275 )
//we don't want this warning
//AcDbObjectId *IS* exported
#pragma warning( disable : 4251 )
//_LAB8OBJECT is defined in the Lab8Object project
//export the class depending on the
//_LAB8OBJECT symbol
class 
#ifdef _LAB8OBJECT
_declspec(dllexport)
#endif
EmployeeEntry : public AcDbObject{
protected:
    AcDbObjectId m_idEmp;
    static long version;
public:
    ACRX_DECLARE_MEMBERS(EmployeeEntry);
    const AcDbObjectId employee()const;
    Acad::ErrorStatus setEmployee(const AcDbObjectId& idEmp);

    //AcDbObject overrides
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

private:
    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 and vc6 do not properly support array new and delete.
    // The "vector deleting dtor" gets optimized into a scalar deleting
    // dtor by the linker if the server dll does not call vector delete.
    // The linker shouldn't do that, because it doesn't know that the
    // object won't be passed to some other dll which *does* do vector
    // delete.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](unsigned nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](unsigned nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

};

#endif //_LAB8EMPLOYEEENTRY_H