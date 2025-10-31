//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
								const char* promptString,
								int initGetFlags,
								const char* pKeywords);

    virtual void	endGetPoint(Acad::PromptStatus returnStatus,
								const AcGePoint3d& pointOut,
								const char*& pKeyword);

    virtual void	beginGetAngle(const AcGePoint3d* pointIn,
                               const char* promptString,
                               int initGetFlags,
                               const char* pKeywords);

    virtual void	endGetAngle(Acad::PromptStatus returnStatus,
								double& angle,
								const char*& pKeyword);

    virtual void	beginGetDistance(const AcGePoint3d* pointIn,
                                const char* promptString,
                                int initGetFlags,
                                const char* pKeywords);

    virtual void	endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const char*& pKeyword);

    virtual void	beginGetOrientation(const AcGePoint3d* pointIn,
                                const char* promptString,
                                int   initGetFlags,
                                const char* pKeywords);

    virtual void	endGetOrientation(Acad::PromptStatus returnStatus,
                                double& angle,
                                const char*& pKeyword);

    virtual void	beginGetCorner(const AcGePoint3d* firstCorner,
                                const char* promptString,
                                int   initGetFlags,
                                const char* pKeywords);
    
    virtual void	endGetCorner(Acad::PromptStatus returnStatus,
								AcGePoint3d& secondCorner,
								const char*& pKeyword);

    virtual void	beginGetScaleFactor(const AcGePoint3d* pointIn,
                                const char* promptString,
                                int initGetFlags,
                                const char* pKeywords);

    virtual void	endGetScaleFactor(Acad::PromptStatus returnStatus,
                                double& distance,
                                const char*& pKeyword);

    virtual void	beginGetString(const char* promptString, int initGetFlags);

    virtual void	endGetString(Acad::PromptStatus returnStatus, const char*& pString);

    virtual void	beginGetKeyword(const char* promptString,
                                int initGetFlags,
                                const char* pKeywords);

    virtual void	endGetKeyword(Acad::PromptStatus returnStatus, const char*& pKeyword);

    virtual void	beginGetInteger(const int* dfault,
								const char* promptString,
                                int initGetFlags,
                                const char* pKeywords);

    virtual void	endGetInteger(Acad::PromptStatus returnStatus,
								int& retValue,
								const char*& pKeyword);

    virtual void	beginGetColor(const int* dfault,
								const char* promptString,
								int initGetFlags,
								const char* pKeywords);

    virtual void	endGetColor(Acad::PromptStatus returnStatus,
								int& retValue,
								const char*& pKeyword);

    virtual void	beginGetReal(const double* dfault,
								const char* promptString,
								int   initGetFlags,
								const char* pKeywords);

    virtual void	endGetReal(Acad::PromptStatus returnStatus,
								double& returnValue,
								const char*& pKeyword);

    virtual void	beginEntsel(const char* promptString,
								int initGetFlags,
								const char* pKeywords);

    virtual void	endEntsel(Acad::PromptStatus returnStatus,
								AcDbObjectId& entPicked,
								AcGePoint3d& pickPoint,
								const char* pKeyword);

    virtual void	beginNentsel(const char* promptString,
								Adesk::Boolean pickFlag,
								int initGetFlags,
								const char* pKeywords);

    virtual void	endNentsel(Acad::PromptStatus returnStatus,
								AcDbObjectId entPicked,
								const AcGePoint3d&  pickPoint,
								const AcGeMatrix3d& xform,
								const resbuf* referenceStack,
								const char* pKeyword);

    virtual void	beginSSGet(const char*  pPrompt,
								int  initGetFlags,
								const char* pKeywords,
								const char* pSSControls, // str in ADS
								const AcArray<AcGePoint3d>& points,
								const resbuf* entMask);

    virtual void	endSSGet(Acad::PromptStatus returnStatus,
								const AcArray<AcDbObjectId>& ss);
                    
    virtual void	beginDragSequence(const char* promptString);

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
	void	printPrompt(const char* promptStr) const;
	void	printKeywords(const char* keywords) const;
	void	printKeywordPicked(const char*& keywordPicked) const;
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
									ArxDbgEdInputContextReactor(const& ArxDbgEdInputContextReactor);
    ArxDbgEdInputContextReactor&	operator=(const& ArxDbgEdInputContextReactor);        
};


#endif    // ARXDBGEDINPUTCONTEXTREACTOR_H
