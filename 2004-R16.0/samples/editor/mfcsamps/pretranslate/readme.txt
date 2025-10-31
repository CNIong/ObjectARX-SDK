mfcsamps\pretranslate sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This sample shows how to pretranslate AutoCAD messages
before they're processed by AutoCAD.
In order to preprocesse AutoCAD messages, a hook function
need to be installed. The following commands install 
different hook functions.

- vhmouse/unvhmouse
  Installs/uninstalls a hook that makes the mouse move only in a
  vertical direction if <CTRL> key is pressed, and only in a
  horizontal direction if the <SHIFT> key is pressed.

- caps/uncaps
  Installs/uninstalls a hook that captializes all
  letters typed in the command window.

- noX/yes
  Installs/uninstalls a hook that filters out the
  letters 'x' or 'X'.

- watchCC/unwatchCC
  Installs/uninstalls a hook that watchs
  for <CTRL>+C key combination to be pressed.