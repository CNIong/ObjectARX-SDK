/////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2000 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary to Autodesk,
// Inc., and considered a trade secret as defined in section 499C of the
// penal code of the State of California.  Use of this information by anyone
// other than authorized employees of Autodesk, Inc. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
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
// DESCRIPTION:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ANavArray_h
#define _ANavArray_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "afxtempl.h"       // MFC array template classes

/////////////////////////////////////////////////////////////////////////////
// File Navigation Array

template <class T>
class CNavArray : public CTypedPtrArray<CObArray, T*> {
public:
                CNavArray ();
virtual         ~CNavArray ();

// Data management
protected:
virtual T       *NewData ();
public:
        T       *AddData ();
        int     GetCount ();
        T       *GetData (int index);
        BOOL    IsIndexValid (int index);
        void    RemoveData (int index);
        void    RemoveAllData ();
};

/////////////////////////////////////////////////////////////////////////////
// File Navigation Array - implementation

template <class T>
CNavArray<T>::CNavArray () :
    CTypedPtrArray<CObArray, T*>()
{
}

template <class T>
CNavArray<T>::~CNavArray ()
{
    RemoveAllData();
}

//----------------
// Data management

template <class T>
T    *CNavArray<T>::AddData ()
{
    T    *d = NewData();

    ASSERT(d != NULL);
    if (d != NULL)
        Add(d);
    return d;
}

template <class T>
int  CNavArray<T>::GetCount ()
{
    return (GetUpperBound() + 1);
}

template <class T>
T    *CNavArray<T>::GetData (int index)
{
    T    *d = NULL;

    if (IsIndexValid(index))
        d = GetAt(index);
    return d;
}

template <class T>
BOOL CNavArray<T>::IsIndexValid (int index)
{
    return ((index >= 0) && (index <= GetUpperBound()));
}

template <class T>
T    *CNavArray<T>::NewData ()
{
    return new T;
}

template <class T>
void CNavArray<T>::RemoveData (int index)
{
    T    *d;

    if (IsIndexValid(index)) {
        d = GetAt(index);
        RemoveAt(index);
        delete d;
    }
}

template <class T>
void CNavArray<T>::RemoveAllData ()
{
    int  i, n = GetCount();
    T    *d;

    for (i = 0; i < n; i++) {
        d = GetAt(i);
        delete d;
    }
    RemoveAll();
    FreeExtra();
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
