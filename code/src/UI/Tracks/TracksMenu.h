#ifndef TRACKSMENU_H
#define TRACKSMENU_H

#include <Widgets/MainMenu.h>
#include <Widgets/CompactContainer.h>
#include <Widgets/Select.h>
#include <Widgets/ToggleButton.h>

class TracksMenu : public MainMenu
{
    Q_OBJECT
public:
    explicit TracksMenu();

    CompactContainer *editSelectsContainer = new CompactContainer();
    Select *editionSelect = new Select("Edition");
    Select *functionsSelect = new Select("Functions");
    Select *visualizationSelect = new Select("Visualization");

    CompactContainer *editModesContainer = new CompactContainer();
    ToggleButton *automationBtn = new ToggleButton(1,new Icon(":res/svg/nodes.svg",QSize(24,24)));
    ToggleButton *flexBtn = new ToggleButton(1,new Icon(":res/svg/stretch.svg",QSize(24,24)));

    ToggleButton *headTrackerBtn = new ToggleButton(3,new Icon(":res/svg/head.svg",QSize(20,20)));

    CompactContainer *cursorModesContainer = new CompactContainer();
    Select *leftBtnSelect = new Select(new Icon(":res/svg/cursor.svg",QSize(12,12)),6);
    Select *rightBtnSelect = new Select(new Icon(":res/svg/pencil.svg",QSize(12,12)),6);

    Select *confSelect = new Select(new Icon(":res/svg/settings-4.svg",QSize(12,12)),6);

    ToggleButton *wavesZoomBtn = new ToggleButton(1,new Icon(":res/svg/waves-peak.svg",QSize(24,24)));

    CompactContainer *zoomContainer = new CompactContainer();
    ToggleButton *verticalZoomBtn = new ToggleButton(5,new Icon(":res/svg/zoom-vertical.svg",QSize(16,16)));
    ToggleButton *horizontalZoomBtn = new ToggleButton(5,new Icon(":res/svg/zoom-horizontal.svg",QSize(16,16)));

private:
    void setupTopBar();

signals:

};

#endif // TRACKSMENU_H
