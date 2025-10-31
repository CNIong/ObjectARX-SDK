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

#ifndef ARXDBGEDINPUTCONTEXTREACTOR_H
#define ARXDBGEDINPUTCONTEXTREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgEdInputContextReactor:
**
**  **jma
**
*************************************/

class ArxDbgEdInputContextReactor : public AcEdInputContextReactor {

public:
					ArxDbgEdInputContextReactor();
    virtual			~ArxDbgEdInputContextReactor();

    virtual void	beginGetPoint(const AcGePoint3d* pointIn,
								const TCHAR* promptString,
								int initGetFlags,
								const TCHAR* pKeywords);

    virtual void	endGetPoint(Acad::PromptStatus returnStatus,
								const AcGePoint3d& pointOut,
								const TCHAR*& pKeyword);

    virtual void	beginGetAngle(const AcGePoint3d* pointIn,
                               const TCHAR* promptString,
                               int initGetFlags,
                               const TCHAR* pKeywords);

    virtual void	endGetAngle(Acad::PromptStatus returnStatus,
								double& angle,
								const TCHAR*& pKeyword);

    virtual void	beginGetDistance(const AcGePoint3d* pointIn,
                                const TCHAR* promptString,
                                int initGetFlags,
                                const TCHAR* pKeywords);

    virtual void	endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const TCHAR*& pKeyword);

    virtual void	beginGetOrientation(const AcGePoint3d* pointIn,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords);

    virtual void	endGetOrientation(Acad::PromptStatus returnStatus,
                                double& angle,
                                const TCHAR*& pKeyword);

    virtual void	beginGetCorner(const AcGePoint3d* firstCorner,
                                const TCHAR* promptString,
                                int   initGetFlags,
                                const TCHAR* pKeywords);
    
    virtual void	endGetCorner(Acad::PromptStatus returnStatus,
								AcGePoint3d& secondCorner,
								const TCHAR*& pKeyword);

    virtual void	beginGetScaleFactor(const AcGePoint3d* pointIn,
                                const TCHAR* promptString,
                                int initGetFlags,
                                const TCHAR* pKeywords);

    virtual void	endGetScaleFactor(Acad::PromptStatus returnStatus,
                                double& distance,
                                const TCHAR*& pKeyword);

    virtual void	beginGetString(const TCHAR* promptString, int initGetFlags);

    virtual void	endGetString(Acad::PromptStatus returnStatus, TCHAR* pString);

    virtual void	beginGetKeyword(const TCHAR* promptString,
                                int initGetFlags,
                                const TCHAR* pKeywords);

    virtual void	endGetKeyword(Acad::PromptStatus returnStatus, const TCHAR*& pKeyword);

    virtual void	beginGetInteger(const int* dfault,
								const TCHAR* promptString,
                                int initGetFlags,
                                const TCHAR* pKeywords);

    virtual void	endGetInteger(Acad::PromptStatus returnStatus,
								int& retValue,
								const TCHAR*& pKeyword);

    virtual void	beginGetColor(const int* dfault,
								const TCHAR* promptString,
								int initGetFlags,
								const TCHAR* pKeywords);

    virtual void	endGetColor(Acad::PromptStatus returnStatus,
								int& retValue,
								const TCHAR*& pKeyword);

    virtual void	beginGetReal(const double* dfault,
								const TCHAR* promptString,
								int   initGetFlags,
								const TCHAR* pKeywords);

    virtual void	endGetReal(Acad::PromptStatus returnStatus,
								double& returnValue,
								const TCHAR*& pKeyword);

    virtual void	beginEntsel(const TCHAR* promptString,
								int initGetFlags,
								const TCHAR* pKeywords);

    virtual void	endEntsel(Acad::PromptStatus returnStatus,
								AcDbObjectId& entPicked,
								AcGePoint3d& pickPoint,
								const TCHAR* pKeyword);

    virtual void	beginNentsel(const TCHAR* promptString,
								Adesk::Boolean pickFlag,
								int initGetFlags,
								const TCHAR* pKeywords);

    virtual void	endNentsel(Acad::PromptStatus returnStatus,
								AcDbObjectId entPicked,
								const AcGePoint3d&  pickPoint,
								const AcGeMatrix3d& xform,
								const resbuf* referenceStack,
								const TCHAR* pKeyword);

    virtual void	beginSSGet(const TCHAR*  pPrompt,
								int  initGetFlags,
								const TCHAR* pKeywords,
								const TCHAR* pSSControls, // str in ADS
								const AcArray<AcGePoint3d>& points,
								const resbuf* entMask);

    virtual void	endSSGet(Acad::PromptStatus returnStatus,
								const AcArray<AcDbObjectId>& ss);
                    
    virtual void	beginDragSequence(const TCHAR* promptString);

    virtual void	endDragSequence(Acad::PromptStatus returnStatus,
                                AcGePoint3d& pickPoint, AcGeVector3d& vec);

    virtual void	beginQuiescentState();
    virtual void	endQuiescentState();

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

	bool			suppressDetailsDuringDrag() const;
	void			setSuppressDetailsDuringDrag(bool suppressThem);

private:
		// data members
	bool	m_showDetails;
	bool	m_suppressDetailsDuringDrag;
	bool	m_dragJustStarted;

		// helper functions
    void    printReactorMessage(LPCTSTR event) const;
	void	printPrompt(const TCHAR* promptStr) const;
	void	printKeywords(const TCHAR* keywords) const;
	void	printKeywordPicked(const TCHAR*& keywordPicked) const;
	void	printInitGetFlags(int flags) const;
	void	printReturnStatus(Acad::PromptStatus returnStatus) const;
	void	printValue(LPCTSTR label, LPCTSTR value) const;
	void	printPointIn(const AcGePoint3d* pointIn) const;
	void	printFirstCorner(const AcGePoint3d* pointIn) const;
	void	printDefaultInt(const int* def) const;
	void	printDefaultReal(const double* def) const;
	void	printResbufs(LPCTSTR label, const resbuf* rb) const;
	void	printPoints(const AcGePoint3dArray& pts) const;

	bool	printDetails();

        // outlawed functions
    ArxDbgEdInputContextReactor(const ArxDbgEdInputContextReactor &copy);
    ArxDbgEdInputContextReactor&	operator=(const ArxDbgEdInputContextReactor &copy);        
};


#endif    // ARXDBGEDINPUTCONTEXTREACTOR_H
