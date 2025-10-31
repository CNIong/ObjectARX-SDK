//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2016 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"
#include "acarray.h"
#include "AcString.h"

#pragma pack (push, 8)
#include "aduipathenums.h"
#ifndef _ADESK_MAC_
#define  MAX_PATH 260
#endif
namespace Autodesk
{
    namespace AutoCAD
    {
        namespace PAL
        {
            namespace FileSystem
            {
                class VolumeDescriptor;
            }
        }
    }
}
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
class ACBASE_PORT CAdUiVolumeDescriptor {

friend class CAdUiPathname;

public:

// methods

    CAdUiVolumeDescriptor();
    CAdUiVolumeDescriptor(const AcString&);
    virtual ~CAdUiVolumeDescriptor();

    /* return true if the volume is read-only, false otherwise */
    virtual bool CheckReadOnly() const ;

    /* return true if the path is valid according to the rules of 
       this volume type  */
    virtual bool ValidateFilename( const AcString*,
                                   bool wildcard_ok = false ) const =0;

    /* validate a segment of a filename */
    virtual bool ValidateSegment( const AcString*,
                                  bool wildcard_ok = false ) const =0;

    /* convert the string to the upper case if the volume is not
       case sensitive */
    virtual void VolCase( AcString& ) const;

    /* return true if the strings match according to volume
       rules on case */
    virtual bool VolMatch( const ACHAR * a, const AcString* b ) const;
    virtual bool VolMatch( const AcString* a, const AcString* b) const;

    /* return the local drive letter or volume name in the format 
         required to build complete path strings */
    virtual inline const AcString* GetLocalName() const { return m_vol_localname;};

    /* return the free space on this volume in units of 1024 bytes.
    As a general rule, if the available space exceeds 2 terabytes,
    return -1.   */
    virtual Adesk::UInt64 GetVolFreeSpace() const;

    /// <summary>
    /// Check if the volume is remote
    /// </summary>
    /// <returns>Return true if this is a remote volume , false otherwise.</returns>
    bool IsRemote() const;

    /// <summary>
    /// Check if the volume is removable
    /// </summary>
    /// <returns>Return true if this is a removable volume , false otherwise.</returns>
    bool IsRemovable() const;

    /// <summary>
    /// This function gets maximal component size and return the size value.
    /// </summary>
    /// <returns>Return the size value.</returns>
    int getMaxComponentSize() const;

protected:

// data elements

    /* the filesystem type for the drive */
    FS_TYPE m_vol_fs_type;

    /* the local name for this volume */
    AcString* m_vol_localname;

    /* the maximum path length for this volume type */
    int    m_max_path_length;

    Autodesk::AutoCAD::PAL::FileSystem::VolumeDescriptor* mpVolumeDescriptor;

    bool IsNameLegal(const AcString* name, const AcString&  sIllegalName, bool isFileName = false) const;
};

class ACBASE_PORT CAdUiNTFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiNTFSVolumeDescriptor(const AcString&);
        ~CAdUiNTFSVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};


class ACBASE_PORT CAdUiVFATVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiVFATVolumeDescriptor(const AcString&);
        ~CAdUiVFATVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};


class ACBASE_PORT CAdUiHPFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiHPFSVolumeDescriptor(const AcString&);
        ~CAdUiHPFSVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};


class ACBASE_PORT CAdUiCDFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiCDFSVolumeDescriptor(const AcString&);
        ~CAdUiCDFSVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};


class ACBASE_PORT CAdUiFATVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiFATVolumeDescriptor(const AcString&);
        ~CAdUiFATVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;
    protected:
        
        int m_segc;
};


class ACBASE_PORT CAdUiUFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiUFSVolumeDescriptor(const AcString&);
        ~CAdUiUFSVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};


class ACBASE_PORT CAdUiNOFSVolumeDescriptor : public CAdUiVolumeDescriptor {

    public:

        CAdUiNOFSVolumeDescriptor(const AcString&);
        ~CAdUiNOFSVolumeDescriptor(){};

        bool ValidateFilename( const AcString*,
                               bool wildcard_ok = false ) const override;
        bool ValidateSegment( const AcString*,
                              bool wildcard_ok = false ) const override;

};

#pragma pack (pop)

