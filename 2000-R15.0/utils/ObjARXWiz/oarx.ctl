[!Debug()]
[!set(AddCppTemplate,"TRUE")]
[!newguid(InterfaceGUID)]

[!Dialog("Ax2DbConn", "Names98","AxOPM")]
[!set(ErrorInfoEnabled,"TRUE")]
[!set(FreeThreadedMarshaler,"FALSE")]
[!set(ConnectionPointsEnabled, "FALSE")]
[!set(Dual,"TRUE")]
[!set(ThreadingModel, "Single")]
[!set(Aggregatable,"NO")]

[!if=(ConnectionPointsEnabled, "TRUE")]
[!newguid(InterfaceGUIDCP)]
[!endif]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "oarx.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "oarx.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "oarx.rgs")]
[!AddSymbolToSymbol(RGSName, ProjectDirectory, ShortName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]

[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperShortName)]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]

[!target(HeaderName)]
[!include(HeaderTemplate)]
[!target()]

[!target(CPPName)]
[!include(CPPTemplate)]
[!target()]

[!AddStringToSymbol(IDLCoClass, GalleryPath, "oarxco.idl")]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!target(IDLName)]
[!include(IDLTemplate)]
[!target()]

[!AddToObjectMap(CoClassName, ClassName)]
[!AddImportFile(IDLProject, "oaidl.idl")]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

[!set(AddCppTemplate,"FALSE")]
[!if=(DbServerAlreadyLoaded,"FALSE")]
[!ExistsMemberFunction(NULLSTR,"BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)",DllMainExists)]
[!if=(DllMainExists,"1")]
	[!AddToMemberFunction(NULLSTR, "BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)", CPPTemplate, InsertDbServerName,BEGIN)]
	[!AddToMemberFunction(NULLSTR, "BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)", CPPTemplate, InsertLoadDbServer, AFTERSEARCH, "DisableThreadLibraryCalls(hInstance)")]
	[!AddToMemberFunction(NULLSTR, "BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)", CPPTemplate, InsertUnloadDbServer, BEFORESEARCH, "_Module.Term()")]
[!else]
	[!AddMemberVariable(CWinApp, "m_strDbServerName","const char*","ACCESS_PROTECTED","1",AcDbServerNameVariable)]
	[!AddToMemberFunction(CWinApp, "BOOL InitInstance()", CPPTemplate, InsertLoadDbServer, BEFORESEARCH, "return CWinApp::InitInstance();")]
	[!AddToMemberFunction(CWinApp, "int ExitInstance()", CPPTemplate, InsertUnloadDbServer, BEFORESEARCH, "return CWinApp::ExitInstance();")]
[!endif]
[!endif]
