
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

#ifndef _ACUTXMLDOMIMPLEMENTATION_H
#define _ACUTXMLDOMIMPLEMENTATION_H

#include "acutXMLDOM.h"

class ACUTXMLDOM_API AcUtXMLDOMImplementation
{
public:
    AcUtXMLDOMImplementation();
    virtual ~AcUtXMLDOMImplementation();

    AcUtXMLDOMResult hasFeature(const AcUtString& feature,
        const AcUtString& version, bool& bHasFeature);

private:
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMImplementation;

    AcUtImpXMLDOMImplementation* mpImpl;
};

#endif // _ACUTXMLDOMIMPLEMENTATION_H