// (C) Copyright 1997-1998 by Autodesk, Inc. 
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _ACTRUTILPTR_H
#define _ACTRUTILPTR_H

#include <dbmain.h>
#include <actrans.h>
#include <adscodes.h>

#pragma warning(push)
#pragma warning(disable:4290)
#pragma warning(disable:4310)

//////////////////////////////////////////////////////////////////////////////
// AcTrUtil namespace.
// Encapsulates the classes AcTrUtil::Ptr, AcTrUtil::Transaction
namespace AcTrUtil
{
//////////////////////////////////////////////////////////////////////////////
// Useful inline
template<class E >
inline void 
checkErrorT(Acad::ErrorStatus what) throw(E)
{
    if (what!=Acad::eOk) 
        throw E(what);
}
template<class E >
inline void 
checkErrorT(Acad::ErrorStatus what,UINT descID,UINT helpID=0) throw(E)
{
    if (what!=Acad::eOk) 
        throw E(what,descID,helpID);
}
template<class E >
inline void 
checkErrorT(Acad::ErrorStatus what,const char* strDesc,UINT helpID=0) throw(E)
{
    if (what!=Acad::eOk) 
        throw E(what,strDesc,helpID);
}


//////////////////////////////////////////////////////////////////////////////
// Class AcTrUtil::Ptr

template<class T, class E = Acad::ErrorStatus>
class Ptr
{
public:
    Ptr(const T* pObj= NULL) throw()
        : m_pObj( const_cast<T*>( pObj ) )
    {}
    Ptr(const Ptr<T,E>&) throw()
        : m_pObj( p.m_pObj )
    {}
    Ptr(AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead, bool bOpenErased = false) throw(E)
        : m_pObj( T::cast( getObject( id, mode, bOpenErased ) ) )
    {}
    Ptr(ads_name ename, AcDb::OpenMode mode = AcDb::kForRead, bool bOpenErased = false) throw(E)
        : m_pObj( T::cast( getObject( ename, mode, bOpenErased ) ) ) {}
    ~Ptr() throw(E)
    {
        doneObject();
    }
    const Ptr<T,E>& operator=  (const Ptr<T,E>& p) throw(E)
    {
        if (m_pObj == p.m_pObj)
            return *this;
        
        doneObject();
        m_pObj = p.m_pObj;
        return *this;
    }
    const Ptr<T,E>& operator=  (const T* p) throw(E)
    {
        if (m_pObj == p)
            return *this;
        
        doneObject();
        m_pObj = const_cast<T*>( p );
        return *this;
    }
    T* operator-> () throw()
    {
        assert(NULL!=m_pObj);
        return m_pObj;
    }
    const T* operator-> () const throw()
    {
        assert(NULL!=m_pObj);
        return m_pObj;
    }
    operator T*& () throw()
    {
        return m_pObj;
    }
    operator const T* const & () const throw()
    {
        assert(NULL!=m_pObj);
        return m_pObj;
    }
protected:
    void doneObject() throw(E)
    {
        if (NULL != m_pObj)
        {
            if (AcDbObjectId::kNull == m_pObj->objectId())
            {
                delete m_pObj;
            }
            else
            {
                if (!m_pObj->isTransactionResident())
                {
                    if (m_pObj->isNewObject())
                    {
                        checkErrorT<E>( actrTransactionManager
                            ->addNewlyCreatedDBRObject( m_pObj ) );
                    }
                    else
                    {
                        getObject( m_pObj->objectId(),
                            m_pObj->isWriteEnabled()
                            ? AcDb::kForWrite : AcDb::kForRead,Adesk::kTrue);
                        m_pObj->close();
                    }
                }
            }
            m_pObj = NULL;
        }
    }
    AcDbObject* getObject (AcDbObjectId id, AcDb::OpenMode mode,
                       bool openErasedObject = false) throw(E)
    {
        AcDbObject *pRet = NULL;
        checkErrorT<E>( actrTransactionManager->getObject( pRet, id, mode, openErasedObject ) );
        return pRet;
    }
    AcDbObject* getObject (ads_name ename, AcDb::OpenMode mode,
                       bool openErasedObject = false) throw(E)
    {
        AcDbObjectId id;
        checkErrorT<E>( acdbGetObjectId( id, ename ) );
        return getObject( id, mode, openErasedObject );
    }
    T   *m_pObj;
};


//////////////////////////////////////////////////////////////////////////////
// Class AcTrUtil::Transaction

class Transaction
{
public:
    Transaction ()
        : m_bCommit( false )
    {
        AcTransaction *pt = actrTransactionManager->startTransaction();
        assert( NULL != pt );
#ifdef _DEBUG
        m_numTransaction = actrTransactionManager->numActiveTransactions();
#endif
    }

    ~Transaction ()
    {
#ifdef _DEBUG
        assert( actrTransactionManager->numActiveTransactions()== m_numTransaction );
#endif
        if (m_bCommit)
            actrTransactionManager->endTransaction();
        else
            actrTransactionManager->abortTransaction();
    }
    void commit()
    {
        m_bCommit = true;
    }
private:
    bool m_bCommit;
#ifdef _DEBUG
    int  m_numTransaction;
#endif
};
}; //namespace AcTrUtil
#pragma warning(pop)

#endif  // _ACTRUTILPTR_H
