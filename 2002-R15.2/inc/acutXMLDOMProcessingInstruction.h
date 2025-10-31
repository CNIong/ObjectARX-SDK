
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
#include "acutXMLDOMNode.h"

/* 
The AcUtXMLDOMProcessingInstruction node represents the
contents between the delimiters of a processing instruction.

The processing instruction has a target and data.

The target is the first token after the "<?" string, and is 
directed to an application which is to process the instruction.  
The target is the same as the nodeName property.

The data the text from the first nonwhite-space character after the 
target through the character  immediately preceding the "?>" string 
that signifies the end of the tag. The data is the same as the
nodeValue property.

*/
class ACUTXMLDOM_API AcUtXMLDOMProcessingInstruction : public AcUtXMLDOMNode
{
public:
    AcUtXMLDOMProcessingInstruction();
    AcUtXMLDOMProcessingInstruction(const AcUtXMLDOMNode* pNode);
    virtual ~AcUtXMLDOMProcessingInstruction();

    AcUtXMLDOMResult get_data(AcUtString& value) const;
    // Gets the processing instruction text, excluding the target.
    // Parameters
    // value  [out] Text of the processing instruction for this target. 

    AcUtXMLDOMResult put_data(const AcUtString& value);
    // Sets the text of the processing instruction, excluding the target.
    // Parameters
    // value [in] Text for the processing instruction, excluding the target. 
    // Return Value:
    // S_OK           Returned if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_target(AcUtString& name) const;
    // Gets the target, the application to which this processing instruction 
    // is directed.
    // Parameters
    // name [out] The name of the application to which this processing 
    // instruction is directed (the target). 

protected:
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMProcessingInstruction;
    AcUtImpXMLDOMProcessingInstruction* mpImpPI;
};
