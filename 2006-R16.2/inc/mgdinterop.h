//
// (C) Copyright 2003-2005 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary
// to Autodesk, Inc., and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of this information by anyone other than authorized
// employees of Autodesk, Inc. is granted only under a written
// non-disclosure agreement, expressly prescribing the scope
// and manner of such use.
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
//

// Unmanaged types
class AcGeVector2d;
class AcGeVector3d;
class AcGeMatrix2d;
class AcGeMatrix3d;
class AcGePoint2d;
class AcGePoint3d;
class AcGeScale2d;
class AcGeScale3d;
class AcGeTol;
class AcDbObjectId;
class AcDbExtents;

// Managed types
namespace Autodesk 
{
    namespace AutoCAD 
    {
        namespace Runtime
        {
            public __gc __abstract class DisposableWrapper;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Classes
//

class AcMgObjectFactoryBase : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcMgObjectFactoryBase);
    virtual gcroot<Autodesk::AutoCAD::Runtime::DisposableWrapper*> createRCW(AcRxObject* unmanagedPointer, bool autoDelete) = 0;
    virtual bool isManaged()
    {
        return false;
    }
    virtual ~AcMgObjectFactoryBase(){}
};


template <typename RCW, typename ImpObj>
class AcMgObjectFactory : public AcMgObjectFactoryBase
{
   
public:
    gcroot<Autodesk::AutoCAD::Runtime::DisposableWrapper*> createRCW(AcRxObject* unmanagedPointer, bool autoDelete)
    {
        gcroot<Autodesk::AutoCAD::Runtime::DisposableWrapper*> temp = new RCW(System::IntPtr(static_cast<ImpObj*>(unmanagedPointer)),autoDelete);
        return temp;
    }
    AcMgObjectFactory()
    {
        ImpObj::desc()->addX(AcMgObjectFactoryBase::desc(),this);
    }
    ~AcMgObjectFactory()
    {
        ImpObj::desc()->delX(AcMgObjectFactoryBase::desc());
    }
};

///////////////////////////////////////////////////////////////////////////////
// Data Marshalling
//

class StringToCIF
{
    char* m_ptr;
    
public:

    StringToCIF(System::String * str)
    {
        int 
        /*FCN*/WideCharToMultiByteCIF(
            UINT     CodePage,        // code page 
            DWORD    dwFlags,         // performance and mapping flags 
            LPCWSTR  lpWideCharStr,   // address of wide-character string 
            int      cchWideChar,     // number of characters in string 
            LPSTR    lpMultiByteStr,  // address of buffer for new string 
            int      cchMultiByte,    // size of buffer 
            DWORD    dwCustomFlags
        );
        m_ptr = NULL;
        if (str==NULL)
            return;
        int wLen = str->Length +1;

        wchar_t* wbuf = (wchar_t*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(str).ToPointer();
        try
        {
            int mbLen = WideCharToMultiByteCIF(CP_ACP,0,wbuf,wLen,NULL,0,0);
            m_ptr = (char*)System::Runtime::InteropServices::Marshal::AllocHGlobal(mbLen).ToPointer();
            WideCharToMultiByteCIF(CP_ACP,0,wbuf,wLen,m_ptr,mbLen+1,0);
        }
        __finally
        {
            System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(wbuf));
        }
    }
    ~StringToCIF()
    {
        System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(m_ptr));
    }
    operator const char*()
    {
        return m_ptr;
    }
}; 

inline System::String* CIFToString(const char* value)
{
    extern int 
    /*FCN*/MultiByteCIFToWideChar(
        UINT   CodePage,         // code page 
        DWORD  dwFlags,          // character-type options 
        LPCSTR lpMultiByteStr,   // address of string to map 
        int    cchMultiByte,     // number of characters in string 
        LPWSTR lpWideCharStr,    // address of wide-character buffer 
        int    cchWideChar       // size of buffer
    );
    if (value==NULL)
        return NULL;
    size_t mbLen = strlen(value)+1;
    int wLen = MultiByteCIFToWideChar(CP_ACP,0,value,mbLen,NULL,0);
    wchar_t* wbuf =(wchar_t*)System::Runtime::InteropServices::Marshal::AllocHGlobal(wLen*sizeof(wchar_t)).ToPointer();
    try
    {
        MultiByteCIFToWideChar(CP_ACP,0,value,mbLen,(WCHAR*)wbuf,wLen);
        return wbuf;
    }
    __finally
    {
        System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(wbuf));
    }
}

#if _MSC_VER == 1300
//need to turn off this warning because the compiler get confused when a value type
//has properties that return an object. It thinks that the value type actually has a member that
//is an object. 
#pragma warning(disable:4669) 
#endif

#define GETVECTOR3D(vec3d)  (*reinterpret_cast<AcGeVector3d*>(&(vec3d)))
#define GETVECTOR2D(vec2d)  (*reinterpret_cast<AcGeVector2d*>(&(vec2d)))
#define GETMATRIX3D(mat3d)  (*reinterpret_cast<AcGeMatrix3d*>(&(mat3d)))
#define GETMATRIX2D(mat2d)  (*reinterpret_cast<AcGeMatrix2d*>(&(mat2d)))
#define GETPOINT3D(point3d) (*reinterpret_cast<AcGePoint3d*>(&(point3d)))
#define GETPOINT2D(point2d) (*reinterpret_cast<AcGePoint2d*>(&(point2d)))
#define GETSCALE2D(scale2d) (*reinterpret_cast<AcGeScale2d*>(&(scale2d)))
#define GETSCALE3D(scale3d) (*reinterpret_cast<AcGeScale3d*>(&(scale3d)))
#define GETTOL(tol)         (*reinterpret_cast<AcGeTol*>(&(tol)))
#define GETOBJECTID(id)     (*reinterpret_cast<AcDbObjectId*>(&(id)))
#define GETEXTENTS3D(ext3d) (*reinterpret_cast<AcDbExtents*>(&(ext3d)))

#ifndef ACDBMGD

#ifdef AC_GEVEC3D_H
inline Autodesk::AutoCAD::Geometry::Vector3d ToVector3d(const AcGeVector3d& pt)
{
    Autodesk::AutoCAD::Geometry::Vector3d ret;
    GETVECTOR3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEVEC2D_H
inline Autodesk::AutoCAD::Geometry::Vector2d ToVector2d(const AcGeVector2d& pt)
{
    Autodesk::AutoCAD::Geometry::Vector2d ret;
    GETVECTOR2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEMAT2D_H
inline Autodesk::AutoCAD::Geometry::Matrix3d ToMatrix3d(const AcGeMatrix3d& pt)
{
    Autodesk::AutoCAD::Geometry::Matrix3d ret;
    GETMATRIX3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEMAT3D_H
inline Autodesk::AutoCAD::Geometry::Matrix2d ToMatrix2d(const AcGeMatrix2d& pt)
{
    Autodesk::AutoCAD::Geometry::Matrix2d ret;
    GETMATRIX2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEPNT3D_H
inline Autodesk::AutoCAD::Geometry::Point3d ToPoint3d(const AcGePoint3d& pt)
{
    Autodesk::AutoCAD::Geometry::Point3d ret;
    GETPOINT3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEPNT2D_H
inline Autodesk::AutoCAD::Geometry::Point2d ToPoint2d(const AcGePoint2d& pt)
{
    Autodesk::AutoCAD::Geometry::Point2d ret;
    GETPOINT2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GESCL2D_H
inline Autodesk::AutoCAD::Geometry::Scale2d ToScale2d(const AcGeScale2d& pt)
{
    Autodesk::AutoCAD::Geometry::Scale2d ret;
    GETSCALE2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GESCL3D_H
inline Autodesk::AutoCAD::Geometry::Scale3d ToScale3d(const AcGeScale3d& pt)
{
    Autodesk::AutoCAD::Geometry::Scale3d ret;
    GETSCALE3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GETOL_H
inline Autodesk::AutoCAD::Geometry::Tolerance ToTolerance(const AcGeTol& pt)
{
    Autodesk::AutoCAD::Geometry::Tolerance ret;
    GETTOL(ret) = pt;
    return ret;
}
#endif

#ifdef _AD_DBID_H
inline Autodesk::AutoCAD::DatabaseServices::ObjectId ToObjectId(const AcDbObjectId& pt)
{
    Autodesk::AutoCAD::DatabaseServices::ObjectId ret;
    GETOBJECTID(ret) = pt;
    return ret;
}
#endif

#ifdef AD_DBMAIN_H
inline Autodesk::AutoCAD::DatabaseServices::Extents3d ToExtents3d(const AcDbExtents& pt)
{
    Autodesk::AutoCAD::DatabaseServices::Extents3d ret;
    GETEXTENTS3D(ret) = pt;
    return ret;
}
#endif

#endif // #ifndef ACDBMGD
