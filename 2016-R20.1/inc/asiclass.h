//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

//   Name: asiclass.h                           ast_asi_inc_appl_asiclass_h
//
//   Description:  Header file for AutoCAD SQL Interface.
//                 ASI C++ User Interface.

#ifndef ASI_ASICLASS_HH
#define ASI_ASICLASS_HH asiclasshh


///////////////////////////////////////////////////////////////////////////
// INCLUDES 
///////////////////////////////////////////////////////////////////////////
#include <asisdata.h>

#include <avoidtry.h> //for DecreaseGlobalAccount only
///////////////////////////////////////////////////////////////////////////
// DEFINES 
///////////////////////////////////////////////////////////////////////////
#define ASI_TRY           { CAsiExceptionHandler AsiExceptionHandler; try {  

#define ASI_CATCH(x)      } catch(CAsiException* x) { x=x;

#define ASI_END_CATCH     }}
#define ASI_THROW(x)      AsiExceptionThrow(x);
#define ASI_THROW_LAST    AsiExceptionThrow(0);


///////////////////////////////////////////////////////////////////////////
// FORWARD DEFINITIONS 
///////////////////////////////////////////////////////////////////////////

#pragma pack (push, 8)

// ASI Class Hierarchy
//
class DLLScope CAsiObject;                  // Superclass for all classes
    class CAsiHostBuffer;                   // Host program buffer
        class CAsiParameter;                // Parameter desriptor
  
    class CAsiException;                    // ASI Exception

    class CAsiSQLObject;                    // ASI User Interface base class
        class CAsiSession;                  // SQL Session
        class CAsiStm;                      // Generic SQL statement functionality
            class CAsiExecStm;              // Executable SQL statement
            class CAsiCsr;                  // Cursor
                class CAsiCsrTable;         // Superclass for table access
                    class CAsiCsrRegTable;  // Regular table access
                    class CAsiCsrInfSchema; // Information Schema access
                    class CAsiEnumerator;   // Data Source access.
        class CAsiBinding;                  // Input/Output parameters support


    class CAsiDSProperties;
class CAsiTACond;
class CAsiTCCond;

class CAsiExceptionHandler;                 // Exception handler


///////////////////////////////////////////////////////////////////////////
//     TYPEDEFS 
///////////////////////////////////////////////////////////////////////////

typedef enum {
    kOpNodeUndefined = 0,       /* Undefined node */

    /* Boolean operations */
    kOpNot,                     /* Not */
    kOpOr,                      /* Or */
    kOpAnd,                     /* And */
    kOpTest,                    /* Boolean test */

    /* Comparision predicate */
    kOpNull,                    /* is Null */
    kOpGtr,                     /* > */
    kOpGeq,                     /* >= */
    kOpEq,                      /* = */
    kOpLeq,                     /* <= */
    kOpLss,                     /* < */
    kOpNeq                      /* <> */
} EAsiCompType;

/////////////////////////////////////////////////////////////////////////
class CAsiExceptionHandler
// This class is used internaly to support asi exception handling 
// feature
{
public:
    // Constrution/destruction
    // 
    CAsiExceptionHandler(void);
    ~CAsiExceptionHandler(void);

    // Internal data for support TRY/CATCH
    // 
    CAsiException*        pException;
    CAsiExceptionHandler* pPrevHandler;
    EAsiBoolean           wasThrown;
};


//////////////////////////////////////////////////////////////////////
class CAsiException : public CAsiObject
//
// This class provides functionality of the SQL exception condition
// It is thrown by ASI member function when an exception condition was 
// raised. (ASI_TRY, ASI_CATCH, ASI_THROW facility).
//
{
    friend class CAsiSQLObject;
public:
    // Constrution/destruction
                            CAsiException (void);
    virtual					~CAsiException (void);

    // Getting Diagnostics Information   
    //
    int						CondQty    (void) const;       // Number of conditions in diag
    AsiError				Err        (int d = 0) const;  // get completion code
    CAsiUcStr		*		ErrMsg     (int d = 0) const;  // get error message
    char			*		SQLSTATE   (int d = 0) const;  // get SQLSTATE

    int						ErrPosition (void) const;     

  
    // Get Diagnostics Parameter
    //
    EAsiBoolean				getDiagPar (int, AsiDiag, integer *) const;
    EAsiBoolean				getDiagPar (int, AsiDiag, CAsiUcStr *) const;

     // Setting Diagnostics information

    EAsiBoolean				setErr      (AsiError);           // set completion code
    EAsiBoolean				setErrMsg   (const CAsiUcStr &);  // set error message
    EAsiBoolean				setSQLSTATE (const char *);       // set SQLSTATE // Unicode: Leave it as "char", it represents a buffer.

    // Set Diagnostics Parameter
    //
    EAsiBoolean				setDiagPar	(AsiDiag, integer);
    EAsiBoolean				setDiagPar	(AsiDiag, const CAsiUcStr &);



        
    EAsiBoolean				pushCond	(void);       // Push diagnostics information
    EAsiBoolean				flushCond	(void);       // Clear diagnostics

    ////////////////////////////////////////////////////
    // Utility
    //
    void			*  		getDiagData (void) const;
    void					setErrPosition (int);

    virtual CAsiObject *	duplicate	(void) const;         


private:
    void		*			pExceptionBody;
};





////////////////////////////////////////////////////////////////////////////////
class CAsiSQLObject : public CAsiObject
//
// This is a base class for classes that support SQL Connection-Session-
// Statement-Cursor functionality. It provides storage for the diagnostics 
// information generated by the derived classes.
// Besides diagnostics this class allows to get information about foreground
// DBMS driver, and the current ASI version.
//
// MEMBER FUNCTIONS
// ----------------
//
//  
// Getting Statement Information
//
// EAsiStatement StmType       (void) const    
// EAsiStatement CmdStmType    (void) const    
// long          RowCount      (void) const    
//
// These function retrieve SQL statement type, SQL Command statement type,
// number of rows affected by the <update:searched>, <delete: searched>, or 
// insert statements
//
//
// Syntax error position
//
// int ErrPosition   (void) const     
//
// Getting Diagnostics Information   
//
// int CondQty (void) const
//
// This function returns number of conditions stored in diagnostics area
// associated with the SQL object. Diagnostics area can hold several items
// belonging to the same or different conditions. Eash new condition in the
// diagnostics area introduces a new condition or clarifies a previouss one.
//
//
// EAsiError Err(
//   int icond) const       // Condition number
//
// This function returns error code associated with the condition specified 
// by its number. Condition codes are listed in the asiconst.h header file.
// If a wrong condition number was passed,  kAsiERUndefined is returned.
//
//
// CAsiUcStr *ErrMsg (
//   int icond) const       // Condition number
//
// This function returns pointer to the Unicode string object that contains
// message associated with specified condition. If invalid condition number 
// was specified, 0 is returned instead of it.
//
//
// char * SQLSTATE (
//   int icond) const       // Condition number
//
// This function returns pointer to the character ASCII string containing
// SQLSTATE diagnostics parameter associated with the specified condition.
// (SQLSTATE parameter is a 5 bytes null terminated charater string,
// consisting of class and subclass codes). If an invalid condition number
// was specified, NULL is returned instead of pointer.
//
//
// EAsiBoolean getDiagPar (int icond,              // Condition number
//     EAsiDiag pCode,         // Parameter code
//     integer *ivalue         // Integer parameter value
//    ) const
// EAsiBoolean getDiagPar (int icond,              // Condition number
//     EAsiDiag pCode,         // Parameter code
//     CAsiUcStr *ucvalue      // Character parameter value
//    ) const;
//
// These functions store value of diagnostics parameter specified by its
// code (pCode) for the specified condition into integer or Unicode 
// character string buffers. Return kAsiTrue if succeeded, or kAsiFalse 
// if an invalid condition number was specified.
//
// Parameters
//
// icond      Condition number
// pCode      Diagnostics parameter code
// ivalue     Destination for an integer value
// ucvalue    Destination for an Unicode character string
//
//
// Linked DBMS information
//
// The following functions allow to get information about DBMS driver 
// that maintains link between ASI application and DBMS server.
//
// EAsiBoolean DBMS (
//   CAsiUcStr & dbms         // DBMS Name
//  ) const    
//
// Stores DBMS name into Ucode string. Reference to the Unicode string 
// shall be provided by caller.
//
//
// EAsiBoolean SQLObject (
//   CAsiUcStr &objid         // SQL object identifier
//  ) const    
//
// Stores SQL object identifier into Ucode string. Reference to the destination
// Unicode string shall be provided by caller.
//
//
// EAsiBoolean DrvMessage (
//   CAsiUcStr &mess          // Driver message
//  ) const
//
// Stores driver message into Ucode string. Reference to the destination
// Unicode string shall be provided by caller.
//
//
// EAsiBoolean CheckOp (
//    ulong operation        // Operation codes
//   )                
//
// Return kAsiTrue if operations specified in the parameter are supported 
// by DBMS driver. Operation codes are a bit coded fields, that can be ored.
// kAsiFalse is returned if at least one operation is not supported.
//
//
// ASI version
//
// EAsiBoolean Version (
//    CAsiUcStr*             // Pointer for store ASI version string
//   ) const
//
// const char* Version (void) const
//
// Return pointer to the unocode string containing ASI version.
//
//
{
friend class CAsiCsr;
friend class CAsiExecStm;
friend class CAsiBinding;
public:
    // Constrution/destruction
    // 
protected:
                                CAsiSQLObject   ();
                                            // Setting Diagnostics information
protected:
    virtual EAsiBoolean         setErr      (EAsiError);           // set completion code
    virtual EAsiBoolean         setErrMsg   (const CAsiUcStr &);  // set error message
    virtual EAsiBoolean         setSQLSTATE (const char *);       // set SQLSTATE // Unicode: Leave it as "char", it represents a buffer.

            // Set Diagnostics Parameter
            //
    virtual EAsiBoolean         setDiagPar (EAsiDiag, integer);
    virtual EAsiBoolean         setDiagPar (EAsiDiag, const CAsiUcStr &);

        
    virtual EAsiBoolean			pushCond   (void);       // Push diagnostics information
    virtual EAsiBoolean			flushCond  (void); 


    virtual EAsiBoolean			pushErr    (EAsiError);     // Push diagnostics information
    virtual EAsiBoolean			pushHResult(HRESULT);		// Push diagnostics information


public:
    virtual                     ~CAsiSQLObject  ();

    // Getting Statement Information
    //
    EAsiStatement               StmType         (void) const;    // statement type
    LONG_PTR                    RowCount        (void) const;    // get row count


    // This is optional method for defining cursor
    virtual EAsiBoolean         IsRowset        (void) const;       // Can object create rowset?

    // Syntax error position
    virtual int                 ErrPosition     (void) const;     

    // Getting Diagnostics Information   
    //
    virtual int                 CondQty         (void) const;       // Number of conditions in diag
    virtual EAsiError           Err             (int d = 0) const;  // get completion code
    virtual CAsiUcStr       *   ErrMsg          (int d = 0);        // get error message
    virtual char            *   SQLSTATE        (int d = 0);        // get SQLSTATE

            // Get Diagnostics Parameter
            //
    virtual EAsiBoolean         getDiagPar      (int d,       // Integer condition
                                                EAsiDiag,
                                                integer *) const;
    virtual EAsiBoolean         getDiagPar      (int d,       // character condition
                                                EAsiDiag,
                                                CAsiUcStr *) const;
            
    // Linked DBMS information
    //
    EAsiBoolean                 DBMS            (CAsiUcStr *) const;            // DBMS type
    EAsiBoolean                 SQLObject       (CAsiUcStr *) const;            // SQL object identifier
    EAsiBoolean                 DrvMessage      (CAsiUcStr *) const;            // Driver message
    EAsiBoolean                 CheckOp         (ulong);                     // Check base operation
    virtual EAsiBoolean         GetStatus       (EAsiStatInfo, ULONG_PTR *);     // Get check status

    //  ASI version
    //
    const char             *    Version         (void) const;

protected:
    EAsiBoolean                 isInit      (void) const;
    EAsiBoolean                 InitErrorInfo (HRESULT, IUnknown *, GUID);
    void                        ReleaseErrorInfo ();
    void						InheritStatusInfo (const CAsiSQLObject &);


protected:
    //
    IErrorInfo          *       m_pIErrorInfo;      // Error info
    HRESULT                     m_HResult;

private:
    // ASI version string
    //
    static const char   *       m_pAsiVersion;
    CAsiException               m_Except;

protected:
    EAsiBoolean                 m_CSP;

protected:
    EAsiStatement               m_eStmType;
	LONG_PTR                m_lRowCount;

    CAsiDSProperties	   *	m_pDSProperties;

};


////////////////////////////////////////////////////////////////////////////
class CAsiAppl: public CAsiSQLObject
// This class is introduces functionality of ASI application 
// initialization/termination and disconnectinf from all 
// SQL environments. It is derived from the CAsiSQLObject class
// to provide caller with diagnostics info.
//
{
friend class CAsiSession;
friend class CAsiEnumerator;
friend class CAsiCsr;
public:
      //  Construction/destruction
      //
                                CAsiAppl        ();  
      virtual                   ~CAsiAppl       ();

      //  Application initialization/termination, Disconnect all
      //
      EAsiBoolean               Init            (void);  // Initialize application
      EAsiBoolean               Term            (void);  // Terminate application
      EAsiBoolean               Abort           (void);  // Abort application (rollback all active transactions
      EAsiBoolean               DisconnectAll   (void);  // Disconnect from all environmants

protected:
      EAsiBoolean               addConnection   (CAsiSession *);
      EAsiBoolean               removeConnection(CAsiSession *);

private: 
      EAsiBoolean               rollbackAll     (void);

private:
      IClassFactory		*		m_pIClassFactory;		// Csp Class Factory		
      IDataInitialize	*		m_pIDataInitialize;		// MSDA Initialize object
      IDataConvert		*		m_pIDataConvert;		// Data convert object
      CAsiObject        *       m_pSessions;            // Sessions
};


////////////////////////////////////////////////////////////////////////////////
class CAsiSession: public CAsiSQLObject
//
// This class provides services of the SQL connection and session management.
// Besides natural connection functionality (connect to and disconnect
// from SQL environment), this class provides straightforward way of executing
// transaction management and session management statements. Of course they
// can be also executed as a ordinary SQL statements by means of prepare and
// execute.
//
// MEMBER FUNCTIONS
// ----------------
//
// Construction/Destruction
//
// CAsiSession (CAsiAppl *)
//
// CAsiSession constructor constructs SQL-session object, but doesn't start
// the SQL session. Session is started when connecting to SQL environemnt
// is performed by means of the Connect () method provided by this class.
//
// ~CAsiSession ()
//
// Destroy CAsiSession object. If SQL-session is active when destructor is
// called, then terminate current transaction by ROLLBACK.
//
//
// Starting/Terminating Session
//
// EAsiBoolean Connect (
//   const CAsiUcStr & LinkFile,       // Link File name
//   const CAsiUcStr & usrname,        // User name
//   const CAsiUcStr & password,	   // Password	
//	 EAsiBoolean	   fPrompt)		   // Prompt
//
// Connect ot OLEDB data source via OLEDB provider.
// This function can throw exception and sets complition condition. 
// Return kAsiTrue if succeeded and kAsiFalse otherwise.
//
//
// EAsiBoolean Disconnect (void)
//
// Terminate SQL session and disconnect from SQL environment if there is
// mo active transaction associated with the session. Otherwise throw
// exception condition (if ASI_TRY was established), and store complition
// condition.
//
//
// Setting Session Context
//
// The function listed below are provided to set context of the current 
// SQL session. Session context items that can be set by means of them 
// comprise the following items:
//
//   catalog name,
//   schema name,
//   character set name,
//   time zone displacement, and
//   authorization
//
// These function can throw ASI exception and set complition condition.
// They return kAsiTrue if succeeded and kAsiFalse otherwise.
//
// EAsiBoolean SetCatalog  (
//   const CAsiUcStr & catalog)     // Catalog name
//
// EAsiBoolean SetSchema   (
//   const CAsiUcStr & schema)      // Schema name
//
// EAsiBoolean SetNames    (
//   const CAsiUcStr & name)        // Character set name
//
// EAsiBoolean SetTimeZone (
//   const CAsiDT &timezone)   // Time Zone 
//
// EAsiBoolean SetAuthor   (
//   const CAsiUcStr &  user);      // Authorization
//
//
// Transaction management
//
// EAsiBoolean SetTrans (
//   EAsiTILevel ilevel,         // Isolation level
//   EAsiTMode tmpode,           // Transaction mode
//   uint size                   // Diagnostics area size 
//  )
// Set transaction isolation level and transaction mode for the
// next transaction. If transaction is currently active, then throw ASI
// exception. Store complition condition. 
//
//
// EAsiBoolean DeferrConstr (
//   CAsiIdent *consname)        // Constraint name
//
// Change constraint checking mode to deffered.
//
// EAsiBoolean ImmConstr (
//   const CAsiIdent &consname)  // Constraint name
//
// Change constraint checking mode to immediate
//
// EAsiBoolean Commit       (void);                   // Commit work
//
// Terminate transaction by commit
//
// EAsiBoolean Rollback     (void);                   // Rollback
//
// Terminate transaction by rollback
//            
//
{
friend class CAsiStm;
friend class CAsiCsr;
friend class CAsiExecStm;
friend class CAsiAppl;
friend class CAsiCsrTable;
friend class CAsiCsrInfSchema;
friend class CAsiCsrRegTable;
public:
    // Construction/Destruction
    //
                            CAsiSession         (CAsiAppl *);
    virtual                 ~CAsiSession        ();

    // Starting/Terminating Session
    //
    EAsiBoolean             Connect             (const CAsiUcStr & LinkFile, 
                                                 const CAsiUcStr & Username,
                                                 const CAsiUcStr & Password,
                                                 EAsiBoolean	   fPrompt = kAsiFalse);

    EAsiBoolean				ConnectIniString	(const CAsiUcStr & IniString);

    EAsiBoolean				GetConnectionString (CAsiUcStr *);
    EAsiBoolean             Disconnect          (void);

           
    // Setting Session Context
    //
    EAsiBoolean             SetCatalog          (const CAsiUcStr &);
    EAsiBoolean             SetSchema           (const CAsiUcStr &);
    EAsiBoolean             SetNames            (const CAsiUcStr &);
    EAsiBoolean             SetTimeZone         (const CAsiDT &);
    EAsiBoolean             SetTimeZone         (void);          // Set local time zone 
    EAsiBoolean             SetAuthor           (const CAsiUcStr &);

    // Transaction management
    //
    EAsiBoolean             SetTrans            (EAsiTILevel, EAsiTMode, uint dSize = 64);  // Set transaction
    EAsiBoolean             DeferrConstr        (CAsiIdent * cnst = 0);   // Deffer constraint
    EAsiBoolean             ImmConstr           (CAsiIdent * cnst = 0);   // Immediate constraint

    EAsiBoolean             Commit              (void);                   // Commit work
    EAsiBoolean             Rollback            (void);                   // Rollback

    // Misceleneous
    //
    const CAsiUcStr      &  Name                (void) const;             // Session/connection name
    virtual EAsiBoolean     GetStatus			(EAsiStatInfo, ULONG_PTR *);  // Get check status

protected:
    EAsiBoolean             Disconnect          (CAsiObject *);
    EAsiBoolean				GetCatalog			(CAsiUcStr *);

private:
    virtual CAsiObject  *   duplicate           (void) const;             // Duplicate
    EAsiBoolean				CreateSession		(IDBInitialize *);

    EAsiBoolean             Execute             (const CAsiUcStr &);      // Execute command

    EAsiBoolean				CheckForNotNull		(EAsiInfSchTab, int);
    EAsiBoolean				CanRetrieveCatalogs	(void);
    EAsiBoolean				CanRetrieveSchemas	(void);
    void					GetProviderTypes	(void);
    EAsiBoolean				GetStatusInfo 		();

    void					AttachStm			(CAsiExecStm *);
    void					DetachStm			(CAsiExecStm *);
    void					DetachAllStm 		(void);
    void					DeallocateAllStm	(void);


    void					AttachCsr			(CAsiCsr *);
    void					DetachCsr 			(CAsiCsr *);
    void					DetachAllCsr 		(void);

    EAsiBoolean				HasOpenedObjects	(void);

private: 
    CAsiAppl            *   m_pAppl;                    // Aplication
    CAsiUcStr               m_LinkFileName ;			// Link file name
    CAsiUcStr				m_ConnectionString;			// Connection string from provider
    IUnknown            *   m_pISession;                // Session 
    CAsiUcStr				m_ucCatalog;	   			// Current catalog

    ULONG                   m_BLOBStorage;              // Only if BLOBs supported;

    CAsiList			*	m_pStms;					// statements
    CAsiList			*	m_pCsrs;					// cursors
};


////////////////////////////////////////////////////////////////////////////////
class CAsiStm: public CAsiSQLObject
//
// This class introduces functionality of the SQL statement descriptors
// Basic categories of services provided by this class are listed below:
//  - Input parameters manipulation (bind buffers)
//  - Output parameter manipulation (resulting columns)
//
//  MEMBER FUNCTIONS
//  ----------------
//
// Construction/Destruction
//
//  CAsiStm (void)
//
//  Allocate SQL statement descriptor.
//
//  virtual ~CAsiStm                   (void);
//
//  Destroy statement descriptor.
//
//
// Input Parameters Manipulation
//
// int ParamQty (void)
//
// Return number of input parameters (bind variables) in the original
// SQL statement. Number of parameter becomes available after SQL statement
// was prepared.
//
//
// CAsiParameter * ParamDsc (
//   int ipar                // Parameter number
//  ) const
//
// Get parameter descriptor. ipar shall be greater than or equal to 0 and 
// less than number of parameters returned by the ParamQty ().
// If wrong parameter number was specified return 0 instead of pointer to it.
//
//
// Bind parameter with host buffer
//
// EAsiBoolean Bind ( ... )
//
// Two basic methods for binding input paramters with the host variable
// buffers are provided by the CAsiStm class. They are
//
// - by parameter number
// - by parameter name
//
// Input parameter is bound with CAsiData object
//
//
// Output Column Descriptors / Column Values
//
// This set of services are provided in order to get description and 
// values of the resulting columns for the single row select statement
// and cursor. For other types of statements these services have no sence
// and always return kAsiBad.
//
// int ColQty (void) const
//
// Return number of columns in resuting rowset. 
//
//
// CAsiColumn *ColDsc (
//   int colnum                    // Column number
// ) const;         
//
// Return pointer to descripttor of the specified column.
//
//
// Two basic methods are provided to retrieve values of the resulting 
// columns:
//
//  - bind output column with the host buffer, and
//  - retrieve column value from descriptor
//
// These two methods are incompatible, i.e. if one method is used, another
// is not allowed.
//
// Both methods are simular and allow to store output value into 
// CAsiData object
//
// EAsiBoolean Sob ( ... )
//
// Bind output column with the host program buffer
//
//
// EAsiBoolean Cvl (...)
//
// Retrieve column data from descriptor
//
//
{
friend class CAsiSession;

public:
    // Construction/Destruction
    //
                                CAsiStm         (void);
    virtual                     ~CAsiStm        (void);

    // Init parrent session
    //
            void                SetSession      (CAsiSession *);

    // Input Parameters Manipulation
    //
    virtual int                 ParamQty        (void) const; // Parameter quantity
    virtual CAsiParameter   *   ParamDsc        (int) const;  // Get parameter descriptor

    // Bind input parameter by number with
    //
    virtual EAsiBoolean         Bind            (int, CAsiData *);    // CAsiData object
    virtual EAsiBoolean         Bind            (int, void *, short *,
                                                 int, EAsiHostType);  // Host buffer

    // Bind input parameter by name with
    //
    virtual EAsiBoolean         Bind            (const CAsiIdent &, CAsiData *); // CAsiData object
    virtual EAsiBoolean         Bind            (const CAsiIdent &, void *, short *,
                                                 int, EAsiHostType);    // Host buffer

    // Output Column Descriptors / Column Values
    //
    //
    virtual int                 ColQty          (void) const;      // Column quantity
    virtual CAsiColumn *        ColDsc          (int) const;       // Get column descriptor

     // Bind output parameter (column) with 
    virtual EAsiBoolean         Sob             (int, CAsiData *);    // CAsiData object
    virtual EAsiBoolean         Sob             (int, void *, short *,// Host buffer
                                                 int, EAsiHostType); 

    // Retrieve value of output parameter (column) into
    virtual EAsiBoolean         Cvl             (int, CAsiData *);    // CAsiData object
    virtual EAsiBoolean         Cvl             (int, void *, short *,// Host buffer
                                                 int, EAsiHostType);

protected:
    EAsiBoolean                 CvlInt          (int, CAsiData *) const;    // CAsiData object
    EAsiBoolean                 pInput          (void);
    EAsiBoolean					InitColsDsc		();

protected:
    CAsiBinding             *   m_pInput;		// Input bindings
    CAsiBinding             *   m_pOutput;		// Output buffers 

    CAsiSession             *   m_pSession;                         // Where I was allocated

    // Column descriptors buffer
    ULONG_PTR                   m_lColNumber;
    DBCOLUMNINFO            *   m_pColumnInfo;
    OLECHAR                 *   m_pStringBuff;
    CAsiRow                 *   m_pAsiRow;


};


////////////////////////////////////////////////////////////////////////////////
class CAsiExecStm: public CAsiStm
//
// This class introduces functionality of the executable SQL statement. 
// Another type of statement is a cursor that can't be executed, and 
// should be opend.
// Basic categories of services provided by this class are listed below:
//  - Statement preparing
//  - Statement execution
//
//  MEMBER FUNCTIONS
//  ----------------
//
// Construction/Destruction
//
//  CAsiExecStm (void)
//
//  Constructs SQL statement object
//
//  virtual ~CAsiExecStm  (void);
//
//  Destroy statement. If statement was not deallocated explicitly by
//  means of Dealocate method, then statement is deallocated implicitly.
//  
//
// Preparing/Deallocating
//
// EAsiBoolean Prepare (
//   CAsiSession *session,       // Session
//   const CAsiUcStr & stm,        // Statement
//   EAsiBoolean trans = kAsiTrue // translation flag.
//  )   

// Prepare standard SQL statement. Associate
// SQL statement with the session and prepares it. If trans parameter is true, ASI 
// performs translation into DBMS nastive format.
// This function stores complition condtion and 
// throws ASI exception if error condition was encounted. 
//
// EAsiBoolean Deallocate  (void)
//
// Deallocate either standard or interdatabase SQL statement. If statement is 
// a cursor specification associated with cursor in the open state, then
// ASI exception is raised.
//
//
// Execute statement
//
// EAsiBoolean Execute (void)
//
// Execute prepared SQL statement. Complition condition is always set and  
// ASI exception can be thrown.
//
//
// Immediate SQL and Native statement execution
//
// EAsiBoolean ImmediateExecute (
//   CAsiSession *session,     // session
//   const CAsiUcStr & stm)     // SQL statement
//
// Immediate execute standard SQL statement 
// Successful execution results is returning kAsiGood. If execution fails, 
// then ASI exception is thrown, complition
// conditon is stored CAsiSQLObject and kAsiBad is returned. Execution
// of this statement can start transaction.
//
{
friend class CAsiCsr;
friend class CAsiSession;
public:
    // Construction/Destruction
    //
                                CAsiExecStm         (void);
    virtual                     ~CAsiExecStm        (void);


    virtual EAsiBoolean         IsRowset            (void) const;


    // Preparing/Deallocating
    //
    virtual EAsiBoolean         Prepare             (CAsiSession *, 
                                                     const CAsiUcStr &, 
                                                     EAsiBoolean trans = kAsiTrue);
    virtual EAsiBoolean         Deallocate          (void);  // Deallocate statement

    // Prepared and execute statement (immediate execution)
    //
    virtual EAsiBoolean         Execute             (void);
    virtual EAsiBoolean         ImmediateExecute    (CAsiSession *, 
                                                     const CAsiUcStr &,
                                                     EAsiBoolean trans = kAsiTrue);
    EAsiBoolean					Cancel              (void);  // Cancel execution of SQL statment


    // Input Parameters Manipulation
    //
    virtual int                 ParamQty            (void) const; // Parameter quantity
    virtual CAsiParameter   *   ParamDsc            (int) const;  // Get parameter descriptor

    virtual EAsiBoolean         Bind                (int, CAsiData *);
    virtual EAsiBoolean         Bind                (int, void *, short *, int, EAsiHostType);
    virtual EAsiBoolean         Bind                (const CAsiIdent &, CAsiData *);
    virtual EAsiBoolean         Bind                (const CAsiIdent &, void *, short *, int, EAsiHostType);


    virtual int                 ColQty              (void) const;
    virtual CAsiColumn *        ColDsc              (int) const; 

    virtual EAsiBoolean			GetStatus			(EAsiStatInfo, ULONG_PTR *);     // Get check status


private:
    virtual CAsiObject      *   duplicate           (void) const;

    EAsiBoolean                 Prepare             (void);

    EAsiBoolean					IsPrepared			(void) const;
    void						AttachCsr			(CAsiCsr *);
    void						DetachCsr			(CAsiCsr *);
    void						DetachAllCsr 		(void);
    void						CloseAllCsr			(void);

protected:
    ICommandText            *   m_pICommand;                // Command

    // Parameter descriptors buffer
    ULONG                       m_lParNumber;
    DBPARAMINFO             *   m_pParamInfo;
    OLECHAR                 *   m_pStringBuffParam;

    // cursors
    CAsiList				*	m_pCsrs;
};  



////////////////////////////////////////////////////////////////////////////
class CAsiCsr: public CAsiStm
//
// This class proivides functionality of cursor 
//
// Construction/Destruction
//
// CAsiCsr (void);
//
// Construct cusror object
//
// ~CAsiCsr (void);
//
// Destroy cursor object. If cursor was in open state, close cursor implicitly.
//
//
// Allocate/Deallocate Cursor
//
//
// EAsiBoolean Allocate  (
//   CAsiExecStm * statement,         // Prepared cursor specification
//   const CAsiIdent & name,          // Cursor name
//   EAsiCurScr Scrollability,        // Cursor Scrollability
//   EAsiCurSns Sensivity);           // Cursor Sensitivity
//
// Allocate cursor. Statement shall be a prepared cursor specification.
// Otherwise ASI exception is thrown.
//
//
//
// Open/Close Cursor
//     
// EAsiBoolean Open (void)
//
// Open cursor. Cursor state becomes open and cursor position becomes before
// the first row of the selection set.
//
//
// EAsiBoolean Close (void)
//
// Close cursor. Cursor state is set to 'close'.
//
//
// Fetching Resulting Rowset        
//
// These services allow to fetch
//   - Next row
//   - Prior row
//   - First row
//   - Last row
//   - by the Relative row number (offset)
//   - by the Absolute row number (direct)
//
//   EAsiBoolean Fetch (void)
//
//   EAsiBoolean FetchPrior (void)
//
//   EAsiBoolean FetchFirst (void)
//   
//   EAsiBoolean FetchLast (void)
//
//   EAsiBoolean FetchRelative (
//     long rrow)                  // Relative row number
//
//   EAsiBoolean FetchAbsolute (
//     long row)                   // Absolute row number
//
//
// Storing Resulting Column Values
//
// CAsiRow   * getCurrentRow (void) 
//
// Return pointer to the CAsiRow object containing current row 
//
//
// Delete/Update Current Row (Delete: positioned, Update: positioned)
//
// EAsiBoolean Delete  (void)
//
// Delete current row
//
//
// EAsiBoolean Update  (const CAsiRow &) 
//
// Update current row. Only columns that are present in the CAsiRow 
// object are updated. Association is done by column name
//
//
// Misceleneous 
// 
// EAsiBoolean is_updatable  (void);      // Is cursor updatable
// EAsiBoolean is_scrollable (void);      // Is cursor scrollable
// EAsiBoolean is_open       (void);      // Is cursor in open state
//
{
friend class CAsiExecStm;
public:
    // Construction/Destruction
    //
                                CAsiCsr             (void);
    virtual                     ~CAsiCsr            (void);

    // Allocate SQL Cursor 
    EAsiBoolean                 Allocate            (CAsiExecStm * csrspec,      
                                                     const CAsiIdent & csrname, 
                                                     EAsiCurScr sc = kAsiNonScroll,     // Scrollability
                                                     EAsiCurSns sn = kAsiSnsUndef,      // Sensitivity
                                                     EAsiBoolean upd = kAsiUnknown,		// Updatbility
                                                     EAsiBoolean fIns = kAsiFalse);		// Inserts

    // Input Parameters Manipulation
    //
    virtual int                 ParamQty            (void) const; // Parameter quantity
    virtual CAsiParameter   *   ParamDsc            (int) const;  // Get parameter descriptor

    virtual EAsiBoolean         Bind                (int, CAsiData *);
    virtual EAsiBoolean         Bind                (int, void *, short *, int, EAsiHostType);
    virtual EAsiBoolean         Bind                (const CAsiIdent &, CAsiData *);
    virtual EAsiBoolean         Bind                (const CAsiIdent &, void *, short *, int, EAsiHostType);

     // Bind output parameter (column) with 
    virtual EAsiBoolean         Sob                 (int, CAsiData *);
    virtual EAsiBoolean         Sob                 (int, void *, short *, int, EAsiHostType); 

    // Open/Close Cursor
    virtual EAsiBoolean         Open                (void);     // Open cursor
    virtual EAsiBoolean         Close               (void);     // Close
    EAsiBoolean					Cancel              (void);		// Cancel cursor open

    // Fetching Resulting Rowset        
    //
    virtual EAsiBoolean         Fetch               (void);     // Fetch next row
    virtual EAsiBoolean         FetchPrior          (void);     // Fetch Prior row
    virtual EAsiBoolean         FetchFirst          (void);     // Fetch First row
    virtual EAsiBoolean         FetchLast           (void);     // Fetch Last row
    virtual EAsiBoolean         FetchRelative       (long);     // Fetch Relative row
    virtual EAsiBoolean         FetchAbsolute       (long);     // Fetch Absolute row
    virtual EAsiBoolean         CheckCCondition     (CAsiData **);

    // Storing Resulting Column Values
    //
    CAsiRow             *       getCurrentRow       (void);   // Get pointer to current row

    // Delete/Update Current Row (Delete: positioned, Update: positioned)
    //
    virtual EAsiBoolean         Delete              (void);            // Delete current row
    virtual EAsiBoolean         Update              (const CAsiRow &); // Update current row

    // Insert row
    virtual EAsiBoolean			Insert				(const CAsiRow &);
    virtual EAsiBoolean			Insert				(void);			   // Default row	


    virtual int                 ColQty              (void) const;
    virtual CAsiColumn *        ColDsc              (int) const; 

    virtual EAsiBoolean         Cvl                 (int, CAsiData *);
    virtual EAsiBoolean         Cvl                 (int, void *, short *,
                                                     int, EAsiHostType); 

    // Misceleneous 
    // 
    virtual EAsiBoolean			GetStatus			(EAsiStatInfo, ULONG_PTR *);     // Get check status
    virtual EAsiBoolean         IsRowset            (void) const;
    virtual EAsiBoolean         is_updatable        (void) const;       // Is cursor updatable
    virtual EAsiBoolean         is_insertable       (void) const;       // Can insert rows
    virtual EAsiBoolean         is_scrollable       (void) const;       // Is cursor scrollable
    virtual EAsiBoolean         is_insensitive      (void) const;       // Is cursor insensitive
    virtual EAsiBoolean         is_open             (void) const;       // Is cursor in open state
    virtual EAsiCurPos          position            (void) const;       // Cursor position


private:
    virtual CAsiObject  *       duplicate           (void) const;

protected:
    EAsiBoolean                 InitOutputBind      ();
    EAsiBoolean                 MakeCursorProp      (DBPROPSET  * pRowsetPropSet);
    EAsiBoolean                 QueryCursorProp     (void);
    EAsiBoolean					SobValues           (void);
    EAsiBoolean					Svl                 (int);
    EAsiBoolean                 ReadData            (void);
    EAsiBoolean                 GetColValue         (int, CAsiData *);
    EAsiBoolean					StoreValueFromDBType(CAsiData *, DBTYPE, void *);
	EAsiBoolean					InitAccessor		(ULONG_PTR, DBCOLUMNINFO *, const CAsiRow &,
                                                     ULONG *, DBBINDING	**,	HACCESSOR *,
                                                     EAsiBoolean);

    EAsiBoolean					DoChangeErrors		(HRESULT hr, ULONG, DBBINDING *);
    EAsiBoolean                 UpdateRow           (ULONG_PTR, DBCOLUMNINFO *, const CAsiRow &);
    EAsiBoolean                 InsertRow           (ULONG_PTR, DBCOLUMNINFO *, const CAsiRow &);

protected:
    CAsiExecStm         *       m_pCursorSpec;      // Pointer to cursor spec
    IRowset             *       m_pIRowset;         // Rowset object
    IRowsetChange       *       m_pIRowsetChange;
    IRowsetLocate       *       m_pIRowsetLocate;

    IAccessor           *       m_pIAccessor;
    HACCESSOR                   m_hAccessor;
    DWORD_PTR                   m_lRowCount; 
    DWORD                       m_lCurrRow;

    IDataConvert		*		m_pIDataConvert;		// Data convert object

    HROW                *       m_rghRows;
    BYTE                *       m_pData;

    // Output bindings
    DWORD_PTR                   m_dwOffset;
    DBBINDING           *       m_rgBind;
    int                         m_iNumBind;
    EAsiBoolean                 m_fDataRead;    // Data read flag


    EAsiBoolean					m_fBlkStorObj;  // Bloking storage objects
    EAsiBoolean                 m_fBLOBExpected;// Blobs in recordset
    IUnknown			*		m_pIUnknown;	// only one blob per cusrsor.
                                                // release it when next row is fetched

    CAsiIdent                   m_CsrName;      // cursor name
    EAsiCurScr                  m_ScrFlag;      // Scrollability flag
    EAsiCurSns                  m_SnsFlag;      // Sensitivity flag
    EAsiBoolean                 m_fUpd;         // Updatability flag
    EAsiBoolean                 m_fIns;         // Inserts flag
    EAsiBoolean					m_fOwnInserts;	// Own inserts 
    EAsiBoolean					m_fOwnUpdates;	// Own Updates


    EAsiBoolean					m_fIsOpen;		// Is open flag

    EAsiCurPos                  m_CsrPos;       // Cursor position

    // Info for scrollable cursors:
    ULONG_PTR                   m_ulColumns;
    ULONG                       m_ulCurrentRowNo;
    ULONG                       m_ulMaxRowNo;
    ULONG                       m_ulRows;

    // For CAsiCsrTable based classes:
    CAsiTCCond              *   m_pTCCond;
};



////////////////////////////////////////////////////////////////////////////
class CAsiCsrTable : public CAsiCsr
//  
//  This class provides access to database data on a table level. It is derived from
// the CAsiCsr class and inherits all its functionality. It is superclass for all
// ASI classes that provides access to data on a table level, such as Regular Table   
// Cursor (CAsiCsrRegTable) and Information Schema Table Cursor (CAsiCsrInfSchema) and 
// Data Source Enumerator (CAsiEnumerator) .
{
public:
                                CAsiCsrTable        (void);
    virtual                     ~CAsiCsrTable       (void);

    virtual int                 ColQty              (void) const;
    virtual CAsiColumn *        ColDsc              (int) const; 

    virtual EAsiBoolean         Open                (void);
    virtual EAsiBoolean         Close               (void);

    virtual EAsiBoolean         Update              (const CAsiRow &); 

    virtual EAsiBoolean         Cvl                 (int, CAsiData *);
    virtual EAsiBoolean         Cvl                 (int, void *, short *,
                                                     int, EAsiHostType); 

    virtual EAsiBoolean         SetFilter           (CAsiTCCond *);
    virtual EAsiBoolean         SetOrder            ();

protected:
    void                        DeallocCsr          (void);

protected:
};


////////////////////////////////////////////////////////////////////////////
class CAsiCsrRegTable : public CAsiCsrTable
// Regular table cursor. It is derived from CAsiCsrTable class and inherits all
// its functionality. Method Allocate provides functionality for allocating Regular 
// table rowset. Rows of the table must be accessed by mean regular cursor navigating
// and modification methods.   
{
public:
                                CAsiCsrRegTable     (void);
    virtual                     ~CAsiCsrRegTable    (void);

    // Database table
    EAsiBoolean                 Allocate            (CAsiSession * ses, 
                                                     const CAsiUcStr & catalog,    
                                                     const CAsiUcStr & schema,   
                                                     const CAsiUcStr & table,
                                                     EAsiCurScr    sc = kAsiNonScroll,      // Scrollability
                                                     EAsiBoolean   upd = kAsiUnknown		// Updatbility
                                                     ); 

protected:
    CAsiUcStr                   m_pCatalog ;
    CAsiUcStr                   m_pSchema;
    CAsiUcStr                   m_pName;

};



////////////////////////////////////////////////////////////////////////////
class CAsiCsrInfSchema : public CAsiCsrTable
// Infomation schema table cursor. It is derived from CAsiCsrTable class and inherits all
// its functionality. Method Allocate provides functionality for allocating information 
// schema table rowset. Rows of the table must be accessed by mean regular cursor navigating
// methods. Information Schema cursor is a read only cursor.
{
public:
                                CAsiCsrInfSchema    (void);
    virtual                     ~CAsiCsrInfSchema   (void);

    // allocate INFORMATION_SCHEMA cursor
    EAsiBoolean                 Allocate            (CAsiSession * ses, 
                                                     EAsiInfSchTab ischema,
                                                     EAsiCurScr    sc = kAsiNonScroll   // Scrollability
                                                     );

protected:
    EAsiInfSchTab               m_istType;
};



////////////////////////////////////////////////////////////////////////////
class CAsiEnumerator: public CAsiCsrTable
// Enumerator class provides services to enumerate Providers and Databases 
// supported by Providers. CAsiEnumerator is build upon rowset ISourcesRowset 
// object. It inherits all functionality of CAsiCsr class. Enumerator is a read only 
// cursor.
{
public:
                                CAsiEnumerator      (void);
    virtual                     ~CAsiEnumerator     (void);

    EAsiBoolean                 Allocate            (CAsiAppl *);
    EAsiBoolean                 Allocate            (CAsiAppl *, CLSID & clsidEnum);

    // Set restriction
    //  Data Source Type (EAsiDataSourceType)
    //      kAsiDSSOURCETYPE_DATASOURCE
    //      kAsiDSSOURCETYPE_ENUMERATOR
    //      kAsiDSSOURCETYPE_BOTH
    //  Name of data source or enumerator
    //      NULL - not restricted
    //  Is Parent
    void                        SetFilter           (EAsiDataSourceType dst,
                                                     const CAsiUcStr & pName,
                                                     EAsiBoolean isParent = kAsiUnknown);


    virtual EAsiBoolean         Fetch               (void);



protected:
    CLSID                       m_clsidEnum;  
    EAsiDataSourceType          m_eDsType;
    CAsiUcStr                   m_pName;
    EAsiBoolean                 m_fIsParent;

};


/////////////////////////////////////////////////////////////////////////
class CAsiTACond: public CAsiObject
//
// This class represents atomic condition for the table cursor in the 
// low-level driver.
//
{
    friend class CAsiTCCond;

public:
                                CAsiTACond          (void);
                                CAsiTACond          (const CAsiTACond &);
    virtual                      ~CAsiTACond        (void);

    virtual CAsiObject      *   duplicate           (void) const;

    CAsiData                *   m_pData;            // Pointer to internal data object
    int                         m_cColnum;          // Column number
    EAsiCompType                m_CompOp;           // Comparision predicate
};

/////////////////////////////////////////////////////////////////////
class CAsiTCCond: public CAsiObject
//
// This class is used to represent Database Table Cursor condition
// Actually this class is an array of the atomic conditions CAsiACond, 
// which are assumed to be ANDed. This class is passed to the AllocCsr 
// member function of the CAsiTable class and is used to filter table data
// during fetching.
//
{
public:
                                CAsiTCCond          (void);
                                CAsiTCCond          (int);
                                CAsiTCCond          (const CAsiTCCond &);
    virtual                     ~CAsiTCCond         (void);

    // Manipulation
            int                 Count               (void) const;           // Number of items
            void                Append              (const CAsiTACond &);   // Append item

    // Operators
            CAsiTACond      &   operator []         (int);                  // Get reference to item

    virtual CAsiObject      *   duplicate           (void) const;

private:
    int                         m_cQnty;            // Number of conditions
    CAsiList                    m_Conds;            // Conditions
};

////////////////////////////////////////////////////////////////////////////////////////
//
// Helper functions
//
////////////////////////////////////////////////////////////////////////////////////////
// Allocate Enumerator over a Data Source
// pAppl		 -  pointer to initialized ASI application
// guidEnum      -  pointer to data source parent enumerator. If NULL, assume 
//                  OLEDB root enumerator (CLSID_OLEDB_ENUMERATOR)
// pDS           -  Data Source name to enumerate
// pEnum         -  pointer to memory location where to store CAsiEnumerator. 
//                  0 if cannot enumerate.
//
// returns kAsiFalse, if enumerator cannot be allocated
//
EAsiBoolean AsiAllocateDSEnumerator (
    CAsiAppl		*		pAppl,			// [in] Asi Application
    const GUID      *       guidEnum,       // [in] Parent enumerator CLSID
    const CAsiUcStr &       pDS,            // [in] DS name
    CAsiEnumerator  **      pEnum           // [out] returned enumerator
);

////////////////////////////////////////////////////////////////////////////////////////
// Get Enumerator CLSID over a data source
// 
// Analogous to the AsiAllocateDSEnumerator. Returns enumerator CLSID, which
// can be used to Allocate CAsiEnumerator
//
EAsiBoolean AsiGetDSEnumerator (
    CAsiAppl		*		pAppl,			// [in]	ASI Application
    const GUID      *       guidEnum,       // [in] Parent enumerator CLSID
    const CAsiUcStr &       pDS,            // [in] DS name
    GUID            *       guidDsEnum      // [out] enumerator CLSID
);



                                    



////////////////////////////////////////////////
//  Extern function prototypes
//
extern "C" {
void                      AsiExceptionThrow (CAsiException*);
}

#pragma pack (pop)
#endif /* ASI_ASICLASS_HH */
/*EOF*/
