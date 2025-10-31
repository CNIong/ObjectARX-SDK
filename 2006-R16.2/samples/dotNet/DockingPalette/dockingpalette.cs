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
using AcadApp = Autodesk.AutoCAD.ApplicationServices.Application;

namespace Autodesk.AutoCAD.Samples.DockingPalette
{
    /// <summary>
    /// Sample control to be embedded on a palette
    /// </summary>
    public class TestControl : System.Windows.Forms.UserControl
    {
        private System.Windows.Forms.Label label1;
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public TestControl()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();

            // TODO: Add any initialization after the InitializeComponent call

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

		#region Component Designer generated code
        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.Location = new System.Drawing.Point(72, 128);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(128, 16);
            this.label1.TabIndex = 8;
            this.label1.Text = "Drag me on the drawing";
            this.label1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.label1_MouseMove);
            // 
            // TestControl
            // 
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.label1});
            this.Name = "TestControl";
            this.Size = new System.Drawing.Size(280, 296);
            this.GiveFeedback += new System.Windows.Forms.GiveFeedbackEventHandler(this.TestControl_GiveFeedback);
            this.QueryContinueDrag += new System.Windows.Forms.QueryContinueDragEventHandler(this.TestControl_QueryContinueDrag);
            this.ResumeLayout(false);

        }
		#endregion

        /// <summary>
        /// Drop target to control the drop behavior to the AutoCAD window
        /// </summary>
        public class MyDropTarget : Autodesk.AutoCAD.Windows.DropTarget
        {
            public override void OnDragEnter(System.Windows.Forms.DragEventArgs e)
            {
                System.Diagnostics.Debug.WriteLine("DragEnter");
            }
        
            public override void OnDragLeave()
            {
                System.Diagnostics.Debug.WriteLine("DragLeave");
            }
        
            public override void OnDragOver(System.Windows.Forms.DragEventArgs e)
            {
                System.Diagnostics.Debug.WriteLine("DragOver");
            }
            static string data;
            public override void OnDrop(System.Windows.Forms.DragEventArgs e)
            {
                System.Diagnostics.Debug.WriteLine("Drop");
                //let's drop it
                //stash away the payload
                data = (string)e.Data.GetData(typeof(string)) ;
                //start a command to handle the interaction with the user. Don't do it directly from the OnDrop method
                AcadApp.DocumentManager.MdiActiveDocument.SendStringToExecute("netdrop\n",false,false,false);
            }
            //command handler for the netdrop command. This is executed when our payload is
            //dropped on the acad window.
            [Autodesk.AutoCAD.Runtime.CommandMethod("netdrop")]
            public static void netdropCmd()
            {
                if (data!=null)
                {
                    AcadApp.DocumentManager.MdiActiveDocument.Editor.WriteMessage(data);
                    data = null;
                }
                else
                    AcadApp.DocumentManager.MdiActiveDocument.Editor.WriteMessage("nothing to do.");
            }
        }


        #region Handlers for drag events from control
        private void TestControl_GiveFeedback(object sender, System.Windows.Forms.GiveFeedbackEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("GiveFeedback");
        }

        private void TestControl_QueryContinueDrag(object sender, System.Windows.Forms.QueryContinueDragEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine("QueryContinueDrag");
        }
        #endregion

        private void label1_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (System.Windows.Forms.Control.MouseButtons ==  System.Windows.Forms.MouseButtons.Left)
            {
                //start dragDrop operation, MyDropTarget will be called when the cursor enters the AutoCAD view area.
                AcadApp.DoDragDrop(this,"Drag & drop successful!!!",System.Windows.Forms.DragDropEffects.All,new MyDropTarget());
            }
        }
    }
    public class TestPalettes 
    {
        static Autodesk.AutoCAD.Windows.PaletteSet ps;
        [Autodesk.AutoCAD.Runtime.CommandMethod("palettedemo")]
        public static void DoIt()
        {
            if (ps==null)
            {
                //use constructor with Guid so that we can save/load user data
                ps = new Autodesk.AutoCAD.Windows.PaletteSet("Test Palette Set",new Guid("63B8DB5B-10E4-4924-B8A2-A9CF9158E4F6"));
                ps.Load+=new Autodesk.AutoCAD.Windows.PalettePersistEventHandler(ps_Load);
                ps.Save+=new Autodesk.AutoCAD.Windows.PalettePersistEventHandler(ps_Save);
                ps.Style = Autodesk.AutoCAD.Windows.PaletteSetStyles.NameEditable | 
                    Autodesk.AutoCAD.Windows.PaletteSetStyles.ShowPropertiesMenu |
                    Autodesk.AutoCAD.Windows.PaletteSetStyles.ShowAutoHideButton | 
                    Autodesk.AutoCAD.Windows.PaletteSetStyles.ShowCloseButton;
                ps.MinimumSize = new System.Drawing.Size(300,300);
                ps.Add("Test Palette 1", new TestControl());
            }
            bool b = ps.Visible;
       
            ps.Visible = true;
            Autodesk.AutoCAD.EditorInput.Editor e = AcadApp.DocumentManager.MdiActiveDocument.Editor;
            
            Autodesk.AutoCAD.EditorInput.PromptResult res = e.GetKeywords("Select a palette set option:","Opacity","TitleBarLocation","Docking");
            if (res.Status == Autodesk.AutoCAD.EditorInput.PromptStatus.OK)
            {
                switch (res.StringResult)
                {
                    case "Opacity":
                        Autodesk.AutoCAD.EditorInput.PromptIntegerResult resInt;
                        do
                        {
                            resInt = e.GetInteger("Enter opacity:");
                            if (resInt.Status != Autodesk.AutoCAD.EditorInput.PromptStatus.OK)
                                break;
                            if (resInt.Value>=0 && resInt.Value<=100)
                                break;
                            e.WriteMessage("Opacity must be between 0 and 100\n");
                        }
                        while (true);
                        ps.Opacity = resInt.Value;
                        break;
                    case "TitleBarLocation":
                        res = e.GetKeywords("Select titlebar location:","Left","Right");
                        if (res.Status == Autodesk.AutoCAD.EditorInput.PromptStatus.OK)
                            switch (res.StringResult)
                            {
                                case "Left":
                                    ps.TitleBarLocation = Autodesk.AutoCAD.Windows.PaletteSetTitleBarLocation.Left;
                                    break;
                                case "Right":
                                    ps.TitleBarLocation = Autodesk.AutoCAD.Windows.PaletteSetTitleBarLocation.Right;
                                    break;
                            }
                        break;
                    case "Docking":
                    {
                        res = e.GetKeywords("Choose a docking option:","None","Left","Right","Top","Bottom");
                        if (res.Status == Autodesk.AutoCAD.EditorInput.PromptStatus.OK)
                        {
                            switch (res.StringResult)
                            {
                                case "None":
                                    ps.Dock = Autodesk.AutoCAD.Windows.DockSides.None;
                                    break;
                                case "Left":
                                    ps.Dock = Autodesk.AutoCAD.Windows.DockSides.Left;
                                    break;
                                case "Right":
                                    ps.Dock = Autodesk.AutoCAD.Windows.DockSides.Right;
                                    break;
                                case "Top":
                                    ps.Dock = Autodesk.AutoCAD.Windows.DockSides.Top;
                                    break;
                                case "Bottom":
                                    ps.Dock = Autodesk.AutoCAD.Windows.DockSides.Bottom;
                                    break;
                            }
                        }
                        break;
                    }
                }
            }
        }
        
        private static void ps_Load(object sender, Autodesk.AutoCAD.Windows.PalettePersistEventArgs e)
        {
            //demo loading user data
            double a = (double)e.ConfigurationSection.ReadProperty("whatever",22.3);
        }

        private static void ps_Save(object sender, Autodesk.AutoCAD.Windows.PalettePersistEventArgs e)
        {
            //demo saving user data
            e.ConfigurationSection.WriteProperty("whatever",32.3);
        }
    }
}
