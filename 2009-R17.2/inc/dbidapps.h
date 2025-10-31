#ifndef _AD_DBID_APPS_H
#define _AD_DBID_APPS_H 1
//
// (C) Copyright 1995-2006 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// This file contains the inlined versions of the comparsion operators
// for the AcDbObjectId class, that are for use by adjacent applications.
// These operators call out to explicit functions, to allow behavioral
// modification of these operators between c4 and c5.  Presumably, the
// AutoCAD/adjacent app division of these operators will be collapsed back
// into dbid.h at a future date.
// 
// See dbid.cc for the body of the function calls.
// See dbid.h for further description of the AcDbObjectId types.

#include "adesk.h"
#include "dbid.h"
#include "dbid_ops.h"
#pragma pack (push, 8)

//////////////////// AcDbObjectId inlines ////////////////////

// LHS AcDbObjectId -- RHS AcDbObjectId

inline bool
AcDbObjectId::operator < (const AcDbObjectId& id) const
{ return c5ObjIdIsLessThan(*this, id); }

inline bool
AcDbObjectId::operator > (const AcDbObjectId& id) const
{ return c5ObjIdIsGreaterThan(*this, id); }

inline bool
AcDbObjectId::operator <= (const AcDbObjectId& id) const
{ return c5ObjIdLessThanOrEqual(*this, id); }

inline bool
AcDbObjectId::operator >= (const AcDbObjectId& id) const
{ return c5ObjIdGreaterThanOrEqual(*this, id); }

inline bool
AcDbObjectId::operator == (const AcDbObjectId& id) const
{ return c5ObjIdIsEqualTo(*this, id); }

inline bool
AcDbObjectId::operator != (const AcDbObjectId& id) const
{ return !c5ObjIdIsEqualTo(*this, id); }



// LHS AcDbObjectId -- RHS AcDbStub*

inline bool
AcDbObjectId::operator < (const AcDbStub* pStub) const
{ return c5ObjIdIsLessThan(*this, pStub); }

inline bool
AcDbObjectId::operator > (const AcDbStub* pStub) const
{ return c5ObjIdIsGreaterThan(*this, pStub); }

inline bool
AcDbObjectId::operator <= (const AcDbStub* pStub) const
{ return c5ObjIdLessThanOrEqual(*this, pStub); }

inline bool
AcDbObjectId::operator >= (const AcDbStub* pStub) const
{ return c5ObjIdGreaterThanOrEqual(*this, pStub); }

inline bool
AcDbObjectId::operator == (const AcDbStub* pStub) const
{ return c5ObjIdIsEqualTo(*this, pStub); }

inline bool
AcDbObjectId::operator != (const AcDbStub* pStub) const
{ return !c5ObjIdIsEqualTo(*this, pStub); }


//////////////////// AcDbR13ObjectId inlines ////////////////////
// The behavior of AcDbObjectId's in 3rd party applications with
// respect to the boolean operators defined by this class has 
// changed from R13. If applications need to return to the old-style
// behavior for some reason (they shouldn't, but you never know ...)
// they can cast objectIds to this class.

class AcDbR13ObjectId : public AcDbObjectId
{

public:

    bool operator < (const AcDbR13ObjectId& id) const;
    bool operator > (const AcDbR13ObjectId& id) const;
    bool operator <= (const AcDbR13ObjectId& id) const;
    bool operator >= (const AcDbR13ObjectId& id) const;
    bool operator == (const AcDbR13ObjectId& id) const;
    bool operator != (const AcDbR13ObjectId& id) const;

    bool operator < (const AcDbStub* pStub) const;
    bool operator > (const AcDbStub* pStub) const;
    bool operator <= (const AcDbStub* pStub) const;
    bool operator >= (const AcDbStub* pStub) const;
    bool operator == (const AcDbStub* pStub) const;
    bool operator != (const AcDbStub* pStub) const;

};

// LHS AcDbObjectId -- RHS AcDbObjectId

inline bool
AcDbR13ObjectId::operator < (const AcDbR13ObjectId& id) const
{ return c4ObjIdIsLessThan(reinterpret_cast<Adesk::ULongPtr>(mId),
                           reinterpret_cast<Adesk::ULongPtr>(id.mId));
}

inline bool
AcDbR13ObjectId::operator > (const AcDbR13ObjectId& id) const
{ return c4ObjIdIsGreaterThan(reinterpret_cast<Adesk::ULongPtr>(mId),
                              reinterpret_cast<Adesk::ULongPtr>(id.mId));
}

inline bool
AcDbR13ObjectId::operator <= (const AcDbR13ObjectId& id) const
{ return c4ObjIdLessThanOrEqual(reinterpret_cast<Adesk::ULongPtr>(mId),
                                reinterpret_cast<Adesk::ULongPtr>(id.mId));
}

inline bool
AcDbR13ObjectId::operator >= (const AcDbR13ObjectId& id) const
{ return c4ObjIdGreaterThanOrEqual(reinterpret_cast<Adesk::ULongPtr>(mId),
                                   reinterpret_cast<Adesk::ULongPtr>(id.mId));
}

inline bool
AcDbR13ObjectId::operator == (const AcDbR13ObjectId& id) const
{ return c4ObjIdIsEqualTo(reinterpret_cast<Adesk::ULongPtr>(mId),
                          reinterpret_cast<Adesk::ULongPtr>(id.mId));
}

inline bool
AcDbR13ObjectId::operator != (const AcDbR13ObjectId& id) const
{ return c4ObjIdNotEqualTo(reinterpret_cast<Adesk::ULongPtr>(mId),
                           reinterpret_cast<Adesk::ULongPtr>(id.mId));
}



// LHS AcDbObjectId -- RHS AcDbStub*

inline bool
AcDbR13ObjectId::operator < (const AcDbStub* pStub) const
{ return c4ObjIdIsLessThan(reinterpret_cast<Adesk::ULongPtr>(mId),
                           reinterpret_cast<Adesk::ULongPtr>(pStub)); }

inline bool
AcDbR13ObjectId::operator > (const AcDbStub* pStub) const
{ return c4ObjIdIsGreaterThan(reinterpret_cast<Adesk::ULongPtr>(mId),
                              reinterpret_cast<Adesk::ULongPtr>(pStub)); }

inline bool
AcDbR13ObjectId::operator <= (const AcDbStub* pStub) const
{ return c4ObjIdLessThanOrEqual(reinterpret_cast<Adesk::ULongPtr>(mId),
                                reinterpret_cast<Adesk::ULongPtr>(pStub)); }

inline bool
AcDbR13ObjectId::operator >= (const AcDbStub* pStub) const
{ return c4ObjIdGreaterThanOrEqual(reinterpret_cast<Adesk::ULongPtr>(mId),
                                   reinterpret_cast<Adesk::ULongPtr>(pStub)); }

inline bool
AcDbR13ObjectId::operator == (const AcDbStub* pStub) const
{ return c4ObjIdIsEqualTo(reinterpret_cast<Adesk::ULongPtr>(mId),
                          reinterpret_cast<Adesk::ULongPtr>(pStub)); }

inline bool
AcDbR13ObjectId::operator != (const AcDbStub* pStub) const
{ return c4ObjIdNotEqualTo(reinterpret_cast<Adesk::ULongPtr>(mId),
                           reinterpret_cast<Adesk::ULongPtr>(pStub)); }

#pragma pack (pop)
#endif // _AD_DBID_APPS_H
