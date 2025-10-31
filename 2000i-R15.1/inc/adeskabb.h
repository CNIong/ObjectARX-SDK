//
//  (C) Copyright 1992-1999 by Autodesk, Inc.  All rights reserved.
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

#ifndef   _ADESKABB_H
#define   _ADESKABB_H

// DESCRIPTION:
//
// Using the fully qualified names from the `Adesk' struct can be
// cumbersome.	If there are no global name conflicts use the
// following synonyms for convenience.
//
// Note:  All interface descriptions must use fully qualified names.
//	  That is, header files MUST NOT include this file and MUST
//	  NOT use these abbreviations.
//
// Note:  If any of the following abbreviations cause conflicts and
//	  this file cannot be included, then the acceptable abbreviations
//	  (those that do not cause conflicts) will have to be manually
//	  introduced, or another abbreviation header file will have to
//	  be created containing only the acceptable abbreviations.
//
// Note:  When this file is included in a source file, it MUST BE
//	  included AFTER all other include files (except possibly
//	  other abbreviation include files).
//	  For example:
//            #include "foo.h"
//            #include "bar.h"
//            #include "adeskabb.h" // <- Must be last!

#include "adesk.h"

typedef Adesk::Int8	    Int8;
typedef Adesk::Int16	    Int16;
typedef Adesk::Int32	    Int32;
typedef Adesk::UInt8	    UInt8;
typedef Adesk::UInt16	    UInt16;
typedef Adesk::UInt32	    UInt32;
typedef Adesk::uchar	    uchar;
typedef Adesk::ushort	    ushort;
typedef Adesk::uint	    uint;
typedef Adesk::ulong	    ulong;
typedef Adesk::Boolean	    Boolean;

enum
{
    kTrue                   = Adesk::kTrue,
    kFalse                  = Adesk::kFalse
};

#endif /* _ADESKABB_H */
