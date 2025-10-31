// Copyright 2005-2008 by Autodesk, Inc.
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
//(Rights in Technical Data and Computer Software), as applicable.
namespace AcCtrlClient
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.axAcCtrl1 = new AxACCTRLLib.AxAcCtrl();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.ldDwg = new System.Windows.Forms.Button();
            this.dwgPath = new System.Windows.Forms.TextBox();
            this.savDwg = new System.Windows.Forms.Button();
            this.DrwLine = new System.Windows.Forms.Button();
            this.UnldDwg = new System.Windows.Forms.Button();
            this.zmExt = new System.Windows.Forms.Button();
            this.regen = new System.Windows.Forms.Button();
            this.tglSpc = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.axAcCtrl1)).BeginInit();
            this.SuspendLayout();
            // 
            // axAcCtrl1
            // 
            this.axAcCtrl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.axAcCtrl1.Enabled = true;
            this.axAcCtrl1.Location = new System.Drawing.Point(21, 12);
            this.axAcCtrl1.Name = "axAcCtrl1";
            this.axAcCtrl1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axAcCtrl1.OcxState")));
            this.axAcCtrl1.Size = new System.Drawing.Size(673, 400);
            this.axAcCtrl1.TabIndex = 0;
            // 
            // openFileDialog1
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // button1
            // 
            this.ldDwg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ldDwg.Location = new System.Drawing.Point(558, 425);
            this.ldDwg.Name = "ldDwg";
            this.ldDwg.Size = new System.Drawing.Size(136, 31);
            this.ldDwg.TabIndex = 1;
            this.ldDwg.Text = "Select Drawing";
            this.ldDwg.UseVisualStyleBackColor = true;
            this.ldDwg.Click += new System.EventHandler(this.ldDwg_Click);
            // 
            // textBox1
            // 
            this.dwgPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dwgPath.Location = new System.Drawing.Point(21, 430);
            this.dwgPath.Name = "dwgPath";
            this.dwgPath.ReadOnly = true;
            this.dwgPath.Size = new System.Drawing.Size(531, 20);
            this.dwgPath.TabIndex = 2;
            // 
            // savDwg
            // 
            this.savDwg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.savDwg.Location = new System.Drawing.Point(25, 510);
            this.savDwg.Name = "savDwg";
            this.savDwg.Size = new System.Drawing.Size(96, 25);
            this.savDwg.TabIndex = 3;
            this.savDwg.Text = "Save Drawing";
            this.savDwg.UseVisualStyleBackColor = true;
            this.savDwg.Click += new System.EventHandler(this.savDwg_Click);
            // 
            // DrwLine
            // 
            this.DrwLine.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.DrwLine.Location = new System.Drawing.Point(25, 468);
            this.DrwLine.Name = "DrwLine";
            this.DrwLine.Size = new System.Drawing.Size(96, 25);
            this.DrwLine.TabIndex = 4;
            this.DrwLine.Text = "Draw Line";
            this.DrwLine.UseVisualStyleBackColor = true;
            this.DrwLine.Click += new System.EventHandler(this.DrwLine_Click);
            // 
            // UnldDwg
            // 
            this.UnldDwg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.UnldDwg.Location = new System.Drawing.Point(136, 510);
            this.UnldDwg.Name = "UnldDwg";
            this.UnldDwg.Size = new System.Drawing.Size(99, 25);
            this.UnldDwg.TabIndex = 5;
            this.UnldDwg.Text = "Unload Drawing";
            this.UnldDwg.UseVisualStyleBackColor = true;
            this.UnldDwg.Click += new System.EventHandler(this.UnldDwg_Click);
            // 
            // zmExt
            // 
            this.zmExt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.zmExt.Location = new System.Drawing.Point(136, 468);
            this.zmExt.Name = "zmExt";
            this.zmExt.Size = new System.Drawing.Size(99, 25);
            this.zmExt.TabIndex = 6;
            this.zmExt.Text = "Zoom Extents";
            this.zmExt.UseVisualStyleBackColor = true;
            this.zmExt.Click += new System.EventHandler(this.zmExt_Click);
            // 
            // regen
            // 
            this.regen.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.regen.Location = new System.Drawing.Point(249, 468);
            this.regen.Name = "regen";
            this.regen.Size = new System.Drawing.Size(98, 24);
            this.regen.TabIndex = 7;
            this.regen.Text = "Regen";
            this.regen.UseVisualStyleBackColor = true;
            this.regen.Click += new System.EventHandler(this.regen_Click);
            // 
            // tglSpc
            // 
            this.tglSpc.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tglSpc.Location = new System.Drawing.Point(366, 468);
            this.tglSpc.Name = "tglSpc";
            this.tglSpc.Size = new System.Drawing.Size(87, 23);
            this.tglSpc.TabIndex = 8;
            this.tglSpc.Text = "Toggle Space";
            this.tglSpc.UseVisualStyleBackColor = true;
            this.tglSpc.Click += new System.EventHandler(this.tglSpc_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(726, 583);
            this.Controls.Add(this.tglSpc);
            this.Controls.Add(this.regen);
            this.Controls.Add(this.zmExt);
            this.Controls.Add(this.UnldDwg);
            this.Controls.Add(this.DrwLine);
            this.Controls.Add(this.savDwg);
            this.Controls.Add(this.dwgPath);
            this.Controls.Add(this.ldDwg);
            this.Controls.Add(this.axAcCtrl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axAcCtrl1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxACCTRLLib.AxAcCtrl axAcCtrl1;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button ldDwg;
        private System.Windows.Forms.TextBox dwgPath;
        private System.Windows.Forms.Button savDwg;
        private System.Windows.Forms.Button DrwLine;
        private System.Windows.Forms.Button UnldDwg;
        private System.Windows.Forms.Button zmExt;
        private System.Windows.Forms.Button regen;
        private System.Windows.Forms.Button tglSpc;
    }
}

