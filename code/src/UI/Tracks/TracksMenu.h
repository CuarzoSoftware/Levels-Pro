#ifndef TRACKSMENU_H
#define TRACKSMENU_H

#include <UI/Tracks/TracksMenuTopBar.h>

class TracksMenu : public MainMenu
{
    Q_OBJECT
public:
    explicit TracksMenu();
    TracksMenuTopBar *topBar = new TracksMenuTopBar();


signals:

};

#endif // TRACKSMENU_H
