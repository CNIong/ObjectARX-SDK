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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AcCtrlClient
{
    public partial class Form1 : Form
    {
        byte tglState; // member variable storing the toggle state to switch between spaces
        public Form1()
        {
            try
            {
                InitializeComponent();
                tglState = 1;
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Perform initialization during load
        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                // Disable all controls that we do not need
                EnableDisable(false);
                this.Text = "AcCtrl sample control";
            
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
            
        }

        // We have a DWG file. Load it into the AcCtrl control 
        // and enable the necessary buttons
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            try
            {
                dwgPath.Text = openFileDialog.FileName;
                axAcCtrl1.Src = openFileDialog.FileName;
                EnableDisable(true);
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Query for a DWG file
        private void ldDwg_Click(object sender, EventArgs e)
        {
            try
            {
                openFileDialog.Filter = "AutoCAD Drawing files(*.dwg)|*.dwg";
                openFileDialog.Multiselect = false;
                openFileDialog.ShowDialog();
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Save changes made to the drawing
        private void savDwg_Click(object sender, EventArgs e)
        {
            try
            {
                axAcCtrl1.PostCommand("qsave ");
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }

        }

        // Draw a line between two hard coded coordinates
        private void DrwLine_Click(object sender, EventArgs e)
        {
            try
            {
                axAcCtrl1.PostCommand("line 10,10 50,50  ");
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Close the drawing
        private void UnldDwg_Click(object sender, EventArgs e)
        {
            try
            {
                axAcCtrl1.Src = "";
                dwgPath.Text = "";
                EnableDisable(false);
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // When a DWG file is not loaded, we do not need certain buttons
        // So disable them when there is no DWG file and enable them otherwise.
        private void EnableDisable(bool enable)
        {
            try
            {
                tglSpc.Enabled = regen.Enabled = zmExt.Enabled = UnldDwg.Enabled = DrwLine.Enabled = savDwg.Enabled = enable;

            }
            catch(System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }

            
        }

        // Zoom extents
        private void zmExt_Click(object sender, EventArgs e)
        {
            try
            {
                axAcCtrl1.PostCommand("zoom e ");
            }
            catch(System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Regen a loaded drawing
        private void regen_Click(object sender, EventArgs e)
        {
            try
            {
                axAcCtrl1.PostCommand("regen ");
            
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }
        }

        // Toggle between model space and paper space
        private void tglSpc_Click(object sender, EventArgs e)
        {
            try
            {
                if (1 == tglState)
                    tglState = 0;
                else
                    tglState = 1;

                axAcCtrl1.PostCommand("tilemode " + tglState.ToString() + " ");
            }
            catch (System.Exception excp)
            {
                MessageBox.Show(excp.Message, "Exception");
            }

        }

    }
}