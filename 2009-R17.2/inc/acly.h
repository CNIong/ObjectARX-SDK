#ifndef _AC_LY_H
#define _AC_LY_H
//
// Copyright (C) 2003-2006 by Autodesk, Inc.
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

#include "AdAChar.h"
#include "acadstrc.h"
#include "acarray.h"
#include "dbsymtb.h"
#include "dbxrecrd.h"


//Filter parse tree API (read-only)
//
//represents an relational expression of the form:
//variable OP constant
//where OP is either the equality operator (==) or the LIKE 
//operator
//
class AcLyRelExpr 
{
public:
    virtual const ACHAR * getVariable() const = 0;
    virtual const ACHAR * getConstant() const = 0;
};
//represents a term of the form:
//a AND b
class AcLyAndExpr 
{
public:
    virtual ~AcLyAndExpr() { }
    virtual const AcArray<AcLyRelExpr*>& getRelExprs() const = 0;
};
//represents an expression of the form:
//(a AND b) OR (c AND d) OR (e AND f)
class AcLyBoolExpr 
{
public:
    virtual ~AcLyBoolExpr() { }
    virtual const AcArray<AcLyAndExpr*>& getAndExprs() const = 0;
};

#ifndef HIMAGELIST
struct _IMAGELIST;
typedef struct _IMAGELIST* HIMAGELIST;
#endif

//Main filter API. All layer filters implement this interface.
class AcLyLayerFilter : public AcRxObject, public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcLyLayerFilter);
    AcLyLayerFilter ();
    virtual ~AcLyLayerFilter ();

    //persistent name of filter, some filters may not allow
    //renaming ("All", "Xref", etc.)
    virtual const ACHAR * name() const;
    virtual Acad::ErrorStatus setName(const ACHAR *);
    virtual bool allowRename() const;

    virtual Acad::ErrorStatus getImages(HIMAGELIST& imageList, Adesk::UInt32& normalImage, Adesk::UInt32& selected) const;

    virtual AcLyLayerFilter* parent() const;

    //nested filter manipulation
    virtual const AcArray<AcLyLayerFilter*>& getNestedFilters() const;
    virtual Acad::ErrorStatus addNested(AcLyLayerFilter* filter);
    virtual Acad::ErrorStatus removeNested(AcLyLayerFilter* filter);

    //some filters generate nested filters automatically (xref, standard)
    //the following api will be called on filters after they are loaded to allow 
    //them to regenerate their nested filters
    virtual Acad::ErrorStatus generateNested();

    //returns true if this filter was dynamically generated i.e.
    //it doesn't persist on its own
    virtual bool dynamicallyGenerated() const;

    //returns true if this filter can have nested filters
    virtual bool allowNested() const;

    //returns true if this filter can be removed
    virtual bool allowDelete() const;

    //return true if this filter is a proxy for an
    //unknown filter (we are not going to show these on the UI)
    virtual bool isProxy() const;

    //groups are id filters, i.e. filters on layer id.
    virtual bool isIdFilter() const;
    
    //returns true if the given layer is "visible" with this filter
    //false otherwise
    virtual bool filter(AcDbLayerTableRecord* layer) const;

    //called by host application to show an editor window for the filter.
    //Display the editor as child of the active popup window
    //Return kUseDefault if you want to instruct the host application to
    //display the default filter dialog.
    enum DialogResult {kOk = 0, kCancel=1, kUseDefault = 2};
    virtual  DialogResult showEditor();

    virtual const ACHAR * filterExpression() const;
    virtual Acad::ErrorStatus setFilterExpression(const ACHAR * expr);

    //returns a simple expression tree for this filter
    virtual const AcLyBoolExpr* filterExpressionTree() const;

    /*
    BNF for the valid boolean expression we evaluate
    <bool_expr>::= <bool_expr> or <and_expr> | <and_expr>
    <and_expr>::=<and_expr> and <rel_expr> | <rel_expr>
    <rel_expr>::=<variable><rel_op><constant> 
    <rel_op>::= == | !=
    <constant>::=A-Z0-9*?~@.,-
    <variable>::=#A-Z0-9
    */

    //returns true if this and pOther will allow the same
    //layers
    virtual bool compareTo(const AcLyLayerFilter* pOther) const;

    //persistence support
    //
    //read/write native data, we use a dxf filer to decouple the filter
    //from the underlying xrecod. This is necessary to support custom filter
    //types.
    virtual Acad::ErrorStatus readFrom(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus writeTo(AcDbDxfFiler* pFiler) const;

private:
    void *mp_impObj;
    friend class AcLySystemInternals;

protected:
    AcLyLayerFilter(AcLySystemInternals*);
};


class AcLyLayerGroup : public AcLyLayerFilter
{
public:
    ACRX_DECLARE_MEMBERS(AcLyLayerGroup);
    AcLyLayerGroup();

    virtual Acad::ErrorStatus        addLayerId    (const AcDbObjectId& id);
    virtual Acad::ErrorStatus        removeLayerId (const AcDbObjectId& id);
    virtual const AcDbObjectIdArray& layerIds      () const;

protected:
    AcLyLayerGroup(AcLySystemInternals*);
};


class AcLyLayerFilterManager
{
public:
    //reads the filters from the database this manager belongs to, and returns
    //the root filter in pRoot.
    //The caller is responsible for deleting  the filters
    //by calling delete pRoot;
    virtual Acad::ErrorStatus getFilters(AcLyLayerFilter*& pRoot, AcLyLayerFilter*& pCurrent) = 0;
    //writes the filters pointer by pRoot into the current
    //database, call the various writeTo methods on each filter
    virtual Acad::ErrorStatus setFilters( const AcLyLayerFilter* pRoot, const AcLyLayerFilter* pCurrent) = 0;
};

//returns the filter manager for the given database
AcLyLayerFilterManager* aclyGetLayerFilterManager(AcDbDatabase* pDb);

#endif  // _AC_LY_H
