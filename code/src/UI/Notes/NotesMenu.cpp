#include "NotesMenu.h"

NotesMenu::NotesMenu()
{
    // Asigna un ancho mínimo
    setMinimumWidth(200);

    // Asigna el ancho máximo
    setMaximumWidth(600);

    // Lo esconde inicialmente
    hide();
}