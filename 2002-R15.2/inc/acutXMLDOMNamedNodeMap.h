
/*
**  (C) Copyright 1999-2000 by Autodesk, Inc.  All rights reserved.
**
**  The information contained herein is confidential, proprietary to 
**  Autodesk, Inc., and considered a trade secret as defined in 
**  section 499C of the penal code of the State of California.  
**  Use of this information by anyone other than authorized employees 
**  of Autodesk, Inc. is granted only under a written non-disclosure 
**  agreement, expressly prescribing the scope and manner of such use.
*/

#ifndef _ACUTXMLDOMNAMEDNODEMAP_H
#define _ACUTXMLDOMNAMEDNODEMAP_H

#include "acutXMLDOM.h"
#include "acutXMLDOMNode.h"

class ACUTXMLDOM_API AcUtXMLDOMNamedNodeMap
{
public:
    AcUtXMLDOMNamedNodeMap();
    virtual ~AcUtXMLDOMNamedNodeMap();

    AcUtXMLDOMResult getNamedItem(const AcUtString& name,
        AcUtXMLDOMNode*& namedItem) const;
    // Retrieves the attribute with the specified name.
    // Parameters
    // name [in] Name of the attribute. 
    // namedItem [out] IXMLDOMNode object for the specified attribute. 
    // Returns NULL if the attribute node is not in this collection. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  
    // E_INVALIDARG   Value returned if namedItem is null.
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult getQualifiedItem(const AcUtString& baseName,
        const AcUtString& nameSpaceURI,
        AcUtXMLDOMNode*& qualifiedItem) const;
    // Returns the attribute with the specified namespace and 
    // attribute name.
    // Parameters
    // baseName [in] Base name of the attribute, without namespace qualification.
    // nameSpaceURI [in] Namespace prefix that qualifies the attribute name. 
    // qualifiedItem [out] Attribute node specified by the baseName and 
    // nameSpaceURI parameters. Returns NULL if the attribute is not in the 
    // collection, or if the item is not an attribute. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  
    // E_INVALIDARG   Value returned if qualifiedItem is null.
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult get_item(long index, AcUtXMLDOMNode*& listItem) const;
    // Allows random access to individual nodes within the collection.
    // Parameters
    // index  [in] Index of the item within the collection. 
    // The first item is zero. 
    // listItem [out] IXMLDOMNode object. Returns NULL if the 
    // index is out of range. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // E_INVALIDARG   Value returned if listItem is null or index is out of range
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult get_length(long& listLength) const;
    // Indicates the number of items in the collection.
    // Parameters
    // listLength  [out] Number of items in the collection. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult nextNode(AcUtXMLDOMNode*& nextItem);
    // Returns the next node in the collection.
    // Parameters
    // nextItem [out] Next node in the collection, or NULL if there is
    // no next node. 
    // Return Values:
    // S_OK             Value returned if successful. 
    // S_FALSE          Value when returning null.  
    // E_INVALIDARG     Value returned if nextItem is null.
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult removeNamedItem(const AcUtString& name,
        AcUtXMLDOMNode*& namedItem);
    // Removes an attribute from the collection.
    // Parameters
    // name [in] Name of the attribute to remove from the collection. 
    // namedItem [out] Node removed from the collection.
    // Returns NULL if the named node is not an attribute. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.   
    // E_FAIL         Value returned if an error occurs. 

    AcUtXMLDOMResult removeQualifiedItem(const AcUtString& baseName,
        const AcUtString& nameSpaceURI, AcUtXMLDOMNode*& qualifiedItem);
    // Removes the attribute with the specified namespace and attribute name.
    // Parameters
    // baseName [in] Base name of the attribute, without namespace qualification. 
    // nameSpaceURI [in] Namespace prefix that qualifies the attribute name. 
    // qualifiedItem [out] Attribute node removed, or NULL if no node was removed. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  
    // E_FAIL         Value returned if an error occurs. 


    AcUtXMLDOMResult reset(void);
    // Resets the iterator.
    // Return Value:
    // Returns S_OK if successful, or an error code otherwise.

    AcUtXMLDOMResult setNamedItem(const AcUtXMLDOMNode& newItem,
        AcUtXMLDOMNode*& namefItem);
    // Adds the supplied node to the collection.
    // Parameters
    // newItem [in] Attribute to be added to the collection. 
    // namedItem [out] Attribute successfully added to the collection. 
    // If null, no object is created. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // E_INVALIDARG   Value returned if newItem is null. 
    // E_FAIL         Value returned if an error occurs. 

protected:
    void* mpImpl;
    friend class AcUtImpXMLDOMNode;
    friend class AcUtImpXMLDOMDocumentType;
};

#endif // _ACUTXMLDOMNAMEDNODEMAP_H