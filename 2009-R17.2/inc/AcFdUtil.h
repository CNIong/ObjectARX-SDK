//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2003-2007  by Autodesk, Inc.
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
// Name:            AcFdUtil.h
//
// Description:     Header for global methods exported from AcFdEval 
//                  module
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"
#include "AcCell.h"

interface IAcSmDatabase;
interface IAcSmSheetSet;
interface IAcSmComponent;
struct AcHyperlink;


#ifdef  ACFD_API
    # define ACFD_PORT __declspec(dllexport)
#else
    # define ACFD_PORT
#endif


// From dbeval.h
typedef unsigned long AcDbEvalNodeId;

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

