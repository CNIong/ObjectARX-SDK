//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#include "blockorderfilter.h"
#include "blockorderindex.h"
#include "blockorderiterator.h"

ACRX_DXF_DEFINE_MEMBERS(AsdkBlockOrderFilter,AcDbFilter,AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,0,AsdkBLOCKORDERFILTER,AsdkBlockOrder);

//classes may change their version without changing the dwg version
//so we need a seperate version number
Adesk::Int16 AsdkBlockOrderFilter::classVersion = 1;

AsdkBlockOrderFilter::~AsdkBlockOrderFilter()
{
}

AcRxClass* AsdkBlockOrderFilter::indexClass() const
{
    assertReadEnabled();
	return AsdkBlockOrderIndex::desc();
}

Acad::ErrorStatus AsdkBlockOrderFilter::dwgInFields (AcDbDwgFiler* pFiler)
{
    assertWriteEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbFilter::dwgInFields(pFiler))!=Acad::eOk)
        return es;

    //read the version of this piece of persistent data
    Adesk::Int16 version;
    pFiler->readInt16(&version);
    if (version > classVersion)
      return Acad::eMakeMeProxy;//it was saved by a newer version of this class
    //remove old items
    for (;mSentToTop.length()>0;)
        mSentToTop.removeAt(0);
    for (;mSentToBottom.length()>0;)
        mSentToBottom.removeAt(0);
    //read the new ones
    Adesk::UInt32 len;
    pFiler->readUInt32(&len);
    unsigned int i;
    AcDbSoftPointerId id;
    for (i=0;i<len;i++)
    {
        pFiler->readSoftPointerId(&id);
        //this is where we get rid of non translated (erased, not copied etc.) objects
        if (!id.isNull())
            mSentToTop.append(id);
    }
    pFiler->readUInt32(&len);
    for (i=0;i<len;i++)
    {
        pFiler->readSoftPointerId(&id);
        //this is where we get rid of non translated (erased, not copied etc.) objects
        if (!id.isNull())
            mSentToBottom.append(id);
    }
    return pFiler->filerStatus();
}
Acad::ErrorStatus AsdkBlockOrderFilter::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    if ((es=AcDbFilter::dwgOutFields(pFiler))!=Acad::eOk)
        return es;
    //write class version
    pFiler->writeInt16(classVersion);
    pFiler->writeUInt32(mSentToTop.length());
    int i;
    for (i=0;i<mSentToTop.length();i++)
        pFiler->writeSoftPointerId(mSentToTop[i]);
    pFiler->writeUInt32(mSentToBottom.length());
    for (i=0;i<mSentToBottom.length();i++)
        pFiler->writeSoftPointerId(mSentToBottom[i]);
    return pFiler->filerStatus();
}

Acad::ErrorStatus AsdkBlockOrderFilter::moveToTop(const AcDbObjectId& id)
{
    assertWriteEnabled();
    int pos;
    //make sure it does not live in any of the arrays yet
    if (mSentToTop.find(id,pos))
        mSentToTop.removeAt(pos);
    if (mSentToBottom.find(id,pos))
        mSentToBottom.removeAt(pos);
    //add it
    mSentToTop.append(id);
    return Acad::eOk;
}
Acad::ErrorStatus AsdkBlockOrderFilter::moveToBottom(const AcDbObjectId& id)
{
    assertWriteEnabled();
    int pos;
    //make sure it does not live in any of the arrays yet
    if (mSentToTop.find(id,pos))
        mSentToTop.removeAt(pos);
    if (mSentToBottom.find(id,pos))
        mSentToBottom.removeAt(pos);
    //add it
    mSentToBottom.append(id);
    return Acad::eOk;
}