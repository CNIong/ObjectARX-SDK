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
    public class MyToolTipW
    {
        public MyToolTipW()
        {
            _ToolTip = new Autodesk.Windows.ToolTip();
            _ToolTip.HelpInvoking += new Autodesk.Windows.ToolTip.HelpInvokingHandle(_ToolTip_HelpInvoking);
        }

        void _ToolTip_HelpInvoking(object sender, HelpInvokingEventArgs e)
        {
            if (HelpTopic != null &&
                HelpSource != null)
            {
                string strSource = HelpSource.OriginalString;
                string strTopic = HelpTopic;

                strSource = strSource.TrimStart(null).TrimEnd(null);
                strTopic = strTopic.TrimStart(null).TrimEnd(null);

                System.Windows.Forms.Help.ShowHelp(null, strSource, strTopic);
            }
        }

        private Autodesk.Windows.ToolTip _ToolTip;
        public Autodesk.Windows.ToolTip ToolTip
        {
            get { return _ToolTip; }
        }

        private string _HelpTopic;
        public string HelpTopic
        {
            get { return _HelpTopic; }
            set { _HelpTopic = value; }
        }

        private Uri _HelpSource;
        public Uri HelpSource
        {
            get { return _HelpSource; }
            set { _HelpSource = value; }
        }
    }
}
