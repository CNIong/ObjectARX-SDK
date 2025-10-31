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
#if !defined(_BLOCKORDERINDEX_H)
#define _BLOCKORDERINDEX_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "dbindex.h"

#pragma warning(push)
#pragma warning(disable: 4275 4251)
#ifdef _EXPORT_SYMBOLS
#define DLLIMPEXP __declspec( dllexport )
#else

// Note: we don't use __declspec(dllimport) here, because of the
// "local vtable" problem with msvc.  If you use __declspec(dllimport),
// then, when a client dll does a new on the class, the object's
// vtable pointer points to a vtable allocated in that client
// dll.  If the client dll then passes the object to another dll,
// and the client dll is then unloaded, the vtable becomes invalid
// and any virtual calls on the object will access invalid memory.
//
// By not using __declspec(dllimport), we guarantee that the
// vtable is allocated in the server dll during the ctor and the
// client dll does not overwrite the vtable pointer after calling
// the ctor.  And, since we expect the server dll to remain in
// memory indefinitely, there is no problem with vtables unexpectedly
// going away.
// 
#define DLLIMPEXP
#endif

class DLLIMPEXP AsdkBlockOrderIndex : public AcDbIndex
{
    static Adesk::Int16 classVersion;
public:
	ACRX_DECLARE_MEMBERS(AsdkBlockOrderIndex);
	virtual ~AsdkBlockOrderIndex();
    virtual AcDbFilteredBlockIterator* newIterator(const AcDbFilter* pFilter) const;
    virtual Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData);
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
protected:
    virtual Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter);

private:
    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 and vc6 do not properly support array new and delete.
    // The "vector deleting dtor" gets optimized into a scalar deleting
    // dtor by the linker if the server dll does not call vector delete.
    // The linker shouldn't do that, because it doesn't know that the
    // object won't be passed to some other dll which *does* do vector
    // delete.
    //
    void *operator new[](unsigned nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](unsigned nSize, const char *file, int line) { return 0;}

};
#pragma warning(pop)
#endif //_BLOCKORDERINDEX_H