//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
class CDocReactor : public AcApDocManagerReactor
{
public:
    virtual void  documentCreated(AcApDocument* pDoc);
	virtual void  documentActivated(AcApDocument* pDoc);
    virtual void  documentToBeDestroyed(AcApDocument* pDoc);
    virtual void  documentToBeDeactivated(AcApDocument* pDoc);
    virtual void  documentToBeActivated(AcApDocument* pDoc);
};