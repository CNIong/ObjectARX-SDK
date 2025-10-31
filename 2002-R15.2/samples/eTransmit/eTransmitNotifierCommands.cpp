//
// (C) Copyright 2001 by Autodesk, Inc. 
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
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "eTransmitNotifier.h"
#include "AddFileHandler.h"

CComPtr<ITransmittalAddFileNotificationHandler> pHandler;
CComPtr<ITransmittalOperation> pITransmitOperation;
Adesk::Boolean bActive = Adesk::kFalse;


// This is command 'ADDNOTIFIER'
void AsdkeTransmitAddNotifier()
{
	if (bActive == Adesk::kTrue)
	{
		acutPrintf("\n*** Notifier already in place. ***");
		return;
	}	

	//	Initialise  AddFileNotification interface.
	if (!SUCCEEDED(pHandler.CoCreateInstance(CLSID_AddFileHandler)))
	{
		acedPrompt("\n*** Couldn't instantiate handler interface ***");
		return;
	}
	
	// Initialise the ITransmittalOperation interface.
	if (!SUCCEEDED(pITransmitOperation.CoCreateInstance(CLSID_TransmittalOperation)))
	{
		//	If failed, release the handler interface and end command
		acedPrompt("\n*** Couldn't instantiate Transmittal interface ***");
		pHandler.Release();
		return;
	}

	//	Subscribe to eTransmit notifications.
	if (!SUCCEEDED(pITransmitOperation->subscribeToAddFileNotification(pHandler)))
	{
		acedPrompt("\n*** Couldn't subscribe to Add File notification ***");
		pHandler.Release();
		pITransmitOperation.Release();
		return;
	}
	bActive = Adesk::kTrue;
	acedPrompt("\n*** eTransmit Notifier attached ***");
	return;
}

// This is command 'REMOVENOTIFIER'
void AsdkeTransmitRemoveNotifier()
{
	if (bActive == Adesk::kFalse)
	{
		acedPrompt("\n*** There is no eTransmit Notifier in place ***");
		return;
	}

	//	Stop subscribing to eTransmit notifications
	if (SUCCEEDED(pITransmitOperation->cancelSubscriptionToAddFileNotification(pHandler)))
	{
		pITransmitOperation.Release();
		pHandler.Release();
		bActive = Adesk::kFalse;
		acedPrompt("\n*** eTransmit Notifier removed ***");
	}
	else
	{
		acedPrompt("\n*** Can't unsubscribe from Add File notification ***");
	}
}

