#ifndef TRACKSMENU_H
#define TRACKSMENU_H

#include <UI/Tracks/TracksMenuTopBar.h>
#include <UI/Tracks/TracksLeftMenu.h>
#include <UI/Tracks/TracksRightMenu.h>

#include <QSplitter>

class Core;

class TracksMenu : public MainMenu
{
    Q_OBJECT
public:
    explicit TracksMenu(Core *_core);

    // Tracks top toolbar
    TracksMenuTopBar *topBar = new TracksMenuTopBar();

    // Horizontal Splitter
    QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal);

    // Left Menu ( Tracks controls )
    TracksLeftMenu *leftMenu = new TracksLeftMenu(this);

    // Right Menu ( Tracks and regions View )
    TracksRightMenu *rightMenu = new TracksRightMenu();

    void wheelEvent(QWheelEvent*event);

    Core *core;

signals:

};

#endif // TRACKSMENU_H
