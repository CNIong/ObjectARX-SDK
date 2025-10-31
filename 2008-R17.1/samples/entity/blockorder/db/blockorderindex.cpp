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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "blockorderindex.h"
#include "blockorderiterator.h"



ACRX_DXF_DEFINE_MEMBERS(AsdkBlockOrderIndex,AcDbIndex,AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,0,ASDKBLOCKORDERINDEX,AsdkBlockOrder);

//classes may change their version without changing the dwg version
//so we need a seperate version number
Adesk::Int16 AsdkBlockOrderIndex::classVersion = 1;

AsdkBlockOrderIndex::~AsdkBlockOrderIndex()
{
}

AcDbFilteredBlockIterator* AsdkBlockOrderIndex::newIterator(const AcDbFilter* pFilter) const
{
    assertReadEnabled();
    if (!pFilter->isKindOf(AsdkBlockOrderFilter::desc()))
        return NULL;
    return new AsdkBlockOrderIterator(AsdkBlockOrderFilter::cast(pFilter),objectBeingIndexedId());
}

Acad::ErrorStatus AsdkBlockOrderIndex::rebuildFull(AcDbIndexUpdateData* pIdxData)
{
    //there's nothing to rebuild
    assertWriteEnabled();
    return Acad::eOk;
}

Acad::ErrorStatus AsdkBlockOrderIndex::rebuildModified(AcDbBlockChangeIterator* iter)
{
    //there's nothing to rebuild
    assertWriteEnabled();
    return Acad::eOk;
}

Acad::ErrorStatus AsdkBlockOrderIndex::dwgInFields (AcDbDwgFiler* pFiler)
{
    //right now we don't save and load any persistent state
    //still we write the class version so later revisions can recognize
    //this version
    assertWriteEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbIndex::dwgInFields(pFiler))!=Acad::eOk)
        return es;

    //read the version of this piece of persistent data
    Adesk::Int16 version;
    pFiler->readInt16(&version);
    if (version > classVersion)
      return Acad::eMakeMeProxy;//it was saved by a newer version of this class

    return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkBlockOrderIndex::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    //right now we don't save and load any persistent state
    //still we write the class version so later revisions can recognize
    //this version
    assertReadEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbIndex::dwgOutFields(pFiler))!=Acad::eOk)
        return es;
    //write class version
    pFiler->writeInt16(classVersion);
    return pFiler->filerStatus();
}