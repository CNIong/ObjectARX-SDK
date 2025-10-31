//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgReferenceFiler.h"



ACRX_CONS_DEFINE_MEMBERS(ArxDbgReferenceFiler, AcDbDwgFiler, 0);

/****************************************************************************
**
**  ArxDbgReferenceFiler::writeHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgReferenceFiler::writeHardOwnershipId(const AcDbHardOwnershipId& id)
{
	if (id.isNull() == false)
		m_hardOwnershipIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgReferenceFiler::writeSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgReferenceFiler::writeSoftOwnershipId(const AcDbSoftOwnershipId& id)
{
	if (id.isNull() == false)
		m_softOwnershipIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgReferenceFiler::writeHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgReferenceFiler::writeHardPointerId(const AcDbHardPointerId& id)
{
	if (id.isNull() == false)
		m_hardPointerIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgReferenceFiler::writeSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgReferenceFiler::writeSoftPointerId(const AcDbSoftPointerId& id)
{
	if (id.isNull() == false)
		m_softPointerIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgReferenceFiler::reset
**
**  **jma
**
*************************************/

void
ArxDbgReferenceFiler::reset()
{
    m_hardPointerIds.setLogicalLength(0);
    m_softPointerIds.setLogicalLength(0);
    m_hardOwnershipIds.setLogicalLength(0);
    m_softOwnershipIds.setLogicalLength(0);
}