BlockOrder Sample

This sample demostrates the use of the index/filter API. 
The sample is broken into two binary modules.
1. AsdkblockOrderDb.dbx - defines a filter and index and filtered iterator class and exports them.
2. AsdkblockOrderUi.arx - defines a command "BLOCKORDER" that lets the user select a block reference then a an entity within the block reference, finally it prompts the user for draw order of the selected entity.