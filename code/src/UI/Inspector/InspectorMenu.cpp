#include "InspectorMenu.h"

/*!
    \class InspectorMenu
    \brief The InspectorMenu class...

    \inheaderfile UI/Inspector/InspectorMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

InspectorMenu::InspectorMenu()
{
    // Asigna un ancho fijo
    setFixedWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
