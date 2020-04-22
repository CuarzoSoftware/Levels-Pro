QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS



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



HEADERS += \
    src/Audio/AudioImporter.h \
    src/Audio/Test.h \
    src/Global/Color.h \
    src/Global/Global.h \
    src/Global/Utils.h \
    src/UI/InspectorMenu.h \
    src/UI/LibraryMenu.h \
    src/UI/MainWindow.h \
    src/UI/TopBar.h \
    src/UI/TracksMenu.h \
    src/Widgets/CompactContainer.h \
    src/Widgets/ToggleButton.h

SOURCES += \
    src/Audio/AudioImporter.cpp \
    src/Global/Utils.cpp \
    src/UI/InspectorMenu.cpp \
    src/UI/LibraryMenu.cpp \
    src/UI/MainWindow.cpp \
    src/UI/TopBar.cpp \
    src/UI/TracksMenu.cpp \
    src/Widgets/CompactContainer.cpp \
    src/Widgets/ToggleButton.cpp \
    src/main.cpp





