#ifndef __DBSECURITY_H_
#define __DBSECURITY_H_
//
// (C) Copyright 2002 by Autodesk, Inc.
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
//
// DESCRIPTION: DWG Security - Parameters for encryption/decryption
//              and digital signatures
//

class AcDbDate;


enum
{
    SECURITYPARAMS_ENCRYPT_DATA     = 0x00000001,
    SECURITYPARAMS_ENCRYPT_PROPS    = 0x00000002,

    SECURITYPARAMS_SIGN_DATA        = 0x00000010,
    SECURITYPARAMS_ADD_TIMESTAMP    = 0x00000020
};


enum
{
    SECURITYPARAMS_ALGID_RC4        = 0x00006801
};


struct SecurityParams
{
    unsigned long   cbSize;
    unsigned long   ulFlags;        // see enum above for flag values

    // data relevant to password protection
    wchar_t*        wszPassword;
    unsigned long   ulProvType;
    wchar_t*        wszProvName;
    unsigned long   ulAlgId;        // SECURITYPARAMS_ALGID_RC4
    unsigned long   ulKeyLength;

    // data relevant to digital signatures
    wchar_t*        wszCertSubject;
    wchar_t*        wszCertIssuer;
    wchar_t*        wszCertSerialNum;
    wchar_t*        wszComment;
    wchar_t*        wszTimeServer;
};


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following struct is for internal use only.                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

struct SignatureInfo
{
    unsigned long   cbSize;

    unsigned long   ulFlags;
    wchar_t*        wszCertSubject;
    wchar_t*        wszCertIssuer;
    wchar_t*        wszSubjectEMail;
    wchar_t*        wszCertSerialNum;
    wchar_t*        wszX500;
    AcDbDate*       pTimeCertNotBefore;
    AcDbDate*       pTimeCertNotAfter;
    wchar_t*        wszComment;
    wchar_t*        wszTimeServer;
    AcDbDate*       pTimestamp;
};


#endif  // __DBSECURITY_H_
