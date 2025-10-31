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
    class Utilities
    {
        public enum ViewType
        {
            NoCurrentView = 0,
            ModelSpaceView,
            PaperSpaceView
        };

        // Get the current Viewport and information weather it is model space viewport or paper space viewport
        public static ObjectId currentViewId(ref Database db, out Utilities.ViewType vt)
        {
            ObjectId objId = ObjectId.Null;
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
             
            using(Transaction trans = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction())
            {
                if (!db.TileMode)
                {
                    objId = ed.CurrentViewportObjectId;
                    try
                    {
                        Autodesk.AutoCAD.DatabaseServices.Viewport obj = (Autodesk.AutoCAD.DatabaseServices.Viewport)trans.GetObject(objId, OpenMode.ForRead);
                        if(obj.Number == 1)
                            vt = ViewType.NoCurrentView;
                        else
                            vt = ViewType.PaperSpaceView;
                    }
                    catch
                    {
                        vt = ViewType.NoCurrentView;
                    }

                }
                else
                {
                    ed.UpdateTiledViewportsInDatabase();
                    ViewportTable vptbl = (ViewportTable)trans.GetObject(db.ViewportTableId, OpenMode.ForRead);
                    objId = vptbl["*Active"];
                    vt = ViewType.ModelSpaceView;
                }
                trans.Commit();
            }

            return objId;
        }

        // Utility to add an object to a dictionary in the named object dictionary
        public static void addAnEntryToADict(ref Database db, string dictName, string entryName, DBObject pObj, out ObjectId dictId, out ObjectId objId)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

            using(Transaction trans = db.TransactionManager.StartTransaction())
            {
                DBDictionary nodDict = (DBDictionary)trans.GetObject(db.NamedObjectsDictionaryId, OpenMode.ForWrite);
                DBDictionary dictObj;
                dictId = ObjectId.Null;
                objId = ObjectId.Null;
                try
                {
                    dictId = nodDict.GetAt(dictName);
                    dictObj = (DBDictionary)trans.GetObject(dictId, OpenMode.ForWrite);
                }
                catch
                {
                    dictObj = new DBDictionary();
                    dictId = nodDict.SetAt(dictName, dictObj);
                    trans.AddNewlyCreatedDBObject(dictObj, true);
                }
                try
                {
                    objId = dictObj.GetAt(entryName);
                    dictObj.Remove(entryName);
                }
                catch
                {
                }

                objId = dictObj.SetAt(entryName, pObj);
                trans.AddNewlyCreatedDBObject(pObj, true);
                trans.Commit();
            }
        }

        // Utility to add an object to a dictionary in the named object dictionary
        public static void addAnEntryToADict(ref Database pDb, string dictName, string entryName, DBObject pObj)
	    {
		    ObjectId dictId, objId;
		    addAnEntryToADict(ref pDb, dictName, entryName, pObj, out dictId, out objId);
	    }

        // Get the ObjectID of the Render dictionary objecs
        public static ObjectId renderEnvironmentOrGlobalObj(ref Database db, bool renderEnv)
        {
            ObjectId renderId = ObjectId.Null;
            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                DBDictionary nodDict = (DBDictionary)trans.GetObject(db.NamedObjectsDictionaryId, OpenMode.ForRead);
                if (renderEnv)
                    try
                    {
                        renderId = nodDict.GetAt("ACAD_RENDER_ENVIRONMENT");
                    }
                    catch (Autodesk.AutoCAD.Runtime.Exception)
                    {
                        // By default these dictionaries don't exist in the NOD.  If they are not present
                        // we can add default values manually here.
                        RenderEnvironment Env = new RenderEnvironment();
                        nodDict.UpgradeOpen();
                        renderId = nodDict.SetAt("ACAD_RENDER_ENVIRONMENT", Env);
                        trans.AddNewlyCreatedDBObject(Env, true);
                    }
                else
                    try
                    {
                        renderId = nodDict.GetAt("ACAD_RENDER_GLOBAL");
                    }
                    catch (Autodesk.AutoCAD.Runtime.Exception)
                    {
                        // By default these dictionaries don't exist in the NOD.  If they are not present
                        // we can add default values manually here.
                        RenderGlobal Glob = new RenderGlobal();
                        nodDict.UpgradeOpen();
                        renderId = nodDict.SetAt("ACAD_RENDER_GLOBAL", Glob);
                        trans.AddNewlyCreatedDBObject(Glob, true);
                    }
                trans.Commit();
            }
            return renderId;
        }
    }
}
