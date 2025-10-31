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
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
using Autodesk.Windows;

using System.Windows.Interop;
using System.Windows.Input;

namespace TaskDialogSampleWPF
{
    public class MyToolTip : System.Windows.Controls.ToolTip
    {
        public static readonly DependencyProperty HelpSourceProperty;
        public static readonly DependencyProperty HelpTopicProperty;

        public MyToolTip()
        {
        }

        protected override void OnInitialized(System.EventArgs e)
        {
            base.OnInitialized(e);

            this.Margin = new System.Windows.Thickness(0);
            this.Padding = new System.Windows.Thickness(0);

            MyKeyboardHook.getMyKeyboardHook().F1Event += new MyKeyboardHook.F1Handler(MyToolTip_F1Event);
        }

        static MyToolTip()
        {
            HelpSourceProperty = DependencyProperty.Register("HelpSource", typeof(Uri), typeof(MyToolTip));
            HelpTopicProperty = DependencyProperty.Register("HelpTopic", typeof(string), typeof(MyToolTip));
        }

        void MyToolTip_F1Event()
        {
            if (this.IsVisible &&
                HelpTopic != null &&
                HelpSource != null)
            {
                string strSource = HelpSource.OriginalString;
                string strTopic = HelpTopic;

                strSource = strSource.TrimStart(null).TrimEnd(null);
                strTopic = strTopic.TrimStart(null).TrimEnd(null);

                System.Windows.Forms.Help.ShowHelp(null, strSource, strTopic);
            }
        }

        public string HelpTopic
        {
            get { return (string)GetValue(HelpTopicProperty); }
            set { SetValue(HelpTopicProperty, value); }
        }

        public Uri HelpSource
        {
            get { return (Uri)GetValue(HelpSourceProperty); }
            set { SetValue(HelpSourceProperty, value); }
        }
    }
}
