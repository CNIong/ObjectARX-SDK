//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
#include "subentselfilter.h"
#include <string.h>

CSubEntSelFilter::CSubEntSelFilter(void)
{
}

CSubEntSelFilter::~CSubEntSelFilter(void)
{
}

void CSubEntSelFilter::ssgetAddFilter(
	    int ssgetFlags,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
	    const AcDbObjectIdArray& subSelectionSet)

{
    // Just do the subentity highlighting here, nothing else.
    // (No modification of the resulting selection set)
    //
    ads_name eName;
	AcDbObjectId id;
	
	for (int i = 0; i < subSelectionSet.length(); i++)
    {
        resbuf * rb = NULL;
        service.ssNameX(true, i, rb);
        
        if (NULL != rb)
        {
            AcDbObjectIdArray curIdPath;
            resbuf *rbWalk = rb;
            while (NULL != rbWalk)
            {
                if (RTENAME == rbWalk->restype)
				{
                    eName[0] = rbWalk->resval.rlname[0];
					eName[1] = rbWalk->resval.rlname[1];
					if(Acad::eOk == acdbGetObjectId(id, eName))
						curIdPath.append(id);
				}
				rbWalk = rbWalk->rbnext;
            }
            // reverse the curIdPath order (required for highlighting)
            AcDbObjectIdArray reversedIdPath;
            for (int j = curIdPath.length() - 1; j >= 0; j--)
                reversedIdPath.append(curIdPath[j]);
            AcDbFullSubentPath fsp(reversedIdPath, AcDbSubentId());

			
			// Exempt AdskRings custom entity from highlighting, otherwise subselection will be overridden
            AcDbEntity *pEnt;
			char *cust_ent = "AsdkRings";
			if (Acad::eOk == acdbOpenObject(pEnt, id, AcDb::kForRead))
			{
				if (_stricmp(cust_ent,pEnt->isA()->name()) == 0){
					pEnt->close();
				     acutRelRb(rb);
					 return;
				}
			}


            if (service.highlight(i, fsp) !=  Acad::eOk)
				acutPrintf("\nHighlighting failed!");
    					pEnt->close();
						acutRelRb(rb);
        }
    }
}

