//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
#include "StdAfx.h"


void colorToStr(int color, CString& str, bool convertStandard)
{
    color = abs(color);    // in case used from Layer table

    if (color == 0)
        str = _T("ByBlock");
    else if (color == 256)
        str = _T("ByLayer");
    else if (convertStandard)
	{
        if (color == 1)
            str = _T("1-Red");
        else if (color == 2)
            str = _T("2-Yellow");
        else if (color == 3)
            str = _T("3-Green");
        else if (color == 4)
            str = _T("4-Cyan");
        else if (color == 5)
            str = _T("5-Blue");
        else if (color == 6)
            str = _T("6-Magenta");
        else if (color == 7)
            str = _T("7-White");
        else
            str.Format(_T("%d"), color);
    }
    else
	{
        str.Format(_T("%d"), color);
	}
}


int dxfCodeToDataType(int resType)
{
        // which data type is this value
    if ((resType >= 0) && (resType <= 9))
        return RTSTR;
    else if ((resType >= 10) && (resType <= 17))
        return RT3DPOINT;
    else if ((resType >= 38) && (resType <= 59))
        return RTREAL;
    else if ((resType >= 60) && (resType <= 79))
        return RTSHORT;
    else if ((resType >= 90) && (resType <= 99))
        return RTLONG;
    else if ((resType == 100) || (resType == 101) || (resType == 102) ||(resType == 105))
        return RTSTR;
	else if ((resType >= 110) && (resType <= 112))
		return RTSTR;
    else if ((resType >= 140) && (resType <= 149))
        return RTREAL;
    else if ((resType >= 170) && (resType <= 179))
        return RTSHORT;
    else if ((resType >= 210) && (resType <= 219))
        return RT3DPOINT;
    else if ((resType >= 270) && (resType <= 299))
        return RTSHORT;
    else if ((resType >= 300) && (resType <= 309))
        return RTSTR;
    else if ((resType >= 310) && (resType <= 369))
        return RTENAME;
    else if ((resType >= 370) && (resType <= 379))
        return RTSHORT;
    else if ((resType >= 380) && (resType <= 389))
        return RTSHORT;
    else if ((resType >= 390) && (resType <= 399))
        return RTENAME;
    else if ((resType >= 400) && (resType <= 409))
        return RTSHORT;
    else if ((resType >= 410) && (resType <= 419))
        return RTSTR;
    else if (resType == 1004)
        return resType;        // binary chunk
    else if ((resType >= 999) && (resType <= 1009))
        return RTSTR;
    else if ((resType >= 1010) && (resType <= 1013))
        return RT3DPOINT;
    else if ((resType >= 1038) && (resType <= 1059))
        return RTREAL;
    else if ((resType >= 1060) && (resType <= 1070))
        return RTSHORT;
    else if ((resType == 1071))
        return RTLONG;
    else if ((resType < 0) || (resType > 4999))
        return resType;
    else
        return RTNONE;
}


void dxfToStr(const resbuf* rb, CString& dxfCodeStr, CString& valueStr)
{
    int dataType = dxfCodeToDataType(rb->restype);
    dxfCodeStr.Format(_T("%d"), rb->restype);

    CString tmpStr;

    switch (dataType) {
        case RTSHORT:
            valueStr.Format(_T("%d"), rb->resval.rint);
            break;
        case RTLONG:
            valueStr.Format(_T("%ld"), rb->resval.rlong);
            break;
        case RTREAL:
            valueStr.Format(_T("%g"), rb->resval.rreal);
            break;
        case RTSTR:
            if (rb->resval.rstring == NULL)
                valueStr = _T("(NULL)");
            else
                valueStr.Format(_T("\"%s\""), rb->resval.rstring);
            break;
        case RT3DPOINT:
            valueStr.Format(_T("(%g, %g, %g)"), rb->resval.rpoint[X],
                        rb->resval.rpoint[Y], rb->resval.rpoint[Z]);
            break;
        case RTPOINT:
            valueStr.Format(_T("(%g, %g)"), rb->resval.rpoint[X], rb->resval.rpoint[Y]);
            break;
        case 1004:
            valueStr.Format(_T("Binary Chunk: "));
            break;
        case -6:
            valueStr = _T("Extension Dictionary");
            break;
        case -5:
            valueStr = _T("Persistent Reactors");
            break;
        case -4:
            valueStr.Format(_T("Conditional Operator: \"%s\""), rb->resval.rstring);
            break;
        case -3:
            valueStr = _T("Start of Xdata");
            break;
        case -2:
            valueStr.Format(_T("<Entity Name Reference: %8lx>"), rb->resval.rlname[0]);
            break;
        case -1:
        case RTENAME:
            if ((rb->restype >= 330 )&& (rb->restype < 340))
                valueStr.Format(_T("<Soft Pointer: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 340) && (rb->restype < 350))
                valueStr.Format(_T("<Hard Pointer: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 350) && (rb->restype < 360))
                valueStr.Format(_T("<Soft Ownership: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 360) && (rb->restype < 370))
                valueStr.Format(_T("<Hard Ownership: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 390) && (rb->restype < 399))
                valueStr.Format(_T("<Hard Pointer: %8lx>"), rb->resval.rlname[0]);
            else
                valueStr.Format(_T("<Entity Name: %8lx>"), rb->resval.rlname[0]);
            break;
        case RTPICKS:
            valueStr.Format(_T("<Selection Set: %8lx>"), rb->resval.rlname[0]);
            break;
        case RTLB:
            valueStr = _T("List Begin");
            break;
        case RTLE:
            valueStr = _T("List End");
            break;
        case RTNIL:
            valueStr = _T("NIL");
            break;
        case RTT:
            valueStr = _T("T");
            break;
        default:
            valueStr = _T("*Unknown*");
            break;
    }
}

void FindPixleRatio(double &dX)
{
	AcGePoint3d point1;
	AcGePoint3d point2;

	acedCoordFromPixelToWorld(CPoint(10,10), asDblArray(point1));
	acedCoordFromPixelToWorld(CPoint(110,10), asDblArray(point2));

	//only x value
	dX = abs(point1.x - point2.x) * 0.01 ;

}

BOOL GetTooltipDataFromBlockReference(AcDbBlockReference *pRef, CString &strImageName, CString &strImageDescription)
{
	int nCount = 0;
	if(pRef != NULL)
	{
		AcDbObjectIterator *pIterator =  pRef->attributeIterator();
		

		if(pIterator != NULL)
		{
			while(pIterator->done() == false)
			{
				AcDbAttribute *pAttribute = NULL;
				::AcDbObjectId attId =  pIterator->objectId();

				if(pRef->openAttribute(pAttribute, attId, AcDb::kForRead) == eOk)
				{
					ACHAR *szTag = pAttribute->tag();

					if(_tcsicmp(szTag, L"IMAGE") == 0)
					{
						//update the graphics
						strImageName = pAttribute->textString();
						nCount++;
					}
					else if(_tcsicmp(szTag, L"TEXT_DESCRIPTION") == 0)
					{
						strImageDescription = pAttribute->textString();
						nCount++;
					}
					pAttribute->close();
				}

				pIterator->step();
			}
			delete pIterator;
		}
	}

	if(nCount != 2)
		return FALSE;

	return TRUE;

}