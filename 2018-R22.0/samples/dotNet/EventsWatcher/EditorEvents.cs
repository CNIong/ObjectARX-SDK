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
using Autodesk.AutoCAD.EditorInput;

namespace EventsWatcher
{
	/// <summary>
	/// EditorEvents.
	/// </summary>
	public class EditorEvents
	{
		public EditorEvents()
		{
			try
			{
				m_bDone = false; // Have Editor Events been planted?
				m_bShownInput = false; // Have point monitor&filter been planted?
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private Editor m_ed;
		private bool m_bDone;
		private bool m_bShownInput;

		public void Do()
		{
			try 
			{
				// Events other than point filter&monitor
				if( !m_bDone )
				{
					// Keep record the Editor object.
					// Note: the m_ed is valid only for the current/active MdiDocument.
					// Therefore, we plant the Editor events when document has been activated
					// and remove them when it is to be deactivated.
					if(	Application.DocumentManager.MdiActiveDocument != null
						&& Application.DocumentManager.Count != 0
						&& Application.DocumentManager.MdiActiveDocument.Editor != null)
						m_ed = Application.DocumentManager.MdiActiveDocument.Editor;
					else
						return;

					m_ed.EnteringQuiescentState += new System.EventHandler(callback_EnteringQuiescentState);
					m_ed.LeavingQuiescentState += new System.EventHandler(callback_LeavingQuiescentState);
				
					m_ed.PromptedForAngle += new PromptDoubleResultEventHandler(callback_PromptedForAngle);
					m_ed.PromptedForCorner += new PromptPointResultEventHandler(callback_PromptedForCorner);
					m_ed.PromptedForDistance += new PromptDoubleResultEventHandler(callback_PromptedForDistance);
					m_ed.PromptedForDouble += new PromptDoubleResultEventHandler(callback_PromptedForDouble);
					m_ed.PromptedForEntity += new PromptEntityResultEventHandler(callback_PromptedForEntity);
					m_ed.PromptedForInteger += new PromptIntegerResultEventHandler(callback_PromptedForInteger);
					m_ed.PromptedForKeyword += new PromptStringResultEventHandler(callback_PromptedForKeyword);
					m_ed.PromptedForNestedEntity += new PromptNestedEntityResultEventHandler(callback_PromptedForNestedEntity);
					m_ed.PromptedForPoint += new PromptPointResultEventHandler(callback_PromptedForPoint);
					m_ed.PromptedForSelection += new PromptSelectionResultEventHandler(callback_PromptedForSelection);
					m_ed.PromptedForString += new PromptStringResultEventHandler(callback_PromptedForString);
					m_ed.PromptForEntityEnding += new PromptForEntityEndingEventHandler(callback_PromptForEntityEnding);
					m_ed.PromptForSelectionEnding += new PromptForSelectionEndingEventHandler(callback_PromptForSelectionEnding);
					m_ed.PromptingForAngle += new PromptAngleOptionsEventHandler(callback_PromptingForAngle);
					m_ed.PromptingForCorner += new PromptPointOptionsEventHandler(callback_PromptingForCorner);
					m_ed.PromptingForDistance += new PromptDistanceOptionsEventHandler(callback_PromptingForDistance);
					m_ed.PromptingForDouble += new PromptDoubleOptionsEventHandler(callback_PromptingForDouble);
					m_ed.PromptingForEntity += new PromptEntityOptionsEventHandler(callback_PromptingForEntity);
					m_ed.PromptingForInteger += new PromptIntegerOptionsEventHandler(callback_PromptingForInteger);
					m_ed.PromptingForKeyword += new PromptKeywordOptionsEventHandler(callback_PromptingForKeyword);
					m_ed.PromptingForNestedEntity += new PromptNestedEntityOptionsEventHandler(callback_PromptingForNestedEntity);
					m_ed.PromptingForPoint += new PromptPointOptionsEventHandler(callback_PromptingForPoint);
					m_ed.PromptingForSelection += new PromptSelectionOptionsEventHandler(callback_PromptingForSelection);
					m_ed.PromptingForString += new PromptStringOptionsEventHandler(callback_PromptingForString);
					m_ed.SelectionAdded += new SelectionAddedEventHandler(callback_SelectionAdded);
					m_ed.SelectionRemoved += new SelectionRemovedEventHandler(callback_SelectionRemoved);
                    m_ed.Dragging += new DraggingEventHandler(callback_Dragging);
                    m_ed.DraggingEnded += new DraggingEndedEventHandler(callback_DraggingEnded);
					m_bDone = true;
				}
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
				if( m_bDone )
				{
					if(	m_ed == null )
						return;

					m_ed.EnteringQuiescentState -= new System.EventHandler(callback_EnteringQuiescentState);
					m_ed.LeavingQuiescentState -= new System.EventHandler(callback_LeavingQuiescentState);
					
					m_ed.PromptedForAngle -= new PromptDoubleResultEventHandler(callback_PromptedForAngle);
					m_ed.PromptedForCorner -= new PromptPointResultEventHandler(callback_PromptedForCorner);
					m_ed.PromptedForDistance -= new PromptDoubleResultEventHandler(callback_PromptedForDistance);
					m_ed.PromptedForDouble -= new PromptDoubleResultEventHandler(callback_PromptedForDouble);
					m_ed.PromptedForEntity -= new PromptEntityResultEventHandler(callback_PromptedForEntity);
					m_ed.PromptedForInteger -= new PromptIntegerResultEventHandler(callback_PromptedForInteger);
					m_ed.PromptedForKeyword -= new PromptStringResultEventHandler(callback_PromptedForKeyword);
					m_ed.PromptedForNestedEntity -= new PromptNestedEntityResultEventHandler(callback_PromptedForNestedEntity);
					m_ed.PromptedForPoint -= new PromptPointResultEventHandler(callback_PromptedForPoint);
					m_ed.PromptedForSelection -= new PromptSelectionResultEventHandler(callback_PromptedForSelection);
					m_ed.PromptedForString -= new PromptStringResultEventHandler(callback_PromptedForString);
					m_ed.PromptForEntityEnding -= new PromptForEntityEndingEventHandler(callback_PromptForEntityEnding);
					m_ed.PromptForSelectionEnding -= new PromptForSelectionEndingEventHandler(callback_PromptForSelectionEnding);
					m_ed.PromptingForAngle -= new PromptAngleOptionsEventHandler(callback_PromptingForAngle);
					m_ed.PromptingForCorner -= new PromptPointOptionsEventHandler(callback_PromptingForCorner);
					m_ed.PromptingForDistance -= new PromptDistanceOptionsEventHandler(callback_PromptingForDistance);
					m_ed.PromptingForDouble -= new PromptDoubleOptionsEventHandler(callback_PromptingForDouble);
					m_ed.PromptingForEntity -= new PromptEntityOptionsEventHandler(callback_PromptingForEntity);
					m_ed.PromptingForInteger -= new PromptIntegerOptionsEventHandler(callback_PromptingForInteger);
					m_ed.PromptingForKeyword -= new PromptKeywordOptionsEventHandler(callback_PromptingForKeyword);
					m_ed.PromptingForNestedEntity -= new PromptNestedEntityOptionsEventHandler(callback_PromptingForNestedEntity);
					m_ed.PromptingForPoint -= new PromptPointOptionsEventHandler(callback_PromptingForPoint);
					m_ed.PromptingForSelection -= new PromptSelectionOptionsEventHandler(callback_PromptingForSelection);
					m_ed.PromptingForString -= new PromptStringOptionsEventHandler(callback_PromptingForString);
					m_ed.SelectionAdded -= new SelectionAddedEventHandler(callback_SelectionAdded);
					m_ed.SelectionRemoved -= new SelectionRemovedEventHandler(callback_SelectionRemoved);
                    m_ed.Dragging -= new DraggingEventHandler(callback_Dragging);
                    m_ed.DraggingEnded -= new DraggingEndedEventHandler(callback_DraggingEnded);
					m_bDone = false;
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void DoPoint()
		{
			try 
			{
				// Point filter and monitor events
				if( !m_bShownInput )
				{
					if(	Application.DocumentManager.MdiActiveDocument != null
						&& Application.DocumentManager.Count != 0
						&& Application.DocumentManager.MdiActiveDocument.Editor != null)
						m_ed = Application.DocumentManager.MdiActiveDocument.Editor;
					else
						return;

					m_ed.PointFilter += new PointFilterEventHandler(callback_PointFilter);
					m_ed.PointMonitor += new PointMonitorEventHandler(callback_PointMonitor);
					m_bShownInput = true;
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		 
		public void UndoPoint()
		{
			try
			{
				if(m_bShownInput)
				{
					if(	m_ed == null )
						return;

					m_ed.PointFilter -= new PointFilterEventHandler(callback_PointFilter);
					m_ed.PointMonitor -= new PointMonitorEventHandler(callback_PointMonitor);
					m_bShownInput = false;
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
    
		private void callback_EnteringQuiescentState(object sender, EventArgs e)
		{
			WriteLine("EnteringQuiescentState");
		}

		private void callback_LeavingQuiescentState(object sender, EventArgs e)
		{
			WriteLine("LeavingQuiescentState");
		}

        void callback_DraggingEnded(object sender, DraggingEndedEventArgs e)
        {
            try
            {
                WriteLine(String.Format("DraggingEnded - Status={0}, PickPoint={1}, Offset={2}", e.Status,e.PickPoint,e.Offset));
            }
            catch (System.Exception ex)
            {
                Helper.Message(ex);
            }
        }

        void callback_Dragging(object sender, DraggingEventArgs e)
        {
            try
            {
                WriteLine(String.Format("Dragging - {0}", e.Prompt));
            }
            catch (System.Exception ex)
            {
                Helper.Message(ex);
            }
        }
		
		private void callback_PointFilter(object sender, PointFilterEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PointFilter - {0}", e.Context.ComputedPoint));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PointMonitor(object sender, PointMonitorEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PointMonitor - {0}", e.Context.ComputedPoint));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForAngle(object sender, PromptDoubleResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForAngle - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForCorner(object sender, PromptPointResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForCorner - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForDistance(object sender, PromptDoubleResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForDistance - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForDouble(object sender, PromptDoubleResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForDouble - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForEntity(object sender, PromptEntityResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForEntity - {0}", e.Result.ObjectId));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForInteger(object sender, PromptIntegerResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForInteger - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForKeyword(object sender, PromptStringResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForKeyword - {0}", e.Result.Status));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForNestedEntity(object sender, PromptNestedEntityResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForNestedEntity - {0}", e.Result.PickedPoint));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForPoint(object sender, PromptPointResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForPoint - {0}", e.Result.Value));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptedForSelection(object sender, PromptSelectionResultEventArgs e)
		{
			WriteLine(String.Format("PromptedForSelection"));
		}

		private void callback_PromptedForString(object sender, PromptStringResultEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForString - {0}", e.Result.Status));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptForEntityEnding(object sender, PromptForEntityEndingEventArgs e)
		{
			WriteLine(String.Format("PromptForEntityEnding"));
		}

		private void callback_PromptForSelectionEnding(object sender, PromptForSelectionEndingEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptForSelectionEnding - ssCount:{0}", e.Selection.Count));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptingForAngle(object sender, PromptAngleOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForAngle - allowZero:{0}", e.Options.AllowZero));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptingForCorner(object sender, PromptPointOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForCorner - useDashedLine:{0}", e.Options.UseDashedLine));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptingForDistance(object sender, PromptDistanceOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForDistance - useBasePoint:{0}", e.Options.UseBasePoint));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptingForDouble(object sender, PromptDoubleOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptedForDouble - allowNegative:{0}", e.Options.AllowNegative));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_PromptingForEntity(object sender, PromptEntityOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForEntity - allowNone:{0}", e.Options.AllowNone));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_PromptingForInteger(object sender, PromptIntegerOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForInteger - allowNegative:{0}", e.Options.AllowNegative));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_PromptingForKeyword(object sender, PromptKeywordOptionsEventArgs e)
		{
			try
			{
				WriteLine(String.Format("PromptingForKeyword - allowNone:{0}", e.Options.AllowNone));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_PromptingForNestedEntity(object sender, PromptNestedEntityOptionsEventArgs e)
		{
			WriteLine(String.Format("PromptingForNestedEntity"));
		}

		private void callback_PromptingForPoint(object sender, PromptPointOptionsEventArgs e)
		{
			WriteLine(String.Format("PromptingForPoint"));
		}

		private void callback_PromptingForSelection(object sender, PromptSelectionOptionsEventArgs e)
		{
			WriteLine(String.Format("PromptingForSelection"));
		}

		private void callback_PromptingForString(object sender, PromptStringOptionsEventArgs e)
		{
			WriteLine(String.Format("PromptingForString"));
		}
		
		private void callback_SelectionAdded(object sender, SelectionAddedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("SelectionAdded - {0} ssCount:{1} added:{2}", e.Flags, e.Selection.Count, e.AddedObjects.Count));
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}
		
		private void callback_SelectionRemoved(object sender, SelectionRemovedEventArgs e)
		{
			try
			{
				WriteLine(String.Format("SelectionRemoved - {0} ssCount:{1} removed:{2}", e.Flags, e.Selection.Count, e.RemovedObjects.Count));
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
				bool acedIsDragging = false;
				if(	Application.DocumentManager.MdiActiveDocument != null
					&& Application.DocumentManager.Count != 0
					&& Application.DocumentManager.MdiActiveDocument.Editor != null)
				{
					acedIsDragging = Application.DocumentManager.MdiActiveDocument.Editor.IsDragging;
				}

				if (EventsWatcher.m_suppressInputDuringDrag && acedIsDragging)
					return;

				string str = "\nED Events: " + obj.ToString();
				Helper.StreamMessage(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine function

	}	// end of class EditorEvents

}

