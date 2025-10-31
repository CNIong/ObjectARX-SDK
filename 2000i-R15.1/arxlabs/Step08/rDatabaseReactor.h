/////////////////////////////////////////////
// AcDbDatabaseReactor reactors.

#if !defined(ARX__RDATABASEREACTOR_H__19990619_154636)
#define ARX__RDATABASEREACTOR_H__19990619_154636

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbmain.h"


class AsdkDbEmployeeReactor : public AcDbDatabaseReactor
{
public:

	// Constructor / Destructor
	AsdkDbEmployeeReactor(const bool storeInDocVars = true, AcApDocument* pDoc = curDoc());
	virtual ~AsdkDbEmployeeReactor();

	//{{AFX_ARX_METHODS(AsdkDbEmployeeReactor)
	virtual void objectAppended(const AcDbDatabase* dwg,
	                            const AcDbObject* dbObj);
	//}}AFX_ARX_METHODS

private:
	// Pointer to the document this reactor instance belongs to.
	AcApDocument* m_pDoc;
};



#endif // !defined(ARX__RDATABASEREACTOR_H__19990619_154636)