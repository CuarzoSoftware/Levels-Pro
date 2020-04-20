QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    src/audio/AudioImporter.cpp \
    src/main.cpp \
    src/ui/InspectorMenu.cpp \
    src/ui/LibraryMenu.cpp \
    src/ui/MainWindow.cpp \
    src/ui/TopBar.cpp \
    src/ui/TracksMenu.cpp \
    src/widgets/ToggleButton.cpp


HEADERS += \
    src/audio/AudioImporter.h \
    src/audio/test.h \
    src/global/Global.h \
    src/ui/InspectorMenu.h \
    src/ui/LibraryMenu.h \
    src/ui/MainWindow.h \
    src/ui/TopBar.h \
    src/ui/TracksMenu.h \
    src/widgets/ToggleButton.h


# Mac OS X
unix:!macx
{
    ICON = res/icon.icns
    QMAKE_INFO_PLIST = res/Info.plist

    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreFoundation.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreAudio.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioToolBox.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioUnit.framework/
    LIBS += -framework CoreFoundation
    LIBS += -framework CoreAudio
    LIBS += -framework AudioToolbox
    LIBS += -framework AudioUnit
}

# Linux
unix:!macx
{

}

# Window
win32
{

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    levels.qrc

DISTFILES += \
    res/Info.plist \
    res/icon.icns \
    res/stylesheet.qss
