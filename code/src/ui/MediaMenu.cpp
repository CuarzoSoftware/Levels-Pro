#include "MediaMenu.h"

MediaMenu::MediaMenu()
{
    // Asigna un ancho mínimo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}
