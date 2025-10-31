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

#ifndef _LAB7PERDOCDATA_H_
#define _LAB7PERDOCDATA_H_

#include "dbidar.h"
#include "gept3dar.h"
#include "Lab7DatabaseReactor.h"


#include "acdocman.h"
#include <map>

class AsdkChangedEmployees
{ 
public:
	AsdkChangedEmployees();
	AcDbObjectIdArray ChangedIds;
	AcGePoint3dArray  EmployeePositions;
	bool EditCommand,
		 NoObjReactor;
    AsdkLab7DbReactor* m_pDbReactor;
}; 

class AsdkLab7DataManager : public AcApDocManagerReactor
{
public:
    AsdkLab7DataManager();
    virtual ~AsdkLab7DataManager();
	virtual void documentToBeActivated(AcApDocument* pDoc); 
    virtual void documentToBeDestroyed( AcApDocument *pDoc );
    AsdkChangedEmployees& docData(AcApDocument* pDoc)
    {
        return m_dataMap[ pDoc ];
    }
    AsdkChangedEmployees& docData()
    {
        return docData(acDocManager->curDocument());
    }
    
private:
    std::map<AcApDocument*, AsdkChangedEmployees> m_dataMap;
};


extern AsdkLab7DataManager lab7DataMgr; // MDI Safe
#define chEmployeesInfo lab7DataMgr.docData()

#endif // _LAB7PERDOCDATA_H_