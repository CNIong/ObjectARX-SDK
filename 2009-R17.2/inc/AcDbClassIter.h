
//
// (C) Copyright 2004 by Autodesk, Inc. 
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
//  DESCRIPTION:
//

#pragma once
#include "dbmain.h"

#pragma pack (push, 4)

class ADESK_NO_VTABLE AcDbClassIterator
{
  public:
    //
    // Factory methods.  Allocation and deallocation.
    // ----------------
    //
    // Create and return a new, unattached iterator.
    static AcDbClassIterator * ADESK_STDCALL newIterator();

    // Destroy an iterator
    // pIter : input pointer to the iterator
    static void ADESK_STDCALL deleteIterator(AcDbClassIterator *pIter);


    //
    // Iteration methods
    // -----------------
    //
    // Flag values passed to start() method.  Specify type of iteration.
    enum { kAllClasses = 0x01,        // returns all classes in the db
           kCustomClasses   = 0x02,   // returns only custom classes
           kProxyClasses    = 0x04 }; // returns only proxy classes

    // Attach this iterator to a database and begin iteration.
    // pDb : input pointer to a drawing database
    // nFlags : input flags specifying how to iterate
    virtual Acad::ErrorStatus start(AcDbDatabase *pDb, int nFlags) = 0;

    // Advance the iterator to the next class
    // Returns true if there is a next class, false if iteration is done
    virtual bool next() = 0;

    // Returns false if there is a next class, true if iteration is done
    virtual bool done() const = 0;

    // Resets this iterator.  Detaches it from its current database.
    virtual void detach() = 0;


    //
    // Querying methods
    // ----------------
    //
    // Return name of current class.
    virtual const ACHAR *name() const = 0;

    // Return name of current class's application (enabler).
    virtual const ACHAR *appName() const = 0;

    // Return dxf name of current class
    virtual const ACHAR *dxfName() const = 0;

    // Return number of instances of current class.  This may be
    // approximate, if not all objects have been loaded into memory
    // or if objects have been erased.
    virtual Adesk::UInt32 numInstances() const = 0;

    // Return true if the current class is a proxy (i.e. its
    // enabler is not loaded), false if enabler is loaded.
    virtual bool isProxy() const = 0;

    // Return true if the current class is an entity (i.e. is directly
    // or indirectly derived from AcDbEntity), false if not.
    virtual bool isEntity() const = 0;


  protected:
    // The ctor and dtor are only here to prevent attempts at
    // direct instantiation or deletion of this class.  Please use
    // the factory methods to create and destroy iterator objects.
    AcDbClassIterator();
    ~AcDbClassIterator();
};

#pragma pack (pop)

