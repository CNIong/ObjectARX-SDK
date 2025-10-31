// (C) Copyright 2002-2008 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

using System;
using System.Collections.Generic;
using System.IO;
using Autodesk.AutoCAD;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Windows;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.DataExtraction;

namespace ClassLibrary
{
  /// <summary>
  /// Summary description for adskClass.
  /// </summary>
  public class adskClass
  {
    public adskClass()
    {
      Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
      ed.WriteMessage("\nData Extraction Sample Loaded");
      ed.WriteMessage("\nCommands are:");
      ed.WriteMessage("\n\nextractAll - extracts all data types and properties from selected drawings\n");
    }

    // Extract all data types from selected drawings  
    [CommandMethod("extractAll")]
    public void extractData() // This method can have any name
    {
      bool useTemplate = false;
      IDxExtractionSettings extractionSettings = null;
      IDxDrawingDataExtractor dwgExtractor = null;
      try
      {
        // Use a template
        if (GetYesNo("Use template? [Yes/No]") == "Yes")
        {
          // ask the user for the template file, then load it into the extraction manager
          useTemplate = InitialiseTemplateFile(ref extractionSettings);
          // if we got a template
          if (useTemplate)
          {
            // now create the drawing extractor
            dwgExtractor = extractionSettings.DrawingDataExtractor;
          }
        }
      }
      catch
      {
        return;
      }

      // if not using template or the initialise template failed then
      if (!useTemplate)
      {
        // ok, now create one from scratch
        extractionSettings = new DxExtractionSettings();
        // now create the drawing extractor
        dwgExtractor = extractionSettings.DrawingDataExtractor;

        try
        {
          // Do we want to extract data from Xrefs?
          if (GetYesNo("Extract Data from ModelSpace Only? [Yes/No]") == "Yes")
            dwgExtractor.Settings.ExtractFlags |= ExtractFlags.ModelSpaceOnly;
          else
            // otherwise clear the flag
            dwgExtractor.Settings.ExtractFlags &= ~ExtractFlags.ModelSpaceOnly;

          // Do we want to extract data from Xrefs?
          if (GetYesNo("Extract Data from XRefs? [Yes/No]") == "Yes")
              dwgExtractor.Settings.ExtractFlags |= ExtractFlags.XrefDependent;
          else
            // otherwise clear the flag
            dwgExtractor.Settings.ExtractFlags &= ~ExtractFlags.XrefDependent;

          // how about nested blocks
          if (GetYesNo("Extract Data from nested Blocks? [Yes/No]") == "Yes")
            dwgExtractor.Settings.ExtractFlags |= ExtractFlags.Nested;
          else
            // otherwise clear the flag
            dwgExtractor.Settings.ExtractFlags &= ~ExtractFlags.Nested;
        }
        catch
        {
          return;
        }

        // select drawing file(s), the user may enter a path/filename.dwg or path/a*.dwg
        if (!SelectDrawingFiles(Environment.CurrentDirectory, dwgExtractor))
          return;
        
        // Scan the collection of drawings for object types and their properties
        dwgExtractor.DiscoverTypesAndProperties(Environment.CurrentDirectory);
        // extract what we found
        List<IDxTypeDescriptor> types = dwgExtractor.DiscoveredTypesAndProperties;
        
        List<string> selectedTypes = new List<string>();
        List<string> selectedProps = new List<string>();

        // select all types and properties for extraction
        foreach (IDxTypeDescriptor type in types)
        {
          selectedTypes.Add(type.GlobalName);
          foreach (IDxPropertyDescriptor prop in type.Properties)
          {
            if (!selectedProps.Contains(prop.GlobalName))
              selectedProps.Add(prop.GlobalName);
          }
        }
        // tell the extractor what objects we want to include
        dwgExtractor.Settings.SetSelectedTypesAndProperties(types, selectedTypes, selectedProps);
      }
      
      // now extract them
      dwgExtractor.ExtractData(Environment.CurrentDirectory);
      // get the datatable created
      System.Data.DataTable dataTable = dwgExtractor.ExtractedData;

      // select select the name and path of the xml file
      if (!SelectXMLFile(Environment.CurrentDirectory, dataTable))
        return;
    }

    //////////////////////////////////////////////////////////////////////////    
    // utility functions
    //////////////////////////////////////////////////////////////////////////    
    public bool InitialiseTemplateFile(ref IDxExtractionSettings extractionSettings)
    {
      Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

      bool useTemplate = false;
      while (!useTemplate)
      {
        PromptStringOptions filenameOptions = new PromptStringOptions("Enter template path ");
        filenameOptions.AllowSpaces = true;
        PromptResult res = ed.GetString(filenameOptions);
        if (res.Status != PromptStatus.OK)
          return false;
        if (res.StringResult.Length == 0)
          continue;
        if (res.StringResult.Length == 1 && res.StringResult == "~")
        {
          // pop up the file select dialog
          if (SelectTemplateFileAndLoad(ref extractionSettings))
            // if ok, return success
            return true;
          else
            return false;
        }
        else
        {
          // if he entered the path directly to the command line, try and load the template
          if (LoadTemplateFromFile(res.StringResult, ref extractionSettings))
            return true;
          else
            continue;
        }
      }

      return false;
    }

    //////////////////////////////////////////////////////////////////////////    
    // display select file dialog to select a IDxExtractionSettings template file
    private bool SelectTemplateFileAndLoad(ref IDxExtractionSettings extractionSettings)
    {
      // set no urls or ftp sites
      OpenFileDialog.OpenFileDialogFlags flags = OpenFileDialog.OpenFileDialogFlags.NoUrls | OpenFileDialog.OpenFileDialogFlags.NoFtpSites;
      // create a new select dialog
      OpenFileDialog ofd = new OpenFileDialog("Select Template file", "", "dxe", "BrowseTemplateFile", flags);

      bool bCheckFile = true;
      while (bCheckFile)
      {
        if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
        {
          if (LoadTemplateFromFile(ofd.Filename, ref extractionSettings))
          {
            bCheckFile = false;
            return true;
          }
          else
            System.Windows.Forms.MessageBox.Show("Failed to open that template file, please try again...");
        }
        else
          bCheckFile = false;
      }
      return false;
    }


    //////////////////////////////////////////////////////////////////////////    
    // ask the user to select the drawings required
    private bool SelectDrawingFiles(string curFolder, IDxDrawingDataExtractor dwgExtractor)
    {
      Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;

      bool folderName = false;
      bool fullPath = false;
      bool wildCards = false;
      bool recurseFolders = false;
      // ask the questions for the type of entry required
      try
      {
        // this enabled easy demonstration of what is available via the API
        if (GetYesNo("Enter folder name? [Yes/No]") == "Yes")
          folderName = true;
        else
        {
          if (GetYesNo("Enter full drawing path? [Yes/No]") == "Yes")
            fullPath = true;
          else
          {
            if (GetYesNo("Enter full drawing path with wildcards? [Yes/No]") == "Yes")
              wildCards = true;
          }
        }

        // if not a single file, ask if he wants to recurse the folders
        if (!fullPath)
        {
          if (GetYesNo("Recurse folders? [Yes/No]") == "Yes")
            recurseFolders = true;
        }
      }
      catch
      {
        return false;
      }

      bool ok = false;
      while (!ok)
      {
        PromptStringOptions filenameOptions = new PromptStringOptions("Enter path ");
        filenameOptions.AllowSpaces = true;
        PromptResult res = ed.GetString(filenameOptions);
        if (res.Status != PromptStatus.OK)
          return false;
        if (res.StringResult.Length == 0)
          continue;
        else
        {
          // if just a folder name
          string fileName = "";
          if (folderName)
          {
            System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(res.StringResult);
            // extract the folder name
            fileName = di.FullName;
          }
          else if (!wildCards) // if wildcards, Fileinfo will throw an exception
          {
            System.IO.FileInfo fi = new System.IO.FileInfo(res.StringResult);
            // otherwise the full file path
            fileName = fi.FullName;
          }

          // if not a single file name
          if (!fullPath)
          {
            string folderPath = res.StringResult;
            // if wild cards, we need to do our own processing
            string wildCard = "";
            if (wildCards)
            {
              int index = res.StringResult.LastIndexOf("/");
              // if not found
              if (index == -1)
              {
                index = res.StringResult.LastIndexOf(@"\");
                // if not found, then we can't have a path
                if (index == -1)
                {
                  wildCard = res.StringResult;
                  folderPath = ".";
                }
                else
                {
                  // from path c:\temp\t*.dwg make wildcard t*.dwg
                  wildCard = res.StringResult.Substring(index+1);
                  // and folderpath c:\temp
                  folderPath = folderPath.Remove(index);
                }
              }
              else
              {
                // from path c:\temp\t*.dwg make wildcard t*.dwg
                wildCard = res.StringResult.Substring(index + 1);
                // and folderpath c:\temp
                folderPath = folderPath.Remove(index);
              }
            }

            IDxFileReference dxFileReference = new DxFileReference(curFolder, folderPath);
            IDxFolder dxFolder = new DxFolder(dxFileReference, wildCard, recurseFolders, wildCards, true);
            dwgExtractor.Settings.DrawingList.AddFolder(dxFolder);

            // Now that we've added the folder, we need to enumerate the 
            // drawings that are currently in that folder and added them 
            // to the SelectedFiles collection. This is due to an issue with the
            // way the SelectedFiles property works within the API.
            
            dxFolder.SelectedFiles.Clear();
            IEnumerator<FileInfo> fIter = dxFolder.GetEnumerator(curFolder);
            while (fIter.MoveNext())
            {
                FileInfo fi = fIter.Current;
                IDxFileReference fr = new DxFileReference(curFolder, fi.FullName);
                dxFolder.SelectedFiles.Add(fr);
            }
          }
          else
          {
            IDxFileReference dxFileReference = new DxFileReference(curFolder, fileName);
            dwgExtractor.Settings.DrawingList.AddFile(dxFileReference);
          }

          return true;
        }
      }

      return false;
    }

    //////////////////////////////////////////////////////////////////////////
    // select select the name and path of the xml file
    private bool SelectXMLFile(string curFolder, System.Data.DataTable dataTable)
    {
      bool ok = false;
      while (!ok)
      {
        PromptStringOptions tableNameOptions = new PromptStringOptions("Enter the name of the Table <MyTable> ");
        tableNameOptions.AllowSpaces = true;
        Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
        PromptResult res = ed.GetString(tableNameOptions);
        if (res.Status != PromptStatus.OK)
          return false;
        if (res.StringResult.Length == 0)
        {
          dataTable.TableName = "MyTable";
          break;
        }
        else
        {
          dataTable.TableName = res.StringResult;
          break;
        }
      }

      // find a place to output the xml file
      string fileName = null;
      if (BrowseSaveFile("Save XML File", "xml", ref fileName))
      {
        // now output it
        dataTable.WriteXml(fileName);
        return true;
      }

      return false;
    }

    //////////////////////////////////////////////////////////////////////////    
    // browse the output filepath
    private bool BrowseSaveFile(string prompt, string extension, ref string fileName)
    {
      // set no urls or ftp sites
      SaveFileDialog.SaveFileDialogFlags flags = SaveFileDialog.SaveFileDialogFlags.NoUrls | SaveFileDialog.SaveFileDialogFlags.NoFtpSites;

      //  set the start directory to "My Documents" or equiv
      string startLoc = System.Environment.GetFolderPath(System.Environment.SpecialFolder.Personal);
      if (!startLoc.EndsWith("\\"))
        startLoc += "\\";

      // create the dialog
      SaveFileDialog ofd = new SaveFileDialog(prompt, startLoc, extension, "BrowseSaveFile", flags);
      bool ok = false;
      while (!ok)
      {
        if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
        {
          fileName = ofd.Filename;
          return true;
        }
      }
      return false;
    }

    //////////////////////////////////////////////////////////////////////////    
    // set the template for the extraction manager
    bool LoadTemplateFromFile(String fileName, ref IDxExtractionSettings extractionSettings)
    {
      try
      {
        extractionSettings = DxExtractionSettings.FromFile(fileName);
        if (extractionSettings != null)
          return true;
        else
          return false;
      }
      catch (System.Exception e)
      {
        Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
        ed.WriteMessage("\nProblem reading template " + fileName + "\n" + e.Message);
      }
      return false;
    }

    //////////////////////////////////////////////////////////////////////////
    // return a yes or no for a given prompt
    public string GetYesNo(string prompt)
    {
      // find out where the user wants to extract the data from...
      PromptKeywordOptions options = new PromptKeywordOptions(prompt, "Yes No");
      options.Keywords.Default = "Yes";

      Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
      PromptResult res = ed.GetKeywords(options);
      // if ESC is hit, throw an exception
      if (res.Status == PromptStatus.Cancel)
        throw new System.Exception();

      return res.StringResult;
    }
  }
}