Docman

 (C) Copyright 1998 by Autodesk, Inc.
This sample demonstrates some aspects of the MDI document management API.

The following commands are available

LISTDOCS - lists all open documents.
WATCHDOCS - starts/stops watching document activity. When on it prints messages to the command line about various mdi operations. Such as activation, creation, locking etc.
SEND - exercises switching between documents and sending commands.
TOGGLE - exercises toggling activation on and off.
NEWDOC - exercises creating new document in MDI using standard user interface.
OPENDOC - exercises opening a document in MDI using standard user interfacec.
CLOSEDOC - exercises closing a document in MDI using standard user interface.
CMD - routine to exercise ads_command
ACTIVATE - utility to have the user choose an open document to be activated programmatically. 
APPCONTEXT - requests a routine to be executed via the application context.
OPENSYNCDOC - requests a OPEN to be executed via the application context. 
NEWSYNDOC - requests a NEW to be executed via the application context.

Please see the Remarks section for each command handle for more details on these command.

TESTDLG - displays a modeless dialog with several UI elements that perform MDI API calls.
          Below is a description of the UI elements.

Buttons:
-----------

AppContextNew Document:  calls appContextNewDocument.

AppContextOpen Document: calls appContextOpenDocument.

New Doc: calls newDocument()

Open Doc: calls openDocument()

Send String: calls sendStringToExecute with a hardcoded string to draw a line
             from 0,0 to 5,5. Note: you first need to select a document in the
             listbox that specifies which document the string is going to be sent to.

Activate Doc: calls activateDocument. Note: you first need to select a document
              in the listbox.

Close Doc: calls closeDoc. Note: you first need to select a document in the listbox.

Is Doc Quiescent?: checks if the document is in a quiescent state (by calling
                   isQuiescent) and displays the documents lock modes too.

Set Current Doc: calls unlockDocument and then setCurDocument. Note: you first need
                 to select a document in the listbox that specifies which document is
                 going to become the current document and also you need to select a
                 lock mode for the document in the lock mode droplist.

Refresh Dialog: use this button to refresh all UI elements in case you are suspicious
                that an event was not intercepted by the modeless dialog.

Other UI elements:
------------------------

Doc. Activation Enabled (CheckBox): displays the current activation state. Allows
                                    the user to enable/disable document activation.
                                    The documentActivationModified reactor can also
                                    change the value of this checkbox.

lock mode DropList: to be used in conjunction with the SetCurrentDoc button.

Document to become current (field): displays the name of the document indicated by a
                                    documentToBecomeCurrent reactor.

Active/Current Document groups: displays the document title, LockMode, myLockMode of
                                the active and current documents (that are not
                                necessarily the same)




