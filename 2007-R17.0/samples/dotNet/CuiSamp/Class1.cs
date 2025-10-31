// Copyright 2005-2006 by Autodesk, Inc.
//
//Permission to use, copy, modify, and distribute this software in
//object code form for any purpose and without fee is hereby granted, 
//provided that the above copyright notice appears in all copies and 
//that both that copyright notice and the limited warranty and
//restricted rights notice below appear in all supporting 
//documentation.
//
//AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
//AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
//MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
//UNINTERRUPTED OR ERROR FREE.
//
//Use, duplication, or disclosure by the U.S. Government is subject to 
//restrictions set forth in FAR 52.227-19 (Commercial Computer
//Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
//(Rights in Technical Data and Computer Software), as applicable.
using System;
using System.IO;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.DatabaseServices;

using Autodesk.AutoCAD.Customization;

// This application implements several commands that shows how to
// manipulate some of the existing CUI User interface and components.
// The commands implemented here allow you to:
//
// 1) Create/Remove menu and its items (ADDMENU/REMMENU)
// 3) Create/Remove a workspace (ADDWS/REMWS)
// 2) Create/Remove a toolbar and its items (ADDTOOLBAR/REMTOOLBAR)
// 4) Create a keyboard shortcut (CUISHORTCUT)
// 5) Create a temporary override (TEMPKEY)
// 6) Change position and docking of "Info Palette" 
//    window (DOCKR, DOCKL, DOCKF)
// 7) Add a double-click action (DBLCLICK)
// 8) A command that performs the tasks of ADDMENU,ADDTOOLBAR,
//    DOCKL and CUISHORTCUT (CUIALL)
// 9) Save a CUI after its modifications and reload it (SAVECUI)

// Apart from the above commands, lisp wrappers have also been 
// implemented to make the commands callable from windows.

// To use CuiSamp.dll:
// 1) Start AutoCAD and open a new drawing.
// 2) Type netload and select CuiSamp.dll.
// 3) Execute the CUIALL command, if you want the UI related 
//    modifications.

// Please add the References acdbmgd.dll,acmgd.dll,
// AcCui.dll and AcCustomize.dll before trying to 
// build this project.

namespace CuiSamp
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class CuiSamp
	{
		// All Cui files (main/partial/enterprise) have to be loaded into an object of class 
		// CustomizationSection
		// cs - main AutoCAD CUI file
		CustomizationSection cs;
		CustomizationSection entCs;
		CustomizationSection[]partials ;
		
		int numPartialFiles;

		YesNoIgnoreToggle yes = YesNoIgnoreToggle.yes;
		YesNoIgnoreToggle no  = YesNoIgnoreToggle.no;
		
		// True when enterprise CUI file is loaded successfully
		bool entCsLoaded;

		// ed - access to the AutoCAD Command Line
		// Allows us to write messages or Issue Commands in the interface
		Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;


		//Default Constructor
		public CuiSamp()
		{
			// retrieve the location of, and open the ACAD Main CUI File
			string mainCuiFile = (string)Application.GetSystemVariable("MENUNAME");
			mainCuiFile += ".cui";
			cs = new CustomizationSection(mainCuiFile);
			
			string entCuiFile = (string)Application.GetSystemVariable("ENTERPRISEMENU");
			if( entCuiFile.Equals("."))
				entCsLoaded = false;
			else
			{
				entCs = new CustomizationSection(entCuiFile);
				entCsLoaded = true;
			}
			
			// Code for loading all partial CUI's listed in the main CUI file
			
			partials = new CustomizationSection[cs.PartialCuiFiles.Count];
			int i=0;
			foreach(string fileName in cs.PartialCuiFiles)
			{	
				if (File.Exists(fileName))
				{
					partials[i] = new CustomizationSection(fileName);
					i++;
				}
			}
			numPartialFiles = i;	
		}


		// Command: savecui
		// This Command saves all open CUI Files that have been modified
		[CommandMethod("savecui")]
		public void saveCui()
		{
			// Save all Changes made to the CUI file in this session. 
			// If changes were made to the Main CUI file - save it
			// If changes were made to teh Partial CUI files need to save them too
	
			if(cs.IsModified)
				cs.Save();

			for(int i=0;i < numPartialFiles;i++)
			{	
				if(partials[i].IsModified)
					partials[i].Save();
			}
			
			if(entCsLoaded && entCs.IsModified)
				entCs.Save();

			// Here we unload and reload the main CUI file so the changes to the CUI file could take effect immediately.
			string flName = cs.CUIFileBaseName;
			Application.SetSystemVariable("FILEDIA",0);
			Application.DocumentManager.MdiActiveDocument.SendStringToExecute("cuiunload " + flName + " ",false,false,false);
			Application.DocumentManager.MdiActiveDocument.SendStringToExecute("cuiload " + flName + " filedia 1 ",false,false,false);
		}

		// Lisp callable function: savecui
		// Lisp wrapper for savecui command
		[LispFunction("savecui")]
		public void saveCui(ResultBuffer args)
		{
			saveCui();
		}

		// Command: addmenu
		// This Command adds a new menu to all workspaces called Custom Menu, which contains 2 sub items
		// The Menu is first added to the Main CUI File and then added to all it's workspaces. 
		[CommandMethod("addmenu")]
		public void addMenu()
		{
			if (cs.MenuGroup.PopMenus.IsNameFree("Custom Menu"))
			{
				
				System.Collections.Specialized.StringCollection pmAliases = new System.Collections.Specialized.StringCollection();
				pmAliases.Add("POP12");
				
				PopMenu pm = new PopMenu("Custom Menu",pmAliases,"Custom Menu",cs.MenuGroup);
				
				addItemsToPM(pm);
				addMenu2Workspaces(pm);
			}
			else
				ed.WriteMessage("Custom Menu already Exists\n");	
		}

		// Lisp callable function: addmenu
		// Lisp wrapper for addmenu command
		[LispFunction("addmenu")]
		public void addMenu(ResultBuffer args)
		{
			addMenu();
		}

		// Add new Items to a PopMenu
		private void addItemsToPM(PopMenu pm)
		{
			PopMenuItem pmi = new PopMenuItem(pm,-1);
			pmi.MacroID = "ID_AUGI";pmi.Name = "Autodesk User Group International";
			
			pmi = new PopMenuItem(pm,-1);

			pmi = new PopMenuItem(pm,-1);
			pmi.MacroID = "ID_CustomSafe";pmi.Name = "Online Developer Center";
		}

		// Add the menu to all the workspaces
		private void addMenu2Workspaces(PopMenu pm)
		{
			foreach(Workspace wk in cs.Workspaces)
			{
				WorkspacePopMenu wkpm = new WorkspacePopMenu(wk,pm);
				wkpm.Display = 1;
			}
		
		}
	
		// Command: remmenu
		// This Command deletes the menu added above from the Main CUI File and any
		//  workspaces that it was added to. 
		[CommandMethod("remmenu")]
		public void remMenu()
		{
			// Find Index of the desired MenuItem
			// Remove it from all Workspaces that it exists in
			// Omitting this step leaves nasty left-overs in the Workspace files
			// Remove it from the Cui files' Menu List
			
			PopMenu	pm = cs.MenuGroup.PopMenus.FindPopWithAlias("POP12");
			if (pm != null )
			{
				foreach(Workspace wk in cs.Workspaces)
				{
					WorkspacePopMenu wkPm = wk.WorkspacePopMenus.FindWorkspacePopMenu(pm.ElementID,pm.Parent.Name);
			
					if(wkPm != null)
						wk.WorkspacePopMenus.Remove(wkPm);
				}
				cs.MenuGroup.PopMenus.Remove(pm);	// Deletes the Menu from ACAD Menu Group
			}
		}

		// Lisp callable function: remmenu
		// Lisp wrapper for remmenu command
		[LispFunction("remmenu")]
		public void remMenu(ResultBuffer args)
		{
			remMenu();
		}

		// Command: addws
		// This command adds a new workspace. The name of the workspace to create is
		// obtained from the command line.
		[CommandMethod("addws")]
		public void addws()
		{
			String wsName;
			PromptResult prs = ed.GetString("Enter name of workspace to create: ");
			if(PromptStatus.OK == prs.Status )
			{
				wsName = prs.StringResult;
				if(-1 == cs.Workspaces.IndexOfWorkspaceName(wsName)) // If the workspace doesnot exist
				{
					Workspace nwWs = new Workspace (cs, wsName); // Create the workspace
					saveCui(); // Save and reload the CUI file
				}
				else
				{
					ed.WriteMessage("A workspace with this name already exists");
				}
			}

		}

		// Lisp callable function: addws
		// Lisp wrapper for addws command
		[LispFunction("addws")]
		public void addws(ResultBuffer args)
		{
			addws();
		}

		// Command: remws
		// This command removes a workspace. The name of the workspace to remove is
		// obtained from the command line.
		[CommandMethod("remws")]
		public void remws()
		{
			String wsName;
			PromptResult prs = ed.GetString("Enter name of workspace to remove: ");
			if(PromptStatus.OK == prs.Status )
			{
				wsName = prs.StringResult;
				if(-1 != cs.Workspaces.IndexOfWorkspaceName(wsName)) // If the workspace exist
				{
					cs.deleteWorkspace(wsName); // Remove the workspace
					saveCui(); // Save and reload the CUI file
				}
				else
				{
					ed.WriteMessage("No workspace exists with this name");
				}
			}
			
		}
		// Lisp callable function: remws
		// Lisp wrapper for remws command
		[LispFunction("remws")]
		public void remws(ResultBuffer args)
		{
			remws();
		}


		// Command: cuishortcut
		// This adds a Shortcut key to the CUI command.
		// Ctrl+B is used for Toggling SNAP. It gets reassigned
		[CommandMethod("cuishortcut")]
		public void shortCut()
		{
			// In here we will make a shortcut Key combination to the Customize.. command
			MacroGroup mg = cs.MenuGroup.MacroGroups[0]; // Search the ACAD Macros
			foreach (MenuMacro mcr in mg.MenuMacros)
			{
				if(mcr.ElementID.Equals("MM_1570"))
				{
					MenuAccelerator ma = new MenuAccelerator(mcr,cs.MenuGroup);
					ma.AcceleratorShortcutKey = "CTRL+B";
				}
			}
		}
		// Lisp callable function: cuishortcut
		// Lisp wrapper for cuishortcut command
		[LispFunction("cuishortcut")]
		public void shortCut(ResultBuffer args)
		{
			shortCut();
		}

		// Command: dockr
		// Dock Info Palette to the right
		[CommandMethod("dockr")]
		public void dockInfoPalR()
		{
			dockInfoPalette(DockableWindowOrient.right);
		}
		// Lisp callable function: dockr
		// Lisp wrapper for dockr command
		[LispFunction("dockr")]
		public void dockInfoPalR(ResultBuffer args)
		{
			dockInfoPalR();
		}

		// Command: dockl
		// Dock Info Palette to the left
		[CommandMethod("dockl")]
		public void dockInfoPalL()
		{
			dockInfoPalette(DockableWindowOrient.left);
		}

		// Lisp callable function: dockl
		// Lisp wrapper for dockl command
		[LispFunction("dockl")]
		public void dockInfoPalL(ResultBuffer args)
		{
			dockInfoPalL();
		}

		// Command: dockf
		// Set Info Palette to float
		[CommandMethod("dockf")]
		public void dockInfoPalF()
		{
			dockInfoPalette(DockableWindowOrient.floating);
		}
		// Lisp callable function: dockf
		// Lisp wrapper for dockf command
		[LispFunction("dockf")]
		public void dockInfoPalF(ResultBuffer args)
		{
			dockInfoPalF();
		}


		// Method to implement the positiioning/docking of the "Info Palette" window
		private void dockInfoPalette(DockableWindowOrient orientation)
		{
			int wkB = cs.Workspaces.IndexOfWorkspaceName("AutoCAD Default");
			// check to see if it exists
			if (wkB == -1)
			{
				// if not, then see if it is called simply AutoCAD
				wkB = cs.Workspaces.IndexOfWorkspaceName("AutoCAD");
				if (wkB == -1)
				{
					// if not, then ok - it's something else
					Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage("Workspace not found.");
					return;
				}
			}
			Workspace wk = cs.Workspaces[wkB];
			
			foreach(WorkspaceDockableWindow dockableWindow in wk.DockableWindows)
			{
				if(dockableWindow.Name.Equals("Info Palette"))
				{	
					if(orientation.Equals(DockableWindowOrient.floating))
						dockableWindow.DockFloat = DockedFloatingIgnoreToggle.floating;
					else	
						dockableWindow.DockFloat = DockedFloatingIgnoreToggle.docked;

					dockableWindow.Display = yes;
					dockableWindow.Orientation = orientation;
					dockableWindow.AutoHide = OnOffIgnoreToggle.off;
					dockableWindow.UseTransparency = no;
					break;
				}
			}
		}

		// Command: addtoolbar
		// Creates a new toolbar called "New Toolbar", and adds it to all workspaces. 
		// This toolbar contains a Toolbar control for named view, button for drawing 
		// a pline, and a flyout that uses the "Draw" tool bar.
		[CommandMethod("addtoolbar")]
		public void addToolbar()
		{
			Toolbar newTb = new Toolbar("New Toolbar",cs.MenuGroup);
			newTb.ToolbarOrient = ToolbarOrient.floating;
			newTb.ToolbarVisible = ToolbarVisible.show;
			
			ToolbarControl tbCtrl = new ToolbarControl(ControlType.NamedViewControl,newTb,-1);
						
			ToolbarButton tbBtn = new ToolbarButton(newTb,-1);
			tbBtn.Name = "PolyLine";
			tbBtn.MacroID = "ID_Pline";

			ToolbarFlyout tbFlyout = new ToolbarFlyout(newTb,-1);
			tbFlyout.ToolbarReference = "DRAW";

			foreach( Workspace wk in cs.Workspaces)
			{
				WorkspaceToolbar wkTb = new WorkspaceToolbar(wk,newTb);
				wk.WorkspaceToolbars.Add(wkTb);
				wkTb.Display = 1;
			}
		}
		// Lisp callable function: addtoolbar
		// Lisp wrapper for addtoolbar command
		[LispFunction("addtoolbar")]
		public void addToolbar(ResultBuffer args)
		{
			addToolbar();
		}

		// Command: remtoolbar
		// This Command removes the toolbar added above from the Main CUI File and any
		// workspaces that it was added to. 
		[CommandMethod("remtoolbar")]
		public void remToolbar()
		{
			Toolbar tbr = cs.MenuGroup.Toolbars.FindToolbarWithName("New Toolbar");
			if (tbr != null )
			{
				foreach(Workspace wk in cs.Workspaces)
				{
					WorkspaceToolbar wkTb = wk.WorkspaceToolbars.FindWorkspaceToolbar(tbr.ElementID,tbr.Parent.Name);
			
					if(wkTb != null)
						wk.WorkspaceToolbars.Remove(wkTb);
				}
				cs.MenuGroup.Toolbars.Remove(tbr);	// Deletes the toolbar from ACAD Menu Group
			}
		}

		// Lisp callable function: remtoolbar
		// Lisp wrapper for remtoolbar command
		[LispFunction("remtoolbar")]
		public void remToolbar(ResultBuffer args)
		{
			remToolbar();
		}

		// Command: tempkey
		// This command will install a temporary override key. Temporary override keys are keys that temporarily 
		// turn on or turn off one of the drawing aids that are set in the Drafting Settings dialog box 
		// (for example, Ortho mode, object snaps, or Polar mode).
		[CommandMethod("tempkey")]
		public void tempOverride()
		{
			TemporaryOverride newTempOverride = new TemporaryOverride(cs.MenuGroup);	
			newTempOverride.OverrideShortcutKey = "SHIFT+Y"; // Scan code for Y
			newTempOverride.Name = "Customization Override";
			newTempOverride.Description = "Customization Override";
			newTempOverride.ElementID ="EID_CUITEMPOVERRIDE";
			// Creating a override for Shift+Y (Key down) that will behave as temporary override for OSnap to endpoint (MM_1629)
			OverrideItem newOverrideItem = new OverrideItem("MM_1629",OverrideKeyState.Down,newTempOverride);
			newTempOverride.DownOverride = newOverrideItem;			
		}
		// Lisp callable function: tempkey
		// Lisp wrapper for tempkey command
		[LispFunction("tempkey")]
		public void tempOverride(ResultBuffer args)
		{
			tempOverride();
		}

		// Command: dblclick
		// This command adds a double click action for polylines (Non-LWpolylines like 2D polylines).
		// After running this command, When we double click a polyline (i.e., a non-light weight polyline), 
		// the "Properties" window is launched. This replaces the original behaviour where "pedit" was launched.
		[CommandMethod("dblclick")]
		public void doubleClick()
		{
			DoubleClickAction dblClickAction = new DoubleClickAction(cs.MenuGroup,"My Double click",-1);
			dblClickAction.Description = "Double Click Customization";
			dblClickAction.ElementID = "EID_mydblclick";
			dblClickAction.DxfName = "Polyline";
			DoubleClickCmd dblClickCmd = new DoubleClickCmd(dblClickAction);
			dblClickCmd.MacroID = "ID_Ai_propch";
			dblClickAction.DoubleClickCmd = dblClickCmd;
		}
		// Lisp callable function: dblclick
		// Lisp wrapper for dblclick command
		[LispFunction("dblclick")]
		public void doubleClick(ResultBuffer args)
		{
			doubleClick();
		}

		
		// Command: cuiall
		// Issuing this command will run the methods to make all changes to the UI
		// This will add the custom menu, toolbar, and shortcut, as well as 
		// dock the info palette on the right side.
		[CommandMethod("cuiall")]
		public void callForAllChanges()
		{
			addMenu();
			shortCut();
			addToolbar();
			dockInfoPalR();
			saveCui();
		}
		// Lisp callable function: cuiall
		// Lisp wrapper for cuiall command
		[LispFunction("cuiall")]
		public void callForAllChanges(ResultBuffer args)
		{
			callForAllChanges();
		}

	}
}
