Sheet Set ReadMe.txt

 (C) Copyright 2002-2003 by Autodesk, Inc.

ABOUT:

This sample demonstrates how to create sheet set components using COM API. It creates a sheet set from scratch and adds sheets based on existing layouts under various categories (both under root and nested). Apart from adding sheets, it shows how to add custom property, label blocks, callout blocks, resource file location and sheet selection set to the sheet set. There is also an example that shows how to sink to sheet set events using an event handler class. 

NOTES:
 
 The path to ssm type library is hard coded to C:\Program Files\Common Files\Autodesk Shared\. Please change it to appropriate location to common shared folder for your install!!!!

Make certain to load this module from the directory it was created in (the folder where drawings are located);   This ensures that the relative paths to the required files is correct.

DEMO:

After loading AsdkSheetSet.arx in the debug directory, try the following 5 commands


SSC  

	This creates a new sheet set overwriting any existing sheet set with the same name. If the sheet is already open by the sheet set navigator (the UI) or by us, a new sheet  set will not be created. An error message "Database already open" is sent to the command line. Give a different name to the new sheet set. 

	After the command completes, try loading the sheet set created into the UI. OPENSHEETSET is the command to open it - navigate to where you created the new sheet set to load it.

	You should see the result of all the components created in the UI. Right click on sheet set root and select menu item "Properties". Check out the label and call out blocks added.l Go to resource tab and see the path to resource location added. Double clicking on the path will expand it.


SSListAll 

	This lists all the sheets and categories names for every sheet set currently open by the sheet set manager. The output is sent to the command line.


SSList

	This accepts a *.dst (sheet set) file name from the user and lists it. The sheet set may or may not be open already.



Best Practices when accessing sheet set objects:


- Db should only be locked when you plan to make changes and should

  be locked and unlocked as few times as possible.

 
- Do not directly cache pointers to sheet set objects. Use objectids. 

  A reload of the db  that occurs on lock, or unlock will cause 

  object pointers to become invalid. ObjectIds avoid this issue.

  Use the IAcSmObjectId interface to maintain a reference to a 

  dst resident object.
  

   In other words... Object instances should not be directly accessed 

  after the db has been unlocked. If you need to access a sheet set resident

  object after an unlock call, store the id, unlock, and then use 

  the id to get the instance of the object.

 

For example: (error checking omitted for clarity)

    //lock the db

    hr = pSheetSetDb->LockDb(pSheetSetDb); //changed to just one lock call

 

    // create a new subset

    CComPtr<IAcSmSubset> pSubset = NULL;

    hr = pSheetSet->CreateSubset(_bstr_t(strName), _bstr_t(strName), &pSubset);

 

    // get the objectid of the new subset

    CComPtr<IAcSmObjectId> pId = NULL;

    pSubset->GetObjectId(&pId);

 

    // unlock the db

    pSheetSetDb->UnlockDb(pSheetSetDb, true); //IMPORTANT NOTE: Do not hold on to object pointers across unlock calls.

 

    // use the pId to access the new subset ...

    pSubset = NULL;

    pId->GetPersistObject(&pSubset);

 

