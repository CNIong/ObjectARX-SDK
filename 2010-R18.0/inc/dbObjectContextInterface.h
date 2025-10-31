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
// dbObjectContextInterface.h
//
// DESCRIPTION: Protocol extension base class
//                AcDbObjectContextInterface
//

#pragma once
#pragma pack (push, 8)

#include "acdb.h"
#include "dbmain.h"

class AcDbObjectContext;

////////////////////////////////////////////////////////////////////////
// class AcDbObjectContextInterface
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Abstract protocol extension interface class which allows supporting
/// context-specific behavior on an object.
/// </summary>
///
/// <remarks>
/// Custom objects provide an implementation of this interface and associate
/// with their AcRxClass to provide context-dependent object behavior. One
/// example of such behavior is annotation scalin where the context is the
/// current viewport scale, and where the custom object behavior for text is
/// the text height, orientation, and position. Applications can define other
/// context types (AcDbObjectContext custom classes), store them in custom
/// collections (AcDbObjectContextCollection). By implementing this interface,
/// custom objects expose information about which context types they support
/// and when context instances they participate in. 
/// </remarks>
///
class AcDbObjectContextInterface : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbObjectContextInterface);

    /// <summary>
    /// Determines if a particular context type is supported by the object. 
    /// </summary>
    ///
    /// <param name="pObject">
    /// The object supporting the collection.
    /// </param>
    ///
    /// <param name="collectionName">
    /// The name of the collection (context type) to test for support.
    /// </param>
    ///
    /// <returns>
    /// Returns "true" if the object supports context types with the specified
    /// name.
    /// </returns>
    /// 
    /// <remarks>
    /// Whether an object supports a collection type is different from whether
    /// the object currently participates in any contexts of that type. See
    /// also the hasContext() method. 
    /// </remarks>
    virtual bool supportsCollection ( 
                            const AcDbObject* pObject,
                            const AcString&   collectionName ) const = 0;

    /// <summary>
    /// Determines if an object is currently active in a partuclar context. 
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to an object supporting object contexts. 
    /// </param>
    ///
    /// <param name="context">
    /// The context to test.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the object supports the context type and is currently
    /// active in the specified context instance.
    /// </returns>
    virtual bool hasContext ( const AcDbObject*        pObject,
                              const AcDbObjectContext& context ) const = 0;

    /// <summary>
    /// Adds a context to the list of active contexts for an object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the object to make active in the context.
    /// </param>
    ///
    /// <param name="context">
    /// The context to make active for the object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the
    /// object does not support the context type. Returns
    /// Acad::eDuplicateRecordName if a context with the specified name already
    /// exists. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus addContext ( 
                                AcDbObject*              pObject,
                                const AcDbObjectContext& context ) const = 0;

    /// <summary>
    /// Removes a contextfrom the list of active contexts for an object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the object to remove the context from.
    /// </param>
    ///
    /// <param name="context">
    /// The context to remove from the object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the
    /// object does not support the context type. 
    /// </returns>
    ///    
    virtual Acad::ErrorStatus removeContext ( 
                                AcDbObject*              pObject,
                                const AcDbObjectContext& context ) const = 0;
};

#pragma pack (pop)

