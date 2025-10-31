//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//    Name: aseconst.h
//
//    Description:
//		  This file contains the ASE constant definition

#ifndef _ASECONST_H
#define _ASECONST_H

/***************************************************************************/
/* DEFINES */
/***************************************************************************/

#pragma pack(push, 8)

/* The Database Object attribute masks */
#define        ASE_DO_CURRENT       0x01  /* The DOis the current */
#define        ASE_DO_REG           0x02  /* The DO is registered */
#define        ASE_DO_EXIST         0x04  /* The DO exists in the SQL database*/
#define        ASE_DO_CON           0x08  /* The DO belong to the connected env*/
#define        ASE_DO_UNKNOWN       0x10  /* Can't check the DO existence  */
#define        ASE_DO_WRONGKEY      0x20  /* Some registered key columns */
                                          /* doesn't exist in the real table */
#define        ASE_DO_WRONGKEYTYPE  0x40  /* Some registered key columns */
                                          /* types, precisions and scales */
                                          /* differ from the ones, taken */
                                          /* from the real table.*/

/* NULL definition */
#ifndef NULL
#define NULL 0L
#endif /*NULL*/

/* The link and link selection predefined values */
#define        LINKID_NULL	 -1L
#define        LINKSELID_NULL	 -1L

/* TYPEDEFS */

typedef long     LinkSelID ;     /* The link selection identifier */
typedef LONG_PTR LinkID ;	     /* The link identifier */

/* The Link type codes */
typedef enum {
  kAseUnknownLinkType = 0,
  kAseEntityLink=1,  /* Ordinary Entity link */
  kAseDALink=2,	     /* DA (MText Label) link */
  kAseLeaderLink=3	     /* DA (Leader Label) link */
} EAseLinkType ;

/* The link attribute identification codes */
typedef enum  {
  /* Normal attributes */
  kAseAttrAll=0,	 /* All link attributes */
  kAseAttrId=1, 	 /* link identifier (valid in the one drawing session) */
  kAseAttrType=2,	 /* link type code */
  kAseAttrStatus=3,	 /* link status */
  kAseAttrEnt=4,	 /* entity name */
  kAseAttrName=5,	 /* Link Table Name */
  kAseAttrKeyValue=6,	 /* key value */
  kAseAttrDAColumns=7,	 /* the DA column names list (for DA link) */
  kAseAttrDAParms=8,	 /* the DA entity parameters (for DA link) */
  kAseAttrDAValues=9,	 /* the known DA entity values (for DA link) */
  kAseAttrXName=10,	 /* the Xref/Block name (for enclosed link) */
  kAseAttrReserved1=11,  /* internal reserved attribute */
  kAseAttrParKeyValue=12,/* partial key value */

  /* Extended attributes */
  kAseExtAttrTextCond=-1,/* text condition */
  kAseExtAttrEntities=-2,/* selection set name */
  kAseExtAttrDoPath=-3	 /* The Database Object Path */
} EAseLinkAttr;


/* Database Object Reference definition codes */
typedef enum {
  kAseUnknownNameCode=0, /* Unknown DO name code */
  kAseEnvCode=1,	     /* DataSource / Environment */
  kAseCatCode=2,	     /* Catalog */
  kAseSchemaCode=3,	     /* Schema */
  kAseTableCode=4,	     /* Table */
  kAseLpnCode=5,	     /* Link Path Name */
  kAsePathCode=6,	     /* Full path code */
  kAseDOCode=7, 	     /* DO path only */
  kAseSQLCode=8 	     /* SQL object path */
} EAseDoNameCode ;

/* ASE error code in the ASI error codes sequence */
#define eAseErrEntry   (MinUserDefErrorCode+1)

/* Detects whether or not the error entry contains ASE error data */
#define isAseErr(x)   (x == eAseErrEntry ? kAsiTrue : kAsiFalse)

/* Status of Ase Path. Set and get by CAsePath::GetStatus, CAsePath::SetStatus */
#define			ASEPATH_STAT_EMPTY		0		/* void */

/* Query and table are mutual exclusive */
#define			ASEPATH_STAT_TABLE		0x01 	/* Table */
#define			ASEPATH_STAT_QUERY		0x02 	/* Query */


/* The ASE error description codes */
typedef enum {

    eAseEDscUnknown = 0, /* Unknown error  */

    eAseEDscInternal = 1,  /* Internal ASE error. This code hasn't be assigned*/
               /* in the normal situation. It indicates about an */
               /* internally detected ASE bug. See EAseErrCodes. */

    eAseEDscAse = 2,	   /* Logical common error, see EAseErrCodes. */

    eAseEDscFile = 3,	   /* File I/O error, see ASI error diagnostic */

    eAseEDscAsi = 4,	   /* ASI error, see ASI error diagnostic */

    eAseEDscDb = 5,	   /* ASI group error qualificator, see EAseDbErrCodes */

    eAseEDscDwg = 6,	   /* Drawing error, see EAseDwgErrCodes for error codes */

    eAseEDscDlg = 7,	   /* Dialogue errors, see EAseDlgErrCodes for error codes */

    eAseEDscApi = 8,	   /* API errors, see EAseApiErrCodes for error codes */

    eAseEDscLink = 9	   /* Internal error with the Link Information,*/
               /* see EAseLinkErrCodes */
} EAseErrDsc ;

/* The common ASE error codes */
typedef enum {
    eAseErrUnknown=0,	   /* Unknown ASE error */
    eAseErrInternal=1,	   /* Internal ASE error, inconsistent call of the*/
               /* internal ASE functions.*/
    eAseErrMemory=2,	   /* No memory*/
    eAseErrInfo=3,	   /* Information message entry*/
    eAseErrMaxQty=4,	   /* The maximum quantity of the errors is exceded*/


    eAseErrNoReg=10,	      /* No one DO is registered*/
    eAseErrDoReg=11,	      /* The DO isn't registered*/
    eAseErrEnvNotConnected=12,	 /* Environment isn't connected*/
    eAseErrNoLpn=13,	      /* LPN isn't set*/
    eAseErrNoEnvName=14,      /* Environment name isn't specified*/
    eAseErrNoCatName=15,      /* Catalog name isn't specified*/
    eAseErrNoSchemaName=16,   /* Schema name isn't specified*/
    eAseErrNoTableName=17,    /* Table name isn't specified*/
    eAseErrLpnExist=18,       /* Link Path Name already exists*/
    eAseErrWrongKey=19,       /* Some of the key columns doesn't exist in table*/
    eAseErrWrongKeyType=20,   /* Wrong key column type is detected:*/
                  /* table structure was changed or BIT, BITVAR*/
                  /* column types are specified*/
    eAseErrNoSelEnts=21,      /* No one entity is selected*/
    eAseErrNoSelLinks=22,     /* No one links exist in the specified entities*/
    eAseErrNoSelDALinks=23,   /* No one links exist in the specified entities*/
    eAseErrNoDoLinks=24,      /* No one links to the DO is specified*/
    eAseErrDAUpd=25,	       /* Some of the DAs aren't updatable */

    eAseErrWrongDoName=26,  /* Invalid DO Name */
    eAseErrWrongResbuf=27,  /* Invalid resbuf*/
    eAseErrBadR12DOR=28,    /* Can't find the R13 terms for R12 DOR */
    eAseErrWrongLPN=29,     /* Invalid LPN */
    eAseErrWrongPath=30,    /* Invalid DO path */
    eAseErrLinkUpd=31,	    /* Some of the links aren't updatable */
    eAseErrLinkSynch=32,    /* The links(s) can't be synchronized */
    eAseErrLPSynch=33,	    /* The Link Path(s) can't be synchronized */
    eAseErrCharSet=34	    /* Can't find character set */

} EAseErrCodes ;

/* The File I/O related error codes */
typedef enum {
    eAseFileErrUnknown=400,   /* Unknown error*/
    eAseFileNotFound,	      /* File not found*/
    eAseFileErrOpen,	      /* Can't open file*/
    eAseFileErrRead,	      /* Read error*/
    eAseFileErrWrite	      /* Write error*/
} EAseFileErrCodes;


/* ASI group error codes*/
typedef enum {
    eAseDbErrUnknown=500,    /* Unknown ASE error*/
    eAseDbErrSyntax=501,     /* SQL syntax error*/
    eAseDbErrPrepare=502,    /* Can't prepare SQL statement*/
    eAseDbErrExecute=503,    /* Can't execute the statement*/
    eAseDbErrOpenCsr=504,    /* Can't open the cursor*/
    eAseDbErrEntry=505,      /* Wrong entry format in ASE_R12 section of*/
                 /* ASI.INI file*/
    eAseDbErrIni=506,	     /* Can't get ASI.INI file*/
    eAseDbErrFetch=507	     /* Can't fetch */
} EAseDbErrCodes ;

/* The AutoCAD drawing related codes*/
typedef enum {
   eAseDwgErrUnknown		 = 700,
   eAseDwgErrOpenReadEntity	 = 701,
/*
   Error openning entity for read. Object is to be opened for read as soon as
   any entity information, such as name of the layer, name of the parent block,
   XData ant etc. is requested.
*/
   eAseDwgErrTranslateHandle	 = 702,
/* Error translation entity handle, stored in the R12 Link, to the R13
   AcDbObjectId
*/
   eAseDwgErrAdsNameId		 = 703,
/*
   Can not convert AcDbObjectId to ads_name
*/
   eAseDwgErrXEDAppidNotFound	 = 704,
/*
   XData is corrupt - APPID group not found
*/
   eAseDwgErrXEDCorrupt 	 = 705,
/*
   R13 XData is corrupt
*/
   eAseDwgErrUpdateXED		 = 706,
/*
   Can not write/update XData.
*/
   eAseDwgErrParcingLink	 = 707,
/*
   Can not parce ASE Link XData
*/
   eAseDwgErrParcingLPN 	 = 708,
/*
   Can not parce ASE LPN XData
*/
   eAseDwgErrOpenWriteEntity	 = 709,
/*
   Can not open entity for write
*/
   eAseDwgErrConvertingLink	 = 710,
/*
   Error converting link to the result buffer
*/
   eAseDwgErrOpenBlockTable	 = 711,
/*
   Can not open block table
*/
   eAseDwgErrAppendBlockTable	 = 712,
/*
   Can not add DA block definition to the block table
*/
   eAseDwgErrAppendObjBlockTable = 713,
/*
   Can not append DA to the MODEL_SPACE or PAPER_SPACE sections
*/
   eAseDwgErrOpenBlock		 = 714,
/*
   Can not open Block Table Record
*/
   eAseDwgErrDelSelSet		 = 715,
/*
   Error releasing selection set
*/
   eAseDwgErrFilterSelSet	 = 716,
/*
   Error scanning block hierarchy
*/
   eAseDwgErrCreateLPNTable	 = 717,
/*
   Can not create LPN dictionary in the Drawing Database
*/
   eAseDwgErrFindLPNTable	 = 718,
/*
   Can not find LPN dictionary in the Drawing Database
*/
   eAseDwgErrFindAppid		 = 719,
/*
   Can not find ASE APPID
*/
   eAseDwgErrOpenLPNDict	 = 720,
/*
   Can not open LPN Dictionary
*/
   eAseDwgErrAddEntry		 = 721,
/*
   Can not add entry to the LPN dictionary
*/
   eAseDwgErrRemoveEntry	 = 722,
/*
   Can not remove entry from the LPN dictionary
*/
   eAseDwgErrUnexpSymb		 = 723,
/*
   Unexpected symbol in ASE XData found. XData is corrupted.
*/
   eAseDwgErrDwgInit		 = 724,
/*
   Can not initialize Drawing Subsystem
*/
   eAseDwgErrBlockIterator	 = 725,
/*
   Can not open Block Table Record iterator
*/
   eAseDwgErrTransOpen		 = 726,
/*
   Previous drawing transaction is not closed
*/
   eAseDwgErrTransClose 	 = 727,
/*
   Current Drawing transaction has not been opened
*/
   eAseDwgErrGrips		 = 728,
/*
   Can not store selection set in the AutoCAD via ads_sssetfirst() function.
   The error can accure in ASEROWS and ASESELECT commands
*/
   eAseDwgErrFindBlock		 = 729,
/*
   Block not found in the Block Table
*/
   eAseDwgErrOpenRegapTable	 = 730,
/*
   Can not open AutoCAD REGAPP table. This operation is to be fulfilled as
   soon as ASE information should be stored in the drawing for the first
   time in the ASE session.
*/
   eAseDwgErrRegisterAppid	 = 731,
/*
   Can not register ASE APPID. APPID should be registered before ASE
   information should be stored in the drawing for the first time in the
   ASE session.
*/
   eAseDwgErrInitObject 	 = 732,
/*
   Can not initialize CAseDEntity object
*/
   eAseDwgErrAddLink		 = 733,
/*
   Can not write link in the drawing
*/
   eAseDwgErrAddLPN		 = 734,
/*
   Can not write LPN in the drawing
*/
   eAseDwgErrDelLink		 = 735,
/*
   Can not delete link from the drawing
*/
   eAseDwgErrDelLPN		 = 736,
/*
   Can not delet LPN from the drawing
*/
   eAseDwgErrUpdLink		 = 737,
/*
   Can not update link in the drawing
*/
   eAseDwgErrUpdLPN		 = 738,
/*
   Can not update LPN in the drawing
*/
   eAseDwgErrDeleteObj		 = 739,
/*
   Can not delete DA object from the drawing
*/
   eAseDwgErrCorruptDA		 = 740,
/*
   Can not read DA column values from DA block attributes
*/
   eAseDwgErrErasedObj		 = 741,
/*
   Can not open object	- it has been erased
*/
   eAseDwgErrOpenNotify 	 = 742,
/*
   Object can not be updated - it is opened for notify
*/
   eAseDwgErrOpenUndo		 = 743,
/*
   Object can not be updated - it is opened for undo
*/
   eAseDwgErrOpenWrite		 = 744,
/*
   Object can not be updated - it is opened for write
*/
   eAseDwgErrOpenRead		 = 744,
/*
   Object can not be updated - it is opened for read
   */
   eAseDwgErrOpenXref		 = 745,
/*
   Object can not be updated - it is object from XRef
*/
   eAseDwgErrOpenLocked 	 = 746,
/*
   Object can not be updated - it is on the locked layer
*/
   eAseDwgErrDelR12DOMesh	 = 747,
/*
   Can not delete R12 DO Mesh
*/
   eAseDwgErrDelR12LinkMesh	 = 748,
/*
   Can not delete R12 Link Mesh
*/
   eAseDwgErrReadLTypeTable	 = 749,
/*
   Can not read line style table
*/
   eAseDwgErrReadLayerTable	 = 750,
/*
   Can not read layer table
*/
   eAseDwgErrReadStyleTable	    = 751,
/*
   Can not read style table
*/
   eAseDwgErrOpenLPNEntry	 = 752,
/*
   Can not open LPN dictionary entry
*/
   eAseDwgErrAppendBlkBlockHierarchy= 753,
/*
   Can not add block to ASE block hierarchy
*/
   eAseDwgErrAppendRefBlockHierarchy= 754,
/*
   Can not add block reference to ASE block hierarchy
*/
   eAseDwgErrFindBlkBlockHierarchy= 755,
/*
   Can not find block in ASE block hierarchy
*/
   eAseDwgErrDelBlkBlockHierarchy   = 756,
/*
   Can not delete block from ASE block hierarchy
*/
   eAseDwgErrInvR12Mesh 	 = 757,
/*
   Invalid R12 Polimesh found.
*/
   eAseDwgErrEOR		 = 758,
/*
   Unexpected End of ASE XData found
*/
   eAseDwgErrBraceExpected	 = 758,
/*
   Brace is mismatched in ASE XData
*/
   eAseDwgErrBlockName		 = 759,
/*
   Can not get name of the block  from AcDbBlockTableRecord
*/
   eAseDwgErrOpenLayer		 = 760
/*
   Can not open layer table record for update
*/
} EAseDwgErrCodes ;

/* The AutoCAD Dialog related codes */
typedef enum {
    eAseDlgErrUnknown=800,	/* Unknown ASE error */
    eAseDlgWrongObj,
    eAseDlgNoDsc,
    eAseDlgMakeKey,
    eAseDlgReadStyleTable
} EAseDlgErrCodes ;

/* ASE API related error codes */
typedef enum {
    eAseApiErrUnknown=900,     /* Unknown ASE error */
    eAseApiErrWrongData=901,	   /* Input data in the wrong format */
    eAseApiErrInitObj=902,	   /* The API class isn't initialized */
    eAseApiErrInitApp=903,	   /* Communication with ASE isn't extablished */
    eAseApiErrWrongAttr=904,	   /* Wrong link attribute code */
    eAseApiErrXmx=905,		   /* Can't load XMX file */
    eAseApiErrWrongFunc=906,	   /* Wrong call of API func. */
    eAseApiErrEmptyList=907,	   /* Can't find DO list */
    eAseApiErrMissingTable=908,    /* Missing table path in filter */
    eAseApiErrLinkNotFound=909,    /* Can't find link by link ID */
    eAseApiErrLinkMake=910,	   /* Error in link creation */
    eAseApiErrLinkUpdate=911,	   /* Error in link updating */
    eAseApiErrLinkDelete=912,	   /* Error in link deleting */
    eAseApiErrMissingLinkType=913, /* Missing link type */
    eAseApiErrWrongLinkType=914,   /* Wrong link type value */
    eAseApiErrMissingLinkID=915,   /* Missing link ID */
    eAseApiErrWrongLinkID=916,	   /* Wrong link ID value */
    eAseApiErrMissingEntName=917,  /* Missing entity name */
    eAseApiErrWrongEntName=918,    /* Wrong entity name value */
    eAseApiErrMissingLpn=919,	   /* Missing LPN */
    eAseApiErrWrongLpn=920,	   /* Invalid LPN */
    eAseApiErrMissingKeyVal=921,   /* Missing Key value list */
    eAseApiErrWrongKeyVal=922,	   /* Invalid Key valie list */
    eAseApiErrSelNotFound=923,	   /* Can't find link selection by ID */
    eAseApiErrSelAddLink=924,	   /* Can't add link to the link sel. */
    eAseApiErrSelDelLink=925,	   /* Can't delete link from the link sel. */
    eAseApiErrSelFree=926,	   /* Can't free the link sel. */
    eAseApiErrSelEmpty=927,	   /* Empty link sel. */
    eAseApiErrMissingKeyNames=928, /* Missing Key names list */
    eAseApiErrWrongKeyNames=929,   /* Invalid Key names list */
    eAseApiErrKeyNameNotFound=930, /* Key column name is not found in the table */
    eAseApiErrDupKeyNames=931,	   /* Duplicated Key names */
    eAseApiErrLpnNew=932,	   /* Error in creation of new LPN */
    eAseApiErrLpnDel=933,	   /* Error in deleting of LPN */
    eAseApiErrLpnNotFound=934,	   /* LPN is not exist */
    eAseApiErrLpnRen=935,	   /* Error in renaming of LPN */
    eAseApiErrWrongEntSel=936,	   /* Invalid entity sel. set name */
    eAseApiErrWrongBlock=937,	   /* Invalid Xref/Block name */
    eAseApiErrWrongWhere=938,	   /* Invalid WHERE condition */
    eAseApiErrSelUnite=939,	   /* Error in union */
    eAseApiErrSelSubtract=940,	   /* Error in subtract */
    eAseApiErrSelIntersect=941,    /* Error in intersect */
    eAseApiErrSelErase=942,	   /* Can't erase link sel. with links */
    eAseApiErrSelEraseLinks=943,   /* Can't erase some links */
    eAseApiErrCurrent=944,	   /* Can't set current path */
    eAseApiErrWrongRowVal=945,	   /* Invalid row values */
    eAseApiErrDuplicatedLink=946,  /* Attempt of duplicated link creation */
    eAseApiErrMissingDANames=947,  /* Missing DA names list */
    eAseApiErrWrongDANames=948,    /* Invalid DA names list */
    eAseApiErrWrongDAVal=949,	   /* Invalid DA values list */
    eAseApiErrMissingDAPar=950,    /* Missing DA parameters */
    eAseApiErrWrongDAPar=951,	   /* Invalid DA parameters */
    eAseApiErrMakeDA=952	   /* Error in make DA */
} EAseApiErrCodes ;

/* Internal Link Information related codes*/
typedef enum {
eAseLinkErrUnknown		= 1000, /* Unknown ASE error*/
eAseLinkErrWrongRegPath 	= 1001,
/*
    a) Invalid path to register table.
    b) LPN syntax error. LPN with prefix can't
       be registered.
    c) LPN syntax error. Wrong Xref name syntax.
*/

eAseLinkErrWrongRegDsc		= 1002,
/*
    a) Wrong column desriptor.				registration
    b) Invalid list of the key columns to register.
*/

eAseLinkErrWrongPath12		= 1003,
/*
    Invalid path to Database Object Release 12 to	registration
    register.
*/

eAseLinkErrWrongTypeDsc 	= 1005,
/*
    a) Unknown column descriptor data type.		registration
    b) Length of the key value can't be defined.        access to key value
*/

eAseLinkErrWrongLsAddOp 	= 1007,
/*
    Wrong Link Selection Identifier			Link Selection addition
*/

eAseLinkErrWrongLsSubOp 	= 1008,
/*
    Wrong Link Selection Identifier			Link Selection subraction
*/

eAseLinkErrWrongLsId		= 1009,
/*
    Wrong Link Selection Identifier			Access to Link Selection
*/

eAseLinkErrWrongEntityId	= 1010,
/*
    Undefined drawing object to link			DA Link creation
*/

eAseLinkErrUndefDa		= 1011,
/*
    Undefined DA list					DA link creation
*/

eAseLinkErrNoMemForLs		= 1012,
/*
    Out of memory					Link Selection manipulation
*/

eAseLinkErrWrongPtrToLnk	= 1013,
/*
    Wrong Link Identifier				Access to Link
*/

eAseLinkErrNoLinkInLMem 	= 1014,
/*
    Link was lost					Access to Link
*/

eAseLinkErrNoEntityForLink	= 1016,
/*
    Invalid Link in the memory				Access to Link
*/

eAseLinkErrWrongPtrToLs 	= 1017,
/*
    Wrong Link Selection Identifier			Access to Link Selection
*/

eAseLinkErrNoLsInLMem		= 1018,
/*
    Link Selection was lost				Access to Link Selection
*/

eAseLinkErrMLsNotValid		= 1019,
/*
    Invalid Link Selection				Access to Link Selection
*/

eAseLinkErrMLinkNotValid	= 1020,
/*
    Invalid Link in the memory				ASE Transaction
*/

eAseLinkErrTabNoChanges 	= 1021,
/*
    Link Information assosiated with			Erase LPN
    LPN can't be changed
*/

eAseLinkErrRnmWrongOldLPN	= 1022,
/*
    Old LPN is invalid					LPN Renaming
*/

eAseLinkErrRnmWrongNewLPN	= 1023,
/*
    New LPN is invalid					LPN Renaming
*/

eAseLinkErrRnmNoUpd		= 1024,
/*
    Link Information associated with LPN		LPN Renaming
    isn't updatable
*/

eAseLinkErrLLinkNotValid	= 1025,
/*
    CAseLLink object is not valid. Object		Link Manipulations
    had not been initialized
*/

eAseLinkErrLLinkNotUpdate	= 1026,
/*
    Link can't be modified. Drawing object              Link modification
    isn't updatable
*/

eAseLinkErrLLinkNoMakeDup	= 1027,
/*
    Can't create duplicated link                        Link creation
*/

eAseLinkErrLLinkNoMakeKey	= 1029,
/*
      Can't create link. Wrong keys                     Link creation
*/

eAseLinkErrLLinkNoMakeStore	= 1030,
/*
      Can't store Link into drawing                     Link creation
*/

eAseLinkErrLLinkWrongId 	= 1031,
/*
      Can't intialize CAseLLink object.                 Access to Link
      Wrong Link Identifier
*/

eAseLinkErrLLinkWrongType	= 1032,
/*
    a) Can't intialize CAseLLink object.                Access to Link
       Wrong Link type
    b) Can't update DA. Link isn't DA link              DA Link updating
*/

eAseLinkErrLLinkManyLinks	= 1033,
/*
    Can't intialize CAseLLink object by                 CAseLLink object initialization
    drawing object. Drawing object contains
    several links.
*/

eAseLinkErrLLinkNoMake		= 1034,
/*
    a) Can't make link. Duplicate link.                 Link creation
    b) Can't store Link in the memory.
    c) Can't make link. Wrong keys.
*/

eAseLinkErrLLinkNoDel		= 1035,
/*
    a) Can't delete link. Link is not valid             Link deleting
    b) Can't delete link. Link is not updatable
    c) Can't delete Xdata assocoated with link
*/

eAseLinkErrLLinkNoUpd		= 1036,
/*
    a) Can't update link. Link Information              Link modification
       was not changed.
    b) Can't update link. Link isn't valid
    c) Can't update link. Drawing object is
       not updatable.
*/

eAseLinkErrLLinkNoDATab 	= 1037,
/*
      Wrong DA Link modification.			DA link modification.
      Table name can't be changed for DA link
*/

eAseLinkErrLLinkNoDAEnt 	= 1038,
/*
      Wrong  DA Link modification			DA link modification
      Drawing object can't be changed for DA link
*/

eAseLinkErrLLinkWrongEnt	= 1039,
/*
      CAseLLink obejct was not initialized correctly	Access to link
*/

eAseLinkErrLLinkWrongDA 	= 1040,
/*
      Wrong DA columns					DA Link creation
*/

eAseLinkErrLLinkAbsent		= 1041,
/*
      Can't find out Link by Link Identifier            Access to Link
*/

eAseLinkErrLSWrongFilter	= 1042,
/*
      Wrong filter					Link Selection filtering
*/

eAseLinkErrInLMem		= 1045,
/*
      Can't clear Link Selection.                       Access to Link Selection
*/

eAseLinkErrKeyNotValid		= 1046,
/*
      Key isn't valid                                   Access to key values
*/

eAseLinkErrWrongKeyVal		= 1047,
/*
      Wrong key value					Row registration
*/

eAseLinkErrCantStoreKeyVal	= 1048,
/*
      Key value can't be stored. It is possible
      if ASE have not enough memory or key column
      descriptor is not correct.
*/

eAseLinkErrWrongDsc		= 1049,
/*
      Can't store key value. Descriptor is not          Row registration
      correct
*/

eAseLinkErrWrongKeyInit 	= 1050,
/*
      Can't initialize CAseLKey object.                 Row registration
      LPN is not valid.
*/

eAseLinkErrValid		= 1051,
/*
      Link Subsystem is not valid. Internal error.
*/

eAseLinkErrStart		= 1052,
/*
      Link subsystem can't begin ASE transaction.
      Internal error.
*/

eAseLinkErrLMemWrongId		= 1053,
/*
      Wrong Link Identifier				Access to link
*/

eAseLinkErrLMemInternal 	= 1054,
/*
      Link Subsystem internal error			Access to link
*/

eAseLinkErrLMemRBack		= 1055,
/*
      Can't restore link                                Rollback of the ASE Transaction
*/

eAseLinkErrWrongTransForUpd	= 1056,
/*
      Can't update link. Transaction wasn't opend.      Updating of the link
*/

eAseLinkErrEnameEIdConvert	= 1059,
/*
      Can't convert ads_name to AcDbEntityId.           Link making
*/

eAseLinkErrEntNoUpd		= 1060,
/*
      Entity is not updatable. Link can't be created.   Link making
*/

eAseLinkErrContainerItem	= 1061,
/*
      Can't intialize Link Selection for container.     ASELINKS command
*/

eAseLinkErrNtfEraseUnlinkedEntity = 1062,
/*
    Link Subsystem has got notification to delete     Processing of the notifications
    links, but specified object has no links.	      from linked drawing object
*/

eAseLinkErrNtfCopyUnlinkedEntity = 1063,
/*
    Link Subsystem has got notification to copy       Processing of the notifications
    links, but specified object has no links.	      from linked drawing object
*/

eAseLinkErrNtfCanTProcess	= 1064,
/*
      Link Subsysten can't process the notification.    Processing of the notifications
*/

eAseLinkErrNtfUnXED		= 1065,
/*
      Can't restore link. Wrong Xdata.                  Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eAseLinkErrNtfUnKey		= 1066,
/*
      Can't restore link. Row can't be registered.      Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eAseLinkErrNtfUnDA		= 1067,
/*
    Can't restore link. Can't store DA columns          Processing of the notifications
                            from linked drawing objects.
                            Undo command
*/

eAseLinkErrNtfUnErase		= 1069,
/*
    Can't restore link. Link isn't found out in the     Processing of the notifications
    Link memory 					from linked drawing objects.
                            Undo command
*/

eAseLinkErrInternal		= 1070,
/*
    Internal error of the Link Subsystem.
*/

eAseLinkErrWrongRecordLpnPos	= 1071,
/*
    Link subsystem can't set the position of the Lpn  Reading link information
    in the Xdata				      from drawing
*/

eAseLinkErrWrongLpnSyntax	= 1073,
/*
    LPN syntax error.				      Reading link information from
                              drawing
*/

eAseLinkErrCantRegLink		= 1076,
/*
    Can't store link. Link Path Name isn't            Reading link information from
    registered yet.				      drawing. Undo command
*/

eAseLinkErrCantInitKey		= 1077,
/*
    Can't initilize key row to register.              Reading link information from
                              drawing. Undo command
*/

eAseLinkErrWrongLinkNumber	= 1078,
/*
    Wrong link structure in the drawing object.       Reading link information from
                              drawing. Undo command
*/

eAseLinkErrDuplicateReg 	= 1079,
/*
    Duplicate registration.			      LPN registration
*/

eAseLinkErrTrRbackUndel 	= 1081,
/*
    Can't restore the deleted link.                   Rollback ASE Transaction
*/

eAseLinkErrTrRbackTable 	= 1082,
/*
    Link subsystem can't execute rollback ASE         Rollback ASE Transaction
    Transaction for link table.
*/

eAseLinkErrTrRback		= 1083,
/*
    Link subsystem can't execute rollback ASE         Rollback ASE Transaction
    Transaction, because transaction wasn't opened.
*/

eAseLinkErrTrCommit		= 1084,
/*
    Link subsystem can't execute commit ASE
    Transaction, because transaction wasn't
    opened.
*/

eAseLinkErrTrCommitTable	= 1085,
/*
    Link subsystem can't execute commit for
    Link Table.
*/

eAseLinkErrTrCommitDelLink	= 1086,
/*
    Link subsystem can't delete link data from        Commit ASE Transaction
    Xdata of the drawing object.
*/

eAseLinkErrTrCommitAddLink	= 1087,
/*
    Link subsystem can't add new link Xdata of        Commit ASE Transaction
    drawing object.
*/

eAseLinkErrLnkDestroed		= 1088,
/*
    Linked row is deleted from link memory before     Commands: Open, New Rx/Unload
    accosiated link have been erased		      Quit
*/

eAseLinkErrDupUpdLnk		= 1090,
/*
    Can't update link. Duplicated links.              Link updating.
*/

eAseLinkErrRubbNoMem		= 1091,
/*
    Can't execute rubbish collector algorithm.        Commit ASE Transaction
    Out of memory
*/

eAseLinkErrCommitNoMem		= 1092,
/*
    Can't execute commit ASE Transaction.             Commit ASE Transaction
*/

eAseLinkErrCommit		= 1093,
/*
    Link Sybsystem can't commit ASE Transaction       Commit ASE Transaction
*/

eAseLinkErrTrExportLpn		= 1094,
/*
    Can't store the export LPN to external database   Wblock command
*/

eAseLinkErrLostLink		= 1095,
/*
    Can't store the link from Xdata
*/

eAseLinkErrLinkToLeaderLink		= 1096
/*
    Can't create link because the entity is leader link component
*/

} EAseLinkErrCodes ;

/* ASE Diagnostic Parameters*/
typedef enum {
    kAseDiagErrDsc    =	 MinUserDefDiagParam+1, /* ASE error description - Int*/
    kAseDiagErrCode   =	 MinUserDefDiagParam+2, /* Error Code	         - Int*/
    kAseDiagErrMsg    =	 MinUserDefDiagParam+3, /* ASE Error Message - Char*/
    kAseDiagStatement =  MinUserDefDiagParam+4, /* SQL statement	 - Char*/
    kAseDiagSynErrPos =  MinUserDefDiagParam+5, /* Syntax error position - Int*/
    kAseDiagLPName    =	 MinUserDefDiagParam+6, /* Link Path Name	 - Char*/
    kAseDiagEnvName   =	 MinUserDefDiagParam+7, /* Environment name	 - Char*/
    kAseDiagEntHandle =  MinUserDefDiagParam+8, /* Entity handle	 - Char*/
    kAseDiagBlockName =  MinUserDefDiagParam+9, /* Block name	     - Char*/
    kAseDiagLayerName =  MinUserDefDiagParam+10,/* Layer name        - Char*/
    kAseDiagLabelName =  MinUserDefDiagParam+11,/* Label name        - Char*/
    kAseDiagAcApDoc   =  MinUserDefDiagParam+12,/* AcApDocument Address  - Int*/
    kAseDiagGroupName =  MinUserDefDiagParam+13,/* LinkTemplateGroup - Char*/
    kAseDiagQueryName =  MinUserDefDiagParam+14,/* QueryName         - Char*/
    kAseDiagTableName =  MinUserDefDiagParam+15 /* TableName         - Char*/
} EAseDiagParms ;

/* API class codes*/
typedef enum {
    kAseApiUnknownId,/* Unknown API class*/
    kAseApiAppl,	 /* for class CAseAppl and descriptor ASE_APPLDSC*/
    kAseApiLinkPath, /* for class CAseLinkPath and descriptor ASE_LPDSC*/
    kAseApiLink,	 /* for class CAseLink and descriptor ASE_LINKDSC*/
    kAseApiLinkSel	 /* for class CAseLinkSel and descriptor ASE_LSELDSC*/
} EAseApiClassId ;


// Data source translation codes 
//
enum DatasourceTranslationCode {
    kTranslateFromR14toR15 = 0,   
    kTranslateFromR15toR14
};  

#pragma pack (pop)
#endif /*_ASECONST_H*/
/*EOF*/
