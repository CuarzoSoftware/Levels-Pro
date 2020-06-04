#include "NotesMenu.h"

/*!
    \class NotesMenu
    \brief The NotesMenu class...

    \inheaderfile UI/Notes/NotesMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

NotesMenu::NotesMenu()
{
    // Asigna un ancho mínimo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
