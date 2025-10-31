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
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.ApplicationServices; 

[assembly: CommandClass(typeof(SurfaceHelix.Class))]

namespace SurfaceHelix
{
    /// <summary>
    /// Summary description for Class.
    /// </summary>
    public class Class : IExtensionApplication
    {
        public Class()
        {
        }

        public void Initialize()
        {
            Editor editor = Application.DocumentManager.MdiActiveDocument.Editor;

            editor.WriteMessage("\nCommands:");

            editor.WriteMessage("\n1.  ADDPLANESURF");
            editor.WriteMessage("\n2.  ADDEXTRUDSURF");
            editor.WriteMessage("\n3.  ADDREVSURF");
            editor.WriteMessage("\n4.  ADDSWEPTSURF");
            editor.WriteMessage("\n5.  ADDLOFTSURF");
            editor.WriteMessage("\n6.  ADDHELIX ");
            editor.WriteMessage("\n7.  ADDALL");
        }

        public void Terminate()
        {
        }

        [CommandMethod("ADDPLANESURF")]
        static public void addPlaneSurface()
        {
            MakeCreation.addPlaneSurface();
        }

        [CommandMethod("ADDEXTRUDSURF")]
        static public void addExtrudedSurface()
        {
            MakeCreation.addExtrudedSurface();
        }

        [CommandMethod("ADDREVSURF")]
        static public void addRevolvedSurface()
        {
            MakeCreation.addRevolvedSurface();
        }

        [CommandMethod("ADDSWEPTSURF")]
        static public void addSweptSurface()
        {
            MakeCreation.addSweptSurface();
        }

        [CommandMethod("ADDLOFTSURF")]
        static public void addLoftedSurface()
        {
            MakeCreation.addLoftedSurface();
        }

        [CommandMethod("ADDHELIX")]
        static public void addHelix()
        {
            MakeCreation.addHelix();
        }

        [CommandMethod("ADDALL")]
        static public void addAll()
        {
            MakeCreation.addPlaneSurface();
            MakeCreation.addExtrudedSurface();
            MakeCreation.addRevolvedSurface();
            MakeCreation.addSweptSurface();
            MakeCreation.addLoftedSurface();
            MakeCreation.addHelix();
        }
    }
}