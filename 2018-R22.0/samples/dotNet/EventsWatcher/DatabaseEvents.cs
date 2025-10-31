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
	/// DatabaseEvents.
	/// </summary>
	public class DatabaseEvents
	{
		public DatabaseEvents()
		{
			m_bDone = false;
			m_dbsTable = new Hashtable();
			collectAllDbs();
			Do();
		}

		public void collectAllDbs()
		{
			try
			{
				DocumentCollection m_docCol = Application.DocumentManager;
				IEnumerator docEnum = m_docCol.GetEnumerator();
				while( docEnum.MoveNext() )
				{
					Database db = (Database)((Document)docEnum.Current).Database;
					addDb(ref db);
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void addDb(ref Database db)
		{
			if(!m_dbsTable.ContainsKey(db))
				m_dbsTable.Add( db, new CBoolClass(false) );
		}

		public void removeDb(ref Database db)
		{
			if(m_dbsTable.ContainsKey(db))
			{
				UndoADb(ref db);
				m_dbsTable.Remove(db);
			}
		}

		private Database m_db;	// Used as a temporary var only.
		private Hashtable m_dbsTable;	// Database(key)/bool(value) pair
		private bool m_bDone;	// A flag to indicate if events have been planted.
		// A counterpart flag to the On option in the UI.

		public void Do()
		{
			if(m_bDone == false)
				m_bDone = true;
			else // Don't return because we may need to address some new dbs.
			{}

			try
			{
				foreach(DictionaryEntry entry in m_dbsTable)
				{
					CBoolClass boolClassVar = (CBoolClass)entry.Value;
					
					// Continue if events have alrealy planted for the specific db
					if(boolClassVar.ToString().ToLower() == "true") 
						continue;

					m_db = (Database)entry.Key;
					m_db.AbortDxfIn += new EventHandler(callback_AbortDxfIn);
					m_db.AbortDxfOut += new EventHandler(callback_AbortDxfOut);
					m_db.AbortSave += new EventHandler(callback_AbortSave);
					m_db.BeginDeepClone += new IdMappingEventHandler(callback_BeginDeepClone);
					m_db.BeginDeepCloneTranslation += new IdMappingEventHandler(callback_BeginDeepCloneTranslation);
					m_db.BeginDxfIn += new EventHandler(callback_BeginDxfIn);
					m_db.BeginDxfOut += new EventHandler(callback_BeginDxfOut);
					m_db.BeginInsert += new BeginInsertEventHandler(callback_BeginInsert);
					m_db.BeginSave += new DatabaseIOEventHandler(callback_BeginSave);
					m_db.BeginWblockBlock += new BeginWblockBlockEventHandler(callback_BeginWblockBlock);
					m_db.BeginWblockEntireDatabase += new BeginWblockEntireDatabaseEventHandler(callback_BeginWblockEntireDatabase);
					m_db.BeginWblockObjects += new BeginWblockObjectsEventHandler(callback_BeginWblockObjects);
					m_db.BeginWblockSelectedObjects += new BeginWblockSelectedObjectsEventHandler(callback_BeginWblockSelectedObjects);
					Database.DatabaseConstructed += new EventHandler(callback_DatabaseConstructed);
					m_db.DatabaseToBeDestroyed += new EventHandler(callback_DatabaseToBeDestroyed);
					m_db.DeepCloneAborted += new EventHandler(callback_DeepCloneAborted);
					m_db.DeepCloneEnded += new EventHandler(callback_DeepCloneEnded);
					m_db.Disposed += new EventHandler(callback_Disposed);
					m_db.DwgFileOpened += new DatabaseIOEventHandler(callback_DwgFileOpened);
					m_db.DxfInComplete += new EventHandler(callback_DxfInComplete);
					m_db.DxfOutComplete += new EventHandler(callback_DxfOutComplete);
					m_db.InitialDwgFileOpenComplete += new EventHandler(callback_InitialDwgFileOpenComplete);
					m_db.InsertAborted += new EventHandler(callback_InsertAborted);			
					m_db.InsertEnded += new EventHandler(callback_InsertEnded);
					m_db.InsertMappingAvailable += new IdMappingEventHandler(callback_InsertMappingAvailable);
					m_db.ObjectAppended += new ObjectEventHandler(callback_ObjectAppended);
					m_db.ObjectErased += new ObjectErasedEventHandler(callback_ObjectErased);
					m_db.ObjectModified += new ObjectEventHandler(callback_ObjectModified);
					m_db.ObjectOpenedForModify += new ObjectEventHandler(callback_ObjectOpenedForModify);
					m_db.ObjectReappended += new ObjectEventHandler(callback_ObjectReappended);
					m_db.ObjectUnappended += new ObjectEventHandler(callback_ObjectUnappended);
					m_db.PartialOpenNotice += new EventHandler(callback_PartialOpenNotice);
					m_db.ProxyResurrectionCompleted += new ProxyResurrectionCompletedEventHandler(callback_ProxyResurrectionCompleted);
					m_db.SaveComplete += new DatabaseIOEventHandler(callback_SaveComplete);
					// Full name to avoid the error of ambiguous reference
					m_db.SystemVariableChanged += new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangedEventHandler(callback_SystemVariableChanged);
					// Full name to avoid the error of ambiguous reference
					m_db.SystemVariableWillChange += new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangingEventHandler(callback_SystemVariableWillChange);
					m_db.WblockAborted += new EventHandler(callback_WblockAborted);
					m_db.WblockEnded += new EventHandler(callback_WblockEnded);
					m_db.WblockMappingAvailable += new IdMappingEventHandler(callback_WblockMappingAvailable);
					m_db.WblockNotice += new WblockNoticeEventHandler(callback_WblockNotice);
					Database.XrefAttachAborted += new EventHandler(callback_XrefAttachAborted);
					m_db.XrefAttachEnded += new EventHandler(callback_XrefAttachEnded);
					m_db.XrefBeginAttached += new XrefBeginOperationEventHandler(callback_XrefBeginAttached);
					m_db.XrefBeginOtherAttached += new XrefBeginOperationEventHandler(callback_XrefBeginOtherAttached);
					m_db.XrefBeginRestore += new XrefBeginOperationEventHandler(callback_XrefBeginRestore);
					m_db.XrefComandeered += new XrefComandeeredEventHandler(callback_XrefComandeered);
					m_db.XrefRedirected += new XrefRedirectedEventHandler(callback_XrefRedirected);
					m_db.XrefRestoreAborted += new EventHandler(callback_XrefRestoreAborted);
					m_db.XrefRestoreEnded += new EventHandler(callback_XrefRestoreEnded);

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
				IDictionaryEnumerator docsEnumerator = m_dbsTable.GetEnumerator();
				while(docsEnumerator.MoveNext())
				{
					DictionaryEntry entry = (DictionaryEntry)docsEnumerator.Current;
					
					CBoolClass boolClassVar = (CBoolClass)entry.Value;

					// Continue if events have alrealy been removed from the specific doc
					if(boolClassVar.ToString().ToLower() == "false") 
						continue;

					m_db = (Database)entry.Key;
					m_db.AbortDxfIn -= new EventHandler(callback_AbortDxfIn);
					m_db.AbortDxfOut -= new EventHandler(callback_AbortDxfOut);
					m_db.AbortSave -= new EventHandler(callback_AbortSave);
					m_db.BeginDeepClone -= new IdMappingEventHandler(callback_BeginDeepClone);
					m_db.BeginDeepCloneTranslation -= new IdMappingEventHandler(callback_BeginDeepCloneTranslation);
					m_db.BeginDxfIn -= new EventHandler(callback_BeginDxfIn);
					m_db.BeginDxfOut -= new EventHandler(callback_BeginDxfOut);
					m_db.BeginInsert -= new BeginInsertEventHandler(callback_BeginInsert);
					m_db.BeginSave -= new DatabaseIOEventHandler(callback_BeginSave);
					m_db.BeginWblockBlock -= new BeginWblockBlockEventHandler(callback_BeginWblockBlock);
					m_db.BeginWblockEntireDatabase -= new BeginWblockEntireDatabaseEventHandler(callback_BeginWblockEntireDatabase);
					m_db.BeginWblockObjects -= new BeginWblockObjectsEventHandler(callback_BeginWblockObjects);
					m_db.BeginWblockSelectedObjects -= new BeginWblockSelectedObjectsEventHandler(callback_BeginWblockSelectedObjects);
					Database.DatabaseConstructed -= new EventHandler(callback_DatabaseConstructed);
					m_db.DatabaseToBeDestroyed -= new EventHandler(callback_DatabaseToBeDestroyed);
					m_db.DeepCloneAborted -= new EventHandler(callback_DeepCloneAborted);
					m_db.DeepCloneEnded -= new EventHandler(callback_DeepCloneEnded);
					m_db.Disposed -= new EventHandler(callback_Disposed);
					m_db.DwgFileOpened -= new DatabaseIOEventHandler(callback_DwgFileOpened);
					m_db.DxfInComplete -= new EventHandler(callback_DxfInComplete);
					m_db.DxfOutComplete -= new EventHandler(callback_DxfOutComplete);
					m_db.InitialDwgFileOpenComplete -= new EventHandler(callback_InitialDwgFileOpenComplete);
					m_db.InsertAborted -= new EventHandler(callback_InsertAborted);			
					m_db.InsertEnded -= new EventHandler(callback_InsertEnded);
					m_db.InsertMappingAvailable -= new IdMappingEventHandler(callback_InsertMappingAvailable);
					m_db.ObjectAppended -= new ObjectEventHandler(callback_ObjectAppended);
					m_db.ObjectErased -= new ObjectErasedEventHandler(callback_ObjectErased);
					m_db.ObjectModified -= new ObjectEventHandler(callback_ObjectModified);
					m_db.ObjectOpenedForModify -= new ObjectEventHandler(callback_ObjectOpenedForModify);
					m_db.ObjectReappended -= new ObjectEventHandler(callback_ObjectReappended);
					m_db.ObjectUnappended -= new ObjectEventHandler(callback_ObjectUnappended);
					m_db.PartialOpenNotice -= new EventHandler(callback_PartialOpenNotice);
					m_db.ProxyResurrectionCompleted -= new ProxyResurrectionCompletedEventHandler(callback_ProxyResurrectionCompleted);
					m_db.SaveComplete -= new DatabaseIOEventHandler(callback_SaveComplete);
					// Full name to avoid the error of ambiguous reference
					m_db.SystemVariableChanged -= new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangedEventHandler(callback_SystemVariableChanged);
					// Full name to avoid the error of ambiguous reference
					m_db.SystemVariableWillChange -= new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangingEventHandler(callback_SystemVariableWillChange);
					m_db.WblockAborted -= new EventHandler(callback_WblockAborted);
					m_db.WblockEnded -= new EventHandler(callback_WblockEnded);
					m_db.WblockMappingAvailable -= new IdMappingEventHandler(callback_WblockMappingAvailable);
					m_db.WblockNotice -= new WblockNoticeEventHandler(callback_WblockNotice);
					Database.XrefAttachAborted -= new EventHandler(callback_XrefAttachAborted);
					m_db.XrefAttachEnded -= new EventHandler(callback_XrefAttachEnded);
					m_db.XrefBeginAttached -= new XrefBeginOperationEventHandler(callback_XrefBeginAttached);
					m_db.XrefBeginOtherAttached -= new XrefBeginOperationEventHandler(callback_XrefBeginOtherAttached);
					m_db.XrefBeginRestore -= new XrefBeginOperationEventHandler(callback_XrefBeginRestore);
					m_db.XrefComandeered -= new XrefComandeeredEventHandler(callback_XrefComandeered);
					m_db.XrefRedirected -= new XrefRedirectedEventHandler(callback_XrefRedirected);
					m_db.XrefRestoreAborted -= new EventHandler(callback_XrefRestoreAborted);
					m_db.XrefRestoreEnded -= new EventHandler(callback_XrefRestoreEnded);

					boolClassVar.val = false;
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}			

		public void UndoADb(ref Database db)
		{
			if(m_bDone == false)
				return;
			else 
				m_bDone = false;

			try
			{
				if( !m_dbsTable.Contains(db) )
					return;
				
				CBoolClass boolClassVar = (CBoolClass)m_dbsTable[db];

				// Return if events have not been planted for it.
				if(boolClassVar.ToString().ToLower() == "false") 
					return;
				
				m_db = db;
				m_db.AbortDxfIn -= new EventHandler(callback_AbortDxfIn);
				m_db.AbortDxfOut -= new EventHandler(callback_AbortDxfOut);
				m_db.AbortSave -= new EventHandler(callback_AbortSave);
				m_db.BeginDeepClone -= new IdMappingEventHandler(callback_BeginDeepClone);
				m_db.BeginDeepCloneTranslation -= new IdMappingEventHandler(callback_BeginDeepCloneTranslation);
				m_db.BeginDxfIn -= new EventHandler(callback_BeginDxfIn);
				m_db.BeginDxfOut -= new EventHandler(callback_BeginDxfOut);
				m_db.BeginInsert -= new BeginInsertEventHandler(callback_BeginInsert);
				m_db.BeginSave -= new DatabaseIOEventHandler(callback_BeginSave);
				m_db.BeginWblockBlock -= new BeginWblockBlockEventHandler(callback_BeginWblockBlock);
				m_db.BeginWblockEntireDatabase -= new BeginWblockEntireDatabaseEventHandler(callback_BeginWblockEntireDatabase);
				m_db.BeginWblockObjects -= new BeginWblockObjectsEventHandler(callback_BeginWblockObjects);
				m_db.BeginWblockSelectedObjects -= new BeginWblockSelectedObjectsEventHandler(callback_BeginWblockSelectedObjects);
				Database.DatabaseConstructed -= new EventHandler(callback_DatabaseConstructed);
				m_db.DatabaseToBeDestroyed -= new EventHandler(callback_DatabaseToBeDestroyed);
				m_db.DeepCloneAborted -= new EventHandler(callback_DeepCloneAborted);
				m_db.DeepCloneEnded -= new EventHandler(callback_DeepCloneEnded);
				m_db.Disposed -= new EventHandler(callback_Disposed);
				m_db.DwgFileOpened -= new DatabaseIOEventHandler(callback_DwgFileOpened);
				m_db.DxfInComplete -= new EventHandler(callback_DxfInComplete);
				m_db.DxfOutComplete -= new EventHandler(callback_DxfOutComplete);
				m_db.InitialDwgFileOpenComplete -= new EventHandler(callback_InitialDwgFileOpenComplete);
				m_db.InsertAborted -= new EventHandler(callback_InsertAborted);			
				m_db.InsertEnded -= new EventHandler(callback_InsertEnded);
				m_db.InsertMappingAvailable -= new IdMappingEventHandler(callback_InsertMappingAvailable);
				m_db.ObjectAppended -= new ObjectEventHandler(callback_ObjectAppended);
				m_db.ObjectErased -= new ObjectErasedEventHandler(callback_ObjectErased);
				m_db.ObjectModified -= new ObjectEventHandler(callback_ObjectModified);
				m_db.ObjectOpenedForModify -= new ObjectEventHandler(callback_ObjectOpenedForModify);
				m_db.ObjectReappended -= new ObjectEventHandler(callback_ObjectReappended);
				m_db.ObjectUnappended -= new ObjectEventHandler(callback_ObjectUnappended);
				m_db.PartialOpenNotice -= new EventHandler(callback_PartialOpenNotice);
				m_db.ProxyResurrectionCompleted -= new ProxyResurrectionCompletedEventHandler(callback_ProxyResurrectionCompleted);
				m_db.SaveComplete -= new DatabaseIOEventHandler(callback_SaveComplete);
				// Full name to avoid the error of ambiguous reference
				m_db.SystemVariableChanged -= new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangedEventHandler(callback_SystemVariableChanged);
				// Full name to avoid the error of ambiguous reference
				m_db.SystemVariableWillChange -= new Autodesk.AutoCAD.DatabaseServices.SystemVariableChangingEventHandler(callback_SystemVariableWillChange);
				m_db.WblockAborted -= new EventHandler(callback_WblockAborted);
				m_db.WblockEnded -= new EventHandler(callback_WblockEnded);
				m_db.WblockMappingAvailable -= new IdMappingEventHandler(callback_WblockMappingAvailable);
				m_db.WblockNotice -= new WblockNoticeEventHandler(callback_WblockNotice);
				Database.XrefAttachAborted -= new EventHandler(callback_XrefAttachAborted);
				m_db.XrefAttachEnded -= new EventHandler(callback_XrefAttachEnded);
				m_db.XrefBeginAttached -= new XrefBeginOperationEventHandler(callback_XrefBeginAttached);
				m_db.XrefBeginOtherAttached -= new XrefBeginOperationEventHandler(callback_XrefBeginOtherAttached);
				m_db.XrefBeginRestore -= new XrefBeginOperationEventHandler(callback_XrefBeginRestore);
				m_db.XrefComandeered -= new XrefComandeeredEventHandler(callback_XrefComandeered);
				m_db.XrefRedirected -= new XrefRedirectedEventHandler(callback_XrefRedirected);
				m_db.XrefRestoreAborted -= new EventHandler(callback_XrefRestoreAborted);
				m_db.XrefRestoreEnded -= new EventHandler(callback_XrefRestoreEnded);

				boolClassVar.val = false;
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}	

		private void callback_DatabaseConstructed(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DatabaseConstructed - {0}", db.Filename));
		}

		private void callback_DatabaseToBeDestroyed(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DatabaseToBeDestroyed - {0}", db.Filename));
		}

		private void callback_DeepCloneAborted(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DeepCloneAborted - {0}", db.Filename));
		}

		private void callback_DeepCloneEnded(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DeepCloneEnded - {0}", db.Filename));
		}

		private void callback_Disposed(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("Disposed - {0}", db.Filename));
		}

		private void callback_DwgFileOpened(object sender, DatabaseIOEventArgs e)
		{
			WriteLine(String.Format("DwgFileOpened - {0}",  e.FileName));
		}

		private void callback_DxfInComplete(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DxfInComplete - {0}", db.Filename));
		}

		private void callback_DxfOutComplete(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("DxfOutComplete - {0}", db.Filename));
		}

		private void callback_AbortDxfIn(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("AbortDxfIn - {0}", db.Filename));
		}

		private void callback_AbortDxfOut(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("AbortDxfOut - {0}", db.Filename));
		}

		private void callback_AbortSave(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("AbortSave - {0}", db.Filename));
		}

		private void callback_BeginDeepClone(object sender, IdMappingEventArgs e)
		{
			WriteLine(String.Format("BeginDeepClone - {0}", e.IdMapping.ToString()));
		}

		private void callback_BeginDeepCloneTranslation(object sender, IdMappingEventArgs e)
		{
			WriteLine(String.Format("BeginDeepCloneTranslation {0}", e.IdMapping.ToString()));
		}

		private void callback_BeginDxfIn(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("BeginDxfIn - {0}", db.Filename));
		}

		private void callback_BeginDxfOut(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("BeginDxfOut - {0}", db.Filename));
		}

		private void callback_BeginInsert(object sender, BeginInsertEventArgs e)
		{
			WriteLine(String.Format("BeginInsert - from:{0}", e.From));
		}

		private void callback_BeginSave(object sender, DatabaseIOEventArgs e)
		{
			WriteLine(String.Format("BeginSave - {0}",  e.FileName));
		}

		private void callback_BeginWblockBlock(object sender, BeginWblockBlockEventArgs e)
		{
			WriteLine(String.Format("BeginWblockBlock - from:{0} {1} ", e.From, e.BlockId));
		}

		private void callback_BeginWblockEntireDatabase(object sender, BeginWblockEntireDatabaseEventArgs e)
		{
			WriteLine(String.Format("BeginWblockEntireDatabase - from:{0}", e.From));
		}

		private void callback_BeginWblockObjects(object sender, BeginWblockObjectsEventArgs e)
		{
			WriteLine(String.Format("BeginWblockObjects - from:{0} {1}", e.From, e.IdMapping.ToString()));
		}

		private void callback_BeginWblockSelectedObjects(object sender, BeginWblockSelectedObjectsEventArgs e)
		{
			WriteLine(String.Format("BeginWblockSelectedObjects - from:{0} {1} ", e.From, e.InsertionPoint));
		}

		private void callback_InitialDwgFileOpenComplete(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("InitialDwgFileOpenComplete - {0}", db.Filename));
		}

		private void callback_InsertAborted(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("InsertAborted - {0}", db.Filename));
		}

		private void callback_InsertEnded(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("InsertEnded - {0}", db.Filename));
		}

		private void callback_InsertMappingAvailable(object sender, IdMappingEventArgs e)
		{
			WriteLine(String.Format("InsertMappingAvailable - {0}", e.IdMapping.ToString()));
		}

		private void callback_ObjectAppended(object sender, ObjectEventArgs e)
		{
			WriteLine(String.Format("ObjectAppended - {0} {1}", e.DBObject.ToString(), e.DBObject.Id.ToString()));
		}

		private void callback_ObjectErased(object sender, ObjectErasedEventArgs e)
		{
			WriteLine(String.Format("ObjectErased - {0} {1} {2}", e.DBObject.ToString(), e.DBObject.Id.ToString(), e.Erased));
		}

		private void callback_ObjectModified(object sender, ObjectEventArgs e)
		{
			WriteLine(String.Format("ObjectModified - {0} {1}", e.DBObject.ToString(), e.DBObject.Id.ToString()));
		}

		private void callback_ObjectOpenedForModify(object sender, ObjectEventArgs e)
		{
			WriteLine(String.Format("ObjectOpenedForModify - {0} {1}", e.DBObject.ToString(), e.DBObject.Id.ToString()));
		}

		private void callback_ObjectReappended(object sender, ObjectEventArgs e)
		{
			WriteLine(String.Format("ObjectReappended - {0} {1}", e.DBObject.ToString(), e.DBObject.Id.ToString()));
		}

		private void callback_ObjectUnappended(object sender, ObjectEventArgs e)
		{
			WriteLine(String.Format("ObjectUnappended - {0} {1}", e.DBObject.ToString(), e.DBObject.Id.ToString()));
		}

		private void callback_PartialOpenNotice(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("PartialOpenNotice - {0}", db.Filename));
		}

		private void callback_ProxyResurrectionCompleted(object sender, ProxyResurrectionCompletedEventArgs e)
		{
			WriteLine(String.Format("ProxyResurrectionCompleted - {0}", e.ApplicationName));
		}

		private void callback_SaveComplete(object sender, DatabaseIOEventArgs e)
		{
			WriteLine(String.Format("SaveComplete - {0}", e.FileName));
		}

		private void callback_SystemVariableChanged(object sender, Autodesk.AutoCAD.DatabaseServices.SystemVariableChangedEventArgs e)
		{
			WriteLine(String.Format("SystemVariableChanged - {0} {1}", e.Name, e.Changed));
		}

		private void callback_SystemVariableWillChange(object sender, Autodesk.AutoCAD.DatabaseServices.SystemVariableChangingEventArgs e)
		{
			WriteLine(String.Format("SystemVariableWillChange - {0} ", e.Name));
		}

		private void callback_WblockAborted(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("WblockAborted - {0}", db.Filename));
		}

		private void callback_WblockEnded(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("WblockEnded - {0}", db.Filename));
		}

		private void callback_WblockMappingAvailable(object sender, IdMappingEventArgs e)
		{
			WriteLine(String.Format("WblockMappingAvailable - {0}", e.IdMapping.ToString()));
		}

		private void callback_WblockNotice(object sender, WblockNoticeEventArgs e)
		{
			WriteLine(String.Format("WblockNotice - to:{0}", e.To));
		}

		private void callback_XrefAttachAborted(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("XrefAttachAborted - {0}", db.Filename));
		}

		private void callback_XrefAttachEnded(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("XrefAttachEnded - {0}", db.Filename));

		}

		private void callback_XrefBeginAttached(object sender, XrefBeginOperationEventArgs e)
		{
			WriteLine(String.Format("XrefBeginAttached - {0} from:{1}", e.FileName, e.From));
		}

		private void callback_XrefBeginOtherAttached(object sender, XrefBeginOperationEventArgs e)
		{
			WriteLine(String.Format("XrefBeginOtherAttached - {0} from:{1}", e.FileName, e.From));
		}

		private void callback_XrefBeginRestore(object sender, XrefBeginOperationEventArgs e)
		{
			WriteLine(String.Format("XrefBeginRestore - {0} from:{1}", e.FileName, e.From));
		}

		private void callback_XrefComandeered(object sender, XrefComandeeredEventArgs e)
		{
			WriteLine(String.Format("XrefComandeered - from:{0} {1}", e.From, e.Id));
		}

		private void callback_XrefRedirected(object sender, XrefRedirectedEventArgs e)
		{
			WriteLine(String.Format("XrefComandeered - old:{0} new:{1}", e.OldId, e.NewId));
		}

		private void callback_XrefRestoreAborted(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("XrefRestoreAborted - {0}", db.Filename));
		}

		private void callback_XrefRestoreEnded(object sender, EventArgs e)
		{
			Database db = sender as Database;
			WriteLine(String.Format("XrefRestoreEnded - {0}", db.Filename));
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nDB Events: " + obj.ToString();
				Helper.StreamMessage(str);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine

	}	// end of class DatabaseEvents
}

