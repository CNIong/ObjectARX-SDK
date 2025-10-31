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

