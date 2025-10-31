#ifndef AC_BRELEM_H
#define AC_BRELEM_H 1
// (C) Copyright 1997-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
// The AcBrElement class is the interface base class for mesh elements.
// All the functionality supported by this class is implemented by the
// class AcBrImpElement.
//
// This class defines the functions that are common to all dimensions
// of mesh elements, and cannot be directly set by the user as the
// initialisation requirements are only available internally at the
// time of a call to AcBrMesh::generate().
//
// An element is a minimal closed, ordered subset of connected nodes 
// in a mesh.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brment.h"


// forward class declarations
class AcBrMeshEntity;


class AcBrElement : public AcBrMeshEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrElement);
    virtual ~AcBrElement();
    
protected:
    AcBrElement();
    AcBrElement(const AcBrElement& src);
    AcBrElement&		operator =      (const AcBrElement& src);
};


#endif

