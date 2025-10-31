//Copyright (C) 2004 by Autodesk, Inc.
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
//(Rights in Technical Data and Computer Software), as applicable

using System;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.Windows;

[assembly: ExtensionApplication(typeof(EventsWatcher.ExtApp))]

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

