#include "TrackController.h"
#include <QVariant>

/*!
    \class TrackController
    \brief The TrackController class...

    \inheaderfile UI/Tracks/TrackController.h
    \ingroup UI
    \inmodule UI

    \inherits QWidget
*/


TrackController::TrackController()
{
    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Sets the style class
    setProperty("class","trackController");

    // Sets fixed height
    setFixedHeight(50);
}
