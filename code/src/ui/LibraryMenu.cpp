#include "LibraryMenu.h"

LibraryMenu::LibraryMenu()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","libraryMenu");

    // Asigna un ancho fijo
    setFixedWidth(200);
}
