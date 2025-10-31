#ifndef _RXDITER_H
#define _RXDITER_H 1
//
// (C) Copyright 1992-2006 by Autodesk, Inc.
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
// DESCRIPTION:  header file for class RxDictIterator
// This is a layer of commonality between the two iterators needed for
// RxIDDictionary; RxDictSkipListIterator, and RxDictArrayIterator.

#include "rxobject.h"
#include "rxiter.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class AcRxDictionaryIterator: public AcRxIterator
{
public:
    ACRX_DECLARE_MEMBERS(AcRxDictionaryIterator);

    virtual const ACHAR * key   () const = 0;
    virtual AcRxObject*   object() const = 0;
    virtual Adesk::UInt32 id    () const = 0;
};

#pragma pack (pop)
#endif
