;
; WarQuest windows installer configuration file.
;
; The file can be processed with "Inno Setup Compiler v5.5.4"
;
; All Copyrights Reserved (c) PlaatSoft 2008-2014

[Setup]
AppPublisher=PlaatSoft
AppPublisherURL=http://www.plaatsoft.nl
AppName=WarQuest
AppVerName=PlaatSoft WarQuest v1.6
AppVersion=1.6
AppCopyright=Copyright (C) 2008-2014 PlaatSoft

DefaultDirName={pf}\WarQuest
DefaultGroupName=PlaatSoft
UninstallDisplayIcon={app}\WarQuest.exe
Compression=lzma
SolidCompression=yes
OutputDir=release\

[Files]
Source: "build\release\icuuc51.dll"; DestDir: "{app}"
Source: "build\release\icuin51.dll"; DestDir: "{app}"
Source: "build\release\icudt51.dll"; DestDir: "{app}"
Source: "build\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "build\release\libstdc++-6.dll"; DestDir: "{app}"
Source: "build\release\libwinpthread-1.dll"; DestDir: "{app}"

Source: "build\release\imageformats\qgif.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qico.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qmng.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qtga.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"
Source: "build\release\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"

Source: "build\release\platforms\qminimal.dll"; DestDir: "{app}\platforms"
Source: "build\release\platforms\qoffscreen.dll"; DestDir: "{app}\platforms"
Source: "build\release\platforms\qwindows.dll"; DestDir: "{app}\platforms"

Source: "build\release\Qt5Core.dll"; DestDir: "{app}"
Source: "build\release\Qt5Gui.dll"; DestDir: "{app}"
Source: "build\release\Qt5Multimedia.dll"; DestDir: "{app}"
Source: "build\release\Qt5MultimediaWidgets.dll"; DestDir: "{app}"
Source: "build\release\Qt5Network.dll"; DestDir: "{app}"
Source: "build\release\Qt5OpenGL.dll"; DestDir: "{app}"
Source: "build\release\Qt5PrintSupport.dll"; DestDir: "{app}"
Source: "build\release\Qt5Positioning.dll"; DestDir: "{app}"
Source: "build\release\Qt5Qml.dll"; DestDir: "{app}"
Source: "build\release\Qt5Quick.dll"; DestDir: "{app}"
Source: "build\release\Qt5Sensors.dll"; DestDir: "{app}"
Source: "build\release\Qt5Sql.dll"; DestDir: "{app}"
Source: "build\release\Qt5WebKit.dll"; DestDir: "{app}"
Source: "build\release\Qt5WebKitWidgets.dll"; DestDir: "{app}"
Source: "build\release\Qt5Widgets.dll"; DestDir: "{app}"

Source: "build\release\WarQuest.exe"; DestDir: "{app}"

Source: "release\license.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\WarQuest\WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{commondesktop}\PlaatSoft WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{group}\WarQuest\Uninstaller"; Filename: "{uninstallexe}"

[Registry]
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "target"; ValueData: {app}; ValueType: string;  Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "username"; ValueData: {username}; ValueType: string;  Flags: uninsdeletekeyifempty

