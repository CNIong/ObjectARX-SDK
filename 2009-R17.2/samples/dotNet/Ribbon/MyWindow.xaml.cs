// (C) Copyright 2006-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

//using Autodesk.AutoCAD.Windows;
using Autodesk.Windows;

namespace TaskDialogSampleWPF
{
    /// <summary>
    /// Interaction logic for MyWindow.xaml
    /// </summary>

    public partial class MyWindow : System.Windows.Window
    {

        public MyWindow()
        {
            InitializeComponent();

            CreateControlToolTip();
        }

        void CreateControlToolTip()
        {
            // I. our own type of tooltip

            // Autodesk.Windows.ToolTip is inside AdWindows.dll which is 
            // independent of AutoCAD
            Autodesk.Windows.ToolTip toolTip1 = new Autodesk.Windows.ToolTip();

            // get the MyToolTips.xaml file  
            System.Windows.ResourceDictionary resDir = new System.Windows.ResourceDictionary();
            resDir.Source = new System.Uri("/AdskRibbon;component/MyToolTips.xaml", UriKind.RelativeOrAbsolute);
            
            // set the tooltip content
            toolTip1.Content = resDir["Acommand"];

            // assign it to the button
            this.Button1.ToolTip = toolTip1;

            // II. MyToolTip - AutoCAD like tooltip - derived from System.Windows.Controls.ToolTip

            MyToolTip toolTip2 = new MyToolTip();

            toolTip2.Content = resDir["MyCommand1"];
            toolTip2.HelpSource = new System.Uri(@".\Help\MyHtmlHelp.chm", UriKind.RelativeOrAbsolute);
            toolTip2.HelpTopic = "Content/MyCommand1.html";

            this.Button2.ToolTip = toolTip2;

            // III. MyToolTipW - AutoCAD like tooltip - derived from Object and wraps Autodesk.Windows.ToolTip

            MyToolTipW toolTip3 = new MyToolTipW();

            toolTip3.ToolTip.Content = resDir["MyCommand2"];
            toolTip3.HelpSource = new System.Uri(@".\Help\MyHtmlHelp.chm", UriKind.RelativeOrAbsolute);
            toolTip3.HelpTopic = "Content/MyCommand2.html";

            this.Button3.ToolTip = toolTip3.ToolTip;

            // IV. Button3's tooltip is defined directly in MyWindows.xaml and is using 
            // MyToolTip as well
        }
   }
}