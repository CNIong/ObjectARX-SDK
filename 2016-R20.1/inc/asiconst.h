//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//    Name: asiconst.h                           ast_asi_inc_appl_asiconst_h
//
//    Description:  Header file for AutoCAD SQL Interface.
//                  Constant definitions

#ifndef ASI_ASICONST_H
#define ASI_ASICONST_H asiconsth

/* ///////////////////////////////////////////////////////////////////////// */
/* */
/*  SPECIAL DEFINES FOR FUNCTION PROTOTYPES   */
/* */
/* ///////////////////////////////////////////////////////////////////////// */
#ifdef _
#undef _
#endif /* _ */
#ifdef PROTOTYPES
#define _(x) x
#else /* PROTOTYPES not allowed */
#define _(x) ()
#endif  /* PROTOTYPES */

#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

/* ///////////////////////////////////////////////////////////////////////// */
/* */
/*  DEFINES  */
/* */
/* ///////////////////////////////////////////////////////////////////////// */
#define ASI_MAX(x,y) ((x)>(y)?(x):(y))
#define ASI_MIN(x,y) ((x)<(y)?(x):(y))

#include "csptypes.h"
#pragma pack (push, 8)
/* ///////////////////////////////////////////////////////////////////////// */
/* */
/* TYPEDEFS  */
/* */
/* ///////////////////////////////////////////////////////////////////////// */
typedef unsigned char  uchar;         /* Unsigned char */
#if !defined(hpux) || !defined(_SYS_TYPES_INCLUDED)
typedef unsigned short ushort;        /* Unsigned short */
typedef unsigned int   uint;          /* Unsigned int */
#endif /* !hpux  || !_SYS_TYPES_INCLUDED */
typedef unsigned long  ulong;         /* Unsigned long */
typedef double         real;          /* Real */
typedef long           integer;       /* Integer */
typedef short          smallint;      /* Small integer */


/* Interval data */

typedef struct asi_year {
    long        sign;       /* kAsiTrue if negative */
    ulong       years;      /* Years */
} ASI_IYEAR;

typedef struct asi_yeartomonth {
    long        sign;       /* kAsiTrue if negative */
    ulong       years;      /* Years */
    ulong       months;     /* Months (0-11) */
} ASI_IYEARTOMONTH;

typedef struct asi_month {
    long        sign;       /* kAsiTrue if negative */
    ulong       months;     /* Months */
} ASI_IMONTH;

typedef struct asi_day  {
    long        sign;       /* kAsiTrue if negative */
    ulong       days;       /* Days */
} ASI_IDAY;

typedef struct asi_daytohour  {
    long        sign;       /* kAsiTrue if negative */
    ulong       days;       /* Days */
    ulong       hours;      /* Hours (0-23) */
} ASI_IDAYTOHOUR;

typedef struct asi_daytominute {
    long        sign;       /* kAsiTrue if negative */
    ulong       days;       /* Days */
    ulong       hours;      /* Hours (0-23) */
    ulong       minutes;    /* Minutes (0-59) */
} ASI_IDAYTOMINUTE;

typedef struct asi_daytosecond {
    double      seconds;    /* Seconds (0-59.99..9) */
    long        sign;       /* kAsiTrue if negative */
    ulong       days;       /* Days */
    ulong       hours;      /* Hours (0-23) */
    ulong       minutes;    /* Minutes (0-59) */
} ASI_IDAYTOSECOND;

typedef struct asi_hour {
    long        sign;       /* kAsiTrue if negative */
    ulong       hours;      /* Hours */
} ASI_IHOUR;

typedef struct asi_hourtominute {
    long        sign;       /* kAsiTrue if negative */
    ulong       hours;      /* Hours */
    ulong       minutes;    /* Minutes (0-59)  */
} ASI_IHOURTOMINUTE;

typedef struct asi_hourtosecond {
    double      seconds;    /* Seconds (0-59.99..9) */
    long        sign;       /* kAsiTrue if negative */
    ulong       hours;      /* Hours */
    ulong       minutes;    /* Minutes (0-59) */
} ASI_IHOURTOSECOND;

typedef struct asi_minute {
    long        sign;       /* kAsiTrue if negative */
    ulong       minutes;    /* Minutes */
} ASI_IMINUTE;

typedef struct asi_minuteitosecond {
    double      seconds;    /* Seconds (0-59.99..9) */
    long        sign;       /* kAsiTrue if negative */
    ulong       minutes;    /* Minutes */
} ASI_IMINUTETOSECOND;

typedef struct asi_second {
    double      seconds;    /* Seconds */
    long        sign;       /* kAsiTrue if negative */
} ASI_ISECOND;

/* Datetime data */
/* */
typedef struct asi_date {  /* Date */
    ushort year;             /* Year */
    ushort month;            /* Month (0-11) */
    ushort day;              /* Day (0-31) */
    short  pad;              /* pad short */
} ASI_DTDATE;

typedef struct asi_time {       /* Time with time zone */
    double            second;   /* Second (0-59.99..9) */
    ASI_IHOURTOMINUTE timezone; /* time zone */
    ushort            hour;     /* Hour (0-23) */
    ushort            minute;   /* Minute (0-59) */
} ASI_DTTIME;

typedef struct asi_timestamp {  /* Timestamp with time zone */
    ASI_DTTIME   time;          /* Time */
    ASI_DTDATE   date;          /* Date */
} ASI_DTTIMESTAMP; 


/* */
typedef enum {
    kAsiUnknown = -1,           /* Boolean value is undefined */
    kAsiFalse = 0,
    kAsiTrue = 1,
    kAsiBad = 0,
    kAsiGood = 1
} EAsiBoolean;

#define EAsiFlag EAsiBoolean

/* SQL data types */
typedef enum {
    kAsiVector      = -2,       /* Row */
    kAsiImplDefined = -1,       /* Implementation-defined data type */
    kAsiTUnknown = 0,
    kAsiChar = 1,
    kAsiNumeric,
    kAsiDecimal,
    kAsiInteger,
    kAsiSmallInt,
    kAsiFloat,
    kAsiReal,
    kAsiDouble,
    kAsiDateTime,
    kAsiInterval,
    kAsiCharVar = 12,
    kAsiBit = 14,
    kAsiBitVar,
    kAsiPoint,	/* n-dimentional point  */
	kAsiBlob
} EAsiDataType;

/* Date time types */
typedef enum {
    kAsiDTUnknown = 0,
    kAsiDate = 1,
    kAsiTime,
    kAsiTimeStamp,
    kAsiTimeTZ,
    kAsiTimeStampTZ
} EAsiDTType;

/* Interval types */
typedef enum {
    kAsiIUnknown = 0,
    kAsiYear = 1,
    kAsiMonth,
    kAsiDay,
    kAsiHour,
    kAsiMinute,
    kAsiSecond,
    kAsiYear2Month,
    kAsiDay2Hour,
    kAsiDay2Minute,
    kAsiDay2Second,
    kAsiHour2Minute,
    kAsiHour2Second,
    kAsiMinute2Second
} EAsiIType;


typedef unsigned int uint;

/* //////////////////////////////////////////////////////////// */
/* */
/* Trim specification */
/* */
typedef enum {
  kAsiLeading = 0,
  kAsiTrailing,
  kAsiBoth
} EAsiTrimSpec;


/* Host variable type */
/* */
typedef enum {
    kAsiHnull  = 0,           /* Type undefined */
    kAsiHshort = 1,           /* short int */
    kAsiHlong,                /* long int */
    kAsiHfloat,               /* float */
    kAsiHreal,                /* double */
    kAsiHchar,                /* null terminated character string */
    kAsiHunicode,             /* unicode string (wide characters string) */
    kAsiHbinary,              /* binary buffer */
    kAsiHdate,                /* date  (ASI_DTDATE) */
    kAsiHtime,                /* time  (ASI_DTTIME) */
    kAsiHtimestamp,           /* timestamp (ASI_DTTIMESTAMP) */
    kAsiHyear,                /* Year (ASI_IYEAR) */
    kAsiHyeartomonth,         /* Year to Month (ASI_IYEARTOMONTH) */
    kAsiHmonth,               /* Month (ASI_IMONTH) */
    kAsiHday,                 /* Day (ASI_IDAY) */
    kAsiHdaytohour,           /* Day to hour (ASI_IDAYTOHOUR) */
    kAsiHdaytominute,         /* Day to minute (ASI_IDAYTOMINUTE) */
    kAsiHdaytosecond,         /* Day to second (ASI_IDAYTOSECOND) */
    kAsiHhour,                /* Hour (ASI_IHOUR) */
    kAsiHhourtominute,        /* Hour to minute (ASI_IHOURTOMINUTE) */
    kAsiHhourtosecond,        /* Hour to second (ASI_IHOURTOSECOND) */
    kAsiHminute,              /* Minute (ASI_IMINUTE) */
    kAsiHminutetosecond,      /* Minute to second (ASI_IMINUTETOSECOND) */
    kAsiHsecond               /* Second (ASI_ISECOND) */
} EAsiHostType;

/* */
/*  EAsiDrvStatus, EAsiSIDataType, and EAsiSITransactionType  */
/*  sepecify features and capabilities that connection supports. */
/*  They can be retrieved by means of CAsiSQLObject::GetStatus function */
/* */

/* Supported general features codes */
/* */
typedef enum {
   kAsiStatUsername       = (int)0x00000001      /* User name */
  ,kAsiStatPassword       = (int)0x00000002      /* Password */
  ,kAsiStatCatalog        = (int)0x00000004      /* Catalog feature */
  ,kAsiStatSchema         = (int)0x00000008      /* Schema feature */
  ,kAsiStatTimeZone       = (int)0x00000010      /* Time zone */
  ,kAsiStatNames          = (int)0x00000020      /* Character set names */
  ,kAsiStatTranslation    = (int)0x00000040      /* Translations */
  ,kAsiStatInfoSchema     = (int)0x00000080      /* Information schema facility */
  ,kAsiStatCDCatalog      = (int)0x00000100      /* Catalog definition/drop catalog */
  ,kAsiStatCDSchema       = (int)0x00000200      /* Schema definition/drop schema */
  ,kAsiStatCDTable        = (int)0x00000400      /* Table definition/drop table */
  ,kAsiStatCDView         = (int)0x00000800      /* View definition/drop view */
  ,kAsiStatCDIndex        = (int)0x00001000      /* Index definition/drop index */
  ,kAsiStatCDTranslation  = (int)0x00002000      /* Translation definition/drop translation */
  ,kAsiStatCDAssertion    = (int)0x00004000      /* Create assertion/drop assertion */
  ,kAsiStatCDCharset      = (int)0x00008000      /* Character set definition/drop character set */
  ,kAsiStatCDCollation    = (int)0x00010000      /* Collation definition/drop collation */
  ,kAsiStatCDDomain       = (int)0x00020000      /* Domain definition/drop domain */
  ,kAsiStatADomain        = (int)0x00040000      /* Alter domain */
  ,kAsiStatATable         = (int)0x00080000      /* Alter table */
  ,kAsiStatPrivileges     = (int)0x00100000      /* Grant/revoke privileges */
  ,kAsiStatCommitRollback = (int)0x00200000      /* Commit work/Rollback work */
  ,kAsiStatSetTrans       = (int)0x00400000      /* Set transaction */
  ,kAsiStatSetConstr      = (int)0x00800000      /* Set constraint */
  ,kAsiStatCursor         = (int)0x01000000      /* Cursor manipulation (open, close, fetch next) */
  ,kAsiStatFetch          = (int)0x02000000      /* Fetches Prior, First, Last, Absolute, Relative */
  ,kAsiStatSingSelect     = (int)0x04000000      /* Select statement: single row  */
  ,kAsiStatDeletePos      = (int)0x08000000      /* Delete: positioned */
  ,kAsiStatUpdatePos      = (int)0x10000000      /* Update: positioned */
  ,kAsiStatDeleteSearch   = (int)0x20000000      /* Delete: searched */
  ,kAsiStatUpdateSearch   = (int)0x40000000      /* Update: searched */
  ,kAsiStatInsert         = (int)0x80000000      /* Insert */

} EAsiDrvStatus;


/* Supported data type  */
typedef enum {
    kAsiSDImplDefined = (int)0x00000001,
    kAsiSDChar        = (int)0x00000002,
    kAsiSDNumeric     = (int)0x00000004,
    kAsiSDDecimal     = (int)0x00000008,
    kAsiSDInteger     = (int)0x00000010,
    kAsiSDSmallInt    = (int)0x00000020,
    kAsiSDFloat       = (int)0x00000040,
    kAsiSDReal        = (int)0x00000080,
    kAsiSDDouble      = (int)0x00000100,
    kAsiSDDate        = (int)0x00000200,
    kAsiSDTime        = (int)0x00000400,
    kAsiSDTimeTZ      = (int)0x00000800,
    kAsiSDTimestamp   = (int)0x00001000,
    kAsiSDTimestampTZ = (int)0x00002000,
    kAsiSDYM          = (int)0x00004000,
    kAsiSDDT          = (int)0x00008000,
    kAsiSDCharVar     = (int)0x00010000,
    kAsiSDBit         = (int)0x00020000,
    kAsiSDBitVar      = (int)0x00040000,
	kAsiSDBLOB		  = (int)0x00080000,
	kAsiSDCharAsStr	  = (int)0x00100000	  // provider may use STR rather that WSTR to  
										  // accept char input paramters

} EAsiSIDataType;


/* Supported transaction types */
typedef enum {
	kAsiTSUndefined = (int )0,		 /* Undefined */	
									 /* Read/Write, Read Uncommitted is not possible */
	kAsiTSRWRC = (int)0x00000001,    /* Read/Write, Read Committed */
	kAsiTSRWRR = (int)0x00000002,    /* Read/Write, Repeatable Read */
	kAsiTSRWSR = (int)0x00000004,    /* Read/Write, Serializable */
	kAsiTSRORU = (int)0x00000008,    /* Read Only, Read Uncommitted  */
	kAsiTSRORC = (int)0x00000010,    /* Read Only, Read Committed */
	kAsiTSRORR = (int)0x00000020,    /* Read Only, Repeatable Read */
	kAsiTSROSR = (int)0x00000040     /* Read Only, Serializable */

} EAsiSITransactionType;


/* Driver features, capabilities and status codes */
typedef enum {
   kAsiSISupportedFeatures            /* Supported base features codes (EAsiDrvStatus) */
  ,kAsiSITransaction                  /* Transaction state (EAsiBoolean) */
  ,kAsiSICsrState                     /* Open/Close cursor (EAsiBoolean) */
  ,kAsiSICsrSns                       /* Sensitive/insensitive cursor (EAsiBoolean) */
  ,kAsiSICsrScr                       /* Scroll/non scroll cursor (EAsiBoolean) */
  ,kAsiSICsrPos                       /* Cursor position (long) */
  ,kAsiSICsrUpd                       /* Cursor updatability (EAsiBoolean) */
  ,kAsiSIDataType                     /* Supported data types (EAsiSIDataType) */
  ,kAsiSIBindDataType                 /* Supported bind data types  (EAsiSIDataType) */
  ,kAsiSITransactionType              /* Supported types of tranactions (EAsiSITransactionType) */
} EAsiStatInfo;

#ifdef A
/* SQL statement types */
/* */
typedef enum {
    kAsiTYPE_UNDEFINED = 0,   /*  undefined */
    kAsiALLOC_CURSOR,         /*  allocate cursor  */
    kAsiALLOC_STATEMENT,      /*  allocate statement */
    kAsiALTER_DOMAIN,         /*  alter domain */
    kAsiALTER_TABLE,          /*  alter table */
    kAsiCREATE_ASSERTION,     /*  assertion definition */
    kAsiCREATE_CATALOG,       /*  create catalog */
    kAsiCREATE_CHARACTER_SET, /*  character set definition */
    kAsiCREATE_COLLATION,     /*  collation definition */
    kAsiCREATE_DOMAIN,        /*  domain definition */
    kAsiCLOSE_CURSOR,         /*  close cursor  */
    kAsiCOMMIT,               /*  commit work */
    kAsiCONNECT,              /*  connect  */
    kAsiCREATE_SCHEMA,        /*  schema definition */
    kAsiCREATE_TABLE,         /*  table definition */
    kAsiCREATE_VIEW,          /*  view definition */
    kAsiCREATE_INDEX,         /*  index definition */
    kAsiCREATE_TRANSLATION,   /*  translation definition */
    kAsiCURSOR,               /*  cursor specification */
    kAsiDELETE_CURSOR,        /*  delete positioned */
    kAsiDELETE_WHERE,         /*  delete searched */
    kAsiDEALLOCATE_STATEMENT, /*  deallocate statement */
    kAsiDISCONNECT,           /*  disconnect */
    kAsiDROP_ASSERTION,       /*  drop assertion */
    kAsiDROP_CATALOG,         /*  drop catalog */
    kAsiDROP_CHARACTER_SET,   /*  drop character set */
    kAsiDROP_COLLATION,       /*  drop collation */
    kAsiDROP_DOMAIN,          /*  drop domain */
    kAsiDROP_SCHEMA,          /*  drop schema */
    kAsiDROP_TABLE,           /*  drop table */
    kAsiDROP_TRANSLATION,     /*  drop translation */
    kAsiDROP_VIEW,            /*  drop view */
    kAsiDROP_INDEX,           /*  drop index */
    kAsiEXECUTE_IMMEDIATE,    /*  immediate execute */
    kAsiEXECUTE,              /*  execute */
    kAsiFETCH,                /*  fetch */
    kAsiGRANT,                /*  grant privileges */
    kAsiINSERT,               /*  insert */
    kAsiOPEN,                 /*  open cursor */
    kAsiPREPARE,              /*  prepare */
    kAsiREVOKE,               /*  revoke privileges */
    kAsiROLLBACK,             /*  rollback work */
    kAsiSELECT,               /*  select statement: single row */
    kAsiSET_CATALOG,          /*  set catalog */
    kAsiSET_SCHEMA,           /*  set schema */
    kAsiSET_TIME_ZONE,        /*  set time zone */
    kAsiSET_NAMES,            /*  set names  */
    kAsiSET_TRANSACTION,      /*  set transaction */
    kAsiSET_CONSTRAINT,       /*  set constraint mode  */
    kAsiSET_AUTHORIZATION,    /*  set authorization identifier */
    kAsiUPDATE_CURSOR,        /*  update: positioned */
    kAsiUPDATE_WHERE          /*  update: searched */
} EAsiStatement;
#endif


/* Transaction isolation level */
typedef enum {
    kAsiTIUndefined = 0,
    kAsiReadUncommitted = 1,
    kAsiReadCommitted,
    kAsiRepeatableRead,
    kAsiSerializable
} EAsiTILevel;

/* Transaction mode */
typedef enum {
    kAsiTMUndefined = 0,
    kAsiTReadOnly = 1,
    kAsiTReadWrite
} EAsiTMode;

/* default diagnostics size */
#define  DefaultDiagSize 32

/* Defer or immediate constriant checking */
typedef enum {
  kAsiCDefer = 1,
  kAsiCImmediate
} EAsiConstrCheck;


/* Cursor scrollability */
typedef enum {
    kAsiNonScroll = 0,
    kAsiScroll = 1
} EAsiCurScr;

/* Cursor Sensitivity */
typedef enum {
    kAsiSnsUndef = 0,      /* Cursor sensitivity is undefined */
    kAsiInsensitive = 1
} EAsiCurSns;

/* Fetch direction */
typedef enum {
    kAsiNext = 1,
    kAsiPrior,
    kAsiFirst,
    kAsiLast,
    kAsiAbsolute,
    kAsiRelative
} EAsiDirection;

/* Cursor position */
/* */
typedef enum {
    kAsiCPUnknown = 0,     /* Position unknown */
    kAsiTos       = 1,     /* Before the first row */
    kAsiEos       = 2,     /* After the last row */
    kAsiBnr       = 3,     /* Before row (on deleted row) */
    kAsiOcr       = 4      /* Current row */
} EAsiCurPos;

/*  Coercibility attributes */
/* */
typedef enum {
   kAsiCACoercible = 0,    /* Coercible */
   kAsiCAImplicit  = 1,    /* Implicit */
   kAsiNoCollation = 2,    /* No collating sequence  */
   kAsiCAExplicit  = 3     /* Explicit */
} EAsiCAttr;


/* Information schema tables */
typedef enum {
     kAsiISUnknown					= 0

	// Logical tables
	,kAsiIS_ASSERTIONS				= 1
	,kAsiIS_CHARACTER_SETS			= 2
	,kAsiIS_CHECK_CONSTRAINTS		= 3
	,kAsiIS_COLLATIONS				= 4
	,kAsiIS_COLUMN_DOMAIN_USAGE		= 5
	,kAsiIS_COLUMN_PRIVILEGES		= 6
	,kAsiIS_COLUMNS					= 7
	,kAsiIS_CONSTRAINT_COLUMN_USAGE	= 8
	,kAsiIS_CONSTRAINT_TABLE_USAGE	= 9
	,kAsiIS_FOREIGN_KEYS			= 10
	,kAsiIS_KEY_COLUMN_USAGE		= 11
	,kAsiIS_PRIMARY_KEYS			= 12
	,kAsiIS_PROCEDURE_COLUMNS		= 13
	,kAsiIS_PROCEDURE_PARAMETERS   	= 14
	,kAsiIS_PROCEDURES             	= 15
	,kAsiIS_REFERENTIAL_CONSTRAINTS	= 16
	,kAsiIS_SCHEMATA               	= 17
	,kAsiIS_SQL_LANGUAGES          	= 18
	,kAsiIS_TABLE_CONSTRAINTS      	= 19
	,kAsiIS_TABLE_PRIVILEGES       	= 20
	,kAsiIS_TABLES                 	= 21
	,kAsiIS_TRANSLATIONS           	= 22
	,kAsiIS_USAGE_PRIVILEGES       	= 23
	,kAsiIS_VIEW_COLUMN_USAGE      	= 24
	,kAsiIS_VIEW_TABLE_USAGE       	= 25
	,kAsiIS_VIEWS                  	= 26

	// Physical
	,kAsiIS_CATALOGS				= 27
	,kAsiIS_INDEXES					= 28
	,kAsiIS_PROVIDER_TYPES			= 29
	,kAsiIS_STATISTICS				= 30

} EAsiInfSchTab;


/* Datasource type */
typedef enum {
    kAsiDSSOURCETYPE_BOTH       = 0,
    kAsiDSSOURCETYPE_DATASOURCE = 1,
    kAsiDSSOURCETYPE_ENUMERATOR = 2
} EAsiDataSourceType;




/* //////////////////////////////////////////////////////////////// */
/* */
/* Default, minimal and maximal setting for ASI data */
/*  */
#define MaxCharLength             256
#define DefaultCharLength         1

#define MaxBinaryLength           (256*8)
#define DefaultBinaryLength       1

#define SmallIntPrecision         6

#define IntegerPrecision          10

#define MaxNumericPrecision       32
#define MaxNumericScale           MaxNumericPrecision
#define DefaultNumericPrecision   18
#define DefaultNumericScale       0

#define MaxDecimalPrecision       32
#define MaxDecimalScale           MaxDecimalPrecision
#define DefaultDecimalPrecision   18
#define DefaultDecimalScale       0

#define MaxFloatPrecision         32
#define DefaultFloatPrecision     16

#define RealPrecision             32

#define DoublePrecision           64

#define MaxLeadingFieldPrec       6    /* Interval  */
#define MaxFracSecondPrec         8
#define MinLeadingFieldPrec       2
#define MinFracSecondPrec         0
#define DefaultLeadingFieldPrec   4
#define DefaultFracSecondPrec     0

#define MaxTimePrecision          6
#define DefaultTimePrecision      0

#define MaxTimeStampPrecision     6
#define DefaultTimeStampPrecision 6

#define MaxIdentLength            256

#define DefaultPointDimension     3


/* //////////////////////////////////////////////////////////////// */
/* */
/* Implementation defined data definition */
/* */
#define AsiImplDefFxdMin          0000 /* 0000 - 1999 reserved for ASI */
#define AsiImplDefFxdUser         2000 /* 2000 - 3999 avail for User */
#define AsiImplDefFxdMax          3999
#define AsiImplDefRawMin          4000 /* 4000 - 5999 reserved for ASI */
#define AsiImplDefRawUser         6000 /* 6000 - 8000 avail for User */
#define AsiImplDefRawMax          8000


/* //////////////////////////////////////////////////////////////////// */
/* */
/* Condition information item names */
/* */
typedef enum {                /* Type of data in buffer */
    kAsiConditionNumber = 1,  /* Integer */
    kAsiMessageLength,        /* Integer */
    kAsiMessageOctetLength,   /* Integer */

    kAsiHRESULT          =  4,/* HRESULT */

    kAsiConditionStrings = 20,
    kAsiReturnedSQLSTATE,     /* Char */
    kAsiClassOrigin,          /* Char */
    kAsiSubClassOrigin,       /* Char */
    kAsiServerName,           /* Char */
    kAsiConnectionName,       /* Char */
    kAsiConstraintCatalog,    /* Char */
    kAsiConstraintSchema,     /* Char */
    kAsiConstraintName,       /* Char */
    kAsiCatalogName,          /* Char */
    kAsiSchemaName,           /* Char */
    kAsiTableName,            /* Char */
    kAsiColumnName,           /* Char */
    kAsiCursorName,           /* Char */
    kAsiMessageText,          /* Char */

    kAsiInterface        = 35 /*IID*/  

} EAsiDiag;

typedef unsigned int AsiDiag;
#define MinUserDefDiagParam         0x0400

/* //////////////////////////////////////////////////////////////////// */
/* */
/* Exception conditions used in ASI. */
/* */
typedef enum {
    kAsiErrUndefined = -1

   ,kAsiNoError = 0   /* Successful completion */
   ,kAsiOKAY = 0


   /* The following error codes are for standard SQLSTATE values */
   /* */
   ,kAsiSQLWARN =           0x0100  /* warning  */
   ,kAsiSQLWARNCUROP                /* cursor operation conflict  */
   ,kAsiSQLWARNDISC                 /* disconnect error  */
   ,kAsiSQLNULLSET                  /* null value eliminated in set function  */
   ,kAsiSQLWARNRTRUNC               /* string data, right truncation  */
   ,kAsiSQLWARNINSUFDESC            /* insufficient item descriptor areas  */
   ,kAsiSQLWARNREVOKE               /* privilege not revoked  */
   ,kAsiSQLWARNGRANT                /* privilege not granted  */
   ,kAsiSQLWARNBITPAD               /* implicit zero-bit padding  */
   ,kAsiSQLWARNLONGCOND             /* search condition too long for information schema  */
   ,kAsiSQLWARNLONGEXPR             /* query expression too long for information schema  */

   ,kAsiSQLNODATA =         0x0200  /* no data  */
   ,kAsiSQLNDSearchStm              /* rows were not modified by searched statement */
   ,kAsiSQLNDSingSelect             /* row doesn't match single select */
   ,kAsiSQLNDEOS                    /* fetch: end of selection set */
   ,kAsiSQLNDTOS                    /* fetch: top of selection set */

   ,kAsiSQLDYN    =         0x0700  /* dynamic SQL error  */
   ,kAsiSQLDYNUPMISMATCH            /* using clause does not match dynamic parameter specification  */
   ,kAsiSQLDYNUTMISMATCH            /* using clause does not match target specification  */
   ,kAsiSQLDYNEXECUR                /* cursor specification cannot be executed  */
   ,kAsiSQLDYNUSINGMIS              /* using clause required for dynamic parameter  */
   ,kAsiSQLDYNNOTCURSOR             /* prepared statement not a cursor specification  */
   ,kAsiSQLDYNAVIOLATION            /* restricted data type attribute violation  */
   ,kAsiSQLDYNINTOMIS               /* using clause required for result fields  */
   ,kAsiSQLDYNINVDSCCOUN            /* invalid descriptor count  */
   ,kAsiSQLDYNINVDSCIDX             /* invalid descriptor index  */
   ,kAsiSQLDYNNOTPREPARED           /* statement was not prepared */
   ,kAsiSQLDYNAlreadyBound          /* columns were already bound with host buffers */
   
   ,kAsiSQLCON     =        0x0800  /* connection exception  */
   ,kAsiSQLCONCLIENT                /* SQL-client unable to establish SQL- connection  */
   ,kAsiSQLCONNAMEUSE               /* connection name in use  */
   ,kAsiSQLCONNOTEXIST              /* connection does not exist */
   ,kAsiSQLCONSERVER                /* SQL-server rejected establishment of SQL-connection  */
   ,kAsiSQLCONOPENOBJS				/* open objects associated with session */
   ,kAsiSQLCONFAILURE               /* connection failure    */
   ,kAsiSQLCONTRANS                 /* transaction resolution unknown  */
                                    
   ,kAsiSQLCURCONFLICT =    0x0900  /* cursor operation conflict   */
   
   ,kAsiSQLNOTSUPPORTED =   0x0A00  /* feature not supported  */
   ,kAsiSQLMULTRANS                 /* multiple environment transaction  */
   
   ,kAsiSQLCARVIOLATION  =  0x2100  /* cardinality violation  */
   
   ,kAsiSQLDATA          =  0x2200  /* data exception  */
   ,kAsiSQLDATASRTRUN               /* string data, right truncation  */
   ,kAsiSQLDATANOIND                /* null value, no indicator parameter */ 
   ,kAsiSQLDATANUMRANGE             /* numeric value out of range  */
   ,kAsiSQLDATANUMTRUNC             /* decimal fractional part was rounded */
   ,kAsiSQLDATAASSIGN               /* error in assignment  */
   ,kAsiSQLDATAFETSEQ               /* invalid fetch sequence */
   ,kAsiSQLDATADTFORMAT             /* invalid datetime format */
   ,kAsiSQLDATADTOVF                /* datetime field overflow */
   ,kAsiSQLDATATZDISP               /* invalid time zone displacement value  */
   ,kAsiSQLDATA10                   /* Undefined */
   ,kAsiSQLDATASUBSTRERR            /* substring error  */
   ,kAsiSQLDATAZERODIV              /* division by zero */
   ,kAsiSQLDATA13                   /* Undefined */
   ,kAsiSQLDATAINFORMAT             /* invalid interval format (ASI extra) */
   ,kAsiSQLINTEROVF                 /* interval field overflow  */
   ,kAsiSQLColRO                    /* column is read only */
   ,kAsiSQLDATA17                   /* Undefined */
   ,kAsiSQLDATACHARCAST             /* invalid character value for cast */
   ,kAsiSQLDATAESCCHAR              /* invalid escape character  */
   ,kAsiSQLDATA20                   /* Undefined */
   ,kAsiSQLDATACHAR                 /* character not in repertoire */
   ,kAsiSQLDATAINDIVF               /* indicator overflow  */
   ,kAsiSQLDATAPARVAL               /* invalid parameter value  */
   ,kAsiSQLDATACSTR                 /* unterminated C string  */
   ,kAsiSQLDATAESCSEQ               /* invalid escape sequence  */
   ,kAsiSQLDATASTRLEN               /* string data, length mismatch  */
   ,kAsiSQLDATATRIMERR              /* trim error  */
   ,kAsiSQLDATADTUNDF               /* datetime field underflow */

   ,kAsiSQLINTCONSTR     =  0x2300  /* integrity constraint violation  */
   
   ,kAsiSQLINVCURSTATE   =  0x2400  /* invalid cursor state  */
   ,kAsiSQLICSDeallocStm =  0x2401  /* deallocate statement associated with open cursor */
   ,kAsiSQLICSClose      =  0x2402  /* cursor is in close state */
   ,kAsiSQLICSNotScroll  =  0x2403  /* can only fetch next in non-scroll cursor */
   ,kAsiSQLICSReadOnly   =  0x2404  /* cursor is read only */
   ,kAsiSQLICSNoCurRow   =  0x2405  /* cursor is not positioned on row */
   ,kAsiSQLICSOpen       =  0x2406  /* cursor is in open state */
   
   ,kAsiSQLINVTRSTATE    =  0x2500  /* invalid transaction state  */
   ,kAsiSQLITSActive     =  0x2501  /* disconnect while transaction is active */
   ,kAsiSQLITSNotActive  =  0x2502  /* transaction is in-active */
   ,kAsiSQLITSSetTrans   =  0x2503  /* set transaction (transaction is active) */
   ,kAsiSQLINVTSTabRO    =  0x2504  /* Table is read only */
   ,kAsiSQLINVTSTrsRO    =  0x2505  /* Transaction is read only */
   ,kAsiSQLINVTSAuth     =  0x2506  /* Set authorization id but transaction is active */

   
   ,kAsiSQLINVSTMNAME    =  0x2600  /* invalid SQL statement name  */
   
   ,kAsiSQLTRIGCHNVIOL   =  0x2700  /* triggered data change violation  */
   
   ,kAsiSQLINVAUTHID     =  0x2800  /* invalid authorization specification  */
   
   ,kAsiSQLDIRSYNACS     =  0x2A00  /* syntax error or access rule violation in direct SQL statement  */
   
   ,kAsiSQLPRIVEXIST     =  0x2B00  /* dependent privilege descriptor still exist  */
   
   ,kAsiSQLINVCHARSET    =  0x2C00  /* invalid character set name    */
   
   ,kAsiSQLINVTRTERM     =  0x2D00  /* invalid transaction termination     */
   
   ,kAsiSQLINVDESC       =  0x3300  /* invalid SQL descriptor name  */
   
   ,kAsiSQLINVCURNAME    =  0x3400  /* invalid cursor name  */
   
   ,kAsiSQLINVCONDNUM    =  0x3500  /* invalid condition number  */
   
   ,kAsiSQLDYNSYNACS     =  0x3700  /* syntax error or access rule violation in dynamic SQL statement  */
    /* ASI syntax errors */
   ,kAsiErSynWrStr                  /* Wrong string format */
   ,kAsiErSynLongStr                /* String is too long (character, binary) */
   ,kAsiErSynMisQuot                /* Missing right quotas  */
   ,kAsiErSynHexDigit               /* Wrong Hexadecimal digit */
   ,kAsiErSynBinDigit               /* Wrong Binary digit */
   ,kAsiErSynInterval               /* Wrong interval string */
   ,kAsiErSynTypeMatch              /* Data types mismatch  */
   ,kAsiErSynCollate                /* Invalid collate clause */
   ,kAsiErSynWrTimeZone             /* Misleading time zone specification  */
   ,kAsiErSynMisZone                /* Missing ZONE keyword   */
   ,kAsiErSynNotTimeZone            /* Not a time zone interval */
   ,kAsiErSynUnbalPar               /* Unbalance parenthesis */
   ,kAsiErSynExprEx                 /* Expression expected */
   ,kAsiErSynMisCol                 /* Missing column specification  */
   ,kAsiErSynWrColSpec              /* Wrong column specification  */
   ,kAsiErSynNoLeftPar              /* Left parenthesis expected  */
   ,kAsiErSynMlStar                 /* Misleading star symbol */
   ,kAsiErSynMisIn                  /* Expected IN keyword */
   ,kAsiErSynWrDTField              /* Wrong datetime field for extraction */
   ,kAsiErSynMisFrom                /* Expected FROM keyword */
   ,kAsiErSynMisUsing               /* Expected USING keyword */
   ,kAsiErSynFOUorTR                /* Form-of-use or translation name expected */
   ,kAsiErSynMisTimePrec            /* Missing time precision */
   ,kAsiErSynWrCollName             /* Wrong collation name */
   ,kAsiErSynWrSetSq                /* Set function or subquery can't be set function argument */
   ,kAsiErSynNoComma                /* Missing comma */
   ,kAsiErSynNoWhen                 /* Missing when clause */
   ,kAsiErSynMisThen                /* Missing then clause */
   ,kAsiErSynMisEnd                 /* Missing END  */
   ,kAsiErSynWrNot                  /* Wrong usage of NOT  */
   ,kAsiErSynNull                   /* NULL expected  */
   ,kAsiErSynCompare                /* Compare operator expected  */
   ,kAsiErSynWrComma                /* Wrong comma position */
   ,kAsiErSynMask                   /* Mask should be of character type */
   ,kAsiErSynEsc                    /* Escape character expected  */
   ,kAsiErSynMisSq                  /* Subquery expected */
   ,kAsiErSynAndBet                 /* AND was missed in BETWEEN predicate  */
   ,kAsiErSynNotJoin                /* Not a joined table */
   ,kAsiErSynMisJoin                /* Missing JOIN keyword */
   ,kAsiErSynWrNatural              /* Union join can't be natural union  */
   ,kAsiErSynMisJoinSpec            /* Misleading join specification */
   ,kAsiErSynMisCorName             /* Missing correlation name  */
   ,kAsiErSynWrTabSpec              /* Wrong table specification  */
   ,kAsiErSynEmptyList              /* List of columns is empty  */
   ,kAsiErSynNoJoinSpec             /* Missing join specification */
   ,kAsiErSynMisName                /* Missing database object name  */
   ,kAsiErSynMisQueryPrimary        /* Missing query primary */
   ,kAsiErSynEEEEEEEEEEEEEEE        /* Not Used              */
   ,kAsiErSynNotJoinedTable         /* Not a joined table */
   ,kAsiErSynMisTabValConstr        /* Missing table value constructor */
   ,kAsiErSynMisSelect              /* Missing SELECT keyword */
   ,kAsiErSynMisColName             /* Missing column name */
   ,kAsiErSynMisGroup               /* Selection list contains set functions and columns  */
                                    /* references but GROUP BY clause was missed  */
   ,kAsiErSynNotScalar              /* Scalar expression expected */
   ,kAsiErSynElementInParen         /* Element can't be in parenthesis */
   ,kAsiErSynOvrlDegree             /* Wrong overlaps operand degree  */
   ,kAsiErSynDegreeViolation        /* Degree violation */
   ,kAsiErSynMisAs                  /* Missing keyword AS  */
   ,kAsiErSynWrongCast              /* Wrong cast */
   ,kAsiErSynInvalidDomain          /* Invalid domain name */
   ,kAsiErSynCharExpected           /* CHAR expected */
   ,kAsiErSynTypeExpected           /* Data type specification expected  */
   ,kAsiErSynWrongPrecLength        /* Wrong precision or length */
   ,kAsiErSynScaleExpected          /* Scale expected */
   ,kAsiErSynWrongScale             /* Wrong scale */
   ,kAsiErSynWithTimeZoneExpected   /* Wrong WITH TIME ZONE sentence */
   ,kAsiErSynNoVarLength            /* Missing varying length */
   ,kAsiErSynOrderByExpected        /* ORDER BY expected */
   ,kAsiErSynReadOnlyExpected       /* READ ONLY expected */
   ,kAsiErSynWrongSortKey           /* Wrong sort key */
   ,kAsiErSynEmptySortList          /* Empty sort list */
   ,kAsiErSynWrongToken             /* Wrong token was met  */
   ,kAsiErSynWrTabName              /* Wrong table name */
   ,kAsiErSynMisOf                  /* Missing keyword OF  */
   ,kAsiErSynMisCursorName          /* Missing cursor name */
   ,kAsiErSynMisSet                 /* Missing keyword SET */
   ,kAsiErSynMisBecome              /* = expected in UPDATE set clause */
   ,kAsiErSynMisInto                /* Missing INTO keyword  */
   ,kAsiErSynMisValues              /* Missing VALUES keyword  */
   ,kAsiErSynMisTarget              /* Missing target specification */
   ,kAsiErSynDubTransMode           /* Diplicate definition of transaction mode */
   ,kAsiErSynMisSize                /* Missing SIZE keyword */
   ,kAsiErSynWrDiagSize             /* Wrong diagnostics area size */
   ,kAsiErSynMisTransMode           /* Transaction modes are not specified */
   ,kAsiErSynInCompLevelMode        /* Incompatible transaction access mode and isolation level */
   ,kAsiErSynWrConstrChkMode        /* Wrong constraint checking mode */
   ,kAsiErSynWrConstrName           /* Wrong constraint name */
   ,kAsiErSynMisRead                /* Missing READ keyword  */
   ,kAsiErSynMisAuthorization       /* Missing AUTHORIZATION keyword */
   ,kAsiErSynMisTemporary           /* Missing TEMPORARY keyword */
   ,kAsiErSynMisTable               /* Missing TABLE keyword */
   ,kAsiErSynOnCommit               /* Shall be ON COMMIT */
   ,kAsiErSynNotTemporary           /* Commit behaviour only for temporary table */
   ,kAsiErSynWrComBehaviour         /* Wrong commit behaviour */
   ,kAsiErSynMisRows                /* Missing ROWS keyword */
   ,kAsiErSynMisTableName           /* Missing table name */
   ,kAsiErSynWrCheckTime            /* Wrong constraint time specification */
   ,kAsiErSynMisDeferrable          /* Keyword DEFERRABLE expected */
   ,kAsiErSynWrNotDefer             /* Initialy deferred constraint can't be not deferrable */
   ,kAsiErSynNotNull                /* Not Null shall be specified for constraint */
   ,kAsiErSynPrimaryKey             /* Primary key shall be specified for constraint */
   ,kAsiErSynMisConstr              /* Missing constraint specification */
   ,kAsiErSynMisRefSpec             /* Missing references specification */
   ,kAsiErSynMisRefTable            /* Referenced table and columns expected */
   ,kAsiErSynWrMatchType            /* Wrong match type of constraint  */
   ,kAsiErSynSetAction              /* Set triggered action expected */
   ,kAsiErSynDuplAction             /* Duplicated triggered action specification */
   ,kAsiErSynMisTrigRule            /* Missing triggered rule    */
   ,kAsiErSynForeignKey             /* Foreign key shall be specified for constraint */
   ,kAsiErSynNoColDef               /* No column definitions */
   ,kAsiErSynMisAlterAction         /* Missing alter action */
   ,kAsiErSynDropDefault            /* Drop default action expected */
   ,kAsiErSynSetDefault             /* Set default action expected */
   ,kAsiErSynMisDropBehaviour       /* Missing drop behaviour */
   ,kAsiErSynNotCheckConstr         /* Domain constraint shall be check constraint */
   ,kAsiErSynMisCheckOption         /* CHECK OPTION expected */
   ,kAsiErSynMisCharSet             /* CHARACTER SET expected */
   ,kAsiErSynMisCharSetSource       /* Character set source expected */
   ,kAsiErSynCharSetExp             /* Character set expected */
   ,kAsiErSynPadAttr                /* Pad attribute expected */
   ,kAsiErSynMisTransName           /* Missing translation name */
   ,kAsiErSynCollationExp           /* Collation expected */
   ,kAsiErSynMisExternColl          /* Missing external collation */
   ,kAsiErSynMisTo                  /* Missing TO keyword  */
   ,kAsiErSynMisOn                  /* Missing ON keyword  */
   ,kAsiErSynMisGrantOption         /* GRANT OPTION expected */
   ,kAsiErSynMisFor                 /* Missing FOR keyword  */
   ,kAsiErSynMisObjectName          /* Missing object name */
   ,kAsiErSynMisGrantee             /* Missing grantee */
   ,kAsiErSynAllPrivileges          /* ALL PRIVILEGES expected */
   ,kAsiErSynMisIndex               /* INDEX keyword expected */
   ,kAsiErSynAuthorExpected         /* Authorization identifier expected */
   ,kAsiSynErDublColumnName         /* Duplicate column name */
   ,kAsiSynErAmbTabRef              /* Ambigious table reference */
   ,kAsiSynErTableNotFound          /* Table name is not found (+ table name) */
   ,kAsiSynErColumnNotFound         /* Column name is not found (+ column name) */
   ,kAsiSynErAmbColRef              /* Ambigious column reference (+ column name) */
   ,kAsiSynErWrongParameterUsage    /* Parameter was specified in wrong place */
   ,kAsiSynErLocalCol               /* Column shall be local reference */
   ,kAsiSynErOuterCol               /* Column shall be outer reference */
   ,kAsiSynErDuplDistinct           /* Duplicate distinct in query specification */
   ,kAsiSynErArgNotColumn           /* Distinct argument shall be column reference */
   ,kAsiSynErNoCorrColumns          /* Corresponding column were not found */
   ,kAsiSynErWrongCorrColumn        /* Wrong corresponding column name */
   ,kAsiSynErMustBeGroupCol         /* Column reference must be a group column */
   ,kAsiErSynMisLeadSetFunc         /* Misleading set function usage */
   ,kAsiErSynWrongEscLength         /* Escape character must be 1 symbol length */
   ,kAsiErSynSimpleValue            /* Should be simple value */
   ,kAsiErSynInvOrderSpec           /* Invalid order specification */
   ,kAsiErSynMustBeOnlyCol          /* Column shall be the single outer reference */
   ,kAsiErSynCursorNotFound         /* Cursor name not found */
   ,kAsiErSynUpdateColDupl          /* Column name duplicates in the set clause */
   ,kAsiErSynDefaultUse             /* DEFAULT shall be specified in INSERT  */
   ,kAsiErSynWrColInsert            /* Wrong column name in insert list */
   ,kAsiErSynNotCastable            /* Expression can't be casted to the specified type */
   ,kAsiErSynMisDefValue            /* Missing default value */
   ,kAsiErSynMisServerName          /* Missing server name */
   ,kAsiErSynMisCorNameForRemote    /* Missing correlation name for remote table */
   ,kAsiErSynWrongForUpdateColSpec  /* Wrong column name in FOR UPDATE specification */
   ,kAsiErSynNotUpdateCol           /* Not updatable column */
   ,kAsiErSynTransMode              /* Invalid transaction mode specification */
   ,kAsiErSynMisLevel               /* Missing LEVEL keyword */
   ,kAsiErSynUncommComm             /* Uncommitted/committed expected */
   ,kAsiErSynDubIsoLevel            /* Duplicated specification of isolation level */
   ,kAsiErSynDubDiagSize            /* Duplicated diagnostics size specification */
   ,kAsiErSynMisIsoLevel            /* missing isolation level specification */
   ,kAsiErSynCharSetUsage           /* character set usage */
   ,kAsiErSynCollatingSeq           /* collating sequence invalid syntax */
   ,kAsiErSynNotCharCollate         /* collation can be specified only for character data */
   ,kAsiErSynColCharSetMisMatch     /* character set doesn't has specified collation */
   ,kAsiErSynDuplJoinCol            /* Duplicate column name in natural or named column join */
   ,kAsiSynErCorrJoinColNotFound    /* common join columns not found */
   ,kAsiSynErFunctionNotExists      /* function doesn't exist */
   ,kAsiSynErNoMatchFunction        /* no implemetation-defined function match argument list */
   ,kAsiSynErWrongBoolFuncUsage     /* wrong boolean function usage */
   ,kAsiSynErWrongValueFuncUsage    /* wrong value function usage */


   ,kAsiSQLAMBCURSOR     =  0x3C00  /* ambiguous cursor name  */
   
   ,kAsiSQLINVCATNAME    =  0x3D00  /* invalid catalog name     */
   
   ,kAsiSQLINVSCHNAME    =  0x3F00  /* invalid schema name      */
   
   ,kAsiSQLTR            =  0x4000  /* transaction rollback  */
   ,kAsiSQLTRINTEGRITY              /* integrity constrint violation      */
   ,kAsiSQLTRSER                    /* serialization failure   */
   ,kAsiSQLTRSTMCOMP                /* statement completition unknown  */
   
   ,kAsiSQLSYNACS        =  0x4200  /* access rule violation (permission denied) */
   
   ,kAsiSQLCHECKOPT      =  0x4400  /* with check option violation  */
   
   ,kAsiSQLRDA           =  0x8000  /* Remote Database Access   */
   

    /* Generic ASI excpetions */
    /*                     */
   ,kAsiEXCP             =  0xA000  /* ASI Exception  */
   ,kAsiEXCPINIT                    /* unable to initialize ASI  */
   ,kAsiEXCPTERM                    /* error during ASI termination  */
   ,kAsiEXCPDUPLINIT                /* ASI was already initialized */
   ,kAsiEXCPNOTINIT                 /* ASI was not initialized */
   ,kAsiEXCPBADINI                  /* initialization file has errors or is corrupted */
   ,kAsiEXCPWRONGENV                /* environment is not defined in AST configuration */
   ,kAsiEXCPWRENVPAR                /* invalid environment parameter in AST configuration */
   ,kAsiNoMemory                    /* insufficient memory             */
   ,kAsiErStkOvrFlw                 /* Stack overflow  */
   ,kAsiErStkUnrFlw                 /* Stack underflow */
   ,kAsiInvalidParam                /* Invalid parameter */
   ,kAsiInternalError               /* Iternal error  */
   ,kAsiFunctionNotSupported        /* Function overflow */
   ,kAsiTryTableOverflow
   ,kAsiOperationNotSupported
   ,kAsiCannotOpenTable
   ,kAsiOutOfRange
   ,kAsiInvalidUcObject
   ,kAsiInvalidDDAObject            /* Invalid DDA object */
   ,kAsiErrEofFound                 /* EOF found */
   ,kAsiErrFileLocked               /* File was locked during the timeout period */
   ,kAsiRecLocked                   /* Record is locked */
   ,kAsiTableLocked                 /* Table is locked */
   ,kAsiNativePrepare               /* Native statement cannot be prepared */
   ,kAsiNativeExecute               /* Native statement cannot be executed */
   ,kAsiRemoteTabModification       /* Remote table has read only access */
   ,kAsiInterDBExecution            /* Can't execute interdatabase statement */
   ,kAsiErrCodePageNotDefined       /* Code page not supported */
   ,kAsiErrCodePageFileNotFound     /* Code page not supported */
   ,kAsiErrCodePageFormat           /* Corrupted code page data */
   ,kAsiErrCollationNotDefined      /* Collation not supported */
   ,kAsiErrCollationFileNotFound    /* Collation not supported */
   ,kAsiErrCollationFormat          /* Corrupted collation data */
   ,kAsiErrAsilocNotFound           /* Cannot find asiloc.xmx */

    /* Interprocess Communication Exceptions */
    /*                                   */
   ,kAsiErrDrv          = 0xB000    /* IPC exceptions */
   ,kAsiErrOpenDrv                  /* OLEDB provider not registered */
   ,kAsiErrPathNotFound             /* Path not found */
   ,kAsiErrProvNotSpecified         /* OLEDB Provider not specified */
   ,kAsiErrToManyFileOpen           /* Too many open files */
   ,kAsiErrAccessDenied             /* Access denied */
   ,kAsiErrFileHandle               /* Invalid file handle */
   ,kAsiErrSrvNotReg				/* Services not registered */
   ,kAsiErrCannotRegSrv				/* Unable to register services */
   ,kAsiErrCannotFindSrv            /* csp.dll not found */
   ,kAsiErrNoRegEntryPoint 			/* Server doesn't have DllRegisterServer entry point */
   ,kAsiErrCannotLoadSrvDll         /* Cannot load services DLL */
   ,kAsiErrOutPhysicalMemory        /* Out of physical memory */
   ,kAsiErrOutSwapSpace             /* Out of swap space */
   ,kAsiErrOLEDB20NotInstalled      /* OLEDB 2.0 not installed */
   ,kAsiErrOLENotInit				/* Cannot initialize OLE or one of its components */
   ,kAsiErrNoVirtualMemory          /* Insufficient virtual memory space */
   ,kAsiErrNoConvMemory             /* Insufficient conventional memory space */
   ,kAsiErrMDLNotFound              /* MDL file not found */
   ,kAsiErrOpenIni                  /* Cannot get AST configuration information */
   ,kAsiErrNoEnv                    /* Environment name not specified */
   ,kAsiErrIncompEnv                /* Incompatible environment */
   ,kAsiErrNoPath                   /* Driver path and name was not specified */
   ,kAsiErrLostConnection           /* Server died, connection lost */
   ,kAsiErrToManyDrivers            /* Too many driver loaded */
   ,kAsiErrInvalidName              /* Driver name is invalid */
   ,kAsiErrNotAsiDrv                /* Program referenced in AST configuration
                                    /* is not an ASI driver */
   ,kAsiErrOsEnv                    /* Bad format for OS environment */
   ,kAsiErrDrvInit                  /* Error found durring driver initialization */
   ,kAsiErrDrvThunk                 /* Trap in DBMS communication */
   ,kAsiErrComBuf                   /* Cannot create communication buffer */
   ,kAsiErrBlockByTSR               /* User has loaded TSR from AutoCAD shell command */
   ,kAsiErrNoDrv                    /* Driver not found in AST configuration */
   ,kAsiErrMemoryAccess             /* Memory access violatation */
   ,kAsiErrOS                       /* OS error */
   ,kAsiErrDrvOld                   /* Old driver's version */
   
   ,kAsiErrDBMSServer =  0xCF00     /* Exception raised by DBMS driver  */
   ,kAsiErrHRESULT                  /* Generate HRESULT description     */
   
} EAsiError;

typedef unsigned int AsiError;

#define MinUserDefErrorCode         0xE000

#pragma pack (pop)

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif /* ASI_ASICONST_H */
/*EOF*/
