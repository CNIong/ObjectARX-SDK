DataExtraction .NET Sample

This sample demonstrates how to use the Data Extraction .NET API. The command in AutoCAD is "Tools->Data Extraction"
 
APIs used in this sample are as follows:

IDxExtractionSettings
IDxDrawingDataExtractor
IDxTypeDescriptor
IDxPropertyDescriptor
IDxFileReference
IDxFolder
 
The commands implemented are:
 
extractAll - extracts all data types and properties from selected drawings 


NOTES:

The Data Extraction API works by setting up Extraction settings via the IDxExtractionSettings. These settings can 
either be initialised by hand or by means of a template file (.dxe). 
Once the Extraction Settings are initalised the API developer must let the Extractor Engine discover the types
and properties available for the selected drawings (IDxDrawingDataExtractor::DiscoverTypesAndProperties), after 
which, the developer can decide which ones to include via SetSelectedTypesAndProperties.
Finally, the Extractor Engine will populate a standard System.Data.DataTable from which a decision can be 
made on how to output, perhaps .csv, .xls or, as this sample demonstrates, .xml.

Please note, to use this sample it's a good idea to copy the .dll to the acad.exe folder.
