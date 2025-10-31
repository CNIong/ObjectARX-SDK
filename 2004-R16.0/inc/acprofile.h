//
//  (C) Copyright 1998-2002 by Autodesk, Inc.  All rights reserved.
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
#pragma pack (push, 8)

class AcApProfileStorage;

class AcApProfileManagerReactor 
{
public:
    virtual void currentProfileWillChange(const char *newProfile);
    virtual void currentProfileChanged(const char *newProfile);
    virtual void currentProfileWillBeReset(const char *currentProfile);
    virtual void currentProfileReset(const char *currentProfile);
    virtual void currentProfileWillBeSaved(const char *currentProfile);
    virtual void currentProfileSaved(const char *currentProfile);
    virtual void profileWillReset(const char *profileName);
    virtual void profileReset(const char *profileName);
    virtual void profileWillBeSaved(const char *profileName);
    virtual void profileSaved(const char *profileName);
    virtual ~AcApProfileManagerReactor() {}
};

typedef AcArray<char*> AcApProfileNameArray;

class AcApProfileManager 
{
    public:

        virtual void ProfileRegistryKey(char*& strRegProfileKey,
                                        const char* strProfileName)=0;

        virtual Acad::ErrorStatus ProfileStorage(AcApProfileStorage*& pStore, 	
                                        const char* strProfileName, 
                                        BOOL bCreateIfNotExists = TRUE)=0;
        virtual Acad::ErrorStatus FixedProfileStorage(AcApProfileStorage*& pStore, 	
                                        BOOL bCreateIfNotExists = TRUE)=0;

        virtual int ProfileListNames(AcApProfileNameArray& nameList)=0;

        virtual Acad::ErrorStatus ProfileExport(const char* strProfileName,
                                                const char* exportFileName)=0;

        virtual Acad::ErrorStatus ProfileImport(const char* strProfileName,
                                                const char* importFileName,
                                                const char* profileDescription,
                                                Adesk::Boolean bImportPathInfo)=0; 

        virtual Acad::ErrorStatus ProfileDelete(const char* strProfileName)=0;

        virtual Acad::ErrorStatus ProfileReset(const char* strProfileName)=0;

        virtual Acad::ErrorStatus ProfileSetCurrent(const char* strProfileName)=0;

        virtual Acad::ErrorStatus ProfileCopy(const char* newProfileName,
                                              const char* oldProfileName,
                                              const char* newProfileDesc)=0;

        virtual Acad::ErrorStatus ProfileRename(const char* newProfileName,
                                                const char* oldProfileName,
                                                const char* newProfileDesc)=0;

        virtual void addReactor(AcApProfileManagerReactor* ) = 0;
        virtual void removeReactor(AcApProfileManagerReactor* ) = 0;

};

extern AcApProfileManager* acProfileManagerPtr();
#define acProfileManager acProfileManagerPtr()

class AcApProfileStorage
{
    public:
        virtual ~AcApProfileStorage() {}
        virtual Acad::ErrorStatus CreateNode(const char* pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus GetNode(const char* pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus ReplaceNode(const char* pszNodePath, 
            IUnknown* pUnknown) = 0;
        virtual Acad::ErrorStatus DeleteNode(const char* pszNodePath) = 0;
        virtual Acad::ErrorStatus GetStorageFile(LPTSTR pszFile) = 0;
        virtual Acad::ErrorStatus Save(void) = 0;
};


#pragma pack (pop)
#endif // _ACPROFILE_H__
