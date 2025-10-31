// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// SUBENT.CPP

#include  <stdio.h>
#include "dbents.h"
#include "gemat3d.h"
#include "adslib.h"
#include "string.h"

Acad::ErrorStatus postToDatabase(AcDbEntity*, AcDbObjectId&);

int 
extractEntityInfo(struct resbuf *rb,
                  int&      sel_method,
                  ads_name  ename,
                  ads_name  subname,
                  short&	marker,
                  AcGePoint3d&    pickpnt,
                  AcGeVector3d&   pickvec,
                  // AcGeMatrix3d& xform,
                  struct resbuf*& containers);


static  Adesk::Boolean
getYesOrNo(char* promptStr)
{
    char option[256];
    Adesk::Boolean yes = Adesk::kTrue;
    
    ads_initget(0, "Yes No");
    int as = ads_getkword(promptStr, option);
    
    switch (as) {
    case RTNORM:
        if (strcmp(option, "Yes") == 0)
            yes = Adesk::kTrue;
        else
            yes = Adesk::kFalse;
        break;
        
    case RTNONE:
    case RTCAN:
    default:
        break;
    }
    
    return yes;
}


Acad::ErrorStatus
getSubEntPtr(AcDbObjectId& objId)
{
    Acad::ErrorStatus	es ;
    
    ads_name  		 ename,subname, sset;
    AcDbObjectId	 entId;
    AcDbEntity*		 ent = NULL ;
    int  			 numIds;
    short 			 marker;
    AcGeMatrix3d	 xForm;
    AcGeVector3d     pickvec;
    int 			 sel_method;
    struct	resbuf	 *rb;
    struct  resbuf   *containers;
    AcGePoint3d		 pickpnt;
    
    //ads_prompt("\nSelect entity: ");
    if (ads_ssget(NULL, NULL, NULL, NULL, sset) != RTNORM)
    {
        //ads_printf("\nFailed: Incorrect selection set (ads_ssget)");
        return Acad::eUnrecoverableErrors ;
    }
    
    if (ads_ssnamex(&rb,sset,0) != RTNORM)
    {
        ads_ssfree(sset);
        //ads_printf("\nFailed: Incorrect selection set (ads_ssnamex)");
        return Acad::eUnrecoverableErrors;
    }
    ads_ssfree(sset);

    
    if (!extractEntityInfo(rb,
        sel_method,
        ename,
        subname,
        marker,
        pickpnt,
        pickvec,
        // AcGeMatrix3d& xform,
			     containers)) 
    {
        ads_relrb(rb);
        ads_printf("\nFailed: Incorrect Entity Info");
        return Acad::eUnrecoverableErrors ;
    }
    ads_relrb(rb);

    es = acdbGetObjectId(entId, ename);
    
    if (es != Acad::eOk) 
    {
        ads_printf("\nFailed: Errorcode for acdbGetObjectId() is: %d\n", es);
        return Acad::eUnrecoverableErrors ;
    }
    
    es = acdbOpenAcDbEntity(ent, entId, AcDb::kForRead);
    
    if (es != Acad::eOk) 
    {
        ads_printf("\nFailed: Errorcode for acdbOpenAcDbEntity() is: %d\n", es);
        return es;
    }
    
    
    AcDbFullSubentPath*   subentIds;
    
    // AcDb::SubentType needs to be changed for each entity type 
    
    es = ent->getSubentPathsAtGsMarker (AcDb::kFaceSubentType, 
        marker,
        pickpnt,
        xForm,
        numIds,
        subentIds);
    
    if (es != Acad::eOk) 
    {
        ads_printf("\nFailed: Errorcode for gsMarkerToSubentIds() is: %d\n", es);
        ent->close();
        return es;
    }
    
    int i=0;
    ent->highlight(subentIds[i]);
    while (!getYesOrNo("Is this the face <Yes>/No: ")){
        ent->unhighlight(subentIds[i]);
        if (++i >=numIds)
            i =0;
        ent->highlight(subentIds[i]);
    }
    
    // unhilight the subent
    ent->unhighlight(subentIds[i]);
    AcDbEntity*  pEnt = ent->subentPtr(subentIds[i]); 
    delete[] subentIds;
    
    if (pEnt == NULL) 
    {
        ads_printf("\nFailed: subentPtr()\n");
        ent->close();
        return Acad::eUnrecoverableErrors;
    }
    
    es = postToDatabase(pEnt, objId);
    if (es != Acad::eOk) 
    {
        ads_printf("\nFailed: Errorcode for postToDb() is: %d\n", es);
        ent->close();
        delete pEnt;
        return es;
    }
    ent->close();
    
    return Acad::eOk;
}




int extractEntityInfo(struct resbuf *rb,
                      int&      sel_method,
                      ads_name  ename,
                      ads_name  subname,
                      short&	marker,
                      AcGePoint3d&    pickpnt,
                      AcGeVector3d&   pickvec,
                      // AcGeMatrix3d& xform,
                      struct resbuf*& containers)
{
    if ( rb == NULL || rb->restype != RTLB )
    {
        assert(0);
        return 0;
    }
    
    // Get the selection method.
    //
    rb = rb->rbnext;  // Bump up to the selection method, always after RTLB.
    sel_method = rb->resval.rint;
    
    // Get the first ename (could be either the actual entity name or
    // subentity name).
    //
    rb = rb->rbnext;  // Bump up to the first name, always after sel method.
    ename[0] = rb->resval.rlname[0];
    ename[1] = rb->resval.rlname[1];
    subname[0] = rb->resval.rlname[0];
    subname[1] = rb->resval.rlname[1];
    
    // Get marker info.
    //
    rb = rb->rbnext;
    marker = rb->resval.rint;
    
    return 1;
}
