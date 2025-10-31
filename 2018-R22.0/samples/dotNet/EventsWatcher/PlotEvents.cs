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
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.PlottingServices;

namespace EventsWatcher
{
	/// <summary>
	/// PlotEvents.
	/// </summary>
	public class PlotEvents
	{
		public PlotEvents()
		{
			m_bDone = false;
			m_plotMan = new PlotReactorManager();
			Do();
		}

		static private PlotReactorManager m_plotMan;
		private bool m_bDone;
		
		public void Do()
		{
			// Only plant it once.
			if(m_bDone == false)
			{
				m_bDone = true;
			}
			else
			{
				WriteLine("PlotEvents watcher is working.");
				return;
			}

			try
			{
				if( m_plotMan == null )
					m_plotMan = new PlotReactorManager();

				m_plotMan.BeginPlot += new BeginPlotEventHandler( callback_BeginPlot);
				m_plotMan.BeginDocument += new BeginDocumentEventHandler( callback_BeginDocument);
				m_plotMan.BeginPage += new BeginPageEventHandler( callback_BeginPage);
				m_plotMan.EndPlot += new EndPlotEventHandler( callback_EndPlot); 
				m_plotMan.EndDocument += new EndDocumentEventHandler( callback_EndDocument);
				m_plotMan.EndPage += new EndPageEventHandler( callback_EndPage); 
				m_plotMan.PlotCancelled += new PlotCancelledEventHandler( callback_PlotCancelled);
				m_plotMan.PageCancelled += new PageCancelledEventHandler( callback_PageCancelled);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void Undo()
		{
			if( m_plotMan == null || m_bDone == false)
				return;

			try
			{
				m_plotMan.BeginPlot -= new BeginPlotEventHandler( callback_BeginPlot);
				m_plotMan.BeginDocument -= new BeginDocumentEventHandler( callback_BeginDocument);
				m_plotMan.BeginPage -= new BeginPageEventHandler( callback_BeginPage);
				m_plotMan.EndPlot -= new EndPlotEventHandler( callback_EndPlot); 
				m_plotMan.EndDocument -= new EndDocumentEventHandler( callback_EndDocument);
				m_plotMan.EndPage -= new EndPageEventHandler( callback_EndPage); 
				m_plotMan.PlotCancelled -= new PlotCancelledEventHandler( callback_PlotCancelled);
				m_plotMan.PageCancelled -= new PageCancelledEventHandler( callback_PageCancelled);

				m_plotMan = null;
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}

			m_bDone = false;
		}

		void callback_BeginPlot(object sender, BeginPlotEventArgs e)
		{
			PlotProgress oPlotProgress = e.PlotProgress;
			if (oPlotProgress != null)
				WriteLine(string.Format("BeginPlot - PlotProgress.IsVisible:{0} PlotType:{1}",e.PlotProgress.IsVisible, e.PlotType));
			else
				WriteLine(string.Format("BeginPlot - PlotProgress:null PlotType:{0}", e.PlotType));
		}

		void callback_BeginDocument(object sender, BeginDocumentEventArgs e)
		{
			WriteLine(string.Format("BeginDocument - Copies:{0} DocumentName:{1} FileName:{2} PlotToFile:{3}",e.Copies,e.DocumentName,e.FileName,e.PlotToFile));
		}

		void callback_BeginPage(object sender, BeginPageEventArgs e)
		{
			WriteLine(string.Format("BeginPage - LastPage:{0} ConfigName:{1} PageInfo.EntityCount:{2}",e.LastPage, e.PlotInfo.OverrideSettings.PlotConfigurationName, e.PlotPageInfo.EntityCount));
		}

		void callback_EndPlot(object sender, EndPlotEventArgs e)
		{
			WriteLine(string.Format("EndPlot - Status:{0}", e.Status));
		}

		void callback_EndDocument(object sender, EndDocumentEventArgs e)
		{
			WriteLine(string.Format("EndDocument - Status:{0}",e.Status));
		}
	        
		void callback_EndPage(object sender, EndPageEventArgs e)
		{
			WriteLine(string.Format("EndPage - Status:{0}",e.Status));
		}
	        
		void callback_PlotCancelled(object sender, EventArgs e)
		{
			WriteLine(string.Format("PlotCancelled"));
		}
	        
		void callback_PageCancelled(object sender, EventArgs e)
		{
			WriteLine("PageCancelled");
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nPlot Events: " + obj.ToString();
				Helper.StreamMessage(str);	
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine function

	}	// end of class PlotEvents
}

