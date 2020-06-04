#include "LibraryMenu.h"

/*!
    \class LibraryMenu
    \brief The LibraryMenu class...

    \inheaderfile UI/Library/LibraryMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

LibraryMenu::LibraryMenu()
{
    // Asigna un ancho mínimo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();

}
