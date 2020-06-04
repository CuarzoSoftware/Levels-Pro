#include "MediaMenu.h"

/*!
    \class MediaMenu
    \brief The MediaMenu class...

    \inheaderfile UI/Media/MediaMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

MediaMenu::MediaMenu()
{
    // Asigna un ancho mínimo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
