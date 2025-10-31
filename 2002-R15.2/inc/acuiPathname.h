//
//  (C) Copyright 1995-1998 by Autodesk, Inc.  All rights reserved.
//
//  The information contained herein is confidential, proprietary to 
//  Autodesk, Inc., and considered a trade secret as defined in 
//  section 499C of the penal code of the State of California.  
//  Use of this information by anyone other than authorized employees 
//  of Autodesk, Inc. is granted only under a written non-disclosure 
//  agreement, expressly prescribing the scope and manner of such use.
//

#ifndef _acuiPathname_h
#define _acuiPathname_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//Forward declarations.
class AFILE;

class ACUI_PORT CAcUiPathname : public CAdUiPathname {

public:

// methods
        // constructor (initializes private data)
        CAcUiPathname(void);
        CAcUiPathname(const CAcUiPathname&);

        // destructor (frees allocated storage)
        ~CAcUiPathname(void);

        // parse a string, validate the format and fill in the data
        //  This routine actually calls ParseRelative with the
        //  current document path (if any) or the current application
        //  path as the relative path.
virtual PathErr Parse( LPCTSTR, const BOOL wildcard_ok = FALSE );

        // check status for the path
        //  the returned values are defined in astat.h
        int Status(void);

        // takes a path and tries to open it.  Return TRUE if
        //  the open succeeded, FALSE otherwise.  Note that
        //  these routines set the current directory to the
        //  appropriate place before opening, and reset it
        //  afterward.
        BOOL Open(AFILE** fdp, const char *openmode);

        // create an assignment operator that does the right thing.
        const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc);
        const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc);
        
protected:
        // the guts of the assignment operator
virtual void AssignCopy( const CAcUiPathname& );
    
};

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc)
{
    AssignCopy( pathSrc);

    return *this;
}

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc)
{
    AssignCopy( *pathSrc);

    return *this;
}

#endif // _acuiPathname_h
