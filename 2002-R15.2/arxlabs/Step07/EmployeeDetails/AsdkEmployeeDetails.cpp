/////////////////////////////////////////////
// AsdkEmployeeDetails custom object.

#include "StdAfx.h"
#include "StdArx.h"
#include "dbproxy.h"
#include "geassign.h"
#include "acgi.h"

#define VERSION_ASDKEMPLOYEEDETAILS 1


//{{AFX_ARX_MACRO
ACRX_DXF_DEFINE_MEMBERS(AsdkEmployeeDetails, AcDbObject,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyObject::kNoOperation,
                        ASDKEMPLOYEE_DETAILS, AsdkEmployeeDetails
);
//}}AFX_ARX_MACRO


// Constructor / Destructor

AsdkEmployeeDetails::AsdkEmployeeDetails()
{
	// TODO: do your initialization.
	m_firstName = NULL;
	m_lastName  = NULL;
}

AsdkEmployeeDetails::~AsdkEmployeeDetails()
{
	// TODO: clean up.

}


Acad::ErrorStatus AsdkEmployeeDetails::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;

	// Call dwgInFields from AcDbObject
	if ((es = AcDbObject::dwgInFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Read version number.
	Adesk::UInt16 version;
	pFiler->readItem(&version);
	if (version > VERSION_ASDKEMPLOYEEDETAILS)
		return Acad::eMakeMeProxy;

	// Read the data members.
	switch (version)
	{
	case (1):
		pFiler->readItem(&m_lastName);
		pFiler->readItem(&m_firstName);
		pFiler->readItem(&m_cube);
		pFiler->readItem(&m_ID);
		// TODO: here you can file datamembers not
		//       created by the ObjectARX Add-In.

		break;
	}


	return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkEmployeeDetails::dwgOutFields(AcDbDwgFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	// Call dwgOutFields from AcDbObject
	if ((es = AcDbObject::dwgOutFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Write version number.
	pFiler->writeItem((Adesk::UInt16) VERSION_ASDKEMPLOYEEDETAILS);

	// Write the data members.
	pFiler->writeItem(m_lastName);
	pFiler->writeItem(m_firstName);
	pFiler->writeItem(m_cube);
	pFiler->writeItem(m_ID);
	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.


	return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkEmployeeDetails::dxfInFields(AcDbDxfFiler* pFiler)
{
	assertWriteEnabled();
	struct resbuf rb;

	if ((AcDbObject::dxfInFields(pFiler) != Acad::eOk) ||
	    !pFiler->atSubclassData("AsdkEmployeeDetails"))
		return pFiler->filerStatus();

	// Read version number.
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt16) {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected object version group code %d",
		                 AcDb::kDxfInt16);
		return pFiler->filerStatus();
	} else {
		Adesk::UInt16 version = rb.resval.rint;
		if (version > VERSION_ASDKEMPLOYEEDETAILS)
			return Acad::eMakeMeProxy;
	}

	pFiler->readItem(&rb);
	if (rb.restype == AcDb::kDxfXTextString) {
		if (m_lastName != NULL)
			free(m_lastName);
		m_lastName = strdup(rb.resval.rstring);
	} else {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected group code %d",
		                AcDb::kDxfXTextString);
		return pFiler->filerStatus();
	}

	pFiler->readItem(&rb);
	if (rb.restype == AcDb::kDxfXTextString + 1) {
		if (m_firstName != NULL)
			free(m_firstName);
		m_firstName = strdup(rb.resval.rstring);
	} else {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected group code %d",
		                AcDb::kDxfXTextString + 1);
		return pFiler->filerStatus();
	}

	pFiler->readItem(&rb);
	if (rb.restype == AcDb::kDxfInt32) {
		m_cube = rb.resval.rlong; 
	} else {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected group code %d",
		                AcDb::kDxfInt32);
		return pFiler->filerStatus();
	}

	pFiler->readItem(&rb);
	if (rb.restype == AcDb::kDxfInt32 + 1) {
		m_ID = rb.resval.rlong; 
	} else {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected group code %d",
		                AcDb::kDxfInt32 + 1);
		return pFiler->filerStatus();
	}

	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.

	return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkEmployeeDetails::dxfOutFields(AcDbDxfFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	if ((es = AcDbObject::dxfOutFields(pFiler)) != Acad::eOk)
		return es;

	// Write version number.
	pFiler->writeItem(AcDb::kDxfInt16, (Adesk::UInt16) VERSION_ASDKEMPLOYEEDETAILS);

	pFiler->writeItem(AcDb::kDxfSubclass, "AsdkEmployeeDetails");
	pFiler->writeItem(AcDb::kDxfXTextString, m_lastName);
	pFiler->writeItem(AcDb::kDxfXTextString + 1, m_firstName);
	pFiler->writeItem(AcDb::kDxfInt32, m_cube);
	pFiler->writeItem(AcDb::kDxfInt32 + 1, m_ID);

	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.

	return es;
}

Acad::ErrorStatus AsdkEmployeeDetails::lastName(char *& lastName)
{
	assertReadEnabled();
	lastName = strdup(m_lastName);
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::setLastName(const char* lastName)
{
	assertWriteEnabled();
	if (m_lastName)
		free(m_lastName);
	m_lastName = strdup(lastName);
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::firstName(char *& firstName)
{
	assertReadEnabled();
	firstName = strdup(m_firstName);
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::setFirstName(const char* firstName)
{
	assertWriteEnabled();
	if (m_firstName)
		free(m_firstName);
	m_firstName = strdup(firstName);
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::cube(Adesk::Int32& cube)
{
	assertReadEnabled();
	cube = m_cube;
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::setCube(const Adesk::Int32 cube)
{
	assertWriteEnabled();
	m_cube = cube;
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::iD(Adesk::Int32& ID)
{
	assertReadEnabled();
	ID = m_ID;
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployeeDetails::setID(const Adesk::Int32 ID)
{
	assertWriteEnabled();
	m_ID = ID;
  return Acad::eOk;
}

