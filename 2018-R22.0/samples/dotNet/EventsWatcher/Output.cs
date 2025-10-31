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

namespace EventsWatcher
{
	/// <summary>
	/// Summary description for Output.
	/// </summary>
	public class Output : System.Windows.Forms.Form
	{
		public System.Windows.Forms.RichTextBox richTextBox1;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Output()
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Output));
			this.richTextBox1 = new System.Windows.Forms.RichTextBox();
			this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
			this.SuspendLayout();
			// 
			// richTextBox1
			// 
			this.richTextBox1.Name = "richTextBox1";
			this.richTextBox1.Size = new System.Drawing.Size(760, 432);
			this.richTextBox1.TabIndex = 0;
			this.richTextBox1.Text = "";
			this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
			// 
			// saveFileDialog1
			// 
			this.saveFileDialog1.FileName = "EventsLog";
			// 
			// Output
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(760, 435);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.richTextBox1});
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "Output";
			this.Text = "Output";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.Output_Closing);
			this.Load += new System.EventHandler(this.Output_Load);
			this.Layout += new System.Windows.Forms.LayoutEventHandler(this.Output_Layout);
			this.ResumeLayout(false);

		}
		#endregion

		private void Output_Layout(object sender, System.Windows.Forms.LayoutEventArgs e)
		{
			this.richTextBox1.Size = this.ClientSize;
		}

		private void Output_Load(object sender, System.EventArgs e)
		{
			ContextMenu cm = new ContextMenu();
			this.richTextBox1.ContextMenu = cm;

			//Add File Menu
			cm.MenuItems.Add(new MenuItem("&Save...", new EventHandler(this.FileSave_Clicked), Shortcut.CtrlS));
			cm.MenuItems.Add("-");     
			cm.MenuItems.Add(new MenuItem("&Clean", new EventHandler(this.Clean_Clicked), Shortcut.CtrlC));
		}

		private void Output_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			this.richTextBox1.Dispose();
			this.richTextBox1 = null;
		}

		// Clean the rich text control
		private void Clean_Clicked(object sender, System.EventArgs e) 
		{
			this.richTextBox1.Clear();
		}

		//File->Open Menu item handler
		private void FileSave_Clicked(object sender, System.EventArgs e) 
		{
			saveFileDialog1.Filter = "txt files (*.txt)|*.txt|rtf files (*.rtf)|*.rtf";
			saveFileDialog1.FilterIndex = 2 ;
			saveFileDialog1.RestoreDirectory = true ;
			saveFileDialog1.DefaultExt = "*.doc";
 
			if(saveFileDialog1.ShowDialog(this) == DialogResult.OK)
			{
				// Determine if the user selected a file name from the saveFileDialog.
				if(	saveFileDialog1.FileName.Length > 0) 
				{
					// Save the contents of the RichTextBox into the file.
					if( saveFileDialog1.FileName.EndsWith(".txt") )
						richTextBox1.SaveFile(saveFileDialog1.FileName, RichTextBoxStreamType.PlainText);

					if( saveFileDialog1.FileName.EndsWith(".rtf") )
						richTextBox1.SaveFile(saveFileDialog1.FileName, RichTextBoxStreamType.RichText);
				}
			}
		} // end of FileSave_Clicked

		private void richTextBox1_TextChanged(object sender, System.EventArgs e)
		{
		
		} 

	}
}

