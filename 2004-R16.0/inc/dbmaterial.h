
#pragma once
//
// (C) Copyright 2001, 2002 by Autodesk, Inc.
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
#include "acgimaterial.h"

#pragma pack (push, 8)

class AcDbMaterial : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbMaterial);

    AcDbMaterial();
    virtual ~AcDbMaterial();

    // AcDbMaterial protocol
    //
    virtual Acad::ErrorStatus   setName (const char * pName);
    virtual const char*         name    (void) const;

    virtual Acad::ErrorStatus   setDescription(const char * pDescription);
    virtual const char*         description(void) const;

    virtual void setAmbient     (const AcGiMaterialColor & color);
    virtual void ambient        (AcGiMaterialColor & color) const;

    virtual void setDiffuse     (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map);
    virtual void diffuse        (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map) const;

    virtual void setSpecular    (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map,                                
                                 double dGloss);
    virtual void specular       (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map,                                
                                 double & dGloss) const;

    virtual void setReflection  (const AcGiMaterialMap & map);
    virtual void reflection     (AcGiMaterialMap & map) const;

    virtual void setOpacity     (double dPercentage, 
                                 const AcGiMaterialMap & map);
    virtual void opacity        (double & dPercentage, 
                                 AcGiMaterialMap & map) const;

    virtual void setBump        (const AcGiMaterialMap & map);
    virtual void bump           (AcGiMaterialMap & map) const;

    virtual void setRefraction  (double dIndex, 
                                 const AcGiMaterialMap & map);
    virtual void refraction     (double & dIndex, 
                                 AcGiMaterialMap & map) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;
    virtual AcGiDrawable*     drawable     (void);
    virtual void              setGsNode    (AcGsNode* pNode);
    virtual AcGsNode*         gsNode       (void) const;

    // AcGiDrawable protocol
	//
    virtual Adesk::UInt32  setAttributes (AcGiDrawableTraits* pTraits);
};

#pragma pack (pop)


