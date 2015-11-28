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

# The name of your application
TARGET = harbour-findjolla

CONFIG += sailfishapp
QT += dbus

SOURCES += src/findjolla.cpp \
    src/messagelistener.cpp \
    src/displayalarm.cpp

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
TRANSLATIONS += translations/findjolla-de.ts

HEADERS += \
    src/messagelistener.h \
    src/displayalarm.h

