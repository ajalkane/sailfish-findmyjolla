# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

DEFINES += JOLLA_STORE_CRIPPLED

# The name of your application
TARGET = harbour-findjolla

CONFIG += sailfishapp
QT += dbus

SOURCES += \
    src/maininit.cpp \
    src/main.cpp \
    src/app/controlclient.cpp \
    src/app/processcontrol.cpp \
    src/app/appmaininit.cpp \
    src/app/qmlbackend.cpp \
    src/daemon/messagelistener.cpp \
    src/daemon/displayalarm.cpp \
    src/daemon/daemonmaininit.cpp \
    src/daemon/preferences.cpp \
    src/daemon/configuration.cpp \
    src/daemon/controlinterface.cpp

HEADERS += \
    src/maininit.h \
    src/app/controlclient.h \
    src/app/processcontrol.h \
    src/app/appmaininit.h \
    src/app/qmlbackend.h \
    src/daemon/messagelistener.h \
    src/daemon/displayalarm.h \
    src/daemon/daemonmaininit.h \
    src/daemon/preferences.h \
    src/daemon/configuration.h \
    src/daemon/controlinterface.h

OTHER_FILES += qml/findjolla.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/About.qml \
    rpm/harbour-findjolla.changes.in \
    rpm/harbour-findjolla.spec \
    rpm/harbour-findjolla.yaml \
    translations/*.ts \
    harbour-findjolla.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-findjolla-fi.ts \
    translations/harbour-findjolla-ru.ts

