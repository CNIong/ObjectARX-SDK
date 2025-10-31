/////////////////////////////////////////////
// AsdkEmployeeDetails custom object.

#if !defined(ARX__ASDKEMPLOYEEDETAILS_H__19990618_160422)
#define ARX__ASDKEMPLOYEEDETAILS_H__19990618_160422

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4275 4251)

#ifdef _EMPLOYEEDETAILS_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ASDKEMPLOYEEDETAILS_DBXSERVICE
#define ASDKEMPLOYEEDETAILS_DBXSERVICE "ASDKEMPLOYEEDETAILS_DBXSERVICE"
#endif



#include "dbmain.h"


class DLLIMPEXP AsdkEmployeeDetails : public AcDbObject
{
public:

	ACRX_DECLARE_MEMBERS(AsdkEmployeeDetails);

	// Constructor / Destructor
	AsdkEmployeeDetails();
	virtual ~AsdkEmployeeDetails();

	//{{AFX_ARX_METHODS(AsdkEmployeeDetails)
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	//}}AFX_ARX_METHODS


	//{{AFX_ARX_DATA_ACCESS(AsdkEmployeeDetails)
	Acad::ErrorStatus setID(const Adesk::Int32 ID);
	Acad::ErrorStatus iD(Adesk::Int32& ID);
	Acad::ErrorStatus setCube(const Adesk::Int32 cube);
	Acad::ErrorStatus cube(Adesk::Int32& cube);
	Acad::ErrorStatus setFirstName(const char* firstName);
	Acad::ErrorStatus firstName(char*& firstName);
	Acad::ErrorStatus setLastName(const char* lastName);
	Acad::ErrorStatus lastName(char*& lastName);
	//}}AFX_ARX_DATA_ACCESS


private:
	//{{AFX_ARX_DATA(AsdkEmployeeDetails)
	Adesk::Int32 m_ID;
	Adesk::Int32 m_cube;
	char* m_firstName;
	char* m_lastName;
	//}}AFX_ARX_DATA


private:

	void *operator new[](unsigned nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](unsigned nSize, const char *file, int line) { return 0; }

};



#endif // !defined(ARX__ASDKEMPLOYEEDETAILS_H__19990618_160422)