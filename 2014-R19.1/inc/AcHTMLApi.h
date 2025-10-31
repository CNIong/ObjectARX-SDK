#if !defined(_ACHTMLAPI_H_INCLUDED_)
#define _ACHTMLAPI_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAdUiPaletteSet;

int  acedAddHTMLPalette(CAdUiPaletteSet* ps, const ACHAR* name, const ACHAR* uriOfHtmlPage );
bool acedShowHTMLModalWindow(HWND owner, const ACHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);
void acedShowHTMLModelessWindow(HWND owner, const ACHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);
void acedLoadJSScript(const ACHAR* pUriOfJSFile);

#endif // !defined(_ACHTMLAPI_H_INCLUDED_)