#ifndef TRACKSMENU_H
#define TRACKSMENU_H

#include <UI/Tracks/TracksMenuTopBar.h>
#include <UI/Tracks/TracksLeftMenu.h>
#include <UI/Tracks/TracksRightMenu.h>

#include <Widgets/ScrollBar.h>

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

    // Vertical Scroll Bar
    ScrollBar *verticalScrollBar = new ScrollBar(Qt::Vertical,this);

    // Horizontal Scroll Bar
    ScrollBar *horizontalScrollBar = new ScrollBar(Qt::Horizontal,this);

    Core *core;

private:
    virtual void wheelEvent(QWheelEvent*event) override;
    virtual bool eventFilter(QObject *object, QEvent *event) override;

};

#endif // TRACKSMENU_H
