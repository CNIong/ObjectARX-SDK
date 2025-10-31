// (C) Copyright 2007 by Autodesk, Inc.
// Ribbon Sample - .NET API Sample
//

 
NOTE: 

1) In order to compile the Ribbon sample, you must install Visual Studio 2005 extensions for .NET Framework 3.0 (WCF & WPF), November 2006 CTP (http://www.microsoft.com/downloads/details.aspx?FamilyId=F54F5537-CC86-4BF5-AE44-F5A1E805680D&displaylang=en).
2) The assembly built by this sample, "AdskRibbon", should be placed in the AutoCAD install folder for this sample to run properly.
3) Make sure the file "MyHtmlHelp.chm" (included with the sample) is copied to a folder "Help" within the AutoCAD install folder. This is necessary for the tooltips to work properly.

Description:

This sample demonstrates usage of several .NET APIs including the Ribbon API, the Task Dialog API, the ToolTip API and the Menu Browser API.

RIBBON API:
**************************************************************************************************************************
This sample implements a command called "CustRibbon". This command demonstrates the APIs to be used to add a custom ribbon tab to the default AutoCAD ribbon. The Custom Tab added will contain two panels of which one(Documents panel) is defined in the resource dictionary or a XAML file and the other (Layouts panel) is created runtime.


Documents panel:
-------------------------------------------------------------------------
This panel is defined in the ResourceDictionary.

DocumentsGalleryControl 
- This control lists a collection of all documents open in AutoCAD. This is a custom ribbon item defined in this sample. This class inherits from RibbonItem as this class is used to create an item in the ribbon. The DataTemplate to define the UI for the custom control must be defined in Themes/generic.xaml file.

RibbonDropDownButton
- This flyout consists of two RibbonButton items that implement the new & open commands of AutoCAD.
-------------------------------------------------------------------------

Layouts panel:
-------------------------------------------------------------------------
This panel is created runtime.

LayoutListBoxControl 
- This control lists a collection of all layouts of the active document. This is also a custom ribbon item similar to the DocumentsGalleryControl defined in this sample. 

RibbonButton(CreateLayout)
- This button is placed in the slide out panel of the layouts panel. It creates a layout using the "CreateLayout" command defined in this application.

RibbonButton(Select Entity)
- This button is also placed in the slide out panel of the layouts panel. This button would prompt the user to select an entity and display a Custom Contextual Tab consisting of a single panel(Entity Properties).  

Note: The “Custom Contextual Tab” here is created in Merge mode so that we can display two tabs at a time (one normal tab – “Custom Tab” and a Contextual Tab – “Custom Contextual Tab”) and it would be removed upon deactivating the Custom Tab.
-------------------------------------------------------------------------

Entity Properties panel:
-------------------------------------------------------------------------
This panel is defined in the ResourceDictionary and would host a .NET 2.0 PropertyGrid control.

****************************************************************************************************************************

Task Dialog API:
****************************************************************************************************************************
The following commands are defined to demonstrate the task dialog API:

1) TaskDialogSimple: shows a simple task dialog, which is created using a single static function called ShowDialog.

2) TaskDialogProgressBar: shows how to take advantage of using task dialog progress bars. Useful for providing feedback to the user during a lengthy process. If you want to use hyperlinks in your taskdialog, then you can use it as a reference for that as well. When you click on the Autodesk hyperlink in the dialog, then the www.autodesk.com site is opened in a browser.

3) TaskDialogWPF: shows how to create a task dialog from an xaml resource dictionary with WPF (Windows Presentation Foundation) objects in it. 
It also presents the usage of verification, which can be useful when the same message is likely to come up several times and therefore we want to let the user suppress them. 
Once suppressed, this dialog will be shown in the Hidden Messages Settings dialog, where it can be unsuppressed by selecting them.


****************************************************************************************************************************

ToolTip API:
****************************************************************************************************************************
The sample implements a single command "ToolTip" to demonstrate the concepts of the ToolTip API (explained below). This command displays a simple dialog with buttons. Hovering over these buttons display different kinds of tooltips:

The tool tip of the buttons in the Ribbon are of two types:

1) One is a simple ToolTip, which is not AutoCAD specific, and can be used to add some small information aboutyour dialog controls.

2) One is using CommandToolTip as a template, which is AutoCAD specific, and can be used to provide the same look and feel as the standard AutoCAD tooltips of e.g. the buttons in the AutoCAD Ribbon.
It automatically uses the settings available on the Display tab of the Options dialog.
[e.g. the time for the extended content to appear] 
Shows the use of progressive panel, which means, that you can display several pages of content with a time delay between them. 
In case of pressing F1 while the tool tip is visible, it will bring up a given topic from a help file [chm].
To make the F1 help work, you need to copy the MyHtmlHelp.chm file into the "[AutoCAD install folder]/Help" folder.
The properties set programmatically can also be set directly in the xaml file of your WPF dialog/window.

****************************************************************************************************************************

Menu Browser API:
****************************************************************************************************************************
The following commands are defined to demonstrate the menu browser API:

1) MbShow: Show the MenuBrowser Window at a specific screen location

2) MbAdd: Add a new Item after “File > Open”, with the name “NewItemForTest” and if you click it, the command “time” will be execute.

3) MbDel: Remove the “File > Open” menu item from Menu Browser

4) MbAddMenu: Add a new Root Menu

Note: Please do not run the MbAdd command after running the MbDel command. The MbDel command removes the "File > Open" menu item that MbAdd depends on.

****************************************************************************************************************************

Steps to test:
1. Build the project to generate AdskRibbon.dll and copy it to AutoCAD install folder
2. NETLOAD AdskRibbon.dll (in the AutoCAD install folder)
3. Run any of the above commands you want to test.