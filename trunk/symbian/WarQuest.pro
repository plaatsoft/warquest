# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian {
    TARGET.CAPABILITY += LocalServices NetworkServices ReadDeviceData
    TARGET.EPOCHEAPSIZE = 0x100000 \
                          0x2500000
    TARGET.EPOCSTACKSIZE = 0x14000

    my_deployment.pkg_prerules += vendorinfo
    vendorinfo += "%{\"PlaatSoft\"}" ":\"PlaatSoft\""

    DEPLOYMENT += my_deployment

    TARGET.UID3 = 0x2005ebe3

    ICON = warquest.svg
}

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
CONFIG += mobility
MOBILITY += systeminfo

QT += core gui webkit network

SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
    resource.qrc
