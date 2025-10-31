//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-1999 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiComboBox_h
#define _acuiComboBox_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAcUiComboBox window

class ACUI_PORT CAcUiComboBox : public CAdUiComboBox {
    DECLARE_DYNAMIC(CAcUiComboBox);

public:
                CAcUiComboBox ();
virtual         ~CAcUiComboBox ();

// Subclassed EditBox and Validation
public:
        CAcUiEdit *AcUiEditBox ();
        BOOL    Validate ();
        ACUI_ERROR_CODE ValidateData (CString& x);
        void    Convert ();
        BOOL    ConvertData (CString& x);
        void    SetRange (double vMin, double vMax);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiAngleComboBox window
//
// ComboBox with the persistent CAcUiAngleEdit control for the Edit box

class ACUI_PORT CAcUiAngleComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiAngleComboBox);

public:
                CAcUiAngleComboBox ();
virtual         ~CAcUiAngleComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiAngleComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiAngleComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiNumericComboBox window
//
// ComboBox with the persistent CAcUiNumericEdit control for the Edit box

class ACUI_PORT CAcUiNumericComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiNumericComboBox);

public:
                CAcUiNumericComboBox ();
virtual         ~CAcUiNumericComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiNumericComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiNumericComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiStringComboBox window
//
// ComboBox with the persistent CAcUiStringEdit control for the Edit box

class ACUI_PORT CAcUiStringComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiStringComboBox);

public:
                CAcUiStringComboBox ();
virtual         ~CAcUiStringComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiStringComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiStringComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiSymbolComboBox window
//
// ComboBox with the persistent CAcUiSymbolEdit control for the Edit box

class ACUI_PORT CAcUiSymbolComboBox : public CAcUiComboBox {
    DECLARE_DYNAMIC(CAcUiSymbolComboBox);

public:
                CAcUiSymbolComboBox ();
virtual         ~CAcUiSymbolComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiSymbolComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiSymbolComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MRU Prototypes

#define ACUI_MAX_COMBOBOX_MRU   6

class ACUI_PORT CAcUiMRUComboBox;
class ACUI_PORT CAcUiMRUListBox;

typedef enum {
    kAcUiMRUCargo_Option2 = -105,
    kAcUiMRUCargo_Option1 = -104,
    kAcUiMRUCargo_Other2 = -103,
    kAcUiMRUCargo_Other1 = -102,
    kAcUiMRUCargo_None = -101
} ACUI_MRU_CARGO;

//////////////////////////////////////////////////////////////////////////////
// ComboLBox for MRU ComboBox - Provides DrawTip support

class ACUI_PORT CAcUiMRUListBox : public CAcUiListBox {
public:
                CAcUiMRUListBox ();
virtual         ~CAcUiMRUListBox ();

// Misc.
public:
virtual void    GetContentExtent (
                    int item, LPCTSTR text, int& width, int& height
                );

// AdUi message handler
protected:
virtual BOOL    OnGetTipRect (CRect& r);

// MRU control
protected:
        int     ExtraWidth ();
        CAcUiMRUComboBox *MRUComboBox ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiMRUListBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiMRUListBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MRU ComboBox

class ACUI_PORT CAcUiMRUComboBox : public CAcUiComboBox {
public:
                CAcUiMRUComboBox ();
virtual         ~CAcUiMRUComboBox ();

// Misc.
virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
virtual BOOL    GetItemColors(DRAWITEMSTRUCT& dis, COLORREF& fgColor, 
                              COLORREF& bgColor, COLORREF& fillColor);

// AdUi message handler
protected:
virtual BOOL    OnGetTipRect (CRect& r);

// MRU control
protected:
        BOOL    m_bIsDynamicCreation : 1;   // TRUE if Create() is used, else FALSE.
        BOOL    m_bUseOption1       : 1;
        BOOL    m_bUseOption2       : 1;
        BOOL    m_bUseOther1        : 1;
        BOOL    m_bUseOther2        : 1;
        BOOL    m_bOther1Selected   : 1;
        BOOL    m_bOther2Selected   : 1;
        int     m_cargoOption1;
        int     m_cargoOption2;
        LOGPALETTE *m_logPalette;
        HPALETTE m_hPalette;
        int     m_itemHeight;
        int     m_lastSelection;
        int     m_mruCargo[ACUI_MAX_COMBOBOX_MRU];
        int     m_mruLen;
        CString m_mruName[ACUI_MAX_COMBOBOX_MRU];

virtual int     CalcItemHeight ();
virtual void    DrawItemImage (CDC& dc, CRect& r, int cargo);
        BOOL    FindCargoInMRU (int cargo);
        int     GenerateCargoFromMRU (int seed);
virtual BOOL    GetOptionName (BOOL isOption2, CString& name);
virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
virtual void    OnAddItems ();
virtual void    OnComboBoxInit ();
virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel);
        void    SelectOther (BOOL isOther2);

public:
        int     AddItemToList (LPCTSTR name, int cargo);
        int     AddItemToMRU (LPCTSTR name, int cargo); // Returns item index (or -1).
        void    AddItems ();
virtual BOOL    Create (DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
virtual int     ExtraWidth ();
        int     FindItemByCargo (int cargo);            // Get corresponding item index.
        int     GetCargoOption1 ();
        int     GetCargoOption2 ();
        int     GetCurrentItemCargo ();                 // Get current item's cargo (or -1).
        int     GetItemCargo (int item);                // Get item's cargo (or -1).
        LOGPALETTE *GetLogPalette ();
        HPALETTE GetPalette ();
        BOOL    GetUseOption1 ();
        BOOL    GetUseOption2 ();
        BOOL    GetUseOther1 ();
        BOOL    GetUseOther2 ();
virtual int     ImageWidth ();
        int     InsertItemInList (int index, LPCTSTR name, int cargo);
        int     ItemHeight ();
        void    RecalcHeight ();
        void    RemoveItemFromMRU (int cargo);
        void    SetCargoOption1 (int cargo);
        void    SetCargoOption2 (int cargo);
        void    SetLastSelection (int sel);
        void    SetLogPalette (LOGPALETTE *logPalette);
        void    SetPalette (HPALETTE hPalette);
        void    SetUseOption1 (BOOL use);
        void    SetUseOption2 (BOOL use);
        void    SetUseOther1 (BOOL use);
        void    SetUseOther2 (BOOL use);

// Aliases for OptionX and OtherX
public:        
        BOOL    GetUseByBlock ();
        BOOL    GetUseByLayer ();
        BOOL    GetUseOther ();
        BOOL    GetUseWindows ();
        void    SetUseByBlock (BOOL use);
        void    SetUseByLayer (BOOL use);
        void    SetUseOther (BOOL use);
        void    SetUseWindows (BOOL use);

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiMRUComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiMRUComboBox)
	afx_msg BOOL OnCloseUp();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnDropDown();
	afx_msg BOOL OnSelEndOk();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiColorComboBox : public CAcUiMRUComboBox {
public:
                CAcUiColorComboBox ();
virtual         ~CAcUiColorComboBox ();

// MRU control
protected:
virtual void    DrawItemImage (CDC& dc, CRect& r, int cargo);
virtual void    OnAddItems ();
virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel);

// Color control
protected:
        int     m_blockColorIndex;

virtual BOOL    GetOtherColorIndex (
                    int defaultColorIndex, int layerColorIndex, BOOL enableMetaColors,
                    int& colorIndex
                );
virtual BOOL    GetWindowsColor (COLORREF& color);
        void    RGBFill (CDC& dc, CRect& rFill);
public:
        int     AddColorToMRU (int colorIndex);         // Returns item index (or -1).
        int     FindItemByColorIndex (int colorIndex);  // Get corresponding item index.
        int     GetBlockColorIndex ();
virtual COLORREF GetColorFromIndex (int colorIndex);    // Returns corresponding color.
virtual int     GetColorIndex (COLORREF color);         // Returns color index (or -1).
        int     GetCurrentItemColorIndex ();            // Get current item's color index (or -1).
virtual int     GetCurrentLayerColorIndex ();
        int     GetItemColorIndex (int item);           // Get item's color index (or -1).
virtual COLORREF LookupColor (                          // Returns corresponding raw color.
                    int colorIndex,
                    LOGPALETTE *logPalette
                );
        void    SetBlockColorIndex (int colorIndex);
        
// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiColorComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiColorComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiLineWeightComboBox : public CAcUiMRUComboBox {
public:
                CAcUiLineWeightComboBox ();
virtual         ~CAcUiLineWeightComboBox ();

// MRU control
protected:
virtual void    DrawItemImage (CDC& dc, CRect& r, int cargo);
virtual void    OnAddItems ();

// LineWeight control
protected:
        double  m_lineWeightScale;

public:
        int     FindItemByLineWeight (int lw);  // Get corresponding item index.
        int     GetCurrentItemLineWeight ();    // Get current item's LW (or -1).
        int     GetCurrentLayerLineWeight ();
        int     GetItemLineWeight (int item);   // Get item's LW (or -1).
        double  GetLineWeightScale ();
        void    SetLineWeightScale (double scale);
        void    SetUseDefault(BOOL b);

private:
        BOOL    m_bUseDefault;

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiLineWeightComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiLineWeightComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiArrowHeadComboBox : public CAcUiMRUComboBox {
public:
                CAcUiArrowHeadComboBox ();
virtual         ~CAcUiArrowHeadComboBox ();

// MRU control
protected:
virtual void    DrawItemImage (CDC& dc, CRect& r, int cargo);
virtual int     CalcItemHeight ();
virtual BOOL    GetOtherName (BOOL isOther2, CString& name);
virtual void    OnAddItems ();
virtual void    OnComboBoxInit ();

// Aliases for Option2
public:        
        BOOL    GetUseOrigin2 ();
        void    SetUseOrigin2 (BOOL use);

// ArrowHead control
private:
        CBitmap m_arrowBitmap;
        int     m_arrowCount;           // Number of images in bitmap
        int     m_arrowSize;            // Image height and width in pixels
        BOOL    m_bUseOrigin2;


public:
        int     AddArrowHeadToMRU (LPCTSTR name);   // Returns item index (or -1).

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiArrowHeadComboBox)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAcUiArrowHeadComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiPlotStyleTablesComboBox : public CAcUiMRUComboBox {
    public:
        CAcUiPlotStyleTablesComboBox ();
        CAcUiPlotStyleTablesComboBox (BOOL bInitialize);        
        virtual         ~CAcUiPlotStyleTablesComboBox ();
        // NOTE: to show color style tables, set both currentDrawing and named to false
        void    SetFileType(bool currentDrawing, bool named);
        int     AddMissingStyleTable(LPCTSTR fullFileName);
        bool    IsMissing(int index);

        virtual int     ImageWidth ();    // Override to allow setting of 0 image width. INTERNAL USE ONLY

        // override getLBText to account for the (missing) string thing
        void GetLBText(int nIndex, CString& rString) const;     // INTERNAL USE ONLY

        // Override to sort correctly.                          // INTERNAL USE ONLY
        int     AddItemToList (LPCTSTR name, int cargo);        
// MRU control
    protected:
        virtual void    DrawItemImage (CDC& dc, CRect& r, int cargo);   // INTERNAL USE ONLY
        virtual int     CalcItemHeight ();                              // INTERNAL USE ONLY
        virtual void    OnAddItems ();
        virtual void    OnComboBoxInit ();                              // INTERNAL USE ONLY

// ArrowHead control
    private:
        CBitmap m_plotStyleTablesBitmap;
        int     m_plotStyleTableBitmapSize;         // Image height and width in pixels
        BOOL    m_bImageDisplayed;                  // TRUE if image is displayed in the list.
        bool    m_bCurrentDrawing;   // Which kind of style table to populate the list with.
        bool    m_bNamed;
        BOOL    m_bInitialize;      // TRUE to initialize the contents at create time.
// ClassWizard-controlled
    public:
    //{{AFX_VIRTUAL(CAcUiPlotStyleTablesComboBox)
    //}}AFX_VIRTUAL

    protected:
    //{{AFX_MSG(CAcUiPlotStyleTablesComboBox)
    afx_msg BOOL OnDropDown();
    //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

class ACUI_PORT CAcUiPlotStyleNamesComboBox : public CAcUiMRUComboBox {
    public:
        CAcUiPlotStyleNamesComboBox ();
        virtual         ~CAcUiPlotStyleNamesComboBox ();
        virtual int     ImageWidth ();    // Override to allow setting of 0 image width. INTERNAL USE ONLY
        void            OtherRunsSelectPlotStyle() {m_whatOtherDoes = 0; }
        void            OtherRunsCurrentPlotStyle() {m_whatOtherDoes = 1; }
        void            OtherRunsDefault() {m_whatOtherDoes = -1;}
        void            SetAllowByLayerByBlock(BOOL bAllow) {m_bAllowByLayerByBlock = bAllow;}
        void            SetColorDependentMode();
        void            SetNamedMode();
   
    protected:
        virtual void    OnAddItems ();
        virtual BOOL    OnSelectOther (BOOL isOther2, int curSel, int& newSel); // INTERNAL USE ONLY
        virtual void    OnComboBoxInit ();                                      // INTERNAL USE ONLY       

    private:
        // -1 to leave up to control, 0 to run select plot style, 1 to run curent plot style.
        int m_whatOtherDoes;

        // TRUE if this control is in color depedent mode.
        BOOL m_bColorDependentMode;

        // If TRUE the following allows the selection of ByLayer/ByBlock in
        // the "Other..." dialog.
        BOOL m_bAllowByLayerByBlock;

        // Save the last set named mode settings for using ByBlock, ByLayer
        // and Other... when switched to color dependent mode.
        BOOL m_bLastByBlock;
        BOOL m_bLastByLayer;
        BOOL m_bLastUseOther;        
                
// ClassWizard-controlled
    public:
    //{{AFX_VIRTUAL(CAcUiPlotStyleNamesComboBox)
    //}}AFX_VIRTUAL

    protected:
    //{{AFX_MSG(CAcUiPlotStyleNamesComboBox)
    //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
