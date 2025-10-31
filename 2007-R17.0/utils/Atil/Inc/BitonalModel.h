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

#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef RGBGRAYMODEL_H
#include "RgbGrayModel.h"
#endif

#ifndef  BITONALMODEL_H
#define  BITONALMODEL_H

namespace Atil
{
// The data model for 1-bit images that are part of the RgbModel space. 
// This datamodel is derived from RgbGrayModel. The foreground "on" or "1" pixels 
// are considered to be white, and the background "off" or "0" pixels are considered 
// to be black.
//
// This class is declared in BitonalModel.h. Its parent, RgbGrayModel, can be found 
// in RgbGrayModel.h.
//
class BitonalModel : public RgbGrayModel
{

public:
    BitonalModel ();
    virtual ~BitonalModel ();

    virtual DataModel* clone () const;
    DataModelAttributes::DataModelType dataModelType () const;
    virtual DataModelAttributes::PixelType pixelType () const;

    virtual bool canConvertTo (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionTo (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

    virtual bool canConvertFrom (const ColorModelInterface* colorModel) const;
    virtual RowProviderInterface* getModelConversionFrom (
        const ColorModelInterface* colorModel, RowProviderInterface* pConvert) const;

};

}
#endif
