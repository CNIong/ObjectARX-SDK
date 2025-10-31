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
using Autodesk.AutoCAD.DatabaseServices;

namespace EventsWatcher
{
	/// <summary>
	/// DocManEvents.
	/// </summary>
	public class DocManEvents
	{
		public DocManEvents()
		{
			m_bDone = false;
			m_docMan = Application.DocumentManager;
			Do();
		}

		private DocumentCollection m_docMan;
		private bool m_bDone;

		public void Do()
		{
			if(m_bDone == false)
			{
				m_bDone = true;
			}
			else
			{
				WriteLine("\nDocMan watcher is working.");
				return;
			}

			try
			{
				m_docMan.DocumentCreated += new DocumentCollectionEventHandler(callback_DocumentCreated);
				m_docMan.DocumentCreateStarted += new DocumentCollectionEventHandler(callback_DocumentCreateStarted);
				m_docMan.DocumentCreationCanceled += new DocumentCollectionEventHandler(callback_DocumentCreationCanceled);

				m_docMan.DocumentToBeDestroyed += new DocumentCollectionEventHandler(callback_DocumentToBeDestroyed);
				m_docMan.DocumentDestroyed += new DocumentDestroyedEventHandler(callback_DocumentDestroyed);
			
				m_docMan.DocumentToBeActivated += new DocumentCollectionEventHandler(callback_DocumentToBeActivated);
				m_docMan.DocumentActivated += new DocumentCollectionEventHandler(callback_DocumentActivated);
				m_docMan.DocumentActivationChanged += new DocumentActivationChangedEventHandler(callback_DocumentActivationChanged);

				m_docMan.DocumentToBeDeactivated += new DocumentCollectionEventHandler(callback_DocumentToBeDeactivated);
				m_docMan.DocumentBecameCurrent += new DocumentCollectionEventHandler(callback_DocumentBecameCurrent);

				m_docMan.DocumentLockModeWillChange += new DocumentLockModeWillChangeEventHandler(callback_DocumentLockModeWillChange);
				m_docMan.DocumentLockModeChanged += new DocumentLockModeChangedEventHandler(callback_DocumentLockModeChanged);
				m_docMan.DocumentLockModeChangeVetoed += new DocumentLockModeChangeVetoedEventHandler(callback_DocumentLockModeChangeVetoed);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void Undo()
		{
			if(m_docMan == null || m_bDone != true)
				return;

			try
			{
				m_docMan.DocumentCreated -= new DocumentCollectionEventHandler(callback_DocumentCreated);
				m_docMan.DocumentCreateStarted -= new DocumentCollectionEventHandler(callback_DocumentCreateStarted);
				m_docMan.DocumentCreationCanceled -= new DocumentCollectionEventHandler(callback_DocumentCreationCanceled);

				m_docMan.DocumentToBeDestroyed -= new DocumentCollectionEventHandler(callback_DocumentToBeDestroyed);
				m_docMan.DocumentDestroyed -= new DocumentDestroyedEventHandler(callback_DocumentDestroyed);
			
				m_docMan.DocumentToBeActivated -= new DocumentCollectionEventHandler(callback_DocumentToBeActivated);
				m_docMan.DocumentActivated -= new DocumentCollectionEventHandler(callback_DocumentActivated);
				m_docMan.DocumentActivationChanged -= new DocumentActivationChangedEventHandler(callback_DocumentActivationChanged);

				m_docMan.DocumentToBeDeactivated -= new DocumentCollectionEventHandler(callback_DocumentToBeDeactivated);
				m_docMan.DocumentBecameCurrent -= new DocumentCollectionEventHandler(callback_DocumentBecameCurrent);

				m_docMan.DocumentLockModeWillChange -= new DocumentLockModeWillChangeEventHandler(callback_DocumentLockModeWillChange);
				m_docMan.DocumentLockModeChanged -= new DocumentLockModeChangedEventHandler(callback_DocumentLockModeChanged);
				m_docMan.DocumentLockModeChangeVetoed -= new DocumentLockModeChangeVetoedEventHandler(callback_DocumentLockModeChangeVetoed);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}

			m_bDone = false;
		}

		private void callback_DocumentCreated(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentCreated - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentCreated"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}		
		}

		private void callback_DocumentCreateStarted(Object sender, DocumentCollectionEventArgs e)
		{
			try 
			{
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentCreateStarted - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentCreateStarted"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}		
		}
		
		private void callback_DocumentCreationCanceled(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentCreationCanceled - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentCreationCanceled"));
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
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentToBeDestroyed - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentToBeDestroyed"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentDestroyed(Object sender, DocumentDestroyedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("DocumentDestroyed - {0}", e.FileName));
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
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentToBeActivated - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentToBeActivated"));
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
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentToBeDeactivated - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentToBeDeactivated"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_DocumentBecameCurrent(Object sender, DocumentCollectionEventArgs e)
		{
			try
			{
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentBecameCurrent - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentBecameCurrent"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentActivationChanged(Object sender, DocumentActivationChangedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("DocumentActivationChanged - {0}", e.NewValue));
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
				if(e.Document != null && e.Document.Window != null)
					WriteLine(String.Format("DocumentActivated - {0}", e.Document.Window.Text));
				else
					WriteLine(String.Format("DocumentActivated"));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentLockModeWillChange(object sender, DocumentLockModeWillChangeEventArgs e)
		{
			try
			{
				WriteLine(String.Format("DocumentLockModeWillChange - from {0} to {1} with command {2}", e.MyCurrentMode, e.MyNewMode, e.GlobalCommandName));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentLockModeChanged(object sender, DocumentLockModeChangedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("DocumentLockModeChanged - from {0} to {1} with command {2}", e.MyPreviousMode, e.MyCurrentMode, e.GlobalCommandName));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_DocumentLockModeChangeVetoed(object sender, DocumentLockModeChangeVetoedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("DocumentLockModeChangeVetoed - {0}",	e.GlobalCommandName));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nDocMan Events: " + obj.ToString();
				Helper.StreamMessage(str);	
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine function

	}	// end of class DocManEvents
}

