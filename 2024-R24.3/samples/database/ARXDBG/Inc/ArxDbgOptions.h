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

#ifndef ARXDBGOPTIONS_H
#define ARXDBGOPTIONS_H

/****************************************************************************
**
**  CLASS ArxDbgOptions:
**
**  **jma
**
*************************************/

class ArxDbgOptions {

public:
				ArxDbgOptions();
	virtual		~ArxDbgOptions()	{}

        // data members (public since this is just a simple container)
    bool    m_showDwgFilerMessages;
    bool    m_showWblockCloneDetails;
    bool    m_showDeepCloneDetails;
    bool    m_doDictRecordInsertByHand;

	static ArxDbgOptions	m_instance;
};

#endif  // ARXDBGOPTIONS_H
