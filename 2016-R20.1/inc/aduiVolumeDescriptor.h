//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"

#pragma pack (push, 8)

// This file is also built as part of the acdb dll separately from the rest of
// AdUi.  To do so, we can only use a part of MFC, so a little tweaking is
// needed.
// 
#ifdef ACUTIL_INTERNAL
#include <tchar.h>
#include <afx.h>
#ifdef ADUI_PORT
#undef ADUI_PORT
#endif
#ifdef ACCORE_BUILD
#define ADUI_PORT __declspec(dllexport)
#else
#define ADUI_PORT
#endif
#endif

#include "aduipathenums.h"

// File system types.
enum FS_TYPE {
    NOFS,        // no media in drive (floppy, etc.)
    UKFS,        // unknown, never heard of it!
    NTFS,        // NT file system 
    FAT,         // DOS 8.3 file system
    VFAT,        // Win95 LFN file system
    HPFS,        // OS/2 File system
    CDFS,        // ISO9660/High Sierra
    HFS,         // Mac HFS volume type
    UFS          // UNIX volume type
};


// Some oft used char constants for volume and file names
extern __declspec(selectany) const ACHAR kBackslash =  ACRX_T( '\\' );
extern __declspec(selectany) const ACHAR kColon =      ACRX_T( ':' );
extern __declspec(selectany) const ACHAR kDoubleQuote= ACRX_T( '"' );
extern __declspec(selectany) const ACHAR kEOS =        ACRX_T( '\0' );
extern __declspec(selectany) const ACHAR kPeriod =     ACRX_T( '.' );
extern __declspec(selectany) const ACHAR kSlash =      ACRX_T( '/' );
extern __declspec(selectany) const ACHAR kSpace =      ACRX_T( ' ' );
extern __declspec(selectany) const ACHAR kAsterisk =   ACRX_T( '*' );
extern __declspec(selectany) const ACHAR kQuestionmark = ACRX_T( '?' );   
extern __declspec(selectany) const ACHAR kZero =       ACRX_T( '0' );

/*******************************************************************
   The CAdUiVolumeDescriptor class is the base windows volume class.
   Derived classes corresponding to specific filesystem types are
   intended to perform the real work.
 *******************************************************************/
class ADUI_PORT CAdUiVolumeDescriptor {

friend class CAdUiPathname;

public:

// methods

    CAdUiVolumeDescriptor();
    CAdUiVolumeDescriptor(const CString&);
    virtual ~CAdUiVolumeDescriptor();

    /* return true if the volume is read-only, false otherwise */
    virtual inline BOOL CheckReadOnly() const {return m_d_readonly==1;};

    /* return true if the path is valid according to the rules of 
       this volume type  */
    virtual BOOL ValidateFilename( const CString*,
                         const BOOL wildcard_ok = false ) const =0;

    /* validate a segment of a filename */
    virtual BOOL ValidateSegment( const CString*,
                         const BOOL wildcard_ok = false ) const =0;

    // Return true if the filesystem is case_sensitive.  Note that
    // we're talking about strict case sensitivity, as in Unix.
    virtual BOOL IsCaseSensitive(void) const;

    // Return true if the filesystem preserves case (like FAT, FAT32
    // and NTFS).
    virtual BOOL PreservesCase(void) const;

    // Return true if the filesystem "allows case sensitive lookup".
    // This is the Win32 FS_CASE_SENSITIVE bit.  It's not clear
    // how useful this is, but whatever...
    virtual BOOL AllowsCaseSensitiveLookup(void) const;

    /* convert the string to the upper case if the volume is not
       case sensitive */
    virtual void VolCase( CString& ) const;

    /* return true if the strings match according to volume
       rules on case */
    virtual BOOL VolMatch( const ACHAR * a, const CString* b ) const;
    virtual BOOL VolMatch( const CString* a, const CString* b) const;

    /* return the local drive letter or volume name in the format 
         required to build complete path strings */
    virtual inline const CString* GetLocalName() const { return m_vol_localname;};

    /* return the free space on this volume in units of 1024 bytes.
       As a general rule, if the available space exceeds 2 terabytes, 
       return -1.   */
    virtual LONG GetVolFreeSpace() const;

    /* check for available free space;  i.e. return true if the 
       specified number of bytes is available on this drive;  I 
       think it's safe to assume we won't be creating files 
       larger than 4 Gbytes  for quite a while. */
    virtual BOOL WillFit(DWORD) const;

    /* return true if the volume is still valid; i.e. if the network
       connection is still ok, if the same cd-rom is in the drive,
       etc.  Obviously a NO-OP for a fixed disk. */
    virtual BOOL VolumeValid() const;

#ifdef _DEBUG
    /* a debugging function to dump the contents of the volume
       descriptor in some human readable format */
    virtual void debug_dump(FILE*) const;
#endif

    inline BOOL IsRemote() const { return m_d_remote == 1; }

    inline BOOL IsRemovable() const { return m_d_removable == 1; }

protected:

    void GetConnectionName( void );

    // To be removed in future release.  Just use CString::Find()
    int Find(const CString& str, UINT ch) const;
    int IsControl(int c) const;
    
// data elements

    /* the filesystem type for the drive */
    FS_TYPE m_vol_fs_type;

    /* flags for drive characteristics */
    typedef unsigned flagbits;

    flagbits m_d_fixed:    1;
    flagbits m_d_removable: 1;
    flagbits m_d_cdrom: 1;
    flagbits m_d_remote: 1;
    flagbits m_d_ramdisk: 1;
    flagbits m_d_readonly: 1;
    flagbits m_d_caseSensitive: 1;
    
    /* the local name for this volume */
    CString* m_vol_localname;

    /* the maximum length for any component of a path */
    int    m_max_component_size;

    /* the maximum path length for this volume type */
    int    m_max_path_length;

    /* The correct component separator for this volume type
       To be used in generating file references.  For normal
       work the native UI syntax is always used. */
    ACHAR    m_vol_slash;

    BOOL     mbUnused;  // delete me - was m_amodeMultiByte
    DWORD    m_vol_serial;
    DWORD    m_fsflags;
    CString* m_vol_label;
    CString* m_connection_name;
    const ACHAR * m_doubleslash;
};

class ADUI_PORT CAdUiNTFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiNTFSVolumeDescriptor(const CString&);
        ~CAdUiNTFSVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};


class ADUI_PORT CAdUiVFATVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiVFATVolumeDescriptor(const CString&);
        ~CAdUiVFATVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};


class ADUI_PORT CAdUiHPFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiHPFSVolumeDescriptor(const CString&);
        ~CAdUiHPFSVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};


class ADUI_PORT CAdUiCDFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiCDFSVolumeDescriptor(const CString&);
        ~CAdUiCDFSVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};


class ADUI_PORT CAdUiFATVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiFATVolumeDescriptor(const CString&);
        ~CAdUiFATVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;
    protected:
        
        int m_segc;
};


class ADUI_PORT CAdUiUFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiUFSVolumeDescriptor(const CString&);
        ~CAdUiUFSVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};


class ADUI_PORT CAdUiNOFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiNOFSVolumeDescriptor(const CString&);
        ~CAdUiNOFSVolumeDescriptor(){};

        BOOL ValidateFilename( const CString*,
                               const BOOL wildcard_ok = false ) const;
        BOOL ValidateSegment( const CString*,
                              const BOOL wildcard_ok = false ) const;

};

#pragma pack (pop)

