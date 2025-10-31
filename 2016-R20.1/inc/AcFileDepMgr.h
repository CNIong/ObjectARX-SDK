//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION: Definition for AcFileDependencyManager, for ARX
//              and AcFileDependencyInfo, return data class
//
 
#ifndef _ACFILEDEPMGR_H
#define _ACFILEDEPMGR_H

#pragma pack(push, 8)

/////////////////////////////////////////////////////
///////////// Data class - FDL Entry ////////////////
/////////////////////////////////////////////////////

class AcFileDependencyInfo {
    public:
        const ACHAR *mpFullFileName;
        const ACHAR *mpFileName;
        const ACHAR *mpFoundPath;
        const ACHAR *mpFingerprintGuid;
        const ACHAR *mpVersionGuid;
        const ACHAR *mpFeature;
        bool        mIsModified;
        bool        mAffectsGraphics;
        Adesk::Int32        mIndex;
        Adesk::Int32        mTimeStamp;
        Adesk::Int32        mFileSize;
        Adesk::Int32        mReferenceCount;
};

class ADESK_NO_VTABLE AcFileDependencyManager {
    public:
        virtual ~AcFileDependencyManager() {};
///////////////////////////////////////////////
///////////// Entry Management ////////////////
///////////////////////////////////////////////

        // createEntry:

        // Returns new, permanent (life-of-entry), unique index for this Entry,
        // that an app or feature can store in place of the filename 

        // fullFileName does not have to contain a full-qualified path.
        // If it contains only a base filename, FDL will follow a set of
        // rules for locating the file, and the foundPathname field will 
        // be filled in with the file's actual path. 
        
        // For non-AutoCAD (3rd party) feature types, this rule consists of
        // simply searching the AutoCAD support path, and the current .dwg's directory.
        
        // For XRefs (featurename="ACAD:XRef"), createEntry will retrieve
        // the .dwg's FingerPrint and Version GUIDs, and store them for
        // later retrieval.
        
        // noIncrement should only be set true if you are going thru and "updating"
        // your data, createEntry()s if they don't exist, but leaving them alone
        // if they do.  setting it to true will stop the reference count from being
        // incremented if the record already exists.  It will still return the existing
        // index for the matching record found.
 
        virtual Adesk::Int32 createEntry(const ACHAR *feature,
                                 const ACHAR *fullFileName,
                                 const bool affectsGraphics = false,
                                 const bool noIncrement = false) = 0;

        // For these next 6, caller should check for eKeyNotFound on return.

        // getEntry:
        
        // Returns an AcFileDependencyInfo class that contains
        // all the relevant data on this entry.
        
        // if usedCachedInfo is set to true, the file will NOT be checked
        // for a new time/size/guid, using the OS - instead the last cached
        // values for this and the isModified flag will be returned.
        // This is useful when the entry is being checked repeatedly, as
        // actually checking the file is a time-expensive operation.

        
        virtual Acad::ErrorStatus getEntry(const ACHAR *feature,
                                           const ACHAR *fullFileName,
                                           AcFileDependencyInfo *&fileInfo, 
                                           const bool useCachedInfo = false) = 0;

        virtual Acad::ErrorStatus getEntry(const Adesk::Int32 index,
                                           AcFileDependencyInfo *&fileInfo, 
                                           const bool useCachedInfo = false) = 0;


        // updateEntry:
        
        // Forces this entry to store new (current) time/size/guid info,
        // effectively "resetting" the isModified flag.
        // It's a shortcut for erasing/re-creating a new Entry.
        // This is the ONLY method that will stop an entry from continuing
        // to report "modified" after it has started to.
          
        virtual Acad::ErrorStatus updateEntry(const ACHAR *feature,
                                              const ACHAR *fullFileName) = 0;
                                      
        virtual Acad::ErrorStatus updateEntry(const Adesk::Int32 index) = 0;


        // eraseEntry:
        
        // Remove an entry (or just decrements it's reference count if
        // greater than 1, unless forceRemove is true.)
  
        virtual Acad::ErrorStatus eraseEntry(const ACHAR *feature,
                                             const ACHAR *fullFileName,
                                             const bool forceRemove=false) = 0;
                                      
        virtual Acad::ErrorStatus eraseEntry(const Adesk::Int32 index,
                                             const bool forceRemove=false) = 0;
        
        
        // Returns current count of FDL Entries
        
        virtual Adesk::Int32 countEntries() = 0;
        
///////////////////////////////////////////////
///////////   Iteration   /////////////////////
///////////////////////////////////////////////

        // Iteration initialization
        // If graphicsOnly is true, only entries that affects on-screen graphics
        // are returned.
        // If featurename == NULL, all features entries returned
        // If modified is true, returns only records that have changed since last save
        // (i.e. since the entry was written)
        
        // WalkXRefTree is a special flag that will attempt to walk the entire xref
        // tree by opening each Xref's FDL and pulling those records, all the way down.
        // Any entry anywhere in the tree will be included in the iteration list, if it 
        // matches the feature, graphicsOnly, and modified only arguments.  
        // Note that any Xrefs that do not have an FDL (i.e. AutoCAD 2002 and earlier formats)
        // will get no entries returned. (Obviously.)
        
        // So GC call will look like: 
        // IteratorInitialize(NULL, true, true, true);
        // long needRegen = IteratorNext();  // non-zero index if at least one entry
        // or "while (index = IteratorNext())"
        
        // Note that entries will continue to report as "modified" until the next
        // save (i.e. records are recreated), unless an app/feature wishes to delete
        // and recreate its entries.
        
        virtual void iteratorInitialize(const ACHAR *feature = NULL, 
                                        const bool modifiedOnly = false,
                                        const bool affectsGraphicsOnly = false,
                                        const bool walkXRefTree = false) = 0;

        // Returns the actual entries' index, call until 0.
        // Note that this only returns the entry's index, because some features
        // will use the Iterator only to determine if any records exist.
        // If you want the actual record, just plug the index returned into
        // getEntryByIndex().
        
        // When index returned is 0, we're all done.
        
        virtual Adesk::Int32 iteratorNext() = 0;
};

#pragma pack(pop)

#endif
