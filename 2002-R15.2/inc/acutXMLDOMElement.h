
// (C) Copyright 1993-2000 by Autodesk, Inc.
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

#pragma once

#include "acutXMLDOM.h"
#include "acutXMLDOMNode.h"
#include "acutXMLDOMNodeList.h"
#include "acutXMLDOMAttribute.h"

class ACUTXMLDOM_API AcUtXMLDOMElement : public AcUtXMLDOMNode
{
public:
    AcUtXMLDOMElement();
    AcUtXMLDOMElement(const AcUtXMLDOMNode* pNode);
    virtual ~AcUtXMLDOMElement();

    AcUtXMLDOMResult getAttribute(const AcUtString& name, AcUtVariant& value) const;
    AcUtXMLDOMResult get_tagName(AcUtString& tagName) const;
    AcUtXMLDOMResult getAttributeNode(const AcUtString& name, 
        AcUtXMLDOMAttribute*& attributeNode) const;
    AcUtXMLDOMResult getElementsByTagName(const AcUtString& tagName,
        AcUtXMLDOMNodeList*& resultList) const;
    AcUtXMLDOMResult normalize(void);
    AcUtXMLDOMResult removeAttribute(const AcUtString& name);
    AcUtXMLDOMResult removeAttributeNode(
        const AcUtXMLDOMAttribute* DOMAttribute,
        AcUtXMLDOMAttribute*& attributeNode);
    AcUtXMLDOMResult setAttribute(const AcUtString& name, AcUtVariant& value);
    AcUtXMLDOMResult setAttributeNode(
        const AcUtXMLDOMAttribute* DOMAttribute,
        AcUtXMLDOMAttribute*& attributeNode);

protected:
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMNode;
    friend class AcUtImpXMLDOMElement;
    AcUtImpXMLDOMElement* mpImpElement;
};
