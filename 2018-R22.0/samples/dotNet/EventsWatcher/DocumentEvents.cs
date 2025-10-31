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
using System.Collections;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;

namespace EventsWatcher
{
	/// <summary>
	/// DocumentEvents.
	/// </summary>
	public class DocumentEvents
	{
		public DocumentEvents()
		{
			m_bDone = false;
			m_docsTable = new Hashtable();
			collectAllDocs();
			Do();
		}

		public void collectAllDocs()
		{
			try{
				DocumentCollection m_docCol = Application.DocumentManager;
				IEnumerator docEnum = m_docCol.GetEnumerator();
				while( docEnum.MoveNext() )
				{
					Document doc = (Document)docEnum.Current;
					addDoc(ref doc);
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void addDoc(ref Document doc)
		{
			if(!m_docsTable.ContainsKey(doc))
				m_docsTable.Add( doc, new CBoolClass(false) );
		}

		public void removeDoc(ref Document doc)
		{
			if(m_docsTable.ContainsKey(doc))
			{
				UndoADoc(ref doc);
				m_docsTable.Remove(doc);
			}
		}

		private Document m_doc;	// Used as a temporary var only.
		private Hashtable m_docsTable;	// Document(key)/bool(value) pair
		private bool m_bDone;	// A flag to indicate if events have been planted.
								// A counterpart flag to the On option in the UI.
		public void Do()
		{
			if(m_bDone == false)
				m_bDone = true;
			else // Don't return because we may need to address some new docs.
			{}

			try
			{
				foreach(DictionaryEntry entry in m_docsTable)
				{
					CBoolClass boolClassVar = (CBoolClass)entry.Value;
					
					// Continue if events have alrealy planted for the specific doc
					if(boolClassVar.ToString().ToLower() == "true") 
						continue;

					m_doc = (Document)entry.Key;

					m_doc.BeginDocumentClose += new DocumentBeginCloseEventHandler(callback_BeginDocumentClose);
					m_doc.CloseAborted += new EventHandler(callback_CloseAborted);
					m_doc.CloseWillStart += new EventHandler(callback_CloseWillStart);
					m_doc.CommandCancelled += new CommandEventHandler(callback_CommandCancelled);
					m_doc.CommandEnded += new CommandEventHandler(callback_CommandEnded);
					m_doc.CommandFailed += new CommandEventHandler(callback_CommandFailed);
					m_doc.CommandWillStart += new CommandEventHandler(callback_CommandWillStart);
					m_doc.LispCancelled += new EventHandler(callback_LispCancelled);
					m_doc.LispEnded += new EventHandler(callback_LispEnded);
					m_doc.LispWillStart += new LispWillStartEventHandler(callback_LispWillStart);
					m_doc.UnknownCommand += new UnknownCommandEventHandler(callback_UnknownCommand);
					
					boolClassVar.val = true;
				}
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
			else 
				m_bDone = false;

			try
			{
				IDictionaryEnumerator docsEnumerator = m_docsTable.GetEnumerator();
				while(docsEnumerator.MoveNext())
				{
					DictionaryEntry entry = (DictionaryEntry)docsEnumerator.Current;
					
					CBoolClass boolClassVar = (CBoolClass)entry.Value;

					// Continue if events have alrealy been removed from the specific doc
					if(boolClassVar.ToString().ToLower() == "false") 
						continue;

					m_doc = (Document)entry.Key;
					m_doc.BeginDocumentClose -= new DocumentBeginCloseEventHandler(callback_BeginDocumentClose);
					m_doc.CloseAborted -= new EventHandler(callback_CloseAborted);
					m_doc.CloseWillStart -= new EventHandler(callback_CloseWillStart);
					m_doc.CommandCancelled -= new CommandEventHandler(callback_CommandCancelled);
					m_doc.CommandEnded -= new CommandEventHandler(callback_CommandEnded);
					m_doc.CommandFailed -= new CommandEventHandler(callback_CommandFailed);
					m_doc.CommandWillStart -= new CommandEventHandler(callback_CommandWillStart);
					m_doc.LispCancelled -= new EventHandler(callback_LispCancelled);
					m_doc.LispEnded -= new EventHandler(callback_LispEnded);
					m_doc.LispWillStart -= new LispWillStartEventHandler(callback_LispWillStart);
					m_doc.UnknownCommand -= new UnknownCommandEventHandler(callback_UnknownCommand);

					boolClassVar.val = false;
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void UndoADoc(ref Document doc)
		{
			try
			{
				if( !m_docsTable.Contains(doc) )
					return;
				
				CBoolClass boolClassVar = (CBoolClass)m_docsTable[doc];

				// Return if events have not been planted for it.
				if(boolClassVar.ToString().ToLower() == "false") 
					return;
				
				m_doc = doc;
				m_doc.BeginDocumentClose -= new DocumentBeginCloseEventHandler(callback_BeginDocumentClose);
				m_doc.CloseAborted -= new EventHandler(callback_CloseAborted);
				m_doc.CloseWillStart -= new EventHandler(callback_CloseWillStart);
				m_doc.CommandCancelled -= new CommandEventHandler(callback_CommandCancelled);
				m_doc.CommandEnded -= new CommandEventHandler(callback_CommandEnded);
				m_doc.CommandFailed -= new CommandEventHandler(callback_CommandFailed);
				m_doc.CommandWillStart -= new CommandEventHandler(callback_CommandWillStart);
				m_doc.LispCancelled -= new EventHandler(callback_LispCancelled);
				m_doc.LispEnded -= new EventHandler(callback_LispEnded);
				m_doc.LispWillStart -= new LispWillStartEventHandler(callback_LispWillStart);
				m_doc.UnknownCommand -= new UnknownCommandEventHandler(callback_UnknownCommand);

				boolClassVar.val = false;
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void callback_BeginDocumentClose(Object o, DocumentBeginCloseEventArgs e)
		{
			WriteLine("BeginDocumentClose");
		}

		private void callback_CloseAborted(Object o, EventArgs e)
		{
			WriteLine("CloseAborted");
		}

		private void callback_CloseWillStart(Object o, EventArgs e)
		{
			WriteLine("CloseWillStart");
		}

		private void callback_CommandWillStart(Object o, CommandEventArgs e)
		{
			WriteLine(String.Format("CommandWillStart - {0}", e.GlobalCommandName));
		}

		private void callback_CommandEnded(Object o, CommandEventArgs e)
		{
			WriteLine(String.Format("CommandEnded - {0}", e.GlobalCommandName));
		}

		private void callback_CommandCancelled(Object o, CommandEventArgs e)
		{
			WriteLine(String.Format("CommandCancelled - {0}", e.GlobalCommandName));
		}

		private void callback_CommandFailed(Object o, CommandEventArgs e)
		{
			WriteLine(String.Format("CommandFailed - {0}", e.GlobalCommandName));
		}

		private void callback_LispCancelled(Object o, EventArgs e)
		{
			WriteLine("LispCancelled");
		}

		private void callback_LispEnded(Object o, EventArgs e)
		{
			WriteLine("LispEnded");
		}

		private void callback_LispWillStart(Object o, LispWillStartEventArgs e)
		{
			WriteLine(String.Format("LispWillStart - {0}", e.FirstLine));
		}	

		private void callback_UnknownCommand(Object o, UnknownCommandEventArgs e)
		{
			WriteLine(String.Format("UnknownCommand - {0}", e.GlobalCommandName));
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nDoc Events: " + obj.ToString();
				Helper.StreamMessage(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine

	}	// end of class DocumentEvents
}

