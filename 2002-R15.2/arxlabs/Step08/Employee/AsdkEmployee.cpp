/////////////////////////////////////////////
// AsdkEmployee custom object.

#include "StdAfx.h"
#include "StdArx.h"
#include "dbproxy.h"
#include "geassign.h"
#include "acgi.h"

#define VERSION_ASDKEMPLOYEE 1


//{{AFX_ARX_MACRO
ACRX_DXF_DEFINE_MEMBERS(AsdkEmployee, AcDbEllipse,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyEntity::kNoOperation,
                        ASDKEMPLOYEE, AsdkEmployee
);
//}}AFX_ARX_MACRO


// Constructor / Destructor

AsdkEmployee::AsdkEmployee() : AcDbEllipse (AcGePoint3d (), AcGeVector3d (0, 0, 1), AcGeVector3d (1, 0, 0), 1)
{
	// TODO: do your initialization.
	m_firstName =m_lastName =NULL ;
}

AsdkEmployee::~AsdkEmployee()
{
	// TODO: clean up.

}


Acad::ErrorStatus AsdkEmployee::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;

	// Call dwgInFields from AcDbEllipse
	if ((es = AcDbEllipse::dwgInFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Read version number.
	Adesk::UInt16 version;
	pFiler->readItem(&version);
	if (version > VERSION_ASDKEMPLOYEE)
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

Acad::ErrorStatus AsdkEmployee::dwgOutFields(AcDbDwgFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	// Call dwgOutFields from AcDbEllipse
	if ((es = AcDbEllipse::dwgOutFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Write version number.
	pFiler->writeItem((Adesk::UInt16) VERSION_ASDKEMPLOYEE);

	// Write the data members.
	pFiler->writeItem(m_lastName);
	pFiler->writeItem(m_firstName);
	pFiler->writeItem(m_cube);
	pFiler->writeItem(m_ID);
	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.


	return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkEmployee::dxfInFields(AcDbDxfFiler* pFiler)
{
	assertWriteEnabled();
	struct resbuf rb;

	if ((AcDbEllipse::dxfInFields(pFiler) != Acad::eOk) ||
	    !pFiler->atSubclassData("AsdkEmployee"))
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
		if (version > VERSION_ASDKEMPLOYEE)
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

Acad::ErrorStatus AsdkEmployee::dxfOutFields(AcDbDxfFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	if ((es = AcDbEllipse::dxfOutFields(pFiler)) != Acad::eOk)
		return es;

	// Write version number.
	pFiler->writeItem(AcDb::kDxfInt16, (Adesk::UInt16) VERSION_ASDKEMPLOYEE);

	pFiler->writeItem(AcDb::kDxfSubclass, "AsdkEmployee");
	pFiler->writeItem(AcDb::kDxfXTextString, m_lastName);
	pFiler->writeItem(AcDb::kDxfXTextString + 1, m_firstName);
	pFiler->writeItem(AcDb::kDxfInt32, m_cube);
	pFiler->writeItem(AcDb::kDxfInt32 + 1, m_ID);

	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.

	return es;
}

Acad::ErrorStatus AsdkEmployee::lastName(char*& lastName)
{
	assertReadEnabled();
	lastName = strdup(m_lastName);
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::setLastName(const char* lastName)
{
	assertWriteEnabled();
	if (m_lastName)
		free(m_lastName);
	m_lastName = strdup(lastName);
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::firstName(char*& firstName)
{
	assertReadEnabled();
	firstName = strdup(m_firstName);
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::setFirstName(const char* firstName)
{
	assertWriteEnabled();
	if (m_firstName)
		free(m_firstName);
	m_firstName = strdup(firstName);
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::cube(Adesk::UInt32& cube)
{
	assertReadEnabled();
	cube = m_cube;
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::setCube(const Adesk::UInt32 cube)
{
	assertWriteEnabled();
	m_cube = cube;
  return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::iD(Adesk::UInt32& ID)
{
	assertReadEnabled();
	ID = m_ID;
	return Acad::eOk;
}

Acad::ErrorStatus AsdkEmployee::setID(const Adesk::UInt32 ID)
{
	assertWriteEnabled();
	m_ID = ID;
  return Acad::eOk;
}

Adesk::Boolean AsdkEmployee::worldDraw(AcGiWorldDraw* mode)
{
	assertReadEnabled();
	// TODO: implement this function.

	//----- Draw the entity
	AcDbEllipse::worldDraw (mode) ;
	//----- Write the Employee ID and Name
	char buffer [255] ;
	sprintf (buffer, "%d (cube#: %d)", m_ID, m_cube) ;
	mode->geometry ().text (center (), normal (), majorAxis (), minorAxis ().length () / 2, 1.0, 0.0, buffer) ;
	sprintf (buffer, "%s %s", m_firstName, m_lastName) ;
	mode->geometry ().text (center () - minorAxis () / 2, normal (), majorAxis (), minorAxis ().length () / 2, 1.0, 0.0, buffer) ;
	//----- Returns Adesk::kTrue to not call viewportDraw()
	return (Adesk::kTrue) ;
}

