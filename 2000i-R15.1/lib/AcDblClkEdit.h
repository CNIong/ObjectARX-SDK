//
// $Header: /banff/develop/global/inc/dbxsdk/AcDblClkEdit.h 2     3/30/00 5:27p Klugj $
//
// DoubleClickEdit.h - Double-click Editing (for external developers)
//
// Copyright © 1999 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary
// to Autodesk, Inc., and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of this information by anyone other than authorized
// employees of Autodesk, Inc. is granted only under a written
// non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
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
// DoubleClickEdit.h
//
// DESCRIPTION: AcDbDoubleClickEdit Protocol extension abstract base class
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//

#ifndef DOUBLECLICKEDIT_H
#define DOUBLECLICKEDIT_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

class AcDbDoubleClickEdit : public AcRxObject
//
//  AcDbDoubleClickEdit Protocol extension abstract base class. 
//
{
public:
	ACRX_DECLARE_MEMBERS(AcDbDoubleClickEdit);

	virtual void startEdit(AcDbEntity *pEnt, AcGePoint3d pt) = 0; 
	virtual void finishEdit(void) = 0;
};

#pragma pack (pop)

#endif //DOUBLECLICKEDIT_H
