#ifndef AD_DBFILTER_H
#define AD_DBFILTER_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// AcDbFilter is the base class for all Filter implementations.
//
// An AcDbFilter object can be associated with a block reference, and,
// if the corresponding Block has the equivalent AcDbIndex, a filtered
// traversal of the block can be performed.
//

#include "dbmain.h"

#pragma pack (push, 8)

class AcDbFilteredBlockIterator;

class AcDbFilter: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFilter);
	     AcDbFilter();
    virtual ~AcDbFilter();

    virtual AcRxClass* indexClass() const;
};

#pragma pack (pop)

#endif // AD_DBFILTER_H
