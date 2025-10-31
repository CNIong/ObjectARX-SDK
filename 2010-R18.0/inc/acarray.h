#ifndef AC_ACARRAY_H
#define AC_ACARRAY_H
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// DESCRIPTION:
//
// This file contains the definition for a dynamic array, called
// AcArray<T,R>, of objects of type "T".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "T" in the
// usual manner.  For example declaring "T myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcArray<T,R>, you need to understand
// a couple of simple, yet key, concepts:
//
//     1) The logical length of the array.
//            - How many entries have been placed into the array,
//              initially always zero.
//     2) The physical length of the array.
//            - How many entries the array will hold before it
//              automatically "grows" larger.
//     3) The grow length of the array.
//            - How much the array will grow when required.
//
// The physical length of the array is the actual length of the
// physically allocated, but perhaps not fully used, array.
// As a point of clarification, the size in bytes of the array
// buffer for an array called `myArray' would be:
//
//     sizeOf(T) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of T have been placed into the array
// with, for example, append() or insertAt().  Many member-functions
// are only valid for indices that are greater than or equal to
// zero AND less than length().  For example, indexing into the
// array with the operator[] is only valid for indices in this range.
//
// You can explicitly set the logical length() to any value and
// if the physical length is not large enough the array will grow to
// that length.  Note that if the logical length is explicitly reset
// to a larger value, then all the entries from the old length up
// to the new length may contain garbage values, therefor they must be
// initialized explicitly.
//
// The logical length is always less than or equal to the physical
// length.  NOTE that the array ALWAYS starts out empty, i.e., the
// length() always starts at zero regardless of the initial physical
// length.
//
// If you add an element to the array causing the logical length
// to become greater than the physical length of the array then
// additional space is allocated to increase the physical length.
// The amount of the increase is the larger of: the current grow
// length, or double the current logical length if the space used 
// is less than 64k bytes, or the number items that will grow
// the total space by an additional 64k bytes.
//
// The grow length must be a positive number, that is, zero is an illegal
// grow length.
//

#pragma warning (disable: 4786)

#include <memory.h>     
#include <stdlib.h>
#include "adesk.h"
#include "assert.h"
#include <type_traits>

//Fix for defect 672405
#ifdef ASSERT
#define AC_ARRAY_ASSERT ASSERT
#elif defined assert
#define AC_ARRAY_ASSERT assert
#elif defined _ASSERTE
#define AC_ARRAY_ASSERT _ASSERTE
#else
#define AC_ARRAY_ASSERT(T)
#endif

#pragma pack (push, 8)

#define ACARRAY_GROWTH_THRESHOLD 0x10000

// If the contained class can be safely copied by the memcpy operator you
// should use the AcArrayMemCopyReallocator template with the array.
// If the class you intend to contain requires the use of operator=() for
// the copying during reallocation you should use AcArrayObjectCopyReallocator
//
// The default behaviour is to use the AcArrayMemCopyReallocator
//

template <class T> class AcArrayMemCopyReallocator
{
public:
    static void reallocateArray(T* pCopy, const T * pSource, int nCount)
    {
        AC_ARRAY_ASSERT(nCount >= 0);
        AC_ARRAY_ASSERT(nCount < 0x40000000);  // 1G sanity check
        if (nCount > 0) 
        {
            memcpy(pCopy, pSource, nCount * sizeof(T));
        }
    }
};


template <class T> class AcArrayObjectCopyReallocator
{
public:
    static void reallocateArray(T* pCopy, const T * pSource, int nCount)
    {
        AC_ARRAY_ASSERT(nCount >= 0);
        AC_ARRAY_ASSERT(nCount < 0x40000000);  // 1G sanity check
        while (nCount--)
        {
            *pCopy = *pSource;
            pCopy++;
            pSource++;
        }
    }
};

template<typename T, bool>
struct AllocatorSelector;

template<typename T>
struct AllocatorSelector<T, false>
{
    typedef AcArrayObjectCopyReallocator<T> allocator;
};

template<typename T>
struct AllocatorSelector<T, true>
{
    typedef AcArrayMemCopyReallocator<T> allocator;
};


template <typename T, typename R = typename AllocatorSelector<T, std::tr1::is_pod<T>::value>::allocator  > class AcArray
{
public:
    AcArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcArray(const AcArray<T,R>&);
    ~AcArray();

    // Copy operator.
    //
    AcArray<T,R>&         operator =  (const AcArray<T,R>&);
    bool                operator == (const AcArray<T,R>&) const;

    // Indexing into the array.
    //
    T&                  operator [] (int);
    const T &           operator [] (int) const;

    // More access to array-elements.
    //
    const T &             at          (int index) const;
          T &             at          (int index);
    AcArray<T,R>&         setAt       (int index, const T& value);
    AcArray<T,R>&         setAll      (const T& value);
    T&                  first       ();
    const T &           first       () const;
    T&                  last        ();
    const T &           last        () const;

    // Adding array-elements.
    //
    int                 append      (const T& value);
    AcArray<T,R>&         append      (const AcArray<T,R>& array);
    AcArray<T,R>&         insertAt    (int index, const T& value);

    // Removing array-elements.
    //
    AcArray<T,R>&         removeAt    (int index);
    bool                  remove      (const T& value, int start = 0);
    AcArray<T,R>&         removeFirst ();
    AcArray<T,R>&         removeLast  ();
    AcArray<T,R>&         removeAll   ();
    AcArray<T,R>&         removeSubArray (int startIndex, int endIndex);

    // Query about array-elements.
    //
    bool                contains    (const T& value, int start = 0) const;
    bool                find        (const T& value, int& foundAt,
                                     int start = 0) const;
    int                 find        (const T& value) const;
    int                 findFrom    (const T& value, int start) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    bool                isEmpty     () const;
    int                 logicalLength() const;
    AcArray<T,R>&         setLogicalLength(int);
    int                 physicalLength() const;
    AcArray<T,R>&         setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcArray<T,R>&         setGrowLength(int);

    // Utility.
    //
    AcArray<T,R>&         reverse     ();
    AcArray<T,R>&         swap        (int i1, int i2);

    // Treat as simple array of T.
    //
    const T*            asArrayPtr  () const;
    T*                  asArrayPtr  ();

protected:
    T*                  mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    bool                isValid     (int) const;
};

#pragma pack (pop)

#ifdef GE_LOCATED_NEW
#include "gegblnew.h"
#endif

#pragma pack (push, 8)

// Inline methods.

template <class T, class R> inline bool
AcArray<T,R>::contains(const T& value, int start) const
{ return this->findFrom(value, start) != -1; }

template <class T, class R> inline int
AcArray<T,R>::length() const
{ return mLogicalLen; }

template <class T, class R> inline bool
AcArray<T,R>::isEmpty() const
{ return mLogicalLen == 0; }

template <class T, class R> inline int
AcArray<T,R>::logicalLength() const
{ return mLogicalLen; }

template <class T, class R> inline int
AcArray<T,R>::physicalLength() const
{ return mPhysicalLen; }

template <class T, class R> inline int
AcArray<T,R>::growLength() const
{ return mGrowLen; }

template <class T, class R> inline const T*
AcArray<T,R>::asArrayPtr() const
{ return mpArray; }

template <class T, class R> inline T*
AcArray<T,R>::asArrayPtr()
{ return mpArray; }

template <class T, class R> inline bool
AcArray<T,R>::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

template <class T, class R> inline T&
AcArray<T,R>::operator [] (int i)
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline const T&
AcArray<T,R>::operator [] (int i) const
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline T&
AcArray<T,R>::at(int i)
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline const T&
AcArray<T,R>::at(int i) const
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::setAt(int i, const T& value)
{ AC_ARRAY_ASSERT(this->isValid(i)); mpArray[i] = value; return *this; }

template <class T, class R> inline T&
AcArray<T,R>::first()
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[0]; }

template <class T, class R> inline const T&
AcArray<T,R>::first() const
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[0]; }

template <class T, class R> inline T&
AcArray<T,R>::last()
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[mLogicalLen-1]; }

template <class T, class R> inline const T&
AcArray<T,R>::last() const
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[mLogicalLen-1]; }

template <class T, class R> inline int
AcArray<T,R>::append(const T& value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeFirst()
{ AC_ARRAY_ASSERT(!isEmpty()); return removeAt(0); }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeLast()
{ 
    AC_ARRAY_ASSERT(!isEmpty());
    if (!isEmpty())
        mLogicalLen--;
    return *this;
}

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeAll()
{ this->setLogicalLength(0); return *this; }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::setGrowLength(int glen)
{ AC_ARRAY_ASSERT(glen > 0); mGrowLen = glen; return *this; }


#define lowMemBail() AC_ARRAY_ASSERT(false)

template < class T, class R >
AcArray< T, R > ::AcArray(int physicalLength, int growLength)
: mpArray(NULL),
  mPhysicalLen(physicalLength),
  mLogicalLen(0),
  mGrowLen(growLength)
{
    AC_ARRAY_ASSERT(mGrowLen > 0);
    AC_ARRAY_ASSERT(mPhysicalLen >= 0);
    if (mPhysicalLen > 0) {
#ifdef GE_LOCATED_NEW
        mpArray = GENEWLOCVEC(T, mPhysicalLen, this) ();
#else
        mpArray = new T[mPhysicalLen];
#endif
        if (mpArray == NULL) {
            mPhysicalLen = 0;
            lowMemBail();
        }
    }
}

// This is the usual copy constructor with the caveat that,
// if the system can not allocate enough memory to satisfy the
// request then it is assumed that the entire system is in a
// dangerously low memory situation, and there is no alternative
// but to have the system gracefully abort (i.e., prompting the
// users to save files, and/or free up more memory, or what-have-you).
//
template <class T, class R>
AcArray<T,R>::AcArray(const AcArray<T,R>& src)
: mpArray(NULL),
  mPhysicalLen(src.mPhysicalLen),
  mLogicalLen(src.mLogicalLen),
  mGrowLen(src.mGrowLen)
{
    if (mPhysicalLen > 0) {
#ifdef GE_LOCATED_NEW
        mpArray = GENEWLOCVEC(T, mPhysicalLen, this) ();
#else
        mpArray = new T[mPhysicalLen];
#endif
        if (mpArray == NULL) {
            lowMemBail();
            mPhysicalLen = 0;
            mLogicalLen = 0;
        }
    }

    R::reallocateArray(mpArray, src.mpArray, mLogicalLen);
}

template <class T, class R>
AcArray<T,R>::~AcArray()
{
    if (mpArray != NULL)
        delete[] mpArray;
}

// The assignment operator.  The assignment operator copies
// the data from the source array to this array.  If the
// source array contains more elements that this array has
// space to store, then this array is grown to meet the demand.
// Otherwise, the physical length of this array does not change.
// After this operation is completed the logical lengths of the
// two arrays will be equal.  The grow length of this array is
// not affected by this operation.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::operator = (const AcArray<T,R>& src)
{
    if (this != &src) {
        if (mPhysicalLen < src.mLogicalLen) {
            if (mpArray != NULL)
                delete[] mpArray;
            mPhysicalLen = src.mLogicalLen;
            // mPhysicalLen will never be zero...
#ifdef GE_LOCATED_NEW
        mpArray = GENEWLOCVEC(T, mPhysicalLen, this) ();
#else
            mpArray = new T[mPhysicalLen];
#endif
            if (mpArray == NULL) { // ...so this only happens if failure.
                lowMemBail();
                mPhysicalLen = 0;
                mLogicalLen = 0;
                return *this;
            }
        }
        mLogicalLen = src.mLogicalLen;
        R::reallocateArray(mpArray, src.mpArray, mLogicalLen);
    }
    return *this;
}


// The equal to operator.  The equal to operator compares
// the data in two arrays.  If the logical length of the
// two arrays are the same and the corresponding entries of
// the two arrays are equal, true is returned. Otherwise,
// false is returned.
//
template <class T, class R> bool
AcArray<T,R>::operator == (const AcArray<T,R>& cpr) const
{
    if (mLogicalLen == cpr.mLogicalLen) {
        for (int i = 0; i < mLogicalLen; i++)
            if (mpArray[i] != cpr.mpArray[i])
                return false;
        return true;
    }
    return false;
}

// Sets all the elements within the logical-length of the array,
// (that is, elements 0..length()-1), to `value'.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setAll(const T& value)
{
    for (int i = 0; i < mLogicalLen; i++) {
        mpArray[i] = value;
    }
    return *this;
}

// Appends the `otherArray' to the end of this array.  The logical length of
// this array will increase by the length of the `otherArray'.  If the
// physical length is not long enough it will increase by the amount
// necessary to fit the newly added elements (with the usual caveat about
// insufficient memory).
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::append(const AcArray<T,R>& otherArray)
{
    int otherLen = otherArray.length();
    if (otherLen == 0) {
        return *this;
    }
    int newLen = mLogicalLen + otherLen;
    if (newLen > mPhysicalLen) {
        setPhysicalLength(newLen);
    }

    R::reallocateArray(mpArray + mLogicalLen, otherArray.mpArray, otherLen);
    
    mLogicalLen = newLen;
    return *this;
}

// Inserts `value' at `index'.  The value formerly at `index'
// gets moved to `index+1',  `index+1 gets moved to `index+2' and so on.
// Note that insertAt(length(), value) is equivalent to append(value).
// The logical length of the array will increase by one.  If the physical
// length is not long enough it will increase by the grow length (with the
// usual caveat about insufficient memory).
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::insertAt(int index, const T& value)
{
    T  tmp(value);
    AC_ARRAY_ASSERT(index >= 0 && index <= mLogicalLen);

    if (mLogicalLen >= mPhysicalLen) {
        int growth = (mLogicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ?
            mLogicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);
        setPhysicalLength(mLogicalLen + __max(growth, mGrowLen));
    }

    if (index != mLogicalLen) {
        AC_ARRAY_ASSERT(mLogicalLen >= 0);
        T* p = mpArray + mLogicalLen;
        T* pStop = mpArray + index;
        do {
            *p = *(p-1);
        } while (--p != pStop);
    }
    mpArray[index] = tmp;
    mLogicalLen++;
    return *this;
}

// Removes the element at `index'.  The logical length will
// decrease by one.  `index' MUST BE within bounds.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::removeAt(int index)
{
    AC_ARRAY_ASSERT(isValid(index));

    // Shift array elements to the left if needed.
    //
    if (index < mLogicalLen - 1) {
        T* p = mpArray + index;
        T* pStop = mpArray + mLogicalLen - 1;
        do {
            *p = *(p+1);
        } while (++p != pStop);
    }

    AC_ARRAY_ASSERT(!isEmpty());
    if (!isEmpty())
        mLogicalLen--;
    return *this;
}

// Removes all elements starting with 'startIndex' and ending with 'endIndex'
// The logical length will decrease by number of removed elements.
// Both `startIndex' and 'endIndex' MUST BE within bounds.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::removeSubArray(int startIndex, int endIndex)
{
    AC_ARRAY_ASSERT(isValid(startIndex));
    AC_ARRAY_ASSERT(startIndex <= endIndex);

    if ( endIndex >= mLogicalLen - 1) {
        mLogicalLen = startIndex;
        return *this;
    }

    // Shift array elements to the left if needed.
    //
    if (startIndex < mLogicalLen - 1) {
        T* p = mpArray + startIndex;
        T* q = mpArray + endIndex + 1;
        T* pStop = mpArray + mLogicalLen;
        for (; q < pStop; p++, q++ ) {
            *p = *q;
        }
    }
    mLogicalLen -= endIndex - startIndex + 1;
    return *this;
}

// Returns true if and only if the array contains `value' from
// index `start' onwards.  Returns, in `index', the first location
// that contains `value'.  The search begins at position `start'.
// `start' is supplied with a default value of `0', i.e., the
// beginning of the array.
//
template <class T, class R> bool
AcArray<T,R>::find(const T& value, int& index, int start) const
{
    const int nFoundAt = this->findFrom(value, start);
    if (nFoundAt == -1)
        return false;
    index = nFoundAt;
    return true;
}

template <class T, class R> int
AcArray<T,R>::find(const T& value) const
{
    return this->findFrom(value, 0);   // search from the beginning
}

template <class T, class R> int
AcArray<T,R>::findFrom(const T& value, int start) const
{
    for (int i = start; i < this->mLogicalLen; i++) {
        if (mpArray[i] == value)
            return i;
    }
    return -1;
}

// Allows you to set the logical length of the array.
// If you try to set the logical length to be greater than
// the physical length, then the array is grown to a
// reasonable size (thus increasing both the logical length
// AND the physical length).
// Also, the physical length will grow in growth length
// steps.
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setLogicalLength(int n)
{
    AC_ARRAY_ASSERT(n >= 0);
    if (n > mPhysicalLen) {

        int growth = (mPhysicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ?
            mPhysicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);

        int minSize = mPhysicalLen + __max(growth, mGrowLen);
        if ( n > minSize)
            minSize = n;
        setPhysicalLength(minSize);
    }
    mLogicalLen = (n >= 0) ? n : 0; // avoid going negative
    return *this;
}

// Allows you to set the physical length of the array.
// If you set the physical length to be less than
// the logical length, then the logical length is reset
// to match the new physical length.  A physical length
// of zero is valid.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setPhysicalLength(int n)
{
    AC_ARRAY_ASSERT(n >= 0);
    if (n == mPhysicalLen) return *this;
    T* pOldArray = mpArray;

    if (n == 0) { // Empty the array.
        mpArray = NULL;
        mPhysicalLen = 0;

    // Get the required amount of space.
    //
    } else {
#ifdef GE_LOCATED_NEW
        mpArray = GENEWLOCVEC(T, n, this) ();
#else
        mpArray = new T[n];
#endif
        if (mpArray == NULL) {
            lowMemBail();
            mPhysicalLen = 0;
        } else {

            R::reallocateArray(mpArray, pOldArray, ((n < mLogicalLen) ? n : mLogicalLen));
            mPhysicalLen = n;
        }
    }

    if (pOldArray != NULL) { // Blow away the old array buffer.
        delete[] pOldArray;
    }
    if (mPhysicalLen < mLogicalLen) {
        mLogicalLen = mPhysicalLen;
    }
    return *this;
}

// Reverses the order of the array.  That is if you have two
// arrays, `a' and `b', then if you assign `a = b' then call
// `a.reverse()' then a[0] == b[n], a[1] == b[n-1],... a[n] == b[0].
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::reverse()
{
    for (int i = 0; i < mLogicalLen/2; i++) {
        T tmp = mpArray[i];
        mpArray[i] = mpArray[mLogicalLen - 1 - i];
        mpArray[mLogicalLen - 1 - i] = tmp;
    }
    return *this;
}

// Swaps the elements in `i1' and `i2'.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::swap(int i1, int i2)
{
    AC_ARRAY_ASSERT(isValid(i1));
    AC_ARRAY_ASSERT(isValid(i2));

    if (i1 == i2) return *this;

    T tmp = mpArray[i1];
    mpArray[i1] = mpArray[i2];
    mpArray[i2] = tmp;
    return *this;
}

// Returns true if and only if `value' was removed from the array from
// position `start' onwards.  Only the first occurrence of `value'
// is removed.  Calling this function is equivalent to doing a "find(),
// then "removeAt()".
//
template <class T, class R> bool
AcArray<T,R>::remove(const T& value, int start)
{
    const int i = this->findFrom(value, start);
    if (i == -1)
        return false;
    this->removeAt(i);
    return true;
}

#include "acarrayhelper.h"

#pragma pack (pop)
#endif
