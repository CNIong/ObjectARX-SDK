
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

#ifndef _ACUTXMLDOMPARSEERROR_H
#define _ACUTXMLDOMPARSEERROR_H

#include "acutXMLDOM.h"

class ACUTXMLDOM_API AcUtXMLDOMParseError
{
public:
    AcUtXMLDOMParseError();
    virtual ~AcUtXMLDOMParseError();

    AcUtXMLDOMResult get_errorCode(long& errorCode) const;
    // Gets the error code of the last parse error.
    // Parameters
    // errorCode [out] Returns the error code in a decimal value. 
    // Return Value
    // S_OK if successful, or an error code otherwise.

    AcUtXMLDOMResult get_filepos(long& filePosition) const;
    // Gets the absolute file position where the error occurred.
    // Parameters
    // filePosition [out] Absolute file position where the error occurred. 
    // Return Value
    // S_OK if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_line(long& lineNumber) const;
    // Gets the line number that contains the error.
    // Parameters 
    // lineNumber [out] Line number where the error occurred. 
    // Return Value
    // S_OK if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_linepos(long& linePosition) const;
    // Gets the character position within the line where the error occurred.
    // Parameters
    // linePosition [out] Character position within the line where the error 
    // occurred. 
    // Return Value
    // S_OK if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_reason(AcUtString& reasonString) const;
    // Gets text explaining the reason for the error.
    // Parameters
    // reasonString [out] Text describing the reason for the error. 
    // This text includes a description of the error, the line number, 
    // character position, and source text of the error. 
    // Validation errors also include the URL of the schema and 
    // the node within the schema that corresponds to the error. 
    // Return Value
    // S_OK if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_srcText(AcUtString& sourceString) const;
    // Gets the text of the line containing the error.
    // Parameters
    // sourceString [out] Full text of the line containing the error. This returns an empty string if the error is caused when the XML is not well-formed and the error cannot be assigned to a specific line. 
    // Return Value:
    // S_OK if successful, or an error code otherwise. 

    AcUtXMLDOMResult get_url(AcUtString& urlString) const;
    // Gets the URL of the XML document containing the last error.
    // Parameters
    // urlString  [out] URL of the XML file containing the error. 
    // Return Value
    // S_OK if successful, or an error code otherwise. 

protected:
    friend class AcUtImpXMLDOMDocument;
    friend class AcUtImpXMLDOMParseError;
    AcUtImpXMLDOMParseError* mpImpParseError;
};

#endif // _ACUTXMLDOMPARSEERROR_H