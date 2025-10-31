//
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

#ifndef AcDMMEPlotProperty_h
#define AcDMMEPlotProperty_h


/////////////////////////////////////////////////////////////////////////
// class AcDMMEPlotProperty
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class is a lightweight proxy for the DWF EPlotProperty object.
/// It allows clients of the DMM (DWF Metadata Manager) API to add
/// properties to an AcDMMEPlotProperties object which in turn
/// is used to associate properties with an entity in a DWF file
/// without linking to the DWF toolkit
/// </summary>
///
/// <remarks>
/// This is just a container for Unicode strings. Two of these are required,
/// the property name and its value. The other three are optional. If the 
/// strings are not already XML encoded, they will be encoded when this 
/// object is converted to the corresponding DWF toolkit object and this
/// can result in significant expansion of the string due to the
/// escaping of reserved characters. The maximum length of any encoded
/// attribute string is 8192 bytes.
/// </remarks>
///
class AcDMMEPlotProperty
{
public:

    /// <summary>
    /// Default constructor
    /// </summary>
    ///
    /// <remarks> initializes data members to an empty state
    /// </remarks>
    ///
    AcDMMEPlotProperty()
    {
        m_name = NULL;
        m_value = NULL;
        m_type = NULL;
        m_units = NULL;
        m_category = NULL;
    }
    
    /// <summary>
    /// constructs an AcDMMEPlotProperty wrapping a name and value
    /// </summary>
    ///
    /// <param name="name">
    /// a Unicode string supplying the name of the property
    /// </param>
    ///
    /// <param name="value">
    /// a Unicode string supplying a value for the property
    /// this must not exceed 8192 bytes after xml encoding
    /// </param>
    ///
    /// <remarks> can construct from two wide strings supplying just 
    /// the property name and property value. 
    /// </remarks>
    ///
    AcDMMEPlotProperty(wchar_t *name, wchar_t * value)
    {
        if (NULL != name) {
            m_name = new wchar_t[::wcslen(name) + 1];
            ::wcscpy(m_name, name);
        } else {
            m_name = NULL;
        }    
    
        if (NULL != value) {
            m_value = new wchar_t[::wcslen(value) + 1];
            ::wcscpy(m_value, value);
        } else {
            m_value = NULL;
        }    
        m_category = NULL;
        m_type = NULL;
        m_units = NULL;
    }
    
    /// <summary>
    /// Copy Constructor
    /// </summary>
    ///
    /// <param name="src">
    /// The object to copy from
    /// </param>
    ///
    AcDMMEPlotProperty(const AcDMMEPlotProperty &src)
    {
        m_name = NULL;
        m_value = NULL;
        m_type = NULL;
        m_units = NULL;
        m_category = NULL;
        {*this = src;}
    }


    /// <summary>
    /// Destructor
    /// </summary>
    ///
    /// <remarks>
    /// The string data in the property is freed by this destructor
    /// </remarks>
    ///
    ~AcDMMEPlotProperty()
    {
        if (NULL != m_name)
            delete m_name;
        if (NULL != m_value)
            delete m_value;
        if (NULL != m_category)
            delete m_category;
        if (NULL != m_type)
            delete m_type;
        if (NULL != m_units)
            delete m_units;
    }
    
    /// <summary>
    /// mutator for the optional Type attribute
    /// </summary>
    ///
    /// <param name ="type">
    /// A Unicode string setting the DWF type of the property
    /// </param>
    ///
    /// <remarks>
    /// type is an optional Unicode string
    ///    
    /// some recognized type name strings:
    /// String_List_Type "string"
    /// Boolean_Type "boolean"
    /// UriReference_Type "uriReference"
    /// TimeDuration_Type "timeDuration"
    /// TimeInstant_Type "timeInstant"
    /// Date_Type "date"
    /// Month_Type "month"
    /// Year_Type "year"
    /// Century_Type "century"
    /// RecurringDate_Type "recurringDate"
    /// RecurringDay_Type "recurringDay"
    /// Float_Type "float"
    /// Double_Type "double"
    /// Double_List_Type "doubleList"
    /// Long_Type  "long"
    /// Long_List_Type; "longList"
    /// Int_Type "int"
    /// Short_Type "short"
    /// Byte_Type "byte"
    /// UnsignedLong_Type "unsignedLong"
    /// UnsignedInt_Type "unsignedint"
    /// UnsignedShort_Type "unsignedShort"
    /// UnsignedByte_Type "unsignedByte"
    /// StringList_Type "stringList"
    ///
    /// Note: the List types are space separated lists of values 
    /// </remarks>
    void SetType(wchar_t * type)
    {
        if (m_type) 
            delete m_type;
            m_type = NULL;
    
        if (NULL != type) {
            m_type = new wchar_t[::wcslen(type) + 1];
            ::wcscpy(m_type, type);
        } else {
            m_type = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the optional Type attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Type string
    /// </returns>
    const wchar_t * GetType() const
    {
        return m_type;
    }
    
    
    /// <summary>
    /// mutator for the optional Units attribute
    /// </summary>
    ///
    /// <param name ="units">
    /// A Unicode string setting the DWF units of the property
    /// </param>
    ///
    /// <remarks>
    /// The units string is appended to the value string by the viewer
    /// when displaying properties. The convention is that they should be
    /// English and obvious, e.g., standard, abbreviations wherever possible.
    /// Examples include mm, cm, m, km, in, ft, yd and mi.
    /// </remarks>
    void SetUnits(wchar_t * units)
    {
        if (m_units) 
            delete m_units;
            m_units = NULL;
    
        if (NULL != units) {
            m_units = new wchar_t[::wcslen(units) + 1];
            ::wcscpy(m_units, units);
        } else {
            m_units = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the optional Units attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Units string
    /// </returns>
    const wchar_t * GetUnits() const
    {
        return m_units;
    }
    
    
    /// <summary>
    /// mutator for the optional Category attribute
    /// </summary>
    ///
    /// <param name ="category">
    /// A Unicode string setting the category of the property
    /// </param>
    ///
    /// <remarks>
    /// category is a Unicode string property for categorizing objects
    /// The category string is displayed in the DWF viewer properties window
    /// Clients may use category in various ways. The viewer recognizes one
    /// magic category, hidden, which will cause it not to display the 
    /// property.
    /// </remarks>
    ///
    void SetCategory(wchar_t * category)
    {
        if (m_category) 
            delete m_category;
            m_category = NULL;
    
        if (NULL != category) {
            m_category = new wchar_t[::wcslen(category) + 1];
            ::wcscpy(m_category, category);
        } else {
            m_category = NULL;
        }    
    }
    
    
    /// <summary>
    /// accessor for the optional Category attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Category string
    /// </returns>
    ///
    const wchar_t * GetCategory() const
    {
        return m_category;
    }


    /// <summary>
    /// mutator for the required property Name attribute
    /// </summary>
    ///
    /// <param name ="name">
    /// A Unicode string setting the name of the property
    /// </param>
    ///
    /// <remarks>
    /// the name is a Unicode string property 
    /// The name string is displayed in the DWF viewer properties window
    /// </remarks>
    ///
    void SetName(wchar_t * name)
    {
        if (m_name) 
            delete m_name;
            m_name = NULL;
    
        if (NULL != name) {
            m_name = new wchar_t[::wcslen(name) + 1];
            ::wcscpy(m_name, name);
        } else {
            m_name = NULL;
        }    
    }
        
        
    /// <summary>
    /// accessor for the required property name attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode name string
    /// </returns>
    ///
    const wchar_t * GetName() const
    {
        return m_name;
    }
    
    /// <summary>
    /// mutator for the reqiured property Value attribute
    /// </summary>
    ///
    /// <param name ="value">
    /// A Unicode string setting the value of the property
    /// </param>
    ///
    /// <remarks>
    /// value is a Unicode string property for objects
    /// The value string is displayed in the DWF viewer properties window
    /// </remarks>
    void SetValue(wchar_t * value)
    {
        if (m_value) 
            delete m_value;
            m_value = NULL;
    
        if (NULL != value) {
            m_value = new wchar_t[::wcslen(value) + 1];
            ::wcscpy(m_value, value);
        } else {
            m_value = NULL;
        }    
    }
    
    /// <summary>
    /// accessor for the required proterty Value attribute
    /// </summary>
    ///
    /// <returns>
    /// Returns a const pointer to the Unicode Value string
    /// </returns>
    ///
    const wchar_t * GetValue() const
    {
        return m_value;
    }
    
    /// <summary>
    /// operator= also used by the copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    ///
    AcDMMEPlotProperty& operator= (const AcDMMEPlotProperty& src)
    {
        if (this == &src)
            return *this;
    
        SetName(src.m_name);
        SetValue(src.m_value);
        SetType(src.m_type);
        SetUnits(src.m_units);
        SetCategory(src.m_category);
        return *this;
    }
    
    
private:
    wchar_t * m_name; 
    wchar_t * m_value;
    wchar_t * m_type;
    wchar_t * m_units;
    wchar_t * m_category;
    
};
    
typedef std::vector<AcDMMEPlotProperty> AcDMMEPlotPropertyVec;
    
#endif // AcDMMEPlotProperty_h
