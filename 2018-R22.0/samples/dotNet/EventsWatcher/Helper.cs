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
using Autodesk.AutoCAD.ApplicationServices;

namespace EventsWatcher
{
	/// <summary>
	/// Helper class including some static helper functions.
	/// </summary>
	public class Helper
	{
		public static void StreamMessage(string str)
		{
			try
			{
				// Application.DocumentManager.Count should be used to check zero doc status
				// MdiActiveDocument returns non null sometimes even if in zero doc status!
				if(	Application.DocumentManager.MdiActiveDocument != null
					&& Application.DocumentManager.Count != 0)
					Helper.CmdLineMessage(str);
				else
					Helper.InfoMessageBox(str);

				Helper.StreamToRichTextControl(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public static void Message(System.Exception ex)
		{
			try
			{
				System.Windows.Forms.MessageBox.Show(
					ex.ToString(),
					"Error",
					System.Windows.Forms.MessageBoxButtons.OK,
					System.Windows.Forms.MessageBoxIcon.Error);
			}
			catch 
			{
			}
		}

		public static void InfoMessageBox(string str)
		{
			try
			{
				System.Windows.Forms.MessageBox.Show(
					str,
					"Events Watcher",
					System.Windows.Forms.MessageBoxButtons.OK,
					System.Windows.Forms.MessageBoxIcon.Information);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		// Please check the valibility of Editor object before calling this.
		public static void CmdLineMessage(string str)
		{
			try
			{
				if(	Application.DocumentManager.MdiActiveDocument != null
					&& Application.DocumentManager.Count != 0
					&& Application.DocumentManager.MdiActiveDocument.Editor != null)
				{
					Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage(str);
				}
				else
					return;
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public static void StreamToRichTextControl(string str)
		{
			try
			{
				if( ExtApp.outForm == null || ExtApp.outForm.richTextBox1 == null)
					return;

				ExtApp.outForm.richTextBox1.AppendText(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
	}

	// Helper class to workaround a Hashtable issue: 
	// Can't change values in a foreach loop or enumerator
	class CBoolClass
	{
		public CBoolClass(bool val) {this.val = val;}
		public bool val;
		public override string ToString(){return(val.ToString());}
	}
}

