//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003  by Autodesk, Inc.
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
// Name:            DbField.h
//
// Description:     AcDbObject derived API classes for fields. 
//                  Contains the following classes: 
//                      AcDbField
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcField.h"

class AcDbField;


typedef AcArray<AcDbField*> AcDbFieldArray;


//*************************************************************************
// AcFd
//*************************************************************************
typedef struct AcFd
{
    // Enum for acdbEvaluateFields
    enum EvalFields
    {
        kEvalRecursive      = (0x1 << 0),       // Recursively evaluate complex objects
    };

} AcFd;


//*************************************************************************
// AcDbField
//*************************************************************************

class AcDbField : public AcDbObject
{
public:
    enum State
    {
        kInitialized        = (0x1 << 0),       // Field has been initialized by the evaluator
        kCompiled           = (0x1 << 1),       // Field has beene compiled
        kModified           = (0x1 << 2),       // Field code has been modified, but not yet evaluated
        kEvaluated          = (0x1 << 3),       // Field has been evaluated
        kHasCache           = (0x1 << 4),       // Field has evaluated cache
        kHasFormattedString = (0x1 << 5),       // For internal use only. Field has cached formatted string. 
    };

    enum EvalOption
    {
        kDisable            = 0,                // Disable evaluation of field
        kOnOpen             = (0x1 << 0),       // Evaluate on drawing open
        kOnSave             = (0x1 << 1),       // Evaluate on drawing save
        kOnPlot             = (0x1 << 2),       // Evaluate on drawing plot
        kOnEtransmit        = (0x1 << 3),       // Evaluate on drawing etransmit
        kOnRegen            = (0x1 << 4),       // Evaluate on drawing regen
        kOnDemand           = (0x1 << 5),       // Evaluate on demand
        kAutomatic          = (kOnOpen | kOnSave | kOnPlot | 
                               kOnEtransmit | kOnRegen | kOnDemand),    // No restriction
    };

    enum EvalContext
    {
        kOpen               = (0x1 << 0),       // Field being evaluated on drawing open
        kSave               = (0x1 << 1),       // Field being evaluated on drawing save
        kPlot               = (0x1 << 2),       // Field being evaluated on drawing plot
        kEtransmit          = (0x1 << 3),       // Field being evaluated on drawing etransmit
        kRegen              = (0x1 << 4),       // Field being evaluated on drawing regen
        kDemand             = (0x1 << 5),       // Field being evaluated on demand
        kPreview            = (0x1 << 6),       // Field being evaluated for preview
    };

    enum EvalStatus
    {
        kNotYetEvaluated    = (0x1 << 0),       // Not yet evaluated
        kSuccess            = (0x1 << 1),       // Evaluated successfully
        kEvaluatorNotFound  = (0x1 << 2),       // Evaluator not found
        kSyntaxError        = (0x1 << 3),       // Field code syntax error
        kInvalidCode        = (0x1 << 4),       // Invalid field code
        kInvalidContext     = (0x1 << 5),       // Invalid context to evaluate field
        kOtherError         = (0x1 << 6),       // Evaluation error
    };

    enum FieldCodeFlag
    {
        kFieldCode          = (0x1 << 0),       // Get raw field code. Used only in getFieldCode().
        kEvaluatedText      = (0x1 << 1),       // Get evaluated text. Used only in getFieldCode().
        kEvaluatedChildren  = (0x1 << 2),       // Get field code with evaluated text for child fields. Used only in getFieldCode().
        kObjectReference    = (0x1 << 3),       // Get field code as object reference. Used only in getFieldCode().
        kAddMarkers         = (0x1 << 4),       // Include markers around field codes. Used only in getFieldCode().
        kEscapeBackslash    = (0x1 << 5),       // Convert single backslashes to double backslashes. Used only in getFieldCode().
        kStripOptions       = (0x1 << 6),       // Strip the standard options from field code. Used only in getFieldCode().
        kPreserveFields     = (0x1 << 7),       // Try to preserve existing fields. Used only in setFieldCode().
        kTextField          = (0x1 << 8),       // Treat the field as text with embedded fields. Used only in setFieldCode().
    };

    enum FilingOption
    {
        kSkipFilingResult   = (0x1 << 0),       // Don't file field value
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbField);

    ACDB_PORT AcDbField(void);
    ACDB_PORT AcDbField(const char* pszFieldCode, bool bTextField = false);
    ACDB_PORT ~AcDbField(void);

    ACDB_PORT Acad::ErrorStatus setInObject (AcDbObject* pObj, 
                                             const char* pszPropName);
    ACDB_PORT Acad::ErrorStatus postInDatabase(AcDbDatabase* pDb);
    ACDB_PORT AcDbField::State state        (void) const;
    ACDB_PORT AcDbField::EvalStatus evaluationStatus(int* pnErrCode = NULL, 
                                             char** pszErrMsg = NULL) const;
    ACDB_PORT AcDbField::EvalOption evaluationOption(void) const;
    ACDB_PORT Acad::ErrorStatus setEvaluationOption(AcDbField::EvalOption nEvalOption);
    ACDB_PORT AcDbField::FilingOption filingOption(void) const;
    ACDB_PORT Acad::ErrorStatus setFilingOption(AcDbField::FilingOption nOption);

    ACDB_PORT const char * evaluatorId      (void) const;
    ACDB_PORT Acad::ErrorStatus setEvaluatorId(const char* pszEvaluatorId);
    bool            isTextField             (void) const;
    Acad::ErrorStatus convertToTextField    (void);

    ACDB_PORT const char * getFieldCode     (AcDbField::FieldCodeFlag nFlag,
                                             AcArray<AcDbField*>* pChildFields = NULL, 
                                             AcDb::OpenMode mode = AcDb::kForRead) const;
    ACDB_PORT Acad::ErrorStatus getFieldCode(char*& pszFieldCode, 
                                             AcDbField::FieldCodeFlag nFlag,
                                             AcArray<AcDbField*>* pChildFields = NULL, 
                                             AcDb::OpenMode mode = AcDb::kForRead) const;
    ACDB_PORT Acad::ErrorStatus setFieldCode(const char* pszFieldCode, 
                                             AcDbField::FieldCodeFlag nFlag = (AcDbField::FieldCodeFlag) 0,
                                             AcDbFieldArray* pChildFields = NULL);

    ACDB_PORT int   childCount              (void) const;
    ACDB_PORT Acad::ErrorStatus getChild    (int iIndex, 
                                             AcDbField*& pField, 
                                             AcDb::OpenMode mode);

    ACDB_PORT const char * getFormat        (void) const;
    ACDB_PORT Acad::ErrorStatus getFormat   (char*& pszFormat) const;
    ACDB_PORT Acad::ErrorStatus setFormat   (const char* pszFormat);

    ACDB_PORT Acad::ErrorStatus evaluate    (int nContext, 
                                             AcDbDatabase* pDb, 
                                             int* pNumFound     = NULL,
                                             int* pNumEvaluated = NULL);
    ACDB_PORT AcFdFieldValue::DataType dataType (void) const;

    ACDB_PORT const char * getValue         (void) const;
    ACDB_PORT Acad::ErrorStatus getValue    (char*& pszValue) const;
    ACDB_PORT Acad::ErrorStatus getValue    (AcFdFieldValue& value) const;

    ACDB_PORT bool  hasHyperlink            (void) const;
    ACDB_PORT Acad::ErrorStatus getHyperlink(char** pszName,
                                             char** pszDescription, 
                                             char** pszSubLocation,
                                             char** pszDisplayString) const;
    ACDB_PORT Acad::ErrorStatus setHyperlink(const char* pszName, 
                                             const char* pszDescription, 
                                             const char* pszSubLocation = NULL);
    ACDB_PORT Acad::ErrorStatus removeHyperlink(void);

    ACDB_PORT Acad::ErrorStatus getData     (const char* pszKey, 
                                             AcFdFieldValue* pData) const;
    ACDB_PORT Acad::ErrorStatus setData     (const char* pszKey, 
                                             const AcFdFieldValue* pData);

public:
    // Base class overrides
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus subClose();
};


//*************************************************************************
// Global exported functions
//*************************************************************************

ACDB_PORT AcFdFieldEngine* acdbGetFieldEngine(void);
ACDB_PORT bool      acdbGetFieldMarkers     (const char*& pszPrefix, 
                                             const char*& pszSuffix);
ACDB_PORT bool      acdbHasFields           (LPCTSTR pszText);
ACDB_PORT bool      acdbFindField           (LPCTSTR pszText, 
                                             int iSearchFrom, 
                                             int& nStartPos, 
                                             int& nEndPos);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectId& objId, 
                                             int nContext, 
                                             const char* pszPropName    = NULL, 
                                             AcDbDatabase* pDb          = NULL, 
                                             AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive,
                                             int* pNumFound             = NULL,
                                             int* pNumEvaluated         = NULL);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectIdArray& objIds, 
                                             int nContext, 
                                             const char* pszPropName    = NULL, 
                                             AcDbDatabase* pDb          = NULL, 
                                             AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive,
                                             int* pNumFound             = NULL,
                                             int* pNumEvaluated         = NULL);
ACDB_PORT Acad::ErrorStatus acdbMakeFieldCode(LPCTSTR pszFieldExpr, 
                                             char*& pszFieldCode, 
                                             LPCTSTR pszEvalId      = NULL, 
                                             LPCTSTR pszFormat      = NULL, 
                                             LPCTSTR pszHLUrl       = NULL, 
                                             LPCTSTR pszHLDesc      = NULL, 
                                             LPCTSTR pszHLSubLoc    = NULL);
