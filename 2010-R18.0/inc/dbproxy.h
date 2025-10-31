#ifndef AD_DBPROXY_H
#define AD_DBPROXY_H 1
//
// (C) Copyright 1996-2009 by Autodesk, Inc.
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

#include "dbmain.h"
#include <dbintar.h>

#pragma pack (push, 8)

class ADESK_NO_VTABLE AcDbProxyObject : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbProxyObject);
    
    virtual ~AcDbProxyObject() {};
    
    virtual int   proxyFlags() const = 0;
    virtual const ACHAR * originalClassName() const = 0;
    virtual const ACHAR * originalDxfName() const = 0;
    virtual const ACHAR * applicationDescription() const = 0;
    virtual Acad::ErrorStatus getReferences(AcDbObjectIdArray&,
        AcDbIntArray&) const = 0;

    virtual AcDb::DuplicateRecordCloning mergeStyle() const = 0;

    enum {kNoOperation          = 0,
          kEraseAllowed         = 0x01,
          kCloningAllowed       = 0x80,
          kAllButCloningAllowed = 0x01,
          kAllAllowedBits       = 0x81,
          kMergeIgnore          = 0,      // Keep existing (= default)
          kMergeReplace         = 0x100,  // Use clone
          kMergeMangleName      = 0x200,  // anonymous name
          kDisableProxyWarning  = 0x400
           };
};

class ADESK_NO_VTABLE AcDbProxyEntity : public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbProxyEntity);
    
    virtual ~AcDbProxyEntity() {};
    
    virtual int   proxyFlags() const = 0;
    virtual const ACHAR * originalClassName() const = 0;
    virtual const ACHAR * originalDxfName() const = 0;
    virtual const ACHAR * applicationDescription() const = 0;
    virtual Acad::ErrorStatus getReferences(AcDbObjectIdArray&,
        AcDbIntArray&) const = 0;

    enum GraphicsMetafileType {
        kNoMetafile   = 0,
        kBoundingBox  = 1,
        kFullGraphics = 2 };

    virtual AcDbProxyEntity::GraphicsMetafileType graphicsMetafileType()
        const = 0;


    enum  {kNoOperation                = 0,
           kEraseAllowed               = 0x1,
           kTransformAllowed           = 0x2,
           kColorChangeAllowed         = 0x4,
           kLayerChangeAllowed         = 0x8,
           kLinetypeChangeAllowed      = 0x10,
           kLinetypeScaleChangeAllowed = 0x20,
           kVisibilityChangeAllowed    = 0x40,
           kCloningAllowed             = 0x80,
           kLineWeightChangeAllowed    = 0x100,
           kPlotStyleNameChangeAllowed = 0x200,
           kAllButCloningAllowed       = 0x37F,
           kAllAllowedBits             = 0xBFF,
           kDisableProxyWarning        = 0x400,
           kMaterialChangeAllowed      = 0x800,
            };

};

#pragma pack (pop)

#endif // AD_DBPROXY_H
