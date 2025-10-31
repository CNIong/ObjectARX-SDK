/* 
      (C) Copyright 1990-1998 by Autodesk, Inc.

******************************************************************************
*                                                                            *
* The information contained herein is confidential, proprietary to Autodesk, *
* Inc., and considered a trade secret as defined in section 499C of the      *
* penal code of the State of California.  Use of this information by anyone  *
* other than authorized employees of Autodesk, Inc. is granted only under a  *
* written non-disclosure agreement, expressly prescribing the scope and      *
* manner of such use.                                                        *
*                                                                            *
**************************************************************************** */

#ifndef _DATAMGR_H_
#define _DATAMGR_H_ 1

#include "acdocman.h"

// 'DEBUG workaround' prevents the #include <map> statement in AdskDMgr.h
// from pulling in "use_ansi.h" that would force the debug CRT through 
// #pragma-s.
#if defined(_DEBUG) && (defined (_AFXDLL) || !defined (_WINDLL))
#define _DMGR_DEBUG_WAS_DEFINED
#undef _DEBUG
#define NDEBUG
#endif
#include <map>
#ifdef _DMGR_DEBUG_WAS_DEFINED
#undef NDEBUG
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
    };
    
    T& docData(AcApDocument* pDoc)
    {
        return m_dataMap[ pDoc ];
    }
    T& docData()
    {
        return docData(acDocManager->curDocument());
    }
    
private:
    std::map<AcApDocument*, T> m_dataMap;
};

#endif  /* _DATAMGR_H_ */
