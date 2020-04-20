#include "InspectorMenu.h"

InspectorMenu::InspectorMenu()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","inspectorMenu");

    // Asigna un ancho fijo
    setFixedWidth(200);
}
