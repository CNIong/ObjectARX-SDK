Mfcsamps\ExtendTabs sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This sample demonstrates how to add some additional tabs to the Options 
dialog box.

Some key points:
	- This sample uses an MFC extension dll.
	- # derivatives are provided in stdafx.h which enables your debug
	  project to work with release AutoCAD.
	- There is a new temporary resource override class.
	- _hdllInstance is a global variable.

This application adds two tabs to the OPTIONS dialog box in AutoCAD.
The Tabs are CTab1 and CTab2, both of which are derived from
CAcUiTabChildDialog. In the acrxEntryPoint() of our application, we call
initApp(). This in turn registers our AutoCAD custom command EXTTABS. In
addition to registering the command "EXTTABS", we call upon the services of the
CAcUiTabExtensionManager when we call:

acedRegisterExtendedTab("EXTENDTABS.ARX", "OptionsDialog");

See documentation (MFC Topics) for further details on the usage of
acedRegisterExtendedTab. This function take two arguments, namely the name of
our ObjectARX application and the AutoCAD dialog that we wish to extend.

The EXTTABS command is pretty straightforward in that we launch our modal
dialog, CMyDlg, which is a simple dialog where we ask the user to execute the
AutoCAD OPTIONS command. If you notice in the acrxEntryPoint() we have an
AcRx::kInitDialogMsg message which is called each time the OPTIONS command
is executed. This in turn calls addMyTabs() which takes as a parameter the
CAdUiTabExtensionManager parameter 'pXtabManager'. We have two global automatic
storage variables, gTab1 and gTab2, of type CMyTab1 and CMyTab2 respectively.
Here, we ask the tab extension manager to add these custom tabs to the OPTIONS
dialog (AddTab).  The OPTIONS dialog is a resizable dialog. In this section of
the application, we respond to the resizing event, using the
following functions:

StretchControlXY(), MoveControlX(), MoveControlY()
(See CAdUiDialog Resizing Functions for more detail and additional functions.)

All of these functions take as a first parameter a resource ID, which is the ID
of the control itself. The remaining parameters indicate the change in the X and
Y direction for the control in the tabbed dialog.

The tabbed dialogs themselves are pretty straightforward. In the CTab1 class,
notice how we call some of the virtual functions that the CAdUiTabChildDialog
have to offer. Remember that CAcUiTabChildDialog is derived from CAdUiTabChildDialog.
The functions that we override are:

CAdUiTabChildDialog::OnMainDialogOK()
CAdUiTabChildDialog::OnMainDialogHelp()
CAdUiTabChildDialog::OnMainDialogOK()

There are many other other funciton available to you also in the
CAdUiTabChildDialog class.

When you unload the ExtendTabs.arx application, the global variables gTab1 and gTab2
are no longer in scope and the OPTIONS dialog returns to normal.
