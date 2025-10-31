
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2007-2009 by Autodesk, Inc. 
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
// CREATED BY: Jiri Kripac                                 August 2007
//
// DESCRIPTION:
//
// AcDbAssocDependencyPE AcRx protocol extension base class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)


/// <summary> <para>
/// AcRx protocol extension base class that allows objects and entities to 
/// control whether they allow AcDbAssocDependencies to be attached to them.
/// When there is no protocol extension for the object's class, it means that 
/// the object allows both read and write-type dependencies.
/// </para> <para>
/// Other AcDbAssocDependency-related protocol may later be added.
/// </para>
/// </summary>
///
class ACDB_PORT AcDbAssocDependencyPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocDependencyPE);

    /// <summary>
    /// This predicate allows objects and entities to control whether they allow 
    /// AcDbAssocDependencies to be attached to them.
    /// Returns true iff the object allows AcDbAssocDependencies to be attached 
    /// to it. The default implementation returns false.
    /// </summary>
    /// <param name="pObject"> The queried object, must be open for read. </param>
    /// <param name="isWriteDependency"> The dependency will also modify the object. </param>
    /// <returns> True iff the object allows AcDbAssocDependencies on itself. </returns>
    ///
    virtual bool allowsDependencies(const AcDbObject* pObject, bool isWriteDependency) const
    { return false; }

}; // class AcDbAssocDependencyPE

#pragma pack (pop)


