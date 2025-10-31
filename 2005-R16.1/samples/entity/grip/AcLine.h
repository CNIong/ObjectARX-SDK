//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

# ifndef _ACLINE_H
# define _ACLINE_H

# include "GripImp.h"
# include "dbgrip.h"
#pragma once 


//========================================================================
//
// AcLine class declaration
//
//========================================================================

class AcLine : public AcDbEntity
{
	enum 
	{ GripCount=3};

public:
	ACRX_DECLARE_MEMBERS(AcLine);
	AcLine();
	AcLine(const AcGePoint3d &sp,const AcGePoint3d &ep);
	virtual ~AcLine();

	
	Acad::ErrorStatus dwgInFields(AcDbDwgFiler*);
	Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
	Acad::ErrorStatus dxfInFields(AcDbDxfFiler*);
	Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;
	
	Adesk:: Boolean   worldDraw(AcGiWorldDraw* mode);

	Acad::ErrorStatus getGripPoints(AcGePoint3dArray&,AcDbIntArray&,
					  			    AcDbIntArray&) const;
	Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray&,
									   const AcGeVector3d&);
	//New overloaded grip methods that need to be implemented 
	//to use the Grip Enhancement
	Acad::ErrorStatus  getGripPoints(AcDbGripDataPtrArray& grips,
                                     const double viewSize,
		                             const AcGeVector3d& offset, 
                                     const int bitflags) const;
	
	Acad::ErrorStatus  moveGripPointsAt(const AcDbVoidPtrArray&,
										const AcGeVector3d&,
                                        const int bitflags);
	
	Acad::ErrorStatus   transformBy(const AcGeMatrix3d& xform);

	void dragStatus(const AcDb::DragStat status);
	void gripStatus(const AcDb::GripStat status);
	

private:
	AcGePoint3d						 msp; // start point
	AcGePoint3d						 mep; // end point
	AcGePoint3d						 mcp; //Center point
	static appDataType				 msAppData; //AppData
	static appDataType::iterator     putAppData();
};

#endif//_ACLINE_H