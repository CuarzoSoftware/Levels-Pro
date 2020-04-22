#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Global/Global.h"

#include "TopBar.h"
#include "LibraryMenu.h"
#include "InspectorMenu.h"
#include "TracksMenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app);

    QApplication *levels;

    QWidget *mainWidget = new QWidget();
    TopBar *topBar = new TopBar();
    LibraryMenu *libraryMenu = new LibraryMenu();
    InspectorMenu *inspectorMenu = new InspectorMenu();
    TracksMenu *tracksMenu = new TracksMenu();

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QSplitter *horizontalSplitter = new QSplitter();


    void loadDefaultStyle();

    ~MainWindow();
};
#endif // MAINWINDOW_H
