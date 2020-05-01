#ifndef TRACKSLEFTMENU_H
#define TRACKSLEFTMENU_H

#include <Widgets/MenuTopBar.h>
#include <Widgets/ToggleButton.h>

#include <UI/Tracks/TrackController.h>

#include <QScrollArea>
#include <QList>

class TracksMenu;

class TracksLeftMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksLeftMenu(TracksMenu *tracksMenu);

    // Reference to the Tracks Menu
    TracksMenu *menu;

    // Vertical Layout
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    // Vertical Scroll
    QScrollArea *tracksScrollArea = new QScrollArea();

    // Tracks widget container
    QFrame *tracksWidget = new QFrame();

    // Tracks vertical layout
    QVBoxLayout *tracksLayout = new QVBoxLayout(tracksWidget);

    // Topbar ( Contains add, duplicare, etc buttons )
    MenuTopBar *topBar = new MenuTopBar();

    // Topbar buttons
    ToggleButton *addTrackBtn = new ToggleButton(6,new Icon(":res/svg/plus.svg",QSize(13,13)));
    ToggleButton *duplicateTrackBtn = new ToggleButton(6,new Icon(":res/svg/duplicate.svg",QSize(13,13)));
    ToggleButton *globalTracksBtn = new ToggleButton(6,new Icon(":res/svg/window-down.svg",QSize(13,13)));

    // Track Controllets List
    QList<TrackController*>trackControllers;

    // Adds a new track
    void addTrack(TrackController *newTrackController);




signals:

};

#endif // TRACKSLEFTMENU_H
