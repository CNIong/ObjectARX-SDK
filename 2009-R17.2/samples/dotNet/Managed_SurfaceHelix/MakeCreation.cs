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
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.Colors;

namespace SurfaceHelix
{
    class MakeCreation
    {
        static public void addPlaneSurface()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                // Add plane surfaces
                // In-memory circle is used to form the base of a bowl on a spring (Helix)on the table.		
                Circle circle = new Circle(new Point3d(10.0, 3.0, 12.5), Vector3d.ZAxis, 1.0);

                // In-memory polyline is used to form a floor surface
                Polyline polyline = new Polyline();
                polyline.SetDatabaseDefaults();
                polyline.Reset(false, 0);

                polyline.AddVertexAt(0, new Point2d(-10, -10), 0, 0, 0);
                polyline.AddVertexAt(1, new Point2d(-10, 20), 0, 0, 0);
                polyline.AddVertexAt(2, new Point2d(30, 20), 0, 0, 0);
                polyline.AddVertexAt(3, new Point2d(30, -10), 0, 0, 0);
                polyline.Closed = true;

                DBObjectCollection entities = new DBObjectCollection();
                entities.Add(polyline);
                entities.Add(circle);

                // Create regions for a Bowl base(circle) and floor(polyline)
                DBObjectCollection regions = Region.CreateFromCurves(entities);

                // After Regions, create the surfaces and set the colors
                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);
                
                foreach (Region region in regions)
                {
                    PlaneSurface planeSurface = new PlaneSurface();
                    planeSurface.CreateFromRegion(region);

                    if (region == regions[0])
                        planeSurface.Color = Color.FromRgb(40, 216, 251);
                    else
                        planeSurface.Color = Color.FromRgb(160, 158, 209);

                    modelSpace.AppendEntity(planeSurface);
                    transaction.AddNewlyCreatedDBObject(planeSurface, true);
                }

                transaction.Commit();
            }
        }

        static private ExtrudedSurface createExtrudedSurface(
            Entity sweepEntity,
			Vector3d direction,
			SweepOptions sweepOptions,
			Color color,
            BlockTableRecord blockTableRecord,
            Transaction transaction)
        {
	        ExtrudedSurface extrudedSurface = new ExtrudedSurface();

            extrudedSurface.CreateExtrudedSurface(sweepEntity, direction, sweepOptions);

            blockTableRecord.AppendEntity(extrudedSurface);
            transaction.AddNewlyCreatedDBObject(extrudedSurface, true);
    		
            extrudedSurface.Color = color;

            return extrudedSurface;
        }

        static public void addExtrudedSurface()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                // Using ExtrudedSurface class to create a extruded surface, 
                // creating a Table which has 4 legs and table top
                SweepOptions sweepOptions = new SweepOptions();
                Color color = Color.FromRgb(123, 72, 55);

                // In-memory circles for legs.
                Circle circle1 = new Circle(new Point3d(1.5, 1.5, 0.0), Vector3d.ZAxis, 0.5);
                Circle circle2 = new Circle(new Point3d(1.5, 8.5, 0.0), Vector3d.ZAxis, 0.5);
                Circle circle3 = new Circle(new Point3d(18.5, 8.5, 0.0), Vector3d.ZAxis, 0.5);
                Circle circle4 = new Circle(new Point3d(18.5, 1.5, 0.0), Vector3d.ZAxis, 0.5);

                circle1.SetDatabaseDefaults();
                circle2.SetDatabaseDefaults();
                circle3.SetDatabaseDefaults();
                circle4.SetDatabaseDefaults();

                // In-memory polyline for table top
                Polyline polyline = new Polyline();
                polyline.SetDatabaseDefaults();
                polyline.Reset(false, 0);

                polyline.AddVertexAt(0, new Point2d(0, -1), 0, 0, 0);
                polyline.AddVertexAt(1, new Point2d(0, 11), 0, 0, 0);
                polyline.AddVertexAt(2, new Point2d(20, 11), 0, 0, 0);
                polyline.AddVertexAt(3, new Point2d(20, -1), 0, 0, 0);
                polyline.Closed = true;
                polyline.Elevation = 10.0;

                Vector3d direction = Vector3d.ZAxis * 10.0;

                // Create the table legs, top and set the colors
                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                createExtrudedSurface(circle1, direction, sweepOptions, color, modelSpace, transaction);
                createExtrudedSurface(circle2, direction, sweepOptions, color, modelSpace, transaction);
                createExtrudedSurface(circle3, direction, sweepOptions, color, modelSpace, transaction);
                createExtrudedSurface(circle4, direction, sweepOptions, color, modelSpace, transaction);

                direction *= 0.05;
                createExtrudedSurface(polyline, direction, sweepOptions, color, modelSpace, transaction);

                transaction.Commit();
            }
        }

        static public void addRevolvedSurface()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                // Using RevolvedSurface to create a revolved surface i.e create a Pen holder on top of the table
                RevolvedSurface revolvedSurface = new RevolvedSurface();

                // In-memory polyline to represents the longitudinal cross-section of  the pen holder
                Polyline polyline = new Polyline();
                polyline.SetDatabaseDefaults();
                polyline.Reset(false, 0);

                polyline.AddVertexAt(0, new Point2d(16.0, 5.0), 0, 0, 0);
                polyline.AddVertexAt(1, new Point2d(16.1, 5.0), 0, 0, 0);
                polyline.AddVertexAt(2, new Point2d(16.1, 8.0), 0, 0, 0);
                polyline.AddVertexAt(3, new Point2d(16.0, 8.0), 0, 0, 0);
                polyline.Closed = true;
                polyline.Elevation = 10.5;

                // Create the surface
                revolvedSurface.CreateRevolvedSurface(polyline, new Point3d(16.7, 5.0, 10.5), Vector3d.YAxis, 2 * Math.PI, 0, new RevolveOptions());

                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                Matrix3d matrix = Matrix3d.Rotation(Math.PI / 2.0, Vector3d.XAxis, new Point3d(16.7, 5.0, 10.5));

                modelSpace.AppendEntity(revolvedSurface);
                transaction.AddNewlyCreatedDBObject(revolvedSurface, true);

                revolvedSurface.TransformBy(matrix);
                revolvedSurface.Color = Color.FromRgb(230, 25, 230);

                transaction.Commit();
            }
        }

        static public void addSweptSurface()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                Vector3d direction = new Vector3d(-0.4, 0.0, 3.0);

                Point3dCollection vertices = new Point3dCollection();
                vertices.Add(new Point3d(16.5, 5.0, 10.5));
                vertices.Add(new Point3d(16.1, 5.0, 13.5) + direction.GetNormal() * 1.5);

                // Polyline that represents the axis of the of the pen.
                Polyline3d polyline = new Polyline3d(Poly3dType.SimplePoly, vertices, false);
                polyline.SetDatabaseDefaults();

                Vector3d perpendicular = direction.GetNormal();
                perpendicular.RotateBy(Math.PI * 270.0 / 180.0, -Vector3d.YAxis);

                // Circle that represents the cross-section of the pen
                Circle circle = new Circle(new Point3d(16.55, 5.0, 10.5), Vector3d.ZAxis, 0.05);
                circle.SetDatabaseDefaults();

                // Sweep options to align the cross-section with the axis and also bank it with respect to (W.R.T) the axis
                SweepOptionsBuilder sweepOptionsBuilder = new SweepOptionsBuilder();
                sweepOptionsBuilder.Bank = true;
                sweepOptionsBuilder.Align = SweepOptionsAlignOption.AlignSweepEntityToPath;

                // Create the pen surface
                SweptSurface sweptSurface = new SweptSurface();

                sweptSurface.CreateSweptSurface(circle, polyline, sweepOptionsBuilder.ToSweepOptions());

                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                Matrix3d matrix = Matrix3d.Displacement(perpendicular * 0.05);
                modelSpace.AppendEntity(sweptSurface);
                transaction.AddNewlyCreatedDBObject(sweptSurface, true);

                sweptSurface.TransformBy(matrix);
                sweptSurface.Color = Color.FromRgb(253, 106, 73);

                // Polyline that represents the cross-section of the stand in the light stand
                Polyline standLine = new Polyline();
                standLine.SetDatabaseDefaults();
                standLine.Reset(false, 0);

                standLine.AddVertexAt(0, new Point2d(17.7, 7.7), 0, 0, 0);
                standLine.AddVertexAt(1, new Point2d(17.7, 8.3), 0, 0, 0);
                standLine.AddVertexAt(2, new Point2d(18.3, 8.3), 0, 0, 0);
                standLine.AddVertexAt(3, new Point2d(18.3, 7.7), 0, 0, 0);
                standLine.Closed = true;
                standLine.Elevation = 10.5;

                // Create a spline that represents the axis of sweep that the polyline above
                // will follow
                vertices.Clear();
                vertices.Add(new Point3d(19.0, 8.0, 10.5));
                vertices.Add(new Point3d(18.7, 8.0, 13.5));
                vertices.Add(new Point3d(18.3, 8.0, 14.5));
                vertices.Add(new Point3d(18.0, 8.0, 17.5));

                Spline spline = new Spline(vertices, 4, 0.0);

                // Create the stand surface
                sweptSurface = new SweptSurface();

                // Make sure the profile aligns with the sweep path
                sweepOptionsBuilder = new SweepOptionsBuilder();
                sweepOptionsBuilder.Bank = true;
                sweepOptionsBuilder.Align = SweepOptionsAlignOption.AlignSweepEntityToPath;

                sweptSurface.CreateSweptSurface(standLine, spline, sweepOptionsBuilder.ToSweepOptions());

                modelSpace.AppendEntity(sweptSurface);
                transaction.AddNewlyCreatedDBObject(sweptSurface, true);

                sweptSurface.Color = Color.FromRgb(55, 230, 84);

                transaction.Commit();
            }
        }

        static public void addLoftedSurface()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                // Using the LoftedSurface class creating a lofted Surface. 
                // The lamp shade surface and the bowl surface are created as a lofted surface

                // In-memory circles that represents the lamp shade profile
                Circle circle1 = new Circle(new Point3d(18.0, 8.0, 15.5), Vector3d.ZAxis, 2.0);
                Circle circle2 = new Circle(new Point3d(18.0, 8.0, 17.5), Vector3d.ZAxis, 1.0); 

                Point3dCollection points = new Point3dCollection();

                points.Add(new Point3d(20.0, 8.0, 15.5));
                points.Add(new Point3d(19.3, 8.0, 16.5));
                points.Add(new Point3d(19.0, 8.0, 17.5));

                // In-memory splines that serve as guide curves for the lamp shade
                Spline spline1 = new Spline(points, 4, 0.0);

                points.Clear();
                points.Add(new Point3d(16.0, 8.0, 15.5));
                points.Add(new Point3d(16.7, 8.0, 16.5));
                points.Add(new Point3d(17.0, 8.0, 17.5));

                Spline spline2 = new Spline(points, 4, 0.0);

                // Create the shade surface
                LoftedSurface loftedSurface = new LoftedSurface();

                LoftOptions loftOptions = new LoftOptions();

                Entity[] crossSections = new Entity[] { circle1, circle2 };
                Entity[] guideCurves = new Entity[] { spline1, spline2 };

                loftedSurface.CreateLoftedSurface(crossSections, guideCurves, null, loftOptions);

                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                modelSpace.AppendEntity(loftedSurface);
                transaction.AddNewlyCreatedDBObject(loftedSurface, true);

                loftedSurface.Color = Color.FromRgb(252, 234, 39);

                // In memory circles that represents the profile of the bowl that sits on the helix
                circle1 = new Circle(new Point3d(10.0, 3.0, 12.5), Vector3d.ZAxis, 1.0);
                circle2 = new Circle(new Point3d(10.0, 3.0, 14.5), Vector3d.ZAxis, 2.0);

                points.Clear();
                points.Add(new Point3d(11.0, 3.0, 12.5));
                points.Add(new Point3d(11.8, 3.0, 13.5));
                points.Add(new Point3d(12.0, 3.0, 14.5));

                // Splines that act as guide curves for the bowl profile.
                spline1 = new Spline(points, 4, 0.0); 

                points.Clear();
                points.Add(new Point3d(9.0, 3.0, 12.5));
                points.Add(new Point3d(8.2, 3.0, 13.5));
                points.Add(new Point3d(8.0, 3.0, 14.5));

                spline2 = new Spline(points, 4, 0.0);

                // Create the bowl surface
                loftedSurface = new LoftedSurface();

                crossSections = new Entity[] { circle1, circle2 };

                guideCurves = new Entity[] { spline1, spline2 };

                loftedSurface.CreateLoftedSurface(crossSections, guideCurves, null, loftOptions);

                modelSpace.AppendEntity(loftedSurface);
                transaction.AddNewlyCreatedDBObject(loftedSurface, true);

                loftedSurface.Color = Color.FromRgb(40, 216, 251);

                transaction.Commit();
            }
        }

        static public void addHelix()
        {
            using (Transaction transaction = Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction())
            {
                // Using Helix helix. 
                // This helix object created using Helix, acts as a stand for the bowl.
                Helix helix = new Helix();
                helix.SetDatabaseDefaults();

                // Set the Helix parameters
                helix.Constrain = ConstrainType.Height;
                helix.Height = 2.0;
                helix.Turns = 20.0;
                helix.AxisVector = Vector3d.ZAxis;
                helix.BaseRadius = 0.8;
                helix.TopRadius = 0.4;
                helix.SetAxisPoint(new Point3d(10.0, 3.0, 10.5), true);

                // The following call creates the internal spline that defines the helix path
                helix.CreateHelix(); // Generate the spline

                BlockTable blockTable = (BlockTable)transaction.GetObject(HostApplicationServices.WorkingDatabase.BlockTableId, OpenMode.ForRead, false);
                BlockTableRecord modelSpace = (BlockTableRecord)transaction.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite);

                modelSpace.AppendEntity(helix);
                transaction.AddNewlyCreatedDBObject(helix, true);

                helix.Color = Color.FromRgb(208, 83, 204);

                transaction.Commit();
            }
        }
    }
}
