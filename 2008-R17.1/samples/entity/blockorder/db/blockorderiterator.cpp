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

#include "blockorderiterator.h"
#include "dbsymtb.h"



AsdkBlockOrderIterator::AsdkBlockOrderIterator(const AsdkBlockOrderFilter* pFilter, const AcDbObjectId& idBTR) 
{
    mpFilter = pFilter;
    midBTR = idBTR;
    mbMain = true;
}

AsdkBlockOrderIterator::~AsdkBlockOrderIterator() 
{
    
}

Acad::ErrorStatus AsdkBlockOrderIterator::start()
{
    //initialize our position
    mPos = 0;
    AcDbObjectId id;
    if (mbMain) //we are the main iterator
    {
        mbMain = false;//we only need to initialize once
        //build the buffer with all the ids in the block table record
        AcDbBlockTableRecord* pBTR;
        if (acdbOpenObject(pBTR,midBTR,AcDb::kForRead)==Acad::eOk)
        {
            AcDbBlockTableRecordIterator* pIter;
            if (pBTR->newIterator(pIter)==Acad::eOk)
            {
                for (pIter->start();!pIter->done();pIter->step())
                {
                    if (pIter->getEntityId(id)==Acad::eOk)
                        mBuffer.append(id);
                }
                delete pIter;
            }
            pBTR->close();
        }
    }
    //nothing to do
    if (mBuffer.length()==0)
        return Acad::eOk;
    int pos;
    int i;            
    //fill in all the object that were 'sent back' in reverse order
    //the one sent back most lately should be the first to be regenerated
    const AcDbObjectIdArray* pOrder = &(mpFilter->sentToBottom());
    for (i=pOrder->length()-1;i>=0;i--)
    {
        if (mBuffer.find(pOrder->at(i),pos))
        {
            mIds.append(pOrder->at(i));
            mBuffer.removeAt(pos);
        }
    }
    //note where we stop with 'sent back' items
	int bottomHalf = mIds.length();
    //fill in the objects that were 'sent to top'
    pOrder = &(mpFilter->sentToTop());
    for (i=0;i<pOrder->length();i++)
    {
        if (mBuffer.find(pOrder->at(i),pos))
        {
            mIds.append(pOrder->at(i));
            mBuffer.removeAt(pos);
        }
    }
    //insert the rest in between
    //this is not reverse order just that's how insertAt works
     for (i=mBuffer.length()-1;i>=0;i--)
    {
        mIds.insertAt(bottomHalf,mBuffer[i]);
    }
    return Acad::eOk;
}
AcDbObjectId      AsdkBlockOrderIterator::next()
{
    AcDbObjectId temp = id();
    if (mIds.length()>mPos)
        mPos++;
	return temp;
}
AcDbObjectId      AsdkBlockOrderIterator::id() const
{
    if (mIds.length()>mPos)
        return mIds[mPos];
	return AcDbObjectId::kNull;
}

Acad::ErrorStatus AsdkBlockOrderIterator::seek(AcDbObjectId id)
{
    int temp;
    if (mIds.find(id,temp))
    {
        mPos = temp;
        return Acad::eOk;
    }
	return Acad::eKeyNotFound;
}
double AsdkBlockOrderIterator::estimatedHitFraction() const
{
    // so that other iterators are candidates for the main one before
    // this
	return 1.0; 
}
Acad::ErrorStatus AsdkBlockOrderIterator::accepts(AcDbObjectId id, 
          Adesk::Boolean& idPassesFilter) const
{
    //this is a buffering iterator so this is not applicable
	return Acad::eNotApplicable;
}
Adesk::Boolean    AsdkBlockOrderIterator::buffersForComposition() const
{
    //set this flag to false because we are not the main iterator
    const_cast<AsdkBlockOrderIterator*>(this)->mbMain = false; 
	return Adesk::kTrue;
}
Acad::ErrorStatus AsdkBlockOrderIterator::addToBuffer(AcDbObjectId id)
{
    //if we are not the main iterator then this function will be called
    //repeatedly with the results of the previous iterator
    mBuffer.append(id);
	return Acad::eOk;
}
