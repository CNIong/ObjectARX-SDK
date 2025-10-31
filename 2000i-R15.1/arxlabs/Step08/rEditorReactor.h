/////////////////////////////////////////////
// AcEditorReactor reactors.

#if !defined(ARX__REDITORREACTOR_H__19990619_151317)
#define ARX__REDITORREACTOR_H__19990619_151317

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbidmap.h"
#include "aced.h"


class AsdkEdEmployeeReactor : public AcEditorReactor
{
public:

	// Constructor / Destructor
	AsdkEdEmployeeReactor(const bool autoInitAndRelease = true);
	virtual ~AsdkEdEmployeeReactor();

	//{{AFX_ARX_METHODS(AsdkEdEmployeeReactor)
	virtual void commandEnded(const char* cmdStr);
	virtual void commandWillStart(const char* cmdStr);
	//}}AFX_ARX_METHODS

private:
	// Auto initialization and release flag.
	bool m_autoInitAndRelease;
};



#endif // !defined(ARX__REDITORREACTOR_H__19990619_151317)