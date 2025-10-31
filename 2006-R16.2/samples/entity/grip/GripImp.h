//
// (C) Copyright 1998-2002,2004 by Autodesk, Inc. 
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

# ifndef _GRIPIMP_H
# define _GRIPIMP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "dbapserv.h"                 // AcDbHostApplicationServices
#include "actrans.h"
#include "adeskabb.h"
#include "acgi.h"
#include "math.h"
#include "dbproxy.h"
#include <comdef.h>
#include "dbgrip.h"
//stl headers
# include<vector>
# include<map>
# include<string>
#pragma once 


class GripData;
//typedef std::map<const char*,int> appData;
typedef std::map<const TCHAR*,int>::value_type grip_type;

typedef std::map<AcDbGripOperations::GripStatus,const TCHAR*> GripStatus;
typedef std::map<AcDbGripOperations::GripStatus,const TCHAR*>::value_type GripStatus_type;

typedef  std::vector<std::string>  appDataType;


Acad::ErrorStatus 
getCurrentEntity(AcDbEntity *&pEntity);

//========================================================================
//
// Grip Call back functions
//
//========================================================================
namespace GripCback
{

	AcDbGripOperations::ReturnValue
	hotGripfunc(					AcDbGripData			*pthis,
									const AcDbObjectId&		entId,
									int						contextFlags);
	
	AcDbGripOperations::ReturnValue
	hoverGripfunc(					AcDbGripData			*pthis,
									const AcDbObjectId&     eObjId,
									int					    contextFlags);

	void 
	ContextMenuItemIndexfunc(		unsigned int			 index);

	AcDbGripOperations::ReturnValue 
	Rtclkfunc(						AcDbGripDataArray		 &hotGrips,
									const AcDbObjectIdArray	 &ents, 
									char					 *&menuName,
									HMENU					 &menu,
									ContextMenuItemIndexPtr  &cb);
	
	void							    
	OpStatusfunc(			AcDbGripData					*pthis,
							const AcDbObjectId&				 entId,
							AcDbGripOperations::GripStatus	 stat);

	bool 
	WorldDrawfunc(					AcDbGripData			 *pThis,
									AcGiWorldDraw			 *pWd,
									const AcDbObjectId&		 entId, 
							AcDbGripOperations::DrawType	 type, 
									AcGePoint3d				 *cursor,
									double					 dGripSize);

	void 
	GripViewportDrawfunc(			AcDbGripData			 *pThis, 
									AcGiViewportDraw		 *pWd,
									const AcDbObjectId		 &entId, 
						  AcDbGripOperations::DrawType		 type, 
									AcGePoint3d				 *cursor,
									int						 gripSize);

	const TCHAR* 
	GripToolTipFunc		(			AcDbGripData* pThis);
		
};

//========================================================================
//
// Dynamic Dimensioning Call back functions
//
//========================================================================
namespace DynDimCback
{
	void
	hotGripDimensionfunc(			AcDbGripData			   *pGrip, 
									const AcDbObjectId		   &objId,
									AcDbDimDataPtrArray		   &dimDataArr);

	void
	hoverGripDimensionfunc(			AcDbGripData				*pGrip,
									const AcDbObjectId			&objId,
									AcDbDimDataPtrArray			&dimDataArr);
};
//========================================================================
//
// Color 
//
//========================================================================
namespace Colors
{
	static const Adesk::UInt16 kYellow=50;
	static const Adesk::UInt16 kRed=1; 
}

Adesk::Boolean addEntity(AcDbEntity *pEnt);

#endif//_GRIPIMP_H