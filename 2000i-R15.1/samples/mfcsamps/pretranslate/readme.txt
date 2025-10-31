This sample shows how to pretranslate AutoCAD messages
before they're processed by AutoCAD.
In order to preprocesse AutoCAD messages, a hook function
need to be installed. The following commands install 
different hook functions.

- vhmouse/unvhmouse
  It installs/uninstalls a hook that basically
  makes mouse  move only in vertical direction if
  control key is pressed and only in horizontal
  direction if shift key is pressed.
- caps/uncaps
  It installs/uninstalls a hook that makes all
  letters typed in the command window into
  capital letters.
- noX/yes
  It installs/uninstalls a hook that filters out
  letter 'x' or 'X'.
- watchCC/unwatchCC
  It installs/uninstalls a hook that watchs
  for control-c key.