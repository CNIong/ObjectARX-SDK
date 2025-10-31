#ifndef DB_DBAUDITA_H
#define DB_DBAUDITA_H 1
//
// (C) Copyright 1994-1999 by Autodesk, Inc. 
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
//
//      Header file for auditing routines

#pragma pack(push, 8)

class AcDbDatabase;
class AcDbAuditInfo;
class AcDbImpAuditInfo;
class AcDbAuditImp;
class AcDbObject;

class AcDbAuditInfo
{
public:

    friend AcDbImpAuditInfo;
    friend AcDbAuditImp;

    enum AuditPass {
            PASS1 = 1,
            PASS2 = 2
    };

    AcDbAuditInfo();
    ~AcDbAuditInfo();

    bool           fixErrors(void) const;        // True if errors are to
                                                 // be fixed.

    int numErrors() const;

    int numFixes(void) const;

    void errorsFound(int count);            // Specify the number     
                                            // of errors found.

    void errorsFixed(int count);            // Specify the number of 
                                            // errors fixed.

    AuditPass auditPass(void) const;        // The audit pass
                                            // number:
                                            // 1 = pass 1,
                                            // 2 = pass 2.
    void printError(const char * name,
                    const char * value, 
                    const char * validation,
                    const char * defaultValue);   // Print an error 
                                            // message string to the
                                            // Audit report file.
                                            // Obeys AUDITCTL.

    // Same as above except that name is automatically constructed
    // from the AcDbObject.
    //
    void printError(const AcDbObject *pObj,
                    const char * value, 
                    const char * validation,
                    const char * defaultValue);

    void requestRegen();

    void resetNumEntities();
    
    void incNumEntities();

    int numEntities();

    void printNumEntities(const char* msg);

private:

    AcDbImpAuditInfo * getImpAudit() const;

    AcDbImpAuditInfo * mpImpAudit;
};

//    Class to hold the call back function.

class AcDbRecover{

    public:
    virtual  int callBack(AcDbDatabase*) = 0;
};

class  AcDbImpRecoverCallBack;

class AcDbRecoverCallBack {

    public:
    AcDbRecoverCallBack();
    virtual ~AcDbRecoverCallBack();

    virtual  Acad::ErrorStatus registerCallBack(AcDbRecover*);
    virtual  Acad::ErrorStatus removeCallBack();

    private:

        AcDbImpRecoverCallBack *mpImpRecoverCallBack;

};

#pragma pack(pop)

#endif
