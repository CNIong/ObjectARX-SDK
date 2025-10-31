// 
// (C) Copyright 1993-2002 by Autodesk, Inc. 
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
// AcGiStyleAttributes interface

#ifndef __AcGiStyleAttributes_H_Defined__
#define __AcGiStyleAttributes_H_Defined__

#include "AcGiLineAttributes.h"

typedef enum {
	kNothing								= 0x00,
	kColor      							= 0x01,
	kLine       							= 0x02,
	kEverything 							= 0x03
} AcGiAttributeFlags; 

class ADESK_NO_VTABLE AcGiStyleAttributes
{
public:

    // Ctor/dtor/copy
    AcGiStyleAttributes()   { }
    AcGiStyleAttributes(const AcGiStyleAttributes& source);
    virtual ~AcGiStyleAttributes()  { }

	// Member data access
    AcCmEntityColor& getColorAttribute();
    const AcCmEntityColor& getColorAttribute() const;
    void setColorAttribute(const AcCmEntityColor& color);

    // Interface methods
	virtual AcGiLineAttributes* getLineAttribute()                              = 0;
    virtual const AcGiLineAttributes* getLineAttribute() const                  = 0;
    virtual void setLineAttribute(const AcGiLineAttributes* pLineAttributes)    = 0;

    virtual void EnsureColorVisibility (AcCmEntityColor& color)	                = 0;	

protected:
    /* The style engine will resolve the color, taking into account color
		policy, dither, specified color, assigned pen number, and dimming.
		If m_colorAttribute.isByColor() then use
        getColorAttribute().color();
        if m_colorAttribute.isByPen() then use
        getColorAttribute().penIndex()
	*/
	AcCmEntityColor m_colorAttribute;

};

inline
AcGiStyleAttributes::AcGiStyleAttributes(
	const AcGiStyleAttributes& source) 
{
	m_colorAttribute = source.getColorAttribute();
}

inline
AcCmEntityColor& 
AcGiStyleAttributes::getColorAttribute()
{ 
    return m_colorAttribute; 
}

inline
const AcCmEntityColor& 
AcGiStyleAttributes::getColorAttribute() const
{ 
    return m_colorAttribute; 
}

inline 
void	
AcGiStyleAttributes::setColorAttribute (
	const AcCmEntityColor& color) 
{
	m_colorAttribute = color; 
}


#endif // #ifndef __AcGiStyleAttributes_H_Defined__