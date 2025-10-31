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
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

using Autodesk.AutoCAD.DatabaseServices;

namespace EventsWatcher
{
	/// <summary>
	/// EventsWatcher.
	/// </summary>
	public class EventsWatcher : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button OK;
		private System.Windows.Forms.Button Cancel;
		private System.Windows.Forms.CheckBox EdInputSuppress;
		private System.Windows.Forms.CheckBox EdInputShowPoint;
		private System.Windows.Forms.GroupBox LayoutManager;
		private System.Windows.Forms.CheckBox LayoutManOn;
		private System.Windows.Forms.GroupBox DocMan;
		private System.Windows.Forms.GroupBox DynamicLinker;
		private System.Windows.Forms.CheckBox DynLinkerOn;
		private System.Windows.Forms.GroupBox PlotEvent;
		private System.Windows.Forms.GroupBox DocumentReactor;
		private System.Windows.Forms.CheckBox DocumentOn;
		private System.Windows.Forms.GroupBox DatabaseReactor;
		private System.Windows.Forms.CheckBox DatabaseOn;
		private System.Windows.Forms.GroupBox AppEvent;
		private System.Windows.Forms.GroupBox EditorEvent;
		private System.Windows.Forms.CheckBox AppOn;
		private System.Windows.Forms.CheckBox PlotOn;
		private System.Windows.Forms.CheckBox DocManOn;
		private System.Windows.Forms.CheckBox EditorOn;
		private System.Windows.Forms.Button Retire;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public EventsWatcher()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(EventsWatcher));
			this.OK = new System.Windows.Forms.Button();
			this.Cancel = new System.Windows.Forms.Button();
			this.EditorEvent = new System.Windows.Forms.GroupBox();
			this.EdInputSuppress = new System.Windows.Forms.CheckBox();
			this.EdInputShowPoint = new System.Windows.Forms.CheckBox();
			this.EditorOn = new System.Windows.Forms.CheckBox();
			this.LayoutManager = new System.Windows.Forms.GroupBox();
			this.LayoutManOn = new System.Windows.Forms.CheckBox();
			this.DocMan = new System.Windows.Forms.GroupBox();
			this.DocManOn = new System.Windows.Forms.CheckBox();
			this.DynamicLinker = new System.Windows.Forms.GroupBox();
			this.DynLinkerOn = new System.Windows.Forms.CheckBox();
			this.PlotEvent = new System.Windows.Forms.GroupBox();
			this.PlotOn = new System.Windows.Forms.CheckBox();
			this.DocumentReactor = new System.Windows.Forms.GroupBox();
			this.DocumentOn = new System.Windows.Forms.CheckBox();
			this.DatabaseReactor = new System.Windows.Forms.GroupBox();
			this.DatabaseOn = new System.Windows.Forms.CheckBox();
			this.AppEvent = new System.Windows.Forms.GroupBox();
			this.AppOn = new System.Windows.Forms.CheckBox();
			this.Retire = new System.Windows.Forms.Button();
			this.EditorEvent.SuspendLayout();
			this.LayoutManager.SuspendLayout();
			this.DocMan.SuspendLayout();
			this.DynamicLinker.SuspendLayout();
			this.PlotEvent.SuspendLayout();
			this.DocumentReactor.SuspendLayout();
			this.DatabaseReactor.SuspendLayout();
			this.AppEvent.SuspendLayout();
			this.SuspendLayout();
			// 
			// OK
			// 
			this.OK.Location = new System.Drawing.Point(520, 320);
			this.OK.Name = "OK";
			this.OK.Size = new System.Drawing.Size(88, 24);
			this.OK.TabIndex = 1;
			this.OK.Text = "OK";
			this.OK.Click += new System.EventHandler(this.OK_Click);
			// 
			// Cancel
			// 
			this.Cancel.Location = new System.Drawing.Point(624, 320);
			this.Cancel.Name = "Cancel";
			this.Cancel.Size = new System.Drawing.Size(88, 24);
			this.Cancel.TabIndex = 2;
			this.Cancel.Text = "Cancel";
			this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
			// 
			// EditorEvent
			// 
			this.EditorEvent.Controls.AddRange(new System.Windows.Forms.Control[] {
																					  this.EdInputSuppress,
																					  this.EdInputShowPoint,
																					  this.EditorOn});
			this.EditorEvent.Location = new System.Drawing.Point(8, 112);
			this.EditorEvent.Name = "EditorEvent";
			this.EditorEvent.Size = new System.Drawing.Size(224, 88);
			this.EditorEvent.TabIndex = 18;
			this.EditorEvent.TabStop = false;
			this.EditorEvent.Text = "Editor Event";
			// 
			// EdInputSuppress
			// 
			this.EdInputSuppress.Location = new System.Drawing.Point(8, 64);
			this.EdInputSuppress.Name = "EdInputSuppress";
			this.EdInputSuppress.Size = new System.Drawing.Size(200, 24);
			this.EdInputSuppress.TabIndex = 2;
			this.EdInputSuppress.Text = "Suppress While Dragging";
			this.EdInputSuppress.CheckedChanged += new System.EventHandler(this.EdInputSuppress_CheckedChanged);
			// 
			// EdInputShowPoint
			// 
			this.EdInputShowPoint.Location = new System.Drawing.Point(8, 40);
			this.EdInputShowPoint.Name = "EdInputShowPoint";
			this.EdInputShowPoint.Size = new System.Drawing.Size(200, 24);
			this.EdInputShowPoint.TabIndex = 1;
			this.EdInputShowPoint.Text = "Point Filter and Monitor";
			this.EdInputShowPoint.CheckedChanged += new System.EventHandler(this.EdInputShowPoint_CheckedChanged);
			// 
			// EditorOn
			// 
			this.EditorOn.Location = new System.Drawing.Point(8, 16);
			this.EditorOn.Name = "EditorOn";
			this.EditorOn.Size = new System.Drawing.Size(200, 24);
			this.EditorOn.TabIndex = 0;
			this.EditorOn.Text = "Events except for Point";
			this.EditorOn.CheckedChanged += new System.EventHandler(this.EditorOn_CheckedChanged);
			// 
			// LayoutManager
			// 
			this.LayoutManager.Controls.AddRange(new System.Windows.Forms.Control[] {
																						this.LayoutManOn});
			this.LayoutManager.Location = new System.Drawing.Point(8, 216);
			this.LayoutManager.Name = "LayoutManager";
			this.LayoutManager.Size = new System.Drawing.Size(224, 88);
			this.LayoutManager.TabIndex = 17;
			this.LayoutManager.TabStop = false;
			this.LayoutManager.Text = "Layout Manager";
			// 
			// LayoutManOn
			// 
			this.LayoutManOn.Location = new System.Drawing.Point(8, 24);
			this.LayoutManOn.Name = "LayoutManOn";
			this.LayoutManOn.Size = new System.Drawing.Size(200, 24);
			this.LayoutManOn.TabIndex = 0;
			this.LayoutManOn.Text = "On";
			this.LayoutManOn.CheckedChanged += new System.EventHandler(this.LayoutManOn_CheckedChanged);
			// 
			// DocMan
			// 
			this.DocMan.Controls.AddRange(new System.Windows.Forms.Control[] {
																				 this.DocManOn});
			this.DocMan.Location = new System.Drawing.Point(248, 8);
			this.DocMan.Name = "DocMan";
			this.DocMan.Size = new System.Drawing.Size(224, 88);
			this.DocMan.TabIndex = 16;
			this.DocMan.TabStop = false;
			this.DocMan.Text = "Document Manager";
			// 
			// DocManOn
			// 
			this.DocManOn.Location = new System.Drawing.Point(8, 24);
			this.DocManOn.Name = "DocManOn";
			this.DocManOn.Size = new System.Drawing.Size(200, 24);
			this.DocManOn.TabIndex = 0;
			this.DocManOn.Text = "On";
			this.DocManOn.CheckedChanged += new System.EventHandler(this.DocManOn_CheckedChanged);
			// 
			// DynamicLinker
			// 
			this.DynamicLinker.Controls.AddRange(new System.Windows.Forms.Control[] {
																						this.DynLinkerOn});
			this.DynamicLinker.Location = new System.Drawing.Point(488, 8);
			this.DynamicLinker.Name = "DynamicLinker";
			this.DynamicLinker.Size = new System.Drawing.Size(224, 88);
			this.DynamicLinker.TabIndex = 15;
			this.DynamicLinker.TabStop = false;
			this.DynamicLinker.Text = "Dynamic Linker";
			// 
			// DynLinkerOn
			// 
			this.DynLinkerOn.Location = new System.Drawing.Point(8, 24);
			this.DynLinkerOn.Name = "DynLinkerOn";
			this.DynLinkerOn.Size = new System.Drawing.Size(200, 24);
			this.DynLinkerOn.TabIndex = 0;
			this.DynLinkerOn.Text = "On";
			this.DynLinkerOn.CheckedChanged += new System.EventHandler(this.DynLinkerOn_CheckedChanged);
			// 
			// PlotEvent
			// 
			this.PlotEvent.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.PlotOn});
			this.PlotEvent.Location = new System.Drawing.Point(488, 112);
			this.PlotEvent.Name = "PlotEvent";
			this.PlotEvent.Size = new System.Drawing.Size(224, 88);
			this.PlotEvent.TabIndex = 14;
			this.PlotEvent.TabStop = false;
			this.PlotEvent.Text = "Plot Event";
			// 
			// PlotOn
			// 
			this.PlotOn.Location = new System.Drawing.Point(8, 24);
			this.PlotOn.Name = "PlotOn";
			this.PlotOn.Size = new System.Drawing.Size(200, 24);
			this.PlotOn.TabIndex = 0;
			this.PlotOn.Text = "On";
			this.PlotOn.CheckedChanged += new System.EventHandler(this.PlotOn_CheckedChanged);
			// 
			// DocumentReactor
			// 
			this.DocumentReactor.Controls.AddRange(new System.Windows.Forms.Control[] {
																						  this.DocumentOn});
			this.DocumentReactor.Location = new System.Drawing.Point(248, 112);
			this.DocumentReactor.Name = "DocumentReactor";
			this.DocumentReactor.Size = new System.Drawing.Size(224, 88);
			this.DocumentReactor.TabIndex = 13;
			this.DocumentReactor.TabStop = false;
			this.DocumentReactor.Text = "Document Event";
			// 
			// DocumentOn
			// 
			this.DocumentOn.Location = new System.Drawing.Point(8, 24);
			this.DocumentOn.Name = "DocumentOn";
			this.DocumentOn.Size = new System.Drawing.Size(200, 24);
			this.DocumentOn.TabIndex = 0;
			this.DocumentOn.Text = "On";
			this.DocumentOn.CheckedChanged += new System.EventHandler(this.DocumentOn_CheckedChanged);
			// 
			// DatabaseReactor
			// 
			this.DatabaseReactor.Controls.AddRange(new System.Windows.Forms.Control[] {
																						  this.DatabaseOn});
			this.DatabaseReactor.Location = new System.Drawing.Point(248, 216);
			this.DatabaseReactor.Name = "DatabaseReactor";
			this.DatabaseReactor.Size = new System.Drawing.Size(224, 88);
			this.DatabaseReactor.TabIndex = 12;
			this.DatabaseReactor.TabStop = false;
			this.DatabaseReactor.Text = "Database Event";
			// 
			// DatabaseOn
			// 
			this.DatabaseOn.Location = new System.Drawing.Point(8, 24);
			this.DatabaseOn.Name = "DatabaseOn";
			this.DatabaseOn.Size = new System.Drawing.Size(200, 24);
			this.DatabaseOn.TabIndex = 0;
			this.DatabaseOn.Text = "On";
			this.DatabaseOn.CheckedChanged += new System.EventHandler(this.DatabaseOn_CheckedChanged);
			// 
			// AppEvent
			// 
			this.AppEvent.Controls.AddRange(new System.Windows.Forms.Control[] {
																				   this.AppOn});
			this.AppEvent.Location = new System.Drawing.Point(8, 8);
			this.AppEvent.Name = "AppEvent";
			this.AppEvent.Size = new System.Drawing.Size(224, 88);
			this.AppEvent.TabIndex = 10;
			this.AppEvent.TabStop = false;
			this.AppEvent.Text = "Application Event";
			// 
			// AppOn
			// 
			this.AppOn.Location = new System.Drawing.Point(8, 24);
			this.AppOn.Name = "AppOn";
			this.AppOn.Size = new System.Drawing.Size(200, 24);
			this.AppOn.TabIndex = 0;
			this.AppOn.Text = "On";
			this.AppOn.CheckedChanged += new System.EventHandler(this.AppOn_CheckedChanged);
			// 
			// Retire
			// 
			this.Retire.Location = new System.Drawing.Point(200, 320);
			this.Retire.Name = "Retire";
			this.Retire.Size = new System.Drawing.Size(88, 24);
			this.Retire.TabIndex = 19;
			this.Retire.Text = "Retire";
			this.Retire.Click += new System.EventHandler(this.Retire_Click);
			// 
			// EventsWatcher
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(720, 355);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.Retire,
																		  this.EditorEvent,
																		  this.LayoutManager,
																		  this.DocMan,
																		  this.DynamicLinker,
																		  this.PlotEvent,
																		  this.DocumentReactor,
																		  this.DatabaseReactor,
																		  this.AppEvent,
																		  this.Cancel,
																		  this.OK});
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "EventsWatcher";
			this.Text = "EventsWatcher";
			this.Load += new System.EventHandler(this.EventsWatcher_Load);
			this.EditorEvent.ResumeLayout(false);
			this.LayoutManager.ResumeLayout(false);
			this.DocMan.ResumeLayout(false);
			this.DynamicLinker.ResumeLayout(false);
			this.PlotEvent.ResumeLayout(false);
			this.DocumentReactor.ResumeLayout(false);
			this.DatabaseReactor.ResumeLayout(false);
			this.AppEvent.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		// Static global variables
		public static bool		m_doApp;
		public static bool		m_doPlot;
		public static bool		m_doLayout;
		public static bool		m_doLinker;
		public static bool		m_doDocMan;
		public static bool		m_doDoc;
		public static bool		m_doDatabase;
		public static bool		m_doEditor;

		public static bool  m_showInput;
		public static bool	m_suppressInputDuringDrag;

		// Static global event watchers
		public static ApplicationEvents			m_appWatcher;
		public static DynLinkerEvents			m_dynLinkerWatcher;
		public static LayoutManEvents			m_layoutManWatcher;
		public static PlotEvents				m_plotWatcher;
		public static EditorEvents				m_editorWatcher;
		public static DocManEvents				m_docManWatcher;
		public static DocumentEvents			m_docWatcher;
		public static DatabaseEvents			m_dbWatcher;

		public static DocManForUI				m_docManForUI;
		
		// Helper functions
		public static void documentCreated(ref Autodesk.AutoCAD.ApplicationServices.Document doc)
		{
			if(m_docWatcher != null)
			{
				m_docWatcher.addDoc(ref doc);
				if(m_doDoc)
				{
					m_docWatcher.Do();
				}
			}
			
			if(m_dbWatcher != null)
			{
				Database db = doc.Database;
				m_dbWatcher.addDb(ref db);
				if(m_doDatabase)
				{
					m_dbWatcher.Do();
				}
			}
		}

		public static void documentToBeDestroyed(ref Autodesk.AutoCAD.ApplicationServices.Document doc)
		{
			if(m_docWatcher != null)
			{
				m_docWatcher.removeDoc(ref doc);
			}

			if(m_dbWatcher != null)
			{
				Database db = doc.Database;
				m_dbWatcher.removeDb(ref db);
			}
		}

		public static void documentActivated()
		{
			try
			{
				if(m_doEditor)
				{
					m_editorWatcher.Undo();
					m_editorWatcher.Do();
				}
		
				if(m_showInput)
				{
					m_editorWatcher.UndoPoint();
					m_editorWatcher.DoPoint();
				}
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}			
		}

		public static void documentToBeDeactivated()
		{
			try
			{
				if(m_doEditor)
					m_editorWatcher.Undo();
			
				if(m_showInput)
					m_editorWatcher.UndoPoint();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void watchersOffDuty()
		{
			// Mark all watchers as off duty.
			EventsWatcher.m_doApp = false;
			EventsWatcher.m_doPlot = false;
			EventsWatcher.m_doLayout = false;
			EventsWatcher.m_doLinker = false;
			EventsWatcher.m_doDocMan = false;
			EventsWatcher.m_doDoc = false;
			EventsWatcher.m_doDatabase = false;
			EventsWatcher.m_doEditor = false;

			EventsWatcher.m_showInput = false;
			EventsWatcher.m_suppressInputDuringDrag = true;

			// Have them have a rest indeed.
			appWatcherOnDuty();
			plotWatcherOnDuty();
			layoutWatcherOnDuty();
			linkerWatcherOnDuty();
			docManWatcherOnDuty();
			docWatcherOnDuty();
			dbWatcherOnDuty();
			editorWatcherOnDuty();

			// Release spaces.
			EventsWatcher.m_appWatcher = null;
			EventsWatcher.m_dynLinkerWatcher = null;
			EventsWatcher.m_layoutManWatcher = null;
			EventsWatcher.m_plotWatcher = null;
			EventsWatcher.m_editorWatcher = null;
			EventsWatcher.m_docManWatcher = null;
			EventsWatcher.m_docWatcher = null;
			EventsWatcher.m_dbWatcher = null;
		}
		
		private void EventsWatcher_Load(object sender, System.EventArgs e)
		{
			// Restore all the status of controls.
			AppOn.Checked		= m_doApp;
			PlotOn.Checked		= m_doPlot;
			LayoutManOn.Checked	= m_doLayout;
			DynLinkerOn.Checked	= m_doLinker;
			DocManOn.Checked	= m_doDocMan;
			DocumentOn.Checked	= m_doDoc;
			DatabaseOn.Checked	= m_doDatabase;
			EditorOn.Checked	= m_doEditor;
			EdInputShowPoint.Checked	= m_showInput;
			EdInputSuppress.Checked		= m_suppressInputDuringDrag;
		}

		private void Retire_Click(object sender, System.EventArgs e)
		{
			watchersOffDuty();

			this.Close();
		}

		private void OK_Click(object sender, System.EventArgs e)
		{
			appWatcherOnDuty();
			plotWatcherOnDuty();
			layoutWatcherOnDuty();
			linkerWatcherOnDuty();
			docManWatcherOnDuty();
			docWatcherOnDuty();
			dbWatcherOnDuty();

			editorWatcherOnDuty();

			this.Close();
		}

		private void appWatcherOnDuty()
		{
			if(m_doApp)
			{
				if( m_appWatcher == null)
					m_appWatcher = new ApplicationEvents();
				else
					m_appWatcher.Do();
			}
			else
			{
				if( m_appWatcher != null)
					m_appWatcher.Undo();
			}
		}

		private void plotWatcherOnDuty()
		{
			if(m_doPlot)
			{
				if(m_plotWatcher == null)
					m_plotWatcher = new PlotEvents();
				else
					m_plotWatcher.Do();
			}
			else
			{
				if(m_plotWatcher != null)
				{
					m_plotWatcher.Undo();
				}
			}
		}

		private void layoutWatcherOnDuty()
		{
			if(m_doLayout)
			{
				if(m_layoutManWatcher == null)
					m_layoutManWatcher = new LayoutManEvents();
				else
					m_layoutManWatcher.Do();
			}
			else
			{
				if(m_layoutManWatcher != null)
				{
					m_layoutManWatcher.Undo();
				}
			}
		}

		private void linkerWatcherOnDuty()
		{
			if(m_doLinker)
			{
				if(m_dynLinkerWatcher == null)
					m_dynLinkerWatcher = new DynLinkerEvents();
				else
					m_dynLinkerWatcher.Do();
			}
			else
			{
				if(m_dynLinkerWatcher != null)
				{
					m_dynLinkerWatcher.Undo();
				}
			}
		}
		
		private void docManWatcherOnDuty()
		{
			if(m_doDocMan)
			{
				if(m_docManWatcher == null)
					m_docManWatcher = new DocManEvents();
				else
					m_docManWatcher.Do();
			}
			else
			{
				if(m_docManWatcher != null)
				{
					m_docManWatcher.Undo();
				}
			}
		}	
		
		private void docWatcherOnDuty()
		{
			if(m_doDoc)
			{
				if(m_docWatcher == null)
					m_docWatcher = new DocumentEvents();
				else
					m_docWatcher.Do();
			}
			else
			{
				if(m_docWatcher != null)
				{
					m_docWatcher.Undo();
				}
			}
		}

		private void dbWatcherOnDuty()
		{
			if(m_doDatabase)
			{
				if(m_dbWatcher == null)
					m_dbWatcher = new DatabaseEvents();
				else
					m_dbWatcher.Do();
			}
			else
			{
				if(m_dbWatcher != null)
				{
					m_dbWatcher.Undo();
				}
			}
		}

		private void editorWatcherOnDuty()
		{
			try
			{
				if(m_editorWatcher == null)
					m_editorWatcher = new EditorEvents();

				if(m_doEditor)
					m_editorWatcher.Do();
				else
					m_editorWatcher.Undo();
			
				if(m_showInput)
					m_editorWatcher.DoPoint();
				else
					m_editorWatcher.UndoPoint();
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		private void Cancel_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

		private void AppOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doApp = AppOn.Checked;
		}

		private void EditorOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doEditor = EditorOn.Checked;
		}

		private void EdInputShowPoint_CheckedChanged(object sender, System.EventArgs e)
		{
			m_showInput = EdInputShowPoint.Checked;
		}

		private void EdInputSuppress_CheckedChanged(object sender, System.EventArgs e)
		{
			m_suppressInputDuringDrag = EdInputSuppress.Checked;
		}

		private void LayoutManOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doLayout = LayoutManOn.Checked;
		}

		private void DocManOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doDocMan = DocManOn.Checked;
		}

		private void DocumentOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doDoc = DocumentOn.Checked;
		}

		private void DatabaseOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doDatabase = DatabaseOn.Checked;
		}

		private void DynLinkerOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doLinker = DynLinkerOn.Checked;
		}

		private void PlotOn_CheckedChanged(object sender, System.EventArgs e)
		{
			m_doPlot = PlotOn.Checked;
		}

	}
}

