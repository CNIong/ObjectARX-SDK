//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ADSKDMGR_H_
#define _ADSKDMGR_H_ 1

#include "acdocman.h"

// Defines
//     #pragma warning(disable: 4786)
// in your precompiled header to get rid of this warning

// 'DEBUG workaround' prevents the #include <map> statement in AdskDMgr.h
// from pulling in "use_ansi.h" that would force the debug CRT through 
// #pragma-s.
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG) && (defined (_AFXDLL) || !defined (_WINDLL))
// The result of the above line is that arx/dbx application statically linked 
// to MFC will  use the debug version of the c++ runtime, all other 
// configurations will use the release version.
#define _DMGR_DEBUG_WAS_DEFINED
#undef _DEBUG
#endif
#include <map>
#ifdef _DMGR_DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

template <class T> class AsdkDataManager : public AcApDocManagerReactor
{
public:
    AsdkDataManager()
    {
        acDocManager->addReactor(this);
    }
    ~AsdkDataManager()
    {
        acDocManager->removeReactor(this);
    }
    virtual void documentToBeDestroyed( AcApDocument *pDoc )
    {
        m_dataMap.erase(pDoc);
    }
    
    T& docData(AcApDocument* pDoc)
    {
        std::map<AcApDocument*, T>::iterator i;
        i = m_dataMap.find(pDoc);
        if (i==m_dataMap.end())
            return  m_dataMap[ pDoc ];
        else
            return (*i).second;
    }
    T& docData()
    {
        return docData(acDocManager->curDocument());
    }
    
private:
    std::map<AcApDocument*, T> m_dataMap;
};

#endif  /* _ADSKDMGR_H_ */
