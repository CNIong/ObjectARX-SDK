//
//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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
// layerDialog.cpp : implementation file

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "layerDialog.h"
#include <string.h>
#include "util.h"
#include "accmd.h"



// layerDialog dialog

IMPLEMENT_DYNAMIC(layerDialog, CDialog)


//constructor
layerDialog::layerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(layerDialog::IDD, pParent)
{
	/*void*/
}


//destructor
layerDialog::~layerDialog()
{
	/*void*/
}


//data exchange
void layerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAYERLIST, m_layerList);
	DDX_Control(pDX, IDC_BUTTON_ENTORDER, m_entOrderBtn);
	DDX_Control(pDX, IDC_BUTTON_LAYERORDER, m_layerOrderBtn);
}


BEGIN_MESSAGE_MAP(layerDialog, CDialog)	
	ON_BN_CLICKED(IDCLOSE, OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON_ENTORDER, OnBnClickedButtonEntorder)
	ON_BN_CLICKED(IDC_BUTTON_LAYERORDER, OnBnClickedButtonLayerorder)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTONOK, OnBnClickedButtonok)
	ON_LBN_SELCHANGE(IDC_LAYERLIST, OnLbnSelchangeLayerlist)
END_MESSAGE_MAP()


//This function display the layer order in CDraglistbox.
//"layers" is an array of layerIds. iRepeats is an interger array which indicate
//if the draworders of entities on a certain layer are continuous. For example, if
//iRepeat.at(0) is 0, the draworders of  entities on layers.at(0) are continous. If iRepeat.at(0)
//is greater than 0, draworders of entities on layers.at(0) are not continuous and the layer name 
//of layers.at(0) displayed in the list box will have a "*" prefix and postfix.
bool layerDialog::displayLayerOrder(AcDbObjectIdArray &layers, CUIntArray* iRepeats)
{
	//Clear the current display
	m_layerList.ResetContent();
	
	//if iRepeat is NULL, just list the layers' names in the array, "layers".
	if (iRepeats == NULL)
	{	
		
		for (int i = 0; i < layers.length(); i++)
		{
			AcDbObject* pLayer;
			if (Acad::eOk == acdbOpenObject(pLayer, layers.at(i), AcDb::kForRead))
			{
				const TCHAR* name;
				AcDbLayerTableRecord::cast(pLayer)->getName(name);
				TCHAR newName[260];
				_tcscpy(newName, _T(" "));
				_tcscat(newName, name);
				_tcscat(newName, _T(" "));
				m_layerList.AddString(newName);	
			}
			pLayer->close();
		}
		
		// You can't drag any item beyond the last item in CDragListbox by default.
		//This sample workaroud this problem by appending an empty string to the end of layer list.
		m_layerList.AddString(_T(""));
		
		return true;
	}
	else //if iRepeats != NULL
	{
		
		for (int i = 0; i < layers.length(); i++)
		{
			AcDbObject* pLayer;
			if (Acad::eOk == acdbOpenObject(pLayer, layers.at(i), AcDb::kForRead))
			{
				const TCHAR* name;
				AcDbLayerTableRecord::cast(pLayer)->getName(name);
				
				//iRepeats->GetAt(i) > 0 indicates the draworders of entities on layers.at(i) are not continuous
				if (iRepeats->GetAt(i) > 0)
				{
					TCHAR newName[kNameLength];
					//prefix "*"
					_tcscpy(newName, _T("*"));
					_tcscat(newName, name);
					//postfix "*"
					_tcscat(newName, _T("*"));
					m_layerList.AddString(newName);
				}else //if iRepeat->GetAt(i)==0, the draworders of entities on layers.at(i) are continous
				{
					TCHAR newName[kNameLength];
					//prefix " "
					_tcscpy(newName, _T(" "));
					_tcscat(newName, name);
					//postfix " "
					_tcscat(newName, _T(" "));
					m_layerList.AddString(newName);
				}

			}
			pLayer->close();
		}
		
		m_layerList.AddString(_T(""));
		
		return true;
	}
}


//This function is to let tooltip control to handle messages first. This is used to display tooltips on buttons
BOOL layerDialog::PreTranslateMessage(MSG* pMsg)
{
	m_tooltipCtrl.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}


// onInitDialog event handling
BOOL layerDialog::OnInitDialog( )
{
	CDialog::OnInitDialog();
	
	//Create tooltips
	m_tooltipCtrl.Create(this);
	m_tooltipCtrl.SetMaxTipWidth(300);
	m_tooltipCtrl.Activate(true);
	m_tooltipCtrl.AddTool(&m_entOrderBtn, _T("\r\n Sort the layer list by the order \r\n  entities appear in the drawing \r\n"));
	m_tooltipCtrl.AddTool(&m_layerOrderBtn, _T("\r\n Sort the layer list by the \r\n order in the layer table. \r\n"));
	
	//Displayer all the layers in the order in the layer table
	m_layerList.SubclassDlgItem(IDC_LAYERLIST, this);
	AcDbObjectIdArray arrAllLayers;
	if(getAllLayers(arrAllLayers)) 
		if(displayLayerOrder(arrAllLayers, NULL))
			return true;
	
	return false;
}


//Button,"cancel",is clicked
void layerDialog::OnBnClickedClose()
{
	OnCancel();	
}


//Button,"Sort By Entity Order", is clicked
void layerDialog::OnBnClickedButtonEntorder()
{
	Acad::ErrorStatus es ; 
	AcDbObjectIdArray ents;
	AcDbObjectIdArray layers;
	CUIntArray iRepeat;
	AcDbSortentsTable *pSortTab = NULL;
	
	//Get the AcDbSortEntsTable object
	if(getOrCreateSortEntsDictionary(pSortTab))
	{
		
		//Get the draw order of all the entities
		es = pSortTab->getFullDrawOrder(ents);
		pSortTab->close();
		pSortTab = NULL;
		if(es == Acad::eOk)
		{
			if(ents.isEmpty() == Adesk::kFalse)
			{		
				//Iterate through all the entities
				for(int i = 0; i < ents.length(); i++) 
				{
					AcDbEntity* pEnt;
					acdbOpenObject(pEnt,ents.at(i),AcDb::kForRead);
					//If the array "layers" is empty, append the entity's layerId to array "layers"
					//and append 0 to array "iRepeats"
					
					if(layers.isEmpty() == true)
					{
						layers.append(pEnt->layerId());
						iRepeat.Add(0);
					}
					else //if layers.isEmpty() == false
					{
						//If the entity's layerId is the same as the layerId of last entity, go to the next entity.
						if( pEnt->layerId() == layers.last())
							continue;
						
						int index;
						//If the entity's layerId is not the same as the last entity, but it's appeared before, change the
						//corresponding item in array "iRepeat" to 1 to indicate the draworders of entities on that layer are
						//not continuous
						if(Adesk::kTrue == layers.find( pEnt->layerId(), index))
						{
							iRepeat.SetAt(index, 1);	
						}else //If the entity's layerId hasn't appear before, append it to the array ,"layers"
						{
							layers.append(pEnt->layerId());
							iRepeat.Add(0);
						}
					}
					
					pEnt->close();	
				}

			}
		}
		//Display the layer order in the dragListBox.
		displayLayerOrder(layers, &iRepeat);
	}
}


//Button, "Sort By Layer Table" is clicked
void layerDialog::OnBnClickedButtonLayerorder()
{
	AcDbObjectIdArray arrAllLayers;
	
	//Get all the layerIds in the layer table
	getAllLayers(arrAllLayers);
	
	//Display all the layers in the order in layer table.
	displayLayerOrder(arrAllLayers,NULL);
}


//Button, "Apply", is clicked
void layerDialog::OnBnClickedButtonApply()
{
	//redraw entities based on the layer order in the dragListBox
	ApplyLayerOrder();
	
	//Refresh the layer list in the dragListBox.
	refreshList();
	
	return;
	
}


//Button,"OK" , is clicked
void layerDialog::OnBnClickedButtonok()
{
	//redraw entities based on the layer order in the dragListBox
	ApplyLayerOrder();
	
	OnOK();
}


//If the last item in the dragListBox(the empty string) is selected,
//deselect it and select the last layer name in stead.
void layerDialog::OnLbnSelchangeLayerlist()
{
	if(m_layerList.GetCurSel()==m_layerList.GetCount()-1)
	{
		m_layerList.SetCurSel(m_layerList.GetCount()-2);
	}
}


//Refresh the layer list in the dragBox after reordering the entities based on
//layer order. This is to change the prefix and postfix from "*" to " " since
//the draworders of entities on all the layers should be continuous by now.
bool layerDialog::refreshList(void)
{
	CStringArray arrItems;
	
	for(int i=0;i<m_layerList.GetCount();i++)
	{
		CString sItem;
		m_layerList.GetText(i,sItem);
		if(sItem[0]==_T('*'))
			sItem.Replace(_T('*'),_T(' '));
		arrItems.Add(sItem);
	}
	
	//Clear current display and display the updated names.
	m_layerList.ResetContent();
	
	for(int i=0;i<arrItems.GetCount();i++)
	{
		m_layerList.AddString(arrItems.GetAt(i));
	}
	
	return true;
}


//redraw all entities based on the order of the layers in the dragListBox
void layerDialog::ApplyLayerOrder(void)
{
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
	Acad::ErrorStatus es ;  
	
	if(pDb)
	{	
		AcDbObjectIdArray AllEnts;
		
		//Iterate through the layer names in the dragListBox
		for (int i = 0; i < m_layerList.GetCount()-1; i++)
		{
			AcDbObjectIdArray entsOnLayer;
			CString str;
			TCHAR* layerName;
			m_layerList.GetText(i, str);
			//Remove prefix and postfix if there is any
			if(str[0] == _T(' ') || str[0] == _T('*'))
				str = str.Mid(1, str.GetLength() - 2);
			layerName = str.GetBuffer(str.GetLength());
			//Get all the entities on the layer
			if(getAllEntitiesOnLayer(layerName, entsOnLayer))
				//Append all the entities on the layer to array, "AllEnts"
				AllEnts.append(entsOnLayer);
			str.ReleaseBuffer();
		}
		
		//Get the AcDbSortEntsTable
		AcDbSortentsTable *pSortTab = NULL;
		if(getOrCreateSortEntsDictionary(pSortTab))
		{
			//Use setRelativeDrawOrder method to set the entities' draworders based on the layer they reside
			es = pSortTab->setRelativeDrawOrder(AllEnts);
		}	
		pSortTab->close();
		pSortTab = NULL;
		
		//Regen to update the screen.
		ads_regen();
		
		return;
	}
}
