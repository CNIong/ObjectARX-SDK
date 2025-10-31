
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

#ifndef _ACUTXMLDOMNODELIST_H
#define _ACUTXMLDOMNODELIST_H

#include "acutXMLDOM.h"
#include "acutXMLDOMNode.h"

class ACUTXMLDOM_API AcUtXMLDOMNodeList
{
public:
    AcUtXMLDOMNodeList();
    virtual ~AcUtXMLDOMNodeList();

    AcUtXMLDOMResult get_item(long index, AcUtXMLDOMNode*& listItem) const;
    // Description:
    // Allows random access to individual nodes within the collection
    //
    // Parameters:
    // index: [in] Index of the item within the collection. The first item is number zero. 
    // listItem [out] IXMLDOMNode object. Returns NULL if the index is out of range. 
    //
    // Return values:
    // S_OK          Value returned if successful. 
    // E_INVALIDARG  Value returned if listItem is null.

    AcUtXMLDOMResult get_length(long& listLength) const;
    // Description:
    // Indicates the number of items in the collection.
    //
    // Parameters:
    // listLength [out] Number of items in the collection
    //
    // Return values:
    // S_OK          Value returned if successful. 
    // E_INVALIDARG  Value returned if listLength is null.

    AcUtXMLDOMResult nextNode(AcUtXMLDOMNode*& nextItem);
    // Description:
    // Returns the next node in the collection.
    //
    // Parameters:
    // nextItem: [out] Next node in the collection, or NULL if there is no next node. 
    //
    // Return values:
    // S_OK          Value returned if successful. 
    // E_INVALIDARG  Value returned if nextItem is null.

    AcUtXMLDOMResult reset(void);
    // Description:
    // Resets the iterator.
    //
    // Parameters: none
    //
    // Return values:
    // Returns S_OK if successful, or an error code otherwise.


private:
    friend class AcUtImpXMLDOMNode;
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMElement;

    void* mpImpl;
};

#endif // _ACUTXMLDOMNODELIST_H