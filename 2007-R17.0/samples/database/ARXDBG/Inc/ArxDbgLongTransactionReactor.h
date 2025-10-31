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

#ifndef ARXDBGLONGTRANSACTIONREACTOR_H
#define ARXDBGLONGTRANSACTIONREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgLongTransactionReactor:
**
**  **jma
**
*************************************/

class ArxDbgLongTransactionReactor: public AcApLongTransactionReactor { 

public:
    ACRX_DECLARE_MEMBERS(ArxDbgLongTransactionReactor);

					ArxDbgLongTransactionReactor();
	virtual			~ArxDbgLongTransactionReactor();

    virtual void	beginCheckOut(AcDbLongTransaction& lt, AcDbObjectIdArray& originList);
    virtual void	endCheckOut(AcDbLongTransaction& lt);
    virtual void	beginCheckIn(AcDbLongTransaction& lt);
    virtual void	endCheckIn(AcDbLongTransaction& lt);
    virtual void	abortLongTransaction(AcDbLongTransaction& lt);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

	void	printReactorMessage(AcDbLongTransaction& lt, LPCTSTR event) const;

        // outlawed functions
									ArxDbgLongTransactionReactor(const ArxDbgLongTransactionReactor &copy);
    ArxDbgLongTransactionReactor&	operator=(const ArxDbgLongTransactionReactor &copy);        

};

#endif  // ARXDBGLONGTRANSACTIONREACTOR_H
