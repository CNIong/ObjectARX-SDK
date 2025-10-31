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

#ifndef ARXDBGTRANSACTIONREACTOR_H
#define ARXDBGTRANSACTIONREACTOR_H

/****************************************************************************
**
**	CLASS ArxDbgTransactionReactor:
**
**	**jma
**
*************************************/

class ArxDbgTransactionReactor : public AcTransactionReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgTransactionReactor);

        // constructors/destructor
					ArxDbgTransactionReactor();
    virtual			~ArxDbgTransactionReactor();

    virtual void	transactionAboutToStart(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAboutToEnd(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAboutToAbort(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);

    virtual void	transactionStarted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionEnded(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAborted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	endCalledOnOutermostTransaction(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	objectIdSwapped(const AcDbObject* pTransResObj, const AcDbObject* pOtherObj, AcDbTransactionManager* transactionManagerPtr);


private:
    void    printReactorMessage(LPCTSTR event, int numTransactions) const;
    void    printReactorMessage(LPCTSTR event, int numTransactions, AcDbTransactionManager* transactionManagerPtr) const;
	void	printReactorMessage(LPCTSTR event, const AcDbObject* obj1,
							const AcDbObject* obj2,
							AcDbTransactionManager* transactionManagerPtr) const;

        // outlawed functions
    ArxDbgTransactionReactor(const ArxDbgTransactionReactor &copy);
    ArxDbgTransactionReactor&    operator=(const ArxDbgTransactionReactor &copy);        
};


#endif    // ARXDBGTRANSACTIONREACTOR_H
