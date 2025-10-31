//
// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// DRAWENT.CPP
//
// DESCRIPTION: Implementation of the custom draw entity.  Its only
//  purpose is to reside in the database and call shell
//  when its worldDraw method is called.  The shell data
//  is the same as the trapped data.

#include "drawent.h"


ACRX_DXF_DEFINE_MEMBERS(AsdkCustomDrawEntity,AcDbEntity,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
                        0, ASDK_CUSTOM_DRAW_ENTITY,Acgisamp);

AsdkCustomDrawEntity::AsdkCustomDrawEntity()
: mpShellData(NULL) {}

AsdkCustomDrawEntity::~AsdkCustomDrawEntity()
{
	if(mpShellData != NULL)
		delete mpShellData;		
}

AsdkCustomDrawEntity::worldDraw(AcGiWorldDraw*	mode)
{

	if (mpShellData != NULL) {
	mode->geometry().shell( mpShellData->mNumVertices,
							mpShellData->mpVertexList,
							mpShellData->mFaceListSize,
							mpShellData->mpFaceList,
							mpShellData->mpEdgeData,
							mpShellData->mpFaceData,
							mpShellData->mpVertexData);
	}
	return Adesk::kTrue;
}

Acad::ErrorStatus  AsdkCustomDrawEntity::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();

    Acad::ErrorStatus es;

    if ((es = AcDbEntity::dwgInFields(filer)) != Acad::eOk) {
        return es;
    }
	mpShellData = new AsdkShellData;

    filer->readItem(&(mpShellData->mNumVertices));
	mpShellData->mpVertexList = new AcGePoint3d[mpShellData->mNumVertices];
	for (unsigned int i = 0; i < mpShellData->mNumVertices; i++)
		filer->readItem( &(mpShellData->mpVertexList[i]) );	 

	filer->readItem(&(mpShellData->mFaceListSize));
	mpShellData->mpFaceList = new Adesk::Int32[mpShellData->mFaceListSize];
	for (i = 0; i < mpShellData->mFaceListSize; i++)
		filer->readItem( &(mpShellData->mpFaceList[i]) );

	mpShellData->mpFaceData	 = new AcGiFaceData;
		 
	unsigned int numFaces = mpShellData->numberOfFaces();
	short*			pColors = new short[mpShellData->numberOfFaces()];

	for (i = 0; i < numFaces; i++)
		filer->readItem( &(pColors[i]) );	

	mpShellData->mpFaceData->setColors(pColors);

	mpShellData->mpEdgeData = NULL;
	mpShellData->mpVertexData = NULL;

return Acad::eOk;

}

Acad::ErrorStatus  AsdkCustomDrawEntity::dwgOutFields(AcDbDwgFiler* filer) const
{

    assertReadEnabled();

    Acad::ErrorStatus es;

    if ((es = AcDbEntity::dwgOutFields(filer)) != Acad::eOk) {
        return es;
    }

    filer->writeItem(mpShellData->mNumVertices);
	for(unsigned int i = 0; i < mpShellData->mNumVertices; i++)
		filer->writeItem(mpShellData->mpVertexList[i]);

	filer->writeItem(mpShellData->mFaceListSize);
	for(i =0; i < mpShellData->mFaceListSize; i++)
		filer->writeItem(mpShellData->mpFaceList[i]);
				
	unsigned int numFaces = mpShellData->numberOfFaces();
	for(i = 0; i < numFaces; i++)
		filer->writeItem( *(mpShellData->mpFaceData->colors()+i) );	

	return Acad::eOk;
}
