//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXDBGXDATA_H
#define ARXDBGXDATA_H

#include "ArxDbgRbList.h"

class ArxDbgXdataList;        // forward declaration

/******************************************************************
**
**  CLASS ArxDbgAppXdata
**      encapsulates the xdata for a single application.
**  ArxDbgAppXdata can have xdata from many different apps, i.e., a list
**  of ArxDbgAppXdata objects (ArxDbgAppXdataList).
**
**  **jma
**
****************************/

class ArxDbgAppXdata {

public:
        // constructors/destructors
                    ArxDbgAppXdata(LPCTSTR appname, AcDbDatabase* db);
    virtual         ~ArxDbgAppXdata();

    // get functions
    bool        getInteger(int tag, int& value, bool speakIfMissing = true);
    bool        getLong(int tag, long& value, bool speakIfMissing = true);
    bool        getReal(int tag, double& value, bool speakIfMissing = true);
    bool        getDistance(int tag, double& value, bool speakIfMissing = true);
    bool        getScale(int tag, double& value, bool speakIfMissing = true);
    bool        getString(int tag, CString& value, bool speakIfMissing = true);  // copies into buffer
    bool        getLayer(int tag, CString& value, bool speakIfMissing = true);  // copies into buffer
    bool        getHandle(int tag, AcDbHandle& value, bool speakIfMissing = true);  // copies into buffer
    bool        getPoint(int tag, AcGePoint3d& value, bool speakIfMissing = true);
    bool        getPosition(int tag, AcGePoint3d& value, bool speakIfMissing = true);
    bool        getDisplacement(int tag, AcGePoint3d& value, bool speakIfMissing = true);
    bool        getDirection(int tag, AcGeVector3d& value, bool speakIfMissing = true);

    // set functions
    void        setInteger(int tag, int value);
    void        setLong(int tag, long value);
    void        setReal(int tag, double value);
    void        setDistance(int tag, double value);
    void        setScale(int tag, double value);
    void        setString(int tag, LPCTSTR value);
    void        setLayer(int tag, LPCTSTR value);
    void        setHandle(int tag, const AcDbHandle& value);
    void        setPoint(int tag, const AcGePoint3d& value);
    void        setPosition(int tag, const AcGePoint3d& value);
    void        setDisplacement(int tag, const AcGePoint3d& value);
    void        setDirection(int tag, const AcGeVector3d& value);

        // removal
    bool		remove(int tag);

        // operations on lists of items
    bool		detachList(int tag, ArxDbgXdataList& xdataList);
    bool		getList(int tag, ArxDbgXdataList& xdataList);
    void		setList(int tag, ArxDbgXdataList& xdataList);

        // set from a resbuf chain
    void		adoptResbufChain(resbuf* xdata);    // accepts responsibility for memory

        // get or set from AcDbObject
    void                getXdata(AcDbObject* obj);    // erases any existing data
    Acad::ErrorStatus   setXdata(AcDbObject* obj);    // object opened for write

        // data retrieval
    resbuf*		allocResbufChain();        // caller accepts copy of resbuf chain
    LPCTSTR		getAppName() const;
    bool		isEmpty();

private:
        // data members
    ArxDbgRbList	m_xdata;
    resbuf*			m_appNameNode;        // 1001 group storing the appname

        // helper functions
    bool		getGenericReal(int tag, double& value, bool speakIfMissing, int dxfType);
    bool		getGenericString(int tag, CString&, bool speakIfMissing, int dxfType);
    bool		getGenericPoint(int tag, AcGePoint3d& pt, bool speakIfMissing, int dxfType);

    void		setGenericReal(int tag, double value, int dxfType);
    void		setGenericString(int tag, LPCTSTR value, int dxfType);
    void        setGenericPoint(int tag, const AcGePoint3d& value, int dxfType);

    resbuf*     findItemStart(int tag);             // find an existing tag
    resbuf*     findItemEnd(resbuf* startPtr);      // find an existing tag's last value node
    resbuf*     detach(int tag);                    // remove from list, but don't delete
    void        addTagNode(int tag);                // add new tag specifier resbuf
    bool		isBeginList(resbuf* rb);            // is "{"
    bool		isEndList(resbuf* rb);              // is "}"

        // outlawed functions (for now)
                    ArxDbgAppXdata(const ArxDbgAppXdata&);
    ArxDbgAppXdata&	operator=(const ArxDbgAppXdata&);
};


/****************************************************************************
**
**  CLASS ArxDbgXdataList:
**
**  **jma
**
*************************************/

class ArxDbgXdataList {

friend class ArxDbgAppXdata;
friend class ArxDbgXdataListIterator;

public:
        // constructors/destructor
                ArxDbgXdataList();
    virtual     ~ArxDbgXdataList();

        // adding items to the list
    void        appendInteger(int value);
    void        appendLong(long value);
    void        appendReal(double value);
    void        appendDistance(double value);
    void        appendScale(double value);
    void        appendString(LPCTSTR value);
    void        appendLayer(LPCTSTR value);
    void        appendHandle(const AcDbHandle& value);
    void        appendPoint(const AcGePoint3d& value);
    void        appendPosition(const AcGePoint3d& value);
    void        appendDisplacement(const AcGePoint3d& value);
    void        appendDirection(const AcGeVector3d& value);

        // remove all the elements
    void        removeAll();

        // direct access to resbuf chain, use only if absolutely necessary
    void        adoptResbufChain(resbuf* xdata);
    resbuf*     orphanResbufChain();

private:
        // data members
    ArxDbgRbList	m_xdata;

        // helper functions
    void        appendGenericReal(double value, int dxfType);
    void        appendGenericString(LPCTSTR value, int dxfType);
    void        appendGenericPoint(const AcGePoint3d& value, int dxfType);

        // outlawed functions (for now)
						ArxDbgXdataList(const ArxDbgXdataList&);
    ArxDbgXdataList&	operator=(const ArxDbgXdataList&);
};



/****************************************************************************
**
**  CLASS ArxDbgXdataListIterator:
**
**  **jma
**
*************************************/

class ArxDbgXdataListIterator {

public:
        // constructor/destructor
                ArxDbgXdataListIterator(ArxDbgXdataList& xdata);
    virtual     ~ArxDbgXdataListIterator();

    void        start();	// set to start position

        // get value and advance to next position
    bool        getInteger(int& value);
    bool        getLong(long& value);
    bool        getReal(double& value);
    bool        getDistance(double& value);
    bool        getScale(double& value);
    bool        getString(CString& value);
    bool        getLayer(CString& value);
    bool        getHandle(AcDbHandle& value);
    bool        getPoint(AcGePoint3d& value);
    bool        getPosition(AcGePoint3d& value);
    bool        getDisplacement(AcGePoint3d& value);
    bool        getDirection(AcGeVector3d& value);

        // set value and advance to next position
    bool        setInteger(int value);
    bool        setLong(long value);
    bool        setReal(double value);
    bool        setDistance(double value);
    bool        setScale(double value);
    bool        setString(LPCTSTR value);
    bool        setLayer(LPCTSTR value);
    bool        setHandle(const AcDbHandle& value);
    bool        setPoint(const AcGePoint3d& value);
    bool        setPosition(const AcGePoint3d& value);
    bool        setDisplacement(const AcGePoint3d& value);
    bool        setDirection(const AcGeVector3d& value);

private:
    resbuf*		m_xdata;
    resbuf*     m_curPtr;

        // helper functions
    bool        getGenericReal(double& value, int dxfType);
    bool        getGenericString(CString&, int dxfType);
    bool        getGenericPoint(AcGePoint3d& value, int dxfType);

    bool        setGenericReal(double value, int dxfType);
    bool        setGenericString(LPCTSTR value, int dxfType);
    bool        setGenericPoint(const AcGePoint3d& value, int dxfType);

        // outlawed functions (for now)
								ArxDbgXdataListIterator(const ArxDbgXdataListIterator&);
    ArxDbgXdataListIterator&	operator=(const ArxDbgXdataListIterator&);
};

/******************************************************************
**
**  CLASS ArxDbgAppXdataList
**      All xdata for a given object.
**
**    **jma
**
****************************/

class ArxDbgAppXdataList {

friend class ArxDbgAppXdataListIterator;

public:
        // constructors/destructors
                    ArxDbgAppXdataList(AcDbObject* const obj);    // must have already opened the object
    virtual         ~ArxDbgAppXdataList();

    void            append(ArxDbgAppXdata* newApp);
    void            prepend(ArxDbgAppXdata* newApp);
    bool			contains(LPCTSTR appName) const;
    int             entries() const;
    bool			isEmpty() const;
    ArxDbgAppXdata* at(int index);
    void            removeAndDestroy();
    void            removeAndDestroy(LPCTSTR appName);

private:
    AcArray<ArxDbgAppXdata*> m_list;
    AcDbObject*     m_obj;
    resbuf*         m_xdataStart;    // place holder for -3 node

        // helper functions
    void            divideApps(resbuf* xdata);
    int             find(LPCTSTR appName) const;  // returns index to the location -1 if not contained

};


/****************************************************************************
**
**  CLASS ArxDbgAppXdataListIterator:
**
**  **jma
**
*************************************/

class ArxDbgAppXdataListIterator {

public:
        // constructors/destructor
                ArxDbgAppXdataListIterator(const ArxDbgAppXdataList& list);
    virtual     ~ArxDbgAppXdataListIterator();

    virtual void            toFirst();
    virtual void            toLast();
    virtual void            previous();
    virtual void            next();
    virtual ArxDbgAppXdata*	item() const;
    virtual bool			done() const;

private:
        // data members
    int		m_pos;
    const ArxDbgAppXdataList&  m_xdataList;

        // outlawed functions (for now)
    ArxDbgAppXdataListIterator(const ArxDbgAppXdataListIterator&);
    ArxDbgAppXdataListIterator&    operator=(const ArxDbgAppXdataListIterator&);
};


///////////////////////////////////////////////////////////////////////////////////


// global functions
void    malformedXdataTagError(int tag);
void    missingXdataTagWarning(int tag);


#endif    // ARXDBGXDATA_H
