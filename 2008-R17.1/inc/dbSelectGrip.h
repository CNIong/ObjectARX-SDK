//
//  Copyright 2006-2007 by Autodesk, Inc.
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
//
//  dbSelectVPGrip.h - public header file for AcDbSelectVPGrip api
//

#ifndef _DBSELECTGRIP_H
#define _DBSELECTGRIP_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbSelectGrip
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class allows applications to determine whether a grip on a 
/// custom entity is selectable.
/// </summary>
///
/// <remarks>
/// Currently only called from the AutoCAD grip mechanism before
/// snapping to, hovering, or heating a grip.
/// </remarks>
///

class ADESK_NO_VTABLE AcDbSelectGrip : public AcRxObject {
public:
    ACRX_DECLARE_MEMBERS(AcDbSelectGrip);
    /// <summary>
    /// Determine whether a grip on a custom entity is selectable. 
    /// </summary>
    ///
    /// <param name="pEnt">
    /// [Input] Pointer to the entity that this grip belongs to.
    /// </param>
    /// 
    /// <param name="pVd">
    /// [Input] Pointer to a current viewport context AcGiViewportDraw object.
    /// </param>
    /// 
    /// <param name="pAppData">
    /// [Input] The private AcDbGripData appdata assigned to the custom grip.
	///   Use this private appdata along with pVd to determine whether the grip 
	///   is selectable in the current (viewport) context.
    /// </param>
    /// 
    /// <returns>
    /// Returns true if the grip is selectable and false if not.
    /// </returns>
    ///

    virtual bool SelectGrip(const AcDbEntity * pEnt, 
		                    const AcGiViewportDraw* pVd,
							const void * pAppData) = 0;
};

#pragma pack (pop)

#endif  // _DBSELECTGRIP_H

