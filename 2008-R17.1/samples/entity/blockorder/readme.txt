BlockOrder sample Readme.txt

 (C) Copyright 2001-2006 by Autodesk, Inc.

This sample demonstrates the use of the index/filter API.
The sample is broken into two binary modules.

1. AsdkblockOrderDb.dbx - defines a filter, index and filtered iterator
   class, and exports them.

2. AsdkblockOrderUi.arx - defines a command BLOCKORDER that lets the
   user select a block reference, then an entity within the block
   reference and finally prompts the user for the draw order of the
   selected entity.

Note: The BLOCKORDER command will not work with Smart blocks.
