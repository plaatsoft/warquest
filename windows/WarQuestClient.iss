;
; RedSquare windows installer configurationm file.
;
; The file can be processed with "Inno Setup Compiler v5.3.11"
;
; All Copyrights Reserved (c) PlaatSoft 2008-2011

[Setup]
AppPublisher=PlaatSoft
AppPublisherURL=http://www.plaatsoft.nl
AppName=WarQuest
AppVerName=PlaatSoft WarQuest v1.4
AppVersion=1.4
AppCopyright=Copyright (C) 2008-2012 PlaatSoft

DefaultDirName={pf}\WarQuest
DefaultGroupName=PlaatSoft
UninstallDisplayIcon={app}\WarQuest.exe
Compression=lzma
SolidCompression=yes
OutputDir=release\

[Files]
Source: "src\release\WarQuest.exe"; DestDir: "{app}"
Source: "src\release\mingwm10.dll"; DestDir: "{app}"
Source: "src\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "src\release\mingwm10.dll"; DestDir: "{app}"
Source: "src\release\QtCore4.dll"; DestDir: "{app}"
Source: "src\release\QtGui4.dll"; DestDir: "{app}"
Source: "src\release\QtNetwork4.dll"; DestDir: "{app}"
Source: "src\release\QtWebKit4.dll"; DestDir: "{app}"
Source: "src\release\phonon4.dll"; DestDir: "{app}"
Source: "src\release\imageformats\qgif4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qico4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qjpeg4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qmng4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qsvg4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qtiff4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\license.txt"; DestDir: "{app}"; Flags: isreadme
Source: "src\release\libeay32.dll"; DestDir: "{app}"
Source: "src\release\libssl32.dll"; DestDir: "{app}"
Source: "src\release\ssleay32.dll"; DestDir: "{app}"

[Icons]
Name: "{group}\WarQuest\WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{commondesktop}\PlaatSoft WarQuest"; Filename: "{app}\WarQuest.exe"
Name: "{group}\WarQuest\Uninstaller"; Filename: "{uninstallexe}"

[Registry]
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "target"; ValueData: {app}; ValueType: string;  Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\PlaatSoft\WarQuest"; ValueName: "username"; ValueData: {username}; ValueType: string;  Flags: uninsdeletekeyifempty

