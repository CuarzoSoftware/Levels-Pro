#include "ListsEditorMenu.h"

/*!
    \class ListsEditorMenu
    \brief The ListsEditorMenu class...

    \inheaderfile UI/Lists/ListsEditorMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/
ListsEditorMenu::ListsEditorMenu()
{
    // Asigna un ancho fijo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
