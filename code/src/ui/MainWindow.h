#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Global/Global.h"

#include "TopBar.h"
#include "MainToolBar.h"

#include "LibraryMenu.h"
#include "InspectorMenu.h"
#include "MixerMenu.h"
#include "EditorMenu.h"
#include "TracksMenu.h"
#include "ListsEditorMenu.h"
#include "NotesMenu.h"
#include "LoopsMenu.h"
#include "MediaMenu.h"

#include "../Widgets/MenuSplitter.h"


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
