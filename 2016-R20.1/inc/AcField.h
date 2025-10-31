//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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
//                      AcFdFieldReactor
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"
#include "AcValue.h"

class AcDbField;
class AcDbFieldCache;
class AcFdFieldResult;
class AcFdFieldEvaluator;
class AcFdFieldEvaluatorLoader;
class AcFdFieldEngine;
class AcFdFieldValue;
class AcFdImpFieldFormat;
class AcDbEvalVariant;


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
    ACDB_PORT virtual Acad::ErrorStatus setFieldValue(const AcValue* pValue);
    ACDB_PORT virtual Acad::ErrorStatus setEvaluationStatus(int nStatus, 
                                             int dwErrCode = 0, 
                                             const ACHAR * pszMsg = NULL);
};


//*************************************************************************
// AcFdFieldValue
//*************************************************************************

class AcFdFieldValue : public AcValue
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldValue);
    
    ACDB_PORT AcFdFieldValue(void);
    ACDB_PORT AcFdFieldValue(AcFdFieldValue::DataType nDataType);
    ACDB_PORT AcFdFieldValue(const AcFdFieldValue& value);
    ACDB_PORT AcFdFieldValue(const ACHAR * pszValue);
    ACDB_PORT AcFdFieldValue(Adesk::Int32 lValue);
    ACDB_PORT AcFdFieldValue(double fValue);
#if _ADESK_WINDOWS_
    ACDB_PORT AcFdFieldValue(const __time64_t& date);
    ACDB_PORT AcFdFieldValue(const SYSTEMTIME& date);
#endif
    ACDB_PORT AcFdFieldValue(const AcGePoint2d& pt);
    ACDB_PORT AcFdFieldValue(double x, double y);
    ACDB_PORT AcFdFieldValue(const AcGePoint3d& pt);
    ACDB_PORT AcFdFieldValue(double x, double y, double z);
    ACDB_PORT AcFdFieldValue(const AcDbObjectId& id);
    ACDB_PORT AcFdFieldValue(const resbuf& rb);
    ACDB_PORT AcFdFieldValue(const AcDbEvalVariant& evalVar);
    ACDB_PORT AcFdFieldValue(const VARIANT& var);
    ACDB_PORT AcFdFieldValue(const void* pBuf, DWORD dwBufSize);
};


//*************************************************************************
// AcFdFieldReactor
//*************************************************************************

class AcFdFieldReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldReactor);

    ACDB_PORT virtual Acad::ErrorStatus beginEvaluateFields(int nContext, 
                                             AcDbDatabase* pDb);
    ACDB_PORT virtual Acad::ErrorStatus endEvaluateFields(int nContext, 
                                             AcDbDatabase* pDb);
};

typedef AcArray<AcFdFieldReactor*> FieldReactors;


//*************************************************************************
// Global exported functions
//*************************************************************************

ACDB_PORT Acad::ErrorStatus   acdbAddFieldReactor     (AcFdFieldReactor* pReactor);
ACDB_PORT Acad::ErrorStatus   acdbRemoveFieldReactor  (AcFdFieldReactor* pReactor);
