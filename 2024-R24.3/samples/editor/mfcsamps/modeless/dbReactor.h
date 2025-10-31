//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#ifndef _DBREACTOR_H
#define _DBREACTOR_H

class CDbModReactor : public AcDbDatabaseReactor
{
public:
	virtual void objectModified(const AcDbDatabase* pDb,
								const AcDbObject* pDbObj);
	virtual void objectErased(	const AcDbDatabase* pDb,
								const AcDbObject* pDbObj,
								Adesk::Boolean bErased = Adesk::kTrue);

};

#endif // _DBREACTOR_H
