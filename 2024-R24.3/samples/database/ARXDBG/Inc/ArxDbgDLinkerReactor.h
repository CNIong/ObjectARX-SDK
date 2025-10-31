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

#ifndef ARXDBGDLINKERREACTOR_H
#define ARXDBGDLINKERREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgDLinkerReactor:
**
**  **jma
**
*************************************/

class ArxDbgDLinkerReactor : public AcRxDLinkerReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxDbgDLinkerReactor);

        // constructors/destructor
					ArxDbgDLinkerReactor();
    virtual			~ArxDbgDLinkerReactor();

    virtual void	rxAppWillBeLoaded(const TCHAR* moduleName);
    virtual void	rxAppLoaded(const TCHAR* moduleName);
    virtual void	rxAppLoadAborted(const TCHAR* moduleName);

    virtual void	rxAppWillBeUnloaded(const TCHAR* moduleName);
    virtual void	rxAppUnloaded(const TCHAR* moduleName);
    virtual void	rxAppUnloadAborted(const TCHAR* moduleName);

private:
    void    printReactorMessage(LPCTSTR event, const TCHAR* moduleName) const;

        // outlawed functions
    ArxDbgDLinkerReactor(const ArxDbgDLinkerReactor &copy);
    ArxDbgDLinkerReactor&	operator=(const ArxDbgDLinkerReactor &copy);        
};


#endif    // ARXDBGDLINKERREACTOR_H
