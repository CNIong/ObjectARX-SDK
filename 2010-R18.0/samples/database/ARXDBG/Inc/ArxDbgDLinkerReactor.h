//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
