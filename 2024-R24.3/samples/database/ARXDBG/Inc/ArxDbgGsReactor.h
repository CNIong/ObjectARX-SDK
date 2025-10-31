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

#ifndef ARXDBGGSREACTOR_H
#define ARXDBGGSREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgGsReactor:
**
**  **jma
**
*************************************/

class ArxDbgGsReactor : public AcGsReactor {

public:
    //ACRX_DECLARE_MEMBERS(ArxDbgGsReactor); TBD: not derived off of AcRxObject yet!

                 ArxDbgGsReactor();
    virtual     ~ArxDbgGsReactor();

    virtual void viewWasCreated(AcGsView* pView);
    virtual void viewToBeDestroyed(AcGsView* pView);
    virtual void gsToBeUnloaded(AcGsGraphicsKernel* pGraphicsKernel);

private:
    void printReactorMessage(LPCTSTR event) const;
    class AcGsGraphicsKernel *m_pGraphicsKernel;

    // outlawed functions
    ArxDbgGsReactor(const ArxDbgGsReactor &copy);
    ArxDbgGsReactor& operator=(const ArxDbgGsReactor &copy);
};


#endif    // ARXDBGGSREACTOR_H
