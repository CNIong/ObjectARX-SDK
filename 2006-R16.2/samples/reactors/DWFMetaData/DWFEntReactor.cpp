//  Copyright 2004 by Autodesk, Inc.
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


#include "StdAfx.h"
#include "acpublishreactors.h"
#include "acdmmapi.h"
#include "DWFEntReactor.h"
#include <stack>



AcadEntGeneralProps ::AcadEntGeneralProps()
{
	m_nColorIndex = -1;
	m_strLayer = "";
	m_strLineType = "";
	m_dLineTypeScale = 0.0;
	m_chHandle[0]='\0';
	m_chEntityType[0] ='\0';
}
AcadEntGeneralProps::~AcadEntGeneralProps()
{
}

AcTestDMMEntReactor ::AcTestDMMEntReactor()
{

}

AcTestDMMEntReactor ::~AcTestDMMEntReactor()
{

}
//
//This function is to read the general properties of any entity
//and set the same to member variables for ready use in other functions
//For example: OnBeginEntity() uses these member values
//
void AcTestDMMEntReactor::GetEntityInfo(AcDbEntity* pEntity)
{	
	if (pEntity != NULL)
	{
		AcCmColor cColor = pEntity->color();		
		m_EntGenralPorps.m_nColorIndex =  cColor.colorIndex();
		m_EntGenralPorps.m_strLayer = pEntity->layer();
		m_EntGenralPorps.m_strLineType = pEntity->linetype();
		m_EntGenralPorps.m_dLineTypeScale = pEntity->linetypeScale();

		AcDbHandle objHandle;
		pEntity->getAcDbHandle(objHandle);
       
        objHandle.getIntoAsciiBuffer(m_EntGenralPorps.m_chHandle);
        const char *kpchEntTpe = pEntity->isA()->name();
		strcpy(m_EntGenralPorps.m_chEntityType,kpchEntTpe);
		if (stricmp ("AcDbBlockReference", m_EntGenralPorps.m_chEntityType)== 0)
		{
			m_EntGenralPorps.mIsBlockRef = true;
		}
        acutPrintf("Processing Object Id %lx, handle %s, class %s.\n",
            pEntity->objectId(), m_EntGenralPorps.m_chHandle, kpchEntTpe);       
	}	
}

// OnBeginSheet () is called before any entities are plotted
// for this sheet, to let clients know about the sheet which
// is about to be plotted.

void AcTestDMMEntReactor :: OnBeginSheet(AcDMMSheetReactorInfo * pInfo)
{
	pInfo->GetPlotLogger()->logMessage("OnBeginSheet");
	acutPrintf ("OnBeginSheet\n");		
}

// OnEndSheet is called after all entities on the sheet have been
// plotted, to let clients know that plotting of the sheet is complete.
// At this time clients may add resources and/or properties to the
// sheet which are not associated with an specific entity.
// For Example : AddPageProperties, AddPageResources
void AcTestDMMEntReactor :: OnEndSheet(AcDMMSheetReactorInfo * pInfo)
{
	acutPrintf ("OnEndSheet\n");	
	pInfo->GetPlotLogger()->logMessage("OnEndSheet");
}

// OnBeginEntity is called before each entity is plotted. This
// allows a client to determine if this entity is one for which
// it will publiush metadata, and provides the APIs needed to
// associate a Node with this entity and to associate Properties
// with the Node. The context data for the OnBeginEntity notification 
// provides methods for adding entity metadata to the DWF file.
// This notifier is sent from AcEplotX.arx
void AcTestDMMEntReactor:: OnBeginEntity(AcDMMEntityReactorInfo * pInfo)
{	
	USES_CONVERSION;
	AcDbObjectIdArray objectIds;
	bool bret;
	Acad::ErrorStatus er;
	int nNodeId = 0;

	//step1: Detect your entity
	AcDbEntity* pEntity = pInfo->entity();
	AcDbObjectId objId = pEntity->objectId();
	long oldId = objId.asOldId();

	//step2: create container for object's metadata
	AcDMMEPlotProperties props;	

	//TODO: will come back later and include the logic to process insert entities
	if(pEntity->isKindOf(AcDbBlockReference::desc()) || pEntity->isKindOf(AcDbBlockEnd::desc()))
		return;

	// Add the object Id to the objectIds array. Will be used for AcDbBlockRefernce
	//objectIds.append(objId);
	
	//check if Node has already been assigned to entity
	bool bRet = pInfo->GetEntityNode(pInfo->entity()->objectId(), objectIds, nNodeId);
	if (!bRet)
	{
		//Fetch the next unused node number		
		int nodeId = pInfo->GetNextAvailableNodeId();

		// create a Node for this entity
		const AcDMMNode * node;
		node = new AcDMMNode(nodeId, L"ACAD");
		
		GetEntityInfo(pEntity);

		//set general properties of AutoCAD entities to DWF entity
		AcCmColor cColor = pEntity->color();
		Adesk :: UInt16 colorIndex =  cColor.colorIndex();
		char * chLayerName = pEntity->layer();
		char * chLineType = pEntity->linetype();
		double dLineTypeScale = pEntity->linetypeScale();

		const wchar_t * wsUnique = pInfo->UniqueEntityId();

		//step3: Assume we want to get the handle of object and publish same as metadata
		AcDMMEPlotProperty * entityProp1 = new AcDMMEPlotProperty(L"Handle", A2W(m_EntGenralPorps.m_chHandle));
		entityProp1->SetCategory(L"DMMAPI");
		AcDMMEPlotProperty * entityProp2 = new AcDMMEPlotProperty(L"EntityType", A2W(m_EntGenralPorps.m_chEntityType));
		entityProp2->SetCategory(L"DMMAPI");

		//set entity color	
		char kpchColor[12];
		sprintf (kpchColor, "%d",m_EntGenralPorps.m_nColorIndex);
		AcDMMEPlotProperty * entityProp3 = new AcDMMEPlotProperty(L"color", A2W(kpchColor));
		entityProp3->SetCategory(L"DMMAPI");

		//set Layer	
		AcDMMEPlotProperty * entityProp4 = new AcDMMEPlotProperty(L"Layer", A2W(m_EntGenralPorps.m_strLayer.GetBuffer(m_EntGenralPorps.m_strLayer.GetLength())));
		entityProp4->SetCategory(L"DMMAPI");

		//set Linetype	
		AcDMMEPlotProperty * entityProp5 = new AcDMMEPlotProperty(L"Linetype", A2W(m_EntGenralPorps.m_strLineType.GetBuffer(m_EntGenralPorps.m_strLineType.GetLength())));
		entityProp5->SetCategory(L"DMMAPI");

		//set linetype scale
		char kpchLTypeScale[12];
		sprintf (kpchLTypeScale, "%f",m_EntGenralPorps.m_dLineTypeScale);
		AcDMMEPlotProperty * entityProp6 = new AcDMMEPlotProperty(L"Linetype Scale", A2W(kpchLTypeScale));
		entityProp6->SetCategory(L"DMMAPI");

		entityProp1->SetType(L"string");
		entityProp2->SetType(L"string");
		entityProp3->SetType(L"short");	//color
		entityProp4->SetType(L"string");//layer	
		entityProp5->SetType(L"string");//linetype
		entityProp6->SetType(L"double");//linetype scale

		//step4:Add each of AcDMMEPlotProperty objects to the AcDMMEPlotProperties 
		props.AddProperty(entityProp1);
		props.AddProperty(entityProp2);

		props.AddProperty(entityProp3);	//color
		props.AddProperty(entityProp4);	//layer
		props.AddProperty(entityProp5);	//linetype
		props.AddProperty(entityProp6);	//linetype Scale

		//got a custom entity
		if (stricmp (pEntity->isA()->name(), "AcDbMPolygon") == 0)
		{
			acutPrintf("Custom Entity AcDbMPolygon Found\n");
			AcDbMPolygon *pMPoly = AcDbMPolygon::cast (pEntity);
			double dArea = 0;
			dArea = pMPoly->getArea();		

			//set Area of Mpolygon
			char kpchBuf[12];
			sprintf (kpchBuf, "%f",dArea);
			AcDMMEPlotProperty * entityProp8 = new AcDMMEPlotProperty(L"MPoly Area", A2W(kpchBuf));
			entityProp8->SetType(L"double");//
			entityProp8->SetCategory(L"DMMAPI_CUSTOMENT");
			props.AddProperty(entityProp8);	
			
			//set perimeter
			double dPerimeter = pMPoly->getPerimeter();

			sprintf (kpchBuf, "%f",dPerimeter);
			AcDMMEPlotProperty * entityProp9 = new AcDMMEPlotProperty(L"MPoly Perimeter", A2W(kpchBuf));
			entityProp9->SetType(L"double");//
			entityProp9->SetCategory(L"DMMAPI_CUSTOMENT");
			props.AddProperty(entityProp9);		
		}
		//step5:Generate a unique ID, Assign same ID to props
		AcDMMWideString wsPropId; // need a unique string id for properties
		wsPropId =  L"ACAD";
		wsPropId += wsUnique;
		delete wsUnique;
		props.SetId(PCWIDESTR(wsPropId));

		//add props obj to cache   
		pInfo->AddProperties(&props);

		AcDMMStringVec IdVec;
		IdVec.push_back(wsPropId);

		long oldId =0;
		if (m_EntGenralPorps.mIsBlockRef)	//check if AcDbBlockReference
		{	
			AcDbBlockReference *pRef = NULL;
			pRef = AcDbBlockReference::cast (pEntity);
			if (pRef != NULL)
			{				
				oldId = pEntity->blockId().asOldId();
				AcDbObjectId  blockId = pRef->blockTableRecord();
				//oldId = blockId.asOldId();
				m_EntGenralPorps.mIsBlockRef = false;
			}
		}
		//step6: assign node to entity
		bRet = pInfo->AddNodeToMap(pEntity->objectId(), objectIds, nodeId);
		// step7: Now associate your properties with this node by calling AddPropertiesIds() 
		bRet = pInfo->AddPropertiesIds(&IdVec, (AcDMMNode &)*node);
	}
}

//OnEndEntity is called after each entity is plotted
void AcTestDMMEntReactor::OnEndEntity(AcDMMEntityReactorInfo * pInfo)
{
	AcDbEntity* pEntity = NULL;
	pEntity = pInfo->entity();
	if((pEntity->isKindOf(AcDbBlockEnd::desc()) || pEntity->isKindOf(AcDbBlockReference::desc())))
	{
		return;
	}
	int nNodeId = -1;
	//check if we got the same node id as we set in OnBeginEntity	
	bool bRet = pInfo->GetEntityNode(pInfo->entity()->objectId(), 0, nNodeId);
	acutPrintf("OnEndEntity : Node ID = %d\n",nNodeId);

}