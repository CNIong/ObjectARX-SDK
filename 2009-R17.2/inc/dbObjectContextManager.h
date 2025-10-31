#ifndef ACDB_OBJECTCONTEXTMANAGER_H
#define ACDB_OBJECTCONTEXTMANAGER_H
//
// (C) Copyright 2006-2007 by Autodesk, Inc.
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
// DESCRIPTION: Object context manager class.  This class manages collections
//              of object contexts for a particular database.

#pragma once

#include "acdb.h"
#include "dbmain.h"
#include "AcString.h"


class AcDbObjectContextCollection;
class AcDbObjectContext;
class AcDbImpObjectContextManager;


#pragma pack (push, 8)


////////////////////////////////////////////////////////////////////////
// class AcDbObjectContextManager
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Exposes the collection of context types supported by the drawing. 
/// </summary>
///
/// <remarks>
/// Each AcDbDatabase exposes an AcDbObjectContextManager which can be used
/// to register, unregister, and enumerate custom context collections. 
/// </remarks>
///
class AcDbObjectContextManager: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectContextManager);

    /// <summary>
    /// Default constructor. 
    /// </summary>
    ///
    /// <remarks>
    /// For internal use only.
    /// </remarks>
    ///
    AcDbObjectContextManager();  

    /// <summary>
    /// Destructor.
    /// </summary>
    ///
    virtual ~AcDbObjectContextManager();

    /// <summary>
    /// Registers a context collection with the context manager. 
    /// </summary>
    ///
    /// <param name="collectionName">
    /// The name of the collection to register with the manager.
    /// </param>
    ///
    /// <param name="pCollection">
    /// A pointer to the collection to register with the manager.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Applications are responsible for allocating and freeing the object
    /// context collection object. Before an application unloads it should
    /// unregister all instances of the collection and free any resources. 
    /// </remarks>
    /// 
    Acad::ErrorStatus registerContextCollection(
                                  const AcString&              collectionName,
                                  AcDbObjectContextCollection* pCollection);

    /// <summary>
    /// Unregisters a context collection with the context manager. 
    /// </summary>
    ///
    /// <param name="collectionName">
    /// The name of the collection to unregister with the manager.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Applications are responsible for
    /// freeing any memory allocated for a collection, simply unregistering the
    /// collection with the manager does not free any resources. 
    /// </returns>
    Acad::ErrorStatus unregisterContextCollection(
                                  const AcString& collectionName);

    /// <summary>
    /// Returns a registered context collection by name
    /// </summary>
    /// 
    /// <param name="collectionName">
    /// The name of the desired collection.
    /// </param>
    ///
    /// <returns>
    /// Returns a const pointer to the collection registered if one exists with
    /// the specified name, or NULL if no such collection is registered.
    /// </returns>
    ///
    /// <remarks>
    /// Applications should not delete the returned pointer. 
    /// </remarks>
    ///
    AcDbObjectContextCollection* const contextCollection(
                                  const AcString& collectionName) const;

private:
    AcDbImpObjectContextManager* mpImp;

    friend class AcDbContextDataSubManager;
};

#pragma pack (pop)

#endif
