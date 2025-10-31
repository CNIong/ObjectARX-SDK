//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#ifndef _DOCREACTOR_H
#define _DOCREACTOR_H

#include "acdocman.h"

class AsdkDocReactor: public AcApDocManagerReactor 
{ 
public: 
    virtual void documentToBeActivated(AcApDocument* pDoc); 
    virtual void documentCreated(AcApDocument* pDoc); 
    virtual void documentToBeDestroyed(AcApDocument* pDoc); 
}; 

class AsdkPerDocData
{ 
	friend class AsdkDocGlobals; 
public: 
    AsdkPerDocData(AcApDocument* pDoc); 

	//  colorIndex set by user.  Entity
	//  will shade itself in this color.
	int colorIndex;
	//  Facet deviation.  Smaller value
	//   causes more facets to be drawn and
	//   a more accurate represention of the
	//   geometry is obtained.  This is set
	//   by the user.
	double deviation;  

private: 
    AcApDocument* m_pDoc; 
    AsdkPerDocData* m_pNext; 
}; 

class AsdkDocGlobals  
{ 
public: 
    AsdkDocGlobals (AcApDocument* pDoc); 
    void setGlobals(AcApDocument* pDoc); 
    void removeDocGlobals(AcApDocument *pDoc); 
    void removeAllDocGlobals(AsdkPerDocData* pTarget); 
    void unload(); 

private: 
    AsdkPerDocData *m_pHead; 
    AsdkPerDocData *m_pData; 
    AsdkDocReactor *m_pDocReactor; 
}; 

extern AsdkDocGlobals *gpAsdkDocGlobals; 
extern AsdkPerDocData * gpActualData;

void InitializeMDIManagement();
void ShutDownMDIManagement();

#endif // _DOCREACTOR_H