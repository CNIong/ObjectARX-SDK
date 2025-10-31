//
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2000-2002 by Autodesk, Inc.
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

#include <adslib.h>
#include <aced.h>
#include <rxregsvc.h>
#include <dbmain.h>
#include <dbapserv.h>
#include <acdocman.h>
#include <acedinpt.h>
#include <acssgetfilter.h>


class MySSGetFilter : public AcEdSSGetFilter
{
public:

    void ssgetAddFilter(
	    int ssgetFlags,
	    AcEdSelectionSetService &service,
	    const AcDbObjectIdArray& selectionSet,
	    const AcDbObjectIdArray& subSelectionSet);
};


void
addMyFilter()
{
    // The ssget filter is required to highlight the subentities.
    //
    MySSGetFilter ssGetFilter;
    addSSgetFilterInputContextReactor(curDoc(), &ssGetFilter);

    // we have to allow duplicates; otherwise, the xref could be selected
    // only once (because the main entity is the one that counts).
    //
    setAllowDuplicateSelection(curDoc(), true);

    ads_name sset, eName;
	AcDbObjectId id;
	
    // "_:n" gives us nested entities
    //
    if (RTNORM == acedSSGet("_:n", NULL, NULL, NULL, sset))
    {
        acutPrintf("\n");
        long len = 0;
        acedSSLength(sset, &len);
        for (long i = 0; i < len; i++)// For each entity in sset
        {
           
			resbuf *rb = NULL;
            // We use ssnamex() here, because the regular ssname()
            // would give only the main entity (the xref)
            //
            if (RTNORM == acedSSNameX(&rb, sset, i))//Get the sub entity
            {
                resbuf *rbWalk = rb;
                while (NULL != rbWalk)
                {
                    if (RTENAME == rbWalk->restype)
                    {
                        eName[0] = rbWalk->resval.rlname[0];
						eName[1] = rbWalk->resval.rlname[1];
						if(Acad::eOk == acdbGetObjectId(id, eName))
						{					
							acutPrintf("Entity %d: <%x>", i, id.asOldId());
							AcDbEntity *pEnt;
							if (Acad::eOk == acdbOpenObject(pEnt, id, AcDb::kForRead))
							{
								acutPrintf("(%s)\n", pEnt->isA()->name());
								pEnt->close();
							}
							else
								acutPrintf("\nCouldn't open object");
						}
						rbWalk = NULL; //force quit out of loop	
					}
                    else
                        rbWalk = rbWalk->rbnext;
                }
                acutRelRb(rb);
            }
        }
        acedSSFree(sset);
    }

    setAllowDuplicateSelection(curDoc(), false);
    removeSSgetFilterInputContextReactor(curDoc(), &ssGetFilter);
}


void MySSGetFilter::ssgetAddFilter(int ssgetFlags, AcEdSelectionSetService& service, 
        const AcDbObjectIdArray& selectionSet, const AcDbObjectIdArray& 
        subSelectionSet)
{
    // Just do the subentity highlighing here, nothing else.
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
            service.highlight(i, fsp);
            acutRelRb(rb);
        }
    }
}


extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void *p)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(p);
        acrxRegisterAppMDIAware(p);
        acedRegCmds->addCommand("ASDK_SELECTION_FILTER", "test", "test", ACRX_CMD_TRANSPARENT,
            addMyFilter);
        break;

    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup("ASDK_SELECTION_FILTER");
        break;
    }
    return AcRx::kRetOK;
}
