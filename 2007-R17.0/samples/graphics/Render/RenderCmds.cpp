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
#include "stdafx.h"
#include "RenderCmds.h"
#include "RenderObjects.h"
#include "adscodes.h"

void setRenderSettings(void)
{
	CRenderObjects renderObjs;

	// Set render global parameter object
	renderObjs.setRenderGlobal();
	// Set render environment parameter object
	renderObjs.setRenderEnv();

}

void listRenderSettings()
{
	CRenderObjects renderObjs;

	// List render global parameter object
	renderObjs.listRenderGlobalParams();
	// List render environment parameter object
	renderObjs.listRenderEnvParams();
}

void objectsToRender(void)
{
	CRenderObjects renderObjs;

	// Add a wood material
	renderObjs.addAMaterial();
	// Create a cube and attach the above material to it.
	renderObjs.createACube(AcGeVector3d(100.0, 100.0, 100.0), 100.0);

	// Set the view to a friendly direction.
	acedCommand(RTSTR, _T("_VPOINT"), RTSTR, _T("1,-2,4"), RTNONE);
}

void addLights(void)
{
	CRenderObjects renderObjs;

	// Add a spot light
	renderObjs.addASpotLight();
	// Add a point light
	renderObjs.addAPointLight();
}

void addSunAndBackground(void)
{
	CRenderObjects renderObjs;

	// Add a sun to the active view
	renderObjs.addASun();
	// Add a gradient background object
	renderObjs.addAGradientBackground();
	// Add an image background and set it to the current view.
	renderObjs.addAnImageBackgroundAndSetItToCurrentView();
}

