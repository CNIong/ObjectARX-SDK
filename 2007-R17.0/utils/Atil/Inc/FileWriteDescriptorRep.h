///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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
#ifndef DATASTREAMINTERFACE_H
namespace Atil { class DataStreamInterface; }
#endif
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef FILEREADDESCRIPTOR_H
namespace Atil { class FileReadDescriptor; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef SIZE_H
namespace Atil { class Size; }
#endif

#ifndef  FILEWRITEDESCRIPTORREP_H
#define  FILEWRITEDESCRIPTORREP_H

namespace Atil
{
class FileWriteDescriptorRep 
{

public:
    virtual ~FileWriteDescriptorRep ();

    virtual void construct (const ImageFormatCodec* codec) = 0;

    virtual const ImageFormatCodec* formatCodec () const = 0;
    virtual void getFileSpecifier (FileSpecifier& fs) const = 0;
    virtual bool setFileSpecifier (const FileSpecifier& fs) = 0;

    virtual void setOutputStream (DataStreamInterface* pdsStream) = 0;

    virtual void createImageFrame (const DataModel& dataModel, Size size) = 0;
    
    virtual bool requiredPropertiesSet () const = 0;
    virtual FormatCodecPropertySetIterator * newPropertySetIterator () = 0;
    virtual FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const = 0;
    virtual FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const = 0;
    virtual bool setProperty ( const FormatCodecPropertyInterface* pProperty ) = 0;
    virtual bool setProperties (const FileReadDescriptor * fd) = 0;

    virtual int writeImageFrame (RowProviderInterface* rowProvider) = 0;
};

} // end of namespace Atil
#endif
