
// (C) Copyright 2008-2011 by Autodesk, Inc.
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

/// <description>
/// Internal use only. Base class for all overrules.
/// </description>                                                      

class AcRxOverruleIteratorBase;

class ADESK_NO_VTABLE AcRxOverruleBase : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxOverruleBase);
private:
    mutable AcRxOverruleIteratorBase* m_pIter;
    friend class AcRxOverruleInternals;
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcRxOverrule is an abstract base class for implementing
/// overrules. Overrule providers register and unregister their
/// overrules through addOverrule and removeOverrule. Overrules
/// can be globally activated or deactivated by setIsOverruling.
/// It can also be queried by isOverruleing.
/// 
/// Overrules are internally managed by pairs of "targetClass"
/// and "overrule". The "targetClass" is the class that
/// "overrule" is intended to own. Each class can have multiple
/// overrules registered and their order is implied by the order
/// they are registered.
/// 
/// Each derived overrule class should provide some or all
/// default implementations that delegate to the default behavior
/// for the targeted class. 
/// </description>                                                      
class ACDB_PORT AcRxOverrule : public AcRxOverruleBase
{
public:
    // --- AcRxObject protocol
    ACRX_DECLARE_MEMBERS(AcRxOverrule);
    virtual ~AcRxOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Used to make per-instance determination whether the overrule is applicable.
    /// </description>
    /// <returns>
    /// Returns true if overruling of the overrule should be applied when queried, false otherwise.
    /// </returns>
    /// <param name="pOverruledSubject">Pointer to an AcRxObject to check.</param>
    /// <remarks>
    /// If pOverruledSubject is database resident then it is open for read. 
    /// </remarks>                                                   
    virtual bool isApplicable(const AcRxObject* pOverruledSubject) const = 0;

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Registers an overrule object to an AcRxClass.
    /// </description>
    /// <param name="pClass">Pointer to an AcRxClass to which "pOverrule" is intended to apply.</param>
    /// <param name="pOverrule">Pointer to an AcRxOverrule derived object to overrule.</param>
    /// <param name="bAddAtLast">Indicates whether the {pClass, pOverrule} pair should be added at
    ///                          the end of the overrule's collection.</param>
    /// <remarks>
    /// You should ensure "pOverrule" is appropriate for "pClass". If "pOverrule" can't
    /// overrule behaviors in "pClass", then "pOverrule" will have no effect. If more than one
    /// overrule specifies bAddAtLast to be true, then their orders will be determined
    /// by last in first out.
    /// </remarks>
    /// <returns>
    /// Returns true if the overrule is successfully added.
    /// </returns>                                                       
    static Acad::ErrorStatus addOverrule(AcRxClass* pClass, AcRxOverrule* pOverrule, bool bAddAtLast = false);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Unregister an overrule object from an AcRxClass.
    /// </description>
    /// <param name="pClass">AcRxClass to which "pOverrule" was applied.</param>
    /// <param name="pOverrule">AcRxOverrule derived object to remove.</param>
    /// <remarks>
    /// The parameters should match the parameters when addOverrule was called.
    /// </remarks>
    /// <returns>
    /// Returns Acad::Ok if the overrule was registered and is now removed from the overrule collection by this call.
    /// </returns>                                                 
    static Acad::ErrorStatus removeOverrule(AcRxClass* pClass, AcRxOverrule* pOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Globally (application-wise) enable or disable overruling mechanism.
    /// </description>
    /// <param name="bIsOverruling">True to enable overruling, false to disable.</param>
    /// <remarks>
    /// Overrule can be turned ON or OFF across the entire application. Does not
    /// support per-document enabling or disabling.
    /// </remarks>                                                  
    static void setIsOverruling(bool bIsOverruling);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Queries if the global overruling flag is true or false.
    /// </description>
    /// <returns>
    /// Returns true if overruling is currently turned on, false otherwise. 
    /// </returns>                                                  
    static bool isOverruling(void);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Test whether a given object is targeted by a registed overule. 
    /// </description>
    /// <param name="pSubject">AcRxObject to which its type will be examined against all registered overrules of type pOverruleClass.</param>
    /// <param name="pOverruleClass">AcRxClass which specifies an overrule class to test.</param>
    /// <returns>
    /// Returns true if the object is to be handled by the specified overrule. false otherwise.
    /// <remarks>
    /// Client can test whether there is a given overrule, represented by pOverruleClass,
    /// that is interested in overruling the object, pSubject. It returns true if:
    ///   - The global AcRxOverrule::isOverruling() is turned on;
    ///   - An overrule (of, or derived from, pOverruleClass) is registered; 
    ///   - The above overrule is targeting objects of pSubject's type. 
    /// </remarks>                                                  
    static bool hasOverrule(const AcRxObject* pSubject, AcRxClass* pOverruleClass);
};

#pragma pack (pop)
#endif  // _RXOVERRULE_H
