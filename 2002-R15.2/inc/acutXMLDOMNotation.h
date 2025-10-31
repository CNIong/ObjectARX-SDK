
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
Notations identify by name the format of unparsed entities, 
the format of elements that bear a notation attribute, or 
the application to which a processing instruction is addressed. 

The nodeName property contains the notation name. 
*/

class ACUTXMLDOM_API AcUtXMLDOMNotation : public AcUtXMLDOMNode
{
public:
    AcUtXMLDOMNotation();
    AcUtXMLDOMNotation(const AcUtXMLDOMNode* pNode);
    virtual ~AcUtXMLDOMNotation();

    AcUtXMLDOMResult get_publicId(AcUtString& publicID) const;
    // Gets the public identifier for the notation.
    // Parameters
    // publicID [out] Public identifier associated with the entity, if 
    // specified. If the public identifier is not specified, contains 
    // the empty string. 
    // Return Values:
    // S_OK             Value returned if successful. 
    // S_FALSE          Value when the public identifier is empty.

    AcUtXMLDOMResult get_systemId(AcUtString& systemID) const;
    // Gets the system identifier for the notation.
    // Parameters
    // systemID [out] System identifier associated with the entity, 
    // if specified. If the system identifier is not specified, contains 
    // the empty string. 
    // Return Values:
    // S_OK             Value returned if successful. 
    // S_FALSE          Value when returning null. 

protected:
    friend class AcUtImpXMLDOMNotation;
    AcUtImpXMLDOMNotation* mpImpNotation;
};

