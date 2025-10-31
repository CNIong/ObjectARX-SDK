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
	/// DocManForUI.
	/// </summary>
	public class DocManForUI
	{
		public DocManForUI()
		{
		}
		
		public void Do()
		{
			try
			{
				DocumentCollection m_docMan = Application.DocumentManager;

				// Used to plant and remove Doc or DB events if applicable.
				m_docMan.DocumentCreated += new DocumentCollectionEventHandler(callback_DocumentCreated);
				m_docMan.DocumentToBeDestroyed += new DocumentCollectionEventHandler(callback_DocumentToBeDestroyed);

				// Used to plant and remove Editor events if applicable.
				// Why? To workaround the limitation of that Editor object only works with the MdiActiveDocument.
				m_docMan.DocumentToBeActivated += new DocumentCollectionEventHandler(callback_DocumentToBeActivated);
				m_docMan.DocumentActivated += new DocumentCollectionEventHandler(callback_DocumentActivated);
				m_docMan.DocumentToBeDeactivated += new DocumentCollectionEventHandler(callback_DocumentToBeDeactivated);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentCreated(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				Document doc = e.Document;
				EventsWatcher.documentCreated(ref doc);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentToBeDestroyed(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				Document doc = e.Document;
				EventsWatcher.documentToBeDestroyed(ref doc);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentActivated(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				EventsWatcher.documentActivated();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_DocumentToBeActivated(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				EventsWatcher.documentActivated();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentToBeDeactivated(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				EventsWatcher.documentToBeDeactivated();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

	}	// end of class DocManForUI
}

