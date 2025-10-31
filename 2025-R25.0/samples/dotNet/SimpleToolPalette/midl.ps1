$vsInstallPath = & "${env:ProgramFiles(x86)}/Microsoft Visual Studio/Installer/vswhere.exe" -latest -property installationPath;
Import-Module "$vsInstallPath/Common7/Tools/Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -VsInstallPath $vsInstallPath -SkipAutomaticLocation

& midl.exe /header nul /iid nul /proxy nul /dlldata nul $args[0]