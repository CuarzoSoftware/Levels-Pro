#include "TrackController.h"
#include <QVariant>

TrackController::TrackController()
{
    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Sets the style class
    setProperty("class","trackController");

    // Sets fixed height
    setFixedHeight(50);
}
