#include "MenuTopBar.h"

MenuTopBar::MenuTopBar()
{
    // Asigna una altura fija
    setFixedHeight(30);

    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","menuTopBar");
}
