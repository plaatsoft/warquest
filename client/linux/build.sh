# Builds and installs the application locally
if valac --pkg gtk+-3.0 --pkg webkit2gtk-4.0 src/App.vala -o ~/.local/bin/nl.plaatsoft.warquest; then
    cp data/nl.plaatsoft.warquest.desktop ~/.local/share/applications
    nl.plaatsoft.warquest
fi
