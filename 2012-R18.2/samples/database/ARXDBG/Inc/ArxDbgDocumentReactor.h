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

#ifndef ARXDBGDOCUMENTREACTOR_H
#define ARXDBGDOCUMENTREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgDocumentReactor:
**
**  **jma
**
*************************************/

class ArxDbgDocumentReactor : public AcApDocManagerReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgDocumentReactor);

        // constructor/destructors
                    ArxDbgDocumentReactor();
    virtual         ~ArxDbgDocumentReactor();

        // messages that are sent by notification
    virtual void	documentCreateStarted(AcApDocument* doc);
    virtual void	documentCreated(AcApDocument* doc);
    virtual void	documentToBeDestroyed(AcApDocument* doc);
    virtual void	documentCreateCanceled(AcApDocument* doc);

    virtual void    documentLockModeWillChange(AcApDocument* doc,
                            AcAp::DocLockMode myCurrentMode,
                            AcAp::DocLockMode myNewMode,
                            AcAp::DocLockMode currentMode,
                            const TCHAR* pGlobalCmdName);
    virtual void    documentLockModeChangeVetoed(AcApDocument* doc,
                            const TCHAR* pGlobalCmdName);
    virtual void    documentLockModeChanged(AcApDocument* doc,
                            AcAp::DocLockMode myPreviousMode,
                            AcAp::DocLockMode myCurrentMode,
                            AcAp::DocLockMode currentMode,
                            const TCHAR* pGlobalCmdName);

    virtual void    documentBecameCurrent(AcApDocument* doc);
 
    virtual void    documentToBeActivated(AcApDocument* doc);
    virtual void    documentToBeDeactivated(AcApDocument* doc);
	virtual void	documentActivationModified(bool bActivation);
    virtual void	documentActivated(AcApDocument* pActivatedDoc);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

		// helper functions
    void		printReactorMessage(AcApDocument* doc, LPCTSTR event) const;
    void		printReactorMessage(LPCTSTR event) const;

        // outlawed functions
    ArxDbgDocumentReactor(const ArxDbgDocumentReactor &copy);
    ArxDbgDocumentReactor&  operator=(const ArxDbgDocumentReactor &copy);        
};

#endif    // ARXDBGDOCUMENTREACTOR_H
