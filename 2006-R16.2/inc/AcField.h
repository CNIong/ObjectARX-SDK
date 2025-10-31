//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003-2005  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
// 
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            AcField.h
//
// Description:     AcRxObject derived API classes for fields. Contains 
//                  the following classes: 
//                      AcFdFieldEvaluator
//                      AcFdFieldEvaluatorLoader
//                      AcFdFieldEngine
//                      AcFdFieldResult
//                      AcFdFieldValue
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"

class AcDbField;
class AcDbFieldCache;
class AcFdFieldResult;
class AcFdFieldEvaluator;
class AcFdFieldEvaluatorLoader;
class AcFdFieldEngine;
class AcFdFieldValue;
class AcFdImpFieldFormat;


//*************************************************************************
// AcFdFieldEvaluator
//*************************************************************************

class AcFdFieldEvaluator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEvaluator);

    ACDB_PORT AcFdFieldEvaluator(void);
    ACDB_PORT virtual ~AcFdFieldEvaluator(void);

    ACDB_PORT virtual const ACHAR * evaluatorId(void) const;
    ACDB_PORT virtual const ACHAR * evaluatorId(AcDbField* pField);

    ACDB_PORT virtual Acad::ErrorStatus initialize(AcDbField* pField); 
    ACDB_PORT virtual Acad::ErrorStatus compile(AcDbField* pField, 
                                             AcDbDatabase* pDb,
                                             AcFdFieldResult* pResult);
    ACDB_PORT virtual Acad::ErrorStatus evaluate(AcDbField* pField, 
                                             int nContext, 
                                             AcDbDatabase* pDb, 
                                             AcFdFieldResult* pResult);
    ACDB_PORT virtual Acad::ErrorStatus format(AcDbField* pField, 
                                             ACHAR *& pszValue);

protected:
    AcFdFieldEvaluator(void*);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};


//*************************************************************************
// AcFdFieldEvaluatorLoader
//*************************************************************************

class AcFdFieldEvaluatorLoader : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEvaluatorLoader);

    ACDB_PORT AcFdFieldEvaluatorLoader(void);
    ACDB_PORT AcFdFieldEvaluatorLoader(void*);    
    ACDB_PORT ~AcFdFieldEvaluatorLoader(void);

    ACDB_PORT virtual AcFdFieldEvaluator* getEvaluator(
                                                const ACHAR * pszEvalId);
    ACDB_PORT virtual AcFdFieldEvaluator * findEvaluator(AcDbField* pField, 
                                             const ACHAR *& pszEvalId);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};


//*************************************************************************
// AcFdFieldEngine
//*************************************************************************

class AcFdFieldEngine : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEngine);

    ACDB_PORT AcFdFieldEngine();
    ACDB_PORT virtual ~AcFdFieldEngine();

    ACDB_PORT Acad::ErrorStatus registerEvaluatorLoader(AcFdFieldEvaluatorLoader* pLoader);
    ACDB_PORT Acad::ErrorStatus unregisterEvaluatorLoader(AcFdFieldEvaluatorLoader* pLoader);
    ACDB_PORT int   evaluatorLoaderCount    (void) const;
    ACDB_PORT AcFdFieldEvaluatorLoader * getEvaluatorLoader(int iIndex);
    ACDB_PORT AcFdFieldEvaluator * getEvaluator (const ACHAR * pszEvalId);
    ACDB_PORT AcFdFieldEvaluator * findEvaluator(AcDbField* pField, 
                                             const ACHAR *& pszEvalId);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};


//*************************************************************************
// AcFdFieldResult
//*************************************************************************

class AcFdFieldResult : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldResult);

    AcFdFieldResult(void);
    ACDB_PORT virtual Acad::ErrorStatus setFieldValue(const AcFdFieldValue* pValue);
    ACDB_PORT virtual Acad::ErrorStatus setEvaluationStatus(int nStatus, 
                                             int dwErrCode = 0, 
                                             const ACHAR * pszMsg = NULL);
};


//*************************************************************************
// AcFdFieldValue
//*************************************************************************

class AcFdFieldValue : public AcRxObject
{
public:
    enum DataType
    {
        kUnknown        = 0,
        kLong           = (0x1 << 0),
        kDouble         = (0x1 << 1),
        kString         = (0x1 << 2),
        kDate           = (0x1 << 3),
        kPoint          = (0x1 << 4),
        k3dPoint        = (0x1 << 5),
        kObjectId       = (0x1 << 6),
        kBuffer         = (0x1 << 7),
        kResbuf         = (0x1 << 8),
    };

public:
    static bool     isValidDataType         (const VARIANT& var);

public:
    ACRX_DECLARE_MEMBERS(AcFdFieldValue);
    
    ACDB_PORT AcFdFieldValue(void);
    ACDB_PORT AcFdFieldValue(const AcFdFieldValue& value);
    ACDB_PORT AcFdFieldValue(const ACHAR * pszValue);
    ACDB_PORT AcFdFieldValue(long lValue);
    ACDB_PORT AcFdFieldValue(double fValue);
    ACDB_PORT AcFdFieldValue(const __time64_t& date);
    ACDB_PORT AcFdFieldValue(double x, double y);
    ACDB_PORT AcFdFieldValue(double x, double y, double z);
    ACDB_PORT AcFdFieldValue(const AcDbObjectId& id);
    ACDB_PORT AcFdFieldValue(const resbuf& rb);
    ACDB_PORT AcFdFieldValue(const VARIANT& var);
    ACDB_PORT AcFdFieldValue(const void* pBuf, DWORD dwBufSize);

    ACDB_PORT ~AcFdFieldValue(void);

    ACDB_PORT bool  reset                   (void);
    ACDB_PORT AcFdFieldValue::DataType dataType (void) const;
    ACDB_PORT bool  isValid                 (void) const;

    ACDB_PORT       operator const ACHAR *  (void) const;
    ACDB_PORT       operator long           (void) const;
    ACDB_PORT       operator double         (void) const;
    ACDB_PORT       operator __time64_t     (void) const;
    ACDB_PORT       operator AcDbObjectId   (void) const;

    ACDB_PORT AcFdFieldValue& operator=     (const AcFdFieldValue& value);
    ACDB_PORT AcFdFieldValue& operator=     (const ACHAR * pszValue);
    ACDB_PORT AcFdFieldValue& operator=     (long lValue);
    ACDB_PORT AcFdFieldValue& operator=     (double fValue);
    ACDB_PORT AcFdFieldValue& operator=     (__time64_t date);
    ACDB_PORT AcFdFieldValue& operator=     (const AcDbObjectId& objId);
    ACDB_PORT AcFdFieldValue& operator=     (const resbuf& rb);
    ACDB_PORT AcFdFieldValue& operator=     (const VARIANT& var);

    Adesk::Boolean  isEqualTo               (const AcRxObject* pOther) const;

    ACDB_PORT bool  get                     (const ACHAR *& pszValue) const;
    ACDB_PORT bool  get                     (ACHAR *& pszValue) const;
    ACDB_PORT bool  get                     (long& lValue) const;
    ACDB_PORT bool  get                     (double& fValue) const;
    ACDB_PORT bool  get                     (__time64_t& date) const;
    ACDB_PORT bool  get                     (double& x, 
                                             double& y) const;
    ACDB_PORT bool  get                     (double& x, 
                                             double& y, 
                                             double& z) const;
    ACDB_PORT bool  get                     (AcDbObjectId& objId) const;
    ACDB_PORT bool  get                     (resbuf** pRb) const;
    ACDB_PORT bool  get                     (VARIANT& var) const;
    ACDB_PORT bool  get                     (void*& pBuf, 
                                             DWORD& dwBufSize) const;

    ACDB_PORT bool  set                     (const AcFdFieldValue& value);
    ACDB_PORT bool  set                     (const ACHAR * pszValue);
    ACDB_PORT bool  set                     (long lValue);
    ACDB_PORT bool  set                     (double fValue);
    ACDB_PORT bool  set                     (const __time64_t& date);
    ACDB_PORT bool  set                     (double x, 
                                             double y);
    ACDB_PORT bool  set                     (double x, 
                                             double y, 
                                             double z);
    ACDB_PORT bool  set                     (const AcDbObjectId& objId);
    ACDB_PORT bool  set                     (const resbuf& rb);
    ACDB_PORT bool  set                     (const VARIANT& var);
    ACDB_PORT bool  set                     (const void* pBuf, 
                                             DWORD dwBufSize);
    ACDB_PORT bool  format                  (const ACHAR * pszFormat, 
                                             ACHAR *& pszValue) const;

    Acad::ErrorStatus dwgInFields           (AcDbDwgFiler* pFiler);
    Acad::ErrorStatus dwgOutFields          (AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus dxfInFields           (AcDbDxfFiler* pFiler);
    Acad::ErrorStatus dxfOutFields          (AcDbDxfFiler* pFiler) const;

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};
