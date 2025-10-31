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

#ifndef ARXDBGEDUICONTEXT_H
#define ARXDBGEDUICONTEXT_H

/**************************************************************************
**
**  CLASS ArxDbgEdUiContextApp
**
**  **jma
**
*************************************/

class ArxDbgEdUiContextApp : public AcEdUIContext {

public:
				ArxDbgEdUiContextApp();
	virtual		~ArxDbgEdUiContextApp();

    //ACRX_DECLARE_MEMBERS(ArxDbgEdUiContextApp);

    virtual void*	getMenuContext(const AcRxClass* classtype, const AcDbObjectIdArray& selectedObjs);
    virtual void	onCommand(Adesk::UInt32 cmdId);

	bool			isValid() const { return (m_cMenu != NULL); }

private:
		// data members
    CMenu*		m_cMenu;
    HMENU		m_hMenu;
};

#endif // ARXDBGEDUICONTEXT_H