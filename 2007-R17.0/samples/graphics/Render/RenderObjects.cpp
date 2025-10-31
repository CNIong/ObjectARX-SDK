//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"
#include "RenderObjects.h"

CRenderObjects::CRenderObjects(void):
pDb(acdbHostApplicationServices()->workingDatabase())
{
}

CRenderObjects::~CRenderObjects(void)
{
}


//////////////////////////////////////////////////////////////////////

using namespace RenderAPISample;

const TCHAR* nameWood = _T("Wood1");

Acad::ErrorStatus CRenderObjects::addASpotLight()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbLight* pLight = new AcDbLight();
	assert(pLight);
	AcCmColor color;
	color.setRGB(0, 255, 0);
	es = pLight->setLightType(AcGiDrawable::kSpotLight);
	assert(es==Acad::eOk);
	es = pLight->setLightColor(color);
	assert(es==Acad::eOk);

	es = pLight->setLightDirection(AcGeVector3d(1,1,1));
	assert(es==Acad::eOk);
	es = pLight->setHotspotAndFalloff(100, 50);
	assert(es==Acad::eOk);
	es = pLight->setIntensity(100);
	assert(es==Acad::eOk);

	// Make sure both of attenuation type of limits are disabled.
	AcGiLightAttenuation lgtAtten;
	lgtAtten.setAttenuationType(AcGiLightAttenuation::kNone);
	lgtAtten.setUseLimits(false);

	pLight->setLightAttenuation(lgtAtten);

	es = pLight->setIsPlottable(true);
	assert(es==Acad::eOk);
	AcString lgtName(_T("MySpotLight"));
	es = pLight->setName(lgtName);
	assert(es==Acad::eOk);
	es = pLight->setOn(true);
	assert(es==Acad::eOk);
	es = pLight->setPosition(AcGePoint3d(0,0,0));
	assert(es==Acad::eOk);
	es = pLight->setTargetLocation(AcGePoint3d(100,100,100));
	assert(es==Acad::eOk);
	AcGiShadowParameters shadowPar;
	shadowPar.setShadowMapSize(128);
	shadowPar.setShadowMapSoftness(54);
	shadowPar.setShadowsOn(true);
	shadowPar.setShadowType(AcGiShadowParameters::kShadowMaps);
	pLight->setShadowParameters(shadowPar);

	es = postEntToCurrentSpace(pDb, pLight);
	if( Acad::eOk != es )
	{
		delete pLight;
		return es;
	}

	return Acad::eOk;
}

Acad::ErrorStatus CRenderObjects::addAPointLight()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbLight* pLight = new AcDbLight();
	assert(pLight);
	AcCmColor color;
	color.setRGB(0, 0, 128);
	es = pLight->setLightType(AcGiDrawable::kPointLight);
	assert(es==Acad::eOk);
	es = pLight->setLightColor(color);
	assert(es==Acad::eOk);

	es = pLight->setIntensity(5000);
	assert(es==Acad::eOk);

	// Make sure both of attenuation type of limits are disabled.
	AcGiLightAttenuation lgtAtten;
	lgtAtten.setAttenuationType(AcGiLightAttenuation::kNone);
	lgtAtten.setUseLimits(false);
	pLight->setLightAttenuation(lgtAtten);

	AcString lgtName(_T("MyPointLight"));
	es = pLight->setName(lgtName);
	assert(es==Acad::eOk);
	es = pLight->setOn(true);
	assert(es==Acad::eOk);
	es = pLight->setPosition(AcGePoint3d(300,0,300));
	assert(es==Acad::eOk);

	es = postEntToCurrentSpace(pDb, pLight);
	if( Acad::eOk != es )
	{
		delete pLight;
		return es;
	}

	return Acad::eOk;
}

Acad::ErrorStatus CRenderObjects::addASun()
{
	Acad::ErrorStatus es = Acad::eOk;
	AcDbSun* pSun = new AcDbSun(); 
	assert(pSun);

	AcDbDate date;
	date.setDate(11, 21, 2005);
	date.setTime(23, 23, 23, 23);
	pSun->setDateTime(date);
	es = pSun->setDayLightSavingsOn(true);
	assert(es==Acad::eOk);
	es = pSun->setIntensity(1000);
	assert(es==Acad::eOk);
	es = pSun->setOn(true);
	assert(es==Acad::eOk);
	AcCmColor color;
	color.setRGB(255, 0, 0);
	es = pSun->setSunColor(color);
	assert(es==Acad::eOk);
	AcGiShadowParameters shadowPar;
	shadowPar.setShadowMapSize(128);
	shadowPar.setShadowMapSoftness(54);
	shadowPar.setShadowsOn(true);
	shadowPar.setShadowType(AcGiShadowParameters::kShadowMaps);
	pSun->setShadowParameters(shadowPar);

	AcDbObjectId sunId;

	RenderAPISample::ViewType vt;
	AcDbObjectId curViewId = currentViewId(pDb, vt);

	if( vt == RenderAPISample::ModelSpaceView )
	{
		AcDbObjectPointer<AcDbViewportTableRecord> pVTR(curViewId, AcDb::kForWrite); 
		if(pVTR.openStatus()==Acad::eOk) 
		{ 
			if(pVTR->setSun(sunId, pSun)!=Acad::eOk)
			{
				delete pSun;
				acutPrintf(_T("\nFailed to add a sun to the current VIEW!"));
			}
			else
				pSun->close();
		} 
		else
			delete pSun;
	}
	else if( vt == RenderAPISample::PaperSpaceView )
	{
		AcDbObjectPointer<AcDbViewport> pV(curViewId, AcDb::kForWrite); 
		if(pV.openStatus()==Acad::eOk) 
		{ 
			if(pV->setSun(sunId, pSun)!=Acad::eOk)
			{
				delete pSun;
				acutPrintf(_T("\nFailed to add a sun to the current VIEW!"));
			}
			else
				pSun->close();
		} 
		else
			delete pSun;
	}
	else
		delete pSun;

	return es;
}


Acad::ErrorStatus CRenderObjects::addAGradientBackground()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbGradientBackground* pGrdBckgrd = new AcDbGradientBackground(); 
	assert(pGrdBckgrd);

	AcCmEntityColor red;
	red.setRGB(64, 0, 0);
	AcCmEntityColor green;
	green.setRGB(0, 192, 0);
	AcCmEntityColor blue;
	blue.setRGB(0, 0, 128);

	pGrdBckgrd->setColorTop(blue);
	pGrdBckgrd->setColorMiddle(green);
	pGrdBckgrd->setColorBottom(red);
	pGrdBckgrd->setRotation(atan(1.0)*30.0/45.0);

	es = addAnEntryToADict(pDb, _T("ACAD_BACKGROUND"), _T("MYBACKGROUND1"), pGrdBckgrd);
	if(Acad::eOk!=es)
		delete pGrdBckgrd;
	else
	{

		pGrdBckgrd->close();
	}

	return es;
}

Acad::ErrorStatus CRenderObjects::addAnImageBackgroundAndSetItToCurrentView()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbImageBackground* pImgBckgrd = new AcDbImageBackground(); 
	assert(pImgBckgrd);

	AcCmEntityColor red;
	red.setRGB(64, 0, 0);
	AcCmEntityColor green;
	green.setRGB(0, 192, 0);
	AcCmEntityColor blue;
	blue.setRGB(0, 0, 128);

	pImgBckgrd->setImageFilename(_T("C:\\temp\\background.jpg"));
	pImgBckgrd->setFitToScreen(true);

	AcDbObjectId bkgId;
	es = addAnEntryToADict(pDb, _T("ACAD_BACKGROUND"), _T("MYBACKGROUND2"), pImgBckgrd);
	if(Acad::eOk!=es)
		delete pImgBckgrd;
	else
	{
		bkgId = pImgBckgrd->objectId();
		pImgBckgrd->close();
	}

	RenderAPISample::ViewType vt;
	AcDbObjectId curViewId = currentViewId(pDb, vt);

	if( vt == RenderAPISample::ModelSpaceView )
	{
		AcDbObjectPointer<AcDbViewportTableRecord> pVTR(curViewId, AcDb::kForWrite); 
		if(pVTR.openStatus()==Acad::eOk) 
		{ 
			if(pVTR->setBackground(bkgId) !=Acad::eOk)
			{
				acutPrintf(_T("\nFailed to set the background to the current VIEW!"));
			}
		} 
	}
	else if( vt == RenderAPISample::PaperSpaceView )
	{
		AcDbObjectPointer<AcDbViewport> pV(curViewId, AcDb::kForWrite); 
		if(pV.openStatus()==Acad::eOk) 
		{ 
			if(pV->setBackground(bkgId)!=Acad::eOk)
			{
				acutPrintf(_T("\nFailed to set the background to the current VIEW!"));
			}
		}
	}

	return es;
}

Acad::ErrorStatus CRenderObjects::setRenderGlobal()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbRenderGlobal* pRenderGlobal = NULL;

	es = renderEnvironmentOrGlobalObj(pDb, AcDbRenderGlobal::desc(), (AcDbObject*&)pRenderGlobal);
	if(es != Acad::eOk || !pRenderGlobal)
		return es;

	es = pRenderGlobal->upgradeOpen();
	assert(es == Acad::eOk);
	es = pRenderGlobal->setDimensions(1000, 800);
	assert(es == Acad::eOk);
	pRenderGlobal->setSaveEnabled(true);
	es = pRenderGlobal->setSaveFileName(_T("C:\\temp\\myrender.png"));
	assert(es == Acad::eOk);
	es = pRenderGlobal->downgradeOpen();
	assert(es == Acad::eOk);

	es = pRenderGlobal->close();
	assert(es == Acad::eOk);

	return es;
}

Acad::ErrorStatus CRenderObjects::setRenderEnv() // mostly fog parameters
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbRenderEnvironment* pEnv = NULL;

	es = renderEnvironmentOrGlobalObj(pDb, AcDbRenderEnvironment::desc(), (AcDbObject*&)pEnv);
	if(es != Acad::eOk || !pEnv)
		return es;

	es = pEnv->upgradeOpen();
	assert(es == Acad::eOk);

	AcCmEntityColor fogColor;
	fogColor.setRGB(64, 128, 255);

	pEnv->setFogEnabled(true);
	pEnv->setFogColor(fogColor);
	pEnv->setFogBackgroundEnabled(true);
	es = pEnv->setDistances(0.0, 88.8);
	assert(es==Acad::eOk);
	es = pEnv->setFogDensity(22.2, 66.6);
	assert(es==Acad::eOk);

	es = pEnv->downgradeOpen();
	assert(es==Acad::eOk);
	es = pEnv->close();
	assert(es==Acad::eOk);

	return es;
}

Acad::ErrorStatus CRenderObjects::listRenderGlobalParams()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbRenderGlobal* pRenderGlobal = NULL;

	es = renderEnvironmentOrGlobalObj(pDb, AcDbRenderGlobal::desc(), (AcDbObject*&)pRenderGlobal);
	if(es != Acad::eOk || !pRenderGlobal)
		return es;

	int w, h;
	pRenderGlobal->dimensions(w, h);
	acutPrintf(_T("\n\nRender global settings:"));
	acutPrintf(_T("\nImage width: %d\t\theight: %d"), w, h);
	bool b = pRenderGlobal->saveEnabled();
	if(b)
		acutPrintf(_T("\nSave enabled: true"));
	else
		acutPrintf(_T("\nSave enabled: false"));
	acutPrintf(_T("\nSavefile name: %s"), pRenderGlobal->saveFileName().constPtr());

	es = pRenderGlobal->close();

	return es;
}

Acad::ErrorStatus CRenderObjects::listRenderEnvParams()
{
	Acad::ErrorStatus es=Acad::eOk;
	AcDbRenderEnvironment* pRenderEnv = NULL;

	es = renderEnvironmentOrGlobalObj(pDb, AcDbRenderEnvironment::desc(), (AcDbObject*&)pRenderEnv);
	if(es != Acad::eOk || !pRenderEnv)
		return es;

	acutPrintf(_T("\n\nRender environment settings:"));
	acutPrintf(_T("\nFog enabled: %d"), pRenderEnv->fogEnabled() );
	AcCmEntityColor fogColor;
	fogColor = pRenderEnv->fogColor();
	acutPrintf(_T("\nFog color: %d,%d,%d"), fogColor.red(), fogColor.green(), fogColor.blue());
	double dNear, dFar;
	pRenderEnv->fogDensity(dNear, dFar);
	acutPrintf(_T("\nFog density: near(%f)  far(%f)"), dNear, dFar);
	double distNear, distFar;
	pRenderEnv->distances(distNear, distFar);
	acutPrintf(_T("\nFog distances: near(%f)  far(%f)"), distNear, distFar);
	es = pRenderEnv->close();

	return es;
}

// Create a wood material
AcDbObjectId CRenderObjects::addAMaterial()
{
	AcDbDictionary *pMaterialDict;
	Acad::ErrorStatus es=Acad::eOk;
	AcDbObjectId matId;

	es = pDb->getMaterialDictionary(pMaterialDict, AcDb::kForWrite);
	if ( es == Acad::eOk)
	{
		AcDbMaterial *pMaterial = new AcDbMaterial();
		assert(pMaterial);
		es = pMaterial->setName(nameWood);
		assert(es==Acad::eOk);

		// Diffuse texture
		AcGiMaterialMap map;
		map.setSource(AcGiMaterialMap::kProcedural);

		AcGiWoodTexture* pTexture = new AcGiWoodTexture();
		assert(pTexture);

		AcGiMaterialColor matColor, woodColor1, woodColor2;
		AcCmEntityColor entColor;

		matColor.setMethod(AcGiMaterialColor::kOverride);
		matColor.setFactor(1.0);
		entColor.setRGB(128,0, 128);
		matColor.setColor(entColor);

		woodColor1.setMethod(AcGiMaterialColor::kOverride);
		woodColor1.setFactor(1.0);
		entColor.setRGB(128,128, 0);
		woodColor1.setColor(entColor);

		woodColor2.setMethod(AcGiMaterialColor::kOverride);
		woodColor2.setFactor(1.0);
		entColor.setRGB(0,128, 128);
		woodColor2.setColor(entColor);

		pTexture->setColor1(woodColor1);
		pTexture->setColor2(woodColor2);
		map.setTexture(pTexture);
		delete pTexture;

		pMaterial->setDiffuse(matColor, map);

		// Ambient and specular color
		AcGiMaterialColor inheritColor;
		matColor.setFactor(1.0);
		pMaterial->setAmbient(matColor);
		pMaterial->setSpecular(matColor, AcGiMaterialMap(), 0.5);
		
		es = pMaterial->setMode(AcGiMaterialTraits::kRealistic);
		if( es != Acad::eOk )
			delete pMaterial;

		// Add material to dictionary
		es = pMaterialDict->setAt(nameWood, pMaterial, matId);
		if( es != Acad::eOk )
			delete pMaterial;

		// Close the material and dictionary
		pMaterial->close();
		pMaterialDict->close();
	}

	return matId;
}

// Create a cube
AcDbObjectId CRenderObjects::createACube(AcGeVector3d location, double length)
{
	assert(pDb);

	AcDbObjectId id; 
	id.setNull();
	Acad::ErrorStatus es;

	AcDb3dSolid* pSolid = new AcDb3dSolid(); 
	assert(pSolid);

	es = pSolid->createBox(length, length, length);  
	if(es != Acad::eOk)
	{
		acutPrintf(_T("\nError in creating a box."));   
		delete pSolid;
		return id;
	}

	AcGeMatrix3d mat;  
	mat.setToIdentity();  
	mat.setTranslation(location);  
	es = pSolid->transformBy(mat); 
	if(es != Acad::eOk)
	{
		delete pSolid;
		return id;
	}

	es = addEntToCurrentSpace(pDb, pSolid);
	if( Acad::eOk != es )
	{
		acutPrintf(_T("\nError in adding the solid to database."));    
		delete pSolid;  
		return id;
	}

	// Set a material to the cube
	es = pSolid->setMaterial(nameWood);
	if(es != Acad::eOk)    
	{
		acutPrintf(_T("\nError in setting material to the solid."));    
	}

	es = pSolid->close();
	assert(es == Acad::eOk);

	return id;
}

