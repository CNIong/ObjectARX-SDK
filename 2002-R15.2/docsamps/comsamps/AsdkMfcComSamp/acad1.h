// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace wrapper class

class IAcadModelSpace : public COleDispatchDriver
{
public:
	IAcadModelSpace() {}		// Calls COleDispatchDriver default constructor
	IAcadModelSpace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadModelSpace(const IAcadModelSpace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	LPDISPATCH AddCustomObject(LPCTSTR ClassName);
	LPDISPATCH Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH Add3DMesh(long M, long N, const VARIANT& PointsMatrix);
	LPDISPATCH Add3DPoly(const VARIANT& PointsArray);
	LPDISPATCH AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle);
	LPDISPATCH AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value);
	LPDISPATCH AddBox(const VARIANT& Origin, double Length, double Width, double Height);
	LPDISPATCH AddCircle(const VARIANT& Center, double Radius);
	LPDISPATCH AddCone(const VARIANT& Center, double BaseRadius, double Height);
	LPDISPATCH AddCylinder(const VARIANT& Center, double Radius, double Height);
	LPDISPATCH AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition);
	LPDISPATCH AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength);
	LPDISPATCH AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle);
	LPDISPATCH AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis);
	LPDISPATCH AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength);
	LPDISPATCH AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio);
	LPDISPATCH AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle);
	LPDISPATCH AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path);
	LPDISPATCH AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type);
	LPDISPATCH AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text);
	LPDISPATCH AddPoint(const VARIANT& Point);
	LPDISPATCH AddLightWeightPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddRay(const VARIANT& Point1, const VARIANT& Point2);
	VARIANT AddRegion(const VARIANT& ObjectList);
	LPDISPATCH AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle);
	LPDISPATCH AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH AddSphere(const VARIANT& Center, double Radius);
	LPDISPATCH AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent);
	LPDISPATCH AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height);
	LPDISPATCH AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction);
	LPDISPATCH AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius);
	LPDISPATCH AddTrace(const VARIANT& PointsArray);
	LPDISPATCH AddWedge(const VARIANT& Center, double Length, double Width, double Height);
	LPDISPATCH AddXline(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation);
	LPDISPATCH AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity);
	LPDISPATCH AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint);
	BOOL GetIsLayout();
	LPDISPATCH GetLayout();
	BOOL GetIsXRef();
	LPDISPATCH AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing);
	LPDISPATCH AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList);
	LPDISPATCH AddMLine(const VARIANT& VertexList);
	LPDISPATCH AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH GetXRefDatabase();
	LPDISPATCH AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay);
	void Unload();
	void Reload();
	void Bind(BOOL bPrefixName);
	void Detach();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDocument wrapper class

class IAcadDocument : public COleDispatchDriver
{
public:
	IAcadDocument() {}		// Calls COleDispatchDriver default constructor
	IAcadDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDocument(const IAcadDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetModelSpace();
	LPDISPATCH GetPaperSpace();
	LPDISPATCH GetBlocks();
	VARIANT CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs);
	LPDISPATCH GetGroups();
	LPDISPATCH GetDimStyles();
	LPDISPATCH GetLayers();
	LPDISPATCH GetLinetypes();
	LPDISPATCH GetDictionaries();
	LPDISPATCH GetRegisteredApplications();
	LPDISPATCH GetTextStyles();
	LPDISPATCH GetUserCoordinateSystems();
	LPDISPATCH GetViews();
	LPDISPATCH GetViewports();
	double GetElevationModelSpace();
	void SetElevationModelSpace(double newValue);
	double GetElevationPaperSpace();
	void SetElevationPaperSpace(double newValue);
	VARIANT GetLimits();
	void SetLimits(const VARIANT& newValue);
	LPDISPATCH HandleToObject(LPCTSTR Handle);
	LPDISPATCH ObjectIdToObject(long ObjectID);
	LPDISPATCH GetLayouts();
	LPDISPATCH GetPlotConfigurations();
	LPDISPATCH GetPreferences();
	LPDISPATCH GetPlot();
	LPDISPATCH GetActiveLayer();
	void SetActiveLayer(LPDISPATCH newValue);
	LPDISPATCH GetActiveLinetype();
	void SetActiveLinetype(LPDISPATCH newValue);
	LPDISPATCH GetActiveDimStyle();
	void SetActiveDimStyle(LPDISPATCH newValue);
	LPDISPATCH GetActiveTextStyle();
	void SetActiveTextStyle(LPDISPATCH newValue);
	LPDISPATCH GetActiveUCS();
	void SetActiveUCS(LPDISPATCH newValue);
	LPDISPATCH GetActiveViewport();
	void SetActiveViewport(LPDISPATCH newValue);
	LPDISPATCH GetActivePViewport();
	void SetActivePViewport(LPDISPATCH newValue);
	long GetActiveSpace();
	void SetActiveSpace(long nNewValue);
	LPDISPATCH GetSelectionSets();
	LPDISPATCH GetActiveSelectionSet();
	CString GetFullName();
	CString GetName();
	CString GetPath();
	BOOL GetObjectSnapMode();
	void SetObjectSnapMode(BOOL bNewValue);
	BOOL GetReadOnly();
	BOOL GetSaved();
	BOOL GetMSpace();
	void SetMSpace(BOOL bNewValue);
	LPDISPATCH GetUtility();
	LPDISPATCH Open(LPCTSTR FullName);
	void AuditInfo(BOOL FixErr);
	LPDISPATCH Import(LPCTSTR FileName, const VARIANT& InsertionPoint, double ScaleFactor);
	void Export(LPCTSTR FileName, LPCTSTR Extension, LPDISPATCH SelectionSet);
	LPDISPATCH New(LPCTSTR TemplateFileName);
	void Save();
	void SaveAs(LPCTSTR FullFileName, const VARIANT& SaveAsType);
	void Wblock(LPCTSTR FileName, LPDISPATCH SelectionSet);
	void PurgeAll();
	VARIANT GetVariable(LPCTSTR Name);
	void SetVariable(LPCTSTR Name, const VARIANT& Value);
	void LoadShapeFile(LPCTSTR FullName);
	void Regen(long WhichViewports);
	LPDISPATCH GetPickfirstSelectionSet();
	BOOL GetActive();
	void Activate();
	void Close(const VARIANT& SaveChanges, const VARIANT& FileName);
	void SetWindowState(long nNewValue);
	long GetWindowState();
	void SetWidth(long nNewValue);
	long GetWidth();
	void SetHeight(long nNewValue);
	long GetHeight();
	void SetActiveLayout(LPDISPATCH newValue);
	LPDISPATCH GetActiveLayout();
	void SendCommand(LPCTSTR Command);
	long GetHwnd();
	CString GetWindowTitle();
	LPDISPATCH GetApplication();
	LPDISPATCH GetDatabase();
	void StartUndoMark();
	void EndUndoMark();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadApplication wrapper class

class IAcadApplication : public COleDispatchDriver
{
public:
	IAcadApplication() {}		// Calls COleDispatchDriver default constructor
	IAcadApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadApplication(const IAcadApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CString GetName();
	CString GetCaption();
	LPDISPATCH GetApplication();
	LPDISPATCH GetActiveDocument();
	void SetActiveDocument(LPDISPATCH newValue);
	CString GetFullName();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowLeft();
	void SetWindowLeft(long nNewValue);
	CString GetPath();
	long GetLocaleId();
	long GetWindowTop();
	void SetWindowTop(long nNewValue);
	CString GetVersion();
	long GetWidth();
	void SetWidth(long nNewValue);
	LPDISPATCH GetPreferences();
	BOOL GetStatusId(LPDISPATCH VportObj);
	VARIANT ListArx();
	void LoadArx(LPCTSTR Name);
	LPDISPATCH GetInterfaceObject(LPCTSTR ProgID);
	void UnloadArx(LPCTSTR Name);
	void Update();
	void Quit();
	LPDISPATCH GetVbe();
	LPDISPATCH GetMenuGroups();
	LPDISPATCH GetMenuBar();
	void LoadDVB(LPCTSTR Name);
	void UnloadDVB(LPCTSTR Name);
	LPDISPATCH GetDocuments();
	void Eval(LPCTSTR Expression);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	void RunMacro(LPCTSTR MacroPath);
	void ZoomExtents();
	void ZoomAll();
	void ZoomCenter(const VARIANT& Center, double Magnify);
	void ZoomScaled(double scale, long ScaleType);
	void ZoomWindow(const VARIANT& LowerLeft, const VARIANT& UpperRight);
	void ZoomPickWindow();
	LPDISPATCH GetAcadState();
	void ZoomPrevious();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups wrapper class

class IAcadMenuGroups : public COleDispatchDriver
{
public:
	IAcadMenuGroups() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuGroups(const IAcadMenuGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Load(LPCTSTR MenuFileName, const VARIANT& BaseMenu);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup wrapper class

class IAcadMenuGroup : public COleDispatchDriver
{
public:
	IAcadMenuGroup() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuGroup(const IAcadMenuGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	long GetType();
	CString GetMenuFileName();
	LPDISPATCH GetMenus();
	LPDISPATCH GetToolbars();
	void Unload();
	void Save(long MenuFileType);
	void SaveAs(LPCTSTR MenuFileName, long MenuFileType);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus wrapper class

class IAcadPopupMenus : public COleDispatchDriver
{
public:
	IAcadPopupMenus() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenus(const IAcadPopupMenus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Add(LPCTSTR MenuName);
	void InsertMenuInMenuBar(LPCTSTR MenuName, const VARIANT& Index);
	void RemoveMenuFromMenuBar(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu wrapper class

class IAcadPopupMenu : public COleDispatchDriver
{
public:
	IAcadPopupMenu() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenu(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenu(const IAcadPopupMenu& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetNameNoMnemonic();
	BOOL GetShortcutMenu();
	BOOL GetOnMenuBar();
	LPDISPATCH AddMenuItem(const VARIANT& Index, LPCTSTR Label, LPCTSTR Macro);
	LPDISPATCH AddSubMenu(const VARIANT& Index, LPCTSTR Label);
	LPDISPATCH AddSeparator(const VARIANT& Index);
	void InsertInMenuBar(const VARIANT& Index);
	void RemoveFromMenuBar();
	CString GetTagString();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem wrapper class

class IAcadPopupMenuItem : public COleDispatchDriver
{
public:
	IAcadPopupMenuItem() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenuItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenuItem(const IAcadPopupMenuItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	CString GetTagString();
	void SetTagString(LPCTSTR lpszNewValue);
	BOOL GetEnable();
	void SetEnable(BOOL bNewValue);
	BOOL GetCheck();
	void SetCheck(BOOL bNewValue);
	long GetType();
	LPDISPATCH GetSubMenu();
	CString GetMacro();
	void SetMacro(LPCTSTR lpszNewValue);
	long GetIndex();
	CString GetCaption();
	CString GetHelpString();
	void SetHelpString(LPCTSTR lpszNewValue);
	void Delete();
	long GetEndSubMenuLevel();
	void SetEndSubMenuLevel(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar wrapper class

class IAcadMenuBar : public COleDispatchDriver
{
public:
	IAcadMenuBar() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuBar(const IAcadMenuBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
};
