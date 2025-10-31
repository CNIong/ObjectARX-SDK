
// (C) Copyright 2008-2009 by Autodesk, Inc.
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

#ifndef _RXOVERRULE_H
#define _RXOVERRULE_H

#include "rxobject.h"
#include "acarray.h"

#pragma pack (push, 8)

class AcRxOverruleIterator;

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcRxOverrule is an abstract base class for implementing
/// overrules. Overrule providers register and unregister their
/// overrules through addOverrule and removeOverrule. Overrules
/// can be globally activated or deactivated by setIsOverruling.
/// It can also be queried by isOverruleing.
/// 
/// Overrules are internally managed by pairs of &quot;targetClass&quot;
/// and &quot;overrule&quot;. The “targetClass” is the class that
/// “overrule” is intended to on. Each class can have multiple
/// overrules registered and their order is implied by the order
/// they are registered.
/// 
/// Each derived overrule class should provide some or all
/// default implementations that delegate to the default behavior
/// for the targeted class. 
/// </description>                                                      
class AcRxOverrule : public AcRxObject
{
public:
    // --- AcRxObject protocol
    ACRX_DECLARE_MEMBERS(AcRxOverrule);
    ACDB_PORT virtual ~AcRxOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Used to make per-instance determination whether the overrule
    /// is applicable.
    /// </description>
    /// <returns>
    /// True if overruling is the overrule should be applied when
    /// queried, false otherwise.
    /// </returns>
    /// <param name="pOverruledSubject">Pointer to an AcRxObject to
    ///                                 check.</param>
    /// <remarks>
    /// If pOverruledSubject is database resident then it is open for
    /// read. 
    /// </remarks>                                                   
    virtual bool isApplicable(const AcRxObject* pOverruledSubject) const = 0;

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Registers an overrule object to an AcRxClass.
    /// </description>
    /// <param name="pClass">Pointer to an AcRxClass that
    ///                      “pOverrule” is intended to apply.</param>
    /// <param name="pOverrule">Pointer to an AcRxOverrule derived
    ///                         object to overrule.</param>
    /// <param name="bAddAtLast">Indicats whether the {pClass,
    ///                          pOverrule} pair should be added at
    ///                          the end of overrules collection.</param>
    /// <remarks>
    /// You should ensure &quot;pOverrule&quot; is appropriate for
    /// &quot;pClass&quot;. If &quot;pOverrule can't overrule
    /// behaviors in &quot;pClass&quot;, then &quot;pOverrule&quot;
    /// will have no effect. If more than one overrule specifies
    /// bAddAtLast to be true, then their orders will be determined
    /// by last in first out.
    /// </remarks>
    /// <returns>
    /// True if the overrule is successfully added.
    /// </returns>                                                       
    ACDB_PORT static Acad::ErrorStatus addOverrule(AcRxClass* pClass, AcRxOverrule* pOverrule, bool bAddAtLast = false);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Unregister an overrule object from an AcRxClass.
    /// </description>
    /// <param name="pClass">AcRxClass to which “pOverrule” was
    ///                      applied.</param>
    /// <param name="pOverrule">AcRxOverrule derived object to
    ///                         remove.</param>
    /// <remarks>
    /// The parameters should match the parameters when addOverrule
    /// was called.
    /// </remarks>
    /// <returns>
    /// Acad::Ok if the overrule was registered and is now removed
    /// from the overrule collection by this call.
    /// </returns>                                                 
    ACDB_PORT static Acad::ErrorStatus removeOverrule(AcRxClass* pClass, AcRxOverrule* pOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Globally (application-wise) enable or disable overruling
    /// mechanism.
    /// </description>
    /// <param name="bIsOverruling">True to enable overruling, false
    ///                             to disable.</param>
    /// <remarks>
    /// Overrule can be turned ON or OFF across the entire
    /// application, does not support per-document enabling or
    /// disabling.
    /// </remarks>                                                  
    ACDB_PORT static void setIsOverruling(bool bIsOverruling);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Queries if the global overruling flag is true or false.
    /// </description>
    /// <returns>
    /// True if overruling is currently turned on, false otherwise. 
    /// </returns>                                                  
    ACDB_PORT static bool isOverruling(void);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Test whether a given object is targeted by a registed overule. 
    /// </description>
    /// <param name="pSubject">AcRxObject to which its type will be examined against all registered overrules of type pOverruleClass.</param>
    /// <param name="pOverruleClass">AcRxClass which specifies an overrule class to test.</param>
    /// <returns>
    /// True if the object is to be handled by the specified overrule. false otherwise.
    /// <remarks>
    /// Client can test whether there is a given overrule, represented by pOverruleClass,
    /// is interested in overruling the object, pSubject. It returns true if:
    ///   - The global AcRxOverrule::isOverruling() is turned;
    ///   - An overrule (of, or derived from, pOverruleClass) is registered; 
    ///   - The above overrule is targeting objects of pSubject's type. 
    /// </remarks>                                                  
    ACDB_PORT static bool hasOverrule(const AcRxObject* pSubject, AcRxClass* pOverruleClass);

private:
    AcRxOverruleIterator* m_pIter;
    friend class AcRxOverruleInternals;
};

#pragma pack (pop)
#endif  // _RXOVERRULE_H
