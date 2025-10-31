///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECPROPERTYSETITERATOR_H
#define FORMATCODECPROPERTYSETITERATOR_H

namespace Atil
{
/// <summary>
/// This class is an iterator for properties used to ferry properties to and
/// from <c>ImageFormatCodec</c> instances.
/// </summary>
///
class FormatCodecPropertySetIterator 
{
public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecPropertySetIterator ();

    /// <summary>
    /// This method will start the iteration.
    /// </summary>
    ///
    virtual void start ();

    /// <summary>
    /// This method will step (increase by one) the position in the iteration.
    /// </summary>
    ///
    virtual void step ();

    /// <summary>
    /// This queries the state of the iterator.
    /// </summary>
    ///
    /// <returns>
    /// This method returns true if the end of the list has been reached.
    /// </returns>
    ///
    virtual bool endOfList ();

    /// <summary>
    /// This queries the number of properties in the iterator.
    /// </summary>
    ///
    /// <returns>
    /// This method returns an the integer number of properties in the list.
    /// </returns>
    ///
    virtual int numProperties ();

    /// <summary>
    /// This method opens the property at the current position in the list.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the property at the current position in the list.
    /// </returns>
    ///
    /// <remarks>
    /// The property should be return using <c>closeProperty</c> and should not
    /// be deleted by the caller.
    /// </remarks>
    ///
    virtual FormatCodecPropertyInterface* openProperty ();

    /// <summary>
    /// This method opens a specific property if it is in the list.
    /// </summary>
    ///
    /// <param name="identifier">
    /// The id of the property that should be located and opened
    /// <see cref="FormatCodecPropertyInterface"/>.
    /// </param>
    ///
    /// <returns>
    /// This method returns the property at the current position in the list.
    /// </returns>
    ///
    /// <remarks>
    /// The property should be return using <c>closeProperty</c> and should not
    /// be deleted by the caller.
    /// </remarks>
    ///
    virtual FormatCodecPropertyInterface* openProperty (FormatCodecPropertyInterface::PropertyIdentifier identifier);

    /// <summary>
    /// This method should be used to return the pointer of the currently open property.
    /// </summary>
    ///
    /// <remarks>
    /// The property should be return using <c>closeProperty</c> and should not
    /// be deleted by the caller.
    /// </remarks>
    ///
    virtual void closeProperty ();

    
protected:
    /// <summary>
    /// (Protected) The copy constructor will initialize the new instance to the argument.
    /// </summary>
    ///
    /// <param name="iter">
    /// A const reference to an <c>FormatCodecPropertySetIterator</c> instance to copy.
    /// </param>
    ///
    FormatCodecPropertySetIterator (const FormatCodecPropertySetIterator& iter);

    /// <summary>
    /// (Protected) An empty constructor.
    /// </summary>
    ///
    FormatCodecPropertySetIterator ();

    /// <summary>
    /// (Protected) An empty constructor with preallocation.
    /// </summary>
    ///
    /// <param name="nNumToAlloc">
    /// The number of properties to pre-allocate to hold.
    /// </param>
    ///
    FormatCodecPropertySetIterator (int nNumToAlloc);
    
    /// <summary>
    /// (Protected) This method will place the property as the specified index in the list.
    /// </summary>
    ///
    /// <param name="nIndex">
    /// The index to place the property into.
    /// </param>
    ///
    /// <param name="pProperty">
    /// The <c>FormatCodecPropertyInterface</c> to be added to the list.
    /// </param>
    ///
    /// <remarks>
    /// The property will be "cloned" into the list creating a new instance
    /// so the passed in pointer is not held by this and should be cleaned by
    /// the caller/allocator.
    /// </remarks>
    ///
    void setProperty (int nIndex, const FormatCodecPropertyInterface* pProperty);

    /// <summary>
    /// (Protected) This method will append the property as the end of the list allocating 
    /// space for it if necessary.
    /// </summary>
    ///
    /// <param name="pProperty">
    /// The <c>FormatCodecPropertyInterface</c> to be added to the list.
    /// </param>
    ///
    /// <remarks>
    /// The property will be "cloned" into the list creating a new instance
    /// so the passed in pointer is not held by this and should be cleaned by
    /// the caller/allocator.
    /// </remarks>
    ///
    void appendProperty (const FormatCodecPropertyInterface* pProperty);

    /// <summary>
    /// (Protected) The array of properties held by the iterator.
    /// </summary>
    ///
    /// <remarks>
    /// The properties in the list will be cleaned by the destructor of the iterator.
    /// </remarks>
    ///
    FormatCodecPropertyInterface** mppProperties;

    /// <summary>
    /// (Protected) The number of properties in the iterator.
    /// </summary>
    ///
    int mnNumProperties;    

    /// <summary>
    /// (Protected) The size of the allocated array in the iterator.
    /// </summary>
    ///
    int mnArraySize;

    /// <summary>
    /// (Protected) The current index active in the iterator.
    /// </summary>
    ///
    int mnIndex;

private:
    FormatCodecPropertySetIterator& operator= (const FormatCodecPropertySetIterator& from); // not implemented
};

} // end of namespace Atil

#endif
