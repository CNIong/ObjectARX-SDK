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
using System.Collections.Generic;
using System.Text;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.Colors;
using Autodesk.AutoCAD.GraphicsInterface;

namespace Managed_Render
{
    class RenderObjects
    {
        public static string nameWood = "Wood1";

        // Code to add a spot light.
        static public void addASpotLight()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            
            using(Transaction trans = db.TransactionManager.StartTransaction())
            {
                // Create a light object and set its properties
                Light light = new Light();
                light.SetDatabaseDefaults();
                Color color = Color.FromRgb(0, 255, 0);
                light.LightType = Autodesk.AutoCAD.GraphicsInterface.DrawableType.SpotLight;
                light.LightColor = color;
                light.Direction = new Vector3d(1, 1, 1);
                light.SetHotspotAndFalloff(100, 50);
                light.Intensity = 100;

                // Create a Light Attenuation object and add it to the light object
                LightAttenuation lightAtten = new LightAttenuation();
                lightAtten.AttenuationType = AttenuationType.None;
                lightAtten.UseLimits = false;

                light.Attenuation = lightAtten;
                light.IsPlottable = true;
                light.Name = "MySpotLight";
                light.IsOn = true;
                light.Position = new Point3d(0, 0, 0);
                light.TargetLocation = new Point3d(100, 100, 100);

                // Create a Shadow Parameters object and add it to the light object
                ShadowParameters shadowPar = new ShadowParameters();

                shadowPar.ShadowMapSize = 128;
                shadowPar.ShadowMapSoftness = 9;
                shadowPar.ShadowsOn = true;
                shadowPar.ShadowType = ShadowType.Maps;

                light.Shadow = shadowPar;

                // Add the light to the current space
                BlockTableRecord curSpc = (BlockTableRecord)trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite);
                curSpc.AppendEntity(light);
                trans.AddNewlyCreatedDBObject(light, true);

                trans.Commit();
            }
        }

        // Code to add point light
        static public void addAPointLight()
        {
            Database db = HostApplicationServices.WorkingDatabase;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                // Create a light object and set its properties
                Light light = new Light();
                light.SetDatabaseDefaults();
                Color color = Color.FromRgb(0, 0, 128);
                light.LightType = Autodesk.AutoCAD.GraphicsInterface.DrawableType.PointLight;
                light.LightColor = color;
                light.Intensity = 5000;

                // Create a Light Attenuation object and add it to the light object
                LightAttenuation lightAtten = new LightAttenuation();
                lightAtten.AttenuationType = AttenuationType.None;
                lightAtten.UseLimits = false;

                light.Attenuation = lightAtten;
                light.Name = "MyPointLight";
                light.IsOn = true;
                light.Position = new Point3d(0, 0, 0);

                // Add the light to the current space
                BlockTableRecord curSpc = (BlockTableRecord)trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite);
                curSpc.AppendEntity(light);
                trans.AddNewlyCreatedDBObject(light, true);

                trans.Commit();
            }
        }

        // Code to add a sun object
        static public void addASun()
        {
            Database db = HostApplicationServices.WorkingDatabase;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                // Create a Sun object and set its parameters
                Sun sun = new Sun();

                DateTime dateTm = new DateTime(2006, 11, 21, 23, 23, 23, 23);
                sun.DateTime = dateTm;

                sun.IsDaylightSavingsOn =true;
	        	sun.Intensity = 1000;
	            sun.IsOn = true;
	            Color color = Color.FromRgb(255, 0, 0);
	            sun.SunColor = color;
	            
                // Create a Shadow parameters object and set its parameters. Later set it to the Sun object.
	            ShadowParameters shadowPar = new ShadowParameters();
	            shadowPar.ShadowMapSize = 128;
	            shadowPar.ShadowMapSoftness = 10;
	            shadowPar.ShadowsOn = true;
                shadowPar.ShadowType = ShadowType.Maps;
	            sun.ShadowParameters = shadowPar;

                // Get the current viewport and add the sun to the current viewport
                Utilities.ViewType vt;
                ObjectId objId = Utilities.currentViewId(ref db, out vt);
                if (Utilities.ViewType.ModelSpaceView == vt)
                {
                    ViewportTableRecord vprtTblRcd = (ViewportTableRecord)trans.GetObject(objId, OpenMode.ForWrite);
                    vprtTblRcd.SetSun(sun);
                    trans.AddNewlyCreatedDBObject(sun, true);
                }
                else if (Utilities.ViewType.PaperSpaceView == vt)
                {
                    Autodesk.AutoCAD.DatabaseServices.Viewport vprt = (Autodesk.AutoCAD.DatabaseServices.Viewport)trans.GetObject(objId, OpenMode.ForWrite);
                    vprt.SetSun(sun);
                    trans.AddNewlyCreatedDBObject(sun, true);
                }
                trans.Commit();
            }

        }

        // Create a gradient background
        public static void addAGradientBackground()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            
            using(Transaction trans = db.TransactionManager.StartTransaction())
            {
                GradientBackground gradBack = new GradientBackground();

                Color red = new Color();
                red = Color.FromRgb(64, 0, 0);
                Color green = new Color();
                green = Color.FromRgb(0, 192, 0);
                Color blue = new Color();
                blue = Color.FromRgb(0, 0, 128);

                gradBack.ColorTop = blue.EntityColor;
                gradBack.ColorMiddle = green.EntityColor;
                gradBack.ColorBottom = red.EntityColor;
                gradBack.Rotation = System.Math.Atan(1.0) * 30.0 / 45.0;

                Utilities.addAnEntryToADict(ref db, "ACAD_BACKGROUND", "MYBACKGROUND1", gradBack);

                trans.Commit();
            }
        }

        // Create an image background and set it to the current view
        public static void addAnImageBackgroundAndSetItToCurrentView()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using(Transaction trans = db.TransactionManager.StartTransaction())
            {
                ImageBackground imgBck = new ImageBackground();

                Color red = new Color();
                red = Color.FromRgb(64, 0, 0);
                Color green = new Color();
                green = Color.FromRgb(0, 192, 0);
                Color blue = new Color();
                blue = Color.FromRgb(0, 0, 128);

                imgBck.ImageFileName = "C:\\temp\\background.jpg"; // Make sure a JPG file is available here. 
                                                                   // Else the code will not work properly.
                imgBck.FitToScreen = true;
                ObjectId dictId, entId;
                Utilities.addAnEntryToADict(ref db, "ACAD_BACKGROUND", "MYBACKGROUND2", imgBck, out dictId, out entId);

                // Add the image background to the current viewport
                Utilities.ViewType vt;
                ObjectId viewId = Utilities.currentViewId(ref db, out vt);

                if (Utilities.ViewType.ModelSpaceView == vt)
                {
                    ViewportTableRecord vprtTblRcd = (ViewportTableRecord)trans.GetObject(viewId, OpenMode.ForWrite);
                    vprtTblRcd.Background = entId;
                }
                else if (Utilities.ViewType.PaperSpaceView == vt)
                {
                    Autodesk.AutoCAD.DatabaseServices.Viewport vprt = (Autodesk.AutoCAD.DatabaseServices.Viewport)trans.GetObject(viewId, OpenMode.ForWrite);
                    vprt.Background = entId;
                }

                trans.Commit();

            }

        }

        public static void setRenderGlobal()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using(Transaction trans = db.TransactionManager.StartTransaction())
            {
                RenderGlobal renderGlob = (RenderGlobal)trans.GetObject(Utilities.renderEnvironmentOrGlobalObj(ref db, false), OpenMode.ForWrite);
                renderGlob.Dimensions = new RenderGlobal.DimensionsParameter(1000, 800);
                renderGlob.SaveEnabled = true;
                renderGlob.SaveFileName = "C:\\temp\\myrender.png";
                trans.Commit();
            }
        }

        public static void setRenderEnv()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                RenderEnvironment renderEnv = (RenderEnvironment)trans.GetObject(Utilities.renderEnvironmentOrGlobalObj(ref db, true), OpenMode.ForWrite);
                EntityColor fogColor = new EntityColor(64, 128, 255);
                renderEnv.FogEnabled = true;
                renderEnv.FogColor = fogColor;
                renderEnv.FogBackgroundEnabled = true;
                renderEnv.Distances = new RenderEnvironment.DoubleRangeParameter(0.0,88.8);
                renderEnv.FogDensity = new RenderEnvironment.DoubleRangeParameter(22.2, 66.6);
                trans.Commit();
            }
        }

        // List the current settings of the RenderGlobal object
        public static void listRenderGlobalParams()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                RenderGlobal renderGlob = (RenderGlobal)trans.GetObject(Utilities.renderEnvironmentOrGlobalObj(ref db, false), OpenMode.ForRead);
                RenderGlobal.DimensionsParameter dimParam = renderGlob.Dimensions;
                bool savEnbld = renderGlob.SaveEnabled;
                String saveFileName = renderGlob.SaveFileName;
                ed.WriteMessage("\n\nRender Global Settings:");
                ed.WriteMessage("\nImage Width: {0}, Height: {1}", dimParam.Width, dimParam.Height);
                ed.WriteMessage("\nSave Enabled: " + savEnbld.ToString());
                ed.WriteMessage("\nSavefile Name: " + saveFileName);
                trans.Commit();
            }
        }

        // List the current settings of the RenderEnvironment object
        public static void listRenderEnvParams()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                RenderEnvironment renderEnv = (RenderEnvironment)trans.GetObject(Utilities.renderEnvironmentOrGlobalObj(ref db, true), OpenMode.ForRead);
                bool fogEnbld = renderEnv.FogEnabled;
                EntityColor fogColor = renderEnv.FogColor;
                bool fogBckEnbld = renderEnv.FogBackgroundEnabled;
                RenderEnvironment.DoubleRangeParameter dist = renderEnv.Distances;
                RenderEnvironment.DoubleRangeParameter fogDens = renderEnv.FogDensity;

                ed.WriteMessage("\n\nRender Environment Settings:");
                ed.WriteMessage("\nFog Enabled: " + fogEnbld.ToString());
                ed.WriteMessage("\nFog color: {0}, {1}, {2}", fogColor.Red, fogColor.Green, fogColor.Blue);
                ed.WriteMessage("\nFog density: near({0})  far({1})", fogDens.Near,fogDens.Far);
                ed.WriteMessage("\nFog distances: near({0})  far({1})", dist.Near, dist.Far);

                trans.Commit();
            }
        }

        // Create a material called "Wood1"
        public static void addAMaterial()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                DBDictionary matDict = (DBDictionary)trans.GetObject(db.MaterialDictionaryId, OpenMode.ForWrite);
                Material mat = new Material();
                mat.Name = nameWood;

                // Create a Texture
                WoodTexture wdTexture = new WoodTexture();

                MaterialColor matColor, woodColor1, woodColor2;
                EntityColor entColor = new EntityColor(128,0, 128);
                matColor = new MaterialColor(Method.Override, 1.0, entColor);
                woodColor1 = new MaterialColor(Method.Override, 1.0, new EntityColor(128, 128, 0));
                woodColor2 = new MaterialColor(Method.Override, 1.0, new EntityColor(0, 128, 128));
                wdTexture.Color1 = woodColor1;
                wdTexture.Color2 = woodColor2;

                // Create Material Map using the texture and add it as diffuse component
                MaterialMap matMap = new MaterialMap(Source.Procedural, wdTexture, 0.5, null);
                mat.Diffuse = new MaterialDiffuseComponent(matColor, matMap);
                mat.Ambient = matColor;
                mat.Specular = new MaterialSpecularComponent(matColor, new MaterialMap(), 0.5);
                mat.Mode = Mode.Realistic;

                // Add material to the material dictionary
                matDict.SetAt(nameWood, mat);
                trans.AddNewlyCreatedDBObject(mat, true);
                trans.Commit();
            }
        }

        // Create a Box Solid entity that uses the "Wood1" material
        public static void createACube(Vector3d location, Double length)
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                Solid3d sol = new Solid3d();
                sol.CreateBox(length, length, length);

                Matrix3d mat;
                mat = Matrix3d.Identity;
                mat = Matrix3d.Displacement(location);
                sol.TransformBy(mat);
                BlockTableRecord curSpc = (BlockTableRecord)trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite);
                curSpc.AppendEntity(sol);
                trans.AddNewlyCreatedDBObject(sol, true);
                sol.Material = nameWood;
                trans.Commit();
            }
            
        }
    }
}
