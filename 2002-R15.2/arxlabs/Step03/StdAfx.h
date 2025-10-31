// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__A5458F15_1F33_11D3_8D63_0060B0CDE437__INCLUDED_)
#define AFX_STDAFX_H__A5458F15_1F33_11D3_8D63_0060B0CDE437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)

#include <windows.h>

extern HINSTANCE _hdllInstance ;

// RX Includes
#include "rxdebug.h"
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager

#endif // !defined(AFX_STDAFX_H__A5458F15_1F33_11D3_8D63_0060B0CDE437__INCLUDED)
