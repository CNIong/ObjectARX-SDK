//
// (C) Copyright 2008-2009 by Autodesk, Inc.
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
//              Specialized templates to enbale the following types
//              to use certain allocators.
//


#if defined(ADSK_ACGEVECTOR2D_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACGEVECTOR2D_DEFINED
template<>
struct AllocatorSelector<AcGeVector2d, false>
{
    typedef AcArrayMemCopyReallocator<AcGeVector2d> allocator;
};
#endif

#if defined(ADSK_ACGEVECTOR3D_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACGEVECTOR3D_DEFINED
template<>
struct AllocatorSelector<AcGeVector3d, false>
{
    typedef AcArrayMemCopyReallocator<AcGeVector3d> allocator;
};
#endif

#if defined(ADSK_ACGEPOINT3D_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACGEPOINT3D_DEFINED
template<>
struct AllocatorSelector<AcGePoint3d, false>
{
    typedef AcArrayMemCopyReallocator<AcGePoint3d> allocator;
};
#endif

#if defined(ADSK_ACGEPOINT2D_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACGEPOINT2D_DEFINED
template<>
struct AllocatorSelector<AcGePoint2d, false>
{
    typedef AcArrayMemCopyReallocator<AcGePoint2d> allocator;
};
#endif

#if defined(ADSK_ACDBOBJECTID_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACDBOBJECTID_DEFINED
template<>
struct AllocatorSelector<AcDbObjectId, false>
{
    typedef AcArrayMemCopyReallocator<AcDbObjectId> allocator;
};
#endif

#if defined(ADSK_ACCMENTITYCOLOR_DEFINED) && defined(AC_ACARRAY_H)
#undef ADSK_ACCMENTITYCOLOR_DEFINED
template<>
struct AllocatorSelector<AcCmEntityColor, false>
{
    typedef AcArrayMemCopyReallocator<AcCmEntityColor> allocator;
};
#endif


