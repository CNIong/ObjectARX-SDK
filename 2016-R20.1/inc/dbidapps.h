//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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

#ifndef _AD_DBID_APPS_H
#define _AD_DBID_APPS_H 1

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
