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

#ifndef ARXDBGSELSET_H
#define ARXDBGSELSET_H

/****************************************************************************
**
**  CLASS ArxDbgSelSet:
**      Thin wrapper around an AutoCAD selection set.
**  The constructor creates a "NULL" set.  If you want to
**  actually create an AutoCAD selection set, you must use one
**  of the selection mechanisms, or explicitly call createEmptySet().
**
**  **jma
**
****************************/

class ArxDbgSelSet {

public:

    enum SelSetStatus {
        kSelected,
        kNone,
        kCanceled,
		kRejected,
    };

                    ArxDbgSelSet();
    virtual         ~ArxDbgSelSet();

        // selection mechanisms
    SelSetStatus    createEmptySet();

    SelSetStatus    userSelect(const resbuf* filter = NULL);
    SelSetStatus    userSelect(LPCTSTR selectPrompt, LPCTSTR removePrompt, const resbuf* filter = NULL);

    SelSetStatus    impliedSelect(const resbuf* filter = NULL);
    SelSetStatus    crossingSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter = NULL);
    SelSetStatus    crossingPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter = NULL);
    SelSetStatus    fenceSelect(const AcGePoint3dArray& ptArray, const resbuf* filter = NULL);
    SelSetStatus    lastSelect(const resbuf* filter = NULL);
    SelSetStatus    pointSelect(const AcGePoint3d& pt1, const resbuf* filter = NULL);
    SelSetStatus    previousSelect(const resbuf* filter = NULL);
    SelSetStatus    windowSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter = NULL);
    SelSetStatus    windowPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter = NULL);
    SelSetStatus    filterOnlySelect(const resbuf* filter = NULL);
	SelSetStatus	allSelect(const resbuf* filter = NULL);
	SelSetStatus	boxSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter = NULL);

        // inquiry
    SelSetStatus    lastStatus() const;

        // options
	void			setFilterLockedLayers(bool filterThem);
    void            setAllowDuplicates(bool dups);
    void            setAllAtPickBox(bool pickBox);
    void            setAllowSingleOnly(bool single, bool allowLast);
	void			setRejectNonCurrentSpace(bool rejectIt);
	void			setRejectPaperSpaceViewport(bool rejectId);
    void            setKeywordCallback(LPCTSTR extraKwords, struct resbuf* (*pFunc) (const TCHAR*));
    void            setOtherCallback(struct resbuf* (*pFunc) (const TCHAR*));

        // operations on the selection set (backward compatibility with ADS)
    long            length();
    void            add(ads_name ent);
    void            add(const AcDbObjectId& objId);
    void            remove(ads_name ent);
    void            remove(const AcDbObjectId& objId);
    bool			member(ads_name ent);
    bool			member(const AcDbObjectId& objId);

    bool			subEntMarkerAt(long index, AcDbObjectId& objId, int& gsMarker);

        // conversion to AcDbObjectIdArray, ads_name
    void            asArray(AcDbObjectIdArray& objIds);
    void            asAdsName(ads_name ss);

private:
        // data members
    ads_name        m_ss;
    SelSetStatus    m_lastStatus;
    bool			m_allowDuplicates;
    bool			m_allAtPickBox;
    bool			m_singleOnly;
    bool			m_allowLast;
	bool			m_filterLockedLayers;
	bool			m_rejectNonCurrentSpace;
	bool			m_rejectPaperSpaceViewport;
    CString			m_flags;
    CString			m_extraKwords;
    struct resbuf* (*m_kwordFuncPtr)(const TCHAR*);
    struct resbuf* (*m_otherFuncPtr)(const TCHAR*);

        // helper functions
    bool			isInitialized() const;       // has the set been allocated by AutoCAD?
    void            clear();                     // free up ss and reinitialize
    SelSetStatus    handleResult(int result);    // common ads_ssget() return action
    void            setFlags(bool hasPrompts);

        // outlawed functions (move these up when implemented)
                    ArxDbgSelSet(const ArxDbgSelSet&);
    ArxDbgSelSet&	operator=(const ArxDbgSelSet&);
};


#endif    // ARXDBGSELSET_H
