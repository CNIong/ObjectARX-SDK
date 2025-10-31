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
using System.Windows;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;
using Autodesk.AutoCAD.Windows.ToolPalette;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;

[assembly: ExtensionApplication(null)]
[assembly: CommandClass(typeof(SimpleToolPaletteExample.Command))]

namespace SimpleToolPaletteExample
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	[Guid("ADB8A9F8-E340-429e-BC10-1FE38D69A2D3")]
	[Tool("MySimpleTool", "IDB_TOOL1")]
	[FlyoutEntry(2)]
	[ClassInterface(ClassInterfaceType.AutoDual)]
	public class SimpleTool : CustomToolBase
	{
		public SimpleTool()
		{
		}
		[ComVisible(true)]
		[DispId(1)]
		public string CmdName
		{
			get { return m_cmdName;}
			set { m_cmdName = value;}
		}

		[DispId(2)]
		public string Flyout 
		{
			get { return m_flyout;}
			set { m_flyout = value;}
		}

		[DispId(3)]
		public double StartX
		{
			get { return m_startX;}
			set { m_startX = value;}
		}

		[DispId(4)]
		public double StartY
		{
			get { return m_startY;}
			set { m_startY = value;}
		}

		[DispId(5)]
		public double StartZ
		{
			get { return m_startZ;}
			set { m_startZ = value;}
		}

		[DispId(6)]
		public double EndX
		{
			get { return m_endX;}
			set { m_endX = value;}
		}

		[DispId(7)]
		public double EndY
		{
			get { return m_endY;}
			set { m_endY = value;}
		}

		[DispId(8)]
		public double EndZ
		{
			get { return m_endZ;}
			set { m_endZ = value;}
		}


		/// <summary>
		/// ITool override
		/// </summary>
		public override void New()
		{
			m_startX = 2.0;
			m_startY = 2.0;
			m_startZ = 0.0;
			m_endX = 8.0;
			m_endY = 8.0;
			m_endZ = 0.0;

			m_cmdName = "_LINE";
		}

		const int MF_STRING = 0;
		const int MAX_MENU_ENTRIES = 3;
		static uint[] m_nMenuIds = new uint[] {0,0,0 };

		///IAcadToolContextMenu
		public override UInt32 Customize(Int32 nContextFlag, UInt32 hMenu,  
			UInt32 idCmdFirst, UInt32 idCmdLast,
			ref Guid pPaletteId)
		{
			uint maxMenu = (idCmdLast - idCmdFirst) < MAX_MENU_ENTRIES ? (idCmdLast - idCmdFirst) : MAX_MENU_ENTRIES;
    
			CatalogItem item = ToolPaletteManager.Manager.Catalogs.Find(pPaletteId);

			System.Diagnostics.Debug.Assert(item != null);

			String name = item.Name;

			uint i = 0;

			if (name != "SimplePalette")
			{
				for (i = 0; i < maxMenu; i++)
				{
					m_nMenuIds[i] = 0;
				}
				throw new NotImplementedException();
			}


			for (i = 0; i < maxMenu; i++)
			{
				m_nMenuIds[i] =  Convert.ToUInt32(idCmdFirst) + i;
			}

			Util.AppendMenu(new IntPtr(hMenu), MF_STRING, m_nMenuIds[0], "Menu&1");
			Util.AppendMenu(new IntPtr(hMenu), MF_STRING, m_nMenuIds[1], "Menu&2");
			Util.AppendMenu(new IntPtr(hMenu), MF_STRING, m_nMenuIds[2], "Menu&3");

			return 0;
		}
    
		public override UInt32 InvokeMenuCommand(UInt32 idCmd, ref Guid pPaletteId, UInt32 hWnd)
		{
			if (idCmd == m_nMenuIds[0])
				MessageBox.Show("Menu1 chosen");
			else if (idCmd == m_nMenuIds[1])
				MessageBox.Show("Menu2 chosen");
			else if (idCmd == m_nMenuIds[2])
				MessageBox.Show("Menu3 chosen");
			return 0;
		}
    
		/// <summary>
		/// CustomToolBase override
		/// </summary>
		/// <param name="?"></param>
		public override bool ExecuteCallback()
		{
			Point3d ptStart = new Point3d(m_startX, m_startY, m_startZ);
			Point3d ptEnd = new Point3d(m_endX, m_endY, m_endZ);

			Database db = HostApplicationServices.WorkingDatabase;
			TransactionManager tm = db.TransactionManager;
			using (Transaction t = tm.StartTransaction())
			{
				BlockTable bt = (BlockTable) t.GetObject(db.BlockTableId,OpenMode.ForRead);
				BlockTableRecord btr=(BlockTableRecord)t.GetObject(bt[BlockTableRecord.ModelSpace],OpenMode.ForWrite);

				using (Line	l= new Line(ptStart,ptEnd))
				{
					btr.AppendEntity(l);
					tm.AddNewlyCreatedDBObject(l,true);
				}
				t.Commit();
			}
			return true;
		}

		public override bool DropCallback (Autodesk.AutoCAD.DatabaseServices.Entity entity)
		{
			return false;
		}


		String m_cmdName;
		String m_flyout;
		double m_startX;
		double m_startY;
		double m_startZ;
		double m_endX;
		double m_endY;
		double m_endZ;
	}

	class Util
	{
		[DllImport("user32.dll")]
		public static extern bool AppendMenu(IntPtr hMenu, UInt32 wFlags, UInt32
			wIDNewItem, string lpNewItem);

	}
	public sealed class Command
	{

		/// <summary>
		/// Define an AutoCAD command called 'CreateSimple'
		/// This command will create the Simple tool and add it to ToolPalette catalogs
		/// </summary>
		[CommandMethod("CreateSimple")]        
		public void DoIt()
		{
			// Get the tool GUID;
			Type t = typeof(SimpleTool);
			GuidAttribute guidAttr = (GuidAttribute)t.GetCustomAttributes(typeof(GuidAttribute), false)[0];
			Guid guid = new Guid(guidAttr.Value);

			// don't redefine the stock tool if it's already in the catalog
			ToolPaletteManager mgr = ToolPaletteManager.Manager;
			if (mgr.StockToolCatalogs.Find(guid) != null)
				return;

			SimpleTool tool = new SimpleTool();
			tool.New();

			Catalog catalog = tool.CreateStockTool("SimpleCatalog");
			Palette palette = tool.CreatePalette(catalog, "SimplePalette");
			Package package = tool.CreateShapeCatalog("*AutoCADShapes");
			tool.CreateFlyoutTool(palette, package, null);
			ImageInfo imageInfo = new ImageInfo();
			imageInfo.ResourceFile = "TOOL1.bmp";
			imageInfo.Size=new System.Drawing.Size(65,65);

			tool.CreateCommandTool(palette, "Line", imageInfo, tool.CmdName);
			tool.CreateTool(palette, "Custom Line",imageInfo);
			mgr.LoadCatalogs();
		}
	}
}
