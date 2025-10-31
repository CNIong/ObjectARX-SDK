Status Bar SDK Sample:

There is a new Status Bar API for customization of the AutoCAD document status bars. The API allows creation of buttons, icons and bubble notifications which are fully customizable with a variety of styles.  This sample demonstrates several of these features.

To test, build using the ARX SDK, and load the ARX module into AutoCAD.  The Sample will create 5 icons on each open document's status bar;  2 Pane buttons on the bottom (1 icon and 1 text), and 3 tray icons in the lower right hand corner of the document.  Each button is represented by a derived class,  the overrides of which are callbacks for the items, handling events such as Left/Right/double click.

The sample defines the NOTIFY command to display a simple bubble-notification for the current document.

The sample also implements an AcApDocumentReactor to handle document creation and deletion events, to dynamically create and destroy the tray items.