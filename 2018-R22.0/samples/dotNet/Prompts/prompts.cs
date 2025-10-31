//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


using System;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.EditorInput;

[assembly: ExtensionApplication(null)]
[assembly: CommandClass(typeof(Prompts.PromptsTest))]

namespace Prompts
{
	public class PromptsTest
	{
		static PromptAngleOptions useThisAngleOption;
		static PromptDoubleResult useThisAngleResult;
		static PromptPointOptions useThisPointOption;
		static PromptPointResult useThisPointResult;
		static PromptEntityOptions useThisEntityOption;
		static PromptEntityResult useThisEntityResult;

		//A small function that shows how to prompt for an integer
		[CommandMethod("GetInteger")] 
		public void integerTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptIntegerOptions opt0 = new PromptIntegerOptions("Enter your age");
			opt0.AllowNegative = false;
			opt0.AllowNone = false;
			opt0.AllowZero = false;
			opt0.DefaultValue = 1;
			PromptIntegerResult IntRes = ed.GetInteger(opt0);
			if(IntRes.Status == PromptStatus.OK)
			{
				ed.WriteMessage(string.Format("\nYou entered {0}",IntRes.Value));
			}
		}

		//This method prompts for a double value.
		//Pi,Two-pi  are valid keywords that can be entered
		//by the user at the prompt.
		[CommandMethod("GetDouble")] 
		public void DoubleTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptDoubleOptions opt1 = new PromptDoubleOptions("Enter a number or Pi/Two-pi");
			opt1.Keywords.Add("Pi");
			opt1.Keywords.Add("Two-pi");
			opt1.AllowNone = false;
			opt1.AllowZero = false;
			opt1.DefaultValue = 1.0;

			PromptDoubleResult doubleRes = ed.GetDouble(opt1);
			if(doubleRes.Status == PromptStatus.Keyword)
			{
                switch (doubleRes.StringResult)
                {
                    case "Pi":
                        ed.WriteMessage("Value is 3.14");
                        break;
                    case "Two-pi":
                        ed.WriteMessage("\nValue is 6.28");
                        break;
                    default:
                        ed.WriteMessage("\nKeyword unknown");
                        break;
                }
            }
			if(doubleRes.Status != PromptStatus.OK)
			{
				ed.WriteMessage("\nUser entered: " + doubleRes.Status.ToString());
			}
		}

		//Gets the radius of the circle from the user using GetDistance command
		//and draw the circle.
	    //The user can either specify the number in the command prompt or
		//The user can set the distance (in this case radius of circle) also
		//by specifying two locations on the graphics screen.
		//AutoCAD draws a rubber-band line from the first point to
		//the current crosshair position to help the user visualize the distance.
		[CommandMethod("GetDistance")] 
		public void DistanceTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptDistanceOptions opt1 = new PromptDistanceOptions("Enter the radius of the circle");
	
			opt1.AllowNegative = false;
			opt1.AllowZero = false;
			opt1.AllowNone = false;
			opt1.UseDashedLine = true;

			PromptDoubleResult res = ed.GetDistance(opt1);
			
			if(res.Status == PromptStatus.OK)
			{
				Point3d center = new Point3d(9.0, 3.0, 0.0);
				Vector3d normal = new Vector3d(0.0, 0.0, 1.0);
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				using (Transaction myT = tm.StartTransaction())
				{
                    BlockTable bt = (BlockTable)tm.GetObject(db.BlockTableId, OpenMode.ForRead, false);
                    BlockTableRecord btr = (BlockTableRecord)tm.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false);
                    using (Circle pcirc = new Circle(center, normal, res.Value))
                    {
                        btr.AppendEntity(pcirc);
                        tm.AddNewlyCreatedDBObject(pcirc, true);
                    }
                    myT.Commit();
				}
				
			}
			
		}

	

		//The user is prompted to enter the start angle and end angle at the
		//command prompt.  Using which an arc is created.

		//Not only by entering the values but The user can set the angle also by 
		//specifying two 2D locations on the graphics screen. AutoCAD draws a
		//rubber-band line from the first point to the current crosshair position 
		//to help the user visualize the angle.

		//Also attached to this function is the input context reactor event
		//PromptingForAngle and PromptedForAngle. During ed.GetAngle(), these
		//events gets fired. The call back function just remembers the prompt option
		//that the user has set initially and also the prompt result that the
		//user sees after he calls GetAngle() method.


		[CommandMethod("GetAngle")] 
		public void AngleTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptAngleOptions opt1 = new PromptAngleOptions("Enter start angle of the arc");
			
			opt1.AllowNone = false;
			opt1.UseDashedLine = true;
			
			//USAGE OF INPUT CONTEXT REACTORS
			ed.PromptingForAngle += new PromptAngleOptionsEventHandler(handle_promptangleOptions);
			ed.PromptedForAngle += new PromptDoubleResultEventHandler(handle_promptAngleResult);
			
			PromptDoubleResult startAngle = ed.GetAngle(opt1);
			
			ed.PromptingForAngle -= new PromptAngleOptionsEventHandler(handle_promptangleOptions);
			ed.PromptedForAngle -= new PromptDoubleResultEventHandler(handle_promptAngleResult);


			opt1.Message = "Enter end angle of the arc";
			PromptDoubleResult endAngle = ed.GetAngle(opt1);

			PromptDoubleOptions opt2 = new PromptDoubleOptions("Enter the radius of the arc(double)");
			opt2.Message = "Enter the radius of the arc(double)";
			PromptDoubleResult radius = ed.GetDouble(opt2);

			if(startAngle.Status == PromptStatus.OK && endAngle.Status == PromptStatus.OK && radius.Status == PromptStatus.OK)
			{
				Point3d center = new Point3d(30.0, 19.0, 0.0);
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				
				using (Transaction myT = tm.StartTransaction())
				{
                    BlockTable bt = (BlockTable)tm.GetObject(db.BlockTableId, OpenMode.ForRead, false);
                    BlockTableRecord btr = (BlockTableRecord)tm.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false);
                    using (Arc arc1 = new Arc(center, radius.Value, startAngle.Value, endAngle.Value))
                    {
                        btr.AppendEntity(arc1);
                        tm.AddNewlyCreatedDBObject(arc1, true);
                    }
                    myT.Commit();
				}
				
			}
			else
			{
				ed.WriteMessage("Arc cannot be constructed");
			}
		
		}



		[CommandMethod("useAngle")] 
		public void UsingAngleOptionsAndResults()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			//Verify GetAngle has been ran once before executing this one
			if ( useThisAngleOption == null || useThisAngleResult == null )
			{
				ed.WriteMessage("Please run GetAngle command first");
				return;
			}
			//Using the stored PromptAngleOption.
			PromptDoubleResult res1 = ed.GetAngle(useThisAngleOption);
			//Using the stored PromptAngleResult.
			PromptDoubleResult res2 = useThisAngleResult;
			if(res1.Status == PromptStatus.OK && res2.Status == PromptStatus.OK)
			{
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				
				using (Transaction myT = tm.StartTransaction())
				{             
					BlockTable bt = (BlockTable)tm.GetObject(db.BlockTableId,OpenMode.ForRead,false);
					BlockTableRecord btr = (BlockTableRecord)tm.GetObject(bt[BlockTableRecord.ModelSpace],OpenMode.ForWrite,false);
                    Point3d center = new Point3d(30.0, 19.0, 0.0);
                    using (Arc arc1 = new Arc(center, res1.Value, res2.Value, 5.0))
                    {
                        arc1.ColorIndex = 3;
                        btr.AppendEntity(arc1);
                        myT.AddNewlyCreatedDBObject(arc1, true);
                    }
                    myT.Commit();
				}
				
			}
			else
			{
				ed.WriteMessage("Arc cannot be constructed");
			}
		}

//	    Drawing a line using the points entered by the user.
//		Prompt the user for the start point and end point of the line.

//		The AutoCAD user can specify the point by entering a coordinate in
//		the current units format; The user can specify the point also by specifying 
//		a location on the graphics screen.
		[CommandMethod("GetPoint")] 
		public void PointTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptPointOptions ptopts = new PromptPointOptions("Enter start point of the line");
			ptopts.BasePoint = new Point3d(1,1,1);
			ptopts.UseDashedLine = true;
			ptopts.Message = "Enter start point of the line";
			
			ed.PromptingForPoint += new PromptPointOptionsEventHandler(handle_promptPointOptions);
			ed.PromptedForPoint += new PromptPointResultEventHandler(handle_promptPointResult);
			PromptPointResult ptRes = ed.GetPoint(ptopts);
			ed.PromptingForPoint -= new PromptPointOptionsEventHandler(handle_promptPointOptions);
			ed.PromptedForPoint -= new PromptPointResultEventHandler(handle_promptPointResult);
			

			Point3d start = ptRes.Value;
			if(ptRes.Status == PromptStatus.Cancel)
			{
				ed.WriteMessage("Taking (0,0,0) as the start point");
			}

			ptopts.Message ="Enter end point of the line: ";
			ptRes = ed.GetPoint(ptopts);
			Point3d end = ptRes.Value;
			if(ptRes.Status == PromptStatus.Cancel)
			{
				ed.WriteMessage("Taking (0,0,0) as the end point");
			}
			
			Database db = Application.DocumentManager.MdiActiveDocument.Database;
			Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
			
			using (Transaction myT = tm.StartTransaction())
			{   
				BlockTable bt = (BlockTable)tm.GetObject(db.BlockTableId,OpenMode.ForRead,false);
				BlockTableRecord btr = (BlockTableRecord)tm.GetObject(bt[BlockTableRecord.ModelSpace],OpenMode.ForWrite,false);
                using (Line myline = new Line(start, end))
                {
                    btr.AppendEntity(myline);
                    tm.AddNewlyCreatedDBObject(myline, true);
                }
                myT.Commit();
			}
			
		}


		[CommandMethod("usepoint")] 
		public void UsingPointOptionsAndResults()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			//Verify GetPoint has been ran once before executing this one
			if ( useThisPointOption == null || useThisPointResult == null )
			{
				ed.WriteMessage("Please run GetPoint command first");
				return ;
			}
			//Using the stored PromptPointOption.
			PromptPointResult res1 = ed.GetPoint(useThisPointOption);
			//Using the stored PromptPointResult.
			PromptPointResult res2 = useThisPointResult;
			
			if(res1.Status != PromptStatus.Cancel && res2.Status != PromptStatus.Cancel)
			{
				Point3d start = res1.Value;
				Point3d end = res2.Value;
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				using (Transaction myT = tm.StartTransaction())
				{             
					BlockTable bt = (BlockTable)tm.GetObject(db.BlockTableId,OpenMode.ForRead,false);
					BlockTableRecord btr = (BlockTableRecord)tm.GetObject(bt[BlockTableRecord.ModelSpace],OpenMode.ForWrite,false);
                    using (Line myline = new Line(start, end))
                    {
                        myline.ColorIndex = 3;
                        btr.AppendEntity(myline);
                        myT.AddNewlyCreatedDBObject(myline, true);
                    }
                    myT.Commit();
				}
				
			}
		}
		
		//Here the user is prompted for a string that could be used as a keyword.
		//We then test to see if the user entered string has been taken as a valid 
		//keyword or not by asking the user to enter that string as a keyword in the
		//command prompt. If it is not a valid one then the user is prompted for a 
		//different value (which is a bug).
		[CommandMethod("GetKW")] 
		public void KWandStringTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptStringOptions stropts = new PromptStringOptions("Enter a string you want to use as keyword");
			PromptKeywordOptions kwopts = new PromptKeywordOptions("Enter a string you want to use as keyword");
			stropts.AllowSpaces = false;
			PromptResult str = ed.GetString(stropts);
			kwopts.Keywords.Add(str.StringResult);
			kwopts.Keywords.Add("onemore");
			kwopts.Message = "Enter the word that u just enterd to test if its a valid keyword or not";
            PromptResult kw = ed.GetKeywords(kwopts);
			if(kw.Status == PromptStatus.OK)
			{
				ed.WriteMessage("You entered a valid keyword");
			}
			else
			{
				ed.WriteMessage("You didn't enter a valid keyword: "+kw.Status.ToString());
			}
		}

		//Try to draw a few entities in the drawing for the user to select.
		//It prompts the user to select some entities and finally types
		//the name of the selected entity at the command prompt.
		//Also added the two input context reactor events:
		//PromptingForEntity and PromptedForEntity
		[CommandMethod("Getentity")] 
		public void EntityTest()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptEntityOptions entopts = new PromptEntityOptions("Pick an entity of your choice from the drawing");
			entopts.Message = "Pick an entity of your choice from the drawing";
			PromptEntityResult ent=null;
			//ADDED INPUT CONTEXT REACTOR	
			ed.PromptingForEntity += new PromptEntityOptionsEventHandler(handle_promptEntityOptions);
			ed.PromptedForEntity += new PromptEntityResultEventHandler(handle_promptEntityResult);
				
			try
			{
				ent = ed.GetEntity(entopts);
			}
			catch
			{
				ed.WriteMessage("You did not select a valid entity");
				ed.PromptingForEntity -= new PromptEntityOptionsEventHandler(handle_promptEntityOptions);
				ed.PromptedForEntity -= new PromptEntityResultEventHandler(handle_promptEntityResult);
					
			}
			ed.PromptingForEntity -= new PromptEntityOptionsEventHandler(handle_promptEntityOptions);
			ed.PromptedForEntity -= new PromptEntityResultEventHandler(handle_promptEntityResult);
	
			if(ent.Status != PromptStatus.Error)
			{
				ObjectId entid = ent.ObjectId;
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				using (Transaction myT = tm.StartTransaction())
				{             
					Entity entity = (Entity)tm.GetObject(entid,OpenMode.ForRead,true);
					ed.WriteMessage("You selected: "+entity.GetType().FullName);
					myT.Commit();
				}
			}
			
    	}

	

		//This method just makes use of the entity option and entity result
		//that was stored in a static variable when the PromptingForEntity
		//and PromptingForEntity events where fired from EntityTest() function.
		[CommandMethod("useentity")] 
		public void UsingEntityOptionsAndResults()
		{
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			//Using the stored PromptEntityOption.
			PromptEntityResult res1 = ed.GetEntity(useThisEntityOption);
			//Using the stored PromptEntityResult.
			PromptEntityResult res2 = useThisEntityResult;
			ed.WriteMessage("\nCHANGING THE ALREADY SELECTED ENTITIES COLORS TO GREEN");
			if(res2.Status != PromptStatus.Error)
			{
				ObjectId entid = res2.ObjectId;
				Database db = Application.DocumentManager.MdiActiveDocument.Database;
				Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
				ObjectId nowSelEntid = res1.ObjectId;
				
				using (Transaction myT = tm.StartTransaction())
				{             
					Entity Oldentity = (Entity)tm.GetObject(entid,OpenMode.ForWrite,true);
					Oldentity.ColorIndex = 2;
					ed.WriteMessage("\nYou Now selected: "+Oldentity.GetType().FullName);
					myT.Commit();
				}
			}

		}

		//Try to draw a few nested entities like blocks and xrefs in the drawing for the user to select.
		//if the user selects a nested entity then the name of the nested entity is displayed.
		//Finally after the user is done selecting the entities, a non interactive selection is made
		//at the point 30.4,11.6,0 and the name of the nested entity if any is displayed.
		[CommandMethod("GetNestentity")] 
		public void NestedEntityTest()
		{
			ObjectIdCollection coll = new ObjectIdCollection();
			Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
			PromptNestedEntityOptions entopts = new PromptNestedEntityOptions("prompt nested entity");
			entopts.AllowNone = true;
			entopts.Keywords.Add("Done");
			PromptNestedEntityResult ent= null;
			Database db = Application.DocumentManager.MdiActiveDocument.Database;
			Autodesk.AutoCAD.DatabaseServices.TransactionManager tm = db.TransactionManager;
			
			using (Transaction myT = tm.StartTransaction())
			{     
				while(true)
				{

					entopts.Message = "\nPick an entity of your choice from the drawing or type Done";

					try
					{
						ent = ed.GetNestedEntity(entopts);
					}
					catch
					{
						ed.WriteMessage("\nYou did not select a valid nested entity");
						break;
					}
					if(ent.Status == PromptStatus.Keyword)
					{
						if(ent.StringResult.Equals("Done"))
							break;
					}

					try
					{
						if(ent.GetContainers().Length > 0)
						{
							Entity entity;
							foreach(ObjectId oid in ent.GetContainers())
							{
								entity = (Entity)tm.GetObject(oid,OpenMode.ForRead,true);
								ed.WriteMessage("You selected: "+entity.GetType().FullName);
							}
							break;
						}
						else
						{
							ed.WriteMessage("You did not select any nested entity");
						}
					}
					catch
					{
						ed.WriteMessage("You are Done or did not select any nested entity");
						myT.Commit();
						return;
					}

				}

				entopts.NonInteractivePickPoint = new Point3d(30.4,11.6,0);
				entopts.UseNonInteractivePickPoint = true;

				try
				{
					ent = ed.GetNestedEntity(entopts);
					if(ent.GetContainers().Length > 0)
					{
						Entity entity;
						foreach(ObjectId oid in ent.GetContainers())
						{
							entity = (Entity)tm.GetObject(oid,OpenMode.ForRead,true);
							ed.WriteMessage(entity.GetType().FullName+" has been selected");
						}
						}
					else
					{
						ed.WriteMessage("No nested entity was selected");
					}
				}
				catch
				{
					ed.WriteMessage("\nNo entity was selected");
					
				}
				myT.Commit();
			}
				
		}
		private static void handle_promptEntityOptions(object sender, PromptEntityOptionsEventArgs e)
		{
			useThisEntityOption = e.Options;

		}
		private static void handle_promptEntityResult(object sender, PromptEntityResultEventArgs e)
		{
			useThisEntityResult = e.Result;

		}
		private static void handle_promptPointOptions(object sender, PromptPointOptionsEventArgs e)
		{
			useThisPointOption = e.Options;

		}
		private static void handle_promptPointResult(object sender, PromptPointResultEventArgs e)
		{
			useThisPointResult = e.Result;

		}
		private static void handle_promptangleOptions(object sender, PromptAngleOptionsEventArgs e)
		{
			useThisAngleOption = e.Options;

		}
		private static void handle_promptAngleResult(object sender, PromptDoubleResultEventArgs e)
		{
			useThisAngleResult = e.Result;
		}

	}
}
