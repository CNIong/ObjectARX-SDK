//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef   ACDWGEXTRACTOR_H
#define   ACDWGEXTRACTOR_H
#include "AcString.h"
#include "rxvalue.h"
#include "dbid.h"
#include "pimplapi.h"

#if defined (ACDWGEXTRACTOR_API)
#define   ACDWGEXTRACTOR_PORT ADESK_EXPORT
#else
#define ACDWGEXTRACTOR_PORT
#endif

namespace AcDwgExtractor
{
    class ExtractorImp;

    class BeginExtractionEventArgs
    {
        friend class ExtractorImp;
        BeginExtractionEventArgs();
    public:
        /// <summary>
        /// Queues an object for property extraction. The properties extracted are subject to change.
        /// </summary>
        /// <param name="idObject">the object to be queued</param>
        /// <param name="idLayout">the layout associated with object</param>
        /// <returns>eOk if successful</returns>
        ACDWGEXTRACTOR_PORT Acad::ErrorStatus queueForExtraction(const AcDbObjectId& idObject, const AcDbObjectId& idLayout);
    };

    class EndExtractionEventArgs
    {
        friend class ExtractorImp;
        EndExtractionEventArgs();
    public:
        /// <summary>
        /// Adds a property to property database.
        /// </summary>
        /// <param name="idEntity">denotes the object that has this property</param>
        /// <param name="propertyCategory">denotes the category of the property</param>
        /// <param name="propertyName">denotes the name of the property</param>
        /// <param name="propertyValue">the property value</param>
        /// <param name="units">denotes the units of the property</param>
        /// <param name="hidden">indicates whether the property is intended for the user to see</param>
        /// <returns>eOk if successful</returns>
        ACDWGEXTRACTOR_PORT Acad::ErrorStatus addProperty(const AcDbObjectId& idEntity, const AcString& propertyCategory, const AcString& propertyName, const AcRxValue& propertyValue, const AcString& units = L"", bool hidden = false);
    };

    /// <summary>
    /// Reactor/Observer interface.
    /// </summary>
    class ADESK_NO_VTABLE ExtractorReactor
    {
    public:
        /// <summary>
        /// Called at the beginning of the extraction process. 
        /// Gives clients an opportunity to queue extra objects for property extraction.
        /// </summary>
        /// <param name="args">event arguments</param>
        virtual void beginExtraction(BeginExtractionEventArgs& args) = 0;
        /// <summary>
        /// Called at the end of the extraction process.
        /// Gives clients an opportunity to add extra properties to extraction results.
        /// </summary>
        /// <param name="args"></param>
        virtual void endExtraction(EndExtractionEventArgs& args) = 0;
    };

    /// <summary>
    /// A singleton who purpose is to act as event source for clients
    /// who want to observe the extraction process to add their own properties
    /// </summary>
    class Extractor : public Pimpl::ApiPart<void, ExtractorImp>
    {
    protected:
        using base_type = Pimpl::ApiPart<void, ExtractorImp>;
    public:
        Extractor(ExtractorImp* pImp);
        /// <summary>
        /// Adds a reactor/observer. Reactors that must be removed before they are destroyed.
        /// </summary>
        /// <param name="reactor">the reactor to be added.</param>
        ACDWGEXTRACTOR_PORT void addReactor(ExtractorReactor* reactor);
        /// <summary>
        /// Removes a reactor/observer. Reactors that must be removed before they are destroyed.
        /// </summary>
        /// <param name="reactor">the reactor to be removed.</param>
        ACDWGEXTRACTOR_PORT void removeReactor(ExtractorReactor* reactor);
        /// <summary>
        /// Returns the singleton instance of the Extractor.
        /// </summary>
        /// <returns>Extractor</returns>
        ACDWGEXTRACTOR_PORT static Extractor& theOne();
    };

    
}
#endif 