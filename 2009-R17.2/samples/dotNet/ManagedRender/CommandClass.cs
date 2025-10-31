// (C) Copyright 2006-2007 by Autodesk, Inc. 
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

using System;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Managed_Render;

[assembly: CommandClass(typeof(ClassLibrary.ADSCommandClass))]

namespace ClassLibrary
{
    /// <summary>
    /// Summary description for ADSClass.
    /// </summary>
    public class ADSCommandClass
    {
        public ADSCommandClass()
        {
            //
            // TODO: Add constructor logic here
            //
        }

        [CommandMethod("SetRenderSettings")]
        static public void setRenderSettings()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            try
            {
                // Set render global parameter object
                RenderObjects.setRenderGlobal();
                // Set render environment parameter object
                RenderObjects.setRenderEnv();
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage(ex.Message);
            }
        }

        [CommandMethod("ListRenderSettings")]
        static public void listRenderSettings()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            try
            {
                // List render global parameter object
                RenderObjects.listRenderGlobalParams();
                // List render environment parameter object
                RenderObjects.listRenderEnvParams();
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage(ex.Message);
            }
        }

        [CommandMethod("ObjsToRender")]
        static public void objectsToRender()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            try
            {
                // Add a wood material
                RenderObjects.addAMaterial();
                // Create a cube and attach the above material to it.
                RenderObjects.createACube(new Vector3d(100.0, 100.0, 100.0), 100.0);

                Application.DocumentManager.MdiActiveDocument.SendStringToExecute("_VPOINT 1,-2,4 ", false, false, false);
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage(ex.Message);
            }
        }

        [CommandMethod("AddLights")]
        static public void addLights()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            try
            {
                
                setRenderSettings();
                /// Add a spot light
                RenderObjects.addASpotLight();
                // Add a point light
                RenderObjects.addAPointLight();
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage(ex.Message);
            }
        }

        [CommandMethod("AddSunAndBackground")]
        static public void addSunAndBackground()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            try
            {
                // Add a sun to the active view
                RenderObjects.addASun();
                // Add a gradient background object
                RenderObjects.addAGradientBackground();
                // Add an image background and set it to the current view.
                RenderObjects.addAnImageBackgroundAndSetItToCurrentView();
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage(ex.Message);
            }
        }

    }
}