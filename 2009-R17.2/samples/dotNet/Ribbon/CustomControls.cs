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
using Autodesk.Windows;
using System.Windows;
using System.Windows.Controls;
using System.Collections.ObjectModel;
using System.Windows.Media.Imaging;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using acadApp = Autodesk.AutoCAD.ApplicationServices.Application;
using Autodesk.AutoCAD.DatabaseServices;

/// <summary>
/// - Attribute that helps AutoCAD Ribbon identify the class factory which would
///   contain the methods to create ribbon items on demand 
/// </summary>
/// 
[assembly: RibbonItemFactoryClass(typeof(AdskRibbon.AdskRibbonCustomControlFactory))]

namespace AdskRibbon
{
    public class AdskRibbonCustomControlFactory
    {
        /// <summary>
        /// - Attribute in the factory class to identify a method to create a ribbon item on demand
        /// - Documents Gallery Control displayed on the Documents panel
        /// </summary>
        /// 
        [CreateRibbonItem("Documents Gallery Control")]
        public static RibbonItem CreateRibbonGal(RibbonItemMetaData metaData)
        {
            RibbonItem item = new DocumentsGalleryControl();
            return item;
        }

        /// <summary>
        /// - Attribute in the factory class to identify a method to create a ribbon item on demand
        /// - Layouts ListBox Control displayed on the Layouts panel
        /// </summary>
        /// 
        [CreateRibbonItem("Layout ListBox Control")]
        public static RibbonItem CreateLayoutListBox(RibbonItemMetaData metaData)
        {
            RibbonItem item = new LayoutListBoxControl();
            return item;
        }
    }

    /// <summary>
    /// - Enum used by the ModifyContent method of LayoutListBoxControl class
    /// </summary>
    /// 
    public enum ModificationType
    {
        Add = 0,
        Delete = 1,
        Rename = 2,
        Switch = 3
    }

    /// <summary>
    /// - Class to create the Documents gallery control
    /// 
    /// NOTE:
    /// - The DataTemplate used to define the UI for this class must be placed in Themes/generic.xaml for
    ///   AutoCAD Ribbon to identify the template
    /// </summary>
    /// 
    public class DocumentsGalleryControl : RibbonItem 
    {
        public static readonly DependencyProperty ListProperty;
        public static readonly DependencyProperty CurrentProperty;
        
        static DocumentsGalleryControl()
        {
            ListProperty = DependencyProperty.Register("List", typeof(ObservableCollection<DocumentItem>),
                typeof(DocumentsGalleryControl),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    null));
            CurrentProperty = DependencyProperty.Register("Current", typeof(DocumentItem),
                typeof(DocumentsGalleryControl),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    OnCurrentPropertyChanged));
        }

        public DocumentsGalleryControl()
        {
            List = new ObservableCollection<DocumentItem>();
        }

        public ObservableCollection<DocumentItem> List
        {
            get { return (ObservableCollection<DocumentItem>)GetValue(ListProperty); }
            set { SetValue(ListProperty, value); }
        }

        public DocumentItem Current
        {
            get { return (DocumentItem)GetValue(CurrentProperty); }
            set { SetValue(CurrentProperty, value); }
        }

        static void OnCurrentPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            DocumentItem item = (DocumentItem)d.GetValue(CurrentProperty);
            if(item != null)
            {
                Document active = null;
                foreach (Document document in acadApp.DocumentManager)
                {
                    if (item.DocumentHandle == document.Window.Handle.ToString()
                        && document != acadApp.DocumentManager.MdiActiveDocument)
                    {
                        active = document;
                        break;
                    }
                }

                if (active != null)
                {
                    acadApp.DocumentManager.MdiActiveDocument = active;
                }
            }
        }

        public void Initialize()
        {
            foreach(Document doc in acadApp.DocumentManager)
            {
                string text = doc.Name.Substring(doc.Name.LastIndexOf("\\") + 1 );
                DocumentItem temp = new DocumentItem(doc.Window.Handle.ToString(), text);
                List.Add(temp);

                if (doc == acadApp.DocumentManager.MdiActiveDocument)
                {
                    Current = temp;
                }
            }
        }

        public void ResetCurrentItem()
        {
            Document document = acadApp.DocumentManager.MdiActiveDocument;
            foreach (DocumentItem item in List)
            {
                if(item.DocumentHandle == document.Window.Handle.ToString())
                {
                    Current = item;
                }
            }
        }

        public void AddNewItem(Document document)
        {
            string text = document.Name.Substring(document.Name.LastIndexOf("\\") + 1);
            DocumentItem temp = new DocumentItem(document.Window.Handle.ToString(), text);
            List.Add(temp);

            if (document == acadApp.DocumentManager.MdiActiveDocument)
            {
                Current = temp;
            }
        }

        public void RemoveItem(Document document)
        {
            DocumentItem delete = null;
            foreach (DocumentItem item in List)
            {
                if(item.DocumentHandle == document.Window.Handle.ToString())
                {
                    delete = item;
                    break;
                }
            }
            
            if(delete != null)
            {
                List.Remove(delete);
            }
        }
    }

    /// <summary>
    /// - Class used to create GalleryControlItems 
    /// - This class will help us store the Handle of the Document
    /// </summary>
    /// 
    public class DocumentItem : GalleryControlItem
    {
        public static readonly DependencyProperty DocumentHandleProperty;
        
        static DocumentItem()
        {
            DocumentHandleProperty = DependencyProperty.Register("DocumentHandle", typeof(string),
                typeof(DocumentItem),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    null));
        }
        
        public DocumentItem(string handle, string text)
        {
            DocumentHandle = handle;
            Text = text;
            Image = Commands.RibbonDictionary["DWGImage"] as BitmapImage;    
        }

        public string DocumentHandle
        {
            get { return (string)GetValue(DocumentHandleProperty); }
            set { SetValue(DocumentHandleProperty, value); }
        }
    }


    /// <summary>
    /// - Class to create the Layouts ListBox Control
    /// 
    /// NOTE:
    /// - The DataTemplate used to define the UI for this class must be placed in Themes/generic.xaml for
    ///   AutoCAD Ribbon to identify the template
    /// </summary>
    /// 
    public class LayoutListBoxControl : RibbonItem
    {
        public static readonly DependencyProperty ListProperty;
        public static readonly DependencyProperty CurrentProperty;

        static LayoutListBoxControl()
        {
            ListProperty = DependencyProperty.Register("List", typeof(ObservableCollection<LayoutItem>),
                typeof(LayoutListBoxControl),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    null));
            CurrentProperty = DependencyProperty.Register("Current", typeof(LayoutItem),
                typeof(LayoutListBoxControl),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    OnCurrentPropertyChanged));
        }

        public LayoutListBoxControl()
        {
            List = new ObservableCollection<LayoutItem>();
        }

        public ObservableCollection<LayoutItem> List
        {
            get { return (ObservableCollection<LayoutItem>)GetValue(ListProperty); }
            set { SetValue(ListProperty, value); }
        }

        public ListBoxItem Current
        {
            get { return (LayoutItem)GetValue(CurrentProperty); }
            set { SetValue(CurrentProperty, value); }
        }

        static void OnCurrentPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            Database db = acadApp.DocumentManager.MdiActiveDocument.Database;
            LayoutItem item = (LayoutItem)d.GetValue(CurrentProperty);

            if(item != null)
            {
                using (DocumentLock docLock = acadApp.DocumentManager.MdiActiveDocument.LockDocument())
                {
                    if (LayoutManager.Current.CurrentLayout != item.LayoutName)
                    {
                        LayoutManager.Current.CurrentLayout = item.LayoutName;
                    }
                }
            }
        }

        public void Initialize()
        {
            Database db = acadApp.DocumentManager.MdiActiveDocument.Database;

            using(Transaction tr = db.TransactionManager.StartTransaction())
            {
                try
                {
                    string currentLayout = LayoutManager.Current.CurrentLayout;
                    DBDictionary layoutDict = (DBDictionary)tr.GetObject(db.LayoutDictionaryId, OpenMode.ForRead);

                    foreach (System.Collections.DictionaryEntry Obj in layoutDict)
                    {
                        string layout = Obj.Key as string;
                        LayoutItem temp = new LayoutItem(layout);
                        List.Add(temp);
                        if(currentLayout == layout)
                        {
                            Current = temp;
                        }
                    }
                }
                catch
                {
                    tr.Abort();
                }
            }           
        }

        public void ResetContent()
        {
            if(List != null)
            {
                List.Clear();
                Initialize();
            }
        }

        public void ModifyContent(string name, ModificationType typeCode, string newName)
        {
            LayoutItem temp = null;
            switch (typeCode)
            {
                case ModificationType.Add:
                    temp = new LayoutItem(name);
                    List.Add(temp);
                    break;

                case ModificationType.Delete:
                    foreach(LayoutItem item in List)
                    {
                        if(item.LayoutName == name)
                        {
                            temp = item;
                            break;
                        }
                    }

                    if (temp != null)
                    {
                        List.Remove(temp);
                    }
                    break;

                case ModificationType.Rename:
                    foreach (LayoutItem item in List)
                    {
                        if (item.LayoutName == name)
                        {
                            temp = item;
                            break;
                        }
                    }

                    if(temp != null)
                    {
                        List.Remove(temp);
                        temp = new LayoutItem(newName);
                        List.Add(temp);
                    }
                    break;

                case ModificationType.Switch:
                    foreach (LayoutItem item in List)
                    {
                        if (item.LayoutName == name)
                        {
                            temp = item;
                            break;
                        }
                    }

                    if (temp != null)
                    {
                        Current = temp;
                    }
                    break;

                default :
                    break;
            }
        }
    }

    /// <summary>
    /// - Class used to create ListBoxItems 
    /// - This class will help us store the Layout Name
    /// </summary>
    /// 
    public class LayoutItem : ListBoxItem
    {
        public static readonly DependencyProperty LayoutNameProperty;

        static LayoutItem()
        {
            LayoutNameProperty = DependencyProperty.Register("LayoutName", typeof(string),
                typeof(LayoutItem),
                new FrameworkPropertyMetadata(null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsArrange |
                    FrameworkPropertyMetadataOptions.AffectsParentArrange | FrameworkPropertyMetadataOptions.AffectsParentMeasure |
                    FrameworkPropertyMetadataOptions.Inherits,
                    null));
        }

        public LayoutItem(string text)
        {
            LayoutName = text;
            StackPanel panel = new StackPanel();
            panel.Orientation = Orientation.Horizontal;
            
            System.Windows.Controls.Image image = new System.Windows.Controls.Image();
            image.Source = Commands.RibbonDictionary["LayoutImage"] as BitmapImage;
            image.Margin = new Thickness(3.0);
            panel.Children.Add(image);

            TextBlock textBlock = new TextBlock();
            textBlock.Text = LayoutName;
            textBlock.Margin = new Thickness(2.0, 5.0, 0.0, 0.0);
            textBlock.FontSize = 12;
            panel.Children.Add(textBlock);
            this.Content = panel;
            this.Margin = new Thickness(0, 2, 0, 2);
        }

        public string LayoutName
        {
            get { return (string)GetValue(LayoutNameProperty); }
            set { SetValue(LayoutNameProperty, value); }
        }
    }

    /// <summary>
    /// - Class used by a .NET 2.0 PropertyGrid control 
    /// </summary>
    /// 
    public class PropertyGridContent
    {
        private string mColor;
        private string mLayer;
        private string mLinetype;
        private string mLinetypeScale;
        private string mPlotStyle;
        private string mLineweight;
        private string mMaterial;

        public PropertyGridContent()
        {
            mColor = "ByLayer";
            mLayer = "0";
            mLinetype = "Test";
            mLinetypeScale = "1.0000";
            mPlotStyle = "ByBlock";
            mLineweight = "0.0";
            mMaterial = "ByLayer";
        }

        [DescriptionAttribute("Specifies the current color"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string Color
        {
            get { return mColor; }
            set { mColor = value; }
        }

        [DescriptionAttribute("Specifies the current layer"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string Layer
        {
            get { return mLayer; }
            set { mLayer = value; }
        }

        [DescriptionAttribute("Specifies the current linetype"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string Linetype
        {
            get { return mLinetype; }
            set { mLinetype = value; }
        }

        [DescriptionAttribute("Specifies the current linetype scaling factor"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string LinetypeScale
        {
            get { return mLinetypeScale; }
            set { mLinetypeScale = value; }
        }

        [DescriptionAttribute("Specifies the plotstyle name for the object"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string PlotStyle
        {
            get { return mPlotStyle; }
            set { mPlotStyle = value; }
        }

        [DescriptionAttribute("Specifies the current lineweight"),
        CategoryAttribute("General"),
        ReadOnlyAttribute(true)]
        public string Lineweight
        {
            get { return mLineweight; }
            set { mLineweight = value; }
        }

        [DescriptionAttribute("Specifies the material"),
        CategoryAttribute("3D Visualization"),
        ReadOnlyAttribute(true)]
        public string Material
        {
            get { return mMaterial; }
            set { mMaterial = value; }
        }
    }
}
