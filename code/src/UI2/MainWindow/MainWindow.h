#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Global/Includes.h>

#include <Widgets/MenuSplitter.h>

#include <UI/MainWindow/TopBar.h>
#include <UI/MainWindow/MainToolBar.h>
#include <UI/Library/LibraryMenu.h>
#include <UI/Inspector/InspectorMenu.h>
#include <UI/Mixer/MixerMenu.h>
#include <UI/Editor/EditorMenu.h>
#include <UI/Tracks/TracksMenu.h>
#include <UI/Lists/ListsEditorMenu.h>
#include <UI/Notes/NotesMenu.h>
#include <UI/Loops/LoopsMenu.h>
#include <UI/Media/MediaMenu.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app);

    QApplication *levels;

    QWidget *mainWidget = new QWidget();
    TopBar *topBar = new TopBar();
    MainToolBar *toolBar = new MainToolBar();

    LibraryMenu *libraryMenu = new LibraryMenu();
    InspectorMenu *inspectorMenu = new InspectorMenu();
    MixerMenu *mixerMenu = new MixerMenu();
    EditorMenu *editorMenu = new EditorMenu();
    TracksMenu *tracksMenu = new TracksMenu();
    ListsEditorMenu *listsEditorMenu = new ListsEditorMenu();
    NotesMenu *notesMenu = new NotesMenu();
    LoopsMenu *loopsMenu = new LoopsMenu();
    MediaMenu *mediaMenu = new MediaMenu();

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    MenuSplitter *horizontalSplitter = new MenuSplitter(Qt::Horizontal);
    MenuSplitter *verticalSplitter = new MenuSplitter(Qt::Vertical);



    ~MainWindow();

public slots:
    void libraryBtnChanged(bool state);
    void inspectorBtnChanged(bool state);
    void mixerBtnChanged(bool state);
    void editorBtnChanged(bool state);
    void listsEditorBtnChanged(bool state);
    void notesBtnChanged(bool state);
    void loopsBtnChanged(bool state);
    void mediaBtnChanged(bool state);

private:
    void connectButtons();
    void loadDefaultStyle();


};
#endif // MAINWINDOW_H
