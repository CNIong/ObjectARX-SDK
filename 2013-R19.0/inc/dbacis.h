//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
// DESCRIPTION:
//
// Internal AutoCAD functions dealing with ACIS-based entities which are 
// exported to be used by Autodesk Designer and related products.
//

#ifndef DB_API_DBACIS_H
#define DB_API_DBACIS_H

#include "acdb.h"
#pragma pack (push, 8)

class AcDbDwgFiler;
class AcDbDxfFiler;
class ENTITY;

extern "C"
{
	void acdbModelerStart();
	void acdbModelerEnd();
	Adesk::Boolean acdbIsModelerStarted();

    Acad::ErrorStatus acdbAcisSaveEntityToDwgFiler     (AcDbDwgFiler* filer, 
							ENTITY*       ent);
    Acad::ErrorStatus acdbAcisSaveEntityToDwgFiler2     (AcDbDwgFiler* filer, 
							ENTITY*       ent, AcDbDatabase* pDb);
    Acad::ErrorStatus acdbAcisRestoreEntityFromDwgFiler(AcDbDwgFiler* filer, 
							ENTITY*&      ent);
    Acad::ErrorStatus acdbAcisSaveEntityToDxfFiler     (AcDbDxfFiler* filer, 
                            ENTITY*       ent);
    Acad::ErrorStatus acdbAcisSaveEntityToDxfFiler2     (AcDbDxfFiler* filer, 
                            ENTITY*       ent, AcDbDatabase* pDb);
    Acad::ErrorStatus acdbAcisRestoreEntityFromDxfFiler(AcDbDxfFiler* filer, 
                            ENTITY*&      ent); 

    // Set/get flag whether the ACIS bulletins are going to be deleted at the
    // beginning of each AutoCAD command. The initial value is kTrue, i.e. the
    // bulletins are always deleted to save memory.
    //
    // Disabling deletion of ACIS bulletins is needed by Designer, who
    // uses ads_command() calls in the middle of other code which expects
    // the ACIS bulletins to be present.

    void           acdbAcisSetDeleteBulletins(Adesk::Boolean onOff);
    Adesk::Boolean acdbAcisGetDeleteBulletins();

	// api to set the ACIS save versions for DWG
	Adesk::Boolean acdbSetAcisDwgVer(int version);

    void           acdbAcisDeleteModelerBulletins(void);
}

// #defines for the old names of the functions, they will be removed soon.
// Please do not use the old names any more.

#define acdbSaveAcisEntityToDwgFiler      acdbAcisSaveEntityToDwgFiler
#define acdbRestoreAcisEntityFromDwgFiler acdbAcisRestoreEntityFromDwgFiler

#pragma pack (pop)
#endif
