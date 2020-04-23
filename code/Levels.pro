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
    src/UI/EditorMenu.h \
    src/UI/InspectorMenu.h \
    src/UI/LibraryMenu.h \
    src/UI/ListsEditorMenu.h \
    src/UI/LoopsMenu.h \
    src/UI/MainToolBar.h \
    src/UI/MainWindow.h \
    src/UI/MediaMenu.h \
    src/UI/MixerMenu.h \
    src/UI/NotesMenu.h \
    src/UI/TopBar.h \
    src/UI/TracksMenu.h \
    src/Widgets/CompactContainer.h \
    src/Widgets/MainMenu.h \
    src/Widgets/MenuSplitter.h \
    src/Widgets/ToggleButton.h

SOURCES += \
    src/Audio/AudioImporter.cpp \
    src/Global/Utils.cpp \
    src/UI/EditorMenu.cpp \
    src/UI/InspectorMenu.cpp \
    src/UI/LibraryMenu.cpp \
    src/UI/ListsEditorMenu.cpp \
    src/UI/LoopsMenu.cpp \
    src/UI/MainToolBar.cpp \
    src/UI/MainWindow.cpp \
    src/UI/MediaMenu.cpp \
    src/UI/MixerMenu.cpp \
    src/UI/NotesMenu.cpp \
    src/UI/TopBar.cpp \
    src/UI/TracksMenu.cpp \
    src/Widgets/CompactContainer.cpp \
    src/Widgets/MainMenu.cpp \
    src/Widgets/MenuSplitter.cpp \
    src/Widgets/ToggleButton.cpp \
    src/main.cpp





