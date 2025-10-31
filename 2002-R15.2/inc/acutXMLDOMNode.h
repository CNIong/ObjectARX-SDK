
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

#include "acutXMLDOM.h"


typedef enum { 
    kElement = 1, 
    // The node represents an element (its nodeTypeString property is "element").
    // An element node can have the following child node types: kElement, kText, 
    // kComment, kProcessingInstruction, kCDATA, and kEntityReference. 
    // An element node can be the child of the kDocument, kDocumentFragment, 
    // kEntityReference, and kElement nodes. 
    kAttribute, 
    // The node represents an attribute of an element (its nodeTypeString 
    // property is "attribute"). An attribute node can have the following child 
    // node types: kText and kEntityReference. The attribute does not appear as 
    // the child node of any other node type; note that it is not considered a 
    // child node of an element.
    kText, 
    // The node represents the text content of a tag (its nodeTypeString 
    // property is "text"). A text node cannot have any child nodes. 
    // The text node can appear as the child node of the kAttribute, 
    // kDocumentFragment, kElement, and kEntityReference nodes. 
    kCDATA, 
    // The node represents a CDATA section in the XML source (its nodeTypeString 
    // property is "cdatasection"). CDATA sections are used to escape blocks of 
    // text that would otherwise be recognized as markup. A CDATA section node 
    // cannot have any child nodes. The CDATA section node can appear as the 
    // child of the kDocumentFragment, kEntityReference, and kElement nodes. 
    kEntityReference,
    // The node represents a reference to an entity in the XML document 
    // (its nodeTypeString property is "entityreference"). This applies to all
    // entities, including character entity references. An entity reference 
    // node can have the following child node types: kElement, 
    // kProcessingInstruction, kComment, kText, kCDATA, and 
    // kEntityReference. The entity reference node can appear as the 
    // child of the kAttribute, kDocumentFragment, kElement, and 
    // kEntityReference nodes. 
    kEntity,
    // The node represents an expanded entity (its nodeTypeString 
    // property is "entity"). An entity node can have child nodes that 
    // represent the expanded entity (for example, kText and 
    // kEntityReference nodes). The entity node can appear as the child
    // of the kDocumentType node. 
    kProcessingInstruction, 
    // The node represents a processing instruction (PI) from the XML document 
    // (its nodeTypeString property is "processinginstruction"). 
    // A PI node cannot have any child nodes. The PI node can appear as the 
    // child of the kDocument, kDocumentFragment, kElement, and 
    // kEntityReference nodes. 
    kComment, 
    // The node represents a comment in the XML document (its nodeTypeString 
    // property is "comment"). A comment node cannot have any child nodes. 
    // The comment node can appear as the child of the kDocument, 
    // kDocumentFragment, kElement, and kEntityReference nodes. 
    kDocument, 
    // The node represents a document object, which, as the root of the
    // document tree, provides access to the entire XML document (its 
    // nodeTypeString property is "document"). It is created using the 
    // ProgID "Microsoft.XMLDOM", or through a data island using <XML> 
    // or <SCRIPT LANGUAGE=XML>. The document node can have the 
    // following child node types: Element (maximum of one), 
    // kProcessingInstruction, kComment, and kDocumentType. The document 
    // node cannot appear as the child of any node types. 
    kDocumentType, 
    // The node represents the document type declaration, indicated by
    // the <!DOCTYPE > tag (its nodeTypeString property is 
    // "documenttype"). The document type node can have the following 
    // child node types: kNotation and kEntity. The document type node 
    // can appear as the child of the kDocument node. 
    kDocumentFragment,
    // The node represents a document fragment (its nodeTypeString 
    // property is "documentfragment"). The document fragment node 
    // associates a node or subtree with a document without actually 
    // being contained within the document. The document fragment node 
    // can have the following child node types: kElement, 
    // kProcessingInstruction, kComment, kText, kCDATA, and 
    // kEntityReference. The kDocumentFragment node cannot appear as 
    // the child of any node types. 
    kNotation 
    // A node represents a notation in the document type declaration 
    // (its nodeTypeString property is "notation"). The notation node 
    // cannot have any child nodes. The notation node can appear as the 
    // child of the kDocumentType node. 
} AcUtDOMNodeType;


class AcUtXMLDOMDocument;
class AcUtXMLDOMNamedNodeMap;
class AcUtXMLDOMNodeList;
class AcUtXMLDOMElement;
class AcUtXMLDOMAttribute;

class ACUTXMLDOM_API AcUtXMLDOMNode
{
public:
    AcUtXMLDOMNode();           // Nodes must be obtained from other means
    virtual ~AcUtXMLDOMNode();

    virtual AcUtXMLDOMResult appendChild(const AcUtXMLDOMNode& newChild,
        AcUtXMLDOMNode*& outNewChild);
    // Appends newChild as the last child of this node.
    // Parameters
    // newChild [in] Address of the new child node to be appended to the end of 
    // the list of children of this node. 
    // outNewChild [out] New child node successfully appended to the list. 
    // If null, no object is created. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_FAIL          Value returned if an error occurs. 

    virtual AcUtXMLDOMResult cloneNode(bool deep, AcUtXMLDOMNode*& cloneRoot);
    // Creates a new node that is an exact clone of this node.
    // Parameters
    // deep [in] Flag that indicates whether to recursively clone all nodes that 
    // are descendants of this node. If true, create a clone of the complete tree 
    // below this node. If false, clone this node and its attributes only. 
    // cloneRoot [out] Newly created clone node. 
    // Return Values: 
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if cloneRoot is null.


    virtual AcUtXMLDOMResult get_attributes(AcUtXMLDOMNamedNodeMap*& attributeMap) const;
    // Contains the list of attributes for this node.
    //
    // Parameters
    // attributeMap [out] NamedNodeMap returned for nodes that can return attributes 
    // (Element, Entity, and Notation nodes). Returns NULL for all other node types. 
    // Note that for the valid node types, the NamedNodeMap is always returned; 
    // when there are no attributes on the element, the list length is set to zero. 
    // Return Values:
    // S_OK            Success. Returns a non-NULL pointer value.  
    // S_FALSE         Success. Returns a NULL pointer value. 
    // E_INVALIDARG    Value returned if attributeMap is NULL.

    virtual AcUtXMLDOMResult get_baseName(AcUtString& name) const;
    // Returns the base name for the name qualified with the namespace.
    // Parameters
    // nameString [out] Right side of a namespace qualified name. For example, it 
    // returns yyy for the element <xxx:yyy>. It always returns a non-empty string. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  
    // E_INVALIDARG   Value returned if nameString is null.

    virtual AcUtXMLDOMResult get_childNodes(AcUtXMLDOMNodeList*& childList) const;
    // Contains a node list containing the children (for nodes that can have children).
    // Parameters:
    // childList [out] Note that an IXMLDOMNodeList is returned even if there are no 
    // children of the node. In such a case, the length of the list will be set to zero. 
    // For information about valid child node types for each node, see DOMNodeType. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if childList is null.

    virtual AcUtXMLDOMResult get_dataType(AcUtString& dataTypeName) const;
    // Gets the data type for this node -- the dt:dt attribute.
    // Parameters:
    // dataTypeName [out] Name of the node's dt:dt attribute.
    // Return Values:
    // S_OK             Value returned if successful.
    // S_FALSE          Value when no data type found.

    // This value depends on the value of the node object's nodeType property.
    // NODE_ATTRIBUTE       Contains the string representation of the data type 
    //                      specifier included in the schema, or NULL if no data
    //                      type was specified. 
    // NODE_CDATA_SECTION, 
    // NODE_COMMENT, 
    // NODE_DOCUMENT, 
    // NODE_DOCUMENT_FRAGMENT, 
    // NODE_DOCUMENT_TYPE, 
    // NODE_ENTITY, 
    // NODE_NOTATION, 
    // NODE_PROCESSING_INSTRUCTION, 
    // NODE_TEXT            Contains the constant string value "string". 
    //                      These node types do not have data types, so the 
    //                      dataType property cannot be set for these node 
    //                      types. Attempts to set this property are ignored. 
    // NODE_ELEMENT         Contains the string representation of the data 
    //                      type specifier included on the instance of the 
    //                      element or in the schema, or NULL if no data type 
    //                      was specified. 
    // NODE_ENTITY_REFERENCE Contains the string representation of the data 
    //                      type specifier for the referenced entity. This is 
    //                      limited to entities with a single data type on the 
    //                      root level element of the subtree corresponding to 
    //                      the entity. Contains NULL if no data type was 
    //                      specified. It is not possible to set the data type 
    //                      of an entity reference. The data type must be set 
    //                      directly on the referenced element. Attempts to set 
    //                      the value of the dataType property are ignored. 

    virtual AcUtXMLDOMResult get_definition(AcUtXMLDOMNode*& definitionNode) const;
    // Returns the definition of the node in the DTD or schema.
    // Parameters
    // definitionNode [out] Node that contains the definition for the entity referenced. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null.  
    // E_INVALIDARG    Value returned if definitionNode is null.

    virtual AcUtXMLDOMResult get_firstChild(AcUtXMLDOMNode*&  firstChild) const;
    // Contains the first child of this node.
    // Parameters
    // firstChild [out] First child node. If there are no such children, it returns NULL. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null. 
    // E_INVALIDARG    Value returned if firstChild is null. 

    virtual AcUtXMLDOMResult get_lastChild(AcUtXMLDOMNode*& lastChild) const;
    // Returns the last child node.
    // Parameters
    // lastChild [out] Last child node. If there are no children, it returns NULL
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null. 
    // E_INVALIDARG    Value returned if lastChild is null. 

    virtual AcUtXMLDOMResult get_nextSibling(AcUtXMLDOMNode*& nextSibling) const;
    // Contains the next sibling of this node in the parent's child list.
    // Parameters
    // nextSibling [out] Right sibling of this node. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null.  
    // E_INVALIDARG    Value returned if nextSibling is null.

    virtual AcUtXMLDOMResult get_previousSibling(AcUtXMLDOMNode*& previousSibling) const;
    // Contains the left sibling of this node.
    // Parameters 
    // previousSibling [out] Left sibling of this node. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null.  
    // E_INVALIDARG    Value returned if previousSibling is null

    virtual AcUtXMLDOMResult get_namespaceURI(AcUtString& namespaceURI) const;
    // Returns the URI for the namespace.
    // Parameters
    // namespaceURI [out] URI (universal resource identifier) for the namespace. 
    // This refers to the "uuu" portion of the namespace declaration xmlns:nnn="uuu". 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null.  
    // E_INVALIDARG    Value returned if nameSpaceURI is null.

    virtual AcUtXMLDOMResult get_nodeName(AcUtString& name) const;
    // Contains the qualified name of the element, attribute, or entity reference,
    // or a fixed string for other node types.
    // Parameters
    // name [out] Node name, which varies depending on the node type. 
    // Return Value:
    // S_OK          Value returned if successful. 
    // E_INVALIDARG  Value returned if name is null. 

    virtual AcUtXMLDOMResult get_nodeValue(AcUtString& value) const;
    // Contains the text associated with the node.
    // Parameters
    // value [out] Node value; depends on the nodeType property. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when returning null. 
    //.E_INVALIDARG    Value returned if value is null. 
    // E_FAIL          Value returned if an error occurs. 

    virtual AcUtXMLDOMResult get_nodeTypedValue(AcUtVariant& typedValue) const;
    // Contains this node's value expressed in its defined data type.
    // Parameters
    // typedValue [out] Value of this node in its defined data type, if such a 
    // data type is defined. L. 
    // Return Values:
    // S_OK             Value returned if successful. 
    // E_FAIL           Value returned if the node has no content.

    virtual AcUtXMLDOMResult get_nodeType(AcUtDOMNodeType& nodeType) const;
    // Specifies the DOM node type, which determines valid values and whether 
    // the node can have child nodes.
    // Parameters
    // nodeType [out] Type of the node. 
    // Return Values:
    // S_OK            Value returned if successful. 
    
    virtual AcUtXMLDOMResult get_nodeTypeString(AcUtString& nodeTypeString) const;
    // Returns the node type in string form.
    // Parameters
    // nodeTypeString [out] String version of the node type. 
    // Return Values
    // S_OK           Value returned if successful. 

    virtual AcUtXMLDOMResult get_ownerDocument(AcUtXMLDOMDocument*& pDocument) const;
    // Returns the root of the document that contains this node.
    // Parameters
    // DOMDocument [out] Address of the parent document object that represents 
    // the root of the document. 
    // Return Values: 
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if pDocument is null. 

    virtual AcUtXMLDOMResult get_parentNode(AcUtXMLDOMNode*& pParent) const;
    // Contains the parent node (for nodes that can have parents).
    // Parameters
    // parent [out] Parent of the given node instance. All nodes, except 
    // kDocument, kDocumentFragment, and kAttribute nodes, can have a parent. 
    // However, if a node has just been created and not yet added to the tree, 
    // or if it has been removed from the tree, the parent is null. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if parent is null.

    virtual AcUtXMLDOMResult get_prefix(AcUtString& prefixString) const;
    // Returns the namespace prefix.
    // Parameters
    // prefixString [out] Namespace prefix specified on the element, attribute, 
    // or entity reference. For example, for the element <xxx:yyy>, 
    // it returns xxx. It returns an empty string, "", if no prefix is specified. 
    // 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_FAIL          Value couldn't be determined.

    virtual AcUtXMLDOMResult get_parsed(bool& isParsed) const;
    // Indicates whether this node and all descendants have been parsed and instantiated.
    // During asynchronous access, not all of the document tree may be available. 
    // Before performing some operations, such as XSL transformations or 
    // pattern-matching operations, it is useful to know whether the entire tree 
    // below this node is available for processing.
    //
    // Parameters
    // isParsed [out] True if this node and all descendants have been parsed, 
    // or false if any descendants remain to be parsed. 
    // Return Values:
    // S_OK            Value returned if successful. 

    virtual AcUtXMLDOMResult get_specified(bool& isSpecified) const;
    // Indicates whether the node (usually an attribute) is explicitly specified 
    // or derived from a default value in the DTD or schema.
    // Parameters
    // isSpecified 
    // [out] True if the attribute is explicitly specified in the element. 
    // Returns false if the attribute value comes from the document type
    // definition (DTD) or schema. 
    // Return Values:
    // S_OK            Value returned if successful. 

    virtual AcUtXMLDOMResult get_text(AcUtString& text) const;
    // Contains the text content of the node and its subtrees.
    // Parameters
    // text [out] String representing the text content of this node and its 
    // descendants. This value varies depending on the value of the nodeType 
    // property.
    // Return Values:
    // S_OK            Value returned if successful. 

    virtual AcUtXMLDOMResult get_xml(AcUtString& xmlString) const;
    // Contains the XML representation of the node and all its descendants.
    // Parameters
    // xmlString [in, out] XML representation of this node and all its descendants. 
    // Return Values:
    // S_OK           Value returned if successful. 

    virtual AcUtXMLDOMResult hasChildNodes(bool& hasChildren) const;
    // Returns true if this node has children.
    // Parameters
    // hasChild [out] True is returned if this node has children. 
    // Return Values:  
    // S_OK            Value returned if successful. 
    // S_FALSE         Value when VARIANT_FALSE is returned.  

    virtual AcUtXMLDOMResult insertBefore(const AcUtXMLDOMNode& newChild,
        const AcUtXMLDOMNode* refChild, AcUtXMLDOMNode*& outNewChild);
    // Inserts a child node to the left of the specified node or at 
    // the end of the list.
    // Parameters
    // newChild [in] Address of the new node to be inserted. 
    // refChild [in] Address of the reference node; newChild is inserted 
    // to the left of refChild. If NULL, newChild is inserted at the end 
    // of the child list. 
    // outNewChild [out] On success, the child node that was inserted. 
    // If NULL, no object is created. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // E_FAIL         Value returned if an error occurs. 

    virtual AcUtXMLDOMResult removeChild(AcUtXMLDOMNode* oldChild,
        AcUtXMLDOMNode*& outOldChild);
    // Removes the specified child node from the list of children and returns it.
    // Parameters
    // oldChild [in] Child node to be removed from the list of children of this node. 
    // outOldChild [out] Removed child node. If null, no object is created. 
    // Return Values:   
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if oldChild is not a child of this node, 
    //                 when the specified oldChild is read-only and cannot be removed, 
    //                 or when oldChild is null. 
    // E_FAIL          Value returned if an error occurs. 

    virtual AcUtXMLDOMResult put_dataType(const AcUtString& dataTypeName);
    // Specifies the data type for this node.
    // Parameters
    // dataTypeName [in] The data type name
    // Return Values:
    // S_OK             Value returned if successful. 
    // E_FAIL           Value returned if an error occurs.

    virtual AcUtXMLDOMResult put_nodeTypedValue(const AcUtVariant& typedValue);
    // Sets this node's value expressed in its defined data type.
    // Parameters
    // typedValue [in] Value for this node in its defined data type, if such a 
    // data type is defined.
    // Return Values:
    // S_OK             Value returned if successful. 
    // E_FAIL           Value returned if an error occurs. 

    virtual AcUtXMLDOMResult put_text(const AcUtString& text);
    // Contains the text content of the node and its subtrees.
    // Parameters
    // text [out] String representing the text content of this node and its 
    // descendants. This value varies depending on the value of the nodeType
    // property.
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  

    virtual AcUtXMLDOMResult put_nodeValue(const AcUtString& value);
    // Associates text with the node.
    // Parameters
    // value [in] Node value; depends on the nodeType property. 
    // Return Value
    // S_OK         if successful, or an error code otherwise.
    // Remarks
    // This value depends on the value of the nodeType property.
    // NODE_ATTRIBUTE       A string representing the value of the attribute. 
    //                      For attributes with subnodes, this is the 
    //                      concatenated text of all subnodes with entities
    //                      expanded. Setting this value deletes all children 
    //                      of the node and replaces them with a single text 
    //                      node containing the value written. 
    // NODE_CDATA_SECTION   A string representing the text stored in the CDATA 
    //                      section. 
    // NODE_COMMENT         The content of the comment, exclusive of the comment
    //                      begin and end sequence. 
    // NODE_DOCUMENT,
    // NODE_DOCUMENT_TYPE, 
    // NODE_DOCUMENT_FRAGMENT, 
    // NODE_ELEMENT, 
    // NODE_ENTITY, 
    // NODE_ENTITY_REFERENCE, 
    // NODE_NOTATION        Attempting to set the value of the node returns an error. 
    // NODE_PROCESSING_INSTRUCTION The content of the processing instruction, 
    //                      excluding the target. (The target appears in the 
    //                      nodeName property.) 
    // NODE_TEXT            A string representing the text stored in the text node. 

    virtual AcUtXMLDOMResult replaceChild(AcUtXMLDOMNode* newChild,
        AcUtXMLDOMNode* oldChild, AcUtXMLDOMNode*& outOldChild);
    // Replaces the specified old child node with the supplied new child 
    // node in the set of children of this node, and returns the old child node.
    //
    // Parameters
    // newChild [in] Address of the new child that is to replace the old child. 
    // If NULL, oldChild is removed without a replacement. 
    // oldChild [in] Address of the old child that is to be replaced by the new child. 
    // outOldChild [out] Old child that is replaced. If null, no object is created. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if the newChild node cannot be inserted as a 
    // child of this node, when the specified oldChild is not a child of this node, 
    // or if oldChild is null. 
    // E_FAIL          Value returned if an error occurs. 


    // *** XML Query functions *** 
    virtual AcUtXMLDOMResult selectNodes(const AcUtString& patternString, 
        AcUtXMLDOMNodeList*& resultList) const;
    // Applies the specified pattern-matching operation to this node's context and 
    // returns the list of matching nodes.
    // Parameters
    // patternString [in] XSL Pattern that is to be used in the query;
    // applied to this node's context. 
    // resultList [out] List of nodes selected by the XSL Pattern query. 
    // If no nodes are selected by the query, an empty node list is returned. 
    // Return Values
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if resultList is null.

    virtual AcUtXMLDOMResult selectSingleNode(const AcUtString& patternString,
        AcUtXMLDOMNode*& resultNode) const;
    // Applies the specified pattern to this node's context and returns the 
    // first matching node.
    // Parameters
    // patternString [in] XSL Pattern that is to be used in the query; applied 
    // to this node's context. 
    // resultNode [out] First node that is selected by the XSL Pattern query. 
    // If no nodes result from the query, it returns NULL. 
    // Return Values:
    // S_OK           Value returned if successful. 
    // S_FALSE        Value when returning null.  
    // E_INVALIDARG   Value returned if resultNode is null.

    // *** XSL Transformation functions *** 
    virtual AcUtXMLDOMResult transformNode(const AcUtXMLDOMNode& stylesheet,
        AcUtString& xmlString);
    // Processes this node and its children using the supplied XSL style sheet, 
    // and returns the resulting transformation.
    // Parameters
    // stylesheet [in] Valid XML document or DOM node, which consists of XSL 
    // elements that direct the transformation of this node. 
    // xmlString [out] String that contains the product of the transformation 
    // of this XML document based on the XSL style sheet. 
    // Return Values:
    // S_OK            Value returned if successful. 
    // E_INVALIDARG    Value returned if xmlString is null.

    virtual AcUtXMLDOMResult transformNodeToObject(
        const AcUtXMLDOMNode& stylesheet, AcUtVariant& outputObject);
    // Processes this node and its children using the supplied XSL style sheet,
    // and returns the resulting transformation.
    // Parameters
    // stylesheet [in] Valid XML document or DOM node, which consists of XSL
    // elements that direct the transformation of this node. 
    // outputObject [out] Object that contains the product of the 
    // transformation of this XML document based on the XSL style sheet. 
    // If the variant represents the IXMLDOMDocument object, the document is built according to its properties, and its child nodes are replaced during this transformation process. If the variant contains an IStream interface, the XML transformation is sent to this stream. 
    // Return Values:
    // S_OK            Value returned if successful. 

protected:
    friend class AcUtImpXMLDOMNode;
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMNamedNodeMap;
    friend class AcUtImpXMLDOMNodeList;
    friend class AcUtImpXMLDOMAttribute;
    friend class AcUtImpXMLDOMElement;
    friend class AcUtImpXMLDOMCDATASection;
    friend class AcUtImpXMLDOMCharacterData;
    friend class AcUtImpXMLDOMComment;
    friend class AcUtImpXMLDOMDocumentFragment;
    friend class AcUtImpXMLDOMDocumentType;
    friend class AcUtImpXMLDOMEntity;
    friend class AcUtImpXMLDOMEntityReference;
    friend class AcUtImpXMLDOMNotation;
    friend class AcUtImpXMLDOMProcessingInstruction;
    friend class AcUtImpXMLDOMText;
    friend class AcUtImpXTLRuntime;
    AcUtImpXMLDOMNode* mpImpNode;
};
