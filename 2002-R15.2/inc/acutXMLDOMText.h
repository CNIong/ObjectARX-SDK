
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

#pragma once

#include "acutXMLDOMNode.h"
#include "acutXMLDOMCharacterData.h"

/*
The AcUtXMLDOMText object represents the text content of an element 
or attribute. XML refers to this text content as character data and 
distinguishes it from markup, the tags that modify that character data. 

If there is no markup inside an element, that element's text is 
contained in a single IXMLDOMText object that is the child of the 
element. If there is markup inside an element, it is parsed into 
child elements that are siblings of the IXMLDOMText object(s). 
(Note that the content of the markup elements also appears within 
text nodes, which are the children of the specific markup element.) 

When a document is first made available to the DOM, all text is 
normalized: there is only one text node for each block of text. 
Users can create adjacent text nodes that represent the contents 
of a given element without any intervening markup, but should be 
aware that there is no way to represent the separations between 
these nodes, so they will not persist between DOM sessions. 

The normalize method on the AcUtXMLDOMElement object merges adjacent
text nodes into a single node. You should normalize before starting 
any operations that depend on a particular document structure, to 
ensure that subsequent sessions will operate on the same structure. 
*/
class ACUTXMLDOM_API AcUtXMLDOMText : public AcUtXMLDOMCharacterData
{
public:
    AcUtXMLDOMText();
    AcUtXMLDOMText(const AcUtXMLDOMNode* pNode);
    virtual ~AcUtXMLDOMText();

    AcUtXMLDOMResult splitText(long offset,
        AcUtXMLDOMText*& rightHandTextNode);
    // Breaks this text node into two text nodes at the specified 
    // offset, and inserts the new text node into the tree as a 
    // sibling that immediately follows this node.
    // Parameters
    // offset [in] Number of characters at which to split this 
    // text node into two nodes, starting from zero. 
    // rightHandTextNode [out] New text node. 
    // Return Values:
    // S_OK             Value returned if successful. 
    // S_FALSE          Value when returning null.  
    // E_FAIL           Value returned if an error occurs.

protected:
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMText;
    friend class AcUtImpXMLDOMCDATASection;
    AcUtImpXMLDOMText* mpImpText;
};
