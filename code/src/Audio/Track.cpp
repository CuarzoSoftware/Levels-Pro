#include "Track.h"

/*!
    \class Track
    \brief The Track class...

    \inheaderfile Audio/Track.h
    \ingroup Audio
    \inmodule Audio

    \inherits QObject
*/

Track::Track()
{
    trackBand->setFixedHeight(height);
    controller->setFixedHeight(height);
}
