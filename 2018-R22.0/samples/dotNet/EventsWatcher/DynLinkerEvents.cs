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
using Autodesk.AutoCAD.PlottingServices;

namespace EventsWatcher
{
	/// <summary>
	/// DynLinkerEvents.
	/// </summary>
	public class DynLinkerEvents
	{
		public DynLinkerEvents()
		{
			m_bDone = false;
			m_dl = SystemObjects.DynamicLinker;
			Do();
		}

		DynamicLinker m_dl;
		private bool m_bDone;

		public void Do()
		{
			if(m_bDone == false)
				m_bDone = true;
			else
			{
				WriteLine("DynamicLinker watcher is working.");
				return;
			}

			try
			{
				m_dl.ModuleLoadAborted += new ModuleLoadAbortedEventHandler(callback_ModuleLoadAborted);
				m_dl.ModuleLoaded += new ModuleLoadedEventHandler(callback_ModuleLoaded);
				m_dl.ModuleLoading += new ModuleLoadingEventHandler(callback_ModuleLoading);
				m_dl.ModuleUnloadAborted += new ModuleUnloadAbortedEventHandler(callback_ModuleUnloadAborted);
				m_dl.ModuleUnloaded += new ModuleUnloadedEventHandler(callback_ModuleUnloaded);
				m_dl.ModuleUnloading += new ModuleUnloadingEventHandler(callback_ModuleUnloading);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void Undo()
		{
			try
			{
				m_dl.ModuleLoadAborted -= new ModuleLoadAbortedEventHandler(callback_ModuleLoadAborted);
				m_dl.ModuleLoaded -= new ModuleLoadedEventHandler(callback_ModuleLoaded);
				m_dl.ModuleLoading -= new ModuleLoadingEventHandler(callback_ModuleLoading);
				m_dl.ModuleUnloadAborted -= new ModuleUnloadAbortedEventHandler(callback_ModuleUnloadAborted);
				m_dl.ModuleUnloaded -= new ModuleUnloadedEventHandler(callback_ModuleUnloaded);
				m_dl.ModuleUnloading -= new ModuleUnloadingEventHandler(callback_ModuleUnloading);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}

			m_bDone = false;
		}

		private void callback_ModuleLoadAborted(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleLoadAborted - {0}", e.FileName));
		}

		private void callback_ModuleLoaded(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleLoaded - {0}", e.FileName));
		}

		private void callback_ModuleLoading(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleLoading - {0}", e.FileName));
		}

		private void callback_ModuleUnloadAborted(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleUnloadAborted - {0}", e.FileName));
		}

		private void callback_ModuleUnloaded(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleUnloaded - {0}", e.FileName));
		}

		private void callback_ModuleUnloading(Object sender, DynamicLinkerEventArgs e)
		{
			WriteLine(String.Format("ModuleUnloading - {0}", e.FileName));
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nDynLinker Events: " + obj.ToString();
				Helper.StreamMessage(str);				
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine() function

	}	// end of class DynLinkerEvents
}

