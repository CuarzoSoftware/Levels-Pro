#include "TracksRightMenu.h"
#include <QVariant>

/*!
    \class TracksRightMenu
    \brief The TracksRightMenu class...

    \inheaderfile UI/Tracks/TracksRightMenu.h
    \ingroup UI
    \inmodule UI

    \inherits QFrame
*/

TracksRightMenu::TracksRightMenu()
{

    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);


    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    verticalLayout->addWidget(timeRuler);
    verticalLayout->addSpacing(18);
    verticalLayout->addWidget(tracksView,1);

    tracksLayout->setMargin(0);
    tracksLayout->setSpacing(0);
    tracksLayout->addSpacing(100);
    tracksLayout->addStretch(1);

}


void TracksRightMenu::addTrack(TrackBand *newTrack)
{
    tracksLayout->insertWidget(0,newTrack);
}
