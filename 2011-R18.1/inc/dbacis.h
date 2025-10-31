#ifndef DB_API_DBACIS_H
#define DB_API_DBACIS_H
//
//
// (C) Copyright 1993-2008 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// Internal AutoCAD functions dealing with ACIS-based entities which are 
// exported to be used by Autodesk Designer and related products.
//

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
