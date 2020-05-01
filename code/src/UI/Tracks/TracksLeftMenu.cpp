#include "TracksLeftMenu.h"
#include <QVariant>

TracksLeftMenu::TracksLeftMenu(TracksMenu *tracksMenu)
{
    // Stores the tracks menu reference
    menu = tracksMenu;

    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);
    setProperty("class","tracksLeftMenu");
    setMaximumWidth(400);

    // Configure vertical layout
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    // Adds the buttons to the topbar
    topBar->horizontalLayout->addWidget(addTrackBtn);
    topBar->horizontalLayout->addWidget(duplicateTrackBtn);
    topBar->horizontalLayout->addStretch(1);
    topBar->horizontalLayout->addWidget(globalTracksBtn);

    // Configure topbar
    topBar->setFixedHeight(40);
    topBar->horizontalLayout->setContentsMargins(6,0,6,0);
    topBar->horizontalLayout->setSpacing(6);

    // Configure scroll area
    tracksScrollArea->setWidget(tracksWidget);
    tracksScrollArea->setWidgetResizable(true);
    tracksScrollArea->setProperty("class","scrollArea");
    tracksScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tracksScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // Configure tracks vertical layout
    tracksLayout->setMargin(0);
    tracksLayout->setSpacing(0);
    tracksLayout->addStretch(1);

    // Adds the topbar and the scroll area to the layout
    verticalLayout->addWidget(topBar);
    verticalLayout->addWidget(tracksScrollArea);



    for(int i = 0; i < 20; i++)
    {
        addTrack(new TrackController());
    }


}

void TracksLeftMenu::addTrack(TrackController *newTrackController)
{
    trackControllers.append(newTrackController);
    tracksLayout->insertWidget(0,newTrackController);
}
