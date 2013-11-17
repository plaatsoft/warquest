;
; RedSquare windows installer configurationm file.
;
; The file can be processed with "Inno Setup Compiler v5.3.11"
;
; All Copyrights Reserved (c) PlaatSoft 2008-2013

[Setup]
AppPublisher=PlaatSoft
AppPublisherURL=http://www.plaatsoft.nl
AppName=WarQuest
AppVerName=PlaatSoft WarQuest v1.5
AppVersion=1.5
AppCopyright=Copyright (C) 2008-2013 PlaatSoft

DefaultDirName={pf}\WarQuest
DefaultGroupName=PlaatSoft
UninstallDisplayIcon={app}\WarQuest.exe
Compression=lzma
SolidCompression=yes
OutputDir=release\

[Files]
Source: "build\release\WarQuest.exe"; DestDir: "{app}"
Source: "build\release\Qt5Widgets.dll"; DestDir: "{app}"
Source: "build\release\Qt5WebKitWidgets.dll"; DestDir: "{app}"
Source: "build\release\Qt5WebKit.dll"; DestDir: "{app}"
Source: "build\release\Qt5V8.dll"; DestDir: "{app}"
Source: "build\release\Qt5Sql.dll"; DestDir: "{app}"
Source: "build\release\Qt5Quick.dll"; DestDir: "{app}"
Source: "build\release\Qt5Qml.dll"; DestDir: "{app}"
Source: "build\release\Qt5PrintSupport.dll"; DestDir: "{app}"
Source: "build\release\Qt5OpenGL.dll"; DestDir: "{app}"
Source: "build\release\Qt5Network.dll"; DestDir: "{app}"
Source: "build\release\Qt5MultimediaWidgets.dll"; DestDir: "{app}"
Source: "build\release\Qt5Multimedia.dll"; DestDir: "{app}"
Source: "build\release\Qt5Gui.dll"; DestDir: "{app}"
Source: "build\release\Qt5Core.dll"; DestDir: "{app}"

Source: "build\release\libwinpthread-1.dll"; DestDir: "{app}"
Source: "build\release\libstdc++-6.dll"; DestDir: "{app}"
Source: "build\release\libGLESv2.dll"; DestDir: "{app}"
Source: "build\release\libgcc_s_sjlj-1.dll"; DestDir: "{app}"
Source: "build\release\libEGL.dll"; DestDir: "{app}"
Source: "build\release\icuuc49.dll"; DestDir: "{app}"
Source: "build\release\icuin49.dll"; DestDir: "{app}"
Source: "build\release\icudt49.dll"; DestDir: "{app}"

Source: "release\license.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\WarQuest\WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{commondesktop}\PlaatSoft WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{group}\WarQuest\Uninstaller"; Filename: "{uninstallexe}"

[Registry]
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "target"; ValueData: {app}; ValueType: string;  Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "username"; ValueData: {username}; ValueType: string;  Flags: uninsdeletekeyifempty

