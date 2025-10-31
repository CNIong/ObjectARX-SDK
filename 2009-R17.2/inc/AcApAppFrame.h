//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2007-2008  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
// 
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcAppFrame.h
//
// Description:     Application Frame interface class
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACAP_APPFRAME_H__
#define __ACAP_APPFRAME_H__

class AcApQuickAccessToolbar;
class AcApMenuBar;

/// <summary>
/// The AcApApplicationFrame class is an interface for ARX to interact and
/// manipulate Application Frame. It provides methods to retrieve Quick Access 
/// Toolbar and Menu Bar interfaces.
/// Use acedGetApplicationFrame() to retrieve a reference to AcApApplicationFrame 
/// interface.
/// </summary> 
///
class AcApApplicationFrame
{
public:
    /// <summary>
    /// This function returns a pointer to the AcApQuickAccessToolbar interface.
    /// </summary>
    ///
    /// <returns>
    /// Returns the pointer to the AcApQuickAccessToolbar interface, or NULL if
    /// the interface is not found.
    /// </returns>
    /// 
    virtual AcApQuickAccessToolbar* getQuickAccessToolbar() = 0;

    /// <summary>
    /// This function returns a pointer to the AcApMenuBar interface.
    /// </summary>
    ///
    /// <returns>
    /// Returns the pointer to the AcApMenuBar interface, or NULL if the
    /// interface is not found.
    /// </returns>
    /// 
    virtual AcApMenuBar* getMenuBar() = 0;

    /// <summary>
    /// Call this function to show or hide the menu. 
    /// </summary>
    ///
    /// <param name="bShow">
    /// Set this value to "true" to show the menu, or false otherwise.
    /// </param>
    /// 
    virtual void showMenu(bool bShow) = 0;

    /// <summary>
    /// Call this function to know if the menu is visible. 
    /// </summary>
    ///
    /// <returns>
    /// Returns true if menu is visialbe, false otherwise.
    /// </returns>
    /// 
    virtual bool isMenuVisible() const = 0;

    /// <summary>
    /// Call this function to show or hide the area below the caption bar in 
    /// application frame. This area is normally occupied by the menu bar, and 
    /// it can be blank when the menu bar is hidden.
    /// </summary>
    ///
    /// <param name="bShow">
    /// Set this value to "true" to show the area below the caption bar, or 
    /// "false" otherwise.
    /// </param>
    /// 
    virtual void showLowerCaptionArea(bool bShow) = 0;

    /// <summary>
    /// Call this function to know if the area below the caption bar in 
    /// application frame is visible. This area is normally occupied by the 
    /// menu bar, and it can be blank when the menu bar is hidden.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the area below the caption bar in application frame is 
    /// visialbe, false otherwise.
    /// </returns>
    /// 
    virtual bool isLowerCaptionAreaVisible() const = 0;
};


// AcApQuickAccessToolbar

/// <summary>
/// The _ACAPQAT_INSERTINFO structure contains the insertion information of a 
/// Quick Access Toolbar button.
/// </summary>
///
typedef struct _ACAPQAT_INSERTINFO
{
    /// <summary><para>Insertion mask. Its value can be one or more flags
    /// defined in <c>AcApQuickAccessToolbar::AcApQAT_InsertMask</c> 
    /// enumeration. The following are various possible values for this mask:
    /// </para>
    /// <list type="table">
    /// <listheader>
    ///     <term>Flag</term>
    ///     <description>Description</description>
    /// </listheader>
    /// <item><term><c>kRelativeToId</c></term>
    /// <description>This indicates that <c>nRelativeToId</c> member of the 
    /// structure carries a valid value. The new button will be inserted based 
    /// on the position of button specified by <c>nRelativeToId</c> member. Note 
    /// that this flag cannot be used with <c>kRelativeToAlias</c>. If 
    /// <c>kRelativeToId</c> and <c>kRelativeToAlias</c> are not specified, the 
    /// new button will be appended to the end of Quick Access Toolbar by 
    /// default.</description></item>
    /// <item><term><c>kRelativeToAlias</c></term>
    /// <description>This flag indicates that <c>wszRelativeToAlias</c> member 
    /// of the structure carries a valid value. The new button will be inserted 
    /// based on the position of button specified by <c>wszRelativeToAlias</c>.
    /// Note that this flag cannot be used with <c>kRelativeToId</c>. If none of
    /// <c>kRelativeToAlias</c> and <c>kRelativeToId</c> are specified, the new 
    /// button will be appended to the end of Quick Access Toolbar by default.
    /// </description></item>
    /// <item><term><c>kLoadIconFromRsrc</c></term>
    /// <description>Icon of the newly inserted button should be loaded from a 
    /// resource file. When this flag is specified, <c>hInstResource</c> and 
    /// <c>nResourceId</c> members must be valid. In addition, the runtime 
    /// expects <c>hButtonIcon</c> to be NULL. If this flag is not specified, 
    /// <c>hButtonIcon</c> will be used as the icon for the newly inserted 
    /// button.</description></item>
    /// <item><term><c>kInsertBefore</c></term>
    /// <description>Insert the new button before an existing button specified 
    /// by <c>nRelativeToId</c> or <c>wszRelativeToAlias</c> member. If this 
    /// flag is set, either <c>wszRelativeToAlias</c> or <c>nRelativeToId</c>
    /// must be valid.</description></item>
    /// </list>
    /// </summary>
    /// 
    DWORD       dwInsertMask;

    /// <summary>Insert a new button relative to the button specified by the 
    /// <c>nRelativeToId</c> member. Set <c>kRelativeToId</c> flag 
    /// in <c>dwInsertMask</c> to use this member.</summary>
    /// 
    INT         nRelativeToId;

    /// <summary>Insert a new button relative to the button specified by the 
    /// <c>wszRelativeToAlias</c> member. Set <c>kRelativeToAlias
    /// </c> flag in <c>dwInsertMask</c> to use this member.</summary>
    /// 
    LPCWSTR     wszRelativeToAlias;

    /// <summary>Handle to the icon to be used for the new button. This value 
    /// must be valid if <c>kLoadIconFromRsrc</c> is not specified. 
    /// </summary>
    /// 
    HICON       hButtonIcon;

    /// <summary>Handle to the resource module where icon specified by 
    /// <c>nResourceId</c> is to be loaded from. This member must be valid if 
    /// <c>kLoadIconFromRsrc</c> is set in <c>dwInsertMask</c>.
    /// </summary>
    /// 
    HINSTANCE   hInstResource;

    /// <summary>Identifier of the icon resource to be loaded from module 
    /// <c>hInstResource</c>. This member must be valid if 
    /// <c>kLoadIconFromRsrc</c> flag is set in <c>dwInsertMask</c>.
    /// </summary>
    /// 
    UINT        nResourceId;

    /// <summary>The identifier of the new button.</summary>
    /// 
    INT         nButtonId;

    /// <summary>The alias of the new button.</summary>
    /// 
    LPCWSTR     wszButtonAlias;

    /// <summary>The style of the new button. This member can have zero or more 
    /// values declared in <c>AcApQAT_BtnStyle</c> enumeration.</summary>
    /// 
    UINT        nButtonStyle;

    /// <summary>The state of the new button. This member can have zero or more 
    /// values declared in <c>AcApQAT_BtnState</c> enumeration.</summary>
    /// 
    UINT        nButtonState;

    /// <summary>The tool tip string for the new button. This string, if 
    /// specified, must be NULL terminated.</summary>
    /// 
    LPCWSTR     wszToolTipText;

    /// <summary>String representing the command macro for the new button. This 
    /// command macro will be sent to AutoCAD Command Line Interface for 
    /// execution when the button is clicked. If specified, this string must be 
    /// NULL terminated.</summary>
    /// 
    LPCWSTR     wszCommandMacro;

    /// <summary>Handle of the owner window. If the button does not have 
    /// <c>wszCommandMacro</c> specified, the owner window will receive a 
    /// <c>WM_COMMAND</c> (with <c>nButtonId</c> being the command ID) when the 
    /// button is clicked. <c>WM_COMMAND</c> will also be sent when AutoCAD is 
    /// in a zero-document state, even if <c>wszCommandMacro</c> is specified, 
    /// this is because command macros cannot be used in zero-document state. If 
    /// this member is not specified, <c>WM_COMMAND</c> will be sent to AutoCAD 
    /// mainframe instead.</summary>
    /// 
    HWND        hWndOwner;

} ACAPQAT_INSERTINFO, *LPACAPQAT_INSERTINFO;

/// <summary>
/// The _ACAPQAT_BTNINFO structure contains the information about a Quick 
/// Access Toolbar button.
/// </summary>
///
typedef struct _ACAPQAT_BTNINFO
{
    /// <summary>
    /// Members to retrieve or set. Its value can be one or more flags defined 
    /// in <c>AcApQuickAccessToolbar::AcApQAT_BtnInfoMask</c>.
    /// </summary>
    unsigned int nMask;
    /// <summary>
    /// Idenitfier the Quick Access Toolbar button.
    /// </summary>
    int nIdentifier;
    /// <summary>
    /// Size of wszAlias field in number of characters, this value cannot be 
    /// zero and it should include space for NULL terminating character. If this 
    /// value is -1, wszAlias must be a NULL-terminated string.
    /// </summary>
    int nAliasSize;
    /// <summary>
    /// Alias of the Quick Access Toolbar button. This string must be 
    /// NULL-terminated only when nCharCount is equal to -1.
    /// </summary>
    wchar_t* wszAlias;
    /// <summary>
    /// The index of icon in the image list of the Quick Access Toolbar button.
    /// </summary>
    int nIndexImageList;
    /// <summary>
    /// Style of the Quick Access Toolbar button. This can be one or more values
    /// specified by BtnStyle.
    /// </summary>
    unsigned int nStyle;
    /// <summary>
    /// State of the Quick Access Toolbar button. This can be one or more values
    /// specified by BtnState.
    /// </summary>
    unsigned int nState;
    /// <summary>
    /// Size of wszTooltip field in number of characters, this value cannot be 
    /// zero and it should include space for NULL terminating character. If this 
    /// value is -1, wszTooltip must be a NULL-terminated string.
    /// </summary>
    int nTooltipSize;
    /// <summary>
    /// Tooltip of the Quick Access Toolbar button. This string must be 
    /// NULL-terminated only when nCharCount is equal to -1.
    /// </summary>
    wchar_t* wszTooltip;
    /// <summary>
    /// Size of wszCommand field in number of characters, this value cannot be 
    /// zero and it should include space for NULL terminating character. If this 
    /// value is -1, wszCommand must be a NULL-terminated string.
    /// </summary>
    int nCommandSize;
    /// <summary>
    /// Command macro of the Quick Access Toolbar button. This string must be 
    /// NULL-terminated only when nCharCount is equal to -1.
    /// </summary>
    wchar_t* wszCommand;
    /// <summary>
    /// Window handle of the Owner of the Quick Access Toolbar button. Events of 
    /// this particular button are sent to this window. If this value is NULL, 
    /// button events are sent to AutoCAD mainframe.
    /// </summary>
    HWND hWndOwner;
} ACAPQAT_BTNINFO, *LPACAPQAT_BTNINFO;

/// <summary>
/// The AcApQuickAccessToolbar class is an interface for ARX to interact and manipulate
/// Quick Access Toolbar. It provides methods to add and remove Quick Access Toolbar
/// buttons and retrieve and set Quick Access Toolbar button infomation.
/// Use getQuickAccessToolbar() function in AcApApplicationFrame to retrieve 
/// a reference to AcApQuickAccessToolbar interface.
/// </summary> 
///
class AcApQuickAccessToolbar
{
public:
    /// <summary>
    /// The insertion mask used in ACAPQAT_INSERTINFO structure.
    /// The following are various possible values for this mask:
    /// </summary>
    enum AcApQAT_InsertMask
    {
        /// <summary>
        /// This indicates that <c>nRelativeToId</c> member of the structure 
        /// carries a valid value.
        /// </summary>
        kRelativeToId       = 0x0001,
        /// <summary>
        /// This flag indicates that <c>wszRelativeToAlias</c> member of the 
        /// structure carries a valid value.
        /// </summary>
        kRelativeToAlias    = 0x0002,
        /// <summary>
        /// When this flag is specified, icon of the newly inserted button 
        /// should be loaded from a resource file.
        /// </summary>
        kLoadIconFromRsrc   = 0x0004,
        /// <summary>
        /// When this flag is specified, insert the new button before an existing
        /// button specified by <c>nRelativeToId</c> or <c>wszRelativeToAlias</c> 
        /// member.
        /// </summary>
        kInsertBefore       = 0x0008,
    };

    /// <summary>
    /// Describes the members to retrieve or set. Used in ACAPQAT_BTNINFO structure
    /// The following are various possible values for this mask:
    /// </summary>
    enum AcApQAT_BtnInfoMask
    {
        /// <summary>
        /// Retrieves or sets the nIdentifier member.
        /// </summary>
        kMaskID         = 0x01,
        /// <summary>
        /// Retrieves or sets the wszAlias member.
        /// </summary>
        kMaskAlias      = 0x02,
        /// <summary>
        /// Retrieves or sets the nIndexImageList member.
        /// </summary>
        kMaskImageIndex = 0x04,
        /// <summary>
        /// Retrieves or sets the nStyle member.
        /// </summary>
        kMaskStyle      = 0x08,
        /// <summary>
        /// Retrieves or sets the nState member.
        /// </summary>
        kMaskState      = 0x10,
        /// <summary>
        /// Retrieves or sets the wszTooltip member.
        /// </summary>
        kMaskTooltip    = 0x20,
        /// <summary>
        /// Retrieves or sets the wszCommand member.
        /// </summary>
        kMaskCommand    = 0x40,
        /// <summary>
        /// Retrieves or sets the hWndOwner member.
        /// </summary>
        kMaskOwner      = 0x80,
    };

    /// <summary>
    /// The possible styles of the Quick Access Toolbar button.
    /// </summary>
    enum AcApQAT_BtnStyle 
    {
        /// <summary>
        /// The Quick Access Toolbar button is a normal button.
        /// </summary>
        kNormal     = 0x00,
        /// <summary>
        /// The Quick Access Toolbar button contains is a drop down button.
        /// </summary>
        kDropDown   = 0x01,
        /// <summary>
        /// The Quick Access Toolbar button is checkable.
        /// </summary>
        kCheckable  = 0x02,
    };

    /// <summary>
    /// The current state of the Quick Access Toolbar button.
    /// </summary>
    enum AcApQAT_BtnState
    {
        /// <summary>
        /// The Quick Access Toolbar button is currently disabled.
        /// </summary>
        kDisabled    = 0x01,
        /// <summary>
        /// The Quick Access Toolbar button is currently checked.
        /// </summary>
        kChecked     = 0x02,
        /// <summary>
        /// The Quick Access Toolbar button is currently in a mouse over event.
        /// This is a read-only property.
        /// </summary>
        kMouseOver   = 0x04,
        /// <summary>
        /// The Quick Access Toolbar button is currently in a left mouse down 
        /// event. This is a read-only property.
        /// </summary>
        kMouseDown   = 0x08,
    };

    /// <summary>
    /// This function inserts a Quick Access Toolbar button into the current 
    /// Quick Access Toolbar
    /// </summary>
    ///
    /// <param name="pInfo">
    /// A pointer to the _ACAPQAT_INSERTINFO structure containing information of
    /// the Quick Access Toolbar button to be inserted.
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool insertButton(LPACAPQAT_INSERTINFO lpInsertInfo) = 0; 

    /// <summary>
    /// This function inserts a list of Quick Access Toolbar buttons
    /// </summary>
    ///
    /// <param name="lpBtnInfo">
    /// A pointer to a list of LPACAPQAT_INSERTINFO structures containing 
    /// information of the Quick Access Toolbar buttons.
    /// </param>
    ///
    /// <param name="nButtonCount">
    /// Number of Buttons in the lpBtnInfo list to be added.
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool insertButtons(LPACAPQAT_INSERTINFO lpBtnsInfo, int nButtonCount) = 0;

    /// <summary>
    /// This function removes a Quick Access Toolbar button specified by its identifier.
    /// </summary>
    ///
    /// <param name="nIdentifier">
    /// The identifier of the Quick Access Toolbar button to be removed.
    /// </param>
    ///
    /// <returns>
    /// Return true if the Quick Access Toolbar button is removed successfully, 
    /// false otherwise.
    /// </returns>
    ///
    virtual bool removeButton(int nIdentifier) = 0;

    /// <summary>
    /// This function removes a Quick Access Toolbar button specified by its alias.
    /// </summary>
    ///
    /// <param name="wszAlias">
    /// The alias of the Quick Access Toolbar button to be removed. Comparison of 
    /// alias is case-insensitive.
    /// </param>
    ///
    /// <returns>
    /// Return true if the Quick Access Toolbar button is removed successfully, 
    /// false otherwise.
    /// </returns>
    ///
    virtual bool removeButton(const wchar_t* wszAlias) = 0;

    /// <summary>
    /// This function removes all the  Quick Access Toolbar buttons.
    /// </summary>
    ///
    /// <returns>
    /// Return true if all the Quick Access Toolbar button are removed 
    /// successfully, false otherwise.
    /// </returns>
    ///
    virtual bool removeAll() = 0;

    /// <summary>
    /// This function retrieves information of all Quick Access Toolbar Buttons.
    /// It is the caller's responsibility to free up the memory allocated for
    /// wszAlias/wszTooltip/wszCommand of each button. (e.g. delete [] wszAlias)
    /// </summary>
    ///
    /// <param name="buttonList">
    /// AcArray to a list of ACAPQAT_BTNINFO structures containing information 
    /// of the Quick Access Toolbar buttons.
    /// </param>
    ///
    virtual void getButtonList(AcArray<ACAPQAT_BTNINFO>& buttonList) = 0;

    /// <summary>
    /// This function retrieves information of a Quick Access Toolbar button specified 
    /// by its identifier.
    /// </summary>
    ///
    /// <param name="nIdentifier">
    /// The identifier of the Quick Access Toolbar button.
    /// </param>
    ///
    /// <param name="lpBtnInfo">
    /// A pointer to a _ACAPQAT_BTNINFO structure containing information for the 
    /// Quick Access Toolbar button
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool getButtonInfo(int nIdentifier, LPACAPQAT_BTNINFO lpBtnInfo) = 0;

    /// <summary>
    /// This function retrieves information of a Quick Access Toolbar button specified 
    /// by its alias.
    /// </summary>
    ///
    /// <param name="wszAlias">
    /// The alias of the Quick Access Toolbar button. Comparison of alias is 
    /// case-insensitive.
    /// </param>
    ///
    /// <param name="lpBtnInfo">
    /// A pointer to a _ACAPQAT_BTNINFO structure containing information for 
    /// the Quick Access Toolbar button
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool getButtonInfo(const wchar_t* wszAlias, LPACAPQAT_BTNINFO lpBtnInfo) = 0;

    /// <summary>
    /// This function sets the properties of a Quick Access Toolbar button specified by 
    /// its identifier.
    /// </summary>
    ///
    /// <param name="nIdentifier">
    /// The identifier of the Quick Access Toolbar button.
    /// </param>
    ///
    /// <param name="lpBtnInfo">
    /// A pointer to a _ACAPQAT_BTNINFO structure containing information for the 
    /// Quick Access Toolbar button
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool setButtonInfo(int nIdentifier, LPACAPQAT_BTNINFO lpBtnInfo) = 0;

    /// <summary>
    /// This function sets the properties of a Quick Access Toolbar button specified by 
    /// its alias.
    /// </summary>
    ///
    /// <param name="wszAlias">
    /// The alias of the Quick Access Toolbar button. Comparison of alias is 
    /// case-insensitive.
    /// </param>
    ///
    /// <param name="lpBtnInfo">
    /// A pointer to a _ACAPQAT_BTNINFO structure containing information for the 
    /// Quick Access Toolbar button
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool setButtonInfo(const wchar_t* wszAlias, LPACAPQAT_BTNINFO lpBtnInfo) = 0;
};

/// <summary>
/// The AcApMenuBar class is an interface for ARX to interact and manipulate the 
/// Menu Bar. It provides methods to replace and update menu.
/// Use getMenuBar() function in AcApApplicationFrame to retrieve a reference 
/// to AcApMenuBar interface.
/// </summary> 
///
class AcApMenuBar
{
public:
    /// <summary>
    /// This function replaces the main menu with the menu passed in.
    /// It calls the updateMenu function internally.
    /// </summary>
    ///
    /// <param name="hMenu">
    /// Handle to the menu to be set.
    /// </param>
    ///
    /// <returns>
    /// Return true if the function succeeds, false otherwise.
    /// </returns>
    ///
    virtual bool setMenuHandle(HMENU hMenu) = 0;

    /// <summary>
    /// This function updates the layout of the menu.
    /// </summary>
    ///
    virtual void updateMenu() = 0;

    /// <summary>
    /// This function retrieves the main menu handle.
    /// </summary>
    ///
    /// <returns>
    /// Returns the handle of the mainf menu.
    /// </returns>
    ///
    virtual HMENU getMenuHandle() = 0;
};


#endif // __ACAP_APPFRAME_H__