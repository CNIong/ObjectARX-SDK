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
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.Windows;

[assembly: ExtensionApplication(typeof(EventsWatcher.ExtApp))]
[assembly: CommandClass(null)]

namespace EventsWatcher
{
	/// <summary>
	/// ExtApp.
	/// </summary>
	public class ExtApp : IExtensionApplication
	{
		public ExtApp()
		{
		}

		public void Terminate() 
		{
			// We don't clean up watchers at this time. Let AutoCAD do so.
			//EventsWatcher.watchersOffDuty();

            // Remove the application default context menu.
            DefaultContextMenu.RemoveMe();
		}
		
		public static Output outForm;

		public void Initialize() 
		{
			try 
			{
				EventsWatcher.m_doApp = false;
				EventsWatcher.m_doPlot = false;
				EventsWatcher.m_doLayout = false;
				EventsWatcher.m_doLinker = false;
				EventsWatcher.m_doDocMan = false;
				EventsWatcher.m_doDoc = false;
				EventsWatcher.m_doDatabase = false;
				EventsWatcher.m_doEditor = false;

				EventsWatcher.m_showInput = false;
				EventsWatcher.m_suppressInputDuringDrag = true;

				EventsWatcher.m_appWatcher = null;
				EventsWatcher.m_dynLinkerWatcher = null;
				EventsWatcher.m_layoutManWatcher = null;
				EventsWatcher.m_plotWatcher = null;
				EventsWatcher.m_editorWatcher = null;
				EventsWatcher.m_docManWatcher = null;
				EventsWatcher.m_docWatcher = null;
				EventsWatcher.m_dbWatcher = null;

				EventsWatcher.m_docManForUI = new DocManForUI();
				EventsWatcher.m_docManForUI.Do();

				// Output form
				outForm = null;

				// Add a menu item to the application default context menu.
				DefaultContextMenu.AddMe();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
	}

	public class DefaultContextMenu
	{
        private static ContextMenuExtension s_cme;

        public static void RemoveMe()
        {
            Application.RemoveDefaultContextMenuExtension(s_cme);
        }

		public static void AddMe()
		{
			try
			{
				s_cme = new ContextMenuExtension();
				s_cme.Title = "Watcher";

				MenuItem mi = new MenuItem("Events Watcher ...");
				mi.Click += new EventHandler(callback_OnClick);
				s_cme.MenuItems.Add(mi);

				MenuItem mi1 = new MenuItem("Events Ouput Window");
				mi1.Click += new EventHandler(callback_OnClick1);
				s_cme.MenuItems.Add(mi1);

				Application.AddDefaultContextMenuExtension(s_cme);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private static void callback_OnClick(Object o, EventArgs e)
		{
			try
			{
				EventsWatcher ewForm = new EventsWatcher();
				
				// The following does not work well. Actually worse, it will cause AutoCAD hang.
				// ewForm.ShowDialog(Autodesk.AutoCAD.ApplicationServices.Application.MainWindow);
				
				// We need to use the AutoCAD way to show it.
				Application.ShowModalDialog(Application.MainWindow.Handle, ewForm);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private static void callback_OnClick1(Object o, EventArgs e)
		{
			try
			{
				if( ExtApp.outForm != null && !ExtApp.outForm.IsDisposed)
				{
					ExtApp.outForm.Close();
				}

				ExtApp.outForm = new Output();
				ExtApp.outForm.Show(); 
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
	}

}

