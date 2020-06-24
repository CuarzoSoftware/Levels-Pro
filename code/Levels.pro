QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Inccludes in project
INCLUDEPATH += $$PWD/src

# Mac OS X
macx {
    ICON = res/icons/icon.icns
    QMAKE_INFO_PLIST = res/mac/Info.plist

    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreFoundation.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreAudio.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioToolBox.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AudioUnit.framework/
    QMAKE_LFLAGS += -F /System/Library/Frameworks/AppKit.framework/

    LIBS += -framework CoreFoundation
    LIBS += -framework CoreAudio
    LIBS += -framework AudioToolbox
    LIBS += -framework AudioUnit
    LIBS += -framework AppKit

    HEADERS += \
    src/Audio/AudioImporter.h \
    src/Audio/Test.h \

    SOURCES += \
        src/Audio/AudioImporter.cpp \

    OBJECTIVE_SOURCES += src/Audio/Test.mm \
}

# Linux
unix:!macx {

}

# Window
win32 {

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    levels.qrc

# src/Widgets/OpenGLRuler.h \
# src/Widgets/OpenGLRuler.cpp \

HEADERS += \
    src/Audio/AUPluginUI.h \
    src/Audio/Core.h \
    src/Audio/Region.h \
    src/Audio/TimeSettings.h \
    src/Audio/Track.h \
    src/Global/Color.h \
    src/Global/Utils.h \
    src/UI/Editor/EditorMenu.h \
    src/UI/Inspector/InspectorMenu.h \
    src/UI/Library/LibraryMenu.h \
    src/UI/Lists/ListsEditorMenu.h \
    src/UI/Loops/LoopsMenu.h \
    src/UI/MainWindow/MainToolBar.h \
    src/UI/MainWindow/MainWindow.h \
    src/UI/MainWindow/TopBar.h \
    src/UI/Media/MediaMenu.h \
    src/UI/Mixer/MixerMenu.h \
    src/UI/Notes/NotesMenu.h \
    src/UI/Tracks/TrackBand.h \
    src/UI/Tracks/TrackController.h \
    src/UI/Tracks/TracksLeftMenu.h \
    src/UI/Tracks/TracksMenu.h \
    src/UI/Tracks/TracksMenuTopBar.h \
    src/UI/Tracks/TracksRightMenu.h \
    src/Widgets/CompactContainer.h \
    src/Widgets/HScrollBar.h \
    src/Widgets/Icon.h \
    src/Widgets/IconSlider.h \
    src/Widgets/MainMenu.h \
    src/Widgets/MenuSplitter.h \
    src/Widgets/MenuTopBar.h \
    src/Widgets/Ruler.h \
    src/Widgets/Select.h \
    src/Widgets/TimeRuler.h \
    src/Widgets/ToggleButton.h

SOURCES += \
    src/Audio/AUPluginUI.mm \
    src/Audio/Core.cpp \
    src/Audio/Region.cpp \
    src/Audio/Track.cpp \
    src/Global/Utils.cpp \
    src/UI/Editor/EditorMenu.cpp \
    src/UI/Inspector/InspectorMenu.cpp \
    src/UI/Library/LibraryMenu.cpp \
    src/UI/Lists/ListsEditorMenu.cpp \
    src/UI/Loops/LoopsMenu.cpp \
    src/UI/MainWindow/MainToolBar.cpp \
    src/UI/MainWindow/MainWindow.cpp \
    src/UI/MainWindow/TopBar.cpp \
    src/UI/Media/MediaMenu.cpp \
    src/UI/Mixer/MixerMenu.cpp \
    src/UI/Notes/NotesMenu.cpp \
    src/UI/Tracks/TrackBand.cpp \
    src/UI/Tracks/TrackController.cpp \
    src/UI/Tracks/TracksLeftMenu.cpp \
    src/UI/Tracks/TracksMenu.cpp \
    src/UI/Tracks/TracksMenuTopBar.cpp \
    src/UI/Tracks/TracksRightMenu.cpp \
    src/Widgets/CompactContainer.cpp \
    src/Widgets/HScrollBar.cpp \
    src/Widgets/Icon.cpp \
    src/Widgets/IconSlider.cpp \
    src/Widgets/MainMenu.cpp \
    src/Widgets/MenuSplitter.cpp \
    src/Widgets/MenuTopBar.cpp \
    src/Widgets/Ruler.cpp \
    src/Widgets/Select.cpp \
    src/Widgets/TimeRuler.cpp \
    src/Widgets/ToggleButton.cpp \
    src/main.cpp

DISTFILES += \
    res/svg/cursor.svg \
    res/svg/pencil.svg








