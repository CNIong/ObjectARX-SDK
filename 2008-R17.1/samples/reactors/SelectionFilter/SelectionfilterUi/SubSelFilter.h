//
//
// (C) Copyright 1990-2006 by Autodesk, Inc. 
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
#pragma once
#include "subselect.h"
#include "StdAfx.h"

class CSubSelFilter :
	public AcEdSubSelectFilter
{
public:
	CSubSelFilter(void);
	~CSubSelFilter(void);

	    virtual bool selectEntity(
            const AcGePoint3d&  wvpt, 
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
            double              wxaper,
            double              wyaper,
            long                ssgetFlags,
            const AcGiViewport* pCurVp,
            AcDbEntity*         pEnt) const;
  
		virtual AcEdSubSelectFilter::SubSelectStatus subSelectEntity(
            const AcGePoint3d&  wpt1,
            const AcGePoint3d&  wpt2,
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
			double wxaper,
			double wyaper,                             
			AcDb::SelectType    seltype,
			bool                bAugment,
			bool                bIsInPickfirstSet,
            bool                bEvery,
			const AcGiViewport* pCurVP,
			AcDbEntity*         pEnt,
			AcSubentPathArray&  paths);

		virtual bool reSubSelectEntity(AcDbEntity* pEnt, AcSubentPathArray& paths);
       virtual bool cancelAllSubSelect();
	    virtual bool cancelSubSelect(AcDbEntity* pEnt);
	   virtual Acad::ErrorStatus subSelectClassList(AcArray<AcRxClass*>& clsIds);
	   //virtual bool onKey(unsigned long wMsg, unsigned int nChar, unsigned int rptCnt, unsigned int flags);

	
private:
	AcDbObjectIdArray mSelectedEnts;
	//bool m_selstatus; //selection status (true= full selection, false=subselection)

};
