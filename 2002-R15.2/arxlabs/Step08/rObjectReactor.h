/////////////////////////////////////////////
// AcDbObjectReactor reactors.

#if !defined(ARX__ROBJECTREACTOR_H__19990619_152600)
#define ARX__ROBJECTREACTOR_H__19990619_152600

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbmain.h"


class AsdkEmployeeReactor : public AcDbObjectReactor
{
public:

	//{{AFX_ARX_METHODS(AsdkEmployeeReactor)
	virtual void openedForModify(const AcDbObject* dbObj);
	//}}AFX_ARX_METHODS

};



#endif // !defined(ARX__ROBJECTREACTOR_H__19990619_152600)