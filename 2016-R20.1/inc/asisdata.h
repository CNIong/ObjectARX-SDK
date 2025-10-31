//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//    Name: asisdata.h                           ast_asi_inc_appl_asisdata_h
//
//    Description:  Basic SQL data definitions for ASI.
//                  ASI C++ User Interface.

#ifndef ASI_SDATA_HH
#define ASI_SDATA_HH asisdata.hh


#define AST_DEPRECATE_TEXT "This function is deprecated. Consider using another overload of this function."
#define AST_DEPRECATE      __declspec(deprecated(AST_DEPRECATE_TEXT))

///////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////
#include <oledb.h>

// If the compiler version is lower than VC7 LARGE_INTEGER is defined in largeint.h
// VC7 Platform SDK defines LARGE_INTEGER in winnt.h
#if _MSC_VER < 1300
  #include <largeint.h>
#else
  #include <winnt.h>
#endif

#include "asisys.h"

///////////////////////////////////////////////////////////////////////////
// FORWARD DEFINITIONS
///////////////////////////////////////////////////////////////////////////

// ASI Class Hierarchy
//
class DLLScope CAsiObject;                   // Superclass for all classes
    class DLLScope CAsiIdent;                // Identifier
    class DLLScope CAsiData;                 // ASI Data generic class
        class DLLScope CAsiNum;              // Numeric data
            class DLLScope CAsiExactNum;     // Exact numeric data
                class DLLScope CAsiSmallInt; // Small Integer
                class DLLScope CAsiInt;      // Integer
                class DLLScope CAsiNumeric;  // Numeric
                class DLLScope CAsiDecimal;  // Decimal
            class DLLScope CAsiApproxNum;    // Approximate numeric data
                class DLLScope CAsiFloat;    // Float
                class DLLScope CAsiReal;     // Real
                class DLLScope CAsiDouble;   // Double precision
        class DLLScope CAsiChar;             // Character
        class DLLScope CAsiBinary;           // Bit
        class DLLScope CAsiIQualifier;       // Interval qualifier
            class DLLScope CAsiInterval;     // Interval
                class DLLScope CAsiYM;       // Year month intervals
                class DLLScope CAsiDT;       // Day Time intervals
        class DLLScope CAsiDatetime;         // Datetime data
            class DLLScope CAsiDate;         // Date
            class DLLScope CAsiTime;         // Time
            class DLLScope CAsiTimeStamp;    // Timestamp
        class DLLScope CAsiBlob;             // OLEDB BLOBs

    class DLLScope CAsiColumn;               // Column definition
    class DLLScope CAsiRow;                  // Array of columns
    class DLLScope CAsiHostBuffer;           // Host program buffer
        class DLLScope CAsiParameter;        // Parameter desriptor
    class DLLScope CAsiImplDefFunc;          // Function

    // Class collections
    class DLLScope CAsiIRow;                 // Array of data pointers
    class DLLScope CAsiList;                 // List of CAsiObject's

    class DLLScope CAsiUcStr;                // Unicode string
    class DLLScope CAsiUcChar;               // Unicode character

    class DLLScope CAsiObjPack;              // Communication buffer access

typedef char ASIBCD [34];           // Decimal number
                                    // bcd[0] actual scale
                                    // bcd[1] sign
                                    // bcd[2-33] 32 digits unpacked BCD


#include "asiconst.h"
#include "asiucode.h"

#pragma pack (push, 8)
///////////////////////////////////////////////////////////////////////////
class CAsiObject
//
// This class is a principal base class for ALL ASI classes. It provides
// services for memory management by reloading new and delete operators.
//
{
public:
            CAsiObject                (void);
    virtual ~CAsiObject               (void);

            void*         operator new    (size_t);
            void          operator delete (void*);
#if defined(__WATCOMC__)
            void*         operator new[]    (unsigned int);
            void          operator delete[] (void*);
#endif /* __WATCOMC__ */

     // Duplicate
     //
     virtual CAsiObject  * duplicate  (void) const;

     // Nullify all members
     //
     virtual void          Clear      (void);

     // Runtime class iteraction functions. Used internaly
     //
     virtual unsigned long packSize        (void) const;
     virtual unsigned long packTo          (CAsiObjPack *) const;
     virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

     virtual unsigned long packValueSize   (void) const;
     virtual unsigned long packValueTo     (CAsiObjPack *) const;
     virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);
};



////////////////////////////////////////////////////////////////////////////////
class CAsiIdent : public CAsiObject
//
//  SQL Identifier. Most SQL names are represented as identifiers.
//  Identifier can be regular and delimitered.
//
//  Regular identifier body must begin from the letter and contain
//  letters, underscope, and digits. ASI convertes regular
//  identifier body to upper case.
//  Delimited identifier can contain arbitrary symbol. In
//  SQL statements delimeted identifiers are enclosed into double
//  quotas
//
{
public:
     // Construct identifier
     //
                            CAsiIdent       (void);
                            CAsiIdent       (const char *);
                            CAsiIdent       (const AsiUcStr);
                            CAsiIdent       (const CAsiUcStr &);
                            CAsiIdent       (const CAsiUcStr &, const CAsiUcStr &);
                            CAsiIdent       (const CAsiIdent &);
    virtual                 ~CAsiIdent      (void);

      // Set and get identifier value
      //
    void                    set             (EAsiBoolean,
                                            const CAsiUcStr &,
                                            const CAsiUcStr &);

    void                    setDelimited    (EAsiBoolean);
    void                    setDelimited    (void);
    void                    setCharSet      (const CAsiUcStr &);

    // fParse = false, do not parse body. store it as it is
    void                    setBody         (const CAsiUcStr &, EAsiBoolean fParse = kAsiTrue);

    EAsiBoolean             isDelimited     (void) const;   // True if delimitered identifier
    const CAsiUcStr         & CharSet       (void) const;
    const CAsiUcStr         & Body          (void) const;

    // Length of Identifer (inc. introducer, char set name and
    // identifier itself
    int                     Length          (void) const;

    // Clear components
    //
    virtual void            Clear           (void);


    // Operators
    //
    CAsiIdent       &       operator=       (const CAsiIdent &);  // Assign another identifier
    CAsiIdent       &       operator=       (const CAsiUcStr &);  // Assign regular identifier

    int                     operator==      (const CAsiIdent &) const;

    // Print identifier
    //
    void                    ToString        (CAsiUcStr *) const; // Append identifier to string

    // Duplicate
    //
    virtual CAsiObject   *  duplicate       (void) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long   packSize        (void) const;
    virtual unsigned long   packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean     unpackFrom      (CAsiObjPack *);

private:
    EAsiBoolean             isDelim;      // Is delimited identifier
    CAsiUcStr               charset;      // Character set name
    CAsiUcStr               ident;        // Identifier body
};



////////////////////////////////////////////////////////////////////
//
//  ASI Data classes
//



/////////////////////////////////////////////////////////////////////////
//
//
//
class CAsiData : public CAsiObject
//
//  SQL Data
//
//
// This class is a base class for all ASI data classes.
// The basic functionality of it comprise the foolowing:
//   - Getting data type descriptor;
//   - Getting value in specified format;
//   - Storing value provided in arbitrary format;
//   - NULL value manipulating;
//   - Self duplicating
//
//
//  MEMBER FUNCTIONS:
//  -----------------
//
//  Get data descriptor
//
//  EAsiDataType  Type          (void)  // type of data
//  EAsiDTType    DateTimeType  (void)  // Datetime type
//  EAsiIType     IntervalType  (void)  // Interval type
//  int           ImplDataType  (void)  // Implemetation defined type
//  uint          Length        (void)  // Length of character or bit data
//  uint          Precision     (void)  // Precision
//  uint          Scale         (void)  // Scale
//  uint          TimePrec      (void)  // Time Precision
//  uint          TimeStampPrec (void)  // Timestamp precision
//  uint          LeadFieldPrec (void)  // Leading field precision
//  uint          FracSecPrec   (void)  // Fractional second precision
//  uint          ReturnLength  (void)  // Actual length of data
//
//  The functions listed above allow to retrieve desription of the
//  the SQL data in terms of SQL. They are pure virtual functions,
//  actual transaltion of internal data descriptioon to the SQL data description
//  is done by the derived classes.
//
//
//  NULL value manipulation
//
//  void setNull (void)
//
//    Set internal data to NULL value (absence of value)
//
//
//  EAsiBoolean isNull (void) const
//
//    Return kAsiTrue if data is NULL and kAsiFalse otherwise
//
//
// Store Data value
//
//  virtual EAsiBoolean   storeValue   (...);
//
// These functions allow to store data into class derived from
// the CAsiData. Source data is converted to the actual type of the CAsiData
// If conversion is possible and data was successfully stored and kAsiTrue is
// returned, if conversion is impossible, kAsiFalse is returned.
//
//
// Get data value
//
//  virtual void getValue (...)
//
// Store value of the CAsiData object into destination buffer and perform all
// needed converisons. If operation succeeded, kAsiTrue is returned, if not
// kSiFalse is returned and contents of destination buffer is undefined.
// If null value is stored, destination buffer contents is undefined.
//
//  EAsiBoolean   SQLType    (CAsiUcStr * dst) const
//  EAsiBoolean   SQLLiteral (CAsiUcStr * dst) const
//
//  This functions stores SQL data type string and SQL literal into destination
//  buffer. For example, for Year to month interval first function will
//  return INTERVAL YEAR TO MONTH, the second one - INTERVAL 'yy-dd' YEAR TO MONTH
//
// Duplicate
//
// virtual CAsiObject *duplicate (void) const
//
// Create duplicate of the CAsiData object.
//
//
//  Operations with the Internal Data (Operators)
//
//  Each class derived from CAsiData defines a set of functions that
//  perform certain operations with it. These functions comprise:
//    - assignment operator;
//    - arithmetics operator;
//    - data specific operations
//
//  For more details see appropriate class definition.
//
//
{
friend class CAsiColumn;

public:

    //  Construction destruction
    //

            CAsiData  (void);
    virtual ~CAsiData (void);

    //  Get data descriptor
    //
    virtual EAsiDataType    Type                (void) const = 0;  // type of data
    virtual EAsiDTType      DateTimeType        (void) const; // Datetime type
    virtual EAsiIType       IntervalType        (void) const; // Interval type
    virtual int             ImplDataType        (void) const; // Implemetation defined type
    virtual uint            Length              (void) const; // Length of character or bit data
    virtual uint            Precision           (void) const; // Precision
    virtual uint            Scale               (void) const; // Scale
    virtual uint            TimePrec            (void) const; // Time Precision
    virtual uint            TimeStampPrec       (void) const; // Timestamp precision
    virtual uint            LeadFieldPrec       (void) const; // Leading field precision
    virtual uint            FracSecPrec         (void) const; // Fractional second precision
    virtual uint            ReturnLength        (void) const; // Actual length of data

    //  is_ functions
    //
    virtual EAsiBoolean     is_numeric          (void) const;
    virtual EAsiBoolean     is_exactnumeric     (void) const;
    virtual EAsiBoolean     is_approxnumeric    (void) const;
    virtual EAsiBoolean     is_character        (void) const;
    virtual EAsiBoolean     is_binary           (void) const;
    virtual EAsiBoolean     is_datetime         (void) const;
    virtual EAsiBoolean     is_interval         (void) const;
    virtual EAsiBoolean     is_yminterval       (void) const;
    virtual EAsiBoolean     is_dtinterval       (void) const;
    virtual EAsiBoolean     is_implement        (void) const;

    virtual EAsiBoolean     is_comparable       (const CAsiData *) const;
    virtual EAsiBoolean     is_storable         (const CAsiData *) const;
    virtual EAsiBoolean     is_castable         (const CAsiData *) const;

    // Check certain operations and return resulting descriptor
    virtual CAsiData *      checkAdd            (const CAsiData *) const;
    virtual CAsiData *      checkSub            (const CAsiData *) const;
    virtual CAsiData *      checkMul            (const CAsiData *) const;
    virtual CAsiData *      checkDiv            (const CAsiData *) const;
    virtual CAsiData *      checkCat            (const CAsiData *) const;
    virtual CAsiData *      checkSet            (const CAsiData *) const;    // Set Operation result

    // Equal & Greater than relations
    virtual EAsiBoolean     isEqualTo           (const CAsiData &) const;
    virtual EAsiBoolean     isGreaterThan       (const CAsiData &) const;

    // Member function execution
    virtual CAsiImplDefFunc *  getFuncDsc       (const CAsiIdent &, const CAsiRow &) const;


    //  NULL value manipulation
    //
    virtual void            setNull             (void);            // Assign NULL
    virtual EAsiBoolean     isNull              (void) const;      // Is Null ?

    // Store Data value
    //
    virtual EAsiBoolean     storeValue          (real);                 // Real
    virtual EAsiBoolean     storeValue          (integer);              // Integer
    virtual EAsiBoolean     storeValue          (smallint);             // Smallint
    virtual EAsiBoolean     storeValue          (char *, uint);         // ASCII string
    virtual EAsiBoolean     storeValue          (const CAsiUcStr &);    // Unicode string
    virtual EAsiBoolean     storeValue          (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean     storeValue          (const CAsiData &);     // store value to CAsiData (cast to)
    virtual EAsiBoolean     storeValue          (const AsiUcStr);       // Store AsiUcStr
    virtual EAsiBoolean		storeValue			(const DECIMAL &);
    virtual EAsiBoolean		storeValue			(const DB_NUMERIC *);
    virtual EAsiBoolean		storeValue			(const DBDATE *);
    virtual EAsiBoolean		storeValue			(const DBTIME *);
    virtual EAsiBoolean		storeValue			(const DBTIMESTAMP *);

    //  Retrive data value
    //
    virtual EAsiBoolean     getValue            (real *) const;               // Real
    virtual EAsiBoolean     getValue            (integer *) const;            // Integer
    virtual EAsiBoolean     getValue            (smallint *) const;           // Smallint
    virtual EAsiBoolean     getValue            (char *, uint) const;         // ASCII string
    virtual EAsiBoolean     getValue            (CAsiUcStr *) const;          // Unicode string
    virtual EAsiBoolean     getValue            (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean     getValue            (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean     getValue            (CAsiData &) const;           // Get value from CAsiData (cast from)
    virtual EAsiBoolean		getValue			(DECIMAL *) const;
    virtual EAsiBoolean		getValue			(DB_NUMERIC *) const;
    virtual EAsiBoolean		getValue			(DBDATE *) const;
    virtual EAsiBoolean		getValue			(DBTIME *) const;
    virtual EAsiBoolean		getValue			(DBTIMESTAMP *) const;


    virtual EAsiBoolean     SQLType             (CAsiUcStr *) const = 0;    // SQL data type as string
    virtual EAsiBoolean     SQLLiteral          (CAsiUcStr *) const = 0;    // SQL compatible literal


    // OLE DB To Asi mapping
    static CAsiData *       MapColumnInfoToAsi  (DBCOLUMNINFO * pColumnInfo);
    static CAsiData *       MapParamInfoToAsi	(DBPARAMINFO * pParamInfo);

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;

    // Runtime class iteraction functions
    //

    // Duplicate itself
    //
    virtual CAsiObject*     duplicate           (void) const = 0;

    // Nullify all members

    virtual void            Clear               (void);

protected:
    EAsiBoolean             isnull;                           // kAsiTrue if data is null
};


////////////////////////////////////////////////
//
//
class CAsiNum : public CAsiData
//
// Numeric data
//
{
friend class CAsiLex;
protected:
                                CAsiNum ();           
public:
    virtual						~CAsiNum ();          

    // Get data descriptor
    //
    virtual uint                Precision       (void) const;
    virtual uint                Scale           (void) const;

    //  is_ functions
    //
        virtual EAsiBoolean     is_numeric      (void) const;
    virtual EAsiBoolean         is_exactnumeric (void) const;
    virtual EAsiBoolean         is_approxnumeric(void) const;
    virtual EAsiBoolean         is_comparable   (const CAsiData *) const;
    virtual EAsiBoolean         is_storable     (const CAsiData *) const;
    virtual EAsiBoolean         is_castable     (const CAsiData *) const;

    virtual CAsiData    *       checkAdd        (const CAsiData *) const;
    virtual CAsiData    *       checkSub        (const CAsiData *) const;
    virtual CAsiData    *       checkMul        (const CAsiData *) const;
    virtual CAsiData    *       checkDiv        (const CAsiData *) const;


    // Get data value
    //
    virtual integer             intValue        (void) const;
    virtual real                realValue       (void) const;


    // virtual Comparision operators
    //
    virtual int                 operator>  (const CAsiSmallInt &) const;
    virtual int                 operator>  (const CAsiInt &)      const;
    virtual int                 operator>  (const CAsiNumeric &)  const;
    virtual int                 operator>  (const CAsiDecimal &)  const;
    virtual int                 operator>  (const CAsiFloat &)    const;
    virtual int                 operator>  (const CAsiReal &)     const;
    virtual int                 operator>  (const CAsiDouble &)   const;
    virtual int                 operator>  (const smallint)       const;
    virtual int                 operator>  (const integer)        const;
    virtual int                 operator>  (const real)           const;
    virtual int                 operator>  (const int)            const;

    virtual int                 operator>= (const CAsiSmallInt &) const;
    virtual int                 operator>= (const CAsiInt &)      const;
    virtual int                 operator>= (const CAsiNumeric &)  const;
    virtual int                 operator>= (const CAsiDecimal &)  const;
    virtual int                 operator>= (const CAsiFloat &)    const;
    virtual int                 operator>= (const CAsiReal &)     const;
    virtual int                 operator>= (const CAsiDouble &)   const;
    virtual int                 operator>= (const smallint)       const;
    virtual int                 operator>= (const integer)        const;
    virtual int                 operator>= (const real)           const;
    virtual int                 operator>= (const int)            const;

    virtual int                 operator== (const CAsiSmallInt &) const;
    virtual int                 operator== (const CAsiInt &)      const;
    virtual int                 operator== (const CAsiNumeric &)  const;
    virtual int                 operator== (const CAsiDecimal &)  const;
    virtual int                 operator== (const CAsiFloat &)    const;
    virtual int                 operator== (const CAsiReal &)     const;
    virtual int                 operator== (const CAsiDouble &)   const;
    virtual int                 operator== (const smallint)       const;
    virtual int                 operator== (const integer)        const;
    virtual int                 operator== (const real)           const;
    virtual int                 operator== (const int)            const;

    virtual int                 operator<= (const CAsiSmallInt &) const;
    virtual int                 operator<= (const CAsiInt &)      const;
    virtual int                 operator<= (const CAsiNumeric &)  const;
    virtual int                 operator<= (const CAsiDecimal &)  const;
    virtual int                 operator<= (const CAsiFloat &)    const;
    virtual int                 operator<= (const CAsiReal &)     const;
    virtual int                 operator<= (const CAsiDouble &)   const;
    virtual int                 operator<= (const smallint)       const;
    virtual int                 operator<= (const integer)        const;
    virtual int                 operator<= (const real)           const;
    virtual int                 operator<= (const int)            const;

    virtual int                 operator<  (const CAsiSmallInt &) const;
    virtual int                 operator<  (const CAsiInt &)      const;
    virtual int                 operator<  (const CAsiNumeric &)  const;
    virtual int                 operator<  (const CAsiDecimal &)  const;
    virtual int                 operator<  (const CAsiFloat &)    const;
    virtual int                 operator<  (const CAsiReal &)     const;
    virtual int                 operator<  (const CAsiDouble &)   const;
    virtual int                 operator<  (const smallint)       const;
    virtual int                 operator<  (const integer)        const;
    virtual int                 operator<  (const real)           const;
    virtual int                 operator<  (const int)            const;

    virtual int                 operator!= (const CAsiSmallInt &) const;
    virtual int                 operator!= (const CAsiInt &)      const;
    virtual int                 operator!= (const CAsiNumeric &)  const;
    virtual int                 operator!= (const CAsiDecimal &)  const;
    virtual int                 operator!= (const CAsiFloat &)    const;
    virtual int                 operator!= (const CAsiReal &)     const;
    virtual int                 operator!= (const CAsiDouble &)   const;
    virtual int                 operator!= (const smallint)       const;
    virtual int                 operator!= (const integer)        const;
    virtual int                 operator!= (const real)           const;
    virtual int                 operator!= (const int)            const;


protected:
    uint        precision;
    uint        scale;

};


////////////////////////////////////////////////
//
//
class CAsiExactNum : public CAsiNum
//
// Exact numeric data
//
{
protected:
                            CAsiExactNum ();
public:
    virtual					~CAsiExactNum ();

    //  is_ functions
    //
    virtual EAsiBoolean		is_exactnumeric       (void) const;
    CAsiData              * checkAdd                      (const CAsiData *) const;


    // Comparision operators
    //
    virtual int         operator>  (const CAsiSmallInt &) const;
    virtual int         operator>  (const CAsiInt &)      const;
    virtual int         operator>  (const CAsiNumeric &)  const;
    virtual int         operator>  (const CAsiDecimal &)  const;
    virtual int         operator>  (const CAsiFloat &)    const;
    virtual int         operator>  (const CAsiReal &)     const;
    virtual int         operator>  (const CAsiDouble &)   const;
    virtual int         operator>  (const smallint)       const;
    virtual int         operator>  (const integer)        const;
    virtual int         operator>  (const real)           const;
    virtual int         operator>  (const int)            const;

    virtual int         operator>= (const CAsiSmallInt &) const;
    virtual int         operator>= (const CAsiInt &)      const;
    virtual int         operator>= (const CAsiNumeric &)  const;
    virtual int         operator>= (const CAsiDecimal &)  const;
    virtual int         operator>= (const CAsiFloat &)    const;
    virtual int         operator>= (const CAsiReal &)     const;
    virtual int         operator>= (const CAsiDouble &)   const;
    virtual int         operator>= (const smallint)       const;
    virtual int         operator>= (const integer)        const;
    virtual int         operator>= (const real)           const;
    virtual int         operator>= (const int)            const;

    virtual int         operator== (const CAsiSmallInt &) const;
    virtual int         operator== (const CAsiInt &)      const;
    virtual int         operator== (const CAsiNumeric &)  const;
    virtual int         operator== (const CAsiDecimal &)  const;
    virtual int         operator== (const CAsiFloat &)    const;
    virtual int         operator== (const CAsiReal &)     const;
    virtual int         operator== (const CAsiDouble &)   const;
    virtual int         operator== (const smallint)       const;
    virtual int         operator== (const integer)        const;
    virtual int         operator== (const real)           const;
    virtual int         operator== (const int)            const;

    virtual int         operator<= (const CAsiSmallInt &) const;
    virtual int         operator<= (const CAsiInt &)      const;
    virtual int         operator<= (const CAsiNumeric &)  const;
    virtual int         operator<= (const CAsiDecimal &)  const;
    virtual int         operator<= (const CAsiFloat &)    const;
    virtual int         operator<= (const CAsiReal &)     const;
    virtual int         operator<= (const CAsiDouble &)   const;
    virtual int         operator<= (const smallint)       const;
    virtual int         operator<= (const integer)        const;
    virtual int         operator<= (const real)           const;
    virtual int         operator<= (const int)            const;

    virtual int         operator<  (const CAsiSmallInt &) const;
    virtual int         operator<  (const CAsiInt &)      const;
    virtual int         operator<  (const CAsiNumeric &)  const;
    virtual int         operator<  (const CAsiDecimal &)  const;
    virtual int         operator<  (const CAsiFloat &)    const;
    virtual int         operator<  (const CAsiReal &)     const;
    virtual int         operator<  (const CAsiDouble &)   const;
    virtual int         operator<  (const smallint)       const;
    virtual int         operator<  (const integer)        const;
    virtual int         operator<  (const real)           const;
    virtual int         operator<  (const int)            const;

    virtual int         operator!= (const CAsiSmallInt &) const;
    virtual int         operator!= (const CAsiInt &)      const;
    virtual int         operator!= (const CAsiNumeric &)  const;
    virtual int         operator!= (const CAsiDecimal &)  const;
    virtual int         operator!= (const CAsiFloat &)    const;
    virtual int         operator!= (const CAsiReal &)     const;
    virtual int         operator!= (const CAsiDouble &)   const;
    virtual int         operator!= (const smallint)       const;
    virtual int         operator!= (const integer)        const;
    virtual int         operator!= (const real)           const;
    virtual int         operator!= (const int)            const;



protected:
            int         cmpeqlen(const  CAsiExactNum *)   const;
            int         cmpeqlan(const  CAsiNum *)        const;
            int         cmpeqlenC(const real)             const;
            int         cmpneqen(const  CAsiExactNum *)   const;
            int         cmpneqan(const  CAsiNum *)        const;
            int         cmpneqenC(const real)             const;
            int         cmpltren(const  CAsiExactNum *)   const;
            int         cmpltran(const  CAsiNum *)        const;
            int         cmpltrenC(const real)             const;
            int         cmplteen(const  CAsiExactNum *)   const;
            int         cmpltean(const  CAsiNum *)        const;
            int         cmplteenC(const real)             const;
            int         cmpgtren(const  CAsiExactNum *)   const;
            int         cmpgtran(const  CAsiNum *)        const;
            int         cmpgtrenC(const real)             const;
            int         cmpgteen(const  CAsiExactNum *)   const;
            int         cmpgtean(const  CAsiNum *)        const;
            int         cmpgteenC(const real)             const;

};



////////////////////////////////////////////////
//
//
class CAsiApproxNum : public CAsiNum
//
// Approximate numeric data
//
{
protected:
                        CAsiApproxNum ();     // Constructor
public:
    virtual				~CAsiApproxNum ();    // Destructor

    //  is_ functions
    //
    virtual EAsiBoolean is_approxnumeric    (void) const;


    // Comparision operators
    //
    virtual int         operator>  (const CAsiSmallInt &) const;
    virtual int         operator>  (const CAsiInt &)      const;
    virtual int         operator>  (const CAsiNumeric &)  const;
    virtual int         operator>  (const CAsiDecimal &)  const;
    virtual int         operator>  (const CAsiFloat &)    const;
    virtual int         operator>  (const CAsiReal &)     const;
    virtual int         operator>  (const CAsiDouble &)   const;
    virtual int         operator>  (const smallint)       const;
    virtual int         operator>  (const integer)        const;
    virtual int         operator>  (const real)           const;
    virtual int         operator>  (const int)            const;

    virtual int         operator>= (const CAsiSmallInt &) const;
    virtual int         operator>= (const CAsiInt &)      const;
    virtual int         operator>= (const CAsiNumeric &)  const;
    virtual int         operator>= (const CAsiDecimal &)  const;
    virtual int         operator>= (const CAsiFloat &)    const;
    virtual int         operator>= (const CAsiReal &)     const;
    virtual int         operator>= (const CAsiDouble &)   const;
    virtual int         operator>= (const smallint)       const;
    virtual int         operator>= (const integer)        const;
    virtual int         operator>= (const real)           const;
    virtual int         operator>= (const int)            const;

    virtual int         operator== (const CAsiSmallInt &) const;
    virtual int         operator== (const CAsiInt &)      const;
    virtual int         operator== (const CAsiNumeric &)  const;
    virtual int         operator== (const CAsiDecimal &)  const;
    virtual int         operator== (const CAsiFloat &)    const;
    virtual int         operator== (const CAsiReal &)     const;
    virtual int         operator== (const CAsiDouble &)   const;
    virtual int         operator== (const smallint)       const;
    virtual int         operator== (const integer)        const;
    virtual int         operator== (const real)           const;
    virtual int         operator== (const int)            const;

    virtual int         operator<= (const CAsiSmallInt &) const;
    virtual int         operator<= (const CAsiInt &)      const;
    virtual int         operator<= (const CAsiNumeric &)  const;
    virtual int         operator<= (const CAsiDecimal &)  const;
    virtual int         operator<= (const CAsiFloat &)    const;
    virtual int         operator<= (const CAsiReal &)     const;
    virtual int         operator<= (const CAsiDouble &)   const;
    virtual int         operator<= (const smallint)       const;
    virtual int         operator<= (const integer)        const;
    virtual int         operator<= (const real)           const;
    virtual int         operator<= (const int)            const;

    virtual int         operator<  (const CAsiSmallInt &) const;
    virtual int         operator<  (const CAsiInt &)      const;
    virtual int         operator<  (const CAsiNumeric &)  const;
    virtual int         operator<  (const CAsiDecimal &)  const;
    virtual int         operator<  (const CAsiFloat &)    const;
    virtual int         operator<  (const CAsiReal &)     const;
    virtual int         operator<  (const CAsiDouble &)   const;
    virtual int         operator<  (const smallint)       const;
    virtual int         operator<  (const integer)        const;
    virtual int         operator<  (const real)           const;
    virtual int         operator<  (const int)            const;

    virtual int         operator!= (const CAsiSmallInt &) const;
    virtual int         operator!= (const CAsiInt &)      const;
    virtual int         operator!= (const CAsiNumeric &)  const;
    virtual int         operator!= (const CAsiDecimal &)  const;
    virtual int         operator!= (const CAsiFloat &)    const;
    virtual int         operator!= (const CAsiReal &)     const;
    virtual int         operator!= (const CAsiDouble &)   const;
    virtual int         operator!= (const smallint)       const;
    virtual int         operator!= (const integer)        const;
    virtual int         operator!= (const real)           const;
    virtual int         operator!= (const int)            const;



protected:

};




////////////////////////////////////////////////
//
//
class CAsiSmallInt : public CAsiExactNum
//
// SMALL INTEGER
//
{
public:
                        CAsiSmallInt (void);
                        CAsiSmallInt (const CAsiSmallInt &);
    virtual				~CAsiSmallInt (void);


    //  Get data descriptor
    //
    virtual EAsiDataType Type           (void) const;
    virtual uint         ReturnLength   (void) const;

    virtual EAsiBoolean  isEqualTo      (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan  (const CAsiData &) const;


    virtual CAsiData *   checkAdd       (const CAsiData *) const;
    virtual CAsiData *   checkSub       (const CAsiData *) const;
    virtual CAsiData *   checkMul       (const CAsiData *) const;
    virtual CAsiData *   checkDiv       (const CAsiData *) const;
    virtual CAsiData *   checkSet       (const CAsiData *) const;

    // Store Data value
    //
    virtual EAsiBoolean   storeValue (real) ;
    virtual EAsiBoolean   storeValue (integer) ;
    virtual EAsiBoolean   storeValue (smallint) ;
    virtual EAsiBoolean   storeValue (char *, uint) ;
    virtual EAsiBoolean   storeValue (const CAsiUcStr &) ;
    virtual EAsiBoolean   storeValue (const CAsiData &);

    // ****
    virtual EAsiBoolean   storeValue (char *, uint, uint *);
    virtual EAsiBoolean   storeValue (const AsiUcStr);


    //  Get data value
    //
    virtual integer       intValue  (void) const;
    virtual real          realValue (void) const;

    virtual EAsiBoolean   getValue (real *) const;
    virtual EAsiBoolean   getValue (integer *) const;
    virtual EAsiBoolean   getValue (smallint *) const;
    virtual EAsiBoolean   getValue (char *, uint) const;
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;

    // ****
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;

    virtual EAsiBoolean   SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal


    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *) ;


    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
    //
            // Assignment
            CAsiSmallInt &operator= (const CAsiSmallInt &);
            CAsiSmallInt &operator= (const CAsiInt &);
            CAsiSmallInt &operator= (const CAsiNumeric &);
            CAsiSmallInt &operator= (const CAsiDecimal &);
            CAsiSmallInt &operator= (const CAsiFloat &);
            CAsiSmallInt &operator= (const CAsiReal &);
            CAsiSmallInt &operator= (const CAsiDouble &);
            CAsiSmallInt &operator= (const smallint);
            CAsiSmallInt &operator= (const integer);
            CAsiSmallInt &operator= (const real);
            CAsiSmallInt &operator= (const int);

            // Arithmetic operators
            CAsiSmallInt &operator+= (const CAsiSmallInt &);
            CAsiSmallInt &operator+= (const CAsiInt &);
            CAsiSmallInt &operator+= (const CAsiNumeric &);
            CAsiSmallInt &operator+= (const CAsiDecimal &);
            CAsiSmallInt &operator+= (const CAsiFloat &);
            CAsiSmallInt &operator+= (const CAsiReal &);
            CAsiSmallInt &operator+= (const CAsiDouble &);
            CAsiSmallInt &operator+= (const smallint);
            CAsiSmallInt &operator+= (const integer);
            CAsiSmallInt &operator+= (const real);
            CAsiSmallInt &operator+= (const int);

            CAsiSmallInt &operator-= (const CAsiSmallInt &);
            CAsiSmallInt &operator-= (const CAsiInt &);
            CAsiSmallInt &operator-= (const CAsiNumeric &);
            CAsiSmallInt &operator-= (const CAsiDecimal &);
            CAsiSmallInt &operator-= (const CAsiFloat &);
            CAsiSmallInt &operator-= (const CAsiReal &);
            CAsiSmallInt &operator-= (const CAsiDouble &);
            CAsiSmallInt &operator-= (const smallint);
            CAsiSmallInt &operator-= (const integer);
            CAsiSmallInt &operator-= (const real);
            CAsiSmallInt &operator-= (const int);

            CAsiSmallInt &operator*= (const CAsiSmallInt &);
            CAsiSmallInt &operator*= (const CAsiInt &);
            CAsiSmallInt &operator*= (const CAsiNumeric &);
            CAsiSmallInt &operator*= (const CAsiDecimal &);
            CAsiSmallInt &operator*= (const CAsiFloat &);
            CAsiSmallInt &operator*= (const CAsiReal &);
            CAsiSmallInt &operator*= (const CAsiDouble &);
            CAsiSmallInt &operator*= (const smallint);
            CAsiSmallInt &operator*= (const integer);
            CAsiSmallInt &operator*= (const real);
            CAsiSmallInt &operator*= (const int);

            CAsiSmallInt &operator/= (const CAsiSmallInt &);
            CAsiSmallInt &operator/= (const CAsiInt &);
            CAsiSmallInt &operator/= (const CAsiNumeric &);
            CAsiSmallInt &operator/= (const CAsiDecimal &);
            CAsiSmallInt &operator/= (const CAsiFloat &);
            CAsiSmallInt &operator/= (const CAsiReal &);
            CAsiSmallInt &operator/= (const CAsiDouble &);
            CAsiSmallInt &operator/= (const smallint);
            CAsiSmallInt &operator/= (const integer);
            CAsiSmallInt &operator/= (const real);
            CAsiSmallInt &operator/= (const int);

            CAsiDouble operator+ (const CAsiSmallInt &) const;
            CAsiDouble operator+ (const smallint)       const;
            CAsiDouble operator+ (const integer)        const;
            CAsiDouble operator+ (const real)           const;
            CAsiDouble operator+ (const int)            const;
     friend CAsiDouble DLLScope operator+ (const smallint, const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator+ (const integer,  const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator+ (const real,     const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator+ (const int,      const CAsiSmallInt &);

            CAsiDouble operator- (const CAsiSmallInt &) const;
            CAsiDouble operator- (const smallint)       const;
            CAsiDouble operator- (const integer)        const;
            CAsiDouble operator- (const real)           const;
            CAsiDouble operator- (const int)            const;
     friend CAsiDouble DLLScope operator- (const smallint, const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator- (const integer,  const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator- (const real,     const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator- (const int,      const CAsiSmallInt &);


            CAsiDouble operator* (const CAsiSmallInt &) const;
            CAsiDouble operator* (const smallint)       const;
            CAsiDouble operator* (const integer)        const;
            CAsiDouble operator* (const real)           const;
            CAsiDouble operator* (const int)            const;
     friend CAsiDouble DLLScope operator* (const smallint, const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator* (const integer,  const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator* (const real,     const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator* (const int,      const CAsiSmallInt &);



            CAsiDouble operator/ (const CAsiSmallInt &) const;
            CAsiDouble operator/ (const smallint)  const;
            CAsiDouble operator/ (const integer)   const;
            CAsiDouble operator/ (const real)      const;
            CAsiDouble operator/ (const int)       const;
     friend CAsiDouble DLLScope operator/ (const smallint, const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator/ (const integer,  const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator/ (const real,     const CAsiSmallInt &);
     friend CAsiDouble DLLScope operator/ (const int,      const CAsiSmallInt &);


            CAsiSmallInt &operator-- (void);
            CAsiSmallInt &operator++ (void);

            CAsiSmallInt &operator-  (void);

private:
    smallint sivalue;
};


////////////////////////////////////////////////
//
//
class CAsiInt : public CAsiExactNum
//
// INTEGER
//
// This class introduces functionality of the SQL INTEGER data type.
// It redefines all arithmetic and comparision operators in which
// integer number can be involved in SQL. Memeber functions also allow
// to set and retrieve value of the internal integer number in double and
// integer formats.
//
{
public:
                        CAsiInt ();
                        CAsiInt (const CAsiInt &);
    virtual				~CAsiInt ();

    //  Get data descriptor
    //
    virtual EAsiDataType Type           (void) const;
    virtual uint         ReturnLength   (void) const;

    virtual CAsiData *   checkAdd       (const CAsiData *) const;
    virtual CAsiData *   checkSub       (const CAsiData *) const;
    virtual CAsiData *   checkMul       (const CAsiData *) const;
    virtual CAsiData *   checkDiv       (const CAsiData *) const;
    virtual CAsiData *   checkSet       (const CAsiData *) const;

    virtual EAsiBoolean  isEqualTo      (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan  (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean   storeValue (real);
    virtual EAsiBoolean   storeValue (integer);
    virtual EAsiBoolean   storeValue (smallint);
    virtual EAsiBoolean   storeValue (char *, uint);
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue (const CAsiData &);

    // ****
    virtual EAsiBoolean   storeValue (char *, uint, uint *);
    virtual EAsiBoolean   storeValue (const AsiUcStr);


    //  Get data value
    //
    virtual integer       intValue  (void) const;
    virtual real          realValue (void) const;

    virtual EAsiBoolean   getValue (real *) const;
    virtual EAsiBoolean   getValue (integer *) const;
    virtual EAsiBoolean   getValue (smallint *) const;
    virtual EAsiBoolean   getValue (char *, uint) const;
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;

    // ****
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;

    virtual EAsiBoolean   SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *) ;

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
    //
            // Assignment
            CAsiInt &operator= (const CAsiSmallInt &);
            CAsiInt &operator= (const CAsiInt &);
            CAsiInt &operator= (const CAsiNumeric &);
            CAsiInt &operator= (const CAsiDecimal &);
            CAsiInt &operator= (const CAsiFloat &);
            CAsiInt &operator= (const CAsiReal &);
            CAsiInt &operator= (const CAsiDouble &);
            CAsiInt &operator= (const smallint);
            CAsiInt &operator= (const integer);
            CAsiInt &operator= (const real);
            CAsiInt &operator= (const int);

            // Arithmetic operators

            CAsiInt &operator+= (const CAsiSmallInt &);
            CAsiInt &operator+= (const CAsiInt &);
            CAsiInt &operator+= (const CAsiNumeric &);
            CAsiInt &operator+= (const CAsiDecimal &);
            CAsiInt &operator+= (const CAsiFloat &);
            CAsiInt &operator+= (const CAsiReal &);
            CAsiInt &operator+= (const CAsiDouble &);
            CAsiInt &operator+= (const smallint);
            CAsiInt &operator+= (const integer);
            CAsiInt &operator+= (const real);
            CAsiInt &operator+= (const int);

            CAsiInt &operator-= (const CAsiSmallInt &);
            CAsiInt &operator-= (const CAsiInt &);
            CAsiInt &operator-= (const CAsiNumeric &);
            CAsiInt &operator-= (const CAsiDecimal &);
            CAsiInt &operator-= (const CAsiFloat &);
            CAsiInt &operator-= (const CAsiReal &);
            CAsiInt &operator-= (const CAsiDouble &);
            CAsiInt &operator-= (const smallint);
            CAsiInt &operator-= (const integer);
            CAsiInt &operator-= (const real);
            CAsiInt &operator-= (const int);

            CAsiInt &operator*= (const CAsiSmallInt &);
            CAsiInt &operator*= (const CAsiInt &);
            CAsiInt &operator*= (const CAsiNumeric &);
            CAsiInt &operator*= (const CAsiDecimal &);
            CAsiInt &operator*= (const CAsiFloat &);
            CAsiInt &operator*= (const CAsiReal &);
            CAsiInt &operator*= (const CAsiDouble &);
            CAsiInt &operator*= (const smallint);
            CAsiInt &operator*= (const integer);
            CAsiInt &operator*= (const real);
            CAsiInt &operator*= (const int);

            CAsiInt &operator/= (const CAsiSmallInt &);
            CAsiInt &operator/= (const CAsiInt &);
            CAsiInt &operator/= (const CAsiNumeric &);
            CAsiInt &operator/= (const CAsiDecimal &);
            CAsiInt &operator/= (const CAsiFloat &);
            CAsiInt &operator/= (const CAsiReal &);
            CAsiInt &operator/= (const CAsiDouble &);
            CAsiInt &operator/= (const smallint);
            CAsiInt &operator/= (const integer);
            CAsiInt &operator/= (const real);
            CAsiInt &operator/= (const int);

            CAsiDouble operator+ (const CAsiSmallInt &) const;
     friend CAsiDouble DLLScope operator+ (const CAsiSmallInt &, const CAsiInt &);
            CAsiDouble operator+ (const CAsiInt &) const;
            CAsiDouble operator+ (const smallint)  const;
     friend CAsiDouble DLLScope operator+ (const smallint, const CAsiInt &);
            CAsiDouble operator+ (const integer) const;
     friend CAsiDouble DLLScope operator+ (const integer, const CAsiInt &);
            CAsiDouble operator+ (const real) const;
     friend CAsiDouble DLLScope operator+ (const real, const CAsiInt &);
            CAsiDouble operator+ (const int) const;
     friend CAsiDouble DLLScope operator+ (const int, const CAsiInt &);


            CAsiDouble operator- (const CAsiSmallInt &) const;
     friend CAsiDouble DLLScope operator- (const CAsiSmallInt &, const CAsiInt &);
            CAsiDouble operator- (const CAsiInt &) const;
            CAsiDouble operator- (const smallint)  const;
     friend CAsiDouble DLLScope operator- (const smallint, const CAsiInt &);
            CAsiDouble operator- (const integer) const;
     friend CAsiDouble DLLScope operator- (const integer, const CAsiInt &);
            CAsiDouble operator- (const real) const;
     friend CAsiDouble DLLScope operator- (const real, const CAsiInt &);
            CAsiDouble operator- (const int) const;
     friend CAsiDouble DLLScope operator- (const int, const CAsiInt &);

            CAsiDouble operator* (const CAsiSmallInt &) const;
     friend CAsiDouble DLLScope operator* (const CAsiSmallInt &, const CAsiInt &);
            CAsiDouble operator* (const CAsiInt &) const;
            CAsiDouble operator* (const smallint)  const;
     friend CAsiDouble DLLScope operator* (const smallint, const CAsiInt &);
            CAsiDouble operator* (const integer) const;
     friend CAsiDouble DLLScope operator* (const integer, const CAsiInt &);
            CAsiDouble operator* (const real) const;
     friend CAsiDouble DLLScope operator* (const real, const CAsiInt &);
            CAsiDouble operator* (const int) const;
     friend CAsiDouble DLLScope operator* (const int, const CAsiInt &);

            CAsiDouble operator/ (const CAsiSmallInt &) const;
     friend CAsiDouble DLLScope operator/ (const CAsiSmallInt &, const CAsiInt &);
            CAsiDouble operator/ (const CAsiInt &) const;
            CAsiDouble operator/ (const smallint) const;
     friend CAsiDouble DLLScope operator/ (const smallint, const CAsiInt &);
            CAsiDouble operator/ (const integer) const;
     friend CAsiDouble DLLScope operator/ (const integer, const CAsiInt &);
            CAsiDouble operator/ (const real) const;
     friend CAsiDouble DLLScope operator/ (const real, const CAsiInt &);
            CAsiDouble operator/ (const int) const;
     friend CAsiDouble DLLScope operator/ (const int, const CAsiInt &);

            CAsiInt &operator-- (void);
            CAsiInt &operator++ (void);

            CAsiInt &operator-  (void);

private:
    integer ivalue;
};


////////////////////////////////////////////////
//
//
class CAsiNumeric: public CAsiExactNum
//
// NUMERIC
//
{
friend class CAsiDecimal;
private:
    //  private helper
            EAsiBoolean SetNumeric (real);
//
public:
                                CAsiNumeric     (uint, uint);
                                CAsiNumeric     (uint);
                                CAsiNumeric     (const CAsiNumeric &);
                                CAsiNumeric     (void);
    virtual                     ~CAsiNumeric    (void);

    //  Get data descriptor
    //
    virtual EAsiDataType Type           (void) const;
    virtual uint         ReturnLength   (void) const;

    virtual CAsiData *   checkAdd       (const CAsiData *) const;
    virtual CAsiData *   checkSub       (const CAsiData *) const;
    virtual CAsiData *   checkMul       (const CAsiData *) const;
    virtual CAsiData *   checkDiv       (const CAsiData *) const;
    virtual CAsiData *   checkSet       (const CAsiData *) const;

    virtual EAsiBoolean  isEqualTo      (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan  (const CAsiData &) const;



    // Store Data value
    //
    virtual EAsiBoolean   storeValue (real);
    virtual EAsiBoolean   storeValue (integer);
    virtual EAsiBoolean   storeValue (smallint);
    virtual EAsiBoolean   storeValue (char *, uint);
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue (const CAsiData &);
    virtual EAsiBoolean   storeValue (const DB_NUMERIC *);

    // ****
    virtual EAsiBoolean   storeValue (char *, uint, uint *);
    virtual EAsiBoolean   storeValue (const AsiUcStr);

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;

    virtual EAsiBoolean   SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

    //  Get data value
    //
    virtual integer       intValue  (void) const;
    virtual real          realValue (void) const;

    virtual EAsiBoolean   getValue (real *) const;
    virtual EAsiBoolean   getValue (integer *) const;
    virtual EAsiBoolean   getValue (smallint *) const;
    virtual EAsiBoolean   getValue (char *, uint) const;
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;
    virtual EAsiBoolean   getValue (DB_NUMERIC *) const;

    // ****
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *) ;

    // Duplicate itself
    //
    virtual CAsiObject     *duplicate (void) const;

    // Operators
    //
            // Assignment
            CAsiNumeric &operator= (const CAsiSmallInt &);
            CAsiNumeric &operator= (const CAsiInt &);
            CAsiNumeric &operator= (const CAsiNumeric &);
            CAsiNumeric &operator= (const CAsiDecimal &);
            CAsiNumeric &operator= (const CAsiFloat &);
            CAsiNumeric &operator= (const CAsiReal &);
            CAsiNumeric &operator= (const CAsiDouble &);
            CAsiNumeric &operator= (const smallint);
            CAsiNumeric &operator= (const integer);
            CAsiNumeric &operator= (const real);
            CAsiNumeric &operator= (const int);

            // Arithmetic operators

            CAsiNumeric &operator+= (const CAsiSmallInt &);
            CAsiNumeric &operator+= (const CAsiInt &);
            CAsiNumeric &operator+= (const CAsiNumeric &);
            CAsiNumeric &operator+= (const CAsiDecimal &);
            CAsiNumeric &operator+= (const CAsiFloat &);
            CAsiNumeric &operator+= (const CAsiReal &);
            CAsiNumeric &operator+= (const CAsiDouble &);
            CAsiNumeric &operator+= (const smallint);
            CAsiNumeric &operator+= (const integer);
            CAsiNumeric &operator+= (const real);
            CAsiNumeric &operator+= (const int);

            CAsiNumeric &operator-= (const CAsiSmallInt &);
            CAsiNumeric &operator-= (const CAsiInt &);
            CAsiNumeric &operator-= (const CAsiNumeric &);
            CAsiNumeric &operator-= (const CAsiDecimal &);
            CAsiNumeric &operator-= (const CAsiFloat &);
            CAsiNumeric &operator-= (const CAsiReal &);
            CAsiNumeric &operator-= (const CAsiDouble &);
            CAsiNumeric &operator-= (const smallint);
            CAsiNumeric &operator-= (const integer);
            CAsiNumeric &operator-= (const real);
            CAsiNumeric &operator-= (const int);

            CAsiNumeric &operator*= (const CAsiSmallInt &);
            CAsiNumeric &operator*= (const CAsiInt &);
            CAsiNumeric &operator*= (const CAsiNumeric &);
            CAsiNumeric &operator*= (const CAsiDecimal &);
            CAsiNumeric &operator*= (const CAsiFloat &);
            CAsiNumeric &operator*= (const CAsiReal &);
            CAsiNumeric &operator*= (const CAsiDouble &);
            CAsiNumeric &operator*= (const smallint);
            CAsiNumeric &operator*= (const integer);
            CAsiNumeric &operator*= (const real);
            CAsiNumeric &operator*= (const int);

            CAsiNumeric &operator/= (const CAsiSmallInt &);
            CAsiNumeric &operator/= (const CAsiInt &);
            CAsiNumeric &operator/= (const CAsiNumeric &);
            CAsiNumeric &operator/= (const CAsiDecimal &);
            CAsiNumeric &operator/= (const CAsiFloat &);
            CAsiNumeric &operator/= (const CAsiReal &);
            CAsiNumeric &operator/= (const CAsiDouble &);
            CAsiNumeric &operator/= (const smallint);
            CAsiNumeric &operator/= (const integer);
            CAsiNumeric &operator/= (const real);
            CAsiNumeric &operator/= (const int);

            CAsiDouble operator+ (const CAsiSmallInt &) const;
            CAsiDouble operator+ (const CAsiInt &)      const;
            CAsiDouble operator+ (const CAsiNumeric &)  const;
     friend CAsiDouble DLLScope operator+ (const CAsiSmallInt &, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator+ (const CAsiInt &, const CAsiNumeric &);
            CAsiDouble operator+ (const smallint) const;
            CAsiDouble operator+ (const integer)  const;
            CAsiDouble operator+ (const real)     const;
            CAsiDouble operator+ (const int)      const;
     friend CAsiDouble DLLScope operator+ (const smallint, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator+ (const integer, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator+ (const real, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator+ (const int, const CAsiNumeric &);

            CAsiDouble operator- (const CAsiSmallInt &) const;
            CAsiDouble operator- (const CAsiInt &)      const;
            CAsiDouble operator- (const CAsiNumeric &)  const;
     friend CAsiDouble DLLScope operator- (const CAsiSmallInt &, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator- (const CAsiInt &, const CAsiNumeric &);
            CAsiDouble operator- (const smallint) const;
            CAsiDouble operator- (const integer)  const;
            CAsiDouble operator- (const real)     const;
            CAsiDouble operator- (const int)      const;
     friend CAsiDouble DLLScope operator- (const smallint, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator- (const integer, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator- (const real, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator- (const int, const CAsiNumeric &) ;

            CAsiDouble operator* (const CAsiSmallInt &) const;
            CAsiDouble operator* (const CAsiInt &)      const;
            CAsiDouble operator* (const CAsiNumeric &)  const;
     friend CAsiDouble DLLScope operator* (const CAsiSmallInt &, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator* (const CAsiInt &, const CAsiNumeric &);
            CAsiDouble operator* (const smallint) const;
            CAsiDouble operator* (const integer)  const;
            CAsiDouble operator* (const real)     const;
            CAsiDouble operator* (const int)      const;
     friend CAsiDouble DLLScope operator* (const smallint, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator* (const integer, const CAsiNumeric &) ;
     friend CAsiDouble DLLScope operator* (const real, const CAsiNumeric &)    ;
     friend CAsiDouble DLLScope operator* (const int, const CAsiNumeric &)     ;

            CAsiDouble operator/ (const CAsiSmallInt &) const;
            CAsiDouble operator/ (const CAsiInt &)      const;
            CAsiDouble operator/ (const CAsiNumeric &)  const;
     friend CAsiDouble DLLScope operator/ (const CAsiSmallInt &, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator/ (const CAsiInt &, const CAsiNumeric &)     ;
            CAsiDouble operator/ (const smallint) const;
            CAsiDouble operator/ (const integer)  const;
            CAsiDouble operator/ (const real)     const;
            CAsiDouble operator/ (const int)      const;
     friend CAsiDouble DLLScope operator/ (const smallint, const CAsiNumeric &);
     friend CAsiDouble DLLScope operator/ (const integer, const CAsiNumeric &) ;
     friend CAsiDouble DLLScope operator/ (const real, const CAsiNumeric &)    ;
     friend CAsiDouble DLLScope operator/ (const int, const CAsiNumeric &)     ;

            CAsiNumeric &operator++ (void);
            CAsiNumeric &operator-- (void);

            CAsiNumeric &operator- (void);

private:
        ASIBCD  bcdvalue;

};


////////////////////////////////////////////////
//
//
class CAsiDecimal: public CAsiExactNum
//
// DECIMAL
//
{
friend class CAsiNumeric;
private:
    //  private helper
            EAsiBoolean SetDecimal (real);

public:
            CAsiDecimal  (uint, uint);
            CAsiDecimal  (uint);
            CAsiDecimal  (const CAsiDecimal &);
            CAsiDecimal  (void);
    virtual ~CAsiDecimal (void);

    //  Get data descriptor
    //
    virtual EAsiDataType Type          (void) const;
    virtual uint         ReturnLength  (void) const;

    virtual CAsiData *   checkAdd      (const CAsiData *) const;
    virtual CAsiData *   checkSub      (const CAsiData *) const;
    virtual CAsiData *   checkMul      (const CAsiData *) const;
    virtual CAsiData *   checkDiv      (const CAsiData *) const;
    virtual CAsiData *   checkSet      (const CAsiData *) const;

    virtual EAsiBoolean  isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean   storeValue (real);
    virtual EAsiBoolean   storeValue (integer);
    virtual EAsiBoolean   storeValue (smallint);
    virtual EAsiBoolean   storeValue (char *, uint);
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue (const CAsiData &);
    virtual EAsiBoolean   storeValue (LARGE_INTEGER);
    virtual EAsiBoolean   storeValue (ULARGE_INTEGER);
    virtual EAsiBoolean   storeValue (const DECIMAL &);

    // ****
    virtual EAsiBoolean   storeValue (char *, uint, uint *);
    virtual EAsiBoolean   storeValue (const AsiUcStr);

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;

    virtual EAsiBoolean   SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

    //  Get data value
    //
    virtual integer       intValue  (void) const;
    virtual real          realValue (void) const;

    virtual EAsiBoolean   getValue (real *) const;
    virtual EAsiBoolean   getValue (integer *) const;
    virtual EAsiBoolean   getValue (smallint *) const;
    virtual EAsiBoolean   getValue (char *, uint) const;
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;
    virtual EAsiBoolean   getValue (LARGE_INTEGER *) const;
    virtual EAsiBoolean   getValue (ULARGE_INTEGER *) const;
    virtual EAsiBoolean   getValue (DECIMAL *) const;

    // ****
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
    //
            // Assignment
            CAsiDecimal &operator= (const CAsiSmallInt &);
            CAsiDecimal &operator= (const CAsiInt &);
            CAsiDecimal &operator= (const CAsiNumeric &);
            CAsiDecimal &operator= (const CAsiDecimal &);
            CAsiDecimal &operator= (const CAsiFloat &);
            CAsiDecimal &operator= (const CAsiReal &);
            CAsiDecimal &operator= (const CAsiDouble &);
            CAsiDecimal &operator= (const smallint);
            CAsiDecimal &operator= (const integer);
            CAsiDecimal &operator= (const real);
            CAsiDecimal &operator= (const int);

            // Arithmetic operators

            CAsiDecimal &operator+= (const CAsiSmallInt &);
            CAsiDecimal &operator+= (const CAsiInt &);
            CAsiDecimal &operator+= (const CAsiNumeric &);
            CAsiDecimal &operator+= (const CAsiDecimal &);
            CAsiDecimal &operator+= (const CAsiFloat &);
            CAsiDecimal &operator+= (const CAsiReal &);
            CAsiDecimal &operator+= (const CAsiDouble &);
            CAsiDecimal &operator+= (const smallint);
            CAsiDecimal &operator+= (const integer);
            CAsiDecimal &operator+= (const real);
            CAsiDecimal &operator+= (const int);

            CAsiDecimal &operator-= (const CAsiSmallInt &);
            CAsiDecimal &operator-= (const CAsiInt &);
            CAsiDecimal &operator-= (const CAsiNumeric &);
            CAsiDecimal &operator-= (const CAsiDecimal &);
            CAsiDecimal &operator-= (const CAsiFloat &);
            CAsiDecimal &operator-= (const CAsiReal &);
            CAsiDecimal &operator-= (const CAsiDouble &);
            CAsiDecimal &operator-= (const smallint);
            CAsiDecimal &operator-= (const integer);
            CAsiDecimal &operator-= (const real);
            CAsiDecimal &operator-= (const int);

            CAsiDecimal &operator*= (const CAsiSmallInt &);
            CAsiDecimal &operator*= (const CAsiInt &);
            CAsiDecimal &operator*= (const CAsiNumeric &);
            CAsiDecimal &operator*= (const CAsiDecimal &);
            CAsiDecimal &operator*= (const CAsiFloat &);
            CAsiDecimal &operator*= (const CAsiReal &);
            CAsiDecimal &operator*= (const CAsiDouble &);
            CAsiDecimal &operator*= (const smallint);
            CAsiDecimal &operator*= (const integer);
            CAsiDecimal &operator*= (const real);
            CAsiDecimal &operator*= (const int);

            CAsiDecimal &operator/= (const CAsiSmallInt &);
            CAsiDecimal &operator/= (const CAsiInt &);
            CAsiDecimal &operator/= (const CAsiNumeric &);
            CAsiDecimal &operator/= (const CAsiDecimal &);
            CAsiDecimal &operator/= (const CAsiFloat &);
            CAsiDecimal &operator/= (const CAsiReal &);
            CAsiDecimal &operator/= (const CAsiDouble &);
            CAsiDecimal &operator/= (const smallint);
            CAsiDecimal &operator/= (const integer);
            CAsiDecimal &operator/= (const real);
            CAsiDecimal &operator/= (const int);

            CAsiDouble operator+ (const CAsiSmallInt &) const;
            CAsiDouble operator+ (const CAsiInt &)      const;
            CAsiDouble operator+ (const CAsiNumeric &)  const;
            CAsiDouble operator+ (const CAsiDecimal &)  const;
     friend CAsiDouble DLLScope operator+ (const CAsiSmallInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator+ (const CAsiInt &, const CAsiDecimal &)     ;
     friend CAsiDouble DLLScope operator+ (const CAsiNumeric &, const CAsiDecimal &) ;
            CAsiDouble operator+ (const smallint) const;
            CAsiDouble operator+ (const integer)  const;
            CAsiDouble operator+ (const real)     const;
     friend CAsiDouble DLLScope operator+ (const smallint, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator+ (const integer, const CAsiDecimal &) ;
     friend CAsiDouble DLLScope operator+ (const real, const CAsiDecimal &)    ;
            CAsiDouble operator+ (const int) const;
     friend CAsiDouble operator+ (const int, const CAsiDecimal &);


            CAsiDouble operator- (const CAsiSmallInt &) const;
            CAsiDouble operator- (const CAsiInt &)      const;
            CAsiDouble operator- (const CAsiNumeric &)  const;
            CAsiDouble operator- (const CAsiDecimal &)  const;
     friend CAsiDouble DLLScope operator- (const CAsiSmallInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator- (const CAsiInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator- (const CAsiNumeric &, const CAsiDecimal &);
            CAsiDouble operator- (const smallint) const;
            CAsiDouble operator- (const integer)  const;
            CAsiDouble operator- (const real)     const;
     friend CAsiDouble DLLScope operator- (const smallint, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator- (const integer, const CAsiDecimal &) ;
     friend CAsiDouble DLLScope operator- (const real, const CAsiDecimal &)    ;
            CAsiDouble operator- (const int) const;
     friend CAsiDouble DLLScope operator- (const int, const CAsiDecimal &);

            CAsiDouble operator* (const CAsiSmallInt &) const;
            CAsiDouble operator* (const CAsiInt &)      const;
            CAsiDouble operator* (const CAsiNumeric &)  const;
            CAsiDouble operator* (const CAsiDecimal &)  const;
     friend CAsiDouble DLLScope operator* (const CAsiSmallInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator* (const CAsiInt &, const CAsiDecimal &)     ;
     friend CAsiDouble DLLScope operator* (const CAsiNumeric &, const CAsiDecimal &) ;
            CAsiDouble operator* (const smallint) const;
            CAsiDouble operator* (const integer)  const;
            CAsiDouble operator* (const real)     const;
     friend CAsiDouble DLLScope operator* (const smallint, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator* (const integer, const CAsiDecimal &) ;
     friend CAsiDouble DLLScope operator* (const real, const CAsiDecimal &)    ;
            CAsiDouble operator* (const int) const                         ;
     friend CAsiDouble DLLScope operator* (const int, const CAsiDecimal &)     ;

            CAsiDouble operator/ (const CAsiSmallInt &) const;
            CAsiDouble operator/ (const CAsiInt &)      const;
            CAsiDouble operator/ (const CAsiNumeric &)  const;
            CAsiDouble operator/ (const CAsiDecimal &)  const;
     friend CAsiDouble DLLScope operator/ (const CAsiSmallInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator/ (const CAsiInt &, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator/ (const CAsiNumeric &, const CAsiDecimal &);
            CAsiDouble operator/ (const smallint) const;
            CAsiDouble operator/ (const integer)  const;
            CAsiDouble operator/ (const real)     const;
     friend CAsiDouble DLLScope operator/ (const smallint, const CAsiDecimal &);
     friend CAsiDouble DLLScope operator/ (const integer, const CAsiDecimal &) ;
     friend CAsiDouble DLLScope operator/ (const real, const CAsiDecimal &)    ;
            CAsiDouble operator/ (const int) const;
     friend CAsiDouble DLLScope operator/ (const int, const CAsiDecimal &);

            CAsiDecimal &operator++ (void);
            CAsiDecimal &operator-- (void);
            CAsiDecimal &operator- (void);

private:
    EAsiBoolean fmt;
    ASIBCD      bcdvalue;
    double      realvalue;

};


////////////////////////////////////////////////
//
//
class CAsiFloat: public CAsiApproxNum
//
// FLOAT
//
{
public:
                                CAsiFloat               (void);
                                CAsiFloat               (uint);
                                CAsiFloat               (const CAsiFloat &);
    virtual                     ~CAsiFloat              (void);

    //  Get data descriptor
    //
    virtual EAsiDataType Type           (void) const;
    virtual uint         ReturnLength   (void) const;

    virtual CAsiData *   checkAdd       (const CAsiData *) const;
    virtual CAsiData *   checkSub       (const CAsiData *) const;
    virtual CAsiData *   checkMul       (const CAsiData *) const;
    virtual CAsiData *   checkDiv       (const CAsiData *) const;
    virtual CAsiData *   checkSet       (const CAsiData *) const;


    virtual EAsiBoolean  isEqualTo      (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan  (const CAsiData &) const;


    // Store Data value
    //
    virtual EAsiBoolean   storeValue    (real);
    virtual EAsiBoolean   storeValue    (integer);
    virtual EAsiBoolean   storeValue    (smallint);
    virtual EAsiBoolean   storeValue    (char *, uint);
    virtual EAsiBoolean   storeValue    (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue    (const CAsiData &);

    // ****
    virtual EAsiBoolean   storeValue    (char *, uint, uint *);
    virtual EAsiBoolean   storeValue    (const AsiUcStr);

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;

    virtual EAsiBoolean   SQLType       (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral    (CAsiUcStr *) const;        // SQL compatible literal

    //  Get data value
    //
    virtual integer       intValue      (void) const;
    virtual real          realValue     (void) const;

    virtual EAsiBoolean   getValue              (real *) const;
    virtual EAsiBoolean   getValue              (integer *) const;
    virtual EAsiBoolean   getValue              (smallint *) const;
    virtual EAsiBoolean   getValue              (char *, uint) const;
    virtual EAsiBoolean   getValue              (CAsiUcStr *) const;

    // ****
    virtual EAsiBoolean   getValue              (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue              (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue              (CAsiData &) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize      (void) const;
    virtual unsigned long packTo        (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom    (CAsiObjPack *);

    virtual unsigned long packValueSize (void)  const;
    virtual unsigned long packValueTo   (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate     (void) const;

    // Operators
    //
            // Assignment
            CAsiFloat &operator= (const CAsiSmallInt &);
            CAsiFloat &operator= (const CAsiInt &);
            CAsiFloat &operator= (const CAsiNumeric &);
            CAsiFloat &operator= (const CAsiDecimal &);
            CAsiFloat &operator= (const CAsiFloat &);
            CAsiFloat &operator= (const CAsiReal &);
            CAsiFloat &operator= (const CAsiDouble &);
            CAsiFloat &operator= (const smallint);
            CAsiFloat &operator= (const integer);
            CAsiFloat &operator= (const real);
            CAsiFloat &operator= (const int);

            // Arithmetic operators
            CAsiFloat &operator+= (const CAsiSmallInt &);
            CAsiFloat &operator+= (const CAsiInt &);
            CAsiFloat &operator+= (const CAsiNumeric &);
            CAsiFloat &operator+= (const CAsiDecimal &);
            CAsiFloat &operator+= (const CAsiFloat &);
            CAsiFloat &operator+= (const CAsiReal &);
            CAsiFloat &operator+= (const CAsiDouble &);
            CAsiFloat &operator+= (const smallint);
            CAsiFloat &operator+= (const integer);
            CAsiFloat &operator+= (const real);
            CAsiFloat &operator+= (const int);

            CAsiFloat &operator-= (const CAsiSmallInt &);
            CAsiFloat &operator-= (const CAsiInt &);
            CAsiFloat &operator-= (const CAsiNumeric &);
            CAsiFloat &operator-= (const CAsiDecimal &);
            CAsiFloat &operator-= (const CAsiFloat &);
            CAsiFloat &operator-= (const CAsiReal &);
            CAsiFloat &operator-= (const CAsiDouble &);
            CAsiFloat &operator-= (const smallint);
            CAsiFloat &operator-= (const integer);
            CAsiFloat &operator-= (const real);
            CAsiFloat &operator-= (const int);

            CAsiFloat &operator*= (const CAsiSmallInt &);
            CAsiFloat &operator*= (const CAsiInt &);
            CAsiFloat &operator*= (const CAsiNumeric &);
            CAsiFloat &operator*= (const CAsiDecimal &);
            CAsiFloat &operator*= (const CAsiFloat &);
            CAsiFloat &operator*= (const CAsiReal &);
            CAsiFloat &operator*= (const CAsiDouble &);
            CAsiFloat &operator*= (const smallint);
            CAsiFloat &operator*= (const integer);
            CAsiFloat &operator*= (const real);
            CAsiFloat &operator*= (const int);

            CAsiFloat &operator/= (const CAsiSmallInt &);
            CAsiFloat &operator/= (const CAsiInt &);
            CAsiFloat &operator/= (const CAsiNumeric &);
            CAsiFloat &operator/= (const CAsiDecimal &);
            CAsiFloat &operator/= (const CAsiFloat &);
            CAsiFloat &operator/= (const CAsiReal &);
            CAsiFloat &operator/= (const CAsiDouble &);
            CAsiFloat &operator/= (const smallint);
            CAsiFloat &operator/= (const integer);
            CAsiFloat &operator/= (const real);
            CAsiFloat &operator/= (const int);

            CAsiFloat operator+ (const CAsiSmallInt &) const;
            CAsiFloat operator+ (const CAsiInt &)      const;
            CAsiFloat operator+ (const CAsiNumeric &)  const;
            CAsiFloat operator+ (const CAsiDecimal &)  const;
            CAsiFloat operator+ (const CAsiFloat &)    const;
     friend CAsiFloat DLLScope operator+ (const CAsiSmallInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator+ (const CAsiInt &, const CAsiFloat &)     ;
     friend CAsiFloat DLLScope operator+ (const CAsiNumeric &, const CAsiFloat &) ;
     friend CAsiFloat DLLScope operator+ (const CAsiDecimal &, const CAsiFloat &) ;
            CAsiFloat operator+ (const smallint) const;
            CAsiFloat operator+ (const integer)  const;
            CAsiFloat operator+ (const real)     const;
     friend CAsiFloat DLLScope operator+ (const smallint, const CAsiFloat &);
     friend CAsiFloat DLLScope operator+ (const integer, const CAsiFloat &) ;
     friend CAsiFloat DLLScope operator+ (const real, const CAsiFloat &)    ;
            CAsiFloat operator+ (const int) const;
     friend CAsiFloat DLLScope operator+ (const int, const CAsiFloat &);

            CAsiFloat operator- (const CAsiSmallInt &) const;
            CAsiFloat operator- (const CAsiInt &)      const;
            CAsiFloat operator- (const CAsiNumeric &)  const;
            CAsiFloat operator- (const CAsiDecimal &)  const;
            CAsiFloat operator- (const CAsiFloat &)    const;
     friend CAsiFloat DLLScope operator- (const CAsiSmallInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator- (const CAsiInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator- (const CAsiNumeric &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator- (const CAsiDecimal &, const CAsiFloat &);
            CAsiFloat operator- (const smallint) const;
            CAsiFloat operator- (const integer)  const;
            CAsiFloat operator- (const real)     const;
     friend CAsiFloat DLLScope operator- (const smallint, const CAsiFloat &);
     friend CAsiFloat DLLScope operator- (const integer, const CAsiFloat &);
     friend CAsiFloat DLLScope operator- (const real, const CAsiFloat &);
            CAsiFloat operator- (const int) const;
     friend CAsiFloat DLLScope operator- (const int, const CAsiFloat &);

            CAsiFloat operator* (const CAsiSmallInt &) const;
            CAsiFloat operator* (const CAsiInt &)      const;
            CAsiFloat operator* (const CAsiNumeric &)  const;
            CAsiFloat operator* (const CAsiDecimal &)  const;
            CAsiFloat operator* (const CAsiFloat &)    const;
     friend CAsiFloat DLLScope operator* (const CAsiSmallInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator* (const CAsiInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator* (const CAsiNumeric &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator* (const CAsiDecimal &, const CAsiFloat &);
            CAsiFloat operator* (const smallint) const;
            CAsiFloat operator* (const integer)  const;
            CAsiFloat operator* (const real)     const;
     friend CAsiFloat DLLScope operator* (const smallint, const CAsiFloat &);
     friend CAsiFloat DLLScope operator* (const integer, const CAsiFloat &);
     friend CAsiFloat DLLScope operator* (const real, const CAsiFloat &);
            CAsiFloat operator* (const int) const;
     friend CAsiFloat DLLScope operator* (const int, const CAsiFloat &);

            CAsiFloat operator/ (const CAsiSmallInt &) const;
            CAsiFloat operator/ (const CAsiInt &)      const;
            CAsiFloat operator/ (const CAsiNumeric &)  const;
            CAsiFloat operator/ (const CAsiDecimal &)  const;
            CAsiFloat operator/ (const CAsiFloat &)    const;
     friend CAsiFloat DLLScope operator/ (const CAsiSmallInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator/ (const CAsiInt &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator/ (const CAsiNumeric &, const CAsiFloat &);
     friend CAsiFloat DLLScope operator/ (const CAsiDecimal &, const CAsiFloat &);
            CAsiFloat operator/ (const smallint) const;
            CAsiFloat operator/ (const integer)  const;
            CAsiFloat operator/ (const real)     const;
     friend CAsiFloat DLLScope operator/ (const smallint, const CAsiFloat &);
     friend CAsiFloat DLLScope operator/ (const integer, const CAsiFloat &);
     friend CAsiFloat DLLScope operator/ (const real, const CAsiFloat &)   ;
            CAsiFloat operator/ (const int) const;
     friend CAsiFloat DLLScope operator/ (const int, const CAsiFloat &);

            CAsiFloat &operator++ (void);
            CAsiFloat &operator-- (void);
            CAsiFloat &operator- (void);

private:
    real fvalue;
};



////////////////////////////////////////////////
//
//
class CAsiReal: public CAsiApproxNum
//
// REAL
//
// This class introduces functionality of the SQL REAL data.
// It redefines all arithmetic and comparision operators in which
// real number can be involved in SQL. Memeber functions also allow
// to set and retrieve value of the internal real number in double and
// integer formats.

{
public:
                                CAsiReal                (void);
                                CAsiReal                (const CAsiReal &);
        virtual                 ~CAsiReal               (void);

    //  Get data descriptor
    //
    virtual EAsiDataType        Type                    (void) const;
    virtual uint                ReturnLength    (void) const;

    virtual CAsiData *          checkAdd        (const CAsiData *) const;
    virtual CAsiData *          checkSub        (const CAsiData *) const;
    virtual CAsiData *          checkMul        (const CAsiData *) const;
    virtual CAsiData *          checkDiv        (const CAsiData *) const;
    virtual CAsiData *          checkSet        (const CAsiData *) const;

    virtual EAsiBoolean         isEqualTo       (const CAsiData &) const;
    virtual EAsiBoolean         isGreaterThan   (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean         storeValue              (real);
    virtual EAsiBoolean         storeValue              (integer);
    virtual EAsiBoolean         storeValue              (smallint);
    virtual EAsiBoolean         storeValue              (char *, uint);
    virtual EAsiBoolean         storeValue              (const CAsiUcStr &);
    virtual EAsiBoolean         storeValue              (const CAsiData &);

    // ****
    virtual EAsiBoolean         storeValue              (char *, uint, uint *);
    virtual EAsiBoolean         storeValue              (const AsiUcStr);

    virtual EAsiBoolean         SQLType                 (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean         SQLLiteral              (CAsiUcStr *) const;        // SQL compatible literal

    //  Get data value
    //
    virtual integer             intValue                (void) const;
    virtual real                realValue               (void) const;

    virtual EAsiBoolean         getValue                (real *) const;
    virtual EAsiBoolean         getValue                (integer *) const;
    virtual EAsiBoolean         getValue                (smallint *) const;
    virtual EAsiBoolean         getValue                (char *, uint) const;
    virtual EAsiBoolean         getValue                (CAsiUcStr *) const;

    // ****
    virtual EAsiBoolean         getValue                (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean         getValue                (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean         getValue                (CAsiData &) const;

    virtual DBCOLUMNINFO *		MapAsiToColumnInfo		(DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *		MapAsiToParamInfo		(DBPARAMINFO *) const;



    // Runtime class iteraction functions
    //
    virtual unsigned long       packSize        (void) const;
    virtual unsigned long       packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean         unpackFrom      (CAsiObjPack *);

    virtual unsigned long       packValueSize   (void)  const;
    virtual unsigned long       packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean         unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *      duplicate               (void) const;

    // Operators
    //
            // Assignment
            CAsiReal &operator= (const CAsiSmallInt &);
            CAsiReal &operator= (const CAsiInt &);
            CAsiReal &operator= (const CAsiNumeric &);
            CAsiReal &operator= (const CAsiDecimal &);
            CAsiReal &operator= (const CAsiFloat &);
            CAsiReal &operator= (const CAsiReal &);
            CAsiReal &operator= (const CAsiDouble &);
            CAsiReal &operator= (const smallint);
            CAsiReal &operator= (const integer);
            CAsiReal &operator= (const real);
            CAsiReal &operator= (const int);

            // Arithmetic operators
            CAsiReal &operator+= (const CAsiSmallInt &);
            CAsiReal &operator+= (const CAsiInt &);
            CAsiReal &operator+= (const CAsiNumeric &);
            CAsiReal &operator+= (const CAsiDecimal &);
            CAsiReal &operator+= (const CAsiFloat &);
            CAsiReal &operator+= (const CAsiReal &);
            CAsiReal &operator+= (const CAsiDouble &);
            CAsiReal &operator+= (const smallint);
            CAsiReal &operator+= (const integer);
            CAsiReal &operator+= (const real);
            CAsiReal &operator+= (const int);

            CAsiReal &operator-= (const CAsiSmallInt &);
            CAsiReal &operator-= (const CAsiInt &);
            CAsiReal &operator-= (const CAsiNumeric &);
            CAsiReal &operator-= (const CAsiDecimal &);
            CAsiReal &operator-= (const CAsiFloat &);
            CAsiReal &operator-= (const CAsiReal &);
            CAsiReal &operator-= (const CAsiDouble &);
            CAsiReal &operator-= (const smallint);
            CAsiReal &operator-= (const integer);
            CAsiReal &operator-= (const real);
            CAsiReal &operator-= (const int);

            CAsiReal &operator*= (const CAsiSmallInt &);
            CAsiReal &operator*= (const CAsiInt &);
            CAsiReal &operator*= (const CAsiNumeric &);
            CAsiReal &operator*= (const CAsiDecimal &);
            CAsiReal &operator*= (const CAsiFloat &);
            CAsiReal &operator*= (const CAsiReal &);
            CAsiReal &operator*= (const CAsiDouble &);
            CAsiReal &operator*= (const smallint);
            CAsiReal &operator*= (const integer);
            CAsiReal &operator*= (const real);
            CAsiReal &operator*= (const int);

            CAsiReal &operator/= (const CAsiSmallInt &);
            CAsiReal &operator/= (const CAsiInt &);
            CAsiReal &operator/= (const CAsiNumeric &);
            CAsiReal &operator/= (const CAsiDecimal &);
            CAsiReal &operator/= (const CAsiFloat &);
            CAsiReal &operator/= (const CAsiReal &);
            CAsiReal &operator/= (const CAsiDouble &);
            CAsiReal &operator/= (const smallint);
            CAsiReal &operator/= (const integer);
            CAsiReal &operator/= (const real);
            CAsiReal &operator/= (const int);

            CAsiReal operator+ (const CAsiSmallInt &) const;
            CAsiReal operator+ (const CAsiInt &)      const;
            CAsiReal operator+ (const CAsiNumeric &)  const;
            CAsiReal operator+ (const CAsiDecimal &)  const;
            CAsiReal operator+ (const CAsiFloat &)    const;
            CAsiReal operator+ (const CAsiReal &)     const;
     friend CAsiReal DLLScope operator+ (const CAsiSmallInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator+ (const CAsiInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator+ (const CAsiNumeric &, const CAsiReal &);
     friend CAsiReal DLLScope operator+ (const CAsiDecimal &, const CAsiReal &);
     friend CAsiReal DLLScope operator+ (const CAsiFloat &, const CAsiReal &)  ;
            CAsiReal operator+ (const smallint) const;
            CAsiReal operator+ (const integer)  const;
            CAsiReal operator+ (const real)     const;
     friend CAsiReal DLLScope operator+ (const smallint, const CAsiReal &);
     friend CAsiReal DLLScope operator+ (const integer, const CAsiReal &) ;
     friend CAsiReal DLLScope operator+ (const real, const CAsiReal &)    ;
            CAsiReal operator+ (const int) const;
     friend CAsiReal DLLScope operator+ (const int, const CAsiReal &);

            CAsiReal operator- (const CAsiSmallInt &) const;
            CAsiReal operator- (const CAsiInt &)      const;
            CAsiReal operator- (const CAsiNumeric &)  const;
            CAsiReal operator- (const CAsiDecimal &)  const;
            CAsiReal operator- (const CAsiFloat &)    const;
            CAsiReal operator- (const CAsiReal &)     const;
     friend CAsiReal DLLScope operator- (const CAsiSmallInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const CAsiInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const CAsiNumeric &, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const CAsiDecimal &, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const CAsiFloat &, const CAsiReal &)  ;
            CAsiReal operator- (const smallint) const;
            CAsiReal operator- (const integer)  const;
            CAsiReal operator- (const real)     const;
     friend CAsiReal DLLScope operator- (const smallint, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const integer, const CAsiReal &);
     friend CAsiReal DLLScope operator- (const real, const CAsiReal &);
            CAsiReal operator- (const int) const;
     friend CAsiReal DLLScope operator- (const int, const CAsiReal &);

            CAsiReal operator* (const CAsiSmallInt &) const;
            CAsiReal operator* (const CAsiInt &)      const;
            CAsiReal operator* (const CAsiNumeric &)  const;
            CAsiReal operator* (const CAsiDecimal &)  const;
            CAsiReal operator* (const CAsiFloat &)    const;
            CAsiReal operator* (const CAsiReal &)     const;
     friend CAsiReal DLLScope operator* (const CAsiSmallInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator* (const CAsiInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator* (const CAsiNumeric &, const CAsiReal &);
     friend CAsiReal DLLScope operator* (const CAsiDecimal &, const CAsiReal &);
     friend CAsiReal DLLScope operator* (const CAsiFloat &, const CAsiReal &)  ;
            CAsiReal operator* (const smallint) const;
            CAsiReal operator* (const integer)  const;
            CAsiReal operator* (const real)     const;
     friend CAsiReal DLLScope operator* (const smallint, const CAsiReal &);
     friend CAsiReal DLLScope operator* (const integer, const CAsiReal &) ;
     friend CAsiReal DLLScope operator* (const real, const CAsiReal &)    ;
            CAsiReal operator* (const int) const;
     friend CAsiReal DLLScope operator* (const int, const CAsiReal &);

            CAsiReal operator/ (const CAsiSmallInt &) const;
            CAsiReal operator/ (const CAsiInt &)      const;
            CAsiReal operator/ (const CAsiNumeric &)  const;
            CAsiReal operator/ (const CAsiDecimal &)  const;
            CAsiReal operator/ (const CAsiFloat &)    const;
            CAsiReal operator/ (const CAsiReal &)     const;
     friend CAsiReal DLLScope operator/ (const CAsiSmallInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator/ (const CAsiInt &, const CAsiReal &);
     friend CAsiReal DLLScope operator/ (const CAsiNumeric &, const CAsiReal &);
     friend CAsiReal DLLScope operator/ (const CAsiDecimal &, const CAsiReal &);
     friend CAsiReal DLLScope operator/ (const CAsiFloat &, const CAsiReal &)  ;
            CAsiReal operator/ (const smallint) const;
            CAsiReal operator/ (const integer)  const;
            CAsiReal operator/ (const real)     const;
     friend CAsiReal DLLScope operator/ (const smallint, const CAsiReal &);
     friend CAsiReal DLLScope operator/ (const integer, const CAsiReal &) ;
     friend CAsiReal DLLScope operator/ (const real, const CAsiReal &);
            CAsiReal operator/ (const int) const;
     friend CAsiReal DLLScope operator/ (const int, const CAsiReal &);

            CAsiReal &operator++ (void);
            CAsiReal &operator-- (void);
            CAsiReal &operator- (void);

private:
    real rvalue;
};


////////////////////////////////////////////////
//
//
class CAsiDouble: public CAsiApproxNum
//
// DOUBLE PRECISION
//
{
public:
                                CAsiDouble              (void);
                                CAsiDouble              (const CAsiDouble &);
    virtual                     ~CAsiDouble     (void);

    //  Get data descriptor
    //
    virtual EAsiDataType Type           (void) const;
    virtual uint         ReturnLength   (void) const;

    virtual CAsiData *   checkAdd       (const CAsiData *) const;
    virtual CAsiData *   checkSub       (const CAsiData *) const;
    virtual CAsiData *   checkMul       (const CAsiData *) const;
    virtual CAsiData *   checkDiv       (const CAsiData *) const;
    virtual CAsiData *   checkSet       (const CAsiData *) const;

    virtual EAsiBoolean  isEqualTo      (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan  (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean   storeValue    (real);
    virtual EAsiBoolean   storeValue    (integer);
    virtual EAsiBoolean   storeValue    (smallint);
    virtual EAsiBoolean   storeValue    (char *, uint);
    virtual EAsiBoolean   storeValue    (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue    (const CAsiData &);

    // ****
    virtual EAsiBoolean   storeValue    (char *, uint, uint *);
    virtual EAsiBoolean   storeValue    (const AsiUcStr);

    //  Get data value
    //
    virtual integer       intValue      (void) const;
    virtual real          realValue     (void) const;

    virtual EAsiBoolean   getValue              (real *) const;
    virtual EAsiBoolean   getValue              (integer *) const;
    virtual EAsiBoolean   getValue              (smallint *) const;
    virtual EAsiBoolean   getValue              (char *, uint) const;
    virtual EAsiBoolean   getValue              (CAsiUcStr *) const;

    // ****
    virtual EAsiBoolean   getValue              (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue              (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue              (CAsiData &) const;

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean   SQLType       (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral    (CAsiUcStr *) const;        // SQL compatible literal

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
    //
            // Assignment
            CAsiDouble &operator= (const CAsiSmallInt &);
            CAsiDouble &operator= (const CAsiInt &);
            CAsiDouble &operator= (const CAsiNumeric &);
            CAsiDouble &operator= (const CAsiDecimal &);
            CAsiDouble &operator= (const CAsiFloat &);
            CAsiDouble &operator= (const CAsiReal &);
            CAsiDouble &operator= (const CAsiDouble &);
            CAsiDouble &operator= (const smallint);
            CAsiDouble &operator= (const integer);
            CAsiDouble &operator= (const real);
            CAsiDouble &operator= (const int);

            // Arithmetic operators
            CAsiDouble &operator+= (const CAsiSmallInt &);
            CAsiDouble &operator+= (const CAsiInt &);
            CAsiDouble &operator+= (const CAsiNumeric &);
            CAsiDouble &operator+= (const CAsiDecimal &);
            CAsiDouble &operator+= (const CAsiFloat &);
            CAsiDouble &operator+= (const CAsiReal &);
            CAsiDouble &operator+= (const CAsiDouble &);
            CAsiDouble &operator+= (const smallint);
            CAsiDouble &operator+= (const integer);
            CAsiDouble &operator+= (const real);
            CAsiDouble &operator+= (const int);

            CAsiDouble &operator-= (const CAsiSmallInt &);
            CAsiDouble &operator-= (const CAsiInt &);
            CAsiDouble &operator-= (const CAsiNumeric &);
            CAsiDouble &operator-= (const CAsiDecimal &);
            CAsiDouble &operator-= (const CAsiFloat &);
            CAsiDouble &operator-= (const CAsiReal &);
            CAsiDouble &operator-= (const CAsiDouble &);
            CAsiDouble &operator-= (const smallint);
            CAsiDouble &operator-= (const integer);
            CAsiDouble &operator-= (const real);
            CAsiDouble &operator-= (const int);

            CAsiDouble &operator*= (const CAsiSmallInt &);
            CAsiDouble &operator*= (const CAsiInt &);
            CAsiDouble &operator*= (const CAsiNumeric &);
            CAsiDouble &operator*= (const CAsiDecimal &);
            CAsiDouble &operator*= (const CAsiFloat &);
            CAsiDouble &operator*= (const CAsiReal &);
            CAsiDouble &operator*= (const CAsiDouble &);
            CAsiDouble &operator*= (const smallint);
            CAsiDouble &operator*= (const integer);
            CAsiDouble &operator*= (const real);
            CAsiDouble &operator*= (const int);

            CAsiDouble &operator/= (const CAsiSmallInt &);
            CAsiDouble &operator/= (const CAsiInt &);
            CAsiDouble &operator/= (const CAsiNumeric &);
            CAsiDouble &operator/= (const CAsiDecimal &);
            CAsiDouble &operator/= (const CAsiFloat &);
            CAsiDouble &operator/= (const CAsiReal &);
            CAsiDouble &operator/= (const CAsiDouble &);
            CAsiDouble &operator/= (const smallint);
            CAsiDouble &operator/= (const integer);
            CAsiDouble &operator/= (const real);
            CAsiDouble &operator/= (const int);

            CAsiDouble operator+ (const CAsiSmallInt &) const;
            CAsiDouble operator+ (const CAsiInt &)      const;
            CAsiDouble operator+ (const CAsiNumeric &)  const;
            CAsiDouble operator+ (const CAsiDecimal &)  const;
            CAsiDouble operator+ (const CAsiFloat &)    const;
            CAsiDouble operator+ (const CAsiReal &)     const;
            CAsiDouble operator+ (const CAsiDouble &)   const;
     friend CAsiDouble DLLScope operator+ (const CAsiSmallInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const CAsiInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const CAsiNumeric &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const CAsiDecimal &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const CAsiFloat &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const CAsiReal &, const CAsiDouble &);
            CAsiDouble operator+ (const smallint) const;
            CAsiDouble operator+ (const integer)  const;
            CAsiDouble operator+ (const real)     const;
     friend CAsiDouble DLLScope operator+ (const smallint, const CAsiDouble &);
     friend CAsiDouble DLLScope operator+ (const integer, const CAsiDouble &) ;
     friend CAsiDouble DLLScope operator+ (const real, const CAsiDouble &)    ;
            CAsiDouble operator+ (const int) const;
     friend CAsiDouble DLLScope operator+ (const int, const CAsiDouble &);

            CAsiDouble operator- (const CAsiSmallInt &) const;
            CAsiDouble operator- (const CAsiInt &)      const;
            CAsiDouble operator- (const CAsiNumeric &)  const;
            CAsiDouble operator- (const CAsiDecimal &)  const;
            CAsiDouble operator- (const CAsiFloat &)    const;
            CAsiDouble operator- (const CAsiReal &)     const;
            CAsiDouble operator- (const CAsiDouble &)   const;
     friend CAsiDouble DLLScope operator- (const CAsiSmallInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const CAsiInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const CAsiNumeric &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const CAsiDecimal &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const CAsiFloat &, const CAsiDouble &)  ;
     friend CAsiDouble DLLScope operator- (const CAsiReal &, const CAsiDouble &);
            CAsiDouble operator- (const smallint) const;
            CAsiDouble operator- (const integer)  const;
            CAsiDouble operator- (const real)     const;
     friend CAsiDouble DLLScope operator- (const smallint, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const integer, const CAsiDouble &);
     friend CAsiDouble DLLScope operator- (const real, const CAsiDouble &);
            CAsiDouble operator- (const int) const;
     friend CAsiDouble DLLScope operator- (const int, const CAsiDouble &);

            CAsiDouble operator* (const CAsiSmallInt &) const;
            CAsiDouble operator* (const CAsiInt &)      const;
            CAsiDouble operator* (const CAsiNumeric &)  const;
            CAsiDouble operator* (const CAsiDecimal &)  const;
            CAsiDouble operator* (const CAsiFloat &)    const;
            CAsiDouble operator* (const CAsiReal &)     const;
            CAsiDouble operator* (const CAsiDouble &)   const;
     friend CAsiDouble DLLScope operator* (const CAsiSmallInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const CAsiInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const CAsiNumeric &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const CAsiDecimal &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const CAsiFloat &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const CAsiReal &, const CAsiDouble &);
            CAsiDouble operator* (const smallint) const;
            CAsiDouble operator* (const integer) const;
            CAsiDouble operator* (const real) const;
     friend CAsiDouble DLLScope operator* (const smallint, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const integer, const CAsiDouble &);
     friend CAsiDouble DLLScope operator* (const real, const CAsiDouble &);
            CAsiDouble operator* (const int) const;
     friend CAsiDouble DLLScope operator* (const int, const CAsiDouble &);

            CAsiDouble operator/ (const CAsiSmallInt &) const;
            CAsiDouble operator/ (const CAsiInt &)      const;
            CAsiDouble operator/ (const CAsiNumeric &)  const;
            CAsiDouble operator/ (const CAsiDecimal &)  const;
            CAsiDouble operator/ (const CAsiFloat &)    const;
            CAsiDouble operator/ (const CAsiReal &)     const;
            CAsiDouble operator/ (const CAsiDouble &)   const;
     friend CAsiDouble DLLScope operator/ (const CAsiSmallInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const CAsiInt &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const CAsiNumeric &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const CAsiDecimal &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const CAsiFloat &, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const CAsiReal &, const CAsiDouble &);
            CAsiDouble operator/ (const smallint) const;
            CAsiDouble operator/ (const integer)  const;
            CAsiDouble operator/ (const real)     const;
     friend CAsiDouble DLLScope operator/ (const smallint, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const integer, const CAsiDouble &);
     friend CAsiDouble DLLScope operator/ (const real, const CAsiDouble &);
            CAsiDouble operator/ (const int) const;
     friend CAsiDouble DLLScope operator/ (const int, const CAsiDouble &);

            CAsiDouble &operator++ (void);
            CAsiDouble &operator-- (void);
            CAsiDouble &operator- (void);


private:
    real dvalue;
};


////////////////////////////////////////////////
//
//
class CAsiChar: public CAsiData
//
// CHARACTER and CHAR VARYING
//
{
friend class CAsiTempTable;
public:
    // Construction/Destruction
    //
                                        CAsiChar                ();
                                        CAsiChar                (uint);
                                        CAsiChar                (const CAsiChar &);
        virtual                                 ~CAsiChar               ();


    // Set Varying, National, Character set name, and Collation
    void                                setVarying      (void);
    void                                setNational     (void);
    void                                setCharSet      (const CAsiUcStr &);
    void                                setDefCharSet   (void);
    void                                setCollName     (const CAsiUcStr &);
    void                                setCollIdent    (AsiUcIdCLT);
    void                                setCoerc        (EAsiCAttr);

    // Get data descriptor
    //
    virtual EAsiDataType    Type                (void) const;
    virtual uint            Length              (void) const;
    virtual uint            ReturnLength        (void) const;

    uint                        ByteSize        (void) const;
    const CAsiUcStr   &         CollName        (void) const;
    const CAsiUcStr   &         CharSetName     (void) const;
    AsiUcIdCLT                  CollIdent       (void) const;
    AsiUcIdCCT                  CharSetIdent    (void) const;
    EAsiCAttr                   Coercibility    (void) const;

    //  is_ functions
    //
    virtual EAsiBoolean         is_character    (void) const;
    virtual EAsiBoolean         is_comparable   (const CAsiData *) const;
    virtual EAsiBoolean         is_storable     (const CAsiData *) const;
    virtual EAsiBoolean         is_castable     (const CAsiData *) const;
            EAsiBoolean         is_national     (void) const;

    virtual CAsiData *          checkCat        (const CAsiData *) const;
    virtual CAsiData *          checkSet        (const CAsiData *) const;

    virtual EAsiBoolean         isEqualTo       (const CAsiData &) const;
    virtual EAsiBoolean         isGreaterThan   (const CAsiData &) const;


    // Store Data value
    //
    virtual EAsiBoolean         storeValue              (real);
    virtual EAsiBoolean         storeValue              (integer);
    virtual EAsiBoolean         storeValue              (smallint);
    virtual EAsiBoolean         storeValue              (char *, uint);
            EAsiBoolean         storeValue              (char *, uint, AsiUcIdCCT);
    virtual EAsiBoolean         storeValue              (const CAsiUcStr &);
    virtual EAsiBoolean         storeValue              (const CAsiData &);
    virtual EAsiBoolean         storeValue              (const AsiUcStr);
            EAsiBoolean         storeValue              (GUID *);
    virtual EAsiBoolean         storeValue              (char *, uint, uint *); // Binary Buffer

    //  Get data value
    //
        const CAsiUcStr  &      charValue (void) const;   // Reference to string

    virtual EAsiBoolean         getValue                (real *) const;
    virtual EAsiBoolean         getValue                (integer *) const;
    virtual EAsiBoolean         getValue                (smallint *) const;
    virtual EAsiBoolean         getValue                (char *, uint) const;
    virtual EAsiBoolean         getValue                (CAsiUcStr *) const;
    virtual EAsiBoolean         getValue                (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean         getValue                (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean         getValue                (CAsiData &) const;
            EAsiBoolean         getValue                (GUID *) const;

    virtual DBCOLUMNINFO *		MapAsiToColumnInfo		(DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *		MapAsiToParamInfo		(DBPARAMINFO *) const;


    virtual EAsiBoolean         SQLType                 (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean         SQLLiteral              (CAsiUcStr *) const;        // SQL compatible literal

    // Runtime class iteraction functions
    //
    virtual unsigned long       packSize        (void)  const;
    virtual unsigned long       packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean         unpackFrom      (CAsiObjPack *);

    virtual unsigned long       packValueSize   (void)  const;
    virtual unsigned long       packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean         unpackValueFrom (CAsiObjPack *);


    // Duplicate itself
    //
    virtual CAsiObject   *      duplicate               (void) const;

    // Nullify all members

    virtual void                Clear                   (void);

    // Like predicate and string functions
    //
    EAsiBoolean                         Like                    (const CAsiChar &, const CAsiChar &) const;
    CAsiChar                            Substring               (uint) const;
    CAsiChar                            Substring               (uint, uint) const;
    CAsiChar                            Upper                   (void) const;
    CAsiChar                            Lower                   (void) const;
    CAsiChar                            Trim                    (EAsiTrimSpec, const CAsiChar &) const;
    CAsiNumeric                         Position                (const CAsiChar &) const;

    // Operators
    //
            // Assignment
            CAsiChar  & operator=  (const CAsiChar &);
            CAsiChar  & operator=  (const CAsiUcStr &);

            // Cancatenation
            CAsiChar    operator+  (const CAsiChar &) const;
            CAsiChar    operator+  (const CAsiUcStr &) const;

            // Comparision
            int         operator>  (const CAsiChar &) const;
            int         operator>  (const CAsiUcStr &) const;
     friend int         DLLScope operator>  (const CAsiUcStr &, const CAsiChar &);

            int         operator>=  (const CAsiChar &) const;
            int         operator>=  (const CAsiUcStr &) const;
     friend int         DLLScope operator>=  (const CAsiUcStr &, const CAsiChar &);

            int         operator==  (const CAsiChar &) const;
            int         operator==  (const CAsiUcStr &) const;
     friend int         DLLScope operator==  (const CAsiUcStr &, const CAsiChar &);

            int         operator<=  (const CAsiChar &) const;
            int         operator<=  (const CAsiUcStr &) const;
     friend int         DLLScope operator<=  (const CAsiUcStr &, const CAsiChar &);

            int         operator<  (const CAsiChar &) const;
            int         operator<  (const CAsiUcStr &) const;
     friend int         DLLScope operator<  (const CAsiUcStr &, const CAsiChar &);

            int         operator!=  (const CAsiChar &) const;
            int         operator!=  (const CAsiUcStr &) const;
     friend int         DLLScope operator!=  (const CAsiUcStr &, const CAsiChar &);

private:

    EAsiBoolean     isCompColSet(const AsiUcIdCLT, EAsiCAttr) const;
    AsiUcIdCLT      CompColSet(const AsiUcIdCLT, EAsiCAttr) const;
    EAsiBoolean     isDyadicOpColSet(const AsiUcIdCLT, EAsiCAttr) const;
    AsiUcIdCLT      DyadicOpColSet(const AsiUcIdCLT, EAsiCAttr *, EAsiCAttr) const;

private:

    uint                maxlength;              // Length of character data
    uint                retlength;              // Length of the stored data
    CAsiUcStr           chvalue;                // Value

    short           mod;                // Type modifiers
    AsiUcIdCCT      CharSetId;          // Character set identifier
    CAsiUcStr       CharSet;            // Character set name
    AsiUcIdCLT      ColId;              // Collation identifier
    CAsiUcStr       CName;              // Collation name
    EAsiCAttr       coercibility;       // Coercibility attribute
};


////////////////////////////////////////////////
//
//
class CAsiBinary: public CAsiData
//
// BIT and BIT VARYING
//
// This class introduces functionality of the BIT and BIT VARYING SQL
// data type
// It defines assignment and binary concatenation operations which are
// associated with = and + operators.
//
//
{
friend class CAsiTempTable;
public:
    // Construction/Destruction
    //
            CAsiBinary  ();
            CAsiBinary  (uint);
            CAsiBinary  (const CAsiBinary &);
    virtual ~CAsiBinary ();


    // Set BIT VARYING
           void          setVarying    (void);

    // Get data descriptor
    //
    virtual EAsiDataType Type         (void) const;
    virtual uint         Length       (void) const; // Binary length
    virtual uint         ReturnLength (void) const;


    //  is_ functions
    //
    virtual EAsiBoolean   is_binary     (void) const;
    virtual EAsiBoolean   is_comparable (const CAsiData *) const;
    virtual EAsiBoolean   is_storable   (const CAsiData *) const;
    virtual EAsiBoolean   is_castable   (const CAsiData *) const;

    virtual CAsiData *    checkCat      (const CAsiData *) const;
    virtual CAsiData *    checkSet      (const CAsiData *) const;

    virtual EAsiBoolean   isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean   isGreaterThan (const CAsiData &) const;

    // Store Data value
    //
            EAsiBoolean   storeHexValue (char *, uint, uint *);
            EAsiBoolean   storeHexValue (const CAsiUcStr &);
            EAsiBoolean   storeBinValue (char *, uint, uint *);
            EAsiBoolean   storeBinValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue    (char *, uint);
    virtual EAsiBoolean   storeValue    (char *, uint, uint *);
    virtual EAsiBoolean   storeValue    (const CAsiData &);

    // ****
    virtual EAsiBoolean   storeValue (real);                 // Real
    virtual EAsiBoolean   storeValue (integer);              // Integer
    virtual EAsiBoolean   storeValue (smallint);             // Smallint
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);    // Unicode string
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr


    //  Get data value
    //
            EAsiBoolean   getHexValue (char *, uint, uint *) const;
            EAsiBoolean   getHexValue (CAsiUcStr *) const;
            EAsiBoolean   getBinValue (char *, uint, uint *) const;
            EAsiBoolean   getBinValue (CAsiUcStr *) const;
    virtual EAsiBoolean   getValue    (char *, uint) const;
    virtual EAsiBoolean   getValue    (char *, uint, uint *) const;

    // *****
    virtual EAsiBoolean   getValue (real *) const;               // Real
    virtual EAsiBoolean   getValue (integer *) const;            // Integer
    virtual EAsiBoolean   getValue (smallint *) const;           // Smallint
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;          // Unicode string
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean   SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal


    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);




    // Duplicate itself
    //
    virtual CAsiObject   *duplicate(void) const;

    // Nullify all members

    virtual void          Clear     (void);

    // Utility
    //
    CAsiBinary Substring(uint);
    CAsiBinary Substring(uint,uint);

    // Operators
    //
            // Assignment
            CAsiBinary   &operator= (const CAsiBinary &);

            // Cancatenation
            CAsiBinary  operator+  (const CAsiBinary &) const;

            // Comparision
            int         operator>  (const CAsiBinary &) const;
            int         operator>= (const CAsiBinary &) const;
            int         operator== (const CAsiBinary &) const;
            int         operator<= (const CAsiBinary &) const;
            int         operator<  (const CAsiBinary &) const;
            int         operator!= (const CAsiBinary &) const;


private:
    uint       blength;   // Length of binary data
    uint       alength;   // Actual length
    uint       buflen;    // Allocated length
    uchar    * value;     // Value
    short      mod;       // Modifier
};


/////////////////////////////////////////////////////////////////////////////
class CAsiIQualifier : public CAsiData
//
// Interval Qualifier
//
{
friend class CAsiInterval;
friend class CAsiDatetime;

public:
    // Construction/Destruction
    //
               CAsiIQualifier (void);
               CAsiIQualifier (EAsiIType);
               CAsiIQualifier (EAsiIType, uint);
               CAsiIQualifier (EAsiIType, uint, uint);
               CAsiIQualifier (const CAsiIQualifier &);
    virtual   ~CAsiIQualifier (void);

    // Set Interval qualifier type and characteristics
    //
    virtual EAsiBoolean  setIType         (EAsiIType);    // Set interval type
            void         setLeadFieldPrec (uint);         // Set Leading field precision
            void         setFracSecPrec   (uint);         // Set Fractional sec prec

    // Get access to interval characteristics
    //
    virtual EAsiDataType Type          (void) const;
    virtual EAsiIType    IntervalType  (void) const;
    virtual uint         LeadFieldPrec (void) const;
    virtual uint         FracSecPrec   (void) const;
    virtual uint         ReturnLength  (void) const;


    // Return interval type
    virtual EAsiBoolean  is_interval     (void) const;
    virtual EAsiBoolean  is_yminterval   (void) const;
    virtual EAsiBoolean  is_dtinterval   (void) const;
    virtual EAsiBoolean  is_storable     (const CAsiData *) const;
    virtual EAsiBoolean  is_comparable   (const CAsiData *) const;
            EAsiBoolean  is_moreaccurate (const CAsiIQualifier *) const;

    virtual EAsiBoolean  SQLType       (CAsiUcStr *) const;        // SQL data type as string

private:
    virtual EAsiBoolean  SQLLiteral    (CAsiUcStr *) const;    // SQL compatible literal

public:
    // Assignment operator
            CAsiIQualifier &operator= (const CAsiIQualifier &);

    // Runtime class iteraction functions
    //

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate(void) const;

protected:
    EAsiIType itype;                 // Interval type
    uint lfp;                        // Leading field precision
    uint fsp;                        // Fractional second precision
};



////////////////////////////////////////////////
//
//
class CAsiInterval : public CAsiIQualifier
//
// INTERVAL
//
//  This is a base class for datetime intervals. The basic functionality
//  for class includes setting and retrieving interval sign.

{
friend class CAsiDate;
friend class CAsiTime;
friend class CAsiTimeStamp;

public:
    // Constructors/Destructors
    //
            CAsiInterval                (void);
    virtual ~CAsiInterval               (void);

    virtual EAsiBoolean   SQLType       (CAsiUcStr *)      const;

    virtual CAsiData *    checkAdd      (const CAsiData *) const;
    virtual CAsiData *    checkSub      (const CAsiData *) const;
    virtual CAsiData *    checkMul      (const CAsiData *) const;
    virtual CAsiData *    checkDiv      (const CAsiData *) const;
    virtual CAsiData *    checkSet      (const CAsiData *) const;

    //  Set/get interval sign
    //
            void          setSign  (EAsiBoolean);
            EAsiBoolean   Sign          (void)             const;


protected:
    EAsiBoolean sign;     // Interval sign
};


////////////////////////////////////////////////
//
//
class CAsiYM : public CAsiInterval
//
// Year Month Intervals
//
// Constructors/Destructor
//
// CAsiYM ()
// CAsiYM (
//   EAsiIType itype)                  // Year Month Interval type
// CAsiYM (
//   EAsiIType itype,                  // Year Month Interval type
//   uint lprec                        // Leading fields precision
//   )
//
// Different forms of constructor allow to specify interval type, and leading
// field precision
// Interval type shall be a valid Year Month interval type.
// If invalid interval type was specified, interval will be set to kAsiIUnknown.
//
//  EAsiBoolean set (
//    EAsiBoolean sign,                // Interval sign kAsiFalse (+), kAsiTrue (-)
//    uint years,                     // Years
//    uint months)                    // Months
//
//  EAsiBoolean setYears (
//    uint years)                     // Years
//
//  EAsiBoolean setMonths (
//    uint months)                    // Months
//
//  Interval fields set functions allow to set interval. They return
//  boolean value, because they must validate input.
//
//
//  Get interval fields
//
//  void get (
//    EAsiBoolean *sign,               // Interval sign kAsiFalse (+), kAsiTrue (-)
//    uint *years,                    // Years
//    uint *months) const             // Months
//
//  EAsiBoolean getYears (
//    uint *years) const              // Years
//
//  EAsiBoolean getMonths (
//    uint *months) const             // Months
//
//  The functions above retrieve interval fields. Return kAsiTrue if
//  specified interval field present in interval and kAsiFalse otherwise.
//
//
//  Operators
//
//  Operators overload interval arithmetics operations like +, -, /, *, and
//  unary minus. Besides them all boolean operators are redefined.
//
//

{
friend class CAsiDate;
friend class CAsiTime;
friend class CAsiTimeStamp;
friend class CAsiTempTable;

public:
    // Construction/Destruction
    //
            CAsiYM (void);
            CAsiYM (EAsiIType);
            CAsiYM (EAsiIType, uint);
            CAsiYM (const CAsiYM &);
    virtual ~CAsiYM (void);

    virtual EAsiBoolean   setIType      (EAsiIType);    // Set interval type

    virtual EAsiBoolean   is_castable   (const CAsiData *) const;


    virtual EAsiBoolean   isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean   isGreaterThan (const CAsiData &) const;


    // Store Data value
    //
    virtual EAsiBoolean   storeValue (integer);
    virtual EAsiBoolean   storeValue (smallint);
    virtual EAsiBoolean   storeValue (char *, uint);
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue (const CAsiData &);

    // ******
    virtual EAsiBoolean   storeValue (real);                 // Real
    virtual EAsiBoolean   storeValue (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr

    // Set data value
    //
       EAsiBoolean   set       (ASI_IYEAR *);
       EAsiBoolean   set       (ASI_IYEARTOMONTH *);
       EAsiBoolean   set       (ASI_IMONTH *);
       EAsiBoolean   set       (EAsiBoolean, uint, uint);
       EAsiBoolean   setYears  (uint);
       EAsiBoolean   setMonths (uint);

    //  Get data value in the Unicode character string format
    //
    virtual EAsiBoolean   getValue (integer *) const;
    virtual EAsiBoolean   getValue (smallint *) const;
    virtual EAsiBoolean   getValue (char *, uint) const;
    virtual EAsiBoolean   getValue (CAsiUcStr *) const;

    // ******
    virtual EAsiBoolean   getValue (real *) const;               // Real
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

            EAsiBoolean   get       (ASI_IYEAR *)        const;
            EAsiBoolean   get       (ASI_IYEARTOMONTH *) const;
            EAsiBoolean   get       (ASI_IMONTH *)       const;
            EAsiBoolean   get       (EAsiBoolean *, uint *, uint *) const;
            EAsiBoolean   getYears  (uint *) const;
            EAsiBoolean   getMonths (uint *) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
        CAsiYM       &operator=  (const CAsiYM &);
        CAsiYM       &operator=  (const CAsiSmallInt &);
        CAsiYM       &operator=  (const CAsiInt &);
        CAsiYM       &operator=  (const CAsiNumeric &);
        CAsiYM       &operator=  (const CAsiDecimal &);
        CAsiYM       &operator=  (integer);

        CAsiYM       operator+  (const CAsiYM &) const;
friend  CAsiDate DLLScope operator+  (const CAsiYM &, const CAsiDate &);
        CAsiYM       operator-  (const CAsiYM &) const;

       CAsiYM       operator*  (const CAsiSmallInt &) const;
       CAsiYM       operator*  (const CAsiInt &) const;
       CAsiYM       operator*  (const CAsiNumeric &) const;
       CAsiYM       operator*  (const CAsiDecimal &) const;
       CAsiYM       operator*  (integer) const;
friend CAsiYM DLLScope operator*  (const CAsiSmallInt &,const CAsiYM &);
friend CAsiYM DLLScope operator*  (const CAsiInt &,     const CAsiYM &);
friend CAsiYM DLLScope operator*  (const CAsiNumeric &, const CAsiYM &);
friend CAsiYM DLLScope operator*  (const CAsiDecimal &, const CAsiYM &);
friend CAsiYM DLLScope operator*  (integer,             const CAsiYM &);

        CAsiYM       operator/  (const CAsiSmallInt &) const;
        CAsiYM       operator/  (const CAsiInt &)      const;
        CAsiYM       operator/  (const CAsiNumeric &)  const;
        CAsiYM       operator/  (const CAsiDecimal &)  const;
        CAsiYM       operator/  (integer)              const;

        CAsiYM       &operator-  (void);

    // Comparision predicates
    //
       int           operator>  (const CAsiYM &) const;
       int           operator>= (const CAsiYM &) const;
       int           operator== (const CAsiYM &) const;
       int           operator<= (const CAsiYM &) const;
       int           operator<  (const CAsiYM &) const;
       int           operator!= (const CAsiYM &) const;
private:
       char *        getYMString (char *, size_t) const;

protected:
    ulong ivalue;         // Interval value in months

};


////////////////////////////////////////////////
//
//
class CAsiDT : public CAsiInterval
//
// Day Time Intervals
//
// This class introduces functionality of the Day Time intervals.
//
// MEMBER FUNCTIONS
// ----------------
// Constructors/Destructor
//
// CAsiDT ()
// CAsiDT (
//   EAsiIType itype                   // Interval type
//  )
// CAsiDT (
//   EAsiIType itype,                  // Interval type
//   uint lprec                        // Leading fields precision
//  )
// CAsiDT (
//   EAsiIType itype                   // Interval type
//   uint lprec,                       // Leading fields precision
//   uint fprec                        // Fractional second precision
//  )

// Constructors allow to set interval type, leading field precision and fractional
// seconds precision
// Interval type shall specify valid day time interval type.
// If invalid interval type was specified, interval will be set to kAsiIUnknown.
//
//
//  EAsiBoolean set (
//    EAsiBoolean sign,                 // Interval sign kAsiFalse (+), kAsiTrue (-)
//    uint days,                        // Days
//    uint hours,                       // Hours
//    uint minutes,                     // Minutes
//    double seconds)                   // Seconds
//
//  EAsiBoolean setDays (
//    uint days)                        // Days
//
//  EAsiBoolean setHours (
//    uint hours)                       // Hours
//
//  EAsiBoolean setMinutes (
//    uint minutes)                     // Minutes
//
//  EAsiBoolean getSeconds (
//    double seconds)                   // Seconds
//
//  Interval fields set functions allow to set interval. They return
//  boolean value, because they must validate input.
//
//
//  Get interval fields
//
//  void get (
//    EAsiBoolean *sign,               // Interval sign kAsiFalse (+), kAsiTrue (-)
//    uint *days,                       // Days
//    uint *hours,                      // Hours
//    uint *minutes,                    // Minutes
//    double *seconds) const            // Seconds with fraction
//
//  EAsiBoolean getDays (
//    uint *days                       // Days
//   ) const
//
//  EAsiBoolean getHours (
//    uint *hours                      // Hours
//   ) const;
//
//  EAsiBoolean getMinutes (
//     uint *minutes                    // Minutes
//   ) const;
//
//  EAsiBoolean getSeconds (
//    double *seconds) const;           // Seconds with fraction
//
//  The functions above retrieve interval fields
//
//
//  Operators
//
//  Operators overload interval arithmetics operations like +, -, /, *, and
//  unary minus. Besides them all boolean operators are redefined.
//
//

{
    // Friend classes
friend class CAsiDate;
friend class CAsiTime;
friend class CAsiTimeStamp;
friend class CAsiTempTable;

private:
    // private helpers

                void        ChkMul     (real);
                void        ChkDiv     (real);
                int         cmpDTI     (const CAsiDT&) const;
                EAsiBoolean ChkSet     (double);
                void        ChkSet2    (double);
                double      LocalToUTC (double) const;
                double      UTCToLocal (double) const;

public:

    // Constructors/Destructors
    //
            CAsiDT (void);
            CAsiDT (EAsiIType);
            CAsiDT (EAsiIType, uint);
            CAsiDT (EAsiIType, uint, uint);
            CAsiDT (const CAsiDT &);
    virtual ~CAsiDT (void);

    virtual EAsiBoolean   setIType      (EAsiIType);    // Set interval type

    virtual EAsiBoolean   is_castable   (const CAsiData *) const;

    virtual EAsiBoolean   isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean   isGreaterThan (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean   storeValue (integer);
    virtual EAsiBoolean   storeValue (smallint);
    virtual EAsiBoolean   storeValue (char *, uint);
    virtual EAsiBoolean   storeValue (const CAsiUcStr &);
    virtual EAsiBoolean   storeValue (const CAsiData &);

    // ******
    virtual EAsiBoolean   storeValue (real);                 // Real
    virtual EAsiBoolean   storeValue (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr

    // Set data value
    //
            EAsiBoolean   set        (ASI_IDAY *);
            EAsiBoolean   set        (ASI_IHOUR *);
            EAsiBoolean   set        (ASI_IMINUTE *);
            EAsiBoolean   set        (ASI_ISECOND *);
            EAsiBoolean   set        (ASI_IDAYTOHOUR *);
            EAsiBoolean   set        (ASI_IDAYTOMINUTE *);
            EAsiBoolean   set        (ASI_IDAYTOSECOND *);
            EAsiBoolean   set        (ASI_IHOURTOMINUTE *);
            EAsiBoolean   set        (ASI_IHOURTOSECOND *);
            EAsiBoolean   set        (ASI_IMINUTETOSECOND *);
            EAsiBoolean   set        (EAsiBoolean, uint, uint, uint, double);
            EAsiBoolean   setDays    (uint);
            EAsiBoolean   setHours   (uint);
            EAsiBoolean   setMinutes (uint);
            EAsiBoolean   setSeconds (double);

    //  Get data value in the Unicode character string format
    //
    virtual EAsiBoolean   getValue   (integer *)      const;
    virtual EAsiBoolean   getValue   (smallint *)     const;
    virtual EAsiBoolean   getValue   (char *, uint)   const;
    virtual EAsiBoolean   getValue   (CAsiUcStr *)    const;

    // ******
    virtual EAsiBoolean   getValue (real *) const;               // Real
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean   SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

            EAsiBoolean   get        (ASI_IDAY *)            const;
            EAsiBoolean   get        (ASI_IHOUR *)           const;
            EAsiBoolean   get        (ASI_IMINUTE *)         const;
            EAsiBoolean   get        (ASI_ISECOND *)         const;
            EAsiBoolean   get        (ASI_IDAYTOHOUR *)      const;
            EAsiBoolean   get        (ASI_IDAYTOMINUTE *)    const;
            EAsiBoolean   get        (ASI_IDAYTOSECOND *)    const;
            EAsiBoolean   get        (ASI_IHOURTOMINUTE *)   const;
            EAsiBoolean   get        (ASI_IHOURTOSECOND *)   const;
            EAsiBoolean   get        (ASI_IMINUTETOSECOND *) const;
            EAsiBoolean   get        (EAsiBoolean *, uint *, uint *, uint *,
                                      double *) const;
            EAsiBoolean   getDays    (uint *) const;
            EAsiBoolean   getHours   (uint *) const;
            EAsiBoolean   getMinutes (uint *) const;
            EAsiBoolean   getSeconds (double *) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);
    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
            CAsiDT       &operator=  (const CAsiDT &);

            CAsiDT       &operator=  (const CAsiSmallInt &);
            CAsiDT       &operator=  (const CAsiInt &);
            CAsiDT       &operator=  (const CAsiNumeric &);
            CAsiDT       &operator=  (const CAsiDecimal &);
            CAsiDT       &operator=  (integer);

            CAsiDT       operator+  (const CAsiDT &) const;
            CAsiDT       operator-  (const CAsiDT &) const;
            CAsiDT       operator*  (const CAsiSmallInt &) const;
            CAsiDT       operator*  (const CAsiInt &)      const;
            CAsiDT       operator*  (const CAsiNumeric &)  const;
            CAsiDT       operator*  (const CAsiDecimal &)  const;
            CAsiDT       operator*  (integer)              const;
     friend CAsiDT DLLScope operator*  (const CAsiSmallInt &,const CAsiDT &);
     friend CAsiDT DLLScope operator*  (const CAsiInt &,     const CAsiDT &);
     friend CAsiDT DLLScope operator*  (const CAsiNumeric &, const CAsiDT &);
     friend CAsiDT DLLScope operator*  (const CAsiDecimal &, const CAsiDT &);
     friend CAsiDT DLLScope operator*  (integer,             const CAsiDT &);

            CAsiDT       operator/  (const CAsiSmallInt &) const;
            CAsiDT       operator/  (const CAsiInt &)      const;
            CAsiDT       operator/  (const CAsiNumeric &)  const;
            CAsiDT       operator/  (const CAsiDecimal &)  const;
            CAsiDT       operator/  (integer)              const;

            CAsiDT       &operator-  (void);

    // Comparision predicates
    //
            int           operator>  (const CAsiDT &) const;
            int           operator>= (const CAsiDT &) const;
            int           operator== (const CAsiDT &) const;
            int           operator<= (const CAsiDT &) const;
            int           operator<  (const CAsiDT &) const;
            int           operator!= (const CAsiDT &) const;

private:
    char * getDTString (char * , size_t) const;


protected:
    double ivalue;        // Interval value in seconds with fraction

};


////////////////////////////////////////////////
//
//
class CAsiDatetime : public CAsiData
//
//  Datetime
//
{
public:
    // Construction/Destruction
    //
            CAsiDatetime ();
    virtual ~CAsiDatetime ();

    // Get data descriptor
    //
    virtual EAsiDataType Type          (void) const;

    //  is_ functions
    //
    virtual EAsiBoolean   is_datetime   (void) const;
    virtual EAsiBoolean   is_comparable (const CAsiData *) const;

    virtual CAsiData *    checkAdd      (const CAsiData *) const;
    virtual CAsiData *    checkSub      (const CAsiData *) const;
    virtual CAsiData  *   checkSet      (const CAsiData *) const;

    //  Get datetime field value
    //
    virtual ushort Year                 (void) const = 0;
    virtual ushort Month                (void) const = 0;
    virtual ushort Day                  (void) const = 0;
    virtual ushort Hour                 (void) const = 0;
    virtual ushort Minute               (void) const = 0;
    virtual double Second               (void) const = 0;

protected:

};


////////////////////////////////////////////////
//
//
class CAsiDate: public CAsiDatetime
//
// DATE
//
{
friend class CAsiTimeStamp;
friend class CAsiTempTable;

public:

    // Construction/Destruction
    //
            CAsiDate ();
            CAsiDate (const CAsiDate &);
    virtual ~CAsiDate (void);

    // Get data descriptor
    //
    virtual EAsiDTType   DateTimeType  (void) const;
    virtual uint         ReturnLength  (void) const;

    // Check storable
    virtual EAsiBoolean  is_storable   (const CAsiData *) const;
    virtual EAsiBoolean  is_castable   (const CAsiData *) const;


    virtual EAsiBoolean   isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean   isGreaterThan (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean  storeValue (char *, uint);
    virtual EAsiBoolean  storeValue (const CAsiUcStr &);
    virtual EAsiBoolean  storeValue (const CAsiData &);
    virtual EAsiBoolean  storeValue (const DBDATE *);
    virtual EAsiBoolean  storeValue (DATE);

    // *******
//    virtual EAsiBoolean   storeValue (real);                 // Real == DATE
    virtual EAsiBoolean   storeValue (integer);              // Integer
    virtual EAsiBoolean   storeValue (smallint);             // Smallint
    virtual EAsiBoolean   storeValue (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr

    // Set date fields
    //
            EAsiBoolean  set      (ASI_DTDATE *);
            EAsiBoolean  set      (const DBDATE *);
            EAsiBoolean  set      (ushort, ushort, ushort);
            EAsiBoolean  setYear  (ushort);
            EAsiBoolean  setMonth (ushort);
            EAsiBoolean  setDay   (ushort);

    //  Get data value
    //
            EAsiBoolean  get      (ASI_DTDATE *)  const;
            EAsiBoolean  get      (DBDATE *)      const;
    virtual EAsiBoolean  getValue (char *, uint)  const;
    virtual EAsiBoolean  getValue (CAsiUcStr *)   const;
    virtual EAsiBoolean  getValue (DBDATE *)      const;         // OLE DB date
    virtual EAsiBoolean  getValue (DATE *)        const;         // OLE DB "double" date

    // *****
//    virtual EAsiBoolean   getValue (real *) const;               // Real == DATE
    virtual EAsiBoolean   getValue (integer *) const;            // Integer
    virtual EAsiBoolean   getValue (smallint *) const;           // Smallint
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean  SQLType    (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean  SQLLiteral (CAsiUcStr *) const;        // SQL compatible literal

    virtual ushort       Year      (void) const;
    virtual ushort       Month     (void) const;
    virtual ushort       Day       (void) const;
    virtual ushort       Hour      (void) const;
    virtual ushort       Minute    (void) const;
    virtual double       Second    (void) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject   *duplicate (void) const;

    // Operators
    //
     // Assignments
            CAsiDate    &operator=     (const CAsiDate &);

     // Arithmatics
            CAsiDate     operator+     (const CAsiYM &) const;
            CAsiDate     operator+     (const CAsiDT &) const;
     friend CAsiDate DLLScope operator+     (const CAsiYM &, const CAsiDate &);
     friend CAsiDate DLLScope operator+     (const CAsiDT &, const CAsiDate &);

            CAsiDate     operator-     (const CAsiYM &) const;
            CAsiDate     operator-     (const CAsiDT &) const;

            //   Dates difference , result corresponds with EAsiType value

            CAsiYM YMDiff (const CAsiDate &, const CAsiYM &)   const;
            CAsiDT DTDiff (const CAsiDate &, const CAsiDT &)   const;

     // Comparision
            int          operator>     (const CAsiDate &)      const;
            int          operator>=    (const CAsiDate &)      const;
            int          operator==    (const CAsiDate &)      const;
            int          operator<=    (const CAsiDate &)      const;
            int          operator<     (const CAsiDate &)      const;
            int          operator!=    (const CAsiDate &)      const;


protected:
    ulong month;      // Months since 00-00-00
    ushort day;       // Day of the month

};

///////////////////////////////////////////
//
//
class CAsiTime : public CAsiDatetime
//
// TIME and TIME WITH TIME ZONE
//
{
friend class CAsiTimeStamp;
friend class CAsiTempTable;

public:

    // Construction/Destruction
    //
            CAsiTime  (void);
            CAsiTime  (const CAsiDT&);
            CAsiTime  (uint);
            CAsiTime  (uint, const CAsiDT&);
            CAsiTime  (const CAsiTime &);
    virtual ~CAsiTime (void);


            void         setWithTimeZone (EAsiBoolean f = kAsiTrue );

    // Get data descriptor
    //
    virtual EAsiDTType    DateTimeType  (void) const;
    virtual uint          TimePrec      (void) const;
    virtual uint          ReturnLength  (void) const;

    // Check storable
    virtual EAsiBoolean   is_storable   (const CAsiData *) const;
    virtual EAsiBoolean   is_castable   (const CAsiData *) const;

    virtual EAsiBoolean   isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean   isGreaterThan (const CAsiData &) const;

    // Store Data value
    //
    virtual EAsiBoolean  storeValue   (char *, uint);
    virtual EAsiBoolean  storeValue   (const CAsiUcStr &);
    virtual EAsiBoolean  storeValue   (const CAsiData &);
    virtual EAsiBoolean  storeValue   (const DBTIME *);

    // *******
    virtual EAsiBoolean   storeValue (real);                 // Real
    virtual EAsiBoolean   storeValue (integer);              // Integer
    virtual EAsiBoolean   storeValue (smallint);             // Smallint
    virtual EAsiBoolean   storeValue (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr


    // Set date value
    //
            EAsiBoolean  set           (ASI_DTTIME *);
            EAsiBoolean  set           (const DBTIME *);
            EAsiBoolean  set           (ushort, ushort, double);
            EAsiBoolean  setHour       (ushort);
            EAsiBoolean  setMinute     (ushort);
            EAsiBoolean  setSecond     (double);
            EAsiBoolean  setTimeZone   (const CAsiDT &);

    //  Get data value
    //
            EAsiBoolean  get          (ASI_DTTIME *) const;
            EAsiBoolean  get          (DBTIME *)     const;
    virtual EAsiBoolean  getValue     (char *, uint) const;
    virtual EAsiBoolean  getValue     (CAsiUcStr *)  const;
    virtual EAsiBoolean  getValue     (DBTIME *)     const;      // OLE DB time

    // *****
    virtual EAsiBoolean   getValue (real *) const;               // Real
    virtual EAsiBoolean   getValue (integer *) const;            // Integer
    virtual EAsiBoolean   getValue (smallint *) const;           // Smallint
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean  SQLType      (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean  SQLLiteral   (CAsiUcStr *) const;        // SQL compatible literal

    virtual ushort       Year         (void) const {return 0;};
    virtual ushort       Month        (void) const {return 0;};
    virtual ushort       Day          (void) const {return 0;};
    virtual ushort       Hour         (void) const;
    virtual ushort       Minute       (void) const;
    virtual double       Second       (void) const;
      const CAsiDT      &TimeZone     (void) const;

    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);
    // Duplicate itself
    //
    virtual CAsiObject  *duplicate (void) const;

    // Operators
    //
            // Assignments
            CAsiTime    &operator=     (const CAsiTime &);

            // Arithmatics
            CAsiTime     operator+     (const CAsiDT &) const;
     friend CAsiTime DLLScope operator+     (const CAsiDT &, const CAsiTime &);
            CAsiTime     operator-     (const CAsiDT &) const;

            // Difference
            CAsiDT       DTDiff        (const CAsiTime &,const CAsiDT &) const;

            // Comparision
            int          operator>     (const CAsiTime &) const;
            int          operator>=    (const CAsiTime &) const;
            int          operator==    (const CAsiTime &) const;
            int          operator<=    (const CAsiTime &) const;
            int          operator<     (const CAsiTime &) const;
            int          operator!=    (const CAsiTime &) const;


private:

    ushort timeprec;   // Time precision
    double seconds;    // Seconds since 0:0 AM with fraction
    short  mod;        // Modifiyer
    CAsiDT timezone;
};

///////////////////////////////////////////
//
//
class CAsiTimeStamp: public CAsiDatetime
//
// TIMESTAMP and TIMESTAMP WITH TIME ZONE
//

// This class introduces functionality of the TIMESTAMP SQL data type
//
// MEMBER FUNCTIONS
// ----------------
// Constructors/Destructor
//
//  CAsiTimeStamp ()
//  CAsiTimeStamp (
//    uint tprec)           // Timestamp precision
//
// Two forms of constructor are provided. The second form allows to define
// timestamp precision. If the first form of constructor
// is used, timestamp precision is set to 0.
//
//
// Set Timestamp fields
//
// EAsiBoolean set (
//    ushort year,             // Year
//    ushort month,            // Month
//    ushort day,              // Day
//    ushort hour,             // Hour
//    ushort minute,           // Minute
//    double second)           // Second with fraction
//
// EAsiBoolean setYear (
//    ushort year)             // Year
//
// EAsiBoolean setMonth (
//    ushort month)            // Month
//
// EAsiBoolean setDay (
//    ushort day)              // Day
//
// EAsiBoolean setHour (
//    ushort hour)             // Hour
//
// EAsiBoolean setMinute (
//    ushort minute)           // Minute
//
// EAsiBoolean setSecond (
//    double second)           // Second with fraction
//
// These fiunctions are used to set datetime type and datetime fields.
//
// Year shall be greater or equal than 0;
// Month >= 1 and <= 12;
// Day >= 1 and <= actual number of days for each month;
// Hour >= 0 and <= 23
// Minute >= 0 and <= 59
// Second >= 0 and <= 59
// Second fraction is an unsigned short number that holds second fraction.
//
// Most of functions return boolean value bacause they must validate
// input arguments. For example, seconds can't be stored to the DATE or
// month can be greater than 12.
//
//
// void get (
//    ushort *year,             // Year
//    ushort *month,            // Month
//    ushort *day,              // Day
//    ushort *hour,             // Hour
//    ushort *minute,           // Minute
//    double *second)           // Second with fraction
//
// ushort  Year ()
//
// ushort  Month ()
//
// ushort  Day ()
//
// ushort  Hour ()
//
// ushort  Minute ()
//
// double  Second ()
//
// The functions above extracts all or specified datetime fields.
//
//
// Operators
//
// All meaningful arithmetic and comparision operators are redefined by
// this class. Description of them can be found in SQL/ISO standard (6.14).
// Besides them special datetime operations are defined for the datetime
// data.
//
// CAsiIDateTime & at_time_zone (
//   CAsiDT &tz)         // Time zone value
//
// This function translate TIME or TIMESTAMP datetime according to the
// time zone value specified as a internal hour or hour to minute day time
// interval (see 6.14 SQL/ISO). Interval value shall be between -'12:59 and
// +'13:00'. If wrong interval type was passed or

{
friend class CAsiDate;
friend class CAsiTime;
friend class CAsiTempTable;
public:

                        CAsiTimeStamp ();
                        CAsiTimeStamp (uint);
                        CAsiTimeStamp (const CAsiDT &);
                        CAsiTimeStamp (uint, const CAsiDT &);
                        CAsiTimeStamp (const CAsiTimeStamp &);
    virtual				~CAsiTimeStamp (void);

    virtual void         setNull         (void);            // Assign NULL
            void         setWithTimeZone (EAsiBoolean f = kAsiTrue );

    // Get data descriptor
    //
    virtual EAsiDTType   DateTimeType  (void) const;
    virtual uint         TimeStampPrec (void) const;
    virtual uint         ReturnLength  (void) const;

    // Check storable
    virtual EAsiBoolean  is_storable   (const CAsiData *) const;
    virtual EAsiBoolean  is_castable   (const CAsiData *) const;

    virtual EAsiBoolean  isEqualTo     (const CAsiData &) const;
    virtual EAsiBoolean  isGreaterThan (const CAsiData &) const;


    // Store Data value
    //
    virtual EAsiBoolean  storeValue  (char *, uint);
    virtual EAsiBoolean  storeValue  (const CAsiUcStr &);
    virtual EAsiBoolean  storeValue  (const CAsiData &);
    virtual EAsiBoolean  storeValue  (const DBTIMESTAMP *);

    // *******
    virtual EAsiBoolean   storeValue (real);                 // Real
    virtual EAsiBoolean   storeValue (integer);              // Integer
    virtual EAsiBoolean   storeValue (smallint);             // Smallint
    virtual EAsiBoolean   storeValue (char *, uint, uint *); // Binary Buffer
    virtual EAsiBoolean   storeValue (const AsiUcStr);       // Store AsiUcStr

    // Set timestamp fields
    //
            EAsiBoolean  set         (ASI_DTTIMESTAMP *);
            EAsiBoolean  set         (const DBTIMESTAMP *);
            EAsiBoolean  set         (const CAsiDate &, const CAsiTime &);
            EAsiBoolean  set         (ushort, ushort, ushort, ushort,
                                      ushort, double);
            EAsiBoolean  setYear     (ushort);
            EAsiBoolean  setMonth    (ushort);
            EAsiBoolean  setDay      (ushort);
            EAsiBoolean  setHour     (ushort);
            EAsiBoolean  setMinute   (ushort);
            EAsiBoolean  setSecond   (double);
            EAsiBoolean  setTimeZone (const CAsiDT &);

    //  Get data value
    //
            EAsiBoolean  get           (ASI_DTTIMESTAMP *) const;
            EAsiBoolean  get           (DBTIMESTAMP *)     const;
    virtual EAsiBoolean  getValue      (char *, uint)      const;
    virtual EAsiBoolean  getValue      (CAsiUcStr *)       const;
    virtual EAsiBoolean  getValue      (DBTIMESTAMP *)     const;

    // *****
    virtual EAsiBoolean   getValue (real *) const;               // Real
    virtual EAsiBoolean   getValue (integer *) const;            // Integer
    virtual EAsiBoolean   getValue (smallint *) const;           // Smallint
    virtual EAsiBoolean   getValue (char *, uint, uint *) const; // Binary Buffer
    virtual EAsiBoolean   getValue (AsiUcStr, uint) const;       // Unicode string
    virtual EAsiBoolean   getValue (CAsiData &) const;

    virtual DBCOLUMNINFO *MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO * MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean  SQLType       (CAsiUcStr *) const;        // SQL data type as string
    virtual EAsiBoolean  SQLLiteral    (CAsiUcStr *) const;        // SQL compatible literal

    virtual ushort       Year          (void) const;
    virtual ushort       Month         (void) const;
    virtual ushort       Day           (void) const;
    virtual ushort       Hour          (void) const;
    virtual ushort       Minute        (void) const;
    virtual double       Second        (void) const;
      const CAsiDT      &TimeZone      (void) const;


    // Runtime class iteraction functions
    //
    virtual unsigned long packSize        (void) const;
    virtual unsigned long packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackFrom      (CAsiObjPack *);

    virtual unsigned long packValueSize   (void)  const;
    virtual unsigned long packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean   unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject  *duplicate (void) const;

    // Operators
    //
            // Assignments
            CAsiTimeStamp    &operator=     (const CAsiTimeStamp &);
            CAsiTimeStamp    &operator=     (const CAsiDate &);
            CAsiTimeStamp    &operator=     (const CAsiTime &);

            // Arithmatics
            CAsiTimeStamp    operator+     (const CAsiYM &) const;
            CAsiTimeStamp    operator+     (const CAsiDT &) const;
     friend CAsiTimeStamp DLLScope operator+     (const CAsiYM &, CAsiTimeStamp &);
     friend CAsiTimeStamp DLLScope operator+     (const CAsiDT &, CAsiTimeStamp &);

            CAsiTimeStamp    operator-     (const CAsiYM &) const;
            CAsiTimeStamp    operator-     (const CAsiDT &) const;

            //  Difference between timestamps
            CAsiYM    YMDiff (const CAsiTimeStamp &, const CAsiYM &) const;
            CAsiDT    DTDiff (const CAsiTimeStamp &, const CAsiDT &) const;

            // Comparision
            int               operator>     (const CAsiTimeStamp &) const;
            int               operator>=    (const CAsiTimeStamp &) const;
            int               operator==    (const CAsiTimeStamp &) const;
            int               operator<=    (const CAsiTimeStamp &) const;
            int               operator<     (const CAsiTimeStamp &) const;
            int               operator!=    (const CAsiTimeStamp &) const;

private:
    CAsiTime time;
    CAsiDate date;
};


////////////////////////////////////////////////////////////////////////////////
// OLEDB BLOBs
class CAsiBlob : public CAsiData
{
public:
    // BLOB types used by ASI
    //
    typedef enum {
        kUnknown        = 0,
        kBlob,
        kIPersist,
        kNonIPersist,
        kADT
    } EBlobType;

    // BLOB print format
    //
    typedef enum {
        kUnk            = 0,
        kHex,
        kDec,
        kChr,
        kOct,
        kBin
    } EBlobFormat;

    // Construction/Destruction
    //
                            CAsiBlob        ();
                            CAsiBlob        (const CAsiBlob &);
    virtual                 ~CAsiBlob       ();

            void            SetType         (EBlobType);
            EBlobType       GetType         ()                      const;

    // Get data descriptor
    //
    virtual EAsiDataType    Type            ()                      const;
    virtual uint            Length          ()                      const;
    virtual uint            ReturnLength    ()                      const;

    // Store Data value
    //
    virtual EAsiBoolean     storeValue      (real);
    virtual EAsiBoolean     storeValue      (integer);
    virtual EAsiBoolean     storeValue      (smallint);
    virtual EAsiBoolean     storeValue      (char *, uint);
    virtual EAsiBoolean     storeValue      (const CAsiUcStr &);
    virtual EAsiBoolean     storeValue      (const CAsiData &);
    virtual EAsiBoolean     storeValue      (char *, uint, uint *); 

            EAsiBoolean     set             (IUnknown *);

    // Retrieve Data value
    //
    virtual EAsiBoolean     getValue        (real *)                const;
    virtual EAsiBoolean     getValue        (integer *)             const;
    virtual EAsiBoolean     getValue        (smallint *)            const;
    virtual EAsiBoolean     getValue        (char *, uint)          const;
    virtual EAsiBoolean     getValue        (CAsiUcStr *)           const;
    virtual EAsiBoolean     getValue        (CAsiData &)            const;
            EAsiBoolean     get             (IUnknown **);

    virtual DBCOLUMNINFO *  MapAsiToColumnInfo  (DBCOLUMNINFO *) const;
    virtual DBPARAMINFO *   MapAsiToParamInfo   (DBPARAMINFO *) const;


    virtual EAsiBoolean     SQLType         (CAsiUcStr *)           const;  // SQL data type as string
    virtual EAsiBoolean     SQLLiteral      (CAsiUcStr *)           const;  // SQL compatible literal



    // Runtime class iteraction functions
    //
    virtual unsigned long   packSize        (void)                  const;
    virtual unsigned long   packTo          (CAsiObjPack *)         const;
    virtual EAsiBoolean     unpackFrom      (CAsiObjPack *);
    virtual unsigned long   packValueSize   ()                      const;
    virtual unsigned long   packValueTo     (CAsiObjPack *)         const;
    virtual EAsiBoolean     unpackValueFrom (CAsiObjPack *);

    // Duplicate itself
    //
    virtual CAsiObject  *   duplicate       ()                      const;

    // Nullify all members
    //
    virtual void            Clear           ();

    // Mostly useful interface
    //
            HRESULT         Read            (void *, ulong, ulong *);
            HRESULT         Write           (void *, ulong, ulong *);

    // ConvertToString functions
    //
            void            SetFormat       (EBlobFormat);
            void            SetPrintLen     (int);
            HRESULT         ReadHead        ();

private:
    IUnknown            *   m_pIUnknown;            // OLEDB interface to support I/O

    EBlobType               m_eBlobType;
    EBlobFormat             m_eBlobFormat;
    int                     m_iHeadLen;
    char                    m_cBlobHead[MaxCharLength];
};


///////////////////////////////////////////////////////////////////////////////////////////
//
// class CAsiColumn
//
///////////////////////////////////////////////////////////////////////////////////////////
class CAsiColumn : public CAsiObject
// This class introduces functionality of a table column. It holds a
// column descriptor and column data. Column descriptor includes the
// folowing issues, that can be set and retrieved by the CAsiColumn services:
//
//  - Column name;
//  - Whether column name is an implementation defined;
//  - Domain, if column is based on it;
//  - Data type descriptor ;
//  - Collation name, if any;
//  - Value of the default option
//  - Nullability characteristics
//  - Ordinal position of column within table
//
//


{
public:
                            CAsiColumn      (void);
                            CAsiColumn      (const CAsiIdent &);
                            CAsiColumn      (const CAsiIdent &, const CAsiSmallInt &);
                            CAsiColumn      (const CAsiIdent &, const CAsiInt &);
                            CAsiColumn      (const CAsiIdent &, const CAsiNumeric &);
                            CAsiColumn      (const CAsiIdent &, const CAsiDecimal &);
                            CAsiColumn      (const CAsiIdent &, const CAsiFloat &);
                            CAsiColumn      (const CAsiIdent &, const CAsiReal &);
                            CAsiColumn      (const CAsiIdent &, const CAsiDouble &);
                            CAsiColumn      (const CAsiIdent &, const CAsiChar &);
                            CAsiColumn      (const CAsiIdent &, const CAsiBinary &);
                            CAsiColumn      (const CAsiIdent &, const CAsiDate &);
                            CAsiColumn      (const CAsiIdent &, const CAsiTime &);
                            CAsiColumn      (const CAsiIdent &, const CAsiTimeStamp &);
                            CAsiColumn      (const CAsiIdent &, const CAsiYM &);
                            CAsiColumn      (const CAsiIdent &, const CAsiDT &);
                            CAsiColumn      (const CAsiIdent &, const CAsiIdent &); // By domain name
                            CAsiColumn      (const CAsiIdent &, CAsiData *);        // By generic data
                            CAsiColumn      (const CAsiColumn &);                   // copy constructor
                            CAsiColumn      (const DBCOLUMNINFO *);

    virtual                 ~CAsiColumn     ();
    
    // Setting Column Descriptor
    //
    void                    setName         (const CAsiIdent &);  // Set column name
    void                    setNullable     (EAsiBoolean);        // Set nullability
    void                    setNative       (EAsiBoolean);        // Set native flag
    void                    setCollation    (const CAsiUcStr &);  // Set collation name
    void                    setDefault      (CAsiData *);         // Set Default data
    void                    setDomain       (const CAsiIdent &);  // Set Domain name
    void                    setDataDsc      (CAsiData *);         // Set data descriptor
    void                    setOffset       (uint);               // Set Ordinal position

    // Read Column Descriptor
    //
    const CAsiIdent     &   Name            (void) const;         // Get column name
    EAsiBoolean             Nullable        (void) const;         // Get nullability
    EAsiBoolean             Native          (void) const;         // Get native flag
    const CAsiUcStr     *   Collation       (void) const;         // Get collation name
    CAsiData            *   Default         (void) const;         // Get Default data
    const CAsiIdent     &   Domain          (void) const;         // Get Domain name
    uint                    Offset          (void) const;         // Get Ordinal position
    EAsiBoolean             IsBookmark      (void) const;
    unsigned long           ColumnFlags     (void) const;         // OLEDB column flags
    const DBCOLUMNINFO	&	ColumnInfo		(void) const;


    // Get Access to Column Data Descriptor and Data
    //
    CAsiData          *     getData         (void) const;

    // Overloaded operators

    CAsiColumn      &       operator=       (const CAsiColumn &);
    CAsiColumn      &       operator=       (CAsiData *);

    // Runtime class iteraction functions
    //
    virtual unsigned long   packSize        (void) const;
    virtual unsigned long   packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean     unpackFrom      (CAsiObjPack *);

    virtual unsigned long   packValueSize   (void)  const;
    virtual unsigned long   packValueTo     (CAsiObjPack *) const;
    virtual EAsiBoolean     unpackValueFrom (CAsiObjPack *);

    // Duplicate column
    //
    virtual CAsiObject  *   duplicate       (void) const;

    // Release all members
    //
    virtual void            Clear           (void);

private:
    static void				setColumn		(CAsiColumn * t, const CAsiIdent & colname,
                                             CAsiData *   datadsc);

protected:
    CAsiIdent               m_idName;           // Column name
    CAsiData            *   m_pData;            // Column data descriptor and data

    EAsiBoolean             m_fNullable;        // Nullability
    EAsiBoolean             m_fNative;          // Is native
    CAsiData            *   m_pDefval;          // Default value
    CAsiIdent               m_idDomain;         // Domain name
    uint                    m_uiOffset;         // Ordinal position
    unsigned long           m_dwColFlags;       // Column flags (OLEDB column characteristics)
    DBCOLUMNINFO			m_sColumnInfo;		// Column info
};



////////////////////////////////////////////////
//
//
class CAsiRow : public CAsiObject
//
//  This class introduces functionality of a column collection
//
{
public:
                            CAsiRow			(int ColNum);
                            CAsiRow			(const CAsiRow &);
    virtual					~CAsiRow		();

    int						ColNum			(void) const;
    CAsiColumn			&	operator []		(int) const;
    int						findCol			(const CAsiIdent &) const;
    EAsiBoolean				isDistinct		(void) const;

    virtual CAsiObject	*	duplicate		(void) const;
    virtual void			Clear			(void);

private:
    CAsiColumn			*	m_pColumns;		// Columns data
    int						m_iColnum;	  	// Number of columns in row
};



////////////////////////////////////////////////
//
//
class CAsiHostBuffer: public CAsiObject
//
// This class holds information about host variable buffer. Host variable
// buffer has a dual usage in ASI: it is either as a source for dynamic
// parameters input or a destination for column value output.
// CAsiHostBuffer is a base class for CAsiParameter class, designating the
// fact that parameter has to be linked with the host variable buffer.
//
//  virtual EAsiBoolean setBind (
//    CAsiData *pData        // Pointer to host buffer
//   )
//  Bind parameter with data buffer in the host program. Host buffer
//  is represented as a CAsiData object.
//  Function returns kAsiTrue if succeeded and kAsiFalse otherwise.
//
//
//
//  virtual EAsiBoolean getBind (
//    CAsiData  **ppData         // Storage of pointer to host buffer
//   )
//
//  This function stores pointer to the host memory buffer into provided
//  memory location.
//  kAsiFalse is returned if parameter was not bound with host buffer, or
//  other abnormal situation occured.
//
{
friend class CAsiCsr;
friend class CAsiStm;

public:
    // Construction/descriptor
    //
                        CAsiHostBuffer ();
    virtual				~CAsiHostBuffer ();

    // Getting bound variable address
    //
    virtual EAsiBoolean getBind (CAsiData **) const;

    // Runtime class iteraction functions
    //

protected:
    // Binding parameter with host variable buffer
    //
    virtual EAsiBoolean setBind (CAsiData *);


protected:
    CAsiData *pData;      // Pointer to data
};


////////////////////////////////////////////////
//
//
class CAsiParameter: public CAsiHostBuffer
//
// This class describes dynamic parameter or variable reference in the SQL
// statement and its link with the host program buffer. It inherits
// functionality of the CAsiHostBuffer supercalss and reloads setBind()
// member function.
//
//  EAsiBoolean setBind (
//    CAsiData *pData,            // Pointer to host buffer
//    )
//
//  Bind parameter with the host program buffer. Function also checks
//  whether the host variable type matches the parameter type. Return
//  kAsiTrue if succeded, and kAsiFalse otherwise. Can set and push
//  complition in DDA if types mismatch error was detected.
//
{
// Friend classes
//
friend class CAsiParser;
friend class CAsiStm;
friend class CAsiDDAParams;
friend class CAsiHostLink;
friend class CAsiInterDBCursor;
friend class CAsiEmulCursor;
friend class CAsiEmulTable;

public:
                            CAsiParameter ();
                            CAsiParameter (const DBPARAMINFO *);

    virtual					~CAsiParameter ();

protected:
    // Bind parameter with host buffer
    //
    virtual EAsiBoolean		setBind     (CAsiData *);

public:
    // Setting parameter characteristics
    //
    void					setName     (const CAsiIdent &);  // name
    void					setNullable (EAsiBoolean);        // nullability characteristics
    void					setDsc      (CAsiData*);          // data descriptor

    // Getting parameter characteristics
    //
    const CAsiIdent  &		Name        (void) const;  // name
    EAsiBoolean				isNullable  (void) const;  // nullability characteristics
    CAsiData		*		Dsc         (void) const;  // data descriptor

    // Runtime class iteraction functions
    //
    virtual unsigned long	packSize        (void) const;
    virtual unsigned long	packTo          (CAsiObjPack *) const;
    virtual EAsiBoolean		unpackFrom      (CAsiObjPack *);

private:
    virtual CAsiObject *	duplicate   (void) const;
    // Nullify all members
    virtual void			Clear        (void);

private:
    CAsiIdent				ucParName;       // Parameter name
    CAsiData			*	pDataDescriptor; // Parameter data descriptor
    EAsiBoolean				eNul;          // Nullability characteristics
};




/////////////////////////////////////////////////////////////////////////////
struct ListItem {
  struct ListItem *next;
  CAsiObject *item;
};


typedef ULONG_PTR ASILISTPOS;   // List position


/////////////////////////////////////////////////////////////////////////////
//
//  class CAsiList
//
/////////////////////////////////////////////////////////////////////////////
class CAsiList: public CAsiObject
{
public:
     // Construction destruction

                            CAsiList ();
     virtual              ~ CAsiList ();

     // Add  item
     //
             EAsiBoolean    addFirst (CAsiObject *);    // Add First
             EAsiBoolean    addLast  (CAsiObject *);    // Add Last

     // Delete items
             EAsiBoolean    del         (CAsiObject *); // Delete
             EAsiBoolean    del         (int);          // Delete by number
             EAsiBoolean    detach      (CAsiObject *); // Detach object
             EAsiBoolean    detach      (int);          // Detach by number
             EAsiBoolean    delFirst    (void);         // Delete First
             EAsiBoolean    delLast     (void);         // Delete Last
             EAsiBoolean    delTail     (int);          // Delete tail
             EAsiBoolean    detachFirst (void);         // Detach First
             EAsiBoolean    detachLast  (void);         // Detach Last
             EAsiBoolean    detachTail  (int);          // Detach tail

     // Replace item
             EAsiBoolean    replace     (int,           // Replace object.
                                         CAsiObject *); // Delete the old one
             EAsiBoolean    overwrite   (int,           // Overwrite object.
                                         CAsiObject *); // Don't delete the old one


     // Manipulate list
     //
             CAsiObject   * first      (void);          // first item
             CAsiObject   * next       (void);          // Next item
             CAsiObject   * next       (ASILISTPOS);    // Next item after position
             CAsiObject   * last       (void);          // Last item
             int            qnty       (void) const;    // number of items
             void           detachAll  (void);          // Clear list
             ASILISTPOS     position   (void) const;    // Get current position
             CAsiObject   * getCurrent (void) const;    // Get current
             CAsiObject   * getAt      (ASILISTPOS) const; // Get at position

     // Operator []
             CAsiObject    *operator [] (int);         // i-th item

     // Duplicate node
     virtual  CAsiObject   *duplicate () const;
     virtual  void          Clear     (void);          // Clear list

private:
     struct ListItem *head;
     struct ListItem *tail;
     struct ListItem *current;

};


////////////////////////////////////////////////////////////////////////
//
// class CAsiIRow
//
////////////////////////////////////////////////////////////////////////
class CAsiIRow : public CAsiObject
//
// This class represents an array of pointers to the CAsiData objects
//
{
public:
                            CAsiIRow    (void);
                            CAsiIRow    (const int);
                            CAsiIRow    (const CAsiIRow &);
    virtual                 ~CAsiIRow   (void);

    int                     Quantity    (void) const;       // Number of items

    EAsiBoolean             setItem     (int, CAsiData *);  // Initialize item

    // Operators
    //
            CAsiData    *   operator [] (const int item) const;

    // Misceleneous
    //
    virtual CAsiObject  *   duplicate (void) const;
    virtual void            Clear (void);


private:
    CAsiData **values;      // Data
    int        items;       // Number of items in internal row
};

#pragma pack (pop)

#endif /* ASI_SDATA_HH */
