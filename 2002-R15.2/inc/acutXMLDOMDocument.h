
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
#include "acutXMLDOMNamedNodeMap.h"
#include "acutXMLDOMAttribute.h"
#include "acutXMLDOMCDATASection.h"
#include "acutXMLDOMComment.h"
#include "acutXMLDOMDocumentFragment.h"
#include "acutXMLDOMDocumentType.h"
#include "acutXMLDOMElement.h"
#include "acutXMLDOMEntityReference.h"
#include "acutXMLDOMImplementation.h"
#include "acutXMLDOMParseError.h"
#include "acutXMLDOMProcessingInstruction.h"
#include "acutXMLDOMText.h"


class ACUTXMLDOM_API AcUtXMLDOMDocument : public AcUtXMLDOMNode
{
public:
    AcUtXMLDOMDocument();
    AcUtXMLDOMDocument(const AcUtXMLDOMNode* pNode);
    virtual ~AcUtXMLDOMDocument();

    AcUtXMLDOMResult get_async(bool& isAsync) const;
    AcUtXMLDOMResult put_async(bool isAsync);
    AcUtXMLDOMResult get_preserveWhiteSpace(bool& isPreserving) const;
    AcUtXMLDOMResult put_preserveWhiteSpace(bool isPreserving);
    AcUtXMLDOMResult get_readyState(long& value) const;
    AcUtXMLDOMResult get_resolveExternals(bool& isResolving) const;
    AcUtXMLDOMResult put_resolveExternals(bool isResolving);
    AcUtXMLDOMResult get_url(AcUtString& urlString) const;
    AcUtXMLDOMResult get_validateOnParse(bool& isValidating) const;
    AcUtXMLDOMResult put_validateOnParse(bool isValidating);
    AcUtXMLDOMResult get_doctype(AcUtXMLDOMDocumentType*& documentType) const;
    AcUtXMLDOMResult get_documentElement(AcUtXMLDOMElement*& DOMElement) const;
    AcUtXMLDOMResult put_documentElement(const AcUtXMLDOMElement* DOMElement);
    AcUtXMLDOMResult get_implementation(AcUtXMLDOMImplementation*& impl) const;
    AcUtXMLDOMResult get_parseError(AcUtXMLDOMParseError*& errorObj) const;
    AcUtXMLDOMResult abort(void);
    AcUtXMLDOMResult load(const AcUtString& sourceFile, bool& isSuccessful);
    AcUtXMLDOMResult loadXML(const AcUtString& xmlString, bool& isSuccessful);
    AcUtXMLDOMResult createAttribute(const AcUtString& name,
        AcUtXMLDOMAttribute*& attribute);
    AcUtXMLDOMResult createCDATASection(const AcUtString& data,
        AcUtXMLDOMCDATASection*& cdata);
    AcUtXMLDOMResult createComment(const AcUtString& data,
        AcUtXMLDOMComment*& comment);
    AcUtXMLDOMResult createDocumentFragment(AcUtXMLDOMDocumentFragment*& docFrag);
    AcUtXMLDOMResult createElement(const AcUtString& tagName,
        AcUtXMLDOMElement*& element);
    AcUtXMLDOMResult createEntityReference(const AcUtString& name,
        AcUtXMLDOMEntityReference*& entityRef);
    AcUtXMLDOMResult createNode(AcUtDOMNodeType nodeType, const AcUtString& name,
        const AcUtString& nameSpaceURI, AcUtXMLDOMNode*& node);
    AcUtXMLDOMResult createProcessingInstruction(
        const AcUtString& target,
        const AcUtString& data,
        AcUtXMLDOMProcessingInstruction*& pi);
    AcUtXMLDOMResult createTextNode(const AcUtString& data,
        AcUtXMLDOMText*& text);
    AcUtXMLDOMResult save(const AcUtString& filename);
    AcUtXMLDOMResult save(const AcUtVariant& location);
    AcUtXMLDOMResult getElementsByTagName(const AcUtString& tagname,
        AcUtXMLDOMNodeList*& resultList) const;
    AcUtXMLDOMResult nodeFromID(const AcUtString& idString,
        AcUtXMLDOMNode*& node) const;

protected:
    friend class AcUtImpXMLDOMNode;
    AcUtImpXMLDOMDocument* mpImpDocument;
};
