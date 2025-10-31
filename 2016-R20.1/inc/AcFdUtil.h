//
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
// Name:            AcFdUtil.h
//
// Description:     Header for global methods exported from AcFdEval 
//                  module
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"
#include "AcCell.h"

#ifdef  ACFD_API
    # define ACFD_PORT __declspec(dllexport)
#else
    # define ACFD_PORT
#endif

// From dbeval.h
typedef Adesk::UInt32 AcDbEvalNodeId;

namespace AcFdEval
{
    // Option bit flags for object property field
    enum ObjectFieldOption
    {
        kObjFieldNone                   = 0,
        kObjFieldUnresolvedBlockRef     = (0x1 << 0),
        kObjFieldApplyBlockTransform    = (0x1 << 1),
        kObjFieldUnresolvedObjectRef    = (0x1 << 2),
    };

    // Option bit flags for sheet set field
    enum SheetSetFieldOption
    {
        kSheetSetNone                   = 0,
        kSheetSetHyperlink              = (0x1 << 0),
        kSheetSetUnresolvedComponent    = (0x1 << 1),
    };

    // Option bit flags for expression field
    enum ExpressionFieldOption
    {
        // Function types
        kExprFieldNone                  = 0,
        kExprFieldSum                   = (0x1 << 0),
        kExprFieldAverage               = (0x1 << 1),
        kExprFieldCount                 = (0x1 << 2),
        kExprFieldCell                  = (0x1 << 3),
        kExprFieldEquation              = (0x1 << 4),
    };
};

#ifndef _ADESK_MAC_
interface IAcSmDatabase;
interface IAcSmSheetSet;
interface IAcSmComponent;
#else
__interface IAcSmDatabase;
__interface IAcSmSheetSet;
__interface IAcSmComponent;
#endif
struct AcHyperlink;

ACFD_PORT BOOL   AcFdMakeFieldCode  (const AcDbObjectId& objId, 
                                     AcDbEvalNodeId blockParamId, 
                                     const ACHAR * pszPropOrConnectionName, 
                                     AcFdEval::ObjectFieldOption nOption, 
                                     const ACHAR * pszFormat, 
                                     AcHyperlink* pHyperlink, 
                                     ACHAR*& pszFieldCode);
ACFD_PORT BOOL   AcFdMakeFieldCode  (IAcSmDatabase* pSmDb, 
                                     IAcSmSheetSet* pSmSheetSet, 
                                     IAcSmComponent* pSmComp, 
                                     const ACHAR * pszCompName, 
                                     const ACHAR * pszPropName, 
                                     AcFdEval::SheetSetFieldOption nOption,
                                     const ACHAR * pszFormat,
                                     ACHAR*& pszFieldCode);
ACFD_PORT BOOL   AcFdMakeFieldCode  (const AcDbObjectId& tableId, 
                                     const AcDbObjectId& targetTableId, 
                                     AcFdEval::ExpressionFieldOption nOption, 
                                     const AcCellRangeArray& cellRanges,
                                     const ACHAR * pszFormat, 
                                     AcHyperlink* pHyperlink, 
                                     ACHAR*& pszFieldCode);
ACFD_PORT BOOL   AcFdExtractData    (AcDbField* pField, 
                                     ACHAR *& pszSheetSetFile, 
                                     ACHAR *& pszSheetSetId, 
                                     ACHAR *& pszCompName, 
                                     ACHAR *& pszCompId, 
                                     ACHAR *& pszPropName);
ACFD_PORT BOOL   AcFdExtractData    (AcDbField* pField, 
                                     AcDbObjectId& objId, 
                                     ACHAR *& pszPropName);
