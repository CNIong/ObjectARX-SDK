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

