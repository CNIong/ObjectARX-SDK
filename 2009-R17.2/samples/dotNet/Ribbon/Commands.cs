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
using Autodesk.Windows;
using Autodesk.AutoCAD.ApplicationServices;
using acadApp = Autodesk.AutoCAD.ApplicationServices.Application;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using System.Windows;
using System.Windows.Data;
using Autodesk.AutoCAD.Ribbon;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Text;
using TaskDialogSampleWPF;

[assembly: CommandClass(typeof(AdskRibbon.Commands))]

namespace AdskRibbon
{
    /// <summary>
    /// - Class used to define AutoCAD commands and events.
    /// </summary>
    /// 
    public partial class Commands : IExtensionApplication
    {
        private static bool IsEntitySelected;
        public static ResourceDictionary RibbonDictionary;
        private static int counter;
        private static RibbonControl ribbonControl;
        private static DocumentsGalleryControl docsGalleryControl;
        private static LayoutListBoxControl layoutsListControl;
        private static bool IsRibbonUnloaded;
        private static bool IsActivationNeeded;

        public Commands()
        {
            IsEntitySelected = false;
            counter = 1;
            IsRibbonUnloaded = false;
            IsActivationNeeded = true;
        }

        public void Initialize()
        {
            acadApp.BeginQuit += new EventHandler(AdskRibbonBeginQuit);

            // Document specific events 
            DocumentCollection docColl = acadApp.DocumentManager;
            docColl.DocumentActivated += new DocumentCollectionEventHandler(AdskRibbonDocumentActivated);
            docColl.DocumentCreated += new DocumentCollectionEventHandler(AdskRibbonDocumentCreated);
            docColl.DocumentToBeDestroyed += new DocumentCollectionEventHandler(AdskRibbonDocumentToBeDestroyed);
            docColl.DocumentLockModeChanged += new DocumentLockModeChangedEventHandler(DocumentManager_DocumentLockModeChanged);

            
            // Load the ResourceDictionary that defines the RibbonPanels & Images
            RibbonDictionary = System.Windows.Application.LoadComponent(new Uri("/AdskRibbon;component/RibbonDictionary.xaml",
                                    UriKind.Relative)) as ResourceDictionary;

            // LayoutManager specific events
            LayoutManager layMgr = LayoutManager.Current;
            layMgr.LayoutSwitched += new LayoutEventHandler(AdskRibbonLayoutSwitched);
            layMgr.LayoutCreated += new LayoutEventHandler(AdskRibbonLayoutCreated);
            layMgr.LayoutRemoved += new LayoutEventHandler(AdskRibbonLayoutRemoved);
            layMgr.LayoutRenamed += new LayoutRenamedEventHandler(AdskRibbonLayoutRenamed);
            
            ribbonControl = Autodesk.AutoCAD.Ribbon.RibbonServices.RibbonPaletteSet.RibbonControl;
            
            // Ribbon Load and Unload events used to rebuild CustomTab if it present when Ribbon is unloaded
            RibbonPaletteSet paletteSet = Autodesk.AutoCAD.Ribbon.RibbonServices.RibbonPaletteSet;
            paletteSet.Unloading += new EventHandler(RibbonUnloading);
            paletteSet.Loaded += new EventHandler(RibbonLoaded);

            // For Menu browser commands. This initialization is necessary for the Menu Browser commands to
            // work properly.
            MenuBrowserMenu menu = Autodesk.AutoCAD.ApplicationServices.Application.MenuBrowserDatabase;
            string fullName = System.Windows.Forms.Application.ExecutablePath;
            int idx = fullName.LastIndexOf('\\');
            int idx2 = fullName.LastIndexOf('.');
            fullName = fullName.Substring(idx + 1, idx2 - idx - 1).ToUpper() + "::ID_Open";
            MenuBrowserMenuItem itemFile = menu.GetMenuItem(fullName, MenuItemQueryEnum.kByID, true);
            itemFile.IsLazyLoaded = false;
        }

        #region "RibbonCode"
        void RibbonUnloading(object sender, EventArgs e)
        {
            // Mark for rebuilding if our CustomTab is present during Ribbon Unloading
            RibbonTab tab = ribbonControl.FindTab("CustomTab");
            if (tab != null)
            {
                IsRibbonUnloaded = true;
                tab.Deactivated -= new EventHandler(AdskRibbonTabDeactivated);
            }
        }

        void RibbonLoaded(object sender, EventArgs e)
        {
            if(IsRibbonUnloaded)
            {
                acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("CustRibbon ", true, false, false);
                IsRibbonUnloaded = false;
            }
        }

        // LayoutSwitched event that will notify the LayoutListBoxControl
        void AdskRibbonLayoutSwitched(object sender, LayoutEventArgs e)
        {
            if (layoutsListControl != null)
            {
                layoutsListControl.ModifyContent(e.Name, ModificationType.Switch, null);
            }
        }

        // LayoutRenamed event that will notify the LayoutListBoxControl
        void AdskRibbonLayoutRenamed(object sender, LayoutRenamedEventArgs e)
        {
            if (layoutsListControl != null)
            {
                layoutsListControl.ModifyContent(e.Name, ModificationType.Rename, e.NewName);
            }
        }

        // LayoutRemoved event that will notify the LayoutListBoxControl
        void AdskRibbonLayoutRemoved(object sender, LayoutEventArgs e)
        {
            if (layoutsListControl != null)
            {
                layoutsListControl.ModifyContent(e.Name, ModificationType.Delete, null);
            }
        }

        // LayoutCreated event that will notify the LayoutListBoxControl
        void AdskRibbonLayoutCreated(object sender, LayoutEventArgs e)
        {
            if (layoutsListControl != null)
            {
                layoutsListControl.ModifyContent(e.Name, ModificationType.Add, null);
            }
        }

        // DocumentToBeDestroyed event that will notify the DocumentsGalleryControl
        void AdskRibbonDocumentToBeDestroyed(object sender, DocumentCollectionEventArgs e)
        {
            if (docsGalleryControl != null)
            {
                docsGalleryControl.RemoveItem(e.Document);
            }
        }

        // Remove the AdskRibbon specific tabs before quit
        void AdskRibbonBeginQuit(object sender, EventArgs e)
        {
            RibbonTab tab = ribbonControl.FindTab("CustomTab");
            if (tab != null)
            {
                ribbonControl.Tabs.Remove(tab);
                tab = null;
            }

            tab = ribbonControl.FindTab("CustomContextualTab");
            if (tab != null)
            {
                ribbonControl.Tabs.Remove(tab);
            }
        }

        // DocumentCreated event that will notify the DocumentsGalleryControl
        void AdskRibbonDocumentCreated(object sender, DocumentCollectionEventArgs e)
        {
            if (docsGalleryControl != null)
            {
                docsGalleryControl.AddNewItem(e.Document);
            }
        }

        // DocumentActivated event that will notify both DocumentsGalleryControl & LayoutListBoxControl
        void AdskRibbonDocumentActivated(object sender, DocumentCollectionEventArgs e)
        {
            if (docsGalleryControl != null)
            {
                docsGalleryControl.ResetCurrentItem();
            }

            if(layoutsListControl != null)
            {
                layoutsListControl.ResetContent();
            }
        }

        public void DocumentManager_DocumentLockModeChanged(object sender, DocumentLockModeChangedEventArgs e)
        {

            int nCount = acadApp.DocumentManager.Count;

            if (nCount == 1)
            {
                if (e.GlobalCommandName.ToUpper() == "CLOSE" || e.GlobalCommandName.ToUpper() == "#QUIT")
                {
                    if (docsGalleryControl != null)
                    {
                        docsGalleryControl.RemoveItem(e.Document);
                    }
                    RibbonTab tab = ribbonControl.FindTab("CustomTab");
                    if (tab != null)
                    {
                        ribbonControl.Tabs.Remove(tab);
                        tab = null;
                    }

                    tab = ribbonControl.FindTab("CustomContextualTab");
                    if (tab != null)
                    {
                        ribbonControl.Tabs.Remove(tab);
                    }
                }


            }

        }

        public void Terminate()
        {
            // Remove the events added above
            DocumentCollection docColl = acadApp.DocumentManager;
            docColl.DocumentActivated -= new DocumentCollectionEventHandler(AdskRibbonDocumentActivated);
            docColl.DocumentCreated -= new DocumentCollectionEventHandler(AdskRibbonDocumentCreated);
            docColl.DocumentToBeDestroyed -= new DocumentCollectionEventHandler(AdskRibbonDocumentToBeDestroyed);
            docColl.DocumentLockModeChanged -= new DocumentLockModeChangedEventHandler(DocumentManager_DocumentLockModeChanged);

            LayoutManager layMgr = LayoutManager.Current;
            layMgr.LayoutSwitched -= new LayoutEventHandler(AdskRibbonLayoutSwitched);
            layMgr.LayoutCreated -= new LayoutEventHandler(AdskRibbonLayoutCreated);
            layMgr.LayoutRemoved -= new LayoutEventHandler(AdskRibbonLayoutRemoved);
            layMgr.LayoutRenamed -= new LayoutRenamedEventHandler(AdskRibbonLayoutRenamed);

            RibbonPaletteSet paletteSet = Autodesk.AutoCAD.Ribbon.RibbonServices.RibbonPaletteSet;
            paletteSet.Unloading -= new EventHandler(RibbonUnloading);
            paletteSet.Loaded -= new EventHandler(RibbonLoaded);
        }

        /// <summary>
        /// - Select entity button click event
        /// - To demonstrate hosting a .NET 2.0 control on the AutoCAD Ribbon
        /// - Also, demonstrates the usage and creation of Contextual Tabs on the
        ///   Ribbon Bar
        /// </summary>
        /// 
        static void OnSelectEntityClick(object sender, RoutedEventArgs e)
        {
            Editor ed = acadApp.DocumentManager.MdiActiveDocument.Editor;
            Database db = HostApplicationServices.WorkingDatabase;

            PromptEntityOptions entOpts = new PromptEntityOptions("\nSelect an entity: ");
            entOpts.AllowNone = false;

            PromptEntityResult entRes = ed.GetEntity(entOpts);
            if (entRes.Status == PromptStatus.OK)
            {
                IsEntitySelected = true;

                RibbonTab tab = ribbonControl.FindTab("CustomContextualTab");
                if(tab == null)
                {
                    RibbonPanelSource panelSource = RibbonDictionary["Panel_3"] as RibbonPanelSource;
                    RibbonPanel panel = new RibbonPanel();
                    panel.Source = panelSource;

                    tab = new RibbonTab();
                    tab.Title = "Custom Contextual Tab";
                    tab.IsContextualTab = true;
                    tab.ContextualTabOption = ContextualTabOption.Merge;
                    tab.Panels.Add(panel);
                    tab.Id = "CustomContextualTab";
                    ribbonControl.Tabs.Add(tab);
                }

                RibbonPanelSource panelSrc = tab.Panels[0].Source;
                RibbonRow row = panelSrc.Rows[0];
                RibbonItem item = row.Items[0];
                if (item is RibbonForm)
                {
                    RibbonForm form = item as RibbonForm;
                    System.Windows.Forms.PropertyGrid grid = new System.Windows.Forms.PropertyGrid();
                    grid.Name = "Properties";
                    grid.Enabled = true;

                    PropertyGridContent gridContent = new PropertyGridContent();
                    using (Transaction tr = db.TransactionManager.StartTransaction())
                    {
                        Entity ent = (Entity)tr.GetObject(entRes.ObjectId, OpenMode.ForRead);
                        gridContent.Color = ent.Color.ColorNameForDisplay;
                        gridContent.Layer = ent.Layer;
                        gridContent.Linetype = ent.Linetype;
                        gridContent.LinetypeScale = ent.LinetypeScale.ToString();
                        gridContent.Lineweight = ent.LineWeight.ToString();
                        gridContent.Material = ent.Material;
                        gridContent.PlotStyle = ent.PlotStyleName;
                    }

                    grid.SelectedObject = gridContent;
                    form.Control = grid;
                    form.Host.Height = 200;
                    form.Host.Width = 200;
                }                
            }
        }

        static void OnCreateNewLayoutClick(object sender, RoutedEventArgs e)
        {
            acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("CreateLayout ", true, false, false);
        }

        static void OnDropDownButtonItemSelected(object sender, ItemSelectedEventArgs e)
        {
            RibbonButton button = e.SelectedItem as RibbonButton;

            if (button != null)
            {
                switch (button.Id)
                {
                    case "adw:RibbonButton_1":
                        acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("_new ", true, false, false);
                        break;
                    case "adw:RibbonButton_2":
                        acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("_open ", true, false, false);
                        break;
                    default:
                        break;
                }
            }
        }

        static void OnDropDownButtonClick(object sender, RoutedEventArgs e)
        {
            RibbonDropDownButton dropDownButton = sender as RibbonDropDownButton;
            RibbonButton button = dropDownButton.Current as RibbonButton;

            if (button != null)
            {
                switch (button.Id)
                {
                    case "adw:RibbonButton_1":
                        acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("_new ", true, false, false);
                        break;
                    case "adw:RibbonButton_2":
                        acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("_open ", true, false, false);
                        break;
                    default:
                        break;
                }
            }
        }

        // Remove the contextual tab if present when our Custom Tab is deactivated
        static void AdskRibbonTabDeactivated(object sender, EventArgs e)
        {
            RibbonTab tab = ribbonControl.FindTab("CustomContextualTab");
            if (tab != null && IsEntitySelected == true)
            {
                acadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("RemoveContextualTab ", true, false, false);
            }
            IsEntitySelected = false;
        }

        // Command to remove the contextual tab if present
        [CommandMethod("RemoveContextualTab")]
        static public void RemoveContextualTab()
        {
            RibbonTab tab = ribbonControl.FindTab("CustomContextualTab");
            if (tab != null)
            {
                ribbonControl.Tabs.Remove(tab);
            }
        }

        // Command to create a Layout
        [CommandMethod("CreateLayout")]
        static public void CreateLayout()
        {
            LayoutManager layMgr = LayoutManager.Current;
            string layoutName = "AdskRibbon" + counter.ToString();

            do
            {
                counter++;
                if (layMgr.GetLayoutId(layoutName) == ObjectId.Null)
                {
                    layMgr.CreateLayout(layoutName);
                    break;
                }
                else
                {
                    layoutName = "AdskRibbon" + counter.ToString();
                }
            }
            while (true);
        }

        /// <summary>
        /// - COMMAND TO DEMONSTRATE THE RIBBON API 
        /// - Please follow the comments below
        /// </summary>
        /// 
        [CommandMethod("CustRibbon")]
        static public void AdskRibbonCreate()
        {
            /// Start - Create a RibbonPanel using the ResourceDictionary in XAML file
            /// 

            Editor ed = acadApp.DocumentManager.MdiActiveDocument.Editor;
            // Check to create the CustomTab only if it is not present
            RibbonTab tabCheck = ribbonControl.FindTab("CustomTab");
            if (tabCheck != null)
            {
                ed.WriteMessage("The custom tab already exists.");
                return;
            }

            RibbonPanel panel = new RibbonPanel();
            panel.Source = RibbonDictionary["Panel_1"] as RibbonPanelSource;

            // Populate the documents gallery control using Initialize() method
            RibbonRow ribbonRow = panel.Source.Rows[0];
            docsGalleryControl = ribbonRow.Items[0] as DocumentsGalleryControl;
            docsGalleryControl.Initialize();

            ribbonRow = panel.Source.Rows[1];
            RibbonItemCollection coll = ribbonRow.Items;
            foreach (RibbonItem item in coll)
            {
                if (item is RibbonDropDownButton)
                {
                    RibbonDropDownButton dropDownButton = (RibbonDropDownButton)item;
                    // Add events for the RibbonDropDownButton
                    dropDownButton.ItemSelected += new RibbonDropDownButton.ItemSelectedEventHandler(OnDropDownButtonItemSelected);
                    dropDownButton.Click += new RoutedEventHandler(OnDropDownButtonClick);
                }
            }
            ///
            /// End - Create a RibbonPanel using the ResourceDictionary in XAML file
            
            /// Start - Create a RibbonPanel runtime without a resource
            /// 

            // Populate the layouts gallery control using Initialize() method
            layoutsListControl = new LayoutListBoxControl();
            layoutsListControl.Initialize();
            RibbonRow row1 = new RibbonRow();
            row1.Items.Add(layoutsListControl);

            RibbonButton btn1 = new RibbonButton();
            btn1.Text = "Create Layout";
            btn1.Image = RibbonDictionary["LayoutImage"] as BitmapImage;
            btn1.Orientation = Orientation.Horizontal;
            btn1.Size = RibbonItemSize.Large;
            btn1.ShowText = true;
            btn1.Click += new RoutedEventHandler(OnCreateNewLayoutClick);

            RibbonSeparator seperator = new RibbonSeparator();
            seperator.SeparatorStyle = RibbonSeparatorStyle.Spacer;
            
            RibbonButton btn2 = new RibbonButton();
            btn2.Text = "Select Entity";
            btn2.Image = RibbonDictionary["EntSelImage"] as BitmapImage;
            btn2.Orientation = Orientation.Horizontal;
            btn2.Size = RibbonItemSize.Large;
            btn2.Height = btn1.Height;
            btn2.ShowText = true;
            btn2.Click += new RoutedEventHandler(OnSelectEntityClick);

            RibbonRow row2 = new RibbonRow();
            row2.Items.Add(btn1);
            row2.Items.Add(seperator);
            row2.Items.Add(btn2);
            row2.IsInSlideoutPanel = true;

            RibbonPanelSource panSrc2 = new RibbonPanelSource();
            panSrc2.Title = "Layouts";
            panSrc2.Rows.Add(row1);
            panSrc2.Rows.Add(row2);

            RibbonPanel panel2 = new RibbonPanel();
            panel2.Source = panSrc2;
            ///
            /// End - Create a RibbonPanel runtime without a resource

            // Create a tab and add the two panels created above
            RibbonTab tab = new RibbonTab();
            tab.Title = "Custom Tab";
            tab.Id = "CustomTab";
            tab.IsContextualTab = false;
            tab.Panels.Add(panel);
            tab.Panels.Add(panel2);
            tab.Deactivated += new EventHandler(AdskRibbonTabDeactivated);

            ribbonControl.Tabs.Add(tab);
            // activate the custom tab when it is built the first time
            if(IsActivationNeeded)
            {
                tab.IsActive = true;
                ribbonControl.ActiveTab = tab;
                IsActivationNeeded = false;
            }
        }
        #endregion

        #region "TaskDialog"
        [CommandMethod("TaskDialogSimple")]
        public void TaskDialogSimple()
        {
            // simply show a task dialog
            // 1) parent of the window
            // 2) main instruction
            // 3) content
            // 4) window title
            // 5) available buttons
            // 6) icon
            
            // create a task dialog
            TaskDialog taskDialog = new TaskDialog();

            // set the dialog data
            taskDialog.WindowTitle = "Materials - Name Conflict";
            taskDialog.MainInstruction = "The material 'name' already exists in the current drawing.";
            taskDialog.ContentText = "Do you want to overwrite?";
            taskDialog.CommonButtons = (TaskDialogCommonButtons.Yes | TaskDialogCommonButtons.No);
            taskDialog.MainIcon = TaskDialogIcon.Warning;

            if (taskDialog.Show(null) == (int)MessageBoxResult.Yes)
            {

                TaskDialog taskDialog2 = new TaskDialog();
                taskDialog2.WindowTitle = "Existing material has been overwritten with the new one.";
                taskDialog2.MainInstruction = "Materials - Name Conflict";
                taskDialog2.Show(null);

            }

        }

        [CommandMethod("TaskDialogProgressBar")]
        public void TaskDialogProgressBar()
        {
            // create a task dialog
            TaskDialog taskDialog = new TaskDialog();

            // set the dialog data
            taskDialog.WindowTitle = "Window Title";
            taskDialog.MainInstruction = "Main Instruction";
            taskDialog.ContentText = "Content Text - <a href=\"http://www.autodesk.com\">Autodesk</a>";
            taskDialog.FooterText = "Footer Text";
            taskDialog.ExpandedText = "Expanded Text";
            taskDialog.ShowProgressBar = true;
            taskDialog.AllowDialogCancellation = true;

            // we let the user cancel the process and hereby close the dialog
            taskDialog.CommonButtons = TaskDialogCommonButtons.Cancel;

            // have to enable this, so that we can update the progress bar
            taskDialog.CallbackTimer = true;

            // have to enable this, so that we can act on hyperlink clicks
            taskDialog.EnableHyperlinks = true;

            // assign a handler to the dialog, so that ...
            // 1) we can update the progress bar
            // 2) we can handle clicks on hyperlinks
            taskDialog.Callback = new TaskDialogCallback(this.TaskDialogCallback);

            // simply show the task dialog and check the result, 
            // whether it has been completed or cancelled
            if (taskDialog.Show() == (int)MessageBoxResult.Cancel)
                System.Windows.MessageBox.Show("The operation has been cancelled");
            else
                System.Windows.MessageBox.Show("The operation has been completed");
        }

        private bool TaskDialogCallback(ActiveTaskDialog taskDialog, TaskDialogEventArgs args, object callbackData)
        {
            if (args.Notification == TaskDialogNotification.Created)
            {
                // initialize things if needed
            }
            else if (args.Notification == TaskDialogNotification.Timer)
            {
                if (args.TimerTickCount < 10000)
                {
                    // set the position of the progress bar
                    taskDialog.SetProgressBarPosition(((int)(args.TimerTickCount)) / 100);
                    taskDialog.SetMainInstruction(args.TimerTickCount.ToString());
                }
                else if (args.TimerTickCount < 11000)
                {
                    // done
                    taskDialog.SetProgressBarPosition(100);
                }
                else if (args.TimerTickCount < 12000)
                {
                    // we reached the end of the loading process, so let's 
                    // close the dialog and make the result 'OK'
                    taskDialog.ClickButton((int)System.Windows.Forms.DialogResult.OK);

                    // NOTE: if the user pressed the Cancel button in 
                    // the meantime, so this code is not reached, then the result will be 'Cancel'
                }
                else
                {
                    // reset timer
                    return true;
                }
            }
            else if (args.Notification == TaskDialogNotification.HyperlinkClicked)
            {
                // let's deal with hyperlinks
                // if it starts with http (i.e. web address) then we bring it up in a browser
                // using shell
                if (args.Hyperlink.StartsWith("http:", System.StringComparison.InvariantCultureIgnoreCase))
                {
                    System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo();
                    psi.FileName = args.Hyperlink;
                    psi.UseShellExecute = true;
                    System.Diagnostics.Process.Start(psi);
                }
            }
            else if (args.Notification == TaskDialogNotification.Destroyed)
            {
                // do something before the dialog is closed
            }

            return false;
        }

        [CommandMethod("TaskDialogWPF")]
        public void TaskDialogWPF()
        {
            // here we create a dictionary with values to override the default ones
            System.Collections.Generic.Dictionary<string, string> keyValues = new System.Collections.Generic.Dictionary<string, string>();

            // e.g. in this case everywhere in our dialog the %Name% string will be replaced by Wood
            keyValues.Add("Name", "Wood");

            // we have to specify the location of our dialog
            // 1a) /AdskRibbon -> short name for the referenced assembly 
            // 1b) ;component -> the assembly being referred to is referenced from the local assembly
            // 1c) /MyTaskDialogs.xaml -> name of the resource file, including its 
            // path relative to the root of the referenced assembly's project folder
            // 2) RelativeOrAbsolute -> application may accept a user-provided pack URI at run time, 
            // in which case the pack URI might be either absolute or relative
            // 3) MyProduct.MyTaskDialog1 -> the id which identifies our dialog in 
            // the MyTaskDialogs.xaml file inside the <TaskDialog> tag:
            // <TaskDialog x:Key="MyProduct.MyTaskDialog1" ... 
            TaskDialog taskDlg = TaskDialog.CreateFromFile(
                new System.Uri("/AdskRibbon;component/MyTaskDialogs.xaml",
                System.UriKind.RelativeOrAbsolute),
                "MyProduct.MyTaskDialog1", keyValues);

            // we now have access to the dialog and we just have to display it
            bool verFlgChkd;
            int radbtnRes;
            int dlgRes = taskDlg.Show(IntPtr.Zero, out verFlgChkd, out radbtnRes);
            switch (dlgRes)
            {
                // create a copy
                case 101:
                    System.Windows.MessageBox.Show("Create a copy" + (verFlgChkd ? " [Suppressed]" : ""));
                    break;
                // overwrite
                case 102:
                    System.Windows.MessageBox.Show("Overwrite" + (verFlgChkd ? " [Suppressed]" : ""));
                    break;
                // cancel
                default:
                    // the verFlgChkd may be true if the user ticked the checkbox and clicked Cancel, 
                    // but the dialog will come up next time anyway for Cancel is not a valid value for suppressing
                    System.Windows.MessageBox.Show("Cancel" + (verFlgChkd ? " [Suppressed]" : ""));
                    break;
            }
        }
        #endregion

        #region "ToolTip"
        [CommandMethod("ToolTip")]
        public void ToolTip()
        {
            MyWindow myWindow = new MyWindow();

            // show the window which contains buttons with tooltips 
            Autodesk.AutoCAD.ApplicationServices.Application.ShowModalWindow(myWindow);
        }
        #endregion

        #region "MenuBrowser"
        [CommandMethod("MbShow")]
        public static void showMenuBrowser()
        {
            // Show the MenuBrowser Window at (100,100)
            MenuBrowserMenu menu = Autodesk.AutoCAD.ApplicationServices.Application.MenuBrowserDatabase;
            if (menu != null)
            {
                MenuBrowserShow.ShowMB(100, 100, 0, menu, false, IntPtr.Zero, '\0');
            }
        }

        [CommandMethod("MbAdd")]
        public static void addMenuBrowserItem()
        {
            // Add a new Item after “File > Open”, with the name “NewItemForTest” and if you click it,
            // the command “time” will be execute.
            MenuBrowserMenu menu = Autodesk.AutoCAD.ApplicationServices.Application.MenuBrowserDatabase;
            if (menu != null)
            {
                // The current UID is organized as "MenuGroupName::ID"
                string fullName = System.Windows.Forms.Application.ExecutablePath;
                int idx2 = fullName.LastIndexOf('\\');
                int idx3 = fullName.LastIndexOf('.');
                fullName = fullName.Substring(idx2 + 1, idx3 - idx2 - 1).ToUpper() + "::ID_Open";
                MenuBrowserMenuItem itemOpen = menu.GetMenuItem(fullName, MenuItemQueryEnum.kByID, true);
                
                if (itemOpen != null)
                {
                    MenuBrowserMenuItem newItem = new MenuBrowserMenuItem();
                    // The Header is the string to show in the MenuBrowser
                    newItem.Header = "NewItemForTest";
                    // You must have a unique ID for any items. Otherwise the menuItems cannot be executed.
                    newItem.UID = "ID_ForTest1";
                    // The macro is the command you attached to the Menu Item
                    newItem.Macro = "\u0003\u0003_time ";

                    MenuBrowserMenuItem itemParent = itemOpen.Parent as MenuBrowserMenuItem;
                    int idx = itemParent.Items.IndexOf(itemOpen);
                    itemParent.Items.Insert(idx + 1, newItem);
                }
                MenuBrowserShow.ShowMB(100, 100, 0, menu, false, IntPtr.Zero, '\0');
            }
        }

        [CommandMethod("MbDel")]
        public static void delMenuBrowserItem()
        {
            // Remove the “File > Open” from MenuBrowser
            MenuBrowserMenu menu = Autodesk.AutoCAD.ApplicationServices.Application.MenuBrowserDatabase;
            if (menu != null)
            {
                // The current UID is organized as "MenuGroupName::ID"
                string fullName = System.Windows.Forms.Application.ExecutablePath;
                int idx2 = fullName.LastIndexOf('\\');
                int idx3 = fullName.LastIndexOf('.');
                fullName = fullName.Substring(idx2 + 1, idx3 - idx2 - 1).ToUpper() + "::ID_Open";
                MenuBrowserMenuItem itemOpen = menu.GetMenuItem(fullName, MenuItemQueryEnum.kByID, true);
                if (itemOpen != null)
                {
                    MenuBrowserMenuItem itemParent = itemOpen.Parent as MenuBrowserMenuItem;
                    itemParent.Items.Remove(itemOpen);
                }
                MenuBrowserShow.ShowMB(100, 100, 0, menu, false, IntPtr.Zero, '\0');
            }
        }

        [CommandMethod("MbAddMenu")]
        public static void addMenuBrowserMenu()
        {
            // Add a new Root Menu
            MenuBrowserMenu menu = Autodesk.AutoCAD.ApplicationServices.Application.MenuBrowserDatabase;
            if (menu != null)
            {
                MenuBrowserMenuItem rootMenu = new MenuBrowserMenuItem();
                rootMenu.Header = "NewMenu";
                rootMenu.UID = "ID_NewRootMenu";

                MenuBrowserMenuItem newItem = new MenuBrowserMenuItem();
                // The Header is the string to show in the MenuBrowser
                newItem.Header = "NewItem1_Time";
                // You must have a unique ID for any items. Otherwise the menuItems cannot be executed.
                newItem.UID = "ID_NewItem1";
                // The macro is the command you attached to the Menu Item
                newItem.Macro = "\u0003\u0003_time ";
                rootMenu.Items.Add(newItem);

                MenuBrowserMenuItem subMenu1 = new MenuBrowserMenuItem();
                subMenu1.Header = "SubMenu1";
                subMenu1.UID = "ID_NewSubMenu1";
                rootMenu.Items.Add(subMenu1);

                newItem = new MenuBrowserMenuItem();
                newItem.Header = "NewItem2_About";
                newItem.UID = "ID_NewItem2";
                newItem.Macro = "\u0003\u0003_about ";
                subMenu1.Items.Add(newItem);

                newItem = new MenuBrowserMenuItem();
                newItem.Header = "-";
                newItem.IsSeparator = true;
                subMenu1.Items.Add(newItem);

                MenuBrowserMenuItem subMenu2 = new MenuBrowserMenuItem();
                subMenu2.Header = "SubMenu2";
                subMenu2.UID = "ID_NewSubMenu2";
                subMenu1.Items.Add(subMenu2);

                newItem = new MenuBrowserMenuItem();
                newItem.Header = "NewItem3_Open";
                newItem.UID = "ID_NewItem3";
                newItem.Macro = "\u0003\u0003_open ";
                subMenu2.Items.Add(newItem);

                newItem = new MenuBrowserMenuItem();
                newItem.Header = "NewItem4_SaveAs";
                newItem.UID = "ID_NewItem4";
                newItem.Macro = "\u0003\u0003_saveas ";
                subMenu2.Items.Add(newItem);

                menu.Items.Insert(0, rootMenu);
                MenuBrowserShow.ShowMB(100, 100, 0, menu, false, IntPtr.Zero, '\0');
            }
        }
        #endregion
    }
}