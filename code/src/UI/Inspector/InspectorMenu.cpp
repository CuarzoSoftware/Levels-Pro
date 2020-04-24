#include "InspectorMenu.h"

InspectorMenu::InspectorMenu()
{
    // Asigna un ancho fijo
    setFixedWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
