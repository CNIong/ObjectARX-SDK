//
//  (C) Copyright 1998-2006 by Autodesk, Inc.  All rights reserved.
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

#ifndef   _ACPROFILE_H__
#define   _ACPROFILE_H__

#include "acarray.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class AcApProfileStorage;

class AcApProfileManagerReactor 
{
public:
    virtual void currentProfileWillChange(const ACHAR *newProfile);
    virtual void currentProfileChanged(const ACHAR *newProfile);
    virtual void currentProfileWillBeReset(const ACHAR *currentProfile);
    virtual void currentProfileReset(const ACHAR *currentProfile);
    virtual void currentProfileWillBeSaved(const ACHAR *currentProfile);
    virtual void currentProfileSaved(const ACHAR *currentProfile);
    virtual void profileWillReset(const ACHAR *profileName);
    virtual void profileReset(const ACHAR *profileName);
    virtual void profileWillBeSaved(const ACHAR *profileName);
    virtual void profileSaved(const ACHAR *profileName);
    virtual ~AcApProfileManagerReactor() {}
};

typedef AcArray<ACHAR *> AcApProfileNameArray;

class AcApProfileManager 
{
    public:

        virtual void ProfileRegistryKey(ACHAR *& strRegProfileKey,
                                        const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileStorage(AcApProfileStorage*& pStore,
                                        const ACHAR * strProfileName, 
                                        BOOL bCreateIfNotExists = TRUE)=0;
        virtual Acad::ErrorStatus FixedProfileStorage(AcApProfileStorage*& pStore, 
                                        BOOL bCreateIfNotExists = TRUE)=0;

        virtual int ProfileListNames(AcApProfileNameArray& nameList)=0;

        virtual Acad::ErrorStatus ProfileExport(const ACHAR * strProfileName,
                                                const ACHAR * exportFileName)=0;

        virtual Acad::ErrorStatus ProfileImport(const ACHAR * strProfileName,
                                                const ACHAR * importFileName,
                                                const ACHAR * profileDescription,
                                                Adesk::Boolean bImportPathInfo)=0; 

        virtual Acad::ErrorStatus ProfileDelete(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileReset(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileSetCurrent(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileCopy(const ACHAR * newProfileName,
                                              const ACHAR * oldProfileName,
                                              const ACHAR * newProfileDesc)=0;

        virtual Acad::ErrorStatus ProfileRename(const ACHAR * newProfileName,
                                                const ACHAR * oldProfileName,
                                                const ACHAR * newProfileDesc)=0;

        virtual void addReactor(AcApProfileManagerReactor* ) = 0;
        virtual void removeReactor(AcApProfileManagerReactor* ) = 0;

};

AcApProfileManager* acProfileManagerPtr();
#define acProfileManager acProfileManagerPtr()

class AcApProfileStorage
{
    public:
        virtual ~AcApProfileStorage() {}
        virtual Acad::ErrorStatus CreateNode(const ACHAR * pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus GetNode(const ACHAR * pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus ReplaceNode(const ACHAR * pszNodePath, 
            IUnknown* pUnknown) = 0;
        virtual Acad::ErrorStatus DeleteNode(const ACHAR * pszNodePath) = 0;
        virtual Acad::ErrorStatus GetStorageFile(LPTSTR pszFile) = 0;
        virtual Acad::ErrorStatus Save(void) = 0;
};


#pragma pack (pop)
#endif // _ACPROFILE_H__
