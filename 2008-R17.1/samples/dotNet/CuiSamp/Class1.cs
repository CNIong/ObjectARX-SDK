// Copyright 2005-2007 by Autodesk, Inc.
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

using System.Runtime.InteropServices;
using System.Text;

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
// 6) Change position and docking of "Properties" palette
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
		// Dock Properties palette to the right
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
        // Dock Properties palette to the left
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
        // Set Properties palette to float
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


        // Method to implement the positiioning/docking of the "Properties" window
		private void dockInfoPalette(DockableWindowOrient orientation)
		{
			int wkB = cs.Workspaces.IndexOfWorkspaceName("AutoCAD Classic");
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
				//if(dockableWindow.Name.Equals("Info Palette"))
                if (dockableWindow.Name.Equals("Properties"))
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
        // dock the Properties palette on the right side.
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

    public class CUIStartup : IExtensionApplication
    {
        // Used to support the saving and updating of CUI settings.
        [DllImport("acad.exe", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "acedCmd")]
        private static extern int acedCmd(System.IntPtr vlist);

        //Constants used frequently below
        const String WORKSPACENAME = "Acme Workspace";
        const String ACADDEFAULT = "AutoCAD Default";
        const String ACADCLASSIC = "AutoCAD Classic";
                
        
        // All Cui files (main/partial/enterprise) have to be loaded into an object of class 
		// CustomizationSection
		// cs - main AutoCAD CUI file
		CustomizationSection cs;
		
		// ed - access to the AutoCAD Command Line
		// Allows us to write messages or Issue Commands in the interface
		Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

        [DllImport("acad.exe", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "ads_queueexpr")]
        extern static int ads_queueexpr(byte[] command);
        
        public void Initialize() 
        {
            try
            {
                // Create and fill the new Workspace, if it is not already filled.
                bool bCreated = false;
                Workspace newWs = CreateOrGetWorkspace(ref bCreated); // ...and recreate it anew.

                if (bCreated == true)
                {
                    // If we happened to create the workspace, then send the following commands to make sure the UI is updated immediately.
                    // UPDATECUI simply calls the SaveCUI method below.
                    // WSCURRENT sets the Workspace to our newly created workspace.
                    // The reason these must be issued via ads_queueexpr() is that AutoCAD is not yet ready to receive UI directives
                    // that update the editor - sending these through ads_queueexpr() will ensure that the request is sufficiently delayed.

                    UnicodeEncoding uEncode = new UnicodeEncoding();
                    ads_queueexpr(uEncode.GetBytes("(Command \"_UPDATECUI\")"));
                    ads_queueexpr(uEncode.GetBytes("(Command \"WSCURRENT\"  \"" + WORKSPACENAME + "\")"));
                }
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage("Error: " + ex.Message);
            }
        } 
        public void Terminate() { }

        //Default Constructor
        public CUIStartup()
		{
            // retrieve the location of, and open the ACAD Main CUI File
            string mainCuiFile = (string)Application.GetSystemVariable("MENUNAME");
            mainCuiFile += ".cui";
            cs = new CustomizationSection(mainCuiFile);
		}
        
        // This command will enforce the workspace settings - If the workspace doesn't yet exist, it is created.
        // If the workspace settings have been modified, they will be reset to their defaults.
        [CommandMethod("FORCEWS")]
        public void forceWorkspace()
        {
            try
            {
                RemoveAllComponents(); // Remove the workspace, if it exists...

                bool bCreated = false;
                Workspace newWs = CreateOrGetWorkspace(ref bCreated); // ...and recreate it anew.

                if (bCreated == true)
                {
                    // In this case, we have the luxury of having the UI ready for CUI directives.  We can simply call SaveCui and
                    // directly set the WSCURRENT variable without the need to send to the commandline.
                    saveCui(); // Save and reload the CUI file
                    // Set the workspace to the new/updated workspace.
                    Application.SetSystemVariable("WSCURRENT", WORKSPACENAME);
                }
            }
            catch (System.Exception ex)
            {
                ed.WriteMessage("Error: " + ex.Message);
            }
        }

        // This method will return the custom workspace, creating it if necessary.
        public Workspace CreateOrGetWorkspace(ref bool bCreated)
        {
            Workspace newWs;

            if (-1 == cs.Workspaces.IndexOfWorkspaceName(WORKSPACENAME)) // If the workspace doesnot exist
            {
                newWs = new Workspace(cs, WORKSPACENAME); // Create the workspace

                // Call each of these helper methods in-turn to create the CUI content.
                AssertCustomMenu(newWs);// Fill it with our menu's - custom and standard.
                AssertCustomToolbar(newWs); // new custom and standard Toolbar
                AssertDashboard(newWs); //New dashboard entry.

                // Save the changes...
                if (cs.IsModified)
                    cs.Save();

                bCreated = true;
            }
            else // Otherwise, just return the existing workspace.
            {
                bCreated = false;
                newWs = cs.getWorkspace(WORKSPACENAME);
            }

            
            return newWs;
        }

        // **************** Add a Custom Menu to the Workspace********************
        void AssertCustomMenu(Workspace newWs)
        {
            // Create a custom toolbar.  This will have the BOX and PYRAMID commands as well as the User Group and Online Developer Center
            // Command entries.
            
            // Give the toolbar an alias name.
            System.Collections.Specialized.StringCollection pmAliases = new System.Collections.Specialized.StringCollection();
            pmAliases.Add("POP12");

            PopMenu pm = new PopMenu("Custom Menu", pmAliases, "Custom Menu", cs.MenuGroup);

            addItemsToPM(pm); // Populate it with the menu entries...

            WorkspacePopMenu wkpm = new WorkspacePopMenu(newWs, pm);
            wkpm.Display = 1;


            // Now, add some Standard Toolbars from the *AutoCAD Default*  or *AutoCAD Classic* Workspace

            // First, get the AutoCAD Default workspace...
            Workspace defaultWS = cs.getWorkspace(ACADDEFAULT);
            if (defaultWS == null)
            {
                // If it is not found, get the AutoCAD Classic workspace...
                defaultWS = cs.getWorkspace(ACADCLASSIC);
                if (defaultWS == null)
                    throw new ApplicationException("Default AutoCAD Workspaces not found!");
            }

            // Add the standard "Help" Menu
            WorkspacePopMenu stMenu = defaultWS.WorkspacePopMenus.FindWorkspacePopMenu("ID_MnHelp", cs.MenuGroup.Name);
            if (stMenu != null)
            {
                WorkspacePopMenu stNewMenu = new WorkspacePopMenu(newWs, stMenu);
                //newWs.WorkspacePopMenus.Insert(0, stNewMenu);
                stNewMenu.Display = 1;
            }

            // Add the standard "Window" Menu
            stMenu = defaultWS.WorkspacePopMenus.FindWorkspacePopMenu("ID_MnWindow", cs.MenuGroup.Name);
            if (stMenu != null)
            {
                WorkspacePopMenu stNewMenu = new WorkspacePopMenu(newWs, stMenu);
                //newWs.WorkspacePopMenus.Insert(0, stNewMenu);
                stNewMenu.Display = 1;
            }

            // Add the standard "File" Menu
            stMenu = defaultWS.WorkspacePopMenus.FindWorkspacePopMenu("ID_MnFile", cs.MenuGroup.Name);
            if (stMenu != null)
            {
                WorkspacePopMenu stNewMenu = new WorkspacePopMenu(newWs, stMenu);
                //newWs.WorkspacePopMenus.Insert(0, stNewMenu);
                stNewMenu.Display = 1;
            }
        }

        // **************** Add a Custom Toolbar *******************
        void AssertCustomToolbar(Workspace newWs)
        {
            // Create a custom toolbar with the Polyline command and the Draw Flyout - along with the Layer dropdown control.
            
            // Create the toolbar
            Toolbar newTb = new Toolbar("New Toolbar", cs.MenuGroup);
            newTb.ToolbarOrient = ToolbarOrient.floating;
            newTb.ToolbarVisible = ToolbarVisible.show;

            // Add the Polyline command
            ToolbarButton tbBtn = new ToolbarButton(newTb, -1);
            tbBtn.Name = "PolyLine";
            tbBtn.MacroID = "ID_Pline";

            // Add the 'Draw' Flyout.
            ToolbarFlyout tbFlyout = new ToolbarFlyout(newTb, -1);
            tbFlyout.ToolbarReference = "DRAW";

            // Now add the Layer control.
            ToolbarControl tbCtrl = new ToolbarControl(ControlType.LayerControl, newTb, -1);

            // Add the toolbar to the workspace

            WorkspaceToolbar wkTb = new WorkspaceToolbar(newWs, newTb);
            newWs.WorkspaceToolbars.Add(wkTb);
            wkTb.Display = 1;

            // Now, add some *Standard Toolbars* from the AutoCAD Default Workspace

            // First, get the AutoCAD Default workspace...
            Workspace defaultWS = cs.getWorkspace(ACADDEFAULT);
            if (defaultWS == null)
            {
                // If it is not found, get the AutoCAD Classic workspace...
                defaultWS = cs.getWorkspace(ACADCLASSIC);
                if (defaultWS == null)
                    throw new ApplicationException("Default AutoCAD Workspaces not found!");
            }

            // Get the Standard toolbar and add it here - so we have some stock commands available.
            WorkspaceToolbar stWtb = defaultWS.WorkspaceToolbars.FindWorkspaceToolbar("ID_TbStandar", cs.MenuGroup.Name);
            if (stWtb != null)
            {
                WorkspaceToolbar stNewWtb = new WorkspaceToolbar(newWs, stWtb);
                //newWs.WorkspaceToolbars.Insert(0, stWtb);
                stNewWtb.Display = 1;
            }

            // Add the Workspaces toolbar, so we can switch back quickly...
            stWtb = defaultWS.WorkspaceToolbars.FindWorkspaceToolbar("ID_TbWorkspaces", cs.MenuGroup.Name);
            if (stWtb != null)
            {
                WorkspaceToolbar stNewWtb = new WorkspaceToolbar(newWs, stWtb);
                //newWs.WorkspaceToolbars.Insert(0, stWtb);
                stNewWtb.Display = 1;
            }
        }

        // **************** Add a Custom Dashboard entry *******************
        void AssertDashboard(Workspace newWs)
        {
            // Dashboard items have generally at least 2 panes - upper and lower.  This example demonstrates a 2-pane entry.
            
            // Add a dashboard panel entry who's top pane contains toolbar button commands CONE, SPHERE,
            // BOX, 3DPLINE, 3DORBIT, and 3DWALK.  The lower pane contains the Visual Styles and the
            // 3D Navigation View control.
            
            // Create the new upper panel.
            ToolPanel newUpperTp = new ToolPanel("Custom Panel Upper", cs.MenuGroup);
            newUpperTp.ToolbarOrient = ToolbarOrient.right;
            newUpperTp.ToolbarVisible = ToolbarVisible.show;

            // Add the CONE toolbar command
            ToolbarButton tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "Cone";
            tbBtn.MacroID = "ID_Ai_cone";

            // Add the SPHERE toolbar command
            tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "Sphere";
            tbBtn.MacroID = "ID_Ai_sphere";

            // Add the BOX toolbar command
            tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "Box";
            tbBtn.MacroID = "ID_Ai_box";

            // Add the 3D Polyline toolbar command.
            tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "3D Polyline";
            tbBtn.MacroID = "ID_3dpoly";

            // Add the 3D Orbit toolbar command
            tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "3D Orbit";
            tbBtn.MacroID = "ID_3d_orbit";

            // Add the 3D Walk toolbar command
            tbBtn = new ToolbarButton(newUpperTp, -1);
            tbBtn.Name = "3D Walk";
            tbBtn.MacroID = "ID_3DWalk";
            
            // Now, create the lower panel.
            ToolPanel newLowerTp = new ToolPanel("Custom Panel Lower", cs.MenuGroup);
            newLowerTp.ToolbarOrient = ToolbarOrient.right;
            newLowerTp.ToolbarVisible = ToolbarVisible.show;

            // Create the Visual Styles control
            ToolbarControl tbCtrl = new ToolbarControl(ControlType.VSStylesComboControl);
            newLowerTp.ToolbarItems.Insert(0, tbCtrl);

            // Create the 3D Navigation control
            tbCtrl = new ToolbarControl(ControlType._3DNavViewComboCtrl);
            newLowerTp.ToolbarItems.Insert(1, tbCtrl);

            // Now, we must create a Panel object to place our Upper and Lower ToolPanel objects to.
            // Each Panel object must live in a 'PanelSet' collection.  The global Customization Settings
            // keeps a collection of PanelSet collections within the MenuGroup, so this example demonstrates
            // using this collection.

            // So, Customization Group holds a collection of PanelSets
            // We Add our Panel object to the first one of these PanelSets.
            // We attach our upper and lower Tool Panel's to our Panel there.
                        
            // Get the first PanelSet in the Customization group.
            PanelSet panSet = cs.MenuGroup.DashboardPanelSet;
            if (panSet == null)
                throw new ApplicationException("No Existing Panel Set to use!");
            
            // Create our new Panel object, specifying our parent PanelSet.
            Panel newPan = new Panel("Custom Panel", panSet);

            // Attach our Panel to the retrived PanelSet.
            panSet.Panels.Add(newPan);

            // The way we attach our ToolPanel (Upper and Lower) is through the use of ToolPanelRef objects.
            ToolPanelRef upperRef = new ToolPanelRef(newUpperTp, newPan, PanelPosition.Upper);
            ToolPanelRef lowerRef = new ToolPanelRef(newLowerTp, newPan, PanelPosition.Lower);

            // Attach them.
            newPan.UpperPanel = upperRef;
            newPan.LowerPanel = lowerRef;

            // Now, finally add the Panel to the Workspace via a WorkSpacePanel, which is the same design pattern
            // as Menus and Toolbars.
            WorkspacePanel wsPan = new WorkspacePanel(newWs, newPan);
            //newWs.WorkspacePanels.Insert(0, wsPan);
        }

       
        // Add new Items to a PopMenu
       private void addItemsToPM(PopMenu pm)
       {
           PopMenuItem pmi = new PopMenuItem(pm, -1);
           pmi.MacroID = "ID_AUGI"; pmi.Name = "Autodesk User Group International";

           pmi = new PopMenuItem(pm, -1);
           pmi.MacroID = "ID_CustomSafe"; pmi.Name = "Online Developer Center";

           pmi = new PopMenuItem(pm, -1); // Separator

           pmi = new PopMenuItem(pm, -1);
           pmi.MacroID = "ID_Box";
           pmi.Name = "Box";

           pmi = new PopMenuItem(pm, -1);
           pmi.MacroID = "ID_Pyramid";
           pmi.Name = "Pyramid";

       }

        // Here is an example of how we can remove all of our UI elements.  This code can be run from out-of-process during uninstallation
        // of the product, though is not demonstrated here.  We still recommend that you load the CUI elements from first-run AutoCAD.
        [CommandMethod("REMOVEALL")]
        public void RemoveAllComponents()
        {
            Workspace newWs;

            if (-1 == cs.Workspaces.IndexOfWorkspaceName(WORKSPACENAME)) // If the workspace doesnot exist
                return;
            else
                newWs = cs.getWorkspace(WORKSPACENAME);
                        
            // Remove the Menus collection...
            while (newWs.WorkspacePopMenus.Count > 0)
                newWs.WorkspacePopMenus.RemoveAt(0);

            // Clear out the Custom Menu group...
            if (cs.MenuGroup.PopMenus.IsNameFree("Custom Menu") == false)
            {
                PopMenu pop = cs.MenuGroup.PopMenus.FindPopWithName("Custom Menu");
                cs.MenuGroup.PopMenus.Remove(pop);
            }

            // Next, make sure the workspace toolbars collection is empty

            while (newWs.WorkspaceToolbars.Count > 0)
                newWs.WorkspaceToolbars.RemoveAt(0);

            // Clear out the Custom Menu group...
            if (cs.MenuGroup.Toolbars.IsNameFree("New Toolbar") == false)
            {
                Toolbar tb = cs.MenuGroup.Toolbars.FindToolbarWithName("New Toolbar");
                cs.MenuGroup.Toolbars.Remove(tb);
            }

            while (newWs.WorkspacePanels.Count > 0)
                newWs.WorkspacePanels.RemoveAt(0);

            for (int i = cs.MenuGroup.DashboardPanelSet.Panels.Count - 1; i >= 0; i--)
                if ("Custom Panel" == cs.MenuGroup.DashboardPanelSet.Panels[i].Name)
                    cs.MenuGroup.DashboardPanelSet.Panels.Remove(i);

            // Now, clear out the Custom Panel group...
            if (cs.MenuGroup.ToolPanels.IsNameFree("Custom Panel") == false)
            {
                ToolPanel panel = cs.MenuGroup.ToolPanels.FindToolPanelWithName("Custom Panel");
                cs.MenuGroup.ToolPanels.Remove(panel);
            }

            // Finally, remove the workspace itself.

            if (cs.Workspaces.IndexOfWorkspaceName(WORKSPACENAME) > 0) // If the workspace doesnot exist
                cs.Workspaces.Remove(cs.Workspaces.IndexOfWorkspaceName(WORKSPACENAME));

            saveCui(); // Save and reload the CUI file

            Application.SetSystemVariable("WSCURRENT", ACADCLASSIC);

        }

        [CommandMethod("UPDATECUI")]
        public void saveCui()
        {
            // Save all Changes made to the CUI file in this session. 
            // If changes were made to the Main CUI file - save it
            // If changes were made to teh Partial CUI files need to save them too

            if (cs.IsModified)
                cs.Save();

            // Here we unload and reload the main CUI file so the changes to the CUI file could take effect immediately.
            // To do this we P/Invoke into acedCmd() in order to synchronously call the CUIUNLOAD / CUILOAD command, disarming and
            // rearming the file dialog during the process.
            
            ResultBuffer rb = new ResultBuffer();
            // RTSTR = 5005
            rb.Add(new TypedValue(5005, "FILEDIA"));
            rb.Add(new TypedValue(5005, "0"));
            // start the insert command
            acedCmd(rb.UnmanagedObject);

            string cuiFileName = cs.CUIFileBaseName;
            
            //CUIUNLOAD
            rb = new ResultBuffer();
            rb.Add(new TypedValue(5005,"_CUIUNLOAD"));
            rb.Add(new TypedValue(5005, cuiFileName));
            acedCmd(rb.UnmanagedObject);

            //CUILOAD
            rb = new ResultBuffer();
            rb.Add(new TypedValue(5005, "_CUILOAD"));
            rb.Add(new TypedValue(5005, cuiFileName));
            acedCmd(rb.UnmanagedObject);

            //FILEDIA
            rb = new ResultBuffer();
            rb.Add(new TypedValue(5005, "FILEDIA"));
            rb.Add(new TypedValue(5005, "1"));
            acedCmd(rb.UnmanagedObject);
         }
    }
}
