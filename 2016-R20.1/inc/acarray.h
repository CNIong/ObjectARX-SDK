#ifndef AC_ACARRAY_H
#define AC_ACARRAY_H
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

#include <memory.h>
#include <stdlib.h>
#include <algorithm>
#include <type_traits>
#include "adesk.h"
#include "assert.h"

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

// The legacy name AllocatorSelector may go away in the future
#define AllocatorSelector AcArrayItemCopierSelector

// If the contained class T can be safely copied by the memcpy operator you
// should use the AcArrayMemCopyReallocator template with the array.
// If the class you intend to contain requires the use of operator=() for
// the copying during reallocation you should use AcArrayObjectCopyReallocator
//
// The default copy behaviour is based on the is_trivial trait of the type T
//
// If bMove is true, then the old data is not needed and it's safe to move it
// (using C++ 11 move semantics) instead of copying it, for performance.
//
// If bSameBuffer is true, then bMove must be true also and we are moving elements
// left or right in a buffer, and so we have to do that in a safe way without
// clobbering source data.

template <class T> class AcArrayMemCopyReallocator
{
public:
    static void copyItems(T* pDest, size_t nBufLen, const T * pSource, size_t nCount,
                          bool bMove, bool bSameBuffer)
    {
        bMove;   // avoid unreferenced param warning
        AC_ARRAY_ASSERT(nCount <= nBufLen);
        AC_ARRAY_ASSERT(nCount >= 0);
        AC_ARRAY_ASSERT(nCount < 0x40000000);   // 1G sanity check
        AC_ARRAY_ASSERT(pSource > pDest || (pDest >= pSource + nCount)); // no overlap
        AC_ARRAY_ASSERT(bMove || !bSameBuffer);
        if (nCount > 0) {
            if (bSameBuffer)
                memmove_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
            else
                memcpy_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
        }
    }
};


template <class T> class AcArrayObjectCopyReallocator
{
public:
    static void copyItems(T* pDest, size_t nBufLen, const T * pSource, size_t nCount,
                          bool bMove, bool bSameBuffer)
    {
        bMove;   // avoid unreferenced param warning. this one will be used eventually
        nBufLen; // avoid unreferenced param warning
        bSameBuffer;
        AC_ARRAY_ASSERT(nCount <= nBufLen);
        AC_ARRAY_ASSERT(nCount >= 0);
        AC_ARRAY_ASSERT(nCount < 0x40000000);   // 1G sanity check
        AC_ARRAY_ASSERT(pSource > pDest || (pDest >= pSource + nCount)); // no overlap
        AC_ARRAY_ASSERT(bMove || !bSameBuffer);
        while (nCount--)
        {
            *pDest = *pSource;
            pDest++;
            pSource++;
        }
    }
};

template<typename T, bool>
struct AcArrayItemCopierSelector;

template<typename T>
struct AcArrayItemCopierSelector<T, false>
{
    typedef AcArrayObjectCopyReallocator<T> allocator;
};

template<typename T>
struct AcArrayItemCopierSelector<T, true>
{
    typedef AcArrayMemCopyReallocator<T> allocator;
};

template <typename T, typename R = typename AcArrayItemCopierSelector<T, std::is_trivial<T>::value>::allocator  > class AcArray
{

public:
    AcArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcArray(const AcArray<T,R>&);
    AcArray(AcArray<T,R>&&);
    ~AcArray();

    typedef R Allocator;
    // This enum is useful for validating that an AcArray uses the efficient copy method.
    // E.g.: static_assert(AcArray<MyType>::eUsesMemCopy, "AcArray<MyType> uses slow copy!");
    enum {eUsesMemCopy = std::is_same<R, AcArrayMemCopyReallocator<T>>::value};

    // Copy operator.
    //
    AcArray<T,R>&         operator =  (const AcArray<T,R>&);
    AcArray<T,R>&         operator =  (AcArray<T,R>&&);
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

    // begin() and end() methods return iterators which allow things like
    // range based for loops, std::sort, std::for_each etc to use AcArrays
    // E.g.: for (const auto & elt : arr) sum += elt; 
    //
    T * begin() { return mpArray; }
    T * end() { return mpArray + mLogicalLen; }

    const T * begin() const { return mpArray; }
    const T * end() const { return mpArray + mLogicalLen; }

protected:
    T*                  mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    bool                allocPhysBuf();
    bool                deletePhysBuf(T *pBuf, size_t nCount);
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

template < class T, class R >
AcArray< T, R > ::AcArray(int physicalLength, int growLength)
: mpArray(nullptr),
  mPhysicalLen(physicalLength),
  mLogicalLen(0),
  mGrowLen(growLength)
{
    // Replacing is_pod with is_trivial. is_trivial should be a superset of is_pod
    static_assert(std::is_trivial<T>::value || !std::is_pod<T>::value, "is_pod but not is_trivial?");
    AC_ARRAY_ASSERT(mGrowLen > 0);
    AC_ARRAY_ASSERT(mPhysicalLen >= 0);
    if (mPhysicalLen > 0)
        this->allocPhysBuf();
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
: mpArray(nullptr),
  mPhysicalLen(src.mPhysicalLen),
  mLogicalLen(src.mLogicalLen),
  mGrowLen(src.mGrowLen)
{
    AC_ARRAY_ASSERT(mPhysicalLen >= mLogicalLen);
    if (mLogicalLen <= 0) {
        AC_ARRAY_ASSERT(mLogicalLen == 0);
        mPhysicalLen = 0;       // we don't need a buffer yet
    }
    if (mPhysicalLen <= 0) {
        AC_ARRAY_ASSERT(mPhysicalLen == 0);
        AC_ARRAY_ASSERT(mLogicalLen == 0);
    }
    else {
        AC_ARRAY_ASSERT(mLogicalLen > 0);
        if (this->allocPhysBuf())
            R::copyItems(mpArray, mPhysicalLen, src.mpArray, mLogicalLen,
                         /*bMove*/false, /*bSameBuffer*/false);
    }
}

template <class T, class R>
AcArray<T,R>::AcArray(AcArray<T,R>&& src)
: mpArray(src.mpArray),
  mPhysicalLen(src.mPhysicalLen),
  mLogicalLen(src.mLogicalLen),
  mGrowLen(src.mGrowLen)
{
    src.mpArray = nullptr;
    src.mPhysicalLen = 0;
    src.mLogicalLen = 0;
    src.mGrowLen = 8;
}

template <class T, class R>
AcArray<T,R>::~AcArray()
{
    this->deletePhysBuf(mpArray, mPhysicalLen);
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
        if (src.mLogicalLen <= 0) {
            AC_ARRAY_ASSERT(src.mLogicalLen == 0);
            mLogicalLen = 0;    // leave physical buffer as is
        }
        else {
            if (mPhysicalLen < src.mLogicalLen) {
                if (mpArray != nullptr) {
                    deletePhysBuf(mpArray, mPhysicalLen);
                    mpArray = nullptr;
                }
                mPhysicalLen = src.mLogicalLen;
                if (!this->allocPhysBuf())
                    return *this;
            }
            mLogicalLen = src.mLogicalLen;
            AC_ARRAY_ASSERT(mLogicalLen > 0);
            AC_ARRAY_ASSERT(mPhysicalLen >= mLogicalLen);
            R::copyItems(mpArray, mPhysicalLen, src.mpArray, mLogicalLen,
                         /*bMove*/false, /*bSameBuffer*/false);
        }
    }
    return *this;
}

template <class T, class R> AcArray<T,R>&
AcArray<T,R>::operator = (AcArray<T,R>&& src)
{
    if (this != &src) {
        mPhysicalLen = src.mPhysicalLen;
        mpArray = src.mpArray;
        mLogicalLen = src.mLogicalLen;
        mGrowLen = src.mGrowLen;

        src.mpArray = nullptr;
        src.mPhysicalLen = 0;
        src.mLogicalLen = 0;
        src.mGrowLen = 8;
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
// this array will increase by the logical length of the `otherArray'.
// Special case: appending to self, where otherArray == this. That works,
// because otherArray.mapArray gets updated by setPhysicalLength.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::append(const AcArray<T,R>& otherArray)
{
    const int otherLen = otherArray.length();
    if (otherLen == 0)
        return *this;

    const int newLen = mLogicalLen + otherLen;
    if (newLen > mPhysicalLen)  // grow the buffer
        setPhysicalLength(mLogicalLen + std::max<int>(otherLen, mGrowLen));

    R::copyItems(mpArray + mLogicalLen, (mPhysicalLen-mLogicalLen), otherArray.mpArray, otherLen,
                 /*bMove*/false, /*bSameBuffer*/false);
    
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
    AC_ARRAY_ASSERT(index >= 0 && index <= mLogicalLen);
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    if (index < 0 || index > mLogicalLen)
        return *this;
    const T tmp(value); // make a copy in case value is coming from this array!

    if (mLogicalLen >= mPhysicalLen) {
        AC_ARRAY_ASSERT(mLogicalLen == mPhysicalLen);
        const int growth = (mLogicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ?
            mLogicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);
        setPhysicalLength(mLogicalLen + std::max<int>(growth, mGrowLen));
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
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    AC_ARRAY_ASSERT(!isEmpty());
    if (isEmpty() || !isValid(index))
        return *this;

    // Shift array elements to the left if needed.
    //
    if (index < mLogicalLen - 1) {
        R::copyItems(mpArray + index, mPhysicalLen - index,
                     mpArray + index + 1, mLogicalLen - 1 - index,
                     /*bMove*/true, /*bSameBuffer*/true);
    }

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
        mLogicalLen = startIndex;       // deleting to the right end
        return *this;
    }

    // We didn't delete the right end, so shift remaining elements down
    //
    const int kNumToRemove = endIndex + 1 - startIndex;
    const int kNumToShift = mLogicalLen - 1 - endIndex;
    AC_ARRAY_ASSERT(kNumToShift >= 1);
    R::copyItems(mpArray + startIndex, mPhysicalLen - startIndex,
                 mpArray + endIndex + 1, kNumToShift,
                 /*bMove*/true, /*bSameBuffer*/true);
    mLogicalLen -= kNumToRemove;
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
    AC_ARRAY_ASSERT(start >= 0);
    if (start < 0)
        return -1;
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
    if (n < 0)
        n = 0;  // avoid going negative
    AC_ARRAY_ASSERT(n < 0x40000000);    // 1G sanity check
    if (n > mPhysicalLen) {

        const int growth = (mPhysicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ?
            mPhysicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);

        int minSize = mPhysicalLen + std::max<int>(growth, mGrowLen);
        if ( n > minSize)
            minSize = n;
        setPhysicalLength(minSize);
    }
    mLogicalLen = n;
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    return *this;
}

template <class T, class R> bool
AcArray<T,R>::allocPhysBuf()
{
    AC_ARRAY_ASSERT(mPhysicalLen > 0);
    AC_ARRAY_ASSERT(mpArray == nullptr);
#ifdef GE_LOCATED_NEW
    mpArray = GENEWLOCVEC(T, mPhysicalLen, this) ();
#else
    mpArray = new T[mPhysicalLen];
#endif
    AC_ARRAY_ASSERT(mpArray != nullptr);
    if (mpArray == nullptr) {   // shouldn't happen
        mPhysicalLen = 0;
        mLogicalLen = 0;
        return false;
    }
    return true;
}
template <class T, class R> bool
AcArray<T,R>::deletePhysBuf(T *pBuf, size_t nCount)
{
    nCount;     // avoid unused arg warning
    if (pBuf == nullptr) {
        AC_ARRAY_ASSERT(nCount == 0);
    }
    else {
        AC_ARRAY_ASSERT(nCount > 0);
        delete[] pBuf;
    }
    return true;
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
    AC_ARRAY_ASSERT(mPhysicalLen >= mLogicalLen);
    AC_ARRAY_ASSERT((mPhysicalLen == 0) == (mpArray == nullptr));
    AC_ARRAY_ASSERT(n >= 0);
    AC_ARRAY_ASSERT(n < 0x40000000);    // 1G sanity check
    if (n == mPhysicalLen || n < 0)
        return *this;   // nothing to do

    T* pOldArray = mpArray;
    const size_t nOldLen = mPhysicalLen;

    mPhysicalLen = n;   // could be growing or shrinking
    mpArray = nullptr;

    if (mPhysicalLen < mLogicalLen)
        mLogicalLen = mPhysicalLen;     // shrinking the array

    if (mPhysicalLen != 0)
        if (this->allocPhysBuf())
            R::copyItems(mpArray, mPhysicalLen, pOldArray, mLogicalLen,
                         /*bMove*/true, /*bSameBuffer*/false);   // move items (if any) to new buf

    deletePhysBuf(pOldArray, nOldLen);  // Blow away the old array buffer.

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
        const T tmp = mpArray[i];
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

    const T tmp = mpArray[i1];
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
