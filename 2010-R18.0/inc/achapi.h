//
// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
// AcHapi.h
//
#ifndef ACHAPI_H
#define ACHAPI_H 1

#include "AdAchar.h"

#pragma pack (push, 8)


///////////////////////////////////////////////////////////////////////////////
// Hyperlink Object
///////////////////////////////////////////////////////////////////////////////
class AcDbHyperlink 
{
public:
    AcDbHyperlink() {};
    virtual ~AcDbHyperlink(){};
    
    // Flags that can be set on the hyperlink object
    enum HLinkFlags {
        kUndefined = 0,
        kConvertDwgToDwf = 0x1
    };

    // Get/Set the name or URL.
    virtual const ACHAR * name() const = 0;   
    virtual void setName(const ACHAR * cName) = 0; 

    // Get/Set the description or friendly name.
    virtual const ACHAR * description() const = 0;  
    virtual void setDescription(const ACHAR * cDescription) = 0;
    
    // Get/Set the sublocation/named view.
    virtual const ACHAR * subLocation() const = 0;  
    virtual void setSubLocation(const ACHAR * cSubLocation) = 0;

    // Get the hyperlink display string. Rule:
    // if description is not empty, return "description", otherwise,
    // name with subLocation as "name - subLocation"
    virtual const ACHAR * getDisplayString() const = 0;  

    // Returns true if the hyperlink object is associated with the
    // outermost container or object.
    virtual bool isOutermostContainer() const = 0;

    // Returns the nesting level of the associated entity.   See
    // note on GetHyperlink collection below for details on
    // nested level.
    virtual const int getNestedLevel() const = 0;

    // Get/Set flags that can be set on the hyperlink object
    virtual const long flags() const;
    virtual void setFlags(const long lFlags);
};

inline const long AcDbHyperlink::flags() const
{
    return  AcDbHyperlink::kUndefined;
}

inline void AcDbHyperlink::setFlags(const long lFlags)
{
}

///////////////////////////////////////////////////////////////////////////////
// Hyperlink Collection
///////////////////////////////////////////////////////////////////////////////
class AcDbHyperlinkCollection   
{
public:
    AcDbHyperlinkCollection() {};
    virtual ~AcDbHyperlinkCollection(){}; 
   
    // Methods for adding a hyperlink object to a collection.
    virtual void addHead(const ACHAR * sName, const ACHAR * sDescription,
                         const ACHAR * sSubLocation = NULL) = 0;
    virtual void addTail(const ACHAR * sName, const ACHAR * sDescription,
                         const ACHAR * sSubLocation = NULL) = 0;
    virtual void addAt(const int nIndex, const ACHAR * sName,
                       const ACHAR * sDescription,
                       const ACHAR * sSubLocation = NULL) = 0;
    
    // Methods for removing a hyperlink object from a collection.
    virtual void removeHead() = 0;
    virtual void removeTail() = 0;
    virtual void removeAt(const int nIndex) = 0;
    
    // Returns the number of hyperlink objects in the collection.
    virtual int count() const = 0;
    
    // Returns pointer to Hyperlink object at index in collection.
    virtual AcDbHyperlink * item(const int nIndex) const = 0;
};

///////////////////////////////////////////////////////////////////////////////
//  Hyperlink Protocol Extension
///////////////////////////////////////////////////////////////////////////////
class AcDbEntityHyperlinkPE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbEntityHyperlinkPE);
    
    // pcHCL points to the hyperlink collection associated with pObj.  
    // Caller must delete pcHCL when finished using it.  The collection with delete 
    // all its contained hyperlink objects.
    // Set bOneOnly to true to get the first hyperlink only.    
    // Set bIgnoreBlockDefinition to false to when interested in hyperlinks associated 
    // with a block insert's corresponding block definition.
    //
    // The order of hyperlinks for a single entity is:  h1, h2, h3, etc 
    // where h1,h2,h3 are the first, second, third hyperlink respectively.  
    //
    // If pObj is an Insert and bIgnoreBlockDefinition = false, then the
    // hyperlinks associated with the Insert are followed by the hyperlinks associated 
    // with the block definition.   Hyperlinks associated with the Insert will have a 
    // NestedLevel of 0 and the hyperlinks associated withthe definition will have a
    // NestedLevel of 1.
    virtual Acad::ErrorStatus getHyperlinkCollection(AcDbObject * pObj, 
                                                     AcDbHyperlinkCollection *& pcHCL,
                                                     bool bOneOnly = false, 
                                                     bool bIgnoreBlockDefinition = true) = 0;

    
    // pcHCL points to the hyperlink collection associated with the obejcts in the array.
    // Caller must delete pcHCL when finished using it.  The collection with delete 
    // all its contained hyperlink objects.
    // Set bOneOnly to true to get the first hyperlink only.    
    // Set bIgnoreBlockDefinition to false to when interested in hyperlinks associated 
    // with a block insert's corresponding block definition.
    // 
    // The primary use of this function is to determine the hyperlinks associated with an
    // object and it containers.  If for example, idContainers is an array containing an  
    // object id followed by its container insert ids (as returned by ProcessInputPoint) 
    // then  pcHCL will contain the hyperlinks associated with the array in this order:
    //
    //   outmost_container_insert_h1       -- 0 (nested level)
    //   outmost_container_insert_h2       -- 0
    //   outmost_container_definition_h1   -- 1
    //   outmost_container_definition_h2   -- 1
    //   inner_container_insert_h1         -- 2
    //   inner_container_insert_h2         -- 2
    //   inner_container_definition_h1     -- 3
    //   inner_container_definition_h2     -- 3
    //   entity_h1                         -- 4
    //   entity_h2                         -- 4 
    //
    virtual Acad::ErrorStatus getHyperlinkCollection(const AcArray<AcDbObjectId> *& idContainers,
                                              AcDbHyperlinkCollection *& pcHCL,                                               
                                              bool bOneOnly = false,                                               
                                              bool bIgnoreBlockDefinition = true) = 0;

   
    // Sets the hyperlink collection associated with pObj to pcHCL.  Any existing hyperlinks 
    // associated with pObj are removed.
    virtual Acad::ErrorStatus setHyperlinkCollection(AcDbObject * pObj, 
                                                     AcDbHyperlinkCollection * pcHCL) = 0;
    
    // nCount is set to the number of hyperlinks associated with pObj.    
    // Set bIgnoreBlockDefinition to false to when interested in the hyperlinks
    // associated with a block insert's corresponding block definition.
    virtual Acad::ErrorStatus getHyperlinkCount(AcDbObject * pObj, 
                                                UINT & nCount, 
                                                bool bIgnoreBlockDefinition = true) = 0;

    // nCount is set to the number of hyperlinks associated with the objects in idContainers.
    // Set bIgnoreBlockDefinition to false to when interested in the hyperlinks
    // associated with a block insert's corresponding block definition.
    virtual Acad::ErrorStatus getHyperlinkCount(const AcArray<AcDbObjectId> *& idContainers, 
                                                UINT & nCount, 
                                                bool bIgnoreBlockDefinition = true) = 0;
    
    
    // bHasHyperlink is set to true if pObj has a hyperlink.    
    // Set bIgnoreBlockDefinition to false to when interested in hyperlinks
    // associated with a block insert's corresponding block definition.
    virtual Acad::ErrorStatus hasHyperlink(AcDbObject * pObj, 
                                            bool & bHasHyperlink, 
                                            bool bIgnoreBlockDefinition = true) = 0;

    
    // bHasHyperlink is set to true if any object in idContainers has a hyperlink.
    // Set bIgnoreBlockDefinition to false to when interested in the hyperlinks
    // associated with a block insert's corresponding block definition.
    virtual Acad::ErrorStatus hasHyperlink(const AcArray<AcDbObjectId> *& idContainers, 
                                           bool & bHasHyperlink,
                                           bool bIgnoreBlockDefinition = true) = 0;

};


// registered service name
#define HAPI_SERVICE  ACRX_T("AcadHyperlinks")

#pragma pack (pop)
#endif /* ACHAPI_H */
