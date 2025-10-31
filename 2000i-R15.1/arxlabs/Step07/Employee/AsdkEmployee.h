/////////////////////////////////////////////
// AsdkEmployee custom object.

#if !defined(ARX__ASDKEMPLOYEE_H__19990619_140006)
#define ARX__ASDKEMPLOYEE_H__19990619_140006

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4275 4251)

#ifdef _EMPLOYEE_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ASDKEMPLOYEE_DBXSERVICE
#define ASDKEMPLOYEE_DBXSERVICE "ASDKEMPLOYEE_DBXSERVICE"
#endif



#include "dbelipse.h"


class DLLIMPEXP AsdkEmployee : public AcDbEllipse
{
public:

	ACRX_DECLARE_MEMBERS(AsdkEmployee);

	// Constructor / Destructor
	AsdkEmployee();
	virtual ~AsdkEmployee();

	//{{AFX_ARX_METHODS(AsdkEmployee)
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	//}}AFX_ARX_METHODS


	//{{AFX_ARX_DATA_ACCESS(AsdkEmployee)
	Acad::ErrorStatus setID(const Adesk::UInt32 ID);
	Acad::ErrorStatus iD(Adesk::UInt32& ID);
	Acad::ErrorStatus setCube(const Adesk::UInt32 cube);
	Acad::ErrorStatus cube(Adesk::UInt32& cube);
	Acad::ErrorStatus setFirstName(const char* firstName);
	Acad::ErrorStatus firstName(char*& firstName);
	Acad::ErrorStatus setLastName(const char* lastName);
	Acad::ErrorStatus lastName(char*& lastName);
	//}}AFX_ARX_DATA_ACCESS


private:
	//{{AFX_ARX_DATA(AsdkEmployee)
	Adesk::UInt32 m_ID;
	Adesk::UInt32 m_cube;
	char* m_firstName;
	char* m_lastName;
	//}}AFX_ARX_DATA


private:

	void *operator new[](unsigned nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](unsigned nSize, const char *file, int line) { return 0; }

};



#endif // !defined(ARX__ASDKEMPLOYEE_H__19990619_140006)