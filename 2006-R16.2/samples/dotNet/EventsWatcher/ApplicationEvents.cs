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

namespace EventsWatcher
{
	/// <summary>
	/// ApplicationEvents.
	/// </summary>
	public class ApplicationEvents
	{
		public ApplicationEvents()
		{
			m_bDone = false;
			Do();
		}

		// Have the application events been planted?
		private bool m_bDone;

		public void Do()
		{
			if(m_bDone == false)
			{
				m_bDone = true;
			}
			else
				return;

			try
			{
				Application.BeginQuit += new EventHandler(callback_BeginQuit);
				Application.DisplayingCustomizeDialog += new TabbedDialogEventHandler(callback_DisplayingCustomizeDialog);
				Application.DisplayingDraftingSettingsDialog += new TabbedDialogEventHandler(callback_DisplayingDraftingSettingsDialog);
				Application.DisplayingOptionDialog += new TabbedDialogEventHandler(callback_DisplayingOptionDialog);
				Application.QuitAborted += new EventHandler(callback_QuitAborted);
				Application.QuitWillStart += new EventHandler(callback_QuitWillStart);
				Application.SystemVariableChanged += new Autodesk.AutoCAD.ApplicationServices.SystemVariableChangedEventHandler(callback_SystemVariableChanged);
				Application.SystemVariableChanging += new Autodesk.AutoCAD.ApplicationServices.SystemVariableChangingEventHandler(callback_SystemVariableChanging);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void Undo()
		{
			if(m_bDone == false)
				return;

			try 
			{
				Application.BeginQuit -= new EventHandler(callback_BeginQuit);
				Application.DisplayingCustomizeDialog -= new TabbedDialogEventHandler(callback_DisplayingCustomizeDialog);
				Application.DisplayingDraftingSettingsDialog -= new TabbedDialogEventHandler(callback_DisplayingDraftingSettingsDialog);
				Application.DisplayingOptionDialog -= new TabbedDialogEventHandler(callback_DisplayingOptionDialog);
				Application.QuitAborted -= new EventHandler(callback_QuitAborted);
				Application.QuitWillStart -= new EventHandler(callback_QuitWillStart);
				Application.SystemVariableChanged -= new Autodesk.AutoCAD.ApplicationServices.SystemVariableChangedEventHandler(callback_SystemVariableChanged);
				Application.SystemVariableChanging -= new Autodesk.AutoCAD.ApplicationServices.SystemVariableChangingEventHandler(callback_SystemVariableChanging);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
				
			m_bDone = false;
		}

		private void callback_BeginQuit(Object sender, EventArgs e)
		{
			// Actually MessageBox is used here as no editor is available at this time.
			// That is, AutoCAD has already been in zero doc status.
			WriteLine("BeginQuit");
			//System.Windows.Forms.MessageBox.Show("BeginQuit");
		}

		private void callback_DisplayingCustomizeDialog(Object sender, TabbedDialogEventArgs e)
		{
			WriteLine(String.Format("DisplayingCustomizeDialog"));
		}

		private void callback_DisplayingDraftingSettingsDialog(Object sender, TabbedDialogEventArgs e)
		{
			WriteLine(String.Format("DisplayingDraftingSettingsDialog"));
		}

		private void callback_DisplayingOptionDialog(Object sender, TabbedDialogEventArgs e)
		{
			WriteLine(String.Format("DisplayingOptionDialog"));
		}

		private void callback_QuitAborted(Object sender, EventArgs e)
		{
			// Actually MessageBox is used here as no editor is available at this time.
			// That is, AutoCAD has already been in zero doc status.
			WriteLine("QuitAborted");
			//System.Windows.Forms.MessageBox.Show("QuitAborted");
		}
		
		private void callback_QuitWillStart(Object sender, EventArgs e)
		{
			// Actually MessageBox is used here as no editor is available at this time.
			// That is, AutoCAD has already been in zero doc status.
			WriteLine("QuitWillStart");
			//System.Windows.Forms.MessageBox.Show("QuitWillStart");
		}		
		private void callback_SystemVariableChanged(Object sender, Autodesk.AutoCAD.ApplicationServices.SystemVariableChangedEventArgs e)
		{
			WriteLine(String.Format("SystemVariableChanged - {0}", e.Name));
		}
		
		private void callback_SystemVariableChanging(Object sender, Autodesk.AutoCAD.ApplicationServices.SystemVariableChangingEventArgs e)
		{
			WriteLine(String.Format("SystemVariableChanging - {0}", e.Name));
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nAPP Events: " + obj.ToString();
				Helper.StreamMessage(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine function

	}	// end of class ApplicationEvents
}

