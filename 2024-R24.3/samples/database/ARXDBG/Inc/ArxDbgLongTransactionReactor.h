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
