#ifndef ACPLDSDDATA_H
#define ACPLDSDDATA_H
//
//  (C) Copyright 2003 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for AcPlDSDData.h
//

#pragma once

#include "AcPl.h"
#include "AcPlObject.h"
#include "AcPlDSDEntry.h"
#include "AcArray.h"

typedef AcArray<AcPlDSDEntry, AcArrayObjectCopyReallocator <AcPlDSDEntry> > AcPlDSDEntries;

/////////////////////////////////////////////////////////////////////////////
// AcPlDSDData - holds the data for a batch plotting operation

class AcPlDSDData  : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlDSDData)
// Construction
public:

    ACPL_PORT AcPlDSDData();

    ACPL_PORT virtual ~AcPlDSDData();

    ACPL_PORT AcPlDSDData(const AcPlDSDData & src);

    ACPL_PORT AcPlDSDData& operator= (const AcPlDSDData &src);

    ACPL_PORT const char *      projectPath() const;
    ACPL_PORT void              setProjectPath(const char * pVal);

    ACPL_PORT const char *      destinationName() const;
    ACPL_PORT void              setDestinationName(const char * pVal);

    ACPL_PORT void              getDSDEntries(AcPlDSDEntries &val) const;
    ACPL_PORT void              setDSDEntries(const AcPlDSDEntries &val);

    ACPL_PORT int               numberOfDSDEntries() const;
    ACPL_PORT AcPlDSDEntry&     DSDEntryAt(int idx);

    ACPL_PORT AcPlDSDEntry::SheetType sheetType() const;
    ACPL_PORT void                    setSheetType(AcPlDSDEntry::SheetType val);

    ACPL_PORT const char *      password() const;
    ACPL_PORT void              setPassword(const char * pVal);

    ACPL_PORT void              getUnrecognizedData(
                                    AcArray<char*> &sectionArray, 
                                    AcArray<char*> &dataArray) const;
    ACPL_PORT void              setUnrecognizedData(
                                    const AcArray<char*> &sectionArray, 
                                    const AcArray<char*> &dataArray);
    ACPL_PORT void              setUnrecognizedData(
                                    const char * pSectionName, 
                                    const char * pSectionData);
    
    ACPL_PORT unsigned int      majorVersion() const;
    ACPL_PORT void              setMajorVersion(unsigned int majorVersion);

    ACPL_PORT unsigned int      minorVersion() const;
    ACPL_PORT void              setMinorVersion(unsigned int minorVersion);

    ACPL_PORT const char *      sheetSetName() const;
    ACPL_PORT void              setSheetSetName(const char * pSheetSetName);

    ACPL_PORT unsigned int      noOfCopies() const;
    ACPL_PORT void              setNoOfCopies(unsigned int copies);

    ACPL_PORT void              setIsSheetSet(bool bSheetSet);
    ACPL_PORT bool              isSheetSet() const;

    ACPL_PORT bool              isHomogeneous() const;
    ACPL_PORT void              setIsHomogeneous(bool bHomogeneous);
    
    ACPL_PORT bool              plotStampOn() const;
    ACPL_PORT void              setPlotStampOn(bool bOn);

    ACPL_PORT const char *      selectionSetName() const;
    ACPL_PORT void              setSelectionSetName(const char * pSelSetName);

    ACPL_PORT const char *      categoryName() const;
    ACPL_PORT void              setCategoryName(const char * pCategoryName);

    ACPL_PORT const char *      logFilePath() const;
    ACPL_PORT void              setLogFilePath(const char * pLogFilePath);

    ACPL_PORT bool              readDSD(const char *pName);
    ACPL_PORT bool              writeDSD(const char *pName);

    // The following methods are for internal use only 
    ACPL_PORT bool              includeLayerInfo() const;       
    ACPL_PORT void              setIncludeLayerInfo(bool bOn);
    
    ACPL_PORT bool              promptForDwfName() const;
    ACPL_PORT void              setPromptForDwfName(bool bPromptForDwfName);

    ACPL_PORT bool              pwdProtectPublishedDWF() const;
    ACPL_PORT void              setPwdProtectPublishedDWF(
                                    bool bPwdProtectPublishedDWF);

    ACPL_PORT bool              promptForPassword() const;
    ACPL_PORT void              setPromptForPassword(bool bPromptForPassword);
};

#endif // ACPLDSDDATA_H
